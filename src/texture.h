#ifndef TEXTURE_H
#define TEXTURE_H


struct CTexture {
  //private:
  GLuint tex_ind;
  //unsigned int tex_ind; 

  bool erreur;
        
  //public:
  /*taille en pixel de toute la texture*/
  float taillex, tailley;
        
  /*pour d�finir cette texture comme �tant la texture courante*/
  void (* GLTextureCourante)(struct CTexture * this);
        
#if 0
  /*pour charger la texture (fichier JPG, PNG etc...)*/
  CTexture(const char * fichier_image);
        
  /*lib�re la texture*/
  ~CTexture();
#endif
};    


#endif /* TEXTURE_H */
