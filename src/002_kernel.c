#include "global.h"
#include "002_kernel.h"
#include "son.h"
#include "004_cooperative_thread.h" 
#include "005_supervisor.h"
#include "010_game.h"
#include "script.h"
#include "script_c.h"
  
// RL: We have two main sub-systems: 
//      - The Game Engine 
//      - The Script Engine 
// 
//     Both of them are an automaton. 
//     There are run in parallel by the kernel. 
//     Technically speaking, we do not need to implement co-routines/fibers (non-concurrent threads) 
//     as we have full control over each sub-system, and we can run each of them step-by-step. 
//     So this kernel is a regular scheduler: it makes each system run one step at each loop. 
//     - 
//     Also, these two sub-systems are not actually fully concurrent: when one runs, the other one should 
//     not need to run. However, the script may need some data from the game, 
//     and the game may need data from the script. 
//     As such, sequential threads are needed, and not parallel/concurrent threads. 
//     
//     The kernel is also dealing with the video & audio & keyboards & timer & other stuffs. 
//  

static bool sdl__init(void); 
static void sdl__process_events(void); 
static void sdl__dispose(void); 
static void opengl_setup(const int width, const int height);
static void opengl__configure(const int width, const int height); 
static void opengl__stuffs(void); 
static SDL_Surface * SDL_Screen; 

static bool isrunning = true; 

// RL: On the long run, should become a local variable and not a global variable. 
extern api_contexte_t api_contexte; //[1]; // RL: Used in apiscript.c 
api_contexte_t api_contexte = {}; 
//static api_contexte_t api_contexte[1]; 

static int supervisor_mode_huh = false; 
static supervisor_env_t * supervisor_env = NULL; 

static cooperative_thread_env_t * cooperative_thread_env = NULL; 
static int cooperative_thread__opengl         = -1; 
static int cooperative_thread__supervisor     = -1; 
static int cooperative_thread__game_primary   = -1; 
static int cooperative_thread__game_secondary = -1; // RL: When the primary game thread is busy waiting for a script answer, but we still want to display something at the screen. 
static int cooperative_thread__script__control_system__automaton  = -1; 
static int cooperative_thread__script__processing_system__c       = -1; 
static int cooperative_thread__script__processing_system__pscript = -1; 
static int8_t Kernel_Script_Modal = -1; 

//static script_c_env_t script_c_env[1]; 
//static script_c_env_t * script_c_env; 


// *** EXTERNAL EVENTS *** 
//  > Ctrl-C 
//  > WM_Quit 
//  ... 
void sdl__process_events(void) { 
  SDL_Event event; 
  
  while (SDL_PollEvent(&event)) { 
    switch (event.type) { 
#if 0 
    case SDL_KEYDOWN: 
#if 0 
      // RL: Trop bourrin. 
      if (event.key.keysym.sym == SDLK_ESCAPE) //echap -> on quitte 
	isrunning = 0; 
#endif 
	  
      //KeyBoard[event.key.keysym.sym] = 1;
      break;
      
    case SDL_KEYUP:
      //KeyBoard[event.key.keysym.sym] = 0;
      break;
      
    case SDL_MOUSEMOTION:
#if 0 
      Mouse.dx = event.motion.xrel;
      Mouse.dy = event.motion.yrel;
      Mouse.x = event.motion.x;
      Mouse.y = event.motion.y;
#endif 
      break;
      
#endif 
      
    case SDL_QUIT: // RL: Handle quit requests (like Ctrl-c, or window-manager request).
      isrunning = 0;
      break;
      
    default: {}
    };
  };
};






// *** COOPERATIVE THREADS *** 
// RL: There will be four threads (maybe five). 
//     Please note that, here, threads are not concurrent/preemptive, but cooperative. 
//     Meaning that we do not have to deal with any concurrent write to the same variable - can't happen - only one thread run at a time. 
//     (Other names for "cooperative threafs": "fibres", "subroutines", "coroutines".) 
// RL: In preemptive/concurrent threading, the kernel scheduler decides when to give processing time to one thread and when to take one thread off the processor. 
//     Threads can't decide anything - the kernel scheduler decides. 
// RL: In cooperative threading, threads decide when to yield to the kernel schedule. Thus, a non-cooperative thread could 
//     not yield and keep all the processing for itself. This point is not that important (it's a design feature), but the issue 
//     is that if a thread is in an infinite loop: that's the Turing-Machine Termination Problem - the kernel scheduler 
//     can't decide to stop it - it cannot know whether it gonna stop or not. 
// RL: That being said, current situation is half-way: according to the design (one big loop), every sub-engine must yield to 
//     the kernel at every pass. In facts, it's mostly transparent. 
// RL: If it's transparent and cooperative, one could wonder whether it's actually useful or not? 
//     Good question. In deed, it is. To understand, one has to think that it's more a local stack issue. 
//     In cooperative threading, the only thing that changes between threads is the local stack (& IPC, of course). 
//     So, it allows to escape a context, without destroying it, but keeping it safe, doing some kernel stuffs (or others), 
//     and then coming back. So the yielding is actually implemented in the kernel call (explaining why it's transparent). 
//     If one does not want to use cooperative threading, then it has to somehow save the whole context, the current instruction, 
//     and then being able to come back. (Especially, the current instruction is implemented using ugly nested switchs.) 
//     Cooperative threading is also absolutely necessary for scripting: the scripting language must be able to yield to 
//     the scripted environment, while keeping the its current environment. 
// RL: I think that's it. 
// RL: One more thing: cooperative threads are faster to switch context than preemptive/concurrent threads. 
// RL: --- IMPLEMENTATION --- 
// RL: Ok then, how do we implement that interesting feature? 
//     Yes, it isn't a native C feature, nor an obvious libC feature. 
//     First, there's a way to switch from stack to stack: 'longjmp'. 
//     Second, there's a not-obvious way in the libC to generate a second stack: 
//     before calling 'setjmp', one has to call the libC function 'sigaltstack'. 
//     What is that function and what is its purpose? 
//     It handles the issue of a STACKOVERFLOW signal: by definition, such a signal 
//     cannot be handled on the current stack - a dedicated stack is therefore needed. 
//     This is the purpose of 'sigaltstack': it tells the underlying operating system 
//     to run one signal handler on a specific stack. 
//     In order to save that interesting new stack, one does: sigaltstack+sigaction+raise (then drop sigaction, drop sigaltstack). 
//     'raise' then calls the handler, and our well crafted handler does not nothing but saving the current context using 'setjmp'. 
//     And we're done! 
// RL: NB: There are other implementations. This one is standard and works on any POSIX-compatible system. And is not slow. 
//     If you need a very performant implementation (very quick task switching), then please have a look here: 
//        https://byuu.org/projects/libco 
//     The 'longjmp' implementation is only five-six times slower than his native i386-amd64 implementations. 
//     The 'longjmp' implementation is therefore is very good trade-off. 
















