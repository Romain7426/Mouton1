#include "global.h" 
#include "riemann.h" 


// RL: The aim of this file is to provide a model for the riemannian manifold. 
//     We start with the torus/donut (fr: "tore"/"bagel"/"beignet") as it was the purpose of 
//     the present game. 
// 
// RL: But we want everything else to be independant from the riemannian manifold. 
//     As far as we are concerned, it could be anything, as long as we could map a ground onto it. 
// 
// RL: The idea is that we draw in the local map: 
//      - we're in the global manifold 
//      - apply φ: we're in the local map  
//      - do our drawing stuffs 
//      - pop() (mathematically speaking, φ^-1 is applied). 
// 
// RL: We especially need to differentiate 
//     the coordinate on the local and on the global manifold. 
//     As far as the user is concerned, all coordinates are map-local. 
//     - 
//     The user should never see anything about the manifold. 
//     The only thing that he should be using is φ. 
// 
// 

static const char * riemann_type__cstr_array[] = { 
  "NULL", 
  "TORUS", 
  "RECTANGLE", 
  NULL
}; 
enum { riemann_type__cstr_array__size = ARRAY_SIZE(riemann_type__cstr_array) }; 
static void assert_compile__dkushdsuf238s764asddf(void) {
  ASSERT_COMPILE__LOCAL(riemann_type__cstr_array__size == RIEMANN_TYPE__COUNT + 1); 
}; 
extern const char * riemann_type__get_cstr(const int riemann_type) { 
  if (riemann_type < 0) return NULL; 
  if (riemann_type >= RIEMANN_TYPE__COUNT) return NULL; 
  return riemann_type__cstr_array[riemann_type]; 
}; 


#ifndef RIEMAN_TORUS_T 
#define RIEMAN_TORUS_T
struct riemann_torus_t; 
typedef struct riemann_torus_t riemann_torus_t; 
#endif 
struct riemann_torus_t { 
  float R; // RL: This is the radius of the main circle. 
  float a; // RL: This is the radius of the secondary circle. 
  
  // RL: local coordinates are in [0..1]. 
  
  float ybase; // RL: It's a constant y-shift, in map-local coordinates. 
               // RL: Was added by FS, but not actually used (as of 2020-04-24, 'ybase' is always null). 
               // RL: Scale-ly speaking, 'ybase' is in the local-map coordinates. 
  
  uint8_t nb_phi;    // RL: Translation factor between local-map coordinates & torus coordinates: 
                     //     Number of segments in which the outer cicle is divided. 
                     //     => angle on the outer circle = 2π * x / nb_phi 
  uint8_t nb_theta;  // RL: Translation factor between local-map coordinates & torus coordinates: 
                     //     Number of segments in which the inner cicle is divided. 
                     //     => angle on the inner circle = 2π * y / nb_theta 

  
  
  // METHODS 
  void     (* glVertexTore            )(const riemann_t * this, const int map_i, const int global_map_j, const float map_x, const float map_y, const float map_z); 
  TPoint3D (* get_manifold_coordinates)(const riemann_t * this, const int map_i, const int global_map_j, const float map_x, const float map_y, const float map_z); 
}; 
enum {    rieman_torus__sizeof__const = sizeof(riemann_torus_t) }; 
const int rieman_torus__sizeof        = rieman_torus__sizeof__const; 



#ifndef RIEMAN_RECTANGLE_T 
#define RIEMAN_RECTANGLE_T
struct riemann_rectangle_t; 
typedef struct riemann_rectangle_t riemann_rectangle_t; 
#endif 
struct riemann_rectangle_t { 
  float w; // RL: That implies that the width  of a map on the manifold is [ w / w_nb ]. 
  float h; // RL: That implies that the height of a map on the manifold is [ h / h_nb ]. 
  
  float w_one_map; // RL: w / w_nb 
  float h_one_map; // RL: h / h_nb 
  
  // METHODS 
  void     (* glVertexRectangle       )(const riemann_t * this, const int map_i, const int global_map_j, const float map_x, const float map_y, const float map_z); 
  TPoint3D (* get_manifold_coordinates)(const riemann_t * this, const int map_i, const int global_map_j, const float map_x, const float map_y, const float map_z); 
}; 
enum {    rieman_rectangle__sizeof__const = sizeof(riemann_rectangle_t) }; 
const int rieman_rectangle__sizeof        = rieman_rectangle__sizeof__const; 


enum {    RIEMANN_DATA__NEEDED_SIZEOF = MAX(rieman_torus__sizeof__const,rieman_rectangle__sizeof__const) }; 
const int riemann_data__needed_sizeof = RIEMANN_DATA__NEEDED_SIZEOF; 

static void assert_compile__dsakhsda4387hd87(void) { 
  ASSERT_COMPILE__LOCAL(RIEMANN_DATA__NEEDED_SIZEOF <= RIEMANN_DATA__ALLOCATED_SIZEOF); 
}; 


//#define            marche_compression_defaut__macro   0.0050f //RL: That's the old 2π-based value. 
//#define            marche_compression_defaut__macro   0.0010f // RL: Each day is divided in 100 small steps. Supposing the the game resolution is 20ms for a passe (aka 50fps), one in-game day lasts 20s. 

// RL: Basically, the game runs at 50Hz. 
//     Let's say one full day is 6 minutes. 
// RL: So, one pass is roughly 20ms; 6 minutes / 20ms = 6 * 60 * 1000 / 20 = 18000 steps ~ 20.000 steps 
//     1 / 20.000 steps = 0.00005f step-length 
//#define            marche_compression_defaut__macro   0.00005f 
#define            marche_compression_defaut__macro   0.00003f 
//#define            marche_compression_defaut__macro   0.01f 
static const float marche_compression_defaut__var   = marche_compression_defaut__macro; 
#define            marche_compression_defaut          marche_compression_defaut__macro 

const int riemann__sizeof = riemann__sizeof__const; 



riemann_t * riemann__make(void) {
  MALLOC_THIS(riemann_t,this); 
  riemann__make_r(this); 
  this -> malloced_huh = true; 
  return this; 
};

riemann_t * riemann__make_b(const int buffer_size, char * buffer) { 
  if (buffer_size < (int)sizeof(riemann_t)) { return NULL; }; 
  riemann_t * this = (riemann_t *) buffer; 
  return riemann__make_r(this); 
}; 

riemann_t * riemann__make_r(riemann_t * this) {
  BZERO_THIS(this); 
  
  ASSIGN_METHOD(riemann,this,make); 
  ASSIGN_METHOD(riemann,this,delete); 
  ASSIGN_METHOD(riemann,this,Life); 
  ASSIGN_METHOD(riemann,this,temps__do_step); 
  ASSIGN_METHOD(riemann,this,temps__set); 
  ASSIGN_METHOD(riemann,this,temps__bloque); 
  ASSIGN_METHOD(riemann,this,temps__debloque); 
  ASSIGN_METHOD(riemann,this,AfficherCube); 
  ASSIGN_METHOD(riemann,this,camera__LookAt__Blit); 
  ASSIGN_METHOD(riemann,this,manifold_z_scale_factor__set); 
  
  this -> malloced_huh = false; 
  this -> temps_pas    = marche_compression_defaut; 
  this -> manifold_z_scale_factor = 1.0f; 
  
  return this; 
}; 

void riemann__delete_r(riemann_t * this) {
  BZERO_THIS(this); 
}; 
 
void riemann__delete(riemann_t * this) { 
  const int malloced_huh = this -> malloced_huh; 
  riemann__delete_r(this); 
  if (malloced_huh) { free(this); }; 
}; 



void riemann__Life(riemann_t * this) { 
  riemann__temps__do_step(this); 
}; 


void riemann__manifold_z_scale_factor__set(riemann_t * this, const float new_manifold_z_scale_factor) { 
  this -> map_to_manifold_factor__z *= new_manifold_z_scale_factor / this -> manifold_z_scale_factor; 
  this -> manifold_z_scale_factor    = new_manifold_z_scale_factor; 
}; 



void riemann__temps__do_step(riemann_t * this) { 
  this -> temps += this -> temps_pas; 
}; 
 
void riemann__temps__set(riemann_t * this, const float new_utc_time) { 
  this -> temps = new_utc_time; 
}; 
 
void riemann__temps__bloque(riemann_t * this) { 
  this -> temps_pas = 0; 
}; 
 
void riemann__temps__debloque(riemann_t * this) { 
  this -> temps_pas = marche_compression_defaut; 
}; 

#if 0 
float riemann__temps__get_local_time_at_y(const riemann_t * this, const int global_map_j, const float map_y) { 
  // FS: /*renvoie 0 la nuit et 1 quand l'anneau est au zénith*/ 
#if 1 
  const TPoint3D p = this -> get_manifold_coordinates(this, /*map_i*/0, map_j, /*map_x*/0, map_y, /*map_z*/0); 
  
#else 
  const float inner_angle = INNER_ANGLE__GET(j); 
  return (1.0f + cosf(inner_angle)) / 2.0f; 
  //return (1.0f+cosf(our_manifold -> temps+2*PI*(j - our_manifold -> ybase)/our_manifold -> nb_theta))/2.0f;
  //	return sqrt(sqr(R+a*cosf(t+2*PI*j/nb_theta)) - sqr(a*sinf(t+2*PI*j/nb_theta)) );
#endif 
};
#endif  


