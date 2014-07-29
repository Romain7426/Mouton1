#include "global.h"
#include "automate.h"
#include "automate_methode.h"


static inline void epsilon_cloture_calcul(const automate_t * automate, bool * etat_suivant);
static inline unsigned int bool_tab_nb(const bool * etat_suivant, unsigned int etat_nb);
static inline unsigned int bool_tab_nb0(const bool * etat_suivant, unsigned int etat_nb);
static inline unsigned int nombre_from_etat(bool * etat, unsigned int etat_nb);
static inline void etat_from_nombre(unsigned int nombre, bool * etat, unsigned int etat_nb);
static inline unsigned int bool_tab_indice(const bool * etat_accessible_huh, unsigned int elt_indice);
static inline unsigned int bool_tab_indice0(const bool * etat_accessible_huh, unsigned int elt_indice);
static inline unsigned int bool_tab_indice_inverser(const bool * etat_accessible_huh, unsigned int etat_nb, unsigned int indice_recherche);
//static inline void bool_tab_inverser(bool * etat_suivant, unsigned int etat_nb);
static inline void bool_tab_inverser(bool etat_suivant[], unsigned int etat_nb);
#if 0
static inline unsigned int classe_eq_indice(bool (* classe_eq)[][], unsigned int etat, unsigned int classe_eq_nb);
#else
//static inline unsigned int classe_eq_indice(void * classe_eq, unsigned int etat, unsigned int classe_eq_nb);
//static inline unsigned int classe_eq_indice(unsigned int classe_eq_nb, unsigned int etat_nb, const bool (* classe_eq)[etat_nb+1][etat_nb+1], unsigned int etat);
//static inline unsigned int classe_eq_indice(unsigned int classe_eq_nb, unsigned int etat_nb, const void (* classe_eq_void), unsigned int etat);
static inline unsigned int classe_eq_indice(unsigned int classe_eq_nb, unsigned int etat_nb, void (* classe_eq_void), unsigned int etat);
#endif

static inline void accessible_cloture_calcul_deterministe(const automate_t * automate, bool * etat_accessible_huh);
static inline void accessible_cloture_calcul_non_deterministe(const automate_t * automate, bool * etat_accessible_huh);
static inline void coaccessible_cloture_calcul_deterministe(const automate_t * automate, bool * etat_coaccessible_huh);
static inline void coaccessible_cloture_calcul_non_deterministe(const automate_t * automate, bool * etat_coaccessible_huh);


static inline bool etat_equal(const bool * etat1, const bool * etat2, unsigned int etat_nb);
static inline bool * etat_copy(const bool * etat, unsigned int etat_nb);
static inline bool * etat_make(unsigned int etat_nb);
static inline void etat_raz(bool * etat, unsigned int etat_nb);
static inline void etat_copy_void(bool * etat_destination, const bool * etat_source, unsigned int etat_nb);

static inline unsigned int indice_from_etat_tab(const bool * * etat_tab, const bool * etat, unsigned int etat_tab_nb, unsigned int etat_nb);
//static inline unsigned int indice_from_etat_tab(bool * * etat_tab, const bool * etat, unsigned int etat_tab_nb, unsigned int etat_nb);




bool automate_deterministe_huh(const automate_t * automate) {
  for (unsigned int i = 0; i <= automate -> etat_nb; i++)
    for (unsigned int j = 0; j <= automate -> etat_nb; j++)
      if (automate -> transition_epsilon[i][j])
        return false;

  return true;
}



bool automate_mot_reconnu_huh(const automate_t * automate, const char * mot) {
  if (automate_deterministe_huh(automate))
    return automate_mot_reconnu_huh_deterministe(automate, mot);
  
  return automate_mot_reconnu_huh_non_deterministe(automate, mot);
}




bool automate_mot_reconnu_huh_deterministe(const automate_t * automate, const char * mot) {
  unsigned int etat_courant;
  char lettre;
  unsigned int lettre_indice;

  etat_courant = automate -> etat_initial;

  lettre = *mot;
  
  while ('\0' != lettre) {

    lettre_indice = ((unsigned int) ((unsigned char) lettre));

    etat_courant = automate -> transition[etat_courant][lettre_indice];

    if (0 == etat_courant)
      return false; // early stopping

    mot ++;
    lettre = *mot;
  }
  
  return automate -> etat_final_huh[etat_courant];
}



bool automate_mot_reconnu_huh_non_deterministe(const automate_t * automate, const char * mot) {
  bool * etat_courant;
  bool * etat_suivant;
  char lettre;
  unsigned int lettre_indice;
  const unsigned int taille = ((automate -> etat_nb + 1) * (sizeof (unsigned int)));


  etat_courant = (bool *) malloc(taille);
  etat_suivant = (bool *) malloc(taille);
  bzero(etat_courant, taille);

  etat_courant[automate -> etat_initial] = true;
  epsilon_cloture_calcul(automate, etat_courant);

  lettre = *mot;
  
  while ('\0' != lettre) {
    bzero(etat_suivant, taille);

    lettre_indice = ((unsigned int) ((unsigned char) lettre));

    // étape 1
    for (unsigned int i = 1; i <= automate -> etat_nb; i++) {
      if (not(etat_courant[i])) continue;
      
      etat_suivant[automate -> transition[i][lettre_indice]] = true;
    }

    // maintenant il faut calculer l'epsilon-clôture…!
    epsilon_cloture_calcul(automate, etat_suivant);

    // on permute les deux tableaux
    {
      unsigned int * temp;
      temp = etat_courant;
      etat_courant = etat_suivant;
      etat_suivant = temp;
    }

    mot ++;
    lettre = *mot;
  }


  bool reconnu_huh = false;
  for (unsigned int i = 0; i <= automate -> etat_nb; i++)
    if (etat_courant[i])
      if (automate -> etat_final_huh[i]) {
        reconnu_huh = true;
        break;
      }


  free(etat_courant);
  free(etat_suivant);
  
  return reconnu_huh;
}






void epsilon_cloture_calcul(const automate_t * automate, unsigned int * etat_suivant) {
  unsigned int suivant_nb, suivant_nb_prec;
  
  suivant_nb = bool_tab_nb(etat_suivant, automate -> etat_nb);
  
  do {
    suivant_nb_prec = suivant_nb;
    
    // on fait avancer la clôture
    for (unsigned int i = 1; i <= automate -> etat_nb; i++)
      if (etat_suivant[i])
        for (unsigned int j = 1; j <= automate -> etat_nb; j++)
          if (automate -> transition_epsilon[i][j])
            etat_suivant[j] = true;
    
    suivant_nb = bool_tab_nb(etat_suivant, automate -> etat_nb);
    
  } while (suivant_nb != suivant_nb_prec);
  
}



unsigned int bool_tab_nb(const bool * etat_suivant, unsigned int etat_nb) {
  unsigned int suivant_nb = 0;
  for (unsigned int j = 1; j <= etat_nb; j++)
    if (etat_suivant[j])
      suivant_nb++;

  return suivant_nb;
}

unsigned int bool_tab_nb0(const bool * etat_suivant, unsigned int etat_nb) {
  unsigned int suivant_nb = 0;
  for (unsigned int j = 0; j <= etat_nb; j++)
    if (etat_suivant[j])
      suivant_nb++;

  return suivant_nb;
}


