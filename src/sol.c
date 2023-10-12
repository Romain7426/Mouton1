#include "global.h"
#include "sol.h"


//#include "riemann.ci" 

#if 0 
#if 1 
static struct riemann_t our_manifold[1]; 
#else 
static struct riemann_t   our_manifold__struct; 
static struct riemann_t * our_manifold = & our_manifold__struct; 
#endif 
#endif 



// RL: 'CSol' is the ground of the map. 
//      Basically, it contains the z-level. (It contains also the ground textures, the water level, and other related things). 
// RL: The ground is discretized in vertices: 
//      * width : 'TailleX' vertices 
//      * height: 'TailleY' vertices 
// RL: 'TailleX' and 'TailleY' are determined when the z-levels are loaded. 
// RL: Therefore, the work coordinate system of the ground is not the lattice one, nor the normalized map one, but its own ground coordinates (based on the discretization of the z-levels). 
enum { NB_MAX_EXTRA_ARRAYS =   5 }; 
struct CSol { 
  
  // RL: This is the size of the ground-level array. 
  // RL: This is a number of vertices, not a number of cells. 
  // RL: Currently, size is 32x32 vertices (= 1024 vertices) - thus 31x31 cells (= 961 cells). 
  uint8_t TailleX; 
  uint8_t TailleY; 
  
  //float lattice_ZEau; // RL: This is in lattice coordinates. 
  float map_ZEau; // RL: This is in lattice coordinates. 
  
  // ___ Z Level ___ 
  // RL: Array of size TailleX * TailleY. 
  //     It gives the z-level for the vertex (i,j). 
  // RL: Output Z-Values are in lattice coordinates, while input (x,y) are in ground-local coordinates. 
  // RL: Output Z-Values are in map coordinates, while input (x,y) are in ground-local coordinates. 
  //float * ground__lattice_Z; 
  float * ground__map_Z; 
  
  // ___ Map Data ___ 
  // RL: These data are not intrinsic to the ground, but given by the map. 
  //     They are used to convert map coordinates to ground coordinates, 
  //               and to convert map coordinates to manifold coordinates (when rendering). 
  uint8_t over_spanning_w; // RL: If this local map is bigger than a simple map. In this case, it spans over 'over_spanning_w' in width. 
  uint8_t over_spanning_h; // RL: If this local map is bigger than a simple map. In this case, it spans over 'over_spanning_h' in height.   
#if 0   
  uint8_t global_map_i; // RL: In the global map of the world, this map is #'global_map_i' on the  width-axis. 
  uint8_t global_map_j; // RL: In the global map of the world, this map is #'global_map_j' on the height-axis. 
#endif 
  
  
  
  // ___ One-Time Computed Data ___ 
  // RL: This is the normal vector at vertex (i,j). 
  // RL: This is the normal vector in the ground-local coordinates, not the manifold normal. 
  // RL: What's the use of those things? And how can a vertex has a normal vector? What's its definition? 
  //     It seems that normals are used for light computations. 
  //     Each vertex has a normal, and OpenGL uses it to compute diffuse and specular lighting. 
  //     It should represent the normal to the tangent space at the point. (Usually, it's an average: average of its neighbors' z-levels .) 
  //     It answers the question "At what angle the light hits the surface?". 
  //     Here is the Wikipedia entry: 
  //       https://en.wikipedia.org/wiki/Vertex_normal 
  //       https://www.informit.com/articles/article.aspx?p=1377833&seqNum=5
  // RL: In this game, we do not need lighting - can't we disable that? 
  // RL: Yes, we can - the game would just look less smooth: 
  //      https://gamedev.stackexchange.com/questions/50653/opengl-why-do-i-have-to-set-a-normal-with-glnormal 
  // RL: Also, we won't compute the actual manifold normals. 
  //     Because, actually, we do not need the map normals, but the manifold normals. 
  //     And, as our manifold is alive, it implies that the normals should be updated after heart-beat of the manifold. 
  //     That could be done, however, we won't do it. 
  //     Manifold normals will be approximated using map normals mapped into the manifold tangent space. 
  //     It's not 100% accurate, but it's a good approximation. 
  //     (The quality of this approximation depends on the quality of the approximation of the manifold by its tangent space - if the tangent space is a bad approximation, then the normal approximation will be bad; if it's good, then it will be good. That difference comes from that the map-local tangent space is map into a manifold, not in a tangent space.) 
  float (* ground__normal)[3]; // RL: Array of size TailleX * TailleY // RL: Apriori, their norm2 is not 1 (OpenGL will normalize them anyway). 
  
  float (* ground__global_map_x); // RL: Array[TailleX] // RL: x-coordinate of each z-vertex in the global map. 
  float (* ground__global_map_y); // RL: Array[TailleY] // RL: y-coordinate of each z-vertex in the global map. 
  
  
  // ___ Every Pass Computed Data ___ 
  // RL: These are local temporary variables, and not actual properties. 
  // RL: It's an optimization: instead of computing the same cosinus again and again at each tick, 
  //     all these trigo computations are computed once, before blitting/rendering. 
#if 1 
  uint8_t  manifold__extra_w_arrays__nb; 
  float (* manifold__extra_w_arrays[NB_MAX_EXTRA_ARRAYS]); // RL: Array[TailleX] 
  uint8_t  manifold__extra_h_arrays__nb; 
  float (* manifold__extra_h_arrays[NB_MAX_EXTRA_ARRAYS]); // RL: Array[TailleY] 
  uint8_t  manifold__extra_w_h_arrays__nb; 
  float (* manifold__extra_w_h_arrays[NB_MAX_EXTRA_ARRAYS]); // RL: Array[TailleX * TailleY] 
#else 
  float (* manifold__outer_angle); // RL: Array[TailleX] // RL: φ of each x-coordinate. 
  float (* manifold__outer_angle__cosf); // RL: Array[TailleX] // RL: φ of each x-coordinate. 
  float (* manifold__outer_angle__sinf); // RL: Array[TailleX] // RL: φ of each x-coordinate. 
  float (* manifold__inner_angle); // RL: Array[TailleY] // RL: θ of each y-coordinate. 
  float (* manifold__inner_angle__cosf); // RL: Array[TailleY] // RL: θ of each y-coordinate. 
  float (* manifold__inner_angle__sinf); // RL: Array[TailleY] // RL: θ of each y-coordinate. 
#endif 
  float (* manifold__vertex)[3]; // RL: Array[TailleX * TailleY] // RL: Coordinates of each vertex in the manifold. 
  float (* manifold__normal)[3]; // RL: Array[TailleX * TailleY] // RL: Coordinates of each normal in the manifold. 
  float (* manifold__vertex__water)[3]; // RL: Array[TailleX * TailleY] // RL: Coordinates of each vertex in the manifold. 
  float (* manifold__normal__water)[3]; // RL: Array[TailleX * TailleY] // RL: Coordinates of each normal in the manifold. 
  
  
  // ___ Ground Textures ___ 
  // RL: Texture files are enumerated in the '_.carte' file. 
  // RL: Textures layout is described in a bitmap picture file. 
  CTexture * TextureSol[NB_MAX_TEXTURESOL]; // RL: From the '_.carte' file. 
  int8_t     TextureSol_used_huh[NB_MAX_TEXTURESOL]; 
  uint8_t    TextureSol_nb; // RL: From the '_.carte' file. 
  uint32_t   TextureSol_couleur_dans_bitmap[NB_MAX_TEXTURESOL]; // RL: From the '_.carte' file. That's the mapping between the color in the picture file and the chosen texture. 
  uint8_t  indices_texture__width; // 
  uint8_t  indices_texture__height; 
  int8_t * indices_texture__array; // RL: Array of size 'indices_texture__width' * 'indices_texture__height'. 
                                   // RL: This array is in _*_vertex_*_, not in cells. 
                                   // RL: What does that mean that a vertex has a texture? Good question. 
                                   //     Here the idea is that each texture is fully displayed every single time, 
                                   //     and then the associated value at each vertex is an alpha channel value. 
                                   //     Yes, it seems weird, but it renders not that badly. 
                                   // RL: Therefore, to have only one texture for the whole, it could be as simple as having a 1x1-array. 
                                   //     A 2x2-array will give the textures for the z-vertices at (0,0), (0,1), (1,1), and (1,0); it would a 1-cell plane, with four textures. 
                                   // RL: NB: The reverse looked-up is already done - thus this array holds an index of the 'TextureSol' array. 

  //int8_t * indices_texture__normalized_and_reversed; // RL: Array of size 'TailleX' * 'TailleY'. 

  
  
#if 0   
  // RL: I do not understand what this thing is. 
  // RL: It's an array of size TailleX * TailleY. 
  // RL: The field 'pt' contains the manifold coordinate of the point having (i,j) map-local coordinates. 
  // RL: The field 'normal' contains the normal vector at the manifold point. 
  //     Shouldn't it be normalized? What's it used for? 
  // RL: It seems that normals are used for light computations. 
  //     Each vertex has a normal, and OpenGL uses it to compute diffuse and specular lighting. 
  //     It should represent the normal to the tangent space at the point - so it should be a blended average. 
  //     "At what angle the light hits the surface?" 
  // RL: Oh, there's a Wikipedia entry: 
  //       https://en.wikipedia.org/wiki/Vertex_normal 
  // RL:   https://www.informit.com/articles/article.aspx?p=1377833&seqNum=5
  // RL: In this game, we do not need lighting - can't we disable that? 
  // RL: Yes, we can - the game will just look less smooth: 
  //      https://gamedev.stackexchange.com/questions/50653/opengl-why-do-i-have-to-set-a-normal-with-glnormal
  struct TPointEcran * PointsEcran; 
#endif 
  
  
  
  
  
  
  
  // *** METHODS *** 
  
  CSol * (* make          )(void); 
  CSol * (* make_content  )(CSol * this); 
  void   (* delete        )(CSol * this); 
  void   (* delete_content)(CSol * this); 
  int    (* init          )(CSol * this, const int global_map_i, const int global_map_j, const int over_spanning_w, const int over_spanning_h, const float lattice_to_map_scale_factor__z, const riemann_t * our_manifold, const char * z_filename, const char * texure_filename); 

#if 0 
  int (* GetTailleX)(const CSol * this); 
  int (* GetTailleY)(const CSol * this); 
#endif 

#if 0   
  int   (* ChargerZ)(      CSol * this, const int global_map_i, const int global_map_j, const int over_spanning_w, const int over_spanning_h, const riemann_t * our_manifold, const char * filename); 
  float (* GETZ    )(const CSol * this, const float map_x, const float map_y); 
  //void  (* SETZ    )(      CSol * this,   int x,   int y, float z); // FS: en privée, un élément de l'extérieur n'a pas le droit de modifier le terrain; utiliser "ChargerZ" pour cela 
#endif 
  
  float (* GET_MAP_Z )(const CSol * this, const float map_x, const float map_y); 
  
  
  int (* AjouterTextureSol         )(      CSol * this, const char * fichier_texture, const uint32_t couleur_dans_bitmap); 
#if 0   
  /* -- AjouterTextureSol -- 
    ajouter une texture de sol (CSol * this, fichier s)
    indice_dans_bitmap représente la couleur des zones de cette texture dans le fichier
    chargé après dans ChargerIndiceTextureBitmap*/
  /* -- ChargerIndiceTextureBitmap -- 
    charge le fichier bitmap qui contient les zones pour les textures
    il faut faire appel à ChargerIndiceTextureBitmap après avoir fait les
    AjouterTextureSol
    (CSol * this, à priori fichier_bitmap désigne un fichier dans le répertoire
    "../cartes/")*/
  void (* ChargerIndiceTextureBitmap)(      CSol * this, const char * fichier_bitmap); 
  void (* SETINDTEXTURE             )(      CSol * this, const int x, const int y, const int ind); 
  int  (* GETINDTEXTURE             )(const CSol * this, const int x, const int y); 
#endif 

  void (* Life                    )(const CSol * this); 
  
