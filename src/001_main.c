#include "global.h"
#include "001_main.h"
#include "002_kernel.h"
#include "006_check_and_assert.h"
//#include "son.h"
//#include "keys.h"
//#include "timer.h"
#include <sys/resource.h> 
#include <dlfcn.h>
 
#include <unistd.h> /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html */ /* https://en.wikipedia.org/wiki/Unistd.h */ 

#if 0 
// RL: GDB detection 
// RL: Il faudrait être en mesure de détecter la présence de GDB, 
//     car GDB ouvre des descripteurs supplémentaires. 
// RL: En l’état, la tactique consisterait à demander au kernel de 
//     s’auto-débugger, ce que le kernel refuserait si le programme 
//     était déjà en débuggage par GDB. 
//     Problème: Comment annuler son auto-débuggage une fois le test réalisé? 
//     C'est un problème car le programme répond différemment (on ne plus faire kill -9 par exemple). 
//     Je n’ai pas réussi à faire fonctionner PT_DETACH (encore des arcanes de complexité… ☹). 
#include <sys/types.h>
#include <sys/ptrace.h>
//int ptrace(int request, pid_t pid, caddr_t addr, int data);
// RL: This should be in a child? 
#endif 

//#include "lib.ci"
//#include "lib__llfixed.ci"

#include <anime.h>
#include "anime_database.h"




// RL: This file contains all the system stuffs. 
//     Anything here is not related to the program per se. 
//     And is done only once. 

// RL: Étapes de main: 
//      1. Se déplacer vers le bon répertoire. 
//      2. Réassigner stdout. 
//      3. Réassigner stderr. 
//      4. Kernel (init, run, free) 
//      5. Vider tous les buffers, et tout fermer. 
//      6. Bye! 
// 
// RL: Le vrai programme est dans Kernel. 
 
 
// I. Le répertoire 
// ---------------- 
// 
// RL: Tout d’abord, le programme se déplace vers le répertoire contenant les données (à lire) et les logs (à écrire). 
// RL: A priori, toutes ces chaînes de caractères sont allouées dans la stack de la fonction 'main()' (donc aucune gestion mémoire). 
const char *  main_argv0 = NULL; 
      int16_t main_argv0__bytesize = -1; 
      char *  main_argv0__progname = NULL; // RL: INVARIANT: It should *not* hold any slash character '/'. 
      int16_t main_argv0__progname__bytesize = -1; 
      char *  main_argv0__progdir  = NULL; // RL: INVARIANT: The last char should *not* be the slash character '/' (unless it is root). 
      int16_t main_argv0__progdir__bytesize  = -1; 

static int  main__break_argv0_into_progname_and_progdir(const char * argv0, char * * progname_r, char * * progdir_r, char * buffer, const int16_t buffer_bytesize); 
extern char **environ; 
static int  main__look_for_progdir_in_env_path(const char * argv0, char * * progdir_r, char * buffer, const int16_t buffer_bytesize); 
static int  main__move_to_progdir(const char * progdir); 
 
 
// II. Stdout 
// ---------- 
// 
// RL: Ensuite, on réassigne stdout vers un fichier log. 
//     Sur le terminal, ne s’affichent que les éventuelles erreurs. 
//     Car, dans le fichier log, afin de comprendre les erreurs, nous écrivons généreusement. 
// RL: Du fait de cette écriture généreuse, l’écriture dans le fichier log doit se faire à travers une mémoire tampon (un «buffer»). 
// RL: Par défaut, cette mémoire tampon du log («log buffer») est écrite par le kernel une fois à chaque passe de boucle. 
// RL: A priori, toutes ces chaînes de caractères sont allouées dans la stack de la fonction 'main()' (donc aucune gestion mémoire). 
// RL: Le tamponnage est implémenté en utilisant un pipe. 
// RL: Problème — L’implémentation du tamponnage avec un pipe recourt à l’utilisation du signal SIGIO. (Pénible. ☹) 
static const char     main__stdout_log_default_subdir[] = LOGDIR; 
static       char *   main__stdout_log_subdir = NULL; // RL: INVARIANT: The first char and the last char should *not* be the slash character '/' (as a subdir, it cannot be root — but it can be empty). 
static const char     main__stdout_log_default_filename[] = "stdout.log"; // RL: INVARIANT: It should *not* hold any slash character '/'. 
static const char *   main__stdout_log_filepathname = NULL; // RL: Le nom et le chemin du fichier ouvert. 
enum {                main__stdout_log_buffer__bytesize = INT16_MAX }; 
static       char     main__stdout_log_buffer[main__stdout_log_buffer__bytesize] = {}; 
static       int16_t  main__stdout_log_buffer_nb = 0; 
static       int      main__stdout_log_pipe[2] = {-1, -1}; // RL: [0] is output (read end), [1] is input (write end) 
static       int      main__stdout_log_post_fd = -1; 
static       void (*  main__stdout_log__SIGIO_former_handler)(int) = NULL; 

static int  main__subdir__clean_up(const char * default_subdir, char * * cleanup_subdir_r, char * buffer, const int16_t buffer_bytesize); 
extern void main__stdout_log_buffer__flush(void); 
static void main__stdout_log__SIGIO_handler(int sig); 
static int  main__stdout_log_pipe__open(void); 
static int  main__stdout_log_pipe__open_aux(int * stdout_log_pipe, void (* handler)(int), void (* (*former_handler_r))(int)); 
static void main__stdout_log_pipe__close(void); 
static int  main__make_subdir_and_build_filepathname(char * buffer, const int16_t buffer_bytesize); 
static int  main__make_subdir_and_build_filepathname_aux(const char * progdir, const char * log_subdir, const char * log_filename, const char * * log_filepathname_r, char * buffer, const int16_t buffer_bytesize); 
static int  main__reassign_stdout_to_logfile(char * buffer, const int16_t buffer_bytesize); 
static int  main__reassign_stdout_to_logfile_aux(const char * progdir, const char * log_subdir, const char * log_filename, const char * * log_filepathname_r, const int pipe_write_fd, int * opened_log_fd_r, char * buffer, const int16_t buffer_bytesize); 