unsigned int bool_tab_indice(const bool * etat_accessible_huh, unsigned int elt_indice) {
  if (not(etat_accessible_huh[elt_indice]))
    return 0;

  unsigned int indice = 0;
  
  for (unsigned int j = 1; j <= elt_indice; j++)
    if (etat_accessible_huh[j])
      indice++;

  return indice;
}

unsigned int bool_tab_indice0(const bool * etat_accessible_huh, unsigned int elt_indice) {
  if (not(etat_accessible_huh[elt_indice]))
    return 0;

  unsigned int indice = 0;
  
  for (unsigned int j = 0; j < elt_indice; j++)
    if (etat_accessible_huh[j])
      indice++;

  return indice;
}

unsigned int bool_tab_indice_inverser(const bool * etat_accessible_huh, unsigned int etat_nb, unsigned int indice_recherche) {
  unsigned int indice = 0;
  
  for (unsigned int j = 1; j <= etat_nb; j++)
    if (etat_accessible_huh[j]) {
      indice++;
      if (indice == indice_recherche)
        return j;
    }

  return 0;
}





automate_t * automate_des_parties_bourrin32(const automate_t * automate) {

  if (automate_deterministe_huh(automate))
    return automate_copy(automate);


  assert(automate -> etat_nb < 30);


  automate_t * automate_parties;
  bool * etat_courant;
  bool * etat_suivant;
  const unsigned int taille = ((automate -> etat_nb + 1) * (sizeof (bool)));
  unsigned int nombre;
  

  etat_courant = (bool *) malloc(taille);
  etat_suivant = (bool *) malloc(taille);

  automate_parties = automate_make(puissance2_tab[automate -> etat_nb] - 1);
  
  
  bzero(etat_courant, taille);
  etat_courant[automate -> etat_initial] = true;
  epsilon_cloture_calcul(automate, etat_courant);
  nombre = nombre_from_etat(etat_courant, automate -> etat_nb);
  automate_parties -> etat_initial = nombre;


  for (nombre = 1; nombre <= automate_parties -> etat_nb; nombre++) {
    for (unsigned int lettre_indice = 0; lettre_indice < 256; lettre_indice++) {
      etat_from_nombre(nombre, etat_courant, automate -> etat_nb);
      epsilon_cloture_calcul(automate, etat_courant);
      bzero(etat_suivant, taille);
      for (unsigned int i = 1; i <= automate -> etat_nb; i++)
        if (etat_courant[i])
          etat_suivant[automate -> transition[i][lettre_indice]] = true;
      epsilon_cloture_calcul(automate, etat_suivant);

      automate_parties -> transition[nombre][lettre_indice] = nombre_from_etat(etat_suivant, automate -> etat_nb);
    }
  }

  
  for (unsigned int i = 1; i <= automate -> etat_nb; i++)
    if (automate -> etat_final_huh[i])
      for (unsigned int j = 1; j <= automate_parties -> etat_nb; j++)
        if (j & puissance2_tab[i-1]) 
          automate_parties -> etat_final_huh[j] = true;

  
  
  free(etat_courant);
  free(etat_suivant);
  assert(automate_deterministe_huh(automate_parties));
  return automate_parties;
}












automate_t * automate_des_parties_bourrin_unlimited(const automate_t * automate) {

  if (automate_deterministe_huh(automate))
    return automate_copy(automate);

  const unsigned int bit_nb = 32;
  const unsigned int quotient = (((unsigned) (automate -> etat_nb + 1) ) / ((unsigned) bit_nb));
  const unsigned int reste = (((unsigned) (automate -> etat_nb + 1) ) % ((unsigned) bit_nb));
  const unsigned int taille2 = (quotient * (sizeof (bool)));
  unsigned int nombre2 = 0;


  assert(false);
  // cela demande de créer un type automate unlimited


  automate_t * automate_parties;
  bool * etat_courant;
  bool * etat_suivant;
  const unsigned int taille = ((automate -> etat_nb + 1) * (sizeof (bool)));
  unsigned int nombre;
  

  etat_courant = (bool *) malloc(taille);
  etat_suivant = (bool *) malloc(taille);

  automate_parties = automate_make(puissance2_tab[automate -> etat_nb] - 1);
  
  
  bzero(etat_courant, taille);
  etat_courant[automate -> etat_initial] = true;
  epsilon_cloture_calcul(automate, etat_courant);
  nombre = nombre_from_etat(etat_courant, automate -> etat_nb);
  automate_parties -> etat_initial = nombre;


  for (nombre = 1; nombre <= automate_parties -> etat_nb; nombre++) {
    for (unsigned int lettre_indice = 0; lettre_indice < 256; lettre_indice++) {
      etat_from_nombre(nombre, etat_courant, automate -> etat_nb);
      epsilon_cloture_calcul(automate, etat_courant);
      bzero(etat_suivant, taille);
      for (unsigned int i = 1; i <= automate -> etat_nb; i++)
        if (etat_courant[i])
          etat_suivant[automate -> transition[i][lettre_indice]] = true;
      epsilon_cloture_calcul(automate, etat_suivant);

      automate_parties -> transition[nombre][lettre_indice] = nombre_from_etat(etat_suivant, automate -> etat_nb);
    }
  }

  
  for (unsigned int i = 1; i <= automate -> etat_nb; i++)
    if (automate -> etat_final_huh[i])
      for (unsigned int j = 1; j <= automate_parties -> etat_nb; j++)
        if (j & puissance2_tab[i-1]) 
          automate_parties -> etat_final_huh[j] = true;

  
  
  free(etat_courant);
  free(etat_suivant);
  assert(automate_deterministe_huh(automate_parties));
  return automate_parties;
}

















