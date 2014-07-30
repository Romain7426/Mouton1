#ifndef ACTION_H
#define ACTION_H

struct CScriptLauncher;
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CScriptLauncher);

struct CObjActionnable;
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CObjActionnable);

struct CActionsMenu;
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CActionsMenu);



/* cette structe gère un CActionsMenu à l'intérieur éventuellement NULL
   (pour éviter de saturer la mémoire avec un objet alloue qui sert à rien
   ex : les arbres de toute la carte ne vont pas chacun avoir un CActionsMenu
   alloue!!!! sinon, je me pends !!*/
struct CObjActionnable {
  //private:
  CActionsMenu * actions; 

  void (* InputAndRenderActionMenu)(struct CObjActionnable * this);  
  void (* AjouterAction)(struct CObjActionnable * this, const char * caption, const char * nom_texture, const char * fichier_pascal, const char * proc);
};
DECLARE_NEW_OPERATOR_FOR_STRUCT(CObjActionnable);


#if 0
  //public:
  CObjActionnable(void);
  ~CObjActionnable(void);  

static void InputAndRenderActionMenu(struct CObjActionnable * this);  
static void AjouterAction(struct CObjActionnable * this, const char * caption, const char * nom_texture, const char * fichier_pascal, const char * proc);
#endif



#if 0


#include "ressource.h"

struct CMenuAbstrait;

#include "menu.h"




/*
  CScriptLauncher est une structe "limite abstraite" qui gere le lancement de script
  
  cl = new CScriptLauncher("dialogues.pml", "JeanPierreParle");
  cl -> Execute();
  
  delete cl;
*/
  

struct CScriptLauncher {
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
struct CActionsMenu : public CMenuAbstrait {    
  //public:
  bool InputAndRender(void);
};





extern void init_actions(void);
extern void free_actions(void);


#endif
#endif /* ACTION_H */
