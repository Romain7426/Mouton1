#include "global.h"
#include "test.h"
#include "arbre.h"
#include "arbre_methode.h"
#include "automate.h"
#include "automate_methode.h"
#include "compilation.h"
#include "token.h"
#include "token_liste.h"
#include "parser.h"
#include "lexer.h"


static void parser_test(void);

static void arbre_test(void);

static void automate_test(void);
static void automate_test_commentaire_c_multiligne(const automate_t * automate);
static void automate_function_test_commentaire_c_multiligne(bool automate_function(const char * mot));
static bool automate_d_fin_c_function_mot_reconnu_huh(const char * mot);
//static bool automate_d_fin_c_function_mot_reconnu_huh2(const char * mot);

static void compilation_test(void);

static void automate_show_with_dotty(const automate_t * automate, const char * automate_name);
#define AUTOMATE_SHOW(a) automate_show_with_dotty((a),(BIGLIB_STRING(a)))

static void arbre_show_with_dotty(const arbre_t * arbre, const char * arbre_name);
#define ARBRE_SHOW(a) arbre_show_with_dotty((a),(BIGLIB_STRING(a)))



void test(void) {

  printf("yo\n");

  token_liste_t * tokens;
  char * err;
  bool pas_erreur;

  tokens = lex("/\\*!(.*\\*/.*)\\*/", &pas_erreur, &err);
  if (not(pas_erreur)) {
    printf("Analyse lexicale ratée: %s\n", err);
    return;
  }
  
  printf("tokens = %s\n", token_liste_string(tokens));
  
  arbre_t * arbre;
  int ret;
  automate_t * automate;

  
  ret = parser_parse(tokens, &arbre, &err, NULL);
  
  if (ret != 0) {
    printf("Analyse syntaxique ratéee: %s\n", err);
    return;
  }
  
  ARBRE_SHOW(arbre);

  automate = compilation(arbre);
  AUTOMATE_SHOW(automate);

  automate_test_commentaire_c_multiligne(automate);
  
  

#if 0
  parser_test();

  arbre_test();

  automate_test();

  compilation_test();
#endif

#if 0
  for (unsigned int i = 0; i < 32; i++)
    printf("2^%u = %u\n", i, puissance2_tab[i]);
#endif

}




void parser_test(void) {

  token_t * token;
  token_liste_t * tokens;
  tokens = token_liste_vide();
  tokens = token_liste_cons(token_make(TOKEN_TYPE_LETTRE, "a"), tokens);
  tokens = token_liste_cons(token_make(TOKEN_TYPE_LETTRE, "b"), tokens);
  tokens = token_liste_cons(token_make(TOKEN_TYPE_LETTRE, "c"), tokens);
  token_liste_reverse_surplace(&tokens);

  tokens = token_liste_vide();
  tokens = token_liste_cons(token_make(TOKEN_TYPE_LETTRE, "/"), tokens);
  tokens = token_liste_cons(token_make(TOKEN_TYPE_LETTRE, "*"), tokens);
  tokens = token_liste_cons(token_make(TOKEN_TYPE_BANG,   "!"), tokens);
  tokens = token_liste_cons(token_make(TOKEN_TYPE_OPENPAR, "("), tokens);
  tokens = token_liste_cons(token_make(TOKEN_TYPE_LETTRE_ANY, "."), tokens);
  tokens = token_liste_cons(token_make(TOKEN_TYPE_STAR, "*"), tokens);
  tokens = token_liste_cons(token_make(TOKEN_TYPE_LETTRE, "*"), tokens);
  tokens = token_liste_cons(token_make(TOKEN_TYPE_LETTRE, "/"), tokens);
  tokens = token_liste_cons(token_make(TOKEN_TYPE_LETTRE_ANY, "."), tokens);
  tokens = token_liste_cons(token_make(TOKEN_TYPE_STAR, "*"), tokens);
  tokens = token_liste_cons(token_make(TOKEN_TYPE_CLOSEPAR, ")"), tokens);
  tokens = token_liste_cons(token_make(TOKEN_TYPE_LETTRE, "*"), tokens);
  tokens = token_liste_cons(token_make(TOKEN_TYPE_LETTRE, "/"), tokens);
  token_liste_reverse_surplace(&tokens);

  arbre_t * arbre;
  int ret;
  char * err;
  automate_t * automate;

  printf("tokens = %s\n", token_liste_string(tokens));

  ret = parser_parse(tokens, &arbre, &err, NULL);
  
  if (ret != 0) {
    printf("Analyse syntaxique ratéee\n");
    return;
  }

  ARBRE_SHOW(arbre);
  automate = compilation(arbre);
  AUTOMATE_SHOW(automate);
  automate_test_commentaire_c_multiligne(automate);

}




