#ifndef NONANIMEGLOBAL_H
#define NONANIMEGLOBAL_H
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

/*
typedef double corps;
const static corps pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068;
const static corps e = 2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178525166427;
*/

enum action {parler, voler};
typedef enum action action;
const static int nb_actions = 2;


/* Maintenant, on va mettre une s�mantique au programme.
   Pour cela on d�clare les structures objets. */

/* La structure de liste. */
struct liste {
  void *contenu;
  struct liste *suivant;
};

const extern liste* liste_vide(void);
const extern liste* mp(void *, liste*);
const extern void raz(liste **);



/* Un point ou un vecteur, c'est la m�me chose. */
union tvecteur {
  corps coord[3];
  struct {corps x, y, z;} proj;
};

const extern tvecteur* new_vecteur(void);
const extern void del_vecteur(tvecteur **);


/* La partie physique. */
struct tphysique {
  tvecteur choc;
  corps masse;
  booleen compressible;
  booleen fixe;
  corps rebondissement;
};

const extern tphysique* new_physique(void);
const extern void del_physique(tphysique* *);

/* Probl�me de la d�finition du code. */
typedef int *tcode;


/* Maintenant on d�finit les actions. */
struct taction {
  booleen menu;
  char *affichage;
  tcode gestionnaire;
};

const extern taction* new_action(void);
const extern void del_action(taction* *);


/* Maintenant, la gestion du 'genere par' d'un �v�nement. */
enum tgenere {TOUS, AUCUN, CODE};
typedef enum tgenere tgenere;
struct sgenere {
  tgenere type;
  tcode code;
};
const extern sgenere* new_sgenere(void);
const extern void del_sgenere(sgenere* *);

/* On peut passer � la d�finition des �v�nements. */
struct tevent {
  tgenere genere;
  tcode par;
  tcode traitement;
};

const extern tevent* new_event(void);
const extern void del_event(tevent* *);


/* La partie gameplay. */
struct tgameplay {
  unsigned int vie;
  booleen invinsible;
  liste actions;
  liste events;
};

const extern tgameplay* new_gameplay(void);
const extern void del_gameplay(tgameplay* *);



struct telement {
  liste fils;
  char *image;
};
typedef struct telement *telement;
const extern telement new_element(void);
const extern void del_element(telement *);


struct tfils {
  struct telement *qui;
  corps x, y, z;
  corps angle_x, angle_y, angle_z;
};
typedef struct tfils *tfils;
const extern tfils new_fils(void);
const extern void del_fils(tfils *);

/* La partie graphique. */
struct tgraphique {
  liste racines;
};
  
typedef struct tgraphique *tgraphique;
const extern tgraphique new_graphique(void);
const extern void del_graphique(tgraphique *);


/* Et enfin, l'aboutissement. */
struct tnonanime {
  tphysique physique;
  tgameplay gameplay;
  tgraphique graphique;
};

typedef struct tnonanime *tnonanime;
const extern tnonanime new_nonanime(void);
const extern void del_nonanime(tnonanime *);




#endif /* NONANIMEGLOBAL_H */