extern void riemann__AfficherCube(const riemann_t * our_manifold, const int global_map_i, const int global_map_j, const float map_x, const float map_y, const float map_z, const float map_dx, const float map_dy, const float map_dz) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " our_manifold = %p, global_map_i = %d, global_map_j = %d, map_x = %f, map_y = %f, map_z = %f, map_dx = %f, map_dy = %f, map_dz = %f "   "\n", __func__, our_manifold, global_map_i, global_map_j, map_x, map_y, map_z, map_dx, map_dy, map_dz); 
  // RL: Actually, it's two parallel rectangles which are drawn. 
  glBegin(GL_LINES); { 
    for (int xx = 0; xx <= 1; xx++) { 
      for (int yy = 0; yy <= 1; yy++) { 
        for (int zz = 0; zz <= 1; zz++) { 
          our_manifold -> glVertexManifold(our_manifold, global_map_i, global_map_j, map_x            , map_y + yy*map_dy, map_z + zz*map_dz); 
          our_manifold -> glVertexManifold(our_manifold, global_map_i, global_map_j, map_x +    map_dx, map_y + yy*map_dy, map_z + zz*map_dz); 
          
          our_manifold -> glVertexManifold(our_manifold, global_map_i, global_map_j, map_x + xx*map_dx, map_y            , map_z + zz*map_dz); 
          our_manifold -> glVertexManifold(our_manifold, global_map_i, global_map_j, map_x + xx*map_dx, map_y +    map_dy, map_z + zz*map_dz); 
          
          our_manifold -> glVertexManifold(our_manifold, global_map_i, global_map_j, map_x + xx*map_dx, map_y + yy*map_dy, map_z            ); 
          our_manifold -> glVertexManifold(our_manifold, global_map_i, global_map_j, map_x + xx*map_dx, map_y + yy*map_dy, map_z +    map_dz); 
        }; 
      }; 
    }; 
  } glEnd(); 
}; 


extern void riemann__camera__LookAt__Blit(const riemann_t * our_manifold, const float (* manifold__camera_pos_ref)[3], const float (* manifold__target_pos_ref)[3], const float (* manifold__upward_direction_ref)[3]) { 
  glMatrixMode(GL_MODELVIEW); // RL: Compulsory for 'gluLookAt' to work. That means that we switch to the standard object-model, with local-coordinates. 
  glLoadIdentity(); // RL: Where ever we were, it's discarded. So we are at the origin, with the standard vector basis (no translation, no rotation). 
  gluLookAt(
	    // RL: Camera position - From where the target point is looked at. 
	    (*manifold__camera_pos_ref)[0], 
	    (*manifold__camera_pos_ref)[1], 
	    (*manifold__camera_pos_ref)[2], 
	    
	    // RL: Target position - The point that is looked at. 
	    (*manifold__target_pos_ref)[0], 
	    (*manifold__target_pos_ref)[1], 
	    (*manifold__target_pos_ref)[2], 
	    
	    // RL: Vector that gives the upward direction. 
	    //     Without it, the screen would freely spin around. 
	    //     No need to normalize it or to have a perfect vector - OpenGL will project it onto the projecting surface and then normalize it. 
	    (*manifold__upward_direction_ref)[0], 
	    (*manifold__upward_direction_ref)[1], 
	    (*manifold__upward_direction_ref)[2]); 
};  



















// *** TORUS *** 


// RL: Sinus & cosinus on the inner circle 
#define INNER_ANGLE__GET(__our_torus_manifold__,__map_y__) (2.0f * PI * ((__our_torus_manifold__) -> temps + (((float)((__map_y__) - (__our_torus_manifold__) -> torus_data -> ybase)) / ((float) (__our_torus_manifold__) -> torus_data -> nb_theta)))) 
#define float_cjsj(__our_torus_manifold__,__map_y__)			\
  const float inner_angle = INNER_ANGLE__GET((__our_torus_manifold__),(__map_y__)); \
  const float cj = cosf(inner_angle);					\
  const float sj = sinf(inner_angle); 

// RL: Sinus & cosinus on the outer circle 
#define OUTER_ANGLE__GET(__our_torus_manifold__,__map_x__) (2.0f * PI * ((float) (__map_x__)) / ((float) (__our_torus_manifold__) -> torus_data -> nb_phi))
#define float_cisi(__our_torus_manifold__,__map_x__)			\
  const float outer_angle = OUTER_ANGLE__GET((__our_torus_manifold__),(__map_x__)); \
  const float ci = cosf(outer_angle);					\
  const float si = sinf(outer_angle); 





#define TORUS_MANIFOLD_POINT_GET__COMMA(__our_manifold__,__ci__,__si__,__cj__,__sj__,__map_z__) \
  (  ((__our_manifold__) -> torus_data -> R + ((__our_manifold__) -> torus_data -> a + (__our_manifold__) -> map_to_manifold_factor__z * (__map_z__)) * (__cj__)) * (__ci__)), \
    (((__our_manifold__) -> torus_data -> R + ((__our_manifold__) -> torus_data -> a + (__our_manifold__) -> map_to_manifold_factor__z * (__map_z__)) * (__cj__)) * (__si__)), \
    (                                         ((__our_manifold__) -> torus_data -> a + (__our_manifold__) -> map_to_manifold_factor__z * (__map_z__)) * (__sj__)) 

#define TORUS_MANIFOLD_POINT_GET__X(__our_manifold__,__ci__,__si__,__cj__,__sj__,__map_z__) \
  (  ((__our_manifold__) -> torus_data -> R + ((__our_manifold__) -> torus_data -> a + (__our_manifold__) -> map_to_manifold_factor__z * (__map_z__)) * (__cj__)) * (__ci__))  

#define TORUS_MANIFOLD_POINT_GET__Y(__our_manifold__,__ci__,__si__,__cj__,__sj__,__map_z__) \
  (  ((__our_manifold__) -> torus_data -> R + ((__our_manifold__) -> torus_data -> a + (__our_manifold__) -> map_to_manifold_factor__z * (__map_z__)) * (__cj__)) * (__si__)) 

#define TORUS_MANIFOLD_POINT_GET__Z(__our_manifold__,__ci__,__si__,__cj__,__sj__,__map_z__) \
  (                                           ((__our_manifold__) -> torus_data -> a + (__our_manifold__) -> map_to_manifold_factor__z * (__map_z__)) * (__sj__)) 



// RL: These are local coordinates. 
static void riemann__glVertexTore(const riemann_t * our_manifold, const int map_i, const int global_map_j, const float map_x, const float map_y, const float map_z) {
  float_cjsj(our_manifold,map_y); 
  float_cisi(our_manifold,map_x); 
  //TORUS_MANIFOLD_POINT_GET__COMMA(our_manifold,ci,si,cj,sj,z); 
  glVertex3f(TORUS_MANIFOLD_POINT_GET__COMMA(our_manifold,ci,si,cj,sj,map_z)); 
};

static TPoint3D riemann__torus__get_manifold_coordinates(const riemann_t * our_manifold, const int map_i, const int global_map_j, const float map_x, const float map_y, const float map_z) { 
  float_cjsj(our_manifold,map_y); 
  float_cisi(our_manifold,map_x); 
  
  return TPoint3D_make_scalar(TORUS_MANIFOLD_POINT_GET__X(our_manifold,ci,si,cj,sj,map_z), 
			      TORUS_MANIFOLD_POINT_GET__Y(our_manifold,ci,si,cj,sj,map_z), 
			      TORUS_MANIFOLD_POINT_GET__Z(our_manifold,ci,si,cj,sj,map_z)); 


#if 0 
  return TPoint3D_make_scalar(( (our_manifold -> R + (our_manifold -> a + z) * cj) * ci), ((our_manifold -> R + (our_manifold -> a + z) * cj) * si), ( (our_manifold -> a + z) * sj));
  return TPoint3D_make_scalar(TORUS_MANIFOLD_POINT_GET__COMMA(our_manifold,ci,si,cj,sj,z)); 
#endif 
}; 

static float riemann_torus__get_local_time_at_y(const riemann_t * our_manifold, const int global_map_j, const float map_y) { 
  const float inner_angle     = INNER_ANGLE__GET(our_manifold,map_y); 
  const float local_time_at_y = inner_angle / (2.0f * PI); 
  const float int_part        = floorf(local_time_at_y); 
  return local_time_at_y - int_part; // RL: This is in [0 ; 1[. 
}; 

static float riemann_torus__get_sunshine_intensity_at_y(const riemann_t * our_manifold, const int global_map_j, const float map_y) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " map_y = %f"   "\n", __func__,  map_y);   
  // FS: /*renvoie 0 la nuit et 1 quand l'anneau est au zénith*/ 
  const float inner_angle = INNER_ANGLE__GET(our_manifold,map_y); 
  return (1.0f - cosf(inner_angle)) / 2.0f; 
  //return (1.0f + cosf(inner_angle)) / 2.0f; 
  //return (1.0f+cosf(our_manifold -> temps+2*PI*(j - our_manifold -> ybase)/our_manifold -> nb_theta))/2.0f;
  //	return sqrt(sqr(R+a*cosf(t+2*PI*j/nb_theta)) - sqr(a*sinf(t+2*PI*j/nb_theta)) );
};

static float riemann_torus__FacteurCompression(const riemann_t * our_manifold, const int global_map_j, const float map_y) { 
#if 0 
  return riemann_torus__get_sunshine_intensity_at_y(our_manifold, map_j, map_y); 
#else 
  //return (our_manifold -> R + our_manifold -> a * cosf(our_manifold -> temps+2*PI*(j - our_manifold -> ybase)/our_manifold -> nb_theta)) / our_manifold -> R; 
  const float inner_angle = INNER_ANGLE__GET(our_manifold,map_y); 
  const float factor = our_manifold -> torus_data -> a / our_manifold -> torus_data -> R; 
  //return 1.0f + factor * cosf(inner_angle); 
  //return factor * (2.0f + cosf(inner_angle)); 
  //return factor * (3.0f + cosf(inner_angle)) * 0.5f; 
  return (3.0f + cosf(inner_angle)) * 0.375f; 
  //return 0.5f * (2.0f + cosf(inner_angle)); 
  //return 1.0 + our_manifold -> torus_data -> a * cosf(inner_angle) / our_manifold -> torus_data -> R; 
  //return sqrt(sqr(R+a*cosf(t+2*PI*j/nb_theta)) - sqr(a*sinf(t+2*PI*j/nb_theta)) );
#endif 
}; 

