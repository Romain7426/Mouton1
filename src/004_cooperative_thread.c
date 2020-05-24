#include "global.h" 
#include "004_cooperative_thread.h" 

// RL: *** COOPERATIVE THREADS ENV *** 
// RL: Up to 'COOPERATIVE_THREAD__SIZE' cooperative threads can be made. 
// 
enum { COOPERATIVE_THREAD__SIZE                    = INT8_MAX  - 1 }; // RL: So that 'INT8_MAX' is an invalid value. 
enum { COOPERATIVE_THREAD__SYSTEM_STACK__SIZE      = (1 << 21) }; //INT16_MAX - 1 }; // RL: To read 3ds files, I need 850k. // RL: 'SIGSTKSZ' is 28.0k on OpenBSD. 'MINSIGSTKSZ' is 12.0k on OpenBSD. 
enum { COOPERATIVE_THREAD__GLOBAL_THREAD_DATA_SIZE = MIN(INT16_MAX - 1,(COOPERATIVE_THREAD__SYSTEM_STACK__SIZE >> 1)) }; //INT16_MAX - 1 }; // RL: So that 'INT16_MAX' is an invalid value. 
enum { COOPERATIVE_THREAD__TEMP_THREAD_DATA_SIZE   = INT8_MAX  - 1 }; // RL: So that 'INT8_MAX' is an invalid value. 

enum { COOPERATIVE_THREAD__KERNEL_ID = COOPERATIVE_THREAD__SIZE }; 

struct cooperative_thread_env_t { 
  int8_t                   malloced_huh; 
  int_cooperative_thread_t nb; 
#if 0 
  int_cooperative_thread_t active; // RL: Useless 
#endif 
  void *                   system_stack  [COOPERATIVE_THREAD__SIZE]; // RL: Will be malloc'ed. 
  sigjmp_buf               sjlj_env      [COOPERATIVE_THREAD__SIZE]; // RL: The switching context. 
  void                  (* fun           [COOPERATIVE_THREAD__SIZE])(void); // RL: The function currently being run (the root one, as it could be then arbitrarily nested). 
  char                     data_temp     [COOPERATIVE_THREAD__SIZE][COOPERATIVE_THREAD__TEMP_THREAD_DATA_SIZE]; // RL: Local temp data stack. 
  int8_t                   data_temp_nb  [COOPERATIVE_THREAD__SIZE]; 
  char                   * data_global   [COOPERATIVE_THREAD__SIZE]; // RL: Thread global data stack. 
  int16_t                  data_global_nb[COOPERATIVE_THREAD__SIZE]; 
  sigjmp_buf               kernel_sjlj_env; 
}; 
enum {    cooperative_thread_env__sizeof__compiler_const = sizeof(struct cooperative_thread_env_t) }; 
const int cooperative_thread_env__sizeof                 = sizeof(struct cooperative_thread_env_t); 

static void assert_compile__check_type_size_dksauhgsaky837643iduy(void) {
  ASSERT_COMPILE(COOPERATIVE_THREAD__SIZE                    <  INT8_MAX ); // RL: So that 'INT8_MAX' is an invalid value. 
  ASSERT_COMPILE(COOPERATIVE_THREAD__TEMP_THREAD_DATA_SIZE   <  INT8_MAX ); // RL: So that 'INT8_MAX' is an invalid value. 
  ASSERT_COMPILE(COOPERATIVE_THREAD__GLOBAL_THREAD_DATA_SIZE <  INT16_MAX); // RL: So that 'INT16_MAX' is an invalid value. 
  ASSERT_COMPILE(COOPERATIVE_THREAD__GLOBAL_THREAD_DATA_SIZE <= (COOPERATIVE_THREAD__SYSTEM_STACK__SIZE >> 1)); 
  ASSERT_COMPILE(COOPERATIVE_THREAD__SYSTEM_STACK__SIZE      >= SIGSTKSZ); 
  cooperative_thread_env_t * this = NULL; 
  ASSERT_COMPILE(sizeof(this -> nb            ) >= 1); 
  ASSERT_COMPILE(sizeof(this -> data_temp_nb  ) >= 1); 
  ASSERT_COMPILE(sizeof(this -> data_global_nb) >= 2); 

  //ASSERT_COMPILE(cooperative_thread_env__sizeof__compiler_const <= 32144); // RL: 32144 (31,4k) was the first size of that structure. 
}; 

cooperative_thread_env_t * cooperative_thread_env__make_r(cooperative_thread_env_t * this) { 
  bzero(this, sizeof(*this)); 
  // RL: There's no thread saved to the kernel. 
  //     No thread can't switch to the kernel thread. 
  //     A thread can only yield to the kernel. 
  return this; 
}; 

