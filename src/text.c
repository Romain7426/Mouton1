#include "global.h"
//#include <math.h>
#include "text.h"   

//#include "pascal/pascal.tools.hpp"
    
#define TAILLE_CHAR_PIXEL 24
#define TAILLEX_CHAR 16  
#define TAILLEY_CHAR 20                                                          

//extern char * ansi2oem(const char *str);


unsigned char conversionpourrie(const unsigned char c) {
  unsigned char d; 
  if (c == 224) d = 133; //à
  if (c == 226) d = 131; //â
  if (c == 231) d = 135; //ç
  if (c == 233) d = 130; //é
  if (c == 232) d = 138; //è
  if (c == 234) d = 136; //ê    
  if (c == 238) d = 140; //î
  if (c == 244) d = 131+16; //ô
  return d;
}; 




CText * Text;
CMessageTexte * MessageTexte;


void glEnable2D(void) {
  // passe en mode 2D écran/pixel
  GLint vPort[4];
  
  glGetIntegerv(GL_VIEWPORT, vPort);
  
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
  
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glDisable(GL_LIGHTING);
};

void glDisable2D(void) {
  // revient au mode d'avant...(à priori 3D normal, comme d'hab)
  glEnable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
};



CText * CText_make(void) {
  MALLOC_BZERO(CText,this); 

  assert(false); 
  //ASSIGN_METHOD(CText,this,print1); 
  //ASSIGN_METHOD(CText,this,print2); 

  printf("Création du moteur d'affichage de texte (chargement de l'image font.png)\n");
  this -> tex = CTexture_make("./font.png");
  printf("Chargement de font.png réussi\n");
  return this; 
}; 


void CText_delete(CText * this) {
  CTexture_delete(this -> tex);
  free(this);
};




float CText__print2(CText * this, float l, const int nblignes, const int nbcaracmax, const int x, const int y, const int w, const int h, const char* c, bool * toutaffiche_ref) {
  int lignecourante  = 0;

#if 0
  message("CText__print: %s\n", c);
  printf("CText__print: %s\n", c);
  fflush(NULL);
  *((int*) NULL) = 1;
#endif
  printf("CText__print: %s\n", c);
  fflush(NULL);
  
  *toutaffiche_ref = true;

  if (l < 0) l = 0;
  
  assert(c != NULL);
  if (c==NULL) return 0;



  glEnable2D(); {
    
    this -> cx = x;
    this -> cy = y + (int) (l*TAILLEY_CHAR);
    /*this -> cx, this -> cy représentent la position courante. Au début on l'initialise via (x, y)
      on décale également avec l (pour commencer à écrire à la ligne l*/
    
    glEnable(GL_TEXTURE_2D);
    this -> tex -> GLTextureCourante(this -> tex);
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS); {
    
      int i = 0;
      while ((c[i] != 0) && ((lignecourante - l) < nblignes) && (i<=nbcaracmax)) {
        int j = i;
        while((c[j] !=0 ) && (c[j] != ' ') && (c[j] != 10) && (c[j] != 13)) j++;
             
        /*de i, à j on a un mot avec le caractère ' ' ou #0 à la fin*/
            
        if ((this -> cx + (j-i)*TAILLEX_CHAR >= x + w))
          /*si le mot dépasse du cadre, on va à la ligne*/
          {
            this -> cx = x;
            this -> cy-=TAILLEY_CHAR;
            lignecourante++;
          } 
             
        /*lignecourante+1 = l : on est sur une ligne limite au début*/
        /*lignecourante = l : c'est bon, celle là il faut l'afficher en entier*/
        if ((l-1<= lignecourante) && (lignecourante <= l))
          glColor4f(1.0f, 1.0f, 1.0f, min(1.0f, max((lignecourante+1 - l), 0.0f)));
        else if ((l+nblignes<=lignecourante ) && (lignecourante<= l + nblignes+1))
          glColor4f(1.0f, 1.0f, 1.0f, min(1.0f, max(((l+nblignes+1)-lignecourante), 0.0f)));
        else     
          glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        /*on écrit que si on est déjà arrivé sur la ligne à écrire*/
        if (l-1<=lignecourante) {
          for (; (i<j) && (i<=nbcaracmax); i++)
            /*on parcourt le mot sans le caractère final (' ' ou #0), et on l'écrit
              en avançant à chaque fois vers la droite*/
            {
              unsigned char conversionc = conversionpourrie(c[i]);      
              float tx = (float) (conversionc % 16) / 16.0f;
              float ty = (float) (conversionc / 16) / 16.0f;
              glTexCoord2f(tx,ty+0.0625f);  
              glVertex2i(this -> cx,this -> cy);
              glTexCoord2f(tx+0.0625f,ty+0.0625f);
              glVertex2i(this -> cx+TAILLE_CHAR_PIXEL,this -> cy);
              glTexCoord2f(tx+0.0625f,ty);  
              glVertex2i(this -> cx+TAILLE_CHAR_PIXEL,this -> cy+TAILLE_CHAR_PIXEL);          
              glTexCoord2f(tx,ty);
              glVertex2i(this -> cx,this -> cy+TAILLE_CHAR_PIXEL);
              this -> cx+=TAILLEX_CHAR;
            }
        }
        else {
          this -> cx+=(j-i)*TAILLEX_CHAR;
          i = j;
        }    
      
        /*si le dernier caractère étant ' ', on avance encore
          pour faire un espace*/
        if (c[i] == ' ') {
          this -> cx+=TAILLEX_CHAR;
          i++;
        }
      
        if ((c[i] == 10) || (c[i] == 13))
          /*si le dernier caractère était #10, on va à la ligne*/
          {
            this -> cx  = x;
            this -> cy -= TAILLEY_CHAR;
            lignecourante++;
            i++;
          } 
      
        /*sinon, c[i] = #0 et la boucle général s'arrête*/
      }
    
    } glEnd();
    glEnable(GL_LIGHTING);
  } glDisable2D();
  
  if (l > lignecourante - nblignes+1) {
    *toutaffiche_ref = false;
    l = lignecourante - nblignes+1;
  }
  else
    *toutaffiche_ref = true;
 
  return l;

}; 


