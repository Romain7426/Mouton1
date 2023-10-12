#include "global.h" 
#include "script.h" 
#include "script_api.h"
#include "script_c.h"

static CScriptLauncher * current_pscript = NULL;

static TTypeInstructionCourante TypeInstructionCourante = Script_Automaton_Idle; 

static script_c_env_t * script_c_env = NULL; 

static CPascal * script_pscript_env = NULL;

static void Script__automaton(api_contexte_t * api_contexte) {
  //fprintf(stderr, "Tic\n");
  //fprintf(stderr, "Tic: instruction courante = %d" "\n", TypeInstructionCourante);
  //if (TypeInstructionCourante != Script_Automaton_Idle) { fprintf(stderr, "Tic: instruction courante = %d" "\n", TypeInstructionCourante); }; 

  switch (TypeInstructionCourante) { 
    
  case Script_Automaton_Idle: { 
  }; break; 
    
  case Script_Automaton_Script_C: { 
    //assert(false); 
    const int retval = Kernel_Script_C__next(); 
  }; break; 
    
  //case ticInstructionScript: { 
  case Script_Automaton_Script_PScript: { 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " --- ticInstructionScript >>> "   "\n", __func__); 
    /*on place le "execute", fonction 
      qui quitte dès qu'elle rencontre une instruction 
      nécessitant un affichage (par exemple afficher 
      un message...) 
    
      Alors execute initialise les valeurs avec
      les fonctions SCRIPT_... puis c bon
      (yora après par exemple
      TypeInstructionCourante = ticAfficherMessage)
    */
    /***********************<<<<<<<<<<<<<<<<<<<<<<<ICI*/
    //script -> Execute(); 
#if 1 
    bool fini_huh = true; 
    if (script_pscript_env -> busy_huh(script_pscript_env)) { 
      for (int i = 0; i < 100; i++) { 
	script_pscript_env -> next_step(script_pscript_env, &fini_huh); 
	if (fini_huh) break; 
	if (TypeInstructionCourante != Script_Automaton_Script_PScript) break; 
      }; 
    }; 
    if (fini_huh) { 
      api_contexte -> TypeInstructionPrecedente = Script_Automaton_Idle; 
      TypeInstructionCourante = Script_Automaton_Idle; 
    }; 
#else 
    if (current_pscript == NULL) { 
      TypeInstructionCourante = Script_Automaton_Idle; 
      break; 
    }; 
    const bool fini_huh = current_pscript -> execute_step(current_pscript); 
    //fprintf(stderr, "<%s:" STRINGIFY(__LINE__) ">: " "fini_huh = %s" "\n", __func__, bool_string(fini_huh)); fflush(NULL); 
    //fprintf(stderr, "HARO!\n"); 
    if (fini_huh) { 
      //fprintf(stder, " -> HARO?\n"); 
      //ModeJeu = mjCARTE; 
      TypeInstructionCourante = Script_Automaton_Idle; 
    }; 
    { 
      *(api_contexte -> TypeInstructionCourante) = api_contexte -> TypeInstructionPrecedente; 
      api_contexte -> TypeInstructionPrecedente = Script_Automaton_Idle; 
      TypeInstructionCourante = Script_Automaton_Idle; 
    }; 
#endif 
  }; break; 

  case ticWait: { 
    api_contexte -> nbpasses--;
    if (api_contexte -> nbpasses == 0) { 
      //TypeInstructionCourante = ticInstructionScript; 
      TypeInstructionCourante = api_contexte -> TypeInstructionPrecedente; 
    }; 
  }; break;
    
  case ticWaitFor: {
    if (not (api_contexte -> b -> IsSoumisADesOrdres(api_contexte -> b))) { 
      //TypeInstructionCourante = ticInstructionScript; 
      TypeInstructionCourante = api_contexte -> TypeInstructionPrecedente; 
    }; 
  }; break;
    
  case ticAfficherMessage: { 
    CMessageTexte * MessageTexte = *(api_contexte -> MessageTexte_ref); 
    //const int text_was_read_huh = MessageTexte -> InputAndRender(MessageTexte); 
    const int text_was_read_huh = MessageTexte -> Input(MessageTexte); 
    MessageTexte -> Life(MessageTexte); 
    MessageTexte -> Render(MessageTexte); 
    //fprintf(stderr, "<%s:" STRINGIFY(__LINE__) ">: " "text_was_read_huh = %s" "\n", __func__, bool_string(text_was_read_huh)); fflush(NULL); 
    if (text_was_read_huh) { 
      //TypeInstructionCourante = ticInstructionScript; 
      *(api_contexte -> TypeInstructionCourante) = api_contexte -> TypeInstructionPrecedente; 
    }; 
    }; break; 

  case ticMiniMenu: { 
    CMessageTexte * MessageTexte = *(api_contexte -> MessageTexte_ref); 
    //MessageTexte -> SetMsg(MessageTexte, "Chapitre");
    MessageTexte -> Life(MessageTexte); // RL: The title of the menu. 
    MessageTexte -> Render(MessageTexte); // RL: The title of the menu. 

    CMiniMenu * MiniMenu = *(api_contexte -> MiniMenu); 
    const int choice_made_huh = MiniMenu -> Input(MiniMenu); 
    //fprintf(stderr, "<%s:" STRINGIFY(__LINE__) ">: " " --- choice_made_huh = %s" "\n", __func__, bool_string(choice_made_huh)); fflush(NULL); 
    MiniMenu -> Life(MiniMenu); 
    MiniMenu -> Render(MiniMenu); 
    if (choice_made_huh) { 
      //script -> stack_push_int(script, MiniMenu -> parent.itheta); 
      //script -> resPascal -> pscript_env -> menu__async_reverse_callback__push_return_value(script -> resPascal -> pscript_env, MiniMenu -> parent.itheta); 
#if 0 
      const int choice = MiniMenu -> parent.Canceled ? -1 : MiniMenu -> parent.itheta; 
      CPascal__ffiproc_callback__Menu__async_reverse_callback__push_return_value(script -> resPascal, choice); 
#endif 
      if (api_contexte -> TypeInstructionPrecedente == Script_Automaton_Script_PScript) { 
	const int choice = MiniMenu -> parent.Canceled ? -1 : MiniMenu -> parent.itheta; 
	CPascal__ffiproc_callback__Menu__async_reverse_callback__push_return_value(script_pscript_env, choice); 
      }; 
      //TypeInstructionCourante = ticInstructionScript; // RL: It should be a stack. 
      *(api_contexte -> TypeInstructionCourante) = api_contexte -> TypeInstructionPrecedente; 
#if 0 
      fprintf(stderr, "Tic: instruction courante = %d" "\n", TypeInstructionCourante);
      fprintf(stderr, "Tic: instruction courante = %d" "\n", TypeInstructionCourante);
      fprintf(stderr, "Tic: instruction courante = %d" "\n", TypeInstructionCourante);
#endif 
    }; 
  }; break; 
  
  case ticChangerDeCarte: {
#if 1
    //fprintf(stderr, "HERE\n"); 
    CMoteurTeleportation * MoteurTeleportation = api_contexte -> MoteurTeleportation; 
    bool teleportation_terminee_huh = false; 
    //MoteurTeleportation -> Life(MoteurTeleportation, &Map, &EnVaisseau, &Hero, &teleportation_terminee_huh); 
    CMoteurTeleportation__Life(MoteurTeleportation, api_contexte -> Map, api_contexte -> EnVaisseau_ref, api_contexte -> Hero, &teleportation_terminee_huh); 
    if (teleportation_terminee_huh) { 
      //fprintf(stderr, "TELEPORTATION_TERMINEE_HUH\n"); 
      //TypeInstructionCourante = ticInstructionScript; 
#if 0 
      fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " *(api_contexte.TypeInstructionCourante) = %d "   "\n", __func__, TypeInstructionCourante); 
      fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " *(api_contexte.TypeInstructionCourante) = %d "   "\n", __func__, *(api_contexte -> TypeInstructionCourante)); 
      fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " *(api_contexte.TypeInstructionPrecedente) = %d "   "\n", __func__, (api_contexte -> TypeInstructionPrecedente)); 