  //void (* Render   )(const CSol * this, int i1, int j1, int i2, int j2); /*dessine la partie du tore entre )(CSol * this, i1, j1) et )(CSol * this, i2, j2)*/
  //void (* RenderEau)(const CSol * this, int i1, int j1, int i2, int j2);
  //void (* Render                  )(const CSol * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int global_map_i, const int global_map_j, const float target_map_x, const float target_map_y); 
  void (* Render)(const CSol * this, const riemann_t * our_manifold, const int global_map_i, const int global_map_j, const float target_map_x, const float target_map_y, const float target_map_dx, const float target_map_dy); 

  //void (* Render__pre_computations)(      CSol * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int global_map_i, const int globaal_map_j, const float target_map_x, const float target_map_y); 
  void (* Render__pre_computations)(CSol * this, const riemann_t * our_manifold, const int global_map_i, const int global_map_j, const float target_map_x, const float target_map_y, const float target_map_dx, const float target_map_dy); 

  //void (* RenderEau               )(const CSol * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int global_map_i, const int global_map_j, const float target_map_x, const float target_map_y); 
  void (* RenderEau)(const CSol * this, const riemann_t * our_manifold, const int global_map_i, const int global_map_j, const float target_map_x, const float target_map_y, const float target_map_dx, const float target_map_dy); 

  
  
  bool (* yatilEau )(const CSol * this, const float map_x, const float map_y, const float map_z); 
  
  
  
  
  //void (* PositionModulo)(const CSol * this, float& i, float& j); 
  //void (* PositionModulo)(const CSol * this, float * i_ptr, float * j_ptr); 
  //TPoint2D (* Differentiel)(const CSol * this, TPoint3D pos); 
  //void (* CalcPoints)(const CSol * this, int i1, int j1, int i2, int j2);
  
#if 0 
  void (* AfficherCube)(const CSol * this, const float x1, const float y1, const float z1, const float dx, const float dy, const float dz); 
  // FS: utiliser pour Debuguer   
  void (* MatricePourDessiner)(const CSol * this, const float i, const float j); 
  void (* MatricePour2D)(const CSol * this, float i, float j, float z);
  void (* glVertexTore)(const CSol * this, float x, float y, float z);
  //TPoint3D (* GetPoint3D)(const CSol * this, float i, float j, float z);
  void (* tore )(const CSol * this, int i,int j); 
  void (* tore0)(const CSol * this, int i,int j); 
  /*affiche une image 2D en )(CSol * this, i, j) )(CSol * this, position centrale au sol), d'altitude z, de texture tex, 
    et de taille définie*/
  void (* Blit)(CSol * this, float i, float j, float z, CTexture* tex, float taillex, float tailleh); 
  void (* Cube)(CSol * this, float i, float j, float z, float taillex, float tailleh); 
#endif 

#if 0 
  /*donne en fonction de la position en theta le facteur de compression
    il est le plus élevé à l'extérieur du tore, le plus petit à l'intérieur
    et vaut 1 sur le dessus, ou le dessous*/
  float (* FacteurCompression)(const CSol * this, float j);
  float (* IndiceTemps)(const CSol * this, float j);
  void  (* SetTemps)(      CSol * this, const float temps);
  float (* GetTemps)(const CSol * this);
#endif 

#if 0 
#if 0  
  void (* LookAt)(const CSol * this, float i, float j, float z); /*place la caméra au dessus du point (CSol * this, i, j)*/
  void (* LookAt)(const CSol * this, float i, float j, float z, float dist, float AngleXY, float AngleZ); /*place la caméra au dessus du point )(CSol * this, i, j)*/
#elif 0 
  void (* LookAt_vSimple)(const CSol * this, float i, float j, float z);
  void (* LookAt_vCompliquee)(const CSol * this, float i, float j, float z, float dist, float AngleXY, float AngleZ);
#else 
  void (* LookAt)(const CSol * this, float i, float j, float z);
  void (* LookAt_angle)(const CSol * this, float i, float j, float z, float dist, float AngleXY, float AngleZ);
#endif
#endif 
    

  
}; 

const int16_t CSol_bytesize_actual = sizeof(struct CSol); 
ASSERT_COMPILE_TOPLEVEL(CSol_bytesize >= CSol_bytesize_actual); 



float CSol__map_ZEau(const CSol * this) { return this -> map_ZEau; }; 
float * CSol__map_ZEau_ref(CSol * this) { return &(this -> map_ZEau); }; 







static int CSol__Normal_compute(CSol * this); 
static int CSol__compute__global_map__vertex_positions(CSol * this, const int global_map_i, const int global_map_j, const int over_spanning_w, const int over_spanning_h); 


#define theta_vue_blit -1.3f
#define HauteurCamera 120.0f

#if 0 
static int CSol__GetTailleX(const CSol * this) {
  return this -> TailleX; 
}; 

static int CSol__GetTailleY(const CSol * this) {
  return this -> TailleY;
}; 
#endif 


static bool CSol__yatilEau(const CSol * this, const float map_x, const float map_y, const float map_z) {
  return (map_z < this -> map_ZEau); 
}; 

#if 0 
// RL: That's a riemann function. 
static void CSol__SetTemps(CSol * this, const float in_temps) {
  our_manifold -> temps = in_temps;
};

// RL: That's a riemann function. 
static float CSol__GetTemps(const CSol * this) {
  return our_manifold -> temps;    
};
#endif 
	


#define TESTZ_X_Y(__this__,__x__,__y__) ((0 <= (__x__)) && ((__x__) < (__this__) -> TailleX) && (0 <= (__y__)) && ((__y__) < (__this__) -> TailleY)) 
#define  INDICE_Z(__this__,__x__,__y__) ((__y__) * (__this__) -> TailleX + (__x__)) 

#define TEST_TEXIND_X_Y(__this__,__x__,__y__) ((0 <= (__x__)) && ((__x__) < (__this__) -> indices_texture__width) && (0 <= (__y__)) && ((__y__) < (__this__) -> indices_texture__height)) 
#define      INDICE_TEX(__this__,__x__,__y__) ((__y__) * (__this__) -> indices_texture__width + (__x__)) 

static void CSol__SETZ(CSol * this, const int vertex_i, const int vertex_j, const float z) {
  if (!TESTZ_X_Y(this, vertex_i, vertex_j)) {
    messerr("ERREUR: Débordement de tableau dans Z avec (%i, %i)\n", vertex_i, vertex_j);
    return;
  }; 
  this -> ground__map_Z[INDICE_Z(this, vertex_i, vertex_j)] = z;
}; 

static float CSol__GETZ0(const CSol * this, const int vertex_i, const int vertex_j) { 
  if (TESTZ_X_Y(this, vertex_i, vertex_j)) { 
    return this -> ground__map_Z[INDICE_Z(this, vertex_i, vertex_j)]; 
  };   
  messerr("ERREUR : Débordement de tableau des Z avec (%i, %i)\n", vertex_i, vertex_j); 
  return -1; 
}; 

static void CSol__SETINDTEXTURE(CSol * this, const int tex_i, const int tex_j, const int ind) { 
  if (!TEST_TEXIND_X_Y(this, tex_i, tex_j)) { 
    messerr("ERREUR: Débordement de tableau d'indice de textures en écriture avec (%i, %i)\n", tex_i, tex_j);
    return; 
  };
  this -> indices_texture__array[INDICE_TEX(this, tex_i, tex_j)] = ind; 
}; 

static int CSol__GETINDTEXTURE(const CSol * this, const int tex_i, const int tex_j) {
  if (TEST_TEXIND_X_Y(this, tex_i, tex_j)) { 
    return this -> indices_texture__array[INDICE_TEX(this, tex_i, tex_j)]; 
  }; 
  assert(false); 
  messerr("ERREUR : Débordement de tableau d'indice de textures en lecture avec (%i, %i)\n", tex_i, tex_j); 
  return -1; 
}; 

extern int CSol__AjouterTextureSol(CSol * this, const char * s, const uint32_t couleur_dans_bitmap) { 
  if (this -> TextureSol_nb >= NB_MAX_TEXTURESOL) { 
    messerr("ERREUR: Il y a déjà trop de textures de sol dans le terrain." "\n"); 
    return -1; 
  }; 
  CTexture * t = CTexture_make(s); 
  if (t == NULL) { 
    messerr("ERREUR: Impossible de charger la texture: '%s'." "\n", s); 
    return -2; 
  }; 
  const int index = this -> TextureSol_nb; 
  this -> TextureSol_nb ++; 
  this -> TextureSol[index] = t; 
  this -> TextureSol_used_huh[index] = false; 
  this -> TextureSol_couleur_dans_bitmap[index] = couleur_dans_bitmap; 
  return index; 
}; 

static int CSol__Texture_Indice_Lookup(const CSol * this, const uint32_t couleur_dans_le_fichier_bitmap) { 
  for (int i = 0; i < this -> TextureSol_nb; i ++) { 
    if (couleur_dans_le_fichier_bitmap == this -> TextureSol_couleur_dans_bitmap[i]) { 
      return i; 
    }; 
  }; 
  return -1; 
}; 


static float CSol__GET_TEXTURE_ALPHA_AT_VERTEX(const CSol * this, const int vertex_i, const int vertex_j, const int texture_i) { 
  if (vertex_i <                   0) return 0.0f; 
  if (vertex_i > this -> TailleX - 1) return 0.0f; 
  if (vertex_j <                   0) return 0.0f; 
  if (vertex_j > this -> TailleY - 1) return 0.0f; 
  // RL: TODO XXX FIXME: all that could be pre-computed one time. 
  const float texture_x = ((float) vertex_i) / ((float) this -> TailleX - 1) * ((float) this -> indices_texture__width  - 1); 
  const float texture_y = ((float) vertex_j) / ((float) this -> TailleY - 1) * ((float) this -> indices_texture__height - 1); 
  const int tex0_i = (int) floorf(texture_x); 
  const int tex0_j = (int) floorf(texture_y); 
  const float lx = texture_x - tex0_i; 
  const float ly = texture_y - tex0_j; 
  
#define AA_GET_TEXIND(__this__,__x__,__y__) (TESTZ_X_Y((__this__),(__x__),(__y__)) ? (__this__) -> indices_texture__array[INDICE_TEX((__this__),(__x__),(__y__))] : -2) 
#define AA(__this__,__x__,__y__) (texture_i == AA_GET_TEXIND((__this__),(__x__),(__y__)) ? 1.0f : 0.0f) 
  const float a00 = AA(this, vertex_i  ,vertex_j  ); 
  const float a10 = AA(this, vertex_i+1,vertex_j  ); 
  const float a01 = AA(this, vertex_i  ,vertex_j+1); 
  const float a11 = AA(this, vertex_i+1,vertex_j+1); 
  
  const float a   = (a00 * (1 - lx) + a10 * lx) * (1 - ly) + 
                    (a01 * (1 - lx) + a11 * lx) *      ly; 
  
  return a; 
  //return 0.5f; 
  //return 1.0f; 
}; 


//static const riemann_t * __our_manifold__ = NULL; 
//static float CSol__GETZ(const CSol * this, const float map_x, const float map_y) { 
float CSol__GET_MAP_Z(const CSol * this, const float map_x, const float map_y) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " this = %p, map_x = %f, map_y = %f "  "\n", __func__, this, map_x, map_y); 
  // FS: /*on fait une interpolation pour connaître l'altitude (en fait, elle n'est connue que sur un maillage)*/ 
  
  const float stretched_map_x = map_x / ((float) this -> over_spanning_w); 
  const float stretched_map_y = map_y / ((float) this -> over_spanning_h); 
  
#if 1 
  const float ground_x = ((float) this -> TailleX - 1) * stretched_map_x; 
  const float ground_y = ((float) this -> TailleY - 1) * stretched_map_y; 
#else 
  const float ground_x = ((float) this -> TailleX) * (stretched_map_x - floorf(stretched_map_x)); 
  const float ground_y = ((float) this -> TailleY) * (stretched_map_y - floorf(stretched_map_y)); 
#endif 
  
  const int vertex_i = (int) floorf(ground_x); 
  const int vertex_j = (int) floorf(ground_y); 
  
  const float lx = ground_x - vertex_i; 
  const float ly = ground_y - vertex_j; 
  
