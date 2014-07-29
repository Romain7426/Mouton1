#if 0
//#ifndef ACTION_H
#define ACTION_H

#include "ressource.h"

class CMenuAbstrait;

#include "menu.h"




/*
  CScriptLauncher est une classe "limite abstraite" qui gere le lancement de script
  
  cl = new CScriptLauncher("dialogues.pml", "JeanPierreParle");
  cl -> Execute();
  
  delete cl;
*/
  

class CScriptLauncher {
  //private:
  char * proc;

  //public:
  ressource<CPascal> * resPascal;

  CScriptLauncher(const char * const filename, const char * const procedure_name);
  ~CScriptLauncher(void);
           
  void Execute(void);
  void init_step(void);
  bool execute_step(void);
  // execute a partir du point d'entree (filename,  proc)

  void stack_push_int(int a);
  void stack_push_string(const char * str);
};






enum { ACTIONS_MENU_X = 100, ACTIONS_MENU_Y = 400 };

// CActionsMenu c'est un menu qui gere legerement plus les actions
class CActionsMenu : public CMenuAbstrait {    
  //public:
  bool InputAndRender(void);
};



/* cette classe gère un CActionsMenu à l'intérieur éventuellement NULL
   (pour éviter de saturer la mémoire avec un objet alloue qui sert à rien
   ex : les arbres de toute la carte ne vont pas chacun avoir un CActionsMenu
   alloue!!!! sinon, je me pends !!*/
class CObjActionnable {
  //private:
  CActionsMenu * actions; 
  
  //public:
  CObjActionnable(void);
  ~CObjActionnable(void);  
  void InputAndRenderActionMenu(void);  
  void AjouterAction(const char * caption, const char * nom_texture, const char * fichier_pascal, const char * proc);
};



extern void init_actions(void);
extern void free_actions(void);



#endif /* ACTION_H */
