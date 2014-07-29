#ifndef PASCAL_EXPR_HPP
#define PASCAL_EXPR_HPP

#ifndef PASCAL_PROG_HPP
#define PASCAL_PROG_HPP

#include "pascal/pascal.tools.hpp"
#include "pascal/pascal.mem.hpp"
#include "pascal/pascal.env.hpp"

#undef PASCAL_PROG_HPP
#endif



/* Ce fichier contient la d�finition d'une valeur rendue par une expression,
   ainsi que la d�finition d'une expression.
   Ainsi, dans les fonctions d'�valuations associ�es (R & L),
   on aura l'interpr�teur du moteur pascal pour les expressions.
*/
/* Au fait, dor�nanvant on sp�cifie bien la politique pour le passage de param�tre.
   Tout ce qui est pass� en param�tre est plus que susceptible d'�tre chang�,
   et mettre d'�tre utilis� d�finitivement.
   C'est source de tr�s gros ennuis, notamment pour 
   toutes les structures allou�es sur la pile et non sur le tas.
   Cela permet d'�viter d'�crire un constructeur de recopie pour chaque type d�fini.
   Aussi, cela permet d'utiliser la recopie quand cela n'est pas n�cessaire.
   En th�orie, c'est ce que l'on devrait faire.
   Dans les scenarios, on met donc un jour, v�rifier que la recopie se passe bien.
   En plus cela pose le probl�me de savoir qui en est le responsable
   et qui doit donc le d�truire? (probl�me de toute variable partag�es.)
*/
   


struct pascal_eval_type;
typedef struct pascal_eval_type pevaltype;

struct pascal_eval;
typedef struct pascal_eval peval;

struct pascal_evalt;
typedef struct pascal_evalt pevalt;

class CPexpr;


// D'abord la d�finition du type EVal.
// C'est un type en union disjointe, il suit donc la d�finition habituelle.
// PETVide est uniquement l� pour typer le pointeur nil; nil est un pointeur vers tous les types.
// Et il est impossible d'acc�der directement � ce type.
struct pascal_eval_type {
  enum etype {PETDummy, PETBoolean, PETInteger, PETSubrange, PETReal, PETString, PETPointer, PETArray, PETRecord, PETVide, /*PETUser*/};

  union utype {
    //typedef void tpetdummy;
    //typedef void tpetboolean;
    //typedef void tpetinteger;
    //typedef void tpetsubrange;
    struct tpetsubrange {
      int min, max;
    };
    //typedef void tpetreal;
    //typedef void tpetstring;
    //typedef void tpetpointer;
    typedef pascal_eval_type *tpetpointer;
    //typedef void tpetarray;
    struct tpetarray {
      struct pascal_eval_type *type;
      struct tpetsubrange indice;
    };
    //typedef void tpetrecord;
    struct tpetrecord {
      struct champ {
	char *nom;
	struct pascal_eval_type *type;
      };
      class pliste<struct champ> *champs;
    };
    //typedef const char *const tpetuser;


    //tpetdummy d;
    //tpetboolean b;
    //tpetinteger i;
    tpetsubrange s;
    //tpetreal r;
    //tpetstring str;
    tpetpointer ptr;
    tpetarray array;
    tpetrecord record;
    //tpetuser user;
    //tpetcall call;
  };

  enum etype type;
  union utype val;


  // fonction qui dit si deux types sont �gaux
  friend bool pevaltype_equal(struct pascal_eval_type a, struct pascal_eval_type b);

  // fonction qui convertit un type en chaine de caract�re
  char * toString(void) const;

  // Fonction qui retourne la taille d'un type en nombre de cases.
  // Notamment, lors d'un malloc, cela donne la taille � allouer dans la m�moire.
  static unsigned int pevaltype_sizeof(const struct pascal_eval_type a);

  // fonction qui � partir d'un pevaltype cr�e un pdvaltype
  static int pdvaltype_of_pevaltype(const pascal_eval_type evaltype, pdvaltype &dvaltype);

  // Fonction qui cr�e une nouvelle PDValTyp�e � partir d'un PEValType.
  // Code d'erreur comme d'habitude.
  static int pdvalt_of_pevaltype(const pascal_eval_type evaltype, ploc i, pdvalt &dvalt);