//#define ZZ(x,y) (((((x) >= 0) && ((y) >= 0) && ((x) < this -> TailleX) && ((y) < this -> TailleY))) ? this -> Z[(ZIND((x),(y)))] : 0) 
#define ZZ(__this__,__x__,__y__) (TESTZ_X_Y((__this__),(__x__),(__y__)) ? (__this__) -> ground__map_Z[INDICE_Z((__this__),(__x__),(__y__))] : 0) 
  const float z00 = ZZ(this, vertex_i  ,vertex_j  ); 
  const float z10 = ZZ(this, vertex_i+1,vertex_j  ); 
  const float z01 = ZZ(this, vertex_i  ,vertex_j+1); 
  const float z11 = ZZ(this, vertex_i+1,vertex_j+1); 
  
  const float z   = (z00 * (1 - lx) + z10 * lx) * (1 - ly) + 
                    (z01 * (1 - lx) + z11 * lx) *      ly; 

#if 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " z00 = %f, z10 = %f, z01 = %f, z11 = %f, => map_z = %f "  "\n", __func__, z00, z10, z01, z11, z); 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " z00 = %f, z10 = %f, z01 = %f, z11 = %f, => map_z = %f "  "\n", __func__, (__our_manifold__) -> map_to_manifold_factor__z   * z00, (__our_manifold__) -> map_to_manifold_factor__z   * z10, (__our_manifold__) -> map_to_manifold_factor__z   * z01, (__our_manifold__) -> map_to_manifold_factor__z   * z11, (__our_manifold__) -> map_to_manifold_factor__z   * z); 
#endif 
#if 0 
  {
#undef ZZ 
#define ZZ(__this__,__x__,__y__) (TESTZ_X_Y((__this__),(__x__),(__y__)) ? (__this__) -> manifold__vertex[INDICE_Z((__this__),(__x__),(__y__))][2] : 0) 
  const float z00 = ZZ(this, vertex_i  ,vertex_j  ); 
  const float z10 = ZZ(this, vertex_i+1,vertex_j  ); 
  const float z01 = ZZ(this, vertex_i  ,vertex_j+1); 
  const float z11 = ZZ(this, vertex_i+1,vertex_j+1); 
  
  const float z   = (z00 * (1 - lx) + z10 * lx) * (1 - ly) + 
                    (z01 * (1 - lx) + z11 * lx) *      ly; 

    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " z00 = %f, z10 = %f, z01 = %f, z11 = %f, => map_z = %f "  "\n", __func__, z00, z10, z01, z11, z); 
  }; 
#endif 
  
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " this = %p, map_x = %f, map_y = %f => map_z = %f "  "\n", __func__, this, map_x, map_y, z); 
  
  return z; 
}; 

#if 1 
static float CSol__GetSlop(const CSol * this, const TPoint3D map_pos_new, const TPoint3D map_pos_old) { 
  const float map_pos_old__z = this -> GET_MAP_Z(this, map_pos_old.x, map_pos_old.y); 
  const float map_pos_new__z = this -> GET_MAP_Z(this, map_pos_new.x, map_pos_new.y); 
  return map_pos_new__z - map_pos_old__z; 
}; 
#else 
TPoint2D CSol__Differentiel(const CSol * this, const TPoint3D pos) { 
  TPoint2D p; 

#define precdiff 0.5f 

  const float z1 = this -> GETZ(this, pos.x + precdiff, pos.y           ) - this -> GETZ(this, pos.x, pos.y); 
  const float z2 = this -> GETZ(this, pos.x           , pos.y + precdiff) - this -> GETZ(this, pos.x, pos.y); 
  
  /* printf("Calcul de différentiel : %f, %f, %f, %f\n", this -> GETZ(this, pos.x+precdiff, pos.y),
     this -> GETZ(this, pos.x, pos.x), this -> GETZ(this, pos.x, pos.y+precdiff), this -> GETZ(this, pos.x, pos.y));*/
  
  p.x = z1; //this -> GETZ(this, int(rx)+1, int(ry)) - this -> GETZ(this, int(rx)-1, int(ry)); 
  p.y = z2; //this -> GETZ(this, int(rx), int(ry)+1) - this -> GETZ(this, int(rx), int(ry)-1); 
  
  return p; 
}; 
#endif 

static void CSol__compute_manifold_vertices_and_normals(CSol * this, const riemann_t * our_manifold) { 
  our_manifold -> compute_manifold_vertices_and_normals(our_manifold, this -> TailleX, this -> TailleY, 
							this -> ground__global_map_x, this -> ground__global_map_y, this -> ground__map_Z, this -> map_ZEau, 
							this -> ground__normal, 
							this -> manifold__extra_w_arrays__nb  , this -> manifold__extra_w_arrays, 
							this -> manifold__extra_h_arrays__nb  , this -> manifold__extra_h_arrays, 
							this -> manifold__extra_w_h_arrays__nb, this -> manifold__extra_w_h_arrays, 
							this -> manifold__vertex       , this -> manifold__normal, 
							this -> manifold__vertex__water, this -> manifold__normal__water); 
}; 


static int CSol__manifold__alloc_extra_temp_arrays(CSol * this, const riemann_t * our_manifold) { 
  this -> manifold__extra_w_arrays__nb = our_manifold -> get_nb_extra_w_arrays_needed(our_manifold); 
  if (this -> manifold__extra_w_arrays__nb >= NB_MAX_EXTRA_ARRAYS) { 
    messerr("ERREUR: Incompatibilité entre la variété riemannienne et la structure contenant le sol - la variété demande %s extra lignes en longueur pour contenir ses calculs intermédiaires, or la structure de sol ne peut en contenir que %s." "\n", int_string__stack(this -> manifold__extra_w_arrays__nb), int_string__stack(NB_MAX_EXTRA_ARRAYS)); 
    return -1; 
  }; 
  
  this -> manifold__extra_h_arrays__nb = our_manifold -> get_nb_extra_h_arrays_needed(our_manifold); 
  if (this -> manifold__extra_h_arrays__nb >= NB_MAX_EXTRA_ARRAYS) { 
    messerr("ERREUR: Incompatibilité entre la variété riemannienne et la structure contenant le sol - la variété demande %s extra lignes en hauteur pour contenir ses calculs intermédiaires, or la structure de sol ne peut en contenir que %s." "\n", int_string__stack(this -> manifold__extra_h_arrays__nb), int_string__stack(NB_MAX_EXTRA_ARRAYS)); 
    return -2; 
  }; 
  
  this -> manifold__extra_w_h_arrays__nb = our_manifold -> get_nb_extra_w_h_arrays_needed(our_manifold); 
  if (this -> manifold__extra_w_h_arrays__nb >= NB_MAX_EXTRA_ARRAYS) { 
    messerr("ERREUR: Incompatibilité entre la variété riemannienne et la structure contenant le sol - la variété demande %s extra tableaux pour contenir ses calculs intermédiaires, or la structure de sol ne peut en contenir que %s." "\n", int_string__stack(this -> manifold__extra_w_h_arrays__nb), int_string__stack(NB_MAX_EXTRA_ARRAYS)); 
    return -3; 
  }; 
  
  for (int i = 0; i < this -> manifold__extra_w_arrays__nb; i++) { 
    this -> manifold__extra_w_arrays[i]   = malloc(sizeof(*(this -> manifold__extra_w_arrays[i])) * (this -> TailleX)); 
  }; 
  for (int i = 0; i < this -> manifold__extra_h_arrays__nb; i++) { 
    this -> manifold__extra_h_arrays[i]   = malloc(sizeof(*(this -> manifold__extra_h_arrays[i])) * (this -> TailleY)); 
  }; 
  for (int i = 0; i < this -> manifold__extra_w_h_arrays__nb; i++) { 
    this -> manifold__extra_w_h_arrays[i] = malloc(sizeof(*(this -> manifold__extra_w_h_arrays[i])) * (this -> TailleX) * (this -> TailleY)); 
  }; 
  
  this -> manifold__vertex            = malloc(sizeof(*this -> manifold__vertex           ) * ((this -> TailleX)*(this -> TailleY))); 
  this -> manifold__normal            = malloc(sizeof(*this -> manifold__normal           ) * ((this -> TailleX)*(this -> TailleY))); 
  this -> manifold__vertex__water     = malloc(sizeof(*this -> manifold__vertex__water    ) * ((this -> TailleX)*(this -> TailleY))); 
  this -> manifold__normal__water     = malloc(sizeof(*this -> manifold__normal__water    ) * ((this -> TailleX)*(this -> TailleY))); 
  
  return 0; 
}; 



static int CSol__ChargerTextureSolDisposition(CSol * this, const char * fichier_bitmap) { 
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Chargement des zones de textures - fichier:  '%s' " "\n", __func__, fichier_bitmap); 
  
  if (fichier_bitmap == NULL) { return -1; }; 
  
  char reelfile[strlen(NIVEAUXDIR) + strlen(fichier_bitmap) + 1];
  strcat(strcpy(reelfile, NIVEAUXDIR), fichier_bitmap);
  fichier_bitmap = reelfile;
  
  SDL_Surface * img = NULL;
  img = IMG_Load(fichier_bitmap);
  
  if (img == NULL) { 
    messerr("ERREUR: Impossible de lire le fichier image '%s' (ce fichier contient les indices des textures du terrain) - SDL_Image: %s" "\n", fichier_bitmap, IMG_GetError()); 
    return -2; 
  }; 

#if 0 
  if ((img -> w != this -> TailleX) || (img -> h != this -> TailleY)) { 
    messerr("ERREUR: La taille de l'image %s est différente de celle spécifiée dans le fichier des altitudes." "\n", fichier_bitmap); 
    messerr("\t\t" "TEX: " "w x h = %d pixels x %d pixels " "\n", img -> w, img -> h); 
    messerr("\t\t" "Z  : " "w x h = %d pixels x %d pixels " "\n", this -> TailleX, this -> TailleY); 
    return; 
  }; 
#endif 

  if (img -> w >= UINT8_MAX - 1) { 
    messerr("ERREUR: L'image est incompatible: elle ne devrait pas possèder plus de %s sommets en longueur, or elle en contient %s. (Fichier: '%s' [contient les indices des textures du terrain])" "\n", int_string__stack(UINT8_MAX - 1), int_string__stack(img -> w), fichier_bitmap); 
    SDL_FreeSurface(img); 
    return -3; 
  }; 
  
  if (img -> h >= UINT8_MAX - 1) { 
    messerr("ERREUR: L'image est incompatible: elle ne devrait pas possèder plus de %s sommets en hauteur, or elle en contient %s. (Fichier: '%s' [contient les indices des textures du terrain])" "\n", int_string__stack(UINT8_MAX - 1), int_string__stack(img -> h), fichier_bitmap); 
    SDL_FreeSurface(img); 
    return -4; 
  }; 
  
  this -> indices_texture__width  = img -> w; 
  this -> indices_texture__height = img -> h; 
  printf(" ==> Taille de la carte des indices des textures en _*_sommets_*_ (pas en cases!): %s x %s " "\n", int_string__stack(this -> indices_texture__width), int_string__stack(this -> indices_texture__height)); 
  
  if (img->format->BytesPerPixel != 3) { 
    messerr("WARNING: " "L'image '%s' devrait être dans un format 24 bits." "\n.", fichier_bitmap); 
    messerr("         " "Cette image représente les indices des textures du terrain. Or elle est dans un format: %d BytesPerPixel." "\n", img->format->BytesPerPixel); 
    messerr("         " "\t" "w x h = %d pixels x %d pixels " "\n", img -> w, img -> h); 
  }; 
  
  // *** conversion de l'image dans un état potable (RGB) ***
  {
    SDL_Surface * convertie = SDL_ConvertSurface(img, &sdl_pixel_format_rgb, SDL_SWSURFACE);
    SDL_FreeSurface(img); 
    img = convertie; 
  }; 

  const int bpp = img -> format -> BytesPerPixel; 
  assert(3 == bpp); 
  
  const uint8_t * p = (uint8_t *) img -> pixels; 
  //uint24_t * p = (uint24_t *) img -> pixels;
  //uint32_t * p32 = (uint32_t *) img -> pixels;
  //printf("pointeur image: %p\n", p); 
  
  //printf("Allocation en mémoire de la table qui à un point de la carte associe l'id de la texture de ce point." "\n"); 
  //this -> indices_texture = malloc(sizeof(*this -> indices_texture) * ((this -> TailleX)*(this -> TailleY))); 
  this -> indices_texture__array = malloc(sizeof(*this -> indices_texture__array) * ((this -> indices_texture__width)*(this -> indices_texture__height))); 

#define stdtexind                stdout 
#define PRINTF_texind_LINE_BEGIN fprintf(stdtexind, "%2d - [", j); 
#define PRINTF_texind_LINE_END   fprintf(stdtexind, "]\n"); 
  //#define PRINTF_texind fprintf(stdtexind, "%d, ", ind_color); 
#define PRINTF_texind            fprintf(stdtexind, "%d, ", k); 

  for (int j = 0; j < img -> h; j++) { 
    PRINTF_texind_LINE_BEGIN; 
    for (int i = 0; i < img -> w; i++) { 
      //int ind_color = p[j * img->pitch + i * bpp] + 256*p[j * img->pitch + i * bpp + 1] + 256*256*p[j * img->pitch + i * bpp + 2]; 
      const int ind_color = 256*256*p[j * img->pitch + i * bpp] + 256*p[j * img->pitch + i * bpp + 1] + p[j * img->pitch + i * bpp + 2]; 
      
      const int k = CSol__Texture_Indice_Lookup(this, ind_color); 
      if (k < 0) { 
	messerr("ERREUR: la couleur %i au pixel (%i, %i) n'est associée à aucune texture." "\n", ind_color, i, j); 
      }; 
      
      CSol__SETINDTEXTURE(this, i, img->h-1-j, k); 
      
      if (k >= 0) { 
	this -> TextureSol_used_huh[k] = true; 
      }; 
      
      PRINTF_texind; 
    }; 
    PRINTF_texind_LINE_END; 
  }; 
  
  SDL_FreeSurface(img); 
  printf("Chargement des dispositions des textures terminé." "\n"); 
  return 0; 
}; 


