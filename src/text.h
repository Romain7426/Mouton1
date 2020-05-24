#ifndef TEXT_H
#define TEXT_H

// RL: ??? 
extern struct CText * Text;
#if 0 
extern struct CMessageTexte * MessageTexte;
#endif 


/*
 * Cette classe représente le moteur de rendu de texte à l'écran. (il utilise
 * OpenGL et charge en fait une texture : font.png.
 * Par exemple dans les menus
 * La classe MessageTexte utilise l'objet Text aussi.
 
 * exemple : Text -> print(100, 100, 10, 10, "gougou");
 * Attention : le repère est en bas à gauche (comme en maths d'habitude)
 */
struct CText {
  int rx, ry, rw, rh; 
  int cx, cy;
  
  // la police est une texture... ohlàlà ! si les poulets me lisaient...
  CTexture * tex;

  void (* print1)(struct CText * this, int x, int y, int w, int h, const char * s);
  float (* print2)(struct CText * this, float l, int nblignes, int nbcaracmax, int x, int y, int w, int h, const char * s, bool * toutaffiche_ptr);
  // l ligne courante
};
extern CText * CText_make(void);
extern void CText_delete(CText * this);
extern void  CText__print1(CText * this, int x, int y, int w, int h, const char * s);
extern float CText__print2(CText * this, float l, int nblignes, int nbcaracmax, int x, int y, int w, int h, const char * s, bool * toutaffiche_ptr);






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

struct CMessageTexte {
  //private:
  float lignedebut;
  // pour faire le défilement
        
  int nbcaracaffiche;
  // nombre de caractère affiché (pour faire l'effet, "je parle"
  // ce nombre est aussi utilisé pour tester l'appui sur Entrée
  // Si nbcaracaffiche est trop petit l'appui sur Entree ne fera rien :
  // il faut qd ^m en lire un minimum!!!
        
  struct CTexture * texfond;
  struct CTexture * texFlecheBas;
        
  // pour stocker le parchemin 
        
  char * s;
  // pointeur vers la chaîne à afficher 
        
  void (* SetMsg)(struct CMessageTexte * this, const char* inS);
  // dis, maintenant, on va afficher cette chaîne
        
  // RL: TODO XXX FIXME: Should be const. 
  void (* Render)(struct CMessageTexte * this); 
  // s'occupe d'afficher le message... ne récupère aucun code clavier 
        
  bool (* Input)(struct CMessageTexte * this);
  void (* Life)(struct CMessageTexte * this);

  //bool (* InputAndRender)(struct CMessageTexte * this);
  // s'occupe d'afficher, de récupérer le clavier...
};   

extern CMessageTexte * CMessageTexte_make(void);
extern void CMessageTexte_delete(CMessageTexte * this);







/* 
 * routines pour basculer en mode 2D/32
 * mode 2D = dessiner des choses 2D à l'écran avec BLIT par exemple
 * (comme les coeurs, les minimenus...)
 * Attention : le repère est en BAS à gauche et est en pixel
 */
extern void glEnable2D(void);
extern void glDisable2D(void);

              
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




#endif /* TEXT_H */
