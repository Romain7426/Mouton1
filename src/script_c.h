#ifndef SCRIPT_C_H 
#define SCRIPT_C_H 

// *** SCRIPT_C_ENV *** 
 
#ifndef SCRIPT_C_ENV_T 
#define SCRIPT_C_ENV_T 
struct script_c_env_t; 
typedef struct script_c_env_t script_c_env_t; 
#endif /* SCRIPT_C_ENV_T */ 
extern const int script_c_env__sizeof; 
extern script_c_env_t * script_c_env__make    (void); 
extern script_c_env_t * script_c_env__make_r  (script_c_env_t * this); 
extern void             script_c_env__delete  (script_c_env_t * this); 
extern void             script_c_env__delete_r(script_c_env_t * this); 
extern void             script_c_env__print_d(const int fileno, const script_c_env_t * this); 
 
 
// *** SCRIPT_C *** 

// RL: Use for storage, wherein data should be packed. Anywhere else, 'int' is good enough. 
//     That property ensures that a script_c will fit into a 'int_script_c_t'. 
typedef       int8_t          int_script_c_t; 
extern  const int_script_c_t  int_script_c_max; 

extern int_script_c_t script_c__count   (                  const script_c_env_t * this); 
extern const char *   script_c__get_name(                  const script_c_env_t * this, const int script_c); 
extern void           script_c__print_d (const int fileno, const script_c_env_t * this, const int script_c); 
extern int_script_c_t script_c__lookup(                    const script_c_env_t * this, const char * script_c_name); 

extern int            script_c__set     (      script_c_env_t * this, const int target_script_c); 
extern int_script_c_t script_c__get     (const script_c_env_t * this); 
extern int            script_c__busy_huh(const script_c_env_t * this); 
extern int            script_c__run     (      script_c_env_t * this, api_contexte_t * api_contexte); // RL: This function will yield back to the kernel if run in a cooperative-thread - otherwise, it can't and so it won't. 

// RL: The purpose of the temp-data space is to transfer data between the caller and the callee 
//     (as no argument can be passed to the callee, and no return value can be passed). 
extern int            script_c__data_temp__get_size (const script_c_env_t * this); 
extern int            script_c__data_temp__get_used (const script_c_env_t * this); 
extern int            script_c__data_temp__get_avail(const script_c_env_t * this); 
extern int            script_c__data_temp__reset    (      script_c_env_t * this); 
extern int            script_c__data_temp__alloc    (      script_c_env_t * this, const int data_sizeof); 
extern int            script_c__data_temp__push     (      script_c_env_t * this, const int data_sizeof, const char * data_value); 
extern int            script_c__data_temp__write    (      script_c_env_t * this, const int data_offset, const int data_sizeof, const char * data_value); 
extern int            script_c__data_temp__read     (const script_c_env_t * this, const int data_offset, const int data_sizeof, char * data_value_allocated); 
extern int            script_c__data_temp__read_top (const script_c_env_t * this, const int data_sizeof, char * data_value_allocated); 
extern int            script_c__data_temp__drop     (      script_c_env_t * this, const int data_sizeof); 
extern const char *   script_c__data_temp__get_ptr  (const script_c_env_t * this, const int data_offset); 
extern       char *   script_c__data_temp__get_ptr_writable(script_c_env_t * this, const int data_offset); 


// *** SCRIPT_C_LIB1 *** 

extern int script_c__lib1__fill(script_c_env_t * this); 








#endif /* SCRIPT_C_H */