static int CSol__ChargerZ(CSol * this, const float lattice_to_map_scale_factor__z, const char * filename) { 
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Chargement des niveaux de la carte: '%s'" "\n", __func__, filename == NULL ? "<null>" : filename); 

  if (filename == NULL) return -1; 
  
  char reelfile[ARRAY_SIZE(NIVEAUXDIR)-1 + strlen(filename) + 1]; 
  strcat(strcpy(reelfile, NIVEAUXDIR), filename); 
  filename = reelfile; 
  
  SDL_Surface * img; 
  img = IMG_Load(filename); 
  
  if (img == NULL) { 
    messerr("ERREUR: Impossible de lire le fichier image '%s' (ce fichier contient les Z du terrain) - SDL_Image: %s" "\n", filename, IMG_GetError()); 
    return -2; 
  }; 
  
  const int bpp = img -> format -> BytesPerPixel; 
  
  if (bpp != 1) { 
    messerr("WARNING: " "L'image '%s' doit être dans un format niveau de gris. Elle représente les Z de la carte. Or elle est dans un format: %d BytesPerPixel. En conséquence de quoi, nous utiliserons la couleur rouge en tant que proxy.\n", filename, bpp); 
    messerr("\t\t" "w x h = %d pixels x %d pixels " "\n", img -> w, img -> h); 
    //messerr("\t\t" "img -> format -> format = %d  " "\n", img -> format -> format); 
  }; 
  
  if (img -> w >= UINT8_MAX - 1) { 
    messerr("ERREUR: L'image est incompatible: elle ne devrait pas possèder plus de %s sommets en longueur, or elle en contient %s. (Fichier: '%s' [contient les Z du terrain])" "\n", int_string__stack(UINT8_MAX - 1), int_string__stack(img -> w), filename); 
    return -3; 
  }; 
  
  if (img -> h >= UINT8_MAX - 1) { 
    messerr("ERREUR: L'image est incompatible: elle ne devrait pas possèder plus de %s sommets en hauteur, or elle en contient %s. (Fichier: '%s' [contient les Z du terrain])" "\n", int_string__stack(UINT8_MAX - 1), int_string__stack(img -> h), filename); 
    return -4; 
  }; 
  
  this -> TailleX = img -> w; 
  this -> TailleY = img -> h; 
  printf(" ==> Taille de la carte des Z en sommets: %s x %s " "\n", int_string__stack(this -> TailleX), int_string__stack(this -> TailleY)); 
  
  
  // RL: Alright. We're good to move forward. 
  
  this -> ground__map_Z = malloc(sizeof(*this -> ground__map_Z) * ((this -> TailleX)*(this -> TailleY))); 
  
  const uint8_t  * p8  = (uint8_t  *) img -> pixels;
  const uint32_t * p32 = (uint32_t *) img -> pixels;
    
#define PRINTF_Z_LINE_BEGIN fprintf(stdout, "%2d - [", j); 
#define PRINTF_Z_LINE_END   fprintf(stdout, "]\n"); 
#define PRINTF_Z            fprintf(stdout, "%d, ", z_valeur); 
  for (int j = 0; j < img -> h; j++) { 
    PRINTF_Z_LINE_BEGIN; 
    for (int i = 0; i < img -> w; i++) { 
      uint8_t z_valeur; 
      
      if (1 == bpp) { 
        z_valeur = p8[j * img -> w + i]; 
      } 
      else if (4 == bpp) { 
        uint32_t temp = p32[j * img -> w + i];
        temp &= img -> format -> Rmask;           //* Isolate red component */
        temp = (temp >> img -> format -> Rshift); //* Shift it down to 8-bit */
        temp = (temp << img -> format -> Rloss);  //* Expand to a full 8-bit number */
	
        z_valeur = temp; 
      } 
      else if (3 == bpp) { 
        z_valeur = p8[(j * img->w + i) * bpp]; 
      } 
      else { 
        assert(false); 
        z_valeur = 0; 
      }; 
      
      //messerr("\t" "z_valeur = %d " "\n", z_valeur); 
      PRINTF_Z; 
      
      //CSol__SETZ(this, i, img->h - 1 - j,  (((float) z_valeur) - 128.0f) * lattice_to_map_scale_factor__z); 
      CSol__SETZ(this, i, img->h - 1 - j,  (((float) z_valeur) - 128.0f) * lattice_to_map_scale_factor__z * 0.05f); 
    }; 
    PRINTF_Z_LINE_END; 
  }; 
  
  SDL_FreeSurface(img); 
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Chargement des Z terminés || Loading z-levels completed" "\n", __func__); 
  return 0; 
}; 




























#define ARF(__i1__,__TailleX__) if (__i1__ < 0) { __i1__ = 0; } else if (__i1__ >= __TailleX__ - 1) { __i1__ = __TailleX__ - 2; }; 







//void CSol__Render__pre_computations(CSol * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int global_map_i, const int target_map_j, const float target_map_x, const float target_map_y) { 
void CSol__Render__pre_computations(CSol * this, const riemann_t * our_manifold, const int global_map_i, const int global_map_j, const float target_map_x, const float target_map_y, const float target_map_dx, const float target_map_dy) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " this = %p, our_manifold = %p, global_map_i = %d, global_map_j = %d, target_map_x = %f, target_map_y = %f, target_map_dx = %f, target_map_dy = %f "   "\n", __func__, this, our_manifold, global_map_i, global_map_j, target_map_x, target_map_y, target_map_dx, target_map_dy); 
  CSol__compute_manifold_vertices_and_normals(this, our_manifold); 
}; 



#if 1  
//static void CSol__Render(const CSol * this, int i1, int j1, int i2, int j2) { 
//void CSol__Render(const CSol * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int global_map_i, const int target_map_j, const float target_map_x, const float target_map_y) { 
void CSol__Render(const CSol * this, const riemann_t * our_manifold, const int global_map_i, const int global_map_j, const float target_map_x, const float target_map_y, const float target_map_dx, const float target_map_dy) { 
  //messerr("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: "  "CSol = %p - i1, i2, j1, j2 = %d, %d, %d, %d" "\n", __func__, this, i1, i2, j1, j2); 
  //messerr("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: "  "CSol = %p - our_manifold = %p - nb_cells_displayed_x, nb_cells_displayed_y, global_map_i, target_map_j, target_map_x, target_map_y = %d, %d, %d, %d, %f, %f" "\n", __func__, this, our_manifold, nb_cells_displayed_x, nb_cells_displayed_y, global_map_i, target_map_j, target_map_x, target_map_y); 
  //fprintf(stderr, "RenderSol: I am called\n"); 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "(const CSol * this = %p, const riemann_t * our_manifold = %p, const int global_map_i = %d, const int global_map_j = %d, const float target_map_x = %f, const float target_map_y = %f, const float target_map_dx = %f, const float target_map_dy = %f) "   "\n", __func__, this, our_manifold, global_map_i, global_map_j, target_map_x, target_map_y, target_map_dx, target_map_dy); 

  
  const float stretched_map_x = target_map_x / ((float) this -> over_spanning_w); 
  const float stretched_map_y = target_map_y / ((float) this -> over_spanning_h); 
  
#if 1 
  const float ground_x = ((float) this -> TailleX - 1) * stretched_map_x; 
  const float ground_y = ((float) this -> TailleY - 1) * stretched_map_y; 
#else 
  const float ground_x = ((float) this -> TailleX) * (stretched_map_x - floorf(stretched_map_x)); 
  const float ground_y = ((float) this -> TailleY) * (stretched_map_y - floorf(stretched_map_y)); 
#endif 

  ///fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " target_map_x = %f, target_map_y = %f, ground_x = %f, ground_y = %f "  "\n", __func__, target_map_x, target_map_y, ground_x, ground_y); 


  const int vertex_di = ceilf(((float) this -> TailleX) * target_map_dx / ((float) this -> over_spanning_w)); 
  const int vertex_dj = ceilf(((float) this -> TailleY) * target_map_dy / ((float) this -> over_spanning_h)); 
  
  const int vertex0_i = (int) floorf(ground_x); 
  const int vertex0_j = (int) floorf(ground_y); 

  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " target_map_x = %f, target_map_y = %f, ground_x = %f, ground_y = %f, vertex0_i = %d, vertex0_j = %d "  "\n", __func__, target_map_x, target_map_y, ground_x, ground_y, vertex0_i, vertex0_j); 

  
  const int vertex1_i = MAX(0,vertex0_i - (vertex_di >> 1)); 
  const int vertex1_j = MAX(0,vertex0_j - (vertex_dj >> 1)); 
  
  const int vertex2_i = MIN(this -> TailleX - 1, vertex1_i + vertex_di); 
  const int vertex2_j = MIN(this -> TailleY - 1, vertex1_j + vertex_dj); 

  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " vertex1(i,j) = (%d,%d) - vertex2 = (%d,%d) "   "\n", __func__, vertex1_i, vertex1_j, vertex2_i, vertex2_j); 

#if 1 
  // RL: Because the ground renders very weirdly with blending. 
    glDisable(GL_BLEND) ;
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;   
#endif 

  glEnable(GL_TEXTURE_2D);  
  // RL: Here is the logic of that weird thing: 
  //      - All textures are blitted. 
  //      - On vertices, it's the alpha channel that decides whether they are rendered or not. 
  //for (int tex_i = 0; tex_i < MIN(1,this -> TextureSol_nb); tex_i++) { 
