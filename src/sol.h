#ifndef SOL_H 
#define SOL_H 

enum {              CSol_bytesize = 512 }; 
extern const int16_t CSol_bytesize_actual; 
static void CSol__check_and_assert(const int8_t debug_print_huh, const int stderr_d) { 
  if (debug_print_huh) { 
    //fprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "I failed to clean up the log subdir.' " "\n", __func__); 
    write_string4(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<", __func__, "()>}: ", "CSol_bytesize: "); write_long_long_int(stderr_d, CSol_bytesize); write_eol(stderr_d); 
    write_string4(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<", __func__, "()>}: ", "CSol_bytesize_actual: "); write_long_long_int(stderr_d, CSol_bytesize_actual); write_eol(stderr_d); 
  }; 
  assert(CSol_bytesize >= CSol_bytesize_actual); 
}; 

#if 1 
struct CSol_module_t; 
typedef struct CSol_module_t CSol_module_t; 
struct CSol_module_t {
  CSol * (* make          )(void); 
  CSol * (* make_content  )(CSol * this); 
  void   (* delete        )(CSol * this); 
  void   (* delete_content)(CSol * this); 
}; 
//extern const CSol_module_t * CSol_module; 
extern const CSol_module_t CSol_module[1]; 
#endif 

enum { NB_MAX_TEXTURESOL   =  10 }; 

extern CSol * CSol__make(void); 
extern CSol * CSol__make_content(CSol * this); 
extern void   CSol__delete(CSol * this); 
extern void   CSol__delete_content(CSol * this); 

extern void   CSol__RenderEau(const CSol * this, const riemann_t * our_manifold, const int global_map_i, const int global_map_j, const float target_map_x, const float target_map_y, const float target_map_dx, const float target_map_dy); 

extern void   CSol__Render__pre_computations(CSol * this, const riemann_t * our_manifold, const int global_map_i, const int global_map_j, const float target_map_x, const float target_map_y, const float target_map_dx, const float target_map_dy); 
extern float  CSol__GET_MAP_Z(const CSol * this, const float map_x, const float map_y); 
extern float  CSol__map_ZEau(const CSol * this); 
extern float * CSol__map_ZEau_ref(CSol * this); 
extern void   CSol__Life(const CSol * this); 
extern void   CSol__Render(const CSol * this, const riemann_t * our_manifold, const int global_map_i, const int global_map_j, const float target_map_x, const float target_map_y, const float target_map_dx, const float target_map_dy);
extern int    CSol__AjouterTextureSol(      CSol * this, const char * fichier_texture, const uint32_t couleur_dans_bitmap); 
extern int    CSol__init(CSol * this, const int global_map_i, const int global_map_j, const int over_spanning_w, const int over_spanning_h, const float lattice_to_map_scale_factor__z, const riemann_t * our_manifold, const char * z_filename, const char * texture_filename); 








#endif /* SOL_H */
