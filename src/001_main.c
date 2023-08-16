#include "global.h"
#include "001_main.h"
#include "002_kernel.h"
//#include "son.h" 
//#include "keys.h"
//#include "timer.h"
#include <sys/resource.h> 
#include <dlfcn.h>
 
#include <unistd.h> /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html */ /* https://en.wikipedia.org/wiki/Unistd.h */ 

// RL: GDB detection 
#include <sys/types.h>
#include <sys/ptrace.h>
//int ptrace(int request, pid_t pid, caddr_t addr, int data);
// RL: This should be in a child? 

#include "lib.ci"
//#include "lib__llfixed.ci"

#include <anime.h>
#include "anime_database.h"



// RL: This file contains all the system stuffs. 
//     Anything here is not related to the program per se. 
//     And is done only once. 


static const char stdout_log_subdir[]   = LOGDIR; 
static const char stdout_log_filename[] = "stdout.log"; 
static       char stdout_log_buffer[1 << 12] = {}; 
static       int    main__stdlog_d = -1; 
static const char * main__stdlog_filename = NULL; 

static int  main__break_argv0_into_progname_and_progdir(const char * argv0, char * * progname_r, char * * progdir_r, char * buffer, const int16_t buffer_bytesize); 
static int  main__look_for_progdir_in_env_path(const char * argv0, char * * progdir_r, char * buffer, const int16_t buffer_bytesize); 
static int  main__move_to_progdir(const char * progdir); 
static int  main__reassign_stdout_to_logfile(const char * progdir, const char * log_subdir, const char * log_filename, char * buffer, const int16_t buffer_bytesize); 
static void main_proctitle_set(void); 
static void main_locale_set(void); 
static void main_rand_init(void); 
static void main_date_print(void); 
static void main_gcc_print(void); 
static void main_arch_print(void); 
static void main_args_print(const int argc, const char * argv[]); 
static void main_win_print(void); 

const char *  main_argv0 = NULL; 
      int16_t main_argv0__bytesize = -1; 
      char *  main_argv0__progname = NULL; // RL: INVARIANT: It should not hold any slash character '/'. 
      int16_t main_argv0__progname__bytesize = -1; 
      char *  main_argv0__progdir  = NULL; // RL: INVARIANT: The last char should be the slash character '/', unless it is root. 
      int16_t main_argv0__progdir__bytesize  = -1; 

extern char **environ; 

#define LOCAL_ALLOCA__DECLARE(LOCAL_ALLOCA_SIZEOF)			\
  enum { LOCAL_ALLOCA__BYTESIZE = (LOCAL_ALLOCA_SIZEOF) }; char local_alloca__mem[LOCAL_ALLOCA__BYTESIZE]; uint16_t local_alloca__left = LOCAL_ALLOCA__BYTESIZE; uint16_t local_alloca__used = 0; uint16_t local_alloca__requested; 

#define LOCAL_ALLOCA(REQUESTED_SIZEOF)					\
  (local_alloca__requested = (REQUESTED_SIZEOF), ((local_alloca__requested > local_alloca__left) ? NULL : (local_alloca__left -= local_alloca__requested, local_alloca__used += local_alloca__requested,  local_alloca__mem + local_alloca__used - local_alloca__requested))) 

int main(const int argc, const char * argv[]) {
  //int _SDL_main(int argc, char * argv[]) {
  LOCAL_ALLOCA__DECLARE(INT16_MAX); 
  int retour = -1;
  
  if (1 > argc) { 
    write_string(STDERR_FILENO, "Does not make sense - ARGC is lower than 1: "); 
    write_long_long_int(STDERR_FILENO, argc); 
    write_eol(STDERR_FILENO); 
    return 0; 
  }; 
  main_argv0 = argv[0]; 
  main_argv0__bytesize = 1 + strlen(main_argv0); 
  goto label__body; 

 label__exit: { 
    fflush(NULL); 
    return 0; 
  }; 

#if 0 
  label__error__cannot_move_to_root_dir: { 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "I could not change the current directory to the one holding the program: '%s' " "\n", __func__, main_argv0); 
    return -1; 
  }; 
  
  label__error__cannot_reassign_stdout_to_logfile: {
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Failed to reassign stdout to log file: '%s' " "\n", __func__, stdout_log_filename); 
    return -2; 
  }; 