#if 1
  for (int tex_i = 0; tex_i < this -> TextureSol_nb; tex_i++) { 
#else 
  for (int utex_i = 0; utex_i < this -> TextureSol_nb; utex_i++) { 
    const int tex_i = this -> TextureSol_nb - 1 - utex_i; // RL: Weirdly enough, the blending depends on the texture order. The first one is not blended - only the last one. 
#endif 
    if (!(this -> TextureSol_used_huh[tex_i])) { continue; }; 
    
    CTexture__GLTextureCourante(this -> TextureSol[tex_i]); 
    
    ///for (int vertex_i = vertex1_i; vertex_i <= vertex2_i; vertex_i++) { 
    for (int vertex_i = vertex1_i; vertex_i < vertex2_i; vertex_i++) { 
      //for (int vertex_j = vertex1_j; vertex_j <= vertex2_j; vertex_j++) { 
      for (int vertex_j = vertex1_j; vertex_j < vertex2_j; vertex_j++) { 
	const int index00 = (vertex_j + 0) * this -> TailleX + (vertex_i + 0); 
	const int index01 = (vertex_j + 1) * this -> TailleX + (vertex_i + 0); 
	const int index11 = (vertex_j + 1) * this -> TailleX + (vertex_i + 1); 
	const int index10 = (vertex_j + 0) * this -> TailleX + (vertex_i + 1); 
	
	const float a00 = CSol__GET_TEXTURE_ALPHA_AT_VERTEX(this, vertex_i + 0, vertex_j + 0, tex_i); 
	const float a01 = CSol__GET_TEXTURE_ALPHA_AT_VERTEX(this, vertex_i + 0, vertex_j + 1, tex_i); 
	const float a11 = CSol__GET_TEXTURE_ALPHA_AT_VERTEX(this, vertex_i + 1, vertex_j + 1, tex_i); 
	const float a10 = CSol__GET_TEXTURE_ALPHA_AT_VERTEX(this, vertex_i + 1, vertex_j + 0, tex_i); 

	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " a00 = %f, a10 = %f, a11 = %f, a01 = %f  " "\n", __func__, a00, a10, a11, a01); 
#if 1 
        glBegin(GL_QUADS); { 
          glColor4f(1.0f, 1.0f, 1.0f, a00); 
          glTexCoord2f(0.0f,0.0f); 
	  glNormal3fv(this -> manifold__normal[index00]); 
	  glVertex3fv(this -> manifold__vertex[index00]); 
	  
          glColor4f(1.0f, 1.0f, 1.0f, a10); 
          glTexCoord2f(1.0f,0.0f); 
	  glNormal3fv(this -> manifold__normal[index10]); 
	  glVertex3fv(this -> manifold__vertex[index10]); 
          
          glColor4f(1.0f, 1.0f, 1.0f, a11); 
          glTexCoord2f(1.0f,1.0f); 
	  glNormal3fv(this -> manifold__normal[index11]); 
	  glVertex3fv(this -> manifold__vertex[index11]); 
          
          glColor4f(1.0f, 1.0f, 1.0f, a01); 
          glTexCoord2f(0.0f,1.0f); 
	  glNormal3fv(this -> manifold__normal[index01]); 
	  glVertex3fv(this -> manifold__vertex[index01]); 
        } glEnd(); 
#else         
        glBegin(GL_QUADS); { 
          glColor4f(1.0f, 1.0f, 1.0f, a00); 
          glTexCoord2f(0.0f,0.0f); 
	  glNormal3fv(this -> manifold__normal__water[index00]); 
	  glVertex3fv(this -> manifold__vertex[index00]); 
	  
          glColor4f(1.0f, 1.0f, 1.0f, a10); 
          glTexCoord2f(1.0f,0.0f); 
	  glNormal3fv(this -> manifold__normal__water[index10]); 
	  glVertex3fv(this -> manifold__vertex[index10]); 
          
          glColor4f(1.0f, 1.0f, 1.0f, a11); 
          glTexCoord2f(1.0f,1.0f); 
	  glNormal3fv(this -> manifold__normal__water[index11]); 
	  glVertex3fv(this -> manifold__vertex[index11]); 
          
          glColor4f(1.0f, 1.0f, 1.0f, a01); 
          glTexCoord2f(0.0f,1.0f); 
	  glNormal3fv(this -> manifold__normal__water[index01]); 
	  glVertex3fv(this -> manifold__vertex[index01]); 
        } glEnd(); 
#endif 
      }; 
    }; 
    }; 
#if 1 
    glEnable(GL_BLEND) ;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;   
#endif 
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // RL: Re-set alpha-channel at 1.0f. 
}; 
#else 
//static void CSol__Render(const CSol * this, int i1, int j1, int i2, int j2) { 
//void CSol__Render(const CSol * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int global_map_i, const int target_map_j, const float target_map_x, const float target_map_y) { 
void CSol__Render(const CSol * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int global_map_i, const int target_map_j, const float target_map_x, const float target_map_y) { 
  //messerr("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: "  "CSol = %p - i1, i2, j1, j2 = %d, %d, %d, %d" "\n", __func__, this, i1, i2, j1, j2); 
  //messerr("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: "  "CSol = %p - our_manifold = %p - nb_cells_displayed_x, nb_cells_displayed_y, global_map_i, target_map_j, target_map_x, target_map_y = %d, %d, %d, %d, %f, %f" "\n", __func__, this, our_manifold, nb_cells_displayed_x, nb_cells_displayed_y, global_map_i, target_map_j, target_map_x, target_map_y); 
  //fprintf(stderr, "RenderSol: I am called\n"); 
  
  const float sol_x = ((float) this -> TailleX) * (target_map_x - floorf(target_map_x)); 
  const float sol_y = ((float) this -> TailleX) * (target_map_y - floorf(target_map_y)); 
  
  const int nb_cells_on_the_left  = nb_cells_displayed_x >> 1; 
  const int nb_cells_on_the_right = nb_cells_displayed_x - nb_cells_on_the_left; 

  const int nb_cells_behind  = nb_cells_displayed_y >> 1; 
  const int nb_cells_infront = nb_cells_displayed_y - nb_cells_behind; 
  
  const int cell0_x = floorf(sol_x); 
  const int cell0_y = floorf(sol_y); 
  
  const int cell1_x = MAX(0,cell0_x - nb_cells_on_the_left); 
  const int cell1_y = MAX(0,cell0_y - nb_cells_behind); 
  
  const int cell2_x = MIN(this -> TailleX - 2, cell0_x + nb_cells_on_the_right); 
  const int cell2_y = MIN(this -> TailleY - 2, cell0_y + nb_cells_infront); 
  
  glEnable(GL_TEXTURE_2D);  

  /* 
     ALPHATEX(i, j) renvoit 1.0f si la texture de n° numtex s'affiche en (i, j)
     sinon renvoie 0.0f
  */
#if 1 
#define ALPHATEX(i, j)						\
  ((this -> GETINDTEXTURE(this, i, j) == numtex) ? 1.0f : 0.0f) 
#else 
#define ALPHATEX(i, j)							\
  ((this -> GETINDTEXTURE(this, i, j) == numtex) || (numtex >= 0) ? 1.0f : 0.0f)	
#endif 

  // RL: Oh My Lord! 
  // RL: The ground is blitted 'numtex' times! 
  //     Why??? 
  // 

  // RL: Here is the logic of that weird thing: 
  //      - All textures are blitted. 
  //      - On vertices, it's a blended value that we have. 

  // RL: TODO XXX FIXME: Same computations done too many times. Improve! 
  for (int numtex = 0; numtex < this -> nb_texture; numtex++) { 
    if (!(this -> TextureSol_used_huh[numtex])) { continue; }; 

    this -> TextureSol[numtex] -> GLTextureCourante(this -> TextureSol[numtex]); 
    
    for (int vertex_i = cell1_x; vertex_i <= cell2_x; vertex_i++) { 
      for (int vertex_j = cell1_y; vertex_j <= cell2_y; vertex_j++) { 
	const int index00 = (vertex_j + 0) * this -> TailleX + (vertex_i + 0); 
	const int index01 = (vertex_j + 1) * this -> TailleX + (vertex_i + 0); 
	const int index11 = (vertex_j + 1) * this -> TailleX + (vertex_i + 1); 
	const int index10 = (vertex_j + 0) * this -> TailleX + (vertex_i + 1); 
        const int x = vertex_i; 
        const int y = vertex_j; 
	
        const float a1 = ALPHATEX(x  , y  ); 
        const float a2 = ALPHATEX(x+1, y  ); 
        const float a3 = ALPHATEX(x+1, y+1); 
        const float a4 = ALPHATEX(x  , y+1); 
        
        glBegin(GL_QUADS); { 
          glColor4f(1.0f, 1.0f, 1.0f, a1); // RL: Setting up the alpha channel. 
          glTexCoord2f(0.0f,0.0f); 
          //this -> tore(this, x, y); // RL: It's a call to glVertex (and glNormal). BASICALLY, this is the projection function. 
	  glNormal3fv(this -> manifold__normal[index00]); // RL: For lighting models - it smoothens the vertex. // RL: It seems like the call to vertex must be after the call the normal. The vertex and the normal are linked together. Because all the upcoming vertex will get that normal. 
	  glVertex3fv(this -> manifold__vertex[index00]); 
	  
          glColor4f(1.0f, 1.0f, 1.0f, a2); 
          glTexCoord2f(1.0f,0.0f); 
          //this -> tore(this, x+1, y); 
	  glNormal3fv(this -> manifold__normal[index10]); 
	  glVertex3fv(this -> manifold__vertex[index10]); 
          
          glColor4f(1.0f, 1.0f, 1.0f, a3); 
          glTexCoord2f(1.0f,1.0f); 
          //this -> tore(this, x+1, y+1); 
	  glNormal3fv(this -> manifold__normal[index11]); 
	  glVertex3fv(this -> manifold__vertex[index11]); 
          
          glColor4f(1.0f, 1.0f, 1.0f, a4); 
          glTexCoord2f(0.0f,1.0f); 
          //this -> tore(this, x, y+1); 
	  glNormal3fv(this -> manifold__normal[index01]); 
	  glVertex3fv(this -> manifold__vertex[index01]); 
        } glEnd(); 
      };
    };
  };
}; 
#endif 



#if 1 
void CSol__RenderEau(const CSol * this, const riemann_t * our_manifold, const int global_map_i, const int global_map_j, const float target_map_x, const float target_map_y, const float target_map_dx, const float target_map_dy) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "(const CSol * this = %p, const riemann_t * our_manifold = %p, const int global_map_i = %d, const int global_map_j = %d, const float target_map_x = %f, const float target_map_y = %f, const float target_map_dx = %f, const float target_map_dy = %f) "   "\n", __func__, this, our_manifold, global_map_i, global_map_j, target_map_x, target_map_y, target_map_dx, target_map_dy); 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " over_spanning_w = %d - over_spanning_h = %d - map_Zeau = %f "   "\n", __func__, this -> over_spanning_w, this -> over_spanning_h, this -> map_ZEau); 
  
  const float stretched_map_x = target_map_x / ((float) this -> over_spanning_w); 
  const float stretched_map_y = target_map_y / ((float) this -> over_spanning_h); 
  
#if 1 
  const float ground_x = ((float) this -> TailleX - 1) * stretched_map_x; 
  const float ground_y = ((float) this -> TailleY - 1) * stretched_map_y; 
#else 
  const float ground_x = ((float) this -> TailleX) * (stretched_map_x - floorf(stretched_map_x)); 
  const float ground_y = ((float) this -> TailleY) * (stretched_map_y - floorf(stretched_map_y)); 
#endif 

  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " ground_x = %f - ground_y = %f "   "\n", __func__, ground_x, ground_y); 

  const int vertex_di = ceilf(((float) this -> TailleX) * target_map_dx / ((float) this -> over_spanning_w)); 
  const int vertex_dj = ceilf(((float) this -> TailleY) * target_map_dy / ((float) this -> over_spanning_h)); 
  
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " vertex_di = %d - vertex_dj = %d "   "\n", __func__, vertex_di, vertex_dj); 
  
  const int vertex0_i = (int) floorf(ground_x); 
  const int vertex0_j = (int) floorf(ground_y); 
  
  const int vertex1_i = MAX(0,vertex0_i - (vertex_di >> 1)); 
  const int vertex1_j = MAX(0,vertex0_j - (vertex_dj >> 1)); 
  