// *** KERNEL STUFFS *** 

void Kernel_DemanderAQuitterLeJeu(void) {
  isrunning = false;
};



#if 1 
static void Kernel_Script_C__ctfun(void) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "  "   "\n", __func__     ); 
  
  //int retval = script_c__run(script_c_env, &api_contexte); 
  int retval = Script_Run_script_c(&api_contexte); 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " retval = %d "   "\n", __func__, retval); 
  
  if (retval >= 0) { 
    retval = Script_Get_script_c_retval(); 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " retval = %d "   "\n", __func__, retval);  
  }; 
  
  cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__script__processing_system__c); 
  const int data_offset = cooperative_thread__alloc_data__temp(cooperative_thread_env, cooperative_thread__script__processing_system__c, sizeof(retval)); 
  cooperative_thread__write_data__temp(cooperative_thread_env, cooperative_thread__script__processing_system__c, data_offset, sizeof(retval), (const char *) &retval); 
}; 
#endif 

#if 1 
// For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
//int Kernel_Script_Start_arg(const char * script_file_name, const char * script_function_name, const int int_argc, const int int_argv[int_argc], const int ptr_argc, void * ptr_argv[ptr_argc], const int cptr_argc, const void * cptr_argv[ptr_argc], Kernel_Script_Modal_t modal_mode) { 
int Kernel_Script_Start_arg(const char * script_file_name, const char * script_function_name, const int int_argc, const int int_argv[], const int ptr_argc, void * ptr_argv[], const int cptr_argc, const void * cptr_argv[], Kernel_Script_Modal_t modal_mode) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " script_file_name = '%s', script_function_name = '%s', int_argc = %d, int_argv = %p, ptr_argc = %d, ptr_argv = %p, cptr_argc = %d, cptr_argv = %p, modal_mode = %d" "\n", __func__, script_file_name, script_function_name, int_argc, int_argv, ptr_argc, ptr_argv, cptr_argc, cptr_argv, modal_mode); 
  
  if (cooperative_thread__busy_huh(cooperative_thread_env, cooperative_thread__script__processing_system__c)) { return -3; }; 
  
  { 
    const int retval = Script_Start_arg(script_file_name, script_function_name, int_argc, int_argv, ptr_argc, ptr_argv, cptr_argc, cptr_argv); 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " retval = %d "   "\n", __func__, retval); 
    if (retval < 0) return retval; 
  }; 
  
  *(api_contexte.Kernel_Script_Modal_ref) = modal_mode; 
  
  // RL: TODO XXX FIXME: It's a hack until we have a better way of doing that. 
  if (script_file_name == NULL || *script_file_name == '\0') { 
    cooperative_thread__set_fun(cooperative_thread_env, cooperative_thread__script__processing_system__c, Kernel_Script_C__ctfun); 
  }; 
  
  // RL: If we are in 'ScriptSlave' mode, then we have to be synchronized, and the kernel won't return until the operation is completed. 
  //     If not, it will return at the next loop iteration. 
  //     And if there is an error, it will return right away. 
  { 
    const int retval = cooperative_thread__thread_yield_to_kernel(cooperative_thread_env); 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " retval = %d "   "\n", __func__, retval); 
    if (retval < 0) { 
      *(api_contexte.TypeInstructionCourante) = Script_Automaton_Idle; 
      *(api_contexte.Kernel_Script_Modal_ref) = Kernel_Script_Modal__ScriptIsMaster; 
      return retval; 
    }; 
  }; 
  
  int retval = 0; 
  if (modal_mode == Kernel_Script_Modal__ScriptIsSlave) { 
    // RL: In slave mode, we have to read the data returned by the called function to return it to the caller. 
    cooperative_thread__data_temp__read_top(cooperative_thread_env, cooperative_thread__script__processing_system__c, /*data_sizeof*/sizeof(int), (char *)&retval); 
    cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__script__processing_system__c); 
  }; 
  
  return retval; 
}; 
#else 
int Kernel_Script_Start_arg(const char * script_file_name, const char * script_function_name, const int int_argc, const int int_argv[int_argc], const int ptr_argc, void * ptr_argv[ptr_argc], const int cptr_argc, const void * cptr_argv[ptr_argc], Kernel_Script_Modal_t modal_mode) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " script_file_name = '%s', script_function_name = '%s', int_argc = %d, int_argv = %p, ptr_argc = %d, ptr_argv = %p, cptr_argc = %d, cptr_argv = %p, modal_mode = %d" "\n", __func__, script_file_name, script_function_name, int_argc, int_argv, ptr_argc, ptr_argv, cptr_argc, cptr_argv, modal_mode); 
  
  if (script_function_name == NULL || *script_function_name == '\0') { return -2; }; 
  
  if (*(api_contexte.TypeInstructionCourante) != Script_Automaton_Idle) { return -1; }; 
  
  if (cooperative_thread__busy_huh(cooperative_thread_env, cooperative_thread__script__processing_system__c)) { return -3; }; 
  
  if (script_file_name == NULL || *script_file_name == '\0') { 
    const int script_function_i = script_c__lookup(script_c_env, script_function_name); 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " script_c_env['%s'] = %d"   "\n", __func__, script_function_name, script_function_i); 
    if (script_function_i < 0) { 
      messerr("Could not find a C script named in '%s'.", script_file_name); 
      return -4; 
    }; 
    if (script_c__busy_huh(script_c_env)) { return -5; }; // RL: Should not happen though. 
    script_c__set(script_c_env, script_function_i); 
    *(api_contexte.TypeInstructionCourante) = Script_Automaton_Script_C; 
    *(api_contexte.Kernel_Script_Modal_ref) = modal_mode; 
    cooperative_thread__set_fun(cooperative_thread_env, cooperative_thread__script__processing_system__c, Kernel_Script_C__ctfun); 
    // RL: Pushing the args - the last one first. 
