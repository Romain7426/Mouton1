#ifndef CAMERA_HPP
#define CAMERA_HPP


struct TPoint2D;
struct TPoint3D;

#include "structures.hpp"
#include "vectors.hpp"

class CBonhomme;
class CMap;

class CCamera;

TDirection ConvertirDirectionAvecVue(TDirection d, CCamera Camera);
TDirection ConvertirDirectionAvecVue2(TDirection d, CCamera Camera);

#define dist_defaut 150.0f



class CCamera {
private://pas touche !!
  bool solidaire_au_heros;
  float a_dist, dist;
  int anim;
  
public:
  /********* les paramètres cools**************/

  /*le point que regarde la caméra (prévoir une instruction pour affecter
    ce paramètre en abs et en relatif*/
  TPoint3D pos;
  
  /*les angles de vues en radian... angleXY pour touner autour de uz... angleHB
    pour regarder de plus haut ou plus bas*/
  float angleXY, angleHB;
  
  bool IsSolidaireAuHeros(void) const;
 
  void InitCamera(void);
  //initialise les paramètres pour une vue de jeu normal

  //attache la caméra au héros
  void SolidariserAuHeros(void);
  
  /*désattache la caméra au héros.
    le point courant est alors la dernier position du héros lorsqu'il 
    était encore lié à la caméra*/
  void DeSolidariser(void);
  
  /**** ne pas prévoir d'instructions pascal pour ça... 
	CalcCamera est automatiquement appelé dans RaiseRender(void)*/
  void CalcCamera(const CBonhomme * Hero, const CMap * Map);
  
  
  void EffetPsychadelique(void);
  /*c'est nul*/
  
  CCamera(void);
  
  void SetDist(float d);
  /*distance de laquelle on regarde. plus c petit, plus on est près du point qu'on regarde*/

};




#endif /* CAMERA_HPP */
