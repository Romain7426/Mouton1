#include "global.h"
#include "sol.h"


#include "riemann.ci" 

#if 1 
static struct riemann_t our_manifold[1]; 
#else 
static struct riemann_t   our_manifold__struct; 
static struct riemann_t * our_manifold = & our_manifold__struct; 
#endif 


//* précision, nb_phi, nb_theta pour le tore */ 

#if 0 
static void SETZ(CSol * this, int x, int y, const float z);
static void SETINDTEXTURE(CSol * this, int x, int y, int ind);
static void AjouterTextureSol(CSol * this, const char * s, int indice_dans_bitmap);
static void ChargerIndiceTextureBitmap(CSol * this, const char * fichier_bitmap);
static void Blit(CSol * this, const float i, const float j, const float z, CTexture* tex, const float taillex, const float tailleh);
static void Cube(CSol * this, const float i, const float j, const float z, const float taillex, const float tailleh);
static void MatricePourDessiner(CSol * this, const float i, const float j);
static void ChargerZ(CSol * this, const char * filename);	
static void SetTemps(CSol * this, const float temps);

static int GETINDTEXTURE(const CSol * this, int x, int y);
static TPoint3D GetPoint3D(const CSol * this, const float i, const float j, const float z);
static void tore(const CSol * this, int i,int j);
static void tore0(const CSol * this, int i,int j);
static void CalcPoints(const CSol * this, int i1, int j1, int i2, int j2);
static int GetTailleX(const CSol * this);
static int GetTailleY(const CSol * this);
static void AfficherCube(const CSol * this, const float x1, const float y1, const float z1, const float dx, const float dy, const float dz);
static float FacteurCompression(const CSol * this, const float j);
static float IndiceTemps(const CSol * this, const float j);
static void LookAt(const CSol * this, const float i, const float j, const float z); /*place la caméra au dessus du point (const CSol * this, i, j)*/
static void LookAt(const CSol * this, const float i, const float j, const float z, const float dist, const float AngleXY, const float AngleZ); /*place la caméra au dessus du point (const CSol * this, i, j)*/
static void Render(const CSol * this, int i1, int j1, int i2, int j2); /*dessine la partie du tore entre (const CSol * this, i1, j1) et (const CSol * this, i2, j2)*/
static void RenderEau(const CSol * this, int i1, int j1, int i2, int j2);
static bool yatilEau(const CSol * this, const float i, const float j, const float z);
static void PositionModulo(const CSol * this, float& i, float& j);
static TPoint2D Differentiel(const CSol * this, const TPoint3D pos);
static float GETZ(const CSol * this, const float x, const float y);
static void MatricePour2D(const CSol * this, const float i, const float j, const float z);
static void glVertexTore(const CSol * this, const float x, const float y, const float z);
static float GetTemps(const CSol * this);
#endif 




static void CSol__Normal_compute(CSol * this); 


#define theta_vue_blit -1.3f

//extern bool EnVaisseau;


/*dimension du tore*/
//#define R 200.0f
/*#define R 900.0f
  #define a (R/2.0f)
  #define nb_phi ((int)R/6)//((int)R/3)
  #define nb_theta (nb_phi/2)*/
#define HauteurCamera 120.0f

//#define NbBigCases_phi 10


//#define couleureau D3DRGBA(0.4, 0.4, 1, 0.5)

#define RANDINT(min, max) (rand()%((max)-(min))+(min))

	



#if 0 
// RL: These are local coordinates. 
static void CSol__AfficherCube(const CSol * this, const float x1, const float y1, const float z1, const float dx, const float dy, const float dz) { 
  glBegin(GL_LINES); { 
    for (int xx = 0; xx <= 1; xx++) { 
      for (int yy = 0; yy <= 1; yy++) { 
        for (int zz = 0;zz <= 1; zz++) { 
          our_manifold -> glVertexTore(our_manifold, x1        , y1 + yy*dy, z1 + zz*dz); 
          our_manifold -> glVertexTore(our_manifold, x1        , y1 + yy*dy, z1 + zz*dz); 
          
          our_manifold -> glVertexTore(our_manifold, x1 + xx*dx, y1        , z1 + zz*dz); 
          our_manifold -> glVertexTore(our_manifold, x1 + xx*dx, y1 +    dy, z1 + zz*dz); 
          
          our_manifold -> glVertexTore(our_manifold, x1 + xx*dx, y1 + yy*dy, z1        ); 
          our_manifold -> glVertexTore(our_manifold, x1 + xx*dx, y1 + yy*dy, z1 +    dz); 
        }; 
      }; 
    }; 
  } glEnd(); 
}; 
#endif 

#if 1 
// RL: 
#else 
static void CSol__PositionModulo(const CSol * this, float * i_ref, float * j_ref) { 
  if (*i_ref < 0) 
    *i_ref += our_manifold -> nb_phi; 
  
  if (*i_ref >= our_manifold -> nb_phi) 
    *i_ref -= our_manifold -> nb_phi; 
  
  if (*j_ref < 0) 
    *j_ref += our_manifold -> nb_theta; 
  
  if (*j_ref >= our_manifold -> nb_theta) 
    *j_ref -= our_manifold -> nb_theta; 
}; 
#endif 


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
  //*on fait une interpolation pour connaître l'altitude (en fait, elle n'est connue que sur un maillage)*/ 
  
  const float sol_x = ((float) this -> TailleX) * (map_x - floorf(map_x)); 
  const float sol_y = ((float) this -> TailleX) * (map_y - floorf(map_y)); 
  
  //*x dans [0, nb_phi], y dans [0, nb_theta]*/ 
  //this -> PositionModulo(this, &x, &y); 
  //CSol__PositionModulo(this, &x, &y); 
  const int ix = (int) floor(sol_x); 
  const int iy = (int) floor(sol_y); 
  
  const float lx = sol_x - ix; 
  const float ly = sol_y - iy; 
  
