#include "global.h" 
#include "015_game_events.h" 
#include "010_game.h" 

// *** GAME_EVENTS_SUBTYPE *** 

const int_game_events_t int_game_events_max   = INT8_MAX; 
const int_game_events_t     game_events_count = GAME_EVENTS__COUNT; 

static const char * game_events__cstr__array[] = { 
  "MAP__HERO_NO_MORE_PV", 
  "MAP__ALL_HOSTILES_DEAD", 
  "MAP__LOADED_STARTING_FADING", 
  "MAP__LOADED_READY", 
  "MAP__LEAVING", 
  "MAP__GATEWAY_INTERSECTED", 
  NULL
}; 
enum {           game_events__cstr__array__size__compiler_const = ARRAY_SIZE(game_events__cstr__array) }; 
static const int game_events__cstr__array__size                 = game_events__cstr__array__size__compiler_const; 

static void assert_compile__game_events_type__dsaljdhsa7643i2utgd(void) { 
  ASSERT_COMPILE(game_events__cstr__array__size__compiler_const == GAME_EVENTS__COUNT + 1); 
}; 

const char * game_events__get_cstr(const int game_events) { 
  if (game_events <  0                 ) { return NULL; }; 
  if (game_events >= GAME_EVENTS__COUNT) { return NULL; }; 
  return game_events__cstr__array[game_events]; 
}; 


// *** GAME_HANDLERS_SUBTYPE *** 

const int_game_handlers_t int_game_handlers_max   = INT8_MAX; 
const int_game_handlers_t     game_handlers_count = GAME_HANDLERS__COUNT; 

static const char * game_handlers__cstr__array[] = { 
  "SCRIPT", 
  "CALLBACK", 
  "STANDARD__HEROS_MORT", 
  NULL
}; 
enum {           game_handlers__cstr__array__size__compiler_const = ARRAY_SIZE(game_handlers__cstr__array) }; 
static const int game_handlers__cstr__array__size                 = game_handlers__cstr__array__size__compiler_const; 

static void assert_compile__game_handlers__dsaljdhsa7643i2utgd(void) { 
  ASSERT_COMPILE(game_handlers__cstr__array__size__compiler_const == GAME_HANDLERS__COUNT + 1); 
}; 

const char * game_handlers__get_cstr(const int game_handlers) { 
  if (game_handlers <  0                   ) { return NULL; }; 
  if (game_handlers >= GAME_HANDLERS__COUNT) { return NULL; }; 
  return game_handlers__cstr__array[game_handlers]; 
}; 



// *** GAME_EVENTS_ENV *** 

enum { GAME_EVENTS_ENV__STACK__SIZE           = 16 }; 
enum { GAME_EVENTS_ENV__HANDLER__SIZE         =  4 }; 
enum { GAME_EVENTS_ENV__HANDLER__INTARG_SIZE  =  4 }; 
enum { GAME_EVENTS_ENV__HANDLER__PTRARG_SIZE  =  4 }; 
enum { GAME_EVENTS_ENV__HANDLER__CPTRARG_SIZE =  4 }; 
enum { GAME_EVENTS_ENV__HANDLER__ARG_SIZE     =  
   sizeof(int8_t) + sizeof(      int   ) * GAME_EVENTS_ENV__HANDLER__INTARG_SIZE + 
   sizeof(int8_t) + sizeof(      void *) * GAME_EVENTS_ENV__HANDLER__PTRARG_SIZE + 
   sizeof(int8_t) + sizeof(const void *) * GAME_EVENTS_ENV__HANDLER__CPTRARG_SIZE }; 

struct game_events_env_t { 
  int8_t malloced_huh; 
  
  int_game_handlers_t handlers    [GAME_EVENTS__COUNT][GAME_EVENTS_ENV__HANDLER__SIZE]; 
  int_game_handlers_t handlers__nb[GAME_EVENTS__COUNT]; 
  uint8_t             handlers_arg[GAME_EVENTS__COUNT][GAME_EVENTS_ENV__HANDLER__SIZE][GAME_EVENTS_ENV__HANDLER__ARG_SIZE]; 
  
  int_game_events_t stack   [GAME_EVENTS_ENV__STACK__SIZE]; 
  uint8_t           stack_nb; 
  
}; 

enum {    game_events_env__sizeof__compiler_const = sizeof(game_events_env_t) }; 
const int game_events_env__sizeof                 = game_events_env__sizeof__compiler_const; 


game_events_env_t * game_events_env__make(void) { 
  game_events_env_t * this; 
  this = (game_events_env_t *) malloc(sizeof(*this)); 
  game_events_env__make_r(this); 
  this -> malloced_huh = true; 
  return this; 
}; 

game_events_env_t * game_events_env__make_r(game_events_env_t * this) { 
  bzero(this, sizeof(*this)); 
  return this; 
}; 

