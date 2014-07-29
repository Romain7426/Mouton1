#include "global.h"
#include "automate.h"


static inline automate_t * automate_allouer(void);


automate_t * automate_allouer(void) {
  return (automate_t *) malloc((sizeof (automate_t)));
};


automate_t * automate_make(const unsigned int etat_nb) {
  automate_t * retour;
  const unsigned int etat_nb_reel = etat_nb + 1; // il faut rajouter l'état puits!

  assert(0 != etat_nb_reel);

  retour = automate_allouer();

  retour -> etat_nb = etat_nb;

  retour -> transition = (unsigned int * *) malloc(etat_nb_reel * (sizeof (unsigned int *)));
  for (unsigned int i = 0; i < etat_nb_reel; i++) {
    retour -> transition[i] = (unsigned int *) malloc(256 * (sizeof (unsigned int)));
  }

  retour -> transition_epsilon = (bool * *) malloc(etat_nb_reel * (sizeof (bool *)));
  for (unsigned int i = 0; i < etat_nb_reel; i++) {
    retour -> transition_epsilon[i] = (bool *) malloc(etat_nb_reel * (sizeof (bool)));
  }

  retour -> etat_final_huh = (bool *) malloc(etat_nb_reel * (sizeof (bool)));

  automate_raz(retour);

  return retour;
};


void automate_raz(automate_t * automate) {
  const unsigned int etat_nb_reel = automate -> etat_nb + 1; // il faut rajouter l'état puits!

  for (unsigned int i = 0; i < etat_nb_reel; i++) {
    bzero(automate -> transition[i], 256 * (sizeof (unsigned int)));
  }

  for (unsigned int i = 0; i < etat_nb_reel; i++) {
    bzero(automate -> transition_epsilon[i], etat_nb_reel * (sizeof (bool)));
  }

  bzero(automate -> etat_final_huh, etat_nb_reel * (sizeof (bool)));

  automate -> etat_initial = 0;
}

void automate_free(automate_t * automate) {
  if (automate == NULL) return;
  free(automate -> transition);
  free(automate -> transition_epsilon);
  free(automate -> etat_final_huh);
  free(automate);
  return;
};


automate_t * automate_copy(const automate_t * automate) {
  automate_t * retour;
  
  if (NULL == automate) return NULL;

  retour = automate_make(automate -> etat_nb);

  automate_copy_void(retour, automate);
  
  return retour;
};


void automate_copy_void(automate_t * automate_destination, const automate_t * automate_source) {
  assert(automate_destination -> etat_nb >= automate_source -> etat_nb);

  if (automate_destination == automate_source) return;

  automate_raz(automate_destination);

  for (unsigned int i = 0; i <= automate_source -> etat_nb; i++)
    memcpy(automate_destination -> transition[i], automate_source -> transition[i], 256 * (sizeof (unsigned int)));

  for (unsigned int i = 0; i <= automate_source -> etat_nb; i++)
    memcpy(automate_destination -> transition_epsilon[i], automate_source -> transition_epsilon[i], (automate_source -> etat_nb + 1) * (sizeof (unsigned int)));

  memcpy(automate_destination -> etat_final_huh, automate_source -> etat_final_huh, (automate_source -> etat_nb + 1) * (sizeof (bool)));

  automate_destination -> etat_initial = automate_source -> etat_initial;
}


char * automate_string_hard_hard(const automate_t * automate) {
  return pointeur_string(automate);
}

char * automate_string_hard(const automate_t * automate) {
  char * retour;
  char * temp;
  
  retour = strcopy("");
  
  stradd2(&retour, "struct automate_t [");
  
  temp = unsigned_string(automate -> etat_nb);
  stradd3(&retour, "etat_nb = ", temp);
  strfree(temp);
  stradd2(&retour, ", ");
    
  temp = pointeur_string(automate -> transition);
  stradd3(&retour, "transition = ", temp);
  strfree(temp);
  stradd2(&retour, ", ");

  temp = pointeur_string(automate -> transition_epsilon);
  stradd3(&retour, "transition_epsilon = ", temp);
  strfree(temp);
  stradd2(&retour, ", ");

  temp = pointeur_string(automate -> etat_final_huh);
  stradd3(&retour, "etat_final_huh = ", temp);
  strfree(temp);
  stradd2(&retour, ", ");

  temp = unsigned_string(automate -> etat_initial);
  stradd3(&retour, "etat_initial = ", temp);
  strfree(temp);
  
  stradd2(&retour, "]");
  
  return retour;
}



