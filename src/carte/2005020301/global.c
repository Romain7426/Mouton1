#include <stdlib.h>
#include "global.h"


/* On définit toutes fonctions d'allocations de mémoire. */
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

const extern ttexture new_texture(void) {
  return (ttexture) malloc(1 * sizeof(struct ttexture));
}

const extern void del_texture(ttexture *f) {
  free(*f);
  *f = NULL;
}


const extern tobjet new_objet(void) {
  return (tobjet) malloc(1 * sizeof(struct tobjet));
}

const extern void del_objet(tobjet *m) {
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


const extern tcarte new_carte(void) {
  return (tcarte) malloc(1 * sizeof(struct tcarte));
}

const extern void del_carte(tcarte *a) {
  free(*a);
  *a = NULL;
}