  // Fonction qui cr�e un nouveau PEValtype � partir d'un PDValtype.
  static int pevaltype_of_pdvaltype(const pascal_dval_type dvaltype, pascal_eval_type &evaltype);

};

extern bool pevaltype_equal(struct pascal_eval_type a, struct pascal_eval_type b);




struct pascal_eval {
  //enum etype {PEDummy, PEBoolean, PEInteger, PESubrange, PEReal, PEString, PEPointer, PEArray, PERecord};

  union utype {
    //typedef void tpedummy;
    typedef bool tpeboolean;
    typedef int tpeinteger;
    typedef int tpesubrange;
    typedef corps tpereal;
    typedef char * tpestring;
    typedef ploc tpepointer;
    typedef ploc tpearray;
    typedef ploc tperecord;

    //tpedummy;
    tpeboolean b;
    tpeinteger i;
    tpesubrange s;
    tpereal r;
    tpestring str;
    tpepointer ptr;
    tpearray array;
    tperecord record;
  };

  //enum etype type;
  union utype val;
};




struct pascal_evalt {
  pevaltype type;
  peval val;

  char * toString(void) const;
  int toPSVal(psval &sval);
  int fromPSVal(const psval sval); // La fonction ne fait que ajuster la partie "val" 
                                   // On suppose (tr�s important!!!!) que la partie "type" est remplie et correcte.
  int r_fromPDValt(const pmem mem, const pdvalt dvalt);
  int l_fromPDValt(const pmem mem, const pdvalt dvalt);
  int fromPDValt(const pmem mem, const pdvalt dvalt);
  static bool equal(const pevaltype type,  const pascal_eval e1, const pascal_eval e2);
};






// enfin les expressions !!!!!!!
// Comme le reste c'est un type union disjointe � la OCaml.
// Pour cela, on fait comme d'habitude.
class CPexpr {
public:
  enum etype {PEt, POu, PEqual, PDiff, PInf, PSup, PInfEq, PSupEq, PIPlus, PIMoins, PIMult, PIDiv, PIMod, PRPlus, PRMoins, PRMult, PRDiv, PTab, PRecord, PNot, PUIPlus, PUIMoins, PURPlus, PURMoins, PRef, PInd, PIdent, PConst, PCall, PMenu, PDummy, PNomCarte,
              PIdentRef, PTabRef, PRecordRef};


  union utype {
    struct SPOpUnaire {
      CPexpr *e;
    };
    struct SPOpBinaire {
      CPexpr *e1, *e2;
    };
    struct SPEt     : public SPOpBinaire {};
    struct SPOu     : public SPOpBinaire {};
    struct SPEqual  : public SPOpBinaire {};
    struct SPDiff   : public SPOpBinaire {};
    struct SPInf    : public SPOpBinaire {};
    struct SPSup    : public SPOpBinaire {};
    struct SPInfEq  : public SPOpBinaire {};
    struct SPSupEq  : public SPOpBinaire {};
    struct SPIPlus  : public SPOpBinaire {};
    struct SPIMoins : public SPOpBinaire {};
    struct SPIMult  : public SPOpBinaire {};
    struct SPIDiv   : public SPOpBinaire {};
    struct SPIMod   : public SPOpBinaire {};
    struct SPRPlus  : public SPOpBinaire {};
    struct SPRMoins : public SPOpBinaire {};
    struct SPRMult  : public SPOpBinaire {};
    struct SPRDiv   : public SPOpBinaire {};
    struct SPTab    : public SPOpBinaire {};
    struct SPNot     : public SPOpUnaire {};
    struct SPUIPlus  : public SPOpUnaire {};
    struct SPUIMoins : public SPOpUnaire {};
    struct SPURPlus  : public SPOpUnaire {};
    struct SPURMoins : public SPOpUnaire {};
    struct SPRef     : public SPOpUnaire {};
    struct SPInd     : public SPOpUnaire {};
    struct SPIdent {
      char *pident;
    };
    struct SPRecord {
      CPexpr *e;
      char *champ;
    };
    struct SPConst {
      pevalt pconst;
    };
    struct SPCall {
      char *ident;
      class pliste<CPexpr> *args;
    };
    struct SPMenu {
      struct item {
	char * message;
	char * iconfile;
      };
      class pliste<struct item> *pitems; // pile d'items; une _PILE_, pas une file...
      char * nom;
    };
      
    