#if 1 
    { 
      script_c__data_temp__reset(script_c_env); 
      for (int i = 0; i < cptr_argc; i++) { 
	script_c__data_temp__push(script_c_env, sizeof(void *), (const char *)&cptr_argv[cptr_argc - i - 1]); 
      }; 
      script_c__data_temp__push(script_c_env, sizeof(int), (const char *)&cptr_argc); 
      for (int i = 0; i < ptr_argc; i++) { 
	script_c__data_temp__push(script_c_env, sizeof(void *), (const char *)&ptr_argv[ptr_argc - i - 1]); 
      }; 
      script_c__data_temp__push(script_c_env, sizeof(int), (const char *)&ptr_argc); 
      for (int i = 0; i < int_argc; i++) { 
	script_c__data_temp__push(script_c_env, sizeof(int), (const char *)&int_argv[int_argc - i - 1]); 
      }; 
      script_c__data_temp__push(script_c_env, sizeof(int), (const char *)&int_argc); 
    }; 
#else 
    { 
      cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__script__processing_system__c); 
      for (int i = 0; i < cptr_argc; i++) { 
	cooperative_thread__data_temp__push(cooperative_thread_env, cooperative_thread__script__processing_system__c, sizeof(void *), (const char *)&cptr_argv[i]); 
      }; 
      cooperative_thread__data_temp__push(cooperative_thread_env, cooperative_thread__script__processing_system__c, sizeof(int), (const char *)&cptr_argc); 
      for (int i = 0; i < ptr_argc; i++) { 
	cooperative_thread__data_temp__push(cooperative_thread_env, cooperative_thread__script__processing_system__c, sizeof(void *), (const char *)&ptr_argv[i]); 
      }; 
      cooperative_thread__data_temp__push(cooperative_thread_env, cooperative_thread__script__processing_system__c, sizeof(int), (const char *)&ptr_argc); 
      for (int i = 0; i < int_argc; i++) { 
	cooperative_thread__data_temp__push(cooperative_thread_env, cooperative_thread__script__processing_system__c, sizeof(int), (const char *)&int_argv[i]); 
      }; 
      cooperative_thread__data_temp__push(cooperative_thread_env, cooperative_thread__script__processing_system__c, sizeof(int), (const char *)&int_argc); 
    }; 
#endif 
    
    int retval = cooperative_thread__thread_yield_to_kernel(cooperative_thread_env); 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " retval = %d "   "\n", __func__, retval); 
    
    if (retval < 0) { 
      *(api_contexte.TypeInstructionCourante) = Script_Automaton_Idle; 
      *(api_contexte.Kernel_Script_Modal_ref) = Kernel_Script_Modal__ScriptIsMaster; 
      return retval; 
    }; 
    
#if 1 
    script_c__data_temp__read_top(script_c_env, /*data_sizeof*/sizeof(int), (char *)&retval); 
    script_c__data_temp__reset(script_c_env); 
#else 
    cooperative_thread__data_temp__read_top(cooperative_thread_env, cooperative_thread__script__processing_system__c, /*data_sizeof*/sizeof(int), (char *)&retval); 
    //cooperative_thread__read_data__temp(cooperative_thread_env, cooperative_thread__script__processing_system__c, /*data_offset*/0, sizeof(retval), (char *) &retval); 
    cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__script__processing_system__c); 
#endif 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " retval = %d "   "\n", __func__, retval); 
    return retval; 
  }; 
  
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " PSCRIPT NOT YET IMPLEMENTED " "\n", __func__); 
  return -5; 
  
  return 0; 
  
}; 
#endif 



static int Kernel_Run__switch_to__script_c_loop(void) { 
#if 1 
  if (!cooperative_thread__busy_huh(cooperative_thread_env, cooperative_thread__script__processing_system__c)) { return -1; }; 
#else 
  if (!cooperative_thread__busy_huh(cooperative_thread_env, cooperative_thread__script__processing_system__c)) { 
    cooperative_thread__set_fun(cooperative_thread_env, cooperative_thread__script__processing_system__c, Kernel_Script_C__ctfun); 
  }; 
#endif 

  int retval = cooperative_thread__kernel_switch_to_thread(cooperative_thread_env, cooperative_thread__script__processing_system__c); 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " retval = %d "   "\n", __func__, retval); 
  if (retval < 0) { return retval; }; 
#if 1 
  return 0; 
#else 
  cooperative_thread__read_data__temp(cooperative_thread_env, cooperative_thread__script__processing_system__c, /*data_offset*/0, sizeof(int), (char *) &retval); 
  return retval; 
#endif 
}; 



int Kernel_Script_C__next(void) { 
#if 0 
  if (!cooperative_thread__busy_huh(cooperative_thread_env, cooperative_thread__script__processing_system__c)) { return -1; }; 
  int retval = cooperative_thread__kernel_switch_to_thread(cooperative_thread_env, cooperative_thread__script__processing_system__c); 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " retval = %d "   "\n", __func__, retval); 
  if (retval < 0) { return retval; }; 
  return 0; 
#else 
  const int retval = Kernel_Run__switch_to__script_c_loop(); 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " retval = %d "   "\n", __func__, retval); 
  if (retval < 0) { 
    // RL: That means that, either the cooperative thread is done, either there was an error. 
    if (Kernel_Script_Modal == Kernel_Script_Modal__ScriptIsSlave) { 
      // RL: The game is waiting for a value. 
      //     But we haven't dropped the value. 
#if 1 
      {
	int a; 
	//cooperative_thread__read_data__temp(cooperative_thread_env, cooperative_thread__script__processing_system__c, /*data_offset*/0, sizeof(int), (char *) &a); 
	cooperative_thread__data_temp__read_top(cooperative_thread_env, cooperative_thread__script__processing_system__c, /*data_sizeof*/sizeof(int), (char *)&a); 
	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " retval = %d "   "\n", __func__, a); 
      }; 
#else 
      cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__script__processing_system__c); 
      const int data_offset = cooperative_thread__data_temp__push(cooperative_thread_env, cooperative_thread__script__processing_system__c, sizeof(int), (const char *)&retval); 
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " data_offset = %d "   "\n", __func__, data_offset); 
#if 1 
      { 
	int a; 
	cooperative_thread__read_data__temp(cooperative_thread_env, cooperative_thread__script__processing_system__c, /*data_offset*/0, sizeof(int), (char *) &a); 
	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " retval = %d "   "\n", __func__, a); 
      }; 
#endif 
#endif 
      Kernel_Script_Modal = Kernel_Script_Modal__ScriptIsMaster; // RL: Needed to yield back to the primary thread of the game. 
    }; 
    *(api_contexte.TypeInstructionCourante) = Script_Automaton_Idle; 
  }; 
  const int TypeInstruction_next = *(api_contexte.TypeInstructionCourante); 
  return 0; 
  //return TypeInstruction_next; 