static void riemann_torus__MatricePour2D(const riemann_t * our_manifold, const int map_i, const int global_map_j, const float map_x, const float map_y, const float map_z) { 
  float_cjsj(our_manifold,map_y); 
  float_cisi(our_manifold,map_x); 
  
  // FS: on place la sprite sur le point du tore 
  // RL: The local orthonormal-basis is moved to the point on the manifold. 
  glTranslatef(TORUS_MANIFOLD_POINT_GET__COMMA(our_manifold,ci,si,cj,sj,map_z)); 

  // RL: However, the local orthonormal-basis is parallel to the 'UTC'-one. 
  //     Z-axis aside, the basis is not in the tangent space. 
  //     Therefore we need to rotate it so that u is parallel to x, v parallel to y, and w to z. 
  // RL: As far as I know, there isn't any OpenGL command to change the current vector basis. 
  //     So we have to do proceed to two rotations to do it (yes, in R^3, two rotations are enough). 
  // RL: How to find these two rotations? Easy: 
  //      - The standard basis is the local basis for the point (φ_0 = 3π/2, θ_0 = π/2). 
  //      - Then, for a point (φ, 0), the basis has to be rotated around the z-axis of an angle [π/2 + φ]. 
  //      - Then, for a point (0, θ), the basis has to be rotated around the x-axis of an angle [π/2 + θ]. 
  

#if 1 
  // RL: Awkwardly, 'glRotate' is in degrees (360-based - not 2π-based). 
  const float two_pi_based__to__360_based__factor = 360.0f / (2.0f * PI); 
  const float outer_angle__360_based = outer_angle * two_pi_based__to__360_based__factor; 
  const float inner_angle__360_based = inner_angle * two_pi_based__to__360_based__factor; 
  
  // RL: φ-rotation around z-axis. 
  glRotatef( 90.0f + outer_angle__360_based, 0.0f, 0.0f, 1.0f); 
  
  // RL: θ-rotation around x-axis. 
  glRotatef( 90.0f - inner_angle__360_based, 1.0f, 0.0f, 0.0f); 
#else 
  // FS: on la pivote autour de (Oz) 
  // RL: Awkwardly, 'glRotate' is in degrees (360-based - not 2π-based). 
  const float outer_angle__360_based = (outer_angle / (2.0f*PI)) * 360.0f; 
  glRotatef(outer_angle__360_based, 0, 0, 1); 
  
  // FS: puis on la met par terre 
  // RL: Awkwardly, 'glRotate' is in degrees (360-based - not 2π-based). 
  const float inner_angle__360_based = (inner_angle / (2.0f*PI)) * 360.0f; 
  glRotatef(90.0f - inner_angle__360_based, 0, 1, 0); 
#endif 
  
  
  //glScalef(this -> rectangle_data -> w_one_map, this -> rectangle_data -> h_one_map, this -> map_to_manifold_factor__z); 
  const float w_one_map_at_y = 2.0f * PI * (our_manifold -> torus_data -> R + our_manifold -> torus_data -> a * cj) / ((float) our_manifold -> torus_data -> nb_phi); 
  const float h_one_map      = 2.0f * PI * (our_manifold -> torus_data -> a) / ((float) our_manifold -> torus_data -> nb_theta); 
  glScalef(w_one_map_at_y, h_one_map, our_manifold -> map_to_manifold_factor__z); 

}; 



#define TORUS__GET_TANGENT_BASIS__FLAT__UX(__ci__,__si__,__cj__,__sj__) \
  TPoint3D_make_scalar(- __si__         ,   __ci__         ,      0) 

#define TORUS__GET_TANGENT_BASIS__FLAT__UY(__ci__,__si__,__cj__,__sj__) \
  TPoint3D_make_scalar(- __ci__ * __sj__, - __si__ * __sj__, __cj__) 

#define TORUS__GET_TANGENT_BASIS__FLAT__UZ(__ci__,__si__,__cj__,__sj__) \
  TPoint3D_make_scalar(  __ci__ * __cj__,   __si__ * __cj__, __sj__) 

 
#define TORUS_MANIFOLD_TANGENT__MAP_VECTOR__GET__X(__ci__,__si__,__cj__,__sj__,__vector_x__,__vector_y__,__vector_z__) \
  ((__vector_x__) * (- __si__) + (__vector_y__) * (- __ci__ * __sj__) + (__vector_z__) * (__ci__ * __cj__)) 

#define TORUS_MANIFOLD_TANGENT__MAP_VECTOR__GET__Y(__ci__,__si__,__cj__,__sj__,__vector_x__,__vector_y__,__vector_z__) \
  ((__vector_x__) * (  __ci__) + (__vector_y__) * (- __si__ * __sj__) + (__vector_z__) * (__si__ * __cj__)) 

#define TORUS_MANIFOLD_TANGENT__MAP_VECTOR__GET__Z(__ci__,__si__,__cj__,__sj__,__vector_x__,__vector_y__,__vector_z__) \
  ((__vector_x__) * (       0) + (__vector_y__) * (           __cj__) + (__vector_z__) * (         __sj__)) 




static void riemann_torus__get_tangent_basis__flat(const riemann_t * our_manifold, const int map_i, const int global_map_j, const float map_x, const float map_y, const float map_z, TPoint3D * ux_ref, TPoint3D * uy_ref, TPoint3D * uz_ref) { 
  float_cjsj(our_manifold,map_y); 
  float_cisi(our_manifold,map_x); 

  // RL: (ux, uy, uz) is the tangent basis (already normalized and orthogonal). 
  *ux_ref = TORUS__GET_TANGENT_BASIS__FLAT__UX(ci,si,cj,sj); 
  *uy_ref = TORUS__GET_TANGENT_BASIS__FLAT__UY(ci,si,cj,sj); 
  *uz_ref = TORUS__GET_TANGENT_BASIS__FLAT__UZ(ci,si,cj,sj); 
}; 


static void riemann_torus__camera__LookAt__Compute(const riemann_t * our_manifold, const int global_map_i, const int global_map_j, const float target_map_x, const float target_map_y, const float target_map_z, const float map__camera_distance_from_target_point, const float AngleXY, const float AngleZ, float (* manifold__camera_distance_from_target_point_ref), float (* manifold__camera_pos_ref)[3], float (* manifold__target_pos_ref)[3], float (* manifold__upward_direction_ref)[3]) { 
  float_cjsj(our_manifold,target_map_y); 
  float_cisi(our_manifold,target_map_x); 
  
  const TPoint3D target_p = TPoint3D_make_scalar(TORUS_MANIFOLD_POINT_GET__X(our_manifold,ci,si,cj,sj,target_map_z), 
						 TORUS_MANIFOLD_POINT_GET__Y(our_manifold,ci,si,cj,sj,target_map_z), 
						 TORUS_MANIFOLD_POINT_GET__Z(our_manifold,ci,si,cj,sj,target_map_z)); 
  
  // RL: (ux, uy, uz) is the tangent basis (already normalized and orthogonal). 
  const TPoint3D ux = TORUS__GET_TANGENT_BASIS__FLAT__UX(ci,si,cj,sj); 
  const TPoint3D uy = TORUS__GET_TANGENT_BASIS__FLAT__UY(ci,si,cj,sj); 
  const TPoint3D uz = TORUS__GET_TANGENT_BASIS__FLAT__UZ(ci,si,cj,sj); 
  
  // RL: 'direction_horizontale' is already normalized. 
  TPoint3D temp; 
  //const float        AngleXY_shifted = AngleXY - PI / 2.0f; 
  const float        AngleXY_shifted = AngleXY; 
  const float    cos_AngleXY_shifted = cosf(AngleXY_shifted); 
  const float    sin_AngleXY_shifted = sinf(AngleXY_shifted); 
#if 0 
  TPoint3D_add(TPoint3D_lambda__macro(  cos_AngleXY_shifted, ux), TPoint3D_lambda__macro(  sin_AngleXY_shifted, uy), &temp); const TPoint3D direction_horizontale = temp; 
  TPoint3D_add(TPoint3D_lambda__macro(- sin_AngleXY_shifted, ux), TPoint3D_lambda__macro(  cos_AngleXY_shifted, uy), &temp); const TPoint3D upward_direction      = temp; 
  
  TPoint3D camera_p = target_p; 
  TPoint3D_lambda(camera_distance_from_target_point * cosf(AngleZ), direction_horizontale, &temp); TPoint3D_add_self__macro(camera_p, temp); 
  TPoint3D_lambda(camera_distance_from_target_point * sinf(AngleZ),                    uz, &temp); TPoint3D_add_self__macro(camera_p, temp); 
#else 
  TPoint3D_add(TPoint3D_lambda__macro(  cos_AngleXY_shifted, ux), TPoint3D_lambda__macro(  sin_AngleXY_shifted, uy), &temp); const TPoint3D direction_horizontale = temp; 
  //TPoint3D_add(TPoint3D_lambda__macro(- sin_AngleXY_shifted, ux), TPoint3D_lambda__macro(  cos_AngleXY_shifted, uy), &temp); const TPoint3D upward_direction      = temp; 
  
  TPoint3D_add(TPoint3D_lambda__macro(cosf(AngleZ), uz), TPoint3D_lambda__macro(  sinf(AngleZ), direction_horizontale), &temp); const TPoint3D camera_direction = temp; 
  TPoint3D_add(TPoint3D_lambda__macro(sinf(AngleZ), uz), TPoint3D_lambda__macro(- cosf(AngleZ), direction_horizontale), &temp); const TPoint3D upward_direction = temp; //direction_horizontale; //TPoint3D_lambda__macro(  sin_AngleXY_shifted, uy); //TPoint3D_lambda__macro(  cos_AngleXY_shifted, ux); //direction_horizontale; //temp; 
  //TPoint3D_add(TPoint3D_lambda__macro(sinf(AngleZ), uz), TPoint3D_lambda__macro(- cosf(AngleZ), camera_direction), &temp); const TPoint3D upward_direction = temp; 
  
  //TPoint3D_add(target_p, TPoint3D_lambda__macro(camera_distance_from_target_point, camera_direction), &temp); const TPoint3D camera_p = temp; 
  //const float dist_factor = (fabsf(cosf(AngleXY)) * our_manifold -> rectangle_data -> w_one_map + fabsf(sinf(AngleXY)) * our_manifold -> rectangle_data -> w_one_map) * fabsf(sinf(AngleZ)) + fabsf(cosf(AngleZ)) * our_manifold -> map_to_manifold_factor__z; 
  //const float dist_factor = (powf(cosf(AngleXY), 2.0f) * our_manifold -> rectangle_data -> w_one_map + powf(sinf(AngleXY), 2.0f) * our_manifold -> rectangle_data -> w_one_map) * powf(sinf(AngleZ), 2.0f) + powf(cosf(AngleZ), 2.0f) * our_manifold -> map_to_manifold_factor__z; 
  const float w_one_map_at_y = 2.0f * PI * (our_manifold -> torus_data -> R + our_manifold -> torus_data -> a * cj) / ((float) our_manifold -> torus_data -> nb_phi); 
  const float h_one_map      = 2.0f * PI * (our_manifold -> torus_data -> a) / ((float) our_manifold -> torus_data -> nb_theta); 
  const float dist_factor    = (powf(cosf(AngleXY), 2.0f) * w_one_map_at_y + powf(sinf(AngleXY), 2.0f) * h_one_map) * powf(sinf(AngleZ), 2.0f) + powf(cosf(AngleZ), 2.0f) * our_manifold -> map_to_manifold_factor__z; 
  //const float dist_factor    = (ldexpf(cosf(AngleXY), 1) * w_one_map_at_y + ldexpf(sinf(AngleXY), 1) * h_one_map) * ldexpf(sinf(AngleZ), 1) + ldexpf(cosf(AngleZ), 1) * our_manifold -> map_to_manifold_factor__z; 
  
  
  *manifold__camera_distance_from_target_point_ref = dist_factor * map__camera_distance_from_target_point; 
  TPoint3D_add(target_p, TPoint3D_lambda__macro(*manifold__camera_distance_from_target_point_ref, camera_direction), &temp); const TPoint3D camera_p = temp; 
#endif 
  
  (*manifold__camera_pos_ref)[0] = camera_p.x; 
  (*manifold__camera_pos_ref)[1] = camera_p.y; 
  (*manifold__camera_pos_ref)[2] = camera_p.z; 
  
  (*manifold__target_pos_ref)[0] = target_p.x; 
  (*manifold__target_pos_ref)[1] = target_p.y; 
  (*manifold__target_pos_ref)[2] = target_p.z; 

  (*manifold__upward_direction_ref)[0] = upward_direction.x; 
  (*manifold__upward_direction_ref)[1] = upward_direction.y; 
  (*manifold__upward_direction_ref)[2] = upward_direction.z; 
}; 