void arbre_test(void) {

  arbre_t * arbre, * feuille, * fils, * fils1, * fils2;

  arbre = arbre_make_feuille_lettre('e', false);
  printf("arbre = %s\n", arbre_string(arbre));
  arbre = arbre_make_noeud(ARBRE_NOEUD_ET, 3);
  printf("arbre = %s\n", arbre_string(arbre));
  arbre_make_fils_add(arbre, arbre);
  printf("arbre = %s\n", arbre_string(arbre));
  arbre_make_fils_add(arbre, arbre);
  printf("arbre = %s\n", arbre_string(arbre));
  arbre_make_fils_add(arbre, arbre);
  printf("arbre = %s\n", arbre_string(arbre));

  //ARBRE_SHOW(arbre);


  arbre_free(arbre);


  arbre = arbre_make_noeud(ARBRE_NOEUD_ETOILE, 1);
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_any(false));

  fils = arbre;
  ARBRE_SHOW(arbre_copy(fils));

  arbre = arbre_make_noeud(ARBRE_NOEUD_CONCATENATION, 4);
  arbre_make_fils_add(arbre, fils);
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('*', false));
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('/', false));
  arbre_make_fils_add_nocopy(arbre, fils);

  fils = arbre;

  arbre = arbre_make_noeud(ARBRE_NOEUD_NON, 1);
  arbre_make_fils_add_nocopy(arbre, fils);

  fils = arbre;

  arbre = arbre_make_noeud(ARBRE_NOEUD_CONCATENATION, 5);
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('/', false));
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('*', false));
  arbre_make_fils_add_nocopy(arbre, fils);
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('*', false));
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('/', false));

  ARBRE_SHOW(arbre);

  //arbre_make_fils_add(arbre, arbre);
  //printf("arbre = %s\n", arbre_string(arbre));

}


