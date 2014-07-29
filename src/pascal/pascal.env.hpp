#ifndef PASCAL_ENV_HPP
#define PASCAL_ENV_HPP

//#include "global.hpp"
//#include "pascal/pascal.mem.hpp"


/* L'environnement est la table des symboles.
   C'est l� dedans qu'il y a les types, et le lien avec la m�moire
   (l'adresse).
   Ce qui est contenu dans l'environnement sont des DVals.
*/


struct pascal_dval {
  // On a rajout� le type valeur de retour car 
  // il doit r�ellement exister sur la pile.
  // En effet, lors d'appel r�cursif, la valeur de retour
  // doit pouvoir �tre conserv�e [f := 3; if f(5) = 4 then f++; f--;]
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
  // On diff�rencie la valeur de retour et la fonction,
  // car il n'y a aucune instance de la fonction.
  // Et la valeur de retour correspond � une instance de la fonction.
  // Il y a une valeur de retour par appel � la fonction.
  // C'est une variable qui se comporte diff�remment selon
  // qu'elle est lue ou �crite 
  // (dans la mesure o� elle peut ne pas prendre de param�tre).
  // Cette variable contient donc l'adresse m�moire de la fonction
  // (toujours la m�me, quelle que soit l'instance),
  // et l'adresse m�moire de la valeur de retour
  // (unique par instance).
  // Dor�navant, quand on fait un lookup sur le nom de la fonction,
  // on a deux cas : soit aucune instance et on tombe sur la fonction,
  // et alors il faut cr�er la valeur de retour associ�e,
  // soit une instance est d�j� en cours (r�cursivit�) et alors
  // il faut cr�er une nouvelle instance.
  // (M�me traitement � des circonstances diff�rentes.)
  // Cependant, lors d'une prise d'adresse d'une valeur de retour,
  // c'est bien �videmment celle de la fonction qu'on rendra.
  //typedef ploc tpdtretour;
  struct tpdretour {
    ploc read; // L'adresse du code de la fonction associ�e. Ne change pas avec l'instance (i.e. on appelle toujours la m�me fonction :-)).
    ploc write; // L'adresse de la valeur de retour associ�e � cet appel de function.
  };
  typedef ploc tpdtvar;

  union utype {
    // Pas de valeur associ�e � Dummy
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
  // pas besoin car ce sera toujours accompagn� d'un type (pdvalt)

  union utype val;

  // Besoin seulement obj dyn.
  // En l'occurrence, si constante string, alors dyn.
  struct pascal_dval * copy(bool iscstr) const;
};
typedef pascal_dval pdval;



// d�claration d'un type sans le d�finir � cause des cycles.
struct env_cell;
typedef class pliste<struct env_cell> * pascal_env;
typedef pascal_env penv;


class CPexpr;
class CPprog;

// Il faut mettre ce truc a l'exterieur car sinon Dev-Cpp plante...
struct pascal_dval_type;
typedef struct pascal_dval_type * tpdtpointer;

// Le type associ� � une DVal.
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


  // Fonction de conversion en une cha�ne de caract�re.
  char * toString(void) const;

  // Fonction qui donne le nombre de case m�moire qu'utilise ce type.
  unsigned int pdvaltype_sizeof(void);

  // Pas de constructeur, donc pas de destructeur.
  // On ne d�truit que les objets que l'on construit.
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
// Ce tableau est utilis� par tout le monde. 
// Comme il ne peut y avoir qu'une seule ex�cution de script � la fois c'est bon.
// Mais il faut bien penser � l'initialiser correctement et � sauvegarder sa valeur ensuite.
extern ptabdvaltypeuser tabdvaltypeuser; 
extern int ptabdvaltypeuser_lookup(const ptabdvaltypeuser tabdvaltypeuser, const char * ident, struct pascal_dval_type &dvaltype);

// L'�quivalent de penvdel et pmemdel.
extern void ptabdvaltypeuser_del(ptabdvaltypeuser &tabdvaltypeuser);











// Enfin, une dval typ�e.
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

// L'�quivalent de penvdel & co.
extern void pdvaltdel(pdvalt &dvalt);



// M�me chose ici.
// L'environnement a autorit� sur ses cellules.
// Tout ce qui est pass� en param�tre sera utilis� sans vergogne.



// Une cellule de l'environnement.
struct env_cell {
  const char * const ident;
  pdvalt dvalt;
  env_cell(const char * const ident, pdvalt dvalt) : ident(strcopy(ident)) {
    //this->ident = ident;
    this->dvalt = dvalt;
  }
  // Etant donne que c'est pas nous qui allouons ident, c'est pas � nous de le g�rer.
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


// plus haut � cause des cycles.
//typedef class pliste<struct env_cell> *pascal_env;
//typedef pascal_env penv;


extern const penv env0;

extern int penvupdate(penv env, const char * const ident, pdvalt dvalt, penv &res);
extern int penvmodify(penv env, const char *const ident, pdvalt dvalt);
extern int penvlookup(const penv env, const char * const ident, pdvalt &dvalt);
// Bien r�fl�chir l�-dessus : il y a un petit probl�me avec le gel de
// l'environnement pour les fonctions. Je propose qu'on ne d�truise jamais,
// jamais l'environnement : gain de place et de vitesse (enfin, la place...).
// Par contre, bien �tre s�r qu'un environnement est purement lecture seule.
extern int penvfree(penv &env, const penv env0);

// Cette fonction est l'�quivalente de pmemdel.
// Elle est � ex�cuter avant pmemdel si on veut un gain de m�moire plus important.
// cf pascal.mem.hpp pour plus d'info.
extern void penvdel(penv &env);


#endif /* PASCAL_ENV_HPP */
