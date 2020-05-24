#ifndef COOPERATIVE_THREAD_H 
#define COOPERATIVE_THREAD_H 

// *** COOPERATIVE_THREAD_ENV *** 
 
#ifndef COOPERATIVE_THREAD_ENV_T 
#define COOPERATIVE_THREAD_ENV_T 
struct cooperative_thread_env_t; 
typedef struct cooperative_thread_env_t cooperative_thread_env_t; 
#endif /* COOPERATIVE_THREAD_ENV_T */ 
extern const int cooperative_thread_env__sizeof; 
extern cooperative_thread_env_t * cooperative_thread_env__make    (void); 
extern cooperative_thread_env_t * cooperative_thread_env__make_r  (cooperative_thread_env_t * this); 
extern void                       cooperative_thread_env__delete  (cooperative_thread_env_t * this); 
extern void                       cooperative_thread_env__delete_r(cooperative_thread_env_t * this); 
 
extern void                       cooperative_thread_env__print_d(const int fileno, const cooperative_thread_env_t * this); 
 
 
// *** COOPERATIVE_THREAD *** 
 
// RL: Use for storage, wherein data should be packed. Anywhere else, 'int' is good enough. 
//     That property ensures that a cooperative_thread will fit into a 'int_cooperative_thread_t'. 
typedef       int8_t                    int_cooperative_thread_t; 
extern  const int_cooperative_thread_t  int_cooperative_thread_max; 

extern int_cooperative_thread_t cooperative_thread__count  (                  const cooperative_thread_env_t * this); 
extern int_cooperative_thread_t cooperative_thread__push   (                        cooperative_thread_env_t * this); // RL: This function is not 'preemptive/concurrent-thread' safe. 
extern void                     cooperative_thread__print_d(const int fileno, const cooperative_thread_env_t * this, const int cooperative_thread); 

extern const void *             cooperative_thread__get_stack_addr(           const cooperative_thread_env_t * this, const int cooperative_thread); 

extern int                      cooperative_thread__kernel_switch_to_thread(cooperative_thread_env_t * this, const int next_cooperative_thread); 
extern int                      cooperative_thread__thread_yield_to_kernel (cooperative_thread_env_t * this); 
 
extern int_cooperative_thread_t cooperative_thread__get_current(const cooperative_thread_env_t * this); 
#if 0 
extern int                      cooperative_thread__switch_flat(cooperative_thread_env_t * this, const int next_cooperative_thread); 
extern int                      cooperative_thread__switch_recursive(cooperative_thread_env_t * this, const int next_cooperative_thread); 
extern int                      cooperative_thread__switch_recursive_back(cooperative_thread_env_t * this); 
#endif 

extern int                      cooperative_thread__set_fun (cooperative_thread_env_t * this, const int target_cooperative_thread, void (*f)(void)); 
extern void                  (* cooperative_thread__get_fun (const cooperative_thread_env_t * this, const int target_cooperative_thread))(void); 
extern int                      cooperative_thread__busy_huh(const cooperative_thread_env_t * this, const int target_cooperative_thread); 

// RL: The thread global data space is available all the time to the thread. 
extern int                      cooperative_thread__alloc_data__global  (cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_sizeof); 
extern int                      cooperative_thread__write_data__global  (cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_offset, const int data_sizeof, const char * data_value); 
extern int                      cooperative_thread__read_data__global   (const cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_offset, const int data_sizeof, char * data_value_allocated); 
extern const char *             cooperative_thread__get_ptr_data__global(const cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_offset); 
extern       char *             cooperative_thread__get_ptr_data__global_writable(cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_offset); 

// RL: The thread temp data space will be reset at the next context switch. 
//     Its purpose is to transfer data between the caller and the callee 
//     (as no argument can be passed to the callee, and no return value can be passed). 
extern int                      cooperative_thread__data_temp__print_d  (const int fileno, const cooperative_thread_env_t * this, const int target_cooperative_thread); 
extern int                      cooperative_thread__data_temp__get_size (const cooperative_thread_env_t * this, const int target_cooperative_thread); 
extern int                      cooperative_thread__data_temp__get_used (const cooperative_thread_env_t * this, const int target_cooperative_thread); 
extern int                      cooperative_thread__data_temp__get_avail(const cooperative_thread_env_t * this, const int target_cooperative_thread); 
extern int                      cooperative_thread__reset_data__temp  (cooperative_thread_env_t * this, const int target_cooperative_thread); 
extern int                      cooperative_thread__alloc_data__temp  (cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_sizeof); 
extern int                      cooperative_thread__write_data__temp  (cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_offset, const int data_sizeof, const char * data_value); 
extern int                      cooperative_thread__data_temp__push   (      cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_sizeof, const char * data_value); 
extern int                      cooperative_thread__read_data__temp   (const cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_offset, const int data_sizeof, char * data_value_allocated); 
extern int                      cooperative_thread__data_temp__read_top(const cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_sizeof, char * data_value_allocated); 
extern int                      cooperative_thread__data_temp__read_top_and_drop(cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_sizeof, char * data_value_allocated); 
extern const char *             cooperative_thread__get_ptr_data__temp(const cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_offset); 
extern       char *             cooperative_thread__get_ptr_data__temp_writable(cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_offset); 



#endif /* COOPERATIVE_THREAD_H */

