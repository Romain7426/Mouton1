#include "global.hpp"
#include "sol.hpp"


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
  float cj = cosf(temps+(float) 2*PI*(j - ybase)/nb_theta); \
  float sj = sinf(temps+(float)2*PI*(j - ybase)/nb_theta);





void CSol::AfficherCube(float x1, float y1, float z1, float dx, float dy, float dz) const {
                         
  glBegin(GL_LINES); {
    for (int xx = 0; xx <=1; xx++)
      for (int yy = 0; yy <=1; yy++)
        for (int zz = 0;zz <=1; zz++) {
          glVertexTore(x1, y1 + yy*dy, z1 + zz*dz);
          glVertexTore(x1, y1 + yy*dy, z1 + zz*dz);
          
          glVertexTore(x1 + xx*dx, y1, z1 + zz*dz );
          glVertexTore(x1 + xx*dx, y1 + dy, z1 + zz*dz);
          
          glVertexTore(x1 + xx*dx, y1 +yy*dy, z1);
          glVertexTore(x1 + xx*dx, y1 + yy*dy, z1 + dz);
        }
  } glEnd();                        
                         
}


CSol::CSol(const bool EnVaisseau) : ybase(0.0f), nb_texture(0), Z(NULL), PointsEcran(NULL) {
  printf("Constructeur CSol::CSol()\n");

  if (!EnVaisseau) {
    R = 900.0f;
    
    //plus a est petit, moins on voit la compression du tore
    a = (R/3.0f);
  
    nb_phi = ((int)R/4);
    
    nb_theta = (int) (nb_phi/1.618f);
  }
  
  else {
    R = 384.0f;
    a = (R/4.0f);
    nb_phi = 63;
    nb_theta = 31;
  }
 
}

CSol::~CSol() {
     printf("Destruction du sol %p\n", this);         
     delete [] indices_texture;
     delete [] Z;
     delete [] PointsEcran;
}


int CSol::GetTailleX(void) const {
  return TailleX; 
}    


int CSol::GetTailleY() const {
  return TailleY;
}    

#define TEST_X_Y(x, y) ((0<=x) && (x < TailleX) && (0<=y) && (y < TailleY))

void CSol::SETZ(int x, int y, float z) {
    if (TEST_X_Y(x, y))
            Z[(y)*TailleX+(x)] = z;
    else
         printf("ERREUR : Débordement de tableau dans Z avec (%i, %i)\n", x, y);
}


void CSol::SETINDTEXTURE(int x, int y, int ind) {
  if (TEST_X_Y(x, y))
      indices_texture[(y)*TailleX+(x)] = ind;
  else
      printf("ERREUR : Débordement de tableau d'indice de textures en écriture avec (%i, %i)\n", x, y);
}


int CSol::GETINDTEXTURE(int x, int y) const {
   int ii = 0;
  
    if ((0<=x) && (x < TailleX) && (0<=y) && (y < TailleY)) 
        ii = indices_texture[(y)*TailleX+(x)];
    else
      printf("ERREUR : Débordement de tableau d'indice de textures en lecture avec (%i, %i)\n", x, y);
      
      
  return ii;
}


float CSol::GETZ(float x, float y) const {
  /*x dans [0, nb_phi], y dans [0, nb_theta]*/
  /*on fait une interpolation pour connaître l'altitude (en fait, elle n'est connue que sur un maillage)*/
  
  PositionModulo(x, y);
  int ix = (int) floor(x);
  int iy = (int) floor(y);
  
  float lx = x - ix;
  float ly = y - iy;
  
#if 0
#define ZZ(ind) ((((ind) >= 0) && ((ind) < (TailleX+1)*(TailleY+1))) ? Z[(ind)] : 0)
  float z00 = ZZ(iy*TailleX+ix);
  float z10 = ZZ(iy*TailleX+ix+1);
  float z01 = ZZ((iy+1)*TailleX+ix);
  float z11 = ZZ((iy+1)*TailleX+ix+1);
#else
#define ZIND(x,y) ((y)*TailleX+(x))
#define ZZ(x,y) (((((x) >= 0) && ((y) >= 0) && ((x) < TailleX) && ((y) < TailleY))) ? Z[(ZIND((x),(y)))] : 0)
  float z00 = ZZ(ix,iy);
  float z10 = ZZ(ix+1,iy);
  float z01 = ZZ(ix,iy+1);
  float z11 = ZZ(ix+1,iy+1);
#endif

  return ((z00 * (1 - lx) + z10 * lx) * (1 - ly) + (z01 *(1 - lx) + z11 * lx) * ly);
}








