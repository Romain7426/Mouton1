#include "global.h"
#include "sol.h"


#include "riemann.ci" 

#if 1 
static struct riemann_t our_manifold[1]; 
#else 
static struct riemann_t   our_manifold__struct; 
static struct riemann_t * our_manifold = & our_manifold__struct; 
#endif 



static void CSol__Normal_compute(CSol * this); 
static void CSol__compute__global_map__vertex_positions(CSol * this, const int map_i, const int map_j); 


#define theta_vue_blit -1.3f
#define HauteurCamera 120.0f

static int CSol__GetTailleX(const CSol * this) {
  return this -> TailleX; 
}; 

static int CSol__GetTailleY(const CSol * this) {
  return this -> TailleY;
}; 

#define TEST_X_Y(x, y) ((0<=x) && (x < this -> TailleX) && (0<=y) && (y < this -> TailleY))

static void CSol__SETZ(CSol * this, const int x, const int y, const float z) {
  if (!TEST_X_Y(x, y)) {
    messerr("ERREUR: Débordement de tableau dans Z avec (%i, %i)\n", x, y);
    return;
  }; 
  this -> Z[((y)*this -> TailleX) + (x)] = z;
}; 

static float CSol__GETZ0(const CSol * this, const int x, const int y) { 
  if (TEST_X_Y(x, y)) { 
    return this -> Z[(y)*this -> TailleX+(x)]; 
  };   
  messerr("ERREUR : Débordement de tableau des Z avec (%i, %i)\n", x, y); 
  return -1; 
}; 

static void CSol__SETINDTEXTURE(CSol * this, const int x, const int y, const int ind) {
  if (!TEST_X_Y(x, y)) {
    messerr("ERREUR: Débordement de tableau d'indice de textures en écriture avec (%i, %i)\n", x, y);
    return; 
  };
  this -> indices_texture[(y)*this -> TailleX+(x)] = ind;
}; 

static int CSol__GETINDTEXTURE(const CSol * this, const int x, const int y) {
  if (TEST_X_Y(x, y)) { 
    return this -> indices_texture[(y)*this -> TailleX + (x)]; 
  }; 
  assert(false); 
  messerr("ERREUR : Débordement de tableau d'indice de textures en lecture avec (%i, %i)\n", x, y); 
  return -1; 
}; 

static float CSol__GETZ(const CSol * this, const float map_x, const float map_y) { 
  // FS: /*on fait une interpolation pour connaître l'altitude (en fait, elle n'est connue que sur un maillage)*/ 
  
  const float sol_x = ((float) this -> TailleX) * (map_x - floorf(map_x)); 
  const float sol_y = ((float) this -> TailleX) * (map_y - floorf(map_y)); 
  
  const int vertex_i = (int) floor(sol_x); 
  const int vertex_j = (int) floor(sol_y); 
  
  const float lx = sol_x - vertex_i; 
  const float ly = sol_y - vertex_j; 
  
#define ZIND(x,y) ((y)*this -> TailleX+(x)) 
#define ZZ(x,y) (((((x) >= 0) && ((y) >= 0) && ((x) < this -> TailleX) && ((y) < this -> TailleY))) ? this -> Z[(ZIND((x),(y)))] : 0) 
  const float z00 = ZZ(vertex_i  ,vertex_j  ); 
  const float z10 = ZZ(vertex_i+1,vertex_j  ); 
  const float z01 = ZZ(vertex_i  ,vertex_j+1); 
  const float z11 = ZZ(vertex_i+1,vertex_j+1); 
  
  const float z   = (z00 * (1 - lx) + z10 * lx) * (1 - ly) + 
                    (z01 * (1 - lx) + z11 * lx) *      ly; 
  
  return z; 
}; 








