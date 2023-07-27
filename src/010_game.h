#ifndef GAME_H 
#define GAME_H 

enum TModeJeu { 
 mjTITRE,  // au début, on affiche le titre 
 mjCARTE,  // mode normal 
 mjHEROS_MORT,  // 
 mjOEIL,   // 
 mjAEROTHEIERE, 
 mjINVENTAIRE,   // menu pour le choix des armes etc... 
 mjIDLE, // on est en train d'exécuter un script 
 mjTELEPORTATION, 
 mjNOMBRE 
};
TYPEDEF_TYPENAME_WITHOUT_ENUM(TModeJeu);

extern int  Game_Init(api_contexte_t * api_contexte); 
//extern int  Game_Loop(void); 
//extern int  Game_Loop(const int blit_huh); 
extern int  Game_Loop(const int animate_but_do_not_aliven_huh, api_contexte_t * api_contexte); 
extern void Game_Dispose(void); 

extern bool show_choc_cube_huh; 

extern void Game_EventsHandlers__reset(void); 
// For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
//extern int  Game_EventsHandlers__push (const int evt_type, const int handler_type, const int int_argc, const int int_argv[int_argc], const int ptr_argc, void * ptr_argv[ptr_argc], const int cptr_argc, const void * cptr_argv[ptr_argc]); 
extern int  Game_EventsHandlers__push (const int evt_type, const int handler_type, const int int_argc, const int int_argv[], const int ptr_argc, void * ptr_argv[], const int cptr_argc, const void * cptr_argv[]); 
extern int  Game_EventsHandlers__push0(const int evt_type, const int handler_type); 
extern int  Game_EventsHandlers__push_script(const int evt_type, const char * script_file, const char * script_name); 

extern int Game_Events_Raise(const int evt_type); 

#endif /* GAME_H */ 