float CSol::FacteurCompression(float j) const {

  return (R+a*cosf(temps+2*PI*(j - ybase)/nb_theta))/R;

  //return sqrt(sqr(R+a*cosf(t+2*PI*j/nb_theta)) - sqr(a*sinf(t+2*PI*j/nb_theta)) );
}


float CSol::IndiceTemps(float j) const {
  /*renvoie 0 la nuit et 1 quand l'anneau est au zénith*/
  return (1.0f+cosf(temps+2*PI*(j - ybase)/nb_theta))/2.0f;
  //	return sqrt(sqr(R+a*cosf(t+2*PI*j/nb_theta)) - sqr(a*sinf(t+2*PI*j/nb_theta)) );
}


void CSol::glVertexTore(float x, float y, float z) const {
  float cj = cosf(temps+(float) 2*PI*(y - ybase)/nb_theta);
  float sj = sinf(temps+(float) 2*PI*(y - ybase)/nb_theta);

  float ci = cosf((float)2*PI*(x)/nb_phi);
  float si = sinf((float)2*PI*(x)/nb_phi);
	
  glVertex3f((R + (a + z) * cj) * ci, (R + (a + z) * cj) * si, (a + z) * sj); 
}




void CSol::CalcPoints(int i1, int j1, int i2, int j2) const {
  if (PointsEcran == NULL)
    printf("ERREUR: La variable PointsEcran est à NULL. Ce n'est pas normal. Pt un problème dans le .carte. (style un - qui n'est pas -. ... vive Romain!)\n"); 

  for (int j = j1; j<=j2; j++) {
    float cj = cosf(temps+(float) 2*PI*(j - ybase)/nb_theta);
    float sj = sinf(temps+(float)2*PI*(j - ybase)/nb_theta);    

    for (int i = i1; i<=i2; i++) {
      float ci = cosf((float)2*PI*(i)/nb_phi);
      float si = sinf((float)2*PI*(i)/nb_phi);
      
      
      /*
	(R+( a+GETZ((i),(j)) )  *cosf(t+(float)2*PI*(j)/nb_theta) ) * cosf((float)2*PI*(i)/nb_phi)
        (R+( a+GETZ((i),(j)) ) *cosf(t+(float)2*PI*(j)/nb_theta) ) * sinf((float)2*PI*(i)/nb_phi)
        ( a+GETZ((i),(j)) ) *sinf(t+(float)2*PI*(j)/nb_theta) */
      TPoint3D df_theta, df_phi, normal;
      float zsol = GETZ((i),(j));
      df_theta.x = -(R+( a+zsol )*sj ) * ci;
      df_theta.y = -(R+( a+zsol )*sj ) * si;
      df_theta.z =     ( a+zsol )*cj ;
      
      df_phi.x = -(R+( a+zsol )*cj) * si;
      df_phi.y =  (R+( a+zsol )* cj) * ci;
      df_phi.z =  0;
        
      normal = df_theta ^ df_phi;
      
#define TESTINDICEPointsEcran(i) (!((0 <= (i)) & ((i) < (TailleX)*(TailleY))))
          
      if (TESTINDICEPointsEcran(j*TailleX+i))
        printf("ERREUR: Ecriture dans PointsEcran incorrecte (%i, %i) \n", i, j);
      else {
        PointsEcran[j*TailleX+i].normal = normal;
        PointsEcran[j*TailleX+i].pt.x = (R + (a+GETZ((i),(j)) ) *cj) * ci;
        PointsEcran[j*TailleX+i].pt.y = (R + (a+GETZ((i),(j)) ) *cj) * si;
        PointsEcran[j*TailleX+i].pt.z =      (a+GETZ((i),(j)) ) *sj;
      }
    }
  }
}


