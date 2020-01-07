#include <stdio.h>
#include <string.h>
#include "global.hpp"
#include "pascal/pascal.expr.hpp"
#include "pascal/pascal.prog.hpp"
#include "apiscript.hpp"


// TODO XXX Bad
extern CMenuAbstrait * MiniMenu;








// Fonction qui dit si deux types sont égaux.
bool pevaltype_equal(const struct pascal_eval_type a, const struct pascal_eval_type b) {
  bool booleen;
  pliste<struct pascal_eval_type::utype::tpetrecord::champ> *tempa, *tempb;

  if (a.type == pevaltype::PETVide || b.type == pevaltype::PETVide) {
    return true;
  }

  if (a.type != b.type) {
    return false;
  }

  switch (a.type) {
  case pevaltype::PETBoolean:
  case pevaltype::PETInteger:
  case pevaltype::PETReal:
  case pevaltype::PETString: return true; break;
  case pevaltype::PETSubrange: return ((a.val.s.min == b.val.s.min) && (a.val.s.max == b.val.s.max)); break;
  case pevaltype::PETPointer: return pevaltype_equal(*(a.val.ptr), *(b.val.ptr)); break;
  case pevaltype::PETArray:
    return ((a.val.array.indice.min == b.val.array.indice.min) 
            && (a.val.array.indice.max == b.val.array.indice.max)
            && (pevaltype_equal(*(a.val.array.type), *(b.val.array.type))));
    break;

  case pevaltype::PETRecord: {
    booleen = true;
    tempa = ((a.val.record.champs));
    tempb = b.val.record.champs;
    
    do {
      if (tempa == NULL && tempb == NULL) {
        return true;
      }

      if (tempa == NULL || tempb == NULL) {
        return false;
      }

      if (tempa->a == NULL || tempb->a == NULL) {
        pmesserr("pevaltype_equal: L'un des champs est NULL (a: %p ; b: %p).", tempa->a, tempb->a);
        assert(false);
        return false;
      }

      if (tempa->a->nom == NULL || tempb->a->nom == NULL) {
        pmesserr("pevaltype_equal: Le nom d'un champ est NULL (a: %p ; b: %p).", tempa->a->nom, tempb->a->nom);
        assert(false);
        return false;
      }

      booleen = (0 == strcmp(tempa->a->nom, tempb->a->nom));
      if (not booleen)
        return false;

      booleen = pevaltype_equal(*(tempa->a->type), *(tempb->a->type));
      if (not booleen)
        return false;
      
      tempa = tempa->suivant;
      tempb = tempb->suivant;
    } while (true);
    
    assert(false);
    return false;
  }
    break;

  default: pmesserr("pevaltype_equal: type utilisé inconnu ici: %d", a.type); assert(false); return false;
  }

  assert(false);
  return false;
}


// Fonction qui convertit un type en chaine de caractère.
char * pevaltype::toString(void) const {
  char * temp, * temptemp, * temptemptemp, * ret;
  unsigned int taille, tailletemp;
  static const char * const csubrange = "subrange[", *cpp = "..", *ccr = "]";
  static const char * const cpointer = "pointer of [";
  static const char * const carray = "array[", * cof = " of ";
  static const char * const crecord = "record  ", * const cdpt = " : ", * const cptvirg = ";  ", * const cend = "  end";
  char * nb1, * nb2;
  pliste<struct pascal_eval_type::utype::tpetrecord::champ> * tempchamps;

  switch (this->type) {
  case PETBoolean: return strcopy("boolean"); break;
  case PETInteger: return strcopy("integer"); break;
  case PETSubrange:
    nb1 = itoa(this->val.s.min);
    nb2 = itoa(this->val.s.max);
    ret = STRCAT5_(csubrange, nb1, cpp, nb2, ccr);
    delete [] nb2;
    delete [] nb1;
    return ret;
    break;
  case PETReal: return strcopy("real"); break;
  case PETString: return strcopy("string"); break;
  case PETPointer:
    temp = this->val.ptr->toString();
    ret = STRCAT3_(cpointer, temp, ccr);
    delete [] temp;
    return ret;
    break;
  case PETArray:
    temp = this->val.array.type->toString();
    nb1 = itoa(this->val.array.indice.min);
    nb2 = itoa(this->val.array.indice.max);
    ret = STRCAT7_(carray, nb1, cpp, nb2, ccr, cof, temp);
    delete [] nb2;
    delete [] nb1;
    delete [] temp;
    return ret;
    break;

  case PETRecord:
    tempchamps = this->val.record.champs;
    ret = strcopy(crecord);
    while (tempchamps != NULL) {
      if (tempchamps->a == NULL) {
        pmesserr("pevaltype::toString(): le type courant est un record avec un champ NULL.");
        temp = strcopy("");
        tailletemp = 0;
        assert(false);
      }
      else {
        if (tempchamps->a->nom == NULL) {
          pmesserr("pevaltype::toString(): le type courant est un record avec un champ dont le nom est NULL");
          temp = strcopy("");
          assert(false);
        }
        else {
          temp = strcopy(tempchamps->a->nom);
        }
        temptemp = STRCAT2_(temp, cdpt);
        delete [] temp;
        temp = temptemp;
  
        if (tempchamps->a->type == NULL) {
          pmesserr("pevaltype::toString(): le type courant est un record avec un champ dont le type est NULL.");
          temptemp = strcopy("NULL");
          assert(false);
        }
        else {
          temptemp = tempchamps->a->type->toString();
        }
        temptemptemp = STRCAT3_(temp, temptemp, cptvirg);
        delete [] temp;
        delete [] temptemp;
        temp = temptemptemp;
      }
      
      temptemp = STRCAT2_(ret, temp);
      delete [] ret;
      delete [] temp;
      ret = temptemp;
      
      tempchamps = tempchamps->suivant;
    }
    
    temp = STRCAT2_(ret, cend);
    delete [] ret;
    ret = temp;
    return ret;
    break;

  default:
    pmesserr("pevaltype::toString(): essai de conversion en chaîne de caractères d'un typeinconnu.");
    assert(false);
    return NULL;
  }
  
  assert(false);
  return NULL;
}




unsigned int pevaltype::pevaltype_sizeof(const struct pascal_eval_type a) {
  unsigned int ret;
  pliste<struct pascal_eval_type::utype::tpetrecord::champ> *temp;

  switch (a.type) {
  case PETBoolean: 
  case PETInteger: 
  case PETSubrange:
  case PETReal: 
  case PETString:
  case PETPointer: return 1; break;
  case PETArray: return a.val.array.indice.max - a.val.array.indice.min + 1; break;

  case PETRecord: {
    ret = 0;
    temp = a.val.record.champs;
    
    while (temp != NULL) {
      ret += pevaltype::pevaltype_sizeof(*(temp->a->type));
      temp = temp->suivant;
    }

    return ret;
  }
    break;

  default: pmesserr("pevaltype::pevaltype_sizeof: essai de connaitre la taille d'un type non pris en charge."); assert(false); return 0;
  }

  assert(false);
  return 0;
}



char * pevalt::toString(void) const {
  char * temp;
  unsigned int taille;

  switch (this->type.type) {
  case pevaltype::PETBoolean: return btoa(this->val.val.b); break;
  case pevaltype::PETInteger: return itoa(this->val.val.i); break;
  case pevaltype::PETSubrange: return itoa(this->val.val.i); break;
  case pevaltype::PETReal: return ftoa(this->val.val.r); break;
  case pevaltype::PETString: 
    taille = strlen(this->val.val.str) + 2;
    temp = new char[taille + 1];
    temp[0] = '\'';
    strcpy(&(temp[1]), this->val.val.str);
    temp[taille-1] = '\'';
    temp[taille] = '\0';
    return temp;
    break;

  case pevaltype::PETPointer: return itoa(this->val.val.i); break;
  case pevaltype::PETArray: pmesserr("pevalt::toString(): convert an array to string: TODO XXX"); return strcopy("array"); break;
  case pevaltype::PETRecord: pmesserr("pevalt::toString(): convert a record to string: TODO XXX"); return strcopy("record"); break;
  default: pmesserr("pevalt::toString(): demande d'une conversion sur un type non pris en charge."); assert(false); return NULL;
  }

  assert(false);
  return NULL;
}



int pevalt::toPSVal(psval &sval) {
  switch (this->type.type) {
  case pevaltype::PETBoolean: sval.b = this->val.val.b; return 0;
  case pevaltype::PETInteger: sval.i = this->val.val.i; return 0;
  case pevaltype::PETSubrange: sval.i = this->val.val.s; return 0;
  case pevaltype::PETReal: sval.r = this->val.val.r; return 0;
  case pevaltype::PETString: sval.str = strcopy(this->val.val.str); return 0;
  case pevaltype::PETPointer: sval.ptr = this->val.val.ptr; return 0;
  case pevaltype::PETArray: pmesserr("Impossible de mettre directement un tableau en mémoire. Il faut le faire élément par élément."); assert(false); return -71;
  case pevaltype::PETRecord: pmesserr("Impossible de mettre directement un enregistrement en mémoire. Il faut le faire champ par champ."); assert(false); return -81;
  default: pmesserr("pevalt::toPSVal: essai de conversion depuis un type inconnu."); assert(false); return -9999;
  }

  assert(false);
  return -1;
}



bool pevalt::equal(const pevaltype type, const peval e1, const peval e2) {
  switch (type.type) {
  case pevaltype::PETBoolean: return (e1.val.b == e2.val.b); break;
  case pevaltype::PETInteger: return (e1.val.i == e2.val.i); break;
  case pevaltype::PETSubrange: return (e1.val.s == e2.val.s); break;
  case pevaltype::PETReal: return (e1.val.r == e2.val.r); break;
  case pevaltype::PETString: return (strcmp(e1.val.str, e2.val.str) == 0); break;
  case pevaltype::PETPointer: return (e1.val.ptr == e2.val.ptr);
  case pevaltype::PETArray: pmesserr("Comparaison de deux arrays: TODO"); return false;
  case pevaltype::PETRecord: pmesserr("pevalt::equal: comparaison de deux records: TODO"); return false;
  default: pmesserr("pevalt::equal: comparaison de deux types qui ne sont pas connus."); assert(false); return false;
  }

  assert(false);
  return false;
}



int pevaltype::pdvaltype_of_pevaltype(const pascal_eval_type evaltype, pdvaltype &dvaltype) {
  int ret;
  pliste<pdvaltype::tpdtrecord::champ> *tempd;
  pliste<pevaltype::utype::tpetrecord::champ> *tempe;


  switch (evaltype.type) {
  case pevaltype::PETBoolean: dvaltype.type = pdvaltype::PDTBoolean; return 0; break;
  case pevaltype::PETInteger: dvaltype.type = pdvaltype::PDTInteger; return 0; break;
  case pevaltype::PETSubrange:
    dvaltype.type = pdvaltype::PDTSubrange;
    dvaltype.val.s.min  = evaltype.val.s.min;
    dvaltype.val.s.max  = evaltype.val.s.max;
    return 0;
    break;
  case pevaltype::PETReal: dvaltype.type = pdvaltype::PDTReal; return 0; break;
  case pevaltype::PETString: dvaltype.type = pdvaltype::PDTString; return 0; break;
  case pevaltype::PETPointer:
    dvaltype.type = pdvaltype::PDTPointer;
    dvaltype.val.ptr = new pdvaltype;
    ret = pdvaltype_of_pevaltype(*(evaltype.val.ptr), *(dvaltype.val.ptr));
    if (ret < 0) return ret;
    return 0;
    break;
  case pevaltype::PETArray:
    dvaltype.type = pdvaltype::PDTArray;
    dvaltype.val.array.type = new pdvaltype;
    ret = pdvaltype_of_pevaltype(*(evaltype.val.ptr), *(dvaltype.val.ptr));
    if (ret < 0) return ret;
    return 0;
    break;

  case pevaltype::PETRecord: {
    dvaltype.type = pdvaltype::PDTRecord;
    tempe = evaltype.val.record.champs;

    tempd = NULL;
    while (tempe != NULL) {
      tempd = mp(new pdvaltype::tpdtrecord::champ, tempd);
      tempd->a->nom = strcopy(tempe->a->nom);
      ret = pdvaltype_of_pevaltype(*(tempe->a->type), *(tempd->a->type));
      if (ret < 0) return ret;
      tempe = tempe->suivant;
    }
  
    pliste<pdvaltype::tpdtrecord::champ> *tempd2 = tempd -> reverse();
    delete tempd;
    dvaltype.val.record.champs = tempd2;
    return 0;
  }
    break;

  default: pmesserr("pevaltype::pdvaltype_of_pevaltype(): matching un type inconnu."); assert(false); return -9999;
  }

  assert(false);
  return -1;
}




int pevaltype::pdvalt_of_pevaltype(const pascal_eval_type evaltype, const ploc i, pdvalt &dvalt) {
  int ret;

  switch (evaltype.type) {
  case pevaltype::PETBoolean: dvalt.type.type = pdvaltype::PDTBoolean; dvalt.val.val.b = i; return 0; break;
  case pevaltype::PETInteger: dvalt.type.type = pdvaltype::PDTInteger; dvalt.val.val.i = i; return 0; break;
  case pevaltype::PETSubrange: dvalt.type.type = pdvaltype::PDTSubrange; dvalt.type.val.s.min = evaltype.val.s.min; dvalt.type.val.s.max = evaltype.val.s.max; dvalt.val.val.s = i; return 0; break;
  case pevaltype::PETReal: dvalt.type.type = pdvaltype::PDTReal; dvalt.val.val.r = i; return 0; break;
  case pevaltype::PETString: dvalt.type.type = pdvaltype::PDTString; dvalt.val.val.str = i; return 0; break;
  case pevaltype::PETPointer:
    dvalt.type.type = pdvaltype::PDTPointer;
    dvalt.type.val.ptr = new pdvaltype;
    VERIF_OK(pdvaltype_of_pevaltype(*(evaltype.val.ptr), *(dvalt.type.val.ptr)));
    dvalt.val.val.ptr = i;
    return 0;
    break;
    
  case pevaltype::PETArray:
    dvalt.type.type = pdvaltype::PDTArray;
    dvalt.type.val.array.indice.min = evaltype.val.array.indice.min;
    dvalt.type.val.array.indice.max = evaltype.val.array.indice.max;
    dvalt.type.val.array.type = new pdvaltype;
    VERIF_OK(pdvaltype_of_pevaltype(*(evaltype.val.array.type), *(dvalt.type.val.array.type)));
    dvalt.val.val.array = i;
    return 0;
    break;
  case pevaltype::PETRecord:
    VERIF_OK(pdvaltype_of_pevaltype(evaltype, dvalt.type));
    dvalt.val.val.record = i;
    return 0;
    break;
  default:
    pmesserr("pevaltype::pdvalt_of_pevaltype(): I'm not able to convert such a value : unknown.");
    assert(false);
    return -9999;
  }

  assert(false);
  return -1;
}





