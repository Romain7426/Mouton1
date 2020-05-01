#ifndef SOL_H 
#define SOL_H 

#if 0 
#define nb_cases_afficheesX       25 
#define nb_cases_afficheesYfond   20 
#define nb_cases_afficheesYdevant 10 
#else 
enum { nb_cases_afficheesX       = 25 }; 
enum { nb_cases_afficheesYfond   = 20 }; 
enum { nb_cases_afficheesYdevant = 10 }; 
#endif 

struct TPointEcran { 
  TPoint3D pt; 
  TPoint3D normal; 
}; 
TYPEDEF_TYPENAME_WITHOUT_STRUCT(TPointEcran); 





#ifndef STRUCT_CSOL 
#define STRUCT_CSOL 
struct CSol; 
//typedef struct CSol CSol; 
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CSol);
#endif 

struct CSol_module_t; 
typedef struct CSol_module_t CSol_module_t; 
struct CSol_module_t {
  CSol * (* make          )(             const bool EnVaisseau); 
  CSol * (* make_content  )(CSol * this, const bool EnVaisseau); 
  void   (* delete        )(CSol * this); 
  void   (* delete_content)(CSol * this); 
}; 
//extern const CSol_module_t * CSol_module; 
extern const CSol_module_t CSol_module[1]; 


// RL: 'CSol' is the ground of the map. 
//      Basically, it contains the z-level. (It contains also the ground textures, the water level, and other related things). 
// RL: The ground is discretized in vertices: 
//      * width : 'TailleX' vertices 
//      * height: 'TailleY' vertices 
// RL: 'TailleX' and 'TailleY' are determined when the z-levels are loaded. 
enum { NB_MAX_TEXTURESOL =  10 }; 
struct CSol { 

  // FS: taille en case de la carte, c'est ChargerZ qui s'occupe de remplir ça 
  // RL: This is a number of vertices, not a number of cells. 
  uint8_t TailleX; 
  uint8_t TailleY; 

  // RL: Water level. 
  float ZEau; // = 45.8f; 

  // ___ Z Level ___ 
  // RL: Array of size TailleX * TailleY. 
  //     It gives the z-level for the cell (i,j). 
  //     Data loaded from the bitmap file. 
  float * Z; // RL: Array of size TailleX * TailleY 
  
  // RL: This is the normal vector at vertex (i,j). 
  // RL: This is the normal vector in the map-local coordinates, not the manifold normal. 
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
  float (* normal)[3]; // RL: Array of size TailleX * TailleY // RL: Apriori, their norm2 is not 1 (OpenGL will normalize them anyway). 
  
  // RL: These are local temporary variables, and not actual properties. 
  float (* global_map__x); // RL: Array[TailleX] // RL: x-coordinate of each vertex in the global map. 
  float (* global_map__y); // RL: Array[TailleY] // RL: x-coordinate of each vertex in the global map. 
  float (* manifold__outer_angle); // RL: Array[TailleX] // RL: φ of each x-coordinate. 
  float (* manifold__outer_angle__cosf); // RL: Array[TailleX] // RL: φ of each x-coordinate. 
  float (* manifold__outer_angle__sinf); // RL: Array[TailleX] // RL: φ of each x-coordinate. 
  float (* manifold__inner_angle); // RL: Array[TailleY] // RL: θ of each y-coordinate. 
  float (* manifold__inner_angle__cosf); // RL: Array[TailleY] // RL: θ of each y-coordinate. 
  float (* manifold__inner_angle__sinf); // RL: Array[TailleY] // RL: θ of each y-coordinate. 
  float (* manifold__vertex)[3]; // RL: Array[TailleX * TailleY] // RL: Coordinates of each vertex in the manifold. 
  float (* manifold__normal)[3]; // RL: Array[TailleX * TailleY] // RL: Coordinates of each normal in the manifold. 
  float (* manifold__vertex__water)[3]; // RL: Array[TailleX * TailleY] // RL: Coordinates of each vertex in the manifold. 
  float (* manifold__normal__water)[3]; // RL: Array[TailleX * TailleY] // RL: Coordinates of each normal in the manifold. 
  