// II. Stderr 
// ---------- 
// 
// RL: Concernant stderr, cette sortie n’est pas tamponnée. 
//     En revanche, on veut l’écrire à la fois sur le terminal et dans le fichier log. 
//     Il faut donc capturer cette écriture, et la dédoubler dans le fichier log. 
enum {                main__stderr_buffer__bytesize = INT16_MAX }; 
static       char     main__stderr_buffer[main__stderr_buffer__bytesize] = {}; 
static       int16_t  main__stderr_buffer_nb = 0; 
static       int      main__stderr_pipe[2] = {-1, -1}; // RL: [0] is output (read end), [1] is input (write end) 
static       int      main__stderr_post_fd = -1; 
static       void (*  main__stderr_pipe__SIGIO_former_handler)(int) = NULL; 

extern void main__stderr_buffer__flush(void); 
static void main__stderr_pipe__SIGIO_handler(int sig); 
static int  main__stderr_pipe__open(void); 
static int  main__stderr_pipe__open_aux(int * stderr_pipe, void (* handler)(int), void (* (*former_handler_r))(int)); 
static void main__stderr_pipe__close(void); 
static void main__stderr__dup_to_post(void); 
static void main__stderr__dup_to_post_aux(int * stderr_post_fd_r); 
static int  main__stderr__reassign_to_pipe(void); 
static int  main__stderr__reassign_to_pipe_aux(const int pipe_write_fd); 




// RL: Divers 
static void main_proctitle_set(void); 
static void main_locale_set(void); 
static void main_rand_init(void); 
static void main_date_print(void); 
static void main_gcc_print(void); 
static void main_arch_print(void); 
static void main_args_print(const int argc, const char * argv[]); 
static void main_win_print(void); 


#define LOCAL_ALLOCA__DECLARE(LOCAL_ALLOCA_SIZEOF)			\
  enum { LOCAL_ALLOCA__BYTESIZE = (LOCAL_ALLOCA_SIZEOF) }; char local_alloca__mem[LOCAL_ALLOCA__BYTESIZE]; uint16_t local_alloca__left = LOCAL_ALLOCA__BYTESIZE; uint16_t local_alloca__used = 0; uint16_t local_alloca__requested; 

#define LOCAL_ALLOCA(REQUESTED_SIZEOF)					\
  (local_alloca__requested = (REQUESTED_SIZEOF), ((local_alloca__requested > local_alloca__left) ? NULL : (local_alloca__left -= local_alloca__requested, local_alloca__used += local_alloca__requested,  local_alloca__mem + local_alloca__used - local_alloca__requested))) 



// =========================================================================== 
// 0. MAIN 

int main(const int argc, const char * argv[]) { 
  LOCAL_ALLOCA__DECLARE(UINT16_MAX); 
  int retour = -1;
  
 label__start: {
    //int _SDL_main(int argc, char * argv[]) {
    if (1 > argc) { 
      write_string(STDERR_FILENO, "Does not make sense - ARGC is lower than 1: "); 
      write_long_long_int(STDERR_FILENO, argc); 
      write_eol(STDERR_FILENO); 
      return 0; 
    }; 
    main_argv0 = argv[0]; 
    main_argv0__bytesize = 1 + strlen(main_argv0); 
    goto label__check_and_assert; 
  }; 

 label__exit: { 
    main__stdout_log_buffer__flush(); 
    fflush(NULL); 
    return 0; 
  }; 

  label__error__upcleaning_log_subdir_failed: { 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "I failed to clean up the log subdir.' " "\n", __func__); 
    return -3; 
  }; 
  
 label__error__stdout_log__making_pipe_failed: { 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "I failed to make a pipe the stdout log buffer.' " "\n", __func__); 
    return -4; 
  }; 
  
 label__error__stderr__making_pipe_failed: { 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "I failed to make a pipe for stderr.' " "\n", __func__); 
    return -5; 
  }; 
  
 label__error__stderr__reassigning_to_pipe_failed: { 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "I failed to reassign stderr to the pipe.' " "\n", __func__); 
    main__stderr_pipe__close(); 
    return -6; 
  }; 
  
#if 0 
  label__error__cannot_move_to_root_dir: { 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "I could not change the current directory to the one holding the program: '%s' " "\n", __func__, main_argv0); 
    return -1; 
  }; 
  
  label__error__cannot_reassign_stdout_to_logfile: {
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Failed to reassign stdout to log file: '%s' " "\n", __func__, main__stdout_log_default_filename); 
    return -2; 
  }; 