enum { PREC_EAU = 3 }; 

  const int vertex2_i = MIN(this -> TailleX + PREC_EAU, vertex1_i + vertex_di); 
  const int vertex2_j = MIN(this -> TailleY + PREC_EAU, vertex1_j + vertex_dj); 

  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " vertex1(i,j) = (%d,%d) - vertex2 = (%d,%d) "   "\n", __func__, vertex1_i, vertex1_j, vertex2_i, vertex2_j); 

#define COLOR_EAU(__i__,__j__) glColor4f(0.7f,0.7f,1.0f, 0.5f + 0.2f*cos(((__i__)+(__j__)+100*our_manifold -> temps)/2.0f)); 

  glDisable(GL_TEXTURE_2D); { 
enum { PREC_EAU = 3 }; 
    for (int vertex_i = vertex1_i; vertex_i <= vertex2_i; vertex_i += PREC_EAU) { 
      glBegin(GL_QUAD_STRIP); { 
	for (int vertex_j = vertex1_j; vertex_j <= vertex2_j; vertex_j += PREC_EAU) { 
	  const int index00 = MIN(this -> TailleY - 1, vertex_j +        0) * this -> TailleX + MIN(this -> TailleX - 1, vertex_i +        0); 
	  //const int index01 = (vertex_j + PREC_EAU) * this -> TailleX + (vertex_i +        0); 
	  //const int index11 = (vertex_j + PREC_EAU) * this -> TailleX + (vertex_i + PREC_EAU); 
	  const int index10 = MIN(this -> TailleY - 1, vertex_j +        0) * this -> TailleX + MIN(this -> TailleX - 1, vertex_i + PREC_EAU); 
	  
          COLOR_EAU(vertex_i, vertex_j); 
	  glNormal3fv(this -> manifold__normal__water[index00]); 
	  glVertex3fv(this -> manifold__vertex__water[index00]); 
	  
          COLOR_EAU(vertex_i + PREC_EAU, vertex_j); 
	  glNormal3fv(this -> manifold__normal__water[index10]); 
	  glVertex3fv(this -> manifold__vertex__water[index10]); 
	}; 
      } glEnd(); 
    }; 
    glColor3f(1.0f,1.0f,1.0f); 
  } glEnable(GL_TEXTURE_2D); 
  
}; 
#elif 0 
static void CSol__RenderEau(const CSol * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int global_map_i, const int target_map_j, const float target_map_x, const float target_map_y) { 
  //messerr("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: "  "CSol = %p - our_manifold = %p - nb_cells_displayed_x, nb_cells_displayed_y, global_map_i, target_map_j, target_map_x, target_map_y = %d, %d, %d, %d, %f, %f" "\n", __func__, this, our_manifold, nb_cells_displayed_x, nb_cells_displayed_y, global_map_i, target_map_j, target_map_x, target_map_y); 
  //fprintf(stderr, "RenderSol: I am called\n"); 
  
  const float sol_x = ((float) this -> TailleX) * (target_map_x - floorf(target_map_x)); 
  const float sol_y = ((float) this -> TailleX) * (target_map_y - floorf(target_map_y)); 
  
  const int nb_cells_on_the_left  = nb_cells_displayed_x >> 1; 
  const int nb_cells_on_the_right = nb_cells_displayed_x - nb_cells_on_the_left; 

  const int nb_cells_behind  = nb_cells_displayed_y >> 1; 
  const int nb_cells_infront = nb_cells_displayed_y - nb_cells_behind; 
  
  const int cell0_x = floorf(sol_x); 
  const int cell0_y = floorf(sol_y); 

  const int cell1_x = MAX(0,cell0_x - nb_cells_on_the_left); 
  const int cell1_y = MAX(0,cell0_y - nb_cells_behind); 
  
  const int cell2_x = MIN(this -> TailleX - 1, cell0_x + nb_cells_on_the_right); 
  const int cell2_y = MIN(this -> TailleY - 1, cell0_y + nb_cells_infront); 
  
  
  
#define COLOR_EAU(__i__,__j__) glColor4f(0.7f,0.7f,1.0f, 0.5f + 0.2f*cos(((__i__)+(__j__)+100*our_manifold -> temps)/2.0f));
  //#define COLOR_EAU(i, j) glColor4f(0.5f,0.0f,0.0f, 0.5f + 0.2f*cos(((i)+(j)+100*t)/2.0f));

  //fprintf(stderr, "RenderEau: I am called\n");
  //Render(i1, j1, i2, j2);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

  //glDepthFunc(GL_LEQUAL);
  glDisable(GL_TEXTURE_2D); { 
#define PREC_EAU 3 
    for (int vertex_i = cell1_x; vertex_i <= cell2_x; vertex_i += PREC_EAU) { 
      glBegin(GL_QUAD_STRIP); { 
	for (int vertex_j = cell1_y; vertex_j <= cell2_y; vertex_j += PREC_EAU) { 
	  const int index00 = (vertex_j +        0) * this -> TailleX + (vertex_i +        0); 
	  const int index01 = (vertex_j + PREC_EAU) * this -> TailleX + (vertex_i +        0); 
	  const int index11 = (vertex_j + PREC_EAU) * this -> TailleX + (vertex_i + PREC_EAU); 
	  const int index10 = (vertex_j +        0) * this -> TailleX + (vertex_i + PREC_EAU); 
	  
          COLOR_EAU(vertex_i, vertex_j); 
          //	glTexCoord2f(0.0f + num_tex*0.5f,0.0f); 
          //this -> tore0(this, i,j); // RL: Basically, it's a call to glVertex (& glNormal). 
	  glNormal3fv(this -> manifold__normal__water[index00]); 
	  glVertex3fv(this -> manifold__vertex__water[index00]); 

	  
          COLOR_EAU(vertex_i + PREC_EAU, vertex_j); 
          //	glTexCoord2f(0.5f + num_tex*0.5f,0.0f); 
          //this -> tore0(this, i+PREC_EAU,j); 
	  glNormal3fv(this -> manifold__normal__water[index10]); 
	  glVertex3fv(this -> manifold__vertex__water[index10]); 
	  
#if 0
          //	glTexCoord2f(0.5f + num_tex*0.5f,1.0f);
          COLOR_EAU(vertex_i + PREC_EAU, vertex_j + PREC_EAU);
          //this -> tore0(this, i+PREC_EAU,j+PREC_EAU); 
	  glNormal3fv(this -> manifold__normal__water[index11]); 
	  glVertex3fv(this -> manifold__vertex__water[index11]); 

          //	glTexCoord2f(0.0f + num_tex*0.5f,1.0f);
          COLOR_EAU(vertex_i, vertex_j + PREC_EAU);
          //this -> tore0(this, i,j+PREC_EAU);
	  glNormal3fv(this -> manifold__normal__water[index01]); 
	  glVertex3fv(this -> manifold__vertex__water[index01]); 
#endif

	}; 
      } glEnd(); 
    }; 
    glColor3f(1.0f,1.0f,1.0f); 
  } glEnable(GL_TEXTURE_2D); 

}; 

#else 
static void CSol__RenderEau(const CSol * this, int i1, int j1, int i2, int j2) {
  ARF(i1, this -> TailleX);
  ARF(i2, this -> TailleX);
  ARF(j1, this -> TailleY);
  ARF(j2, this -> TailleY);

#define COLOR_EAU(i, j) glColor4f(0.7f,0.7f,1.0f, 0.5f + 0.2f*cos(((i)+(j)+100*our_manifold -> temps)/2.0f));
  //#define COLOR_EAU(i, j) glColor4f(0.5f,0.0f,0.0f, 0.5f + 0.2f*cos(((i)+(j)+100*t)/2.0f));

  //fprintf(stderr, "RenderEau: I am called\n");
  //Render(i1, j1, i2, j2);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

  //glDepthFunc(GL_LEQUAL);
  glDisable(GL_TEXTURE_2D); { 
#define PREC_EAU 3 
    for (int vertex_i = i1; vertex_i <= i2; vertex_i += PREC_EAU) { 
      glBegin(GL_QUAD_STRIP); { 
        for (int j = j1; j <= j2; j += PREC_EAU) { 
	const int index00 = (vertex_j + 0) * this -> TailleX + (vertex_i + 0); 
	const int index01 = (vertex_j + 1) * this -> TailleX + (vertex_i + 0); 
	const int index11 = (vertex_j + 1) * this -> TailleX + (vertex_i + 1); 
	const int index10 = (vertex_j + 0) * this -> TailleX + (vertex_i + 1); 



          COLOR_EAU(i, j); 
          //	glTexCoord2f(0.0f + num_tex*0.5f,0.0f); 
          this -> tore0(this, i,j); // RL: Basically, it's a call to glVertex (& glNormal). 
	  
          COLOR_EAU(i+PREC_EAU, j); 
          //	glTexCoord2f(0.5f + num_tex*0.5f,0.0f); 
          this -> tore0(this, i+PREC_EAU,j); 
	  
#if 0
          //	glTexCoord2f(0.5f + num_tex*0.5f,1.0f);
          COLOR_EAU(i+PREC_EAU, j+PREC_EAU);
          this -> tore0(this, i+PREC_EAU,j+PREC_EAU);

          //	glTexCoord2f(0.0f + num_tex*0.5f,1.0f);
          COLOR_EAU(i, j+PREC_EAU);
          this -> tore0(this, i,j+PREC_EAU);
#endif

	}; 
      } glEnd(); 
    }; 
    glColor3f(1.0f,1.0f,1.0f);
  } glEnable(GL_TEXTURE_2D);
}; 
#endif 























int CSol__init(CSol * this, const int global_map_i, const int global_map_j, const int over_spanning_w, const int over_spanning_h, const float lattice_to_map_scale_factor__z, const riemann_t * our_manifold, const char * z_filename, const char * texture_filename) { 
  if (this -> TextureSol_nb <= 0) { 
    messerr("ERREUR: Aucune texture n'a été chargée." "\n"); 
    messerr("        Avant d'initialiser la carte, il faut lui indiquer toutes les textures qu'elle utilisera (pour cela, il faut utiliser la fonction 'AjouterTextureSol')." "\n"); 
    messerr("        Au moins une texture est nécessaire; cette texture sera utilisée en tant que texture de sol si aucune autre n'est fournie." "\n"); 
    return -1; 
  }; 

  //__our_manifold__ = our_manifold; 
  
  if (0 > CSol__ChargerZ(this, lattice_to_map_scale_factor__z, z_filename)) { return -2; }; 
  
  if (0 > CSol__ChargerTextureSolDisposition(this, texture_filename)) { return -3; }; 
  
  if (0 > CSol__compute__global_map__vertex_positions(this, global_map_i, global_map_j, over_spanning_w, over_spanning_h)) { return -4 ; }; 
  
  if (0 > CSol__Normal_compute(this)) { return -5; }; 
  
  if (0 > CSol__manifold__alloc_extra_temp_arrays(this, our_manifold)) { return -6; }; 
  
  this -> over_spanning_w = over_spanning_w; 
  this -> over_spanning_h = over_spanning_h; 
  
  return 0; 
}; 


void CSol__Life(const CSol * this) { 
  // RL: So far, nothing to be done. 
}; 


CSol * CSol__make_content(CSol * this); 
CSol * CSol__make(void); 
void   CSol__delete_content(CSol * this); 
void   CSol__delete(CSol * this); 

CSol * CSol__make_content(CSol * this) {
  BZERO_THIS(this); 
  
  ASSIGN_METHOD(CSol,this,make); 
  ASSIGN_METHOD(CSol,this,make_content); 
  ASSIGN_METHOD(CSol,this,delete); 
  ASSIGN_METHOD(CSol,this,delete_content); 
  ASSIGN_METHOD(CSol,this,init); 
  ASSIGN_METHOD(CSol,this,Life); 
  ASSIGN_METHOD(CSol,this,Render); 
  ASSIGN_METHOD(CSol,this,Render__pre_computations); 
  ASSIGN_METHOD(CSol,this,RenderEau); 
  ASSIGN_METHOD(CSol,this,yatilEau); 
  ASSIGN_METHOD(CSol,this,AjouterTextureSol); 
  ASSIGN_METHOD(CSol,this,GET_MAP_Z); 
#if 0 
  ASSIGN_METHOD(CSol,this,ChargerZ); 
  ASSIGN_METHOD(CSol,this,GETZ); 
  ASSIGN_METHOD(CSol,this,SETZ); 
  ASSIGN_METHOD(CSol,this,SETINDTEXTURE); 
  ASSIGN_METHOD(CSol,this,GETINDTEXTURE); 
  ASSIGN_METHOD(CSol,this,GetTailleX); 
  ASSIGN_METHOD(CSol,this,GetTailleY); 
  ASSIGN_METHOD(CSol,this,ChargerIndiceTextureBitmap); 
  ASSIGN_METHOD(CSol,this,Differentiel); 
#endif 

#if 0 
  this -> TextureSol_nb   =    0; 
  this -> Z               = NULL; 
  this -> indices_texture = NULL; 
#endif 
  
  return this; 
}; 