automate_t * automate_des_parties_fin(const automate_t * automate) {

  if (automate_deterministe_huh(automate))
    return automate_copy(automate);

  if (automate -> etat_initial == 0)
    return automate_make(0);


  bool * * ap_etats;
  unsigned int * * ap_transitions;
  unsigned int ap_etat_nb;
  unsigned int ap_etat_taille;
  unsigned int ap_etat_taille_reelle;
  
  ap_etat_taille = 127;
  ap_etat_taille_reelle = ap_etat_taille + 1; // l'état puits
  assert(0 != ap_etat_taille_reelle);
  
  ap_etat_nb = 0;
  ap_etats = (bool * *) malloc(ap_etat_taille_reelle * sizeof(bool *));
  ap_transitions = (unsigned int * *) malloc(ap_etat_taille_reelle * sizeof(unsigned int *));
 
  for (unsigned int i = 0; i < ap_etat_taille_reelle; i++) {
    ap_transitions[i] = (unsigned int *) malloc(256 * (sizeof (unsigned int)));
    bzero(ap_transitions[i], 256 * (sizeof (unsigned int)));
  }



  assert(ap_etat_nb < ap_etat_taille);
  ap_etat_nb++;
  ap_etats[0] = etat_make(automate -> etat_nb);



  bool * etat_courant;
  bool * etat_suivant;
  const unsigned int taille = ((automate -> etat_nb + 1) * (sizeof (bool)));
  unsigned int etat_courant_indice;
  unsigned int etat_suivant_indice;

  etat_courant = etat_make(automate -> etat_nb);
  etat_suivant = etat_make(automate -> etat_nb);

  assert(0 != automate -> etat_initial);
  etat_courant[automate -> etat_initial] = true;
  epsilon_cloture_calcul(automate, etat_courant);
  
  assert(ap_etat_nb < ap_etat_taille);
  ap_etat_nb++;
  ap_etats[1] = etat_copy(etat_courant, automate -> etat_nb);


  

  for (unsigned int etat_courant_indice = 1; etat_courant_indice < ap_etat_nb; etat_courant_indice++) {
    //etat_courant_indice = nombre_from_etat_tab(ap_etats, etat_courant, ap_etat_nb, automate -> etat_nb);
    etat_copy_void(etat_courant, ap_etats[etat_courant_indice], automate -> etat_nb);
    for (unsigned int lettre_indice = 0; lettre_indice < 256; lettre_indice++) {
      etat_raz(etat_suivant, automate -> etat_nb);
      for (unsigned int i = 1; i <= automate -> etat_nb; i++)
        if (etat_courant[i])
          etat_suivant[automate -> transition[i][lettre_indice]] = true;
      epsilon_cloture_calcul(automate, etat_suivant);

      // la conversion en Const: Bug de GCC… :-(
      // GCC n'arrive à comprendre que [const bool * *] est un cas particulier de [bool * *]…
      etat_suivant_indice = indice_from_etat_tab((const bool * *) ap_etats, etat_suivant, ap_etat_nb, automate -> etat_nb);
      //etat_suivant_indice = indice_from_etat_tab((const typeof(ap_etats)) ap_etats, etat_suivant, ap_etat_nb, automate -> etat_nb);
      if (etat_suivant_indice == ap_etat_nb) {
        assert(ap_etat_nb < ap_etat_taille);
        ap_etats[ap_etat_nb] = etat_copy(etat_suivant, automate -> etat_nb);
        ap_etat_nb++;
      }
      ap_transitions[etat_courant_indice][lettre_indice] = etat_suivant_indice;
    }
  }





  automate_t * automate_deterministe;

  assert(ap_etat_nb > 0);
  automate_deterministe = automate_make(ap_etat_nb-1);

  for (unsigned int i = 0; i < ap_etat_nb; i++)
    memcpy(automate_deterministe -> transition[i], ap_transitions[i], 256 * (sizeof (unsigned int)));
  
  for (unsigned int i = 1; i <= automate -> etat_nb; i++)
    if (automate -> etat_final_huh[i])
      for (unsigned int j = 1; j < ap_etat_nb; j++)
        if (ap_etats[j][i]) 
          automate_deterministe -> etat_final_huh[j] = true;

  automate_deterministe -> etat_initial = 1;


#if 0
  {
    for (unsigned int i = 0; i < ap_etat_nb; i++) {
      printf("etat %u = ", i);
#if 0
      for (unsigned int j = 0; j <= automate -> etat_nb; j++)
        printf("%u: %s; ", j, bool_string_tab[ap_etats[i][j]]);
#else
      for (unsigned int j = 0; j <= automate -> etat_nb; j++)
        if (ap_etats[i][j])
          printf("%u, ", j);
#endif
      printf("\n");
    }
  }
#endif

  
  
  free(etat_courant);
  free(etat_suivant);
  for (unsigned int i = 0; i < ap_etat_nb; i++)
    free(ap_etats[i]);
  for (unsigned int i = 0; i < ap_etat_nb; i++)
    free(ap_transitions[i]);
  free(ap_transitions);
  assert(automate_deterministe_huh(automate_deterministe));
  return automate_deterministe;
}





//unsigned int indice_from_etat_tab(const bool * * etat_tab, const bool * etat, unsigned int etat_tab_nb, unsigned int etat_nb) {
unsigned int indice_from_etat_tab(const bool * * etat_tab, const bool * etat, unsigned int etat_tab_nb, unsigned int etat_nb) {
  for (unsigned int i = 0; i < etat_tab_nb; i++)
    if (etat_equal(etat_tab[i], etat, etat_nb))
      return i;

  return etat_tab_nb;
}


bool etat_equal(const bool * etat1, const bool * etat2, unsigned int etat_nb) {
  for (unsigned int i = 1; i <= etat_nb; i++)
    if (etat1[i] != etat2[i])
      return false;

  return true;
}

bool * etat_copy(const bool * etat, unsigned int etat_nb) {
  bool * retour;
  retour = etat_make(etat_nb);
  etat_copy_void(retour, etat, etat_nb);
  return retour;
}

void etat_copy_void(bool * etat_destination, const bool * etat_source, unsigned int etat_nb) {
  const unsigned int taille = ((etat_nb+1) * sizeof(bool));
  memcpy(etat_destination, etat_source, taille);
}

bool * etat_make(unsigned int etat_nb) {
  bool * retour;
  const unsigned int taille = ((etat_nb+1) * sizeof(bool));
  retour = (bool *) malloc(taille);
  etat_raz(retour, etat_nb);
  return retour;
}

void etat_raz(bool * etat, unsigned int etat_nb) {
  const unsigned int taille = ((etat_nb+1) * sizeof(bool));
  bzero(etat, taille);
}





void etat_from_nombre(unsigned int nombre, bool * etat, unsigned int etat_nb) {
  const unsigned int taille = ((etat_nb + 1) * (sizeof (bool)));
  bzero(etat, taille);
  for (unsigned int i = 0; i < 32; i++)
    if (nombre & puissance2_tab[i])
      etat[i+1] = true;

}


unsigned int nombre_from_etat(bool * etat, unsigned int etat_nb) {
  unsigned int nombre = 0;
  for (unsigned int i = 1; i <= etat_nb; i++)
    if (etat[i])
      nombre += puissance2_tab[i-1];

  return nombre;
}






automate_t * automate_accessible(const automate_t * automate) {
  if (automate_deterministe_huh(automate))
    return automate_accessible_deterministe(automate);

  return automate_accessible_non_deterministe(automate);
}


automate_t * automate_accessible_deterministe(const automate_t * automate) {
  bool * etat_accessible_huh;
  const unsigned int taille = ((automate -> etat_nb + 1) * (sizeof (bool)));

  etat_accessible_huh = (bool *) malloc(taille);
  bzero(etat_accessible_huh, taille);
  etat_accessible_huh[automate -> etat_initial] = true;
  accessible_cloture_calcul_deterministe(automate, etat_accessible_huh);
  
  automate_t * automate_nouveau;
  automate_nouveau = automate_sous(automate, etat_accessible_huh);

  free(etat_accessible_huh);

  return automate_nouveau;
}

automate_t * automate_accessible_non_deterministe(const automate_t * automate) {
  bool * etat_accessible_huh;
  const unsigned int taille = ((automate -> etat_nb + 1) * (sizeof (bool)));

  etat_accessible_huh = (bool *) malloc(taille);
  bzero(etat_accessible_huh, taille);
  etat_accessible_huh[automate -> etat_initial] = true;
  accessible_cloture_calcul_non_deterministe(automate, etat_accessible_huh);
  
  automate_t * automate_nouveau;
  automate_nouveau = automate_sous_non_deterministe(automate, etat_accessible_huh);

  free(etat_accessible_huh);

  return automate_nouveau;
}