cooperative_thread_env_t * cooperative_thread_env__make(void) { 
  cooperative_thread_env_t * this; 
  this = (cooperative_thread_env_t *) malloc(sizeof(*this)); 
  cooperative_thread_env__make_r(this); 
  this -> malloced_huh = true; 
  return this; 
}; 

void cooperative_thread_env__delete_r(cooperative_thread_env_t * this) { 
  bzero(this, sizeof(*this)); 
}; 
 
void cooperative_thread_env__delete(cooperative_thread_env_t * this) { 
  const int malloced_huh = this -> malloced_huh; 
  cooperative_thread_env__delete_r(this); 
  if (malloced_huh) free(this); 
}; 
 
void cooperative_thread_env__print_d(const int fileno, const cooperative_thread_env_t * this) { 
  dprintf(fileno, "cooperative_thread_env_t: this = %p - sizeof = %d\n", this, (int)sizeof(this)); 
}; 




// *** COOPERATIVE_THREAD *** 
enum { int_cooperative_thread_max__compiler_const = INT8_MAX }; 
const int_cooperative_thread_t int_cooperative_thread_max = int_cooperative_thread_max__compiler_const; 

// RL: This variable is not 'preemptive/concurrent-thread' safe: 
//     we do need a global variable to hold data, as no data can be given to the 'raise' function. 
//static sigjmp_buf * cooperative_thread__sjlj_being_created = NULL; 
static cooperative_thread_env_t * cooperative_thread__push__this  = NULL; 
static int_cooperative_thread_t   cooperative_thread__push__index = int_cooperative_thread_max__compiler_const; 


int_cooperative_thread_t cooperative_thread__count(const cooperative_thread_env_t * this) { 
  return this -> nb; 
}; 

void cooperative_thread__print_d(const int fileno, const cooperative_thread_env_t * this, const int cooperative_thread) { 
  dprintf(fileno, "cooperative_thread: %d\n", (int) cooperative_thread); 
}; 

const void * cooperative_thread__get_stack_addr(const cooperative_thread_env_t * this, const int cooperative_thread) { 
  return this -> system_stack[cooperative_thread]; 
}; 


static void cooperative_thread__handler_to_capture_sigaltstack(const int /* ignored: always SIGUSR1 */signal_number); 

// RL: This function is not 'preemptive/concurrent-thread' safe: 
//     we do need a global variable to hold data, as no data can be given to the 'raise' function. 
int_cooperative_thread_t cooperative_thread__push(cooperative_thread_env_t * this) { 
  if (this -> nb >= COOPERATIVE_THREAD__SIZE) { return INT8_MIN; }; 
  const int index = this -> nb; 
  this -> nb++; 
  
  //cooperative_thread__sjlj_being_created = this -> sjlj_env + index; 
  cooperative_thread__push__this  = this; 
  cooperative_thread__push__index = index; 

  
  int alright_huh = false; 
  do { 
    struct sigaction new_handler;
    struct sigaction old_handler;

    stack_t new_stack;
    stack_t old_stack;

    new_stack.ss_flags = 0; 
    new_stack.ss_size  = COOPERATIVE_THREAD__SYSTEM_STACK__SIZE; 
#ifdef MAP_STACK  
    // RL: I need the 'MAP_STACK' attribute: 
    //       dmesg:  /bsd: trap [mouton1.exe]57914/314933 type 6: sp 793b1bfe560 not inside 793b1bff000-793b1c05000 
    //     NB: The seg-fault won't happen until a libC/Kernel function is called (like 'write(2)'; possibly, a rather large allocation on the stack beforehand could be needed). 
    //         Meaning that if no libC/Kernel functions are called while using that malloc-stack, no seg-fault gonna happen. 
    new_stack.ss_sp    = mmap(NULL, new_stack.ss_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE | MAP_STACK, -1, 0); 
#elif 1 
    new_stack.ss_sp    = malloc(new_stack.ss_size); 
#else 
    //new_stack.ss_sp    = malloc(new_stack.ss_size); 
    new_stack.ss_sp    = malloc(new_stack.ss_size << 12); 
#endif 
    if (NULL == new_stack.ss_sp) { break; }; 
    this -> system_stack[index] = new_stack.ss_sp; 
    if (0 != sigaltstack(&new_stack, &old_stack)) { break; }; 
    new_handler.sa_handler = cooperative_thread__handler_to_capture_sigaltstack; 
    new_handler.sa_flags   = SA_ONSTACK; 
    sigemptyset(&new_handler.sa_mask); 
    const int sigaction_retval = sigaction(SIGUSR1, &new_handler, &old_handler); 
    if (0/*success*/ == sigaction_retval) { 
      // RL: To make that code runs in GDB, we have to tell GDB: "handle SIGUSR1 nostop" (and possibly "handle SIGUSR1 noprint") 
        if (0/*success*/ == raise(SIGUSR1)) { 
	  // RL: We were in the handler, and we came back. 
	  alright_huh = true; 
        }; 
        sigaction(SIGUSR1, &old_handler, NULL); 
    };
    sigaltstack(&old_stack, NULL); 
  } while (false); 
  
  //cooperative_thread__sjlj_being_created = NULL; 
  cooperative_thread__push__this  = NULL; 
  cooperative_thread__push__index = int_cooperative_thread_max__compiler_const; 
  
  if (!alright_huh) { 
    this -> nb --; 
    return INT8_MIN + 1; 
  }; 
  
  return index; 
}; 
 

