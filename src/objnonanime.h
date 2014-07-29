#ifndef OBJNONANIME_HPP
#define OBJNONANIME_HPP

#include "ressource.hpp"

class CPhysicalObj;
#include "physicalobj.hpp"



// Un objet non animé (arbre, maison...) est un objet physique... plus des données graphiques!!
class CObjNonAnime : public CPhysicalObj {
private:
  friend int yynonanimeparse(void);
  ressource<C3DS> * resobj3ds;
  int parse(const char * dir, const char * filename);
  float angleZ;
    
public:
  //* chargement d'un objet non animé (par exemple : arbre.nonanime) */
  CObjNonAnime(const char * filename);
  CObjNonAnime(const CObjNonAnime * o);
  
  void SetAngleZ(float thetaZ);
  ~CObjNonAnime(void);
        
  void Render(const CSol * sol) const;

public:
  const char * const filename;
};    





#endif /* OBJNONANIME_HPP */