// Fonction qui crée un nouveau PEValtype à partir d'un PDValtype.
int pevaltype::pevaltype_of_pdvaltype(const struct pascal_dval_type dvaltype, pascal_eval_type &evaltype) {
  int ret;
  pdvaltype tempdvaltype;
  pevaltype::utype::tpetrecord::champ *tempchampe;
  class pliste<pevaltype::utype::tpetrecord::champ> *tempchampel;
  class pliste<pdvaltype::tpdtrecord::champ> *tempchampdl;

  switch (dvaltype.type) {

  case pdvaltype::PDTConstante:
    pmessage("pevaltype::pevaltype_of_pdvaltype: rencontre d'une constante...");
    switch (dvaltype.val.c) {
    case pdvaltype::PCTBoolean: evaltype.type = pevaltype::PETBoolean; return 0; break;
    case pdvaltype::PCTInteger: evaltype.type = pevaltype::PETInteger; return 0; break;
    case pdvaltype::PCTReal: evaltype.type = pevaltype::PETReal; return 0; break;
    case pdvaltype::PCTString: evaltype.type = pevaltype::PETString; return 0; break;
    default:
      pmesserr("pevaltype::pevaltype_of_pdvaltype: argh, valeur de constante inconnue (%d).", dvaltype.val.c);
      assert(false);
      return -11;
    }

    pmesserr("pevaltype::pevaltype_of_pdvaltype:DTC PDTConstante. pas à être ici.");
    assert(false);
    return -19999;
    break;
      
  case pdvaltype::PDTBoolean: evaltype.type = pevaltype::PETBoolean; return 0; break;
  case pdvaltype::PDTInteger: evaltype.type = pevaltype::PETInteger; return 0; break;
  case pdvaltype::PDTSubrange:
    evaltype.type = pevaltype::PETSubrange;
    evaltype.val.s.min = dvaltype.val.s.min;
    evaltype.val.s.max = dvaltype.val.s.max;
    return 0;
    break;
  case pdvaltype::PDTReal: evaltype.type = pevaltype::PETReal; return 0; break;
  case pdvaltype::PDTString: evaltype.type = pevaltype::PETString; return 0; break;
  case pdvaltype::PDTPointer:
    evaltype.type = pevaltype::PETPointer;
    evaltype.val.ptr = new pevaltype;
    VERIF_OK(pevaltype::pevaltype_of_pdvaltype(*(dvaltype.val.ptr), *(evaltype.val.ptr)));
    return 0;
    break;
  case pdvaltype::PDTArray:
    evaltype.type = pevaltype::PETArray;
    evaltype.val.array.indice.min = dvaltype.val.array.indice.min;
    evaltype.val.array.indice.max = dvaltype.val.array.indice.max;
    evaltype.val.array.type = new pevaltype;
    VERIF_OK(pevaltype::pevaltype_of_pdvaltype(*(dvaltype.val.array.type), *(evaltype.val.array.type)));
    return 0;
    break;

  case pdvaltype::PDTRecord: {
    evaltype.type = pevaltype::PETRecord;
    evaltype.val.record.champs = NULL;

    tempchampdl = dvaltype.val.record.champs;
    tempchampel = NULL;

    while (tempchampdl != NULL) {
      tempchampe = new pevaltype::utype::tpetrecord::champ;
      tempchampe->nom = strcopy(tempchampdl->a->nom);
      tempchampe->type = new pevaltype;
      VERIF_OK(pevaltype::pevaltype_of_pdvaltype(*(tempchampdl->a->type), *(tempchampe->type)));
      
      tempchampel = mp(tempchampe, tempchampel);
      tempchampdl = tempchampdl -> suivant;
    }

    pliste_reverse_surplace(tempchampel);
    evaltype.val.record.champs = tempchampel;

    return 0;
  }
    break;
      
  case pdvaltype::PDTProcedure:
    pmesserr("pevaltype::pevaltype_of_pdevaltype: DTC PDTProcedure.");
    assert(false);
    return -101;
    break;
  case pdvaltype::PDTFunction:
    pmesserr("pevaltype::pevaltype_of_pdvaltype: DTC PDTFunction.");
    assert(false);
    return -111;
    break;
  case pdvaltype::PDTRetour:
    pmesserr("pevaltype::pevaltype_of_pdvaltype: DTC PDTRetour.");
    return -121;
    assert(false);
    break;

  case pdvaltype::PDTUser:
    VERIF_OK(ptabdvaltypeuser_lookup(tabdvaltypeuser, dvaltype.val.user, tempdvaltype));
    VERIF_OK(pevaltype_of_pdvaltype(tempdvaltype, evaltype));
    return 0;
    break;

  case pdvaltype::PDTVar:
    VERIF_OK(pevaltype_of_pdvaltype(*(dvaltype.val.var), evaltype));
    return 0;
    break;

  default:
    assert(false);
    return -9999;
  }

  assert(false);
  return -1;
}




int pevalt::r_fromPDValt(const pmem mem, const pdvalt dvalt) {
  pdvalt tempdvalt;

  if (dvalt.type.type == pdvaltype::PDTRetour) {
    VERIF_OK(pdvalt::pdvalt_of_pdvaltype(*(dvalt.type.val.ret.type), dvalt.val.val.ret.write, tempdvalt));
      
    return this->fromPDValt(mem, tempdvalt);
  }

  return this->fromPDValt(mem, dvalt);
}


int pevalt::l_fromPDValt(const pmem mem, const pdvalt dvalt) {
  psval sval;

    this -> type.type = pevaltype::PETPointer;
    this -> type.val.ptr = new pevaltype;

    if (dvalt.type.type == pdvaltype::PDTRetour)
      {VERIF_OK(pevaltype::pevaltype_of_pdvaltype(*(dvalt.type.val.ret.type), *(this -> type.val.ptr)));}
    else
      {VERIF_OK(pevaltype::pevaltype_of_pdvaltype(dvalt.type, *(this -> type.val.ptr)));}

    switch (dvalt.type.type) {
    case pdvaltype::PDTConstante: pmesserr("L_EVAL: impossible de L_évaluer une constante."); return false; break;
    case pdvaltype::PDTBoolean: this -> val.val.ptr = dvalt.val.val.b; break;
    case pdvaltype::PDTInteger: this -> val.val.ptr = dvalt.val.val.i; break;
    case pdvaltype::PDTSubrange: this -> val.val.ptr = dvalt.val.val.s; break;
    case pdvaltype::PDTReal: this -> val.val.ptr = dvalt.val.val.r; break;
    case pdvaltype::PDTString: this -> val.val.ptr = dvalt.val.val.str; break;
    case pdvaltype::PDTPointer: this -> val.val.ptr = dvalt.val.val.ptr; break;
    case pdvaltype::PDTArray: pmesserr("L_EVAL: impossible de prendre l'adresse d'un tableau."); return false; break;
    case pdvaltype::PDTRecord: pmesserr("L_EVAL: impossible de prendre l'adresse d'un enregistrement."); return false; break;
    case pdvaltype::PDTProcedure: this -> val.val.ptr = dvalt.val.val.proc; break;
    case pdvaltype::PDTFunction: this -> val.val.ptr = dvalt.val.val.func; break;
    case pdvaltype::PDTRetour: this -> val.val.ptr = dvalt.val.val.ret.write; break;
    case pdvaltype::PDTVar: VERIF_OK(pmemread(mem, dvalt.val.val.var, sval)); this -> val.val.ptr = sval.ptr; break;
    default: pmesserr("L_EVAL: Bon ton ident ton je dois prendre l'adresse a un type inconnu."); assert(false); return false;
    }

    return 0;
}



// Après inspection, pas utilisé par l_evaluate
int pevalt::fromPDValt(const pmem mem, const pdvalt dvalt) {
  int ret;
  psval sval;
  pdvalt tempdvalt;
  pevaltype::utype::tpetrecord::champ *tempchampe;
  class pliste<pevaltype::utype::tpetrecord::champ> *tempchampel;
  class pliste<pdvaltype::tpdtrecord::champ> *tempchampdl;


  switch (dvalt.type.type) {

  case pdvaltype::PDTConstante: {
    switch (dvalt.type.val.c) {
    case pdvaltype::PCTBoolean: this->type.type = pevaltype::PETBoolean; this->val.val.b = dvalt.val.val.c.b; return 0; break;
    case pdvaltype::PCTInteger: this->type.type = pevaltype::PETInteger; this->val.val.i = dvalt.val.val.c.i; return 0; break;
    case pdvaltype::PCTReal: this->type.type = pevaltype::PETReal; this->val.val.r = dvalt.val.val.c.r; return 0; break;
    case pdvaltype::PCTString: this->type.type = pevaltype::PETString; this->val.val.str = strcopy(dvalt.val.val.c.str); return 0; break;
    default:
      pmesserr("pevalt::fromPDValt: argh, valeur de constante inconnue (%d).", dvalt.type.val.c);
      assert(false);
      return -11;
    }
    return -19999;
    assert(false);
  }
    break;

  case pdvaltype::PDTBoolean:
    this->type.type = pevaltype::PETBoolean;
    VERIF_OK(pmemread(mem, dvalt.val.val.b, sval));
    this->val.val.b = sval.b;
    return 0;
    break;

  case pdvaltype::PDTInteger:
    this->type.type = pevaltype::PETInteger;
    VERIF_OK(pmemread(mem, dvalt.val.val.i, sval));
    this->val.val.i = sval.i;
    return 0;
    break;

  case pdvaltype::PDTSubrange:
    this->type.type = pevaltype::PETSubrange;
    this->type.val.s.min = dvalt.type.val.s.min;
    this->type.val.s.max = dvalt.type.val.s.max;
    VERIF_OK(pmemread(mem, dvalt.val.val.s, sval));
    this->val.val.s = sval.i;
    return 0;
    break;

  case pdvaltype::PDTReal:
    this->type.type = pevaltype::PETReal;
    VERIF_OK(pmemread(mem, dvalt.val.val.r, sval));
    this->val.val.r = sval.r;
    return 0;
    break;

  case pdvaltype::PDTString:
    this->type.type = pevaltype::PETString;
    VERIF_OK(pmemread(mem, dvalt.val.val.str, sval));
    this->val.val.str = strcopy(sval.str);
    return 0;
    break;

  case pdvaltype::PDTPointer:
    this->type.type = pevaltype::PETPointer;
    this->type.val.ptr = new pevaltype;
    VERIF_OK(pevaltype::pevaltype_of_pdvaltype(*(dvalt.type.val.ptr), *(this->type.val.ptr)));
    VERIF_OK(pmemread(mem, dvalt.val.val.ptr, sval));
    this->val.val.ptr = sval.ptr;
    return 0;
    break;

  case pdvaltype::PDTArray:
    this->type.type = pevaltype::PETArray;
    this->type.val.array.indice.min = dvalt.type.val.array.indice.min;
    this->type.val.array.indice.max = dvalt.type.val.array.indice.max;
    this->type.val.array.type = new pevaltype;
    VERIF_OK(pevaltype::pevaltype_of_pdvaltype(*(dvalt.type.val.array.type), *(this->type.val.array.type)));
    this->val.val.array = dvalt.val.val.array;
    return 0;
    break;

  case pdvaltype::PDTRecord: {
    this->val.val.record = dvalt.val.val.record;
    this->type.type = pevaltype::PETRecord;
    this->type.val.record.champs = NULL;

    tempchampel = NULL;
    tempchampdl = dvalt.type.val.record.champs;

    while (tempchampdl != NULL) {
      tempchampe = new pevaltype::utype::tpetrecord::champ;
      tempchampe->nom = strcopy(tempchampdl->a->nom);
      tempchampe->type = new pevaltype;
      VERIF_OK(pevaltype::pevaltype_of_pdvaltype(*(tempchampdl->a->type), *(tempchampe->type)));
      tempchampel = mp(tempchampe, tempchampel);
      tempchampdl = tempchampdl -> suivant;
    }

    pliste_reverse_surplace(tempchampel);
    this->type.val.record.champs = tempchampel;

    return 0;
  }
    break;
          
  case pdvaltype::PDTProcedure:
    pmesserr("pevalt::fromPDValt: D'après la spécification de la fonction, normalement on n'arrive jamais ici (DTC PDTProcedure).");
    assert(false);
    return -101;
    break;
  case pdvaltype::PDTFunction:
    pmesserr("pevalt::fromPDValt: D'après la spécification de la fonction, normalement on n'arrive jamais ici ; dû au problème de la différenciation entre lval et rval (lecture et écriture) (DTC PDTFunction).");
    assert(false);
    return -111;
    break;
  case pdvaltype::PDTRetour:
    pmesserr("pevalt::fromPDValt: D'après de la spécification de la fonction, normalement on n'arrive jamais ici ; lval & rval ; lecture & écriture ; (DTC PDTRetour)");
    assert(false);
    return -121;
    break;

    //  case pdvaltype::PDTUser:
    //    this->type.type = PETUser;
    //    this->type.val = dvalt.type.val.user;
    //pmesserr("pevalt::fromPDValt: PDTUser, pas encore implémenté.");
    //    return -131;
    //    break;

  case pdvaltype::PDTVar:
    VERIF_OK(pmemread(mem, dvalt.val.val.var, sval));
    VERIF_OK(pdvalt::pdvalt_of_pdvaltype(*(dvalt.type.val.var), sval.ptr, tempdvalt));
    VERIF_OK(this->fromPDValt(mem, tempdvalt));
    return 0;
    break;

  default:
    pmesserr("pevalt::fromPDValt: Bon ton type de DValt est inconnu.");
    assert(false);
    return -9999;
  }

  assert(false);
  return -1;
}





// Alors, a priori, il y a un petit problème étant donné que qu'on ne connait pas le type
// de la SVal. Qu'importe, l'objet qui appelle la méthode, on suppose que lui
// en possède un qui est correct (ce qui n'est pas stupide ;-) ).
int pevalt::fromPSVal(const psval sval) {

  switch (this->type.type) {
  case pevaltype::PETBoolean: this->val.val.b = sval.b; return 0; break;
  case pevaltype::PETInteger: this->val.val.i = sval.i; return 0; break;
  case pevaltype::PETSubrange: this->val.val.s = sval.s; return 0; break;
  case pevaltype::PETReal: this->val.val.r = sval.r; return 0; break;
  case pevaltype::PETString: this->val.val.str = sval.str; return 0; break;
  case pevaltype::PETPointer: this->val.val.ptr = sval.ptr; return 0; break;
  case pevaltype::PETArray: pmesserr("pevalt::fromPSVal: DTC PETArray; array pas un sval."); assert(false); return -71; break;
  case pevaltype::PETRecord: pmesserr("pevalt::fromPSVal: DTC PETRecord; record pas un sval."); assert(false); return -81; break;
  default: pmesserr("pevalt::fromPSVal: type inconnu. As-tu mis correctement le champ TYPE?"); assert(false); return -9999;
  }

  assert(false);
  return -1;
}





#define CPEXPR_TOSTRING1(que,str) {              \
    aa = str;                                    \
    b = val . que . e->toString();               \
    c = STRCAT2_(aa,b);                          \
    delete b;                                    \
    return c;                                    \
  }

#define CPEXPR_TOSTRING2(que,str) {              \
    a = val . que . e1 -> toString();            \
    bb = str;                                    \
    c = val . que . e2 -> toString();            \
    d = STRCAT3_(a,bb,c);                        \
    delete a;                                    \
    delete c;                                    \
    return d;                                    \
  }


// La fonction de conversion vers une chaine de caractère.
char * CPexpr::toString(void) const {
  char * a, * b, * c, * d, * e, * f, * g;
  const char * aa, * bb, * cc, * dd, * ee, * ff, * gg;
  class pliste<CPexpr> * temp;
    
  switch (type) {
    //   enum etype {PEt, POu, PEqual, PDiff, PInf, PSup, PInfEq, PSupEq, PIPlus, PIMoins, PIMult, PIDiv, PIMod, PRPlus, PRMoins, PRMult, PRDiv, PTab, PNot, PUIPlus, PUIMoins, PURPlus, PURMoins, PRef, PInd, PIdent, PConst, PDummy};
  case PEt:     CPEXPR_TOSTRING2(upet,    " and "); break;
  case POu:     CPEXPR_TOSTRING2(upou,    " or ");  break;
  case PEqual:  CPEXPR_TOSTRING2(upequal, " = ");   break;
  case PDiff:   CPEXPR_TOSTRING2(updiff,  " <> ");  break;
  case PInf:    CPEXPR_TOSTRING2(upinf,   " < ");   break;
  case PSup:    CPEXPR_TOSTRING2(upsup,   " > ");   break;
  case PInfEq:  CPEXPR_TOSTRING2(upinfeq, " <= ");  break;
  case PSupEq:  CPEXPR_TOSTRING2(upsupeq, " >= ");  break;
  case PIPlus:  CPEXPR_TOSTRING2(upiplus, " + ");   break;
  case PIMoins: CPEXPR_TOSTRING2(upimoins," - ");   break;
  case PIMult:  CPEXPR_TOSTRING2(upimult, " * ");   break;
  case PIDiv:   CPEXPR_TOSTRING2(upidiv,  " div "); break;
  case PIMod:   CPEXPR_TOSTRING2(upimod,  " mod "); break;
  case PRPlus:  CPEXPR_TOSTRING2(uprplus, " +. ");  break;
  case PRMoins: CPEXPR_TOSTRING2(uprmoins," -. ");  break;
  case PRMult:  CPEXPR_TOSTRING2(uprmult, " *. ");  break;
  case PRDiv:   CPEXPR_TOSTRING2(uprdiv,  " /. ");  break;

  case PTab:
    a = val.uptab.e1->toString();
    c = val.uptab.e2->toString();
    e = STRCAT4_(a, "[", c, "]");
    delete [] a;
    delete [] c;
    return e;
    break;

  case PRecord:
    a = val.uprecord.e->toString();
    cc = val.uprecord.champ;
    d = STRCAT3_(a, " . ", cc);
    delete [] a;
    return d;
    break;

  case PNot:     CPEXPR_TOSTRING1(upnot,    " not "); break;
  case PUIPlus:  CPEXPR_TOSTRING1(upuiplus, " + ");   break;
  case PUIMoins: CPEXPR_TOSTRING1(upuimoins," - ");   break;
  case PURPlus:  CPEXPR_TOSTRING1(upurplus, " +. ");  break;
  case PURMoins: CPEXPR_TOSTRING1(upurmoins," -. ");  break;
  case PRef:     CPEXPR_TOSTRING1(upref," ^ ");  break;
  case PInd:     
    a = val.upind.e -> toString();    
    c = STRCAT2_(a, " ^ ");
    delete[] a;
    return c;        
    break;

  case PIdent: return strcopy(val.upident.pident); break;
  case PConst: return val.upconst.pconst.toString(); break;

  case PCall: 
    a = STRCAT2_(val.upcall.ident, " ( ");
    temp = val.upcall.args;
    while (temp != NULL) {
      b = temp->a->toString();
      d = STRCAT3_(a,b," , ");
      delete [] a;
      delete [] b;
      a = d;
      temp = temp->suivant;
    }
    c = STRCAT2_(a," ) ");
    delete a;
    return c;
    break;

  case PMenu: {
    class pliste<struct CPexpr::utype::SPMenu::item> *temp;
      
    a = STRCAT3_("Menu ( ",val.upmenu.nom," ) Begin ");
    temp = val.upmenu.pitems;
    while (temp != NULL) {
      if (temp->a->iconfile == NULL) {
        e = STRCAT4_(a,"Item ( ",temp->a->message,") ; ");
        delete[] a;
        a = e;
      }
      else {
        g = STRCAT6_(a,"Item ( ",temp->a->message,", ",temp->a->iconfile,") ; ");
        delete [] a;
        a = g;
      }
      temp = temp->suivant;
    }

    c = STRCAT2_(a," End ");
    delete [] a;
    return c;
  }
    break;
    
  case PNomCarte:
    return strcopy("NomCarte()");
    break;

  default:
    pmesserr("CPexpr::toString: element non gere.");
    assert(false);
    return NULL;
  }


  assert(false);
  return NULL;
}