static void riemann_torus__camera__LookAt_angle(const riemann_t * our_manifold, const int global_map_i, const int global_map_j, const float target_map_x, const float target_map_y, const float target_map_z, const float camera_distance_from_target_point, const float AngleXY, const float AngleZ) {
  glMatrixMode(GL_MODELVIEW); // RL: Compulsory for 'gluLookAt' to work. That means that we switch to the standard object-model, with local-coordinates. 
  glLoadIdentity(); // RL: Where ever we were, it's discarded. So we are at the origin, with the standard vector basis (no translation, no rotation). 

#if 1 
  float_cjsj(our_manifold,target_map_y); 
  float_cisi(our_manifold,target_map_x); 
  
  const TPoint3D target_p = TPoint3D_make_scalar(TORUS_MANIFOLD_POINT_GET__X(our_manifold,ci,si,cj,sj,target_map_z), 
						 TORUS_MANIFOLD_POINT_GET__Y(our_manifold,ci,si,cj,sj,target_map_z), 
						 TORUS_MANIFOLD_POINT_GET__Z(our_manifold,ci,si,cj,sj,target_map_z)); 
  
  // RL: (ux, uy, uz) is the tangent basis (already normalized and orthogonal). 
  const TPoint3D ux = TORUS__GET_TANGENT_BASIS__FLAT__UX(ci,si,cj,sj); 
  const TPoint3D uy = TORUS__GET_TANGENT_BASIS__FLAT__UY(ci,si,cj,sj); 
  const TPoint3D uz = TORUS__GET_TANGENT_BASIS__FLAT__UZ(ci,si,cj,sj); 
  
  // RL: 'direction_horizontale' is already normalized. 
  TPoint3D temp; 
  //const float        AngleXY_shifted = AngleXY - PI / 2.0f; 
  const float        AngleXY_shifted = AngleXY; 
  const float    cos_AngleXY_shifted = cosf(AngleXY_shifted); 
  const float    sin_AngleXY_shifted = sinf(AngleXY_shifted); 
  TPoint3D_add(TPoint3D_lambda__macro(  cos_AngleXY_shifted, ux), TPoint3D_lambda__macro(  sin_AngleXY_shifted, uy), &temp); const TPoint3D direction_horizontale = temp; 
  TPoint3D_add(TPoint3D_lambda__macro(- sin_AngleXY_shifted, ux), TPoint3D_lambda__macro(  cos_AngleXY_shifted, uy), &temp); const TPoint3D upward_direction      = temp; 
  
  TPoint3D camera_p = target_p; 
  TPoint3D_lambda(camera_distance_from_target_point * cosf(AngleZ), direction_horizontale, &temp); TPoint3D_add_self__macro(camera_p, temp); 
  TPoint3D_lambda(camera_distance_from_target_point * sinf(AngleZ),                    uz, &temp); TPoint3D_add_self__macro(camera_p, temp); 
  
  gluLookAt(
	    // RL: Camera position - From where the target point is looked at. 
	    camera_p.x, 
	    camera_p.y, 
	    camera_p.z, 
	    
	    // RL: Target position - The point that is looked at. 
	    target_p.x, 
	    target_p.y, 
	    target_p.z, 
	    
	    // RL: Vector that gives the upward direction. 
	    //     Without it, the screen would freely spin around. 
	    //     No need to normalize it or to have a perfect vector - OpenGL will project it onto the projecting surface and then normalize it. 
            upward_direction.x, 
            upward_direction.y, 
            upward_direction.z); 
#else 
  const TPoint3D target_p = our_manifold -> get_manifold_coordinates(our_manifold, global_map_i, global_map_j, target_map_z); 
  
  TPoint3D ux = TPoint3D_sub(our_manifold -> get_manifold_coordinates(our_manifold, i+1.0f, j     , z     ), target_p); 
  TPoint3D uy = TPoint3D_sub(our_manifold -> get_manifold_coordinates(our_manifold, i     , j+1.0f, z     ), target_p); 
  TPoint3D uz = TPoint3D_sub(our_manifold -> get_manifold_coordinates(our_manifold, i     , j     , z+1.0f), target_p); 
  
  TPoint3D direction_horizontale = TPoint3D_add(TPoint3D_lambda(cosf(AngleXY), ux), TPoint3D_lambda(sinf(AngleXY), uy)); 
  
  TPoint3D_Normer2(&direction_horizontale);
  TPoint3D_Normer2(&ux);
  TPoint3D_Normer2(&uy);
  TPoint3D_Normer2(&uz);
  
  TPoint3D u = target_p; 
  TPoint3D_sub_self(u, TPoint3D_lambda(camera_distance_from_target_point * cosf(AngleZ), direction_horizontale)); 
  TPoint3D_sub_self(u, TPoint3D_lambda(camera_distance_from_target_point * sinf(AngleZ), uz)); 
  
  gluLookAt(
	    // FS: position de la caméra 
	    // RL: Camera position - From where the target point is looked at. 
	    u.x, 
	    u.y, 
	    u.z, 
	    
	    // FS: on regarde le point 
	    // RL: Target position - The point that is looked at. 
	    target_p.x, 
	    target_p.y, 
	    target_p.z, 
	    
	    // FS: vecteur qui pointe vers le haut 
	    // RL: Vector that gives the upward direction. 
	    //     Without it, the screen would freely spin around. 
	    //     No need to normalize it or to have a perfect vector - OpenGL will project it onto the projecting surface and then normalize it. 
            uz.x, 
            uz.y, 
            uz.z); 
#endif 
};


