#ifndef RIEMANN_H 
#define RIEMANN_H 

#ifndef RIEMAN_TORUS_T 
#define RIEMAN_TORUS_T
struct riemann_torus_t; 
typedef struct riemann_torus_t riemann_torus_t; 
extern const int rieman_torus__sizeof; 
#endif 

#ifndef RIEMAN_RECTANGLE_T 
#define RIEMAN_RECTANGLE_T
struct riemann_rectangle_t; 
typedef struct riemann_rectangle_t riemann_rectangle_t; 
extern const int rieman_riemann__sizeof; 
#endif 

enum { RIEMANN_DATA__ALLOCATED_SIZEOF = 4*sizeof(float) + 2*sizeof(int8_t) + 2*sizeof(void*) }; 
extern const int riemann_data__needed_sizeof; 

enum { 
  RIEMANN_TYPE__NULL, 
  RIEMANN_TYPE__TORUS, 
  RIEMANN_TYPE__RECTANGLE, 
  RIEMANN_TYPE__COUNT 
  // HELITORE // RL: The covering space of the torus (FR: «le revêtement canonique du tore») 
  // PROJECTIVE_PLANE // RL: The issue here is the negative courbure...? 
  // SPHERE 
}; 

extern const char * riemann_type__get_cstr(const int riemann_type); 
#define riemann_type__cstr riemann_type__get_cstr 


// *** RIEMANNIAN MANIFOLDS *** 
// RL: Maps of the manifold are supposed to be [0..1]x[0..1]. 
// RL: The manifold is supposed to be divided in 'nb_maps_on_width' x 'nb_maps_on_height'.  

struct riemann_t; 
typedef struct riemann_t riemann_t; 
struct riemann_t { 
  int8_t type; 
  char data[RIEMANN_DATA__ALLOCATED_SIZEOF]; 
  riemann_torus_t     *     torus_data; 
  riemann_rectangle_t * rectangle_data; 
  
  int8_t w_nb; //nb_maps_on_width;   // RL: Number of maps in which the width  is divided. 
  int8_t h_nb; //nb_maps_on_height;  // RL: Number of maps in which the height is divided. 
  
  float map_to_manifold_factor__z; // RL: Computed 
  float manifold_z_scale_factor; // RL: User-given. 
  
  float temps; // RL: Our riemannian manifold is alive. 
               // RL: That's UTC time. It's the local time at manifold coordinate 0. 
               //     '0' is midnight, '0.5' is noon, '1' is a full day. 
               // RL: Scale-ly speaking, time-span for a day is '1' (half a day 0.5, etc.). 
               // RL: Technically speaking, When 'temps' is equal to '1', that means we loop around the "height" (the y-coordinate on the manifold). 
               // RL: Technically speaking, that changes the base of the 'y' coordinate for all objects, ground included. 
               // RL: TODO XXX FIXME: As of 2020-04-24, temps is directly moved forward by the kernel... Should be done through a 'Life' function. 
  float temps_pas; // RL: 'pas' is the resolution or sampling step («Finesse d'échantillonnage», «résolution»). 

  int8_t malloced_huh; 
  