int CPexpr::l_evaluate(const penv env, const pmem mem, pevalt &res) {
  int ret;
  pevalt e, e1, e2;
  int min, max;
  pevaltype *evaltype_ptr;
  unsigned int taille;
  ploc where;
  psval sval;
  pdvalt dvalt;
  char * nom;
  class pliste<pevaltype::utype::tpetrecord::champ> * tempchamps;
  char * tempchar_ptr;
  

  switch (this -> type) {
  case PEt: pmesserr(position.toString()); pmesserr("CPexpr::l_evaluate: bon bon bon..., il m'est impossible de connaître l'adresse d'une opération ET. Mais si toi tu y arrives, vas-y, je t'écoute."); return -11; break;
  case POu: pmesserr(position.toString()); pmesserr("CPexpr::l_evaluate: adresse d'un OU => DTC"); return -21; break;
  case PEqual:  pmesserr(position.toString()); pmesserr("CPexpr::l_evaluate: adresse d'un EQUAL => DTC"); return -31; break;
  case PDiff: pmesserr(position.toString()); pmesserr("CPexpr::l_evaluate: adresse d'un DIFF => DTC"); return -41; break;
  case PInf: pmesserr(position.toString()); pmesserr("CPexpr::l_evaluate: adresse d'un INF => DTC"); return -51; break;
  case PSup: pmesserr(position.toString()); pmesserr("CPexpr::l_evaluate: adresse d'un SUP => DTC"); return -61; break;
  case PInfEq: pmesserr(position.toString()); pmesserr("CPexpr::l_evaluate: adresse d'un INFEQ => DTC"); return -71; break;
  case PSupEq: pmesserr(position.toString()); pmesserr("CPexpr::l_evaluate: adresse d'un SUPEQ => DTC"); return -81; break;
  case PIPlus: pmesserr(position.toString()); pmesserr("CPexpr::l_evaluate: adresse d'un IPlus => DTC"); return -91; break; 
  case PIMoins: pmesserr(position.toString()); pmesserr("CPexpr::l_evaluate: adresse d'un IMoins => DTC"); return -101; break;
  case PIMult: pmesserr(position.toString()); pmesserr("CPexpr::l_evaluate: adresse d'un IMult => DTC"); return -111; break;
  case PIDiv: pmesserr(position.toString()); pmesserr("CPexpr::l_evaluate: adresse d'un IDiv => DTC"); return -121; break; 
  case PIMod: pmesserr(position.toString()); pmesserr("CPexpr::l_evaluate: adresse d'un IMod => DTC"); return -131; break; 
  case PRPlus: pmesserr(position.toString()); pmesserr("CPexpr::l_evaluate: adresse d'un RPlus => DTC"); return -141; break; 
  case PRMoins: pmesserr(position.toString()); pmesserr("CPexpr::l_evaluate: adresse d'un RMoins => DTC"); return -151; break;
  case PRMult: pmesserr(position.toString()); pmesserr("CPexpr::l_evaluate: adresse d'un RMult => DTC"); return -161; break;
  case PRDiv:  pmesserr(position.toString()); pmesserr("CPexpr::l_evaluate: adresse d'un RDiv => DTC"); return -171; break;

  case PTab: {
    VERIF_OK(this->val.uptab.e1->r_evaluate(env, mem, e1));
    VERIF_OK(this->val.uptab.e2->r_evaluate(env, mem, e2));

    if (e1.type.type != pevaltype::PETArray) {
      pmesserr(position.toString());
      pmesserr("ok. Bon, y a un truc que tu dois comprendre. Relis la doc les types et l'operateur [], car manifestement tu n'as rien compris: IL NOUS FAUT UN TABLEAU!!! et pas un %s.", e1.type.toString());
      return -182;
    }

    min = e1.type.val.array.indice.min;
    max = e1.type.val.array.indice.max;
    evaltype_ptr = e1.type.val.array.type;
    switch (evaltype_ptr->type) {
    case pevaltype::PETBoolean: break;
    case pevaltype::PETInteger: break;
    case pevaltype::PETSubrange: break;
    case pevaltype::PETReal: break;
    case pevaltype::PETString: break;
    case pevaltype::PETPointer: break;
    case pevaltype::PETArray: pmesserr(position.toString()); pmesserr("L_VAL: Impossible de prendre l'adresse d'un tableau."); return -1841; break;
    case pevaltype::PETRecord: pmesserr(position.toString()); pmesserr("L_VAL: Impossible de prendre l'adresse d'un enregistrement."); return -1842; break;
    default: pmesserr(position.toString()); pmesserr("L_VAL: Ce tableau est un tableau d'éléments dont le type est inconnu."); assert(false); return -1849999;
    }
      
    taille = pevaltype::pevaltype_sizeof(*(evaltype_ptr));

    if (e2.type.type == pevaltype::PETInteger) {
      if (e2.val.val.i >= min && e2.val.val.i <= max) {
        res.type.type = pevaltype::PETPointer;
        res.type.val.ptr = evaltype_ptr;
        where = e1.val.val.array + (e2.val.val.i - min) * taille;
        res.val.val.ptr = where;
        return 0;
      }

      pmesserr(position.toString());
      pmesserr("He Ho!!!! L'indice (%d) est en dehors des limites du tableau (%d et %d).", e2.val.val.i, min, max);
      return -185;
    }

    if (e2.type.type == pevaltype::PETSubrange) {
      if (e2.type.val.array.indice.min == min && e2.type.val.array.indice.max == max) {
        res.type.type = pevaltype::PETPointer;
        res.type.val.ptr = evaltype_ptr;
        where = e1.val.val.array + (e2.val.val.s - min) * taille;
        res.val.val.ptr = where;
        return 0;
      }

      pmesserr(position.toString());
      pmesserr("C'est de mettre en indice un element de type intervalle, seulement, ce serait pas mal qu'il soit du meme type (meme min et max).");
      return -187;
    }

    pmesserr(position.toString());
    pmesserr("Salut tout le monde. Bon, on ne peut pas indicer un tableau avec n'importe quoi. On ne peut mettre que des entiers ou des elements d'intervalles.");
    return -188;
  }  
    break;


  case PRecord: {
    VERIF_OK(this->val.uprecord.e->l_evaluate(env, mem, e));
    
    if (this->val.uprecord.champ == NULL) {
      pmesserr(position.toString());
      pmesserr("CPexpr::l_evaluate(): PRecord: champ est nul.");
      return -1001;
    }

    if (this->val.uprecord.champ[0] == '\0') {
      pmesserr(position.toString());
      pmesserr("CPexpr::l_evaluate(): PRecord: champ est vide.");
      return -1002;
    }

    if (e.type.type != pevaltype::PETPointer) {
      pmesserr(position.toString());
      pmesserr("CPexpr::l_evaluate(): PRecord: erreur interne. L'élément de gauche n'est pas un POINTEUR après l-évaluation.");
      return -1003;
    }
      
    evaltype_ptr = e.type.val.ptr;
    if (evaltype_ptr->type != pevaltype::PETRecord) {
      pmesserr(position.toString());
      pmesserr("CPexpr::l_evaluate(): PRecord: L'élément de gauche n'est pas un RECORD.");
      return -1004;
    }
      

    where = e.val.val.ptr;
    tempchamps = evaltype_ptr->val.record.champs;
    while (tempchamps != NULL) {
      if (strcmp(tempchamps->a->nom, this->val.uprecord.champ) == 0) {
        res.type.type = pevaltype::PETPointer;
        res.type.val.ptr = tempchamps->a->type;
        res.val.val.ptr = where;
        return 0;
      }
      where += pevaltype::pevaltype_sizeof(*(tempchamps->a->type));
      tempchamps = tempchamps->suivant;
    }
    
    pmesserr(position.toString());
    tempchar_ptr = evaltype_ptr -> toString();
    pmesserr("CPexpr::l_evaluate(): PRecord: L'élément de droite \"%s\" n'est pas un champ de l'enregistrement '%s'.", this->val.uprecord.champ, tempchar_ptr);
    delete tempchar_ptr;
    return -1005;
  }
    break;

  case PNot: pmesserr(position.toString()); pmesserr("Impossible de L-évaluer une telle expression (NOT)."); return -191; break;
  case PUIPlus: pmesserr(position.toString()); pmesserr("Impossible de L-évaluer une telle expression (PLUS UNAiRE ENTIER)."); return -201; break;
  case PUIMoins: pmesserr(position.toString()); pmesserr("Impossible de L-évaluer une telle expression (MOINS UNAIRE ENTIER)."); return -211; break;
  case PURPlus: pmesserr(position.toString()); pmesserr("Impossible de L-évaluer une telle expression (PLUS UNAIRE REEL)."); return -221; break;
  case PURMoins: pmesserr(position.toString()); pmesserr("Impossible de L-évaluer une telle expression (MOINS UNAIRE REEL)."); return -231; break;
  case PRef: pmesserr(position.toString()); pmesserr("Tu me demandes de prendre l'adresse d'une adresse! qui est une valeur constante cela dit en passant. La L-évaluation a donc échouée."); return -241; break;   

  case PInd:
    VERIF_OK(this->val.upind.e->r_evaluate(env, mem, e));

    if (e.type.type != pevaltype::PETPointer) {
      pmesserr(position.toString());
      pmesserr("Impossible de réaliser une indirection sur une telle expression. J'ai besoin d'un pointeur bordel de merde.");
      return -251;
    }

    res = e;
    return 0;
    break;

  case PIdent: {
    pmessage("L_EVAL: PIdent de la variable...");
    nom = this->val.upident.pident;
    if (nom == NULL) {
      pmesserr(position.toString());
      pmesserr("L_EVAL: Erreur interne: apparemment là il y a une variable, et son nom est NULL.");
      return -261;
    }

    pmessage("L_EVAL: dont le nom est %s", nom);
    ret = penvlookup(env, nom, dvalt);
    if (ret < 0) {
      pmesserr(position.toString());
      pmesserr("L_EVAL: On ne trouve pas la variable '%s' dans l'environnement.", nom);
      return -262;
    }

    res.type.type = pevaltype::PETPointer;
    res.type.val.ptr = new pevaltype;
    pmessage("On essaye d'afficher son type...");

    pmesserr(dvalt.type.toString());
    if (dvalt.type.type == pdvaltype::PDTRetour) {
      ret = pevaltype::pevaltype_of_pdvaltype(*(dvalt.type.val.ret.type), *(res.type.val.ptr));
    }
    else {
      ret = pevaltype::pevaltype_of_pdvaltype(dvalt.type, *(res.type.val.ptr));
    }
    if (ret < 0) {
      pmesserr(position.toString());
      pmesserr("L_EVAL: Impossible de faire de la variable '%s' un résultat d'une l_evaluation.", nom);
      return -263;
    }

    switch (dvalt.type.type) {
    case pdvaltype::PDTConstante: pmesserr(position.toString()); pmesserr("L_EVAL: impossible de L_évaluer une constante."); return -264; break;
    case pdvaltype::PDTBoolean: res.val.val.ptr = dvalt.val.val.b; return 0; break;
    case pdvaltype::PDTInteger: res.val.val.ptr = dvalt.val.val.i; return 0; break;
    case pdvaltype::PDTSubrange: res.val.val.ptr = dvalt.val.val.s; return 0; break;
    case pdvaltype::PDTReal: res.val.val.ptr = dvalt.val.val.r; return 0; break;
    case pdvaltype::PDTString: res.val.val.ptr = dvalt.val.val.str; return 0; break;
    case pdvaltype::PDTPointer: res.val.val.ptr = dvalt.val.val.ptr; return 0; break;
    case pdvaltype::PDTArray: pmesserr(position.toString()); pmesserr("L_EVAL: impossible de prendre l'adresse d'un tableau."); return -265; break;
    case pdvaltype::PDTRecord: pmesserr(position.toString()); pmesserr("L_EVAL: impossible de prendre l'adresse d'un enregistrement."); return -266; break;
    case pdvaltype::PDTProcedure: res.val.val.ptr = dvalt.val.val.proc; return 0; break;
    case pdvaltype::PDTFunction: res.val.val.ptr = dvalt.val.val.func; return 0; break;
    case pdvaltype::PDTRetour: res.val.val.ptr = dvalt.val.val.ret.write; return 0; break;
    case pdvaltype::PDTVar: VERIF_OK(pmemread(mem, dvalt.val.val.var, sval)); res.val.val.ptr = sval.ptr; return 0; break;
    default: pmesserr(position.toString()); pmesserr("L_EVAL: Bon ton ident ton je dois prendre l'adresse a un type inconnu."); assert(false); return -269999;
    }

    assert(false);
    return -260;
  }
    break;
       
  case PConst: pmesserr(position.toString()); pmesserr("L_EVAL: Ecoute, tu me dis comment prendre l'adresse d'une constante, et après on voit."); return -271; break; 
  case PCall: pmesserr(position.toString()); pmesserr("L_EVAL: Ecoute, tu me dis comment prendre l'adresse d'un appel de fonction, et après on voit."); return -281; break;
  case PMenu: pmesserr(position.toString()); pmesserr("L_EVAL: Ecoute, tu me dis comment prendre l'adresse d'un menu, et après on voit."); return -281; break;
  case PNomCarte: pmesserr(position.toString()); pmesserr("L_EVAL: Ca ne marche pas pour PNomCarte."); return -291; break; 
  default: pmesserr(this->position.toString()); pmesserr("Cette opération est inconnue d'une lval."); return -9999;
  }


  assert(false);
  return -1;
}





