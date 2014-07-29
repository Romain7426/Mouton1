#include "global.hpp"
//#include <math.h>
#include "text.hpp"   

#include "pascal/pascal.tools.hpp"
    
#define TAILLE_CHAR_PIXEL 24
#define TAILLEX_CHAR 16  
#define TAILLEY_CHAR 20                                                          

//extern char * ansi2oem(const char *str);


unsigned char conversionpourrie(unsigned char c) {
  if (c == 224) c = 133; //�
  if (c == 226) c = 131; //�
  if (c == 231) c = 135; //�
  if (c == 233) c = 130; //�
  if (c == 232) c = 138; //�
  if (c == 234) c = 136; //�
    
  if (c == 238) c = 140; //�
  if (c == 244) c = 131+16; //�
    
  return c;     
}




CText * Text;
CMessageTexte * MessageTexte;


void glEnable2D(void) {
  // passe en mode 2D �cran/pixel
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
}


void glDisable2D(void) {
  // revient au mode d'avant...(� priori 3D normal, comme d'hab)
  glEnable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}



CText::CText(void) {
  printf("Cr�ation du moteur d'affichage de texte (chargement de l'image font.png)\n");
  tex = new CTexture("./font.png");
  printf("Chargement de font.png r�ussi\n");

  rx = ry = rw = rh = 0;
  cx = cy = 0;

}


CText::~CText() {
  delete tex;
}



void CText::print(int x, int y, int w, int h, const char * s) {
  bool b;
  print(0.0f, 10000, 10000,x, y, w, h, s, b);   
}



float CText::print(float l, int nblignes, int nbcaracmax, int x, int y, int w, int h, const char* c, bool &toutaffiche) {
  int lignecourante  = 0;

#if 0
  message("CText::print: %s\n", c);
  printf("CText::print: %s\n", c);
  fflush(NULL);
  *((int*) NULL) = 1;
#endif
  printf("CText::print: %s\n", c);
  fflush(NULL);
  
  toutaffiche = true;

  if (l < 0) l = 0;
  
  assert(c != NULL);
  if (c==NULL) return 0;



  glEnable2D(); {
    
    cx = x;
    cy = y + (int) (l*TAILLEY_CHAR);
    /*cx, cy repr�sentent la position courante. Au d�but on l'initialise via (x, y)
      on d�cale �galement avec l (pour commencer � �crire � la ligne l*/
    
    glEnable(GL_TEXTURE_2D);
    tex->GLTextureCourante();
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS); {
    
      int i = 0;
      while ((c[i] != 0) && ((lignecourante - l) < nblignes) && (i<=nbcaracmax)) {
        int j = i;
        while((c[j] !=0 ) && (c[j] != ' ') && (c[j] != 10) && (c[j] != 13)) j++;
             
        /*de i, � j on a un mot avec le caract�re ' ' ou #0 � la fin*/
            
        if ((cx + (j-i)*TAILLEX_CHAR >= x + w))
          /*si le mot d�passe du cadre, on va � la ligne*/
          {
            cx = x;
            cy-=TAILLEY_CHAR;
            lignecourante++;
          } 
             
        /*lignecourante+1 = l : on est sur une ligne limite au d�but*/
        /*lignecourante = l : c'est bon, celle l� il faut l'afficher en entier*/
        if ((l-1<= lignecourante) && (lignecourante <= l))
          glColor4f(1.0f, 1.0f, 1.0f, min(1.0f, max((lignecourante+1 - l), 0.0f)));
        else if ((l+nblignes<=lignecourante ) && (lignecourante<= l + nblignes+1))
          glColor4f(1.0f, 1.0f, 1.0f, min(1.0f, max(((l+nblignes+1)-lignecourante), 0.0f)));
        else     
          glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        /*on �crit que si on est d�j� arriv� sur la ligne � �crire*/
        if (l-1<=lignecourante) {
          for (; (i<j) && (i<=nbcaracmax); i++)
            /*on parcourt le mot sans le caract�re final (' ' ou #0), et on l'�crit
              en avan�ant � chaque fois vers la droite*/
            {
              unsigned char conversionc = conversionpourrie(c[i]);      
              float tx = (float) (conversionc % 16) / 16.0f;
              float ty = (float) (conversionc / 16) / 16.0f;
              glTexCoord2f(tx,ty+0.0625f);  
              glVertex2i(cx,cy);
              glTexCoord2f(tx+0.0625f,ty+0.0625f);
              glVertex2i(cx+TAILLE_CHAR_PIXEL,cy);
              glTexCoord2f(tx+0.0625f,ty);  
              glVertex2i(cx+TAILLE_CHAR_PIXEL,cy+TAILLE_CHAR_PIXEL);          
              glTexCoord2f(tx,ty);
              glVertex2i(cx,cy+TAILLE_CHAR_PIXEL);
              cx+=TAILLEX_CHAR;
            }
        }
        else {
          cx+=(j-i)*TAILLEX_CHAR;
          i = j;
        }    
      
        /*si le dernier caract�re �tant ' ', on avance encore
          pour faire un espace*/
        if (c[i] == ' ') {
          cx+=TAILLEX_CHAR;
          i++;
        }
      
        if ((c[i] == 10) || (c[i] == 13))
          /*si le dernier caract�re �tait #10, on va � la ligne*/
          {
            cx = x;
            cy-=TAILLEY_CHAR;
            lignecourante++;
            i++;
          } 
      
        /*sinon, c[i] = #0 et la boucle g�n�ral s'arr�te*/
      }
    
    } glEnd();
    glEnable(GL_LIGHTING);
  } glDisable2D();
  
  if (l > lignecourante - nblignes+1) {
    toutaffiche = false;
    l = lignecourante - nblignes+1;
  }
  else
    toutaffiche = true;
 
  return l;

} 




