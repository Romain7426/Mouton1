#include "global.hpp"
#include "text.hpp"
#include "action.hpp"
#include "apiscript.hpp"

CTexture * texAction1 = NULL;
CTexture * texAction2 = NULL;
CTexture * texAction3 = NULL;

void init_actions(void) {
  texAction1 = new CTexture("action/action1.png");
  texAction2 = new CTexture("action/action2.png");
  texAction3 = new CTexture("action/action3.png");   
};


void free_actions(void) {
  delete texAction1;
  delete texAction2;
  delete texAction3;    
};


static char * CopyString(const char * const filename) {
  char* s = new char[strlen(filename)+1];
  strcpy(s, filename);
  
  return s; 
}

CScriptLauncher::CScriptLauncher(const char * const filename, const char * const procedure_name) {
  printf("Début Constructeur CScriptLauncher::CScriptLauncher(%s, %s)\n", filename, procedure_name);
  //resPascal = gestionPascal.prendre(filename);
  //char * newfilename = CopyString(filename);
  //P = new CPascal(filename);
  resPascal = gestionPascal.prendre(filename);
  
  printf("   cool on a capté la ressource pascal!!\n");
  proc = CopyString(procedure_name);


  printf("Fin Constructeur CScriptLauncher\n");             

}


CScriptLauncher::~CScriptLauncher(void) {
  //delete resPascal;                               
}

void CScriptLauncher::Execute(void) {
  printf("Exécution du ScriptLauncher...");   
  SCRIPT_Init();
  printf("      on va executer la procédure %s...\n", proc);
  resPascal->getObject()->execProcedure(proc);
  //P->execProcedure(proc);
  printf("      fin de l'exécution\n");
  SCRIPT_Quit();
  printf("      Exécution du ScriptLauncher réussie!!!");   
}

void CScriptLauncher::init_step(void) {
  SCRIPT_Init();

  resPascal->getObject()->execProcedure_step(proc);
}

bool CScriptLauncher::execute_step(void) {
  bool fini_huh;
  int ret;

  ret = resPascal->getObject()->next_step(fini_huh);

  return (fini_huh || ret != 0);
}

void CScriptLauncher::stack_push_int(int a) {
  resPascal->getObject()->stack_push_int(a);
}

void CScriptLauncher::stack_push_string(const char * str) {
  resPascal->getObject()->stack_push_string(str);
}






bool CActionsMenu::InputAndRender(void) {
  glEnable2D();   
  int i = 0; //iphi = 0  
#define NB_PIXEL_HAUTEUR_LIGNE 32.0f
#define NB_PIXEL_DECAL_X 20
  // on parcourt les items du sous-menus
  int num_item_max = ProchainIndice(i);
  for (int j = 0; j < num_item_max; j++) {
#define  yy ACTIONS_MENU_Y - (int) (j*NB_PIXEL_HAUTEUR_LIGNE)
#define xx ACTIONS_MENU_X+j*NB_PIXEL_DECAL_X
    Text->print(xx+40, yy, 1000,1000,Items[i][j].nom);
                    
    if(Items[i][j].texture != NULL)
      {
        glEnable(GL_TEXTURE_2D);
        Items[i][j].texture->GLTextureCourante();
   
        BEGIN_BLIT_END(xx, yy, 32,32, 0.0f, 0.0f, 1.0f, 1.0f);
      } 
    else
      {
        switch(j) {
        case 0: texAction1->GLTextureCourante();  break;       
        case 1: texAction2->GLTextureCourante();  break;      
        case 2: texAction3->GLTextureCourante();  break;      
        default: assert(false);
        }
        BEGIN_BLIT_END(xx, yy, 32,32, 0.0f, 0.0f, 1.0f, 1.0f);
      }
                
  }   
    
    
  if(KEY_ACTION1)
    ((CScriptLauncher*) (Items[0][0 /*action n° 1 - 1*/].qch))->Execute();
         
  if(KEY_ACTION2)
    if (CScriptLauncher* c = (CScriptLauncher*) (Items[0][1 /*action n° 2 - 1*/].qch))
      c->Execute();
  if(KEY_ACTION3)
    if (CScriptLauncher*c = (CScriptLauncher*) (Items[0][2 /*action n° 3 - 1*/].qch))
      c->Execute();

  glDisable2D();
        
     
  return false;
}




CObjActionnable::CObjActionnable() : actions(NULL) {}
/*pourquoi ne pas allouer actions ????
  parce que si un objet n'a pas d'actions, c'est débile de gaspiller de la mémoire
  Si tous les arbres de la carte avaient leur menu d'actions alloué, ça
  serait la fin du monde*/
 
 
CObjActionnable::~CObjActionnable()
{
  delete actions; /*rem : delete NULL ça marche*/                                   
                                   
}
 
 
void CObjActionnable::InputAndRenderActionMenu()
{
  if(actions!= NULL)
    actions->InputAndRender();
     
}

void CObjActionnable::AjouterAction(const char * caption,
                                    const char * nom_texture,
                                    const char * fichier_pascal,
                                    const char * proc)
/*spécification d'entrée : si nom_texture == NULL ou nom_texture == "" alors 
  il n'y a pas de textures*/
{
  printf("CObjActionnable::CObjActionnable(...)\n");       
  if(actions == NULL) {
    printf("Pour ajouter l'action, je dois d'abord créer un menu pour l'accueillir.\n");           
    actions = new CActionsMenu();
    printf("     Création du menu action réussi : pointeur = %p\n", actions); 
  }
  
  /*  printf("     Cré");         
      CPascal* P = new CPascal( fichier_pascal);
      printf("     aze");*/
  
  CScriptLauncher * sl = new CScriptLauncher(fichier_pascal, proc);
  actions->Add(0, caption, nom_texture, sl);    
  printf("     Action ajoutée !!!\n");        
                   
}


