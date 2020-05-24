#ifndef SCRIPT_H 
#define SCRIPT_H 

enum TTypeInstructionCourante { 
  Script_Automaton_Idle, 
  Script_Automaton_Script_C, 
  Script_Automaton_Script_PScript, 
  //ticInstructionScript, // FS: /*instruction genre if, + etc... géré par le script*/
  ticAfficherMessage,   // FS: /*instruction affichermessage (la boucle du jeu s'en occupe*/
  ticMiniMenu,          // FS: /*itou*/
  ticChangerDeCarte, 
  ticReadln, 
  ticWait, 
  ticWaitFor, 
  ticNOMBRE 
}; 
TYPEDEF_TYPENAME_WITHOUT_ENUM(TTypeInstructionCourante); 

extern int  Script_Init(api_contexte_t * api_contexte); 
extern int  Script_Loop(api_contexte_t * api_contexte); 
extern void Script_Dispose(void); 

extern int  Script_Loop(api_contexte_t * api_contexte); 

extern int  Script_BusyHuh(void); 


extern int Script_Start(const char * script_file_name, const char * script_function_name); 
//extern int Script_Start_arg(const char * script_file_name, const char * script_function_name, const int int_argc, const int int_argv[int_argc], const int ptr_argc, void * ptr_argv[ptr_argc], const int cptr_argc, const void * cptr_argv[ptr_argc], Kernel_Script_Modal_t modal_mode); 
extern int Script_Start_arg(const char * script_file_name, const char * script_function_name, const int int_argc, const int int_argv[int_argc], const int ptr_argc, void * ptr_argv[ptr_argc], const int cptr_argc, const void * cptr_argv[ptr_argc]); 
extern int Script_Get_script_c_retval(void); 
extern int Script_Run_script_c(api_contexte_t * api_contexte); 



#endif /* SCRIPT_H */ 

