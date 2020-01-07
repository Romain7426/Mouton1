#ifndef PASCAL_HPP
#define PASCAL_HPP

#include "liste.hpp"

/* Ce fichier contient la classe de cosntruction d'un arbre de compilation
   PASCAL, qui est le langage de script adopt� pour et par le projet.
   Arbre Syntaxique Pascal (ASP)
*/

/* Dans cet arbre syntaxique, les feuilles sont les instructions.
   Un arbre syntaxique est un arbre binaire.
   On ex�cute d'abord le fils de gauche, puis le fils de droite.
*/

/* La cr�ation d'un noeud se fait au moyen de la s�quence.
   La s�quence est associtive comme cela : a ; (b ; c) .
   Ce qui fait qu'une suite d'instruction est un peigne � "droite".
   
   Pour cr�er un arbre � gauche, c'est la commance begin de bloc.
   
   En effet, un programme est une suite d'instruction �l�mentaire,
   donc une suite de feuilles.
   Le begin a pour effet de rendre �l�mentaire ('atomic') un regroupement
   d'instructions, ce qui cr�e une d�rivation dans la suite, donc un arbre.

   La lecture des feuilles de l'arbre syntaxique de gauche � droite donne 
   la liste des instructions qui vont �tre ex�cut�es (ou presque ; 
   on a le cas du if qui cr�e deux branches, mais qui se rejoignent 
   ensuite ; m�me chose pour les boucles).
*/




class CPprog {

/* Bon on s'occupe des types en pascal.
   Comme partout en informatique, on a � faire � un bel arbre.
   Et heureusement, les noeuds et les feuilles sont disjoints.
   (Un vrai langae tout simplement !)
   
   Dans les feuilles, nous avons BOOLEAN, INTEGER, REAL, et STRING.
   En Turbo PASCAL, on trouve aussi le type FILE, ORDINAL,
   SET, LABEL, et TYPE. Ces derniers seront impl�ment�s si n�cessaire.
   On peut aussi distinguer un type CHAR, WORD, BYTE, SHORTINT, LONGINT, etc..
   Il y a aussi le type �num�r� qui est un type de base, car il ne d�pend
   d'aucun autre type.
   M�me chose avec le type intervalle qu'il faut n�anmoins implanter pour le
   type array ; comme il d�pend de deux scalaires et pas d'autres types, 
   c'est bien un type de base (ou plut�t je consid�re que).
   Et puis non, on le met dans les types construits car �a en est un.
   
   Dans les noeuds, nous avons POINTER, ARRAY, RECORD, PROCEDURE, et FUNCTION. 
   Ces deux derniers sont construits car ils prennent des param�tres qui ont des 
   types. En Turbo PASCAL, il y aussi un type OBJECT. D'autre part, le type union
   (RECORD avec des CASE OF) n'est pas reconnue avec le langage.
   Peut �tre ajout� par la suite si n�cessaire.
*/


/* D�claration de constantes pour faire les unions disjointes.
   Les d�finitions vont se faire en remontant.
   D'abord celui qui ne d�pend de personne,
   puis celui qui ne d�pendait que de ceux qui ont �t� d�fini, etc..
*/

/* D'abord, un type est construit ou de base ? */
//enum pascal_type_nature {PTNConstruit, PTNBase};
//typedef pascal_type_nature ptnat;

/* On commence par d�crire le type des feuilles. */
//enum pascal_type_basic {PTBBoolean, PTBInteger, PTBReal, PTBString};
//typedef pascal_type_basic ptbasic;

/* Maintenant le type des noeuds. */
//enum pascal_type_construit {PTCSubrange, PTCArray, PTCRecord, PTCPointer, PTCProcedure, PTCFunction};
//typedef pascal_type_construit ptcons;

enum pascal_type_nature {PTNBoolean, PTNInteger, PTNReal, PTNString, \
PTNSubrange, PTNArray, PTNRecord, PTNPointer, PTNProcedure, PTNFunction};
typedef pascal_type_nature ptnat;




/* Enfin, les constructeurs de l'arbre.
   D'abord les feuilles, puis les noeuds. */
   /*
struct pascal_type_arbre {
       typedef ptbasic pascal_type_feuille;
       
       struct pascal_type_subrange {
              p
       struct pascal_type_noeud {
              ptcons cons;
              pascal_type_arbre *fils;
       };
       
       union pascal_type_contenu {
             pascal_type_feuille feuille;
             pascal_type_noued noeud;
       };
       
       ptnat nature; // filtrage pour savoir si c'est une feuille ou un noeud.
       pascal_type_contenu contenu; // ce qu'il y a dans l'arbre.
};
typedef pascal_type_arbre pascal_type;
typedef pascal_type ptype;
*/

/* On d�finit les constructeurs des types compliqu�s. */
/*
ptype cons_subrange(ptype min, ptype max);
ptype cons_array(ptype subrange, ptype type);
ptype cons_pointer(ptype type);
ptype cons_record(ptype champs);
*/



/* Le type d'une valeur en pascal. */
struct SPType {
       /* Le type d'une feuille. */
       /*
       struct SPBase {
              ptbasic ptb;
       };
       */