static void cooperative_thread__handler_to_capture_sigaltstack(const int /* ignored: always SIGUSR1 */signal_number) { 
  // RL: 'raise' was just called. 
  //     The operating system called this handler, on the provided stack. 
  //     So, right now, we are on the new stack. 
  // RL: We will save this stack using 'sigsetjmp'. 
  // RL: But first, we need to grab our parameters. 
  cooperative_thread_env_t * this; 
  this = cooperative_thread__push__this; 
  const int index = cooperative_thread__push__index; 
  do { // RL: Beware, 'do' drops locally allocated variables. 
    // RL: Second, now we need to allocate the global data to the thread. 
    char thread_global_data[COOPERATIVE_THREAD__GLOBAL_THREAD_DATA_SIZE]; 
    this -> data_global[index] = thread_global_data; 
    // RL: Third, we need a variable where we will hold the function that will be called. 
    void (* f)(void) = NULL; 
    do { // RL: Beware, 'do' drops locally allocated variables. 
      // RL: Alright. Now we can set sjlj. 
      // RL: As a reminder, 'sigsetjmp' returns '0' on the first call (when it saves the environment), 
      //     and a non-zero value when it comes back from a restored environment. 
      if (0 == sigsetjmp(this -> sjlj_env[index], /*savemask?*/0)) { 
	// RL: 'sigsetjmp' returned '0', so this is not a restored environment - we just saved one. 
	//     From now on, when the environment will be restored, we will be in the second branch of the 'if'. 
	// RL: Ok, so we achieved what we wanted. Now we will return to 'raise'. 
	return; // RL: Return to where 'raise' was called. 
      }; 
      // RL: 'sigsetjmp' returned non-'0', so this is a restored environment (not a signal handling environment anymore). 
      // RL: Given that we are here, it means that the is the first call back to that context. 
      // RL: NB: We cannot 'return' anymore: on the stack was the IP & SP addresses of the 'raise' context (which does not 
      //         exist anymore), and, worse, both were droped when the first 'return' happened. 
      //         So this function cannot be returned. 
      //         It must be switched or exited or aborted or looped. 
      for (;;) { // RL: Beware, 'for' drops locally allocated variables. 
#if 1 
	f = this -> fun[index]; 
	if (f != NULL) { 
	  f(); 
	}; 
	this -> fun[index] = NULL; 
	// RL: TODO XXX FIXME 
	// yield to kernel 
	cooperative_thread__thread_yield_to_kernel(this); 
#else 
	const int caller_instance = cooperative_thread__caller_stack__top(); 
	void (* fun)(void) = cooperative_thread__sjlj_being_started; 
	fun(); 
	//dputs_array(stderr__fileno, "BACK\n"); 
	cooperative_thread__caller_stack__drop(); 
	cooperative_thread__switch(caller_instance); 
#endif 
      }; 
      // RL: This should never be reached. 
      abort(); 
      } while (false); 
    // RL: This should never be reached. 
    abort(); 
  } while (false); 
  // RL: This should never be reached. 
  abort(); 
  
  // RL: As above said, the calling context of that function (the 'raise' context) is long dead. 
  //     So this function is unable to return. It must switch, or yield, or exit, or abort. 
}; 




int_cooperative_thread_t cooperative_thread__get_current(const cooperative_thread_env_t * this) { 
  int a; 
  for (int i = 0; i < this -> nb; i++) { 
    if ((void *)&a < this -> system_stack[i]) { continue; }; 
    if ((char *)&a < (char *)this -> system_stack[i] + COOPERATIVE_THREAD__SYSTEM_STACK__SIZE) { return i; }; 
  }; 
  return COOPERATIVE_THREAD__KERNEL_ID; 
}; 