game_events_env_t * game_events_env__make_b(const int buffer_size, char * buffer, int * buffer_used_ref) { 
  if (buffer_size < game_events_env__sizeof__compiler_const) { 
    *buffer_used_ref = 0; 
    return NULL; 
  }; 

  *buffer_used_ref = game_events_env__sizeof__compiler_const; 
  game_events_env_t * this; 
  this = (game_events_env_t *) buffer; 
  game_events_env__make_r(this); 
  return this; 
}; 
 
void game_events_env__delete(game_events_env_t * * this_ref) { 
  const int malloced_huh = (*this_ref) -> malloced_huh; 
  game_events_env__delete_r(*this_ref); 
  if (malloced_huh) free(*this_ref); 
  *this_ref = NULL; 
}; 
 
void game_events_env__delete_r(game_events_env_t * this) { 
  bzero(this, sizeof(*this)); 
}; 
 
void game_events_env__print_d(const int fd, const game_events_env_t * this) { 
  dprintf(fd, "game_events_env[%p]", this); 
}; 
 
 
// *** GAME_EVENTS *** 
 
int game_events__handlers__count(const game_events_env_t * this, const int evt_type) { 
  return this -> handlers__nb[evt_type]; 
}; 
 
int game_events__handlers__empty(game_events_env_t * this, const int evt_type) { 
  this -> handlers__nb[evt_type] = 0; 
  return 0; 
}; 
  
int game_events__handlers__print_d(const int fd, const game_events_env_t * this, const int evt_type) { 
  dprintf(fd, "game_handlers of %s", game_events__get_cstr(evt_type)); 
  return 0; 
}; 

int game_events__handlers__push0(game_events_env_t * this, const int evt_type, const int handler_type) { 
  const int retval = game_events__handlers__push(this, evt_type, handler_type, /*int_argc*/0, /*int_argv*/((int [0]){}), /*ptr_argc*/0, /*ptr_argv*/((void * [0]){}), /*cptr_argc*/0, /*cptr_argv*/((const void * [0]){})); 
  return retval; 
}; 

int game_events__handlers__push_script(game_events_env_t * this, const int evt_type, const char * script_file, const char * script_name) { 
  //const int retval = game_events__handlers__push(this, evt_type, GAME_HANDLERS__SCRIPT, /*int_argc*/0, /*int_argv*/((int [0]){}), /*ptr_argc*/0, /*ptr_argv*/((void * [0]){}), /*cptr_argc*/2, /*cptr_argv*/((const void * [2]) {script_file, script_name})); 
  const int retval = game_events__handlers__push(this, evt_type, GAME_HANDLERS__SCRIPT, /*int_argc*/0, /*int_argv*/((int [0]){}), /*ptr_argc*/2, /*ptr_argv*/((void * [2]){strcopy(script_file), strcopy(script_name)}), /*cptr_argc*/0, /*cptr_argv*/((const void * [0]) {})); 
  return retval; 
}; 

 
// For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
//int game_events__handlers__push(game_events_env_t * this, const int evt_type, const int handler_type, const int int_argc, const int int_argv[int_argc], const int ptr_argc, void * ptr_argv[ptr_argc], const int cptr_argc, const void * cptr_argv[ptr_argc]) { 
int game_events__handlers__push(game_events_env_t * this, const int evt_type, const int handler_type, const int int_argc, const int int_argv[], const int ptr_argc, void * ptr_argv[], const int cptr_argc, const void * cptr_argv[]) { 
  if (( evt_type < 0) || ( evt_type >= GAME_EVENTS__COUNT                    )) return -1; 
  if (( int_argc < 0) || ( int_argc >= GAME_EVENTS_ENV__HANDLER__INTARG_SIZE )) return -2; 
  if (( ptr_argc < 0) || ( ptr_argc >= GAME_EVENTS_ENV__HANDLER__PTRARG_SIZE )) return -3; 
  if ((cptr_argc < 0) || (cptr_argc >= GAME_EVENTS_ENV__HANDLER__CPTRARG_SIZE)) return -4; 
  if ((this -> handlers__nb[evt_type] < 0) || (this -> handlers__nb[evt_type] >= GAME_EVENTS_ENV__HANDLER__SIZE)) return -5; 
  const int index = this -> handlers__nb[evt_type]; 
  this -> handlers__nb[evt_type]++; 
  this -> handlers[evt_type][index] = handler_type; 
  int arg_index = 0; 
  this -> handlers_arg[evt_type][index][arg_index] = int_argc; arg_index += sizeof(int8_t); 
  for (int i = 0; i < int_argc; i++) { 
    *(int *)(&this -> handlers_arg[evt_type][index][arg_index]) = int_argv[i]; arg_index += sizeof(int); 
  }; 
  this -> handlers_arg[evt_type][index][arg_index] = ptr_argc; arg_index += sizeof(int8_t); 
  for (int i = 0; i < ptr_argc; i++) { 
    *(void * *)(&this -> handlers_arg[evt_type][index][arg_index]) = ptr_argv[i]; arg_index += sizeof(void *); 
  }; 
  this -> handlers_arg[evt_type][index][arg_index] = cptr_argc; arg_index += sizeof(int8_t); 
  for (int i = 0; i < cptr_argc; i++) { 
    *(const void * *)(&this -> handlers_arg[evt_type][index][arg_index]) = cptr_argv[i]; arg_index += sizeof(const void *); 
  }; 
  assert(arg_index <= GAME_EVENTS_ENV__HANDLER__ARG_SIZE); 
  
  return index; 
}; 
 
 
 
