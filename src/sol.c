#include "global.h"
#include "sol.h"


/* précision, nb_phi, nb_theta pour le tore */

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

#define float_cjsj(j) \
  const float cj = cosf(this -> temps+(float) 2*PI*(j - this -> ybase)/this -> nb_theta); \
  const float sj = sinf(this -> temps+(float) 2*PI*(j - this -> ybase)/this -> nb_theta);





void CSol__AfficherCube(const CSol * this, const float x1, const float y1, const float z1, const float dx, const float dy, const float dz) {
  glBegin(GL_LINES); {
    for (int xx = 0; xx <= 1; xx++) {
      for (int yy = 0; yy <= 1; yy++) {
        for (int zz = 0;zz <= 1; zz++) {
          this -> glVertexTore(this, x1, y1 + yy*dy, z1 + zz*dz);
          this -> glVertexTore(this, x1, y1 + yy*dy, z1 + zz*dz);
          
          this -> glVertexTore(this, x1 + xx*dx, y1, z1 + zz*dz );
          this -> glVertexTore(this, x1 + xx*dx, y1 + dy, z1 + zz*dz);
          
          this -> glVertexTore(this, x1 + xx*dx, y1 +yy*dy, z1);
          this -> glVertexTore(this, x1 + xx*dx, y1 + yy*dy, z1 + dz);
        };
      };
    };
  } glEnd();                        
}; 


CSol * CSol_make_aux(CSol * this, const bool EnVaisseau) {
  assert(false); 
#if 0
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
  ASSIGN_METHOD(CSol,this,); 
#endif   
  
  this -> ybase = 0.0f; 
  this -> nb_texture = 0; 
  this -> Z = NULL; 
  this -> PointsEcran = NULL; 
  
  if (!EnVaisseau) {
    this -> R = 900.0f;
    //plus a est petit, moins on voit la compression du tore
    this -> a = (this -> R/3.0f);
    this -> nb_phi = ((int)this -> R/4);
    this -> nb_theta = (int) (this -> nb_phi/1.618f);
  }
  else {
    this -> R = 384.0f;
    this -> a = (this -> R/4.0f);
    this -> nb_phi = 63;
    this -> nb_theta = 31;
  };
  return this; 
}; 

CSol * CSol_make(const bool EnVaisseau) {
  printf("Constructeur CSol__CSol()\n");
  MALLOC_BZERO(CSol,this); 
  return CSol_make_aux(this, EnVaisseau); 
};

void CSol_delete(CSol * this) {
  printf("Destruction du sol %p\n", this);         
  //delete [] indices_texture;
  for (int i = 0; i < this -> nb_texture; i++) {
    CTexture_delete(this -> TextureSol[i]);
  }; 
  free(this -> indices_texture); 
  free(this -> Z);
  free(this -> PointsEcran);
  free(this);
};


int CSol__GetTailleX(const CSol * this) {
  return this -> TailleX; 
};   


int CSol__GetTailleY(const CSol * this) {
  return this -> TailleY;
}    

#define TEST_X_Y(x, y) ((0<=x) && (x < this -> TailleX) && (0<=y) && (y < this -> TailleY))

void CSol__SETZ(CSol * this, const int x, const int y, const float z) {
  if (!TEST_X_Y(x, y)) {
    printf("ERREUR : Débordement de tableau dans Z avec (%i, %i)\n", x, y);
    return;
  }; 

  this -> Z[(y)*this -> TailleX+(x)] = z;
}; 

void CSol__SETINDTEXTURE(CSol * this, const int x, const int y, const int ind) {
  if (!TEST_X_Y(x, y)) {
    printf("ERREUR : Débordement de tableau d'indice de textures en écriture avec (%i, %i)\n", x, y);
    return; 
  };
  this -> indices_texture[(y)*this -> TailleX+(x)] = ind;
}; 


