#include "global.h"
#include "affichagemainpierre.h"
#include "text.h"
#include "map.h"


static void Render(const struct CAffichageMainPierre * this, const float y, const CMap * Map);
DEFINE_NEW_OPERATOR_FOR_STRUCT1(CAffichageMainPierre,Render);


CAffichageMainPierre * CAffichageMainPierre(void) {
  CAffichageMainPierre * this = new_CAffichageMainPierre();
  this -> main = new CTexture("main.png");   
  this -> pierre = new CTexture("pierre.png");    
}    

void Render(const CAffichageMainPierre * this, const float y, const CMap * Map) {
  #define MAIN_PIERRE_X 550
  #define MAIN_PIERRE_Y 340  
  #define PIERRE_X 30
  #define PIERRE_Y 128-40
  
  #define TAILLE_PIERRE_X 32
  #define TAILLE_PIERRE_Y 32
  
  glEnable2D(); {

    float d = Map -> FacteurCompression(y);  
    pierre -> GLTextureCourante();
    glBegin(GL_QUADS); {
      BLIT(MAIN_PIERRE_X+PIERRE_X-(d*TAILLE_PIERRE_X/4.0f),
           MAIN_PIERRE_Y+PIERRE_Y-(d*TAILLE_PIERRE_Y/3.0f),
           TAILLE_PIERRE_X+(d*TAILLE_PIERRE_X/2.0f),(d * TAILLE_PIERRE_Y),0,0,1,1);     
    } glEnd();
    
    main -> GLTextureCourante();
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS); {
      BLIT(MAIN_PIERRE_X,MAIN_PIERRE_Y,128,128,0,0,1,1); 
    } glEnd();
    
  } glDisable2D();      
    
}

    
CAffichageMainPierre::~CAffichageMainPierre(void) {
  delete main;
  delete pierre;
}