#endif 
  

  label__check_and_assert: { 
    check_and_assert(/*debug_print_huh*/true, /*stderr_d*/STDERR_FILENO); 
    goto label__body; 
  }; 
  
 label__body: { 
    // RL: First thing to do: 
    // Change current-working-directory to the directory containing the program («mouton-dir»), 
    // in order to read data and write logs. 
    for (;;) { 
      {
	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "local_alloca__left: '%d' " "\n", __func__, (int) local_alloca__left);  
	const int16_t used_size = main__break_argv0_into_progname_and_progdir(main_argv0, &main_argv0__progname, &main_argv0__progdir, local_alloca__mem + local_alloca__used, SATURATED_CAST_TO_INT16(local_alloca__left)); 
	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "main__break_argv0_into_progname_and_progdir: '%d' " "\n", __func__, (int) used_size);  
	if (0 >  used_size) break; 
	if (0 == used_size) break; // RL: ??? Does not make sense. 
	local_alloca__used += used_size; 
	local_alloca__left -= used_size; 
      }; 
      
      if (NULL == main_argv0__progdir) { 
	const int16_t used_size = main__look_for_progdir_in_env_path(main_argv0, &main_argv0__progdir, local_alloca__mem + local_alloca__used, SATURATED_CAST_TO_INT16(local_alloca__left)); 
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
  
#if 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "main_argv0: '%s' " "\n", __func__, main_argv0);  
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "main_argv0__progname: '%s' " "\n", __func__, main_argv0__progname);  
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "main_argv0__progdir: '%s' " "\n", __func__, main_argv0__progdir);  
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "CWD: '%s' " "\n", __func__, getcwd(local_alloca__mem + local_alloca__used, local_alloca__left));  
#endif 
    
    for (;;) { 
      const int16_t used_size = main__subdir__clean_up(main__stdout_log_default_subdir, &main__stdout_log_subdir, local_alloca__mem + local_alloca__used, SATURATED_CAST_TO_INT16(local_alloca__left)); 
      if (0 >= used_size) goto label__error__upcleaning_log_subdir_failed; 
      local_alloca__used += used_size; 
      local_alloca__left -= used_size; 
      break; 
    }; 

    // RL: LOG FILE: Reassigning stdout to log-file 
    for (;;) { 
      if (0 != main__stdout_log_pipe__open()) goto label__error__stdout_log__making_pipe_failed; 
      const int16_t used_size = main__reassign_stdout_to_logfile(local_alloca__mem + local_alloca__used, SATURATED_CAST_TO_INT16(local_alloca__left)); 
      if (0 > used_size) break; 
      local_alloca__used += used_size; 
      local_alloca__left -= used_size; 
      break; 
    }; 

    
    // RL: STDERR: Reassigning stderr to pipe 
    for (;;) { 
      if (0 != main__stderr_pipe__open()) goto label__error__stderr__making_pipe_failed; 
      main__stderr__dup_to_post(); 
      if (0 != main__stderr__reassign_to_pipe()) goto label__error__stderr__reassigning_to_pipe_failed; 
      break; 
    };     
    
    
    // RL: Everything is UTF-8 unless specified otherwise. 
    printf("☺☺☺☺☺☺" "\n"); 
    printf("Cela fait plaisir de vous voir." "\n"); 
    fprintf(stdout, "Démarrage du jeu!!!\n\n"); 
    main__stdout_log_buffer__flush(); 
    
#if 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "main_argv0: '%s' " "\n", __func__, main_argv0);  
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "main_argv0__progname: '%s' " "\n", __func__, main_argv0__progname);  
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "main_argv0__progdir: '%s' " "\n", __func__, main_argv0__progdir);  
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "CWD: '%s' " "\n", __func__, getcwd(local_alloca__mem + local_alloca__used, local_alloca__left));  
    main__stdout_log_buffer__flush(); 
    exit(0); 
#endif 
    
    main_locale_set(); 
    main_rand_init(); 
    main_date_print(); 
    main_gcc_print(); 
    main_arch_print(); 
    main_proctitle_set(); 
    main_args_print(argc, argv); 
    main_win_print(); 
    main__stdout_log_buffer__flush(); 

    if (true) { 
      const char * anime_to_load[] = { "saintexupery.anime", "pere.anime", "bob.anime", "heros.anime", "brigitte.anime.ci", "juliette.anime", "mouton.anime", "chaman.anime", "dinotore.anime", "heros.anime", "pecu.anime", "prokofiev.anime", "sang.anime", "chapinmechant.anime", "fantome.anime", "moutonmechant.anime", "pierre.anime", "y.anime", "m.anime", "c.anime", "a.anime", "bizarre1.anime", "bizarre2.anime", "bucheron.anime", "chapin.anime", "eclaboussures.anime", "homme_bizarre.anime", "puit_boss.anime", "squelette.anime", NULL }; 
      for (int i = 0; ; i++) { 
	const char * anime_filename = anime_to_load[i]; 
	if (NULL == anime_filename) break; 
	const anime_t * one_anime; 
	one_anime = anime_database__load__compile_time(anime_filename); 
	main__stdout_log_buffer__flush(); 
      }; 
    }
    else {
      printf("<<< main" "\n"); 
      printf("===============================================================================" "\n"); 
       
      for (;;) { 
	retour = Kernel_Init();  if (retour < 0) { break; }; 
	{ dprintf(fileno(stdout), "STDOUT BUFFER: %p\n", stdout -> _bf._base); }; 
	
	retour = Kernel_Run(); 
	Kernel_Dispose(); 
	break; 
      }; 
      printf("===============================================================================" "\n"); 
      printf(">>> main" "\n"); 
    }; 
    
    fprintf(stdout, "Fin du jeu!\n"); 

    main__stdout_log_buffer__flush(); 

    goto label__exit; 
  }; 
}; 





// =========================================================================== 
// I. PROGDIR FROM ARGV0 

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
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "argv0_bytesize: '%d' " "\n", __func__, (int) argv0_bytesize);  
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "buffer_bytesize: '%d' " "\n", __func__, (int) buffer_bytesize);  
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


int main__move_to_progdir(const char * progdir) { 
  if (NULL ==  progdir) return -1; 
  if ('\0' == *progdir) return -2; 
  if (0 != chdir(progdir)) return -3; 
  return 0; 
};




// =========================================================================== 
// II. STDOUT TO LOG 

void main__stdout_log_buffer__flush(void) { 
#if 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "main__stdout_log_buffer_nb: '%d'" "\n", __func__, (int) main__stdout_log_buffer_nb); 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "main__stdout_log_post_fd: '%d'" "\n", __func__, (int) main__stdout_log_post_fd); 
#endif 
  if (0 >  main__stdout_log_post_fd) return; 
  //if (0 >  main__stdout_log_buffer_nb) { main__stdout_log_buffer_nb = 0; return; }; 
  if (0 == main__stdout_log_buffer_nb) return; 
  if (0 <= main__stdout_log_post_fd) write(main__stdout_log_post_fd, main__stdout_log_buffer, main__stdout_log_buffer_nb); 
  main__stdout_log_buffer_nb = 0; 
}; 

