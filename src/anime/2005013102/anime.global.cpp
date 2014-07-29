#include <stdlib.h>
#include "anime.global.hpp"


/* On définit toutes fonctions d'allocations de mémoire. */
extern liste *liste_vide(void) {
  return (liste*) NULL;
}

extern liste *mp(void *contenu, liste *l) {
  liste *temp;

  temp = (liste*) malloc(1 * sizeof(struct liste));
  if (temp == NULL) {
    return temp;
  }

  temp->contenu = contenu;
  temp->suivant = l;
  return temp;
}

extern void raz(liste *l) {
  liste *temp;
  temp = l;
  while (temp != NULL) {
    l = temp->suivant;
    free(temp);
    temp = l;
  }
}



extern tvecteur* new_vecteur(void) {
  return (tvecteur*) malloc(1 * sizeof(union tvecteur));
}
 
extern void del_vecteur(tvecteur *v) {
  free(v);
}


extern taction *new_action(void) {
  return (taction*) malloc(1 * sizeof(struct taction));
}

extern void del_action(taction *a) {
  free(a);
}


extern sgenere* new_sgenere(void) {
  return (sgenere*) malloc(1 * sizeof(struct sgenere));
}

extern void del_sgenere(sgenere *s) {
  free(s);
}

  
extern tevent* new_event(void) {
  return (tevent*) malloc(1 * sizeof(struct tevent));
}

extern void del_event(tevent *e) {
  free(e);
}


extern tfils* new_fils(void) {
  return (tfils*) malloc(1 * sizeof(struct tfils));
}

extern void del_fils(tfils *f) {
  free(f);
}


extern tmembre* new_membre(void) {
  return (tmembre*) malloc(1 * sizeof(struct tmembre));
}

extern void del_membre(tmembre *m) {
  free(m);
}