int CSol__GETINDTEXTURE(const CSol * this, const int x, const int y) {
  int ii = 0;
  
  if ((0<=x) && (x < this -> TailleX) && (0<=y) && (y < this -> TailleY)) 
    ii = this -> indices_texture[(y)*this -> TailleX+(x)];
  else
    printf("ERREUR : Débordement de tableau d'indice de textures en lecture avec (%i, %i)\n", x, y);
  
  
  return ii;
};


float CSol__GETZ(const CSol * this, float x, float y) {
  /*x dans [0, nb_phi], y dans [0, nb_theta]*/
  /*on fait une interpolation pour connaître l'altitude (en fait, elle n'est connue que sur un maillage)*/
  
  this -> PositionModulo(this, &x, &y);
  const int ix = (int) floor(x);
  const int iy = (int) floor(y);
  
  const float lx = x - ix;
  const float ly = y - iy;
  
#if 0
#define ZZ(ind) ((((ind) >= 0) && ((ind) < (this -> TailleX+1)*(this -> TailleY+1))) ? this -> Z[(ind)] : 0)
  const float z00 = ZZ(iy*this -> TailleX+ix);
  const float z10 = ZZ(iy*this -> TailleX+ix+1);
  const float z01 = ZZ((iy+1)*this -> TailleX+ix);
  const float z11 = ZZ((iy+1)*this -> TailleX+ix+1);
#else
#define ZIND(x,y) ((y)*this -> TailleX+(x))
#define ZZ(x,y) (((((x) >= 0) && ((y) >= 0) && ((x) < this -> TailleX) && ((y) < this -> TailleY))) ? this -> Z[(ZIND((x),(y)))] : 0)
  const float z00 = ZZ(ix,iy);
  const float z10 = ZZ(ix+1,iy);
  const float z01 = ZZ(ix,iy+1);
  const float z11 = ZZ(ix+1,iy+1);
#endif

  return ((z00 * (1 - lx) + z10 * lx) * (1 - ly) + (z01 *(1 - lx) + z11 * lx) * ly);
}








float CSol__FacteurCompression(const CSol * this, const float j) {
  return (this -> R + this -> a * cosf(this -> temps+2*PI*(j - this -> ybase)/this -> nb_theta)) / this -> R;
  //return sqrt(sqr(R+a*cosf(t+2*PI*j/nb_theta)) - sqr(a*sinf(t+2*PI*j/nb_theta)) );
}; 


float CSol__IndiceTemps(const CSol * this, const float j) {
  /*renvoie 0 la nuit et 1 quand l'anneau est au zénith*/
  return (1.0f+cosf(this -> temps+2*PI*(j - this -> ybase)/this -> nb_theta))/2.0f;
  //	return sqrt(sqr(R+a*cosf(t+2*PI*j/nb_theta)) - sqr(a*sinf(t+2*PI*j/nb_theta)) );
};


void CSol__glVertexTore(const CSol * this, const float x, const float y, const float z) {
  const float cj = cosf(this -> temps+(float) 2*PI*(y - this -> ybase)/this -> nb_theta);
  const float sj = sinf(this -> temps+(float) 2*PI*(y - this -> ybase)/this -> nb_theta);

  const float ci = cosf((float)2*PI*(x)/this -> nb_phi);
  const float si = sinf((float)2*PI*(x)/this -> nb_phi);
	
  glVertex3f((this -> R + (this -> a + z) * cj) * ci, (this -> R + (this -> a + z) * cj) * si, (this -> a + z) * sj); 
};