  // *** METHODS *** 
  riemann_t * (* make                              )(void); 
  void        (* delete                            )(      riemann_t * this); 
  void        (* Life                              )(      riemann_t * this); 
  void        (* glVertexManifold                  )(const riemann_t * this, const int map_i, const int map_j, const float map_x, const float map_y, const float map_z); 
  TPoint3D    (* get_manifold_coordinates          )(const riemann_t * this, const int map_i, const int map_j, const float map_x, const float map_y, const float map_z); 
  void        (* temps__do_step                    )(      riemann_t * this); 
  void        (* temps__set                        )(      riemann_t * this, const float new_utc_time); 
  void        (* temps__bloque                     )(      riemann_t * this); 
  void        (* temps__debloque                   )(      riemann_t * this); 
  float       (* temps__get_local_time_at_y        )(const riemann_t * this, const int map_j, const float map_y); 
  float       (* temps__get_sunshine_intensity_at_y)(const riemann_t * this, const int map_j, const float map_y); // RL: Returns '0' when dark, '1' at zenith 
  float       (* FacteurCompression                )(const riemann_t * this, const int map_j, const float map_y); 
  void        (* manifold_z_scale_factor__set      )(      riemann_t * this, const float new_manifold_z_scale_factor); 
  void        (* MatricePour2D                     )(const riemann_t * this, const int map_i, const int map_j, const float map_x, const float map_y, const float map_z); 
  void        (* camera__LookAt__Compute           )(const riemann_t * our_manifold, const int target_map_i, const int target_map_j, const float target_map_x, const float target_map_y, const float target_map_z, const float map__camera_distance_from_target_point, const float AngleXY, const float AngleZ, float (* manifold__camera_distance_from_target_point_ref), float (* manifold__camera_pos_ref)[3], float (* manifold__target_pos_ref)[3], float (* manifold__upward_direction_ref)[3]); 
  void        (* camera__LookAt__Blit              )(const riemann_t * our_manifold, const float (* manifold__camera_pos_ref)[3], const float (* manifold__target_pos_ref)[3], const float (* manifold__upward_direction_ref)[3]); 
  void        (* AfficherCube                      )(const riemann_t * this, const int map_i, const int map_j, const float map_x, const float map_y, const float map_z, const float map_dx, const float map_dy, const float map_dz); 
  void        (* get_tangent_basis__flat           )(const riemann_t * our_manifold, const int map_i, const int map_j, const float map_x, const float map_y, const float map_z, TPoint3D * ux_ref, TPoint3D * uy_ref, TPoint3D * uz_ref); 
  void        (* glVertexAndNormalAt__flat         )(const riemann_t * this, const int map_i, const int map_j, const float map_x, const float map_y); 
  int         (* get_nb_extra_w_arrays_needed      )(const riemann_t * our_manifold); 
  int         (* get_nb_extra_h_arrays_needed      )(const riemann_t * our_manifold); 
  int         (* get_nb_extra_w_h_arrays_needed    )(const riemann_t * our_manifold); 
  void        (* compute_manifold_vertices_and_normals)(const riemann_t * our_manifold, 
								 const int TailleX, const int TailleY, 
								 const float * global_map__x, const float * global_map__y, const float * global_map__z, const float global_map__z_water, 
								 const float (* global_map__normal)[3], 
								 const int extra_w_arrays__nb  , float * * extra_w_arrays, 
								 const int extra_h_arrays__nb  , float * * extra_h_arrays, 
								 const int extra_w_h_arrays__nb, float * * extra_w_h_arrays, 
								 float (* vertex       )[3], float (* normal       )[3], 
								 float (* vertex__water)[3], float (* normal__water)[3]); 

}; 

enum { riemann__sizeof__const = sizeof(riemann_t) }; 
extern const int riemann__sizeof; 

extern void riemann__temps__do_step (riemann_t * this); 
extern void riemann__temps__set     (riemann_t * this, const float new_time); 
extern void riemann__temps__bloque  (riemann_t * this); 
extern void riemann__temps__debloque(riemann_t * this); 

extern riemann_t * riemann__make(void); 
extern riemann_t * riemann__make_b(const int buffer_size, char * buffer); 
extern riemann_t * riemann__make_r(riemann_t * this); 
extern void        riemann__delete_r(riemann_t * this); 
extern void        riemann__delete(riemann_t * this); 
extern riemann_t * riemann__make_rectangle(const int nb_maps_on_width, const int nb_maps_on_height, const float rectangle_width, const float rectangle_height); 
extern riemann_t * riemann__make_torus(const int nb_maps_on_width, const int nb_maps_on_height, const float primary_circle_radius, const float secondary_circle_radius); 
extern void        riemann__Life(riemann_t * this); 
extern void        riemann__AfficherCube(const riemann_t * our_manifold, const int map_i, const int map_j, const float map_x, const float map_y, const float map_z, const float map_dx, const float map_dy, const float map_dz); 
extern void        riemann__camera__LookAt__Blit(const riemann_t * our_manifold, const float (* manifold__camera_pos_ref)[3], const float (* manifold__target_pos_ref)[3], const float (* manifold__upward_direction_ref)[3]); 
extern void        riemann__manifold_z_scale_factor__set(riemann_t * this, const float new_manifold_z_scale_factor); 



 
 
#endif /* RIEMANN_H */ 