static void CSol__compute_manifold_vertices_and_normals(CSol * this, const int map_i, const int map_j, const riemann_t * our_manifold) { 
#if 1 
  our_manifold -> compute_manifold_vertices_and_normals(our_manifold, this -> TailleX, this -> TailleY, 
							this -> global_map__x, this -> global_map__y, this -> Z, this -> ZEau, 
							this -> normal, 
							this -> manifold__extra_w_arrays__nb  , this -> manifold__extra_w_arrays, 
							this -> manifold__extra_h_arrays__nb  , this -> manifold__extra_h_arrays, 
							this -> manifold__extra_w_h_arrays__nb, this -> manifold__extra_w_h_arrays, 
							this -> manifold__vertex       , this -> manifold__normal, 
							this -> manifold__vertex__water, this -> manifold__normal__water); 

#else 
  assert(this -> manifold__outer_angle       != NULL); 
  assert(this -> manifold__outer_angle__cosf != NULL); 
  assert(this -> manifold__outer_angle__sinf != NULL); 
  assert(this -> manifold__inner_angle       != NULL); 
  assert(this -> manifold__inner_angle__cosf != NULL); 
  assert(this -> manifold__inner_angle__sinf != NULL); 
  assert(this -> manifold__vertex            != NULL); 
  assert(this -> manifold__normal            != NULL); 
  assert(this -> manifold__vertex__water     != NULL); 
  assert(this -> manifold__normal__water     != NULL); 
  
  for (int vertex_i = 0; vertex_i < this -> TailleX; vertex_i++) { 
    const float outer_angle = OUTER_ANGLE__GET(our_manifold,this -> global_map__x[vertex_i]); 
    this -> manifold__outer_angle      [vertex_i] =      outer_angle ; 
    this -> manifold__outer_angle__cosf[vertex_i] = cosf(outer_angle); 
    this -> manifold__outer_angle__sinf[vertex_i] = sinf(outer_angle); 
  }; 
  
  for (int vertex_j = 0; vertex_j < this -> TailleY; vertex_j++) { 
    const float inner_angle = INNER_ANGLE__GET(our_manifold,this -> global_map__y[vertex_j]); 
    this -> manifold__inner_angle      [vertex_j] =      inner_angle ; 
    this -> manifold__inner_angle__cosf[vertex_j] = cosf(inner_angle); 
    this -> manifold__inner_angle__sinf[vertex_j] = sinf(inner_angle); 
  }; 
  
  
  for (int vertex_j = 0; vertex_j < this -> TailleY; vertex_j++) { 
    const float cj = this -> manifold__inner_angle__cosf[vertex_j]; 
    const float sj = this -> manifold__inner_angle__sinf[vertex_j]; 
    for (int vertex_i = 0; vertex_i < this -> TailleX; vertex_i++) { 
      const int index = vertex_j * this -> TailleX + vertex_i; 
      const float ci = this -> manifold__outer_angle__cosf[vertex_i]; 
      const float si = this -> manifold__outer_angle__sinf[vertex_i]; 
      {
	const float map_z = this -> Z[index]; 
	this -> manifold__vertex[index][0] = TORUS_MANIFOLD_POINT_GET__X(our_manifold,ci,si,cj,sj,map_z); 
	this -> manifold__vertex[index][1] = TORUS_MANIFOLD_POINT_GET__Y(our_manifold,ci,si,cj,sj,map_z); 
	this -> manifold__vertex[index][2] = TORUS_MANIFOLD_POINT_GET__Z(our_manifold,ci,si,cj,sj,map_z); 
	this -> manifold__normal[index][0] = TORUS_MANIFOLD_TANGENT__MAP_VECTOR__GET__X(ci,si,cj,sj,this -> normal[index][0],this -> normal[index][1],this -> normal[index][2]); 
	this -> manifold__normal[index][1] = TORUS_MANIFOLD_TANGENT__MAP_VECTOR__GET__Y(ci,si,cj,sj,this -> normal[index][0],this -> normal[index][1],this -> normal[index][2]); 
	this -> manifold__normal[index][2] = TORUS_MANIFOLD_TANGENT__MAP_VECTOR__GET__Z(ci,si,cj,sj,this -> normal[index][0],this -> normal[index][1],this -> normal[index][2]); 
      }; 
      {
	const float map_water_z = this -> ZEau; 
	this -> manifold__vertex__water[index][0] = TORUS_MANIFOLD_POINT_GET__X(our_manifold,ci,si,cj,sj,map_water_z); 
	this -> manifold__vertex__water[index][1] = TORUS_MANIFOLD_POINT_GET__Y(our_manifold,ci,si,cj,sj,map_water_z); 
	this -> manifold__vertex__water[index][2] = TORUS_MANIFOLD_POINT_GET__Z(our_manifold,ci,si,cj,sj,map_water_z); 
	this -> manifold__normal__water[index][0] = TORUS_MANIFOLD_TANGENT__MAP_VECTOR__GET__X(ci,si,cj,sj,1,0,0); 
	this -> manifold__normal__water[index][1] = TORUS_MANIFOLD_TANGENT__MAP_VECTOR__GET__Y(ci,si,cj,sj,0,1,0); 
	this -> manifold__normal__water[index][2] = TORUS_MANIFOLD_TANGENT__MAP_VECTOR__GET__Z(ci,si,cj,sj,0,0,1); 
      }; 
    }; 
  }; 
  
#endif 
}; 




