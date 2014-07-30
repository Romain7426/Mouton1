#ifndef SOL_H
#define SOL_H

//#include "ressource.h"

struct CTexture;
struct TPoint2D;
struct TPoint3D;

struct TPointEcran;

struct TPointEcran {
  TPoint3D pt, normal;       
};
TYPEDEF_TYPENAME_WITHOUT_STRUCT(TPointEcran);
DEFINE_NEW_OPERATOR_FOR_STRUCT(TPointEcran);



enum { NB_MAX_TEXTURESOL =  10 };



TYPEDEF_TYPENAME_WITHOUT_STRUCT(CSol);
// Cette structe stocke une carte
struct CSol {
  //protected:
  float ybase;
  float R, a;
  int nb_phi, nb_theta;     
  
  float temps;
  
  // texture de sol
  //ressource<CTexture> * TextureSol[NB_MAX_TEXTURESOL];
  CTexture * TextureSol[NB_MAX_TEXTURESOL];
  int nb_texture;
  int indices_dans_bitmap[NB_MAX_TEXTURESOL];
  
  // données de la carte
  float * Z; // tableaud de taille TailleX * TailleY
  
  TPointEcran * PointsEcran;
  int * indices_texture;

  // taille en case de la carte, c'est ChargerZ qui s'occupe de remplir ça
  //public:
  int TailleX, TailleY;
  
  float ZEau;// = 45.8f;










  void (*SETZ)(CSol * this, int x, int y, float z);
  /*en privée, un élément de l'extérieur n'a pas le droit de modifier le terrain
    utiliser "ChargerZ" pour cela*/
  
  void (* SETINDTEXTURE)(CSol * this, int x, int y, int ind);
  int (* GETINDTEXTURE)(const CSol * this, int x, int y);
  
  TPoint3D (* GetPoint3D)(const CSol * this, float i, float j, float z);
  void (* tore)(const CSol * this, int i,int j);
  void (* tore0)(const CSol * this, int i,int j);
  
  
  void (* CalcPoints)(const CSol * this, int i1, int j1, int i2, int j2);

  int (* GetTailleX)(const CSol * this);
  int (* GetTailleY)(const CSol * this);
  
  void (* AfficherCube)(const CSol * this, float x1, float y1, float z1, float dx, float dy, float dz);
  //utiliser pour Debuguer
  
  float (* FacteurCompression)(const CSol * this, float j);
  float (* IndiceTemps)(const CSol * this, float j);
  /*ajouter une texture de sol (CSol * this, fichier s)
    indice_dans_bitmap représente la couleur des zones de cette texture dans le fichier
    chargé après dans ChargerIndiceTextureBitmap*/
  void (* AjouterTextureSol)(CSol * this, const char * s, int indice_dans_bitmap);
  
  /*charge le fichier bitmap qui contient les zones pour les textures
    il faut faire appel à ChargerIndiceTextureBitmap après avoir fait les
    AjouterTextureSol
    (CSol * this, à priori fichier_bitmap désigne un fichier dans le répertoire
    "../cartes/")*/
  void (* ChargerIndiceTextureBitmap)(CSol * this, const char * fichier_bitmap);
#if 0  
  void (* LookAt)(const CSol * this, float i, float j, float z); /*place la caméra au dessus du point (CSol * this, i, j)*/
  void (* LookAt)(const CSol * this, float i, float j, float z, float dist, float AngleXY, float AngleZ); /*place la caméra au dessus du point )(CSol * this, i, j)*/
#else
  void (* LookAt_vSimple)(const CSol * this, float i, float j, float z);
  void (* LookAt_vCompliquee)(const CSol * this, float i, float j, float z, float dist, float AngleXY, float AngleZ);
#endif
  void (* Render)(const CSol * this, int i1, int j1, int i2, int j2); /*dessine la partie du tore entre )(CSol * this, i1, j1) et )(CSol * this, i2, j2)*/
  void (* RenderEau)(const CSol * this, int i1, int j1, int i2, int j2);
  bool (* yatilEau)(const CSol * this, float i, float j, float z);
	
  /*affiche une image 2D en )(CSol * this, i, j) )(CSol * this, position centrale au sol), d'altitude z, de texture tex,
    et de taille définie*/
  void (* Blit)(CSol * this, float i, float j, float z, CTexture* tex, float taillex, float tailleh);
  void (* Cube)(CSol * this, float i, float j, float z, float taillex, float tailleh);
  //void (* PositionModulo)(const CSol * this, float& i, float& j);
  void (* PositionModulo)(const CSol * this, float * i_ptr, float * j_ptr);
  void (* MatricePourDessiner)(CSol * this, float i, float j);
  TPoint2D (* Differentiel)(const CSol * this, TPoint3D pos);

  
	
  /*donne en fonction de la position en theta le facteur de compression
    il est le plus élevé à l'extérieur du tore, le plus petit à l'intérieur
    et vaut 1 sur le dessus, ou le dessous*/
  void (* ChargerZ)(CSol * this, const char * filename);
  float (* GETZ)(const CSol * this, float x, float y);
	
  void (* MatricePour2D)(const CSol * this, float i, float j, float z);
	
  void (* glVertexTore)(const CSol * this, float x, float y, float z);
	
  void (* SetTemps)(CSol * this, float temps);
  float (* GetTemps)(const CSol * this);
	



  
};
DEFINE_NEW_OPERATOR_FOR_STRUCT(CSol);












#endif /* SOL_H */
