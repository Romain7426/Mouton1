#ifndef ANIME_GLOBAL_H
#define ANIME_GLOBAL_H

#include <stdio.h>

#define PREFIX anime
#define CDIR ".."
#define HDIR "../../include"
#define CONCAT(s,t) s ## t

extern FILE *yyanimein;
extern FILE *yyanimeout;

extern const  int anime_get_nb_lignes(void);
extern const  int anime_get_nb_chars(void);
extern const  int anime_get_nb_chars_tot(void);
extern const  int anime_get_yyleng(void);
extern const  char * anime_get_yytext(void);
extern const void anime_restart_lexer(void);

extern int yyanimeparse(void);

extern int yyanimelex(void);
extern void yyanimerestart(FILE *new_file);

//extern int memnbelts;
extern void anime_parser_reset(void);


//#include HDIR ## "/" ## "bonhomme.h"
//#include "../../include/bonhomme.h"
#include "bonhomme.hpp"

#include "anime/anime.hpp"


extern CBonhomme *bongars;



enum booleen {faux = 0, vrai = -1};
typedef enum booleen booleen;

typedef float corps;




enum anime_action {parler, voler};
typedef enum anime_action anime_action;
static const  int anime_nb_actions = 2;


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
extern void raz(liste* *);


/* Un point ou un vecteur, c'est la même chose. */
union tvecteur {
  corps coord[3];
  struct {corps x, y, z;} proj;
};

//typedef union tvecteur *tvecteur;

extern tvecteur* new_vecteur(void);
extern void del_vecteur(tvecteur* *);




struct anime_filsdesc {
char *qui;
corps x, y, z;
corps angle_y;
};

class anime_memdesc {
 public:
char *nom;
char *image;
liste *fils;
corps largeur, hauteur;
corps angle_max_y;
};





/* Problème de la définition du code. */
//typedef int *anime_tcode;
struct anime_tcode {
  char *fichier;
  char *proc;
};

extern anime_tcode *anime_new_code(void);
extern void anime_del_code(anime_tcode **);


/* Maintenant on définit les actions. */
struct anime_taction {
  booleen menu;
  char *affichage;
  anime_tcode gestionnaire;
};

//typedef struct taction *taction;

extern anime_taction *anime_new_action(void);
extern void anime_del_action(anime_taction *);


/* Maintenant, la gestion du 'genere par' d'un évènement. */
enum anime_tgenere {TOUS, AUCUN, CODE};
typedef enum anime_tgenere anime_tgenere;
struct anime_sgenere {
  anime_tgenere type;
  anime_tcode *code;
};
//typedef struct sgenere *sgenere;
extern anime_sgenere *anime_new_sgenere(void);
extern void anime_del_sgenere(anime_sgenere *);

/* On peut passer à la définition des évènements. */
struct anime_tevent {
  anime_tgenere genere;
  anime_tcode *par;
  anime_tcode *traitement;
};

//typedef struct tevent *tevent;

extern anime_tevent *anime_new_event(void);
extern void anime_del_event(anime_tevent *);


struct anime_tmembre {
  liste fils;
  char *image;
  corps largeur;
  corps hauteur;
  corps angle_y_max;
};
//typedef struct tmembre *tmembre;
extern anime_tmembre* anime_new_membre(void);
extern void anime_del_membre(anime_tmembre *);


struct anime_tfils {
  struct tmembre *qui;
  corps x, y, z;
  corps angle_y;
};
//typedef struct tfils *tfils;
extern anime_tfils* anime_new_fils(void);
extern void anime_del_fils(anime_tfils *);




#endif /* ANIME_GLOBAL_H */