int main__subdir__clean_up(const char * default_subdir, char * * cleanup_subdir_r, char * buffer, const int16_t buffer_bytesize) { 
  if (NULL == cleanup_subdir_r) return -3; 
  if (0    >= buffer_bytesize ) return -4; 
  int16_t requested_bytesize = -1; 
  goto label__body; 

 label__error__buffer_too_small: { 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Buffer too small - Requested VS Available: %d VS %d" "\n", __func__, (int) requested_bytesize, (int) buffer_bytesize); 
    return -5; 
  }; 
  
 label__subdir_is_empty: { 
    requested_bytesize = 1; 
    if (requested_bytesize > buffer_bytesize) goto label__error__buffer_too_small; 
    *buffer = '\0'; 
    *cleanup_subdir_r = buffer; 
    return requested_bytesize; 
  }; 
  
 label__subdir_is_root: { 
    // RL: Si le subdir est '/', il est alors interpreté comme le même répertoire. 
    goto label__subdir_is_empty; 
  }; 
  
 label__body: { 
    if (NULL ==  default_subdir  ) goto label__subdir_is_empty; 
    if ('\0' == *default_subdir  ) goto label__subdir_is_empty; 
    
    const int16_t default_subdir__bytesize = 1 + strlen(default_subdir); 
    
    // RL: Counting starting slashes. 
    const char * p = default_subdir; 
    for (;;) { if ('/' != *p) break; p++; }; 
    if ('\0' == *p) goto label__subdir_is_root; 
    const int16_t starting_slash_nb = p - default_subdir; 
    
    // RL: Counting trailing slashes. 
    const char * last_char = default_subdir + default_subdir__bytesize - 1 - 1; 
    p = last_char; 
    for (;;) { if ('/' != *p) break; p--; }; 
    const int16_t trailing_slash_nb = last_char - p; 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "trailing_slash_nb: '%d'" "\n", __func__, (int) trailing_slash_nb); 
    
    requested_bytesize = default_subdir__bytesize - starting_slash_nb - trailing_slash_nb; 
    if (requested_bytesize > buffer_bytesize) goto label__error__buffer_too_small; 
    bcopy(default_subdir + starting_slash_nb, buffer, requested_bytesize); 
    *(buffer + requested_bytesize - 1) = '\0'; 
    
    *cleanup_subdir_r = buffer; 

#if 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "default_subdir: '%s'" "\n", __func__, default_subdir); 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "cleanup_subdir: '%s'" "\n", __func__, *cleanup_subdir_r); 
#endif 

    return requested_bytesize; 
  }; 
}; 




int main__stdout_log_pipe__open(void) { 
  return main__stdout_log_pipe__open_aux(main__stdout_log_pipe, &main__stdout_log__SIGIO_handler, &main__stdout_log__SIGIO_former_handler); 
}; 

void main__stdout_log_pipe__close(void) { 
  close(main__stdout_log_pipe[0]); 
  close(main__stdout_log_pipe[1]); 
  main__stdout_log_pipe[0] = -1; 
  main__stdout_log_pipe[1] = -1; 
  signal(SIGIO, main__stdout_log__SIGIO_former_handler); 
}; 

int main__stdout_log_pipe__open_aux(int * stdout_log_pipe, void (* handler)(int), void (* (*former_handler_r))(int)) { 
  if (NULL == former_handler_r) return -1; 
  *former_handler_r = NULL; 
  goto label__body; 
  
  label__error__making_pipe_failed: {
    stdout_log_pipe[0] = -1; 
    stdout_log_pipe[1] = -1; 
    return -2; 
  }; 
  
  label__error__installing_SIGIO_handler_failed: { 
    close(stdout_log_pipe[0]); 
    close(stdout_log_pipe[1]); 
    stdout_log_pipe[0] = -1; 
    stdout_log_pipe[1] = -1; 
    return -3; 
  }; 

 label__body: { 
    if (-1 == pipe(stdout_log_pipe)) goto label__error__making_pipe_failed; 
    
    void * former_handler = signal(SIGIO, handler); 
    if (SIG_ERR == former_handler) goto label__error__installing_SIGIO_handler_failed; 
    *former_handler_r = former_handler; 
    
    fcntl(stdout_log_pipe[0], F_SETOWN, getpid()); // RL: Qui recevra le signal SIGIO? 
    fcntl(stdout_log_pipe[0], F_SETFL, O_ASYNC | O_NONBLOCK); // RL: Générer le signal SIGIO + Ne pas bloquer en cas de poll. 
    
    return 0; 
  }; 
}; 