// RL: That function calls glNormal & glVertex for a flat map ('z' is not taken into account). 
//     That's why it's used by the water rendering function. 
static void riemann_torus__glVertexAndNormalAt__flat(const riemann_t * our_manifold, const int map_i, const int global_map_j, const float map_x, const float map_y) { 
#if 1 
  float_cjsj(our_manifold,map_y); 
  float_cisi(our_manifold,map_x); 
  
  const TPoint3D p = TPoint3D_make_scalar(TORUS_MANIFOLD_POINT_GET__X(our_manifold,ci,si,cj,sj,0), 
					  TORUS_MANIFOLD_POINT_GET__Y(our_manifold,ci,si,cj,sj,0), 
					  TORUS_MANIFOLD_POINT_GET__Z(our_manifold,ci,si,cj,sj,0)); 
  
  // RL: (ux, uy, uz) is the tangent basis (already normalized and orthogonal). 
  const TPoint3D ux = TORUS__GET_TANGENT_BASIS__FLAT__UX(ci,si,cj,sj); 
  const TPoint3D uy = TORUS__GET_TANGENT_BASIS__FLAT__UY(ci,si,cj,sj); 
  const TPoint3D uz = TORUS__GET_TANGENT_BASIS__FLAT__UZ(ci,si,cj,sj); 
  
  glNormal3fv((const float*)&uz); // RL: What's the point of that? 
                            // RL: For lighting models - it smoothens the vertex. 
                            // RL: It seems like the call to vertex must be after the call the normal. The vertex and the normal are linked together. Because all the upcoming vertex will get that normal. 
  glVertex3fv((const float*)&p); 
#else 
  if (i < 0) i += our_manifold -> nb_phi; 
  if (j < 0) j += our_manifold -> nb_theta; 
  
  if (i >= our_manifold -> nb_phi  ) i -= our_manifold -> nb_phi; 
  if (j >= our_manifold -> nb_theta) j -= our_manifold -> nb_theta; 
  
  float_cjsj(our_manifold,j); 
  float_cisi(our_manifold,i); 
  
  /*	(R+( a+GETZ((i),(j)) )  *cosf(t+(float)2*PI*(j)/our_manifold -> nb_theta) ) * cosf((float)2*PI*(i)/our_manifold -> nb_phi)
	(R+( a+GETZ((i),(j)) ) *cosf(t+(float)2*PI*(j)/our_manifold -> nb_theta) ) * sinf((float)2*PI*(i)/our_manifold -> nb_phi)
	( a+GETZ((i),(j)) ) *sinf(t+(float)2*PI*(j)/our_manifold -> nb_theta) */
  TPoint3D df_theta, df_phi, normal; 
  
  df_theta.x = -(our_manifold -> R + (our_manifold -> a + this -> ZEau) * sj) * ci; 
  df_theta.y = -(our_manifold -> R + (our_manifold -> a + this -> ZEau) * sj) * si; 
  df_theta.z =                       (our_manifold -> a + this -> ZEau) * cj; 
  
  df_phi.x = -(our_manifold -> R + (our_manifold -> a + this -> ZEau) * cj) * si; 
  df_phi.y =  (our_manifold -> R + (our_manifold -> a + this -> ZEau) * cj) * ci; 
  df_phi.z =  0; 
  
  //normal = df_theta ^ df_phi; 
  normal = TPoint3D_normale(df_theta, df_phi); 
  
  glNormal3fv((float*)&normal); // RL: What's the point of that? 
                                // RL: For lighting models - it smoothens the vertex. 
                                // RL: It seems like the call to vertex must be after the call the normal. The vertex and the normal are linked together. Because all the upcoming vertex will get that normal. 
  glVertex3f((our_manifold -> R + (our_manifold -> a + this -> ZEau) * cj) * ci, 
	     (our_manifold -> R + (our_manifold -> a + this -> ZEau) * cj) * si, 
        	                  (our_manifold -> a + this -> ZEau) * sj); 
#endif 
}; 



static void riemann_torus__glVertexAndNormalAt(const riemann_t * our_manifold, const int map_i, const int global_map_j, const float map_x, const float map_y, const float map_z) { 
#if 1 
  float_cjsj(our_manifold,map_y); 
  float_cisi(our_manifold,map_x); 
  
  const TPoint3D p = TPoint3D_make_scalar(TORUS_MANIFOLD_POINT_GET__X(our_manifold,ci,si,cj,sj,map_z), 
					  TORUS_MANIFOLD_POINT_GET__Y(our_manifold,ci,si,cj,sj,map_z), 
					  TORUS_MANIFOLD_POINT_GET__Z(our_manifold,ci,si,cj,sj,map_z)); 
  
  // RL: (ux, uy, uz) is the tangent basis (already normalized and orthogonal). 
  const TPoint3D ux = TORUS__GET_TANGENT_BASIS__FLAT__UX(ci,si,cj,sj); 
  const TPoint3D uy = TORUS__GET_TANGENT_BASIS__FLAT__UY(ci,si,cj,sj); 
  const TPoint3D uz = TORUS__GET_TANGENT_BASIS__FLAT__UZ(ci,si,cj,sj); 
  
  glNormal3fv((const float*)&uz); // RL: What's the point of that? 
                            // RL: For lighting models - it smoothens the vertex. 
                            // RL: It seems like the call to vertex must be after the call the normal. The vertex and the normal are linked together. Because all the upcoming vertex will get that normal. 
  glVertex3fv((const float*)&p); 
  
#else 
  /* 
    if (i < 0) i += nb_phi;
    if (j < 0) j += nb_theta;
  
    if (i >= nb_phi) i -= nb_phi;
    if (j >= nb_theta) j -= nb_theta;*/
  
  const int indice_point_ecran = j * this -> TailleX + i; 
  if (TESTINDICEPointsEcran(indice_point_ecran)) { 
    messerr("ERREUR: Lecture dans PointsEcran incorrecte (%i, %i)\n ", i, j); 
    return; 
  }; 
  
  glNormal3fv((float*) &this -> PointsEcran[indice_point_ecran].normal); // RL: What's the point of that thing? 
                                                                         // RL: For lighting models - it smoothens the vertex. 
                                                                         // RL: It seems like the call to vertex must be after the call the normal. The vertex and the normal are linked together. Because all the upcoming vertex will get that normal. 
  glVertex3f(this -> PointsEcran[indice_point_ecran].pt.x, 
             this -> PointsEcran[indice_point_ecran].pt.y, 
             this -> PointsEcran[indice_point_ecran].pt.z); 
#endif 
}; 

static int riemann_torus__get_nb_extra_w_arrays_needed(const riemann_t * our_manifold) { 
  return 3; 
}; 

static int riemann_torus__get_nb_extra_h_arrays_needed(const riemann_t * our_manifold) { 
  return 3; 
}; 

static int riemann_torus__get_nb_extra_w_h_arrays_needed(const riemann_t * our_manifold) { 
  return 0; 
}; 



static void riemann_torus__compute_manifold_vertices_and_normals(const riemann_t * our_manifold, 
								 const int TailleX, const int TailleY, 
								 const float * global_map__x, const float * global_map__y, const float * global_map__z, const float global_map__z_water, 
								 const float (* global_map__normal)[3], 
								 const int extra_w_arrays__nb  , float * * extra_w_arrays, 
								 const int extra_h_arrays__nb  , float * * extra_h_arrays, 
								 const int extra_w_h_arrays__nb, float * * extra_w_h_arrays, 
								 float (* manifold__vertex       )[3], float (* manifold__normal       )[3], 
								 float (* manifold__vertex__water)[3], float (* manifold__normal__water)[3]) { 

  assert(global_map__x           != NULL); 
  assert(global_map__y           != NULL); 
  assert(global_map__z           != NULL); 
  assert(global_map__normal      != NULL); 
  assert(manifold__vertex        != NULL); 
  assert(manifold__normal        != NULL); 
  assert(manifold__vertex__water != NULL); 
  assert(manifold__normal__water != NULL); 
  
  assert(extra_w_arrays    != NULL); 
  assert(extra_h_arrays    != NULL); 
  assert(extra_w_h_arrays  != NULL); 
  
  assert(extra_w_arrays__nb   >= 3); 
  assert(extra_h_arrays__nb   >= 3); 
  assert(extra_w_h_arrays__nb >= 0); 
  
  float * outer_angle       = extra_w_arrays[0]; 
  float * outer_angle__cosf = extra_w_arrays[1]; 
  float * outer_angle__sinf = extra_w_arrays[2]; 

  float * inner_angle       = extra_h_arrays[0]; 
  float * inner_angle__cosf = extra_h_arrays[1]; 
  float * inner_angle__sinf = extra_h_arrays[2]; 

  assert(outer_angle       != NULL); 
  assert(outer_angle__cosf != NULL); 
  assert(outer_angle__sinf != NULL); 
  assert(inner_angle       != NULL); 
  assert(inner_angle__cosf != NULL); 
  assert(inner_angle__sinf != NULL); 
  
  
  for (int vertex_i = 0; vertex_i < TailleX; vertex_i++) { 
    const float phi = OUTER_ANGLE__GET(our_manifold,global_map__x[vertex_i]); 
    outer_angle      [vertex_i] =      phi ; 
    outer_angle__cosf[vertex_i] = cosf(phi); 
    outer_angle__sinf[vertex_i] = sinf(phi); 
  }; 
  
  for (int vertex_j = 0; vertex_j < TailleY; vertex_j++) { 
    const float theta = INNER_ANGLE__GET(our_manifold,global_map__y[vertex_j]); 
    inner_angle      [vertex_j] =      theta ; 
    inner_angle__cosf[vertex_j] = cosf(theta); 
    inner_angle__sinf[vertex_j] = sinf(theta); 
  }; 
  
  
  for (int vertex_j = 0; vertex_j < TailleY; vertex_j++) { 
    const float cj = inner_angle__cosf[vertex_j]; 
    const float sj = inner_angle__sinf[vertex_j]; 
    for (int vertex_i = 0; vertex_i < TailleX; vertex_i++) { 
      const int   index = vertex_j * TailleX + vertex_i; 
      const float ci    = outer_angle__cosf[vertex_i]; 
      const float si    = outer_angle__sinf[vertex_i]; 
      { 
	const float map_z = global_map__z[index]; 
	manifold__vertex[index][0] = TORUS_MANIFOLD_POINT_GET__X(our_manifold,ci,si,cj,sj,map_z); 
	manifold__vertex[index][1] = TORUS_MANIFOLD_POINT_GET__Y(our_manifold,ci,si,cj,sj,map_z); 
	manifold__vertex[index][2] = TORUS_MANIFOLD_POINT_GET__Z(our_manifold,ci,si,cj,sj,map_z); 
	manifold__normal[index][0] = TORUS_MANIFOLD_TANGENT__MAP_VECTOR__GET__X(ci,si,cj,sj,global_map__normal[index][0],global_map__normal[index][1],global_map__normal[index][2]); 
	manifold__normal[index][1] = TORUS_MANIFOLD_TANGENT__MAP_VECTOR__GET__Y(ci,si,cj,sj,global_map__normal[index][0],global_map__normal[index][1],global_map__normal[index][2]); 
	manifold__normal[index][2] = TORUS_MANIFOLD_TANGENT__MAP_VECTOR__GET__Z(ci,si,cj,sj,global_map__normal[index][0],global_map__normal[index][1],global_map__normal[index][2]); 
      }; 
      { 
	const float map_water_z = global_map__z_water; 
	manifold__vertex__water[index][0] = TORUS_MANIFOLD_POINT_GET__X(our_manifold,ci,si,cj,sj,map_water_z); 
	manifold__vertex__water[index][1] = TORUS_MANIFOLD_POINT_GET__Y(our_manifold,ci,si,cj,sj,map_water_z); 
	manifold__vertex__water[index][2] = TORUS_MANIFOLD_POINT_GET__Z(our_manifold,ci,si,cj,sj,map_water_z); 
	manifold__normal__water[index][0] = TORUS_MANIFOLD_TANGENT__MAP_VECTOR__GET__X(ci,si,cj,sj,1,0,0); 
	manifold__normal__water[index][1] = TORUS_MANIFOLD_TANGENT__MAP_VECTOR__GET__Y(ci,si,cj,sj,0,1,0); 
	manifold__normal__water[index][2] = TORUS_MANIFOLD_TANGENT__MAP_VECTOR__GET__Z(ci,si,cj,sj,0,0,1); 
      }; 
    }; 
  }; 
  
}; 








