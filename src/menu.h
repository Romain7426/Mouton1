#ifndef MENU_H
#define MENU_H
/*
  structe pour gérer des menus

  CMenuAbstrait: structe abstraite pour gérer les menus etc...
  CMenu: menu torique
  CMiniMenu: menu normal

  utilisation:
  - Dans Init, on le crée avec le constructeur en indiquant le nombre de sous-menus
  on fait des Add pour ajouter des éléments
    
  - Dans RaiseRender, on fait InputAndRender, qui renvoie vrai si
  le joueur a validé ou annulé quelquechose
  On récupère l'item sélectionné dans iphi et itheta... et iphi = -1 si
  le joueur a annulé
    
  - Rien ne nous empêche en cours de jeu de rajouter des éléments au menu
    
  - Dans Free, on pense à détruire le menu
*/

//#define NB_SOUS_MENU 7
//#define NB_ITEM_MAX 8 // nb d'item sur un anneau
enum { NB_SOUS_MENU = 7 }; 
enum { NB_ITEM_MAX = 12 }; 

// modifier ces constantes pour modifier la "rapidité du menu"
#define nb_pas_phi 8
#define nb_pas_theta 10

// les anneaux
#define ANNEAU_MENU_ARME 0
#define ANNEAU_MENU_OBJET 1
#define ANNEAU_MENU_MAGIE 2


/*******************************************************************************
  MENU ABSTRAIT
******************************************************************************/

// RL: Superfluous... 
// structure pour stocker un élément du menu 
struct MenuItem { 
  char     *     nom; //par convention nom = NULL ==> pas d'item !! 
  CTexture * texture; 
  void     *     qch; //pour stocker des choses (comme un ScriptLauncher) dans ActionMenu 
}; 
DEFINE_NEW_OPERATOR_FOR_STRUCT(MenuItem);
extern MenuItem * MenuItem_make(void); 
extern MenuItem * MenuItem_make_r(MenuItem * this); 
extern MenuItem * MenuItem_make_b(const int buffer_size, void * buffer); 
extern void       MenuItem_delete(MenuItem * this); 
extern MenuItem * MenuItem_copy_aux(MenuItem * this, const MenuItem * src); 




// RL: TODO XXX FIXME: For simple list menus, left key & right key do something... While they should not do so. (The menu disappears during the invisible animation.) 
struct CMenuAbstrait {
  int Action; // détermine le mode du menu (= rien, en train de tourner vers la gauche, tourner vers le haut...)
  int anim_theta[NB_SOUS_MENU];
  int anim_phi; // c'est pas le vrai indice de menu, mais un indice plus grand pour faire les animations
  
  struct MenuItem Items[NB_SOUS_MENU][NB_ITEM_MAX]; // RL: Items in each column. 
  
  /*ici, on récupère en sortie le numéro de sous-menu (iphi) et le numéro
    de l'élément sélectionné (itheta). Utile pour savoir quelle action faire
    après un choix dans un menu :)*/
  int iphi;  // RL: Current column 
  int itheta; // RL: Current row 
  bool Canceled; 
  
  char * NomSousMenu[NB_SOUS_MENU]; // RL: Column title 
  
  
  
  
  
  
  // *** METHODS *** 
  
  int (* ProchainIndice)(const struct CMenuAbstrait * this, const int ssMenu);      

      
  void (* Add)(struct CMenuAbstrait * this, int ssMenu, const char * nom, const char * nom_texture);
  /*ajoute un élément au menu... sur le sous-menu ssMenu
    (ssMenu doit être dans [0, NB_SOUS_MENU-1] sinon ça plante !)
    nom_texture est le nom de fichier d'une image
    ex : "./haricot.png"*/ 
    
  void (* Add_qch)(struct CMenuAbstrait * this, int ssMenu, const char * nom, const char * nom_texture, void * qch);
      