void main__stdout_log__SIGIO_handler(int sig) { 
  // RL: Dans cette routine, nous appelons write(2) qui génère des SIGIO. 
  //     Donc nous devons désactiver le mask, et réinstaller le former_handler. 
  // RL: Symétriquement, notre handler devra être réinstallé à la sortie. 
  //     En revanche, le masque est remis automatiquement à chaque génération du signal SIGIO. 
  { 
    sigset_t sigset[1]; 
    sigemptyset(sigset);
    sigaddset(sigset, SIGIO);
    signal(SIGIO, main__stdout_log__SIGIO_former_handler); 
    sigprocmask(SIG_UNBLOCK, sigset, NULL); 
  }; 
#if 0 
  int debug_fd = open("/dev/tty", O_WRONLY); 
  char debug_buffer[1024]; 
#endif 
  goto label__body;

  label__exit: { 
#if 0 
    close(debug_fd); 
#endif 
    signal(SIGIO, main__stdout_log__SIGIO_handler); 
    return; 
  }; 
 
  label__pas_nous: {
    if (NULL == main__stdout_log__SIGIO_former_handler) goto label__exit; 
    main__stdout_log__SIGIO_former_handler(sig); 
    goto label__exit; 
  }; 
  
  label__body: { 
    // RL: Ici, nous avons un problème: nous ne savons pas qui généra le signal. 
    //     En particulier, était-ce le nôtre ou un autre? 
    //     Donc il faut tester. 
    //     Et pour tester, pas le choix, il faut faire un read(2). 
    //     Et cette lecture doit être non bloquante, et donc le flag O_NONBLOCK doit avoir été allumé en amont. 
    //     Sinon, on reste bloqué ici. 
    // RL: Pour une raison quelconque, le buffer est peut-être déjà plein. 
    if (main__stdout_log_buffer__bytesize == main__stdout_log_buffer_nb) { 
      if (0 <= main__stdout_log_post_fd) write(main__stdout_log_post_fd, main__stdout_log_buffer, main__stdout_log_buffer_nb); 
      main__stdout_log_buffer_nb = 0; 
    }; 
    const ssize_t read_nb = read(main__stdout_log_pipe[0], main__stdout_log_buffer + main__stdout_log_buffer_nb, main__stdout_log_buffer__bytesize - main__stdout_log_buffer_nb); 
#if 0 
    if (true) { 
      write_long_long_int_into_buffer(debug_buffer, sizeof(debug_buffer), read_nb); 
      write_string3(debug_fd, "[STDOUT HANDLER] ---> read_nb = ", debug_buffer, "\n"); 
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "read_nb: '%d'" "\n", __func__, (int) read_nb); 
      if (0 < read_nb) write(debug_fd, main__stdout_log_buffer + main__stdout_log_buffer_nb, read_nb); 
    }; 
#endif 
    if (0 >= read_nb) goto label__pas_nous; 
    main__stdout_log_buffer_nb += read_nb; 
    // RL: On flush dès que le buffer est plein. 
    if (main__stdout_log_buffer__bytesize == main__stdout_log_buffer_nb) { 
      if (0 <= main__stdout_log_post_fd) write(main__stdout_log_post_fd, main__stdout_log_buffer, main__stdout_log_buffer_nb); 
      main__stdout_log_buffer_nb = 0; 
    }; 
    goto label__exit; 
  }; 
}; 



static int main__make_subdir_and_build_filepathname(char * buffer, const int16_t buffer_bytesize) { 
  return main__make_subdir_and_build_filepathname_aux(main_argv0__progdir, main__stdout_log_subdir, main__stdout_log_default_filename, &main__stdout_log_filepathname, buffer, buffer_bytesize); 
}; 

static int main__make_subdir_and_build_filepathname_aux(const char * progdir, const char * log_subdir, const char * log_filename, const char * * log_filepathname_r, char * buffer, const int16_t buffer_bytesize) { 
  int16_t needed_bytesize = -1; 
  if (NULL == log_filepathname_r) return -1; 
  goto label__body; 

  label__progdir_is_empty: {
    // RL: Dans ce cas, par hypothèse, on considère que rien ne doit être fait. 
    *log_filepathname_r = NULL; 
    return 0; 
  }; 
  
  label__filename_is_empty: {
    // RL: Dans ce cas, par hypothèse, on considère que rien ne doit être fait. 
    *log_filepathname_r = NULL; 
    return 0; 
  }; 

 label__error__buffer_too_small: { 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Buffer too small - Requested VS Available: %d VS %d" "\n", __func__, (int) needed_bytesize, (int) buffer_bytesize); 
    return -2; 
  }; 
  
 label__error__cannot_create_logdir: {
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "I could not create log_subdir: '%s'" "\n", __func__, buffer); 
    return -3; 
  }; 
  
 label__subdir_is_empty: {
    const int16_t progdir_bytesize = 1 + strlen(progdir); 
    const int16_t log_filename_bytesize = 1 + strlen(log_filename); 
    needed_bytesize = progdir_bytesize - 1 + 1 + log_filename_bytesize; 
    if (needed_bytesize > buffer_bytesize) goto label__error__buffer_too_small; 
    bcopy(progdir, buffer, progdir_bytesize); 
    *(buffer + progdir_bytesize - 1) = '/'; 
    bcopy(log_filename, buffer + progdir_bytesize, log_filename_bytesize); 
    *log_filepathname_r = buffer; 
    return needed_bytesize; 
  }; 

  label__subdir_is_not_empty: {
    const int16_t progdir_bytesize = 1 + strlen(progdir); 
    const int16_t log_filename_bytesize = 1 + strlen(log_filename); 
    const int16_t log_subdir_bytesize = 1 + strlen(log_subdir); 
    
    needed_bytesize = progdir_bytesize - 1 + 1 + log_subdir_bytesize - 1 + 1 + log_filename_bytesize; 
    if (needed_bytesize > buffer_bytesize) goto label__error__buffer_too_small; 
    
    bcopy(progdir, buffer, progdir_bytesize); 
    *(buffer + progdir_bytesize - 1) = '/'; 
    bcopy(log_subdir, buffer + progdir_bytesize, log_subdir_bytesize); 
    
    // RL: Does the subdir exist? 
    if (-1 == access(buffer, R_OK | W_OK | X_OK | F_OK)) { 
      // RL: No? Then let’s make it. 
      if (-1 == mkdir(buffer, (mode_t) 0777)) goto label__error__cannot_create_logdir; 
    }; 
    
    *(buffer + progdir_bytesize + log_subdir_bytesize - 1) = '/'; 
    bcopy(log_filename, buffer + progdir_bytesize + log_subdir_bytesize, log_filename_bytesize); 
    *log_filepathname_r = buffer; 
    return needed_bytesize; 
  }; 

  
 label__body: {
    if (NULL ==  progdir) goto label__progdir_is_empty; 
    if ('\0' == *progdir) goto label__progdir_is_empty; 

    if (NULL ==  log_filename) goto label__filename_is_empty; 
    if ('\0' == *log_filename) goto label__filename_is_empty; 

    if (NULL ==  log_subdir) goto label__subdir_is_empty; 
    if ('\0' == *log_subdir) goto label__subdir_is_empty; 
    
    goto label__subdir_is_not_empty; 
  }; 
  
}; 