void riemann_torus__init(riemann_t * this, const float primary_circle_radius, const float secondary_circle_radius) { 
  this -> type       = RIEMANN_TYPE__TORUS; 
  this -> torus_data = (riemann_torus_t *) &this -> data; 
  
  this -> torus_data -> R = primary_circle_radius; 
  this -> torus_data -> a = secondary_circle_radius; 
  
  this -> torus_data -> nb_phi   = this -> w_nb; 
  this -> torus_data -> nb_theta = this -> h_nb; 
  
  const float manifold_width  = 2.0f * PI *   primary_circle_radius; 
  const float manifold_height = 2.0f * PI * secondary_circle_radius; 
  const float w_one_map = manifold_width  / this -> w_nb; 
  const float h_one_map = manifold_height / this -> h_nb; 
  //this -> map_to_manifold_factor__z = (w_one_map + h_one_map) / 2.0f; 
  this -> map_to_manifold_factor__z = (w_one_map + h_one_map) / 2.0f * this -> manifold_z_scale_factor; 
  
  this -> glVertexManifold                      = riemann__glVertexTore; 
  this -> get_manifold_coordinates              = riemann__torus__get_manifold_coordinates; 
  this -> temps__get_local_time_at_y            = riemann_torus__get_local_time_at_y; 
  this -> temps__get_sunshine_intensity_at_y    = riemann_torus__get_sunshine_intensity_at_y; 
  this -> FacteurCompression                    = riemann_torus__FacteurCompression; 
  this -> MatricePour2D                         = riemann_torus__MatricePour2D; 
  //this -> camera__LookAt_angle                  = riemann_torus__camera__LookAt_angle; 
  this -> camera__LookAt__Compute               = riemann_torus__camera__LookAt__Compute; 
  this -> get_tangent_basis__flat               = riemann_torus__get_tangent_basis__flat; 
  this -> glVertexAndNormalAt__flat             = riemann_torus__glVertexAndNormalAt__flat; 
  this -> get_nb_extra_w_arrays_needed          = riemann_torus__get_nb_extra_w_arrays_needed; 
  this -> get_nb_extra_h_arrays_needed          = riemann_torus__get_nb_extra_h_arrays_needed; 
  this -> get_nb_extra_w_h_arrays_needed        = riemann_torus__get_nb_extra_w_h_arrays_needed; 
  this -> compute_manifold_vertices_and_normals = riemann_torus__compute_manifold_vertices_and_normals; 
}; 

riemann_t * riemann__make_torus(const int nb_maps_on_width, const int nb_maps_on_height, const float primary_circle_radius, const float secondary_circle_radius) { 
  riemann_t * this = riemann__make(); 
  this -> w_nb = nb_maps_on_width; 
  this -> h_nb = nb_maps_on_height; 
  riemann_torus__init(this, primary_circle_radius, secondary_circle_radius); 
  return this; 
};







// *** RECTANGLE *** 

#define RECTANGLE_MANIFOLD_POINT_GET__X(__our_manifold__,__map_i__,__map_j__,__map_x__,__map_y__,__map_z__) \
  (  (__our_manifold__) -> rectangle_data -> w_one_map * (((float) (__map_i__)) + (__map_x__))) 

#define RECTANGLE_MANIFOLD_POINT_GET__Y(__our_manifold__,__map_i__,__map_j__,__map_x__,__map_y__,__map_z__) \
  (  (__our_manifold__) -> rectangle_data -> h_one_map * (((float) (__map_j__)) + (__map_y__))) 

#define RECTANGLE_MANIFOLD_POINT_GET__Z(__our_manifold__,__map_i__,__map_j__,__map_x__,__map_y__,__map_z__) \
  (  (__our_manifold__) -> map_to_manifold_factor__z   * (__map_z__)) 

#define RECTANGLE_MANIFOLD_POINT_GET__COMMA(__our_manifold__,__map_i__,__map_j__,__map_x__,__map_y__,__map_z__) \
  RECTANGLE_MANIFOLD_POINT_GET__X(__our_manifold__,__map_i__,__map_j__,__map_x__,__map_y__,__map_z__), \
  RECTANGLE_MANIFOLD_POINT_GET__Y(__our_manifold__,__map_i__,__map_j__,__map_x__,__map_y__,__map_z__), \
  RECTANGLE_MANIFOLD_POINT_GET__Z(__our_manifold__,__map_i__,__map_j__,__map_x__,__map_y__,__map_z__) 


#define RECTANGLE_MANIFOLD_POINT_GET__X__GLOBAL(__our_manifold__,__global_map_x__,__global_map_y__,__global_map_z__) \
  (  (__our_manifold__) -> rectangle_data -> w_one_map * (__global_map_x__)) 

#define RECTANGLE_MANIFOLD_POINT_GET__Y__GLOBAL(__our_manifold__,__global_map_x__,__global_map_y__,__global_map_z__) \
  (  (__our_manifold__) -> rectangle_data -> h_one_map * (__global_map_y__)) 

#define RECTANGLE_MANIFOLD_POINT_GET__Z__GLOBAL(__our_manifold__,__global_map_x__,__global_map_y__,__global_map_z__) \
  (  (__our_manifold__) -> map_to_manifold_factor__z   * (__global_map_z__)) 



static void riemann__rectangle__glVertexRectangle(const riemann_t * our_manifold, const int global_map_i, const int global_map_j, const float map_x, const float map_y, const float map_z) {
  glVertex3f(RECTANGLE_MANIFOLD_POINT_GET__COMMA(our_manifold,global_map_i,global_map_j,map_x,map_y,map_z)); 
}; 

static TPoint3D riemann__rectangle__get_manifold_coordinates(const riemann_t * our_manifold, const int map_i, const int global_map_j, const float map_x, const float map_y, const float map_z) { 
  return TPoint3D_make_scalar(RECTANGLE_MANIFOLD_POINT_GET__X(our_manifold,map_i,global_map_j,map_x,map_y,map_z), 
			      RECTANGLE_MANIFOLD_POINT_GET__Y(our_manifold,map_i,global_map_j,map_x,map_y,map_z), 
			      RECTANGLE_MANIFOLD_POINT_GET__Z(our_manifold,map_i,global_map_j,map_x,map_y,map_z)); 
  
#if 0 
  // RL: This one does work as the outer macro is first expanded. 
  return TPoint3D_make_scalar(RECTANGLE_MANIFOLD_POINT_GET__COMMA(our_manifold,ci,si,cj,sj,z)); 
#endif 
}; 



#define RECTANGLE__GET_TANGENT_BASIS__FLAT__UX(__map_i__,__map_j__,__map_x__,__map_y__) \
  TPoint3D_make_scalar(1,0,0)

#define RECTANGLE__GET_TANGENT_BASIS__FLAT__UY(__map_i__,__map_j__,__map_x__,__map_y__) \
  TPoint3D_make_scalar(0,1,0)

#define RECTANGLE__GET_TANGENT_BASIS__FLAT__UZ(__map_i__,__map_j__,__map_x__,__map_y__) \
  TPoint3D_make_scalar(0,0,1)

 
#define RECTANGLE_MANIFOLD_TANGENT__MAP_VECTOR__GET__X(__vector_x__,__vector_y__,__vector_z__) \
  ((__vector_x__)) 

#define RECTANGLE_MANIFOLD_TANGENT__MAP_VECTOR__GET__Y(__vector_x__,__vector_y__,__vector_z__) \
  ((__vector_y__)) 

#define RECTANGLE_MANIFOLD_TANGENT__MAP_VECTOR__GET__Z(__vector_x__,__vector_y__,__vector_z__) \
  ((__vector_z__)) 




static void riemann_rectangle__get_tangent_basis__flat(const riemann_t * our_manifold, const int map_i, const int global_map_j, const float map_x, const float map_y, const float map_z, TPoint3D * ux_ref, TPoint3D * uy_ref, TPoint3D * uz_ref) { 
  // RL: (ux, uy, uz) is the tangent basis (already normalized and orthogonal). 
  *ux_ref = RECTANGLE__GET_TANGENT_BASIS__FLAT__UX(map_i,global_map_j,map_x,map_y); 
  *uy_ref = RECTANGLE__GET_TANGENT_BASIS__FLAT__UY(map_i,global_map_j,map_x,map_y); 
  *uz_ref = RECTANGLE__GET_TANGENT_BASIS__FLAT__UZ(map_i,global_map_j,map_x,map_y); 
}; 





