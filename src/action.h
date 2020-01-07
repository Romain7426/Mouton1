#ifndef ACTION_H
#define ACTION_H

/* cette structe gère un CActionsMenu à l'intérieur éventuellement NULL
   (pour éviter de saturer la mémoire avec un objet alloue qui sert à rien
   ex : les arbres de toute la carte ne vont pas chacun avoir un CActionsMenu
   alloue!!!! sinon, je me pends !!*/
struct CObjActionnable {
  CActionsMenu * actions; 
  
  void (* InputAndRenderActionMenu)(struct CObjActionnable * this);  
  void (* AjouterAction)(struct CObjActionnable * this, const char * caption, const char * nom_texture, const char * fichier_pascal, const char * proc);
};

extern CObjActionnable * CObjActionnable_make(void);
extern CObjActionnable * CObjActionnable_make_aux(CObjActionnable * this);
extern void CObjActionnable_delete(CObjActionnable * this); 
extern void CObjActionnable_delete_aux(CObjActionnable * this); 
extern CObjActionnable * CObjActionnable_copy(const CObjActionnable * src);
extern CObjActionnable * CObjActionnable_copy_aux(CObjActionnable * this, const CObjActionnable * src);
extern void CObjActionnable__InputAndRenderActionMenu(struct CObjActionnable * this); 
extern void CObjActionnable__AjouterAction(struct CObjActionnable * this, const char * caption, const char * nom_texture, const char * fichier_pascal, const char * proc);




/*
  CScriptLauncher est une structe "limite abstraite" qui gere le lancement de script
  
  cl = new CScriptLauncher("dialogues.pml", "JeanPierreParle");
  cl -> Execute();
  
  delete cl;
*/
  

struct CScriptLauncher {
  char * proc;
  CPascal * resPascal;
  
  void (* Execute)(CScriptLauncher * this);
  void (* init_step)(CScriptLauncher * this);
  bool (* execute_step)(CScriptLauncher * this);
  void (* stack_push_int)(CScriptLauncher * this, int a);
  void (* stack_push_string)(CScriptLauncher * this, const char * str);
};
extern CScriptLauncher * CScriptLauncher_make(const char * const filename, const char * const procedure_name);
extern void CScriptLauncher_delete(CScriptLauncher * this);
extern void CScriptLauncher__Execute(CScriptLauncher * this);
extern void CScriptLauncher__init_step(CScriptLauncher * this);
extern bool CScriptLauncher__execute_step(CScriptLauncher * this);
extern void CScriptLauncher__stack_push_int(CScriptLauncher * this, int a);
extern void CScriptLauncher__stack_push_string(CScriptLauncher * this, const char * str);

enum { ACTIONS_MENU_X = 100, ACTIONS_MENU_Y = 400 };

// CActionsMenu c'est un menu qui gere legerement plus les actions
struct CActionsMenu /* : public CMenuAbstrait */ {    
  CMenuAbstrait parent; 
  bool (* InputAndRender)(CActionsMenu * this);
};
extern bool CActionsMenu__InputAndRender(CActionsMenu * this); 
extern CActionsMenu * CActionsMenu_make(void); 
extern void CActionsMenu_delete(CActionsMenu * this); 
extern CActionsMenu * CActionsMenu_copy(const CActionsMenu * src); 




extern void init_actions(void);
extern void free_actions(void);

#if 0


#include "ressource.h"

struct CMenuAbstrait;

#include "menu.h"











// CActionsMenu c'est un menu qui gere legerement plus les actions
struct CActionsMenu { 
  CMenuAbstrait parent; 
  bool InputAndRender(void); 
};







#endif
#endif /* ACTION_H */