void automate_test(void) {
  automate_t * automate;

  automate = automate_make(3);

  automate_etat_initial_set(automate, 1);
  automate_etat_final_set(automate, 3);
  automate_transition_ajouter(automate, '*', 1, 2);
  automate_transition_ajouter(automate, '*', 2, 2);
  automate_transition_ajouter(automate, '/', 2, 3);

  automate_transition_defaut(automate, 1, 1);
  automate_transition_defaut(automate, 2, 1);
  automate_transition_defaut(automate, 3, 3);

  //printf("automate = %s\n", automate_string(automate));


  automate_test_commentaire_c_multiligne(automate);

  printf("\n=========\n");

  automate_etat_final_inverser(automate);

  automate_test_commentaire_c_multiligne(automate);

  automate_free(automate);




  printf("\n=========\n");
  
  automate = automate_make(5);

  automate_etat_initial_set(automate, 1);
  automate_etat_final_set(automate, 5);
  automate_transition_ajouter(automate, '/', 1, 2);
  automate_transition_ajouter(automate, '*', 2, 3);
  automate_transition_ajouter(automate, '*', 3, 4);
  automate_transition_ajouter(automate, '*', 4, 4);
  automate_transition_ajouter(automate, '/', 4, 5);

  automate_transition_defaut(automate, 3, 3);
  automate_transition_defaut(automate, 4, 3);

  //printf("automate = %s\n", automate_string(automate));


  automate_test_commentaire_c_multiligne(automate);


  automate_free(automate);



  printf("\n=========\n");
  
  automate = automate_make(8);

  automate_etat_initial_set(automate, 1);
  automate_etat_final_set(automate, 8);
  automate_transition_ajouter(automate, '/', 1, 2);
  automate_transition_ajouter(automate, '*', 2, 3);
  automate_transition_ajouter(automate, '*', 3, 4);
  automate_transition_ajouter(automate, '*', 4, 4);
  automate_transition_ajouter(automate, '/', 4, 5);
  automate_transition_ajouter(automate, '*', 6, 7);
  automate_transition_ajouter(automate, '/', 7, 8);

  automate_transition_defaut(automate, 3, 3);
  automate_transition_defaut(automate, 4, 3);
  automate_transition_defaut(automate, 5, 5);

  automate_transition_epsilon_ajouter(automate, 3, 6);
  automate_transition_epsilon_ajouter(automate, 4, 6);

  //printf("automate = %s\n", automate_string(automate));


  automate_test_commentaire_c_multiligne(automate);




  printf("\n================== D\n");

  automate_t * automate_d;

  automate_d = automate_des_parties_bourrin32(automate);

#if 0
  printf("automate = %s\n", automate_string(automate));
  printf("automate_d = %s\n", automate_string_hard_hard(automate_d));
  printf("automate_d = %s\n", automate_string_hard(automate_d));
  printf("automate_d = %s\n", automate_string(automate_d));
#endif
  printf("automate_d = %s\n", automate_string(automate_d));

  automate_test_commentaire_c_multiligne(automate_d);



  printf("\n================== DA\n");

  automate_t * automate_da;

  automate_da = automate_accessible(automate_d);

  printf("automate_da = %s\n", automate_string_hard_hard(automate_da));
  printf("automate_da = %s\n", automate_string_hard(automate_da));
  printf("automate_da = %s\n", automate_string(automate_da));

  automate_test_commentaire_c_multiligne(automate_da);



#if 0
  printf("\n================== DAI\n");

  automate_t * automate_dai;

  automate_dai = automate_inverser(automate_da);

  printf("automate_dai = %s\n", automate_string_hard_hard(automate_dai));
  printf("automate_dai = %s\n", automate_string_hard(automate_dai));
  printf("automate_dai = %s\n", automate_string(automate_dai));

  automate_test_commentaire_c_multiligne(automate_dai);
#endif




  printf("\n================== DAC\n");

  automate_t * automate_dac;

  automate_dac = automate_coaccessible(automate_da);

  printf("automate_dac = %s\n", automate_string_hard_hard(automate_dac));
  printf("automate_dac = %s\n", automate_string_hard(automate_dac));
  printf("automate_dac = %s\n", automate_string(automate_dac));

  automate_test_commentaire_c_multiligne(automate_dac);







  printf("\n================== DACM\n");

  automate_t * automate_dacm;

  automate_dacm = automate_minimisation(automate_dac);

  printf("automate_dacm = %s\n", automate_string_hard_hard(automate_dacm));
  printf("automate_dacm = %s\n", automate_string_hard(automate_dacm));
  printf("automate_dacm = %s\n", automate_string(automate_dacm));

  automate_test_commentaire_c_multiligne(automate_dacm);





  printf("\n================== D FIN\n");

  automate_t * automate_d_fin;

  automate_d_fin = automate_des_parties_fin(automate);

#if 0
  printf("automate = %s\n", automate_string(automate));
  printf("automate_d_fin = %s\n", automate_string_hard_hard(automate_d_fin));
  printf("automate_d_fin = %s\n", automate_string_hard(automate_d_fin));
  printf("automate_d_fin = %s\n", automate_string(automate_d_fin));
#endif

  automate_test_commentaire_c_multiligne(automate_d_fin);





  printf("\n================== D FIN\n");

  automate_t * automate_d_fin_c;

  automate_d_fin_c = automate_coaccessible(automate_d_fin);

#if 1
  printf("automate = %s\n", automate_string(automate));
  printf("automate_d_fin_c = %s\n", automate_string_hard_hard(automate_d_fin_c));
  printf("automate_d_fin_c = %s\n", automate_string_hard(automate_d_fin_c));
  printf("automate_d_fin_c = %s\n", automate_string(automate_d_fin_c));
#endif


  automate_test_commentaire_c_multiligne(automate_d_fin_c);


  //printf("%s\n", automate_to_c_function(automate_d_fin_c, "automate_d_fin_c_function"));

  automate_function_test_commentaire_c_multiligne(automate_d_fin_c_function_mot_reconnu_huh);
  //automate_function_test_commentaire_c_multiligne(automate_d_fin_c_function_mot_reconnu_huh2);

  const char str[] = {'/', '*', ' ', 130, 33, -1, 255, -127, -128, 128, ' ', '*', '/'};
  printf("str[5] == str[6] : %s\n", bool_string_tab[str[5] == str[6]]);
  printf("str[8] == str[9] : %s\n", bool_string_tab[str[8] == str[9]]);
  printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_d_fin_c_function_mot_reconnu_huh(str)]);

