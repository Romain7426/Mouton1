#ifndef PASCAL_HPP
#define PASCAL_HPP

//#include "pascal.tools.hpp"

/* Partout là-dedans on va utiliser le principe OCaml des unions disjointes.
   Pour cela, il y a une définition d'uns structure en deux temps :
   d'abord le discriminant (enum etype),
   puis le contenu associé (s'il y a) (union utype).
   La structure au final contient deux éléments :
   un déterminant (type:enum etype) et la valeur associée (val:union utype).
*/


// EVal
// Définition du type rendu par une expression.
// C'est ce que peut contenir un ident (modulo les fonctions et les types).
// Les fonctions sont des appels ! Donc il faut prendre leur adresse !
// Et les types, si tout est bien fait, seront dans une autre table.
struct pascal_eval_type {
  enum etype {PEBoolean, PEInteger, PESubrange, PEReal, PEString, PEPointer, PEArray, PERecord};
  
  //typedef void tpeboolean;
  //typedef void tpeinteger;
  struct tpesubrange {
    int min, max;
  };
  //typedef void tpereal;
  //typedef void tpestring;
  struct tpepointer {
    struct pascal_eval_type *contenu;
  };
  struct tpearray {
    struct tpesubrange intervalle;
    struct pascak_eval_type *contenu;
  };
  struct tperecord {
    struct champ {
      char *nom;
      struct pascal_eval_type *type;
    };
    pliste<champ> *champs;
  };

  union utype {
    struct tpesubrange;
    struct tpepointer;
    struct tpearray;
    struct tperecord;
  };

  // Le discriminant.
  enum etype type;
  
  // La valeur du type.
  union utype val;
};


typedef pascal_eval_type petype;




#endif /* PASCAL_HPP */
