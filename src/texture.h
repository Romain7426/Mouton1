#ifndef TEXTURE_H
#define TEXTURE_H


struct CTexture {
  GLuint tex_ind; // indice de la texture dans OpenGL 
  int internal_ind; // indice interne 
  
  bool erreur;
        
  /*taille en pixel de toute la texture*/
  float taillex, tailley;
        
  /*pour définir cette texture comme étant la texture courante*/
  void (* GLTextureCourante)(const CTexture * this);
}; 
 
extern CTexture * CTexture_make(const char * fichier_image); 
extern void CTexture_delete(CTexture * this); 
extern CTexture * CTexture_copy(const CTexture * src); 
extern void CTexture__GLTextureCourante(const CTexture * this); 



#endif /* TEXTURE_H */
