#ifndef ANIME_GLOBAL_H
#define ANIME_GLOBAL_H


#include "anime.h"
#include "../bonhomme.h"
extern void yyrestart(FILE *new_file);

extern CBonhomme *bongars;



enum booleen {faux = 0, vrai = -1};
typedef enum booleen booleen;

typedef float corps;




enum action {parler, voler};
typedef enum action action;
static const  int nb_actions = 2;


/* Maintenant, on va mettre une sémantique au programme.
   Pour cela on déclare les structures objets. */

/* La structure de liste. */
struct liste {
  void *contenu;
  struct liste *suivant;
};

//typedef struct liste *liste;

extern liste *liste_vide(void);
extern liste *mp(void *, liste*);
extern void raz(liste *);




struct filsdesc {
char *qui;
corps x, y, z;
corps angle_y;
};

class memdesc {
 public:
char *nom;
char *image;
liste *fils;
corps largeur, hauteur;
corps angle_max_y;
};





/* Un point ou un vecteur, c'est la même chose. */
union tvecteur {
  corps coord[3];
  struct {corps x, y, z;} proj;
};

//typedef union tvecteur *tvecteur;

extern tvecteur* new_vecteur(void);
extern void del_vecteur(tvecteur *);


/* Problème de la définition du code. */
typedef int *tcode;


/* Maintenant on définit les actions. */
struct taction {
  booleen menu;
  char *affichage;
  tcode gestionnaire;
};

//typedef struct taction *taction;

extern taction *new_action(void);
extern void del_action(taction *);


/* Maintenant, la gestion du 'genere par' d'un évènement. */
enum tgenere {TOUS, AUCUN, CODE};
typedef enum tgenere tgenere;
struct sgenere {
  tgenere type;
  tcode code;
};
//typedef struct sgenere *sgenere;
extern sgenere *new_sgenere(void);
extern void del_sgenere(sgenere *);

/* On peut passer à la définition des évènements. */
struct tevent {
  tgenere genere;
  tcode par;
  tcode traitement;
};

//typedef struct tevent *tevent;

extern tevent *new_event(void);
extern void del_event(tevent *);


struct tmembre {
  liste fils;
  char *image;
  corps largeur;
  corps hauteur;
  corps angle_y_max;
};
//typedef struct tmembre *tmembre;
extern tmembre* new_membre(void);
extern void del_membre(tmembre *);


struct tfils {
  struct tmembre *qui;
  corps x, y, z;
  corps angle_y;
};
//typedef struct tfils *tfils;
extern tfils* new_fils(void);
extern void del_fils(tfils *);




#endif /* ANIME_GLOBAL_H */
