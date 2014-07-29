#ifndef OBJ3DS_HPP
#define OBJ3DS_HPP

#include "3ds.hpp"

class CTexture;

typedef unsigned char byte;
/*Cette classe permet de g�rer un objet 3D stock� dans un fichier 3DS.
  Pour l'utiliser :
  - pour charger : C3DS* momo = new C3DS("momo.3ds");
  - pour afficher : momo->Render() (avec �ventuellement des changements de
  matrices pour placer l'objet au bon endroit)
  - puis � la fin delete momo;
*/

class C3DS {
private:
  /*le parall�l�pip�de englobant*/
  TPoint3D minPE, maxPE;
     
  CLoad3DS g_Load3ds; // L'objet pour charger un 3ds
  t3DModel g_3DModel;  //l� ou sont stock� les points
  CTexture * g_Texture[MAX_TEXTURES];   //l� o� on stocke les textures
  int g_ViewMode; //mode d'affichage
  unsigned Liste; //liste d'affichage (pour optimiser l'affichage OpenGL)
  void RenderGL();
   
  void CalcPE();
   
public:

  C3DS(const char * filename);
  ~C3DS();
  void Render() const;
    

}; 
 
 
#endif /* OBJ3DS_HPP */
