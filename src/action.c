#include "global.h"
#include "action.h"
#include "text.h"
#include "script_api.h"

static CTexture * texAction1 = NULL;
static CTexture * texAction2 = NULL;
static CTexture * texAction3 = NULL;
//static CText    * Text       = NULL; //*(api_contexte.Text_ref); 


void init_actions(void) {
  texAction1 = CTexture_make("action/action1.png"); 
  texAction2 = CTexture_make("action/action2.png"); 
  texAction3 = CTexture_make("action/action3.png"); 
  //Text = CText_make(); 
};

void free_actions(void) { 
  //CText_delete(Text); 
  CTexture_delete(texAction1); 
  CTexture_delete(texAction2); 
  CTexture_delete(texAction3);    
}; 


static char * CopyString(const char * const filename) {
  //char* s = new char[strlen(filename)+1];
  if (filename == NULL) return NULL; 
  char * s = (char *) malloc((sizeof(char)) * (strlen(filename)+1));
  strcpy(s, filename);
  return s; 
}; 
 
CScriptLauncher * CScriptLauncher_make(const char * const filename, const char * const procedure_name) {
  //printf("Début Constructeur CScriptLauncher::CScriptLauncher(%s, %s)\n", filename, procedure_name);
  
  CScriptLauncher * this = NULL; 
  this = (CScriptLauncher *) malloc(sizeof(CScriptLauncher)); 
  bzero(this, sizeof(*this)); 
  
  //resPascal = gestionPascal.prendre(filename); 
  //char * newfilename = CopyString(filename); 
  //P = new CPascal(filename); 
  //this -> resPascal = gestionPascal.prendre(filename); 
  //this -> resPascal = new CPascal(filename); 
  if (filename != NULL && *filename != '\0') { 
    this -> resPascal = CPascal_make(filename); 
  }; 
  
  //printf("   cool on a capté la ressource pascal!!\n"); 
  this -> fichier = CopyString(filename); 
  this -> proc    = CopyString(procedure_name); 
  
  this -> Execute           = CScriptLauncher__Execute; 
  this -> init_step         = CScriptLauncher__init_step; 
  this -> execute_step      = CScriptLauncher__execute_step; 
  this -> stack_push_int    = CScriptLauncher__stack_push_int; 
  this -> stack_push_string = CScriptLauncher__stack_push_string; 
  
  
  //printf("Fin Constructeur CScriptLauncher\n"); 
  
  return this; 
}; 


void CScriptLauncher_delete(CScriptLauncher * this) {
  free(this -> proc); 
  free(this -> proc); 
  if (this -> resPascal != NULL) CPascal_delete(this -> resPascal); 
}; 

void CScriptLauncher__Execute(CScriptLauncher * this) { 
  //printf("Exécution du ScriptLauncher..."); 
  SCRIPT_Init(); 
  //printf("      on va executer la procédure %s...\n", this -> proc); 
  //this -> resPascal->getObject()->execProcedure(proc); 
  this -> resPascal -> execProcedure(this -> resPascal, this -> proc); 
  //P->execProcedure(proc); 
  //printf("      fin de l'exécution\n"); 
  SCRIPT_Quit(); 
  //printf("      Exécution du ScriptLauncher réussie!!!");   
};

void CScriptLauncher__init_step(CScriptLauncher * this) {
  message("%s" "\n", __func__); 
  SCRIPT_Init();

  this -> resPascal -> execProcedure_step(this -> resPascal, this -> proc);
};

bool CScriptLauncher__execute_step(CScriptLauncher * this) { 
  //message("%s" "\n", __func__); 
  bool fini_huh; 
  int ret; 
  
  ret = this -> resPascal -> next_step(this -> resPascal, &fini_huh); 
  
  //message("%s: " "ret = %d ; fini_huh = %d " "\n", __func__, ret, fini_huh); 
  
  return (fini_huh || ret != 0); 
};

void CScriptLauncher__stack_push_int(CScriptLauncher * this, int a) {
  this -> resPascal -> stack_push_int(this -> resPascal, a);
};

void CScriptLauncher__stack_push_string(CScriptLauncher * this, const char * str) {
  this -> resPascal -> stack_push_string(this -> resPascal, str);
};





CActionsMenu * CActionsMenu_make(void) {
  MALLOC_BZERO(CActionsMenu,this); 
  //this -> InputAndRender = CActionsMenu__InputAndRender; 
  this -> Input  = CActionsMenu__Input; 
  this -> Render = CActionsMenu__Render; 
  this -> Life   = CActionsMenu__Life; 
  CMenuAbstrait_make_aux(&this -> parent); 
  return this; 
}; 

