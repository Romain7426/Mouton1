#ifndef TEXTURE_HPP
#define TEXTURE_HPP


class CTexture {
private:
  GLuint tex_ind;
  //unsigned int tex_ind; 

  bool erreur;
        
public:
  /*taille en pixel de toute la texture*/
  float taillex, tailley;
        
  /*pour définir cette texture comme étant la texture courante*/
  void GLTextureCourante();
        
  /*pour charger la texture (fichier JPG, PNG etc...)*/
  CTexture(const char * fichier_image);
        
  /*libère la texture*/
  ~CTexture();
};    


#endif /* TEXTURE_HPP */
