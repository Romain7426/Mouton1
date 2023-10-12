#include "global.h"
#include "texture.h"

struct CTexture {
  GLuint tex_ind; // indice de la texture dans OpenGL 
  int dico_ind; // indice interne 
  
  bool erreur;
  
  // Taille en pixels de la texture. 
  float taillex; 
  float tailley; 
        
  // Pour dire à OpenGL que cette texture est la texture courante. 
  void (* GLTextureCourante)(const CTexture * this);
}; 
 
const int8_t CTexture_bytesize_actual = sizeof(struct CTexture); 
ASSERT_COMPILE_TOPLEVEL(CTexture_bytesize >= CTexture_bytesize_actual); 

static bool CTexture__charger_fichier_image_dans_OpenGL(const char * fichier_image, GLuint * glindice_ref, float * taillex_ref, float * tailley_ref); 

enum {            texture_dico_size = 512 }; 
static char *     texture_dico_filename[texture_dico_size] = {}; 
static CTexture * texture_dico_texture [texture_dico_size] = {}; 
static int8_t     texture_dico_usersnb [texture_dico_size] = {}; 
static int16_t    texture_dico_nb = 0; 


static int16_t texture_dico_push(const char * filename, CTexture * texture_non_copiee) {
  assert(texture_dico_nb < texture_dico_size); 
  texture_dico_filename[texture_dico_nb] = strcopy(filename); 
  texture_dico_texture[texture_dico_nb] = texture_non_copiee; 
  texture_dico_usersnb[texture_dico_nb] = 1; 
  texture_dico_nb++; 
  return texture_dico_nb-1; 
}; 

static int16_t texture_dico_lookup(const char * filename) {
  char * * p = texture_dico_filename; 
  for (int16_t i = 0; i < texture_dico_nb; i++) {
    if (0 == strcmp(*p, filename)) return i; 
    p++; 
  };
  return -1;
}; 

static CTexture * texture_dico_get(const int16_t i) {
  texture_dico_usersnb[i] ++; 
  return texture_dico_texture[i];
}; 

static void texture_dico_release(const int16_t i) {
  texture_dico_usersnb[i] --; 
}; 

static bool tester_extension(const char * fichier_image, const char * extension) {
  char ext[3] = {0, 0, 0};
  int i = 0;   

  while (fichier_image[i] != '\0') {
    ext[0] = ext[1];
    ext[1] = ext[2];
    ext[2] = fichier_image[i];
    i++;
  }    
  
  return (ext[0] == extension[0]) && (ext[1] == extension[1]) && (ext[2] == extension[2]);
};    

CTexture * CTexture_copy(const CTexture * src) {
#if 0
  MALLOC_BZERO(CTexture,this); 
  *this = *src; 
  // NA 
  return this; 
#else
  return texture_dico_get(src -> dico_ind); 
#endif 
}; 



CTexture * CTexture_make_and_push(const char * fichier_image) {
  //printf("Chargement de la texture '%s'...\n", fichier_image);

  MALLOC_BZERO(CTexture,this);
  
  ASSIGN_METHOD(CTexture,this,GLTextureCourante); 

  bool alright_huh; 
  alright_huh = CTexture__charger_fichier_image_dans_OpenGL(fichier_image, &this -> tex_ind, &this -> taillex, &this -> tailley); 

  this -> erreur = !alright_huh; 
  
  this -> dico_ind = texture_dico_push(fichier_image, this); 
  
  return this; 
};

CTexture * CTexture_make(const char * fichier_image) {
  //printf("Chargement de la texture '%s'...\n", fichier_image);

  const int16_t dico_ind = texture_dico_lookup(fichier_image); 
  if (dico_ind >= 0) { return texture_dico_get(dico_ind); }; 

  return CTexture_make_and_push(fichier_image); 
}; 

void CTexture_delete(CTexture * this) {
  texture_dico_release(this -> dico_ind); 
};

void CTexture_delete_hard(CTexture * this) {
  assert(false); 
  if (!this -> erreur) {
    glDeleteTextures(1, &this -> tex_ind);
  };
  free(this);
};