  // ___ Ground Textures ___ 
  // RL: Texture files are enumerated in the '_.carte' file. 
  // RL: Textures layout is described in a bitmap picture file. 
  CTexture * TextureSol[NB_MAX_TEXTURESOL]; // RL: From the '_.carte' file. 
  int8_t     TextureSol_used_huh[NB_MAX_TEXTURESOL]; 
  int8_t      nb_texture; // RL: From the '_.carte' file. 
  int      indices_dans_bitmap[NB_MAX_TEXTURESOL]; // RL: From the '_.carte' file. That's the mapping between the color in the picture file and the chosen texture. 
  int8_t * indices_texture; // RL: Array of size TailleX * TailleY. 
                            //     It gives the texture at the vertex (i,j). 
                            //     What does that mean? Good question. 
                            //     Here the idea is that each texture is fully displayed every single time, 
                            //     and then the associated value at each vertex is an alpha channel value. 
                            //     Yes, it seems weird, but it renders nicely and smoothly. 
                            // RL: Data loaded from the bitmap file. 
                            // RL: The reverse looked-up is already done - thus this array holds an index of the 'TextureSol' array. 
  
  
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
  
  CSol * (* make          )(             const bool EnVaisseau); 
  CSol * (* make_content  )(CSol * this, const bool EnVaisseau); 
  void   (* delete        )(CSol * this); 
  void   (* delete_content)(CSol * this); 

  int (* GetTailleX)(const CSol * this);
  int (* GetTailleY)(const CSol * this);
  
  void  (* ChargerZ)(      CSol * this, const char * filename); 
  float (* GETZ    )(const CSol * this, const float map_x, const float map_y); 
  void  (* SETZ    )(      CSol * this,   int x,   int y, float z); // FS: en privée, un élément de l'extérieur n'a pas le droit de modifier le terrain; utiliser "ChargerZ" pour cela 
  
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
  void (* AjouterTextureSol         )(      CSol * this, const char * fichier_texture, const int indice_dans_bitmap); 
  void (* ChargerIndiceTextureBitmap)(      CSol * this, const char * fichier_bitmap); 
  void (* SETINDTEXTURE             )(      CSol * this, int x, int y, int ind); 
  int  (* GETINDTEXTURE             )(const CSol * this, int x, int y); 
  
  //void (* Render   )(const CSol * this, int i1, int j1, int i2, int j2); /*dessine la partie du tore entre )(CSol * this, i1, j1) et )(CSol * this, i2, j2)*/
  //void (* RenderEau)(const CSol * this, int i1, int j1, int i2, int j2);
  void (* Render                  )(const CSol * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int target_map_i, const int target_map_j, const float target_map_x, const float target_map_y); 
  void (* Render__pre_computations)(      CSol * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int target_map_i, const int target_map_j, const float target_map_x, const float target_map_y); 
  void (* RenderEau               )(const CSol * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int target_map_i, const int target_map_j, const float target_map_x, const float target_map_y); 
  
  bool (* yatilEau )(const CSol * this, const float i, const float j, const float z);
  
  //void (* PositionModulo)(const CSol * this, float& i, float& j); 
  //void (* PositionModulo)(const CSol * this, float * i_ptr, float * j_ptr); 
  TPoint2D (* Differentiel)(const CSol * this, TPoint3D pos); 
  
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
#if 0 
extern CSol * CSol__make(const bool EnVaisseau); 
extern CSol * CSol__make_content(CSol * this, const bool EnVaisseau); 
extern void CSol__delete(CSol * this); 
extern void CSol__delete_content(CSol * this); 
#endif 











#endif /* SOL_H */