#endif 
  
  
 label__body: { 
    // RL: First thing to do: 
    // Change current-working-directory to the directory containing the program («mouton-dir»), 
    // in order to read data and write logs. 
    for (;;) { 
      {
	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "local_alloca__left: '%d' " "\n", __func__, (int) local_alloca__left); fflush(NULL); 
	const int16_t used_size = main__break_argv0_into_progname_and_progdir(main_argv0, &main_argv0__progname, &main_argv0__progdir, local_alloca__mem + local_alloca__used, local_alloca__left); 
	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "main__break_argv0_into_progname_and_progdir: '%d' " "\n", __func__, (int) used_size); fflush(NULL); 
	if (0 >  used_size) break; 
	if (0 == used_size) break; // RL: ??? Does not make sense. 
	local_alloca__used += used_size; 
	local_alloca__left -= used_size; 
      }; 
      
      if (NULL == main_argv0__progdir) { 
	const int16_t used_size = main__look_for_progdir_in_env_path(main_argv0, &main_argv0__progdir, local_alloca__mem + local_alloca__used, local_alloca__left); 
	if (0 >  used_size) break; 
	if (0 == used_size) break; 
	local_alloca__used += used_size; 
	local_alloca__left -= used_size; 
      }; 

      if (NULL == main_argv0__progdir) break; 
      
      //if (0 != main__change_to_root_dir(main_argv0)) { goto label__error__cannot_move_to_root_dir; }; 
      if (0 != main__move_to_progdir(main_argv0__progdir)) { 
	fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "I could not move to the program directory: '%s' " "\n", __func__, main_argv0__progdir); 
	main_argv0__progdir = NULL; 
	break; 
      }; 
      break; 
    }; 
  
#if 1 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "main_argv0: '%s' " "\n", __func__, main_argv0); fflush(NULL); 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "main_argv0__progname: '%s' " "\n", __func__, main_argv0__progname); fflush(NULL); 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "main_argv0__progdir: '%s' " "\n", __func__, main_argv0__progdir); fflush(NULL); 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "CWD: '%s' " "\n", __func__, getcwd(local_alloca__mem + local_alloca__used, local_alloca__left)); fflush(NULL); 
#endif 
    
    // RL: LOG FILE: Reassigning stdout to log-file 
    for (;;) { 
      const int16_t used_size = main__reassign_stdout_to_logfile(main_argv0__progdir, stdout_log_subdir, stdout_log_filename, local_alloca__mem + local_alloca__used, local_alloca__left); 
      if (0 > used_size) break; 
      local_alloca__used += used_size; 
      local_alloca__left -= used_size; 
      break; 
    }; 
    
    // RL: Everything is UTF-8 unless specified otherwise. 
    printf("☺☺☺☺☺☺" "\n"); 
    printf("Cela fait plaisir de vous voir." "\n"); 
    fprintf(stdout, "Démarrage du jeu!!!\n\n"); 
    
    main_locale_set(); 
    main_rand_init(); 
    main_date_print(); 
    main_gcc_print(); 
    main_arch_print(); 
    main_proctitle_set(); 
    main_args_print(argc, argv); 
    main_win_print(); 

    if (true) { 
      const char * anime_to_load[] = { "bob.anime", "heros.anime", "pere.anime", "brigitte.anime.ci", "juliette.anime", "mouton.anime", "chaman.anime", "dinotore.anime", "heros.anime", "pecu.anime", "prokofiev.anime", "sang.anime", "chapinmechant.anime", "fantome.anime", "moutonmechant.anime", "pierre.anime", "saintexupery.anime", "y.anime", "m.anime", "c.anime", "a.anime", "bizarre1.anime", "bizarre2.anime", "bucheron.anime", "chapin.anime", "eclaboussures.anime", "homme_bizarre.anime", "puit_boss.anime", "squelette.anime", NULL }; 
      for (int i = 0; ; i++) { 
	const char * anime_filename = anime_to_load[i]; 
	if (NULL == anime_filename) break; 
	const anime_t * one_anime; 
	one_anime = anime_database__load__compile_time(anime_filename); 
      }; 
    }
    else {
      printf("<<< main" "\n"); 
      printf("===============================================================================" "\n"); 
      fflush(NULL); 
      for (;;) { 
	retour = Kernel_Init(); fflush(NULL); if (retour < 0) { break; }; 
	{ dprintf(fileno(stdout), "STDOUT BUFFER: %p\n", stdout -> _bf._base); }; 
	
      retour = Kernel_Run(); 
      Kernel_Dispose(); 
      break; 
      }; 
      printf("===============================================================================" "\n"); 
      printf(">>> main" "\n"); 
    }; 
    
    fprintf(stdout, "Fin du jeu!\n"); 
    
    goto label__exit; 
  }; 
}; 




