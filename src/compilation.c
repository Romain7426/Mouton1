#include "global.h"
#include "compilation.h"
#include "arbre.h"
#include "arbre_methode.h"
#include "automate.h"
#include "automate_methode.h"


static automate_t * automate_lettre(const char c);
static automate_t * automate_lettre_non(const char c);
static automate_t * automate_lettre_any(void);
static automate_t * automate_lettre_any_non(void);

static automate_t * automate_empiler(automate_t * * automate_tab, const int automate_tab_nb, const unsigned int etat_suppl_nb);

static automate_t * automate_concatenation(automate_t * * automate_tab, const int automate_nb);
static automate_t * automate_ou(automate_t * * automate_tab, const int automate_tab_nb);
static automate_t * automate_et(automate_t * * automate_tab, const int automate_tab_nb);
static automate_t * automate_non(automate_t * * automate_tab, const int automate_tab_nb);
static automate_t * automate_etoile(automate_t * * automate_tab, const int automate_tab_nb);
static automate_t * automate_plus(automate_t * * automate_tab, const int automate_tab_nb);
static automate_t * automate_01(automate_t * * automate_tab, const int automate_tab_nb);

static automate_t * automate_non_notab(const automate_t * automate_tab);

static automate_t * * compilation_map(arbre_t * * arbre, int arbre_nb);



static automate_t * * automate_tab_allouer(const int automate_tab_nb);
static automate_t * * automate_tab_make(const int automate_tab_nb);
static void automate_tab_raz(automate_t * * automate_tab, const int automate_tab_nb);
static void automate_tab_free(automate_t * * automate_tab, const int automate_tab_nb);


automate_t * compilation(const arbre_t * arbre) {
  automate_t * automate;

  if (arbre_feuille_huh(arbre)) {
    switch (arbre -> type) {
    case ARBRE_FEUILLE_LETTRE: if (arbre -> feuille_non_huh) automate = automate_lettre_non(arbre -> lettre); else automate = automate_lettre(arbre -> lettre); break;
    case ARBRE_FEUILLE_ANY: ; if (arbre -> feuille_non_huh) automate = automate_lettre_any_non(); else automate = automate_lettre_any(); break;
    case ARBRE_NOEUD_CONCATENATION: assert(false); break;
    case ARBRE_NOEUD_OU: assert(false); break;
    case ARBRE_NOEUD_ET: assert(false); break;
    case ARBRE_NOEUD_NON: assert(false); break;
    case ARBRE_NOEUD_ETOILE: assert(false); break;
    case ARBRE_NOEUD_PLUS: assert(false); break;
    case ARBRE_NOEUD_01: assert(false); break;
    case ARBRE_NOMBRE: assert(false); break;
    default: assert(false); break;
    }
    return automate;
  }


  assert(arbre_noeud_huh(arbre));

  automate_t * * automate_tab;
  //arbre_t * const * arbre_tab = arbre -> fils;
  automate_tab = compilation_map(arbre -> fils, arbre -> fils_nb);

  automate = NULL;

  switch (arbre -> type) {
  case ARBRE_NOEUD_CONCATENATION: automate = automate_concatenation(automate_tab, arbre -> fils_nb); break;
  case ARBRE_NOEUD_OU: automate = automate_ou(automate_tab, arbre -> fils_nb); break;
  case ARBRE_NOEUD_ET: automate = automate_et(automate_tab, arbre -> fils_nb); break;
  case ARBRE_NOEUD_NON: automate = automate_non(automate_tab, arbre -> fils_nb); break;
  case ARBRE_NOEUD_ETOILE: automate = automate_etoile(automate_tab, arbre -> fils_nb);  break;
  case ARBRE_NOEUD_PLUS: automate = automate_plus(automate_tab, arbre -> fils_nb);  break;
  case ARBRE_NOEUD_01: automate = automate_01(automate_tab, arbre -> fils_nb);  break;
  case ARBRE_FEUILLE_LETTRE: assert(false); break;
  case ARBRE_FEUILLE_ANY: assert(false); break;
  case ARBRE_NOMBRE: assert(false); break;
  default: assert(false); break;
  }


  automate_tab_free(automate_tab, arbre -> fils_nb);

  
  return automate;
}



automate_t * * compilation_map(arbre_t * * arbre_tab, int arbre_nb) {
  automate_t * * automate_tab;
  automate_tab = automate_tab_make(arbre_nb);
  for (int i = 0; i < arbre_nb; i++)
    automate_tab[i] = compilation(arbre_tab[i]);
  return automate_tab;
}




automate_t * automate_lettre(const char c) {
  automate_t * automate;

  automate = automate_make(2);
  automate_transition_ajouter(automate, c, 1, 2);
  automate -> etat_initial = 1;
  automate -> etat_final_huh[2] = true;

  return automate;
}