static void CSol__AjouterTextureSol(CSol * this, const char * s, const int indice_dans_bitmap) { 
  if (this -> nb_texture >= NB_MAX_TEXTURESOL) { 
    messerr("ERREUR: Il y a déjà trop de textures de sol dans la carte." "\n"); 
    return; 
  }; 
  CTexture * t = CTexture_make(s); 
  if (t == NULL) { 
    messerr("ERREUR: Impossible de charger la texture: '%s'." "\n", s); 
    return; 
  }; 
  this -> TextureSol[this -> nb_texture] = t; 
  this -> indices_dans_bitmap[this -> nb_texture] = indice_dans_bitmap; 
  this -> nb_texture++; 
}; 

static int CSol__Texture_Indice_Lookup(const CSol * this, const int indice_dans_le_fichier_bitmap) { 
  for (int i = 0; i < this -> nb_texture; i ++) { 
    if (indice_dans_le_fichier_bitmap == this -> indices_dans_bitmap[i]) { 
      return i; 
    }; 
  }; 
  return -1; 
}; 

static void CSol__ChargerIndiceTextureBitmap(CSol * this, const char * fichier_bitmap) { 
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Chargement des zones de textures - fichier:  '%s' " "\n", __func__, fichier_bitmap); 
  
  char reelfile[strlen(NIVEAUXDIR) + strlen(fichier_bitmap) + 1];
  strcat(strcpy(reelfile, NIVEAUXDIR), fichier_bitmap);
  fichier_bitmap = reelfile;
  
  SDL_Surface * img = NULL;
  img = IMG_Load(fichier_bitmap);
  
  if (img == NULL) { 
    messerr("ERREUR: Impossible de charger le fichier image '%s'...\n", fichier_bitmap); 
    return; 
  }; 
  
  if ((img -> w != this -> TailleX) || (img -> h != this -> TailleY)) { 
    messerr("ERREUR: La taille de l'image %s est différente de celle spécifiée dans le fichier des altitudes." "\n", fichier_bitmap); 
    messerr("\t\t" "TEX: " "w x h = %d pixels x %d pixels " "\n", img -> w, img -> h); 
    messerr("\t\t" "Z  : " "w x h = %d pixels x %d pixels " "\n", this -> TailleX, this -> TailleY); 
    return; 
  }; 
  
  
  //const int bpp = img->format->BytesPerPixel;
  
  if (img->format->BytesPerPixel != 3) { 
    messerr("WARNING: L'image '%s' doit être dans un format 24 bits." "\n.", fichier_bitmap); 
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
  printf("pointeur image: %p\n", p); 
  
  printf("Allocation en mémoire de la table qui à un point de la carte associe l'id de la texture de ce point." "\n"); 
  this -> indices_texture = malloc(sizeof(*this -> indices_texture) * ((this -> TailleX)*(this -> TailleY))); 

#define stdtexind stdout 
#define PRINTF_texind_LINE_BEGIN fprintf(stdtexind, "%2d - [", j); 
#define PRINTF_texind_LINE_END fprintf(stdtexind, "]\n"); 
  //#define PRINTF_texind fprintf(stdtexind, "%d, ", ind_color); 
#define PRINTF_texind fprintf(stdtexind, "%d, ", k); 

  for (int j = 0; j < img -> h; j++) { 
    PRINTF_texind_LINE_BEGIN; 
    for (int i = 0; i < img -> w; i++) { 
      //int ind_color = p[j * img->pitch + i * bpp] + 256*p[j * img->pitch + i * bpp + 1] + 256*256*p[j * img->pitch + i * bpp + 2]; 
      const int ind_color = 256*256*p[j * img->pitch + i * bpp] + 256*p[j * img->pitch + i * bpp + 1] + p[j * img->pitch + i * bpp + 2]; 
      
      const int k = CSol__Texture_Indice_Lookup(this, ind_color); 
      if (k < 0) { 
	messerr("ERREUR: la couleur %i au pixel (%i, %i) n'est associée à aucune texture." "\n", ind_color, i, j); 
      }; 
      
      this -> SETINDTEXTURE(this, i, img->h-1-j, k); 

      this -> TextureSol_used_huh[k] = true; 
      
      PRINTF_texind; 
    }; 
    PRINTF_texind_LINE_END; 
  }; 
  
  SDL_FreeSurface(img); 
  printf("Chargement de la carte de disposition des textures terminé." "\n"); 
}; 






#define ARF(__i1__,__TailleX__) if (__i1__ < 0) { __i1__ = 0; } else if (__i1__ >= __TailleX__ - 1) { __i1__ = __TailleX__ - 2; }; 








void CSol__Render__pre_computations(CSol * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int target_map_i, const int target_map_j, const float target_map_x, const float target_map_y) { 
  CSol__compute_manifold_vertices_and_normals(this, target_map_i, target_map_j, our_manifold); 
}; 



//static void CSol__Render(const CSol * this, int i1, int j1, int i2, int j2) { 
void CSol__Render(const CSol * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int target_map_i, const int target_map_j, const float target_map_x, const float target_map_y) { 
  //messerr("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: "  "CSol = %p - i1, i2, j1, j2 = %d, %d, %d, %d" "\n", __func__, this, i1, i2, j1, j2); 
  //messerr("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: "  "CSol = %p - our_manifold = %p - nb_cells_displayed_x, nb_cells_displayed_y, target_map_i, target_map_j, target_map_x, target_map_y = %d, %d, %d, %d, %f, %f" "\n", __func__, this, our_manifold, nb_cells_displayed_x, nb_cells_displayed_y, target_map_i, target_map_j, target_map_x, target_map_y); 
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
  
#if 1 

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


#else   
#endif 

}; 




// RL: That's a riemann function. 
static void CSol__SetTemps(CSol * this, const float in_temps) {
  our_manifold -> temps = in_temps;
};

// RL: That's a riemann function. 
static float CSol__GetTemps(const CSol * this) {
  return our_manifold -> temps;    
};

static bool CSol__yatilEau(const CSol * this, const float map_x, const float map_y, const float map_z) {
  return (map_z < this -> ZEau); 
}; 

	
#if 1 
static void CSol__RenderEau(const CSol * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int target_map_i, const int target_map_j, const float target_map_x, const float target_map_y) { 
  //messerr("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: "  "CSol = %p - our_manifold = %p - nb_cells_displayed_x, nb_cells_displayed_y, target_map_i, target_map_j, target_map_x, target_map_y = %d, %d, %d, %d, %f, %f" "\n", __func__, this, our_manifold, nb_cells_displayed_x, nb_cells_displayed_y, target_map_i, target_map_j, target_map_x, target_map_y); 
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




static int CSol__ChargerZ(CSol * this, const int map_i, const int map_j, const riemann_t * our_manifold, const char * filename) { 
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Chargement des niveaux de la carte: '%s'" "\n", __func__, filename == NULL ? "<null>" : filename); 
  
  char reelfile[ARRAY_SIZE(NIVEAUXDIR)-1 + strlen(filename) + 1]; 
  strcat(strcpy(reelfile, NIVEAUXDIR), filename); 
  filename = reelfile; 
  
  SDL_Surface * img; 
  img = IMG_Load(filename); 
  
  if (img == NULL) { 
    messerr("ERREUR: Impossible de lire le fichier image '%s' (ce fichier contient les Z du terrain) - SDL_Image: %s" "\n", filename, IMG_GetError()); 
    return false; 
  }; 
  
  const int bpp = img -> format -> BytesPerPixel; 
  
  if (bpp != 1) { 
    messerr("WARNING: " "L'image '%s' doit être dans un format niveau de gris. Elle représente les Z de la carte. Or elle est dans un format: %d BytesPerPixel. En conséquence de quoi, nous utiliserons la couleur rouge en tant que proxy.\n", filename, bpp); 
    messerr("\t\t" "w x h = %d pixels x %d pixels " "\n", img -> w, img -> h); 
    //messerr("\t\t" "img -> format -> format = %d  " "\n", img -> format -> format); 
  }; 
  
  if (img -> w >= UINT8_MAX - 1) { 
    messerr("ERREUR: L'image est incompatible: elle ne devrait pas possèder plus de %s sommets en longueur, or elle en contient %s. (Fichier: '%s' [contient les Z du terrain])" "\n", int_string__stack(UINT8_MAX - 1), int_string__stack(img -> w), filename); 
    return false; 
  }; 
  
  if (img -> h >= UINT8_MAX - 1) { 
    messerr("ERREUR: L'image est incompatible: elle ne devrait pas possèder plus de %s sommets en hauteur, or elle en contient %s. (Fichier: '%s' [contient les Z du terrain])" "\n", int_string__stack(UINT8_MAX - 1), int_string__stack(img -> h), filename); 
    return false; 
  }; 
  
  this -> TailleX = img -> w; 
  this -> TailleY = img -> h; 
  printf(" ==> Taille de la carte en sommets: %s x %s " "\n", int_string__stack(this -> TailleX), int_string__stack(this -> TailleY)); 
  
  this -> manifold__extra_w_arrays__nb = our_manifold -> get_nb_extra_w_arrays_needed(our_manifold); 
  if (this -> manifold__extra_w_arrays__nb >= NB_MAX_EXTRA_ARRAYS) { 
    messerr("ERREUR: Incompatibilité entre la variété riemannienne et la structure contenant le sol - la variété demande %s extra lignes en longueur pour contenir ses calculs intermédiaires, or la structure de sol ne peut en contenir que %s." "\n", int_string__stack(this -> manifold__extra_w_arrays__nb), int_string__stack(NB_MAX_EXTRA_ARRAYS)); 
    return false; 
  }; 
  
  this -> manifold__extra_h_arrays__nb = our_manifold -> get_nb_extra_h_arrays_needed(our_manifold); 
  if (this -> manifold__extra_h_arrays__nb >= NB_MAX_EXTRA_ARRAYS) { 
    messerr("ERREUR: Incompatibilité entre la variété riemannienne et la structure contenant le sol - la variété demande %s extra lignes en hauteur pour contenir ses calculs intermédiaires, or la structure de sol ne peut en contenir que %s." "\n", int_string__stack(this -> manifold__extra_h_arrays__nb), int_string__stack(NB_MAX_EXTRA_ARRAYS)); 
    return false; 
  }; 
  
  this -> manifold__extra_w_h_arrays__nb = our_manifold -> get_nb_extra_w_h_arrays_needed(our_manifold); 
  if (this -> manifold__extra_w_h_arrays__nb >= NB_MAX_EXTRA_ARRAYS) { 
    messerr("ERREUR: Incompatibilité entre la variété riemannienne et la structure contenant le sol - la variété demande %s extra tableaux pour contenir ses calculs intermédiaires, or la structure de sol ne peut en contenir que %s." "\n", int_string__stack(this -> manifold__extra_w_h_arrays__nb), int_string__stack(NB_MAX_EXTRA_ARRAYS)); 
    return false; 
  }; 
  
  
  
  this -> Z             = malloc(sizeof(*this -> Z            ) * ((this -> TailleX)*(this -> TailleY))); 
  this -> normal        = malloc(sizeof(*this -> normal       ) * ((this -> TailleX)*(this -> TailleY))); 
  this -> global_map__x = malloc(sizeof(*this -> global_map__x) *  (this -> TailleX)                   ); 
  this -> global_map__y = malloc(sizeof(*this -> global_map__y) *                    (this -> TailleY) ); 
#if 1 
  for (int i = 0; i < this -> manifold__extra_w_arrays__nb; i++) { 
    this -> manifold__extra_w_arrays[i] = malloc(sizeof(*(this -> manifold__extra_w_arrays[i])) * (this -> TailleX)); 
  }; 
  for (int i = 0; i < this -> manifold__extra_h_arrays__nb; i++) { 
    this -> manifold__extra_h_arrays[i] = malloc(sizeof(*(this -> manifold__extra_h_arrays[i])) * (this -> TailleY)); 
  }; 
  for (int i = 0; i < this -> manifold__extra_w_h_arrays__nb; i++) { 
    this -> manifold__extra_w_h_arrays[i] = malloc(sizeof(*(this -> manifold__extra_w_h_arrays[i])) * (this -> TailleX) * (this -> TailleY)); 
  }; 
#else 
  //this -> PointsEcran = malloc(sizeof(*this -> PointsEcran) * ((this -> TailleX)*(this -> TailleY))); // RL: Not sure what that is. 
  this -> manifold__outer_angle       = malloc(sizeof(*this -> manifold__outer_angle      ) * (this -> TailleX)); 
  this -> manifold__outer_angle__cosf = malloc(sizeof(*this -> manifold__outer_angle__cosf) * (this -> TailleX)); 
  this -> manifold__outer_angle__sinf = malloc(sizeof(*this -> manifold__outer_angle__sinf) * (this -> TailleX)); 
  this -> manifold__inner_angle       = malloc(sizeof(*this -> manifold__inner_angle      ) * (this -> TailleY)); 
  this -> manifold__inner_angle__cosf = malloc(sizeof(*this -> manifold__inner_angle__cosf) * (this -> TailleY)); 
  this -> manifold__inner_angle__sinf = malloc(sizeof(*this -> manifold__inner_angle__sinf) * (this -> TailleY)); 
#endif 
  this -> manifold__vertex            = malloc(sizeof(*this -> manifold__vertex           ) * ((this -> TailleX)*(this -> TailleY))); 
  this -> manifold__normal            = malloc(sizeof(*this -> manifold__normal           ) * ((this -> TailleX)*(this -> TailleY))); 
  this -> manifold__vertex__water     = malloc(sizeof(*this -> manifold__vertex__water    ) * ((this -> TailleX)*(this -> TailleY))); 
  this -> manifold__normal__water     = malloc(sizeof(*this -> manifold__normal__water    ) * ((this -> TailleX)*(this -> TailleY))); 



  const uint8_t  * p8  = (uint8_t  *) img -> pixels;
  const uint32_t * p32 = (uint32_t *) img -> pixels;
    
#define PRINTF_Z_LINE_BEGIN fprintf(stdout, "%2d - [", j); 
#define PRINTF_Z_LINE_END fprintf(stdout, "]\n"); 
#define PRINTF_Z fprintf(stdout, "%d, ", z_valeur); 
  for (int j = 0; j < img -> h; j++) { 
    PRINTF_Z_LINE_BEGIN; 
    for (int i = 0; i < img -> w; i++) { 
      uint8_t z_valeur; 
      
      if (1 == bpp) { 
        z_valeur = p8[j * img->w + i]; 
      } 
      else if (4 == bpp) { 
        uint32_t temp = p32[j * img->w + i];
        temp &= img -> format -> Rmask;  //* Isolate red component */
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
      
      this -> SETZ(this, i, img->h-1-j,  ((float) z_valeur - 128.0f) / 1.0f);
    }; 
    PRINTF_Z_LINE_END; 
  }; 
  
  // RL: Normals should be computed. 
  CSol__Normal_compute(this); 
  
  // 
  CSol__compute__global_map__vertex_positions(this, map_i, map_j); 
  
  SDL_FreeSurface(img); 
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Chargement des Z terminés || Loading z-levels completed" "\n", __func__); 
  return true; 
}; 


#if 1 
float CSol__GetSlop(const CSol * this, const TPoint3D map_pos_new, const TPoint3D map_pos_old) { 
  const float map_pos_old__z = this -> GETZ(this, map_pos_old.x, map_pos_old.y); 
  const float map_pos_new__z = this -> GETZ(this, map_pos_new.x, map_pos_new.y); 
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




static CSol * CSol__make_content(CSol * this, const bool EnVaisseau); 
static CSol * CSol__make(const bool EnVaisseau); 
static void   CSol__delete_content(CSol * this); 
static void   CSol__delete(CSol * this); 

static CSol * CSol__make_content(CSol * this, const bool EnVaisseau) {
  BZERO_THIS(this); 
  BZERO_THIS(our_manifold); 
  
  ASSIGN_METHOD(CSol,this,make); 
  ASSIGN_METHOD(CSol,this,make_content); 
  ASSIGN_METHOD(CSol,this,delete); 
  ASSIGN_METHOD(CSol,this,delete_content); 
  ASSIGN_METHOD(CSol,this,ChargerZ); 
  ASSIGN_METHOD(CSol,this,GETZ); 
  ASSIGN_METHOD(CSol,this,SETZ); 
  ASSIGN_METHOD(CSol,this,SETINDTEXTURE); 
  ASSIGN_METHOD(CSol,this,GETINDTEXTURE); 
  ASSIGN_METHOD(CSol,this,GetTailleX); 
  ASSIGN_METHOD(CSol,this,GetTailleY); 
  ASSIGN_METHOD(CSol,this,AjouterTextureSol); 
  ASSIGN_METHOD(CSol,this,ChargerIndiceTextureBitmap); 
  ASSIGN_METHOD(CSol,this,Render); 
  ASSIGN_METHOD(CSol,this,Render__pre_computations); 
  ASSIGN_METHOD(CSol,this,RenderEau); 
  ASSIGN_METHOD(CSol,this,yatilEau); 
  //ASSIGN_METHOD(CSol,this,Differentiel); 
  
  this -> nb_texture      =    0; 
  this -> Z               = NULL; 
  this -> indices_texture = NULL; 
  
  return this; 
}; 

static CSol * CSol__make(const bool EnVaisseau) { 
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Constructeur/Constructor CSol()" "\n", __func__); 
  MALLOC_THIS(CSol,this); 
  return CSol__make_content(this, EnVaisseau); 
}; 

static void CSol__delete_content(CSol * this) { 
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "Destructeur/Destructor CSol()" "\n", __func__); 
  
  for (int i = 0; i < this -> nb_texture; i++) { 
    CTexture_delete(this -> TextureSol[i]); 
  };
  
  free(this -> indices_texture); 
  
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
  
  free(this -> global_map__x              ); 
  free(this -> global_map__y              ); 
  free(this -> normal                     ); 
  free(this -> Z); 
  
  BZERO_THIS(this); 
}; 
 
static void CSol__delete(CSol * this) { 
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






























































static void CSol__compute__global_map__vertex_positions(CSol * this, const int map_i, const int map_j) { 
  assert(this -> global_map__x               != NULL); 
  assert(this -> global_map__y               != NULL); 

  for (int vertex_i = 0; vertex_i < this -> TailleX; vertex_i++) { 
    this -> global_map__x[vertex_i] = map_i + ((float) vertex_i) / ((float) (this -> TailleX - 1)); 
  }; 
  
  for (int vertex_j = 0; vertex_j < this -> TailleY; vertex_j++) { 
    this -> global_map__y[vertex_j] = map_j + ((float) vertex_j) / ((float) (this -> TailleY - 1)); 
  };   
}; 

static void CSol__Normal_compute(CSol * this) { 
  // RL: Inside 
  {
    const int start_x = 1; 
    const int start_y = 1; 
    float (* normal)[3] = this -> normal + (start_y * (this -> TailleX) + start_x); 
    TPoint3D u1 = TPoint3D_make_scalar( 0, -1,  0); 
    TPoint3D u2 = TPoint3D_make_scalar( 1,  0,  0); 
    TPoint3D u3 = TPoint3D_make_scalar( 0,  1,  0); 
    TPoint3D u4 = TPoint3D_make_scalar(-1,  0,  0); 
    float * z1          = this -> Z + ((start_y + (int)u1.y) * this -> TailleX + (start_x + (int)u1.x)); 
    float * z2          = this -> Z + ((start_y + (int)u2.y) * this -> TailleX + (start_x + (int)u2.x)); 
    float * z3          = this -> Z + ((start_y + (int)u3.y) * this -> TailleX + (start_x + (int)u3.x)); 
    float * z4          = this -> Z + ((start_y + (int)u4.y) * this -> TailleX + (start_x + (int)u4.x)); 
    for (int i = 1; i < this -> TailleX - 1; i++) { 
      for (int j = 1; j < this -> TailleY - 1; j++) { 
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
    float (* normal)[3] = this -> normal + (start_y * (this -> TailleX) + start_x); 
    //TPoint3D u1 = TPoint3D_make_scalar( 0, -1,  0); 
    TPoint3D u2 = TPoint3D_make_scalar( 1,  0,  0); 
    TPoint3D u3 = TPoint3D_make_scalar( 0,  1,  0); 
    TPoint3D u4 = TPoint3D_make_scalar(-1,  0,  0); 
    //float * z1          = this -> Z + ((start_y + (int)u1.y) * this -> TailleX + (start_x + (int)u1.x)); 
    float * z2          = this -> Z + ((start_y + (int)u2.y) * this -> TailleX + (start_x + (int)u2.x)); 
    float * z3          = this -> Z + ((start_y + (int)u3.y) * this -> TailleX + (start_x + (int)u3.x)); 
    float * z4          = this -> Z + ((start_y + (int)u4.y) * this -> TailleX + (start_x + (int)u4.x)); 
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
    float (* normal)[3] = this -> normal + (start_y * (this -> TailleX) + start_x); 
    TPoint3D u1 = TPoint3D_make_scalar( 0, -1,  0); 
    TPoint3D u2 = TPoint3D_make_scalar( 1,  0,  0); 
    //TPoint3D u3 = TPoint3D_make_scalar( 0,  1,  0); 
    TPoint3D u4 = TPoint3D_make_scalar(-1,  0,  0); 
    float * z1          = this -> Z + ((start_y + (int)u1.y) * this -> TailleX + (start_x + (int)u1.x)); 
    float * z2          = this -> Z + ((start_y + (int)u2.y) * this -> TailleX + (start_x + (int)u2.x)); 
    //float * z3          = this -> Z + ((start_y + (int)u3.y) * this -> TailleX + (start_x + (int)u3.x)); 
    float * z4          = this -> Z + ((start_y + (int)u4.y) * this -> TailleX + (start_x + (int)u4.x)); 
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
    float (* normal)[3] = this -> normal + (start_y * (this -> TailleX) + start_x); 
    TPoint3D u1 = TPoint3D_make_scalar( 0, -1,  0); 
    TPoint3D u2 = TPoint3D_make_scalar( 1,  0,  0); 
    TPoint3D u3 = TPoint3D_make_scalar( 0,  1,  0); 
    //TPoint3D u4 = TPoint3D_make_scalar(-1,  0,  0); 
    float * z1          = this -> Z + ((start_y + (int)u1.y) * this -> TailleX + (start_x + (int)u1.x)); 
    float * z2          = this -> Z + ((start_y + (int)u2.y) * this -> TailleX + (start_x + (int)u2.x)); 
    float * z3          = this -> Z + ((start_y + (int)u3.y) * this -> TailleX + (start_x + (int)u3.x)); 
    //float * z4          = this -> Z + ((start_y + (int)u4.y) * this -> TailleX + (start_x + (int)u4.x)); 
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
    float (* normal)[3] = this -> normal + (start_y * (this -> TailleX) + start_x); 
    TPoint3D u1 = TPoint3D_make_scalar( 0, -1,  0); 
    //TPoint3D u2 = TPoint3D_make_scalar( 1,  0,  0); 
    TPoint3D u3 = TPoint3D_make_scalar( 0,  1,  0); 
    TPoint3D u4 = TPoint3D_make_scalar(-1,  0,  0); 
    float * z1          = this -> Z + ((start_y + (int)u1.y) * this -> TailleX + (start_x + (int)u1.x)); 
    //float * z2          = this -> Z + ((start_y + (int)u2.y) * this -> TailleX + (start_x + (int)u2.x)); 
    float * z3          = this -> Z + ((start_y + (int)u3.y) * this -> TailleX + (start_x + (int)u3.x)); 
    float * z4          = this -> Z + ((start_y + (int)u4.y) * this -> TailleX + (start_x + (int)u4.x)); 
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
    float (* normal)[3] = this -> normal + (start_y * (this -> TailleX) + start_x); 
    //TPoint3D u1 = TPoint3D_make_scalar( 0, -1,  0); 
    TPoint3D u2 = TPoint3D_make_scalar( 1,  0,  0); 
    TPoint3D u3 = TPoint3D_make_scalar( 0,  1,  0); 
    //TPoint3D u4 = TPoint3D_make_scalar(-1,  0,  0); 
    //float * z1          = this -> Z + ((start_y + (int)u1.y) * this -> TailleX + (start_x + (int)u1.x)); 
    float * z2          = this -> Z + ((start_y + (int)u2.y) * this -> TailleX + (start_x + (int)u2.x)); 
    float * z3          = this -> Z + ((start_y + (int)u3.y) * this -> TailleX + (start_x + (int)u3.x)); 
    //float * z4          = this -> Z + ((start_y + (int)u4.y) * this -> TailleX + (start_x + (int)u4.x)); 
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
    float (* normal)[3] = this -> normal + (start_y * (this -> TailleX) + start_x); 
    //TPoint3D u1 = TPoint3D_make_scalar( 0, -1,  0); 
    //TPoint3D u2 = TPoint3D_make_scalar( 1,  0,  0); 
    TPoint3D u3 = TPoint3D_make_scalar( 0,  1,  0); 
    TPoint3D u4 = TPoint3D_make_scalar(-1,  0,  0); 
    //float * z1          = this -> Z + ((start_y + (int)u1.y) * this -> TailleX + (start_x + (int)u1.x)); 
    //float * z2          = this -> Z + ((start_y + (int)u2.y) * this -> TailleX + (start_x + (int)u2.x)); 
    float * z3          = this -> Z + ((start_y + (int)u3.y) * this -> TailleX + (start_x + (int)u3.x)); 
    float * z4          = this -> Z + ((start_y + (int)u4.y) * this -> TailleX + (start_x + (int)u4.x)); 
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
    float (* normal)[3] = this -> normal + (start_y * (this -> TailleX) + start_x); 
    TPoint3D u1 = TPoint3D_make_scalar( 0, -1,  0); 
    //TPoint3D u2 = TPoint3D_make_scalar( 1,  0,  0); 
    //TPoint3D u3 = TPoint3D_make_scalar( 0,  1,  0); 
    TPoint3D u4 = TPoint3D_make_scalar(-1,  0,  0); 
    float * z1          = this -> Z + ((start_y + (int)u1.y) * this -> TailleX + (start_x + (int)u1.x)); 
    //float * z2          = this -> Z + ((start_y + (int)u2.y) * this -> TailleX + (start_x + (int)u2.x)); 
    //float * z3          = this -> Z + ((start_y + (int)u3.y) * this -> TailleX + (start_x + (int)u3.x)); 
    float * z4          = this -> Z + ((start_y + (int)u4.y) * this -> TailleX + (start_x + (int)u4.x)); 
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
    float (* normal)[3] = this -> normal + (start_y * (this -> TailleX) + start_x); 
    TPoint3D u1 = TPoint3D_make_scalar( 0, -1,  0); 
    TPoint3D u2 = TPoint3D_make_scalar( 1,  0,  0); 
    //TPoint3D u3 = TPoint3D_make_scalar( 0,  1,  0); 
    //TPoint3D u4 = TPoint3D_make_scalar(-1,  0,  0); 
    float * z1          = this -> Z + ((start_y + (int)u1.y) * this -> TailleX + (start_x + (int)u1.x)); 
    float * z2          = this -> Z + ((start_y + (int)u2.y) * this -> TailleX + (start_x + (int)u2.x)); 
    //float * z3          = this -> Z + ((start_y + (int)u3.y) * this -> TailleX + (start_x + (int)u3.x)); 
    //float * z4          = this -> Z + ((start_y + (int)u4.y) * this -> TailleX + (start_x + (int)u4.x)); 
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

}; 


