#ifndef AUTOMATE_H
#define AUTOMATE_H

struct automate_t {
  unsigned int etat_nb;
  unsigned int * * transition;
  bool * * transition_epsilon;
  bool * etat_final_huh;
  unsigned int etat_initial;
};

extern automate_t * automate_make(const unsigned int etat_nb);
extern void automate_raz(automate_t * automate);
extern void automate_free(automate_t * automate);
extern automate_t * automate_copy(const automate_t * automate);
extern void automate_copy_void(automate_t * automate_destination, const automate_t * automate_source);
extern char * automate_string_hard_hard(const automate_t * automate);
extern char * automate_string_hard(const automate_t * automate);
extern char * automate_string(const automate_t * automate);
extern bool automate_equal_hard_hard(const automate_t * automate1, const automate_t * automate2);
extern bool automate_equal_hard(const automate_t * automate1, const automate_t * automate2);
extern bool automate_equal(const automate_t * automate1, const automate_t * automate2);


extern void automate_transition_ajouter(automate_t * automate, char lettre, unsigned int etat_depart, unsigned int etat_arrive);
extern void automate_transition_defaut(automate_t * automate, unsigned int etat_depart, unsigned int etat_arrive);
extern void automate_transition_epsilon_ajouter(automate_t * automate, unsigned int etat_depart, unsigned int etat_arrive);
extern void automate_etat_initial_set(automate_t * automate, unsigned int etat_depart);
extern void automate_etat_initial_unset(automate_t * automate);
extern void automate_etat_final_set(automate_t * automate, unsigned int etat_depart);
extern void automate_etat_final_unset(automate_t * automate, unsigned int etat_depart);
extern void automate_etat_final_inverser(automate_t * automate);



#endif /* AUTOMATE_H */
