#include "global.h"
#include "menu.h"
#include "text.h"


MenuItem * MenuItem_make(void) {
  MALLOC_BZERO(MenuItem,this);
  return this; 
}; 

void MenuItem_delete_aux(MenuItem * this) {
  if (this -> nom != NULL) free(this -> nom); 
  if (this -> texture != NULL) CTexture_delete(this -> texture); 
  free(this); 
}; 

void MenuItem_delete(MenuItem * this) {
  MenuItem_delete_aux(this); 
  free(this); 
}; 

MenuItem * MenuItem_copy_aux(MenuItem * this, const MenuItem * src) {
  *this = *src; 
  if (src -> nom != NULL) this -> nom = strcopy(src -> nom); 
  if (src -> texture != NULL) this -> texture = CTexture_copy(src -> texture); 
  return this; 
}; 



/*******************************************************************************
  MENU ABSTRAIT
******************************************************************************/

CMenuAbstrait * CMenuAbstrait_make_aux(CMenuAbstrait * this) {  
  ASSIGN_METHOD(CMenuAbstrait,this,ProchainIndice); 
  ASSIGN_METHOD(CMenuAbstrait,this,Add); 
  ASSIGN_METHOD(CMenuAbstrait,this,Add_qch); 
  ASSIGN_METHOD(CMenuAbstrait,this,InputAndRender); 

  printf("Création du menu 'abstrait'...\n");
  this -> iphi = 0;
  this -> Action = 0;
  this -> anim_phi = 0;

  for (int i = 0; i < NB_SOUS_MENU; i++) {
    this -> NomSousMenu[i] = NULL;
    for (int j = 0; j < NB_ITEM_MAX; j++) {
      this -> Items[i][j].nom = NULL;  
      this -> Items[i][j].qch = NULL;   
    }
    this -> anim_theta[i] = 0;        
  };  
  
  return this; 
};  

CMenuAbstrait * CMenuAbstrait_make(void) {  
  MALLOC_BZERO(CMenuAbstrait,this);
  CMenuAbstrait_make_aux(this); 
  return this; 
}; 

void CMenuAbstrait_delete_aux(CMenuAbstrait * this) {
  for (int i = 0; i < NB_SOUS_MENU; i++) {
    for (int j = 0; j < NB_ITEM_MAX; j++) {
      MenuItem_delete_aux(&this -> Items[i][j]); 
    }
  };
  for (int i = 0; i < NB_SOUS_MENU; i++) {
    if (NULL != this -> NomSousMenu[i]) free(this -> NomSousMenu[i]);
  };   
};

void CMenuAbstrait_delete(CMenuAbstrait * this) {
  CMenuAbstrait_delete_aux(this); 
  free(this); 
}; 

CMenuAbstrait * CMenuAbstrait_copy_aux(CMenuAbstrait * this, const CMenuAbstrait * src) {
  *this = *src; 
  for (int i = 0; i < NB_SOUS_MENU; i++) {
    if (NULL != this -> NomSousMenu[i]) this -> NomSousMenu[i] = strcopy(src -> NomSousMenu[i]); 
  };   
  for (int i = 0; i < NB_SOUS_MENU; i++) {
    for (int j = 0; j < NB_ITEM_MAX; j++) {
      MenuItem_copy_aux(&this -> Items[i][j], &src -> Items[i][j]); 
    };
  };
  return this; 
}; 

CMenuAbstrait * CMenuAbstrait_copy(const CMenuAbstrait * src) {
  MALLOC_BZERO(CMenuAbstrait,this);
  return CMenuAbstrait_copy_aux(this, src); 
}; 



int CMenuAbstrait__ProchainIndice(CMenuAbstrait * this, int ssMenu) {
  /*ProchainIndice représente le prochain indice pour un nouvel
    élément dans le sous-menu ssMenu. Il représente aussi le nombre 
    d'élément dans ce sous-menu*/
  int j = 0;
  for (; (j<NB_ITEM_MAX) && (this -> Items[ssMenu][j].nom != NULL); j++) {};
  return j;
}    


void CMenuAbstrait__Add(CMenuAbstrait * this, int ssMenu, const char * nom, const char * nom_texture) {
  // si nom_texture == NULL, l'élément ajouté n'a pas d'icône
  this -> Add_qch(this, ssMenu, nom, nom_texture, NULL);
}  


