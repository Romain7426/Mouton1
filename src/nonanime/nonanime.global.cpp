#include <stdlib.h>
#include "global.hpp"
#include "nonanime/nonanime.global.hpp"


/* On définit toutes fonctions d'allocations de mémoire. */
/*
extern liste* liste_vide(void) {
  return (liste*) NULL;
}

extern liste* mp(void *contenu, liste* l) {
  liste* temp;

  temp = (liste*) malloc(1 * sizeof(struct liste));
  if (temp == NULL) {
    return temp;
  }

  temp->contenu = contenu;
  temp->suivant = l;
  return temp;
}

const extern void raz(liste* *l) {
  liste* temp;
  temp = *l;
  while (temp != NULL) {
    *l = temp->suivant;
    free(temp);
    temp = *l;
  }
}
*/

/*
extern tvecteur* new_vecteur(void) {
  return (tvecteur*) malloc(1 * sizeof(union tvecteur));
}
 
const extern void del_vecteur(tvecteur* *v) {
  free(*v);
  *v = NULL;
}
*/


extern nonanime_tphysique* nonanime_new_physique(void) {
  return (nonanime_tphysique*) malloc(1 * sizeof(struct nonanime_tphysique));
}

const void nonanime_del_physique(nonanime_tphysique* *p) {
  free(*p);
  *p = NULL;
}


extern nonanime_taction* nonanime_new_action(void) {
  return (nonanime_taction*) malloc(1 * sizeof(struct nonanime_taction));
}

const void nonanime_del_action(nonanime_taction* *a) {
  free(*a);
  *a = NULL;
}


extern nonanime_sgenere* nonanime_new_sgenere(void) {
  return (nonanime_sgenere*) malloc(1 * sizeof(struct nonanime_sgenere));
}

const void nonanime_del_sgenere(nonanime_sgenere* *s) {
  free(*s);
  *s = NULL;
}


extern nonanime_tevent* nonanime_new_event(void) {
  return (nonanime_tevent*) malloc(1 * sizeof(struct nonanime_tevent));
}

const void nonanime_del_event(nonanime_tevent* *e) {
  free(*e);
  *e = NULL;
}


extern nonanime_tgameplay* nnonanime_ew_gameplay(void) {
  return (nonanime_tgameplay*) malloc(1 * sizeof(struct nonanime_tgameplay));
}
  
const void nonanime_del_gameplay(nonanime_tgameplay* *g) {
  free(*g);
  *g = NULL;
}

extern nonanime_tfils* nonanime_new_fils(void) {
  return (nonanime_tfils*) malloc(1 * sizeof(struct nonanime_tfils));
}

const void nonanime_del_fils(nonanime_tfils* *f) {
  free(*f);
  *f = NULL;
}


extern nonanime_telement* nonanime_new_element(void) {
  return (nonanime_telement*) malloc(1 * sizeof(struct nonanime_telement));
}

const void del_element(nonanime_telement* *m) {
  free(*m);
  *m = NULL;
}


extern nonanime_tgraphique* nonanime_new_graphique(void) {
  return (nonanime_tgraphique*) malloc(1 * sizeof(struct nonanime_tgraphique));
}

const void nonanime_del_graphique(nonanime_tgraphique* *g) {
  free(*g);
  *g = NULL;
}


extern nonanime_tnonanime* nonanime_new_nonanime(void) {
  return (nonanime_tnonanime*) malloc(1 * sizeof(struct nonanime_tnonanime));
}

const void nonanime_del_nonanime(nonanime_tnonanime* *a) {
  free(*a);
  *a = NULL;
}






nonanime_tcode *nonanime_new_code(void) {
  return (nonanime_tcode*) malloc(1 * sizeof(struct nonanime_tcode));  
}
void nonanime_del_code(nonanime_tcode **c) {
  free(*c);
  *c = NULL;
}

