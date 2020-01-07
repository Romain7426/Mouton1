#include "global.h"
#include "pagetitre.h"

const char * CHAINE_GENERIQUE = 
#if 0
  "Scripts de descriptions des personnages\nRomain (mainmain)\n\n\n"
  "Scripts des bonhommes\nRomain (mainmain)\n\n\n"
  "Scripts des objets\nRomain (mainmain)\n\n\n"
  "Scripts de  descriptions\nRomain (mainmain)\n\n\n"
  "Scripts des cartes\nRomain (mainmain)\n\n\n"
  "Scripts des cartesplans\nFrançois (c'min)\n\n\n"
#endif
  "Scripts \nRomain (mainmain)\n\n\n"
  "Moteur 3D\nFrançois (c'min)\n\n\n"
  "Musiques\nFrançois (c'min)\n\n\n"
  "Objets 3D\nLudovic (Mac Do)\n\n\n"
  "Bonhommes\nPierre\nMathilde (Tilda)\n\n";


CPageTitre * CPageTitre_make(void) {
  MALLOC_BZERO(CPageTitre,this);
  
  ASSIGN_METHOD(CPageTitre,this,Render); 
  ASSIGN_METHOD(CPageTitre,this,Life); 
  
  this -> Action = ptFADEIN; 
  this -> t = 0; 
  this -> fade = 0;
  this -> Ligne_Courante = 0.0f; 
  this -> DessineMoiUnMouton = CTexture_make("titre/dessine.moi.un.mouton.jpg");
  this -> Titre = CTexture_make("titre/titre.png");                     
  return this; 
};


void CPageTitre_delete(CPageTitre * this) {
  CTexture_delete(this -> DessineMoiUnMouton); 
  CTexture_delete(this -> Titre);             
  free(this); 
};



bool CPageTitre__Life(CPageTitre * this) {
  if (this -> Action == ptFADEIN)
    this -> fade++;
         
  if (this -> Action == ptFADEOUT)
    this -> fade--;
         
  if (this -> fade > NB_ETAPE_FADING) {
    this -> Action = ptTITRE;   
    this -> fade = NB_ETAPE_FADING;
  }

  if (this -> Action == ptTITRE) {
    this -> Ligne_Courante += 0.01f;
  }

  if (KEY_PASSER_TITRE) 
    this -> Action = ptFADEOUT;

  this -> t++;

  return (this -> fade < 0) && (this -> Action == ptFADEOUT);
}; 


void CPageTitre__Render(const CPageTitre * this) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  
  glDisable(GL_DEPTH_TEST);
  
  glEnable2D(); {
    glEnable(GL_TEXTURE_2D);
    
    float f = (float) this -> fade/NB_ETAPE_FADING;
    glColor3f(f, f, f);
    this -> Titre -> GLTextureCourante(this -> Titre);
    BEGIN_BLIT_END(200,320,500,150,0.0f, 0.0f, 1.0f, 1.0f);
    
    this -> DessineMoiUnMouton -> GLTextureCourante(this -> DessineMoiUnMouton);
    float v = ((float) this -> t)/512.0f;
    BEGIN_BLIT_END(0, 100, SCREEN_WIDTH, 200, 0.0f + v, 0.0f, 1.0f, 1.0f);//t/512.0f, 0.0f, 640.0f/512.0f + t/512.0f, 640.0f);
    
    if (this -> Action == ptTITRE) {
      bool b; //sert à rien :)
      Text -> print2(Text, this -> Ligne_Courante, 7, 100000, 100, 100, 5000, 300, CHAINE_GENERIQUE, &b);
    };
    
  } glDisable2D();           

  glEnable(GL_DEPTH_TEST);  
};