void CMenuAbstrait__Add_qch(CMenuAbstrait * this, int ssMenu, const char * nom, const char * nom_texture, void * qch) {
  // si nom_texture == NULL ou "", l'élément ajouté n'a pas d'icône
  int j = this -> ProchainIndice(this, ssMenu);
  this -> Items[ssMenu][j].nom = strcopy(nom);
  
  if (nom_texture == NULL)
    this -> Items[ssMenu][j].texture = NULL;
  else if (nom_texture[0] == 0) 
    this -> Items[ssMenu][j].texture = NULL;
  else 
    this -> Items[ssMenu][j].texture = CTexture_make(nom_texture);
      
  this -> Items[ssMenu][j].qch = qch;
};   


bool CMenuAbstrait__InputAndRender(CMenuAbstrait * this) {
#define R 1.0f
#define a 0.8f
  this -> Canceled = false;

#define THETA_TEST						\
  if (this -> anim_theta[this -> iphi] % nb_pas_theta == 0)     \
    {this -> Action = 0;}
  
#define PHI_TEST                                                        \
  this -> iphi = this -> anim_phi / nb_pas_phi;				\
  printf("Ecart entre phi et iphi : %i\n",this -> anim_phi % nb_pas_phi); \
  if (((this -> anim_phi % nb_pas_phi) == 0) && (this -> ProchainIndice(this, this -> iphi)>0))	\
    {this -> Action = 0;						\
      printf("C'est bon on est sur iphi = %i\n", this -> iphi); ;}
  
#define DEC_THETA 1
#define INC_THETA 2
#define DEC_PHI 3
#define INC_PHI 4
#define ENTRER_MENU 5
#define ANNULER_MENU 6


#define RAMENER_MODULO(iphi, max)                                       \
  if (iphi >= (max)) iphi -= (max); else if (iphi < 0) iphi += (max);

  if (this -> Action == 0) {
    // on traite les entrées clavier que si on ne fait rien dans le menu

    if (this -> ProchainIndice(this, this -> iphi) != 1) {
      // on ne fait tourner en théta que s'il y a plus de 1 élément
      if (KEY_UP) this -> Action = DEC_THETA;
      if (KEY_DOWN) this -> Action = INC_THETA;
    }  

    if (KEY_LEFT) this -> Action = DEC_PHI;
    if (KEY_RIGHT) this -> Action = INC_PHI;
           
    if (KEY_MENU_VALIDER)          
      return true;

    if (KEY_MENU_ECHAP) {
      this -> Canceled = true;       
      return true;         
    }
    
  }


  if (this -> Action == DEC_THETA) {
    this -> anim_theta[this -> iphi] --;
    RAMENER_MODULO(this -> anim_theta[this -> iphi], nb_pas_theta*this -> ProchainIndice(this, this -> iphi));   
    THETA_TEST;
  }    
    
  if (this -> Action == INC_THETA) {
    this -> anim_theta[this -> iphi] ++;
    RAMENER_MODULO(this -> anim_theta[this -> iphi], nb_pas_theta*this -> ProchainIndice(this, this -> iphi));   
    THETA_TEST;
  }    
       
  if (this -> Action == DEC_PHI) {
    this -> anim_phi--;   
    RAMENER_MODULO(this -> anim_phi, NB_SOUS_MENU * nb_pas_phi);
    RAMENER_MODULO(this -> iphi, NB_SOUS_MENU);
    PHI_TEST;
  }    
    
  if (this -> Action == INC_PHI) {
    this -> anim_phi++;  
    RAMENER_MODULO(this -> anim_phi, NB_SOUS_MENU * nb_pas_phi); 
    RAMENER_MODULO(this -> iphi, NB_SOUS_MENU);
    PHI_TEST;
  }    
    
  this -> itheta = this -> anim_theta[this -> iphi] / nb_pas_theta;
  
  return false;
};





/*******************************************************************************
  MENU
******************************************************************************/

CMenu * CMenu_make_aux(CMenu * this) {
  CMenuAbstrait_make_aux(&this -> parent); 
  
  ASSIGN_METHOD(CMenu,this,InputAndRender); 
  
  return this; 
};

CMenu * CMenu_make(void) {
  MALLOC_BZERO(CMenu,this);
  return CMenu_make_aux(this);
};

void CMenu_delete_aux(CMenu * this) {
  CMenuAbstrait_delete_aux(&this -> parent); 
}; 