       /* Ensuite, les types construits qui d�pendent d'autres types. */

       // En Turbo PASCAL 6, un intervalle est entre deux types scalaires.
       // Ici, on n'a que Integer (m�me si Boolean est un type scalaire).
       struct ptsubrange {
              integer min, max;
       };
       struct ptarray {
              ptsubrange indice; // L'intervalle des indices.
              SPType *telement;   // Le type des �l�ments.
       };
       struct ptpointer {
              SPType *telement; // Le type de l'�lement.
       };
       struct ptrecord {
              // Liste d'�l�ments, avec un nom et un type.
              // Contrairement aux proc�dures et aux fonctions,
              // le nom du champ importe pour le type.
              struct lchamps {
                     SPType *tchamp; // type
                     char *nchamp; // nom
                     lchamps *schamp; // suivant
              };
              // La structure vide est autoris�e.
              lchamps *champs;
       };
       struct ptprocedure {
              // M�me chose.
              struct lparams {
                     SPType *tparam; // type
                     lparams *sparam; //suivant
              };
              // On a le droit de na pas avoir de param�tre.
              lparams *params;
       };
       // Une fonction est une proc�dure avec une valeur de retour.
       struct ptfunction : public ptprocedure {
              // La valeur de retour.
              SPType *retour;
       };
       
       union UPType {
             ptsubrange s;
             ptarray a;
             ptpointer p;
             ptrecord r;
             ptprocedure proc;
             ptfunction func;
       };
       
       // Le discriminant.
       ptnat nature;
       // ce qu'il y a dedans.
       UPType t;
};

typedef SPType pascal_type;
typedef pascal_type ptype;              


// Fonctions de manipulation de type.
// Dit si deux types sont �gaux ou pas.
bool ptype_equal(ptype a, ptype b);

// Rend la taille d'un type.
// N�gatif en cas d'erreur.
int ptype_sizeof(ptype a);
              


/* Apr�s avoir fait les types (SVal),
   on s'occupe des valeurs (DVal).
   
   Une valeur poss�de un type, plus un contenu.
   Le contenu est bien s�r une union de contenu,
   dont on choisi la s�mantique selon le type.
*/

struct SPValeur {
       /* On commence par d�finir ce qui ne d�pend pas des autres : 
          les types de bases. */
typedef bool  pvboolean;
typedef int   pvinteger;
typedef float pvreal;
typedef char *pvstring; // Ici, on n'a pas de limites de cha�ne. Cependant,
                        // en Turbo PASCAL 6, la valeur au maximum de 255.


       typedef int pvsubrange; // un nombre compris en tre min et max.
       typedef unsigned int pvpointer; // La valeur d'un pointeur.
       /*
       struct pvarray {
              SPValeur *tab; // Le tableau de valeur en interne.
       };
       */
       typedef pvpointer pvarray; // Le tableau est dans la m�moire. 
                                  // Donc un tableau, c'est une adresse m�moire.
       /*
       struct pvrecord {
              SPValeur *champs; // Les champs sont en fait un tableau de valeur en interne.
              unsigned int taille;
       };
       */
       typedef pvpointer pvrecord; // M�me chose, on met les records en m�moire.
                                   // Tant pis pour la taille.
       /*
       struct pvprocedure {
              struct lvar {
                     char *nom;
                     struct lvar *suivant;
              };
              lvar vars; // Le tableau contenant le nom des variables.
              CPprog *prog; // En fait, du type CPprog.
       };
       struct pvfunction : public pvprocedure {
              SPValeur *retour; // L� o� on range la valeur de retour.
       };
       */
       // M�me chose avec les proc�dures et les fonctions.
       // On met tout dans la m�moire, ce qui permet d'obtenir leur adresse.
       // Ce qui oblige � les ajouter dans SVal.
       // Ensuite, pour la valeur de retour d'une fonction,
       // il faut cr�er une nouvelle DVal.     

