#include "global.h"
#include "objnonanime.h"
//#include "nonanime/nonanime.hpp"
//#include "nonanime.h"
//#include "nonanime/nonanime.h"
#include <nonanime/nonanime.h>

#define DEBUG_TRACE 1

CObjNonAnime * CObjNonAnime__make_core(void) {
  MALLOC_BZERO(CObjNonAnime,this);
  
  ASSIGN_METHOD(CObjNonAnime,this,make); 
  ASSIGN_METHOD(CObjNonAnime,this,copy); 
  ASSIGN_METHOD(CObjNonAnime,this,delete); 
  ASSIGN_METHOD(CObjNonAnime,this,ReadDescriptionFile); 
  ASSIGN_METHOD(CObjNonAnime,this,SetAngleZ); 
  ASSIGN_METHOD(CObjNonAnime,this,Render); 

  return this; 
}; 


CObjNonAnime * CObjNonAnime__copy(const CObjNonAnime * o) {
  CObjNonAnime * this = CObjNonAnime__make_core(); 

  CPhysicalObj__copy_aux(&this -> parent, &o -> parent); 

  this -> angleZ   = 0.0f; 
  this -> filename = strcopy(o -> filename); 
  
  this -> parent.Compressible_huh = o -> parent.Compressible_huh;
  this -> parent.Hostile_huh      = o -> parent.Hostile_huh;
  this -> parent.Fixe_huh         = o -> parent.Fixe_huh;
  
  this -> resobj3ds = o -> resobj3ds -> copy(o -> resobj3ds); 
  
  return this; 
};

void CObjNonAnime__delete(CObjNonAnime * this) {
  this -> resobj3ds -> delete(this -> resobj3ds);        
  CPhysicalObj__delete_aux(&this -> parent); 
  free(this); 
};

CObjNonAnime * CObjNonAnime__make(const char * filename) {
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  CObjNonAnime * this = CObjNonAnime__make_core(); 

#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  CPhysicalObj__make_aux(&this -> parent, CPhysicalObj_subtype_CObjNonAnime, filename); 

  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 

#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  this -> resobj3ds = NULL; 
  this -> angleZ    = 0.0f; 
  this -> filename  = strcopy(filename); 

  this -> parent.Compressible_huh = true;  
  this -> parent.Hostile_huh = false;
  this -> parent.Fixe_huh = true;

  
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  int ret;
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  fflush(NULL); 
  ret = this -> ReadDescriptionFile(this, NONANIMESDIR, filename);
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 

#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  if (0 == ret) { 
    //printf("Création de l'objet non-animé réalisée avec succès!!" "\n"); 
  } 
  else { 
    messerr("Erreur lors de la lecture du fichier de description l'objet non-anime: '%s' " "\n", filename); 
    //assert(false); 
    return NULL; 
  }; 
  
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  return this; 
};



//void CObjNonAnime__Render(const CObjNonAnime * this, const int lattice_width, const int lattice_height, const riemann_t * our_manifold) { 
void CObjNonAnime__Render(const CObjNonAnime * this, const float lattice_to_map_scale_factor__x, const float lattice_to_map_scale_factor__y, const float lattice_to_map_scale_factor__z, const riemann_t * our_manifold) { 
#if 0 
  if (0 != strcmp(filename, "./heros.anime")) { 
    fprintf(stderr, "ObjNonAnime: Rendering: %s\n", filename); 
    fflush(NULL); 
  }; 
#endif
  
  const CPhysicalObj * parent = &this -> parent; 
  //parent -> Render(parent, lattice_width, lattice_height, our_manifold); 
  parent -> Render(parent, lattice_to_map_scale_factor__x, lattice_to_map_scale_factor__y, lattice_to_map_scale_factor__z, our_manifold); 
  
  glPushMatrix(); { 
    
#if 1 
    // RL: This is a change of origin and a change of the tangent vector basis: local coordinates. 
    our_manifold -> MatricePour2D(our_manifold, /*map_i*/0, /*map_j*/0, parent -> p.x * lattice_to_map_scale_factor__x, parent -> p.y * lattice_to_map_scale_factor__y, parent -> p.z  * lattice_to_map_scale_factor__z); 
    glScalef(lattice_to_map_scale_factor__x, lattice_to_map_scale_factor__y, lattice_to_map_scale_factor__z); 
    glScalef(0.05f, 0.05f, 0.05f); // RL: Constant factor. Figured out of the blue. 
#else 
    // RL: This is a change of origin and a change of the tangent vector basis: local coordinates. 
    our_manifold -> MatricePour2D(our_manifold, /*map_i*/0, /*map_j*/0, parent -> p.x / (float) lattice_width, parent -> p.y / (float) lattice_height, parent -> p.z); 
    
    //glScalef(1.0f / lattice_width, 1.0f / lattice_height, 1.0f); 
    //glScalef(1.0f / lattice_width, 1.0f / lattice_height, 1.0f); 
    //glScalef(0.05f, 0.05f, 1.0f); // RL: Constant factor. Figured out of the blue. 
    const float lattice_depth = (lattice_width + lattice_height) / 2.0f; 
    glScalef(1.0f / lattice_width, 1.0f / lattice_height, 1.0f / lattice_depth); 
    glScalef(0.05f, 0.05f, 40.0f); // RL: Constant factor. Figured out of the blue. 
#endif 
    
    // RL: Now onwards, we are in map-local coordinates. 
    
    glRotatef(90.0f, 1.0, 0.0, 0.0); // RL: π/2 x-axis rotation. // RL: Awkwardly, 'glRotate' uses degrees. 
    glRotatef(this -> angleZ * 180.0f/PI, 0.0, 1.0, 0.0); // RL: π y-axis rotation. // RL: Awkwardly, 'glRotate' uses degrees. 

#if 0     
    if (parent -> Compressible_huh) { 
      const float FacteurCompression = our_manifold -> FacteurCompression(our_manifold, /*map_j*/0, parent -> p.y / (float) lattice_height); 
      glScalef(1.0f, 1.0f, FacteurCompression); 
    }; 
#endif 
    
    this -> resobj3ds -> Render(this -> resobj3ds); 
    //this -> resobj3ds -> RenderGL(this -> resobj3ds); 
    
  } glPopMatrix(); 
}; 



