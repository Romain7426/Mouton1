#ifndef TEXTURE_H
#define TEXTURE_H

enum {              CTexture_bytesize = 32 }; 
extern const int8_t CTexture_bytesize_actual; 
extern CTexture *   CTexture_make              (const char     * fichier_image); 
extern void         CTexture_delete            (      CTexture * this); 
extern CTexture *   CTexture_copy              (const CTexture * src); 
extern void         CTexture__GLTextureCourante(const CTexture * this); 
extern float        CTexture__taillex          (      CTexture * this); 
extern float        CTexture__tailley          (      CTexture * this); 

static void CTexture__check_and_assert(const int8_t debug_print_huh, const int stderr_d); 





static void CTexture__check_and_assert(const int8_t debug_print_huh, const int stderr_d) { 

  if (debug_print_huh) { 
    //fprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "I failed to clean up the log subdir.' " "\n", __func__); 
    write_string4(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<", __func__, "()>}: ", "CTexture_bytesize: "); write_long_long_int(stderr_d, CTexture_bytesize); write_eol(stderr_d); 
    write_string4(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<", __func__, "()>}: ", "CTexture_bytesize_actual: "); write_long_long_int(stderr_d, CTexture_bytesize_actual); write_eol(stderr_d); 
  }; 
  assert(CTexture_bytesize >= CTexture_bytesize_actual); 
  
}; 

#endif /* TEXTURE_H */