  //virtual bool InputAndRender(void);
  //bool (* InputAndRender)(struct CMenuAbstrait * this);
  int  (* Input)(struct CMenuAbstrait * this);
  void (* Life)(struct CMenuAbstrait * this);
  void (* Render)(const struct CMenuAbstrait * this);
  /*On appelle ça pour faire vivre le menu (dans RaiseRender)
    pour appeler cette fonction, il faut ABSOLUMENT que le menu ne soit pas vide
    (avoir au moins fait un appel de Add avant)
    sinon elle plante (à coup sûr)*/
 
};
extern CMenuAbstrait * CMenuAbstrait_make(void); 
extern void            CMenuAbstrait_delete(CMenuAbstrait * this);
extern CMenuAbstrait * CMenuAbstrait_make_aux(CMenuAbstrait * this); 
extern void            CMenuAbstrait_delete_aux(CMenuAbstrait * this); 
extern CMenuAbstrait * CMenuAbstrait_copy(const CMenuAbstrait * src); 
extern CMenuAbstrait * CMenuAbstrait_copy_aux(CMenuAbstrait * this, const CMenuAbstrait * src); 

extern int  CMenuAbstrait__ProchainIndice(const struct CMenuAbstrait * this, const int ssMenu);      
extern void CMenuAbstrait__Add(struct CMenuAbstrait * this, int ssMenu, const char * nom, const char * nom_texture);
extern void CMenuAbstrait__Add_qch(struct CMenuAbstrait * this, int ssMenu, const char * nom, const char * nom_texture, void * qch);
//extern bool CMenuAbstrait__InputAndRender(struct CMenuAbstrait * this);
extern int  CMenuAbstrait__Input(struct CMenuAbstrait * this);
extern void CMenuAbstrait__Life(struct CMenuAbstrait * this);
extern void CMenuAbstrait__Render(const struct CMenuAbstrait * this);




/*******************************************************************************
  MENU
******************************************************************************/
    
struct CMenu /* : public CMenuAbstrait */ {
  CMenuAbstrait parent;

  //virtual bool InputAndRender(void);
  //bool (* InputAndRender)(struct CMenu * this);
  int  (* Input)(struct CMenu * this);
  void (* Life)(struct CMenu * this);
  void (* Render)(const struct CMenu * this);
  /*On appelle ça pour faire vivre le menu (dans RaiseRender)
    pour appeler cette fonction, il faut ABSOLUMENT que le menu ne soit pas vide
    (avoir au moins fait un appel de Add avant)
    sinon elle plante (à coup sûr)*/      
};
extern CMenu * CMenu_make(void); 
extern CMenu * CMenu_make_aux(CMenu * this); 
extern void CMenu_delete(CMenu * this); 
extern void CMenu_delete_aux(CMenu * this); 
//extern bool CMenu__InputAndRender(CMenu * this);
extern int  CMenu__Input(CMenu * this);
extern void CMenu__Life(CMenu * this);
extern void CMenu__Render(const CMenu * this);
  



/*******************************************************************************
  MINIMENU
******************************************************************************/

struct CMiniMenu /* : public CMenuAbstrait */ {
  CMenuAbstrait parent;

  int X, Y, W;
  CTexture * Curseur;

  //bool (* InputAndRender)(struct CMiniMenu * this);
  int  (* Input)(struct CMiniMenu * this);
  void (* Render)(const struct CMiniMenu * this);
  void (* Life)(struct CMiniMenu * this);
};
//extern CMiniMenu * CMiniMenu_make0(void); 
extern CMiniMenu * CMiniMenu_make(const int X, const int Y, const int W); 
extern void CMiniMenu_delete(CMiniMenu * this); 
//extern bool CMiniMenu__InputAndRender(CMiniMenu * this);
extern int  CMiniMenu__Input(CMiniMenu * this);
extern void CMiniMenu__Life(CMiniMenu * this);
extern void CMiniMenu__Render(const CMiniMenu * this);

#endif /* MENU_H */
