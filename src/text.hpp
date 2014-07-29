#ifndef TEXT_HPP
#define TEXT_HPP

#include "texture.hpp"


/*
 * Cette classe repr�sente le moteur de rendu de texte � l'�cran. (il utilise
 * OpenGL et charge en fait une texture : font.png.
 * Par exemple dans les menus
 * La classe MessageTexte utilise l'objet Text aussi.
 
 * exemple : Text -> print(100, 100, 10, 10, "gougou");
 * Attention : le rep�re est en bas � gauche (comme en maths d'habitude)
 */

class CText {
private:
  int rx, ry, rw, rh; 
  int cx, cy;
  
  // la police est une texture... ohl�l� ! si les poulets me lisaient...
  CTexture * tex;

public:
  CText();
  void print(int x, int y, int w, int h, const char* s);
  float print(float l, int nblignes,int nbcaracmax,
              int x, int y, int w, int h, 
              const char * s, bool& toutaffiche);
  // l ligne courante
  
  ~CText();
   
};


/* 
 * La classe "message texte" permet d'afficher un message texte comme par exemple
 * quand on parle � quelqu'un. Elle utilise l'objet Text (un peu moins performant
 * mais Text s'utilise pour les textes des menus etc...)
 *
 * Elle g�re :
 *   - le d�filement de texte (appui sur haut et bas)
 *           (avec des p'tits fondus en haut et en bas)
 *   - l'appui sur entr�e (InputAndRender renvoit true)
 *
 * Exemple d'utilisation
 *   pendant l'affectation (dans la routine d'ex�cution du script) :
 *         MessageTexte->SetMsg("Bonjour!");
 *         
 *   pendant la boucle du jeu
 *         if(MessageTexte->InputAndRender())
 *              ...
 */

class CMessageTexte {
private:
  float lignedebut;
  // pour faire le d�filement
        
  int nbcaracaffiche;
  // nombre de caract�re affich� (pour faire l'effet, "je parle"
  // ce nombre est aussi utilis� pour tester l'appui sur Entr�e
  // Si nbcaracaffiche est trop petit l'appui sur Entree ne fera rien :
  // il faut qd ^m en lire un minimum!!!
        
  CTexture * texfond;
  CTexture * texFlecheBas;
        
  // pour stocker le parchemin
        
  const char * s;
  // pointeur vers la cha�ne � afficher
        
public:
  CMessageTexte();
  ~CMessageTexte();
  void SetMsg(const char* inS);
  // dis, maintenant, on va afficher cette cha�ne
        
  void Render();
  // s'occupe d'afficher le message... ne r�cup�re aucun code clavier
        
    
  bool InputAndRender();
  // s'occupe d'afficher, de r�cup�rer le clavier...
    
};   



/* 
 * routines pour basculer en mode 2D/32
 * mode 2D = dessiner des choses 2D � l'�cran avec BLIT par exemple
 * (comme les coeurs, les minimenus...)
 * Attention : le rep�re est en BAS � gauche et est en pixel
 */
extern void glEnable2D();
extern void glDisable2D();

extern CText * Text;
extern CMessageTexte * MessageTexte;

              
/*
 * truc pour afficher une image 2D � l'�cran
 * cx, cy : en pixel
 * ttx, tty : taille de l'image en pixel
 * tx, ty : coord dans la texture
 * w, h : taille dans la texture
*/

#define BEGIN_RECTANGLE_END(cx, cy, ttx, tty) \
      glBegin(GL_QUADS); \
    		glVertex2i((int) cx,(int) cy);		\
    		glVertex2i((int) (cx+ttx),(int) cy);	\
    		glVertex2i((int) (cx+ttx),(int) (cy+tty));	\
    		glVertex2i((int) cx,(int) (cy+tty)); \
      glEnd();
 
 
 
#define BLIT(cx, cy, ttx, tty, tx, ty, w, h) { \
        glTexCoord2f(tx,ty+h);	\
    		glVertex2f(cx,cy);		\
    		glTexCoord2f(tx+w,ty+h); \
    		glVertex2f(cx+ttx,cy);	\
    		glTexCoord2f(tx+w,ty);	\
    		glVertex2f(cx+ttx,cy+tty);	\
    		glTexCoord2f(tx,ty); \
    		glVertex2f(cx,cy+tty); \
        }; 
    		 
#define BLITCX(cx, cy, ttx, tty) \
{glTexCoord2f(0.0f,1.0f);	\
    		glVertex2i((int) (cx-ttx/2),(int) cy);		\
    		glTexCoord2f(1.0f,1.0f); \
    		glVertex2i((int) (cx+ttx/2), (int) cy);	\
    		glTexCoord2f(1.0f,0.0f);	\
    		glVertex2i((int) (cx+ttx/2), (int) (cy+tty));	\
    		glTexCoord2f(0.0f,0.0f); \
    		glVertex2i((int) (cx-ttx/2), (int) (cy+tty));};     		


#define BEGIN_BLIT_END(cx, cy, ttx, tty, tx, ty, w, h) \
      glBegin(GL_QUADS); BLIT(cx, cy, ttx, tty, tx, ty, w, h); glEnd();                               




#endif /* TEXT_HPP */
