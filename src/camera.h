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
  /********* les paramètres cools**************/

  /*le point que regarde la caméra (prévoir une instruction pour affecter
    ce paramètre en abs et en relatif*/
  TPoint3D pos;
  
  /*les angles de vues en radian... angleXY pour touner autour de uz... angleHB
    pour regarder de plus haut ou plus bas*/
  float angleXY, angleHB;


  //struct CCamera(void);
  
  
  bool (* IsSolidaireAuHeros)(const struct CCamera * this);
 
  void (* InitCamera)(struct CCamera * this);
  //initialise les paramètres pour une vue de jeu normal

  //attache la caméra au héros
  void (* SolidariserAuHeros)(struct CCamera * this);
  
  /*désattache la caméra au héros.
    le point courant est alors la dernier position du héros lorsqu'il 
    était encore lié à la caméra*/
  void (* DeSolidariser)(struct CCamera * this);
  
  /**** ne pas prévoir d'instructions pascal pour ça... 
	CalcCamera est automatiquement appelé dans RaiseRender)(struct CCamera * this)*/
  void (* CalcCamera)(struct CCamera * this, const struct CBonhomme * Hero, const struct CMap * Map);
  
  
  void (* EffetPsychadelique)(struct CCamera * this);
  /*c'est nul*/
  
  void (* SetDist)(struct CCamera * this, float d);
  /*distance de laquelle on regarde. plus c petit, plus on est près du point qu'on regarde*/

};




#endif /* CAMERA_H */