// En théorie, mem et env sont const, mais en pratique on déclare des variables locales.
int CPexpr::r_evaluate(const penv env, pmem mem, pevalt &res) {



  int ret;
  pevalt e, e1, e2;
  int min, max;
  pevaltype *evaltype_ptr;
  unsigned int taille;
  ploc where;
  psval sval;
  pdvalt dvalt;
  char *nom;
  class pliste<pevaltype::utype::tpetrecord::champ> *tempchamps;  
  char *tempchar_ptr;


  switch (this->type) {
  case PEt:
    VERIF_OK(this->val.upet.e1->r_evaluate(env, mem, e1));
    VERIF_OK(this->val.upet.e2->r_evaluate(env, mem, e2));

    VERIF_TYPE(e1,pevaltype::PETBoolean);
    VERIF_TYPE(e2,pevaltype::PETBoolean);

    res.type.type = pevaltype::PETBoolean;
    res.val.val.b = e1.val.val.b && e2.val.val.b;

    return 0;
    break;

  case POu:
    VERIF_OK(this->val.upou.e1->r_evaluate(env, mem, e1));
    VERIF_OK(this->val.upou.e2->r_evaluate(env, mem, e2));

    VERIF_TYPE(e1,pevaltype::PETBoolean);
    VERIF_TYPE(e2,pevaltype::PETBoolean);

    res.type.type = pevaltype::PETBoolean;
    res.val.val.b = e1.val.val.b || e2.val.val.b;

    return 0;
    break;

  case PEqual: {
    VERIF_OK(this->val.upequal.e1->r_evaluate(env, mem, e1));
    VERIF_OK(this->val.upequal.e2->r_evaluate(env, mem, e2));

    VERIF_TYPE_EQUAL(e1,e2);

    ret = pevalt::equal(e1.type, e1.val, e2.val);
    res.type.type = pevaltype::PETBoolean;
    res.val.val.b = ret;

    return 0;
  }
    break;
  
  case PDiff:
    VERIF_OK(this->val.updiff.e1->r_evaluate(env, mem, e1));
    VERIF_OK(this->val.updiff.e2->r_evaluate(env, mem, e2));

    VERIF_TYPE_EQUAL(e1,e2);

    ret = pevalt::equal(e1.type, e1.val, e2.val);
    res.type.type = pevaltype::PETBoolean;
    res.val.val.b = !ret;
    return 0;
    break;

  case PInf: {
    VERIF_OK(this->val.upinf.e1->r_evaluate(env, mem, e1));
    VERIF_OK(this->val.upinf.e2->r_evaluate(env, mem, e2));

    VERIF_TYPE_EQUAL(e1,e2);

    res.type.type = pevaltype::PETBoolean;
    switch (e1.type.type) {
    case pevaltype::PETBoolean: pmesserr(position.toString()); pmesserr("Hum. Personnellement, il m'est impossible de savoir entre deux booleens lequel est le plus grand."); return -52; break;
    case pevaltype::PETInteger: res.val.val.b = e1.val.val.i < e2.val.val.i; return 0; break;
    case pevaltype::PETSubrange: res.val.val.b = e1.val.val.s < e2.val.val.s; return 0; break;
    case pevaltype::PETReal: res.val.val.b = e1.val.val.r < e2.val.val.r; return 0; break;
    case pevaltype::PETString: pmesserr(position.toString()); pmesserr("Bon, reste a savoir ce que tu entends par la comparaison de deux chaines de caracteres..."); return -53; break;
    case pevaltype::PETPointer: pmesserr(position.toString()); pmesserr("Euh, la, vraiment, tu te fous de moi! Comparer des pointeurs! N'importe quoi!!!! On est en Pascal ICI!!!!! Pas en C!!!!!"); return -54; break;
    case pevaltype::PETArray: pmesserr(position.toString()); pmesserr("Franchement, je me demande ce que peut bien etre la comparaison de deux tableaux."); return -55; break;
    case pevaltype::PETRecord: pmesserr(position.toString()); pmesserr("Ecoute la, tu m'enerves! Comment veux-tu comparer deux records!!??? T'es vraiment trop con...."); return -56; break;
    default: pmesserr(position.toString()); pmesserr("Lors d'un Inf, evaluation d'un type inconnu."); assert(false); return -1;
    }
    
    assert(false);
    return -1;
  }
    break;

  case PSup: {
    VERIF_OK(this->val.upsup.e1->r_evaluate(env, mem, e1));
    VERIF_OK(this->val.upsup.e2->r_evaluate(env, mem, e2));

    VERIF_TYPE_EQUAL(e1,e2);

    res.type.type = pevaltype::PETBoolean;
    switch (e1.type.type) {
    case pevaltype::PETBoolean: pmesserr(position.toString()); pmesserr("Hum. Personnellement, il m'est impossible de savoir entre deux booleens lequel est le plus grand."); return -62; break;
    case pevaltype::PETInteger: res.val.val.b = e1.val.val.i > e2.val.val.i; return 0; break;
    case pevaltype::PETSubrange: res.val.val.b = e1.val.val.s > e2.val.val.s; return 0; break;
    case pevaltype::PETReal: res.val.val.b = e1.val.val.r > e2.val.val.r; return 0; break;
    case pevaltype::PETString: pmesserr(position.toString()); pmesserr("Bon, reste a savoir ce que tu entends par la comparaison de deux chaines de caracteres..."); return -63; break;
    case pevaltype::PETPointer: pmesserr(position.toString()); pmesserr("Euh, la, vraiment, tu te fous de moi! Comparer des pointeurs! N'importe quoi!!!! On est en Pascal ICI!!!!! Pas en C!!!!!"); return -64; break;
    case pevaltype::PETArray: pmesserr(position.toString()); pmesserr("Franchement, je me demande ce que peut bien etre la comparaison de deux tableaux."); return -65; break;
    case pevaltype::PETRecord: pmesserr(position.toString()); pmesserr("Ecoute la, tu m'enerve! Comment veux-tu comparer deux records!!??? T'es vraiment trop con...."); return -66; break;
    default: pmesserr(position.toString()); pmesserr("Lors d'un Sup, evaluation d'un type inconnu."); assert(false); return -1;
    }

    assert(false);
    return -1;
  }
    break;

  case PInfEq: {
    VERIF_OK(this->val.upinfeq.e1->r_evaluate(env, mem, e1));
    VERIF_OK(this->val.upinfeq.e2->r_evaluate(env, mem, e2));

    VERIF_TYPE_EQUAL(e1,e2);

    res.type.type = pevaltype::PETBoolean;
    switch (e1.type.type) {
    case pevaltype::PETBoolean: pmesserr(position.toString()); pmesserr("Hum. Personnellement, il m'est impossible de savoir entre deux booleens lequel est le plus grand."); return -72; break;
    case pevaltype::PETInteger: res.val.val.b = e1.val.val.i <= e2.val.val.i; return 0; break;
    case pevaltype::PETSubrange: res.val.val.b = e1.val.val.s <= e2.val.val.s; return 0; break;
    case pevaltype::PETReal: res.val.val.b = e1.val.val.r <= e2.val.val.r; return 0; break;
    case pevaltype::PETString: pmesserr(position.toString()); pmesserr("Bon, reste a savoir ce que tu entends par la comparaison de deux chaines de caracteres..."); return -73; break;
    case pevaltype::PETPointer: pmesserr(position.toString()); pmesserr("Euh, la, vraiment, tu te fous de moi! Comparer des pointeurs! N'importe quoi!!!! On est en Pascal ICI!!!!! Pas en C!!!!!"); return -74; break;
    case pevaltype::PETArray: pmesserr(position.toString()); pmesserr("Franchement, je me demande ce que peut bien etre la comparaison de deux tableaux."); return -75; break;
    case pevaltype::PETRecord: pmesserr(position.toString()); pmesserr("Ecoute la, tu m'enerves! Comment veux-tu comparer deux records!!??? T'es vraiment trop con...."); return -76; break;
    default: pmesserr(position.toString()); pmesserr("Lors d'un InfEq, evaluation d'un type inconnu."); assert(false); return -1;
    }
    assert(false);
    return -1;
  }
    break;

  case PSupEq: {
    VERIF_OK(this->val.upsupeq.e1->r_evaluate(env, mem, e1));
    VERIF_OK(this->val.upsupeq.e2->r_evaluate(env, mem, e2));

    VERIF_TYPE_EQUAL(e1,e2);

    res.type.type = pevaltype::PETBoolean;
    switch (e1.type.type) {
    case pevaltype::PETBoolean: pmesserr(position.toString()); pmesserr("Hum. Personnellement, il m'est impossible de savoir entre deux booleens lequel est le plus grand."); return -82; break;
    case pevaltype::PETInteger: res.val.val.b = e1.val.val.i >= e2.val.val.i; return 0; break;
    case pevaltype::PETSubrange: res.val.val.b = e1.val.val.s >= e2.val.val.s; return 0; break;
    case pevaltype::PETReal: res.val.val.b = e1.val.val.r >= e2.val.val.r; return 0; break;
    case pevaltype::PETString: pmesserr(position.toString()); pmesserr("Bon, reste a savoir ce que tu entends par la comparaison de deux chaines de caracteres..."); return -83; break;
    case pevaltype::PETPointer: pmesserr(position.toString()); pmesserr("Euh, la, vraiment, tu te fous de moi! Comparer des pointeurs! N'importe quoi!!!! On est en Pascal ICI!!!!! Pas en C!!!!!"); return -84; break;
    case pevaltype::PETArray: pmesserr(position.toString()); pmesserr("Franchement, je me demande ce que peut bien etre la comparaison de deux tableaux."); return -85; break;
    case pevaltype::PETRecord: pmesserr(position.toString()); pmesserr("Ecoute la, tu m'enerves! Comment veux-tu comparer deux records!!??? T'es vraiment trop con...."); return -86; break;
    default: pmesserr(position.toString()); pmesserr("Lors d'un SupEq, evaluation d'un type inconnu."); assert(false); return -1; 
    }
    assert(false);
    return -1;
  }
    break;


  case PIPlus: {
    VERIF_OK(this->val.upiplus.e1->r_evaluate(env, mem, e1));
    VERIF_OK(this->val.upiplus.e2->r_evaluate(env, mem, e2));

    VERIF_TYPE_EQUAL(e1,e2);

    if (e1.type.type == pevaltype::PETInteger) { 
      res.type.type = pevaltype::PETInteger;
      res.val.val.i = e1.val.val.i + e2.val.val.i;
      return 0;
    }

    if (e1.type.type == pevaltype::PETSubrange) {
      res.type.type = pevaltype::PETSubrange;
      res.type.val.s.min = e1.type.val.s.min;
      res.type.val.s.max = e1.type.val.s.max;
      res.val.val.s = e1.val.val.s + e2.val.val.s;
      if (res.val.val.s < res.type.val.s.min || res.val.val.s > res.type.val.s.max) {
        pmesserr(position.toString());
        pmesserr("Alors, ici on a un petit probleme. En effet, nous sommes en train de considerer une addition sur des elements d'un intervalle [%d ; %d]. Cependant, l'evaluation du premier membre donne %d, et le deuxieme membre donne %d, ce qui nous un resultat de %d, et cet element n'appartient pas a l'intervalle.", e1.type.val.s.min, e1.type.val.s.max, e1.val.val.s, e2.val.val.s, res.val.val.s);
        return -92;
      }
      return 0;
    }
    
    pmesserr(position.toString());
    pmesserr("L'opération plus n'est définie que pour les entiers et les intervalles, et en plus quand uniquement les deux elements sont rigoureusement du meme type (type du 1er element : %s ; type du 2eme element : %s).", e1.type.toString(), e2.type.toString());
    return -93;
  
  }
    break;
   
 
  case PIMoins: {
    VERIF_OK(this->val.upimoins.e1->r_evaluate(env, mem, e1));
    VERIF_OK(this->val.upimoins.e2->r_evaluate(env, mem, e2));

    VERIF_TYPE_EQUAL(e1,e2);

    if (e1.type.type == pevaltype::PETInteger) {
      res.type.type = pevaltype::PETInteger;
      res.val.val.i = e1.val.val.i - e2.val.val.i;
      return 0;
    }

    if (e1.type.type == pevaltype::PETSubrange) {
      res.type.type = pevaltype::PETSubrange;
      res.type.val.s.min = e1.type.val.s.min;
      res.type.val.s.max = e1.type.val.s.max;
      res.val.val.s = e1.val.val.s - e2.val.val.s;
      if (res.val.val.s < res.type.val.s.min || res.val.val.s > res.type.val.s.max) {
        pmesserr(position.toString());
        pmesserr("Alors, ici on a un petit probleme. En effet, nous sommes en train de considerer une soustraction sur des elements d'un intervalle [%d ; %d]. Cependant, l'evaluation du premier membre donne %d, et le deuxieme membre donne %d, ce qui nous un resultat de %d, et cet element n'appartient pas a l'intervalle.", e1.type.val.s.min, e1.type.val.s.max, e1.val.val.s, e2.val.val.s, res.val.val.s);
        return -102;
      }
      return 0;
    }

    pmesserr(position.toString());
    pmesserr("L'opération plus n'est définie que pour les entiers et les intervalles, et en plus quand uniquement les deux elements sont rigoureusement du meme type (type du 1er element : %s ; type du 2eme element : %s).", e1.type.toString(), e2.type.toString());
    return -103;
  }
    break;
    

  case PIMult: {
    VERIF_OK(this->val.upimult.e1->r_evaluate(env, mem, e1));
    VERIF_OK(this->val.upimult.e2->r_evaluate(env, mem, e2));

    VERIF_TYPE_EQUAL(e1,e2);

    if (e1.type.type == pevaltype::PETInteger) {
      res.type.type = pevaltype::PETInteger;
      res.val.val.i = e1.val.val.i * e2.val.val.i;
      return 0;
    }

    if (e1.type.type == pevaltype::PETSubrange) {
      res.type.type = pevaltype::PETSubrange;
      res.type.val.s.min = e1.type.val.s.min;
      res.type.val.s.max = e1.type.val.s.max;
      res.val.val.s = e1.val.val.s * e2.val.val.s;
      if (res.val.val.s < res.type.val.s.min || res.val.val.s > res.type.val.s.max) {
        pmesserr(position.toString());
        pmesserr("Alors, ici on a un petit probleme. En effet, nous sommes en train de considerer une soustraction sur des elements d'un intervalle [%d ; %d]. Cependant, l'evaluation du premier membre donne %d, et le deuxieme membre donne %d, ce qui nous un resultat de %d, et cet element n'appartient pas a l'intervalle.", e1.type.val.s.min, e1.type.val.s.max, e1.val.val.s, e2.val.val.s, res.val.val.s);
        return -112;
      }
      return 0;
    }

    pmesserr(position.toString());
    pmesserr("L'opération plus n'est définie que pour les entiers et les intervalles, et en plus quand uniquement les deux elements sont rigoureusement du meme type (type du 1er element : %s ; type du 2eme element : %s).", e1.type.toString(), e2.type.toString());
    return -113;
  }
    break;
    
  case PIDiv: {
    VERIF_OK(this->val.upidiv.e1->r_evaluate(env, mem, e1));
    VERIF_OK(this->val.upidiv.e2->r_evaluate(env, mem, e2));

    if (e1.type.type == pevaltype::PETInteger) {
      res.type.type = pevaltype::PETInteger;
      res.val.val.i = e1.val.val.i / e2.val.val.i;
      return 0;
    }

    if (e1.type.type == pevaltype::PETSubrange) {
      res.type.type = pevaltype::PETSubrange;
      res.type.val.s.min = e1.type.val.s.min;
      res.type.val.s.max = e1.type.val.s.max;
      res.val.val.s = e1.val.val.s / e2.val.val.s;
      if (res.val.val.s < res.type.val.s.min || res.val.val.s > res.type.val.s.max) {
        pmesserr(position.toString());
        pmesserr("Alors, ici on a un petit probleme. En effet, nous sommes en train de considerer une soustraction sur des elements d'un intervalle [%d ; %d]. Cependant, l'evaluation du premier membre donne %d, et le deuxieme membre donne %d, ce qui nous un resultat de %d, et cet element n'appartient pas a l'intervalle.", e1.type.val.s.min, e1.type.val.s.max, e1.val.val.s, e2.val.val.s, res.val.val.s);
        return -122;
      }
      return 0;
    }

    pmesserr(position.toString());
    pmesserr("L'opération plus n'est définie que pour les entiers et les intervalles, et en plus quand uniquement les deux elements sont rigoureusement du meme type (type du 1er element : %s ; type du 2eme element : %s).", e1.type.toString(), e2.type.toString());
    return -123;
  }
    break;
   
 
  case PIMod: {
    VERIF_OK(this->val.upimod.e1->r_evaluate(env, mem, e1));
    VERIF_OK(this->val.upimod.e2->r_evaluate(env, mem, e2));

    int a, b;

    if (e1.type.type == pevaltype::PETInteger) {
      a = e1.val.val.i;
    }
    else if (e1.type.type == pevaltype::PETSubrange) {
      a = e1.val.val.s;
    }
    else {
      pmesserr(position.toString());
      pmesserr("CPexpr::r_evaluate: e1 n'est pas un scalaire entier mais de type %s (position: %s).", e1.type.toString(), val.upimod.e1->position.toString());
      return -131;
    }


    if (e2.type.type == pevaltype::PETInteger) {
      b = e2.val.val.i;
    }
    else if (e2.type.type == pevaltype::PETSubrange) {
      b = e2.val.val.s;
    }
    else {
      pmesserr(position.toString());
      pmesserr("CPexpr::r_evaluate: e2 n'est pas un scalaire entier mais de type %s (position: %s).", e2.type.toString(), val.upimod.e2->position.toString());
      return -132;
    }

    res.type.type = pevaltype::PETInteger;
    res.val.val.i = a % b;
    
    return 0;
  }
    break;

    
  case PRPlus:
    VERIF_OK(this->val.uprplus.e1->r_evaluate(env, mem, e1));
    VERIF_OK(this->val.uprplus.e2->r_evaluate(env, mem, e2));

    VERIF_TYPE_EQUAL(e1,e2);

    if (e1.type.type == pevaltype::PETReal) {
      res.type.type = pevaltype::PETReal;
      res.val.val.r = e1.val.val.r + e2.val.val.r;
      return 0;
    }

    pmesserr(position.toString());
    pmesserr("Pffff.... Les additions reelles se font sur des reels et uniquement sur des reels (t1 = %s ; t2 = %s).", e1.toString(), e2.toString());
    return -142;
    break;
    
  case PRMoins:
    VERIF_OK(this->val.uprmoins.e1->r_evaluate(env, mem, e1));
    VERIF_OK(this->val.uprmoins.e2->r_evaluate(env, mem, e2));

    VERIF_TYPE_EQUAL(e1,e2);

    if (e1.type.type == pevaltype::PETReal) {
      res.type.type = pevaltype::PETReal;
      res.val.val.r = e1.val.val.r - e2.val.val.r;
      return 0;
    }

    pmesserr(position.toString());
    pmesserr("Pffff.... Les soustractions reelles se font sur des reels et uniquement sur des reels (t1 = %s ; t2 = %s).", e1.toString(), e2.toString());
    return -142;
    break;
    
  case PRMult:
    VERIF_OK(this->val.uprmult.e1->r_evaluate(env, mem, e1));
    VERIF_OK(this->val.uprmult.e2->r_evaluate(env, mem, e2));

    VERIF_TYPE_EQUAL(e1,e2);

    if (e1.type.type == pevaltype::PETReal) {
      res.type.type = pevaltype::PETReal;
      res.val.val.r = e1.val.val.r * e2.val.val.r;
      return 0;
    }

    pmesserr(position.toString());
    pmesserr("Pffff.... Les multiplications reelles se font sur des reels et uniquement sur des reels (t1 = %s ; t2 = %s).", e1.toString(), e2.toString());
    return -142;
    break;
    
  case PRDiv: 
    VERIF_OK(this->val.uprdiv.e1->r_evaluate(env, mem, e1));
    VERIF_OK(this->val.uprdiv.e2->r_evaluate(env, mem, e2));

    VERIF_TYPE_EQUAL(e1,e2);

    if (e1.type.type == pevaltype::PETReal) {
      res.type.type = pevaltype::PETReal;
      res.val.val.r = e1.val.val.r * e2.val.val.r;
      return 0;
    }

    pmesserr(position.toString());
    pmesserr("Pffff.... Les divisions reelles se font sur des reels et uniquement sur des reels (t1 = %s ; t2 = %s).", e1.toString(), e2.toString());
    return -142;
    break;
    

  case PTab: {
    VERIF_OK(this->val.uptab.e1->r_evaluate(env, mem, e1));
    VERIF_OK(this->val.uptab.e2->r_evaluate(env, mem, e2));

    if (e1.type.type != pevaltype::PETArray) {
      pmesserr(position.toString());
      pmesserr("ok. Bon, y a un truc que tu dois comprendre. Relis la doc les types et l'operateur [], car manifestement tu n'as rien compris: IL NOUS FAUT UN TABLEAU !!! et pas un %s.", e1.type.toString());
      return -182;
    }
    
    min  = e1.type.val.array.indice.min;
    max  = e1.type.val.array.indice.max;
    evaltype_ptr = e1.type.val.array.type;
    taille = pevaltype::pevaltype_sizeof(*(evaltype_ptr));

    if (e2.type.type == pevaltype::PETInteger) {
      if (not(min <= e2.val.val.i && e2.val.val.i <= max)) {
        pmesserr(position.toString());
        pmesserr("He Ho!!!! L'indice %d est en dehors des limites du tableau: %d et %d.", e2.val.val.i, min, max);
        return -185;
      }

      res.type = *(evaltype_ptr);
      where = e1.val.val.array + (e2.val.val.i - min) * taille;
      VERIF_OK(pmemread(mem, where, sval));

      // Petit pb: un sval ne possède pas de type!!!!!
      // Cependant, il y a un type dans RES!!!!!!
      res.fromPSVal(sval);
      return 0;
    }

    if (e2.type.type == pevaltype::PETSubrange) {
      if (not(min <= e2.type.val.s.min && e2.type.val.s.max <= max)) {
        pmesserr(position.toString());
        pmesserr("C'est de mettre en indice un element de type intervalle, seulement, ce serait pas mal qu'il soit du meme type (meme min et max).");
        return -187;
      }

      res.type = *(evaltype_ptr);
      where = e1.val.val.array + (e2.val.val.s - min) * taille;
      VERIF_OK(pmemread(mem, where, sval));
      res.fromPSVal(sval);
      return 0;
    }

    pmesserr(position.toString());
    pmesserr("Salut tout le monde. Bon, on ne peut pas indicer un tableau avec n'importe quoi. On ne peut mettre que des entiers ou des elements d'intervalles.");
    return -188;
  }  
    break;


  case PRecord:
    VERIF_OK(this->val.uprecord.e->l_evaluate(env, mem, e));
    
    if (this->val.uprecord.champ == NULL) {
      pmesserr(position.toString());
      pmesserr("CPexpr::r_evaluate(): PRecord: champ est nul.");
      return -1001;
    }

    if (this->val.uprecord.champ[0] == '\0') {
      pmesserr(position.toString());
      pmesserr("CPexpr::r_evaluate(): PRecord: champ est vide.");
      return -1002;
    }

    if (e.type.type != pevaltype::PETPointer) {
      pmesserr(position.toString());
      pmesserr("CPexpr::r_evaluate(): PRecord: erreur interne. L'élément de gauche n'est pas un POINTER après l-évaluation.");
      return -1003;
    }
      
    evaltype_ptr = e.type.val.ptr;
    if (evaltype_ptr->type != pevaltype::PETRecord) {
      pmesserr(position.toString());
      pmesserr("CPexpr::r_evaluate(): PRecord: L'élément de gauche n'est pas un RECORD.");
      return -1004;
    }
      

    where = e.val.val.ptr;
    tempchamps = evaltype_ptr->val.record.champs;
    while (tempchamps != NULL) {
      if (0 == strcmp(tempchamps->a->nom, this->val.uprecord.champ)) {
        pmemread(mem, where, sval);
        res.fromPSVal(sval);
        return 0;
      }
      where += pevaltype::pevaltype_sizeof(*(tempchamps->a->type));
      tempchamps = tempchamps->suivant;
    }
    
    pmesserr(position.toString());
    tempchar_ptr = evaltype_ptr -> toString();
    pmesserr("CPexpr::r_evaluate(): PRecord: L'élément de droite \"%s\" n'est pas un champ de l'enregistrement '%s'.", this->val.uprecord.champ, tempchar_ptr);
    delete tempchar_ptr;
    return -1005;
    break;


  case PNot:
    VERIF_OK(this->val.upnot.e->r_evaluate(env, mem, e));
    
    if (e.type.type != pevaltype::PETBoolean) {
      pmesserr(position.toString());
      pmesserr("Est-ce que tu sais calculer le 'not' d'autre chose qu'un booléen? Non? Et bien moi non plus.");
      return -191;
    }

    res.type.type = pevaltype::PETBoolean;
    res.val.val.b = not(e.val.val.b);
    return 0;
    break;

  case PUIPlus:
    VERIF_OK(this->val.upuiplus.e->r_evaluate(env, mem, e));
    res = e;
    switch (e.type.type) {
    case pevaltype::PETInteger:
    case pevaltype::PETSubrange:
    case pevaltype::PETString: return 0; break;
    case pevaltype::PETBoolean:
    case pevaltype::PETReal:
    case pevaltype::PETPointer:
    case pevaltype::PETArray:
    case pevaltype::PETRecord:
    default: pmesserr(position.toString()); pmesserr("Impossible de calculer le + unaire d'un tel objet."); return -201;
    }

    assert(false);
    return -200;
    break;

  case PUIMoins:
    VERIF_OK(this->val.upuimoins.e->r_evaluate(env, mem, e));
    res = e;
    switch (e.type.type) {
    case pevaltype::PETInteger: res.val.val.i = - e.val.val.i; return 0; break;
    case pevaltype::PETSubrange:
      res.val.val.s = - e.val.val.s;
      if (res.val.val.s < e.type.val.s.min || res.val.val.s > e.type.val.s.max) {
        pmesserr(position.toString());
        pmesserr("Ta variable n'appartient à l'intervalle. Ton intervalle n'est pas symétrique, donc lors d'un '-' unaire, fais attention.");
        return -212;
      }
      return 0;
      break;
    case pevaltype::PETBoolean:
    case pevaltype::PETReal:
    case pevaltype::PETString:
    case pevaltype::PETPointer:
    case pevaltype::PETArray:
    case pevaltype::PETRecord:
    default: pmesserr(position.toString()); pmesserr("Impossible de calculer le - unaire d'un tel objet."); return -211;
    }

    assert(false);
    return -210;
    break;

  case PURPlus:
    VERIF_OK(this->val.upurplus.e->r_evaluate(env, mem, e));
    res = e;
    switch (e.type.type) {
    case pevaltype::PETReal: return 0; break;
    case pevaltype::PETInteger:
    case pevaltype::PETSubrange:
    case pevaltype::PETBoolean:
    case pevaltype::PETString:
    case pevaltype::PETPointer:
    case pevaltype::PETArray:
    case pevaltype::PETRecord:
    default: pmesserr(position.toString()); pmesserr("Impossible de calculer le + unaire réel d'un tel objet."); return -221;
    }

    assert(false);
    return -220;
    break;

  case PURMoins:
    VERIF_OK(this->val.upurmoins.e->r_evaluate(env, mem, e));
    res = e;
    switch (e.type.type) {
    case pevaltype::PETReal: res.val.val.r = - e.val.val.r; return 0; break;
    case pevaltype::PETInteger:
    case pevaltype::PETSubrange:
    case pevaltype::PETBoolean:
    case pevaltype::PETString:
    case pevaltype::PETPointer:
    case pevaltype::PETArray:
    case pevaltype::PETRecord:
    default: pmesserr(position.toString()); pmesserr("Impossible de calculer le - unaire réel d'un tel objet."); return -231;
    }

    assert(false);
    return -230;
    break;

  case PRef:
    VERIF_OK(this->val.upref.e->l_evaluate(env, mem, e));
    res = e;
    return 0;
    break;
      
  case PInd:
    VERIF_OK(this->val.upind.e->r_evaluate(env, mem, e));

    if (e.type.type != pevaltype::PETPointer) {
      pmesserr(position.toString());
      pmesserr("Impossible de réaliser une indirection sur une telle expression. J'ai besoin d'un pointeur bordel de merde.");
      return -251;
    }

    res.type = *(e.type.val.ptr);
    VERIF_OK(pmemread(mem, e.val.val.ptr, sval));
    res.fromPSVal(sval);
    return 0;
    break;

  case PIdent:
    nom = this->val.upident.pident;
    if (nom == NULL) {
      pmesserr(position.toString());
      pmesserr("R_EVAL: Erreur interne: apparemment là il y a une variable, et son nom est NULL.");
      return -261;
    }
    VERIF_OK(penvlookup(env, nom, dvalt));

    // Traiter ici les appels de fonctions sans paramètre.
    // et aussi les valeurs de retour !!! ( ;) )
    // ou plutot dans fromPDValt puisqu'ici on sait qu'on est en lecture.
    // En fait non, car cette fonction est aussi utilisée dans l_evaluate.
    // On va donc faire deux fonctions.
    // fromPDValt n'est pas utilisée par l_evaluation !!!!!!!!!!!
    VERIF_OK(res.r_fromPDValt(mem, dvalt));
    
    return 0;
    break;
       
  case PConst: res = this->val.upconst.pconst; return 0; break;


  case PCall: {
    pmessage("Appel expression avec nom = %s", val.upcall.ident);
    
    VERIF_OK(penvlookup(env, val.upcall.ident, dvalt));

    if (dvalt.type.type == pdvaltype::PDTRetour) {

      // Evaluation des paramètres.
      // Une fois évalués dans l'environnement d'appel (faire attention à var), 
      // on les associe dans l'environnement de la fonction.
      // Pour cela, on déclare, puis on associe.
      class pliste<CPexpr> * tempargs;
      class pliste<struct pdvaltype::tpdtprocedure::param> * tempparams;
      penv tempenv;
      pdvalt tempdvalt, retdvalt;
      ploc i;
      
      tempargs = val.upcall.args;
      tempparams = dvalt.type.val.ret.params;
      tempenv = dvalt.type.val.ret.env;
      
      // Allocation de la valeur de retour.
      taille = dvalt.type.val.ret.type->pdvaltype_sizeof();
      VERIF_OK(pnew(mem, taille, mem, i));
      retdvalt.type.type = pdvaltype::PDTRetour;
      retdvalt.type.val.ret = dvalt.type.val.ret;
      retdvalt.val.val.ret.read = dvalt.val.val.ret.read;
      retdvalt.val.val.ret.write = i;
      VERIF_OK(penvupdate(tempenv, val.upcall.ident, retdvalt, tempenv));

      // Now les args.
      while (tempargs != NULL) {
        if (tempparams == NULL) {
          pmesserr(position.toString());
          pmesserr("CPexpr::r_evaluate: PCall: dans l'appel à fonction %s, il y a trop d'arguments en paramètre.", val.upcall.ident);
          return -283;
        }

        if (tempparams->a->var) {
          VERIF_OK(tempargs->a->l_evaluate(env, mem, e));
        }
        else {
          VERIF_OK(tempargs->a->r_evaluate(env, mem, e));
        }

        // À la main.
        taille = tempparams->a->dvaltype_ptr->pdvaltype_sizeof();
        VERIF_OK(pnew(mem, taille, mem, i));
        VERIF_OK(e.toPSVal(sval));
        VERIF_OK(pmemwrite(mem, i, sval));

        if (tempparams->a->var) {
          tempdvalt.type.type = pdvaltype::PDTVar;
          tempdvalt.type.val.var = tempparams->a->dvaltype_ptr;
          tempdvalt.val.val.var = i;
        }
        else {
          VERIF_OK(pdvalt::pdvalt_of_pdvaltype(*(tempparams->a->dvaltype_ptr), i, tempdvalt));
        }
      
        VERIF_OK(penvupdate(tempenv, tempparams->a->nom, tempdvalt, tempenv));

        // C bon. suivant.
        tempparams = tempparams->suivant;
        tempargs = tempargs->suivant;
      }

      if (tempparams != NULL) {
        pmesserr(position.toString());
        pmesserr("CPexpr::r_evaluate: PCall: dans l'appel à fonction %s, il n'y a pas assez d'arguments en paramètre [%s].", val.upcall.ident, tempparams->a->nom);
        return -289;
      }
    
      // Là c'est OKI, on exécute.
      dvalt . type . val . ret . corps -> execute ( tempenv , mem ) ;
      
      // On récupère la valeur de retour.
      VERIF_OK(res.r_fromPDValt(mem, retdvalt));
    
    }


    else if (dvalt.type.type == pdvaltype::PDTFunction) {
      // Evaluation des paramètres.
      // Une fois évalués dans l'environnement d'appel (faire attention à var), 
      // on les associe dans l'environnement de la fonction.
      // Pour cela, on déclare, puis on associe.
      class pliste<CPexpr> * tempargs;
      class pliste<struct pdvaltype::tpdtprocedure::param> * tempparams;
      penv tempenv;
      pdvalt tempdvalt, retdvalt;
      ploc i;
      
      tempargs = val.upcall.args;
      tempparams = dvalt.type.val.func.params;
      tempenv = dvalt.type.val.func.env;

      // Allocation de la valeur de retour.
      taille = dvalt.type.val.func.type->pdvaltype_sizeof();
      VERIF_OK(pnew(mem, taille, mem, i));
      retdvalt.type.type = pdvaltype::PDTRetour;
      retdvalt.type.val.ret = dvalt.type.val.func;
      retdvalt.val.val.ret.read = dvalt.val.val.func;
      retdvalt.val.val.ret.write = i;
      VERIF_OK(penvupdate(tempenv, val.upcall.ident, retdvalt, tempenv));

      // Now les args.
      while (tempargs != NULL) {
        if (tempparams == NULL) {
          pmesserr(position.toString());
          pmesserr("CPexpr::r_evaluate: PCall: dans l'appel à fonction %s, il y a trop d'arguments en paramètre.", val.upcall.ident);
          return -283;
        }

        if (tempparams->a->var) {
          VERIF_OK(tempargs->a->l_evaluate(env, mem, e));
        }
        else {
          VERIF_OK(tempargs->a->r_evaluate(env, mem, e));
        }

        // À la main.
        taille = tempparams->a->dvaltype_ptr->pdvaltype_sizeof();
        VERIF_OK(pnew(mem, taille, mem, i));
        VERIF_OK(e.toPSVal(sval));
        VERIF_OK(pmemwrite(mem, i, sval));

        if (tempparams->a->var) {
          tempdvalt.type.type = pdvaltype::PDTVar;
          tempdvalt.type.val.var = tempparams->a->dvaltype_ptr;
          tempdvalt.val.val.var = i;
        }
        else {
          VERIF_OK(pdvalt::pdvalt_of_pdvaltype(*(tempparams->a->dvaltype_ptr), i, tempdvalt));
        }
        VERIF_OK(penvupdate(tempenv, tempparams->a->nom, tempdvalt, tempenv));

        // C bon. suivant.
        tempparams = tempparams->suivant;
        tempargs = tempargs->suivant;
      }

      if (tempparams != NULL) {
        pmesserr(position.toString());
        pmesserr("CPexpr::r_evaluate: PCall: dans l'appel à fonction %s, il n'y a pas assez d'arguments en paramètre [%s].", val.upcall.ident, tempparams->a->nom);
        return -289;
      }

      // Là c'est OKI, on exécute.
      dvalt . type . val . func . corps -> execute ( tempenv , mem ) ;
      
      // On récupère la valeur de retour.
      VERIF_OK(res.r_fromPDValt(mem, retdvalt));
    }
    
    else {
      pmesserr(position.toString());
      pmesserr("CPexpr::r_evaluate: PCall: la variable %s n'est pas une fonction mais elle est de type %s..", val.upcall.ident,dvalt.type.toString());
      return -282;
    }
    
    pmessage("Fin Call expression de %s", val.upcall.ident);
    return 0;
  }
    break;


  case PMenu: {
    pmessage("Debut du traitement d'un menu.");
    
    if (this->val.upmenu.nom == NULL) {
      pmesserr(position.toString());
      pmesserr("Ce menu a un nom dont le pointeur est NULL.");
    }

    pmessage("Nom du menu: '%s'", this->val.upmenu.nom);

    // Un menu rend un naturel entre -1 et nbitems-1.
    // -1 dans le cas où le menu est vide.
    class pliste<struct utype::SPMenu::item> *temp;
    int nbitems = 0;
      
    temp = this->val.upmenu.pitems;
    SCRIPT_BeginAfficherMenu();
    while (temp != NULL) {
      if (temp -> a == NULL) {
        pmesserr(position.toString());
        pmesserr("temp->a est NULL.");
      }

      if (temp -> a -> message == NULL) {
        pmesserr(position.toString());
        pmesserr("temp->a->message est NULL.");
      }

      MiniMenu->Add(0, temp->a->message, temp->a->iconfile);
      temp = temp->suivant;
      nbitems++;
    }

    res.type.type = pevaltype::PETInteger;
    res.val.val.i = SCRIPT_AfficherMenu(this->val.upmenu.nom); 
    
    pmessage("Fin du traitement du menu '%s' ; valeur de retour = %d.", this->val.upmenu.nom, res.val.val.s);
    return 0;
  }
    break;

  case PNomCarte: {
    pmessage("exécution de l'instruction PNomCarte.");
    const char * nom_carte = SCRIPT_GetNomCarte();

    e.type.type = pevaltype::PETString;
    e.val.val.str = strcopy(nom_carte);
    return 0;
  }
    break;
    
    
  default: pmesserr(this->position.toString()); pmesserr("Cette opération est inconnue d'une rval."); return -9999;
  }

  assert(false);
  return -1;
}