#endif 
      TypeInstructionCourante = api_contexte -> TypeInstructionPrecedente; 
    }; 
    //MoteurTeleportation -> Render(MoteurTeleportation, &Map, &EnVaisseau, &Hero, our_manifold); 
    CMoteurTeleportation__Render(MoteurTeleportation, api_contexte -> Map, api_contexte -> EnVaisseau_ref, api_contexte -> Hero, *api_contexte -> our_manifold_ref); 
#else 
    //fprintf(stderr, "--TELEPORTATION_TERMINEE_HUH\n"); 
    CMap__delete(Map); 
    Map = new CMap("./village.carte", false); 
    Hero -> parent1.SetPosition(Hero -> parent1, 10.0f, 10.0f, mpABSOLU, Map); 
    TypeInstructionCourante = ticInstructionScript; 
#endif
  }
    break;
  
  case ticReadln: do { 
#if 0
      glClearColor(0.5f, 0.5f, 0.8f, 1.0f);
      glEnable(GL_DEPTH_TEST);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif 
      CMenuEntreeNom * MenuEntreeNom = *api_contexte -> MenuEntreeNom_ref; 
      const int b = MenuEntreeNom -> Input(MenuEntreeNom); 
      MenuEntreeNom -> Life(MenuEntreeNom); 
      MenuEntreeNom -> Render(MenuEntreeNom); 
      if (b) { 
	//script -> stack_push_string(script, MenuEntreeNom -> buffer); 
	//CPascal__ffiproc_callback__Readln__async_reverse_callback__push_return_value(current_pscript -> resPascal, MenuEntreeNom -> buffer); 
	CPascal__ffiproc_callback__Readln__async_reverse_callback__push_return_value(script_pscript_env, MenuEntreeNom -> buffer); 
	// on rend la main au script 
	//SCRIPT_SystemeRendMainAuScript = true; 
	//TypeInstructionCourante = ticInstructionScript; 
	TypeInstructionCourante = api_contexte -> TypeInstructionPrecedente; 
      }; 
    } while (false); break; 

  case ticNOMBRE: assert(false); break; 
  default: assert(false); 
  }; // switch 
 
}; 
 
 
int Script_BusyHuh(void) { 
  return TypeInstructionCourante != Script_Automaton_Idle; 
}; 
 
