#ifndef ARBRE_H
#define ARBRE_H


//typedef struct arbre_t arbre_t;
typedef enum arbre_type_t arbre_type_t;


enum arbre_type_t {
  ARBRE_NOEUD_CONCATENATION,
  ARBRE_NOEUD_OU,
  ARBRE_NOEUD_ET,
  ARBRE_NOEUD_NON,
  ARBRE_NOEUD_ETOILE,
  ARBRE_NOEUD_PLUS,
  ARBRE_NOEUD_01,
  ARBRE_FEUILLE_LETTRE,
  ARBRE_FEUILLE_ANY,
  ARBRE_NOMBRE
};

struct arbre_t {
  arbre_type_t type;
  arbre_t * * fils;
  int fils_nb;
  int fils_taille;
  char lettre;
  bool feuille_non_huh;
};




extern const char * arbre_type_string_tab[ARBRE_NOMBRE+1];

extern char * arbre_type_string(const arbre_type_t arbre_type);
extern const char * arbre_type_string_const(const arbre_type_t arbre_type);
extern bool arbre_type_feuille_huh(const arbre_type_t arbre_type);
extern bool arbre_type_noeud_huh(const arbre_type_t arbre_type);
extern bool arbre_feuille_huh(const arbre_t * arbre);
extern bool arbre_noeud_huh(const arbre_t * arbre);



//extern arbre_t * arbre_make_noeud(arbre_type_t type, arbre_t * fils, ...);
extern arbre_t * arbre_make_noeud(const arbre_type_t type, const int fils_nb);
extern void arbre_make_fils_add(arbre_t * arbre, const arbre_t * fils);
extern void arbre_make_fils_add_nocopy(arbre_t * arbre, arbre_t * fils);
extern arbre_t * arbre_make_liste(const arbre_type_t type, const arbre_liste_t * arbre_liste);
extern arbre_t * arbre_make_liste_nocopy(const arbre_type_t type, arbre_liste_t * arbre_liste);
extern arbre_t * arbre_make_feuille_lettre(const char lettre, const bool non_huh);
extern arbre_t * arbre_make_feuille_any(const bool non_huh);
extern void arbre_free(arbre_t * arbre);
extern arbre_t * arbre_copy(const arbre_t * arbre);
extern char * arbre_string(const arbre_t * arbre);
extern bool arbre_equal(const arbre_t * arbre1, const arbre_t * arbre2);






#if 0 // How to code a function using type 'arbre'

void arbre_fun(const arbre_t * arbre) {

  switch (arbre -> type) {
  case ARBRE_NOEUD_CONCATENATION: do; break;
  case ARBRE_NOEUD_OU: do; break;
  case ARBRE_NOEUD_ET: do; break;
  case ARBRE_NOEUD_NON: do; break;
  case ARBRE_NOEUD_ETOILE: do; break;
  case ARBRE_NOEUD_PLUS: do; break;
  case ARBRE_NOEUD_01: do; break;
  case ARBRE_FEUILLE_LETTRE: do; break;
  case ARBRE_FEUILLE_ANY: do; break;
  case ARBRE_NOMBRE: assert(false); break;
  default: assert(false); break;
  }



  for (int i = 0; i < arbre -> fils_nb; i++) {
    do;
  }

}

  /* NOTREACHED */
  /* FALLTHROUGH */

#endif




#endif /* ARBRE_H */