bool pascal_expr_compile(const CPexpr * expr, pascal_expr_futur_t * &futur) {
  pascal_expr_futur_t * futur1 = NULL;
  pascal_expr_futur_t * futur2 = NULL;
  pascal_expr_futur_cell_t * futur_cell = NULL;
  pascal_expr_futur_cell_t * futur_cell1 = NULL;
  pascal_expr_futur_cell_t * futur_cell2 = NULL;

  futur_cell = new struct pascal_expr_futur_cell_t;
  futur_cell -> type = expr -> type;
  futur = mp(futur_cell, (pliste<pascal_expr_futur_cell_t> *) NULL);

  switch (expr -> type) {
  case CPexpr::PEt:
    VERIF_OK_B(pascal_expr_compile(expr->val.upet.e1, futur1));
    VERIF_OK_B(pascal_expr_compile(expr->val.upet.e2, futur2));
    pliste_concat3_surplace(futur1, futur2, futur);
    futur = futur1;
    return true;
    break;

  case CPexpr::POu:
    VERIF_OK_B(pascal_expr_compile(expr->val.upou.e1, futur1));
    VERIF_OK_B(pascal_expr_compile(expr->val.upou.e2, futur2));
    pliste_concat3_surplace(futur1, futur2, futur);
    futur = futur1;
    return true;
    break;

  case CPexpr::PEqual:
    VERIF_OK_B(pascal_expr_compile(expr->val.upequal.e1, futur1));
    VERIF_OK_B(pascal_expr_compile(expr->val.upequal.e2, futur2));
    pliste_concat3_surplace(futur1, futur2, futur);
    futur = futur1;
    return true;
    break;
  
  case CPexpr::PDiff:
    VERIF_OK_B(pascal_expr_compile(expr->val.updiff.e1, futur1));
    VERIF_OK_B(pascal_expr_compile(expr->val.updiff.e2, futur2));
    pliste_concat3_surplace(futur1, futur2, futur);
    futur = futur1;
    return true;
    break;

  case CPexpr::PInf:
    VERIF_OK_B(pascal_expr_compile(expr->val.upinf.e1, futur1));
    VERIF_OK_B(pascal_expr_compile(expr->val.upinf.e2, futur2));
    pliste_concat3_surplace(futur1, futur2, futur);
    futur = futur1;
    return true;
    break;

  case CPexpr::PSup:
    VERIF_OK_B(pascal_expr_compile(expr->val.upsup.e1, futur1));
    VERIF_OK_B(pascal_expr_compile(expr->val.upsup.e2, futur2));
    futur_cell -> type = CPexpr::PInf;
    pliste_concat3_surplace(futur2, futur1, futur);
    futur = futur2;
    return true;
    break;

  case CPexpr::PInfEq:
    VERIF_OK_B(pascal_expr_compile(expr->val.upinfeq.e1, futur1));
    VERIF_OK_B(pascal_expr_compile(expr->val.upinfeq.e2, futur2));
    futur_cell -> type = CPexpr::PNot;
    futur_cell = new pascal_expr_futur_cell_t;
    futur_cell -> type = CPexpr::PInf;
    futur = mp(futur_cell, futur);
    pliste_concat3_surplace(futur2, futur1, futur);
    futur = futur2;
    return true;
    break;

  case CPexpr::PSupEq:
    VERIF_OK_B(pascal_expr_compile(expr->val.upsupeq.e1, futur1));
    VERIF_OK_B(pascal_expr_compile(expr->val.upsupeq.e2, futur2));
    futur_cell -> type = CPexpr::PNot;
    futur_cell = new pascal_expr_futur_cell_t;
    futur_cell -> type = CPexpr::PInf;
    futur = mp(futur_cell, futur);
    pliste_concat3_surplace(futur1, futur2, futur);
    futur = futur1;
    return true;
    break;

  case CPexpr::PIPlus:
    VERIF_OK_B(pascal_expr_compile(expr->val.upiplus.e1, futur1));
    VERIF_OK_B(pascal_expr_compile(expr->val.upiplus.e2, futur2));
    pliste_concat3_surplace(futur1, futur2, futur);
    futur = futur1;
    return true;
    break;
 
  case CPexpr::PIMoins:
    VERIF_OK_B(pascal_expr_compile(expr->val.upimoins.e1, futur1));
    VERIF_OK_B(pascal_expr_compile(expr->val.upimoins.e2, futur2));
    pliste_concat3_surplace(futur1, futur2, futur);
    futur = futur1;
    return true;
    break;
 
  case CPexpr::PIMult:
    VERIF_OK_B(pascal_expr_compile(expr->val.upimult.e1, futur1));
    VERIF_OK_B(pascal_expr_compile(expr->val.upimult.e2, futur2));
    pliste_concat3_surplace(futur1, futur2, futur);
    futur = futur1;
    return true;
    break;
     
  case CPexpr::PIDiv:
    VERIF_OK_B(pascal_expr_compile(expr->val.upidiv.e1, futur1));
    VERIF_OK_B(pascal_expr_compile(expr->val.upidiv.e2, futur2));
    pliste_concat3_surplace(futur1, futur2, futur);
    futur = futur1;
    return true;
    break;
 
  case CPexpr::PIMod:
    VERIF_OK_B(pascal_expr_compile(expr->val.upimod.e1, futur1));
    VERIF_OK_B(pascal_expr_compile(expr->val.upimod.e2, futur2));
    pliste_concat3_surplace(futur1, futur2, futur);
    futur = futur1;
    return true;
    break;
    
  case CPexpr::PRPlus:
    VERIF_OK_B(pascal_expr_compile(expr->val.uprplus.e1, futur1));
    VERIF_OK_B(pascal_expr_compile(expr->val.uprplus.e2, futur2));
    pliste_concat3_surplace(futur1, futur2, futur);
    futur = futur1;
    return true;
    break;
        
  case CPexpr::PRMoins:
    VERIF_OK_B(pascal_expr_compile(expr->val.uprmoins.e1, futur1));
    VERIF_OK_B(pascal_expr_compile(expr->val.uprmoins.e2, futur2));
    pliste_concat3_surplace(futur1, futur2, futur);
    futur = futur1;
    return true;
    break;
    
  case CPexpr::PRMult:
    VERIF_OK_B(pascal_expr_compile(expr->val.uprmult.e1, futur1));
    VERIF_OK_B(pascal_expr_compile(expr->val.uprmult.e2, futur2));
    pliste_concat3_surplace(futur1, futur2, futur);
    futur = futur1;
    return true;
    break;
    
  case CPexpr::PRDiv: 
    VERIF_OK_B(pascal_expr_compile(expr->val.uprdiv.e1, futur1));
    VERIF_OK_B(pascal_expr_compile(expr->val.uprdiv.e2, futur2));
    pliste_concat3_surplace(futur1, futur2, futur);
    futur = futur1;
    return true;
    break;

  case CPexpr::PTab:
    VERIF_OK_B(pascal_expr_compile(expr->val.uptab.e1, futur1));
    VERIF_OK_B(pascal_expr_compile(expr->val.uptab.e2, futur2));
    pliste_concat3_surplace(futur1, futur2, futur);
    futur = futur1;
    return true;
    break;


  case CPexpr::PRecord:
    VERIF_OK_B(pascal_expr_compile(expr->val.uprecord.e, futur1));
    futur_cell -> str1 = strcopy(expr->val.uprecord.champ);
    pliste_concat2_surplace(futur1, futur);
    futur = futur1;
    return true;
    break;


  case CPexpr::PNot:
    VERIF_OK_B(pascal_expr_compile(expr->val.upnot.e, futur1));
    pliste_concat2_surplace(futur1, futur);
    futur = futur1;
    return true;
    break;

  case CPexpr::PUIPlus:
    VERIF_OK_B(pascal_expr_compile(expr->val.upuiplus.e, futur1));
    pliste_concat2_surplace(futur1, futur);
    futur = futur1;
    return true;
    break;

  case CPexpr::PUIMoins:
    VERIF_OK_B(pascal_expr_compile(expr->val.upuimoins.e, futur1));
    pliste_concat2_surplace(futur1, futur);
    futur = futur1;
    return true;
    break;

  case CPexpr::PURPlus:
    VERIF_OK_B(pascal_expr_compile(expr->val.upurplus.e, futur1));
    pliste_concat2_surplace(futur1, futur);
    futur = futur1;
    return true;
    break;

  case CPexpr::PURMoins:
    VERIF_OK_B(pascal_expr_compile(expr->val.upurmoins.e, futur1));
    pliste_concat2_surplace(futur1, futur);
    futur = futur1;
    return true;
    break;

  case CPexpr::PRef:
    delete futur;
    delete futur_cell;
    VERIF_OK_B(pascal_expr_compile_l(expr->val.upref.e, futur1));
    futur = futur1;
    return true;
    break;

  case CPexpr::PInd:
    VERIF_OK_B(pascal_expr_compile(expr->val.upind.e, futur1));
    pliste_concat2_surplace(futur1, futur);
    futur = futur1;
    return true;
    break;

  case CPexpr::PIdent:
    futur_cell -> str1 = strcopy(expr->val.upident.pident);
    return true;
    break;
       
  case CPexpr::PConst: 
    futur_cell -> pconst = expr->val.upconst.pconst; 
    return true;
    break;

  case CPexpr::PCall: {
    futur_cell -> str1 = strcopy(expr->val.upcall.ident); 

    class pliste<CPexpr> * tempargs = expr -> val.upcall.args;

    futur2 = NULL;
    while (tempargs != NULL) {
      VERIF_OK_B(pascal_expr_compile(tempargs -> a -> val.upind.e, futur1));
      pliste_concat2_surplace(futur1, futur2);
      futur2 = futur1;
      tempargs = tempargs -> suivant;
    }
    pliste_reverse_surplace(futur2);

    pliste_concat2_surplace(futur2, futur);
    futur = futur2;

    return true;
  }
    break;


  case CPexpr::PMenu: {
    futur_cell -> str1 = strcopy(expr->val.upmenu.nom);

    class pliste<struct CPexpr::utype::SPMenu::item> * temp = expr->val.upmenu.pitems;

    int nbitems = temp -> length();
    
    futur_cell -> menu_items_nom = (char * *) malloc((nbitems+1) * ((sizeof (char *))));
    futur_cell -> menu_items_icon = (char * *) malloc((nbitems+1) * ((sizeof (char *))));
    
    int i = 0;
    while (temp != NULL) {
      futur_cell -> menu_items_nom[i] = strcopy(temp->a->message);
      futur_cell -> menu_items_icon[i] = strcopy(temp->a->iconfile);
      i++;
      temp = temp -> suivant;
    }

    futur_cell -> menu_items_nom[i] = NULL;
    futur_cell -> menu_items_icon[i] = NULL;

    return true;
  }
    break;


  case CPexpr::PNomCarte: 
    fprintf(stderr, "Compile: Nom Carte Get\n");
    return true; 
    break;
      
  default: pmesserr("position: %s", expr->position.toString()); pmesserr("Cette opération est inconnue d'une rval."); assert(false); return -9999;
  }

  assert(false);
  return false;
}