int Script_Init(api_contexte_t * api_contexte) { 
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " ">>>" "\n", __func__); 
  
  TypeInstructionCourante = Script_Automaton_Idle; 
  
  api_contexte -> TypeInstructionCourante = &TypeInstructionCourante; 
  api_contexte -> TypeInstructionPrecedente = Script_Automaton_Idle; 
  
#if 0 
  script = CScriptLauncher_make("script.pml", "debut"); 
  assert(script != NULL); 
  current_pscript -> init_step(script); 
#endif 

  script_pscript_env = CPascal__make_with_file("script.pml"); 
  if (script_pscript_env == NULL) { 
    return -1; 
  }; 
  
  
  script_c_env = script_c_env__make(); 
  script_c__lib1__fill(script_c_env); 
  
  
  
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "<<<" "\n", __func__); 
  return 0; 
}; 

void Script_Dispose(void) { 
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " ">>>" "\n", __func__); 

  script_c_env__delete(script_c_env); 

  CPascal__delete(script_pscript_env); 

  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "<<<" "\n", __func__); 
}; 


int Script_Loop(api_contexte_t * api_contexte) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " api_contexte = %p"   "\n", __func__, api_contexte); 
  Script__automaton(api_contexte); 
  return TypeInstructionCourante; 
}; 






int Script_Start(const char * script_file_name, const char * script_function_name) { 
  return Script_Start_arg(script_file_name, script_function_name, 0, /*int_argv*/((int [0]) {}), /*ptr_argc*/0, /*ptr_argv*/((void *[0]) {}), /*cptr_argc*/0, /*cptr_argv*/((const void *[0]) {})); 
}; 


