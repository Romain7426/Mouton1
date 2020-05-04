#ifndef STRUCTURES_H 
#define STRUCTURES_H 

#if 0 
/* 
 * structure pour les données de la souris
 * x, y : position
 * dx, dy : dernier déplacement 
 */
struct TMouse {int x,y,dx,dy;};
TYPEDEF_TYPENAME_WITHOUT_STRUCT(TMouse); 
#endif 

struct TColor {char r,v,b,a;};
TYPEDEF_TYPENAME_WITHOUT_STRUCT(TColor);


enum TDirection {FACE, PROFIL_VERS_D, DOS, PROFIL_VERS_G};
/* bas : 0, droite : 1, haut : 2, gauche : 3 */
TYPEDEF_TYPENAME_WITHOUT_ENUM(TDirection);

enum TModeJeu { 
 mjTITRE,  // au début, on affiche le titre 
 mjCARTE,  // mode normal 
 mjOEIL,   // 
 mjAEROTHEIERE, 
 mjINVENTAIRE,   // menu pour le choix des armes etc... 
 mjIDLE, // on est en train d'exécuter un script 
 mjTELEPORTATION, 
 mjNOMBRE 
};
TYPEDEF_TYPENAME_WITHOUT_ENUM(TModeJeu);



#endif /* STRUCTURES_H */ 
