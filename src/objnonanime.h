#ifndef OBJNONANIME_H 
#define OBJNONANIME_H 
 
// FS: Un objet non animé (arbre, maison...) est un objet physique... plus des données graphiques!! 
struct CObjNonAnime /* : public CPhysicalObj */ { 
  CPhysicalObj parent; 
  //ressource<C3DS> * resobj3ds; 
  C3DS * resobj3ds; 
  float angleZ; 
  char * filename; 


  // *** METHODS *** 
  
  CObjNonAnime * (* make               )(const char * filename); 
  CObjNonAnime * (* copy               )(const        CObjNonAnime * o); 
  void           (* delete             )(             CObjNonAnime * this); 
  int            (* ReadDescriptionFile)(      struct CObjNonAnime * this, const char * dir, const char * filename); 
  void           (* SetAngleZ          )(      struct CObjNonAnime * this, const float thetaZ); 
  //void           (* Render             )(const struct CObjNonAnime * this, const int lattice_width, const int lattice_height, const riemann_t * our_manifold); 
  void           (* Render             )(const CObjNonAnime * this, const float lattice_to_map_scale_factor__x, const float lattice_to_map_scale_factor__y, const float lattice_to_map_scale_factor__z, const riemann_t * our_manifold); 

}; 
extern CObjNonAnime * CObjNonAnime__make(const char * filename); 
extern CObjNonAnime * CObjNonAnime__copy(const CObjNonAnime * o); 
extern void CObjNonAnime__delete(CObjNonAnime * this); 
extern int  CObjNonAnime__ReadDescriptionFile(CObjNonAnime * this, const char * dir, const char * filename); 
extern void CObjNonAnime__SetAngleZ(CObjNonAnime * this, const float thetaZ); 
//extern void CObjNonAnime__Render(const CObjNonAnime * this, const int lattice_width, const int lattice_height, const riemann_t * our_manifold); 
extern void CObjNonAnime__Render(const CObjNonAnime * this, const float lattice_to_map_scale_factor__x, const float lattice_to_map_scale_factor__y, const float lattice_to_map_scale_factor__z, const riemann_t * our_manifold); 

#endif /* OBJNONANIME_H */ 