int main__reassign_stdout_to_logfile(char * buffer, const int16_t buffer_bytesize) { 
  const int16_t buffer_used = main__reassign_stdout_to_logfile_aux(main_argv0__progdir, main__stdout_log_subdir, main__stdout_log_default_filename, &main__stdout_log_filepathname, main__stdout_log_pipe[1], &main__stdout_log_post_fd, buffer, buffer_bytesize); 
  return buffer_used; 
}; 

int main__reassign_stdout_to_logfile_aux(const char * progdir, const char * log_subdir, const char * log_filename, const char * * log_filepathname_r, const int pipe_write_fd, int * opened_log_fd_r, char * buffer, const int16_t buffer_bytesize) { 
  int16_t buffer_used = -1; 
  if (NULL == opened_log_fd_r) return -1; 
  if (0 > pipe_write_fd) return -2; 
  *opened_log_fd_r = -1; 
  goto label__body; 
  
 label__error__cannot_reopen_stdout_to_null: { 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Reopening stdout to null failed: NA - so I close it" "\n", __func__); 
    main__stdout_log_post_fd = -1; 
    return -1; 
  }; 
  
 label__reassign_to_null: { 
    const char path_to_null[] = "/dev/null"; 
    *log_filepathname_r = path_to_null; buffer_used = 0; 
#if 1 
    const int new_fd = open(*log_filepathname_r, O_WRONLY | O_CREAT | O_TRUNC, (mode_t) 0666); 
    if (-1 == new_fd) goto label__error__cannot_reopen_stdout_to_null; 
    //*(&stdout) = fdopen(pipe_write_fd, "wb"); 
    //assert(NULL != stdout); 
    setvbuf(stdout, NULL, _IONBF, 0); 
    //dup2(fileno(stdout), pipe_write_fd); 
    dup2(pipe_write_fd, fileno(stdout)); 
    *opened_log_fd_r = new_fd; 
#else 
    if (NULL == freopen(path_to_null, "wb", stdout)) goto label__error__cannot_reopen_stdout_to_null; 
    setvbuf(stdout, main__stdout_log_buffer, _IOFBF, sizeof(main__stdout_log_buffer)); 
    main__stdout_log_post_fd = fileno(stdout); 
#endif 
    return buffer_used; 
  }; 
  
 label__error__cannot_open_log_filepathname: { 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Could not open file (errno = %d): %s - so I assign log to /dev/null" "\n", __func__, (int) errno, *log_filepathname_r); 
    goto label__reassign_to_null; 
  }; 
  
  label__filepathname_failed: { 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Building and making filepathname failed: %s - so I assign log to /dev/null" "\n", __func__, (int) buffer_used); 
    goto label__reassign_to_null; 
  }; 
  
  label__filepathname_returned_zero: { 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Building and making filepathname returned zero - so I assign log to /dev/null" "\n", __func__); 
    goto label__reassign_to_null; 
  }; 
  
  label__reassign_to_fd9: { 
    const char path_to_fd9[] = "/dev/fd/9"; 
    *log_filepathname_r = path_to_fd9; buffer_used = 0; 
#if 1 
    const int new_fd = 9; //open(*log_filepathname_r, O_WRONLY | O_CREAT | O_TRUNC, (mode_t) 0666); 
    //if (-1 == new_fd) goto label__error__cannot_open_log_filepathname; 
    //fclose(stdout); 
    //stdout = fdopen(pipe_write_fd, "wb"); 
    //assert(NULL != stdout); 
    setvbuf(stdout, NULL, _IONBF, 0); 
    //dup2(fileno(stdout), pipe_write_fd); 
    dup2(pipe_write_fd, fileno(stdout)); 
    *opened_log_fd_r = new_fd; 
#else 
    if (NULL == freopen(path_to_fd9, "wb", stdout)) goto label__error__cannot_reopen_stdout; 
    setvbuf(stdout, main__stdout_log_buffer, _IOFBF, sizeof(main__stdout_log_buffer)); 
    assert(9 == fileno(stdout)); 
    *opened_log_fd_r = fileno(stdout); 
#endif 
    return buffer_used; 
  }; 
  
 label__reassign_to_log_filepathname: { 
#if 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "progdir: '%s'" "\n", __func__, progdir); 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "log_subdir: '%s'" "\n", __func__, log_subdir); 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "log_filename: '%s'" "\n", __func__, log_filename); 
#endif 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "log_filepathname: '%s'" "\n", __func__, *log_filepathname_r); 
#if 1 
    const int new_fd = open(*log_filepathname_r, O_WRONLY | O_CREAT | O_TRUNC, (mode_t) 0666); 
    if (-1 == new_fd) goto label__error__cannot_open_log_filepathname; 
    //fclose(stdout); 
    //stdout = fdopen(pipe_write_fd, "wb"); 
    //assert(NULL != stdout); 
    setvbuf(stdout, NULL, _IONBF, 0); 
    //dup2(fileno(stdout), pipe_write_fd); 
    dup2(pipe_write_fd, fileno(stdout)); 
    *opened_log_fd_r = new_fd; 
#else 
    if (NULL == freopen(log_filepathname, "wb", stdout)) goto label__error__cannot_reopen_stdout; 
    setvbuf(stdout, main__stdout_log_buffer, _IOFBF, sizeof(main__stdout_log_buffer)); 
    *opened_log_fd_r = fileno(stdout); 
#endif 
    return buffer_used; 
  }; 

  label__body: { 
    buffer_used = main__make_subdir_and_build_filepathname_aux(progdir, log_subdir, log_filename, log_filepathname_r, buffer, buffer_bytesize); 
    if (0 >  buffer_used) goto label__filepathname_failed; 
    if (0 == buffer_used) goto label__filepathname_returned_zero; 
    
    // RL: Si le fd a été ouvert par l’utilisateur, alors on écrit dedans. 
    // RL: '9' et pas '3' car GDB utilise fd3… 
    if (-1 != fcntl(9, F_GETFL)) goto label__reassign_to_fd9; 
    
    goto label__reassign_to_log_filepathname; 
  }; 
    
}; 