CSol * CSol__make(void) { 
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Constructeur/Constructor CSol()" "\n", __func__); 
  MALLOC_THIS(CSol,this); 
  return CSol__make_content(this); 
}; 

void CSol__delete_content(CSol * this) { 
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Destructeur/Destructor CSol()" "\n", __func__); 
  
  for (int i = 0; i < this -> TextureSol_nb; i++) { 
    CTexture_delete(this -> TextureSol[i]); 
  }; 
  
  free(this -> indices_texture__array); 
  
#if 1 
  for (int i = 0; i < this -> manifold__extra_w_arrays__nb; i++) { 
    free(this -> manifold__extra_w_arrays[i]); 
  }; 
  for (int i = 0; i < this -> manifold__extra_h_arrays__nb; i++) { 
    free(this -> manifold__extra_h_arrays[i]); 
  }; 
  for (int i = 0; i < this -> manifold__extra_w_h_arrays__nb; i++) { 
    free(this -> manifold__extra_w_h_arrays[i]); 
  }; 
#else 
  free(this -> manifold__outer_angle      ); 
  free(this -> manifold__outer_angle__cosf); 
  free(this -> manifold__outer_angle__sinf); 
  free(this -> manifold__inner_angle      ); 
  free(this -> manifold__inner_angle__cosf); 
  free(this -> manifold__inner_angle__sinf); 
#endif 

  free(this -> manifold__vertex           ); 
  free(this -> manifold__normal           ); 
  free(this -> manifold__vertex__water    ); 
  free(this -> manifold__normal__water    ); 
  
  free(this -> ground__global_map_x              ); 
  free(this -> ground__global_map_y              ); 
  free(this -> ground__normal              ); 
  free(this -> ground__map_Z                   ); 
  
  BZERO_THIS(this); 
}; 
 
void CSol__delete(CSol * this) { 
  CSol__delete_content(this); 
  free(this); 
}; 

static const CSol_module_t CSol_module__content = { 
  CSol__make, 
  CSol__make_content, 
  CSol__delete, 
  CSol__delete_content 
}; 
//const CSol_module_t * CSol_module = &CSol_module__content; 
//const CSol_module_t CSol_module[1] = { &CSol_module__content }; 
const CSol_module_t CSol_module[1] = { { 
  CSol__make, 
  CSol__make_content, 
  CSol__delete, 
  CSol__delete_content 
} 
}; 





























































#if 1 
static int CSol__compute__global_map__vertex_positions(CSol * this, const int global_map_i, const int global_map_j, const int over_spanning_w, const int over_spanning_h) { 
  this -> ground__global_map_x = malloc(sizeof(*this -> ground__global_map_x) * (this -> TailleX)); 
  this -> ground__global_map_y = malloc(sizeof(*this -> ground__global_map_y) * (this -> TailleY)); 
  
  for (int vertex_i = 0; vertex_i < this -> TailleX; vertex_i++) { 
    this -> ground__global_map_x[vertex_i] = global_map_i + ((float) over_spanning_w) * ((float) vertex_i) / ((float) (this -> TailleX - 1)); 
  }; 
  
  for (int vertex_j = 0; vertex_j < this -> TailleY; vertex_j++) { 
    this -> ground__global_map_y[vertex_j] = global_map_j + ((float) over_spanning_h) * ((float) vertex_j) / ((float) (this -> TailleY - 1)); 
  }; 
  
  return 0; 
}; 
#else 
static void CSol__compute__global_map__vertex_positions(CSol * this, const int global_map_i, const int global_map_j, const int over_spanning_w, const int over_spanning_h) { 
  assert(this -> ground__global_map_x               != NULL); 
  assert(this -> ground__global_map_y               != NULL); 

  for (int vertex_i = 0; vertex_i < this -> TailleX; vertex_i++) { 
    this -> ground__global_map_x[vertex_i] = map_i + ((float) vertex_i) / ((float) (this -> TailleX - 1)); 
  }; 
  
  for (int vertex_j = 0; vertex_j < this -> TailleY; vertex_j++) { 
    this -> ground__global_map_y[vertex_j] = map_j + ((float) vertex_j) / ((float) (this -> TailleY - 1)); 
  };   
}; 
#endif 