int main__look_for_progdir_in_env_path(const char * argv0, char * * progdir_r, char * buffer, const int16_t buffer_bytesize) { 
  *progdir_r = NULL; 
  if (NULL ==  argv0) return -1; 
  if ('\0' == *argv0) return -2; 
  const int16_t argv0_bytesize = 1 + strlen(argv0); 
  if (buffer_bytesize < argv0_bytesize) return -3; 
  goto label__body; 

  label__no_env_path: { 
    *progdir_r = NULL; 
    return 0; 
  }; 
  
  label__body: { 
    const char * env_path = getenv("PATH"); 
    if (NULL == env_path) goto label__no_env_path; 
    int16_t pos = 0; 
    for (;;) { 
      const char * cur_pos = env_path + pos; 
      const char * colon_cstr = strchr(cur_pos, ':'); 
      if (NULL == colon_cstr) goto label__no_env_path; 
      const int16_t cur_bytesize = colon_cstr - cur_pos; 
      const int16_t full_bytesize = cur_bytesize + 1 + argv0_bytesize; 
      if (buffer_bytesize < full_bytesize) return -4; 
      bcopy(cur_pos, buffer, cur_bytesize); 
      int16_t buffer_nb = cur_bytesize; 
      for (;;) { 
	if (1 >= buffer_nb) break; 
	if ('/' != *(buffer + buffer_nb - 1)) break; 
	buffer_nb--; 
      }; 
      assert(buffer_nb > 0); 
      assert((buffer_nb == 1) ? (*buffer == '/') : (*(buffer + buffer_nb - 1) != '/')); 
      *(buffer + buffer_nb) = '/'; 
      const int16_t slash_pos = buffer_nb; 
      buffer_nb++; 
      bcopy(argv0, buffer + buffer_nb, argv0_bytesize); 
      buffer_nb += argv0_bytesize; 
      assert('\0' == *(buffer + buffer_nb - 1)); 
      const int found_retval = access(buffer, /*amode*/0); 
      if (0 != found_retval) continue; 
      
      // Found 
      *(buffer + slash_pos) = '\0'; 
      *progdir_r = buffer; 
      return buffer_nb; 
    }; 
    
  }; 

}; 

int main__break_argv0_into_progname_and_progdir(const char * argv0, char * * progname_r, char * * progdir_r, char * buffer, const int16_t buffer_bytesize) { 
  *progdir_r = NULL; 
  *progname_r = NULL; 
  if (NULL ==  argv0) return -1; 
  if ('\0' == *argv0) return -2; 
  
  const int16_t argv0_bytesize = 1 + strlen(argv0); 
  if (buffer_bytesize < 1 + argv0_bytesize) { 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "argv0_bytesize: '%d' " "\n", __func__, (int) argv0_bytesize); fflush(NULL); 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "buffer_bytesize: '%d' " "\n", __func__, (int) buffer_bytesize); fflush(NULL); 
    return -3; 
  }; 
  
  const char * argv0_last_slash = strrchr(argv0, '/'); 
  
  if (NULL == argv0_last_slash) { 
    strlcpy(buffer, argv0, buffer_bytesize); 
    *progname_r = buffer; 
    *progdir_r = NULL; 
    return argv0_bytesize; 
  }; 
  
  assert('/' == *argv0_last_slash); 
  strlcpy(buffer, argv0_last_slash + 1, buffer_bytesize); 
  *progname_r = buffer; 
  const int16_t progname_bytesize = 1 + strlen(argv0_last_slash + 1); 
  // RL: Eating up all the trailing slashes. 
  // RL: Beware of the case of the root directory. 
  for (;;) { 
    if (argv0_last_slash == argv0) { 
      *(buffer + progname_bytesize    ) =  '/'; 
      *(buffer + progname_bytesize + 1) = '\0'; 
      *progdir_r = buffer + progname_bytesize; 
      return progname_bytesize + 2; 
    }; 
    
    argv0_last_slash--; 
    if (*argv0_last_slash == '/') continue; 
    
    { 
      const int16_t dir_len = (argv0_last_slash - argv0) + 1; 
      bcopy(argv0, buffer + progname_bytesize, dir_len); 
      *(buffer + progname_bytesize + dir_len) = '\0'; 
      *progdir_r = buffer + progname_bytesize; 
      return progname_bytesize + dir_len + 1; 
    }; 
    
  }; 
  
}; 