// RL: For a rectangle manifold, the idea is, if one map is spanning over the whole manifold, 
//     then it should not be daylight at 'map_y = 0' and dark at 'map_y = 1', 
//     which would be rather weird (day and night at the same time, on the same map). 
//     Therefore, the model is the manifold rectangle is half-a-day. 
float riemann_rectangle__get_local_time_at_y(const riemann_t * this, const int global_map_j, const float map_y) { 
  static const float global_map_dy_is_how_much_of_a_day = 0.5f; 
  const float y_manifold_coordinate = RECTANGLE_MANIFOLD_POINT_GET__Y(this,0,global_map_j,0,map_y,0); 
  const float non_adjusted_time     = this -> temps - y_manifold_coordinate / this -> rectangle_data -> h * global_map_dy_is_how_much_of_a_day; 
  const float int_part              = floorf(non_adjusted_time); 
  return non_adjusted_time - int_part; // RL: This is in [0 ; 1[. 
}; 

// RL: ensoleillement 
float riemann_rectangle__get_sunshine_intensity_at_y(const riemann_t * this, const int global_map_j, const float map_y) { 
  const float local_time_at_y = riemann_rectangle__get_local_time_at_y(this, global_map_j, map_y); 
  return 1.0f - 2.0f * fabsf(local_time_at_y - 0.5f); // RL: 0 at midnight, 1 at noon 
};
 
static float riemann_rectangle__FacteurCompression(const riemann_t * this, const int global_map_j, const float map_y) { 
  return 1; // RL: Cannot be '0' as it is a factor, so used to multiply and divide. 
}; 


static void riemann_rectangle__MatricePour2D(const riemann_t * this, const int map_i, const int global_map_j, const float map_x, const float map_y, const float map_z) { 
  // FS: on place la sprite sur le point du tore 
  // RL: The local orthonormal-basis is moved to the point on the manifold. 
  glTranslatef(RECTANGLE_MANIFOLD_POINT_GET__COMMA(this,map_i,global_map_j,map_x,map_y,map_z)); 
  
  // RL: The local orthonormal-basis is still parallel to the 'UTC'-one. 
  // RL: For the rectangle, all tangent spaces are strictly parallel to the 'UTC'-one. 
  //     So we're done. 

  //glScalef(this -> rectangle_data -> w_one_map, this -> rectangle_data -> h_one_map, 1.0f); 
  glScalef(this -> rectangle_data -> w_one_map, this -> rectangle_data -> h_one_map, this -> map_to_manifold_factor__z); 
}; 

static void riemann_rectangle__camera__LookAt__Compute(const riemann_t * our_manifold, const int global_map_i, const int global_map_j, const float target_map_x, const float target_map_y, const float target_map_z, const float map__camera_distance_from_target_point, const float AngleXY, const float AngleZ, float (* manifold__camera_distance_from_target_point_ref), float (* manifold__camera_pos_ref)[3], float (* manifold__target_pos_ref)[3], float (* manifold__upward_direction_ref)[3]) { 
  // RL: For a rectangle, the vector basis of the tangent space is the same as origin's. 
  
  const TPoint3D target_p = TPoint3D_make_scalar(RECTANGLE_MANIFOLD_POINT_GET__X(our_manifold,global_map_i,global_map_j,target_map_x,target_map_y,target_map_z), 
						 RECTANGLE_MANIFOLD_POINT_GET__Y(our_manifold,global_map_i,global_map_j,target_map_x,target_map_y,target_map_z), 
						 RECTANGLE_MANIFOLD_POINT_GET__Z(our_manifold,global_map_i,global_map_j,target_map_x,target_map_y,target_map_z)); 
  
  // RL: (ux, uy, uz) is the tangent basis (already normalized). 
  const TPoint3D ux = TPoint3D_make_scalar(1, 0, 0); 
  const TPoint3D uy = TPoint3D_make_scalar(0, 1, 0); 
  const TPoint3D uz = TPoint3D_make_scalar(0, 0, 1); 
  
  // RL: 'direction_horizontale' is already normalized. 
  TPoint3D temp; 
  //const float        AngleXY_shifted = AngleXY - PI / 2.0f; 
  const float        AngleXY_shifted = AngleXY; 
  const float    cos_AngleXY_shifted = cosf(AngleXY_shifted); 
  const float    sin_AngleXY_shifted = sinf(AngleXY_shifted); 
#if 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "    AngleXY_shifted = %f"  "\n", __func__,     AngleXY_shifted); 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "cos_AngleXY_shifted = %f"  "\n", __func__, cos_AngleXY_shifted); 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "sin_AngleXY_shifted = %f"  "\n", __func__, sin_AngleXY_shifted); 
#endif 
  TPoint3D_add(TPoint3D_lambda__macro(  cos_AngleXY_shifted, ux), TPoint3D_lambda__macro(  sin_AngleXY_shifted, uy), &temp); const TPoint3D direction_horizontale = temp; 
  //TPoint3D_add(TPoint3D_lambda__macro(- sin_AngleXY_shifted, ux), TPoint3D_lambda__macro(  cos_AngleXY_shifted, uy), &temp); const TPoint3D upward_direction      = temp; 

  TPoint3D_add(TPoint3D_lambda__macro(cosf(AngleZ), uz), TPoint3D_lambda__macro(  sinf(AngleZ), direction_horizontale), &temp); const TPoint3D camera_direction = temp; 
  TPoint3D_add(TPoint3D_lambda__macro(sinf(AngleZ), uz), TPoint3D_lambda__macro(- cosf(AngleZ), direction_horizontale), &temp); const TPoint3D upward_direction = temp; //direction_horizontale; //TPoint3D_lambda__macro(  sin_AngleXY_shifted, uy); //TPoint3D_lambda__macro(  cos_AngleXY_shifted, ux); //direction_horizontale; //temp; 
  //TPoint3D_add(TPoint3D_lambda__macro(sinf(AngleZ), uz), TPoint3D_lambda__macro(- cosf(AngleZ), camera_direction), &temp); const TPoint3D upward_direction = temp; 
  
  //const float dist_factor = (fabsf(cosf(AngleXY)) * our_manifold -> rectangle_data -> w_one_map + fabsf(sinf(AngleXY)) * our_manifold -> rectangle_data -> w_one_map) * fabsf(sinf(AngleZ)) + fabsf(cosf(AngleZ)) * our_manifold -> map_to_manifold_factor__z; 
  //const float dist_factor = (powf(cosf(AngleXY), 2.0f) * our_manifold -> rectangle_data -> w_one_map + powf(sinf(AngleXY), 2.0f) * our_manifold -> rectangle_data -> w_one_map) * powf(sinf(AngleZ), 2.0f) + powf(cosf(AngleZ), 2.0f) * our_manifold -> map_to_manifold_factor__z; 
  const float dist_factor = (powf(cosf(AngleXY), 2.0f) * our_manifold -> rectangle_data -> w_one_map + powf(sinf(AngleXY), 2.0f) * our_manifold -> rectangle_data -> h_one_map) * powf(sinf(AngleZ), 2.0f) + powf(cosf(AngleZ), 2.0f) * our_manifold -> map_to_manifold_factor__z; 
  //const float dist_factor = our_manifold -> map_to_manifold_factor__z; 

  
  
  *manifold__camera_distance_from_target_point_ref = dist_factor * map__camera_distance_from_target_point; 
  TPoint3D_add(target_p, TPoint3D_lambda__macro(*manifold__camera_distance_from_target_point_ref, camera_direction), &temp); const TPoint3D camera_p = temp; 
  
  
  
  
  (*manifold__camera_pos_ref)[0] = camera_p.x; 
  (*manifold__camera_pos_ref)[1] = camera_p.y; 
  (*manifold__camera_pos_ref)[2] = camera_p.z; 
  
  (*manifold__target_pos_ref)[0] = target_p.x; 
  (*manifold__target_pos_ref)[1] = target_p.y; 
  (*manifold__target_pos_ref)[2] = target_p.z; 

  (*manifold__upward_direction_ref)[0] = upward_direction.x; 
  (*manifold__upward_direction_ref)[1] = upward_direction.y; 
  (*manifold__upward_direction_ref)[2] = upward_direction.z; 
}; 

static void riemann_rectangle__camera__LookAt_angle(const riemann_t * our_manifold, const int global_map_i, const int global_map_j, const float target_map_x, const float target_map_y, const float target_map_z, const float camera_distance_from_target_point, const float AngleXY, const float AngleZ) {
  glMatrixMode(GL_MODELVIEW); // RL: Compulsory for 'gluLookAt' to work. That means that we switch to the standard object-model, with local-coordinates. 
  glLoadIdentity(); // RL: Where ever we were, it's discarded. So we are at the origin, with the standard vector basis (no translation, no rotation). 
  
  // RL: For a rectangle, the vector basis of the tangent space is the same as origin's. 

  const TPoint3D target_p = TPoint3D_make_scalar(RECTANGLE_MANIFOLD_POINT_GET__X(our_manifold,global_map_i,global_map_j,target_map_x,target_map_y,target_map_z), 
						 RECTANGLE_MANIFOLD_POINT_GET__Y(our_manifold,global_map_i,global_map_j,target_map_x,target_map_y,target_map_z), 
						 RECTANGLE_MANIFOLD_POINT_GET__Z(our_manifold,global_map_i,global_map_j,target_map_x,target_map_y,target_map_z)); 
  
  // RL: (ux, uy, uz) is the tangent basis (already normalized). 
  const TPoint3D ux = TPoint3D_make_scalar(1, 0, 0); 
  const TPoint3D uy = TPoint3D_make_scalar(0, 1, 0); 
  const TPoint3D uz = TPoint3D_make_scalar(0, 0, 1); 
  
  // RL: 'direction_horizontale' is already normalized. 
  TPoint3D temp; 
  const float        AngleXY_shifted = AngleXY - PI / 2.0f; 
  const float    cos_AngleXY_shifted = cosf(AngleXY_shifted); 
  const float    sin_AngleXY_shifted = sinf(AngleXY_shifted); 
  TPoint3D_add(TPoint3D_lambda__macro(  cos_AngleXY_shifted, ux), TPoint3D_lambda__macro(  sin_AngleXY_shifted, uy), &temp); const TPoint3D direction_horizontale = temp; 
  TPoint3D_add(TPoint3D_lambda__macro(- sin_AngleXY_shifted, ux), TPoint3D_lambda__macro(  cos_AngleXY_shifted, uy), &temp); const TPoint3D upward_direction      = temp; 
  
  TPoint3D camera_p = target_p; 
  TPoint3D_lambda(camera_distance_from_target_point * cosf(AngleZ), direction_horizontale, &temp); TPoint3D_add_self__macro(camera_p, temp); 
  TPoint3D_lambda(camera_distance_from_target_point * sinf(AngleZ),                    uz, &temp); TPoint3D_add_self__macro(camera_p, temp); 

  
  gluLookAt(
	    // RL: Camera position - From where the target point is looked at. 
	    camera_p.x, 
	    camera_p.y, 
	    camera_p.z, 
	    
	    // RL: Target position - The point that is looked at. 
	    target_p.x, 
	    target_p.y, 
	    target_p.z, 
	    
	    // RL: Vector that gives the upward direction. 
	    //     Without it, the screen would freely spin around. 
	    //     No need to normalize it or to have a perfect vector - OpenGL will project it onto the projecting surface and then normalize it. 
            upward_direction.x, 
            upward_direction.y, 
            upward_direction.z); 
};