void accessible_cloture_calcul_deterministe(const automate_t * automate, bool * etat_accessible_huh) {
  unsigned int suivant_nb, suivant_nb_prec;
  
  suivant_nb = bool_tab_nb(etat_accessible_huh, automate -> etat_nb);
  
  do {
    suivant_nb_prec = suivant_nb;
    
    // on fait avancer la clôture
    for (unsigned int i = 0; i <= automate -> etat_nb; i++)
      if (etat_accessible_huh[i])
        for (unsigned int lettre_indice = 0; lettre_indice < 256; lettre_indice++)
          etat_accessible_huh[automate -> transition[i][lettre_indice]] = true;
    
    suivant_nb = bool_tab_nb(etat_accessible_huh, automate -> etat_nb);
    
  } while (suivant_nb != suivant_nb_prec);

}




void accessible_cloture_calcul_non_deterministe(const automate_t * automate, bool * etat_accessible_huh) {
  unsigned int suivant_nb, suivant_nb_prec;
  
  suivant_nb = bool_tab_nb(etat_accessible_huh, automate -> etat_nb);
  
  do {
    suivant_nb_prec = suivant_nb;
    
    // on fait avancer la clôture
    for (unsigned int i = 0; i <= automate -> etat_nb; i++)
      if (etat_accessible_huh[i]) {

        for (unsigned int lettre_indice = 0; lettre_indice < 256; lettre_indice++)
          etat_accessible_huh[automate -> transition[i][lettre_indice]] = true;

        for (unsigned int j = 0; j <= automate -> etat_nb; j++)
          if (automate -> transition_epsilon[i][j])
            etat_accessible_huh[j] = true;

      }
    
    suivant_nb = bool_tab_nb(etat_accessible_huh, automate -> etat_nb);
    
  } while (suivant_nb != suivant_nb_prec);

}


automate_t * automate_sous(const automate_t * automate, const bool * etat_accessible_huh) {
  if (automate_deterministe_huh(automate))
    return automate_sous_deterministe(automate, etat_accessible_huh);

  return automate_sous_non_deterministe(automate, etat_accessible_huh);
}

automate_t * automate_sous_deterministe(const automate_t * automate, const bool * etat_accessible_huh) {
  automate_t * automate_nouveau;
  const unsigned int suivant_nb = bool_tab_nb(etat_accessible_huh, automate -> etat_nb);
  unsigned int tab_inverser[suivant_nb+1];

  tab_inverser[0] = 0;
  for (unsigned int i = 1; i <= suivant_nb; i ++)
    tab_inverser[i] = bool_tab_indice_inverser(etat_accessible_huh, automate -> etat_nb, i);


  automate_nouveau = automate_make(suivant_nb);

  if (automate -> etat_initial == 0)
    automate_nouveau -> etat_initial = 0;
  else
    automate_nouveau -> etat_initial = bool_tab_indice(etat_accessible_huh, automate -> etat_initial);

  for (unsigned int i = 1; i <= automate_nouveau -> etat_nb; i++) {
    for (unsigned int lettre_indice = 0; lettre_indice < 256; lettre_indice++) {
      const unsigned int etat_arrive = automate -> transition[tab_inverser[i]][lettre_indice];
      if (etat_arrive != 0)
        automate_nouveau -> transition[i][lettre_indice] = bool_tab_indice(etat_accessible_huh, etat_arrive);
    }
  }

  if (etat_accessible_huh[0])
    automate_nouveau -> etat_final_huh[0] = automate -> etat_final_huh[0];
  for (unsigned int i = 1; i <= automate_nouveau -> etat_nb; i++)
    automate_nouveau -> etat_final_huh[i] = automate -> etat_final_huh[tab_inverser[i]];

  return automate_nouveau;
}

automate_t * automate_sous_non_deterministe(const automate_t * automate, const bool * etat_accessible_huh) {
  automate_t * automate_nouveau;
  const unsigned int suivant_nb = bool_tab_nb(etat_accessible_huh, automate -> etat_nb);
  unsigned int tab_inverser[suivant_nb+1];

  tab_inverser[0] = 0;
  for (unsigned int i = 1; i <= suivant_nb; i ++)
    tab_inverser[i] = bool_tab_indice_inverser(etat_accessible_huh, automate -> etat_nb, i);


  automate_nouveau = automate_make(suivant_nb);

  if (automate -> etat_initial == 0)
    automate_nouveau -> etat_initial = 0;
  else
    automate_nouveau -> etat_initial = bool_tab_indice(etat_accessible_huh, automate -> etat_initial);

  for (unsigned int i = 1; i <= automate_nouveau -> etat_nb; i++) {
    for (unsigned int lettre_indice = 0; lettre_indice < 256; lettre_indice++) {
      const unsigned int etat_arrive = automate -> transition[tab_inverser[i]][lettre_indice];
      if (etat_arrive != 0)
        automate_nouveau -> transition[i][lettre_indice] = bool_tab_indice(etat_accessible_huh, etat_arrive);
    }
  }

  for (unsigned int i = 0; i <= automate_nouveau -> etat_nb; i++) {
    for (unsigned int j = 0; j <= automate_nouveau -> etat_nb; j++)
      if (automate -> transition_epsilon[tab_inverser[i]][tab_inverser[j]])
        automate_nouveau -> transition_epsilon[i][j] = true;
  }

  if (etat_accessible_huh[0])
    automate_nouveau -> etat_final_huh[0] = automate -> etat_final_huh[0];
  for (unsigned int i = 1; i <= automate_nouveau -> etat_nb; i++)
    automate_nouveau -> etat_final_huh[i] = automate -> etat_final_huh[tab_inverser[i]];

  return automate_nouveau;
}









automate_t * automate_coaccessible(const automate_t * automate) {
  if (automate_deterministe_huh(automate))
    return automate_coaccessible_deterministe(automate);

  return automate_coaccessible_non_deterministe(automate);
}


automate_t * automate_coaccessible_deterministe(const automate_t * automate) {
  bool * etat_coaccessible_huh;
  const unsigned int taille = ((automate -> etat_nb + 1) * (sizeof (bool)));

  etat_coaccessible_huh = (bool *) malloc(taille);
  memcpy(etat_coaccessible_huh, automate -> etat_final_huh, taille);
  coaccessible_cloture_calcul_deterministe(automate, etat_coaccessible_huh);
  
  automate_t * automate_nouveau;
  automate_nouveau = automate_sous(automate, etat_coaccessible_huh);

  free(etat_coaccessible_huh);

  return automate_nouveau;
}


automate_t * automate_coaccessible_non_deterministe(const automate_t * automate) {
  bool * etat_coaccessible_huh;
  const unsigned int taille = ((automate -> etat_nb + 1) * (sizeof (bool)));

  etat_coaccessible_huh = (bool *) malloc(taille);
  memcpy(etat_coaccessible_huh, automate -> etat_final_huh, taille);
  coaccessible_cloture_calcul_non_deterministe(automate, etat_coaccessible_huh);
  
  automate_t * automate_nouveau;
  automate_nouveau = automate_sous(automate, etat_coaccessible_huh);

  free(etat_coaccessible_huh);

  return automate_nouveau;
}