#if 1
  printf("DOTTY\n%s\n", automate_to_dotty(automate_d_fin_c, "automate_d_fin_c"));
  AUTOMATE_SHOW(automate_d_fin_c);
  AUTOMATE_SHOW(automate_d_fin);
  AUTOMATE_SHOW(automate);
  AUTOMATE_SHOW(automate_da);
  AUTOMATE_SHOW(automate_dac);
  AUTOMATE_SHOW(automate_dacm);
#endif

  automate_free(automate);
  automate_free(automate_d);
  automate_free(automate_da);
  automate_free(automate_dac);
  automate_free(automate_dacm);
  automate_free(automate_d_fin);
  automate_free(automate_d_fin_c);




}


void automate_show_with_dotty(const automate_t * automate, const char * automate_name_const) {
  char * fichier_dot_name;
  char * fichier_jpg_name;
  char * automate_name;
  automate_name = string_char_replace(automate_name_const, '(', 'p');
  string_char_replace_nocopy(automate_name, '(', 'q');
  stradd3(&automate_name, "_rand", uint_string((unsigned)((uint8_t)random())));
  fichier_dot_name = strconcat2(automate_name, ".dot");
  fichier_jpg_name = strconcat2(automate_name, ".jpg");
  system(strconcat2("rm -f ", fichier_dot_name));
  system(strconcat2("rm -f ", fichier_jpg_name));
  char * dot_desc = automate_to_dotty(automate, automate_name);
  biglib_fichier_ecrire(fichier_dot_name, dot_desc);
  free(dot_desc);
  system(strconcat5("dot -Tjpg -o ", fichier_jpg_name, " ", fichier_dot_name, " > /dev/null 2>&1"));
  system(strconcat2("open ", fichier_jpg_name));
  free(fichier_jpg_name);
  free(fichier_dot_name);
}


void arbre_show_with_dotty(const arbre_t * arbre, const char * arbre_name_const) {
  char * fichier_dot_name;
  char * fichier_jpg_name;
  char * arbre_name;
  arbre_name = string_char_replace(arbre_name_const, '(', 'p');
  string_char_replace_nocopy(arbre_name, ')', 'q');
  stradd3(&arbre_name, "_rand", uint_string((unsigned)((uint8_t)random())));
  fichier_dot_name = strconcat2(arbre_name, ".dot");
  fichier_jpg_name = strconcat2(arbre_name, ".jpg");
  system(strconcat3("rm -f \"", fichier_dot_name, "\""));
  system(strconcat3("rm -f \"", fichier_jpg_name, "\""));
  char * dot_desc = arbre_to_dotty(arbre, arbre_name);
  biglib_fichier_ecrire(fichier_dot_name, dot_desc);
  free(dot_desc);
  system(strconcat5("dot -Tjpg -o \"", fichier_jpg_name, "\" \"", fichier_dot_name, "\" > /dev/null 2>&1"));
  system(strconcat3("open \"", fichier_jpg_name, "\""));
  free(fichier_jpg_name);
  free(fichier_dot_name);
}








void automate_test_commentaire_c_multiligne(const automate_t * automate) {
  const char * str;

  printf("\n=========\n");
  str = "*/"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_mot_reconnu_huh(automate, str)]);
  str = ""; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_mot_reconnu_huh(automate, str)]);
  str = "*"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_mot_reconnu_huh(automate, str)]);
  str = "/"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_mot_reconnu_huh(automate, str)]);
  str = "*****/"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_mot_reconnu_huh(automate, str)]);
  str = "*//////"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_mot_reconnu_huh(automate, str)]);
  str = "*****//////"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_mot_reconnu_huh(automate, str)]);
  str = "aaa bb ee "; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_mot_reconnu_huh(automate, str)]);
  str = "aaa bb * ee / "; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_mot_reconnu_huh(automate, str)]);
  str = "a*a/a bb * ee / "; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_mot_reconnu_huh(automate, str)]);
  str = "a*a/a b*/b * ee / "; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_mot_reconnu_huh(automate, str)]);

  printf("\n=========\n");
  str = "/* */"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_mot_reconnu_huh(automate, str)]);
  str = "/**/"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_mot_reconnu_huh(automate, str)]);
  str = "/*/"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_mot_reconnu_huh(automate, str)]);
  str = " /* */"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_mot_reconnu_huh(automate, str)]);
  str = "/* */ "; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_mot_reconnu_huh(automate, str)]);
  str = "/***/"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_mot_reconnu_huh(automate, str)]);
  str = "/**/*/"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_mot_reconnu_huh(automate, str)]);
  str = "/* Bonjour! Ceci est un commentaire C et il est reconnu par un automate déterministe qui possède cinq états. :-) */"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_mot_reconnu_huh(automate, str)]);
  str = "/* Il reconnaît même \n * la version multilignes!! \n */"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_mot_reconnu_huh(automate, str)]);
}


