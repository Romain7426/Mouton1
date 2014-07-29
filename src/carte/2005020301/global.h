#ifndef GLOBAL_H
#define GLOBAL_H

const extern int get_nb_lignes(void);
const extern int get_nb_chars(void);
const extern int get_nb_chars_tot(void);
const extern int get_yyleng(void);
const extern char *get_yytext(void);
extern int yylex(void);


enum booleen {faux = 0, vrai = -1};
typedef enum booleen booleen;

typedef double corps;

const static corps pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068;

const static corps e = 2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178525166427;


/* Maintenant, on va mettre une sémantique au programme.
   Pour cela on déclare les structures objets. */

/* La structure de liste. */
struct liste {
  void *contenu;
  struct liste *suivant;
};

typedef struct liste *liste;

const extern liste liste_vide(void);
const extern liste mp(void *, liste);
const extern void raz(liste *);



/* Un point ou un vecteur, c'est la même chose. */
union tvecteur {
  corps coord[3];
  struct {corps x, y, z;} proj;
};

typedef union tvecteur *tvecteur;

const extern tvecteur new_vecteur(void);
const extern void del_vecteur(tvecteur *);


/* La partie physique. */
struct tphysique {
};

typedef struct tphysique *tphysique;

const extern tphysique new_physique(void);
const extern void del_physique(tphysique *);



/* Problème de la définition du code. */
typedef int *tcode;


/* Maintenant, la gestion du 'genere par' d'un évènement. */
enum tgenere {TOUS, AUCUN, CODE};
typedef enum tgenere tgenere;
struct sgenere {
  tgenere type;
  tcode code;
};
typedef struct sgenere *sgenere;
const extern sgenere new_sgenere(void);
const extern void del_sgenere(sgenere *);

/* On peut passer à la définition des évènements. */
struct tevent {
  tgenere genere;
  tcode par;
  tcode traitement;
};

typedef struct tevent *tevent;

const extern tevent new_event(void);
const extern void del_event(tevent *);


/* La partie gameplay. */
struct tgameplay {
  booleen arme;
  liste events;
};

typedef struct tgameplay *tgameplay;

const extern tgameplay new_gameplay(void);
const extern void del_gameplay(tgameplay *);



struct ttexture {
  char *image;
  unsigned int indice;
};
typedef struct ttexture *ttexture;
const extern ttexture new_texture(void);
const extern void del_texture(ttexture *);


struct tobjet {
  booleen anime;
  char *fichier;
  corps x, y, z;
  corps angle_x, angle_y, angle_z;
};
typedef struct tobjet *tobjet;
const extern tobjet new_objet(void);
const extern void del_objet(tobjet *);

/* La partie graphique. */
struct tgraphique {
  char *niveau;
  char *texture;
  liste textures;
  liste objets;
};
  
typedef struct tgraphique *tgraphique;
const extern tgraphique new_graphique(void);
const extern void del_graphique(tgraphique *);


/* Et enfin, l'aboutissement. */
struct tcarte {
  tphysique physique;
  tgameplay gameplay;
  tgraphique graphique;
};

typedef struct tcarte *tcarte;
const extern tcarte new_carte(void);
const extern void del_carte(tcarte *);




#endif /* GLOBAL_H */