// RL: That function calls glNormal & glVertex for a flat map ('z' is not taken into account). 
//     That's why it's used by the water rendering function. 
static void riemann_rectangle__glVertexAndNormalAt__flat(const riemann_t * this, const int map_i, const int global_map_j, const float map_x, const float map_y) { 
  const TPoint3D p = TPoint3D_make_scalar(RECTANGLE_MANIFOLD_POINT_GET__X(this,map_i,global_map_j,map_x,map_y,0), 
					  RECTANGLE_MANIFOLD_POINT_GET__Y(this,map_i,global_map_j,map_x,map_y,0), 
					  RECTANGLE_MANIFOLD_POINT_GET__Z(this,map_i,global_map_j,map_x,map_y,0)); 
  
  // RL: (ux, uy, uz) is the tangent basis (already normalized and orthogonal). 
  const TPoint3D ux = RECTANGLE__GET_TANGENT_BASIS__FLAT__UX(map_i,global_map_j,map_x,map_y); 
  const TPoint3D uy = RECTANGLE__GET_TANGENT_BASIS__FLAT__UY(map_i,global_map_j,map_x,map_y); 
  const TPoint3D uz = RECTANGLE__GET_TANGENT_BASIS__FLAT__UZ(map_i,global_map_j,map_x,map_y); 
  
  glNormal3fv((const float*)&uz); // RL: What's the point of that? 
                                  // RL: For lighting models - it smoothens the vertex. 
                                  // RL: It seems like the call to vertex must be after the call to normal. The vertex and the normal are linked together - all upcoming vertices will get that normal. 
  glVertex3fv((const float*)&p); 
}; 

static int riemann_rectangle__get_nb_extra_w_arrays_needed(const riemann_t * our_manifold) { 
  return 0; 
}; 

static int riemann_rectangle__get_nb_extra_h_arrays_needed(const riemann_t * our_manifold) { 
  return 0; 
}; 

static int riemann_rectangle__get_nb_extra_w_h_arrays_needed(const riemann_t * our_manifold) { 
  return 0; 
}; 

static void riemann_rectangle__compute_manifold_vertices_and_normals(const riemann_t * our_manifold, 
								 const int TailleX, const int TailleY, 
								 const float * global_map__x, const float * global_map__y, const float * global_map__z, const float global_map__z_water, 
								 const float (* global_map__normal)[3], 
								 const int extra_w_arrays__nb  , float * * extra_w_arrays, 
								 const int extra_h_arrays__nb  , float * * extra_h_arrays, 
								 const int extra_w_h_arrays__nb, float * * extra_w_h_arrays, 
								 float (* manifold__vertex       )[3], float (* manifold__normal       )[3], 
								 float (* manifold__vertex__water)[3], float (* manifold__normal__water)[3]) { 
  
  assert(global_map__x           != NULL); 
  assert(global_map__y           != NULL); 
  assert(global_map__z           != NULL); 
  assert(global_map__normal      != NULL); 
  assert(manifold__vertex        != NULL); 
  assert(manifold__normal        != NULL); 
  assert(manifold__vertex__water != NULL); 
  assert(manifold__normal__water != NULL); 
  
  for (int vertex_j = 0; vertex_j < TailleY; vertex_j++) { 
    const float g_map_y = global_map__y[vertex_j]; 
    for (int vertex_i = 0; vertex_i < TailleX; vertex_i++) { 
      const float g_map_x = global_map__x[vertex_i]; 
      const int   index = vertex_j * TailleX + vertex_i; 
      { 
	const float map_z = global_map__z[index]; 
	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " map_z = %f "   "\n", __func__, map_z); 
	manifold__vertex[index][0] = RECTANGLE_MANIFOLD_POINT_GET__X__GLOBAL(our_manifold,g_map_x,g_map_y,map_z); 
	manifold__vertex[index][1] = RECTANGLE_MANIFOLD_POINT_GET__Y__GLOBAL(our_manifold,g_map_x,g_map_y,map_z); 
	manifold__vertex[index][2] = RECTANGLE_MANIFOLD_POINT_GET__Z__GLOBAL(our_manifold,g_map_x,g_map_y,map_z); 
	manifold__normal[index][0] = RECTANGLE_MANIFOLD_TANGENT__MAP_VECTOR__GET__X(global_map__normal[index][0],global_map__normal[index][1],global_map__normal[index][2]); 
	manifold__normal[index][1] = RECTANGLE_MANIFOLD_TANGENT__MAP_VECTOR__GET__Y(global_map__normal[index][0],global_map__normal[index][1],global_map__normal[index][2]); 
	manifold__normal[index][2] = RECTANGLE_MANIFOLD_TANGENT__MAP_VECTOR__GET__Z(global_map__normal[index][0],global_map__normal[index][1],global_map__normal[index][2]); 
      }; 
      { 
	const float map_water_z = global_map__z_water; 
	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " map_water_z = %f "   "\n", __func__, map_water_z); 
	manifold__vertex__water[index][0] = RECTANGLE_MANIFOLD_POINT_GET__X__GLOBAL(our_manifold,g_map_x,g_map_y,map_water_z); 
	manifold__vertex__water[index][1] = RECTANGLE_MANIFOLD_POINT_GET__Y__GLOBAL(our_manifold,g_map_x,g_map_y,map_water_z); 
	manifold__vertex__water[index][2] = RECTANGLE_MANIFOLD_POINT_GET__Z__GLOBAL(our_manifold,g_map_x,g_map_y,map_water_z); 
	manifold__normal__water[index][0] = RECTANGLE_MANIFOLD_TANGENT__MAP_VECTOR__GET__X(1,0,0); 
	manifold__normal__water[index][1] = RECTANGLE_MANIFOLD_TANGENT__MAP_VECTOR__GET__Y(0,1,0); 
	manifold__normal__water[index][2] = RECTANGLE_MANIFOLD_TANGENT__MAP_VECTOR__GET__Z(0,0,1); 
      }; 
    }; 
  }; 
  
}; 
 


void riemann_rectangle__init(riemann_t * this, const float rectangle_width, const float rectangle_height) { 
  this -> type           = RIEMANN_TYPE__RECTANGLE; 
  this -> rectangle_data = (riemann_rectangle_t *) &this -> data; 
  
  this -> rectangle_data -> w = rectangle_width; 
  this -> rectangle_data -> h = rectangle_height; 
  
  this -> rectangle_data -> w_one_map = rectangle_width  / ((float) this -> w_nb); 
  this -> rectangle_data -> h_one_map = rectangle_height / ((float) this -> h_nb); 
  
  //this -> map_to_manifold_factor__z = (this -> rectangle_data -> w_one_map + this -> rectangle_data -> h_one_map) / 2.0f; 
  this -> map_to_manifold_factor__z = (this -> rectangle_data -> w_one_map + this -> rectangle_data -> h_one_map) / 2.0f  * this -> manifold_z_scale_factor; 
  
  this -> glVertexManifold                      = riemann__rectangle__glVertexRectangle; 
  this -> get_manifold_coordinates              = riemann__rectangle__get_manifold_coordinates; 
  this -> temps__get_local_time_at_y            = riemann_rectangle__get_local_time_at_y; 
  this -> temps__get_sunshine_intensity_at_y    = riemann_rectangle__get_sunshine_intensity_at_y; 
  this -> FacteurCompression                    = riemann_rectangle__FacteurCompression; 
  this -> MatricePour2D                         = riemann_rectangle__MatricePour2D; 
  //this -> camera__LookAt_angle                  = riemann_rectangle__camera__LookAt_angle; 
  this -> camera__LookAt__Compute               = riemann_rectangle__camera__LookAt__Compute; 
  this -> get_tangent_basis__flat               = riemann_rectangle__get_tangent_basis__flat; 
  this -> glVertexAndNormalAt__flat             = riemann_rectangle__glVertexAndNormalAt__flat; 
  this -> get_nb_extra_w_arrays_needed          = riemann_rectangle__get_nb_extra_w_arrays_needed; 
  this -> get_nb_extra_h_arrays_needed          = riemann_rectangle__get_nb_extra_h_arrays_needed; 
  this -> get_nb_extra_w_h_arrays_needed        = riemann_rectangle__get_nb_extra_w_h_arrays_needed; 
  this -> compute_manifold_vertices_and_normals = riemann_rectangle__compute_manifold_vertices_and_normals; 
}; 


riemann_t * riemann__make_rectangle(const int nb_maps_on_width, const int nb_maps_on_height, const float rectangle_width, const float rectangle_height) { 
  riemann_t * this = riemann__make(); 
  this -> w_nb = nb_maps_on_width; 
  this -> h_nb = nb_maps_on_height; 
  riemann_rectangle__init(this, rectangle_width, rectangle_height); 
  return this; 
};