static int main__move_to_progdir(const char * progdir) { 
  if (NULL ==  progdir) return -1; 
  if ('\0' == *progdir) return -2; 
  if (0 != chdir(progdir)) return -3; 
  return 0; 
};

#if 0
static int main__change_to_root_dir(const char * argv0) { 
  enum { path_buffer_bytesize = 1 << 12 }; 
  if (path_buffer_bytesize < main_argv0__bytesize) { return -1; }; 

  char path[path_buffer_bytesize]; 
  strlcpy(path, argv0, path_buffer_bytesize); 
  
  char * program_name = strrchr(path, '/'); 
  
  if (NULL == program_name) { 
    // FIXME TODO XXX 
    // It means that the software is in the PATH variable. 
    return -2; 
  }; 
  
  *program_name = '\0';

  if (0 != chdir(path)) { return -3; }; 
  
  return 0; 
};
#endif 


#if 0 
{
#if 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " stdout [ 'FILE *' before being reopened to the log file ] = %p " "\n", __func__, stdout); 
#endif 
#if 0 
    { dprintf(fileno(stdout), "STDOUT BUFFER: %p\n", stdout -> _bf._base); }; 
    { dprintf(fileno(stdout), "STDERR BUFFER: %p\n", &stderr -> _bf); }; 
#endif 
}; 
    // RL: Second, reopening 
    //  --- man 3 freopen --- 
    // The freopen() function opens the file whose name is the string pointed to by path. 
    // The original stream (if it exists) is closed. 
    // The primary use of the freopen() function is to change the file associated with a standard text stream (stderr, stdin, or stdout). 
    if (NULL == freopen(stdout_log_filename, "wb", stdout)) goto label__error__cannot_reopen_stdout; 
    // RL: Third, assigning a buffer. 
    //setvbuf(stdout, stdout_buffer, _IONBF, sizeof(stdout_buffer)); // RL: Unbuffered. 
    //setvbuf(stdout, stdout_buffer, _IOLBF, sizeof(stdout_buffer)); // RL: Line buffered. 
    //setvbuf(stdout, stdout_buffer, _IOFBF, sizeof(stdout_buffer)); // RL: Fully buffered. 
    setvbuf(stdout, stdout_log_buffer, _IOLBF, sizeof(stdout_log_buffer)); // RL: Line buffered. 
#if 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " sizeof(stdout_buffer) = %d"   "\n", __func__, (int) sizeof(stdout_buffer)); 
    fprintf(stdout, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " sizeof(stdout_buffer) = %d"   "\n", __func__, (int) sizeof(stdout_buffer)); 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " stdout = %p " "\n", __func__, stdout); 
    { dprintf(fileno(stdout), "STDOUT BUFFER: %p\n", stdout -> _bf._base); }; 
    { dprintf(fileno(stdout), "STDERR BUFFER: %p\n", &stderr -> _bf); }; 
    { dprintf(fileno(stdout), "STDOUT BUFFER: %p - " __FILE__ " - %d \n", (const void *)stdout -> _bf._base, (int)__LINE__); }; 
    { const char __file__[] = "" __FILE__ ""; dprintf(fileno(stdout), "STDOUT BUFFER: %p - %s - %d \n", (const void *)stdout -> _bf._base, (const char *)__file__, (int)__LINE__); }; 
#endif 
#endif 

