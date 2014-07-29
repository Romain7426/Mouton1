#ifndef PASCAL_ENV_HPP
#define PASCAL_ENV_HPP

//#include "global.hpp"
//#include "pascal/pascal.mem.hpp"


/* L'environnement est la table des symboles.
   C'est là dedans qu'il y a les types, et le lien avec la mémoire
   (l'adresse).
   Ce qui est contenu dans l'environnement sont des DVals.
*/


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
  typedef ploc tpdtvar;

  union utype {
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

  //enum etype type;
  // pas besoin car ce sera toujours accompagné d'un type (pdvalt)

  union utype val;

  // Besoin seulement obj dyn.
  // En l'occurrence, si constante string, alors dyn.
  struct pascal_dval * copy(bool iscstr) const;
};
typedef pascal_dval pdval;



// déclaration d'un type sans le définir à cause des cycles.
struct env_cell;
typedef class pliste<struct env_cell> * pascal_env;
typedef pascal_env penv;


class CPexpr;
class CPprog;

// Il faut mettre ce truc a l'exterieur car sinon Dev-Cpp plante...
struct pascal_dval_type;
typedef struct pascal_dval_type * tpdtpointer;

// Le type associé à une DVal.
struct pascal_dval_type {
  
  enum etype  {PDTDummy, PDTConstante, PDTBoolean, PDTInteger, PDTSubrange, PDTReal, PDTString, PDTPointer, PDTArray, PDTRecord, PDTProcedure, PDTFunction, PDTRetour, PDTUser, PDTVar};

  
  //typedef void tpdtdummy;
  //typedef void tpdtconstante;
  typedef enum {PCTDummyConstante, PCTBoolean, PCTInteger, PCTReal, PCTString} tpdtconstante;
  //typedef void tpdtboolean;
  //typedef void tpdtinteger;
  //typedef void tpdtsubrange;
  typedef struct {int min, max; class CPexpr *mine, *maxe;} tpdtsubrange;
  //typedef void tpdtreal;
  //typedef void tpdtstring;
  //typedef void tpdtpointer;
  //typedef const struct pascal_dval_type * const tpdtpointer;

  //typedef void tpdtarray;
  typedef struct {struct pascal_dval_type *type; tpdtsubrange indice;} tpdtarray;
  //typedef void tpdtrecord;
  //typedef struct {struct champ {const char *const nom; const pascal_dval_type *const type; champ(const char * const nom, const pascal_dval_type * const type) : nom(nom), type(type) {} champ* copy(void){champ *temp; temp = new champ(nom, type); return temp;}}; pliste<struct champ> *champs;} tpdtrecord;
  typedef struct {struct champ {const char * nom; pascal_dval_type * type; champ* copy(void){champ *temp; temp = new champ; temp->nom = strcopy(nom); temp->type = type->copy(); return temp;}}; pliste<struct champ> *champs;} tpdtrecord;
  //typedef void tpdtprocedure;
  typedef struct {penv env; struct param {bool var; char * nom; struct pascal_dval_type * dvaltype_ptr; param * copy(void) {param * temp; temp = new param; temp->var = this->var; temp->nom = strcopy(this->nom); temp->dvaltype_ptr = this->dvaltype_ptr->copy(); return temp;}}; class pliste<struct param> * params; CPprog * corps;} tpdtprocedure;
  //typedef void tpdtfunction;
  typedef struct _tpdtfunction : public tpdtprocedure {struct pascal_dval_type *type;} tpdtfunction;
  //typedef void tpdtretour;
  //typedef struct _tpdtretour {struct pascal_dval_type *type; struct pascal_dvalt *func;} tpdtretour; // structure pas terrible
  typedef struct _tpdtfunction tpdtretour; 
  //typedef void tpdtuser;
  typedef const char * tpdtuser;
  //typedef void tpdtvar;
  typedef struct pascal_dval_type *tpdtvar;

  


  union utype {
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
    tpdtvar       var;
  };


  enum etype type;
  union utype val;

  //pascal_dval_type(enum etype type, union utype val) : type(type), val(val) {}