void CObjNonAnime__SetAngleZ(CObjNonAnime * this, const float thetaZ) {  
  this -> angleZ = thetaZ;
}; 



int CObjNonAnime__ReadDescriptionFile(CObjNonAnime * this, const char * dir, const char * filename) { 
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  nonanime_t * nonanime_data = NULL; 
  CObjActionnable * this_action = this -> parent.actions; 
  
  { 
    // For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
    //char nonanime_fullpath[strlen(dir) + strlen(filename) + 1]; 
    enum { nonanime_fullpath__bytesize = 1 << 10 }; 
    const size_t nonanime_fullpath__cstrlen = strlen(dir) + strlen(filename); 
    assert(nonanime_fullpath__bytesize > nonanime_fullpath__cstrlen); 
    char nonanime_fullpath[nonanime_fullpath__bytesize]; 
    strcat(strcpy(nonanime_fullpath, dir), filename); 
#define LOG_SUFF ".log" 
    // For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
    //char nonanime_log[strlen(LOGDIR) + strlen(filename) + strlen(LOG_SUFF) + 1]; 
    enum { nonanime_log__bytesize = 1 << 10 }; 
    const size_t nonanime_log__cstrlen = strlen(LOGDIR) + strlen(filename) + strlen(LOG_SUFF); 
    assert(nonanime_log__bytesize > nonanime_log__cstrlen); 
    char nonanime_log[nonanime_log__bytesize]; 
    strcat(strcat(strcpy(nonanime_log, LOGDIR), filename), LOG_SUFF); 
    //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
    nonanime_data = nonanime_make_from_file(nonanime_fullpath, nonanime_log); 
    //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
    if (nonanime_data == NULL) { return -1; }; 
  }; 
  
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  this -> parent.SetDimension(&this -> parent, nonanime_data -> choc_longueur, nonanime_data -> choc_largeur, nonanime_data -> choc_hauteur); 
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  if (NULL == this -> parent.filename) this -> parent.filename = strcopy(filename); 
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  this -> parent.Compressible_huh = nonanime_data -> compressible; 
  this -> parent.Fixe_huh         = nonanime_data -> fixe; 
  this -> parent.pvmax            = nonanime_data -> vie; 
  
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  if (0 < nonanime_data -> elements_nb) { 
    this -> resobj3ds = C3DS__make(nonanime_data -> elements_image[0]); 
  }; 
  
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  if (NULL == this -> filename) this -> filename = strcopy(filename); 
  
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  fflush(NULL); 
  for (int i = 0; i < nonanime_data -> actions_nb; i++) { 
#if 1 
    this_action -> AjouterAction(this_action, nonanime_data -> actions_array_affichage[i], nonanime_data -> actions_array_icone[i], nonanime_data -> actions_array_gestionnaire_fichier[i], nonanime_data -> actions_array_gestionnaire_proc[i]); 
#endif 
  };  
  
  
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  
  nonanime_delete(nonanime_data); 
  
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  return 0; 
}; 

