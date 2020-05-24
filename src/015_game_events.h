#ifndef GAME_EVENTS_H 
#define GAME_EVENTS_H 

// *** GAME_EVENTS_SUBTYPE *** 

enum { 
  GAME_EVENTS__MAP__HERO_NO_MORE_PV, 
  GAME_EVENTS__MAP__ALL_HOSTILES_DEAD, 
  GAME_EVENTS__MAP__LOADED_STARTING_FADING, 
  GAME_EVENTS__MAP__LOADED_READY, 
  GAME_EVENTS__MAP__LEAVING, 
  GAME_EVENTS__MAP__GATEWAY_INTERSECTED, 
  GAME_EVENTS__COUNT 
}; 

// RL: Use for storage, where data should be packed. Anywhere else, 'int' is good. The property ensures that a game_events will fit into a 'int_game_events_t'. 
typedef       int8_t            int_game_events_t; 
extern  const int_game_events_t int_game_events_max; 
extern  const int_game_events_t     game_events_count; 

extern const char *       game_events__get_cstr(const int game_events); 
#define game_events__cstr game_events__get_cstr 


// *** GAME_HANDLERS_SUBTYPE *** 

enum { 
  GAME_HANDLERS__SCRIPT, 
  GAME_HANDLERS__CALLBACK, 
  GAME_HANDLERS__STANDARD__HEROS_MORT, 
  GAME_HANDLERS__COUNT 
}; 

// RL: Use for storage, where data should be packed. Anywhere else, 'int' is good. The property ensures that a game_handlers will fit into a 'int_game_handlers_t'. 
typedef       int8_t              int_game_handlers_t; 
extern  const int_game_handlers_t int_game_handlers_max; 
extern  const int_game_handlers_t int_game_handlers_count; 

extern const char * game_handlers__get_cstr(const int game_handlers); 
#define game_handlers__cstr game_handlers__get_cstr 


// *** GAME_EVENTS_ENV *** 

#ifndef GAME_EVENTS_ENV_T 
#define GAME_EVENTS_ENV_T 
struct game_events_env_t; 
typedef struct game_events_env_t game_events_env_t; 
#endif /* GAME_EVENTS_ENV_T */ 
extern const int game_events_env__sizeof; 
extern game_events_env_t * game_events_env__make    (void); 
extern game_events_env_t * game_events_env__make_r  (game_events_env_t * this); 
extern game_events_env_t * game_events_env__make_b  (const int buffer_size, char * buffer, int * buffer_used_ref); 
extern void                game_events_env__delete  (game_events_env_t * * this_ref); 
extern void                game_events_env__delete_r(game_events_env_t * this); 
extern void                game_events_env__print_d (const int fd, const game_events_env_t * this); 
 
 
// *** GAME_EVENTS *** 
 
//extern void game_events__handlers__reset  (                    game_events_env_t * this); 
extern int  game_events__handlers__count  (              const game_events_env_t * this, const int evt_type); 
extern int  game_events__handlers__empty  (                    game_events_env_t * this, const int evt_type); 
extern int  game_events__handlers__print_d(const int fd, const game_events_env_t * this, const int evt_type); 
extern int  game_events__handlers__push   (                    game_events_env_t * this, const int evt_type, const int handler_type, const int int_argc, const int int_argv[int_argc], const int ptr_argc, void * ptr_argv[ptr_argc], const int cptr_argc, const void * cptr_argv[ptr_argc]); 
extern int  game_events__handlers__push0  (                    game_events_env_t * this, const int evt_type, const int handler_type); 
extern int  game_events__handlers__push_script(                game_events_env_t * this, const int evt_type, const char * script_file, const char * script_name); 


extern int  game_events__stack__count  (              const game_events_env_t * this); 
extern int  game_events__stack__empty  (                    game_events_env_t * this); 
extern int  game_events__stack__push   (                    game_events_env_t * this, const int evt_type); 
extern int  game_events__stack__print_d(const int fd, const game_events_env_t * this); 

extern int  game_events__process(game_events_env_t * this, api_contexte_t * api_contexte); 





#endif /* GAME_EVENTS_H */ 
