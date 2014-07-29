#ifndef TEXT_HPP
#define TEXT_HPP

#include "texture.hpp"


/*
 * Cette classe représente le moteur de rendu de texte à l'écran. (il utilise
 * OpenGL et charge en fait une texture : font.png.
 * Par exemple dans les menus
 * La classe MessageTexte utilise l'objet Text aussi.
 
 * exemple : Text -> print(100, 100, 10, 10, "gougou");
 * Attention : le repère est en bas à gauche (comme en maths d'habitude)
 */

class CText {
private:
  int rx, ry, rw, rh; 
  int cx, cy;
  
  // la police est une texture... ohlàlà ! si les poulets me lisaient...
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
 * quand on parle à quelqu'un. Elle utilise l'objet Text (un peu moins performant
 * mais Text s'utilise pour les textes des menus etc...)
 *
 * Elle gère :
 *   - le défilement de texte (appui sur haut et bas)
 *           (avec des p'tits fondus en haut et en bas)
 *   - l'appui sur entrée (InputAndRender renvoit true)
 *
 * Exemple d'utilisation
 *   pendant l'affectation (dans la routine d'exécution du script) :
 *         MessageTexte->SetMsg("Bonjour!");
 *         
 *   pendant la boucle du jeu
 *         if(MessageTexte->InputAndRender())
 *              ...
 */

class CMessageTexte {
private:
  float lignedebut;
  // pour faire le défilement
        
  int nbcaracaffiche;
  // nombre de caractère affiché (pour faire l'effet, "je parle"
  // ce nombre est aussi utilisé pour tester l'appui sur Entrée
  // Si nbcaracaffiche est trop petit l'appui sur Entree ne fera rien :
  // il faut qd ^m en lire un minimum!!!
        
  CTexture * texfond;
  CTexture * texFlecheBas;
        
  // pour stocker le parchemin
        
  const char * s;
  // pointeur vers la chaîne à afficher
        
public:
  CMessageTexte();
  ~CMessageTexte();
  void SetMsg(const char* inS);
  // dis, maintenant, on va afficher cette chaîne
        
  void Render();
  // s'occupe d'afficher le message... ne récupère aucun code clavier
        
    
  bool InputAndRender();
  // s'occupe d'afficher, de récupérer le clavier...
    
};   



/* 
 * routines pour basculer en mode 2D/32
 * mode 2D = dessiner des choses 2D à l'écran avec BLIT par exemple
 * (comme les coeurs, les minimenus...)
 * Attention : le repère est en BAS à gauche et est en pixel
 */
extern void glEnable2D();
extern void glDisable2D();

extern CText * Text;
extern CMessageTexte * MessageTexte;

              
/*
 * truc pour afficher une image 2D à l'écran
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