       union UPValeur {
       pvboolean b;
       pvinteger n;
       pvreal x;
       pvstring str;
       pvsubrange sub;
       pvarray a;
       pvpointer ptr;
       pvrecord record;
       pvprocedure proc;
       pvfunction func;
       };
       
       
       /* Le type. */
       //ptype t;
       // La valeur.
       UPValeur val;
};
typedef struct SPValeur pval; 

bool pval_equal(pval a, pval b);



/* Les feuilles des expressions. */
/*
enum pascal_type {PBoolean, PInteger, PReal, PPointeur};

typedef enum pascal_type ptype;

typedef unsigned int pascal_adresse_memoire;
typedef pascal_adresse_memoire pam;
*/
/*
struct slptype {
    ptype contenu;
    struct slptype *suivant;
};
*/
/*
struct ptptr {
       pam ptr;
       // correspond au type exact du pointeur.
       //slptype lptype;
       
       // En fait, comme il n'y a que les pointeurs qui contruisent sur eux-m�mes,
       // il est plus simple de compter le nombre d'imbrication (de niveaux) 
       // de pointeurs.
       unsigned int niveau = 0;
       // �a c'est le type qu'on trouve au bout apr�s toutes les indirections.
       // Normalement, �a ne peut pas contenir le type pointeur.
       ptype contenu;
};


union UPValeur {
   ptboolean b;
   ptinteger i;
   ptreal r;
   ptptr ptr;
};

struct PValeur {
       ptype t;
       UPValeur val;
       // Ce dernier champ est dans le cas o� on 
       };
       
*/

















/* La gestion de l'environnemment. */
/* On a un environnement � deux niveaux,
   ce qui permet l'utilisation de pointeurs.
   D'o� un environnement et une m�moire.
   L'environnement est le monde � la compilation,
   et la m�moire est le monde � l'ex�cution.
   Le type des �l�ments de l'environnement est DVal.
   Le type des �l�ments de la m�moire est SVal.
*/
/* C'est l'environnement qui fait le lien entre un ident et sa valeur
   (constante, variable, fonction, procedure).
*/


enum pascal_dval_type {PDConstante, PDMemoire};

typedef pascal_dval_type pdvaltype;


enum pascal_sval_type {PSValeur, PSProcedure, PSFunction};

typedef pascal_sval_type psvaltype;





struct SPDConstante : public pval {
};
struct SPDMemoire {
       pvpointer adr;
};
union UEnvCell {
      SPDConstante c;
      SPDMemoire m;
      };
struct SEnvCell {
       UEnvCell contenu;
       pdvaltype pdtype;
       ptype t;
       };
typedef SEnvCell pdval;
struct EnvCell : public SEnvCell {
       char *nom;
       EnvCell *suivant;
};




struct SPSValeur : pval {
};
struct SPSProcedure {
       struct lvar {
              char *nom;
              struct lvar *suivant;
       };
       lvar vars; // Le tableau contenant le nom des variables.
       CPprog *prog; // En fait, du type CPprog*.
};
struct SPSFunction : public SPSProcedure {
       SPValeur *retour; // L� o� on range la valeur de retour.
};

union UPSVal {
      SPSValeur val;
      SPSProcedure proc;
      SPSFunction func;
};

struct SMemCell {
       UPSVal v;
       psvaltype pstype;
};
typedef SMemCell psval;



//#define MAX_ENVIRONNEMENT 128
//typedef SEnvCell TEnvironnement[MAX_ENVIRONNEMENT];
typedef EnvCell *TEnvironnement;
TEnvironnement env = NULL;
//unsigned int env_nbelts = 0;

#define MAX_MEMOIRE 1024
typedef SMemCell TMemoire[MAX_MEMOIRE];
TMemoire mem;
pvpointer mem_nbelts = 0;


TEnvironnement update(TEnvironnement env, char *ident, pdval val);
int envlookup(TEnvironnement env, char *ident, pdval &val);
int pnew(unsigned int taille, pvpointer &a);














/* Les expressions. */

enum pascal_expression {PEt, POu, PEqual, PDiff, PInf, PSup, PInfEq, PSupEq, \
     PPlus, PMoins, PMult, PDiv, PMod, PTab, PNot, PUPlus, PUMoins, PRef, PInd,
     PIdent, PConst};

typedef enum pascal_expression pexpr;


class CPexpr {
      public:
      /* D�finition des types d'une expression. */
      struct SPOpBinaire {
             CPexpr *e1, *e2;
             };
      struct SPEt : public SPOpBinaire {
             };
      struct SPOu : public SPOpBinaire {
             };
      struct SPEqual : public SPOpBinaire {
             };
      struct SPDiff : public SPOpBinaire {
             };
      struct SPInf : public SPOpBinaire {
             };
      struct SPSup : public SPOpBinaire {
             };
      struct SPInfEq : public SPOpBinaire {
             };
      struct SPSupEq : public SPOpBinaire {
             };
      struct SPPlus : public SPOpBinaire {
             };
      struct SPMoins : public SPOpBinaire {
             };
      struct SPMult : public SPOpBinaire {
             };
      struct SPDiv : public SPOpBinaire {
             };
      struct SPMod : public SPOpBinaire {
             };
      struct SPTab : public SPOpBinaire {
             };
      struct SPOpUnaire {
             CPexpr *e;
             };
      struct SPNot : public SPOpUnaire {
             };
      struct SPUPlus : public SPOpUnaire {
             };
      struct SPUMoins : public SPOpUnaire {
             };
      struct SPRef : public SPOpUnaire {
             };
      struct SPInd : public SPOpUnaire {
             };
      struct SPIdent {
             char *pident;
             };
      struct SPConst {
             pval pconst;
             };
             