void coaccessible_cloture_calcul_deterministe(const automate_t * automate, bool * etat_coaccessible_huh) {
  unsigned int suivant_nb, suivant_nb_prec;
  
  suivant_nb = bool_tab_nb(etat_coaccessible_huh, automate -> etat_nb);
  
  do {
    suivant_nb_prec = suivant_nb;
    
    // on fait avancer la clôture
    for (unsigned int i = 0; i <= automate -> etat_nb; i++)
      if (etat_coaccessible_huh[i])
        for (unsigned int j = 0; j <= automate -> etat_nb; j++)
          for (unsigned int lettre_indice = 0; lettre_indice < 256; lettre_indice++)
            if (i == automate -> transition[j][lettre_indice])
              etat_coaccessible_huh[j] = true;
    
    suivant_nb = bool_tab_nb(etat_coaccessible_huh, automate -> etat_nb);
    
  } while (suivant_nb != suivant_nb_prec);

}



void coaccessible_cloture_calcul_non_deterministe(const automate_t * automate, bool * etat_coaccessible_huh) {
  unsigned int suivant_nb, suivant_nb_prec;
  
  suivant_nb = bool_tab_nb(etat_coaccessible_huh, automate -> etat_nb);
  
  do {
    suivant_nb_prec = suivant_nb;
    
    // on fait avancer la clôture
    for (unsigned int i = 0; i <= automate -> etat_nb; i++)
      if (etat_coaccessible_huh[i]) {

        for (unsigned int j = 0; j <= automate -> etat_nb; j++)
          for (unsigned int lettre_indice = 0; lettre_indice < 256; lettre_indice++)
            if (i == automate -> transition[j][lettre_indice]) {
              etat_coaccessible_huh[j] = true;
              break;
            }

        for (unsigned int j = 0; j <= automate -> etat_nb; j++)
          if (automate -> transition_epsilon[j][i])
              etat_coaccessible_huh[j] = true;

      }
    
    suivant_nb = bool_tab_nb(etat_coaccessible_huh, automate -> etat_nb);
    
  } while (suivant_nb != suivant_nb_prec);

}





#if 0
// dommage! car non déterministe… :-/
automate_t * automate_inverser(const automate_t * automate) {
  automate_t * retour;

  retour = automate_make(automate -> etat_nb);

  for (unsigned int i = 0; i <= automate -> etat_nb; i++)
    for (unsigned int lettre_indice = 0; lettre_indice < 256; lettre_indice++)
      if (0 != automate -> transition[i][lettre_indice])
        retour -> transition[automate -> transition[i][lettre_indice]][lettre_indice] = i;


  memcpy(retour -> etat_final_huh, automate -> etat_final_huh, (automate -> etat_nb + 1) * (sizeof (bool)));
  //retour -> etat_final_huh[automate -> etat_initial] = true;

  retour -> etat_initial = automate -> etat_initial;


  return retour;
}
#endif


automate_t * automate_complementaire(const automate_t * automate) {
  automate_t * retour;
  assert(automate_deterministe_huh(automate));
  retour = automate_make(automate -> etat_nb + 1);
  automate_copy_void(retour, automate);
  bool_tab_inverser(retour -> etat_final_huh, retour -> etat_nb);
  if (not(retour -> etat_final_huh[0]))
    return retour;


  retour -> etat_final_huh[0] = false;

  for (unsigned int i = 1; i <= retour -> etat_nb; i++)
    for (unsigned int lettre_indice = 0; lettre_indice < 256; lettre_indice++)
      if (retour -> transition[i][lettre_indice] == 0)
        retour -> transition[i][lettre_indice] = retour -> etat_nb;

  if (retour -> etat_initial == 0)
    retour -> etat_initial = retour -> etat_nb;

  return retour;
}






automate_t * automate_emonde(const automate_t * automate) {
  assert(automate_deterministe_huh(automate));

  return automate_coaccessible_deterministe(automate);
}

automate_t * automate_emonde_deterministe(const automate_t * automate) {
  automate_t * aa;
  automate_t * ac;
  aa = automate_accessible_deterministe(automate);
  ac = automate_coaccessible_deterministe(aa);
  free(aa);
  return ac;
}




automate_t * automate_minimisation(const automate_t * automate) {
  assert(automate_deterministe_huh(automate));

  return automate_minimisation_deterministe(automate);
}


