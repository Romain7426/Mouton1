#include <stdlib.h>
#include <stdarg.h>
#include "global.hpp"
#include "carte/carte.global.hpp"


// Les fonctions de messages
void carte_mess(const char * mess, ...) {
  va_list args;
  
  va_start(args, mess);
  /*
  if (args == NULL) {
    fprintf(yycarteout, "NULL");
  }
  else {
    fprintf(yycarteout, args);
  }
  */
  vmessage(mess, args);
  va_end(args);
  va_start(args, mess);
  (void) vfprintf(yycarteout, mess, args);
  (void) fprintf(yycarteout, "\n");
  va_end(args);
}

void carte_err(const char * mess, ...) {
  va_list args;
  
  va_start(args, mess);
  vmesserr(mess, args);
  va_end(args);
  va_start(args, mess);
  (void) vfprintf(yycarteout, mess, args);
  (void) fprintf(yycarteout, "\n");
  va_end(args);
}
       





// On définit toutes fonctions d'allocations de mémoire.
/*
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
*/

/*
const extern tvecteur new_vecteur(void) {
  return (tvecteur) malloc(1 * sizeof(union tvecteur));
}
 
const extern void del_vecteur(tvecteur *v) {
  free(*v);
  *v = NULL;
}
*/

const carte_tphysique* carte_new_physique(void) {
  return (carte_tphysique*) malloc(1 * sizeof(struct carte_tphysique));
}

const void carte_del_physique(carte_tphysique* *p) {
  free(*p);
  *p = NULL;
}


carte_sgenere* carte_new_sgenere(void) {
  return (carte_sgenere*) malloc(1 * sizeof(struct carte_sgenere));
}

const void carte_del_sgenere(carte_sgenere* *s) {
  free(*s);
  *s = NULL;
}

  
carte_tevent* carte_new_event(void) {
  return (carte_tevent*) malloc(1 * sizeof(struct carte_tevent));
}

const void carte_del_event(carte_tevent* *e) {
  free(*e);
  *e = NULL;
}


const carte_tgameplay* carte_new_gameplay(void) {
  return (carte_tgameplay*) malloc(1 * sizeof(struct carte_tgameplay));
}
  
const void carte_del_gameplay(carte_tgameplay* *g) {
  free(*g);
  *g = NULL;
}

const carte_ttexture* carte_new_texture(void) {
  return (carte_ttexture*) malloc(1 * sizeof(struct carte_ttexture));
}

const void carte_del_texture(carte_ttexture* *f) {
  free(*f);
  *f = NULL;
}


const carte_tobjet* carte_new_objet(void) {
  return (carte_tobjet*) malloc(1 * sizeof(struct carte_tobjet));
}

const void carte_del_objet(carte_tobjet* *m) {
  free(*m);
  *m = NULL;
}


const carte_tgraphique* carte_new_graphique(void) {
  return (carte_tgraphique*) malloc(1 * sizeof(struct carte_tgraphique));
}

const void carte_del_graphique(carte_tgraphique* *g) {
  free(*g);
  *g = NULL;
}


const carte_tcarte* carte_new_carte(void) {
  return (carte_tcarte*) malloc(1 * sizeof(struct carte_tcarte));
}

const void carte_del_carte(carte_tcarte * *a) {
  free(*a);
  *a = NULL;
}

carte_tcode * carte_new_code(void) {
  return (carte_tcode *) malloc(1 * sizeof(struct carte_tcode));
}  
 
void carte_del_code(carte_tcode *(&code)) {
  free(code);
  code = NULL;
}