void CMenu_delete(CMenu * this) {
  CMenu_delete_aux(this); 
  free(this); 
}; 
 
bool CMenu__InputAndRender(CMenu * this) {
  CMenuAbstrait * parent = &this -> parent; 
  bool b = parent -> InputAndRender(parent); 
  
  glDisable(GL_CULL_FACE);  
  printf("gougou\n"); 
  /* Clear the color and depth buffers. */
  glClear(GL_DEPTH_BUFFER_BIT);

  glDisable(GL_LIGHTING);
  /* We don't want to modify the projection matrix. */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity( );
    
  gluLookAt(3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 1);

#define tailleb 0.0f
#define tailleh 0.2f
#define taillex 0.2f

  //printf("gougou après input\n");
    
    
  /******dessin du tore central (pour faire joli)*******/
     
  
#define MENU_nb_phi 30.0f
#define MENU_nb_theta 25.0f
#define a2 a/2.0f   
#define a22 a/1.1f  

#define tore(i, j)                                                      \
  glVertex3f( (R+a2  *cosf((float)2*PI*(j)/MENU_nb_theta) ) * cosf((float)2*PI*(i)/MENU_nb_phi), \   (R+(a2) *cosf((float)2*PI*(j)/MENU_nb_theta) ) * sinf((float)2*PI*(i)/MENU_nb_phi), \   (a2) *sinf((float)2*PI*(j)/MENU_nb_theta) );
       
  glColor4f(1.0f,1.0f,0.5f,0.2f);
  glDisable(GL_TEXTURE_2D);
    
  printf("para\n"); 
  /*les parallèles*/
  for (int j = 0; j<=MENU_nb_theta; j++) {
    glBegin(GL_LINE_STRIP); {
      float cj = cosf((float)2*PI*(j)/MENU_nb_theta);
      float sj = sinf((float)2*PI*(j)/MENU_nb_theta);
      for (int i = 0; i<=MENU_nb_phi; i++)
        glVertex3f( (R + a2*cj)*cosf((float)2*PI*(i)/MENU_nb_phi),       (R + a2*cj) * sinf((float)2*PI*(i)/MENU_nb_phi),        a2*sj);
    } glEnd();
        
  }
  
  
  printf("minian\n"); 
  
  /*les mini-anneaux*/
  for (int i = 0; i<=MENU_nb_phi; i++) {
    float ci = cosf((float)2*PI*(i)/MENU_nb_phi);
    float si = sinf((float)2*PI*(i)/MENU_nb_phi);

    glBegin(GL_LINE_STRIP);
    for (int j = 0; j<=MENU_nb_theta; j++)
      glVertex3f( (R+a2  *cosf((float)2*PI*(j)/MENU_nb_theta) ) * ci,        (R+(a2) *cosf((float)2*PI*(j)/MENU_nb_theta) ) * si,        (a2) *sinf((float)2*PI*(j)/MENU_nb_theta) ); 
    glEnd();             

  } 
  glEnable (GL_TEXTURE_2D); 
  glColor4f(1.0f,1.0f,1.0f,1.0f);  
    
  printf("itesms\n"); 
       
         
  /*on affiche les items ...*/   
  for (int i = 0; i<NB_SOUS_MENU; i++) {
    int num_item_max = parent -> ProchainIndice(parent, i); /*nb d'item sur l'anneau n° i*/
        
    float phi = (float) parent -> anim_phi / nb_pas_phi;
    float ci = cosf(2*PI*(i-phi)/NB_SOUS_MENU);
    float si = sinf(2*PI*(i-phi)/NB_SOUS_MENU);
      
    /*dessin d'un cercle*/
    if (num_item_max)
      {
        glColor4f(1.0f,1.0f,0.0f,0.4f);      
        glDisable(GL_TEXTURE_2D);
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j<=MENU_nb_theta; j++)
          glVertex3f( (R+a22  *cosf((float)2*PI*(j)/MENU_nb_theta) ) * ci,            (R+(a22) *cosf((float)2*PI*(j)/MENU_nb_theta) ) * si,            (a22) *sinf((float)2*PI*(j)/MENU_nb_theta) );         
        glEnd();      
        glEnable( GL_TEXTURE_2D);      
        glColor4f(1.0f,1.0f,1.0f,1.0f); 
      }     
         
    /*on parcourt les items*/            
    for (int j = 0; j < num_item_max; j++) {
      if (parent -> Items[i][j].texture == NULL)
        glDisable(GL_TEXTURE_2D);
      else {
        glEnable(GL_TEXTURE_2D);
        parent -> Items[i][j].texture -> GLTextureCourante(parent -> Items[i][j].texture);
      }      
      float theta = (float) parent -> anim_theta[i] / nb_pas_theta;        
      float cj = cosf(2*PI*(j-theta)/num_item_max);
      float sj = sinf(2*PI*(j-theta)/num_item_max);                                                 
      glPushMatrix() ;      
      glTranslatef( (R + a *cj) *ci, //on place la sprite sur le point du tore
                    (R+a*cj) * si,          a *sj ) ; 
      glRotatef(360.f*(float)(i-phi)/NB_SOUS_MENU,0,0,1) ; //on la pivote autour de (Oz)
      glRotatef(-360.f*((float)(j-theta)/num_item_max),0,1,0) ; //puis on la met par terre                      
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 1.0f); //en bas, à gauche
      glVertex3f(0,-taillex,tailleb);
        
      glTexCoord2f(1.0f, 1.0f); //en bas, à droite
      glVertex3f(0,taillex,tailleb);
        
      glTexCoord2f(1.0f, 0.0f); //en haut, à droite
      glVertex3f(0,taillex,tailleh);
        
      glTexCoord2f(0.0f, 0.0f); //en haut, à gauche
      glVertex3f(0,-taillex,tailleh);
      glEnd() ;
      glPopMatrix(); 
    }   
  }     
    
  printf("gougouavant texte\n");  
  Text -> print1(Text, 100,SCREEN_HEIGHT-50,10000,100, parent -> NomSousMenu[parent -> iphi]);
  Text -> print1(Text, 100,50,10000,100,parent -> Items[parent -> iphi][parent -> itheta].nom);
    
  glEnable(GL_LIGHTING);
    
  printf("gougoufin\n");  
    
  return b;
  glEnable(GL_CULL_FACE); 
}    