automate_t * automate_minimisation_deterministe(const automate_t * automate) {
  const unsigned int taille = ((automate -> etat_nb + 1));
  const unsigned int taille_octet = ((taille) * (sizeof (bool)));
  bool classe_eq_courante[automate -> etat_nb + 1][automate -> etat_nb + 1];
  unsigned int classe_eq_courante_nb;
  bool classe_arrivee[automate -> etat_nb + 1];

  //printf("MINIMISATION\n");
  
  bzero(classe_eq_courante, taille_octet * (automate -> etat_nb + 1));


  if (automate -> etat_nb == 0)
    return automate_copy(automate);

  assert(not(automate -> etat_final_huh[0]));

  memcpy(classe_eq_courante[1], automate -> etat_final_huh, taille_octet);
  memcpy(classe_eq_courante[0], automate -> etat_final_huh, taille_octet);
  bool_tab_inverser(classe_eq_courante[0], automate -> etat_nb);
  classe_eq_courante_nb = 1;
  //classe_eq_courante[2][0] = false;

  //if (false)
  #if 0
    {
      for (unsigned int j = 1; j <= automate -> etat_nb; j++)
        printf("[%u][%u] = %s ", 0, j, bool_string_tab[automate -> etat_final_huh[j]]);
      printf("\n");
      for (unsigned int j = 1; j <= automate -> etat_nb; j++)
        printf("[%u][%u] = %s ", 0, j, bool_string_tab[classe_eq_courante[0][j]]);
      printf("\n");
      for (unsigned int j = 1; j <= automate -> etat_nb; j++)
        printf("[%u][%u] = %s ", 1, j, bool_string_tab[classe_eq_courante[1][j]]);
      printf("\n");
      fflush(NULL);
    }
#endif

  unsigned nb_classes_au_debut_de_la_boucle;
  unsigned nb_classes_a_la_fin_de_la_boucle;


  do {
    nb_classes_au_debut_de_la_boucle = classe_eq_courante_nb;

    for (unsigned int classe_eq_courante_indice = 0; classe_eq_courante_indice <= classe_eq_courante_nb; classe_eq_courante_indice++) {
     
      for (unsigned int lettre_indice = 0; lettre_indice < 256; lettre_indice++) {
        bzero(classe_arrivee, taille_octet);
        
#if 0
        for (unsigned int j = 0; j <= automate -> etat_nb; j++)
          printf("[%u][%u] = %s ", classe_eq_courante_indice, j, bool_string_tab[classe_eq_courante[classe_eq_courante_indice][j]]);
        printf("\n");

        if (classe_eq_courante[classe_eq_courante_indice][4] && (lettre_indice == (unsigned char) 'd'))
          printf("HERE\n");
#endif

        for (unsigned int i = 0; i <= automate -> etat_nb; i++)
          if (classe_eq_courante[classe_eq_courante_indice][i]) {
            //If (0 != automate -> transition[i][lettre_indice]) 
              {
                //classe_arrivee[classe_eq_indice(classe_eq_courante, automate -> transition[i][lettre_indice], classe_eq_courante_nb)] = true;
                const unsigned int classe_arrivee_indice = classe_eq_indice(classe_eq_courante_nb, automate -> etat_nb, &classe_eq_courante, automate -> transition[i][lettre_indice]);
                classe_arrivee[classe_arrivee_indice] = true;
              }
          }

#if 0
        if ('d' == (char) (unsigned char) lettre_indice) {
          printf("classe arrivee: ");
          for (unsigned int k = 0; k <= automate -> etat_nb; k++)
            printf("%u[%s] ", k, bool_string_tab[classe_arrivee[k]]);
          printf("\n");
          printf("transition 4 -> 5 en d: %s\n", bool_string_const(automate -> transition[4][(unsigned char) 'd'] == 5));
          printf("classe eq indice: %u \n", classe_eq_indice(classe_eq_courante_nb, automate -> etat_nb, &classe_eq_courante, 5));
          printf("classe eq indice: %u \n", classe_eq_indice(classe_eq_courante_nb, automate -> etat_nb, &classe_eq_courante, 4));
        }
#endif
        
        const unsigned int etat_arrivee_nb = bool_tab_nb0(classe_arrivee, automate -> etat_nb);
        
#if 0
        for (unsigned int j = 0; j <= automate -> etat_nb; j++)
          printf("[%u][%u] = %s ", 0, j, bool_string_tab[classe_eq_courante[0][j]]);
        printf("\n");
        printf("etat_arrivee_nb = %u\n", etat_arrivee_nb);
        printf("classe_eq_courante_indice = %u\n", classe_eq_courante_indice);
        printf("classe_eq_courante_nb = %u\n", classe_eq_courante_nb);
        printf("lettre = %c\n", (unsigned char) lettre_indice);
#endif

        if (0 == etat_arrivee_nb || 1 == etat_arrivee_nb)
          continue;
        
        // nous devons créer etat_arrivee_nb-1 nouvelle classe
        //classe_eq_courante_nb += (etat_arrivee_nb-1);
        //assert(classe_eq_courante_nb <= automate -> etat_nb);
        assert((classe_eq_courante_nb + (etat_arrivee_nb-1)) <= automate -> etat_nb);
        
        {
          bool ceq_courante_tab[automate -> etat_nb+1];
          unsigned int ceq_arrivee_tab[automate -> etat_nb+1];
          unsigned int ceq_arrivee_n_tab[automate -> etat_nb+1];
          bzero(ceq_courante_tab, (automate -> etat_nb+1) * (sizeof(bool)));
          bzero(ceq_arrivee_tab, (automate -> etat_nb+1) * (sizeof(unsigned int)));
          bzero(ceq_arrivee_n_tab, (automate -> etat_nb+1) * (sizeof(unsigned int)));
          for (unsigned int i = 0; i <= automate -> etat_nb; i++)
            ceq_courante_tab[i] = classe_eq_courante[classe_eq_courante_indice][i];
          for (unsigned int i = 0; i <= automate -> etat_nb; i++)
            if (ceq_courante_tab[i])
              ceq_arrivee_tab[i] = classe_eq_indice(classe_eq_courante_nb, automate -> etat_nb, &classe_eq_courante, automate -> transition[i][lettre_indice]);
          for (unsigned int i = 0; i <= automate -> etat_nb; i++)
            if (ceq_courante_tab[i])
                ceq_arrivee_n_tab[i] = bool_tab_indice0(classe_arrivee, ceq_arrivee_tab[i]);
          ;;
          for (unsigned int i = 0; i <= automate -> etat_nb; i++)
            if (ceq_courante_tab[i])
              if (0 != ceq_arrivee_n_tab[i]) {
                classe_eq_courante[classe_eq_courante_indice][i] = false;
                classe_eq_courante[classe_eq_courante_nb + ceq_arrivee_n_tab[i]][i] = true;
              }

          classe_eq_courante_nb += (etat_arrivee_nb-1);
          assert(classe_eq_courante_nb <= automate -> etat_nb);
        }

      }
    }

    nb_classes_a_la_fin_de_la_boucle = classe_eq_courante_nb;

  } while (nb_classes_a_la_fin_de_la_boucle != nb_classes_au_debut_de_la_boucle);
  


  //return automate_contracte_deterministe(automate, &classe_eq_courante);
  return automate_contracte_deterministe(automate, classe_eq_courante_nb, &classe_eq_courante);
}




#if 0
//automate_t * automate_contracte_deterministe(const automate_t * automate, unsigned int ceq_nb, const bool (* ceq)[ceq_nb + 1][automate -> etat_nb + 1])
automate_t * automate_contracte_deterministe(const automate_t * automate, unsigned int ceq_nb, const bool (* ceq)[automate -> etat_nb + 1][automate -> etat_nb + 1])
#else
//automate_t * automate_contracte_deterministe(const automate_t * automate, void * ceq_void)
automate_t * automate_contracte_deterministe(const automate_t * automate, const unsigned int ceq_nb, void (* ceq_void))
#endif
{
  automate_t * retour;
#if 1
  const bool (* ceq)[automate -> etat_nb + 1][automate -> etat_nb + 1] = ceq_void;
#endif


#if 0
  classe_nb = 0;

  for (unsigned int i = 1; i <= automate -> etat_nb; i++)
    for (unsigned int j = 1; j <= automate -> etat_nb; j++)
      if ((*ceq)[i][j]) {
        classe_nb ++;
        break;
      }
#else
  const unsigned int classe_nb = ceq_nb;
#endif

  retour = automate_make(classe_nb);

  // Bon, on suppose que les classes se suivent, ce qui nous convient pour la fonction ci-dessus.
  
  //retour -> etat_initial = classe_eq_indice(ceq, automate -> etat_initial, classe_nb);
  retour -> etat_initial = classe_eq_indice(classe_nb, automate -> etat_nb, ceq, automate -> etat_initial);


  for (unsigned int i = 0; i <= automate -> etat_nb; i++) {
    const unsigned int depart_indice = classe_eq_indice(classe_nb, automate -> etat_nb, ceq, i);
    for (unsigned int lettre_indice = 0; lettre_indice < 256; lettre_indice++)
      //if (0 != automate -> transition[i][lettre_indice]) 
      {
        const unsigned int arrivee_indice = classe_eq_indice(classe_nb, automate -> etat_nb, ceq, automate -> transition[i][lettre_indice]);
        retour -> transition[depart_indice][lettre_indice] = arrivee_indice;
      }
  }
  
  

  for (unsigned int i = 0; i <= automate -> etat_nb; i++) {
    if (automate -> etat_final_huh[i]) {
      const unsigned int depart_indice = classe_eq_indice(classe_nb, automate -> etat_nb, ceq, i);
      retour -> etat_final_huh[depart_indice] = true;
    }
  }
  
  
  return retour;
}








#if 0
//unsigned int classe_eq_indice(unsigned int classe_eq_nb, unsigned int etat_nb, bool (* classe_eq)[classe_eq_nb + 1][etat_nb + 1], unsigned int etat)
//unsigned int classe_eq_indice(unsigned int classe_eq_nb, unsigned int etat_nb, const bool (* classe_eq)[etat_nb + 1][etat_nb + 1], unsigned int etat)
unsigned int classe_eq_indice(unsigned int classe_eq_nb, unsigned int etat_nb, const bool (* classe_eq)[etat_nb+1][etat_nb+1], unsigned int etat)
#else
//unsigned int classe_eq_indice(const void (* classe_eq_void), unsigned int etat, unsigned int classe_eq_nb, unsigned int etat_nb)
unsigned int classe_eq_indice(unsigned int classe_eq_nb, unsigned int etat_nb, void (* classe_eq_void), unsigned int etat)
#endif
{
#if 1
  //const bool (* classe_eq)[classe_eq_nb][etat_nb] = classe_eq_void;
  const bool (* classe_eq)[etat_nb+1][etat_nb+1] = classe_eq_void;
#endif

  for (unsigned int i = 0; i <= classe_eq_nb; i++)
    if ((*classe_eq)[i][etat])
      return i;

  assert(false);
}


