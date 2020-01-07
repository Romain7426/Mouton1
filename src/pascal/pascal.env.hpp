#ifndef PASCAL_ENV_HPP
#define PASCAL_ENV_HPP

/* L'environnement est la table des symboles.
   C'est là dedans qu'il y a les types, et le lien avec la mémoire
   (l'adresse).
   Ce qui est contenu dans l'environnement sont des DVals.
*/


typedef struct pascal_dval_type * tpdtpointer;








typedef union {bool b; int i; corps r; const char *str;} tpdconstante;
typedef ploc tpdboolean;
typedef ploc tpdinteger;
typedef ploc tpdsubrange;
typedef ploc tpdreal;
typedef ploc tpdstring;
typedef ploc tpdpointer;
typedef ploc tpdarray;
typedef ploc tpdrecord;
typedef ploc tpdprocedure;
typedef ploc tpdfunction;
// On différencie la valeur de retour et la fonction,
// car il n'y a aucune instance de la fonction.
// Et la valeur de retour correspond à une instance de la fonction.
// Il y a une valeur de retour par appel à la fonction.
// C'est une variable qui se comporte différemment selon
// qu'elle est lue ou écrite 
// (dans la mesure où elle peut ne pas prendre de paramètre).
// Cette variable contient donc l'adresse mémoire de la fonction
// (toujours la même, quelle que soit l'instance),
// et l'adresse mémoire de la valeur de retour
// (unique par instance).
// Dorénavant, quand on fait un lookup sur le nom de la fonction,
// on a deux cas : soit aucune instance et on tombe sur la fonction,
// et alors il faut créer la valeur de retour associée,
// soit une instance est déjà en cours (récursivité) et alors
// il faut créer une nouvelle instance.
// (Même traitement à des circonstances différentes.)
// Cependant, lors d'une prise d'adresse d'une valeur de retour,
// c'est bien évidemment celle de la fonction qu'on rendra.
//typedef ploc tpdtretour;
struct tpdretour {
  ploc read; // L'adresse du code de la fonction associée. Ne change pas avec l'instance (i.e. on appelle toujours la même fonction :-)).
  ploc write; // L'adresse de la valeur de retour associée à cet appel de function.
};
typedef struct tpdretour tpdretour; 
typedef ploc tpdtvar;

union pascal_dval_utype {
  // Pas de valeur associée à Dummy
  tpdconstante c;
  tpdboolean   b;
  tpdinteger   i;
  tpdsubrange  s;
  tpdreal      r;
  tpdstring    str;
  tpdpointer   ptr;
  tpdarray     array;
  tpdrecord    record;
  tpdprocedure proc;
  tpdfunction  func;
  tpdretour ret;
  tpdtvar var;
};



struct pascal_dval {
  // On a rajouté le type valeur de retour car 
  // il doit réellement exister sur la pile.
  // En effet, lors d'appel récursif, la valeur de retour
  // doit pouvoir être conservée [f := 3; if f(5) = 4 then f++; f--;]
  //  enum etype {PDTDummyDVal, PDTConstante, PDTBoolean, PDTInteger, PDTSubrange, PDTReal, PDTString, PDTPointer, PDTArray, PDTRecord, PDTProcedure, PDTFunction, PDTRetour};

  //typedef void tptddummydVal;
  /*
  struct tpdconstante {
        enum etype {PCTDummyConstante, PCTBoolean, PCTInteger, PCTSubrange, PCTReal, PCTString};
    union utype {
      bool b;
      int i;
      corps r;
      char *str;
    };

    enum etype type;
    union utype utype;
  };
  */
  //enum etype type;
  // pas besoin car ce sera toujours accompagné d'un type (pdvalt)

  union pascal_dval_utype val;

  // Besoin seulement obj dyn.
  // En l'occurrence, si constante string, alors dyn.
  //struct pascal_dval * copy(bool iscstr) const;
};
typedef struct pascal_dval pascal_dval;
typedef pascal_dval pdval;

#if 0 
// L'équivalent de penvdel & co.
extern void pdvaltdel(pdvalt &dvalt);

static int pdvalt_of_pdvaltype(const struct pascal_dval_type dvaltype, const ploc i, struct pascal_dvalt &dvalt);

struct pascal_dvalt * copy(void) {
  struct pascal_dvalt *temp; 
  temp = new struct pascal_dvalt; 
  temp -> type = *(type.copy());
  temp -> val = *(val.copy(type.type == pdvaltype::PDTConstante && type.val.c == pdvaltype::PCTString));
  return temp;
}; 




// déclaration d'un type sans le définir à cause des cycles.
struct env_cell;
typedef struct pliste<struct env_cell> * pascal_env;
typedef pascal_env penv;


struct CPexpr;
struct CPprog;