void automate_function_test_commentaire_c_multiligne(bool automate_function(const char * mot)) {
  const char * str;

  printf("\n=========\n");
  str = "*/"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_function(str)]);
  str = ""; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_function(str)]);
  str = "*"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_function(str)]);
  str = "/"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_function(str)]);
  str = "*****/"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_function(str)]);
  str = "*//////"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_function(str)]);
  str = "*****//////"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_function(str)]);
  str = "aaa bb ee "; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_function(str)]);
  str = "aaa bb * ee / "; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_function(str)]);
  str = "a*a/a bb * ee / "; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_function(str)]);
  str = "a*a/a b*/b * ee / "; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_function(str)]);

  printf("\n=========\n");
  str = "/* */"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_function(str)]);
  str = "/**/"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_function(str)]);
  str = "/*/"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_function(str)]);
  str = " /* */"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_function(str)]);
  str = "/* */ "; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_function(str)]);
  str = "/***/"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_function(str)]);
  str = "/**/*/"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_function(str)]);
  str = "/* Bonjour! Ceci est un commentaire C et il est reconnu par un automate déterministe qui possède cinq états. :-) */"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_function(str)]);
  str = "/* Il reconnaît même \n * la version multilignes!! \n */"; printf("str = \"%s\" - reconnu? = %s\n", str, bool_string_tab[automate_function(str)]);
}


















bool automate_d_fin_c_function_mot_reconnu_huh(const char * mot) {
  unsigned int etat_courant;
  unsigned int etat_suivant;
  
  etat_courant = 1;
  
  assert(NULL != mot);
  const unsigned int len = strlen(mot);
  unsigned char lettre;
  
  for (unsigned int i = 0; i < len; i++) {
    
    lettre = mot[i];
    
    switch (etat_courant) {
      case 0: {
        switch (lettre) {
          default: etat_suivant = 0; break;
        }
      }
      break;
      case 1: {
        switch (lettre) {
          case 47: etat_suivant = 2; break; // case '/':
          default: etat_suivant = 0; break;
        }
      }
      break;
      case 2: {
        switch (lettre) {
          case 42: etat_suivant = 3; break; // case '*':
          default: etat_suivant = 0; break;
        }
      }
      break;
      case 3: {
        switch (lettre) {
          case 42: etat_suivant = 4; break; // case '*':
          default: etat_suivant = 3; break;
        }
      }
      break;
      case 4: {
        switch (lettre) {
          case 42: etat_suivant = 4; break; // case '*':
          case 47: etat_suivant = 5; break; // case '/':
          default: etat_suivant = 3; break;
        }
      }
      break;
      case 5: {
        switch (lettre) {
          default: etat_suivant = 0; break;
        }
      }
      break;
      default: assert(false); break;
    }
    
    etat_courant = etat_suivant;
  }
  
  
  bool etat_final_huh;
  switch (etat_courant) {
    case 0: etat_final_huh = false; break;
    case 1: etat_final_huh = false; break;
    case 2: etat_final_huh = false; break;
    case 3: etat_final_huh = false; break;
    case 4: etat_final_huh = false; break;
    case 5: etat_final_huh = true; break;
    default: assert(false); break;
  }
  
  
  return etat_final_huh;
}










void compilation_test(void) {

  arbre_t * arbre, * feuille, * fils, * fils1, * fils2;
  automate_t * automate;


  arbre = arbre_make_noeud(ARBRE_NOEUD_CONCATENATION, 4);
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('a', false));
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('b', false));
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('c', false));
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('d', false));