      private:
      union UPexpr {
            SPEt upet;
            SPOu upou;
            SPEqual upequal;
            SPDiff updiff;
            SPInf upinf;
            SPSup upsup;
            SPInfEq upinfeq;
            SPSupEq upsupeq;
            SPPlus upplus;
            SPMoins upmoins;
            SPMult upmult;
            SPDiv updiv;
            SPMod upmod;
            SPTab uptab;
            SPNot upnot;
            SPUPlus upuplus;
            SPUMoins upumoins;
            SPRef upref;
            SPInd upind;
            SPIdent upident;
            SPConst upconst;
            };
      
      
      /* Le type de l'expression (sens pour filtrer le contenu). */
      pexpr t;
      
      /* Maintenant le contenu. */
      UPexpr expr;
      
      public:
      /* La fonction d'�valuation.
         Elle retourne le r�sultat dans le PValeur,
         et la valeur rendue est un code d'erreur.
           0 : oki
         < 0 : pas oki
      */
      /* r_ et l_ sont identiques, sauf dans l'�valuation des idents.
         Ainsi, dans "x := x",
         � gauche du ':=', on appelle l_  //pointeur
         � droite du ':=', on appelle r_  //valeur
      */
      int r_evaluate(TEnvironnement env, pval &val);
      int l_evaluate(TEnvironnement env, pval &val);


};




/* Les instructions. */

/* Oublier le switch ; � rajouter si n�cessaire. */

enum pascal_instruction {PSeq, PIf, PWhile, PFor, PRepeat, PBegin, \
     PVar, PAffectation, PWrite, PWriteln, PRead, PReadln};


typedef enum pascal_instruction pinst;
/

      /* D'abord d�finition des conteneurs de type. */
      public:
             struct SPSeq {
                    CPprog *p1, *p2;
                    };
                    
             struct SPIf {
                    CPexpr *b;
                    CPprog *p, *q;
                    };
                    
             struct SPWhile {
                     CPexpr *b;
                     CPprog *p;
                     };
                     
             struct SPFor {
                    char *i;
                    CPexpr *e1, *e2;
                    CPprog *p;
                    };
             
             struct SPRepeat {
                    CPprog *p;
                    CPexpr *b;
                    };
             
             struct SPBegin {
                    CPprog *p;
                    };
                    
             struct SPVar {
                    char *nom;
                    ptype t;
                    };
                    
             struct SPAffectation {
                    CPexpr *lvar;
                    CPexpr *e;
                    };
                    
             struct SPWrite {
                    CListe<CPexpr*> *le;
                    };
             
             struct SPWriteln {
                    CListe<CPexpr*> *le;
                    };
                    
             struct SPRead {
                    CListe<CPexpr*> *llvar;
                    };
                    
             struct SPReadln {
                    CListe<CPexpr*> *llvar;
                    };
             

      private:
             /* Une instruction est un de ces �l�ments. */
             union UPinst {
                   SPSeq upseq;
                   SPIf upif;
                   SPWhile upwhile;
                   SPFor upfor;
                   SPRepeat uprepeat;
                   SPBegin upbegin;
                   SPVar upvar;
                   SPAffectation upaffectation;
                   SPWrite upwrite;
                   SPWriteln upwriteln;
                   SPRead upread;
                   SPReadln upreadln;
                   };
                   
              /* Le type de l'instruction. */
              pinst t;
              
              /* L'instruction elle-m�me. */
              UPinst inst;
              
              /* La v�ritable fonction d'ex�cution. */
              int execute_env(TEnvironnement env);
             
      public:
             /* La fonction qui ex�cute une instruction.
                Elle retourne un code d'erreur :
                       0 �a s'est bien pass�
                     < 0 erreur !!!
             */
             int execute(void);
             
};














#endif /* PASCAL_HPP */