#endif 
}; 

#if 1 
int Kernel_Script_Start(const char * script_file_name, const char * script_function_name) { 
  return Kernel_Script_Start_arg(script_file_name, script_function_name, 0, /*int_argv*/((int [0]) {}), /*ptr_argc*/0, /*ptr_argv*/((void *[0]) {}), /*cptr_argc*/0, /*cptr_argv*/((const void *[0]) {}), Kernel_Script_Modal__ScriptIsMaster); 
}; 
#else 
int Kernel_Script_Start(const char * script_file_name, const char * script_function_name) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " script_file_name = '%s', script_function_name = '%s'" "\n", __func__, script_file_name, script_function_name); 

  if (script_function_name == NULL || *script_function_name == '\0') { return -2; }; 
  
  if (*(api_contexte.TypeInstructionCourante) != Script_Automaton_Idle) { return -1; }; 
  
  if (cooperative_thread__busy_huh(cooperative_thread_env, cooperative_thread__script__processing_system__c)) { return -3; }; 
  
  if (script_file_name == NULL || *script_file_name == '\0') { 
    const int script_function_i = script_c__lookup(script_c_env, script_function_name); 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " script_c_env['%s'] = %d"   "\n", __func__, script_function_name, script_function_i); 
    if (script_function_i < 0) { return -4; }; 
    if (script_c__busy_huh(script_c_env)) { return -5; }; // RL: Should not happen though. 
    script_c__set(script_c_env, script_function_i); 
    *(api_contexte.TypeInstructionCourante) = Script_Automaton_Script_C; 
#if 0 
    script_c__run(script_c_env, &api_contexte); 
#else 
    cooperative_thread__set_fun(cooperative_thread_env, cooperative_thread__script__processing_system__c, Kernel_Script_C__ctfun); 

#if 1 
    int retval = cooperative_thread__thread_yield_to_kernel(cooperative_thread_env); 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " retval = %d "   "\n", __func__, retval); 
    if (retval < 0) { 
      *(api_contexte.TypeInstructionCourante) = Script_Automaton_Idle; 
      return retval; 
    }; 
#else 
    int retval = cooperative_thread__kernel_switch_to_thread(cooperative_thread_env, cooperative_thread__script__processing_system__c); 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " retval = %d "   "\n", __func__, retval); 
    if (retval < 0) { 
      *(api_contexte.TypeInstructionCourante) = Script_Automaton_Idle; 
      return retval; 
    }; 
    
    cooperative_thread__read_data__temp(cooperative_thread_env, cooperative_thread__script__processing_system__c, /*data_offset*/0, sizeof(retval), (char *) &retval); 
    cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__script__processing_system__c); 
#endif 
#endif 

    *(api_contexte.TypeInstructionCourante) = Script_Automaton_Idle; 
    return retval; 
  }; 
  
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " PSCRIPT NOT YET IMPLEMENTED " "\n", __func__); 
  return -5; 
  
  return 0; 
}; 
#endif 

int Kernel_Script_YieldToKernel(void) { 
  // RL: The upcoming context was set up by the caller. 
  //     But we do not want to lose the current context (whole point of that cooperative-thread work), 
  //     so we yield back to the kernel. 
  const int retval = cooperative_thread__thread_yield_to_kernel(cooperative_thread_env); 
  // RL: We will come back here ***after** the kernel stuffs were done. 
  return retval; 
}; 


int Kernel_Supervisor_Message(const char * message) { 
  if (supervisor_mode_huh) { return INT_MIN; }; 
  int retval = supervisor__message(supervisor_env, message); 
  if (retval < 0) { return retval; }; 
  supervisor_mode_huh = true; 
  // RL: So we set up the upcoming context. 
  //     But we do not want to lose the current one (whole point of that cooperative-thread work), 
  //     so we yield back to the kernel. 
  retval = cooperative_thread__thread_yield_to_kernel(cooperative_thread_env); 
  // RL: We will come back here ***after** the 'Kernel_Supervisor_Message' stuffs were done. 
  return retval; 
}; 

int Kernel_Supervisor_Menu(const char * message, const int choix_nb, const char * choix_array[]) { 
  if (supervisor_mode_huh) { return INT_MIN; }; 
  int choix = INT_MIN; 
  int retval = supervisor__menu(supervisor_env, &choix, message, choix_nb, choix_array); 
  if (retval < 0) { return retval; }; 
  supervisor_mode_huh = true; 
  // RL: So we set up the upcoming context. 
  //     But we do not want to lose the current one (whole point of that cooperative-thread work), 
  //     so we yield back to the kernel. 
  retval = cooperative_thread__thread_yield_to_kernel(cooperative_thread_env); 
  if (retval < 0) { return retval; }; 
  // RL: We will come back here ***after** the 'Kernel_Supervisor_Message' stuffs were done. 
  return choix; // 'choix' was written by the supervisor - possible because 'choix' context was not disposed. 
}; 


static int Kernel_Ticks_at_start;

static void Kernel_DebutDePasse(void) { 
  Kernel_Ticks_at_start = SDL_GetTicks();   
}; 

static void Kernel_FinDePasse(void) { 
  const int diff = SDL_GetTicks() - Kernel_Ticks_at_start; 
  
enum { nb_microsec_in_passe = 20 }; 
#if 1 
  if (diff < nb_microsec_in_passe) { 
    SDL_Delay(nb_microsec_in_passe - diff); 
  }; 
#endif 
  
}; 


static void Kernel_Run__switch_to__supervisor_loop__fun(void) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " >>>  "   "\n", __func__     ); 
  //messerr("Hello world!" "\n"); 

  supervisor_env_t * supervisor_env = NULL; 
  cooperative_thread__read_data__temp(cooperative_thread_env, cooperative_thread__supervisor, /*data_offset*/0, sizeof(supervisor_env), (char *) &supervisor_env); 
  cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__supervisor); 

  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " --- supervisor_env = %p"   "\n", __func__, supervisor_env); 
  
  const int next_state = supervisor__loop(supervisor_env); 
  
  cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__supervisor); 
  const int data_offset = cooperative_thread__alloc_data__temp(cooperative_thread_env, cooperative_thread__supervisor, sizeof(next_state)); 
  cooperative_thread__write_data__temp(cooperative_thread_env, cooperative_thread__supervisor, data_offset, sizeof(next_state), (const char *) &next_state); 
}; 