void CSol::tore(int i,int j) const {

/*
  if (i < 0) i += nb_phi;
  if (j < 0) j += nb_theta;

  if (i >= nb_phi) i -= nb_phi;
  if (j >= nb_theta) j -= nb_theta;*/

  if (TESTINDICEPointsEcran(j*TailleX+i))
    printf("ERREUR : Lecture dans PointsEcran incorrecte (%i, %i)\n ", i, j);

  glNormal3fv((float*) &PointsEcran[j*TailleX+i].normal);
  glVertex3f(PointsEcran[j*TailleX+i].pt.x, 
             PointsEcran[j*TailleX+i].pt.y, 
             PointsEcran[j*TailleX+i].pt.z);
}



void CSol::tore0(int i, int j) const {
  if (i < 0) i += nb_phi;
  if (j < 0) j += nb_theta;

  if (i >= nb_phi) i -= nb_phi;
  if (j >= nb_theta) j -= nb_theta;

  float_cjsj(j);

  float ci = cosf((float)2*PI*(i)/nb_phi);
  float si = sinf((float)2*PI*(i)/nb_phi);
  /*	(R+( a+GETZ((i),(j)) )  *cosf(t+(float)2*PI*(j)/nb_theta) ) * cosf((float)2*PI*(i)/nb_phi)
	(R+( a+GETZ((i),(j)) ) *cosf(t+(float)2*PI*(j)/nb_theta) ) * sinf((float)2*PI*(i)/nb_phi)
	( a+GETZ((i),(j)) ) *sinf(t+(float)2*PI*(j)/nb_theta) */
  TPoint3D df_theta, df_phi, normal;

  df_theta.x = -(R + (a + ZEau) * sj) * ci;
  df_theta.y = -(R + (a + ZEau) * sj) * si;
  df_theta.z =       (a + ZEau) * cj;

  df_phi.x = -(R+( a+ZEau )*cj) * si;
  df_phi.y =  (R+( a+ZEau )* cj ) * ci;
  df_phi.z =  0;

  normal = df_theta ^ df_phi;
  glNormal3fv((float*)&normal);
  glVertex3f((R + (a + ZEau) * cj) * ci, (R + (a + ZEau) * cj) * si, (a + ZEau) *sj);
}



void CSol::PositionModulo(float &i, float &j) const {
  if (i < 0)
    i += nb_phi;
          
  if (i >= nb_phi)
    i -= nb_phi;
          
          
  if (j < 0)
    j += nb_theta;
          
  if (j >= nb_theta)
    j -= nb_theta;
}




void CSol::LookAt(float i, float j, float z) const {
#define theta_vue -0.15f
#define phi_vue 0.0f
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  float_cjsj(j);
  float cjp = cosf(theta_vue+temps+2*PI*(j-ybase)/nb_theta);
  float sjp = sinf(theta_vue+temps+2*PI*(j-ybase)/nb_theta);
	
  float cip = cosf(phi_vue+2*PI*(i)/nb_phi);
  float sip = sinf(phi_vue+2*PI*(i)/nb_phi);
  float ci = cosf(2*PI*(i)/nb_phi);
  float si = sinf(2*PI*(i)/nb_phi);

  z = a+z;
  gluLookAt((R+(z+HauteurCamera) *cjp )*cip, //position de la caméra
	    (R+(z+HauteurCamera) *cjp )*sip,
               (z+HauteurCamera) *sjp,

	    (R+(z) *cj ) * ci, //on regarde le point
	    (R+(z) *cj ) * si,
	    (z) *sj ,

	    -sj*ci+0*(-si), //vecteur qui pointe vers le haut
	    -sj*(si)+0*ci,
	    cj);
}







