#ifndef AUTOMATE_METHODE_H
#define AUTOMATE_METHODE_H


extern bool automate_deterministe_huh(const automate_t * automate);


extern bool automate_mot_reconnu_huh(const automate_t * automate, const char * mot);
extern bool automate_mot_reconnu_huh_deterministe(const automate_t * automate, const char * mot);
extern bool automate_mot_reconnu_huh_non_deterministe(const automate_t * automate, const char * mot);


extern automate_t * automate_des_parties_bourrin(const automate_t * automate);
extern automate_t * automate_des_parties_bourrin32(const automate_t * automate);
extern automate_t * automate_des_parties_bourrin_unlimited(const automate_t * automate);
extern automate_t * automate_des_parties_fin(const automate_t * automate);


extern automate_t * automate_accessible(const automate_t * automate);
extern automate_t * automate_accessible_deterministe(const automate_t * automate);
extern automate_t * automate_accessible_non_deterministe(const automate_t * automate);

extern automate_t * automate_coaccessible(const automate_t * automate);
extern automate_t * automate_coaccessible_deterministe(const automate_t * automate);
extern automate_t * automate_coaccessible_non_deterministe(const automate_t * automate);

extern automate_t * automate_emonde(const automate_t * automate);
extern automate_t * automate_emonde_deterministe(const automate_t * automate);


// graphe partiel: on enlève des arrêtes
// sous-graphe: on enlève des sommets
// graphe contracté: …
extern automate_t * automate_sous(const automate_t * automate, const bool * etat);
extern automate_t * automate_sous_deterministe(const automate_t * automate, const bool * etat);
extern automate_t * automate_sous_non_deterministe(const automate_t * automate, const bool * etat);

#if 0
extern automate_t * automate_contracte(const automate_t * automate, const bool (* ceq)[][]);
extern automate_t * automate_contracte_deterministe(const automate_t * automate, const bool (* ceq)[][]);
#else
extern automate_t * automate_contracte(const automate_t * automate, void * ceq);
//extern automate_t * automate_contracte_deterministe(const automate_t * automate, void * ceq);
//extern automate_t * automate_contracte_deterministe(const automate_t * automate, unsigned int ceq_nb, const bool (* ceq)[ceq_nb + 1][automate -> etat_nb + 1]);
//extern automate_t * automate_contracte_deterministe(const automate_t * automate, unsigned int ceq_nb, const bool (* ceq)[automate -> etat_nb + 1][automate -> etat_nb + 1]);
extern automate_t * automate_contracte_deterministe(const automate_t * automate, unsigned int ceq_nb, void (* ceq));

#endif


extern automate_t * automate_minimisation(const automate_t * automate);
extern automate_t * automate_minimisation_deterministe(const automate_t * automate);

extern automate_t * automate_determinisation(const automate_t * automate);

extern automate_t * automate_simplify(const automate_t * automate);



// BOF!!! car inverser n'est pas déterministe!!!
#if 0
extern automate_t * automate_inverser(const automate_t * automate);
#endif

extern automate_t * automate_complementaire(const automate_t * automate);


extern char * automate_to_c_function(const automate_t * automate, const char * c_function_name_base);
//extern char * automate_to_c_function_bis(const automate_t * automate, const char * c_function_name_base);
extern char * automate_to_c_function_bis(const automate_t * const automate, const char * const c_function_name_base, const char * const function_storage, const bool definition_huh);
extern char * automate_to_dotty(const automate_t * automate, const char * dotty_name_base);





#endif /* AUTOMATE_METHODE_H */

