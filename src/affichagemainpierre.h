#ifndef CAffichageMainPierre_HPP
#define CAffichageMainPierre_HPP

class CTexture;
class CMap;

/*******************************************************************************
 Affichage de la main et de la pierre (qui indique l'heure)
 ******************************************************************************/

class CAffichageMainPierre {
  private:
  CTexture * main;
  CTexture * pierre;
       
  public:
  void Render(const float y, const CMap * Map) const;
  CAffichageMainPierre();
  ~CAffichageMainPierre();
    
};    


#endif

