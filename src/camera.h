#ifndef CAMERA_H
#define CAMERA_H

extern TDirection ConvertirDirectionAvecVue(const TDirection d, const struct CCamera * Camera);
extern TDirection ConvertirDirectionAvecVue2(const TDirection d, const struct CCamera * Camera);

enum TZoomMethod { TZoomMethod_Absolu, TZoomMethod_Relatif }; 
typedef enum TZoomMethod TZoomMethod; 

enum {               CCamera_bytesize = 256 }; 
extern const int16_t CCamera_bytesize_actual; 
static void CCamera__check_and_assert(const int8_t debug_print_huh, const int stderr_d) { 
  if (debug_print_huh) { 
    //fprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "I failed to clean up the log subdir.' " "\n", __func__); 
    write_string4(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<", __func__, "()>}: ", "CCamera_bytesize: "); write_long_long_int(stderr_d, CCamera_bytesize); write_eol(stderr_d); 
    write_string4(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<", __func__, "()>}: ", "CCamera_bytesize_actual: "); write_long_long_int(stderr_d, CCamera_bytesize_actual); write_eol(stderr_d); 
  }; 
  assert(CCamera_bytesize >= CCamera_bytesize_actual); 
}; 

extern CCamera * CCamera__make(void);
extern CCamera * CCamera__make_aux(CCamera * this);
extern void CCamera__delete(CCamera * this);
extern bool CCamera__IsSolidaireAuHeros(const struct CCamera * this);
extern void CCamera__InitCamera(struct CCamera * this);
extern void CCamera__SolidariserAuHeros(struct CCamera * this);
extern void CCamera__DeSolidariser(struct CCamera * this);
//extern void CCamera__CalcCamera(struct CCamera * this, const struct CBonhomme * Hero, const struct CMap * Map);
//extern void CCamera__CalcCamera(CCamera * this, const CBonhomme * Hero, const int lattice_width, const int lattice_height, const riemann_t * our_manifold); 
extern void CCamera__CalcCamera(CCamera * this, const CBonhomme * Hero, const float lattice_to_map_scale_factor__x, const float lattice_to_map_scale_factor__y, const float lattice_to_map_scale_factor__z, const riemann_t * our_manifold); 
extern void CCamera__Blit(const CCamera * this, const riemann_t * our_manifold); 
extern void CCamera__EffetPsychadelique(struct CCamera * this);
extern void CCamera__SetDist(struct CCamera * this, float d); 
extern void CCamera__Zoom(CCamera * this, const TZoomMethod zoom_method, const float zoom_factor); 

extern float    * CCamera__angleXY                 (CCamera * this);  
extern float    * CCamera__angleZ                  (CCamera * this); 
extern float    * CCamera__lattice__dist           (CCamera * this); 
extern TPoint3D * CCamera__lattice__target_position(CCamera * this); 
extern TPoint3D * CCamera__map__target_position    (CCamera * this); 


#endif /* CAMERA_H */
