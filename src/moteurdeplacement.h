#ifndef ORDRESDEPLACEMENT_H
#define ORDRESDEPLACEMENT_H

struct COrdresDeplacement {
  void (* AjouterOrdreDeplacement)(struct COrdresDeplacement * this, TPoint3D pos);
  void (* AppliquerOrdresA)(struct COrdresDeplacement * this, struct CBonhomme * b);
};

extern COrdresDeplacement * COrdresDeplacement_make(void);
extern void COrdresDeplacement_delete(COrdresDeplacement * this);
extern void COrdresDeplacement__AjouterOrdreDeplacement(COrdresDeplacement * this, TPoint3D pos);
extern void COrdresDeplacement__AppliquerOrdresA(COrdresDeplacement * this, CBonhomme * b);
  

#endif /* ORDRESDEPLACEMENT_H */ 