void CSol__CalcPoints(const CSol * this, const int i1, const int j1, const int i2, const int j2) {
  if (this -> PointsEcran == NULL)
    //printf("ERREUR: La variable PointsEcran est à NULL. Ce n'est pas normal. Pt un problème dans le .carte. (style un - qui n'est pas -. ... vive Romain!)\n"); 
    printf("ERREUR: La variable PointsEcran est à NULL. Ce n'est pas normal. Pt un problème dans le .carte. (style un - qui n'est pas -. !)\n"); 

  for (int j = j1; j<=j2; j++) {
    float cj = cosf(this -> temps+(float) 2*PI*(j - this -> ybase)/this -> nb_theta);
    float sj = sinf(this -> temps+(float) 2*PI*(j - this -> ybase)/this -> nb_theta);    

    for (int i = i1; i<=i2; i++) {
      float ci = cosf((float)2*PI*(i)/this -> nb_phi);
      float si = sinf((float)2*PI*(i)/this -> nb_phi);
      
      
      /*
	(R+( a+GETZ((i),(j)) )  *cosf(t+(float)2*PI*(j)/nb_theta) ) * cosf((float)2*PI*(i)/nb_phi)
        (R+( a+GETZ((i),(j)) ) *cosf(t+(float)2*PI*(j)/nb_theta) ) * sinf((float)2*PI*(i)/nb_phi)
        ( a+GETZ((i),(j)) ) *sinf(t+(float)2*PI*(j)/nb_theta) */
      TPoint3D df_theta, df_phi, normal;
      float zsol = this -> GETZ(this, (i),(j));
      df_theta.x = -(this -> R+( this -> a+zsol )*sj ) * ci;
      df_theta.y = -(this -> R+( this -> a+zsol )*sj ) * si;
      df_theta.z =     ( this -> a+zsol )*cj ;
      
      df_phi.x = -(this -> R+( this -> a+zsol )*cj) * si;
      df_phi.y =  (this -> R+( this -> a+zsol )* cj) * ci;
      df_phi.z =  0;
        
      //normal = df_theta ^ df_phi;
      normal = TPoint3D_normale(df_theta, df_phi);
      
#define TESTINDICEPointsEcran(i) (!((0 <= (i)) & ((i) < (this -> TailleX)*(this -> TailleY))))
          
      if (TESTINDICEPointsEcran(j*this -> TailleX+i))
        printf("ERREUR: Ecriture dans PointsEcran incorrecte (%i, %i) \n", i, j);
      else {
        this -> PointsEcran[j*this -> TailleX+i].normal = normal;
        this -> PointsEcran[j*this -> TailleX+i].pt.x = (this -> R + (this -> a + this -> GETZ(this, (i),(j)) ) *cj) * ci;
        this -> PointsEcran[j*this -> TailleX+i].pt.y = (this -> R + (this -> a + this -> GETZ(this, (i),(j)) ) *cj) * si;
        this -> PointsEcran[j*this -> TailleX+i].pt.z =              (this -> a + this -> GETZ(this, (i),(j)) ) *sj;
      }
    }
  }
};


void CSol__tore(const CSol * this, const int i, const int j) {

/*
  if (i < 0) i += nb_phi;
  if (j < 0) j += nb_theta;

  if (i >= nb_phi) i -= nb_phi;
  if (j >= nb_theta) j -= nb_theta;*/

  if (TESTINDICEPointsEcran(j*this -> TailleX+i))
    printf("ERREUR : Lecture dans PointsEcran incorrecte (%i, %i)\n ", i, j);

  glNormal3fv((float*) &this -> PointsEcran[j*this -> TailleX+i].normal);
  glVertex3f(this -> PointsEcran[j*this -> TailleX+i].pt.x, 
             this -> PointsEcran[j*this -> TailleX+i].pt.y, 
             this -> PointsEcran[j*this -> TailleX+i].pt.z);
}