int main__reassign_stdout_to_logfile(const char * progdir, const char * log_subdir_given, const char * log_filename, char * buffer, const int16_t buffer_bytesize) { 
  //     Redirect 'stdout' to the log file. 
  // RL: The idea is that any errors should show up on 'stderr', so that we know that something 
  //     happened, but also in the log file to have context. 
  const char * log_filepathname = NULL; 
  int16_t needed_bytesize = 0; 
  int16_t buffer_used = 0; 
  goto label__body; 

 label__error__cannot_reopen_stdout_to_null: {
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Reopening stdout to null failed: NA - so I close it" "\n", __func__); 
    main__stdlog_d = -1; 
    return -1; 
 }; 

  label__reassign_to_null: { 
    const char path_to_null[] = "/dev/null"; 
    if (NULL == freopen(path_to_null, "wb", stdout)) goto label__error__cannot_reopen_stdout_to_null; 
    main__stdlog_filename = path_to_null; 
    setvbuf(stdout, stdout_log_buffer, _IOLBF, sizeof(stdout_log_buffer)); // RL: Line buffered. 
    main__stdlog_d = fileno(stdout); 
    return buffer_used; 
  }; 
  
 label__error__cannot_create_logdir: {
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "I could not create LOGDIR: '%s' - so I assign log to /dev/null" "\n", __func__, LOGDIR); 
    goto label__reassign_to_null; 
  }; 
  
 label__error__cannot_reopen_stdout: {
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Reopening stdout to log file failed: '%s' - so I assign log to /dev/null" "\n", __func__, log_filename); 
    goto label__reassign_to_null; 
  }; 

 label__error__log_filename_is_empty: { 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "The log_filename is empty: 'NULL' - so I assign log to /dev/null" "\n", __func__); 
    goto label__reassign_to_null; 
  }; 
  
 label__error__buffer_too_small: { 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Buffer too small - Requested VS Available: %d VS %d - so I assign log to /dev/null" "\n", __func__, (int) needed_bytesize, (int) buffer_bytesize); 
    goto label__reassign_to_null; 
  }; 
  
 label__error__local_stack_too_small: { 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Local stack too small - Requested VS Available: NA VS NA - so I assign log to /dev/null" "\n", __func__); 
    goto label__reassign_to_null; 
  }; 
  

  label__reassign_to_log_filepathname: { 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "log_filepathname: '%s'" "\n", __func__, log_filepathname); 
    if (NULL == freopen(log_filepathname, "wb", stdout)) goto label__error__cannot_reopen_stdout; 
    main__stdlog_filename = log_filepathname; 
    setvbuf(stdout, stdout_log_buffer, _IOLBF, sizeof(stdout_log_buffer)); // RL: Line buffered. 
    main__stdlog_d = fileno(stdout); 
    return buffer_used; 
  }; 

  label__reassign_to_fd3: { 
    const char path_to_fd3[] = "/dev/fd/3"; 
    if (NULL == freopen(path_to_fd3, "wb", stdout)) goto label__error__cannot_reopen_stdout; 
    main__stdlog_filename = path_to_fd3; 
    setvbuf(stdout, stdout_log_buffer, _IOLBF, sizeof(stdout_log_buffer)); // RL: Line buffered. 
    assert(3 == fileno(stdout)); 
    main__stdlog_d = 3; 
    return buffer_used; 
  }; 
  
  label__no_log_subdir_provided: { 
    const int16_t progdir_bytesize = 1 + strlen(progdir); 
    const int16_t log_filename_bytesize = 1 + strlen(log_filename); 
    needed_bytesize = progdir_bytesize - 1 + 1 + log_filename_bytesize; 
    if (needed_bytesize > buffer_bytesize) goto label__error__buffer_too_small; 
    bcopy(progdir, buffer, progdir_bytesize); 
    *(buffer + progdir_bytesize - 1) = '/'; 
    bcopy(log_filename, buffer + progdir_bytesize, log_filename_bytesize); 
    log_filepathname = buffer; 
    buffer_used = needed_bytesize; 
    goto label__reassign_to_log_filepathname; 
  }; 
  
 label__progdir_not_null: { 
    if (NULL ==  log_filename) goto label__error__log_filename_is_empty; 
    if ('\0' == *log_filename) goto label__error__log_filename_is_empty; 
    
    if ((NULL == log_subdir_given) || ('\0' == *log_subdir_given)) goto label__no_log_subdir_provided; 
    
    const int16_t log_subdir_given__bytesize = 1 + strlen(log_subdir_given); 
    char log_subdir_b[1 << 11]; 
    if ((int16_t)sizeof(log_subdir_b) < log_subdir_given__bytesize) goto label__error__local_stack_too_small; 

    char * log_subdir= log_subdir_b;
    bcopy(log_subdir_given, log_subdir, log_subdir_given__bytesize); 
    
    // RL: Remove starting slashes. 
    for (;;) { 
      if ('/' != *log_subdir) break; 
      log_subdir++; 
      continue; 
    }; 
    if ('\0' == *log_subdir) goto label__no_log_subdir_provided; 
    
    // RL: Remove trailing slashes. 
    char * log_subdir_e = log_subdir; 
    for (;;) { log_subdir_e++; if ('\0' == *log_subdir_e) break; }; 
    for (;;) { log_subdir_e--; if ( '/' != *log_subdir_e) break; }; 
    log_subdir_e++;
    *log_subdir_e = '\0'; 
    
    {
      const int16_t progdir_bytesize = 1 + strlen(progdir); 
      const int16_t log_filename_bytesize = 1 + strlen(log_filename); 
      const int16_t log_subdir_bytesize = 1 + strlen(log_subdir); 
      
      // RL: Does the subdir exist? 
      if (-1 == access(LOGDIR, R_OK | W_OK | X_OK | F_OK)) { 
	// RL: No, let’s make it. 
	if (-1 == mkdir(LOGDIR, (mode_t) 0777)) goto label__error__cannot_create_logdir; 
      }; 
      
      // RL: Concat 
      needed_bytesize = progdir_bytesize - 1 + 1 + log_subdir_bytesize - 1 + 1 + log_filename_bytesize; 
      if (needed_bytesize > buffer_bytesize) goto label__error__buffer_too_small; 
      bcopy(progdir, buffer, progdir_bytesize); 
      *(buffer + progdir_bytesize - 1) = '/'; 
      bcopy(log_subdir, buffer + progdir_bytesize, log_subdir_bytesize); 
      *(buffer + progdir_bytesize + log_subdir_bytesize - 1) = '/'; 
      bcopy(log_filename, buffer + progdir_bytesize + log_subdir_bytesize, log_filename_bytesize); 
      log_filepathname = buffer; 
      buffer_used = needed_bytesize; 
      goto label__reassign_to_log_filepathname; 
    }; 

  };
  
 label__body: { 
#if 1 
    const int are_we_in_gdb_huh = true; 
#else 
    // This method works, but the program cannot be killed anylonger. 
    const int are_we_in_gdb_huh = -1 == ptrace(PT_TRACE_ME, 0, NULL, 0); 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "are_we_gdb_huh: '%s'" "\n", __func__, are_we_in_gdb_huh ? "TRUE" : "FALSE"); 
    //if (!are_we_in_gdb_huh) 
    { 
      // RL: Very important. Otherwise, cannot be killed anylonger, as we are self-debugging… ☹ 
      ptrace(PT_DETACH, 0, NULL, 0); 
      ptrace(PT_DETACH, getpid(), NULL, 0); 
      ptrace(PT_DETACH, 0, NULL, 0); 
      ptrace(PT_DETACH, getpid(), NULL, 0); 
    }; 