#define ZIND(x,y) ((y)*this -> TailleX+(x)) 
#define ZZ(x,y) (((((x) >= 0) && ((y) >= 0) && ((x) < this -> TailleX) && ((y) < this -> TailleY))) ? this -> Z[(ZIND((x),(y)))] : 0) 
  const float z00 = ZZ(ix  ,iy  ); 
  const float z10 = ZZ(ix+1,iy  ); 
  const float z01 = ZZ(ix  ,iy+1); 
  const float z11 = ZZ(ix+1,iy+1); 
  
  const float z   = (z00 * (1 - lx) + z10 * lx) * (1 - ly) + 
    (z01 * (1 - lx) + z11 * lx) *      ly; 
  
  return z; 
}; 








static void CSol__compute_manifold_vertices_and_normals(CSol * this, const int map_i, const int map_j, const riemann_t * our_manifold) { 
  assert(this -> global_map__x               != NULL); 
  assert(this -> global_map__y               != NULL); 
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
  
  for (int cell_i = 0; cell_i < this -> TailleX - 1; cell_i++) { 
    this -> global_map__x[cell_i] = map_i + ((float) cell_i) / ((float) this -> TailleX); 
  }; 
  
  for (int cell_j = 0; cell_j < this -> TailleY - 1; cell_j++) { 
    this -> global_map__y[cell_j] = map_j + ((float) cell_j) / ((float) this -> TailleY); 
  }; 
  
  
  for (int cell_i = 0; cell_i < this -> TailleX - 1; cell_i++) { 
    const float outer_angle = OUTER_ANGLE__GET(our_manifold,this -> global_map__x[cell_i]); 
    this -> manifold__outer_angle      [cell_i] =      outer_angle ; 
    this -> manifold__outer_angle__cosf[cell_i] = cosf(outer_angle); 
    this -> manifold__outer_angle__sinf[cell_i] = sinf(outer_angle); 
  }; 
  
  for (int cell_j = 0; cell_j < this -> TailleY - 1; cell_j++) { 
    const float inner_angle = INNER_ANGLE__GET(our_manifold,this -> global_map__y[cell_j]); 
    this -> manifold__inner_angle      [cell_j] =      inner_angle ; 
    this -> manifold__inner_angle__cosf[cell_j] = cosf(inner_angle); 
    this -> manifold__inner_angle__sinf[cell_j] = sinf(inner_angle); 
  }; 
  
  
  for (int cell_j = 0; cell_j < this -> TailleY - 1; cell_j++) { 
    const float cj = this -> manifold__inner_angle__cosf[cell_j]; 
    const float sj = this -> manifold__inner_angle__sinf[cell_j]; 
    for (int cell_i = 0; cell_i < this -> TailleX - 1; cell_i++) { 
      const int index = cell_j * this -> TailleX + cell_i; 
      const float ci = this -> manifold__outer_angle__cosf[cell_i]; 
      const float si = this -> manifold__outer_angle__sinf[cell_i]; 
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
  
}; 










#define TESTINDICEPointsEcran(__i__) (!((0 <= (__i__)) & ((__i__) < (this -> TailleX)*(this -> TailleY)))) 


#if 0 
// RL: We want to compute the manifold coordinate of the sub-rectangle having (i1, i2, j1, j2) for map-local coordinates. 
// RL: What's it used for? 
// RL: That's a riemann function. 
static void CSol__CalcPoints(const CSol * this, const int i1, const int j1, const int i2, const int j2) {
  if (this -> PointsEcran == NULL) { 
    //printf("ERREUR: La variable PointsEcran est à NULL. Ce n'est pas normal. Pt un problème dans le .carte. (style un - qui n'est pas -. ... vive Romain!)\n"); 
    messerr("ERREUR: La variable PointsEcran est à NULL. Ce n'est pas normal. Pt un problème dans le .carte. (style un - qui n'est pas -. !)\n"); 
    return; 
  }; 
  
  
  
  
  
#if 1 

#else   
  // RL: TODO XXX FIXME: 'float_cisi' is computed j2-j1 too many times. One time is enough. 
  for (int j = j1; j <= j2; j++) { 
    float_cjsj(j); 
    for (int i = i1; i <= i2; i++) { 
      
      const int indice_point_ecran = j * this -> TailleX + i; 
      if (TESTINDICEPointsEcran(indice_point_ecran)) { 
        messerr("ERREUR: Écriture dans PointsEcran incorrecte (%i, %i)" "\n", i, j); 
	continue; 
      }; 


      float_cisi(i); 
      const float zsol = this -> GETZ(this, (i),(j)); 
      
      // RL: This is not clear. 
      //     Seems like FS wanted to compute the normal on the manifold. 
      //     In order to do, he computed the base of the tangent plan, 
      //     and then their vectorial product. 
#if 1 // RL: RL's 
      TPoint3D normal; 
      normal.x = cj * ci ; 
      normal.y = cj * si ; 
      normal.z = sj      ; 
      // RL: This computation seems accurate for a true torus. 
      //     However, our torus has an unleveled ground. 
      //     Anyways, that does not show up is FS' computations. 
      //     Because, to take that into account, we have to take the neighbors' z, which is definitely not the case. 
      //     (There's no dz anywhere.) 
      
#else 
      /*
	(R+( a+GETZ((i),(j)) )  *cosf(t+(float)2*PI*(j)/nb_theta) ) * cosf((float)2*PI*(i)/nb_phi)
        (R+( a+GETZ((i),(j)) ) *cosf(t+(float)2*PI*(j)/nb_theta) ) * sinf((float)2*PI*(i)/nb_phi)
        ( a+GETZ((i),(j)) ) *sinf(t+(float)2*PI*(j)/nb_theta) */ 
      // RL: If x moves by dx, then its image moves by dx*df_phi. 
      // RL: If y moves by dy, then its image moves by dy*df_theta. 
      TPoint3D df_theta, df_phi; //, normal; 
#if 1 // RL: RL's 
      // RL: Shouldn't we normalize that? 
      // RL: Why is there 'R' in that? 
      // RL: inner_angle + π/2 
      df_theta.x = - (our_manifold -> a + zsol) * sj * ci ; 
      df_theta.y = - (our_manifold -> a + zsol) * sj * si ; 
      df_theta.z =   (our_manifold -> a + zsol) * cj      ; 
#else // RL: FS' 
      // RL: inner_angle + π/2 
      df_theta.x = - (our_manifold -> R + (our_manifold -> a + zsol) * sj) * ci; 
      df_theta.y = - (our_manifold -> R + (our_manifold -> a + zsol) * sj) * si; 
      df_theta.z =                        (our_manifold -> a + zsol) * cj ; 
#endif 
      
      // RL: outer_angle + π/2 
      df_phi.x   = - (our_manifold -> R + (our_manifold -> a + zsol) * cj) * si; 
      df_phi.y   =   (our_manifold -> R + (our_manifold -> a + zsol) * cj) * ci; 
      df_phi.z   =    0;
        
      // RL: ??? 
      //normal = df_theta ^ df_phi;
      const TPoint3D normal = TPoint3D_normale(df_theta, df_phi);
#endif 
      
      { 
        this -> PointsEcran[indice_point_ecran].normal = normal; 
        this -> PointsEcran[indice_point_ecran].pt.x   = (our_manifold -> R + (our_manifold -> a + zsol) * cj) * ci; 
        this -> PointsEcran[indice_point_ecran].pt.y   = (our_manifold -> R + (our_manifold -> a + zsol) * cj) * si; 
        this -> PointsEcran[indice_point_ecran].pt.z   =                      (our_manifold -> a + zsol) * sj; 
      }; 
    }; 
  };
#endif 
};

#endif 



#if 0 
// RL: Blitting some computed point. 
// RL: That's a riemann function. Should be called glVertexNormalAt 
static void CSol__tore(const CSol * this, const int i, const int j) { 
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
}; 
#endif 


#if 0 
// RL: That thing deals with water. 
// RL: That's a riemann function. Should be called glVertexAndNormalAt 
// RL: That's the riemann function for a flat map: 'z' is not taken into account. That's why it's used for water. 
static void CSol__tore0(const CSol * this, int i, int j) { 
  if (i < 0) i += our_manifold -> nb_phi; 
  if (j < 0) j += our_manifold -> nb_theta; 
  
  if (i >= our_manifold -> nb_phi  ) i -= our_manifold -> nb_phi; 
  if (j >= our_manifold -> nb_theta) j -= our_manifold -> nb_theta; 
  
  float_cjsj(j); 
  float_cisi(i); 
  
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
}; 
#endif 








#if 0 
// RL: That's the camera function. 
// RL: TODO XXX FIXME: Should be in the camera module 
static void CSol__LookAt(const CSol * this, const float i, const float j, const float given_z) { 
#define theta_vue -0.15f 
#define phi_vue 0.0f 
  glMatrixMode(GL_MODELVIEW); // RL: That's the screen projection matrix. 
                              // RL: To read it, glGetFloatv(GL_MODELVIEW_MATRIX, _an_allocated_array__ float m[16]) // Could be used to debug 
  glLoadIdentity(); 
  
  float_cjsj(j); 
  float_cisi(i); 
  
  const float inner_angle_p = theta_vue + inner_angle; 
  const float cjp = cosf(inner_angle_p); 
  const float sjp = sinf(inner_angle_p); 
  
  const float outer_angle_p = phi_vue + outer_angle; 
  const float cip = cosf(outer_angle_p); 
  const float sip = sinf(outer_angle_p); 
  
  //const float z = given_z + our_manifold -> a; 
  gluLookAt(
	    //position de la caméra 
	    // RL: From where. 
	    MANIFOLD_POINT_GET__COMMA(our_manifold,cip,sip,cjp,sjp,given_z + HauteurCamera), 

	    //on regarde le point 
	    //RL: Target position 
	    MANIFOLD_POINT_GET__COMMA(our_manifold,ci,si,cj,sj,given_z), 
	    
	    //vecteur qui pointe vers le haut 
	    // RL: Without it, the screen would be freely spin around. No need to normalize it or to have a perfect vector - OpenGL will project it onto projecting surface and then normalize it. . 
	    - sj * ci  + 0 *(-si), 
	    - sj *(si) + 0 *  ci, 
	    cj); 
}; 



// RL: That's the camera function. 
// RL: TODO XXX FIXME: Should be in the camera module 
static void CSol__LookAt_angle(const CSol * this, const float i, const float j, const float z, const float dist, const float AngleXY, const float AngleZ) {
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );  
  
  const TPoint3D p = our_manifold -> GetPoint3D(our_manifold, i, j, z); //point que l'on regarde (généralement c'est le héros !!)

  TPoint3D ux = TPoint3D_sub(our_manifold -> GetPoint3D(our_manifold, i+1.0f, j     , z     ), p); 
  TPoint3D uy = TPoint3D_sub(our_manifold -> GetPoint3D(our_manifold, i     , j+1.0f, z     ), p); 
  TPoint3D uz = TPoint3D_sub(our_manifold -> GetPoint3D(our_manifold, i     , j     , z+1.0f), p); 
  
  TPoint3D direction_horizontale = TPoint3D_add(TPoint3D_lambda(cosf(AngleXY), ux), TPoint3D_lambda(sinf(AngleXY), uy)); 
  
  TPoint3D_Normer2(&direction_horizontale);
  TPoint3D_Normer2(&ux);
  TPoint3D_Normer2(&uy);
  TPoint3D_Normer2(&uz);
  
  TPoint3D u = our_manifold -> GetPoint3D(our_manifold, i, j, z); 
  TPoint3D_sub_self(u, TPoint3D_lambda(dist * cosf(AngleZ), direction_horizontale)); 
  TPoint3D_sub_self(u, TPoint3D_lambda(dist * sinf(AngleZ), uz));
  
  gluLookAt(
	    //position de la caméra 
	    // RL: From where. 
	    u.x, 
	    u.y, 
	    u.z, 
	    
	    //on regarde le point 
	    //RL: Target position 
	    p.x, 
	    p.y, 
	    p.z, 
	    
	    //vecteur qui pointe vers le haut 
	    // RL: Without it, the screen would be freely spin around. No need to normalize it or to have a perfect vector - OpenGL will project it onto projecting surface and then normalize it. . 
            uz.x, 
            uz.y, 
            uz.z);
};
#endif 



static void CSol__AjouterTextureSol(CSol * this, const char * s, const int indice_dans_bitmap) {
  if (this -> nb_texture >= NB_MAX_TEXTURESOL) {
    messerr("ERREUR: Il y a déjà trop de textures de sol dans la carte." "\n"); 
    return;
  };
  this -> TextureSol[this -> nb_texture] = CTexture_make(s); 
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
  printf("Chargement des zones de textures (fichier %s)...\n", fichier_bitmap); 
  
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
  
  const int cell2_x = MIN(this -> TailleX - 1, cell0_x + nb_cells_on_the_right); 
  const int cell2_y = MIN(this -> TailleY - 1, cell0_y + nb_cells_infront); 
  
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
    
    for (int cell_i = cell1_x; cell_i <= cell2_x; cell_i++) { 
      for (int cell_j = cell1_y; cell_j <= cell2_y; cell_j++) { 
	const int index00 = (cell_j + 0) * this -> TailleX + (cell_i + 0); 
	const int index01 = (cell_j + 1) * this -> TailleX + (cell_i + 0); 
	const int index11 = (cell_j + 1) * this -> TailleX + (cell_i + 1); 
	const int index10 = (cell_j + 0) * this -> TailleX + (cell_i + 1); 
        const int x = cell_i; 
        const int y = cell_j; 
	
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
#define ARF(__i1__,__TailleX__) if (__i1__ < 0) { __i1__ = 0; } else if (__i1__ >= __TailleX__ - 1) { __i1__ = __TailleX__ - 2; }; 
  
  ARF(i1, this -> TailleX);
  ARF(i2, this -> TailleX);
  ARF(j1, this -> TailleY);
  ARF(j2, this -> TailleY);   
  //messerr("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: "  "CSol = %p - i1, i2, j1, j2 = %d, %d, %d, %d" "\n", __func__, this, i1, i2, j1, j2); 
  
  
  //* spécification: i1, i2 entre 0 et this -> TailleX-2 */
  
  this -> CalcPoints(this, i1, j1, i2+1, j2+1);

  //glDisable(GL_DEPTH_TEST) ;
  
  
#define COLOR_Z(i, j) // {float f = 0.5f + GETZ((i), (j))/50.0f; if (f<0.2f) f = 0.2f; if (f>1.0f) f = 1.0f; glColor3f(f,f,f);}
#define ALPHA_ET_BLANC(f) glColor4f(1.0f, 1.0f, 1.0f, f);

  /* 
     ALPHATEX(i, j) renvoit 1.0f si la texture de n° numtex s'affiche en (i, j)
     sinon renvoie 0.0f
  */
#define ALPHATEX(i, j)							\
  ((this -> GETINDTEXTURE(this, i, j) == numtex) || (numtex >= 0) ? 1.0f : 0.0f)	
  
  int x, y;
  
  // Set up the blending of the 2 textures
  /*
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_COMBINE_EXT);
    glTexEnvi(GL_TEXTURE_ENV,GL_COMBINE_RGB_EXT,GL_INTERPOLATE_EXT);
    glTexEnvi(GL_TEXTURE_ENV,GL_SOURCE0_RGB_EXT,GL_PREVIOUS_EXT);
    glTexEnvi(GL_TEXTURE_ENV,GL_OPERAND0_RGB_EXT,GL_SRC_COLOR);
    glTexEnvi(GL_TEXTURE_ENV,GL_SOURCE1_RGB_EXT,GL_TEXTURE);
    glTexEnvi(GL_TEXTURE_ENV,GL_OPERAND1_RGB_EXT,GL_SRC_COLOR);
    glTexEnvi(GL_TEXTURE_ENV,GL_SOURCE2_RGB_EXT,GL_TEXTURE);
    glTexEnvi(GL_TEXTURE_ENV,GL_OPERAND2_RGB_EXT,GL_SRC_ALPHA);
  */
  
  /*
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glEnable(GL_BLEND);
  */
  //glDepthFunc(GL_LEQUAL);
  //glDepthMask(GL_TRUE);
  /*
    glDisable(GL_LIGHTING);
    glDisable(GL_DITHER);
  */
            
#define GL_TEXTURE_ARB(i) 0x84C0 + i
  // là par défaut, il n'y a que le canal 0 d'activé
  
  /*
    for (int numtex = 0; numtex<this -> nb_texture; numtex++)
    {
    // active le canal n° numtex 
    glActiveTextureARB( GL_TEXTURE_ARB(numtex) ); 
    glEnable(GL_TEXTURE_2D);   
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
    glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);
    
    this -> TextureSol[numtex]->getObject()->GLTextureCourante();     
    
    }  
  */        
            
  //glDepthFunc(GL_LEQUAL);
  glEnable(GL_TEXTURE_2D);  

  // RL: Oh My Lord! 
  // RL: The ground is blitted 'numtex' times! 
  //     Why??? 
  // 
  for (int numtex = 0; numtex < this -> nb_texture; numtex++) { 
    this -> TextureSol[numtex] -> GLTextureCourante(this -> TextureSol[numtex]); 
    /*
      if (numtex == 0)
      glBlendFunc(GL_ONE, GL_ZERO);
      else
    */
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
    
#if 0    
    if (numtex > 0)
      glDepthMask(GL_FALSE);
#endif

    for (int i = i1; i <= i2; i++) { 
      for (int j = j1; j <= j2; j++) { 
        x = i; 
        y = j; 
	
        const float a1 = ALPHATEX(x  , y  ); 
        const float a2 = ALPHATEX(x+1, y  ); 
        const float a3 = ALPHATEX(x+1, y+1); 
        const float a4 = ALPHATEX(x  , y+1); 
        
        glBegin(GL_QUADS); { 
          glColor4f(1.0f, 1.0f, 1.0f, a1); // RL: Setting up the alpha channel. 
          glTexCoord2f(0.0f,0.0f); 
          this -> tore(this, x, y); // RL: It's a call to glVertex (and glNormal). BASICALLY, this is the projection function. 
          
          glColor4f(1.0f, 1.0f, 1.0f, a2); 
          glTexCoord2f(1.0f,0.0f); 
          this -> tore(this, x+1, y); 
          
          glColor4f(1.0f, 1.0f, 1.0f, a3); 
          glTexCoord2f(1.0f,1.0f); 
          this -> tore(this, x+1, y+1); 
          
          glColor4f(1.0f, 1.0f, 1.0f, a4); 
          glTexCoord2f(0.0f,1.0f); 
          this -> tore(this, x, y+1); 
        } glEnd(); 
      };
    };
  };
  
  //glDepthMask(GL_TRUE);
  
  /*
    for (int numtex = 1; numtex<this -> nb_texture; numtex++)
    {
    glActiveTextureARB(GL_TEXTURE_ARB(numtex));
    glDisable(GL_TEXTURE_2D); // Disable the 2nd texture
    }
  */

  //glActiveTextureARB(GL_TEXTURE0_ARB); // Switch back to the first texture
    
  
  /*
    
    for (int i = i1; i <= i2; i++)
    {
    for (int j = j2; j >= j1; j--)
    {
    this -> TextureSol[GETINDTEXTURE(i, j)] -> getObject() -> GLTextureCourante();
    glBegin(GL_QUADS);
  	  
    if (GETINDTEXTURE(i, j) != 0)
    {
    x = i; y = j + 1;	
    ALPHA_ET_BLANC(1.0f);
    glTexCoord2f(0.0f, 0.0f);
    tore(x, y);
        
    glTexCoord2f(1.0f, 0.0f);
    tore(x + 1, y);
    
    ALPHA_ET_BLANC(0.0f);
    glTexCoord2f(1.0f, 1.0f);
    tore(x + 1, y + 1);
	        
    glTexCoord2f(0.0f, 1.0f);
    tore(x, y + 1);
                 
              
    x = i + 1; y = j;	
    ALPHA_ET_BLANC(1.0f);
    glTexCoord2f(0.0f, 0.0f);
    tore(x, y);
                 
    ALPHA_ET_BLANC(0.0f); 
    glTexCoord2f(1.0f, 0.0f);
    tore(x + 1, y);
    
    glTexCoord2f(1.0f, 1.0f);
    tore(x + 1, y + 1);
        	  
    ALPHA_ET_BLANC(1.0f);
    glTexCoord2f(0.0f, 1.0f);
    tore(x, y + 1);
    } 
  	  
    glEnd();
    }
    } 	  

  */

  /*
    this -> TextureSol -> getObject() -> GLTextureCourante();
    glBegin(GL_QUADS);
    for (int i = i1; i <= i2; i++)
    {
      
    for (int j = j1; j <= j2; j++)
    {
    int num_tex = i % 2;
	  
	  
    COLOR_Z(i, j);
    glTexCoord2f(0.0f + num_tex * 0.5f, 0.0f);
    tore(i, j);
	  
    COLOR_Z(i + 1, j);
    glTexCoord2f(0.5f + num_tex * 0.5f, 0.0f);
    tore(i + 1, j);
	  
    COLOR_Z(i + 1, j + 1);
    glTexCoord2f(0.5f + num_tex * 0.5f, 1.0f);
    tore(i + 1, j + 1);
	  
    COLOR_Z(i, j + 1);
    glTexCoord2f(0.0f + num_tex * 0.5f, 1.0f);
    tore(i, j + 1);
	  
    }
      
    }
    glEnd();
  */

  //glEnable(GL_DEPTH_TEST) ;
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

static bool CSol__yatilEau(const CSol * this, const float i, const float j, const float z) {
  return (z < this -> ZEau);
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
    for (int cell_i = cell1_x; cell_i <= cell2_x; cell_i += PREC_EAU) { 
      glBegin(GL_QUAD_STRIP); { 
	for (int cell_j = cell1_y; cell_j <= cell2_y; cell_j += PREC_EAU) { 
	  const int index00 = (cell_j +        0) * this -> TailleX + (cell_i +        0); 
	  const int index01 = (cell_j + PREC_EAU) * this -> TailleX + (cell_i +        0); 
	  const int index11 = (cell_j + PREC_EAU) * this -> TailleX + (cell_i + PREC_EAU); 
	  const int index10 = (cell_j +        0) * this -> TailleX + (cell_i + PREC_EAU); 
	  
          COLOR_EAU(cell_i, cell_j); 
          //	glTexCoord2f(0.0f + num_tex*0.5f,0.0f); 
          //this -> tore0(this, i,j); // RL: Basically, it's a call to glVertex (& glNormal). 
	  glNormal3fv(this -> manifold__normal__water[index00]); 
	  glVertex3fv(this -> manifold__vertex__water[index00]); 

	  
          COLOR_EAU(cell_i + PREC_EAU, cell_j); 
          //	glTexCoord2f(0.5f + num_tex*0.5f,0.0f); 
          //this -> tore0(this, i+PREC_EAU,j); 
	  glNormal3fv(this -> manifold__normal__water[index10]); 
	  glVertex3fv(this -> manifold__vertex__water[index10]); 
	  
#if 0
          //	glTexCoord2f(0.5f + num_tex*0.5f,1.0f);
          COLOR_EAU(cell_i + PREC_EAU, cell_j + PREC_EAU);
          //this -> tore0(this, i+PREC_EAU,j+PREC_EAU); 
	  glNormal3fv(this -> manifold__normal__water[index11]); 
	  glVertex3fv(this -> manifold__vertex__water[index11]); 

          //	glTexCoord2f(0.0f + num_tex*0.5f,1.0f);
          COLOR_EAU(cell_i, cell_j + PREC_EAU);
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
    for (int cell_i = i1; cell_i <= i2; cell_i += PREC_EAU) { 
      glBegin(GL_QUAD_STRIP); { 
        for (int j = j1; j <= j2; j += PREC_EAU) { 
	const int index00 = (cell_j + 0) * this -> TailleX + (cell_i + 0); 
	const int index01 = (cell_j + 1) * this -> TailleX + (cell_i + 0); 
	const int index11 = (cell_j + 1) * this -> TailleX + (cell_i + 1); 
	const int index10 = (cell_j + 0) * this -> TailleX + (cell_i + 1); 



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


#if 0 
static void CSol__MatricePour2D(const CSol * this, const float i, const float j, const float z) {
  float_cjsj(j); 
  float_cisi(i); 
  
  //on place la sprite sur le point du tore 
  glTranslatef(MANIFOLD_POINT_GET__COMMA(our_manifold,ci,si,cj,sj,z)); 
  
  //on la pivote autour de (Oz) 
  glRotatef(360.f*(float)(i)/our_manifold -> nb_phi,0,0,1); 
  
  //puis on la met par terre 
  glRotatef(90.0f-360.f*(our_manifold -> temps+2*PI*(float)(j-our_manifold -> ybase)/our_manifold -> nb_theta)/(2*PI),0,1,0); 
}; 
#endif 


#if 0 
static void CSol__MatricePourDessiner(const CSol * this, const float i, const float j) { 
  float_cjsj(j); 
  float_cisi(i); 
  const float zsol = this -> GETZ(this, (i),(j)); 
  
  glPushMatrix(); 
  
  //on place la sprite sur le point du tore 
  glTranslatef(MANIFOLD_POINT_GET__COMMA(our_manifold,ci,si,cj,sj,zsol)); 
  
  //on la pivote autour de (Oz) 
  // RL: Pourquoi 360 et pas 2π?? Parce que 'glRotatef' fait une rotation en degrés. 
  glRotatef(360.f * ((float)(i))/((float)our_manifold -> nb_phi), 0, 0, 1); 
  
  //puis on la met par terre 
  // RL: Pourquoi 360 et pas 2π?? Parce que 'glRotatef' fait une rotation en degrés. 
  glRotatef(90.0f - 360.f * (our_manifold -> temps/(2.*PI) + ((float)(j - our_manifold -> ybase))/((float)our_manifold -> nb_theta)),0,1,0); 
}; 
#endif 



static void CSol__ChargerZ(CSol * this, const char * filename) { 
  printf("Chargement du terrain de la carte...\n"); 
  
  char reelfile[ARRAY_SIZE(NIVEAUXDIR)-1 + strlen(filename) + 1]; 
  strcat(strcpy(reelfile, NIVEAUXDIR), filename); 
  filename = reelfile; 
  
  SDL_Surface * img; 
  img = IMG_Load(filename); 
  
  if (img == NULL) { 
    messerr("ERREUR: Impossible de charger le fichier image '%s' (ce fichier contient les Z du terrain)\n", filename); 
    return; 
  }; 
  
  const int bpp = img -> format -> BytesPerPixel; 
  
  if (bpp != 1) { 
    messerr("WARNING: " "L'image '%s' doit être dans un format niveau de gris. Elle représente les Z de la carte. Or elle est dans un format: %d BytesPerPixel. En conséquence de quoi, nous utiliserons la couleur rouge en tant que proxy.\n", filename, bpp); 
    messerr("\t\t" "w x h = %d pixels x %d pixels " "\n", img -> w, img -> h); 
    //messerr("\t\t" "img -> format -> format = %d  " "\n", img -> format -> format); 
  }; 
  
  
  const uint8_t  * p8  = (uint8_t  *) img -> pixels;
  const uint32_t * p32 = (uint32_t *) img -> pixels;
  
  assert(img -> w < UINT8_MAX - 1); 
  assert(img -> h < UINT8_MAX - 1); 
  this -> TailleX = img -> w; 
  this -> TailleY = img -> h; 
  printf(" ---> on en déduit que la taille de la carte est (%i, %i)." "\n", this -> TailleX, this -> TailleY); 
  
  this -> Z           = malloc(sizeof(*this -> Z          ) * ((this -> TailleX)*(this -> TailleY))); 
  this -> normal      = malloc(sizeof(*this -> normal     ) * ((this -> TailleX)*(this -> TailleY))); 
  //this -> PointsEcran = malloc(sizeof(*this -> PointsEcran) * ((this -> TailleX)*(this -> TailleY))); // RL: Not sure what that is. 
  this -> global_map__x               = malloc(sizeof(*this -> global_map__x              ) * (this -> TailleX)); 
  this -> global_map__y               = malloc(sizeof(*this -> global_map__y              ) * (this -> TailleY)); 
  this -> manifold__outer_angle       = malloc(sizeof(*this -> manifold__outer_angle      ) * (this -> TailleX)); 
  this -> manifold__outer_angle__cosf = malloc(sizeof(*this -> manifold__outer_angle__cosf) * (this -> TailleX)); 
  this -> manifold__outer_angle__sinf = malloc(sizeof(*this -> manifold__outer_angle__sinf) * (this -> TailleX)); 
  this -> manifold__inner_angle       = malloc(sizeof(*this -> manifold__inner_angle      ) * (this -> TailleY)); 
  this -> manifold__inner_angle__cosf = malloc(sizeof(*this -> manifold__inner_angle__cosf) * (this -> TailleY)); 
  this -> manifold__inner_angle__sinf = malloc(sizeof(*this -> manifold__inner_angle__sinf) * (this -> TailleY)); 
  this -> manifold__vertex            = malloc(sizeof(*this -> manifold__vertex           ) * ((this -> TailleX)*(this -> TailleY))); 
  this -> manifold__normal            = malloc(sizeof(*this -> manifold__normal           ) * ((this -> TailleX)*(this -> TailleY))); 
  this -> manifold__vertex__water     = malloc(sizeof(*this -> manifold__vertex__water    ) * ((this -> TailleX)*(this -> TailleY))); 
  this -> manifold__normal__water     = malloc(sizeof(*this -> manifold__normal__water    ) * ((this -> TailleX)*(this -> TailleY))); 
  
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
        temp &= img -> format -> Rmask;  /* Isolate red component */
        temp = (temp >> img -> format -> Rshift); /* Shift it down to 8-bit */
        temp = (temp << img -> format -> Rloss);  /* Expand to a full 8-bit number */

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
  
  printf("On désalloue la mémoire de l'image.." "\n");   
  SDL_FreeSurface(img);
  printf("Chargement des Z terminés!!" "\n"); 
};



TPoint2D CSol__Differentiel(const CSol * this, const TPoint3D pos) { 
  TPoint2D p; 

#define precdiff 0.5f

  const float z1 = this -> GETZ(this, pos.x + precdiff, pos.y) - this -> GETZ(this, pos.x, pos.y);
  const float z2 = this -> GETZ(this, pos.x, pos.y + precdiff) - this -> GETZ(this, pos.x, pos.y);

  /* printf("Calcul de différentiel : %f, %f, %f, %f\n", this -> GETZ(this, pos.x+precdiff, pos.y),
     this -> GETZ(this, pos.x, pos.x), this -> GETZ(this, pos.x, pos.y+precdiff), this -> GETZ(this, pos.x, pos.y));*/

  p.x = z1; //this -> GETZ(this, int(rx)+1, int(ry)) - this -> GETZ(this, int(rx)-1, int(ry)); 
  p.y = z2; //this -> GETZ(this, int(rx), int(ry)+1) - this -> GETZ(this, int(rx), int(ry)-1); 

  return p; 
}; 


/*
  TPoint D1 = GETDER(int(gx), int(gy));
  TPoint D2 = GETDER(int(gx)+1, int(gy));
  TPoint D3 = GETDER(int(gx), int(gy)+1);
  TPoint D4 = GETDER(int(gx)+1, int(gy)+1);


  float tx = gx - int(gx);
  float ty = gy - int(gy);

  float a1 = (1-tx)*(1-ty);
  float a2 = tx*(1-ty);
  float a3 = (1-tx)*ty;
  float a4 = tx*ty;

  return ((a1 * D1) + (a2 * D2) + (a3* D3) + (a4 * D4)) / (a1 + a2 + a3 + a4);


  }


*/



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
  ASSIGN_METHOD(CSol,this,Differentiel); 
  ASSIGN_METHOD(CSol,this,ChargerZ); 
  ASSIGN_METHOD(CSol,this,GETZ); 
#if 0 
  ASSIGN_METHOD(CSol,this,LookAt); 
  ASSIGN_METHOD(CSol,this,LookAt_angle); 
  ASSIGN_METHOD(CSol,this,PositionModulo); 
  ASSIGN_METHOD(CSol,this,MatricePourDessiner); 
  ASSIGN_METHOD(CSol,this,MatricePour2D); 
  ASSIGN_METHOD(CSol,this,GetPoint3D); 
  ASSIGN_METHOD(CSol,this,tore); 
  ASSIGN_METHOD(CSol,this,tore0); 
  ASSIGN_METHOD(CSol,this,CalcPoints); 
  //ASSIGN_METHOD(CSol,this,AfficherCube); 
  //ASSIGN_METHOD(CSol,this,FacteurCompression); 
  ASSIGN_METHOD(CSol,this,IndiceTemps); 
  //ASSIGN_METHOD(CSol,this,Blit); 
  //ASSIGN_METHOD(CSol,this,Cube); 
  //ASSIGN_METHOD(CSol,this,glVertexTore); 
  ASSIGN_METHOD(CSol,this,SetTemps); 
  ASSIGN_METHOD(CSol,this,GetTemps); 
#endif 
  
#if 0 
  ASSIGN_METHOD(riemann,our_manifold,glVertexTore); 
  ASSIGN_METHOD(riemann,our_manifold,GetPoint3D); 
#endif 
  
  this -> nb_texture      =    0; 
  this -> Z               = NULL; 
  //this -> PointsEcran     = NULL; 
  this -> indices_texture = NULL; 
  
#if 0 
  our_manifold -> ybase = 0.0f; 
  if (!EnVaisseau) { 
    our_manifold -> R = 900.0f; 
    //plus a est petit, moins on voit la compression du tore 
    our_manifold -> a = (our_manifold -> R / 3.0f); 
    our_manifold -> nb_phi    = ((int) our_manifold -> R / 4); 
    our_manifold -> nb_theta  = (int) (our_manifold -> nb_phi/1.618f); 
  } 
  else { 
    our_manifold -> R = 384.0f; 
    our_manifold -> a = (our_manifold -> R / 4.0f); 
    our_manifold -> nb_phi    = 63; 
    our_manifold -> nb_theta  = 31; 
  }; 
#endif 
  
  return this; 
}; 

static CSol * CSol__make(const bool EnVaisseau) {
  printf("Constructeur CSol__CSol()\n");
  //MALLOC_BZERO(CSol,this); 
  MALLOC_THIS(CSol,this); 
  return CSol__make_content(this, EnVaisseau); 
};

static void CSol__delete_content(CSol * this) {
  printf("Destruction du sol %p\n", this); 
  //delete [] indices_texture; 
  for (int i = 0; i < this -> nb_texture; i++) { 
    CTexture_delete(this -> TextureSol[i]); 
  };


  free(this -> normal                     ); 
  free(this -> global_map__x              ); 
  free(this -> global_map__y              ); 
  free(this -> manifold__outer_angle      ); 
  free(this -> manifold__outer_angle__cosf); 
  free(this -> manifold__outer_angle__sinf); 
  free(this -> manifold__inner_angle      ); 
  free(this -> manifold__inner_angle__cosf); 
  free(this -> manifold__inner_angle__sinf); 
  free(this -> manifold__vertex           ); 
  free(this -> manifold__normal           ); 
  free(this -> manifold__vertex__water    ); 
  free(this -> manifold__normal__water    ); 



 
  free(this -> indices_texture); 
  free(this -> Z); 
  //free(this -> PointsEcran); 
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
