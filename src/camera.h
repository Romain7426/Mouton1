#ifndef CAMERA_H
#define CAMERA_H


struct TPoint2D;
struct TPoint3D;

#include "structures.h"
#include "vectors.h"

struct CBonhomme;
struct CMap;

struct CCamera;

TDirection ConvertirDirectionAvecVue(TDirection d, struct CCamera Camera);
TDirection ConvertirDirectionAvecVue2(TDirection d, struct CCamera Camera);

#define dist_defaut 150.0f



struct CCamera {
  //private://pas touche !!
  bool solidaire_au_heros;
  float a_dist, dist;
  int anim;
  
  //public:
  /********* les param�tres cools**************/

  /*le point que regarde la cam�ra (pr�voir une instruction pour affecter
    ce param�tre en abs et en relatif*/
  TPoint3D pos;
  
  /*les angles de vues en radian... angleXY pour touner autour de uz... angleHB
    pour regarder de plus haut ou plus bas*/
  float angleXY, angleHB;


  //struct CCamera(void);
  
  
  bool (* IsSolidaireAuHeros)(const struct CCamera * this);
 
  void (* InitCamera)(struct CCamera * this);
  //initialise les param�tres pour une vue de jeu normal

  //attache la cam�ra au h�ros
  void (* SolidariserAuHeros)(struct CCamera * this);
  
  /*d�sattache la cam�ra au h�ros.
    le point courant est alors la dernier position du h�ros lorsqu'il 
    �tait encore li� � la cam�ra*/
  void (* DeSolidariser)(struct CCamera * this);
  
  /**** ne pas pr�voir d'instructions pascal pour �a... 
	CalcCamera est automatiquement appel� dans RaiseRender)(struct CCamera * this)*/
  void (* CalcCamera)(struct CCamera * this, const struct CBonhomme * Hero, const struct CMap * Map);
  
  
  void (* EffetPsychadelique)(struct CCamera * this);
  /*c'est nul*/
  
  void (* SetDist)(struct CCamera * this, float d);
  /*distance de laquelle on regarde. plus c petit, plus on est pr�s du point qu'on regarde*/

};




#endif /* CAMERA_H */