automate_t * automate_lettre_non(const char c) {
  automate_t * automate;

  automate = automate_make(2);
  automate_transition_defaut(automate, 1, 2);
  automate_transition_ajouter(automate, c, 1, 0);
  automate -> etat_initial = 1;
  automate -> etat_final_huh[2] = true;

  return automate;
}

automate_t * automate_lettre_any(void) {
  automate_t * automate;

  automate = automate_make(2);
  automate_transition_defaut(automate, 1, 2);
  automate -> etat_initial = 1;
  automate -> etat_final_huh[2] = true;

  return automate;
}

automate_t * automate_lettre_any_non(void) {
  automate_t * automate;

  automate = automate_make(2);
  automate -> etat_initial = 1;
  automate -> etat_final_huh[2] = true;

  return automate;
}




automate_t * automate_empiler(automate_t * * automate_tab, const int automate_tab_nb, const unsigned int etat_suppl_nb) {
  automate_t * automate;

  {
    unsigned int etat_nb;

    etat_nb = 0;
    for (int i = 0; i < automate_tab_nb; i++)
      etat_nb += automate_tab[i] -> etat_nb;
    
    assert( (max(etat_nb,etat_suppl_nb) - min(etat_nb,etat_suppl_nb))  <  (((unsigned) -1) - max(etat_nb,etat_suppl_nb)) );

    automate = automate_make(etat_nb + etat_suppl_nb);
  }


  unsigned int etat_nb_stack = 0;

  for (int i = 0; i < automate_tab_nb; i++) {

    for (unsigned int j = 1; j <= automate_tab[i] -> etat_nb; j++)
      for (unsigned int lettre_indice = 0; lettre_indice < 256; lettre_indice++)
        if (automate_tab[i] -> transition[j][lettre_indice] != 0)
          automate_transition_ajouter(automate, lettre_indice, j + etat_nb_stack, automate_tab[i] -> transition[j][lettre_indice] + etat_nb_stack);
    
    for (unsigned int j = 1; j <= automate_tab[i] -> etat_nb; j++)
      for (unsigned int k = 1; k <= automate_tab[i] -> etat_nb; k++)
        if (automate_tab[i] -> transition_epsilon[j][k])
          automate_transition_epsilon_ajouter(automate, j + etat_nb_stack, k + etat_nb_stack);
    
    etat_nb_stack += automate_tab[i] -> etat_nb;
  
  }

  return automate;
}




automate_t * automate_concatenation(automate_t * * automate_tab, const int automate_tab_nb) {
  automate_t * automate;
  unsigned int etat_nb_stack;

  if (automate_tab_nb == 0)
    return automate_make(0);

  automate = automate_empiler(automate_tab, automate_tab_nb, 0);
  
  etat_nb_stack = 0;
  for (int i = 0; i < automate_tab_nb; i++) {
    
    for (unsigned int j = 1; j <= automate_tab[i] -> etat_nb; j++)
      if (automate_tab[i] -> etat_final_huh[j]) {
        if (i < (automate_tab_nb - 1))
          automate_transition_epsilon_ajouter(automate, j + etat_nb_stack, automate_tab[i+1] -> etat_initial + etat_nb_stack + automate_tab[i] -> etat_nb);
        else
          automate -> etat_final_huh[j + etat_nb_stack] = true;
      }
    
    etat_nb_stack += automate_tab[i] -> etat_nb;
  }



  automate -> etat_initial = automate_tab[0] -> etat_initial;

  if (true)
  {
    automate_t * automate_d = automate_simplify(automate);
    automate_free(automate);
    automate = automate_d;
  }
  return automate;
}



automate_t * automate_ou(automate_t * * automate_tab, const int automate_tab_nb) {
  automate_t * automate;
  unsigned int etat_nb_stack;
  
  automate = automate_empiler(automate_tab, automate_tab_nb, 2);
  
  const unsigned int etat_initial = automate -> etat_nb - 1;
  const unsigned int etat_final = automate -> etat_nb;
  automate -> etat_initial = etat_initial;
  automate -> etat_final_huh[etat_final] = true;
  
  etat_nb_stack = 0;
  for (int i = 0; i < automate_tab_nb; i++) {
    
    automate_transition_epsilon_ajouter(automate, etat_initial, automate_tab[i] -> etat_initial + etat_nb_stack);
    
    for (unsigned int j = 1; j <= automate_tab[i] -> etat_nb; j++)
      if (automate_tab[i] -> etat_final_huh[j])
        automate_transition_epsilon_ajouter(automate, j + etat_nb_stack, etat_final);
    
    etat_nb_stack += automate_tab[i] -> etat_nb;
  }
  


  if (true)
  {
    automate_t * automate_d = automate_simplify(automate);
    automate_free(automate);
    automate = automate_d;
  }
  return automate;
}