int cooperative_thread__switch_flat(cooperative_thread_env_t * this, const int next_cooperative_thread) { 
  if (next_cooperative_thread < 0) { return -1; }; 
  if (next_cooperative_thread >= this -> nb) { return -2; }; 
  const int current = cooperative_thread__get_current(this); 
  if (current == next_cooperative_thread) { return 1; }; 
  
  // RL: Before switching, we need to save the current context (the whole point of the current work!). 
  if (0 == sigsetjmp(this -> sjlj_env[current], /*savemask?*/0)) { 
    // RL: 'sigsetjmp' returned '0'. So we haven't switched yet. 
    // RL: Let's switch. 
    siglongjmp(this -> sjlj_env[next_cooperative_thread], /*any non-0 value*/1); 
    // RL: It's a goto, so we should never not come back. 
    abort(); 
  }; 
  // RL: 'sigsetjmp' returned non-'0', so this is a context restoration: we already switched, they did their job, and we're coming back. 
  return 0; 
}; 


int cooperative_thread__kernel_switch_to_thread(cooperative_thread_env_t * this, const int next_cooperative_thread) { 
  if (next_cooperative_thread < 0) { return -1; }; 
  if (next_cooperative_thread >= this -> nb) { return -2; }; 
  const int current = cooperative_thread__get_current(this); 
  if (current != COOPERATIVE_THREAD__KERNEL_ID) { return -3; }; 
  
  
  // RL: Before switching, we need to save the current context (the whole point of the current work!). 
  if (0 == sigsetjmp(this -> kernel_sjlj_env, /*savemask?*/0)) { 
    // RL: 'sigsetjmp' returned '0'. So we haven't switched yet. 
    // RL: Let's switch. 
    siglongjmp(this -> sjlj_env[next_cooperative_thread], /*any non-0 value*/1); 
    // RL: It's a goto, so we should never not come back. 
    abort(); 
  }; 
  // RL: 'sigsetjmp' returned non-'0', so this is a context restoration: we already switched, they did their job, and we're coming back. 
  return 0; 
}; 

int cooperative_thread__thread_yield_to_kernel(cooperative_thread_env_t * this) { 
  const int current = cooperative_thread__get_current(this); 
  if (current == COOPERATIVE_THREAD__KERNEL_ID) { return 1; }; 
  
  // RL: Before switching, we need to save the current context (the whole point of the current work!). 
  if (0 == sigsetjmp(this -> sjlj_env[current], /*savemask?*/0)) { 
    // RL: 'sigsetjmp' returned '0'. So we haven't switched yet. 
    // RL: Let's switch. 
    siglongjmp(this -> kernel_sjlj_env, /*any non-0 value*/1); 
    // RL: It's a goto, so we should never not come back. 
    abort(); 
  }; 
  // RL: 'sigsetjmp' returned non-'0', so this is a context restoration: we already switched, they did their job, and we're coming back. 
  return 0; 
}; 

int cooperative_thread__set_fun(cooperative_thread_env_t * this, const int target_cooperative_thread, void (*f)(void)) { 
  if (this -> fun[target_cooperative_thread] != NULL) return -1; 
  this -> fun[target_cooperative_thread] = f; 
  return 0; 
}; 

void (* cooperative_thread__get_fun(const cooperative_thread_env_t * this, const int target_cooperative_thread))(void) { 
  return this -> fun[target_cooperative_thread]; 
}; 

int cooperative_thread__busy_huh(const cooperative_thread_env_t * this, const int target_cooperative_thread) { 
  return this -> fun[target_cooperative_thread] != NULL; 
}; 

int cooperative_thread__alloc_data__global(cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_sizeof) { 
  const int offset    = this -> data_global_nb[target_cooperative_thread]; 
  const int available = COOPERATIVE_THREAD__GLOBAL_THREAD_DATA_SIZE - offset; 
  if (data_sizeof > available) return -1;  
  this -> data_global_nb[target_cooperative_thread] += data_sizeof; 
  return offset; 
};
 
int cooperative_thread__write_data__global(cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_offset, const int data_sizeof, const char * data_value) { 
  bcopy(data_value, this -> data_global[target_cooperative_thread] + data_offset, data_sizeof); 
  return 0; 
}; 

int cooperative_thread__read_data__global(const cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_offset, const int data_sizeof, char * data_value_allocated) { 
  bcopy(this -> data_global[target_cooperative_thread] + data_offset, data_value_allocated, data_sizeof); 
  return 0; 
}; 