void CSol__tore0(const CSol * this, int i, int j) {
  if (i < 0) i += this -> nb_phi;
  if (j < 0) j += this -> nb_theta;

  if (i >= this -> nb_phi) i -= this -> nb_phi;
  if (j >= this -> nb_theta) j -= this -> nb_theta;

  float_cjsj(j);

  const float ci = cosf((float)2*PI*(i)/this -> nb_phi);
  const float si = sinf((float)2*PI*(i)/this -> nb_phi);
  /*	(R+( a+GETZ((i),(j)) )  *cosf(t+(float)2*PI*(j)/this -> nb_theta) ) * cosf((float)2*PI*(i)/this -> nb_phi)
	(R+( a+GETZ((i),(j)) ) *cosf(t+(float)2*PI*(j)/this -> nb_theta) ) * sinf((float)2*PI*(i)/this -> nb_phi)
	( a+GETZ((i),(j)) ) *sinf(t+(float)2*PI*(j)/this -> nb_theta) */
  TPoint3D df_theta, df_phi, normal;

  df_theta.x = -(this -> R + (this -> a + this -> ZEau) * sj) * ci;
  df_theta.y = -(this -> R + (this -> a + this -> ZEau) * sj) * si;
  df_theta.z =               (this -> a + this -> ZEau) * cj;

  df_phi.x = -(this -> R+( this -> a+this -> ZEau )*cj) * si;
  df_phi.y =  (this -> R+( this -> a+this -> ZEau )* cj ) * ci;
  df_phi.z =  0;

  //normal = df_theta ^ df_phi;
  normal = TPoint3D_normale(df_theta, df_phi);

  glNormal3fv((float*)&normal);
  glVertex3f((this -> R + (this -> a + this -> ZEau) * cj) * ci, (this -> R + (this -> a + this -> ZEau) * cj) * si, (this -> a + this -> ZEau) *sj);
}



void CSol__PositionModulo(const CSol * this, float * i_ref, float * j_ref) {
  if (*i_ref < 0)
    *i_ref += this -> nb_phi;
          
  if (*i_ref >= this -> nb_phi)
    *i_ref -= this -> nb_phi;
          
          
  if (*j_ref < 0)
    *j_ref += this -> nb_theta;
          
  if (*j_ref >= this -> nb_theta)
    *j_ref -= this -> nb_theta;
};




void CSol__LookAt(const CSol * this, const float i, const float j, float z) {
#define theta_vue -0.15f
#define phi_vue 0.0f
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  float_cjsj(j);
  const float cjp = cosf(theta_vue+this -> temps+2*PI*(j-this -> ybase)/this -> nb_theta);
  const float sjp = sinf(theta_vue+this -> temps+2*PI*(j-this -> ybase)/this -> nb_theta);
	
  const float cip = cosf(phi_vue+2*PI*(i)/this -> nb_phi);
  const float sip = sinf(phi_vue+2*PI*(i)/this -> nb_phi);
  const float ci = cosf(2*PI*(i)/this -> nb_phi);
  const float si = sinf(2*PI*(i)/this -> nb_phi);

  z += this -> a;
  gluLookAt((this -> R+(z+HauteurCamera) *cjp )*cip, //position de la caméra
	    (this -> R+(z+HauteurCamera) *cjp )*sip,
               (z+HauteurCamera) *sjp,

	    (this -> R+(z) *cj ) * ci, //on regarde le point
	    (this -> R+(z) *cj ) * si,
	    (z) *sj ,

	    -sj*ci+0*(-si), //vecteur qui pointe vers le haut
	    -sj*(si)+0*ci,
	    cj);
}; 







void CSol__LookAt_angle(const CSol * this, const float i, const float j, const float z, const float dist, const float AngleXY, const float AngleZ) {
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );  
  
  
  const TPoint3D p = this -> GetPoint3D(this, i, j, z); //point que l'on regarde (généralement c'est le héros !!)

  TPoint3D ux = TPoint3D_sub(this -> GetPoint3D(this, i+1.0f, j, z), p);
  TPoint3D uy = TPoint3D_sub(this -> GetPoint3D(this, i, j+1.0f, z), p);
  TPoint3D uz = TPoint3D_sub(this -> GetPoint3D(this, i, j, z+1.0f), p); 
  
  TPoint3D direction_horizontale = TPoint3D_add(TPoint3D_lambda(cosf(AngleXY), ux), TPoint3D_lambda(sinf(AngleXY), uy)); 
  
  TPoint3D_Normer2(&direction_horizontale);
  TPoint3D_Normer2(&ux);
  TPoint3D_Normer2(&uy);
  TPoint3D_Normer2(&uz);
  
  TPoint3D u = this -> GetPoint3D(this, i, j, z); 
  TPoint3D_sub_self(u, TPoint3D_lambda(dist * cosf(AngleZ), direction_horizontale)); 
  TPoint3D_sub_self(u, TPoint3D_lambda(dist * sinf(AngleZ), uz));
  
  gluLookAt(u.x, //position de la caméra
	        u.y,
	        u.z,
	        
	        p.x, //on regarde le point
	        p.y,
	        p.z,
	        
            uz.x, //vecteur qui pointe vers le haut
            uz.y,
            uz.z);
};