void CSol::LookAt(float i, float j, float z, float dist, float AngleXY, float AngleZ) const {
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );  
  
  
  TPoint3D p = GetPoint3D(i, j, z); //point que l'on regarde (généralement c'est le héros !!)

  TPoint3D ux = GetPoint3D(i+1.0f, j, z) - p;
  TPoint3D uy = GetPoint3D(i, j+1.0f, z) - p;
  TPoint3D uz = GetPoint3D(i, j, z+1.0f) - p; 
  
  TPoint3D direction_horizontale = cosf(AngleXY) * ux + sinf(AngleXY) * uy;
  
  Normer2(direction_horizontale);
  Normer2(ux);
  Normer2(uy);
  Normer2(uz);
  
  TPoint3D u = GetPoint3D(i, j, z)
                             - dist*(cosf(AngleZ) * direction_horizontale 
                                    + sinf(AngleZ) * uz);
  
  gluLookAt(u.x, //position de la caméra
	        u.y,
	        u.z,
	        
	        p.x, //on regarde le point
	        p.y,
	        p.z,
	        
            uz.x, //vecteur qui pointe vers le haut
            uz.y,
            uz.z);
}



TPoint3D CSol::GetPoint3D(float i, float j, float z) const {
  float_cjsj(j);

  float ci = cosf((float)2*PI*(i)/nb_phi);
  float si = sinf((float)2*PI*(i)/nb_phi);      
         
    return Point3D( (R+( a+z )  *cj) * ci,
	                (R+( a+z ) *cj ) * si, 
	                ( a+z ) *sj
                   );
              
}


void CSol::AjouterTextureSol(const char * s, int indice_dans_bitmap) {
  if (nb_texture >= NB_MAX_TEXTURESOL) {
    printf("   ERREUR: Il y a déjà trop de textures de sol dans la carte.\n");
    return;
  }    
  
  TextureSol[nb_texture] = gestionTexture.prendre(s);
  indices_dans_bitmap[nb_texture] = indice_dans_bitmap;
  
  nb_texture++;
}
  

void CSol::ChargerIndiceTextureBitmap(const char * fichier_bitmap) {
  char * reelfile;
  reelfile = new char[strlen(NIVEAUXDIR) + strlen(fichier_bitmap) + 1];
  strcat(strcpy(reelfile, NIVEAUXDIR), fichier_bitmap);
  fichier_bitmap = reelfile;

  printf("Chargement des zones de textures (fichier %s)...\n", fichier_bitmap);

  SDL_Surface * img;
  img = IMG_Load(fichier_bitmap);
  
  if (img == NULL)
    printf("ERREUR : Impossible de charger le fichier image '%s'...\n", fichier_bitmap);

  if ((img->w != TailleX) || (img->h != TailleY))
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
      for (k = 0; k < nb_texture; k++)
        //if (indices_texture[k] ==  ind_color) break;
        if (indices_dans_bitmap[k] ==  ind_color) break;
      
      //printf("indice de texture en (i = %d ; j = %d) = %i", i, j, k);
      
      
      //if (k<0)
        if (k >= nb_texture) {
          printf("   ERREUR : la couleur %i au pixel (%i, %i) n'est associée à aucune texture.\n", ind_color, i, j);
          k = 0; // le jeu continue à tourner en prenant la texture ° 0 pour ce pixel
        }
        
        // k contient l'indice de texture
        SETINDTEXTURE(i, img->h-1-j, k);
    }
    
  SDL_FreeSurface(img);
  printf("Chargement des indices de textures terminé !! (t'es sur que c ca Fancois ?? euh non...)\n"); 

  delete[] reelfile;
}