int Kernel_Run__switch_to__supervisor_loop(supervisor_env_t * supervisor_env) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " >>> supervisor_env = %p"   "\n", __func__, supervisor_env); 
  if (!cooperative_thread__busy_huh(cooperative_thread_env, cooperative_thread__supervisor)) { 
    cooperative_thread__set_fun(cooperative_thread_env, cooperative_thread__supervisor, Kernel_Run__switch_to__supervisor_loop__fun); 
  
    // RL: That could overflow the data-temp stack. 
    cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__supervisor); 
    const int data_offset = cooperative_thread__alloc_data__temp(cooperative_thread_env, cooperative_thread__supervisor, sizeof(supervisor_env)); 
    cooperative_thread__write_data__temp(cooperative_thread_env, cooperative_thread__supervisor, data_offset, sizeof(supervisor_env), (const char *) &supervisor_env); 
  }; 
  
  const int retval = cooperative_thread__kernel_switch_to_thread(cooperative_thread_env, cooperative_thread__supervisor); 
  if (retval < 0) return retval; 
  
  int next_state; 
  cooperative_thread__read_data__temp(cooperative_thread_env, cooperative_thread__supervisor, /*data_offset*/0, sizeof(next_state), (char *) &next_state); 
  cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__supervisor); 
  
  return next_state; 
}; 


static void Kernel_Run__switch_to__game_loop__secondary__fun(void) { 
  api_contexte_t * api_contexte; 
  cooperative_thread__data_temp__read_top_and_drop(cooperative_thread_env, cooperative_thread__game_secondary, sizeof(api_contexte), (char *) &api_contexte); 
  cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__game_secondary); 

  const int ModeJeu_next = Game_Loop(/*animate_but_do_not_aliven_huh*/true, api_contexte); 
  
  cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__game_secondary); 
  const int data_offset = cooperative_thread__alloc_data__temp(cooperative_thread_env, cooperative_thread__game_secondary, sizeof(int)); 
  cooperative_thread__write_data__temp(cooperative_thread_env, cooperative_thread__game_secondary, data_offset, sizeof(int), (const char *) &ModeJeu_next); 
}; 

int Kernel_Run__switch_to__game_loop__secondary(api_contexte_t * api_contexte) { 
  if (!cooperative_thread__busy_huh(cooperative_thread_env, cooperative_thread__game_secondary)) { 
    cooperative_thread__set_fun(cooperative_thread_env, cooperative_thread__game_secondary, Kernel_Run__switch_to__game_loop__secondary__fun); 
    
    // RL: In supervisor mode, that could overflow the data-temp stack. 
    cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__game_secondary); 
    cooperative_thread__data_temp__push(cooperative_thread_env, cooperative_thread__game_secondary, sizeof(api_contexte), (const char *) &api_contexte); 
  }; 
  
  const int retval = cooperative_thread__kernel_switch_to_thread(cooperative_thread_env, cooperative_thread__game_secondary); 
  if (retval < 0) { return retval; }; 
  
  int ModeJeu_next; 
  cooperative_thread__read_data__temp(cooperative_thread_env, cooperative_thread__game_secondary, /*data_offset*/0, sizeof(int), (char *) &ModeJeu_next); 
  cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__game_secondary); 
  return ModeJeu_next; 
}; 


static void Kernel_Run__switch_to__game_loop__fun(void) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "  "   "\n", __func__     ); 
  //messerr("Kernel Game Loop" "\n"); 
  //const int ModeJeu_next = Game_Loop(/*blit_huh*/false); 
  
  int animate_but_do_not_aliven_huh; 
  cooperative_thread__data_temp__read_top_and_drop(cooperative_thread_env, cooperative_thread__game_primary, sizeof(animate_but_do_not_aliven_huh), (char *) &animate_but_do_not_aliven_huh); 
  api_contexte_t * api_contexte; 
  cooperative_thread__data_temp__read_top_and_drop(cooperative_thread_env, cooperative_thread__game_primary, sizeof(api_contexte), (char *) &api_contexte); 
  cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__game_primary); 

  const int ModeJeu_next = Game_Loop(animate_but_do_not_aliven_huh, api_contexte); 
  
  //Game_Loop(/*blit_huh*/true); 
  cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__game_primary); 
  const int data_offset = cooperative_thread__alloc_data__temp(cooperative_thread_env, cooperative_thread__game_primary, sizeof(int)); 
  cooperative_thread__write_data__temp(cooperative_thread_env, cooperative_thread__game_primary, data_offset, sizeof(int), (const char *) &ModeJeu_next); 
}; 

int Kernel_Run__switch_to__game_loop(const int animate_but_do_not_aliven_huh, api_contexte_t * api_contexte) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " >>> "   "\n", __func__     ); 
  if (!cooperative_thread__busy_huh(cooperative_thread_env, cooperative_thread__game_primary)) { 
    cooperative_thread__set_fun(cooperative_thread_env, cooperative_thread__game_primary, Kernel_Run__switch_to__game_loop__fun); 
    
    // RL: In supervisor mode, that could overflow the data-temp stack. 
    cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__game_primary); 
    cooperative_thread__data_temp__push(cooperative_thread_env, cooperative_thread__game_primary, sizeof(api_contexte), (const char *) &api_contexte); 
    cooperative_thread__data_temp__push(cooperative_thread_env, cooperative_thread__game_primary, sizeof(animate_but_do_not_aliven_huh), (const char *) &animate_but_do_not_aliven_huh); 
  }; 
  
  const int retval = cooperative_thread__kernel_switch_to_thread(cooperative_thread_env, cooperative_thread__game_primary); 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " retval = %d "   "\n", __func__, retval); 
  if (retval < 0) { return retval; }; 
  
  int ModeJeu_next; 
  cooperative_thread__read_data__temp(cooperative_thread_env, cooperative_thread__game_primary, /*data_offset*/0, sizeof(int), (char *) &ModeJeu_next); 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " ModeJeu_next = %d "   "\n", __func__, ModeJeu_next); 
  cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__game_primary); 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " <<< "   "\n", __func__     ); 
  //Game_Loop(/*blit_huh*/true); 
  return ModeJeu_next; 
}; 



