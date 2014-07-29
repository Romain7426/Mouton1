#include "global.hpp"
#include "texture.hpp"



bool tester_extension(const char * fichier_image, const char * extension) {
  char ext[3] = {0, 0, 0};
  int i = 0;   

  while (fichier_image[i] != '\0') {
    ext[0] = ext[1];
    ext[1] = ext[2];
    ext[2] = fichier_image[i];
    i++;
  }    
  
  return (ext[0] == extension[0]) && (ext[1] == extension[1]) && (ext[2] == extension[2]);
}    




CTexture::CTexture(const char * fichier_image) {
  char * reelfile;
  reelfile = new char[strlen(TEXTURESDIR) + strlen(fichier_image) + 1];
  strcat(strcpy(reelfile, TEXTURESDIR), fichier_image);
  fichier_image = reelfile;

  erreur = false;
  printf("Chargement de la texture '%s'...\n", fichier_image);
  SDL_Surface * texture;
         
  texture = IMG_Load(fichier_image);

  if (texture == NULL) {
    erreur = true;
    printf("  ERREUR : Impossible de charger le fichier image '%s'\n",fichier_image);
  }
  else {
    printf("  Chargement réussi.\n");
    printf("  Taille de l'image : %i, %i\n", texture->w, texture->h);
    printf("  Nombre d'octets par pixels : %i\n", texture ->format->BytesPerPixel);
    printf("  Pointeur pixel (juste pour tester) : %p\n", texture -> pixels);
    taillex = texture->w;
    tailley = texture->h;

#if 1
    printf("  On la convertie en un format potable (RGB ou RGBA).\n");
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
#endif

    
    glGenTextures(1, &tex_ind);
    printf("  Numéro OpenGL de texture généré : %u\n", (unsigned int) tex_ind);
    //génère un numéro de texture de libre
    
    glBindTexture(GL_TEXTURE_2D, tex_ind);
    //texture courante = texture_name (sur laquelle on va faire les modifs)
    
    // Jonction entre OpenGL et SDL.
    if (texture ->format->BytesPerPixel == 3) {
      //glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->w, texture->h, 0, GL_RGB, GL_UNSIGNED_BYTE, (unsigned char *) (texture -> pixels));
      gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texture -> w, texture -> h, GL_RGB, GL_UNSIGNED_BYTE, (unsigned char *) (texture -> pixels));    
    }
    else if (texture ->format->BytesPerPixel == 4) {
      //gluBuild2DMipmaps(GL_TEXTURE_2D, 4,
      glTexImage2D (GL_TEXTURE_2D, 0, 4, texture->w, texture->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char *) (texture -> pixels));
    }


#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif        
    // Paramétrage de la texture.
    //GL_CLAMP, GL_REPEAT, GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//GL_CLAMP_TO_EDGE); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      
    const GLfloat tab[4] = {0.0f,0.0f,0.0f,0.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, tab);
    
    // gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pBitmap[0]->w, pBitmap[0]->h, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    printf("  Jonction OpenGL/SDL effectué (code erreur : %d)\n\n", (int) glGetError());
    SDL_FreeSurface(texture);
  }
        
  delete[] reelfile;
}




void CTexture::GLTextureCourante() {
  if (erreur) 
    glDisable( GL_TEXTURE_2D);
  else {
    glBindTexture (GL_TEXTURE_2D, tex_ind); 
    // Paramétrage de la texture.
#if 0
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //GL_CLAMP); //GL_CLAMP_TO_EDGE); //GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //GL_CLAMP); //GL_CLAMP_TO_EDGE); //GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#endif
  }
    
}



CTexture::~CTexture() {
  if (!erreur) {
    glDeleteTextures(1, &tex_ind);
  }
}

