#include "global.hpp"
#include "menuentreenom.hpp"
#include "text.hpp"


//CMenuEntreeNom* MenuEntreeNom;

CMenuEntreeNom::CMenuEntreeNom(void) : poscur(0) {
  NomSousMenu[0] = strcopy("Commande");
  Add(0, "OK!", "lettres/ok.png");
  Add(0, "Ret. arr.", "lettres/retarr.png"); 
   
  NomSousMenu[1] = strcopy("voyelles");
  Add(1, "a", "lettres/a.png");
  Add(1, "e", "lettres/e.png");                                                  
  Add(1, "i", "lettres/i.png");
  Add(1, "o", "lettres/o.png");
  Add(1, "u", "lettres/u.png");
  Add(1, "y", "lettres/y.png");
   
  NomSousMenu[2] = strcopy("consonnes dentales");
  Add(2, "d", "lettres/d.png");
  Add(2, "t", "lettres/t.png");
  Add(2, "n", "lettres/n.png");
   
  NomSousMenu[3] = strcopy("consonnes sybilantes");
  Add(3, "c", "lettres/c.png");
  Add(3, "s", "lettres/s.png");
  Add(3, "x", "lettres/x.png");
  Add(3, "z", "lettres/z.png");
   
   
  NomSousMenu[4] = strcopy("consonnes gutturales");
  Add(4, "c", "lettres/c.png");
  Add(4, "g", "lettres/g.png");
  Add(4, "k", "lettres/k.png");
  Add(4, "q", "lettres/q.png");
   
   
  NomSousMenu[5] = strcopy("consonnes labiales");
  Add(5, "b", "lettres/b.png");
  Add(5, "p", "lettres/p.png");
  Add(5, "v", "lettres/v.png");
  Add(5, "f", "lettres/f.png");
  Add(5, "w", "lettres/w.png");
   
  NomSousMenu[6] = strcopy("consonnes lamentables");
  Add(6, "h", "lettres/h.png");
  Add(6, "j", "lettres/j.png");
  Add(6, "l", "lettres/l.png");
  Add(6, "m", "lettres/m.png");
  Add(6, "r", "lettres/r.png");
  Add(6, "w", "lettres/w.png");
    
   
   
}


void CMenuEntreeNom::Init()
{
  poscur = 0;  
  buffer[0] = 0;  
  iphi = 1; 
  anim_phi = nb_pas_phi;
                 
}


CMenuEntreeNom::~CMenuEntreeNom()
{
                                
}



void CMenuEntreeNom::RetArr()
{
  poscur--;
  if(poscur < 0)
    {   
      buffer[0] = 0;
      poscur = 0; 
    }  
  buffer[poscur] = 0;      
     
}





bool CMenuEntreeNom::InputAndRender()
{
  if(CMenu::InputAndRender())
    {
      if(Canceled)
        RetArr();
      else
        {                       
          if(iphi == 0)
            {
              if(itheta == 0)
                {   
                  if(poscur > 0)
                    return true;     
                }
              else if(itheta == 1)  
                RetArr(); 
            } 
          else
            {                      
              buffer[poscur] = Items[iphi][itheta].nom[0]; 
              buffer[poscur+1] = 0;
                     
              if(poscur < MAX_LONGUEUR_BUFFER-1)
                poscur++;  
            }     
        }                    
    }
   
  Text->print(0,0,10000,1000,"Mon nom est : ");
  Text->print(230,0,10000,1000,buffer);
   
  return false;                       
}