#endif 
    // RL: First, if descriptor 3 is opened, then redirecting to it. 
    if (!are_we_in_gdb_huh) { 
      // RL: We have to check whether we are in GDB, as GDB opens 3, 4, and 5. 
      if (-1 != fcntl(3, F_GETFL)) goto label__reassign_to_fd3; 
    }; 
    if (NULL != main_argv0__progdir) goto label__progdir_not_null; 
    goto label__reassign_to_null; 
  }; 
  
}; 




void main_proctitle_set(void) { 
  // RL: Title shown in 'ps'-like commands. 
  //setproctitle(" - PID: (%d)", getpid()); 
  setproctitle("PID: (%d)", getpid()); 
  //setproctitle("-%s - PID: (%d)", getprogname(), getpid()); 
  //setproctitle("talking to %s", inet_ntoa(addr)); 
}; 

void main_locale_set(void) {
  char * loc_val; 
  const char * loc; 
  
  loc_val = setlocale(LC_CTYPE, NULL); 
  printf("Current locale LC_CTYPE: %s\n", loc_val); 
  
  loc_val = setlocale(LC_CTYPE, ""); 
  printf("Default locale LC_CTYPE: %s\n", loc_val); 
  
#ifndef WIN 
  printf("Codeset = \"%s\"\n", nl_langinfo(CODESET)); 
#endif 
  
  //loc = ""; 
  //loc = "fr"; 
  //loc = "fr_FR"; 
  //loc = "fr_FR.ISO8859-1"; 
  //loc = "fr_FR.ISO8859-15"; 
  //loc = "fr_FR.UTF-8"; 
#ifdef WIN 
  loc = ".OCP"; 
  //loc = ".ACP"; 
  //loc = "fr"; 
#else 
  loc = "fr_FR.UTF-8"; 
#endif 
  
  printf("Setting locale to `%s'.\n", loc); 
  loc_val = setlocale(LC_CTYPE, loc); 
  printf("New locale is `%s'.\n", loc_val); 
  
  // celui-là craint, car par exemple lors de l'analyse lexicale
  // un réel n'est pas reconnu de la même façon (3,5 ou 3.5)
  //loc_val = setlocale(LC_ALL, loc);
  //printf("New locale is `%s'.", loc_val);
}; 



void main_rand_init(void) { 
  time_t date_time; 
  srandom(time(&date_time)); 
}; 

