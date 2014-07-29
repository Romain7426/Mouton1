#ifndef NONANIMEGLOBAL_HPP
#define NONANIMEGLOBAL_HPP

//#include "../global.hpp"
#include "objnonanime.hpp"

extern const int nonanime_get_nb_lignes(void);
extern const int nonanime_get_nb_chars(void);
extern const int nonanime_get_nb_chars_tot(void);
extern const int nonanime_get_yyleng(void);
extern const char * nonanime_get_yytext(void);
extern int yynonanimelex(void);
extern void yynonanimerestart(FILE * new_file);
extern const void nonanime_restart_lexer(void);

//extern int eltnbelts;
extern void nonanime_reset_parser(void);

enum booleen {faux = 0, vrai = !0};
typedef enum booleen booleen;


typedef float corps;
/*
const static corps pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068;
const static corps e = 2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178525166427;
*/



/* La structure de liste. */
struct liste {
  void * contenu;
  struct liste * suivant;
};

extern liste * liste_vide(void);
extern liste * mp(void *, liste *);
extern const void raz(liste **);



struct nonanime_filsdesc {
char * qui;
corps x, y, z;
corps angle_x, angle_y, angle_z;
};

class nonanime_eltdesc {
 public:
char * nom;
char * image;
liste * fils;
};






enum nonanime_action {parler, voler};
typedef enum nonanime_action nonanime_action;
static const int nonanime_nb_actions = 2;


/* Maintenant, on va mettre une sémantique au programme.
   Pour cela on déclare les structures objets. */

/* Un point ou un vecteur, c'est la même chose. */
union tvecteur {
  corps coord[3];
  struct {corps x, y, z;} proj;
};

extern tvecteur* new_vecteur(void);
//const extern void del_vecteur(tvecteur **);
extern const void del_vecteur(tvecteur *);



/* La partie physique. */
struct nonanime_tphysique {
  tvecteur choc;
  corps masse;
  booleen compressible;
  booleen fixe;
  corps rebondissement;
};

extern nonanime_tphysique* nonanime_new_physique(void);
extern const void nonanime_del_physique(nonanime_tphysique* *);

/* Problème de la définition du code. */
//typedef int *nonanime_tcode;
struct nonanime_tcode {
  char * fichier;
  char * proc;
};

extern nonanime_tcode *nonanime_new_code(void);
extern void nonanime_del_code(nonanime_tcode **);



/* Maintenant on définit les actions. */
struct nonanime_taction {
  booleen menu;
  char * affichage;
  nonanime_tcode *gestionnaire;
};

extern nonanime_taction * nonanime_new_action(void);
extern const void nonanime_del_action(nonanime_taction * *);


/* Maintenant, la gestion du 'genere par' d'un évènement. */
enum nonanime_tgenere {TOUS, AUCUN, CODE};
typedef enum nonanime_tgenere nonanime_tgenere;
struct nonanime_sgenere {
  nonanime_tgenere type;
  nonanime_tcode * code;
};
extern nonanime_sgenere* nonanime_new_sgenere(void);
extern const void nonanime_del_sgenere(nonanime_sgenere * *);

/* On peut passer à la définition des évènements. */
struct nonanime_tevent {
  nonanime_tgenere genere;
  nonanime_tcode * par;
  nonanime_tcode * traitement;
};

extern nonanime_tevent * nonanime_new_event(void);
extern const void nonanime_del_event(nonanime_tevent * *);


/* La partie gameplay. */
struct nonanime_tgameplay {
  unsigned int vie;
  booleen invinsible;
  liste actions;
  liste events;
};

extern nonanime_tgameplay * nonanime_new_gameplay(void);
extern const void nonanime_del_gameplay(nonanime_tgameplay * *);



struct nonanime_telement {
  liste fils;
  char * image;
};
extern nonanime_telement* nonanime_new_element(void);
extern const void nonanime_del_element(nonanime_telement * *);


struct nonanime_tfils {
  struct nonanime_telement *qui;
  corps x, y, z;
  corps angle_x, angle_y, angle_z;
};
extern nonanime_tfils* nonanime_new_fils(void);
extern const void nonanime_del_fils(nonanime_tfils * *);

/* La partie graphique. */
struct nonanime_tgraphique {
  liste racines;
};
  
extern nonanime_tgraphique* nonanime_new_graphique(void);
extern const void nonanime_del_graphique(nonanime_tgraphique * *);


/* Et enfin, l'aboutissement. */
struct nonanime_tnonanime {
  nonanime_tphysique physique;
  nonanime_tgameplay gameplay;
  nonanime_tgraphique graphique;
};
extern nonanime_tnonanime* nonanime_new_nonanime(void);
extern const void nonanime_del_nonanime(nonanime_tnonanime * *);




#endif /* NONANIMEGLOBAL_HPP */