void CSol::Render(int i1, int j1, int i2, int j2) const {

  //fprintf(stderr, "RenderSol: I am called\n");
     
#define ARF(i1, TailleX) if (i1 < 0) i1 = 0; else if (i1 >= TailleX-1) i1 = TailleX-2;
  
  ARF(i1, TailleX);
  ARF(i2, TailleX);
  ARF(j1, TailleY);
  ARF(j2, TailleY);   

  
  /* spécification: i1, i2 entre 0 et TailleX-2 */
  
  CalcPoints(i1, j1, i2+1, j2+1);

  //glDisable(GL_DEPTH_TEST) ;
  
  
#define COLOR_Z(i, j) // {float f = 0.5f + GETZ((i), (j))/50.0f; if (f<0.2f) f = 0.2f; if (f>1.0f) f = 1.0f; glColor3f(f,f,f);}
#define ALPHA_ET_BLANC(f) glColor4f(1.0f, 1.0f, 1.0f, f);

/* 
   ALPHATEX(i, j) renvoit 1.0f si la texture de n° numtex s'affiche en (i, j)
   sinon renvoie 0.0f
*/
#define ALPHATEX(i, j) \
 ((GETINDTEXTURE(i, j) == numtex) || (numtex == 0) ? 1.0f : 0.0f)	

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
    for (int numtex = 0; numtex<nb_texture; numtex++)
    {
    // active le canal n° numtex 
    glActiveTextureARB( GL_TEXTURE_ARB(numtex) ); 
    glEnable(GL_TEXTURE_2D);   
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
    glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);
    
    TextureSol[numtex]->getObject()->GLTextureCourante();     
    
    }  
  */        
            
  //glDepthFunc(GL_LEQUAL);
  glEnable(GL_TEXTURE_2D);  

  for (int numtex = 0; numtex < nb_texture; numtex++) { 
    TextureSol[numtex] -> getObject() -> GLTextureCourante();         
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
          tore(x,y);
          
          glColor4f(1.0f, 1.0f, 1.0f, a2);
          glTexCoord2f(1.0f,0.0f);
          tore(x+1,y);
          
          glColor4f(1.0f, 1.0f, 1.0f, a3);
          glTexCoord2f(1.0f,1.0f);
          tore(x+1,y+1);
          
          glColor4f(1.0f, 1.0f, 1.0f, a4);
          glTexCoord2f(0.0f,1.0f);
          tore(x,y+1);
        } glEnd();
      }
    }
  }
  
  //glDepthMask(GL_TRUE);
  
  /*
    for (int numtex = 1; numtex<nb_texture; numtex++)
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
	  TextureSol[GETINDTEXTURE(i, j)] -> getObject() -> GLTextureCourante();
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
  TextureSol -> getObject() -> GLTextureCourante();
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




void CSol::SetTemps(float in_temps) {
  temps = in_temps;
}



float CSol::GetTemps() const {
  return temps;    
}

bool CSol::yatilEau(float i, float j, float z) const {
  return (z < ZEau);
}    

	
void CSol::RenderEau(int i1, int j1, int i2, int j2) const {
  ARF(i1, TailleX);
  ARF(i2, TailleX);
  ARF(j1, TailleY);
  ARF(j2, TailleY);

#define COLOR_EAU(i, j) glColor4f(0.7f,0.7f,1.0f, 0.5f + 0.2f*cos(((i)+(j)+100*temps)/2.0f));
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
          tore0(i,j);

          COLOR_EAU(i+PREC_EAU, j);
          //	glTexCoord2f(0.5f + num_tex*0.5f,0.0f);
          tore0(i+PREC_EAU,j);

#if 0
          //	glTexCoord2f(0.5f + num_tex*0.5f,1.0f);
          COLOR_EAU(i+PREC_EAU, j+PREC_EAU);
          tore0(i+PREC_EAU,j+PREC_EAU);

          //	glTexCoord2f(0.0f + num_tex*0.5f,1.0f);
          COLOR_EAU(i, j+PREC_EAU);
          tore0(i,j+PREC_EAU);
#endif

	}
      } glEnd();
    }
    glColor3f(1.0f,1.0f,1.0f);
  } glEnable(GL_TEXTURE_2D);
}



void CSol::MatricePour2D(float i, float j, float z) const {
  float_cjsj(j);

  float ci = cosf(2*PI*(i)/nb_phi);
  float si = sinf(2*PI*(i)/nb_phi);
         
  glTranslatef( (R + ( a+z )  *cj) *ci, //on place la sprite sur le point du tore
		(R+( a+z) *cj) * si, 
		( a+z ) *sj ) ;

  glRotatef(360.f*(float)(i)/nb_phi,0,0,1) ;
  //on la pivote autour de (Oz)
  
  glRotatef(90.0f-360.f*(temps+2*PI*(float)(j-ybase)/nb_theta)/(2*PI),0,1,0) ;
  //puis on la met par terre	
}



void CSol::MatricePourDessiner(float i, float j) {
  float_cjsj(j);

  float ci = cosf(2*PI*(i)/nb_phi);
  float si = sinf(2*PI*(i)/nb_phi);
  glPushMatrix() ;
         
  glTranslatef( (R + ( a+GETZ(i,j) )  *cj) *ci, //on place la sprite sur le point du tore
		(R+( a+GETZ(i,j) ) *cj) * si, 
		( a+GETZ((i),(j)) ) *sj ) ;

  glRotatef(360.f*(float)(i)/nb_phi,0,0,1) ; //on la pivote autour de (Oz)
  glRotatef(90.0f-360.f*(temps+2*PI*(float)(j-ybase)/nb_theta)/(2*PI),0,1,0) ; //puis on la met par terre	
         

}


void CSol::ChargerZ(const char * filename) {
  char * reelfile;
  reelfile = new char[strlen(NIVEAUXDIR) + strlen(filename) + 1];
  strcat(strcpy(reelfile, NIVEAUXDIR), filename);
  filename = reelfile;

  printf("Chargement du terrain de la carte...\n");
  SDL_Surface * img;
  img = IMG_Load (filename);

  if (img == NULL)
    printf("ERREUR : Impossible de charger le fichier image '%s' (ce fichier contient les Z du terrain)\n",filename);

  int bpp = img->format->BytesPerPixel;
  
  if (bpp != 1)
    printf("WARNING: L'image '%s' doit être dans un format niveau de gris. Elle représente les Z de la carte\n.", filename);     
  
  
  uint8_t * p8 = (uint8_t *) img -> pixels;
  uint32_t * p32 = (uint32_t *) img -> pixels;

  TailleX = img->w;
  TailleY = img->h;
  printf(" ---> on en déduit que la taille de la carte est (%i, %i).\n", TailleX, TailleY); 
     
  Z = new float [(TailleX)*(TailleY)];
  PointsEcran = new TPointEcran[(TailleX)*(TailleY)];
	
  printf("Allocation en mémoire de la table qui à un point de la carte associe l'id de la texture de ce point.\n");
  indices_texture = new int[(TailleX)*(TailleY)];
     
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

      SETZ(i, img->h-1-j,  ((float) valeur - 128.0f) / 1.0f);
    }
  
  printf("On désalloue la mémoire de l'image..\n");   
  SDL_FreeSurface(img);
  printf("Chargement des Z terminés !!\n"); 
  delete[] reelfile;
}


   
TPoint2D CSol::Differentiel(TPoint3D pos) const {
  TPoint2D p;

#define precdiff 0.5f

  float z1 = GETZ(pos.x + precdiff, pos.y) - GETZ(pos.x, pos.y);
  float z2 = GETZ(pos.x, pos.y + precdiff) - GETZ(pos.x, pos.y);

 /* printf("Calcul de différentiel : %f, %f, %f, %f\n", GETZ(pos.x+precdiff, pos.y),
	 GETZ(pos.x, pos.x), GETZ(pos.x, pos.y+precdiff), GETZ(pos.x, pos.y));*/

  p.x = z1; //GETZ(int(rx)+1, int(ry)) - GETZ(int(rx)-1, int(ry));
  p.y = z2;//GETZ(int(rx), int(ry)+1) - GETZ(int(rx), int(ry)-1);

  return p;

}


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