//int Script_Start_arg(const char * script_file_name, const char * script_function_name, const int int_argc, const int int_argv[int_argc], const int ptr_argc, void * ptr_argv[ptr_argc], const int cptr_argc, const void * cptr_argv[ptr_argc], Kernel_Script_Modal_t modal_mode) { 
// For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
//int Script_Start_arg(const char * script_file_name, const char * script_function_name, const int int_argc, const int int_argv[int_argc], const int ptr_argc, void * ptr_argv[ptr_argc], const int cptr_argc, const void * cptr_argv[ptr_argc]) { 
int Script_Start_arg(const char * script_file_name, const char * script_function_name, const int int_argc, const int int_argv[], const int ptr_argc, void * ptr_argv[], const int cptr_argc, const void * cptr_argv[]) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " script_file_name = '%s', script_function_name = '%s', int_argc = %d, int_argv = %p, ptr_argc = %d, ptr_argv = %p, cptr_argc = %d, cptr_argv = %p" "\n", __func__, script_file_name, script_function_name, int_argc, int_argv, ptr_argc, ptr_argv, cptr_argc, cptr_argv); 
  
  if (script_function_name == NULL || *script_function_name == '\0') { return -2; }; 
  
  if (TypeInstructionCourante != Script_Automaton_Idle) { return -1; }; 
  
  //if (cooperative_thread__busy_huh(cooperative_thread_env, cooperative_thread__script__processing_system__c)) { return -3; }; 




  // *** C SCRIPT *** 
  if (script_file_name == NULL || *script_file_name == '\0') { 
    const int script_function_i = script_c__lookup(script_c_env, script_function_name); 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " script_c_env['%s'] = %d"   "\n", __func__, script_function_name, script_function_i); 
    if (script_function_i < 0) { 
      messerr("Could not find a C script named in '%s'.", script_file_name); 
      return -4; 
    }; 
    if (script_c__busy_huh(script_c_env)) { return -5; }; // RL: Should not happen though. 
    script_c__set(script_c_env, script_function_i); 
    TypeInstructionCourante = Script_Automaton_Script_C; 
    //*(api_contexte.Kernel_Script_Modal_ref) = modal_mode; 
    //cooperative_thread__set_fun(cooperative_thread_env, cooperative_thread__script__processing_system__c, Kernel_Script_C__ctfun); 
    
    // RL: Pushing the args - the last one first. 
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
    
#if 1 
    // RL: Here we are supposed to start the script, not to run it. So we return. 
    return 0; 
#else 
    // RL: If we are in 'ScriptSlave' mode, then it will be synchronized, and the kernel won't return until the operation is completed. If not, it will return at the next loop iteration. And if there is an error, it will return right away. 
#if 1 
    int retval = Kernel_Script_YieldToKernel(); 
#else 
    int retval = cooperative_thread__thread_yield_to_kernel(cooperative_thread_env); 
#endif 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " retval = %d "   "\n", __func__, retval); 
    
    if (retval < 0) { 
#if 1 
      TypeInstructionCourante = Script_Automaton_Idle; 
#else 
      *(api_contexte.TypeInstructionCourante) = Script_Automaton_Idle; 
      *(api_contexte.Kernel_Script_Modal_ref) = Kernel_Script_Modal__ScriptIsMaster; 
#endif 
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
#endif 
  }; 




  // *** PSCRIPT *** 
  { 
    if (0 != strcmp(script_file_name, script_pscript_env -> filename)) { 
      fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " The PScript file '%s' has not been loaded yet. (Currently loaded script file: '%s') " "\n", __func__, script_file_name, script_pscript_env -> filename); 
      return -6; 
    }; 
    if (0 != int_argc || 0 != ptr_argc || 0 != cptr_argc) { 
      fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Running non-argless procedures has not been implemented yet. (int_argc = %d, ptr_argc = %d, cptr_argc = %d) " "\n", __func__, int_argc, ptr_argc, cptr_argc); 
      return -7; 
    }; 
    if (script_pscript_env -> busy_huh(script_pscript_env)) { 
      return -8; 
    }; 
    { const int retval = script_pscript_env -> execProcedure_step(script_pscript_env, script_function_name); if (retval < 0) { return retval; }; }; 
    
    TypeInstructionCourante = Script_Automaton_Script_PScript; //ticInstructionScript; 
    
    // RL: Here we are supposed to start the script, not to run it. So we return. 
    return 0; 
  }; 
  
  
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " SOMETHING GOT WRONG. " "\n", __func__); 
  return -5; 
  
  
  
  
  
  
  return 0; 
  
}; 

int Script_Get_script_c_retval(void) { 
  int retval; 
  script_c__data_temp__read_top(script_c_env, /*data_sizeof*/sizeof(int), (char *)&retval); 
  script_c__data_temp__reset(script_c_env); 
  return retval; 
}; 

int Script_Run_script_c(api_contexte_t * api_contexte) { 
  const int retval = script_c__run(script_c_env, api_contexte); 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " retval = %d "   "\n", __func__, retval); 
  return retval; 
}; 