TPoint3D CSol__GetPoint3D(const CSol * this, const float i, const float j, const float z) {
  float_cjsj(j);
  const float ci = cosf((float)2*PI*(i)/this -> nb_phi);
  const float si = sinf((float)2*PI*(i)/this -> nb_phi);      

  return TPoint3D_make_scalar((this -> R+( this -> a + z ) *cj) * ci, 
			      (this -> R+( this -> a + z ) *cj) * si, 
			                 ( this -> a + z ) *sj);
}; 


void CSol__AjouterTextureSol(CSol * this, const char * s, const int indice_dans_bitmap) {
  if (this -> nb_texture >= NB_MAX_TEXTURESOL) {
    printf("   ERREUR: Il y a déjà trop de textures de sol dans la carte.\n");
    return;
  };
  this -> TextureSol[this -> nb_texture] = CTexture_make(s);
  this -> indices_dans_bitmap[this -> nb_texture] = indice_dans_bitmap;
  this -> nb_texture++;
};
  

void CSol__ChargerIndiceTextureBitmap(CSol * this, const char * fichier_bitmap) {
  printf("Chargement des zones de textures (fichier %s)...\n", fichier_bitmap);

  char reelfile[strlen(NIVEAUXDIR) + strlen(fichier_bitmap) + 1];
  strcat(strcpy(reelfile, NIVEAUXDIR), fichier_bitmap);
  fichier_bitmap = reelfile;

  SDL_Surface * img = NULL;
  img = IMG_Load(fichier_bitmap);
  
  if (img == NULL)
    printf("ERREUR : Impossible de charger le fichier image '%s'...\n", fichier_bitmap);

  if ((img->w != this -> TailleX) || (img->h != this -> TailleY))
    printf("ERREUR: La taille de l'image %s est différente de celle spécifiée dans le fichier des altitudes.\n", fichier_bitmap);


  int bpp = img->format->BytesPerPixel;

  if (bpp != 3)
    printf("WARNING: L'image '%s' doit être dans un format 24 bits.\n.", fichier_bitmap);     

    

#if 0
  if (4 == bpp) {
    uint8_t * p = (uint8_t *) img -> pixels;
    if (0 == strcmp("/foretverschaman.textures.png", strrchr(fichier_bitmap, '/'))) {
      FILE * f = fopen("../log/foretverschaman.textures.png.log", "wb");
      for (int j = 0; j < img->h; j++) {
        for (int i = 0; i < img->w; i++) {
          uint8_t r = p[j * img->pitch + i * bpp];
          uint8_t g = p[j * img->pitch + i * bpp + 1];
          uint8_t b = p[j * img->pitch + i * bpp + 2];
          uint8_t a = p[j * img->pitch + i * bpp + 3];
          fprintf(f, "[%3u,%3u,%3u,%3u] ", r, g, b, a);
        }
        fprintf(f, "\n");
      }
      fclose(f);
    }
  }
#endif        

  // *** conversion de l'image dans un état potable (RGB) ***
  {
    SDL_Surface * convertie = SDL_ConvertSurface(img, &sdl_pixel_format_rgb, SDL_SWSURFACE);
    SDL_FreeSurface(img);
    img = convertie;
  }

  bpp = img->format->BytesPerPixel;
  assert(3 == bpp);
    
  uint8_t * p = (uint8_t *) img -> pixels;
  //uint24_t * p = (uint24_t *) img -> pixels;
  //uint32_t * p32 = (uint32_t *) img -> pixels;

#if 0
  //if (0 == strcmp("/foretverschaman.textures.png", strrchr(fichier_bitmap, '/'))) {
  //#define FF "chezmoi.textures.png"
  //#define FF "chezprokofiev.textures.png"
#define FF "cimetiere.textures.png"
  if (0 == strcmp("/" FF, strrchr(fichier_bitmap, '/'))) {
    FILE * f = fopen("../log/" FF ".log", "wb");
      for (int j = 0; j < img->h; j++) {
        for (int i = 0; i < img->w; i++) {
          uint8_t r = p[j * img->pitch + i * bpp];
          uint8_t g = p[j * img->pitch + i * bpp + 1];
          uint8_t b = p[j * img->pitch + i * bpp + 2];
          fprintf(f, "[%3u,%3u,%3u] ", r, g, b);
        }
        fprintf(f, "\n");
      }
      fclose(f);
    }
#undef FF
#endif        
          
  printf("pointeur image : %p\n", p);
  for (int j = 0; j < img->h; j++) 
    for (int i = 0; i < img->w; i++)
      {
        //int ind_color = p[j * img->pitch + i * bpp] + 256*p[j * img->pitch + i * bpp + 1] + 256*256*p[j * img->pitch + i * bpp + 2]; 
        int ind_color = 256*256*p[j * img->pitch + i * bpp] + 256*p[j * img->pitch + i * bpp + 1] + p[j * img->pitch + i * bpp + 2]; 
      
        // on part à la recherche (algo bourrin) de la texture qui aurait la couleur associée correspondantes au pixel (i, j)
        int k;
      
      //for (k = NB_MAX_TEXTURESOL; k>=0; k--)
      for (k = 0; k < this -> nb_texture; k++)
        //if (indices_texture[k] ==  ind_color) break;
        if (this -> indices_dans_bitmap[k] ==  ind_color) break;
      
      //printf("indice de texture en (i = %d ; j = %d) = %i", i, j, k);
      
      
      //if (k<0)
        if (k >= this -> nb_texture) {
          printf("   ERREUR : la couleur %i au pixel (%i, %i) n'est associée à aucune texture.\n", ind_color, i, j);
          k = 0; // le jeu continue à tourner en prenant la texture ° 0 pour ce pixel
        }
        
        // k contient l'indice de texture
        this -> SETINDTEXTURE(this, i, img->h-1-j, k);
      };
    
  SDL_FreeSurface(img);
  printf("Chargement des indices de textures terminé !! (t'es sur que c ca Fancois ?? euh non...)\n"); 
}; 



