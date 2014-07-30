#ifndef OBJNONANIME_H
#define OBJNONANIME_H

//#include "ressource.hpp"

struct CPhysicalObj;
#include "physicalobj.h"



// Un objet non animé (arbre, maison...) est un objet physique... plus des données graphiques!!
struct CObjNonAnime /* : public CPhysicalObj */ {
  struct CPhysicalObj parent;
  //private:
  //friend int yynonanimeparse(void);
  //ressource<C3DS> * resobj3ds;
  struct C3DS * resobj3ds[128];
  float angleZ;
  //public:
  const char * const filename;
    
  //public:
#if 0
  //* chargement d'un objet non animé (par exemple : arbre.nonanime) */
  CObjNonAnime(const char * filename);
  CObjNonAnime(const CObjNonAnime * o);
  ~CObjNonAnime(void);
#endif
  
  int (* parse)(struct CObjNonAnime * this, const char * dir, const char * filename);
  void (* SetAngleZ)(struct CObjNonAnime * this, float thetaZ);
  void (* Render)(const struct CObjNonAnime * this, const CSol * sol);

};    





#endif /* OBJNONANIME_H */
