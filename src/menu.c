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
  BZERO_THIS(this); 
  
  ASSIGN_METHOD(CMenuAbstrait,this,ProchainIndice); 
  ASSIGN_METHOD(CMenuAbstrait,this,Add); 
  ASSIGN_METHOD(CMenuAbstrait,this,Add_qch); 
  //ASSIGN_METHOD(CMenuAbstrait,this,InputAndRender); 
  ASSIGN_METHOD(CMenuAbstrait,this,Input); 
  ASSIGN_METHOD(CMenuAbstrait,this,Render); 
  ASSIGN_METHOD(CMenuAbstrait,this,Life); 

  //printf("Création du menu 'abstrait'...\n");
  this -> iphi = 0;
  this -> Action = 0;
  this -> anim_phi = 0;

#if 1 
  // RL: This should be useless, but there is a MiniMenu with dangling pointer hanging around. 
  for (int i = 0; i < NB_SOUS_MENU; i++) { 
    this -> NomSousMenu[i] = NULL; 
    for (int j = 0; j < NB_ITEM_MAX; j++) { 
      this -> Items[i][j].nom = NULL; 
      this -> Items[i][j].qch = NULL; 
    }; 
    this -> anim_theta[i] = 0; 
  }; 
#endif 
  
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
    if (NULL != this -> NomSousMenu[i]) { 
      free(this -> NomSousMenu[i]); 
      this -> NomSousMenu[i] = NULL; 
    }; 
  };   
};

void CMenuAbstrait_delete(CMenuAbstrait * this) {
  CMenuAbstrait_delete_aux(this); 
  free(this); 
}; 

CMenuAbstrait * CMenuAbstrait_copy_aux(CMenuAbstrait * this, const CMenuAbstrait * src) {
  *this = *src; 
  // RL: Column titles 
  for (int i = 0; i < NB_SOUS_MENU; i++) {
    if (NULL != this -> NomSousMenu[i]) { 
      this -> NomSousMenu[i] = strcopy(src -> NomSousMenu[i]); 
    }; 
  }; 
  // RL: Column contents 
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



int CMenuAbstrait__ProchainIndice(const CMenuAbstrait * this, const int ssMenu) {
  /*ProchainIndice représente le prochain indice pour un nouvel
    élément dans le sous-menu ssMenu. Il représente aussi le nombre 
    d'éléments dans ce sous-menu*/
  // RL: I figured out why the code did shit! Because this function is used to get the number of elements and the next item that can be assigned. Dude... 
  //     So I increased NB_ITEM_MAX so that I do not have to rewrite the code while having a working code with that weird semantic. 
  assert(ssMenu < NB_SOUS_MENU); 
  int j = 0;
  for (; (j<NB_ITEM_MAX) && (this -> Items[ssMenu][j].nom != NULL); j++) {}; 
  assert(j < NB_ITEM_MAX); 
  return j >= NB_ITEM_MAX ? -1 : j; 
  return j;
}; 


void CMenuAbstrait__Add(CMenuAbstrait * this, const int ssMenu, const char * nom, const char * nom_texture) {
  // si nom_texture == NULL, l'élément ajouté n'a pas d'icône 
  this -> Add_qch(this, ssMenu, nom, nom_texture, NULL); 
}; 


void CMenuAbstrait__Add_qch(CMenuAbstrait * this, const int ssMenu, const char * nom, const char * nom_texture, void * qch) {
  // si nom_texture == NULL ou "", l'élément ajouté n'a pas d'icône 
  const int j = this -> ProchainIndice(this, ssMenu); 
  this -> Items[ssMenu][j].nom = strcopy(nom); 
  
  if (nom_texture == NULL) 
    this -> Items[ssMenu][j].texture = NULL; 
  else if (nom_texture[0] == 0) 
    this -> Items[ssMenu][j].texture = NULL; 
  else 
    this -> Items[ssMenu][j].texture = CTexture_make(nom_texture); 
  
  this -> Items[ssMenu][j].qch = qch;
};   


void CMenuAbstrait__Life(CMenuAbstrait * this) { 
  const int    column_i     = this -> iphi; // RL: This is the column. 
  const int    num_item_max = this -> ProchainIndice(this, column_i); // RL: This is the number of items in the column. 
  const char * column_title = this -> NomSousMenu[column_i]; 

  
#define R 1.0f
#define a 0.8f

#define THETA_TEST						\
  if (this -> anim_theta[this -> iphi] % nb_pas_theta == 0)     \
    {this -> Action = 0;}
  
#define PHI_TEST                                                        \
  this -> iphi = this -> anim_phi / nb_pas_phi;				\
  /*printf("Ecart entre phi et iphi : %i\n",this -> anim_phi % nb_pas_phi);*/ \
  if (((this -> anim_phi % nb_pas_phi) == 0) && (this -> ProchainIndice(this, this -> iphi)>0))	\
    {this -> Action = 0;						\
      /*printf("C'est bon on est sur iphi = %i\n", this -> iphi);*/ ;}
  
#define DEC_THETA 1
#define INC_THETA 2
#define DEC_PHI 3
#define INC_PHI 4
#define ENTRER_MENU 5
#define ANNULER_MENU 6


#define RAMENER_MODULO(iphi, max)                                       \
  if (iphi >= (max)) iphi -= (max); else if (iphi < 0) iphi += (max);



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
  }; 
    
  // RL: Shouldn't we check against the number of items in the sub-menu? 
  this -> itheta = this -> anim_theta[this -> iphi] / nb_pas_theta;
}; 