    SPEt upet;
    SPOu upou;
    SPEqual upequal;
    SPDiff updiff;
    SPInf upinf;
    SPSup upsup;
    SPInfEq upinfeq;
    SPSupEq upsupeq;
    SPIPlus upiplus;
    SPIMoins upimoins;
    SPIMult upimult;
    SPIDiv upidiv;
    SPIMod upimod;
    SPRPlus uprplus;
    SPRMoins uprmoins;
    SPRMult uprmult;
    SPRDiv uprdiv;
    SPTab uptab;
    SPRecord uprecord;
    SPNot upnot;
    SPUIPlus upuiplus;
    SPUIMoins upuimoins;
    SPURPlus upurplus;
    SPURMoins upurmoins;
    SPRef upref;
    SPInd upind;
    SPIdent upident;
    SPConst upconst;
    SPCall upcall;
    SPMenu upmenu;
  };
  
  enum etype type;
  union utype val;



public:
  // Les constructeurs.
  CPexpr(unsigned int deb_ligne, unsigned int fin_ligne, unsigned int deb_car, unsigned int fin_car, unsigned int deb_car_tot, unsigned int fin_car_tot) : position(pascal_position(deb_ligne, fin_ligne, deb_car, fin_car, deb_car_tot, fin_car_tot)) { }

  CPexpr(ppos position) : position(position) { }

  // La fonction de conversion vers une chaine de caract�re.
  char * toString(void) const;
  
  // Contient la position de l'expression dans le fichier.
  ppos position;

  // Les fonctions d'�valuations.
  // Renvoie comme d'habitude un code d'erreur, avec les m�mes conventions.
  // Une L-�valuation est comme une R-�valuation, sauf qu'on rend des adresses,
  // surtout pour les variables, et tous les machins qui ont � voir avec la m�moire.
  // En Pascal, une expression ne modifie rien du tout, que ce soit l'environnement
  // ou la m�moire. Comme une v�ritable expression, il n'y a que de la lecture qui est
  // r�alis�e ici. L'�criture dans l'une des deux est faite par une instruction,
  // souvent sp�cialis�. 
  // M�me avec les �critures et les lectures sur les entr�es sorties.
  //
  // En th�orie, y a des const pour mem et env dans r_, �tant donn� que pas d'effet
  // de bord. En pratique, d�claration de variables temporaires.
  int r_evaluate(const penv env, pmem mem, pevalt &res);
  int l_evaluate(const penv env, const pmem mem, pevalt &res);



};



struct pascal_expr_futur_cell_t;
struct pascal_expr_futur_cell_t {
  CPexpr::etype type;
  char * str1;
  pevalt pconst;
  char * * menu_items_nom;
  char * * menu_items_icon;
};

//typedef pliste<CPexpr::etype> pascal_expr_futur_t;
typedef pliste<pascal_expr_futur_cell_t> pascal_expr_futur_t;


extern bool pascal_expr_compile(const CPexpr * expr, pascal_expr_futur_t * &futur);
extern bool pascal_expr_compile_l(const CPexpr * expr, pascal_expr_futur_t * &futur);


#define PASCAL_STACK_SIZE 2048
struct pascal_stack_t {
  pevalt * tab[PASCAL_STACK_SIZE];
  int nb;
};

extern pascal_stack_t * pascal_stack_make(void);
extern void pascal_stack_free(pascal_stack_t * stack);
extern void pascal_stack_push(pascal_stack_t * stack, pevalt * e);
extern pevalt * pascal_stack_pop(pascal_stack_t * stack);


extern bool r_evaluate_futur(const pascal_expr_futur_t * futur, pascal_stack_t * stack, const penv env, pmem mem, const pascal_expr_futur_t * &futur_next);
extern bool r_evaluate_futur_step(const pascal_expr_futur_cell_t * futur_cell, pascal_stack_t * stack, const penv env, pmem mem);

extern bool l_evaluate_futur(const pascal_expr_futur_t * futur, pascal_stack_t * stack, const penv env, pmem mem, const pascal_expr_futur_t * &futur_next);
extern bool l_evaluate_futur_step(const pascal_expr_futur_cell_t * futur_cell, pascal_stack_t * stack, const penv env, pmem mem);





#endif /* PASCAL_EXPR_HPP */
