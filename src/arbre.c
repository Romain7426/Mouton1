#include "global.h"
#include "arbre.h"
#include "arbre_liste.h"


static inline arbre_t * arbre_allouer(void);


arbre_t * arbre_allouer(void) {
  return (arbre_t *) malloc((sizeof (arbre_t)));
};



arbre_t * arbre_make_noeud(const arbre_type_t type, const int fils_taille) {
  assert(arbre_type_noeud_huh(type));

  arbre_t * retour;

  retour = arbre_allouer();

  retour -> type = type;
  retour -> fils_nb = 0;
  retour -> fils_taille = fils_taille;
  retour -> fils = (arbre_t * *) malloc(fils_taille * (sizeof (arbre_t *)));

  return retour;
};

void arbre_make_fils_add(arbre_t * arbre, const arbre_t * fils) {
  arbre_make_fils_add_nocopy(arbre, arbre_copy(fils));
}

void arbre_make_fils_add_nocopy(arbre_t * arbre, arbre_t * fils) {
  assert(arbre -> fils_nb < arbre -> fils_taille);
  arbre -> fils[arbre -> fils_nb] = (fils);
  arbre -> fils_nb ++;
}


arbre_t * arbre_make_liste(const arbre_type_t type, const arbre_liste_t * arbre_liste) {
  arbre_t * arbre;
  arbre_liste_t * l;
  l = arbre_liste_copy(arbre_liste);
  arbre = arbre_make_liste_nocopy(type, l);
  arbre_liste_free_nocopy(l);
  return arbre;
}

arbre_t * arbre_make_liste_nocopy(const arbre_type_t type, arbre_liste_t * arbre_liste) {
  arbre_t * arbre;
  arbre = arbre_make_noeud(type, arbre_liste_longueur(arbre_liste));
  while (not(arbre_liste_vide_huh(arbre_liste))) {
    arbre_make_fils_add_nocopy(arbre, arbre_liste -> car);
    arbre_liste = arbre_liste -> cdr;
  }
  return arbre;
}




arbre_t * arbre_make_feuille_lettre(const char lettre, const bool non_huh) {
  arbre_t * retour;

  retour = arbre_allouer();

  retour -> type = ARBRE_FEUILLE_LETTRE;
  retour -> lettre = lettre;
  retour -> feuille_non_huh = non_huh;

  return retour;
};


arbre_t * arbre_make_feuille_any(const bool non_huh) {
  arbre_t * retour;

  retour = arbre_allouer();

  retour -> type = ARBRE_FEUILLE_ANY;
  retour -> feuille_non_huh = non_huh;

  return retour;
};


void arbre_free(arbre_t * arbre) {
  switch (arbre -> type) {
  case ARBRE_NOEUD_CONCATENATION:
  case ARBRE_NOEUD_OU:
  case ARBRE_NOEUD_ET:
  case ARBRE_NOEUD_NON:
  case ARBRE_NOEUD_ETOILE:
  case ARBRE_NOEUD_PLUS:
  case ARBRE_NOEUD_01:
    for (int i = 0; i < arbre -> fils_nb; i++)
      arbre_free(arbre -> fils[i]);
    free(arbre -> fils);
    break;

  case ARBRE_FEUILLE_LETTRE:
  case ARBRE_FEUILLE_ANY:
    break;

  case ARBRE_NOMBRE: assert(false); break;
  default: assert(false); break;
  };
  
  free(arbre);
  
  return;
};


arbre_t * arbre_copy(const arbre_t * arbre) {
  arbre_t * retour;

  if (arbre_noeud_huh(arbre)) {
    retour = arbre_make_noeud(arbre -> type, arbre -> fils_nb);
    for (int i = 0; i < arbre -> fils_nb; i++) {
      arbre_make_fils_add(retour, arbre -> fils[i]);
    }
  }

  else {
    retour = arbre_allouer();
    *retour = *arbre;
  }
    
  return retour;
};



char * arbre_string(const arbre_t * arbre) {
  char * retour;
  char * temp;
  
  retour = strcopy("");
  
  stradd4(&retour, "arbre_t [ type = ", arbre_type_string_tab[arbre -> type], "; ");


  switch (arbre -> type) {
  case ARBRE_NOEUD_CONCATENATION:
  case ARBRE_NOEUD_OU:
  case ARBRE_NOEUD_ET:
  case ARBRE_NOEUD_NON:
  case ARBRE_NOEUD_ETOILE:
  case ARBRE_NOEUD_PLUS:
  case ARBRE_NOEUD_01:
    temp = int_string(arbre -> fils_nb);
    stradd3(&retour, "fils_nb = ", temp);
    strfree(temp);

    for (int i = 0; i < arbre -> fils_nb; i++) {
      temp = int_string(i);
      stradd4(&retour, ", fils{", temp, "} = ");
      strfree(temp);

      temp = arbre_string(arbre -> fils[i]);
      stradd2(&retour, temp);
      strfree(temp);
    }
    break;

  case ARBRE_FEUILLE_LETTRE:
    temp = char_string(arbre -> lettre);
    stradd4(&retour, "lettre = ", temp, ", ");
    strfree(temp);
  case ARBRE_FEUILLE_ANY:
    temp = bool_string(arbre -> feuille_non_huh);
    stradd3(&retour, "feuille_non_huh = ", temp);
    strfree(temp);
    break;

  case ARBRE_NOMBRE: assert(false); break;
  default: assert(false); break;
  };
  
  stradd2(&retour, "]");
  
  return retour;
};




