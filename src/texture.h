#ifndef TEXTURE_H
#define TEXTURE_H

enum {              CTexture_bytesize = 32 }; 
extern const int8_t CTexture_bytesize_actual; 
extern CTexture *   CTexture_make              (const char     * fichier_image); 
extern void         CTexture_delete            (      CTexture * this); 
extern CTexture *   CTexture_copy              (const CTexture * src); 
extern void         CTexture__GLTextureCourante(const CTexture * this); 
extern float        CTexture__taillex          (const CTexture * this); 
extern float        CTexture__tailley          (const CTexture * this); 

static void CTexture__check_and_assert(void) { 
  assert(CTexture_bytesize >= CTexture_bytesize_actual); 
}; 

#endif /* TEXTURE_H */