void bool_tab_inverser(bool etat_suivant[], unsigned int etat_nb) {
  for (unsigned int i = 0; i <= etat_nb; i++)
    etat_suivant[i] = not(etat_suivant[i]);
}









char * automate_to_c_function(const automate_t * automate, const char * c_function_name_base) {
  assert(automate_deterministe_huh(automate));

  char * c_function_string;

  c_function_string = strcopy("");

  stradd4(&c_function_string, "bool ", c_function_name_base, "_mot_reconnu_huh(const char * mot) {\n");

  stradd2(&c_function_string, "  unsigned int etat_courant;\n");
  stradd2(&c_function_string, "  unsigned int etat_suivant;\n");

  stradd2(&c_function_string, "  \n");

  stradd4(&c_function_string, "  etat_courant = ", uint_string(automate -> etat_initial), ";\n");
  stradd2(&c_function_string, "  \n");
  stradd2(&c_function_string, "  assert(NULL != mot);\n");
  stradd2(&c_function_string, "  const unsigned int len = strlen(mot);\n");
  stradd2(&c_function_string, "  unsigned char lettre;\n");
  stradd2(&c_function_string, "  \n");
  stradd2(&c_function_string, "  for (unsigned int i = 0; i < len; i++) {\n");
  stradd2(&c_function_string, "    \n");
  stradd2(&c_function_string, "    lettre = mot[i];\n");
  stradd2(&c_function_string, "    \n");
  //  stradd2(&c_function_string, "    etat_suivant = 0;\n");
  //  stradd2(&c_function_string, "    \n");
  stradd2(&c_function_string, "    switch (etat_courant) {\n");
  for (unsigned int i = 0; i <= automate -> etat_nb; i++) {
    stradd4(&c_function_string, "      case ", uint_string(i), ": {\n");
    stradd2(&c_function_string, "        switch (lettre) {\n");
    const unsigned int etat_transition_defaut = automate -> transition[i][0];
    for (unsigned int lettre_indice = 1; lettre_indice < 256; lettre_indice++)
      if (etat_transition_defaut != automate -> transition[i][lettre_indice])
        stradd8(&c_function_string, "          case ", uint_string(lettre_indice), ": etat_suivant = ", uint_string(automate -> transition[i][lettre_indice]), "; break; // case '", char_string(lettre_indice),"':\n");
    stradd4(&c_function_string, "          default: etat_suivant = ", uint_string(etat_transition_defaut),"; break;\n");
    stradd2(&c_function_string, "        }\n");
    stradd2(&c_function_string, "      }\n");
    stradd2(&c_function_string, "      break;\n");
  }
  stradd2(&c_function_string, "      default: assert(false); break;\n");
  stradd2(&c_function_string, "    }\n");
  stradd2(&c_function_string, "    \n");
  stradd2(&c_function_string, "    etat_courant = etat_suivant;\n");
  stradd2(&c_function_string, "  }\n");

  stradd2(&c_function_string, "  \n");
  stradd2(&c_function_string, "  \n");

  stradd2(&c_function_string, "  bool etat_final_huh;\n");
  stradd2(&c_function_string, "  switch (etat_courant) {\n");
  for (unsigned int i = 0; i <= automate -> etat_nb; i++)
    stradd6(&c_function_string, "    case ", uint_string(i), ": etat_final_huh = ", bool_string_c_tab[automate -> etat_final_huh[i]], "; break;\n");
  stradd2(&c_function_string, "    default: assert(false); break;\n");
  stradd2(&c_function_string, "  }\n");

  stradd2(&c_function_string, "  \n");
  stradd2(&c_function_string, "  \n");

  stradd2(&c_function_string, "  return etat_final_huh;\n");
  stradd2(&c_function_string, "}\n");


  return c_function_string;
}