static void Kernel_Run__switch_to__script_loop__fun(void) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "  "   "\n", __func__     ); 
  //messerr("Kernel Script Loop" "\n"); 
  api_contexte_t * api_contexte = NULL; 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " --- stack_nb = %d "   "\n", __func__, cooperative_thread__data_temp__get_used(cooperative_thread_env, cooperative_thread__script__control_system__automaton)); 
  //cooperative_thread__data_temp__print_d(2, cooperative_thread_env, cooperative_thread__script__control_system__automaton); dputc(2, '\n'); 

  cooperative_thread__read_data__temp(cooperative_thread_env, cooperative_thread__script__control_system__automaton, /*data_offset*/0, sizeof(api_contexte), (char *) &api_contexte); 
  cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__script__control_system__automaton); 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " --- api_contexte = %p "   "\n", __func__, api_contexte); 
  
  const int TypeInstruction_next = Script_Loop(api_contexte); 
  
  cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__script__control_system__automaton); 
  const int data_offset = cooperative_thread__alloc_data__temp(cooperative_thread_env, cooperative_thread__script__control_system__automaton, sizeof(int)); 
  cooperative_thread__write_data__temp(cooperative_thread_env, cooperative_thread__script__control_system__automaton, data_offset, sizeof(int), (const char *) &TypeInstruction_next); 
}; 

int Kernel_Run__switch_to__script_loop(api_contexte_t * api_contexte) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " >>> api_contexte = %p "   "\n", __func__, api_contexte); 
  if (!cooperative_thread__busy_huh(cooperative_thread_env, cooperative_thread__script__control_system__automaton)) { 
    cooperative_thread__set_fun(cooperative_thread_env, cooperative_thread__script__control_system__automaton, Kernel_Run__switch_to__script_loop__fun); 
    
    // RL: In supervisor mode, that could overflow the data-temp stack. 
    cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__script__control_system__automaton); 
    const int data_offset = cooperative_thread__alloc_data__temp(cooperative_thread_env, cooperative_thread__script__control_system__automaton, sizeof(api_contexte)); 
    cooperative_thread__write_data__temp(cooperative_thread_env, cooperative_thread__script__control_system__automaton, data_offset, sizeof(api_contexte), (const char *) &api_contexte); 
  }; 

  const int retval = cooperative_thread__kernel_switch_to_thread(cooperative_thread_env, cooperative_thread__script__control_system__automaton); 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " retval = %d "   "\n", __func__, retval); 
  if (retval < 0) { return retval; }; 
  
  int TypeInstruction_next; 
  cooperative_thread__read_data__temp(cooperative_thread_env, cooperative_thread__script__control_system__automaton, /*data_offset*/0, sizeof(int), (char *) &TypeInstruction_next); 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " ModeJeu_next = %d "   "\n", __func__, TypeInstruction_next); 
  cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__script__control_system__automaton); 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " <<< "   "\n", __func__     ); 
  return TypeInstruction_next; 
}; 



//extern void asdadsa(const int n1, int a1[n1], const int n2, void * a2[n2]); 

int Kernel_Run(void) { 
  int retval = 0; 
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "\n", __func__); 
  
  { dprintf(fileno(stdout), "STDOUT BUFFER: %p\n", stdout -> _bf._base); }; 
  
  //retval = Game_Init(); if (retval < 0) { return retval; }; 
  
  //fflush(NULL); 
  //fflush(stdout); 
  fflush(NULL); 
 
  while (isrunning) { 
    Kernel_DebutDePasse(); 
    //printf("------------------------------------------------------------------------------" "\n");
    
    // RL: Cleaning up the screen and the z-buffer 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    KeyBoard = SDL_GetKeyState(NULL); 
    
    sdl__process_events(); 

    if (false) { 
      Kernel_Run__switch_to__supervisor_loop(supervisor_env); 
    } 
    else if (supervisor_mode_huh) { 
      //supervisor__loop(supervisor_env); 
      const int next_state = Kernel_Run__switch_to__supervisor_loop(supervisor_env); 
      if (next_state == SUPERVISOR_MODE__IDLE) { supervisor_mode_huh = false; }; 
    } 
    else { 
      //Script__automaton(); 
#if 1 
      const int TypeInstruction_next = Script_Loop(&api_contexte); 
#else 
      int TypeInstruction_next = -1; 
      if (*(api_contexte.TypeInstructionCourante) == Script_Automaton_Script_C) { 
	// RL: TODO XXX FIXME: I can't see why this code is not in the Script_Automaton. 
	// RL: Because it's the scheduler's job. 
	// RL: However, that's weird. Should be in the Script_Automaton. 
	const int retval = Kernel_Run__switch_to__script_c_loop(); 
	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " retval = %d "   "\n", __func__, retval); 
	if (retval < 0) { 
	  // RL: That means that, either the cooperative thread is done, either there was an error. 
	  if (Kernel_Script_Modal == Kernel_Script_Modal__ScriptIsSlave) { 
	    // RL: The game is waiting for a value. 
	    //     But we haven't dropped the value. 
#if 1 
	    {
	      int a; 
	      //cooperative_thread__read_data__temp(cooperative_thread_env, cooperative_thread__script__processing_system__c, /*data_offset*/0, sizeof(int), (char *) &a); 
	      cooperative_thread__data_temp__read_top(cooperative_thread_env, cooperative_thread__script__processing_system__c, /*data_sizeof*/sizeof(int), (char *)&a); 
	      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " retval = %d "   "\n", __func__, a); 
	    }; 
#else 
	    cooperative_thread__reset_data__temp(cooperative_thread_env, cooperative_thread__script__processing_system__c); 
	    const int data_offset = cooperative_thread__data_temp__push(cooperative_thread_env, cooperative_thread__script__processing_system__c, sizeof(int), (const char *)&retval); 
	    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " data_offset = %d "   "\n", __func__, data_offset); 
#if 1
	    { 
	      int a; 
	      cooperative_thread__read_data__temp(cooperative_thread_env, cooperative_thread__script__processing_system__c, /*data_offset*/0, sizeof(int), (char *) &a); 
	      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " retval = %d "   "\n", __func__, a); 
	    }; 
#endif 
#endif 
	    Kernel_Script_Modal = Kernel_Script_Modal__ScriptIsMaster; // RL: Needed yield back to the primary thread of the game. 
	  }; 
	  *(api_contexte.TypeInstructionCourante) = Script_Automaton_Idle; 
	}; 
	TypeInstruction_next = *(api_contexte.TypeInstructionCourante); 
      } 
      else { 
	TypeInstruction_next = Kernel_Run__switch_to__script_loop(&api_contexte); 
      }; 
