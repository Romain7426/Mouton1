#ifndef OBJ3DS_H
#define OBJ3DS_H

#include "3ds.h"

struct CTexture;

//typedef unsigned char byte;
/*Cette structe permet de g�rer un objet 3D stock� dans un fichier 3DS.
  Pour l'utiliser :
  - pour charger : C3DS* momo = new C3DS("momo.3ds");
  - pour afficher : momo->Render() (avec �ventuellement des changements de
  matrices pour placer l'objet au bon endroit)
  - puis � la fin delete momo;
*/

struct C3DS {
  //private:
  /*le parall�l�pip�de englobant*/
  struct TPoint3D minPE, maxPE;
     
  struct CLoad3DS g_Load3ds; // L'objet pour charger un 3ds
  struct t3DModel g_3DModel;  //l� ou sont stock� les points
  struct CTexture * g_Texture[MAX_TEXTURES];   //l� o� on stocke les textures
  int g_ViewMode; //mode d'affichage
  unsigned Liste; //liste d'affichage (pour optimiser l'affichage OpenGL)
   
  //public:
#if 0
  C3DS(const char * filename);
  ~C3DS();
#endif
  void (* Render)(const struct C3DS * this);
  void (* RenderGL)(const struct C3DS * this);
  void (* CalcPE)(struct C3DS * this);
}; 
 
 
#endif /* OBJ3DS_H */
