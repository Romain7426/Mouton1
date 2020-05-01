#ifndef MENUENTREENOM_H
#define MENUENTREENOM_H
 
#define MAX_LONGUEUR_BUFFER 16

struct CMenuEntreeNom /* : public CMenu */ {
  CMenu parent;
  
  int poscur;
  char buffer[MAX_LONGUEUR_BUFFER];

  void (* RetArr)(struct CMenuEntreeNom * this);
  void (* Init)(struct CMenuEntreeNom * this);
  //bool (* InputAndRender)(struct CMenuEntreeNom * this); 
  int  (* Input)(struct CMenuEntreeNom * this); 
  void (* Life)(struct CMenuEntreeNom * this); 
  void (* Render)(const struct CMenuEntreeNom * this); 
};
extern CMenuEntreeNom * CMenuEntreeNom_make(void);
extern void CMenuEntreeNom_delete(CMenuEntreeNom * this);
  
extern void CMenuEntreeNom__RetArr(struct CMenuEntreeNom * this);
extern void CMenuEntreeNom__Init(struct CMenuEntreeNom * this);
//extern bool CMenuEntreeNom__InputAndRender(struct CMenuEntreeNom * this); 
extern int  CMenuEntreeNom__Input(struct CMenuEntreeNom * this); 
extern void CMenuEntreeNom__Life(struct CMenuEntreeNom * this); 
extern void CMenuEntreeNom__Render(const struct CMenuEntreeNom * this); 


#endif /* MENUENTREENOM */ 
