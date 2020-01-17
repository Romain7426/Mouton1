#include "global.h"
#include "kernel.h"
#include "main.h"
#include "son.h" // pour l'initialisation
#include "evenement.h"
#include "keys.h"

#include "timer.h"


/* Ce fichier contient les trucs pas beau à voir. Il contient le main. La boucle
   du programme... les initialisation d'OpenGL et de la SDL...
   normalement, tu n'y touches plus... pour toi, le vrai programme c'est dans
   main.cpp
*/



#define SCREEN_BITSPERPIXEL 16
#define DebugDoncOnNeSwitchePas false

//static unsigned char * KeyBoard;
static TMouse Mouse;

static bool isrunning = 1;


static SDL_Rect Rectangle_Destination;
static SDL_Surface *Screen, *text;

static void setup_opengl(int width, int height);
static bool init_sdl_opengl(void);
static void free_sdl(void);


static void process_events(void);


#if 0
static FILE * stdout_save = NULL;
static FILE * stdout_log = NULL;
#endif
static const char stdout_log_filename[] = LOGDIR "stdout.log";


static void change_to_root_dir(const char * argv0);
static void main_locale_set(void);
static void main_date_print(void);
static void main_gcc_print(void);
static void main_args_print(int argc, char * argv[]);
static void main_win_print(void);


int main(int argc, char * argv[]) {
//int _SDL_main(int argc, char * argv[]) {
  int retour = -1;

  change_to_root_dir(argv[0]);

#if 0
  stdout_save = stdout;
  stdout_log = fopen(stdout_log_filename, "wb");
  if (stdout_log != NULL)
    stdout = stdout_log;
#else
  // The freopen() function opens the file whose name is the string pointed to by path.
  // The original stream (if it exists) is closed.
  // The primary use of the freopen() function is to change the file associated with a standard text stream (stderr, stdin, or stdout).
  freopen(stdout_log_filename, "wb", stdout);
#endif

  fprintf(stdout, "Démarrage du jeu!!!\n\n");

  main_locale_set();
  main_date_print();
  main_gcc_print();
  main_args_print(argc, argv);
  main_win_print();

  init_message();
  message("argc = %d ; argv = %p" "\n", argc, argv);
  
  
  if (init_sdl_opengl()) {
    

    init_audio();

    Init();
#if 0  
    Free(); 
    close_audio(); 
    free_sdl();
    exit(0); 
#endif 


    
    while (isrunning) {
      SCRIPT_unepassedeboucle();
    }

    Free();
    close_audio();
    free_sdl();

    retour = 0;
  }

  else {
    retour = -2;
  }   

  
  end_message();
  fprintf(stdout, "Fin du jeu!\n");

  fflush(NULL);
#if 0
  stdout = stdout_save;
  fclose(stdout_log);
#endif
  
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




void DemanderAQuitterLeJeu(void) {
  isrunning = false;
};




void SCRIPT_unepassedeboucle(void) {
#define COUNT
  //#undef COUNT
#ifdef COUNT
  static int count = 0;
  if (count != 0) 
    return;

  count++;
#endif

  DebutDePasse(); 

  //handle_evts(); // evnt du jeu.
  
  process_events(); {
    KeyBoard = SDL_GetKeyState(NULL);
    RaiseInput();
    
#if 0
    Mouse.dx = 0;
    Mouse.dy = 0;
#endif

    RaiseLife();
    RaiseRender();
  }
  
  FinDePasse();
  fflush(NULL);
#ifdef COUNT
  count--;
#endif
};



//gère les évenements
void process_events(void) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE) //echap -> on quitte
	isrunning = 0;
	  
      //KeyBoard[event.key.keysym.sym] = 1;
      break;
      
    case SDL_KEYUP:
      //KeyBoard[event.key.keysym.sym] = 0;
      break;
      
    case SDL_MOUSEMOTION:
      Mouse.dx = event.motion.xrel;
      Mouse.dy = event.motion.yrel;
      Mouse.x = event.motion.x;
      Mouse.y = event.motion.y;
      break;
      
      
    case SDL_QUIT: // Handle quit requests (like Ctrl-c).
      isrunning = 0;
      break;
      
    default: {}
    };
  };
};





