void CActionsMenu_delete(CActionsMenu * this) {
  CMenuAbstrait_delete_aux(&this -> parent); 
  free(this); 
}; 

CActionsMenu * CActionsMenu_copy(const CActionsMenu * src) {
  MALLOC_BZERO(CActionsMenu,this); 
  *this = *src; 
  CMenuAbstrait_copy_aux(&this -> parent, &src -> parent); 
  return this; 
}; 

//bool CActionsMenu__InputAndRender(CActionsMenu * this) { 
int CActionsMenu__Input(CActionsMenu * this) { 
  //MenuItem (* Items)[7][8] = &this -> parent.Items; 
  //MenuItem (* Items)[8] = this -> parent.Items; 
  MenuItem (* Items)[NB_ITEM_MAX] = this -> parent.Items; 
  //MenuItem * * Items = this -> parent.Items; 
  //MenuItem * * Items = &this -> parent.Items[0]; 
  //MenuItem * * Items = &this -> parent.Items[0][0]; 

    
    if (KEY_ACTION1) { 
      CScriptLauncher * c = Items[0][0 /*action n° 1 - 1*/].qch; 
#if 1 
      if (NULL != c) { 
	Kernel_Script_Start(c -> fichier, c -> proc); 
      }; 
#else 
      if (NULL != c) { 
	if (c -> resPascal != NULL) { 
	  c -> Execute(c); 
	} 
	else { 
	  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " SCRIPT_C = '%s' "   "\n", __func__, c -> proc); 
	  Kernel_Script_Start("", c -> proc); 
	}; 
      }; 
#endif 
    }; 
    
    if(KEY_ACTION2) {
      CScriptLauncher * c = (CScriptLauncher *) (Items[0][1 /*action n° 2 - 1*/].qch); 
#if 1 
      if (NULL != c) { 
	Kernel_Script_Start(c -> fichier, c -> proc); 
      }; 
#else 
      if (NULL != c) { 
	if (c -> resPascal != NULL) { 
	  c -> Execute(c); 
	} 
	else { 
	  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " SCRIPT_C = '%s' "   "\n", __func__, c -> proc); 
	  Kernel_Script_Start("", c -> proc); 
	}; 
      }; 
#endif 
    }; 
    
    if(KEY_ACTION3) { 
      CScriptLauncher * c = (CScriptLauncher *) (Items[0][2 /*action n° 3 - 1*/].qch); 
#if 1 
      if (NULL != c) { 
	Kernel_Script_Start(c -> fichier, c -> proc); 
      }; 
#else 
      if (NULL != c) { 
	if (c -> resPascal != NULL) { 
	  c -> Execute(c); 
	} 
	else { 
	  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " SCRIPT_C = '%s' "   "\n", __func__, c -> proc); 
	  Kernel_Script_Start("", c -> proc); 
	}; 
      }; 
#endif 
    }; 
  
  
  return false;
}; 

void CActionsMenu__Life(CActionsMenu * this) { 
}; 

void CActionsMenu__Render(const CActionsMenu * this) { 
  //MenuItem (* Items)[7][8] = &this -> parent.Items; 
  //MenuItem (* Items)[8] = this -> parent.Items; 
  const MenuItem (* Items)[NB_ITEM_MAX] = this -> parent.Items; 
  //MenuItem * * Items = this -> parent.Items; 
  //MenuItem * * Items = &this -> parent.Items[0]; 
  //MenuItem * * Items = &this -> parent.Items[0][0]; 

  //CText * Text = *(api_contexte.Text_ref); 

  glEnable2D(); { 
    int i = 0; //iphi = 0  
#define NB_PIXEL_HAUTEUR_LIGNE 32.0f
#define NB_PIXEL_DECAL_X 20
    // on parcourt les items du sous-menus
    const int num_item_max = this -> parent.ProchainIndice(&this -> parent, i);
    for (int j = 0; j < num_item_max; j++) {
#define yy ACTIONS_MENU_Y - (int) (j*NB_PIXEL_HAUTEUR_LIGNE)
#define xx ACTIONS_MENU_X+j*NB_PIXEL_DECAL_X
      Text -> print1(Text, xx+40, yy, 1000,1000, Items[i][j].nom);
      
      if (Items[i][j].texture != NULL) {
	glEnable(GL_TEXTURE_2D);
	Items[i][j].texture -> GLTextureCourante(Items[i][j].texture);
	
	BEGIN_BLIT_END(xx, yy, 32,32, 0.0f, 0.0f, 1.0f, 1.0f);
      } 
      else {
	switch(j) {
	case 0: texAction1 -> GLTextureCourante(texAction1);  break;       
	case 1: texAction2 -> GLTextureCourante(texAction2);  break;      
	case 2: texAction3 -> GLTextureCourante(texAction3);  break;      
	default: assert(false);
	}; 
	BEGIN_BLIT_END(xx, yy, 32,32, 0.0f, 0.0f, 1.0f, 1.0f);
      }; 
      
    }; 
    
  } glDisable2D();
  
}; 