bool pascal_expr_compile_l(const CPexpr * expr, pascal_expr_futur_t * &futur) {
  pascal_expr_futur_t * futur1 = NULL;
  pascal_expr_futur_t * futur2 = NULL;
  pascal_expr_futur_cell_t * futur_cell = NULL;
  pascal_expr_futur_cell_t * futur_cell1 = NULL;
  pascal_expr_futur_cell_t * futur_cell2 = NULL;

  futur_cell = new struct pascal_expr_futur_cell_t;
  futur_cell -> type = expr -> type;
  futur = mp(futur_cell, (pliste<pascal_expr_futur_cell_t> *) NULL);

  switch (expr -> type) {
  case CPexpr::PEt:
  case CPexpr::POu:
  case CPexpr::PEqual:
  case CPexpr::PDiff:
  case CPexpr::PInf: 
  case CPexpr::PSup:
  case CPexpr::PInfEq:
  case CPexpr::PSupEq:
  case CPexpr::PIPlus: 
  case CPexpr::PIMoins:
  case CPexpr::PIMult:
  case CPexpr::PIDiv:
  case CPexpr::PIMod:
  case CPexpr::PRPlus:
  case CPexpr::PRMoins:
  case CPexpr::PRMult:
  case CPexpr::PRDiv: 
  case CPexpr::PNot:
  case CPexpr::PUIPlus:
  case CPexpr::PUIMoins:
  case CPexpr::PURPlus:
  case CPexpr::PURMoins:
  case CPexpr::PRef:
  case CPexpr::PInd:
  case CPexpr::PConst: 
  case CPexpr::PCall:
  case CPexpr::PMenu:
  case CPexpr::PNomCarte:
    pmesserr("Cannot get reference of such an expression (need an ident, a record, or a tab).");
    return false;

  case CPexpr::PIdent:
    futur_cell -> type = CPexpr::PIdentRef;
    futur_cell -> str1 = strcopy(expr->val.upident.pident);
    return true;
    break;

  case CPexpr::PTab:
    futur_cell -> type = CPexpr::PTabRef;
    VERIF_OK_B(pascal_expr_compile(expr->val.uptab.e1, futur1));
    VERIF_OK_B(pascal_expr_compile(expr->val.uptab.e2, futur2));
    pliste_concat3_surplace(futur1, futur2, futur);
    futur = futur1;
    return true;
    break;

  case CPexpr::PRecord:
    futur_cell -> type = CPexpr::PRecordRef;
    VERIF_OK_B(pascal_expr_compile(expr->val.uprecord.e, futur1));
    futur_cell -> str1 = strcopy(expr->val.uprecord.champ);
    pliste_concat2_surplace(futur1, futur);
    futur = futur1;
    return true;
    break;

  default: 
    pmesserr("Cette opération est inconnue d'une lval.");
    assert(false); 
    return false;
  }


  assert(false);
  return false;
}




static inline pascal_stack_t * pascal_stack_allouer(void) {
  return (pascal_stack_t *) malloc((sizeof (pascal_stack_t)));
}
pascal_stack_t * pascal_stack_make(void) {
  pascal_stack_t * stack;
  stack = pascal_stack_allouer();
  stack -> nb = 0;
  return stack;
}

void pascal_stack_free(pascal_stack_t * stack) {
  printf("ERREUR: il y a encore %d objets dans la stack PascalML\n", stack -> nb);
  free(stack);
}