// utiliser cette fonction pour plus de 255 états n'est pas raisonnable en temps
char * automate_string(const automate_t * automate) {
  char * retour;
  char * temp;
  
  retour = strcopy("");
  
  stradd2(&retour, "struct automate_t [");
  
  temp = unsigned_string(automate -> etat_nb);
  stradd3(&retour, "etat_nb = ", temp);
  strfree(temp);
  stradd2(&retour, ", ");
    
  
  stradd2(&retour, "transition = {");

  for (unsigned int i = 0; i <= automate -> etat_nb; i++) {
    unsigned int nb_printed = 0;


    //if (i < 32 || i == 0 || i == 1 || i == 2 || i == 3 || i == 6 || i == 36 || i == 104 || i == 144) {
    //if (true) {
    if (i < 256) {
    
      temp = unsigned_string(i);
      stradd4(&retour, "\netat ", temp, " [");
      strfree(temp);

      const unsigned int etat_transition_defaut = automate -> transition[i][0];
      
      for (int j = 1; j < 256; j++) {
        if (etat_transition_defaut != automate -> transition[i][j]) {
          if (0 != nb_printed)
            stradd2(&retour, ", ");
          
          if (0 == (nb_printed mod 16) && 0 != nb_printed)
            stradd2(&retour, "\n        ");
          
          temp = char_string_filtre(j);
          stradd4(&retour, "'", temp, "' -> ");
          strfree(temp);
          
          temp = unsigned_string(automate -> transition[i][j]);
          stradd2(&retour, temp);
          strfree(temp);
          
          nb_printed ++;
        }
      }

      if (0 != etat_transition_defaut) {
        if (0 != nb_printed)
          stradd2(&retour, ", ");
        stradd3(&retour, "defaut: ", uint_string(etat_transition_defaut));
      }
        
      stradd2(&retour, "], ");
    }

    else {

      temp = unsigned_string(i);
      stradd4(&retour, "etat ", temp, ": ");
      strfree(temp);
      
      temp = pointeur_string(automate -> transition[i]);
      stradd2(&retour, temp);
      strfree(temp);
      
      if (i !=  automate -> etat_nb)
        stradd2(&retour, ", ");
    }
  }

  stradd2(&retour, "}, ");


  
  stradd2(&retour, "transition_epsilon = {");

  {
    unsigned int nb_printed = 0;
    
    for (unsigned int i = 0; i <= automate -> etat_nb; i++) {
      for (unsigned int j = 0; j <= automate -> etat_nb; j++) {
        if (automate -> transition_epsilon[i][j]) {
          if (0 != nb_printed)
            stradd2(&retour, ", ");

          temp = unsigned_string(i);
          stradd3(&retour, temp, " -> ");
          strfree(temp);
          
          temp = unsigned_string(j);
          stradd2(&retour, temp);
          strfree(temp);

          nb_printed ++;
        }
      }
    }
  }

  stradd2(&retour, "}, ");




  stradd2(&retour, "etat_final_huh = {");

  { 
    unsigned int nb_printed = 0;

    for (unsigned int i = 0; i <= automate -> etat_nb; i++) {
      if (automate -> etat_final_huh[i]) {
        if (0 != nb_printed)
          stradd2(&retour, ", ");
        
        temp = unsigned_string(i);
        stradd2(&retour, temp);
        strfree(temp);
        
        nb_printed ++;
      }
    }
  }

  stradd2(&retour, "}, ");




  
  temp = unsigned_string(automate -> etat_initial);
  stradd3(&retour, "etat_initial = ", temp);
  strfree(temp);
  
  
  stradd2(&retour, "]");
  
  return retour;
};




