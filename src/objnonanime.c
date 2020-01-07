#include "global.h"
#include "objnonanime.h"
//#include "nonanime/nonanime.hpp"
#include "nonanime.h"


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
  
  this -> parent.Compressible = o -> parent.Compressible;
  this -> parent.Hostile = o -> parent.Hostile;
  this -> parent.Fixe = o -> parent.Fixe;
  
  this -> resobj3ds = C3DS_copy(o -> resobj3ds); 
  
  return this; 
};

void CObjNonAnime_delete(CObjNonAnime * this) {
  C3DS_delete(this -> resobj3ds);        
  CPhysicalObj_delete(&this -> parent); 
  free(this); 
};

CObjNonAnime * CObjNonAnime_make(const char * filename) {
  CObjNonAnime * this = CObjNonAnime_make_core(); 

  CPhysicalObj_make_aux(&this -> parent, CPhysicalObj_subtype_CObjNonAnime, filename); 

  this -> resobj3ds = NULL; 
  this -> angleZ = 0.0f; 
  this -> filename = strcopy(filename); 

  this -> parent.Compressible = true;  
  this -> parent.Hostile = false;
  this -> parent.Fixe = true;
  
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



void CObjNonAnime__Render(const CObjNonAnime * this, const CSol * sol) {
#if 0
  if (0 != strcmp(filename, "./heros.anime")) {
    fprintf(stderr, "ObjNonAnime: Rendering: %s\n", filename);
    fflush(NULL);
  }
#endif

  const CPhysicalObj * parent = &this -> parent; 
  parent -> Render(parent, sol);   
  
  glPushMatrix(); {

    sol -> MatricePour2D(sol, parent -> p.x, parent -> p.y, parent -> p.z);

    glRotatef(90.0f, 1.0, 0.0, 0.0);
    glRotatef(this -> angleZ * 180.0f/PI, 0.0, 1.0, 0.0);

    if (parent -> Compressible)
      glScalef(1.0f, 1.0f, sol -> FacteurCompression(sol, parent -> p.y));
    
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
    nonanime_data = nonanime_make_from_file(nonanime_fullpath); 
  }; 
  
  this -> parent.SetDimension(&this -> parent, nonanime_data -> choc_longueur, nonanime_data -> choc_hauteur, nonanime_data -> choc_hauteur);
  if (NULL == this -> parent.filename) this -> parent.filename = strcopy(filename);
  this -> parent.Compressible = nonanime_data -> compressible; 
  this -> parent.Fixe = nonanime_data -> fixe; 
  this -> parent.pvmax = nonanime_data -> vie; 
  
  if (0 < nonanime_data -> elements_nb) { 
    this -> resobj3ds = C3DS_make(nonanime_data -> elements_image[0]);
  }; 
  if (NULL == this -> filename) this -> filename = strcopy(filename);
  
  nonanime_delete(nonanime_data); 
      
  return 0; 
}; 