// Le tableau des types utilisateurs.
enum { pascal_dval_type_user__size = 127 }; 
struct pascal_dval_type_user {
  char *nom[pascal_dval_type_user__size];
  struct pascal_dval_type dvaltype[pascal_dval_type_user__size];
  int nb; 
};
struct pascal_dval_type_user; 
typedef struct pascal_dval_type_user pascal_dval_type_user;
typedef pascal_dval_type_user pdvaltypeuser;
typedef struct pliste<pdvaltypeuser> *pascal_tab_type_user;
typedef pascal_tab_type_user ptabdvaltypeuser;
extern const ptabdvaltypeuser tabdvaltypeuser0;
// Ce tableau est utilisé par tout le monde. 
// Comme il ne peut y avoir qu'une seule exécution de script à la fois c'est bon.
// Mais il faut bien penser à l'initialiser correctement et à sauvegarder sa valeur ensuite.
extern ptabdvaltypeuser tabdvaltypeuser; 
extern int ptabdvaltypeuser_lookup(const ptabdvaltypeuser tabdvaltypeuser, const char * ident, struct pascal_dval_type &dvaltype);

// L'équivalent de penvdel et pmemdel.
extern void ptabdvaltypeuser_del(ptabdvaltypeuser &tabdvaltypeuser);



#endif 


enum pascal_dval_type_etype { PDTDummy, PDTConstante, PDTBoolean, PDTInteger, PDTSubrange, PDTReal, PDTString, PDTPointer, PDTArray, PDTRecord, PDTProcedure, PDTFunction, PDTRetour, PDTUser, PDTVar }; 
typedef enum { PCTDummyConstante, PCTBoolean, PCTInteger, PCTReal, PCTString } tpdtconstante;
typedef struct { int min, max; struct CPexpr *mine, *maxe;} tpdtsubrange;
typedef struct {struct pascal_dval_type *type; tpdtsubrange indice;} tpdtarray;
enum { tpdtrecord_size = 17 }; 
typedef struct {
  char * nom[tpdtrecord_size]; 
  pascal_dval_type * type[tpdtrecord_size]; 
  int nb; 
} tpdtrecord;
enum { tpdtprocedure_size = 63 }; 
typedef struct {
  penv * env; 
  bool param_var[tpdtprocedure_size]; 
  char * param_nom[tpdtprocedure_size]; 
  struct pascal_dval_type * param_type[tpdtprocedure_size]; 
  int param_nb; 
  CPprog * corps;
  struct pascal_dval_type *type; // pour fonction 
} tpdtprocedure;
typedef tpdtprocedure tpdtfunction; 
typedef tpdtfunction tpdtretour; 
typedef const char * tpdtuser;
typedef struct pascal_dval_type * tpdtvar_u;

union pascal_dval_type_utype {
  //tpdtdummy     d;
  tpdtconstante c;
  //tpdtboolean   b;
  //tpdtinteger   i;
  tpdtsubrange  s;
  //tpdtreal      r;
  //tpdtstring    str;
  tpdtpointer   ptr;
  tpdtarray     array;
  tpdtrecord    record;
  tpdtprocedure proc;
  tpdtfunction  func;
  tpdtretour    ret;
  tpdtuser      user;
  tpdtvar_u       var;
};

// Le type associé à une DVal.
struct pascal_dval_type {
  enum pascal_dval_type_etype type;
  union pascal_dval_type_utype val;

  struct pascal_dval_type * (* copy)(const pascal_dval_type * this);

  // Fonction de conversion en une chaîne de caractère.
  char * (* toString)(const pascal_dval_type * this); 
};


// Fonction qui donne le nombre de case mémoire qu'utilise ce type.
unsigned int pdvaltype_sizeof(const pascal_dval_type * this);

// Pas de constructeur, donc pas de destructeur.
// On ne détruit que les objets que l'on construit.
//int del_pascal_dval_type(void);
  


// Enfin, une dval typée.
struct pascal_dvalt {
  pdvaltype type;
  pdval val;
  //int val; 
};

enum { pascal_env_size = 127 }; 
struct pascal_env { 
  char * ident[pascal_env_size];
  pdvalt dvalt[pascal_env_size];
  //int dvalt[pascal_env_size];
  int nb; 
  struct pascal_env * (* copy)(const struct pascal_env * this); 
}; 













// Même chose ici.
// L'environnement a autorité sur ses cellules.
// Tout ce qui est passé en paramètre sera utilisé sans vergogne.




// plus haut à cause des cycles.
//typedef struct pliste<struct env_cell> *pascal_env;
//typedef pascal_env penv;


extern const penv env0;

extern int penvupdate(penv * env, const char * const ident, pdvalt dvalt, penv * res_ref);
extern int penvmodify(penv * env, const char *const ident, pdvalt dvalt);
extern int penvlookup(const penv * env, const char * const ident, pdvalt * dvalt_ref);
// Bien réfléchir là-dessus : il y a un petit problème avec le gel de
// l'environnement pour les fonctions. Je propose qu'on ne détruise jamais,
// jamais l'environnement : gain de place et de vitesse (enfin, la place...).
// Par contre, bien être sûr qu'un environnement est purement lecture seule.
extern int penvfree(penv * env, const penv env0);

// Cette fonction est l'équivalente de pmemdel.
// Elle est à exécuter avant pmemdel si on veut un gain de mémoire plus important.
// cf pascal.mem.hpp pour plus d'info.
extern void penvdel(penv * env);
#endif /* PASCAL_ENV_HPP */