void main_date_print(void) {
  printf("Compilé le %s à %s." "\n", __DATE__, __TIME__); //STRING(__DATE__), STRING(__TIME__)); 
  time_t date_time; 
  char date_chaine[26]; 
  time(&date_time); 
  printf("Nous sommes le %s\n", ctime_r(&date_time, date_chaine)); 
};

void main_arch_print(void) { 
#if defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(__amd64__) 
  printf("Compilé pour un processeur 64bits (amd64 ou x86_64)." "\n"); 
#else 
  printf("Compilé pour un processeur qui n'est pas 64 bits." "\n"); 
#endif 

#ifdef __INTMAX_TYPE__ 
  printf("Le plus grand entier sur cette architecture: %d bits." "\n", (int) (sizeof(__INTMAX_TYPE__) << 3)); 
#endif 

#ifdef __BYTE_ORDER__ 
  printf("Ordre des entiers ('endian-ness'): %d" "\n", (int) __BYTE_ORDER__); 
#if    __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ 
  printf("Architecture 'little endian'" "\n"); 
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ 
  printf("Architecture 'big endian'" "\n"); 
#elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__ 
  printf("Architecture 'pdp endian'" "\n"); 
#endif 
#endif 

#ifdef __LITTLE_ENDIAN__ 
  printf("Architecture 'little endian'" "\n"); 
#endif 

  printf("Taille d'un entier standard: %d bits " "\n", (int) (sizeof(int) << 3)); 
  printf("Taille d'un pointeur standard: %d bits " "\n", (int) (sizeof(void *) << 3)); 
}; 

void main_gcc_print(void) { 
#ifdef __GNUC__ 
  printf("Compilé avec GCC %s.%s.%s" "\n", STRING(__GNUC__) , STRING(__GNUC_MINOR__), STRING(__GNUC_PATCHLEVEL__)); 
  printf("GCC version: %s" "\n", __VERSION__); 
#else 
  printf("Not compiled with a gcc-compatible compiler (__GNUC__ was not defined)." "\n"); 
#endif 

#ifdef __clang__ 
  printf("Compilé avec CLang %s.%s.%s" "\n", STRING(__clang_major__) , STRING(__clang_minor__), STRING(__clang_patchlevel__)); 
  printf("CLang version: %s" "\n", __clang_version__); 
#else 
  printf("Not compiled with a clang-compatible compiler (__clang__ was not defined)." "\n"); 
#endif 

#ifdef __PCC__ 
  printf("Compilé avec CLang %s.%s.%s" "\n", STRING(__PCC__) , STRING(__PCC_MINOR__), STRING(__PCC_MINORMINOR__)); 
  printf("CLang version: %s" "\n", __clang_version__); 
#else 
  printf("Not compiled with a pcc-compatible compiler (__PCC__ was not defined)." "\n"); 
#endif 

};

void main_args_print(const int argc, const char * argv[]) {
  printf("\nListe des paramètres: ");

  for (int i = 0; i < argc; i ++) {
    printf("\t%s\n", argv[i]);
  };
};

extern void * etext; 
extern void * edata; 
extern void * end; 

