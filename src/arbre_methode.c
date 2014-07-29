#include "global.h"
#include "arbre.h"
#include "arbre_methode.h"


static char * arbre_to_dotty_aux(const arbre_t * arbre, const char * root_name);
static char * arbre_to_dotty_label(const arbre_t * arbre);




char * arbre_to_dotty(const arbre_t * arbre, const char * dotty_name_base) {
  char * dotty_string;
  char * dotty_string_aux;
  char * root_name;

  assert(not(string_contains_char_huh(dotty_name_base, ')')));
  assert(not(string_contains_char_huh(dotty_name_base, '(')));

  dotty_string = strcopy("");

  stradd4(&dotty_string, "digraph ", dotty_name_base, " {\n");
  //stradd2(&dotty_string, "  rankdir = LR;\n");
  // rotate=90 sets landscape mode.  (orientation=land is backward compatible but obsolete.)
  //stradd2(&dotty_string, "  rotate = 90;\n");

  stradd2(&dotty_string, "  \n");

  root_name = strconcat2(dotty_name_base, "_root");
  dotty_string_aux = arbre_to_dotty_aux(arbre, root_name);
  stradd2(&dotty_string, dotty_string_aux);
  strfree(dotty_string_aux);
  strfree(root_name);

  stradd2(&dotty_string, "  \n");
  
  stradd2(&dotty_string, "}\n");

  return dotty_string;
}





char * arbre_to_dotty_aux(const arbre_t * arbre, const char * root_name) {
  char * dotty_string;
  char * label;

  label = arbre_to_dotty_label(arbre);
  dotty_string = strconcat5("  ", root_name, " [label = \"", label, "\"];\n");
  strfree(label);

  if (arbre_feuille_huh(arbre)) {
    return dotty_string;
  }

  for (int i = 0; i < arbre -> fils_nb; i++) {
    stradd8(&dotty_string, "  ", root_name, " -> ", root_name, "_fils", uint_string(i), ";\n");
  }

  stradd2(&dotty_string, "  \n");

  for (int i = 0; i < arbre -> fils_nb; i++) {
    char * fils_name;
    char * fils_dotty_string;
    fils_name = strconcat3(root_name, "_fils", uint_string(i));
    fils_dotty_string = arbre_to_dotty_aux(arbre -> fils[i], fils_name);
    stradd2(&dotty_string, fils_dotty_string);
    strfree(fils_dotty_string);
    strfree(fils_name);
  }

  stradd2(&dotty_string, "  \n");

  return dotty_string;
}




char * arbre_to_dotty_label(const arbre_t * arbre) {
  char * retour;

  switch (arbre -> type) {
  case ARBRE_NOEUD_CONCATENATION: retour = strcopy("concat"); break;
  case ARBRE_NOEUD_OU: retour = strcopy("ou"); break;
  case ARBRE_NOEUD_ET: retour = strcopy("et"); break;
  case ARBRE_NOEUD_NON: retour = strcopy("!"); break;
  case ARBRE_NOEUD_ETOILE: retour = strcopy("*"); break;
  case ARBRE_NOEUD_PLUS: retour = strcopy("+"); break;
  case ARBRE_NOEUD_01: retour = strcopy("0/1"); break;
  case ARBRE_FEUILLE_LETTRE: retour = char_string_filtre(arbre -> lettre); break;
  case ARBRE_FEUILLE_ANY: retour = strcopy("."); break;
  case ARBRE_NOMBRE: assert(false); /* NOTREACHED */ break;
  default: assert(false); /* NOTREACHED */ break;
  }

  if (arbre_feuille_huh(arbre) && (arbre -> feuille_non_huh)) {
    char * temp;
    temp = retour;
    retour = strconcat2("!", temp);
    strfree(temp);
  }


  return retour;
  /* NOTREACHED */
  /* FALLTHROUGH */
}