bool arbre_equal(const arbre_t * arbre1, const arbre_t * arbre2) {
  bool b;
  
  b = (arbre1 -> type == arbre2 -> type);
  
  if (not(b)) return false;
  

  //assert(true == b);

  
  switch (arbre1 -> type) {
  case ARBRE_NOEUD_CONCATENATION:
  case ARBRE_NOEUD_OU:
  case ARBRE_NOEUD_ET:
  case ARBRE_NOEUD_NON:
  case ARBRE_NOEUD_ETOILE:
  case ARBRE_NOEUD_PLUS:
  case ARBRE_NOEUD_01:
    if (arbre1 -> fils_nb != arbre2 -> fils_nb) 
      return false;

    for (int i = 0; i < arbre1 -> fils_nb; i++)
      if (not(arbre_equal(arbre1 -> fils[i], arbre2 -> fils[i])))
        return false;

    return true;
    break;

  case ARBRE_FEUILLE_LETTRE:
    b = (arbre1 -> lettre == arbre2 -> lettre);
  case ARBRE_FEUILLE_ANY:
    b = b && (arbre1 -> feuille_non_huh == arbre2 -> feuille_non_huh);
    return b;
    break;

  case ARBRE_NOMBRE: assert(false); break;
  default: assert(false); break;
  };

  assert(false);
  return false;
};







char * arbre_type_string(const arbre_type_t arbre_type) {
  return strcopy(arbre_type_string_tab[arbre_type]);
};

const char * arbre_type_string_const(const arbre_type_t arbre_type) {
  return (arbre_type_string_tab[arbre_type]);
};

const char * arbre_type_string_tab[ARBRE_NOMBRE+1] = {
  "ARBRE_NOEUD_CONCATENATION",
  "ARBRE_NOEUD_OU",
  "ARBRE_NOEUD_ET",
  "ARBRE_NOEUD_NON",
  "ARBRE_NOEUD_ETOILE",
  "ARBRE_NOEUD_PLUS",
  "ARBRE_NOEUD_01",
  "ARBRE_FEUILLE_LETTRE",
  "ARBRE_FEUILLE_ANY",
  "ARBRE_NOMBRE"
};


static void arbre_type_string_tab_check(void) {
  assert(strequal(arbre_type_string_tab[ARBRE_NOMBRE], "ARBRE_NOMBRE"));
}

#if 0
static void dummy(void) {
  //strequal …
  {static int tab[(arbre_type_string_tab[ARBRE_NOMBRE] == "ARBRE_NOMBRE") ? 1:-2];}
  //  {static int tab[(arbre_type_string_tab[ARBRE_NOMBRE] == "ARBRE_NOMBRE") ? 1:-2] = {0};}
}
#endif

#if 0
#if arbre_type_string_tab[ARBRE_NOMBRE] != "ARBRE_NOMBRE"
#error "WAAAAAAA"
#else
#error "BBBB"
#endif
#endif





bool arbre_type_feuille_huh(const arbre_type_t arbre_type) {
  bool b;

  switch (arbre_type) {
  case ARBRE_NOEUD_CONCATENATION: /* FALLTHROUGH */
  case ARBRE_NOEUD_OU: /* FALLTHROUGH */
  case ARBRE_NOEUD_ET: /* FALLTHROUGH */
  case ARBRE_NOEUD_NON: /* FALLTHROUGH */
  case ARBRE_NOEUD_ETOILE: /* FALLTHROUGH */
  case ARBRE_NOEUD_PLUS: /* FALLTHROUGH */
  case ARBRE_NOEUD_01: /* FALLTHROUGH */ 
    b = false;
    break;
  case ARBRE_FEUILLE_LETTRE: /* FALLTHROUGH */
  case ARBRE_FEUILLE_ANY: /* FALLTHROUGH */ 
    b = true;
    break;
  case ARBRE_NOMBRE: assert(false); break;
  default: assert(false); break;
  }

  return b;
}

bool arbre_type_noeud_huh(const arbre_type_t arbre_type) {
  return not(arbre_type_feuille_huh(arbre_type));
}


bool arbre_feuille_huh(const arbre_t * arbre) {
  return arbre_type_feuille_huh(arbre -> type);
}

bool arbre_noeud_huh(const arbre_t * arbre) {
  return arbre_type_noeud_huh(arbre -> type);
}