void pascal_stack_push(pascal_stack_t * stack, pevalt * e) {
  assert(stack -> nb <= PASCAL_STACK_SIZE);

  stack -> tab[stack -> nb] = e;
  stack -> nb ++;
}


pevalt *  pascal_stack_pop(pascal_stack_t * stack) {
  assert(stack -> nb > 0);

  stack -> nb --;
  return stack -> tab[stack -> nb];
}





bool l_evaluate_futur(const pascal_expr_futur_t * futur, pascal_stack_t * stack, const penv env, pmem mem, const pascal_expr_futur_t * &futur_next) {
  if (futur == NULL)
    return true;

  VERIF_OK_B(l_evaluate_futur_step(futur -> a, stack, env, mem));

  futur_next = futur -> suivant;

  return true;
}


bool l_evaluate_futur_step(const pascal_expr_futur_cell_t * futur_cell, pascal_stack_t * stack, const penv env, pmem mem) {
  int ret;
  pevalt * e, * e1, * e2, * res;
  bool b;
  int min, max;
  pevaltype *evaltype_ptr;
  unsigned int taille;
  ploc where;
  psval sval;
  pdvalt dvalt;
  char *nom;
  class pliste<pevaltype::utype::tpetrecord::champ> *tempchamps;  
  char *tempchar_ptr;


  switch (futur_cell -> type) {
  case CPexpr::PEt:
  case CPexpr::POu:
  case CPexpr::PEqual:
  case CPexpr::PDiff:
  case CPexpr::PInf: 
  case CPexpr::PSup:
  case CPexpr::PInfEq:
  case CPexpr::PSupEq:
  case CPexpr::PIPlus: 
  case CPexpr::PIMoins:
  case CPexpr::PIMult:
  case CPexpr::PIDiv:
  case CPexpr::PIMod:
  case CPexpr::PRPlus:
  case CPexpr::PRMoins:
  case CPexpr::PRMult:
  case CPexpr::PRDiv: 
  case CPexpr::PNot:
  case CPexpr::PUIPlus:
  case CPexpr::PUIMoins:
  case CPexpr::PURPlus:
  case CPexpr::PURMoins:
  case CPexpr::PRef:
  case CPexpr::PInd:
  case CPexpr::PConst: 
  case CPexpr::PCall:
  case CPexpr::PMenu:
  case CPexpr::PNomCarte:
    pmesserr("Cannot get reference of such an expression (need an ident, a record, or a tab).");
    return false;
    
       


  case CPexpr::PIdent: {
    pmessage("L_EVAL: PIdent de la variable...");
    nom = futur_cell -> str1;

    VERIF_OK_B(nom != NULL);
    pmessage("L_EVAL: dont le nom est %s", nom);

    VERIF_OK(penvlookup(env, nom, dvalt));

    res = new pevalt;
    res -> type.type = pevaltype::PETPointer;
    res -> type.val.ptr = new pevaltype;

    if (dvalt.type.type == pdvaltype::PDTRetour)
      {VERIF_OK(pevaltype::pevaltype_of_pdvaltype(*(dvalt.type.val.ret.type), *(res -> type.val.ptr)));}
    else
      {VERIF_OK(pevaltype::pevaltype_of_pdvaltype(dvalt.type, *(res -> type.val.ptr)));}

    switch (dvalt.type.type) {
    case pdvaltype::PDTConstante: pmesserr("L_EVAL: impossible de L_évaluer une constante."); return false; break;
    case pdvaltype::PDTBoolean: res -> val.val.ptr = dvalt.val.val.b; break;
    case pdvaltype::PDTInteger: res -> val.val.ptr = dvalt.val.val.i; break;
    case pdvaltype::PDTSubrange: res -> val.val.ptr = dvalt.val.val.s; break;
    case pdvaltype::PDTReal: res -> val.val.ptr = dvalt.val.val.r; break;
    case pdvaltype::PDTString: res -> val.val.ptr = dvalt.val.val.str; break;
    case pdvaltype::PDTPointer: res -> val.val.ptr = dvalt.val.val.ptr; break;
    case pdvaltype::PDTArray: pmesserr("L_EVAL: impossible de prendre l'adresse d'un tableau."); return false; break;
    case pdvaltype::PDTRecord: pmesserr("L_EVAL: impossible de prendre l'adresse d'un enregistrement."); return false; break;
    case pdvaltype::PDTProcedure: res -> val.val.ptr = dvalt.val.val.proc; break;
    case pdvaltype::PDTFunction: res -> val.val.ptr = dvalt.val.val.func; break;
    case pdvaltype::PDTRetour: res -> val.val.ptr = dvalt.val.val.ret.write; break;
    case pdvaltype::PDTVar: VERIF_OK(pmemread(mem, dvalt.val.val.var, sval)); res -> val.val.ptr = sval.ptr; break;
    default: pmesserr("L_EVAL: Bon ton ident ton je dois prendre l'adresse a un type inconnu."); assert(false); return false;
    }

    
    pascal_stack_push(stack, res);
    
    return true;
  }
    break;




  case CPexpr::PTab: {
    e2 = pascal_stack_pop(stack);
    e1 = pascal_stack_pop(stack);

    VERIF_TYPE2(e1,pevaltype::PETArray);
    
    min = e1 -> type.val.array.indice.min;
    max = e1 -> type.val.array.indice.max;
    evaltype_ptr = e1 -> type.val.array.type;

    switch (evaltype_ptr -> type) {
    case pevaltype::PETBoolean: break;
    case pevaltype::PETInteger: break;
    case pevaltype::PETSubrange: break;
    case pevaltype::PETReal: break;
    case pevaltype::PETString: break;
    case pevaltype::PETPointer: break;
    case pevaltype::PETArray: pmesserr("L_VAL: Impossible de prendre l'adresse d'un tableau."); return false; break;
    case pevaltype::PETRecord: pmesserr("L_VAL: Impossible de prendre l'adresse d'un enregistrement."); return false; break;
    default: pmesserr("L_VAL: Ce tableau est un tableau d'éléments dont le type est inconnu."); assert(false); return false;
    }
      
    taille = pevaltype::pevaltype_sizeof(*(evaltype_ptr));

    int i = 0;
    if (e2 -> type.type == pevaltype::PETInteger)
      i = e2 -> val.val.i;
    else if (e2 -> type.type == pevaltype::PETSubrange)
      i = e2 -> val.val.s;
    else
      assert(false);

    if (not(min <= i && i <= max)) {
      pmesserr("L'indice (%d) est en dehors des limites du tableau (%d et %d).", i, min, max);
      return -185;
    }

    res = new pevalt;
    res -> type.type = pevaltype::PETPointer;
    res -> type.val.ptr = evaltype_ptr;
    where = e1 -> val.val.array + (e2 -> val.val.i - min) * taille;
    res -> val.val.ptr = where;
    pascal_stack_push(stack, res);
    return true;
  }  
    break;



  case CPexpr::PRecord: {
    e = pascal_stack_pop(stack);

    char * champ = futur_cell -> str1;
    
    VERIF_OK_B(champ != NULL);
    VERIF_OK_B(champ[0] != '\0');
    VERIF_OK_B(e -> type.type == pevaltype::PETPointer);
      
    evaltype_ptr = e -> type.val.ptr;
    VERIF_OK_B(evaltype_ptr->type == pevaltype::PETRecord);

    where = e -> val.val.ptr;
    tempchamps = evaltype_ptr -> val.record.champs;

    while (tempchamps != NULL) {
      if (0 == strcmp(tempchamps->a->nom, champ)) {
        res = new pevalt;
        res -> type.type = pevaltype::PETPointer;
        res -> type.val.ptr = tempchamps->a->type;
        res -> val.val.ptr = where;
        return true;
      }
      where += pevaltype::pevaltype_sizeof(*(tempchamps->a->type));
      tempchamps = tempchamps->suivant;
    }
    
    tempchar_ptr = evaltype_ptr -> toString();
    pmesserr("CPexpr::l_evaluate(): PRecord: L'élément de droite \"%s\" n'est pas un champ de l'enregistrement '%s'.", champ, tempchar_ptr);
    delete tempchar_ptr;
    return false;
  }
    break;



  default: 
    pmesserr("Cette opération est inconnue d'une lval.");
    assert(false); 
    return false;
  }





  assert(false);
  return false;
}












bool r_evaluate_futur(const pascal_expr_futur_t * futur, pascal_stack_t * stack, const penv env, pmem mem, const pascal_expr_futur_t * &futur_next) {
  if (futur == NULL)
    return true;

  VERIF_OK_B(r_evaluate_futur_step(futur -> a, stack, env, mem));

  futur_next = futur -> suivant;

  return true;
}







