#include <stdlib.h>
#include "global.h"


/* On d�finit toutes fonctions d'allocations de m�moire. */
const extern liste liste_vide(void) {
  return (liste) NULL;
}

const extern liste mp(void *contenu, liste l) {
  liste temp;

  temp = (liste) malloc(1 * sizeof(struct liste));
  if (temp == NULL) {
    return temp;
  }

  temp->contenu = contenu;
  temp->suivant = l;
  return temp;
}

const extern void raz(liste *l) {
  liste temp;
  temp = *l;
  while (temp != NULL) {
    *l = temp->suivant;
    free(temp);
    temp = *l;
  }
}



const extern tvecteur new_vecteur(void) {
  return (tvecteur) malloc(1 * sizeof(union tvecteur));
}
 
const extern void del_vecteur(tvecteur *v) {
  free(*v);
  *v = NULL;
}


const extern tphysique new_physique(void) {
  return (tphysique) malloc(1 * sizeof(struct tphysique));
}

const extern void del_physique(tphysique *p) {
  free(*p);
  *p = NULL;
}


const extern taction new_action(void) {
  return (taction) malloc(1 * sizeof(struct taction));
}

const extern void del_action(taction *a) {
  free(*a);
  *a = NULL;
}


const extern sgenere new_sgenere(void) {
  return (sgenere) malloc(1 * sizeof(struct sgenere));
}

const extern void del_sgenere(sgenere *s) {
  free(*s);
  *s = NULL;
}

  
const extern tevent new_event(void) {
  return (tevent) malloc(1 * sizeof(struct tevent));
}

const extern void del_event(tevent *e) {
  free(*e);
  *e = NULL;
}


const extern tgameplay new_gameplay(void) {
  return (tgameplay) malloc(1 * sizeof(struct tgameplay));
}
  
const extern void del_gameplay(tgameplay *g) {
  free(*g);
  *g = NULL;
}

const extern tfils new_fils(void) {
  return (tfils) malloc(1 * sizeof(struct tfils));
}

const extern void del_fils(tfils *f) {
  free(*f);
  *f = NULL;
}


const extern telement new_element(void) {
  return (telement) malloc(1 * sizeof(struct telement));
}

const extern void del_element(telement *m) {
  free(*m);
  *m = NULL;
}


const extern tgraphique new_graphique(void) {
  return (tgraphique) malloc(1 * sizeof(struct tgraphique));
}

const extern void del_graphique(tgraphique *g) {
  free(*g);
  *g = NULL;
}


const extern tnonanime new_nonanime(void) {
  return (tnonanime) malloc(1 * sizeof(struct tnonanime));
}

const extern void del_nonanime(tnonanime *a) {
  free(*a);
  *a = NULL;
}





