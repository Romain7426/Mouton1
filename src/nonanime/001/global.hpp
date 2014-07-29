#ifndef NONANIMEGLOBAL_HPP
#define NONANIMEGLOBAL_HPP
#include "../global.h"
#include "../objnonanime.h"

const extern int get_nb_lignes(void);
const extern int get_nb_chars(void);
const extern int get_nb_chars_tot(void);
const extern int get_yyleng(void);
const extern char *get_yytext(void);
extern int yylex(void);


enum booleen {faux = 0, vrai = -1};
typedef enum booleen booleen;


typedef float corps;
/*
const static corps pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068;
const static corps e = 2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178525166427;
*/

enum action {parler, voler};
typedef enum action action;
const static int nb_actions = 2;


/* Maintenant, on va mettre une sémantique au programme.
   Pour cela on déclare les structures objets. */

/* La structure de liste. */
struct liste {
  void *contenu;
  struct liste *suivant;
};

extern liste* liste_vide(void);
extern liste* mp(void *, liste*);
const extern void raz(liste **);



/* Un point ou un vecteur, c'est la même chose. */
union tvecteur {
  corps coord[3];
  struct {corps x, y, z;} proj;
};

extern tvecteur* new_vecteur(void);
const extern void del_vecteur(tvecteur **);


/* La partie physique. */
struct tphysique {
  tvecteur choc;
  corps masse;
  booleen compressible;
  booleen fixe;
  corps rebondissement;
};

extern tphysique* new_physique(void);
const extern void del_physique(tphysique* *);

/* Problème de la définition du code. */
typedef int *tcode;


/* Maintenant on définit les actions. */
struct taction {
  booleen menu;
  char *affichage;
  tcode gestionnaire;
};

extern taction* new_action(void);
const extern void del_action(taction* *);


/* Maintenant, la gestion du 'genere par' d'un évènement. */
enum tgenere {TOUS, AUCUN, CODE};
typedef enum tgenere tgenere;
struct sgenere {
  tgenere type;
  tcode code;
};
extern sgenere* new_sgenere(void);
const extern void del_sgenere(sgenere* *);

/* On peut passer à la définition des évènements. */
struct tevent {
  tgenere genere;
  tcode par;
  tcode traitement;
};

extern tevent* new_event(void);
const extern void del_event(tevent* *);


/* La partie gameplay. */
struct tgameplay {
  unsigned int vie;
  booleen invinsible;
  liste actions;
  liste events;
};

extern tgameplay* new_gameplay(void);
const extern void del_gameplay(tgameplay* *);



struct telement {
  liste fils;
  char *image;
};
extern telement* new_element(void);
const extern void del_element(telement* *);


struct tfils {
  struct telement *qui;
  corps x, y, z;
  corps angle_x, angle_y, angle_z;
};
extern tfils* new_fils(void);
const extern void del_fils(tfils* *);

/* La partie graphique. */
struct tgraphique {
  liste racines;
};
  
extern tgraphique* new_graphique(void);
const extern void del_graphique(tgraphique* *);


/* Et enfin, l'aboutissement. */
struct tnonanime {
  tphysique physique;
  tgameplay gameplay;
  tgraphique graphique;
};
extern tnonanime* new_nonanime(void);
const extern void del_nonanime(tnonanime* *);




#endif /* NONANIMEGLOBAL_HPP */