#endif 
      
      //Game_unepassedeboucle(); 
      //fprintf(stderr, "<%s>" "isrunning = %s" "\n", __func__, bool_string(isrunning)); fflush(NULL); 
      
      //const int ModeJeu_next = Game_Loop(); 
      //const int ModeJeu_next = Kernel_Run__switch_to__game_loop(/*animate_but_do_not_aliven_huh*/TypeInstruction_next != Script_Automaton_Idle); 
      int ModeJeu_next = -1; 
      if (Kernel_Script_Modal == Kernel_Script_Modal__ScriptIsSlave) { 
	ModeJeu_next = Kernel_Run__switch_to__game_loop__secondary(&api_contexte); 
      } 
      else { 
	ModeJeu_next = Kernel_Run__switch_to__game_loop(/*animate_but_do_not_aliven_huh*/TypeInstruction_next != Script_Automaton_Idle, &api_contexte); 
      }; 
      
      if (ModeJeu_next == mjIDLE && TypeInstruction_next == Script_Automaton_Idle) { 
	isrunning = false; 
      }; 
    }; 
    
    SDL_GL_SwapBuffers(); 
    
    //printf("------------------------------------------------------------------------------" "\n"); 
    fflush(NULL); 
    Kernel_FinDePasse(); 
  }; 
  
  fflush(NULL); 
  
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "\n", __func__); 
  
  return retval; 
}; 


int Kernel_Init(void) {
  int retval = 0; 
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " ">>>" "\n", __func__); 
  { dprintf(fileno(stdout), "STDOUT BUFFER: %p\n", stdout -> _bf._base); }; 
  fflush(NULL); 

  cooperative_thread_env = cooperative_thread_env__make(); 
  cooperative_thread__supervisor                         = cooperative_thread__push(cooperative_thread_env); 
  cooperative_thread__game_primary                       = cooperative_thread__push(cooperative_thread_env); 
  cooperative_thread__game_secondary                     = cooperative_thread__push(cooperative_thread_env); 
  cooperative_thread__script__control_system__automaton  = cooperative_thread__push(cooperative_thread_env); 
  cooperative_thread__script__processing_system__c       = cooperative_thread__push(cooperative_thread_env); 
  cooperative_thread__script__processing_system__pscript = cooperative_thread__push(cooperative_thread_env); 
  cooperative_thread__opengl                             = cooperative_thread__push(cooperative_thread_env); 
  messlog("cooperative_thread__supervisor                         = %d" "\n", cooperative_thread__supervisor); 
  messlog("cooperative_thread__game_primary                       = %d" "\n", cooperative_thread__game_primary); 
  messlog("cooperative_thread__game_secondary                     = %d" "\n", cooperative_thread__game_secondary); 
  messlog("cooperative_thread__script__control_system__automaton  = %d" "\n", cooperative_thread__script__control_system__automaton); 
  messlog("cooperative_thread__script__processing_system__c       = %d" "\n", cooperative_thread__script__processing_system__c); 
  messlog("cooperative_thread__script__processing_system__pscript = %d" "\n", cooperative_thread__script__processing_system__pscript); 
  messlog("cooperative_thread__opengl                             = %d" "\n", cooperative_thread__opengl); 

  messlog("MAIN_STACK                                             = %p" "\n", &retval); 
  messlog("cooperative_thread__supervisor                         = %p" "\n", cooperative_thread__get_stack_addr(cooperative_thread_env, cooperative_thread__supervisor)); 
  messlog("cooperative_thread__game_primary                       = %p" "\n", cooperative_thread__get_stack_addr(cooperative_thread_env, cooperative_thread__game_primary)); 
  messlog("cooperative_thread__game_secondary                     = %p" "\n", cooperative_thread__get_stack_addr(cooperative_thread_env, cooperative_thread__game_secondary)); 
  messlog("cooperative_thread__script__control_system__automaton  = %p" "\n", cooperative_thread__get_stack_addr(cooperative_thread_env, cooperative_thread__script__control_system__automaton)); 
  messlog("cooperative_thread__script__processing_system__c       = %p" "\n", cooperative_thread__get_stack_addr(cooperative_thread_env, cooperative_thread__script__processing_system__c)); 
  messlog("cooperative_thread__script__processing_system__pscript = %p" "\n", cooperative_thread__get_stack_addr(cooperative_thread_env, cooperative_thread__script__processing_system__pscript)); 
  messlog("cooperative_thread__opengl                             = %p" "\n", cooperative_thread__get_stack_addr(cooperative_thread_env, cooperative_thread__opengl)); 


  { dprintf(fileno(stdout), "STDOUT BUFFER: %p\n", stdout -> _bf._base); }; 


  if (!sdl__init()) return -1; 
  
  { dprintf(fileno(stdout), "STDOUT BUFFER: %p\n", stdout -> _bf._base); }; 

  opengl__configure(SCREEN_WIDTH, SCREEN_HEIGHT); 
  
  init_audio(); 
  
  //opengl__stuffs(); 
  fflush(NULL); 
  cooperative_thread__set_fun(cooperative_thread_env, cooperative_thread__opengl, opengl__stuffs); 
  fflush(NULL); 
  cooperative_thread__kernel_switch_to_thread(cooperative_thread_env, cooperative_thread__opengl); 
  
  fflush(NULL); 
  supervisor_mode_huh = false; 
  supervisor_env = supervisor_env__make(); if (supervisor_env == NULL) { return -1; }; 
  
  fflush(NULL); 
  api_contexte__make_r(&api_contexte); 
  fflush(NULL); 
  api_contexte.Kernel_Script_Modal_ref = &Kernel_Script_Modal; 
  
  { dprintf(fileno(stdout), "STDOUT BUFFER: %p\n", stdout -> _bf._base); }; 

  fflush(NULL); 
  retval = Game_Init(&api_contexte); if (retval < 0) { return retval; }; 

  { dprintf(fileno(stdout), "STDOUT BUFFER: %p\n", stdout -> _bf._base); }; 

#if 1 
  fflush(NULL); 
  retval = Script_Init(&api_contexte); if (retval < 0) { return retval; }; 

  { dprintf(fileno(stdout), "STDOUT BUFFER: %p\n", stdout -> _bf._base); }; 

  //script_c_env__make_r(script_c_env); 
  //script_c_env = script_c_env__make(); 
  //script_c__lib1__fill(script_c_env); 

#if 0 
  { 
    const int nb = script_c__count(script_c_env); 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " script_c__count(script_c_env) = %d"   "\n", __func__, nb); 
    for (int i = 0; i < nb; i++) { 
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " \t" "script_c_env[%d] = '%s'"   "\n", __func__, i, script_c__get_name(script_c_env, i)); 
    }; 
    const int hello_i = script_c__lookup(script_c_env, "hello"); 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " script_c_env['hello'] = %d"   "\n", __func__, hello_i); 
    if (hello_i >= 0) { 
      script_c__set(script_c_env, hello_i); 
      script_c__run(script_c_env); 
    }; 
  }; 
