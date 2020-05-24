#include "global.h"
#include "affichagemainpierre.h"
#include "text.h"
#include "map.h"




static CAffichageMainPierre * CAffichageMainPierre_set_attributs(CAffichageMainPierre * this) {
  this -> main   = CTexture_make("main.png");   
  this -> pierre = CTexture_make("pierre.png");    
  this -> Render = CAffichageMainPierre__Render; 
  return this; 
}; 
 
CAffichageMainPierre * CAffichageMainPierre_make(void) {
  CAffichageMainPierre * this = (CAffichageMainPierre *) malloc(sizeof(CAffichageMainPierre)); 
  return CAffichageMainPierre_set_attributs(this); 
}; 


void CAffichageMainPierre__Render(const CAffichageMainPierre * this, const float y, const float FacteurCompression) { //const CMap * Map) { 
#if 0 
  { 
    int * a = NULL; 
    *a = 1; 
  }; 
#endif 
  #define MAIN_PIERRE_X 550
  #define MAIN_PIERRE_Y 340  
  #define PIERRE_X 30
  #define PIERRE_Y 128-40
  
  #define TAILLE_PIERRE_X 32
  #define TAILLE_PIERRE_Y 32
  
  glEnable2D(); {
    //const float d = Map -> parent.FacteurCompression(&Map -> parent, y);  
    const float d = FacteurCompression; 
    this -> pierre -> GLTextureCourante(this -> pierre);
    glBegin(GL_QUADS); {
      BLIT(MAIN_PIERRE_X+PIERRE_X-(d*TAILLE_PIERRE_X/4.0f),
           MAIN_PIERRE_Y+PIERRE_Y-(d*TAILLE_PIERRE_Y/3.0f),
           TAILLE_PIERRE_X+(d*TAILLE_PIERRE_X/2.0f),(d * TAILLE_PIERRE_Y),0,0,1,1);     
    } glEnd();
    
    this -> main -> GLTextureCourante(this -> main);
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS); {
      BLIT(MAIN_PIERRE_X,MAIN_PIERRE_Y,128,128,0,0,1,1); 
    } glEnd();
    
  } glDisable2D();          
}; 

    
void CAffichageMainPierre_delete(CAffichageMainPierre * this) {
  CTexture_delete(this -> main);
  CTexture_delete(this -> pierre);
  free(this); 
}