// =========================================================================== 
// III. STDERR TO LOG 

void main__stderr_buffer__flush(void) { 
#if 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "main__stderr_buffer_nb: '%d'" "\n", __func__, (int) main__stderr_buffer_nb); 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "main__stderr_post_fd: '%d'" "\n", __func__, (int) main__stderr_post_fd); 
#endif 
  if (0 >  main__stderr_post_fd) return; 
  //if (0 >  main__stderr_buffer_nb) { main__stderr_buffer_nb = 0; return; }; 
  if (0 == main__stderr_buffer_nb) return; 
  if (0 <= main__stderr_post_fd) write(main__stderr_post_fd, main__stderr_buffer, main__stderr_buffer_nb); 
  main__stderr_buffer_nb = 0; 
}; 

int main__stderr_pipe__open(void) { 
  return main__stderr_pipe__open_aux(main__stderr_pipe, &main__stderr_pipe__SIGIO_handler, &main__stderr_pipe__SIGIO_former_handler); 
}; 

void main__stderr_pipe__close(void) { 
  close(main__stderr_pipe[0]); 
  close(main__stderr_pipe[1]); 
  main__stderr_pipe[0] = -1; 
  main__stderr_pipe[1] = -1; 
  signal(SIGIO, main__stderr_pipe__SIGIO_former_handler); 
}; 

int main__stderr_pipe__open_aux(int * stderr_pipe, void (* handler)(int), void (* (*former_handler_r))(int)) { 
  if (NULL == former_handler_r) return -1; 
  *former_handler_r = NULL; 
  goto label__body; 
  
  label__error__making_pipe_failed: {
    stderr_pipe[0] = -1; 
    stderr_pipe[1] = -1; 
    return -2; 
  }; 
  
  label__error__installing_SIGIO_handler_failed: { 
    close(stderr_pipe[0]); 
    close(stderr_pipe[1]); 
    stderr_pipe[0] = -1; 
    stderr_pipe[1] = -1; 
    return -3; 
  }; 

 label__body: { 
    if (-1 == pipe(stderr_pipe)) goto label__error__making_pipe_failed; 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "pipe[0,1] =  [%d, %d] " "\n", __func__, (int) stderr_pipe[0], (int) stderr_pipe[1]); 
    
    void * former_handler = signal(SIGIO, handler); 
    if (SIG_ERR == former_handler) goto label__error__installing_SIGIO_handler_failed; 
    *former_handler_r = former_handler; 
    
    fcntl(stderr_pipe[0], F_SETOWN, getpid()); // RL: Qui recevra le signal SIGIO? 
    fcntl(stderr_pipe[0], F_SETFL, O_ASYNC | O_NONBLOCK); // RL: Générer le signal SIGIO + Ne pas bloquer en cas de poll. 
    
    return 0; 
  }; 
}; 

void main__stderr__dup_to_post(void) { 
  return main__stderr__dup_to_post_aux(&main__stderr_post_fd); 
}; 

void main__stderr__dup_to_post_aux(int * stderr_post_fd_r) { 
  *stderr_post_fd_r = dup(fileno(stderr)); // This call generates two SIGIO. 
}; 


void main__stderr_pipe__SIGIO_handler(int sig) { 
  // RL: Dans cette routine, nous appelons write(2) qui génère des SIGIO. 
  //     Donc nous devons désactiver le mask, et réinstaller le former_handler. 
  // RL: Symétriquement, notre handler devra être réinstallé à la sortie. 
  //     En revanche, le masque est remis automatiquement à chaque génération du signal SIGIO. 
  { 
    sigset_t sigset[1]; 
    sigemptyset(sigset);
    sigaddset(sigset, SIGIO);
    signal(SIGIO, main__stderr_pipe__SIGIO_former_handler); 
    sigprocmask(SIG_UNBLOCK, sigset, NULL); 
  }; 
#if 0 
  int debug_fd = open("/dev/tty", O_WRONLY); 
  char debug_buffer[1024]; 
#endif 
  goto label__body;

  label__exit: { 
#if 0 
    close(debug_fd); 
#endif 
    signal(SIGIO, main__stderr_pipe__SIGIO_handler); 
    return; 
  }; 
 
  label__pas_nous: {
    if (NULL == main__stderr_pipe__SIGIO_former_handler) goto label__exit; 
    main__stderr_pipe__SIGIO_former_handler(sig); 
    goto label__exit; 
  }; 
  
  label__body: { 
    // RL: Ici, nous avons un problème: nous ne savons pas qui généra le signal. 
    //     En particulier, était-ce le nôtre ou un autre? 
    //     Donc il faut tester. 
    //     Et pour tester, pas le choix, il faut faire un read(2). 
    //     Et cette lecture doit être non bloquante, et donc le flag O_NONBLOCK doit avoir été allumé en amont. 
    //     Sinon, on reste bloqué ici. 
    // RL: Pour une raison quelconque, le buffer est peut-être déjà plein. 
    if (main__stderr_buffer__bytesize == main__stderr_buffer_nb) { 
      if (0 <= main__stderr_post_fd) write(main__stderr_post_fd, main__stderr_buffer, main__stderr_buffer_nb); 
      main__stderr_buffer_nb = 0; 
    }; 
    const ssize_t read_nb = read(main__stderr_pipe[0], main__stderr_buffer + main__stderr_buffer_nb, main__stderr_buffer__bytesize - main__stderr_buffer_nb); 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "read_nb: '%d'" "\n", __func__, (int) read_nb); 
#if 0 
    if (false) { 
      write_long_long_int_into_buffer(debug_buffer, sizeof(debug_buffer), read_nb); 
      write_string3(debug_fd, "[STDERR HANDLER] ---> read_nb = ", debug_buffer, "\n"); 
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "read_nb: '%d'" "\n", __func__, (int) read_nb); 
      if (0 < read_nb) write(debug_fd, main__stderr_buffer + main__stderr_buffer_nb, read_nb); 
    }; 
