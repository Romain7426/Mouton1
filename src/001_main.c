#include "global.h"
#include "001_main.h"
#include "002_kernel.h"
//#include "son.h" 
//#include "keys.h"
//#include "timer.h"
#include <sys/resource.h> 
#include <dlfcn.h>
 
// RL: This file contains all the system stuffs. 
//     Anything here is not related to the program per se. 
//     And is done only once. 


static const char stdout_log_filename[] = LOGDIR "stdout.log"; 


static void change_to_root_dir(const char * argv0); 
static void main_proctitle_set(void); 
static void main_locale_set(void); 
static void main_rand_init(void); 
static void main_date_print(void); 
static void main_gcc_print(void); 
static void main_arch_print(void); 
static void main_args_print(const int argc, const char * argv[]); 
static void main_win_print(void); 



  

int main(const int argc, const char * argv[]) {
//int _SDL_main(int argc, char * argv[]) {
  int retour = -1;
  
  // RL: This is the first thing to do, 
  //     as we will need to write log files 
  //     and read data files. 
  change_to_root_dir(argv[0]);

  // RL: LOG FILE 
  //     Redirecting 'stdout' to the log file. 
  // RL: The idea is that any errors should show up on 'stderr', so that we know that something 
  //     happened, but also on the log file to have context. 
  //  --- man 3 freopen --- 
  // The freopen() function opens the file whose name is the string pointed to by path. 
  // The original stream (if it exists) is closed. 
  // The primary use of the freopen() function is to change the file associated with a standard text stream (stderr, stdin, or stdout). 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " stdout = %p " "\n", __func__, stdout); 
  { dprintf(fileno(stdout), "STDOUT BUFFER: %p\n", stdout -> _bf._base); }; 
  { dprintf(fileno(stdout), "STDERR BUFFER: %p\n", &stderr -> _bf); }; 
#if 1 
  freopen(stdout_log_filename, "wb", stdout); 
  char stdout_buffer[1 << 12]; 
  //setvbuf(stdout, stdout_buffer, _IONBF, sizeof(stdout_buffer)); // RL: Unbuffered. 
  //setvbuf(stdout, stdout_buffer, _IOLBF, sizeof(stdout_buffer)); // RL: Line buffered. 
  //setvbuf(stdout, stdout_buffer, _IOFBF, sizeof(stdout_buffer)); // RL: Fully buffered. 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " sizeof(stdout_buffer) = %d"   "\n", __func__, (int) sizeof(stdout_buffer)); 
  fprintf(stdout, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " sizeof(stdout_buffer) = %d"   "\n", __func__, (int) sizeof(stdout_buffer)); 
#endif 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " stdout = %p " "\n", __func__, stdout); 
  { dprintf(fileno(stdout), "STDOUT BUFFER: %p\n", stdout -> _bf._base); }; 
  { dprintf(fileno(stdout), "STDERR BUFFER: %p\n", &stderr -> _bf); }; 
  { dprintf(fileno(stdout), "STDOUT BUFFER: %p - " __FILE__ " - %d \n", (const void *)stdout -> _bf._base, (int)__LINE__); }; 
  { const char __file__[] = "" __FILE__ ""; dprintf(fileno(stdout), "STDOUT BUFFER: %p - %s - %d \n", (const void *)stdout -> _bf._base, (const char *)__file__, (int)__LINE__); }; 
  
  
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

  { dprintf(fileno(stdout), "STDOUT BUFFER: %p\n", stdout -> _bf._base); }; 

  printf("<<< main" "\n"); 
  printf("===============================================================================" "\n"); 
  do { 
    retour = Kernel_Init(); if (retour < 0) { break; }; 
  { dprintf(fileno(stdout), "STDOUT BUFFER: %p\n", stdout -> _bf._base); }; 

    retour = Kernel_Run(); 
    Kernel_Dispose(); 
    break; 
  } while (false); 
  printf("===============================================================================" "\n"); 
  printf(">>> main" "\n"); 
  
  fprintf(stdout, "Fin du jeu!\n"); 
  
  fflush(NULL); 
  
  return retour; 
}; 





void change_to_root_dir(const char * argv0) {
  char * path = strcopy(argv0);
  char * program_name = strrchr(path, '/');

  assert(program_name != NULL);

  *program_name = '\0';

  assert(0 == chdir(path));

  free(path);

  //fprintf(stderr, "%s\n", getcwd(NULL, 0));
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

