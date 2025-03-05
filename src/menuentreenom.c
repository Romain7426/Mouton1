#include "global.h"
#include "menuentreenom.h"
#include "text.h"


//CMenuEntreeNom* MenuEntreeNom;

CMenuEntreeNom * CMenuEntreeNom_make(void) {
  MALLOC_BZERO(CMenuEntreeNom,this);
  
  CMenu * parent = &this -> parent; 
  CMenuAbstrait * parent_parent = &this -> parent.parent; 
  CMenu_make_aux(parent); 
  
  ASSIGN_METHOD(CMenuEntreeNom,this,RetArr); 
  ASSIGN_METHOD(CMenuEntreeNom,this,Init); 
  //ASSIGN_METHOD(CMenuEntreeNom,this,InputAndRender); 
  ASSIGN_METHOD(CMenuEntreeNom,this,Input); 
  ASSIGN_METHOD(CMenuEntreeNom,this,Render); 
  ASSIGN_METHOD(CMenuEntreeNom,this,Life); 

  this -> poscur = 0; 
  
  parent_parent -> NomSousMenu[0] = strcopy_malloc("Commande");
  parent_parent -> Add(parent_parent, 0, "OK!", "lettres/ok.png");
  parent_parent -> Add(parent_parent, 0, "Ret. arr.", "lettres/retarr.png"); 
   
  parent_parent -> NomSousMenu[1] = strcopy_malloc("voyelles");
  parent_parent -> Add(parent_parent, 1, "a", "lettres/a.png");
  parent_parent -> Add(parent_parent, 1, "e", "lettres/e.png");                                                  
  parent_parent -> Add(parent_parent, 1, "i", "lettres/i.png");
  parent_parent -> Add(parent_parent, 1, "o", "lettres/o.png");
  parent_parent -> Add(parent_parent, 1, "u", "lettres/u.png");
  parent_parent -> Add(parent_parent, 1, "y", "lettres/y.png");
   
  parent_parent -> NomSousMenu[2] = strcopy_malloc("consonnes dentales");
  parent_parent -> Add(parent_parent, 2, "d", "lettres/d.png");
  parent_parent -> Add(parent_parent, 2, "t", "lettres/t.png");
  parent_parent -> Add(parent_parent, 2, "n", "lettres/n.png");
   
  parent_parent -> NomSousMenu[3] = strcopy_malloc("consonnes sybilantes");
  parent_parent -> Add(parent_parent, 3, "c", "lettres/c.png");
  parent_parent -> Add(parent_parent, 3, "s", "lettres/s.png");
  parent_parent -> Add(parent_parent, 3, "x", "lettres/x.png");
  parent_parent -> Add(parent_parent, 3, "z", "lettres/z.png");
  
  parent_parent -> NomSousMenu[4] = strcopy_malloc("consonnes gutturales");
  parent_parent -> Add(parent_parent, 4, "c", "lettres/c.png");
  parent_parent -> Add(parent_parent, 4, "g", "lettres/g.png");
  parent_parent -> Add(parent_parent, 4, "k", "lettres/k.png");
  parent_parent -> Add(parent_parent, 4, "q", "lettres/q.png");
  
  parent_parent -> NomSousMenu[5] = strcopy_malloc("consonnes labiales");
  parent_parent -> Add(parent_parent, 5, "b", "lettres/b.png");
  parent_parent -> Add(parent_parent, 5, "p", "lettres/p.png");
  parent_parent -> Add(parent_parent, 5, "v", "lettres/v.png");
  parent_parent -> Add(parent_parent, 5, "f", "lettres/f.png");
  parent_parent -> Add(parent_parent, 5, "w", "lettres/w.png");
   
  parent_parent -> NomSousMenu[6] = strcopy_malloc("consonnes lamentables");
  parent_parent -> Add(parent_parent, 6, "h", "lettres/h.png");
  parent_parent -> Add(parent_parent, 6, "j", "lettres/j.png");
  parent_parent -> Add(parent_parent, 6, "l", "lettres/l.png");
  parent_parent -> Add(parent_parent, 6, "m", "lettres/m.png");
  parent_parent -> Add(parent_parent, 6, "r", "lettres/r.png");
  parent_parent -> Add(parent_parent, 6, "w", "lettres/w.png");

  return this; 
}; 

void CMenuEntreeNom_delete(CMenuEntreeNom * this) {
  CMenu_delete_aux(&this -> parent); 
  free(this); 
}; 

void CMenuEntreeNom__Init(CMenuEntreeNom * this) {
  CMenu * parent = &this -> parent; 
  CMenuAbstrait * parent_parent = &this -> parent.parent; 
  this -> poscur = 0;  
  this -> buffer[0] = 0;  
  parent_parent -> iphi = 1; 
  parent_parent -> anim_phi = nb_pas_phi;
}; 

void CMenuEntreeNom__RetArr(CMenuEntreeNom * this) {
  this -> poscur--;
  if (this -> poscur < 0) {   
    this -> buffer[0] = 0;
    this -> poscur = 0; 
  }; 
  this -> buffer[this -> poscur] = 0;      
}; 


//bool CMenuEntreeNom__InputAndRender(CMenuEntreeNom * this) {
int CMenuEntreeNom__Input(CMenuEntreeNom * this) { 
  CMenu * parent = &this -> parent; 
  CMenuAbstrait * parent_parent = &this -> parent.parent; 

  if (parent -> Input(parent)) { 
    if (parent_parent -> Canceled)
      this -> RetArr(this);
    else {                       
      if (parent_parent -> iphi == 0) {
	if (parent_parent -> itheta == 0) {   
	  if (this -> poscur > 0)
	    return true;     
	}
	else if (parent_parent -> itheta == 1)  
	  this -> RetArr(this); 
      } 
      else {                      
	this -> buffer[this -> poscur] = parent_parent -> Items[parent_parent -> iphi][parent_parent -> itheta].nom[0]; 
	this -> buffer[this -> poscur+1] = 0;
        
	if (this -> poscur < MAX_LONGUEUR_BUFFER-1)
	  this -> poscur++;  
      } 
    } 
  }; 
  
  return false;                       
}; 

void CMenuEntreeNom__Life(CMenuEntreeNom * this) {   
  CMenu * parent = &this -> parent; 
  parent -> Life(parent); 
};

void CMenuEntreeNom__Render(const CMenuEntreeNom * this) {   
  const CMenu * parent = &this -> parent; 
  parent -> Render(parent); 
  Text -> print1(Text,0,0,10000,1000,"Mon nom est : ");
  Text -> print1(Text,230,0,10000,1000,this -> buffer);
};