#endif 
    if (0 >= read_nb) goto label__pas_nous; 
    main__stderr_buffer_nb += read_nb; 
    
    // RL: On copie dans stdout-log. 
    { int16_t qty_left = read_nb; for (;;) { 
	if (0 == qty_left) break; 
	if (main__stdout_log_buffer__bytesize == main__stdout_log_buffer_nb) { 
	  if (0 <= main__stdout_log_post_fd) write(main__stdout_log_post_fd, main__stdout_log_buffer, main__stdout_log_buffer_nb); 
	  main__stdout_log_buffer_nb = 0; 
	}; 
	const int16_t to_be_copied = MIN(main__stdout_log_buffer__bytesize - main__stdout_log_buffer_nb, qty_left); 
	bcopy(main__stderr_buffer + main__stderr_buffer_nb - qty_left, main__stdout_log_buffer + main__stdout_log_buffer_nb, to_be_copied); 
	main__stdout_log_buffer_nb += to_be_copied; 
	qty_left -= to_be_copied; 
	continue; 
    }; }; 

    // RL: On flush tout de suite: stderr is unbuffered. 
    if (true) { 
      if (0 <= main__stderr_post_fd) write(main__stderr_post_fd, main__stderr_buffer, main__stderr_buffer_nb); 
      main__stderr_buffer_nb = 0; 
    }; 
    goto label__exit; 
  }; 
}; 


int main__stderr__reassign_to_pipe(void) { 
  return main__stderr__reassign_to_pipe_aux(main__stderr_pipe[1]); 
}; 

int main__stderr__reassign_to_pipe_aux(const int pipe_write_fd) { 
  if (0 > pipe_write_fd) return -2; 
  goto label__body; 
  
  label__body: { 
    setvbuf(stderr, NULL, _IONBF, 0); 
#if 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "pipe_write_fd =  %d " "\n", __func__, (int) pipe_write_fd); 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "fileno(stderr) =  %d " "\n", __func__, (int) fileno(stderr)); 
#endif 
    //dup2(fileno(stderr), pipe_write_fd); // This call generates two SIGIO. 
    dup2(pipe_write_fd, fileno(stderr)); // This call generates two SIGIO. 
#if 0 
    write_string(pipe_write_fd, "HELLO pipe_write_fd" "\n"); 
    write_string(fileno(stderr), "HELLO fileno(stderr)" "\n"); 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "pipe_write_fd =  %d " "\n", __func__, (int) pipe_write_fd); 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "fileno(stderr) =  %d " "\n", __func__, (int) fileno(stderr)); 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "pipe[0,1] =  [%d, %d] " "\n", __func__, (int) main__stderr_pipe[0], (int) main__stderr_pipe[1]); 
#endif 
    return 0; 
  }; 
    
}; 














// =========================================================================== 
// DIVERS 


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
    //fprintf(stdout, "sizeof(u): %d" "\n", (int) sizeof(u)); // RL: Good: 12288. 
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
    fprintf(stdout, "Taille actuelle de la stack: %d - Taille maximale de la stack: %d - &a = %p - sbrk(0) = %p " "\n", (int)rlp -> rlim_cur, (int)rlp -> rlim_max, &a, sbrk(0)); 
    fprintf(stdout, "etext = %p - edata = %p - end = %p  " "\n", etext, edata, end); 

  }; 
  { 
    char a; 
    struct rusage rusage[1]; 
    getrusage(RUSAGE_SELF, rusage); 
    fprintf(stdout, "rusage -> ru_isrss = %d" "\n", (int) rusage -> ru_isrss); 
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
    fprintf(stdout, "dlopen = %p  " "\n", a); 
    fprintf(stdout, "dlerror = %s  " "\n", dlerror()); 

    Dl_info info[1]; 
    if (!dladdr(a, info)) { 
      fprintf(stdout, "dladdr: nothing found: %s  " "\n", dlerror()); 
    } 
    else { 
      fprintf(stdout, "dladdr: dli_fname = %s - dli_fbase = %p - dli_sname = %s - dli_saddr = %p  " "\n", info -> dli_fname, info -> dli_fbase, info -> dli_sname, info -> dli_saddr); 
    }; 
    
    void * fun = dlsym(a, "timer_hello"); 
    fprintf(stdout, "dlsym = %p  " "\n", fun); 
    fprintf(stdout, "dlerror = %s  " "\n", dlerror()); 

    if (!dladdr(fun, info)) { 
      fprintf(stdout, "dladdr: nothing found: %s  " "\n", dlerror()); 
    } 
    else { 
      fprintf(stdout, "dladdr: dli_fname = %s - dli_fbase = %p - dli_sname = %s - dli_saddr = %p  " "\n", info -> dli_fname, info -> dli_fbase, info -> dli_sname, info -> dli_saddr); 
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