void CText__print1(CText * this, const int x, const int y, const int w, const int h, const char * s) {
  bool b;
  this -> print2(this, 0.0f, 10000, 10000,x, y, w, h, s, &b);   
};







void CMessageTexte__SetMsg(CMessageTexte * this, const char * inS) {
  printf("Argot s = %p\n", this -> s); 
  fflush(NULL);
  
  //if(s != NULL)
  //          delete[] s;
  //s = NULL
  
  this -> s = strcopy(inS);
  //s = oem2ansi(s);
  this -> lignedebut = 0;
  this -> nbcaracaffiche = 0;
}; 


CMessageTexte * CMessageTexte_make(void) {
  MALLOC_BZERO(CMessageTexte,this); 

  assert(false); 
#if 0
  ASSIGN_METHOD(CMessageTexte,this,SetMsg); 
  ASSIGN_METHOD(CMessageTexte,this,Render); 
  ASSIGN_METHOD(CMessageTexte,this,InputAndRender); 
#endif 

  printf("CMessageTexte__CMessageTexte()\n");                         
  this -> texfond = CTexture_make("parchemin.png");  
  this -> texFlecheBas = CTexture_make("flechebas.png");  
  this -> s = NULL;
};

void CMessageTexte_delete(CMessageTexte * this) {
  CTexture_delete(this -> texFlecheBas);
  CTexture_delete(this -> texfond);
  free(this -> s);   
  free(this); 
};


void CMessageTexte__Render(CMessageTexte * this) {
  this -> nbcaracaffiche++;  
#define MSGTXT_X 100
#define MSGTXT_Y 300
#define MSGTXT_W 500
#define MSGTXT_W2 220
#define MSGTXT_H 150
#define MSGTXTDECAL_Y 56
#define MSGTXTDECAL_X 32
  
  glEnable2D(); {
    glDisable(GL_LIGHTING);
    
    bool toutafficheenbas;
    this -> lignedebut = Text -> print2(Text, this -> lignedebut, 4, this -> nbcaracaffiche,
                             MSGTXT_X + MSGTXTDECAL_X, MSGTXT_Y + MSGTXT_H - MSGTXTDECAL_Y,
                             MSGTXT_W - 2*MSGTXTDECAL_X, MSGTXT_H, this -> s, &toutafficheenbas);
  
    /*if(!toutafficheenbas)
      {*/
    /* glEnable2D();
    
       texFlecheBas->GLTextureCourante();
       glDisable(GL_LIGHTING);
    
       BEGIN_RECTANGLE_END(MSGTXT_X + MSGTXT_W2, MSGTXT_Y - MSGTXTDECAL_Y, 32, 32);  */             
                    
    /*}*/


    this -> texfond -> GLTextureCourante(this -> texfond);
    
    glBegin(GL_QUADS); {
      BLIT(MSGTXT_X,MSGTXT_Y,MSGTXT_W,MSGTXT_H,0,0,1,1); 
    } glEnd();
  

    glEnable(GL_LIGHTING);
  } glDisable2D();
  
}; 



bool CMessageTexte__InputAndRender(CMessageTexte * this) {
  
  /*gestion de l'entrée clavier*/
#define PAS_MESSAGE_TEXTE 0.2f
  if (KEY_UP) this -> lignedebut -= PAS_MESSAGE_TEXTE;
  if (KEY_DOWN) this -> lignedebut += PAS_MESSAGE_TEXTE;
  
  if (this -> nbcaracaffiche > 10)
    if (KEY_MENU_VALIDER) return true;
  
  /*affichage*/
  this -> Render(this);
  
  return false;
    
};     