  struct pascal_dval_type * copy(void) const ;


  // Fonction de conversion en une chaîne de caractère.
  char * toString(void) const;

  // Fonction qui donne le nombre de case mémoire qu'utilise ce type.
  unsigned int pdvaltype_sizeof(void);

  // Pas de constructeur, donc pas de destructeur.
  // On ne détruit que les objets que l'on construit.
  int del_pascal_dval_type(void);
  
};
typedef pascal_dval_type pdvaltype;




// Le tableau des types utilisateurs.
struct pascal_dval_type_user {
  char *nom;
  struct pascal_dval_type dvaltype;
};
typedef pascal_dval_type_user pdvaltypeuser;
typedef class pliste<pdvaltypeuser> *pascal_tab_type_user;
typedef pascal_tab_type_user ptabdvaltypeuser;
extern const ptabdvaltypeuser tabdvaltypeuser0;
// Ce tableau est utilisé par tout le monde. 
// Comme il ne peut y avoir qu'une seule exécution de script à la fois c'est bon.
// Mais il faut bien penser à l'initialiser correctement et à sauvegarder sa valeur ensuite.
extern ptabdvaltypeuser tabdvaltypeuser; 
extern int ptabdvaltypeuser_lookup(const ptabdvaltypeuser tabdvaltypeuser, const char * ident, struct pascal_dval_type &dvaltype);

// L'équivalent de penvdel et pmemdel.
extern void ptabdvaltypeuser_del(ptabdvaltypeuser &tabdvaltypeuser);











// Enfin, une dval typée.
struct pascal_dvalt {
  pdvaltype type;
  pdval val;
  struct pascal_dvalt * copy(void) {
    struct pascal_dvalt *temp; 
    temp = new struct pascal_dvalt; 
    temp -> type = *(type.copy());
    temp -> val = *(val.copy(type.type == pdvaltype::PDTConstante && type.val.c == pdvaltype::PCTString));
    return temp;
  }
  static int pdvalt_of_pdvaltype(const struct pascal_dval_type dvaltype, const ploc i, struct pascal_dvalt &dvalt);
};
typedef pascal_dvalt pdvalt;

// L'équivalent de penvdel & co.
extern void pdvaltdel(pdvalt &dvalt);



// Même chose ici.
// L'environnement a autorité sur ses cellules.
// Tout ce qui est passé en paramètre sera utilisé sans vergogne.



// Une cellule de l'environnement.
struct env_cell {
  const char * const ident;
  pdvalt dvalt;
  env_cell(const char * const ident, pdvalt dvalt) : ident(strcopy(ident)) {
    //this->ident = ident;
    this->dvalt = dvalt;
  }
  // Etant donne que c'est pas nous qui allouons ident, c'est pas à nous de le gérer.
  // TODO Bad comportement bad!! Sans doute source de nombreux bugs!
  /*
  ~env_cell(void) {
    delete ident;
  }
  */
  env_cell * copy(void) {
    return new env_cell(ident, dvalt);
  }
};


// plus haut à cause des cycles.
//typedef class pliste<struct env_cell> *pascal_env;
//typedef pascal_env penv;


extern const penv env0;

extern int penvupdate(penv env, const char * const ident, pdvalt dvalt, penv &res);
extern int penvmodify(penv env, const char *const ident, pdvalt dvalt);
extern int penvlookup(const penv env, const char * const ident, pdvalt &dvalt);
// Bien réfléchir là-dessus : il y a un petit problème avec le gel de
// l'environnement pour les fonctions. Je propose qu'on ne détruise jamais,
// jamais l'environnement : gain de place et de vitesse (enfin, la place...).
// Par contre, bien être sûr qu'un environnement est purement lecture seule.
extern int penvfree(penv &env, const penv env0);

// Cette fonction est l'équivalente de pmemdel.
// Elle est à exécuter avant pmemdel si on veut un gain de mémoire plus important.
// cf pascal.mem.hpp pour plus d'info.
extern void penvdel(penv &env);


#endif /* PASCAL_ENV_HPP */