void CMessageTexte::SetMsg(const char * inS) {
  printf("Argot s = %p\n", s); 
  fflush(NULL);
  
  //if(s != NULL)
  //          delete[] s;
  //s = NULL
  
  s = strcopy(inS);
  //s = oem2ansi(s);
  lignedebut = 0;
  nbcaracaffiche = 0;
}


CMessageTexte::CMessageTexte(void) : s(NULL) {
  printf("CMessageTexte::CMessageTexte()\n");                         
  texfond = new CTexture("parchemin.png");  
  texFlecheBas = new CTexture("flechebas.png");  
  s = NULL;
}

CMessageTexte::~CMessageTexte(void) {
  delete texfond;
  delete[] s;   
}


void CMessageTexte::Render(void) {
  nbcaracaffiche++;  
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
    lignedebut = Text->print(lignedebut, 4, nbcaracaffiche,
                             MSGTXT_X + MSGTXTDECAL_X, MSGTXT_Y + MSGTXT_H - MSGTXTDECAL_Y,
                             MSGTXT_W - 2*MSGTXTDECAL_X, MSGTXT_H, s, toutafficheenbas);
  
    /*if(!toutafficheenbas)
      {*/
    /* glEnable2D();
    
       texFlecheBas->GLTextureCourante();
       glDisable(GL_LIGHTING);
    
       BEGIN_RECTANGLE_END(MSGTXT_X + MSGTXT_W2, MSGTXT_Y - MSGTXTDECAL_Y, 32, 32);  */             
                    
    /*}*/


    texfond->GLTextureCourante();
    
    glBegin(GL_QUADS); {
      BLIT(MSGTXT_X,MSGTXT_Y,MSGTXT_W,MSGTXT_H,0,0,1,1); 
    } glEnd();
  

    glEnable(GL_LIGHTING);
  } glDisable2D();
  
}



bool CMessageTexte::InputAndRender(void) {
  
  /*gestion de l'entr�e clavier*/
#define PAS_MESSAGE_TEXTE 0.2f
  if (KEY_UP) lignedebut -= PAS_MESSAGE_TEXTE;
  if (KEY_DOWN) lignedebut += PAS_MESSAGE_TEXTE;
  
  if (nbcaracaffiche > 10)
    if (KEY_MENU_VALIDER) return true;
  
  /*affichage*/
  Render();
  
  return false;
    
}    

