#include "global.hpp"
#include "pagetitre.hpp"

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


CPageTitre::CPageTitre(void) : Action(ptFADEIN), t(0), fade(0), Ligne_Courante(0.0f) {
  DessineMoiUnMouton = new CTexture("titre/dessine.moi.un.mouton.jpg");
  Titre = new CTexture("titre/titre.png");                     
}


CPageTitre::~CPageTitre(void) {
  delete DessineMoiUnMouton; 
  delete Titre;             
}



bool CPageTitre::Life(void) {
  if (Action == ptFADEIN)
    fade++;
         
  if (Action == ptFADEOUT)
    fade--;
         
  if (fade > NB_ETAPE_FADING) {
    Action = ptTITRE;   
    fade = NB_ETAPE_FADING;
  }

  if (Action == ptTITRE) {
    Ligne_Courante += 0.01f;
  }

  if (KEY_PASSER_TITRE) 
    Action = ptFADEOUT;

  t++;

  return (fade < 0) && (Action == ptFADEOUT);
}


void CPageTitre::Render(void) const {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  
  glDisable(GL_DEPTH_TEST);
  
  glEnable2D(); {

    glEnable(GL_TEXTURE_2D);
    
    float f = (float) fade/NB_ETAPE_FADING;
    glColor3f(f, f, f);
    Titre->GLTextureCourante();
    BEGIN_BLIT_END(200,320,500,150,0.0f, 0.0f, 1.0f, 1.0f);
    
    DessineMoiUnMouton->GLTextureCourante();
    float v = ((float) t)/512.0f;
    BEGIN_BLIT_END(0, 100, SCREEN_WIDTH, 200, 0.0f + v, 0.0f, 1.0f, 1.0f);//t/512.0f, 0.0f, 640.0f/512.0f + t/512.0f, 640.0f);
    
    if (Action == ptTITRE) {
      bool b; //sert à rien :)
      Text->print(Ligne_Courante, 7, 100000, 100, 100, 5000, 300, CHAINE_GENERIQUE, b);
    }
    
  } glDisable2D();           

  glEnable(GL_DEPTH_TEST);
  
}

