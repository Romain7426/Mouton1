#ifndef OBJNONANIME_H 
#define OBJNONANIME_H 
 
// FS: Un objet non animé (arbre, maison...) est un objet physique... plus des données graphiques!! 
struct CObjNonAnime /* : public CPhysicalObj */ { 
  CPhysicalObj parent; 
  //ressource<C3DS> * resobj3ds; 
  C3DS * resobj3ds; 
  float angleZ; 
  char * filename; 
  
  int  (* ReadDescriptionFile)(      struct CObjNonAnime * this, const char * dir, const char * filename); 
  void (* SetAngleZ          )(      struct CObjNonAnime * this, const float thetaZ); 
  void (* Render             )(const struct CObjNonAnime * this, const CSol * sol, const riemann_t * our_manifold); 
}; 
extern CObjNonAnime * CObjNonAnime_make(const char * filename); 
extern CObjNonAnime * CObjNonAnime_copy(const CObjNonAnime * o); 
extern void CObjNonAnime_delete(CObjNonAnime * this); 
extern int  CObjNonAnime__ReadDescriptionFile(CObjNonAnime * this, const char * dir, const char * filename); 
extern void CObjNonAnime__SetAngleZ(CObjNonAnime * this, const float thetaZ); 
extern void CObjNonAnime__Render(const CObjNonAnime * this, const CSol * sol, const riemann_t * our_manifold); 

#endif /* OBJNONANIME_H */ 