const char * cooperative_thread__get_ptr_data__global(const cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_offset) { 
  return this -> data_global[target_cooperative_thread] + data_offset; 
}; 
 
char * cooperative_thread__get_ptr_data__global_writable(cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_offset) { 
  return this -> data_global[target_cooperative_thread] + data_offset; 
}; 







int cooperative_thread__data_temp__get_size(const cooperative_thread_env_t * this, const int target_cooperative_thread) { 
  return COOPERATIVE_THREAD__TEMP_THREAD_DATA_SIZE; 
}; 

int cooperative_thread__data_temp__get_used(const cooperative_thread_env_t * this, const int target_cooperative_thread) { 
  return this -> data_temp_nb[target_cooperative_thread]; 
}; 

int cooperative_thread__data_temp__get_avail(const cooperative_thread_env_t * this, const int target_cooperative_thread) { 
  return COOPERATIVE_THREAD__TEMP_THREAD_DATA_SIZE - this -> data_temp_nb[target_cooperative_thread]; 
}; 

int cooperative_thread__reset_data__temp(cooperative_thread_env_t * this, const int target_cooperative_thread) { 
  this -> data_temp_nb[target_cooperative_thread] = 0; 
  return 0; 
}; 

int cooperative_thread__data_temp__print_d(const int fileno, const cooperative_thread_env_t * this, const int target_cooperative_thread) { 
  dprintf(fileno, "[%d] = { ", this -> data_temp_nb[target_cooperative_thread]); 
  for (int i = 0; i < this -> data_temp_nb[target_cooperative_thread]; i++) { 
    dprintf(fileno, "%hhx ,  ", (char) this -> data_temp[target_cooperative_thread][i]); 
  }; 
  dprintf(fileno, " }"); 
  return 0; 
}; 

int cooperative_thread__alloc_data__temp(cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_sizeof) { 
  const int offset    = this -> data_temp_nb[target_cooperative_thread]; 
  const int available = COOPERATIVE_THREAD__TEMP_THREAD_DATA_SIZE - offset; 
  if (data_sizeof > available) return -1;  
  this -> data_temp_nb[target_cooperative_thread] += data_sizeof; 
  return offset; 
}; 

int cooperative_thread__write_data__temp(cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_offset, const int data_sizeof, const char * data_value) { 
  bcopy(data_value, this -> data_temp[target_cooperative_thread] + data_offset, data_sizeof); 
  return data_offset; 
}; 

int cooperative_thread__data_temp__push(cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_sizeof, const char * data_value) { 
  const int data_offset = cooperative_thread__alloc_data__temp(this, target_cooperative_thread, data_sizeof); 
  if (data_offset < 0) return data_offset; 
  const int retval = cooperative_thread__write_data__temp(this, target_cooperative_thread, data_offset, data_sizeof, data_value); 
  return retval; 
}; 

int cooperative_thread__read_data__temp(const cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_offset, const int data_sizeof, char * data_value_allocated) { 
  if (data_offset < 0) { return -1; }; 
  if (data_offset + data_sizeof > this -> data_temp_nb[target_cooperative_thread]) { return -2; }; 
  bcopy(this -> data_temp[target_cooperative_thread] + data_offset, data_value_allocated, data_sizeof); 
  return 0; 
}; 

int cooperative_thread__data_temp__read_top(const cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_sizeof, char * data_value_allocated) { 
  const int data_offset = this -> data_temp_nb[target_cooperative_thread] - data_sizeof; 
  if (data_offset < 0) { return -1; }; 
  bcopy(this -> data_temp[target_cooperative_thread] + data_offset, data_value_allocated, data_sizeof); 
  return data_offset; 
}; 

int cooperative_thread__data_temp__read_top_and_drop(cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_sizeof, char * data_value_allocated) { 
  const int data_offset = this -> data_temp_nb[target_cooperative_thread] - data_sizeof; 
  if (data_offset < 0) { return -1; }; 
  bcopy(this -> data_temp[target_cooperative_thread] + data_offset, data_value_allocated, data_sizeof); 
  this -> data_temp_nb[target_cooperative_thread] -= data_sizeof; 
  return data_offset;   
}; 




const char * cooperative_thread__get_ptr_data__temp(const cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_offset) { 
  return this -> data_temp[target_cooperative_thread] + data_offset; 
}; 

char * cooperative_thread__get_ptr_data__temp_writable(cooperative_thread_env_t * this, const int target_cooperative_thread, const int data_offset) { 
  return this -> data_temp[target_cooperative_thread] + data_offset; 
}; 