#endif 

#else 
  fflush(NULL); 
  script = CScriptLauncher_make("script.pml", "debut"); 
  assert(script != NULL); 
  script -> init_step(script); 
#endif 
  
  { dprintf(fileno(stdout), "STDOUT BUFFER: %p\n", stdout -> _bf._base); }; 

  printf("Fin de l'initialisation!! YOUPI!!" "\n");
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "<<<" "\n", __func__); 
  printf("==============================================================================" "\n");
  printf("==============================================================================" "\n");
  printf("==============================================================================" "\n");
  fflush(NULL); 
  
  return 0; 
}; 





void Kernel_Dispose(void) {
  printf("==============================================================================" "\n");
  printf("==============================================================================" "\n");
  printf("==============================================================================" "\n");
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " ">>>" "\n", __func__); 

  //script_c_env__delete(script_c_env); 
  //script_c_env__delete_r(script_c_env); 

  Script_Dispose(); 
  
  Game_Dispose(); 
  
  api_contexte__delete_r(&api_contexte); 
  
  supervisor_env__delete(supervisor_env); 
  
  close_audio(); 
  
  sdl__dispose(); 

  cooperative_thread_env__delete(cooperative_thread_env); 
  
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "<<<" "\n", __func__); 
}; // Free()
 












// *** VIDEO SUB SYSTEM STUFFS *** 

static void opengl__configure(const int width, const int height) {
  const float ratio = (float) width / (float) height;

  //* Setup our viewport. */
  glViewport(0, 0, width, height);

  //* Our shading model--Gouraud (smooth). */
  glShadeModel(GL_SMOOTH);

  //* Set the clear color. */
  glClearColor(0.0, 0.0, 0.0, 1.0);

  //* Set the clear depth */
  glClearDepth(1.0);
  
  //* Culling. */
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);

  glEnable(GL_DEPTH_TEST) ;

  // Change to the projection matrix and set our viewing volume.
  //glMatrixMode(GL_MODELVIEW); 
  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity(); 
  //gluPerspective(60.0, ratio, 1.0, 1024.0); 
  gluPerspective(/*view angle*/60.0, ratio, /*near clipping plane*/1.0, /*far clipping plane*/10240.0); 
}; 


static void opengl__stuffs(void) { 
#if 1 
    glEnable(GL_BLEND) ;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;   
#endif 
    glEnable(GL_TEXTURE_2D);
    //MessageTexte -> SetMsg("Bonjour!! Bienvenue dans le jeu le plus révolutionnaire du 24e millénaire. C'est vraiment que c'est cool et que c'est trop bien. Heureusement que ça marche nickel... j'avais peur un moment. Mais j'avoue que tout est bien qui finit bien.");
    glEnable(GL_LIGHTING);
    // on active le calcul de la lumière
    glEnable(GL_LIGHT0); 
    // on dit que la lumière n°0 est allumée
    // Affichage de la lumière: flou ou pas
    glShadeModel(GL_SMOOTH);
    //glShadeModel(GL_FLAT);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    // on dit que les appels glColor modifie en fait la couleur d'ambiance et de diffusion du matériau
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    // Cause l'apparition des triangles.
    // Donc, l'antialising on enlève.
    //glEnable(GL_POLYGON_SMOOTH);
    glDisable(GL_POLYGON_SMOOTH);
    float mat_amb[] = {1.0, 1.0, 1.0, 1.0};
    float mat_diff[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diff);
    float mat_em[] = {0.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_em);
    // les deux lignes qui suivent sont là pour éviter les bugs de chevauchements
    // pour les images avec des parties entièrement translucides (en fait,
    // un pixel entièrement transparent ne touche pas le Z-buffer)
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    //glFogi(GL_FOG_MODE, GL_EXP);   // exponentiel
    //glFogf(GL_FOG_DENSITY, 0.001); 
    //glFogf(GL_FOG_DENSITY, 0.0f); // GL_FOG_DENSITY CA MARCHE PAS en mode linéaire  !!
    glFogf(GL_FOG_START, 0);
    glFogf(GL_FOG_END, 5000); //500
    glEnable(GL_FOG);
    glDisable(GL_FOG);
#if 0
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
#endif
}; 




bool sdl__init(void) {
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " ">>>" "\n", __func__); 
  
  if (-1 == SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) { 
    messerr("Erreur lors de l'initialisation de la SDL: %s." "\n", SDL_GetError()); 
    return false; 
  }; 
  
  printf("SDL initialisée.\n"); 
  printf("SDL_VideoDriverName: %s\n", SDL_VideoDriverName(alloca(512), 512)); 
  
  // RL: These values must be set before creating an OpenGL window. 
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE    ,  5); 
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE  ,  5); 
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE   ,  5); 
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE  , 16); 
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,  1); // RL: Double-buffering in OpenGL. SDL_DOUBLEBUF is different as it requests a double-buffering for SDL, not OpenGL (so for 2D blitting). 
   
  // RL: Creating the SDL window. 
  if (0 == SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BITSPERPIXEL, SDL_OPENGL | SCREEN_MODE | SDL_DOUBLEBUF | SDL_HWSURFACE /*| SDL_NOFRAME*/)) { 
    messerr("SDL_SetVideoMode failed: %s" "\n", SDL_GetError()); 
    return false; 
  }; 
  
  //SDL_WarpMouse(320, 240); 
  SDL_ShowCursor(true);	
  
  SDL_Screen = SDL_GetVideoSurface();
  if (SDL_Screen == NULL) { 
    messerr("La surface écran 'Screen' n'a pas pu être référencée" "\n"); 
    messerr("SDL: %s" "\n", SDL_GetError()); 
    return false; 
  }; 
  
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "<<<" "\n", __func__); 
  return true; 
}; 


void sdl__dispose(void) { 
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " ">>>" "\n", __func__); 
  
  SDL_QuitSubSystem(SDL_INIT_AUDIO); 
  SDL_QuitSubSystem(SDL_INIT_VIDEO); 
#if 1 
  // RL: 2020-01-12: For some reasons, it crashes... 
  SDL_Quit();
#endif 
  
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "<<<" "\n", __func__); 
};