bool r_evaluate_futur_step(const pascal_expr_futur_cell_t * futur_cell, pascal_stack_t * stack, const penv env, pmem mem) {
  int ret;
  pevalt * e, * e1, * e2, * res;
  bool b;
  int min, max;
  pevaltype *evaltype_ptr;
  unsigned int taille;
  ploc where;
  psval sval;
  pdvalt dvalt;
  char *nom;
  class pliste<pevaltype::utype::tpetrecord::champ> *tempchamps;  
  char *tempchar_ptr;


  switch (futur_cell -> type) {
  case CPexpr::PEt:
    e2 = pascal_stack_pop(stack);
    e1 = pascal_stack_pop(stack);

    VERIF_TYPE2(e1,pevaltype::PETBoolean);
    VERIF_TYPE2(e2,pevaltype::PETBoolean);

    res = new pevalt;
    res -> type.type = pevaltype::PETBoolean;
    res -> val.val.b = e1 -> val.val.b && e2 -> val.val.b;

    pascal_stack_push(stack, res);
    return true;
    break;

  case CPexpr::POu:
    e2 = pascal_stack_pop(stack);
    e1 = pascal_stack_pop(stack);

    VERIF_TYPE2(e1,pevaltype::PETBoolean);
    VERIF_TYPE2(e2,pevaltype::PETBoolean);

    res = new pevalt;
    res -> type.type = pevaltype::PETBoolean;
    res -> val.val.b = e1 -> val.val.b || e2 -> val.val.b;

    pascal_stack_push(stack, res);
    return true;
    break;

  case CPexpr::PEqual:
    e2 = pascal_stack_pop(stack);
    e1 = pascal_stack_pop(stack);

    VERIF_TYPE_EQUAL2(e1,e2);

    b = pevalt::equal(e1 -> type, e1 -> val, e2 -> val);

    res = new pevalt;
    res -> type.type = pevaltype::PETBoolean;
    res -> val.val.b = b;

    pascal_stack_push(stack, res);
    return true;
    break;
  
  case CPexpr::PDiff:
    e2 = pascal_stack_pop(stack);
    e1 = pascal_stack_pop(stack);

    VERIF_TYPE_EQUAL2(e1,e2);

    b = pevalt::equal(e1 -> type, e1 -> val, e2 -> val);

    res = new pevalt;
    res -> type.type = pevaltype::PETBoolean;
    res -> val.val.b = not(b);

    pascal_stack_push(stack, res);
    return true;
    break;

  case CPexpr::PInf: {
    e2 = pascal_stack_pop(stack);
    e1 = pascal_stack_pop(stack);

    VERIF_TYPE_EQUAL2(e1,e2);

    switch (e1 -> type.type) {
    case pevaltype::PETBoolean: pmesserr("Hum. Personnellement, il m'est impossible de savoir entre deux booleens lequel est le plus grand."); return false; break;
    case pevaltype::PETInteger: b = e1 -> val.val.i < e2 -> val.val.i; break;
    case pevaltype::PETSubrange: b = e1 -> val.val.s < e2 -> val.val.s; break;
    case pevaltype::PETReal: b = e1 -> val.val.r < e2 -> val.val.r; break;
    case pevaltype::PETString: pmesserr("Bon, reste a savoir ce que tu entends par la comparaison de deux chaines de caracteres..."); return false; break;
    case pevaltype::PETPointer: pmesserr("Euh, la, vraiment, tu te fous de moi! Comparer des pointeurs! N'importe quoi!!!! On est en Pascal ICI!!!!! Pas en C!!!!!"); return false; break;
    case pevaltype::PETArray: pmesserr("Franchement, je me demande ce que peut bien etre la comparaison de deux tableaux."); return false; break;
    case pevaltype::PETRecord: pmesserr("Ecoute la, tu m'enerves! Comment veux-tu comparer deux records!!??? T'es vraiment trop con...."); return false; break;
    default: pmesserr("Lors d'un Inf, evaluation d'un type inconnu."); assert(false); return false;
    }

    res = new pevalt;
    res -> type.type = pevaltype::PETBoolean;
    res -> val.val.b = b;

    pascal_stack_push(stack, res);
    return true;
    break;
  }
    break;

  case CPexpr::PSup:
  case CPexpr::PInfEq:
  case CPexpr::PSupEq:
    assert(false);
    return false;
    break;
    // le code est dans Inf


  case CPexpr::PIPlus: {
    e2 = pascal_stack_pop(stack);
    e1 = pascal_stack_pop(stack);

    VERIF_TYPE_EQUAL2(e1,e2);

    if (e1 -> type.type == pevaltype::PETInteger) { 
      res = new pevalt;
      res -> type.type = pevaltype::PETInteger;
      res -> val.val.i = e1 -> val.val.i + e2 -> val.val.i;
      pascal_stack_push(stack, res);
      return true;
    }

    if (e1 -> type.type == pevaltype::PETSubrange) {
      res = new pevalt;
      res -> type.type = pevaltype::PETSubrange;
      res -> type.val.s.min = e1 -> type.val.s.min;
      res -> type.val.s.max = e1 -> type.val.s.max;
      res -> val.val.s = e1 -> val.val.s + e2 -> val.val.s;
      VERIF_SUBRANGE2(res);
      pascal_stack_push(stack, res);
      return true;
    }
    
    pmesserr("L'opération plus n'est définie que pour les entiers et les intervalles, et en plus quand uniquement les deux elements sont rigoureusement du meme type (type du 1er element : %s ; type du 2eme element : %s).", e1 -> type.toString(), e2 -> type.toString());
    return false;
  
  }
    break;
   
 
  case CPexpr::PIMoins: {
    e2 = pascal_stack_pop(stack);
    e1 = pascal_stack_pop(stack);

    VERIF_TYPE_EQUAL2(e1,e2);

    if (e1 -> type.type == pevaltype::PETInteger) { 
      res = new pevalt;
      res -> type.type = pevaltype::PETInteger;
      res -> val.val.i = e1 -> val.val.i - e2 -> val.val.i;
      pascal_stack_push(stack, res);
      return true;
    }

    if (e1 -> type.type == pevaltype::PETSubrange) {
      res = new pevalt;
      res -> type.type = pevaltype::PETSubrange;
      res -> type.val.s.min = e1 -> type.val.s.min;
      res -> type.val.s.max = e1 -> type.val.s.max;
      res -> val.val.s = e1 -> val.val.s - e2 -> val.val.s;
      VERIF_SUBRANGE2(res);
      pascal_stack_push(stack, res);
      return true;
    }
    
    pmesserr("L'opération moins n'est définie que pour les entiers et les intervalles, et en plus quand uniquement les deux elements sont rigoureusement du meme type (type du 1er element : %s ; type du 2eme element : %s).", e1 -> type.toString(), e2 -> type.toString());
    return false;
  
  }
    break;


  case CPexpr::PIMult: {
    e2 = pascal_stack_pop(stack);
    e1 = pascal_stack_pop(stack);

    VERIF_TYPE_EQUAL2(e1,e2);

    if (e1 -> type.type == pevaltype::PETInteger) { 
      res = new pevalt;
      res -> type.type = pevaltype::PETInteger;
      res -> val.val.i = e1 -> val.val.i * e2 -> val.val.i;
      pascal_stack_push(stack, res);
      return true;
    }

    if (e1 -> type.type == pevaltype::PETSubrange) {
      res = new pevalt;
      res -> type.type = pevaltype::PETSubrange;
      res -> type.val.s.min = e1 -> type.val.s.min;
      res -> type.val.s.max = e1 -> type.val.s.max;
      res -> val.val.s = e1 -> val.val.s * e2 -> val.val.s;
      VERIF_SUBRANGE2(res);
      pascal_stack_push(stack, res);
      return true;
    }
    
    pmesserr("L'opération mult n'est définie que pour les entiers et les intervalles, et en plus quand uniquement les deux elements sont rigoureusement du meme type (type du 1er element : %s ; type du 2eme element : %s).", e1 -> type.toString(), e2 -> type.toString());
    return false;
  
  }
    break;

    
  case CPexpr::PIDiv: {
    e2 = pascal_stack_pop(stack);
    e1 = pascal_stack_pop(stack);

    VERIF_TYPE_EQUAL2(e1,e2);

    if (e1 -> type.type == pevaltype::PETInteger) { 
      res = new pevalt;
      res -> type.type = pevaltype::PETInteger;
      res -> val.val.i = e1 -> val.val.i / e2 -> val.val.i;
      pascal_stack_push(stack, res);
      return true;
    }

    if (e1 -> type.type == pevaltype::PETSubrange) {
      res = new pevalt;
      res -> type.type = pevaltype::PETSubrange;
      res -> type.val.s.min = e1 -> type.val.s.min;
      res -> type.val.s.max = e1 -> type.val.s.max;
      res -> val.val.s = e1 -> val.val.s / e2 -> val.val.s;
      VERIF_SUBRANGE2(res);
      pascal_stack_push(stack, res);
      return true;
    }
    
    pmesserr("L'opération div n'est définie que pour les entiers et les intervalles, et en plus quand uniquement les deux elements sont rigoureusement du meme type (type du 1er element : %s ; type du 2eme element : %s).", e1 -> type.toString(), e2 -> type.toString());
    return false;
  
  }
    break;

 
  case CPexpr::PIMod: {
    e2 = pascal_stack_pop(stack);
    e1 = pascal_stack_pop(stack);

    int a, b;

    if (e1 -> type.type == pevaltype::PETInteger) {
      a = e1 -> val.val.i;
    }
    else if (e1 -> type.type == pevaltype::PETSubrange) {
      a = e1 -> val.val.s;
    }
    else {
      pmesserr("e1 n'est pas un scalaire entier mais de type %s.", e1 -> type.toString());
      return false;
    }

    
    if (e2 -> type.type == pevaltype::PETInteger) {
      b = e2 -> val.val.i;
    }
    else if (e2 -> type.type == pevaltype::PETSubrange) {
      b = e2 -> val.val.s;
    }
    else {
      pmesserr("e2 n'est pas un scalaire entier mais de type %s.", e2 -> type.toString());
      return false;
    }

    res = new pevalt;
    res -> type.type = pevaltype::PETInteger;
    res -> val.val.i = a % b;
    pascal_stack_push(stack, res);
    return true;
  }
    break;

    
  case CPexpr::PRPlus:
    e2 = pascal_stack_pop(stack);
    e1 = pascal_stack_pop(stack);

    VERIF_TYPE_EQUAL2(e1,e2);
    VERIF_TYPE2(e1,pevaltype::PETReal);

    res = new pevalt;
    res -> type.type = pevaltype::PETReal;
    res -> val.val.r = e1 -> val.val.r + e2 -> val.val.r;
    pascal_stack_push(stack, res);
    return true;
    break;
    
  case CPexpr::PRMoins:
    e2 = pascal_stack_pop(stack);
    e1 = pascal_stack_pop(stack);

    VERIF_TYPE_EQUAL2(e1,e2);
    VERIF_TYPE2(e1,pevaltype::PETReal);

    res = new pevalt;
    res -> type.type = pevaltype::PETReal;
    res -> val.val.r = e1 -> val.val.r - e2 -> val.val.r;
    pascal_stack_push(stack, res);
    return true;
    break;
    
  case CPexpr::PRMult:
    e2 = pascal_stack_pop(stack);
    e1 = pascal_stack_pop(stack);

    VERIF_TYPE_EQUAL2(e1,e2);
    VERIF_TYPE2(e1,pevaltype::PETReal);

    res = new pevalt;
    res -> type.type = pevaltype::PETReal;
    res -> val.val.r = e1 -> val.val.r * e2 -> val.val.r;
    pascal_stack_push(stack, res);
    return true;
    break;
    

  case CPexpr::PRDiv: 
    e2 = pascal_stack_pop(stack);
    e1 = pascal_stack_pop(stack);

    VERIF_TYPE_EQUAL2(e1,e2);
    VERIF_TYPE2(e1,pevaltype::PETReal);

    res = new pevalt;
    res -> type.type = pevaltype::PETReal;
    res -> val.val.r = e1 -> val.val.r / e2 -> val.val.r;
    pascal_stack_push(stack, res);
    return true;
    break;
    


  case CPexpr::PTab:
  case CPexpr::PTabRef: {
    e2 = pascal_stack_pop(stack);
    e1 = pascal_stack_pop(stack);

    VERIF_TYPE2(e1,pevaltype::PETArray);
    
    min = e1 -> type.val.array.indice.min;
    max = e1 -> type.val.array.indice.max;
    evaltype_ptr = e1 -> type.val.array.type;

    switch (evaltype_ptr -> type) {
    case pevaltype::PETBoolean: break;
    case pevaltype::PETInteger: break;
    case pevaltype::PETSubrange: break;
    case pevaltype::PETReal: break;
    case pevaltype::PETString: break;
    case pevaltype::PETPointer: break;
    case pevaltype::PETArray: pmesserr("L_VAL: Impossible de prendre l'adresse d'un tableau."); return false; break;
    case pevaltype::PETRecord: pmesserr("L_VAL: Impossible de prendre l'adresse d'un enregistrement."); return false; break;
    default: pmesserr("L_VAL: Ce tableau est un tableau d'éléments dont le type est inconnu."); assert(false); return false;
    }
      
    taille = pevaltype::pevaltype_sizeof(*(evaltype_ptr));

    int i = 0;
    if (e2 -> type.type == pevaltype::PETInteger)
      i = e2 -> val.val.i;
    else if (e2 -> type.type == pevaltype::PETSubrange)
      i = e2 -> val.val.s;
    else
      assert(false);

    if (not(min <= i && i <= max)) {
      pmesserr("L'indice (%d) est en dehors des limites du tableau (%d et %d).", i, min, max);
      return -185;
    }

    where = e1 -> val.val.array + (i - min) * taille;

    if (futur_cell -> type == CPexpr::PTabRef) {
      res = new pevalt;
      res -> type.type = pevaltype::PETPointer;
      res -> type.val.ptr = evaltype_ptr;
      res -> val.val.ptr = where;
    }
    else {
      res = new pevalt;
      res -> type = *(evaltype_ptr);
      VERIF_OK(pmemread(mem, where, sval));
      res -> fromPSVal(sval);
    }
    
    pascal_stack_push(stack, res);

    return true;
  }  
    break;

  case CPexpr::PRecord: {
    e = pascal_stack_pop(stack);
    
    if (futur_cell -> str1 == NULL) {
      pmesserr("PRecord: champ est nul.");
      return false;
    }

    if (futur_cell -> str1[0] == '\0') {
      pmesserr("PRecord: champ est vide.");
      return false;
    }

    if (e -> type.type != pevaltype::PETPointer) {
      pmesserr("PRecord: erreur interne. L'élément de gauche n'est pas un POINTEUR après l-évaluation.");
      return false;
    }
    
    evaltype_ptr = e -> type.val.ptr;
    if (evaltype_ptr->type != pevaltype::PETRecord) {
      pmesserr("PRecord: L'élément de gauche n'est pas un RECORD.");
      return false;
    }
    
    
    where = e -> val.val.ptr;
    tempchamps = evaltype_ptr -> val.record.champs;
    while (tempchamps != NULL) {
      if (0 == strcmp(tempchamps->a->nom, futur_cell -> str1)) {
        res = new pevalt;
        res -> type = *(evaltype_ptr);
        VERIF_OK(pmemread(mem, where, sval));
        res -> fromPSVal(sval);
        pascal_stack_push(stack, res);
        return true;
      }
      where += pevaltype::pevaltype_sizeof(*(tempchamps->a->type));
      tempchamps = tempchamps->suivant;
    }
    
    tempchar_ptr = evaltype_ptr -> toString();
    pmesserr("PRecord: L'élément de droite \"%s\" n'est pas un champ de l'enregistrement '%s'.", futur_cell -> str1, tempchar_ptr);
    delete tempchar_ptr;
    return false;
  }
    break;


  case CPexpr::PNot:
    e = pascal_stack_pop(stack);

    VERIF_TYPE2(e,pevaltype::PETBoolean);

    res = new pevalt;
    res -> type.type = pevaltype::PETBoolean;
    res -> val.val.b = not(e -> val.val.b);
    pascal_stack_push(stack, res);
    return true;
    break;

  case CPexpr::PUIPlus:
    e = pascal_stack_pop(stack);

    switch (e -> type.type) {
    case pevaltype::PETInteger:
    case pevaltype::PETSubrange:
    case pevaltype::PETString: break;
    case pevaltype::PETBoolean:
    case pevaltype::PETReal:
    case pevaltype::PETPointer:
    case pevaltype::PETArray:
    case pevaltype::PETRecord:
    default: pmesserr("Impossible de calculer le + unaire d'un tel objet."); return false;
    }
    res = e;
    pascal_stack_push(stack, res);
    break;

  case CPexpr::PUIMoins:
    e = pascal_stack_pop(stack);

    res = e;
    switch (e -> type.type) {
    case pevaltype::PETInteger: res -> val.val.i = - e -> val.val.i; pascal_stack_push(stack, res); return true; break;
    case pevaltype::PETSubrange: res -> val.val.s = - e -> val.val.s; VERIF_SUBRANGE2(res); pascal_stack_push(stack, res); return true; break;
    case pevaltype::PETBoolean:
    case pevaltype::PETReal:
    case pevaltype::PETString:
    case pevaltype::PETPointer:
    case pevaltype::PETArray:
    case pevaltype::PETRecord:
    default: pmesserr("Impossible de calculer le - unaire d'un tel objet."); return false;
    }

    assert(false);
    return false;
    break;

  case CPexpr::PURPlus:
    e = pascal_stack_pop(stack);

    switch (e -> type.type) {
    case pevaltype::PETReal: break;
    case pevaltype::PETInteger:
    case pevaltype::PETSubrange:
    case pevaltype::PETBoolean:
    case pevaltype::PETString:
    case pevaltype::PETPointer:
    case pevaltype::PETArray:
    case pevaltype::PETRecord:
    default: pmesserr("Impossible de calculer le + unaire réel d'un tel objet."); return false;
    }

    res = e;
    pascal_stack_push(stack, res);
    return true;
    break;

  case CPexpr::PURMoins:
    e = pascal_stack_pop(stack);

    res = e;
    switch (e -> type.type) {
    case pevaltype::PETReal: res -> val.val.r = - e -> val.val.r; pascal_stack_push(stack, res); return true; break;
    case pevaltype::PETInteger:
    case pevaltype::PETSubrange:
    case pevaltype::PETBoolean:
    case pevaltype::PETString:
    case pevaltype::PETPointer:
    case pevaltype::PETArray:
    case pevaltype::PETRecord:
    default: pmesserr("Impossible de calculer le moins unaire réel d'un tel objet."); return false;
    }

    assert(false);
    return false;
    break;

  case CPexpr::PRef:
    assert(false);
    return false;
    break;
      
  case CPexpr::PInd:
    e = pascal_stack_pop(stack);

    VERIF_TYPE2(e,pevaltype::PETPointer);

    res = new pevalt;
    res -> type = *(e -> type.val.ptr);
    VERIF_OK(pmemread(mem, e -> val.val.ptr, sval));
    res -> fromPSVal(sval);
    pascal_stack_push(stack, res);
    return true;
    break;

  case CPexpr::PIdent:
    nom = futur_cell -> str1;
    VERIF_OK_B(nom != NULL);

    VERIF_OK(penvlookup(env, nom, dvalt));

    res = new pevalt;
    VERIF_OK(res -> r_fromPDValt(mem, dvalt));
    pascal_stack_push(stack, res);
    return true;
    break;

  case CPexpr::PIdentRef: {
    nom = futur_cell -> str1;

    //fprintf(stderr, "PIdentRef: %s\n", nom);

    VERIF_OK_B(nom != NULL);

    VERIF_OK(penvlookup(env, nom, dvalt));

    res = new pevalt;
    VERIF_OK(res -> l_fromPDValt(mem, dvalt));
    pascal_stack_push(stack, res);
    
    return true;
  }
    break;

       
  case CPexpr::PConst: 
    res = new pevalt(futur_cell -> pconst);
    pascal_stack_push(stack, res);
    return true; 
    break;

  case CPexpr::PCall: {
    pmessage("Appel expression avec nom = %s", futur_cell -> str1);
    
    VERIF_OK(penvlookup(env, futur_cell -> str1, dvalt));

    if (not(dvalt.type.type == pdvaltype::PDTRetour || dvalt.type.type == pdvaltype::PDTFunction)) {
      pmesserr("PCall: la variable %s n'est pas une fonction mais elle est de type %s..", futur_cell -> str1, dvalt.type.toString());
      return false;
    }

    class pliste<struct pdvaltype::tpdtprocedure::param> * tempparams;
    penv tempenv;
    pdvalt tempdvalt, retdvalt;
    ploc i;


    if (dvalt.type.type == pdvaltype::PDTRetour) {
      tempparams = dvalt.type.val.ret.params;
      tempenv = dvalt.type.val.ret.env;
      taille = dvalt.type.val.ret.type->pdvaltype_sizeof();
    }
    else {
      tempparams = dvalt.type.val.func.params;
      tempenv = dvalt.type.val.func.env;
      taille = dvalt.type.val.func.type->pdvaltype_sizeof();
    }

    int nb_params = tempparams -> length();
    assert(stack -> nb >= nb_params);
      
    // Allocation de la valeur de retour.
    VERIF_OK(pnew(mem, taille, mem, i));
    retdvalt.type.type = pdvaltype::PDTRetour;
    if (dvalt.type.type == pdvaltype::PDTRetour) {
      retdvalt.type.val.ret = dvalt.type.val.ret;
      retdvalt.val.val.ret.read = dvalt.val.val.ret.read;
    }
    else {
      retdvalt.type.val.ret = dvalt.type.val.func;
      retdvalt.val.val.ret.read = dvalt.val.val.func;
    }    
    retdvalt.val.val.ret.write = i;
    VERIF_OK(penvupdate(tempenv, futur_cell -> str1, retdvalt, tempenv));

    // Now les args.
    for (int ii = 0; ii < nb_params; ii++) {
      e = stack -> tab[stack -> nb - (nb_params - ii)];

      taille = tempparams->a->dvaltype_ptr->pdvaltype_sizeof();
      VERIF_OK(pnew(mem, taille, mem, i));
      VERIF_OK(e -> toPSVal(sval));
      VERIF_OK(pmemwrite(mem, i, sval));
      VERIF_OK(pdvalt::pdvalt_of_pdvaltype(*(tempparams->a->dvaltype_ptr), i, tempdvalt));
      VERIF_OK(penvupdate(tempenv, tempparams->a->nom, tempdvalt, tempenv));

      tempparams = tempparams->suivant;
    }


    if (dvalt.type.type == pdvaltype::PDTRetour)
      dvalt . type . val . ret . corps -> execute ( tempenv , mem ) ;
    else
      dvalt . type . val . func . corps -> execute ( tempenv , mem ) ;
      

    res = new pevalt;
    VERIF_OK(res -> r_fromPDValt(mem, retdvalt));
    pascal_stack_push(stack, res);
    pmessage("Fin Call expression de %s", futur_cell -> str1);
    return true;
  }  
    break;


  case CPexpr::PMenu: {
    pmessage("Debut du traitement d'un menu.");
   
    const char * nom = futur_cell -> str1;
    if (nom == NULL) {
      pmesserr("Ce menu a un nom dont le pointeur est NULL.");
    }

    pmessage("Nom du menu: '%s'", nom);

    char * * p = futur_cell -> menu_items_nom;
    char * * q = futur_cell -> menu_items_icon;

    SCRIPT_BeginAfficherMenu();
    while (*p != NULL) {
      MiniMenu -> Add(0, *p, *q);
      p++;
      q++;
    }

    // on a setté le tick correctement (script en mode pause donc, en attente du résultat :-)
    // il va y avoir des passes de boucle tant que choix pas fait
    // quand choix fait, le résultat devrait être pushé sur la stack puis le tick être remis en mode normal et l'exécution du script peut reprendre
    // (le script possède un état… :-p)
#if 0
    res = new pevalt;
    res -> type.type = pevaltype::PETInteger;
    res -> val.val.i = SCRIPT_AfficherMenu(nom);
    pascal_stack_push(stack, res);
    pmessage("Fin du traitement du menu '%s' ; valeur de retour = %d.", nom, res -> val.val.i);
#endif
    pmessage("Fin du traitement du menu '%s'.", nom);
    return true;
  }
    break;

  case CPexpr::PNomCarte: {
    fprintf(stderr, "NOM CARTE GET\n");
    pmessage("exécution de l'instruction PNomCarte.");
    const char * nom_carte = SCRIPT_GetNomCarte();
    fprintf(stderr, "NOM CARTE GET = %s nom_carte\n", nom_carte);

    res = new pevalt;
    res -> type.type = pevaltype::PETString;
    res -> val.val.str = strcopy(nom_carte);
    pascal_stack_push(stack, res);
    return true;
  }
    break;
    
    
  default: 
    pmesserr("Cette opération est inconnue d'une rval."); 
    assert(false); 
    return false;
  }

  assert(false);
  return false;
}