void CSol__Render(const CSol * this, int i1, int j1, int i2, int j2) {

  //fprintf(stderr, "RenderSol: I am called\n");
     
#define ARF(i1,TailleX) if (i1 < 0) i1 = 0; else if (i1 >= TailleX-1) i1 = TailleX-2;
  
  ARF(i1, this -> TailleX);
  ARF(i2, this -> TailleX);
  ARF(j1, this -> TailleY);
  ARF(j2, this -> TailleY);   

  
  /* spécification: i1, i2 entre 0 et this -> TailleX-2 */
  
  this -> CalcPoints(this, i1, j1, i2+1, j2+1);

  //glDisable(GL_DEPTH_TEST) ;
  
  
#define COLOR_Z(i, j) // {float f = 0.5f + GETZ((i), (j))/50.0f; if (f<0.2f) f = 0.2f; if (f>1.0f) f = 1.0f; glColor3f(f,f,f);}
#define ALPHA_ET_BLANC(f) glColor4f(1.0f, 1.0f, 1.0f, f);

/* 
   ALPHATEX(i, j) renvoit 1.0f si la texture de n° numtex s'affiche en (i, j)
   sinon renvoie 0.0f
*/
#define ALPHATEX(i, j) \
 ((this -> GETINDTEXTURE(this, i, j) == numtex) || (numtex == 0) ? 1.0f : 0.0f)	

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

    for (int i = i1; i<=i2; i++) {
      for (int j = j1; j<=j2; j++) {
        x = i; 
        y = j;    
              
        float a1 = ALPHATEX(x, y);
        float a2 = ALPHATEX(x+1, y);
        float a3 = ALPHATEX(x+1, y+1);
        float a4 = ALPHATEX(x, y+1);
        
        glBegin(GL_QUADS); {
          glColor4f(1.0f, 1.0f, 1.0f, a1);
          glTexCoord2f(0.0f,0.0f);
          this -> tore(this, x,y);
          
          glColor4f(1.0f, 1.0f, 1.0f, a2);
          glTexCoord2f(1.0f,0.0f);
          this -> tore(this, x+1,y);
          
          glColor4f(1.0f, 1.0f, 1.0f, a3);
          glTexCoord2f(1.0f,1.0f);
          this -> tore(this, x+1,y+1);
          
          glColor4f(1.0f, 1.0f, 1.0f, a4);
          glTexCoord2f(0.0f,1.0f);
          this -> tore(this, x,y+1);
        } glEnd();
      }
    }
  }
  
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
}




