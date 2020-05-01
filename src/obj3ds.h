#ifndef OBJ3DS_H
#define OBJ3DS_H

/*Cette structe permet de gérer un objet 3D stocké dans un fichier 3DS.
  Pour l'utiliser :
  - pour charger : C3DS* momo = new C3DS("momo.3ds");
  - pour afficher : momo->Render() (avec éventuellement des changements de
  matrices pour placer l'objet au bon endroit)
  - puis à la fin delete momo;
*/

struct C3DS {
  char * filename; 
  int dico_i; 
  
  /*le parallélépipède englobant*/
  TPoint3D minPE, maxPE;
  
  CLoad3DS g_Load3ds; // L'objet pour charger un 3ds
  t3DModel g_3DModel;  //là ou sont stocké les points
  CTexture * g_Texture[MAX_TEXTURES];   //là où on stocke les textures
  int g_ViewMode; //mode d'affichage
  unsigned Liste; //liste d'affichage (pour optimiser l'affichage OpenGL)

  C3DS * (* make)(const char * filename); 
  C3DS * (* copy)(const C3DS * this); 
  void (* delete)(C3DS * this); 
  void (* Render)(const C3DS * this); 
  void (* RenderGL)(const C3DS * this);
  //void (* CalcPE)(struct C3DS * this);
}; 
extern C3DS * C3DS__make(const char * filename); 
#if 0 
extern C3DS * C3DS__copy(const C3DS * this); 
extern void C3DS__delete(C3DS * this); 
extern void C3DS__Render(const C3DS * this); 
extern void C3DS__RenderGL(const C3DS * this);
//extern void C3DS__CalcPE(C3DS * this);
#endif 

 
#endif /* OBJ3DS_H */
