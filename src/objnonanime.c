#include "global.h"
#include "objnonanime.h"
//#include "nonanime/nonanime.hpp"
//#include "nonanime.h"
#include "nonanime/nonanime.h"


CObjNonAnime * CObjNonAnime_make_core(void) {
  MALLOC_BZERO(CObjNonAnime,this);
  
  ASSIGN_METHOD(CObjNonAnime,this,ReadDescriptionFile); 
  ASSIGN_METHOD(CObjNonAnime,this,SetAngleZ); 
  ASSIGN_METHOD(CObjNonAnime,this,Render); 

  return this; 
}; 


CObjNonAnime * CObjNonAnime_copy(const CObjNonAnime * o) {
  CObjNonAnime * this = CObjNonAnime_make_core(); 

  CPhysicalObj_copy_aux(&this -> parent, &o -> parent); 

  this -> angleZ = 0.0f; 
  this -> filename = strcopy(o -> filename); 
  
  this -> parent.Compressible_huh = o -> parent.Compressible_huh;
  this -> parent.Hostile_huh = o -> parent.Hostile_huh;
  this -> parent.Fixe_huh = o -> parent.Fixe_huh;
  
  this -> resobj3ds = o -> resobj3ds -> copy(o -> resobj3ds); 
  
  return this; 
};

void CObjNonAnime_delete(CObjNonAnime * this) {
  this -> resobj3ds -> delete(this -> resobj3ds);        
  CPhysicalObj_delete_aux(&this -> parent); 
  free(this); 
};

CObjNonAnime * CObjNonAnime_make(const char * filename) {
  CObjNonAnime * this = CObjNonAnime_make_core(); 

  CPhysicalObj_make_aux(&this -> parent, CPhysicalObj_subtype_CObjNonAnime, filename); 

  this -> resobj3ds = NULL; 
  this -> angleZ = 0.0f; 
  this -> filename = strcopy(filename); 

  this -> parent.Compressible_huh = true;  
  this -> parent.Hostile_huh = false;
  this -> parent.Fixe_huh = true;

  
  int ret;
  ret = this -> ReadDescriptionFile(this, NONANIMESDIR, filename);

  if (0 == ret)
    printf("Création de l'objet non animé réalisé avec succès!!\n");
  else {
    messerr("Erreur lors de la lecture du fichier de description l'objet non-anime.");
    assert(false);
  }
  
  return this; 
};



void CObjNonAnime__Render(const CObjNonAnime * this, const CSol * sol, const riemann_t * our_manifold) { 
#if 0 
  if (0 != strcmp(filename, "./heros.anime")) { 
    fprintf(stderr, "ObjNonAnime: Rendering: %s\n", filename); 
    fflush(NULL); 
  }; 
#endif
  
  const CPhysicalObj * parent = &this -> parent; 
  parent -> Render(parent, our_manifold); 
  
  glPushMatrix(); { 
    
    // RL: This is a change of origin and a change of the tangent vector basis: local coordinates. 
    our_manifold -> MatricePour2D(our_manifold, /*map_i*/0, /*map_j*/0, parent -> p.x, parent -> p.y, parent -> p.z); 
    
    // RL: Now onwards, we are in map-local coordinates. 
    
    glRotatef(90.0f, 1.0, 0.0, 0.0); // RL: π/2 x-axis rotation. // RL: Awkwardly, 'glRotate' uses degrees. 
    glRotatef(this -> angleZ * 180.0f/PI, 0.0, 1.0, 0.0); // RL: π y-axis rotation. // RL: Awkwardly, 'glRotate' uses degrees. 
    
    if (parent -> Compressible_huh) { 
      const float FacteurCompression = our_manifold -> FacteurCompression(our_manifold, /*map_j*/0, parent -> p.y); 
      glScalef(1.0f, 1.0f, FacteurCompression); 
    }; 
    
    this -> resobj3ds -> Render(this -> resobj3ds); 
    
  } glPopMatrix(); 
}; 



void CObjNonAnime__SetAngleZ(CObjNonAnime * this, const float thetaZ) {  
  this -> angleZ = thetaZ;
}; 



int CObjNonAnime__ReadDescriptionFile(CObjNonAnime * this, const char * dir, const char * filename) {
  nonanime_t * nonanime_data = NULL; 

  { 
    char nonanime_fullpath[strlen(dir) + strlen(filename) + 1];
    strcat(strcpy(nonanime_fullpath, dir), filename); 
#define LOG_SUFF ".log"
    char nonanime_log[strlen(LOGDIR) + strlen(filename) + strlen(LOG_SUFF) + 1];
    strcat(strcat(strcpy(nonanime_log, LOGDIR), filename), LOG_SUFF);
    nonanime_data = nonanime_make_from_file(nonanime_fullpath, nonanime_log); 
  }; 
  
  this -> parent.SetDimension(&this -> parent, nonanime_data -> choc_longueur, nonanime_data -> choc_hauteur, nonanime_data -> choc_hauteur);
  if (NULL == this -> parent.filename) this -> parent.filename = strcopy(filename);
  this -> parent.Compressible_huh = nonanime_data -> compressible; 
  this -> parent.Fixe_huh = nonanime_data -> fixe; 
  this -> parent.pvmax = nonanime_data -> vie; 
  
  if (0 < nonanime_data -> elements_nb) { 
    this -> resobj3ds = C3DS__make(nonanime_data -> elements_image[0]);
  }; 
  if (NULL == this -> filename) this -> filename = strcopy(filename);
  
  nonanime_delete(nonanime_data); 
      
  return 0; 
}; 

