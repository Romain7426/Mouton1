#ifndef SUPERVISOR_H 
#define SUPERVISOR_H 
 
// RL: The "supervisor mode" is an intermediate mode between the user mode (script 
//     engine & game engine) and the kernel mode. (Please note that there is no kernel 
//     mode per se.) 
// RL: The point of that "supervisor mode" is to provide some kind of error recovery to 
//     the user modes. It does not run in parallel of the user modes, but in series: 
//     it's one or the other. 
 

// *** SUPERVISOR_MODE_TYPE *** 
 
enum { 
  SUPERVISOR_MODE__IDLE, 
  SUPERVISOR_MODE__MESSAGE, 
  SUPERVISOR_MODE__MENU, 
  SUPERVISOR_MODE__COUNT 
}; 
// RL: Use for storage, wherein data should be packed. Anywhere else, 'int' is good enough. 
//     That property ensures that a supervisor_mode_type will fit into a 'int_supervisor_mode_type_t'. 
typedef       int8_t                      int_supervisor_mode_type_t; 
extern  const int_supervisor_mode_type_t  int_supervisor_mode_type_max; 
extern  const int_supervisor_mode_type_t  supervisor_mode__count; 
extern  const char * supervisor_mode__type_get_cstr(const int supervisor_mode_type); 
#define supervisor_mode__type_cstr supervisor_mode__type_get_cstr 
 
 
// *** SUPERVISOR_ENV *** 
 
#ifndef SUPERVISOR_ENV_T 
#define SUPERVISOR_ENV_T 
struct supervisor_env_t; 
typedef struct supervisor_env_t supervisor_env_t; 
#endif /* SUPERVISOR_ENV_T */ 
extern const int supervisor_env__sizeof; 
extern supervisor_env_t * supervisor_env__make    (void); 
extern supervisor_env_t * supervisor_env__make_r  (supervisor_env_t * this); 
extern void                    supervisor_env__delete  (supervisor_env_t * this); 
extern void                    supervisor_env__delete_r(supervisor_env_t * this); 
 
 
// *** SUPERVISOR_MODE *** 
 
extern int supervisor__loop(supervisor_env_t * this); 

extern int supervisor__message(supervisor_env_t * this, const char * message); 

extern int supervisor__menu(supervisor_env_t * this, int * where_to_write_the_result_ref, const char * message, const int choix_nb, const char * choix_array[]); 





#endif /* SUPERVISOR_H */ 

