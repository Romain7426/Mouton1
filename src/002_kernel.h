#ifndef KERNEL_H
#define KERNEL_H

extern int  Kernel_Init(void); 
extern void Kernel_Dispose(void); 
extern int  Kernel_Run(void); 

extern void Kernel_DemanderAQuitterLeJeu(void); 

extern int Kernel_Supervisor_Message(const char * message); 
extern int Kernel_Supervisor_Menu(const char * message, const int choix_nb, const char * choix_array[]); 


enum Kernel_Script_Modal_t { 
  Kernel_Script_Modal__ScriptIsMaster, // RL: The standard one. Async. When the script is a back-end. When the game does not wait for the script. When the script takes over, and decides what happens then in the game.  
  Kernel_Script_Modal__ScriptIsSlave,  // RL: Sync. When the script is a front-end. When the game waits for the script. When the game stays in control, and waits for the script before going on. For instance, the game asks the player a question. In that mode, the script cannot change the current map, nor any game property (if wanted, the game has to do it on its own). 
}; 
typedef enum Kernel_Script_Modal_t Kernel_Script_Modal_t; 

extern int Kernel_Script_Start(const char * script_file_name, const char * script_function_name); 
// For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
//extern int Kernel_Script_Start_arg(const char * script_file_name, const char * script_function_name, const int int_argc, const int int_argv[int_argc], const int ptr_argc, void * ptr_argv[ptr_argc], const int cptr_argc, const void * cptr_argv[ptr_argc], Kernel_Script_Modal_t modal_mode); 
extern int Kernel_Script_Start_arg(const char * script_file_name, const char * script_function_name, const int int_argc, const int int_argv[], const int ptr_argc, void * ptr_argv[], const int cptr_argc, const void * cptr_argv[], Kernel_Script_Modal_t modal_mode); 
extern int Kernel_Script_YieldToKernel(void); 
extern int Kernel_Script_C__next(void); 




#endif /* KERNEL_H */
