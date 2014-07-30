#ifndef MENU_H
#define MENU_H

/*
  structe pour g�rer des menus

  CMenuAbstrait: structe abstraite pour g�rer les menus etc...
  CMenu: menu torique
  CMiniMenu: menu normal

  utilisation:
  - Dans Init, on le cr�e avec le constructeur en indiquant le nombre de sous-menus
  on fait des Add pour ajouter des �l�ments
    
  - Dans RaiseRender, on fait InputAndRender, qui renvoie vrai si
  le joueur a valid� ou annul� quelquechose
  On r�cup�re l'item s�lectionn� dans iphi et itheta... et iphi = -1 si
  le joueur a annul�
    
  - Rien ne nous emp�che en cours de jeu de rajouter des �l�ments au menu
    
  - Dans Free, on pense � d�truire le menu
*/

struct CTexture;



#define NB_SOUS_MENU 7
#define NB_ITEM_MAX 8 // nb d'item sur un anneau

// modifier ces constantes pour modifier la "rapidit� du menu"
#define nb_pas_phi 8
#define nb_pas_theta 10

// les anneaux
#define ANNEAU_MENU_ARME 0
#define ANNEAU_MENU_OBJET 1
#define ANNEAU_MENU_MAGIE 2




/*******************************************************************************
  MENU ABSTRAIT
******************************************************************************/

// structure pour stocker un �l�ment du menu
struct MenuItem {
  const char * nom; //par convention nom = NULL ==> pas d'item !!
  CTexture * texture;
  void * qch; //pour stocker des choses (comme un ScriptLauncher) dans ActionMenu
};    
TYPEDEF_TYPENAME_WITHOUT_STRUCT(MenuItem);
DEFINE_NEW_OPERATOR_FOR_STRUCT(MenuItem);

  
struct CMenuAbstrait {
  //protected:
  
  int Action; // d�termine le mode du menu (= rien, en train de tourner vers la gauche, tourner vers le haut...)
  
  int anim_theta[NB_SOUS_MENU];
  int anim_phi; // c'est pas le vrai indice de menu, mais un indice plus grand pour faire les animations
  
  MenuItem Items[NB_SOUS_MENU][NB_ITEM_MAX];
  
  /*ici, on r�cup�re en sortie le num�ro de sous-menu (iphi) et le num�ro
    de l'�l�ment s�lectionn� (itheta). Utile pour savoir quelle action faire
    apr�s un choix dans un menu :)*/
  int iphi;
  int itheta;
  bool Canceled;
  
  char * NomSousMenu[NB_SOUS_MENU];



  int (* ProchainIndice)(struct CMenuAbstrait * this, int ssMenu);      

    
  //public:
#if 0
  CMenuAbstrait(void); 
  virtual ~CMenuAbstrait(void);
#endif
      
  void (* Add1)(struct CMenuAbstrait * this, int ssMenu, const char * nom, const char * nom_texture);
  /*ajoute un �l�ment au menu... sur le sous-menu ssMenu
    (ssMenu doit �tre dans [0, NB_SOUS_MENU-1] sinon �a plante !)
    nom_texture est le nom de fichier d'une image
    ex : "./haricot.png"*/ 
    
  void (* Add2)(struct CMenuAbstrait * this, int ssMenu, const char * nom, const char * nom_texture, void * qch);
      
  //virtual bool InputAndRender(void);
  bool (* InputAndRender)(struct CMenuAbstrait * this);
  /*On appelle �a pour faire vivre le menu (dans RaiseRender)
    pour appeler cette fonction, il faut ABSOLUMENT que le menu ne soit pas vide
    (avoir au moins fait un appel de Add avant)
    sinon elle plante (� coup s�r)*/
 
};
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CMenuAbstrait);




/*******************************************************************************
  MENU
******************************************************************************/
    
struct CMenu /* : public CMenuAbstrait */ {
  CMenuAbstrait parent;

#if 0
  CMenu(void); /*on construit le menu*/
  ~CMenu(void) {}
#endif
  
  //virtual bool InputAndRender(void);
  bool (* InputAndRender)(struct CMenu * this);
  /*On appelle �a pour faire vivre le menu (dans RaiseRender)
    pour appeler cette fonction, il faut ABSOLUMENT que le menu ne soit pas vide
    (avoir au moins fait un appel de Add avant)
    sinon elle plante (� coup s�r)*/
      
};
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CMenu);




/*******************************************************************************
  MINIMENU
******************************************************************************/

struct CMiniMenu /* : public CMenuAbstrait */ {
  CMenuAbstrait parent;

  //private:
  int X, Y, W;
  CTexture * Curseur;
  
  //public:
#if 0
  CMiniMenu(int inX, int inY, int inW);
  ~CMiniMenu(void);
#endif
  
  bool (* InputAndRender)(struct CMiniMenu * this);
};
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CMiniMenu);


#endif /* MENU_H */