automate_t * automate_et(automate_t * * automate_tab, const int automate_tab_nb) {
  automate_t * * automate_non_tab;
  
  automate_non_tab = automate_tab_make(automate_tab_nb);
  for (int i = 0; i < automate_tab_nb; i++)
    automate_non_tab[i] = automate_non_notab(automate_tab[i]);


  automate_t * automate_ou_non;

  automate_ou_non = automate_ou(automate_non_tab, automate_tab_nb);

  //return automate_ou_non;
  //return automate_complementaire(automate_ou_non);
  //return automate_accessible(automate_complementaire(automate_ou_non));
  //return automate_coaccessible(automate_accessible(automate_complementaire(automate_ou_non)));
  //return automate_determinisation(automate_coaccessible(automate_accessible(automate_complementaire(automate_ou_non))));
  //return automate_coaccessible(automate_accessible(automate_determinisation(automate_coaccessible(automate_accessible(automate_complementaire(automate_ou_non))))));
  //return automate_minimisation(automate_coaccessible(automate_accessible(automate_determinisation(automate_coaccessible(automate_accessible(automate_complementaire(automate_ou_non)))))));

  automate_tab_free(automate_non_tab, automate_tab_nb);
  

  automate_t * automate_non_ou_non;
  
  //automate_non_ou_non = automate_non_notab(automate_ou_non);
  automate_non_ou_non = automate_non_notab(automate_ou_non);

  automate_free(automate_ou_non);


  if (false)
    {
      automate_t * automate_d = automate_simplify(automate_non_ou_non);
      automate_free(automate_non_ou_non);
      automate_non_ou_non = automate_d;
    }


  return automate_non_ou_non;
}





automate_t * automate_non(automate_t * * automate_tab, const int automate_tab_nb) {
  assert(automate_tab_nb == 1);
  
  return automate_non_notab(automate_tab[0]);
}





automate_t * automate_non_notab(const automate_t * automate_p) {
  automate_t * automate;
  
  automate = automate_complementaire(automate_p);

  //if (false)
  {
    automate_t * automate_d = automate_simplify(automate);
    automate_free(automate);
    automate = automate_d;
  }
  return automate;
}





automate_t * automate_etoile(automate_t * * automate_tab, const int automate_tab_nb) {
  automate_t * automate;

  assert(automate_tab_nb == 1);

  automate = automate_copy(automate_tab[0]);

  assert(not(automate -> etat_final_huh[0]));


  for (unsigned int i = 1; i <= automate -> etat_nb; i++)
    if (automate -> etat_final_huh[i])
      automate_transition_epsilon_ajouter(automate, i, automate -> etat_initial);

  for (unsigned int i = 1; i <= automate -> etat_nb; i++)
    automate -> etat_final_huh[i] = false;

  automate -> etat_final_huh[automate -> etat_initial] = true;


  //if (false)
  {
    automate_t * automate_d = automate_simplify(automate);
    automate_free(automate);
    automate = automate_d;
  }
  return automate;
}




automate_t * automate_plus(automate_t * * automate_tab, const int automate_tab_nb) {
  automate_t * automate;

  assert(automate_tab_nb == 1);

  automate = automate_copy(automate_tab[0]);

  assert(not(automate -> etat_final_huh[0]));


  for (unsigned int i = 1; i <= automate -> etat_nb; i++)
    if (automate -> etat_final_huh[i])
      automate_transition_epsilon_ajouter(automate, i, automate -> etat_initial);


  //if (false)
  {
    automate_t * automate_d = automate_simplify(automate);
    automate_free(automate);
    automate = automate_d;
  }
  return automate;
}



automate_t * automate_01(automate_t * * automate_tab, const int automate_tab_nb) {
  automate_t * automate;

  assert(automate_tab_nb == 1);

  automate = automate_copy(automate_tab[0]);

  assert(not(automate -> etat_final_huh[0]));

  automate -> etat_final_huh[automate -> etat_initial] = true;


  //if (false)
  {
    automate_t * automate_d = automate_simplify(automate);
    automate_free(automate);
    automate = automate_d;
  }
  return automate;
}






automate_t * * automate_tab_allouer(const int automate_tab_nb) {
  return (automate_t * *) malloc((automate_tab_nb+1) * (sizeof(automate_t *)));
}

automate_t * * automate_tab_make(const int automate_tab_nb) {
  automate_t * * automate_tab;
  automate_tab = automate_tab_allouer(automate_tab_nb);
  automate_tab_raz(automate_tab, automate_tab_nb);
  return automate_tab;
}

void automate_tab_raz(automate_t * * automate_tab, const int automate_tab_nb) {
  bzero(automate_tab, (automate_tab_nb+1) * (sizeof(automate_t *)));
}

void automate_tab_free(automate_t * * automate_tab, const int automate_tab_nb) {
  for (int i = 0; i < automate_tab_nb; i++)
    if (automate_tab[i] != NULL)
      free(automate_tab[i]);
  free(automate_tab);
}

