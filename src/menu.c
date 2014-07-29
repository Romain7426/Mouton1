#include "global.hpp"
#include "menu.hpp"
#include "text.hpp"




/*******************************************************************************
  MENU ABSTRAIT
******************************************************************************/

CMenuAbstrait::CMenuAbstrait() : iphi(0) {  
  printf("Création du menu 'abstrait'...\n");

  for (int i = 0; i < NB_SOUS_MENU; i++) {
    NomSousMenu[i] = NULL;
    for (int j = 0; j < NB_ITEM_MAX; j++) {
      Items[i][j].nom = NULL;  
      Items[i][j].qch = NULL;   
    }
    anim_theta[i] = 0;        
  }
  
  Action = 0;
  anim_phi = 0;
}    


CMenuAbstrait::~CMenuAbstrait(void) {
}    


int CMenuAbstrait::ProchainIndice(int ssMenu) {
  /*ProchainIndice représente le prochain indice pour un nouvel
    élément dans le sous-menu ssMenu. Il représente aussi le nombre 
    d'élément dans ce sous-menu*/
  int j = 0;
  for (; (j<NB_ITEM_MAX) && (Items[ssMenu][j].nom != NULL); j++) {};
  return j;
}    


void CMenuAbstrait::Add(int ssMenu, const char * nom, const char * nom_texture) {
  // si nom_texture == NULL, l'élément ajouté n'a pas d'icône
  Add(ssMenu, nom, nom_texture, NULL);
}  


void CMenuAbstrait::Add(int ssMenu, const char * nom, const char * nom_texture, void * qch) {
  // si nom_texture == NULL ou "", l'élément ajouté n'a pas d'icône
  int j = ProchainIndice(ssMenu);
  Items[ssMenu][j].nom = strcopy(nom);
  
  if (nom_texture == NULL)
    Items[ssMenu][j].texture = NULL;
  else if (nom_texture[0] == 0) 
    Items[ssMenu][j].texture = NULL;
  else 
    Items[ssMenu][j].texture = new CTexture(nom_texture);
      
  Items[ssMenu][j].qch = qch;
  
}   


bool CMenuAbstrait::InputAndRender(void) {
#define R 1.0f
#define a 0.8f
  Canceled = false;

#define THETA_TEST                              \
  if (anim_theta[iphi] % nb_pas_theta == 0)     \
    {Action = 0;}
  
#define PHI_TEST                                                        \
  iphi = anim_phi / nb_pas_phi;                                         \
  printf("Ecart entre phi et iphi : %i\n",anim_phi % nb_pas_phi);       \
  if (((anim_phi % nb_pas_phi) == 0) && (ProchainIndice(iphi)>0))       \
    {Action = 0;                                                        \
      printf("C'est bon on est sur iphi = %i\n", iphi); ;}
  
#define DEC_THETA 1
#define INC_THETA 2
#define DEC_PHI 3
#define INC_PHI 4
#define ENTRER_MENU 5
#define ANNULER_MENU 6


#define RAMENER_MODULO(iphi, max)                                       \
  if (iphi >= (max)) iphi -= (max); else if (iphi < 0) iphi += (max);

  if (Action == 0) {
    // on traite les entrées clavier que si on ne fait rien dans le menu

    if (ProchainIndice(iphi) != 1) {
      // on ne fait tourner en théta que s'il y a plus de 1 élément
      if (KEY_UP) Action = DEC_THETA;
      if (KEY_DOWN) Action = INC_THETA;
    }  

    if (KEY_LEFT) Action = DEC_PHI;
    if (KEY_RIGHT) Action = INC_PHI;
           
    if (KEY_MENU_VALIDER)          
      return true;

    if (KEY_MENU_ECHAP) {
      Canceled = true;       
      return true;         
    }
    
  }


  if (Action == DEC_THETA) {
    anim_theta[iphi] --;
    RAMENER_MODULO(anim_theta[iphi], nb_pas_theta*ProchainIndice(iphi));   
    THETA_TEST;
  }    
    
  if (Action == INC_THETA) {
    anim_theta[iphi] ++;
    RAMENER_MODULO(anim_theta[iphi], nb_pas_theta*ProchainIndice(iphi));   
    THETA_TEST;
  }    
       
  if (Action == DEC_PHI) {
    anim_phi--;   
    RAMENER_MODULO(anim_phi, NB_SOUS_MENU * nb_pas_phi);
    RAMENER_MODULO(iphi, NB_SOUS_MENU);
    PHI_TEST;
  }    
    
  if (Action == INC_PHI) {
    anim_phi++;  
    RAMENER_MODULO(anim_phi, NB_SOUS_MENU * nb_pas_phi); 
    RAMENER_MODULO(iphi, NB_SOUS_MENU);
    PHI_TEST;
  }    
    
  itheta = anim_theta[iphi] / nb_pas_theta;
  
  return false;
}





/*******************************************************************************
  MENU
******************************************************************************/

CMenu::CMenu(void) {
}   

bool CMenu::InputAndRender(void) {
  bool b = CMenuAbstrait::InputAndRender(); 
  
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
    int num_item_max = ProchainIndice(i); /*nb d'item sur l'anneau n° i*/
        
    float phi = (float) anim_phi / nb_pas_phi;
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
      if (Items[i][j].texture == NULL)
        glDisable(GL_TEXTURE_2D);
      else {
        glEnable(GL_TEXTURE_2D);
        Items[i][j].texture->GLTextureCourante();
      }      
      float theta = (float) anim_theta[i] / nb_pas_theta;        
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
  Text->print(100,SCREEN_HEIGHT-50,10000,100,NomSousMenu[iphi]);
  Text->print(100,50,10000,100,Items[iphi][itheta].nom);
    
  glEnable(GL_LIGHTING);
    
  printf("gougoufin\n");  
    
  return b;
  glEnable(GL_CULL_FACE); 
}    









/*******************************************************************************
  MINIMENU
******************************************************************************/
  
CMiniMenu::CMiniMenu(int inX, int inY, int inW) : X(inX), Y(inY), W(inW) {
  Curseur = new CTexture("curseur.png");
}

CMiniMenu::~CMiniMenu(void) {
  delete Curseur;
}

bool CMiniMenu::InputAndRender(void) {
  bool b = CMenuAbstrait::InputAndRender();
   
  glEnable2D(); {
    int i = iphi;
#define NB_PIXEL_HAUTEUR_LIGNE 32.0f
    /*on parcourt les items du sous-menus*/
    int num_item_max = ProchainIndice(i);
    for (int j = 0; j < num_item_max; j++) {
#define  yy Y - (int) (j*NB_PIXEL_HAUTEUR_LIGNE)
      Text -> print(X+40, yy, 1000, 1000, Items[i][j].nom);
      if (Items[i][j].texture != NULL) {
        glEnable(GL_TEXTURE_2D);
        Items[i][j].texture -> GLTextureCourante();
        BEGIN_BLIT_END(X, yy, 32, 32, 0.0f, 0.0f, 1.0f, 1.0f);
      }
    }
    
    Curseur->GLTextureCourante();
    float theta = (float) anim_theta[i] / nb_pas_theta;
    BEGIN_BLIT_END(X-16, Y - (int) (theta*NB_PIXEL_HAUTEUR_LIGNE)+8, 16,16, 0.0f, 0.0f, 1.0f, 1.0f);
    
  } glDisable2D();

  
  return b;
}


