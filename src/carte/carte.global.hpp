#ifndef CARTE_GLOBAL_HPP
#define CARTE_GLOBAL_HPP

#include <stdio.h>
#include <stdarg.h>
#include "map.hpp"
#include "messages.hpp"

extern CMap * carte;


/* Fonctions du lexer. */
extern const int carte_get_nb_lignes(void);
extern const int carte_get_nb_chars(void);
extern const int carte_get_nb_chars_tot(void);
extern const int carte_get_yyleng(void);
extern const char * carte_get_yytext(void);
extern int yycartelex(void);
extern void yycarterestart(FILE * new_file);
extern const void carte_restart_lexer(void);

extern FILE * yycartein;
extern FILE * yycarteout;


/* Fonction du parser. */

extern int yycarteparse(void);
extern void carte_parser_reset(void);


/* Fonction de message. */
/*
extern void message(const char * mess, ...);
extern void messerr(const char * mess, ...);

extern void vmessage(const char * mess, va_list args);
extern void vmesserr(const char * mess, va_list args);
*/
extern void carte_mess(const char * mess, ...);
extern void carte_err(const char * mess, ...);






enum booleen {faux = 0, vrai = -1};
typedef enum booleen booleen;

typedef float corps;

/*
const static corps pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068;

const static corps e = 2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178525166427;
*/

/* Maintenant, on va mettre une sémantique au programme.
   Pour cela on déclare les structures objets. */

/* La structure de liste. */
struct liste {
  void *contenu;
  struct liste *suivant;
};

//typedef struct liste *liste;

extern liste * liste_vide(void);
extern liste * mp(void *, liste *);
extern const void raz(liste * *);



/* Un point ou un vecteur, c'est la même chose. */
union tvecteur {
  corps coord[3];
  struct {corps x, y, z;} proj;
};

//typedef union tvecteur *tvecteur;

extern tvecteur* new_vecteur(void);
extern const void del_vecteur(tvecteur* *);


/* La partie physique. */
struct carte_tphysique {
};

//typedef struct tphysique *tphysique;

extern const carte_tphysique* carte_new_physique(void);
extern const void carte_del_physique(carte_tphysique* *);



/* Problème de la définition du code. */
//typedef int *carte_tcode;
struct carte_tcode {
  const char *nom, *fichier;
};
extern carte_tcode* carte_new_code(void);
extern void carte_del_code(carte_tcode *(&code));

/* Maintenant, la gestion du 'genere par' d'un évènement. */
enum carte_tgenere {TOUS, AUCUN, CODE};
typedef enum carte_tgenere carte_tgenere;
struct carte_sgenere {
  carte_tgenere type;
  carte_tcode * code;
};
//typedef struct sgenere *sgenere;
extern carte_sgenere * carte_new_sgenere(void);
extern const void carte_del_sgenere(carte_sgenere * *);

/* On peut passer à la définition des évènements. */
struct carte_tevent {
  carte_tgenere genere;
  carte_tcode * par;
  carte_tcode * traitement;
};

//typedef struct tevent *tevent;

extern carte_tevent* carte_new_event(void);
extern const void carte_del_event(carte_tevent* *);


/* La partie gameplay. */
struct carte_tgameplay {
  booleen arme;
  liste events;
};

//typedef struct tgameplay *tgameplay;

extern const carte_tgameplay * carte_new_gameplay(void);
extern const void carte_del_gameplay(carte_tgameplay * *);



struct carte_ttexture {
  char *image;
  unsigned int indice;
};
//typedef struct ttexture *ttexture;
extern const carte_ttexture * carte_new_texture(void);
extern const void carte_del_texture(carte_ttexture * *);


struct carte_tobjet {
  booleen anime;
  char * fichier;
  corps x, y, z;
  corps angle_x, angle_y, angle_z;
};
//typedef struct tobjet *tobjet;
extern const carte_tobjet * carte_new_objet(void);
extern const void carte_del_objet(carte_tobjet * *);

/* La partie graphique. */
struct carte_tgraphique {
  char * niveau;
  char * texture;
  liste textures;
  liste objets;
};
  
//typedef struct tgraphique *tgraphique;
extern const carte_tgraphique* carte_new_graphique(void);
extern const void carte_del_graphique(carte_tgraphique* *);


/* Et enfin, l'aboutissement. */
struct carte_tcarte {
  carte_tphysique physique;
  carte_tgameplay gameplay;
  carte_tgraphique graphique;
};

//typedef struct tcarte *tcarte;
extern const carte_tcarte* carte_new_carte(void);
extern const void carte_del_carte(carte_tcarte* *);




#endif /* CARTE_GLOBAL_HPP */
