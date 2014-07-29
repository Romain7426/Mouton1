#include <stdlib.h>
#include "global.hpp"
#include "anime/anime.global.hpp"


/* On définit toutes fonctions d'allocations de mémoire. */
liste *liste_vide(void) {
  return (liste*) NULL;
}

liste *mp(void *contenu, liste *l) {
  liste *temp;

  temp = (liste*) malloc(1 * sizeof(struct liste));
  if (temp == NULL) {
    return temp;
  }

  temp->contenu = contenu;
  temp->suivant = l;
  return temp;
}

void raz(liste* *l) {
  liste *temp;
  temp = *l;
  while (temp != NULL) {
    *l = temp->suivant;
    free(temp);
    temp = *l;
  }
}



tvecteur* new_vecteur(void) {
  return (tvecteur*) malloc(1 * sizeof(union tvecteur));
}
 
void del_vecteur(tvecteur* *v) {
  free(*v);
}


anime_taction *anime_new_action(void) {
  return (anime_taction*) malloc(1 * sizeof(struct anime_taction));
}

void anime_del_action(anime_taction *a) {
  free(a);
}


anime_sgenere* anime_new_sgenere(void) {
  return (anime_sgenere*) malloc(1 * sizeof(struct anime_sgenere));
}

void anime_del_sgenere(anime_sgenere *s) {
  free(s);
}

  
anime_tevent* anime_new_event(void) {
  return (anime_tevent*) malloc(1 * sizeof(struct anime_tevent));
}

void anime_del_event(anime_tevent *e) {
  free(e);
}


anime_tfils* anime_new_fils(void) {
  return (anime_tfils*) malloc(1 * sizeof(struct anime_tfils));
}

void anime_del_fils(anime_tfils *f) {
  free(f);
}


anime_tmembre* anime_new_membre(void) {
  return (anime_tmembre*) malloc(1 * sizeof(struct anime_tmembre));
}

void anime_del_membre(anime_tmembre *m) {
  free(m);
}



anime_tcode *anime_new_code(void) {
  return (anime_tcode*) malloc(1 * sizeof(struct anime_tcode));  
}
void anime_del_code(anime_tcode **c) {
  free(*c);
  *c = NULL;
}