void setup_opengl(int width, int height) {
  float ratio = (float) width / (float) height;

  /* Setup our viewport. */
  glViewport(0, 0, width, height);

  /* Our shading model--Gouraud (smooth). */
  glShadeModel(GL_SMOOTH);

  /* Set the clear color. */
  glClearColor(0.0, 0.0, 0.0, 1.0);

  /* Set the clear depth */
  glClearDepth(1.0);
  
  /* Culling. */
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);

  glEnable(GL_DEPTH_TEST) ;

  /*
   * Change to the projection matrix and set
   * our viewing volume.
   */
  //glMatrixMode(GL_MODELVIEW);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  /*
   * EXERCISE:
   * Replace this with a call to glFrustum.
   */
  gluPerspective(60.0, ratio, 1.0, 1024.0);
};






// initialise SDL, OpenGL...renvoie vrai ssi succès
bool init_sdl_opengl(void) {
  printf("Initialisation de la SDL...\n");

  if (-1 == SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) { 
    messerr("Erreur lors de l'initialisation de la SDL: %s." "\n", SDL_GetError());
    return false; 
  };
  
  printf("SDL initialisée.\n");

  /*
   * Now, we want to setup our requested
   * window attributes for our OpenGL window.
   * We want *at least* 5 bits of red, green
   * and blue. We also want at least a 16-bit
   * depth buffer.
   *
   * The last thing we do is request a double
   * buffered window. '1' turns on double
   * buffering, '0' turns it off.
   *
   * Note that we do not use SDL_DOUBLEBUF in
   * the flags to SDL_SetVideoMode. That does
   * not affect the GL attribute state, only
   * the standard 2D blitting setup.
   */
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  // Set the video mode
  if (!DebugDoncOnNeSwitchePas)
    if (0 == SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BITSPERPIXEL, SDL_OPENGL | SCREEN_MODE | SDL_DOUBLEBUF | SDL_HWSURFACE /*| SDL_NOFRAME*/)) {
      messerr("Video mode set failed: %s" "\n", SDL_GetError());
      return 0;
    };
  

  //SDL_WarpMouse(320, 240);
  SDL_ShowCursor(true);	
  
  setup_opengl(SCREEN_WIDTH, SCREEN_HEIGHT);
  
  Screen = SDL_GetVideoSurface();
  
  
  if (Screen == NULL) {
    messerr("La surface écran 'Screen' n'a pas pu être référencée" "\n");
    messerr("SDL: %s" "\n", SDL_GetError());
  };

  return true;
};




//libère la mémoire...
void free_sdl(void) {
  
  printf("On quitte la SDL.\n");

#if 1 
  // RL: 2020-01-12: For some reasons, it crashes... 
  SDL_Quit();
#endif 
  
  printf("On quitte....\n");
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



void main_date_print(void) {
  time_t date_time;
  char date_chaine[26];
  
  srandom(time(&date_time));
  printf("Nous sommes le %s\n", ctime_r(&date_time, date_chaine));
};

void main_gcc_print(void) {
  printf("Compilé avec GCC %s.%s.%s\n", STRING(__GNUC__) , STRING(__GNUC_MINOR__), STRING(__GNUC_PATCHLEVEL__));
  printf("Le %s à %s.\n", __DATE__, __TIME__); //STRING(__DATE__), STRING(__TIME__));
  printf("GCC version: %s", __VERSION__);
};

void main_args_print(int argc, char * argv[]) {
  printf("\nListe des paramètres: ");

  for (int i = 0; i < argc; i ++) {
    printf("\t%s\n", argv[i]);
  };
};

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
#endif
};