void CSol__SetTemps(CSol * this, const float in_temps) {
  this -> temps = in_temps;
}



float CSol__GetTemps(const CSol * this) {
  return this -> temps;    
}

bool CSol__yatilEau(const CSol * this, const float i, const float j, const float z) {
  return (z < this -> ZEau);
}    

	
void CSol__RenderEau(const CSol * this, int i1, int j1, int i2, int j2) {
  ARF(i1, this -> TailleX);
  ARF(i2, this -> TailleX);
  ARF(j1, this -> TailleY);
  ARF(j2, this -> TailleY);

#define COLOR_EAU(i, j) glColor4f(0.7f,0.7f,1.0f, 0.5f + 0.2f*cos(((i)+(j)+100*this -> temps)/2.0f));
//#define COLOR_EAU(i, j) glColor4f(0.5f,0.0f,0.0f, 0.5f + 0.2f*cos(((i)+(j)+100*t)/2.0f));

  //fprintf(stderr, "RenderEau: I am called\n");
  //Render(i1, j1, i2, j2);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

  //glDepthFunc(GL_LEQUAL);
  glDisable(GL_TEXTURE_2D); {
#define PREC_EAU 3
    for (int i = i1; i<=i2; i+=PREC_EAU) {
      glBegin(GL_QUAD_STRIP); {
        for (int j = j1; j<=j2; j+=PREC_EAU) {
          COLOR_EAU(i, j);
          //	glTexCoord2f(0.0f + num_tex*0.5f,0.0f);
          this -> tore0(this, i,j);

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

	}
      } glEnd();
    }
    glColor3f(1.0f,1.0f,1.0f);
  } glEnable(GL_TEXTURE_2D);
}



void CSol__MatricePour2D(const CSol * this, const float i, const float j, const float z) {
  float_cjsj(j);

  const float ci = cosf(2*PI*(i)/this -> nb_phi);
  const float si = sinf(2*PI*(i)/this -> nb_phi);
         
  glTranslatef( (this -> R + ( this -> a + z ) *cj) * ci, //on place la sprite sur le point du tore
		(this -> R + ( this -> a + z ) *cj) * si, 
		(            ( this -> a + z ) *sj));

  glRotatef(360.f*(float)(i)/this -> nb_phi,0,0,1) ;
  //on la pivote autour de (Oz)
  
  glRotatef(90.0f-360.f*(this -> temps+2*PI*(float)(j-this -> ybase)/this -> nb_theta)/(2*PI),0,1,0) ;
  //puis on la met par terre	
}



void CSol__MatricePourDessiner(const CSol * this, const float i, const float j) {
  float_cjsj(j);

  const float ci = cosf(2*PI*(i)/this -> nb_phi);
  const float si = sinf(2*PI*(i)/this -> nb_phi);
  glPushMatrix() ;
         
  glTranslatef( (this -> R + ( this -> a + this -> GETZ(this, i, j) ) *cj) * ci, //on place la sprite sur le point du tore
		(this -> R + ( this -> a + this -> GETZ(this, i, j) ) *cj) * si, 
		(            ( this -> a + this -> GETZ(this, i, j) ) *sj ));

  glRotatef(360.f*(float)(i)/this -> nb_phi,0,0,1) ; //on la pivote autour de (Oz)
  glRotatef(90.0f-360.f*(this -> temps+2*PI*(float)(j-this -> ybase)/this -> nb_theta)/(2*PI),0,1,0) ; //puis on la met par terre	
         

}


