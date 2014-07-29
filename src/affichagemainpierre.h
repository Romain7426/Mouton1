#ifndef CAffichageMainPierre_H
#define CAffichageMainPierre_H

struct CTexture;
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CTexture);

struct CMap;
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CMap);

/*******************************************************************************
 Affichage de la main et de la pierre (qui indique l'heure)
 ******************************************************************************/

struct CAffichageMainPierre {
  //private:
  CTexture * main;
  CTexture * pierre;
       
  //public:
  void (* Render)(const struct CAffichageMainPierre * this, const float y, const CMap * Map);
};    
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CAffichageMainPierre);
DECLARE_NEW_OPERATOR_FOR_STRUCT(CAffichageMainPierre);



#endif