// RL: These are the normals in the local map, not in the manifold. 
//     One normal is computed for each z-vertex. 
// RL: The normal at one z-vertex depends of its z-level and of its neighbors. 
// RL: If the local-map is flat, then all normals are trivial (uz). 
static int CSol__Normal_compute(CSol * this) { 
  //if (this -> ground__normal != NULL) free(this -> ground__normal); 
  this -> ground__normal = malloc(sizeof(*this -> ground__normal) * ((this -> TailleX)*(this -> TailleY))); 
  
  // RL: Inside 
  {
    const int start_x = 1; 
    const int start_y = 1; 
    float (* normal)[3] = this -> ground__normal + (start_y * (this -> TailleX) + start_x); 
    TPoint3D u1 = TPoint3D_make_scalar( 0, -1,  0); 
    TPoint3D u2 = TPoint3D_make_scalar( 1,  0,  0); 
    TPoint3D u3 = TPoint3D_make_scalar( 0,  1,  0); 
    TPoint3D u4 = TPoint3D_make_scalar(-1,  0,  0); 
    float * z1          = this -> ground__map_Z + ((start_y + (int)u1.y) * this -> TailleX + (start_x + (int)u1.x)); 
    float * z2          = this -> ground__map_Z + ((start_y + (int)u2.y) * this -> TailleX + (start_x + (int)u2.x)); 
    float * z3          = this -> ground__map_Z + ((start_y + (int)u3.y) * this -> TailleX + (start_x + (int)u3.x)); 
    float * z4          = this -> ground__map_Z + ((start_y + (int)u4.y) * this -> TailleX + (start_x + (int)u4.x)); 
    for (int j = 1; j < this -> TailleY - 1; j++) { 
      for (int i = 1; i < this -> TailleX - 1; i++) { 
	const float z_average = (*z1 + *z2 + *z3 + *z4) / 4.0f; 
	u1.z = *z1 - z_average; 
	u2.z = *z2 - z_average; 
	u3.z = *z3 - z_average; 
	u4.z = *z4 - z_average; 
	TPoint3D normal1; TPoint3D_normal(u1, u2, &normal1); 
	TPoint3D normal2; TPoint3D_normal(u2, u3, &normal2); 
	TPoint3D normal3; TPoint3D_normal(u3, u4, &normal3); 
	TPoint3D normal4; TPoint3D_normal(u4, u1, &normal4); 
	(*normal)[0] = (normal1.x + normal2.x + normal3.x + normal4.x) / 4.0f; 
	(*normal)[1] = (normal1.y + normal2.y + normal3.y + normal4.y) / 4.0f; 
	(*normal)[2] = (normal1.z + normal2.z + normal3.z + normal4.z) / 4.0f; 
	z1++; 
	z2++; 
	z3++; 
	z4++; 
	normal++; 
      }; 
      z1 += 2; 
      z2 += 2; 
      z3 += 2; 
      z4 += 2; 
      normal += 2; 
    }; 
  }; 

  // RL: j = 0 
  { 
    const int start_x = 1; 
    const int start_y = 0; 
    float (* normal)[3] = this -> ground__normal + (start_y * (this -> TailleX) + start_x); 
    //TPoint3D u1 = TPoint3D_make_scalar( 0, -1,  0); 
    TPoint3D u2 = TPoint3D_make_scalar( 1,  0,  0); 
    TPoint3D u3 = TPoint3D_make_scalar( 0,  1,  0); 
    TPoint3D u4 = TPoint3D_make_scalar(-1,  0,  0); 
    //float * z1          = this -> ground__map_Z + ((start_y + (int)u1.y) * this -> TailleX + (start_x + (int)u1.x)); 
    float * z2          = this -> ground__map_Z + ((start_y + (int)u2.y) * this -> TailleX + (start_x + (int)u2.x)); 
    float * z3          = this -> ground__map_Z + ((start_y + (int)u3.y) * this -> TailleX + (start_x + (int)u3.x)); 
    float * z4          = this -> ground__map_Z + ((start_y + (int)u4.y) * this -> TailleX + (start_x + (int)u4.x)); 
    for (int i = 1; i < this -> TailleX - 1; i++) { 
      const float z_average = (*z2 + *z3 + *z4) / 3.0f; 
      //u1.z = *z1 - z_average; 
      u2.z = *z2 - z_average; 
      u3.z = *z3 - z_average; 
      u4.z = *z4 - z_average; 
      //TPoint3D normal1; TPoint3D_normal(u1, u2, &normal1); 
      TPoint3D normal2; TPoint3D_normal(u2, u3, &normal2); 
      TPoint3D normal3; TPoint3D_normal(u3, u4, &normal3); 
      //TPoint3D normal4; TPoint3D_normal(u4, u1, &normal4); 
      (*normal)[0] = (normal2.x + normal3.x) / 2.0f; 
      (*normal)[1] = (normal2.y + normal3.y) / 2.0f; 
      (*normal)[2] = (normal2.z + normal3.z) / 2.0f; 
      //z1++; 
      z2++; 
      z3++; 
      z4++; 
      normal++; 
    }; 
  }; 

  // RL: j = TailleY  
  {
    const int start_x = 1; 
    const int start_y = this -> TailleY - 1; 
    float (* normal)[3] = this -> ground__normal + (start_y * (this -> TailleX) + start_x); 
    TPoint3D u1 = TPoint3D_make_scalar( 0, -1,  0); 
    TPoint3D u2 = TPoint3D_make_scalar( 1,  0,  0); 
    //TPoint3D u3 = TPoint3D_make_scalar( 0,  1,  0); 
    TPoint3D u4 = TPoint3D_make_scalar(-1,  0,  0); 
    float * z1          = this -> ground__map_Z + ((start_y + (int)u1.y) * this -> TailleX + (start_x + (int)u1.x)); 
    float * z2          = this -> ground__map_Z + ((start_y + (int)u2.y) * this -> TailleX + (start_x + (int)u2.x)); 
    //float * z3          = this -> ground__map_Z + ((start_y + (int)u3.y) * this -> TailleX + (start_x + (int)u3.x)); 
    float * z4          = this -> ground__map_Z + ((start_y + (int)u4.y) * this -> TailleX + (start_x + (int)u4.x)); 
    for (int i = 1; i < this -> TailleX - 1; i++) { 
      const float z_average = (*z4 + *z1 + *z2) / 3.0f; 
      u1.z = *z1 - z_average; 
      u2.z = *z2 - z_average; 
      //u3.z = *z3 - z_average; 
      u4.z = *z4 - z_average; 
      TPoint3D normal1; TPoint3D_normal(u1, u2, &normal1); 
      //TPoint3D normal2; TPoint3D_normal(u2, u3, &normal2); 
      //TPoint3D normal3; TPoint3D_normal(u3, u4, &normal3); 
      TPoint3D normal4; TPoint3D_normal(u4, u1, &normal4); 
	(*normal)[0] = (normal4.x + normal1.x) / 2.0f; 
	(*normal)[1] = (normal4.y + normal1.y) / 2.0f; 
	(*normal)[2] = (normal4.z + normal1.z) / 2.0f; 
	z1++; 
	z2++; 
	//z3++; 
	z4++; 
	normal++; 
    }; 
  }; 

  // RL: i = 0 
  {
    const int start_x = 0; 
    const int start_y = 1; 
    float (* normal)[3] = this -> ground__normal + (start_y * (this -> TailleX) + start_x); 
    TPoint3D u1 = TPoint3D_make_scalar( 0, -1,  0); 
    TPoint3D u2 = TPoint3D_make_scalar( 1,  0,  0); 
    TPoint3D u3 = TPoint3D_make_scalar( 0,  1,  0); 
    //TPoint3D u4 = TPoint3D_make_scalar(-1,  0,  0); 
    float * z1          = this -> ground__map_Z + ((start_y + (int)u1.y) * this -> TailleX + (start_x + (int)u1.x)); 
    float * z2          = this -> ground__map_Z + ((start_y + (int)u2.y) * this -> TailleX + (start_x + (int)u2.x)); 
    float * z3          = this -> ground__map_Z + ((start_y + (int)u3.y) * this -> TailleX + (start_x + (int)u3.x)); 
    //float * z4          = this -> ground__map_Z + ((start_y + (int)u4.y) * this -> TailleX + (start_x + (int)u4.x)); 
    for (int j = 1; j < this -> TailleY - 1; j++) { 
      const float z_average = (*z1 + *z2 + *z3) / 3.0f; 
      u1.z = *z1 - z_average; 
      u2.z = *z2 - z_average; 
      u3.z = *z3 - z_average; 
      //u4.z = *z4 - z_average; 
      TPoint3D normal1; TPoint3D_normal(u1, u2, &normal1); 
      TPoint3D normal2; TPoint3D_normal(u2, u3, &normal2); 
      //TPoint3D normal3; TPoint3D_normal(u3, u4, &normal3); 
      //TPoint3D normal4; TPoint3D_normal(u4, u1, &normal4); 
      (*normal)[0] = (normal1.x + normal2.x) / 2.0f; 
      (*normal)[1] = (normal1.y + normal2.y) / 2.0f; 
      (*normal)[2] = (normal1.z + normal2.z) / 2.0f; 
      z1 += (this -> TailleX); 
      z2 += (this -> TailleX); 
      z3 += (this -> TailleX); 
      //z4 += (this -> TailleX); 
      normal += (this -> TailleX); 
    }; 
  }; 

  // RL: i = TailleX 
  {
    const int start_x = this -> TailleX - 1; 
    const int start_y = 1; 
    float (* normal)[3] = this -> ground__normal + (start_y * (this -> TailleX) + start_x); 
    TPoint3D u1 = TPoint3D_make_scalar( 0, -1,  0); 
    //TPoint3D u2 = TPoint3D_make_scalar( 1,  0,  0); 
    TPoint3D u3 = TPoint3D_make_scalar( 0,  1,  0); 
    TPoint3D u4 = TPoint3D_make_scalar(-1,  0,  0); 
    float * z1          = this -> ground__map_Z + ((start_y + (int)u1.y) * this -> TailleX + (start_x + (int)u1.x)); 
    //float * z2          = this -> ground__map_Z + ((start_y + (int)u2.y) * this -> TailleX + (start_x + (int)u2.x)); 
    float * z3          = this -> ground__map_Z + ((start_y + (int)u3.y) * this -> TailleX + (start_x + (int)u3.x)); 
    float * z4          = this -> ground__map_Z + ((start_y + (int)u4.y) * this -> TailleX + (start_x + (int)u4.x)); 
    for (int j = 1; j < this -> TailleY - 1; j++) { 
      const float z_average = (*z1 + *z3 + *z4) / 3.0f; 
      u1.z = *z1 - z_average; 
      //u2.z = *z2 - z_average; 
      u3.z = *z3 - z_average; 
      u4.z = *z4 - z_average; 
      //TPoint3D normal1; TPoint3D_normal(u1, u2, &normal1); 
      //TPoint3D normal2; TPoint3D_normal(u2, u3, &normal2); 
      TPoint3D normal3; TPoint3D_normal(u3, u4, &normal3); 
      TPoint3D normal4; TPoint3D_normal(u4, u1, &normal4); 
      (*normal)[0] = (normal3.x + normal4.x) / 2.0f; 
      (*normal)[1] = (normal3.y + normal4.y) / 2.0f; 
      (*normal)[2] = (normal3.z + normal4.z) / 2.0f; 
      z1 += (this -> TailleX); 
      //z2 += (this -> TailleX); 
      z3 += (this -> TailleX); 
      z4 += (this -> TailleX); 
      normal += (this -> TailleX); 
    }; 
  }; 

  // RL: i = 0, j = 0  
  {
    const int start_x = 0; 
    const int start_y = 0; 
    float (* normal)[3] = this -> ground__normal + (start_y * (this -> TailleX) + start_x); 
    //TPoint3D u1 = TPoint3D_make_scalar( 0, -1,  0); 
    TPoint3D u2 = TPoint3D_make_scalar( 1,  0,  0); 
    TPoint3D u3 = TPoint3D_make_scalar( 0,  1,  0); 
    //TPoint3D u4 = TPoint3D_make_scalar(-1,  0,  0); 
    //float * z1          = this -> ground__map_Z + ((start_y + (int)u1.y) * this -> TailleX + (start_x + (int)u1.x)); 
    float * z2          = this -> ground__map_Z + ((start_y + (int)u2.y) * this -> TailleX + (start_x + (int)u2.x)); 
    float * z3          = this -> ground__map_Z + ((start_y + (int)u3.y) * this -> TailleX + (start_x + (int)u3.x)); 
    //float * z4          = this -> ground__map_Z + ((start_y + (int)u4.y) * this -> TailleX + (start_x + (int)u4.x)); 
    { 
      const float z_average = (*z2 + *z3) / 2.0f; 
      //u1.z = *z1 - z_average; 
      u2.z = *z2 - z_average; 
      u3.z = *z3 - z_average; 
      //u4.z = *z4 - z_average; 
      //TPoint3D normal1; TPoint3D_normal(u1, u3, &normal1); 
      TPoint3D normal2; TPoint3D_normal(u2, u3, &normal2); 
      //TPoint3D normal3; TPoint3D_normal(u3, u4, &normal3); 
      //TPoint3D normal4; TPoint3D_normal(u4, u1, &normal4); 
      (*normal)[0] = normal2.x; 
      (*normal)[1] = normal2.y; 
      (*normal)[2] = normal2.z; 
    }; 
  }; 

  // RL: i = TailleX - 1, j = 0  
  {
    const int start_x = this -> TailleX - 1; 
    const int start_y = 0; 
    float (* normal)[3] = this -> ground__normal + (start_y * (this -> TailleX) + start_x); 
    //TPoint3D u1 = TPoint3D_make_scalar( 0, -1,  0); 
    //TPoint3D u2 = TPoint3D_make_scalar( 1,  0,  0); 
    TPoint3D u3 = TPoint3D_make_scalar( 0,  1,  0); 
    TPoint3D u4 = TPoint3D_make_scalar(-1,  0,  0); 
    //float * z1          = this -> ground__map_Z + ((start_y + (int)u1.y) * this -> TailleX + (start_x + (int)u1.x)); 
    //float * z2          = this -> ground__map_Z + ((start_y + (int)u2.y) * this -> TailleX + (start_x + (int)u2.x)); 
    float * z3          = this -> ground__map_Z + ((start_y + (int)u3.y) * this -> TailleX + (start_x + (int)u3.x)); 
    float * z4          = this -> ground__map_Z + ((start_y + (int)u4.y) * this -> TailleX + (start_x + (int)u4.x)); 
    { 
      const float z_average = (*z3 + *z4) / 2.0f; 
      //u1.z = *z1 - z_average; 
      //u2.z = *z2 - z_average; 
      u3.z = *z3 - z_average; 
      u4.z = *z4 - z_average; 
      //TPoint3D normal1; TPoint3D_normal(u1, u3, &normal1); 
      //TPoint3D normal2; TPoint3D_normal(u2, u3, &normal2); 
      TPoint3D normal3; TPoint3D_normal(u3, u4, &normal3); 
      //TPoint3D normal4; TPoint3D_normal(u4, u1, &normal4); 
      (*normal)[0] = normal3.x; 
      (*normal)[1] = normal3.y; 
      (*normal)[2] = normal3.z; 
    }; 
  }; 

  // RL: i = TailleX - 1, j = TailleY - 1  
  {
    const int start_x = this -> TailleX - 1; 
    const int start_y = this -> TailleY - 1; 
    float (* normal)[3] = this -> ground__normal + (start_y * (this -> TailleX) + start_x); 
    TPoint3D u1 = TPoint3D_make_scalar( 0, -1,  0); 
    //TPoint3D u2 = TPoint3D_make_scalar( 1,  0,  0); 
    //TPoint3D u3 = TPoint3D_make_scalar( 0,  1,  0); 
    TPoint3D u4 = TPoint3D_make_scalar(-1,  0,  0); 
    float * z1          = this -> ground__map_Z + ((start_y + (int)u1.y) * this -> TailleX + (start_x + (int)u1.x)); 
    //float * z2          = this -> ground__map_Z + ((start_y + (int)u2.y) * this -> TailleX + (start_x + (int)u2.x)); 
    //float * z3          = this -> ground__map_Z + ((start_y + (int)u3.y) * this -> TailleX + (start_x + (int)u3.x)); 
    float * z4          = this -> ground__map_Z + ((start_y + (int)u4.y) * this -> TailleX + (start_x + (int)u4.x)); 
    { 
      const float z_average = (*z4 + *z1) / 2.0f; 
      u1.z = *z1 - z_average; 
      //u2.z = *z2 - z_average; 
      //u3.z = *z3 - z_average; 
      u4.z = *z4 - z_average; 
      //TPoint3D normal1; TPoint3D_normal(u1, u3, &normal1); 
      //TPoint3D normal2; TPoint3D_normal(u2, u3, &normal2); 
      //TPoint3D normal3; TPoint3D_normal(u3, u4, &normal3); 
      TPoint3D normal4; TPoint3D_normal(u4, u1, &normal4); 
      (*normal)[0] = normal4.x; 
      (*normal)[1] = normal4.y; 
      (*normal)[2] = normal4.z; 
    }; 
  }; 

  // RL: i = 0, j = TailleY - 1  
  {
    const int start_x = 0; 
    const int start_y = this -> TailleY - 1; 
    float (* normal)[3] = this -> ground__normal + (start_y * (this -> TailleX) + start_x); 
    TPoint3D u1 = TPoint3D_make_scalar( 0, -1,  0); 
    TPoint3D u2 = TPoint3D_make_scalar( 1,  0,  0); 
    //TPoint3D u3 = TPoint3D_make_scalar( 0,  1,  0); 
    //TPoint3D u4 = TPoint3D_make_scalar(-1,  0,  0); 
    float * z1          = this -> ground__map_Z + ((start_y + (int)u1.y) * this -> TailleX + (start_x + (int)u1.x)); 
    float * z2          = this -> ground__map_Z + ((start_y + (int)u2.y) * this -> TailleX + (start_x + (int)u2.x)); 
    //float * z3          = this -> ground__map_Z + ((start_y + (int)u3.y) * this -> TailleX + (start_x + (int)u3.x)); 
    //float * z4          = this -> ground__map_Z + ((start_y + (int)u4.y) * this -> TailleX + (start_x + (int)u4.x)); 
    { 
      const float z_average = (*z1 + *z2) / 2.0f; 
      u1.z = *z1 - z_average; 
      u2.z = *z2 - z_average; 
      //u3.z = *z3 - z_average; 
      //u4.z = *z4 - z_average; 
      TPoint3D normal1; TPoint3D_normal(u1, u2, &normal1); 
      //TPoint3D normal2; TPoint3D_normal(u2, u3, &normal2); 
      //TPoint3D normal3; TPoint3D_normal(u3, u4, &normal3); 
      //TPoint3D normal4; TPoint3D_normal(u4, u1, &normal4); 
      (*normal)[0] = normal1.x; 
      (*normal)[1] = normal1.y; 
      (*normal)[2] = normal1.z; 
    }; 
  }; 

  return 0; 
}; 