void CSol__ChargerZ(CSol * this, const char * filename) {
  printf("Chargement du terrain de la carte...\n");

  char reelfile[ARRAY_SIZE(NIVEAUXDIR)-1 + strlen(filename) + 1];
  strcat(strcpy(reelfile, NIVEAUXDIR), filename);
  filename = reelfile;

  SDL_Surface * img;
  img = IMG_Load (filename);

  if (img == NULL)
    printf("ERREUR : Impossible de charger le fichier image '%s' (ce fichier contient les Z du terrain)\n",filename);

  int bpp = img->format->BytesPerPixel;
  
  if (bpp != 1)
    printf("WARNING: L'image '%s' doit être dans un format niveau de gris. Elle représente les Z de la carte\n.", filename);     
  
  
  uint8_t  * p8  = (uint8_t  *) img -> pixels;
  uint32_t * p32 = (uint32_t *) img -> pixels;

  this -> TailleX = img -> w;
  this -> TailleY = img -> h;
  printf(" ---> on en déduit que la taille de la carte est (%i, %i).\n", this -> TailleX, this -> TailleY); 
     
  this -> Z = (float *) malloc(sizeof(float) * ((this -> TailleX)*(this -> TailleY)));
  this -> PointsEcran = malloc(sizeof(*this -> PointsEcran) * ((this -> TailleX)*(this -> TailleY))); 
	
  printf("Allocation en mémoire de la table qui à un point de la carte associe l'id de la texture de ce point.\n");
  this -> indices_texture = (int *) malloc(sizeof(int) * ((this -> TailleX)*(this -> TailleY)));
     
  for (int i = 0; i < img->w; i++)
    for (int j = 0; j < img->h; j++) {
      uint8_t valeur;

      if (1 == bpp)
        valeur = p8[j * img->w + i];
      else if (4 == bpp) {
        uint32_t temp = p32[j * img->w + i];
        temp &= img -> format -> Rmask;  /* Isolate red component */
        temp = (temp >> img -> format -> Rshift); /* Shift it down to 8-bit */
        temp = (temp << img -> format -> Rloss);  /* Expand to a full 8-bit number */

        valeur = temp;
      }
      else if (3 == bpp) {
        valeur = p8[(j * img->w + i) * bpp];
      }
      else {
        assert(false);
        valeur = 0;
      }

      this -> SETZ(this, i, img->h-1-j,  ((float) valeur - 128.0f) / 1.0f);
    }
  
  printf("On désalloue la mémoire de l'image..\n");   
  SDL_FreeSurface(img);
  printf("Chargement des Z terminés !!\n"); 
};


   
TPoint2D CSol__Differentiel(const CSol * this, const TPoint3D pos) {
  TPoint2D p;

#define precdiff 0.5f

  const float z1 = this -> GETZ(this, pos.x + precdiff, pos.y) - this -> GETZ(this, pos.x, pos.y);
  const float z2 = this -> GETZ(this, pos.x, pos.y + precdiff) - this -> GETZ(this, pos.x, pos.y);

 /* printf("Calcul de différentiel : %f, %f, %f, %f\n", this -> GETZ(this, pos.x+precdiff, pos.y),
	 this -> GETZ(this, pos.x, pos.x), this -> GETZ(this, pos.x, pos.y+precdiff), this -> GETZ(this, pos.x, pos.y));*/

  p.x = z1; //this -> GETZ(this, int(rx)+1, int(ry)) - this -> GETZ(this, int(rx)-1, int(ry));
  p.y = z2;//this -> GETZ(this, int(rx), int(ry)+1) - this -> GETZ(this, int(rx), int(ry)-1);

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