/*******************************************************************************
  MINIMENU
******************************************************************************/
  
CMiniMenu * CMiniMenu_make(const int inX, const int inY, const int inW) {
  MALLOC_BZERO(CMiniMenu,this);
  
  CMenuAbstrait_make_aux(&this -> parent); 
  
  ASSIGN_METHOD(CMiniMenu,this,InputAndRender); 

  this -> X = inX; 
  this -> Y = inY; 
  this -> W = inW; 
  this -> Curseur = CTexture_make("curseur.png");
  
  return this; 
}; 

void CMiniMenu_delete_aux(CMiniMenu * this) {
  CTexture_delete(this -> Curseur); 
  CMenuAbstrait_delete_aux(&this -> parent); 
}; 

void CMiniMenu_delete(CMiniMenu * this) {
  CMiniMenu_delete_aux(this);
  free(this); 
}; 

bool CMiniMenu__InputAndRender(CMiniMenu * this) {
  CMenuAbstrait * parent = &this -> parent; 
  bool b = parent -> InputAndRender(parent); 
  
  glEnable2D(); {
    int i = parent -> iphi;
#define NB_PIXEL_HAUTEUR_LIGNE 32.0f
    /*on parcourt les items du sous-menus*/
    int num_item_max = parent -> ProchainIndice(parent, i);
    for (int j = 0; j < num_item_max; j++) {
#define  yy this->Y - (int) (j*NB_PIXEL_HAUTEUR_LIGNE)
      Text -> print1(Text, this -> X+40, yy, 1000, 1000, parent -> Items[i][j].nom);
      if (parent -> Items[i][j].texture != NULL) {
        glEnable(GL_TEXTURE_2D);
        parent -> Items[i][j].texture -> GLTextureCourante(parent -> Items[i][j].texture);
        BEGIN_BLIT_END(this -> X, yy, 32, 32, 0.0f, 0.0f, 1.0f, 1.0f);
      };
    };
    
    this -> Curseur -> GLTextureCourante(this -> Curseur);
    float theta = (float) parent -> anim_theta[i] / nb_pas_theta;
    BEGIN_BLIT_END(this -> X-16, this -> Y - (int) (theta*NB_PIXEL_HAUTEUR_LIGNE)+8, 16,16, 0.0f, 0.0f, 1.0f, 1.0f);
    
  } glDisable2D();

  
  return b;
}; 
 