bool automate_equal_hard_hard(const automate_t * automate1, const automate_t * automate2) {
  return (automate1 == automate2);
};


bool automate_equal_hard(const automate_t * automate1, const automate_t * automate2) {
  if (automate_equal_hard_hard(automate1, automate2))
    return true;

  return ((automate1 -> etat_nb == automate2 -> etat_nb)  && (pointeur_equal(automate1 -> transition, automate2 -> transition))  && (pointeur_equal(automate1 -> transition_epsilon, automate2 -> transition_epsilon))  && (pointeur_equal(automate1 -> etat_final_huh, automate2 -> etat_final_huh))  && (automate1 -> etat_initial == automate2 -> etat_initial));
};


bool automate_equal(const automate_t * automate1, const automate_t * automate2) {
  if (automate_equal_hard(automate1, automate2))
    return true;

  if (automate1 -> etat_nb != automate2 -> etat_nb)
    return false;

  for (unsigned int i = 0; i <= automate1 -> etat_nb; i++)
    for (int j = 0; j < 256; j++)
      if (automate1 -> transition[i][j] != automate2 -> transition[i][j]) 
        return false;

  for (unsigned int i = 0; i <= automate1 -> etat_nb; i++)
    for (unsigned int j = 0; j <= automate1 -> etat_nb; j++)
      if (automate1 -> transition_epsilon[i][j] != automate2 -> transition_epsilon[i][j])
        return false;

  for (unsigned int i = 0; i <= automate1 -> etat_nb; i++)
    if (automate1 -> etat_final_huh[i] != automate2 -> etat_final_huh[i])
      return false;

  if (automate1 -> etat_initial != automate2 -> etat_initial)
    return false;

  return true;
};








void automate_transition_ajouter(automate_t * automate, char lettre, unsigned int etat_depart, unsigned int etat_arrive) {
  unsigned int lettre_indice = ((unsigned int) ((unsigned char) lettre));

  assert(etat_depart != 0); // on ne peut pas sortir de l'état puits…!
  assert(etat_depart <= automate -> etat_nb);
  assert(etat_arrive <= automate -> etat_nb);

  automate -> transition[etat_depart][lettre_indice] = etat_arrive;
}

void automate_transition_defaut(automate_t * automate, unsigned int etat_depart, unsigned int etat_arrive) {
  assert(etat_depart != 0); // on ne peut pas sortir de l'état puits…!
  assert(etat_depart <= automate -> etat_nb);
  assert(etat_arrive <= automate -> etat_nb);

  for (unsigned int lettre_indice = 0; lettre_indice < 256; lettre_indice++)
    if (0 == automate -> transition[etat_depart][lettre_indice])
      automate -> transition[etat_depart][lettre_indice] = etat_arrive;

}

void automate_transition_epsilon_ajouter(automate_t * automate, unsigned int etat_depart, unsigned int etat_arrive) {
  assert(etat_depart != 0); // on ne peut pas sortir de l'état puits…!
  assert(etat_depart <= automate -> etat_nb);
  assert(etat_arrive <= automate -> etat_nb);

  automate -> transition_epsilon[etat_depart][etat_arrive] = true;
}

void automate_etat_initial_set(automate_t * automate, unsigned int etat_depart) {
  assert(etat_depart <= automate -> etat_nb);

  automate -> etat_initial = etat_depart;
}

void automate_etat_initial_unset(automate_t * automate) {
  automate -> etat_initial = 0;
}

void automate_etat_final_set(automate_t * automate, unsigned int etat_depart) {
  assert(etat_depart <= automate -> etat_nb);

  automate -> etat_final_huh[etat_depart] = true;
}

void automate_etat_final_unset(automate_t * automate, unsigned int etat_depart) {
  assert(etat_depart <= automate -> etat_nb);

  automate -> etat_final_huh[etat_depart] = false;
}


void automate_etat_final_inverser(automate_t * automate) {
  for (unsigned int i = 0; i <= automate -> etat_nb; i++)
    automate -> etat_final_huh[i] = not(automate -> etat_final_huh[i]);
}