int game_events__stack__count(const game_events_env_t * this) { 
  return this -> stack_nb; 
}; 
 
int game_events__stack__empty(game_events_env_t * this) { 
  this -> stack_nb = 0; 
  return 0; 
}; 
 
int game_events__stack__push(game_events_env_t * this, const int evt_type) { 
  //dprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " this = %p - this -> stack_nb = %d - evt_type = %d " "\n", __func__, this, this -> stack_nb, evt_type); 
  if ((evt_type         < 0) || (evt_type         >= GAME_EVENTS__COUNT          )) return -1; 
  if ((this -> stack_nb < 0) || (this -> stack_nb >= GAME_EVENTS_ENV__STACK__SIZE)) return -2; 
  const int index = this -> stack_nb; 
  this -> stack_nb++; 
  this -> stack[index] = evt_type; 
  return index; 
}; 
 
int game_events__stack__print_d(const int fd, const game_events_env_t * this) { 
  dprintf(fd, "[game_events_stack having %d]", this -> stack_nb); 
  return 0; 
}; 
 



// *** GAME_EVENTS_PROCESS *** 

static int game_events__process__standard__heros_mort(api_contexte_t * api_contexte); 

int game_events__process(game_events_env_t * this, api_contexte_t * api_contexte) { 
  //messlog(" >>> this = %p - api_contexte = %p" "\n", this, api_contexte); 
  if (this -> stack_nb <= 0) { 
    //messlog(" <<< No events on stack (this -> stack_nb = %d) - leaving " "\n", this -> stack_nb); 
    return 1; 
  }; 
  
  messlog(" --- There are %d events on the stack to process " "\n", this -> stack_nb); 
  for (int i = 0; i < this -> stack_nb; i++) { 
    messlog("\t" "this -> stack[%02d] = (%d)%s" "\n", i, this -> stack[i], game_events__get_cstr(this -> stack[i])); 
  }; 
  
  for (int i = 0; i < this -> stack_nb; i++) { 
    const int evt_type = this -> stack[i]; 
    messlog(" --- Processing this -> stack[%d] = (%d)%s" "\n", i, evt_type, game_events__get_cstr(evt_type)); 
    if (0 == this -> handlers__nb[evt_type]) { 
      messlog("\t" "It does not have any handlers  --  Skipping to next event " "\n"); 
      continue; 
    }; 
    messlog("\t" "It has %d handlers." "\n", (int) this -> handlers__nb[evt_type]); 
    for (int j = 0; j < this -> handlers__nb[evt_type]; j++) { 
      messlog("\t" "\t" "this -> handlers[%s][%d] = (%d)%s" "\n", game_events__get_cstr(evt_type), j, (int) this -> handlers[evt_type][j], game_handlers__get_cstr(this -> handlers[evt_type][j])); 
    }; 
    
    for (int j = 0; j < this -> handlers__nb[evt_type]; j++) { 
      const int handler_type = this -> handlers[evt_type][j]; 
      int arg_index = 0;
      const int       int_argc =                  this -> handlers_arg[evt_type][j][arg_index]; arg_index += sizeof(int8_t); 
      const int    *  int_argv = (const int    *)&this -> handlers_arg[evt_type][j][arg_index]; arg_index +=  int_argc * sizeof(int); 
      const int       ptr_argc =                  this -> handlers_arg[evt_type][j][arg_index]; arg_index += sizeof(int8_t); 
            void * *  ptr_argv = (      void * *)&this -> handlers_arg[evt_type][j][arg_index]; arg_index +=  ptr_argc * sizeof(void *); 
      const int      cptr_argc =                  this -> handlers_arg[evt_type][j][arg_index]; arg_index += sizeof(int8_t); 
      const void * * cptr_argv = (const void * *)&this -> handlers_arg[evt_type][j][arg_index]; arg_index += cptr_argc * sizeof(const void *); 
      assert(arg_index <= GAME_EVENTS_ENV__HANDLER__ARG_SIZE); 
      messlog(" --- int_argc = %d - int_argv = %p - ptr_argc = %d - ptr_argv = %p - cptr_argc = %d - cptr_argv = %p " "\n", int_argc, int_argv, ptr_argc, ptr_argv, cptr_argc, cptr_argv); 
      if (handler_type == GAME_HANDLERS__SCRIPT) { 
#if 1 
	if ((int_argc != 0) || (ptr_argc != 2) || (cptr_argc != 0)) { 
	  messerr(" --- Wrong number of arguments for a SCRIPT handler - expecting: int_argc == 0 - ptr_argc == 2 - cptr_argc == 0 ; got: int_argc = %d - ptr_argc = %d - cptr_argc = %d  --  Skipping to next " "\n", int_argc, ptr_argc, cptr_argc); 
	  continue; 
	}; 
	const char * script_file = ptr_argv[0]; 
	const char * script_name = ptr_argv[1]; 
#else 
	if ((int_argc != 0) || (ptr_argc != 0) || (cptr_argc != 2)) { 
	  messerr(" --- Wrong number of arguments for a SCRIPT handler - expecting: int_argc == 0 - ptr_argc == 0 - cptr_argc == 2 ; got: int_argc = %d - ptr_argc = %d - cptr_argc = %d  --  Skipping to next " "\n", int_argc, ptr_argc, cptr_argc); 
	  continue; 
	}; 
	const char * script_file = cptr_argv[0]; 
	const char * script_name = cptr_argv[1]; 
#endif 
	const int retval = Kernel_Script_Start(/*script_file_name*/script_file, /*script_function_name*/script_name); 
	if (retval < 0) { 
	  messerr(" --- Something got wrong while running a script - returned value = %d  --  Skipping to next handler " "\n", retval); 
	  continue; 
	}; 
	if (retval == 0) { 
	  messlog(" --- The handler returned '0' - Therefore not propagating the event to other handlers --  Skipping to next event " "\n"); 
	  break; 
	}; 
	messlog(" --- The handler returned a positive value (%d) - Therefore propagating the event to the next handler (if any). " "\n", retval); 
	continue; 
      } 
      else if (handler_type == GAME_HANDLERS__CALLBACK) { 
	messerr(" --- // RL: TODO XXX FIXME: GAME_HANDLERS__CALLBACK to be implemented -- Skipping to next handler " "\n"); 
	continue; 
      } 
      else if (handler_type == GAME_HANDLERS__STANDARD__HEROS_MORT) { 
	messlog(" --- GAME_HANDLERS__STANDARD__HEROS_MORT - Running " "\n"); 
	const int retval = game_events__process__standard__heros_mort(api_contexte); 
	if (retval < 0) { 
	  messerr(" --- Something got wrong while running a script - returned value = %d  --  Skipping to next handler " "\n", retval); 
	  continue; 
	}; 
	if (retval == 0) { 
	  messlog(" --- The handler returned '0' - Therefore not propagating the event to other handlers --  Skipping to next event " "\n"); 
	  break; 
	}; 
	messlog(" --- The handler returned a positive value (%d) - Therefore propagating the event to the next handler (if any). " "\n", retval); 
	continue; 
      }; 
      messerr(" --- Unknown handler type: this -> handlers[%s][%d] = (%d)%s  => Skipping to next" "\n", game_events__get_cstr(evt_type), j, handler_type, game_handlers__get_cstr(handler_type)); 
      continue; 
    }; 
    
    messlog(" --- All handlers for the event 'this -> stack[%d] = (%d)%s' were processed  --  Moving forward to next event " "\n", i, evt_type, game_events__get_cstr(evt_type)); 
  }; 
  
  messlog(" --- All events were processed (%d events)  -- Emptying the event stack.  " "\n", this -> stack_nb); 
  
  this -> stack_nb = 0; 
  
  return 0; 
}; 



// *** GAME_EVENTS_PROCESS_STANDARD *** 

static int game_events__process__standard__heros_mort(api_contexte_t * api_contexte) { 
  *(api_contexte -> ModeJeu) = mjHEROS_MORT; 

  CMessageTexte * MessageTexte = *(api_contexte -> MessageTexte_ref); 

  const char msg[] = "Être élu. Tu viens de passer l'arme à gauche. Tu ne pourras pas venger ton père." "\n" "GAME OVER :-("; 
  
  MessageTexte -> SetMsg(MessageTexte, msg); 
  
  //CMusique * Musique = *(api_contexte -> Musique); 
	CMusique_delete(*(api_contexte -> Musique));  
*(api_contexte -> Musique) = CMusique_make("mort.mid"); 
	(*(api_contexte -> Musique)) -> Jouer(*(api_contexte -> Musique)); 

  
  return 0; 
}; 