char * automate_to_c_function_bis(const automate_t * const automate, const char * const c_function_name_base, const char * const function_storage, const bool definition_huh) {
  assert(automate_deterministe_huh(automate));

  char * function_storage_used;
  if (function_storage == NULL) function_storage_used = strcopy("");
  else {
    const size_t len = strlen(function_storage);
    if (len == 0) function_storage_used = strcopy("");
    else if (function_storage[len-1] == ' ') function_storage_used = strcopy(function_storage);
    else function_storage_used = strconcat(function_storage, " ");
  }

  char * c_function_string;

  c_function_string = strcopy("");

  // la fonction "etat_initial_get"
  stradd5(&c_function_string, function_storage_used, "int ", c_function_name_base, "_etat_initial_get(void)");
  if (not(definition_huh)) {
    stradd2(&c_function_string, ";\n");
  }
  else {
    stradd2(&c_function_string, " {\n");
    stradd4(&c_function_string, "  return ", uint_string(automate -> etat_initial), ";\n");
    stradd2(&c_function_string, "}\n");
    stradd2(&c_function_string, "\n");
    stradd2(&c_function_string, "\n");
  }
    
  // la fonction "etat_puits_huh"
  stradd5(&c_function_string, function_storage_used, "int ", c_function_name_base, "_etat_puits_huh(const int etat)");
  if (not(definition_huh)) {
    stradd2(&c_function_string, ";\n");
  }
  else {
    stradd2(&c_function_string, " {\n");
    stradd2(&c_function_string, "  return (0 == etat);\n");
    stradd2(&c_function_string, "}\n");
    stradd2(&c_function_string, "\n");
    stradd2(&c_function_string, "\n");
  }

  // la fonction "etat_final_huh"
  stradd5(&c_function_string, function_storage_used, "int ", c_function_name_base, "_etat_final_huh(const int etat)");
  if (not(definition_huh)) {
    stradd2(&c_function_string, ";\n");
  }
  else {
    stradd2(&c_function_string, " {\n");
    stradd2(&c_function_string, "  int etat_final_huh;\n");
    stradd2(&c_function_string, "  switch (etat) {\n");
    for (unsigned int i = 0; i <= automate -> etat_nb; i++) {
      //stradd6(&c_function_string, "    case ", uint_string(i), ": etat_final_huh = ", bool_string_c_tab[automate -> etat_final_huh[i]], "; break;\n");
      stradd6(&c_function_string, "    case ", uint_string(i), ": etat_final_huh = ", (automate -> etat_final_huh[i] ? "(0 == 0)": "(0 != 0)"), "; break;\n");
    }
    stradd2(&c_function_string, "    default: assert(0 != 0); etat_final_huh = (0 != 0); break;\n");
    stradd2(&c_function_string, "  }\n");
    stradd2(&c_function_string, "  return etat_final_huh;\n");
    stradd2(&c_function_string, "}\n");
    stradd2(&c_function_string, "\n");
    stradd2(&c_function_string, "\n");
  }

  // la fonction "etat_suivant_get"
  stradd5(&c_function_string, function_storage_used, "int ", c_function_name_base, "_etat_suivant_get(const int etat_courant, const char lettre)");
  if (not(definition_huh)) {
    stradd2(&c_function_string, ";\n");
  }
  else {
    stradd2(&c_function_string, " {\n");
    stradd2(&c_function_string, "  int etat_suivant;\n");
    stradd2(&c_function_string, "  switch (etat_courant) {\n");
    for (unsigned int i = 0; i <= automate -> etat_nb; i++) {
      stradd4(&c_function_string, "    case ", uint_string(i), ": {\n");
      stradd2(&c_function_string, "      switch (lettre) {\n");
      const unsigned int etat_transition_defaut = automate -> transition[i][0];
      for (unsigned int lettre_indice = 1; lettre_indice < 256; lettre_indice++)
        if (etat_transition_defaut != automate -> transition[i][lettre_indice])
          stradd8(&c_function_string, "        case ", uint_string(lettre_indice), ": etat_suivant = ", uint_string(automate -> transition[i][lettre_indice]), "; break; // case '", char_string_filtre(lettre_indice),"':\n");
      stradd4(&c_function_string, "        default: etat_suivant = ", uint_string(etat_transition_defaut),"; break;\n");
      stradd2(&c_function_string, "      }\n");
      stradd2(&c_function_string, "    }\n");
      stradd2(&c_function_string, "    break;\n");
    }
    stradd2(&c_function_string, "    default: assert((0 != 0)); etat_suivant = 0; break;\n");
    stradd2(&c_function_string, "  }\n");
    stradd2(&c_function_string, "  return etat_suivant;\n");
    stradd2(&c_function_string, "}\n");
    stradd2(&c_function_string, "\n");
    stradd2(&c_function_string, "\n");
  }

  // la fonction "mot_reconnu_huh"
  stradd5(&c_function_string, function_storage_used, "int ", c_function_name_base, "_mot_reconnu_huh(const char * mot)");
  if (not(definition_huh)) {
    stradd2(&c_function_string, ";\n");
  }
  else {
    stradd2(&c_function_string, " {\n");
    stradd2(&c_function_string, "  assert(NULL != mot);\n");
    stradd2(&c_function_string, "  const size_t len = strlen(mot);\n");
    stradd2(&c_function_string, "  \n");
    stradd4(&c_function_string, "  int etat = ", c_function_name_base, "_etat_initial_get();\n");
    stradd2(&c_function_string, "  \n");
    stradd2(&c_function_string, "  for (int i = 0; i < len; i++) {\n");
    stradd4(&c_function_string, "    etat = ", c_function_name_base, "_etat_suivant_get(etat, mot[i]);\n");
    stradd2(&c_function_string, "  }\n");
    stradd2(&c_function_string, "  \n");
    stradd2(&c_function_string, "  \n");
    stradd4(&c_function_string, "  return ", c_function_name_base, "_etat_final_huh(etat);\n");
    stradd2(&c_function_string, "}\n");
  }


  strfree(function_storage_used);

  return c_function_string;
}




char * automate_to_dotty(const automate_t * automate, const char * dotty_name_base) {
  char * dotty_string;
  
  const bool state0_meaningfull_huh = ((0 == automate -> etat_initial) || (automate -> etat_final_huh[0]));
  
  assert(not(string_contains_char_huh(dotty_name_base, ')')));
  assert(not(string_contains_char_huh(dotty_name_base, '(')));
  
  dotty_string = strcopy("");
  
  stradd4(&dotty_string, "subgraph ", dotty_name_base, " {\n");
  stradd2(&dotty_string, "  rankdir = LR;\n");
  // rotate=90 sets landscape mode.  (orientation=land is backward compatible but obsolete.)
  //stradd2(&dotty_string, "  rotate = 90;\n");
  stradd4(&dotty_string, "  label = \"", dotty_name_base, "\";\n");
  
  stradd2(&dotty_string, "  \n");
  
  // la fleche pour indiquer l'etat initial
  //stradd4(&dotty_string, "  ", dotty_name_base, "_initial [style = invis, label = false, fixedsize = true, height = 0, width = 0];\n");
  stradd4(&dotty_string, "  ", dotty_name_base, "_initial [style = invis, label = \"\", fixedsize = true, height = 0, width = 0];\n");
  stradd8(&dotty_string, "  ", dotty_name_base, "_initial -> ", dotty_name_base, "_", uint_string(automate -> etat_initial),";\n");
  stradd2(&dotty_string, "  \n");
  
  // chaque etat
  for (unsigned int i = (state0_meaningfull_huh?0:1); i <= automate -> etat_nb; i++) {
    stradd8(&dotty_string, "  ", dotty_name_base, "_", uint_string(i), " [label = \"", uint_string(i), "\"");
    if (automate -> etat_final_huh[i])
      stradd2(&dotty_string, ", style = bold");
    stradd2(&dotty_string, "];\n");
  }
  stradd2(&dotty_string, "  \n");
  
  // les fleches
  for (unsigned int i = 0; i <= automate -> etat_nb; i++) {
    const unsigned int etat_transition_defaut = automate -> transition[i][0];
    for (unsigned int lettre_indice = 1; lettre_indice < 256; lettre_indice++)
      if (etat_transition_defaut != automate -> transition[i][lettre_indice])
        stradd12(&dotty_string, "  ", dotty_name_base, "_", uint_string(i), " -> ", dotty_name_base, "_", uint_string(automate -> transition[i][lettre_indice]), " [label = \"'", char_string_filtre(lettre_indice), "'\"];\n");


    if (0 != etat_transition_defaut || state0_meaningfull_huh)
      stradd10(&dotty_string, "  ", dotty_name_base, "_", uint_string(i), " -> ", dotty_name_base, "_", uint_string(etat_transition_defaut), " [label = \"!\"];\n");
    
  }
  stradd2(&dotty_string, "  \n");
  
  // les epsilons transitions
  for (unsigned int i = 0; i <= automate -> etat_nb; i++)
    for (unsigned int j = 0; j <= automate -> etat_nb; j++) 
      if (automate -> transition_epsilon[i][j])
        stradd10(&dotty_string, "  ", dotty_name_base, "_", uint_string(i), " -> ", dotty_name_base, "_", uint_string(j), " [label = \"ε\"];\n");
  stradd2(&dotty_string, "  \n");
  
  stradd2(&dotty_string, "}\n");
  
  
  return dotty_string;
}




automate_t * automate_simplify(const automate_t * automate) {
  automate_t * automate1;
  automate_t * automate2;
  
  automate2 = automate_accessible(automate);
  automate1 = automate2;

  automate2 = automate_coaccessible(automate1);
  automate_free(automate1);
  automate1 = automate2;

  automate2 = automate_determinisation(automate1);
  automate_free(automate1);
  automate1 = automate2;

  automate2 = automate_accessible(automate1);
  automate_free(automate1);
  automate1 = automate2;

  automate2 = automate_coaccessible(automate1);
  automate_free(automate1);
  automate1 = automate2;

  automate2 = automate_minimisation(automate1);
  automate_free(automate1);
  automate1 = automate2;

  return automate1;
}

automate_t * automate_determinisation(const automate_t * automate) {
  return automate_des_parties_fin(automate);
}