void CTexture__GLTextureCourante(const CTexture * this) {
  if (this -> erreur) 
    glDisable( GL_TEXTURE_2D);
  else {
    glBindTexture(GL_TEXTURE_2D, this -> tex_ind); 
    // Paramétrage de la texture.
#if 0
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //GL_CLAMP); //GL_CLAMP_TO_EDGE); //GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //GL_CLAMP); //GL_CLAMP_TO_EDGE); //GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#endif
  };  
};
























bool CTexture__charger_fichier_image_dans_OpenGL(const char * fichier_image, GLuint * glindice_ref, float * taillex_ref, float * tailley_ref) {
  //printf("Chargement de l'image '%s' dans OpenGL\n", fichier_image);
  
  char reelfile[strlen(TEXTURESDIR) + strlen(fichier_image) + 1];
  strcat(strcpy(reelfile, TEXTURESDIR), fichier_image);
  fichier_image = reelfile;

  SDL_Surface * texture = NULL;
  
  // On charge le bitmap en mémoire grâce à la SDL. 
  texture = IMG_Load(fichier_image);
  if (texture == NULL) {
    messerr("Impossible de charger le fichier image '%s'." "\n", fichier_image); 
#if 1 
    {
      char filename_realpath[PATH_MAX]; 
      if (NULL == realpath(fichier_image, filename_realpath)) { 
	messerr("REALPATH: %s" "\n", "File does not exist"); 
      } 
      else { 
	messerr("REALPATH: %s" "\n", filename_realpath); 
      }; 
    }; 
#endif 
#if 1 
    {
      messerr("SDL_image ERROR: %s" "\n", IMG_GetError()); 
    };
#endif 
    return false; 
  }; 
#if 0 
  printf("  Chargement réussi.\n");
  printf("  Taille de l'image : %i, %i\n", texture->w, texture->h);
  printf("  Nombre d'octets par pixels : %i\n", texture ->format->BytesPerPixel);
  printf("  Pointeur pixel (juste pour tester) : %p\n", texture -> pixels);
#endif 
  *taillex_ref = texture -> w;
  *tailley_ref = texture -> h;

  // On ne sait dans quel format est l'image. Nous, on ne connaît que RGB ou RGBA. 
  // Donc on demande à la SDL de la mettre en RGB ou en RGBA. 
  //printf("  On la convertie en un format potable (RGB ou RGBA).\n");
  {
    SDL_Surface * convertie;
    if (texture -> format -> BytesPerPixel == 4) {
      convertie = SDL_ConvertSurface(texture, &sdl_pixel_format_rgba, SDL_SWSURFACE);
    }
    else {
      convertie = SDL_ConvertSurface(texture, &sdl_pixel_format_rgb, SDL_SWSURFACE);
    }
    SDL_FreeSurface(texture);
    texture = convertie;
  }
  
  
  // Chargement du bitmap dans OpenGL. 
  {
    // Génération d'un numéro de texture OpenGL.  
    glGenTextures(1, glindice_ref);
    //printf("  Numéro OpenGL de texture généré : %u\n", (unsigned int) *glindice_ref);
    
    // Sélection de cette texture. 
    glBindTexture(GL_TEXTURE_2D, *glindice_ref); 
    
    // Chargement de la bitmap dans OpenGL. 
    if (texture ->format->BytesPerPixel == 3) {
      //glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->w, texture->h, 0, GL_RGB, GL_UNSIGNED_BYTE, (unsigned char *) (texture -> pixels));
      gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texture -> w, texture -> h, GL_RGB, GL_UNSIGNED_BYTE, (unsigned char *) (texture -> pixels));    
    }
    else if (texture ->format->BytesPerPixel == 4) {
      //gluBuild2DMipmaps(GL_TEXTURE_2D, 4,
      glTexImage2D (GL_TEXTURE_2D, 0, 4, texture->w, texture->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char *) (texture -> pixels));
    }
    else {
      assert(false); 
    }; 
    

    // Paramétrage de OpenGL pour la texture.
    {
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif        
      //GL_CLAMP, GL_REPEAT, GL_CLAMP_TO_EDGE
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//GL_CLAMP_TO_EDGE); 
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      
      const GLfloat tab[4] = {0.0f,0.0f,0.0f,0.0f};
      glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, tab);
    }; 
    
  }; 

  SDL_FreeSurface(texture);
  //printf("Chargement de l'image dans OpenGL à travers la SDL effectué (code OpenGL: %d)\n\n", (int) glGetError());
  return true; 
};