//bool CMenuAbstrait__InputAndRender(CMenuAbstrait * this) { 
int CMenuAbstrait__Input(CMenuAbstrait * this) { 
  //CMenuAbstrait__Life(this); 
  
  this -> Canceled = false;

  if (this -> Action == 0) {
    // on traite les entrées clavier que si on ne fait rien dans le menu

    if (this -> ProchainIndice(this, this -> iphi) != 1) {
      // on ne fait tourner en théta que s'il y a plus de 1 élément
      if (KEY_UP) this -> Action = DEC_THETA; 
      if (KEY_DOWN) this -> Action = INC_THETA; 
    }; 
    
    if (KEY_LEFT) this -> Action = DEC_PHI;
    if (KEY_RIGHT) this -> Action = INC_PHI;
           
    if (KEY_MENU_VALIDER)          
      return true; 

    if (KEY_MENU_ECHAP) { 
      this -> Canceled = true; 
      return true; 
    }; 
    
  }; 
  
  return false;
}; 


void CMenuAbstrait__Render(const CMenuAbstrait * this) { 
};





/*******************************************************************************
  MENU
******************************************************************************/

CMenu * CMenu_make_aux(CMenu * this) {
  CMenuAbstrait_make_aux(&this -> parent); 
  
  //ASSIGN_METHOD(CMenu,this,InputAndRender); 
  ASSIGN_METHOD(CMenu,this,Input); 
  ASSIGN_METHOD(CMenu,this,Render); 
  ASSIGN_METHOD(CMenu,this,Life); 
  
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
 
//bool CMenu__InputAndRender(CMenu * this) {
int CMenu__Input(CMenu * this) { 
  CMenuAbstrait * parent = &this -> parent; 
  const bool b = parent -> Input(parent); 
  return b; 
}; 

void CMenu__Life(CMenu * this) { 
  CMenuAbstrait * parent = &this -> parent; 
  parent -> Life(parent); 
}; 

void CMenu__Render(const CMenu * this) {
  const CMenuAbstrait * parent = &this -> parent; 
  parent -> Render(parent); 

  const int column_i = parent -> iphi; // RL: This is the column. 
  //const int num_item_max = parent -> ProchainIndice(parent, column_i); // RL: This is the number of items in the column. 
  const char * column_title = this -> parent.NomSousMenu[column_i]; 

  
  glDisable(GL_CULL_FACE);  
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
    
  //printf("para\n"); 
  /*les parallèles*/
  for (int j = 0; j<=MENU_nb_theta; j++) {
    glBegin(GL_LINE_STRIP); {
      const float cj = cosf((float)2*PI*(j)/MENU_nb_theta);
      const float sj = sinf((float)2*PI*(j)/MENU_nb_theta);
      for (int i = 0; i <= MENU_nb_phi; i++)
        glVertex3f( (R + a2*cj)*cosf((float)2*PI*(i)/MENU_nb_phi),       (R + a2*cj) * sinf((float)2*PI*(i)/MENU_nb_phi),        a2*sj);
    } glEnd();
  }; 
  
  
  //printf("minian\n"); 
  /*les mini-anneaux*/
  for (int i = 0; i<=MENU_nb_phi; i++) {
    const float ci = cosf((float)2*PI*(i)/MENU_nb_phi);
    const float si = sinf((float)2*PI*(i)/MENU_nb_phi);

    glBegin(GL_LINE_STRIP); { 
      for (int j = 0; j<=MENU_nb_theta; j++) {
      glVertex3f( (R+a2  *cosf((float)2*PI*(j)/MENU_nb_theta) ) * ci,        (R+(a2) *cosf((float)2*PI*(j)/MENU_nb_theta) ) * si,        (a2) *sinf((float)2*PI*(j)/MENU_nb_theta) ); 
    }; 
    } glEnd();             
  }; 
  
  glEnable (GL_TEXTURE_2D); 
  glColor4f(1.0f,1.0f,1.0f,1.0f);  
    
  //printf("items\n"); 
  //*on affiche les items ...*/   
  for (int i = 0; i < NB_SOUS_MENU; i++) {
    const int num_item_max = parent -> ProchainIndice(parent, i); /*nb d'items sur l'anneau n° i*/ // RL: items_nb 
        
    const float phi = (float) parent -> anim_phi / nb_pas_phi;
    const float ci = cosf(2*PI*(i-phi)/NB_SOUS_MENU);
    const float si = sinf(2*PI*(i-phi)/NB_SOUS_MENU);
      
    //*dessin d'un cercle*/
    if (num_item_max > 0) { 
      glColor4f(1.0f,1.0f,0.0f,0.4f); 
      glDisable(GL_TEXTURE_2D); 
      glBegin(GL_LINE_STRIP); { 
	for (int j = 0; j<=MENU_nb_theta; j++) {
	  glVertex3f( (R+a22  *cosf((float)2*PI*(j)/MENU_nb_theta) ) * ci,            (R+(a22) *cosf((float)2*PI*(j)/MENU_nb_theta) ) * si,            (a22) *sinf((float)2*PI*(j)/MENU_nb_theta) );  
	}; 
      } glEnd(); 
      glEnable(GL_TEXTURE_2D); 
      glColor4f(1.0f,1.0f,1.0f,1.0f); 
    };  
         
    //*on parcourt les items*/            
    for (int j = 0; j < num_item_max; j++) {
      if (parent -> Items[i][j].texture == NULL) { 
        glDisable(GL_TEXTURE_2D); 
      }
      else {
        glEnable(GL_TEXTURE_2D);
        parent -> Items[i][j].texture -> GLTextureCourante(parent -> Items[i][j].texture);
      };       
      const float theta = (float) parent -> anim_theta[i] / nb_pas_theta;        
      const float cj = cosf(2*PI*(j-theta)/num_item_max);
      const float sj = sinf(2*PI*(j-theta)/num_item_max);                                                 
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
    }; 
    
  }; 
    
  //printf("gougouavant texte\n");  
  if (column_title != NULL) { 
    Text -> print1(Text, 100,SCREEN_HEIGHT-50,10000,100, column_title); 
  }; 
  
  // RL: How do we know that 'itheta' is in the range? 
  //     Therefore I add that test. 
  if (NULL != parent -> Items[parent -> iphi][parent -> itheta].nom) { 
    Text -> print1(Text, 100,50,10000,100,parent -> Items[parent -> iphi][parent -> itheta].nom); 
  }; 
  
  glEnable(GL_LIGHTING); 
  
  //printf("gougoufin\n"); 
  
  glEnable(GL_CULL_FACE); 
}; 
 








/*******************************************************************************
  MINIMENU
******************************************************************************/
  
CMiniMenu * CMiniMenu_make(const int inX, const int inY, const int inW) {
  MALLOC_BZERO(CMiniMenu,this);
  
  CMenuAbstrait_make_aux(&this -> parent); 
  
  //ASSIGN_METHOD(CMiniMenu,this,InputAndRender); 
  ASSIGN_METHOD(CMiniMenu,this,Input); 
  ASSIGN_METHOD(CMiniMenu,this,Render); 
  ASSIGN_METHOD(CMiniMenu,this,Life); 

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
  if (this == NULL) return; 
  CMiniMenu_delete_aux(this);
  free(this); 
}; 

//bool CMiniMenu__InputAndRender(CMiniMenu * this) {
int CMiniMenu__Input(CMiniMenu * this) { 
  CMenuAbstrait * parent = &this -> parent; 
  const bool b = parent -> Input(parent); 
  return b; 
}; 

void CMiniMenu__Life(CMiniMenu * this) { 
  CMenuAbstrait * parent = &this -> parent; 
  parent -> Life(parent); 
}; 

void CMiniMenu__Render(const CMiniMenu * this) {
  const CMenuAbstrait * parent = &this -> parent; 
  parent -> Render(parent); 
  
  const int column_i = parent -> iphi; // RL: This is the column. 
  const int num_item_max = parent -> ProchainIndice(parent, column_i); // RL: This is the number of items in the column. 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "column_i = %s - " "num_item_max = %s " "\n", __func__, int_string__stack(column_i), int_string__stack(num_item_max)); 
  
  const char * column_title = this -> parent.NomSousMenu[column_i]; 
  
  glEnable2D(); {
#define NB_PIXEL_HAUTEUR_LIGNE 32.0f
    //*on parcourt les items du sous-menus*/
    for (int j = 0; j < num_item_max; j++) { 
      const char * item_nom = parent -> Items[column_i][j].nom; 
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "item_nom = %s " "\n", __func__, item_nom); 
      
#define  yy this->Y - (int) (j*NB_PIXEL_HAUTEUR_LIGNE)
      Text -> print1(Text, this -> X+40, yy, 1000, 1000, item_nom);
      if (parent -> Items[column_i][j].texture != NULL) {
        glEnable(GL_TEXTURE_2D);
        parent -> Items[column_i][j].texture -> GLTextureCourante(parent -> Items[column_i][j].texture);
        BEGIN_BLIT_END(this -> X, yy, 32, 32, 0.0f, 0.0f, 1.0f, 1.0f);
      };
    };
    
    this -> Curseur -> GLTextureCourante(this -> Curseur);
    const float theta = (float) parent -> anim_theta[column_i] / nb_pas_theta;
    BEGIN_BLIT_END(this -> X-16, this -> Y - (int) (theta*NB_PIXEL_HAUTEUR_LIGNE)+8, 16,16, 0.0f, 0.0f, 1.0f, 1.0f);
    
  } glDisable2D();

}; 
 