#if 0
  ARBRE_SHOW(arbre);

  automate = compilation(arbre);
  AUTOMATE_SHOW(automate);
#endif




  arbre = arbre_make_noeud(ARBRE_NOEUD_OU, 4);
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('a', false));
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('b', false));
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('c', false));
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('d', false));

#if 0
  ARBRE_SHOW(arbre);

  automate = compilation(arbre);
  AUTOMATE_SHOW(automate);
#endif


  fils = arbre;
  arbre = arbre_make_noeud(ARBRE_NOEUD_NON, 1);
  arbre_make_fils_add_nocopy(arbre, fils);

#if 0
  ARBRE_SHOW(arbre);

  automate = compilation(arbre);
  AUTOMATE_SHOW(automate);
#endif



  arbre = arbre_make_noeud(ARBRE_NOEUD_ETOILE, 1);
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('a', false));

#if 0
  ARBRE_SHOW(arbre);

  automate = compilation(arbre);
  AUTOMATE_SHOW(automate);
#endif



  arbre = arbre_make_noeud(ARBRE_NOEUD_PLUS, 1);
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('a', false));

#if 0
  ARBRE_SHOW(arbre);

  automate = compilation(arbre);
  AUTOMATE_SHOW(automate);
#endif



  arbre = arbre_make_noeud(ARBRE_NOEUD_01, 1);
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('a', false));

#if 0
  ARBRE_SHOW(arbre);
  automate = compilation(arbre);
  AUTOMATE_SHOW(automate);
#endif




  arbre = arbre_make_noeud(ARBRE_NOEUD_ET, 4);
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('a', false));
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('b', false));
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('c', false));
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('d', false));

  //arbre = arbre_make_noeud(ARBRE_NOEUD_NON, 1);
  //arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('a', false));

#if 0
  ARBRE_SHOW(arbre);
  automate = compilation(arbre);
  AUTOMATE_SHOW(automate);
#endif


  arbre = arbre_make_noeud(ARBRE_NOEUD_CONCATENATION, 2);
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('a', false));
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_any(false));

  fils1 = arbre;

  arbre = arbre_make_noeud(ARBRE_NOEUD_CONCATENATION, 2);
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_any(false));
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('b', false));

  fils2 = arbre;

  arbre = arbre_make_noeud(ARBRE_NOEUD_ET, 2);
  arbre_make_fils_add_nocopy(arbre, fils1);
  arbre_make_fils_add_nocopy(arbre, fils2);

#if 1
  ARBRE_SHOW(arbre);
  automate = compilation(arbre);
  AUTOMATE_SHOW(automate);
#endif









  arbre = arbre_make_noeud(ARBRE_NOEUD_ETOILE, 1);
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_any(false));

  fils = arbre;
  ARBRE_SHOW(arbre_copy(fils));

  arbre = arbre_make_noeud(ARBRE_NOEUD_CONCATENATION, 4);
  arbre_make_fils_add(arbre, fils);
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('*', false));
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('/', false));
  arbre_make_fils_add_nocopy(arbre, fils);

  fils = arbre;

  arbre = arbre_make_noeud(ARBRE_NOEUD_NON, 1);
  arbre_make_fils_add_nocopy(arbre, fils);

  fils = arbre;

  arbre = arbre_make_noeud(ARBRE_NOEUD_CONCATENATION, 5);
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('/', false));
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('*', false));
  arbre_make_fils_add_nocopy(arbre, fils);
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('*', false));
  arbre_make_fils_add_nocopy(arbre, arbre_make_feuille_lettre('/', false));

  ARBRE_SHOW(arbre);

#if 1
  ARBRE_SHOW(arbre);
  automate = compilation(arbre);
  AUTOMATE_SHOW(automate);
#endif

  automate_test_commentaire_c_multiligne(automate);








#if 0
  automate = automate_accessible(automate);
  AUTOMATE_SHOW(automate);

  automate = automate_coaccessible(automate);
  AUTOMATE_SHOW(automate);

  automate = automate_determinisation(automate);
  AUTOMATE_SHOW(automate);

  automate = automate_accessible(automate);
  AUTOMATE_SHOW(automate);

  automate = automate_coaccessible(automate);
  AUTOMATE_SHOW(automate);

  automate = automate_minimisation(automate);
  AUTOMATE_SHOW(automate);
#endif


}