void main_win_print(void) {
#ifdef _WIN32_WINNT 
  // _WIN32_WINNT >= 0x0501  pour windows XP et supérieur 
  // Windows 6: Vista 
  // Windows 5: XP 
  // Windows 4: 95, 98 & Me 
  // Windows 3: Win 3 
  printf("Compilé sur un système Windows 32 bits version: _WIN32_WINNT = %d\n", (int) _WIN32_WINNT); 
#elif (defined WIN) 
  printf("Compilé sur un système Windows (32 bits), mais la macro C qui donne la version n'est pas définie: _WIN32_WINNT\n"); 
#else 
  printf("Compilé pour un système qui n'est pas Windows.\n"); 
#endif 

#if defined(__unix__) || defined(__unix) 
  printf("Compilé pour un système qui est unix-compatible." "\n"); 
#else 
  printf("Compilé pour un système qui n'est pas unix-compatible." "\n"); 
#endif 

#if defined(__OpenBSD__) 
  printf("Compilé pour un système OpenBSD." "\n"); 
#else 
  printf("Compilé pour un système qui n'est pas OpenBSD." "\n"); 
#endif 


#ifdef SIGSTKSZ 
  printf("Taille standard d'une extra stack: %d" "\n", (int) SIGSTKSZ); 
#endif 
  
#ifdef MINSIGSTKSZ 
  printf("Taille minimale standard d'une extra stack: %d" "\n", (int) MINSIGSTKSZ); 
#endif 

#if 0
  { 
    char a; 
    //char u[MINSIGSTKSZ]; 
    //fprintf(stderr, "sizeof(u): %d" "\n", (int) sizeof(u)); // RL: Good: 12288. 
    stack_t oss[1]; 
    stack_t new[1]; 
    new -> ss_sp = &a; 
    new -> ss_size = MINSIGSTKSZ; 
    new -> ss_flags = 0; 
    sigaltstack(new, oss); 
    printf("Taille actuelle de la stack: %d - adresse de la stack: %p - top de la stack: %p " "\n", (int)oss -> ss_size, oss -> ss_sp, &a);
    sigaltstack(oss, NULL); 
    
    //sigjmp_buf kernel_sjlj_env; 
    //sigsetjmp(this -> kernel_sjlj_env, /*savemask?*/0); 
    printf("Taille actuelle de la stack: %d - adresse de la stack: %p - top de la stack: %p " "\n", (int)oss -> ss_size, oss -> ss_sp, &a);
  }; 
  {
    char a; 
    struct rlimit rlp[1];
    getrlimit(RLIMIT_STACK, rlp); 
    fprintf(stderr, "Taille actuelle de la stack: %d - Taille maximale de la stack: %d - &a = %p - sbrk(0) = %p " "\n", (int)rlp -> rlim_cur, (int)rlp -> rlim_max, &a, sbrk(0)); 
    fprintf(stderr, "etext = %p - edata = %p - end = %p  " "\n", etext, edata, end); 

  }; 
  { 
    char a; 
    struct rusage rusage[1]; 
    getrusage(RUSAGE_SELF, rusage); 
    fprintf(stderr, "rusage -> ru_isrss = %d" "\n", (int) rusage -> ru_isrss); 
  };   
#endif 
  { 
    // RL: 4Mo & 32Mo on my config. 
    struct rlimit rlp[1];
    getrlimit(RLIMIT_STACK, rlp); 
    fprintf(stdout, "Taille actuelle de la stack: %d - Taille maximale de la stack: %d  " "\n", (int)rlp -> rlim_cur, (int)rlp -> rlim_max); 
  }; 


  {
    void * a = NULL; 
    a = dlopen(/*const char *path*/"../build/timer.so", /*int mode*/RTLD_NOW | RTLD_LOCAL); 
    fprintf(stderr, "dlopen = %p  " "\n", a); 
    fprintf(stderr, "dlerror = %s  " "\n", dlerror()); 

    Dl_info info[1]; 
    if (!dladdr(a, info)) { 
      fprintf(stderr, "dladdr: nothing found: %s  " "\n", dlerror()); 
    } 
    else { 
      fprintf(stderr, "dladdr: dli_fname = %s - dli_fbase = %p - dli_sname = %s - dli_saddr = %p  " "\n", info -> dli_fname, info -> dli_fbase, info -> dli_sname, info -> dli_saddr); 
    }; 
    
    void * fun = dlsym(a, "timer_hello"); 
    fprintf(stderr, "dlsym = %p  " "\n", fun); 
    fprintf(stderr, "dlerror = %s  " "\n", dlerror()); 

    if (!dladdr(fun, info)) { 
      fprintf(stderr, "dladdr: nothing found: %s  " "\n", dlerror()); 
    } 
    else { 
      fprintf(stderr, "dladdr: dli_fname = %s - dli_fbase = %p - dli_sname = %s - dli_saddr = %p  " "\n", info -> dli_fname, info -> dli_fbase, info -> dli_sname, info -> dli_saddr); 
    }; 
    
    if (fun != NULL) { 
      void (*f)(void) = fun; 
      f(); 
    }; 
    
    // RL: To resolve API_SCRIPT functions which are in the executables: 
    //     Quoting 'man (3) dlopen' 
    //        The main executable's symbols are normally invisible to dlopen() symbol 
    //        resolution.  Those symbols will be visible if linking is done with gcc(1) 
    //         -rdynamic, which is equivalent to ld(1) --export-dynamic. 
    //     Or: 
    //         clang -Wl,"--export-dynamic","-v"  
    //       works, but export all the symbols. 
    //     Or: 
    //         -Wl,--dynamic-list=<file> 
    //       and the <file> contains the list of exported symbols, and its content looks like that: 
    //        { extern "C" { main; }; }; 
    // 
    
    
    if (a != NULL) { 
      dlclose(a); 
    }; 
  }; 


};