CObjActionnable * CObjActionnable_make_aux(CObjActionnable * this) { 
  //this -> InputAndRenderActionMenu = CObjActionnable__InputAndRenderActionMenu; 
  this -> ActionMenu_Input  = CObjActionnable__ActionMenu_Input; 
  this -> ActionMenu_Render = CObjActionnable__ActionMenu_Render; 
  this -> ActionMenu_Life   = CObjActionnable__ActionMenu_Life; 
  this -> AjouterAction     = CObjActionnable__AjouterAction; 
  this -> actions = NULL; 
  return this; 
}; 

CObjActionnable * CObjActionnable_make(void) { 
  CObjActionnable * this = NULL; 
  this = (CObjActionnable *) malloc(sizeof(CObjActionnable)); 
  return CObjActionnable_make_aux(this); 
}; 
/*pourquoi ne pas allouer actions ????
  parce que si un objet n'a pas d'actions, c'est débile de gaspiller de la mémoire
  Si tous les arbres de la carte avaient leur menu d'actions alloué, ça
  serait la fin du monde*/

 
CObjActionnable * CObjActionnable_copy_aux(CObjActionnable * this, const CObjActionnable * src) {
  *this = *src;
  if (src -> actions != NULL) {
    this -> actions = CActionsMenu_copy(src -> actions); 
  }; 
  return this;
}; 

CObjActionnable * CObjActionnable_copy(const CObjActionnable * src) {
  MALLOC_BZERO(CObjActionnable,this); 
  return CObjActionnable_copy_aux(this, src); 
}; 
 

 
void CObjActionnable_delete_aux(CObjActionnable * this) {
  if (this -> actions != NULL) {
    CActionsMenu_delete(this -> actions); 
  };
}; 
 
void CObjActionnable_delete(CObjActionnable * this) {
  CObjActionnable_delete_aux(this);
  free(this); 
}; 
 
int CObjActionnable__ActionMenu_Input(CObjActionnable * this) {
  if (this -> actions != NULL)
    return this -> actions -> Input(this -> actions); 
  return 0; 
};

void CObjActionnable__ActionMenu_Life(CObjActionnable * this) {
  if (this -> actions != NULL)
    this -> actions -> Life(this -> actions); 
};

void CObjActionnable__ActionMenu_Render(const CObjActionnable * this) {
  if (this -> actions != NULL)
    this -> actions -> Render(this -> actions); 
};

void CObjActionnable__AjouterAction(CObjActionnable * this, const char * caption, const char * nom_texture, const char * fichier_pascal, const char * proc) { 
  // FS: /*spécification d'entrée : si nom_texture == NULL ou nom_texture == "" alors il n'y a pas de textures*/ 
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " this = %p, caption = '%s', nom_texture = '%s', fichier_pascal = '%s', proc ='%s' "  "\n", __func__, this, caption, nom_texture, fichier_pascal, proc); 
  
  //printf("CObjActionnable__AjouterAction(...)\n"); 
  if (this -> actions == NULL) { 
    //printf("Pour ajouter l'action, je dois d'abord créer un menu pour l'accueillir.\n"); 
    this -> actions = CActionsMenu_make(); 
    //printf("     Création du menu action réussi : pointeur = %p\n", this -> actions); 
  }; 
  
  CScriptLauncher * sl = CScriptLauncher_make(fichier_pascal, proc); 
  if (fichier_pascal == NULL || *fichier_pascal == '\0') { 
    if (sl -> resPascal != NULL) CPascal_delete(sl -> resPascal); 
    sl -> resPascal = NULL; 
  }; 

  CMenuAbstrait * m = &this -> actions -> parent; 
  m -> Add_qch(m, /*ssMenu*/0, caption, nom_texture, sl); 
  //printf("     Action ajoutée !!!\n"); 
}; 


