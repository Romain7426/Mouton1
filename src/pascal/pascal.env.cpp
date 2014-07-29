#include "global.hpp"
#include "pascal/pascal.tools.hpp"
#include "pascal/pascal.mem.hpp"
#include "pascal/pascal.env.hpp"
#include "pascal/pascal.expr.hpp"
#include "pascal/pascal.prog.hpp"



pdval * pdval::copy(bool iscstr) const {
  pdval *temp;
  
  temp = new pdval;
  
  if (iscstr) {
    if (val.c.str == NULL) {
      temp -> val.c.str = NULL;
    }
    else {
      temp -> val.c.str = strcpy(new char[strlen(val.c.str)+1], val.c.str);
    }
  }
  else {
    //*temp = *this;
    temp -> val.c.str = strcpy(new char[strlen(this -> val.c.str) + 1], this -> val.c.str);
  }

  return temp;
}




#define NULLCOPY(a) (((a) == NULL) ? NULL : (a) -> copy())
pdvaltype * pdvaltype::copy(void) const {
  pdvaltype * temp;

  temp = new pdvaltype;
  
  pmessage("pdvaltype::copy");
  fflush(NULL);
  *temp = *this;
  //{PDTDummy, PDTConstante, PDTBoolean, PDTInteger, PDTSubrange, PDTReal, PDTString, PDTPointer, PDTArray, PDTRecord, PDTProcedure, PDTFunction, PDTRetour}
  switch (type) {
  case PDTConstante: break;
  case PDTBoolean: break;
  case PDTInteger: break;
  case PDTSubrange: break;
  case PDTReal: break;
  case PDTString: break;
  case PDTPointer: temp -> val.ptr = NULLCOPY(val.ptr); break;
  case PDTArray: temp -> val.array.type = NULLCOPY(val.array.type); break;
  case PDTRecord: temp -> val.record.champs = NULLCOPY(val.record.champs); break;
  case PDTProcedure: temp -> val.proc.params = NULLCOPY(val.proc.params); break;
  case PDTFunction: temp -> val.func.params = NULLCOPY(val.func.params); temp -> val.func.type = NULLCOPY(val.func.type); break;
  case PDTRetour: temp -> val.func.params = NULLCOPY(val.func.params); temp -> val.func.type = NULLCOPY(val.func.type); break;//temp -> val.ret = NULLCOPY(val.ret); break;
  case PDTUser: temp -> val.user = strcopy(val.user); break;
  case PDTDummy: assert(false); break;
  case PDTVar: assert(false); break;
  default:
    pmesserr("pdvaltype::copy(): impossible de copier un élément dont le type est inconnu.");
    // --1-- delete temp;
    return NULL;
  }

  return temp;
}






char * pdvaltype::toString(void) const {
  char * a, * b, * c, * d, * e, * f, * g;
  const char * aa, * bb, * cc, * dd, * ee, * ff, * gg, * hh, * ii, * jj, * kk, * ll, * mm;
  class pliste<struct pascal_dval_type::tpdtrecord::champ> *tempchamps;
  class pliste<struct pascal_dval_type::tpdtprocedure::param> *tempparams;

  switch (type) {
  case PDTConstante: {
    switch (val.c) {
    case PCTBoolean: return strcopy("Constante Booléenne."); break;
    case PCTInteger: return strcopy("Constante Entière."); break;
    case PCTReal: return strcopy("Constante Réelle."); break;
    case PCTString: return strcopy("Constante Chaîne."); break;
    case PCTDummyConstante: assert(false); return NULL; break;
    default: pmesserr("pdvaltype::toString: type constante inconnue."); assert(false); return NULL;
    }
    assert(false); 
    return NULL;
  }
    break;

  case PDTBoolean: return strcopy("Booléen"); break;
  case PDTInteger: return strcopy("Entier"); break;
  case PDTSubrange:
    pmessage("pdvaltype::toString: PDTSubrange");
    aa = ("Subrange "); 
    b = val.s.mine == NULL ? itoa(val.s.min) : (val.s.mine -> toString());
    cc = "..";
    d = val.s.maxe == NULL ? itoa(val.s.max) : (val.s.maxe -> toString());
    e = STRCAT4_(aa,b,cc,d);
    // --1-- delete [] b;
    // --1-- delete [] d;
    return e;
    break;

  case PDTReal: return strcopy("Réel"); break;
  case PDTString: return strcopy("Chaîne"); break;
  case PDTPointer:
    aa = "Pointeur vers ";
    b = val.ptr -> toString();
    c = STRCAT2_(aa,b);
    // --1-- delete [] b;
    return c;
    break;

  case PDTArray:
    aa = "Tableau [";
    b = val.array.indice.mine == NULL ? itoa(val.array.indice.min) : val.array.indice.mine -> toString();
    cc = "..";
    d = val.array.indice.maxe == NULL ? itoa(val.array.indice.max) : val.array.indice.maxe -> toString();
    ee = "] de ";
    f = val.array.type -> toString();
    g = STRCAT6_(aa,b,cc,d,ee,f);
    // --1-- delete [] b;
    // --1-- delete [] d;
    // --1-- delete [] f;
    return g;
    break;

  case PDTRecord:
    a = strcopy("enregistrement { ");
    tempchamps = val.record.champs;
    while (tempchamps != NULL) {
      if (tempchamps -> a == NULL) {
        pmesserr("pdvaltype::toString: record: NULL pointer on a ' -> a'.");
        bb = " Erreur ; } ; ";
        c = STRCAT2_(a,bb);
        // --1-- delete [] a;
        return c;
      }

      if (tempchamps -> a -> nom == NULL) {
        pmesserr("pdvaltype::toString: record : NULL pointer on a ' -> a -> nom'.");
        bb = " Erreur ; ) ; ";
        c = STRCAT2_(a,bb);
        // --1-- delete [] a;
        return c;
      }

      if (tempchamps -> a -> type == NULL) {
        pmesserr("pdvaltype::toString: record : NULL pointer on a ' -> a -> type'.");
        bb = " Erreur ; ) ; ";
        c = STRCAT2_(a,bb);
        // --1-- delete [] a;
        return c;
      }

      bb = tempchamps -> a -> nom;
      cc = " : ";
      d = tempchamps -> a -> type -> toString();
      ee = " ; ";
      f = STRCAT5_(a,bb,cc,d,ee);
      // --1-- delete [] a;
      // --1-- delete [] d;
      a = f;
      tempchamps = tempchamps -> suivant;
    }
    bb = " } ";
    c = STRCAT2_(a,bb);
    // --1-- delete [] a;
    return c;
    break;

  case PDTProcedure:
    a = strcopy("Procedure (");
    tempparams = val.proc.params;
    while (tempparams != NULL) {
      if (tempparams -> a == NULL) {
        pmesserr("pdvaltype::toString: procedure : NULL pointer on a ' -> a'.");
        bb  = " ; Erreur ) ; ";
        c = STRCAT2_(a,bb);
        // --1-- delete [] a;
        return c;
      }

      if (tempparams -> a -> var) {
        b = STRCAT2_(a," var ");
        // --1-- delete [] a;
        a = b;
      }

      b = tempparams -> a -> nom;
      cc = " : ";
      d = tempparams -> a -> dvaltype_ptr -> toString();
      ee = " ; ";
      f = STRCAT5_(a,b,cc,d,ee);
      // --1-- delete [] a;
      // --1-- delete [] d;
      a = f;
      tempparams = tempparams -> suivant;
    }

    bb = " ) ";
    c = val.proc.corps -> toString();
    d = STRCAT3_(a,bb,c);
    // --1-- delete [] a;
    // --1-- delete [] c;
    return d;
    break;

  case PDTFunction:
    a = strcopy("Fonction (");
    tempparams = val.proc.params;
    while (tempparams != NULL) {
      if (tempparams -> a == NULL) {
        pmesserr("pdvaltype::toString: function : NULL pointer on a ' -> a'.");
        bb = " Erreur ; ";
        c = STRCAT2_(a,bb);
        // --1-- delete [] a;
        a = c;
        break;
      }

      if (tempparams -> a -> var) {
        b = STRCAT2_(a," var ");
        // --1-- delete [] a;
        a = b;
      }

      b = tempparams -> a -> nom;
      cc = " : ";
      d = tempparams -> a -> dvaltype_ptr -> toString();
      ee = " ; ";
      f = STRCAT5_(a,b,cc,d,ee);
      // --1-- delete [] a;
      // --1-- delete [] d;
      a = f;
      tempparams = tempparams -> suivant;
    }

    if (val.func.type == NULL) {
      pmesserr("pdvaltype::toString: function : NULL pointer on a '.func.type'.");
      bb = " Erreur ; ";
      STRCAT2(a,bb,c);
      // --1-- delete [] a;
      return c;
    }
    bb = " ) : ";
    c = val.func.type -> toString();
    dd = " ; ";
    e =  val.func.corps -> toString();
    f = STRCAT5_(a,bb,c,dd,e);
    // --1-- delete [] a;
    // --1-- delete [] c;
    // --1-- delete [] e;
    return f;
    break;

  case PDTRetour:
    aa = "Retour de Fonction : ";
    if (val.ret.type == NULL) {
      pmesserr("pdvaltype::toString: function : NULL pointer on a '.ret'.");
      bb = " Erreur ; ";
      c = STRCAT2_(aa,bb);
      return c;
    }

    b = val.ret.type -> toString();
    c = STRCAT2_(a,b);
    // --1-- delete [] b;
    return c;
    break;

  case PDTVar: return val.var -> toString(); break;
  case PDTUser: return strcopy(val.user); break;
  case PDTDummy: assert(false); return NULL; break;
  default: pmesserr("pdvaltype::toString(): impossible de toStringer un élément dont le type est inconnu."); assert(false); return NULL;
  }
  
  assert(false); 
  return NULL;
}






const ptabdvaltypeuser tabdvaltypeuser0 = NULL;
ptabdvaltypeuser tabdvaltypeuser = tabdvaltypeuser0;


int ptabdvaltypeuser_lookup(const ptabdvaltypeuser tabdvaltypeuser, const char *ident, struct pascal_dval_type &dvaltype) {
  ptabdvaltypeuser temp;
  
  if (ident == NULL) return -1;
  if (ident[0] == '\0') return -2;
  temp = tabdvaltypeuser;
  while (temp != NULL) {
    if (strcmp(temp -> a -> nom, ident) == 0) {
      dvaltype = temp -> a -> dvaltype;
      return 0;
    }
    temp = temp -> suivant;
  }
  return -3;
}


void ptabdvaltypeuser_del(ptabdvaltypeuser &tabdvaltypeuser) {
  ptabdvaltypeuser temp, tamp;
  
  temp = tabdvaltypeuser;
  while (temp != NULL) {
    tamp = temp -> suivant;

    // --1-- delete [] temp -> a -> nom;
    temp -> a -> dvaltype.pdvaltype::del_pascal_dval_type();
    // --1-- delete temp -> a;
    // --1-- delete temp;

    temp = tamp;
  }

  tabdvaltypeuser = tabdvaltypeuser0;
}
  
























int pdvalt::pdvalt_of_pdvaltype(const struct pascal_dval_type dvaltype, const ploc i, struct pascal_dvalt &dvalt) {
  int ret;
  pdvaltype tempdvaltype;
  dvalt.type = *(dvaltype.copy());

  pmessage("THERE");
  fflush(NULL);

  switch (dvaltype.type) {
  case pdvaltype::PDTConstante:
    pmesserr("pdvalt::pdvalt_of_pdvaltype(): PDTConstante :  ce cas est impossible.");
    return -11;
    break;
  case pdvaltype::PDTBoolean:
    dvalt.val.val.b = i;
    return 0;
    break;
  case pdvaltype::PDTInteger:
    dvalt.val.val.i = i;
    return 0;
    break;
  case pdvaltype::PDTSubrange:
    dvalt.val.val.s = i;
    return 0;
    break;
  case pdvaltype::PDTReal:
    dvalt.val.val.r = i;
    return 0;
    break;
  case pdvaltype::PDTString:
    dvalt.val.val.str = i;
    return 0;
    break;
  case pdvaltype::PDTPointer:
    dvalt.val.val.ptr = i;
    return 0;
    break;
  case pdvaltype::PDTArray:
    dvalt.val.val.array = i;
    return 0;
    break;
  case pdvaltype::PDTRecord:
    dvalt.val.val.record = i;
    return 0;
    break;
  case pdvaltype::PDTProcedure:
    dvalt.val.val.proc = i;
    return 0;
    break;
  case pdvaltype::PDTFunction:
    dvalt.val.val.func = i;
    return 0;
    break;
  case pdvaltype::PDTRetour:
    dvalt.val.val.ret.write = i;
    // read doit se faire ailleurs, par exemple à la déclaration de la variable (ou fonction plutot).
    //pmesserr("pdvalt::pdvalt_of_pdvaltype(): PDTRetour :  ce cas est impossible.");
    //return -121;
    return 0;
    break;
  case pdvaltype::PDTUser:
    ret = ptabdvaltypeuser_lookup(tabdvaltypeuser, dvaltype.val.user, tempdvaltype);
    if (ret != 0) {
      pmesserr("pdvalt::pdvalt_of_pdvaltype(): PDTUser: impossible de trouver le type %s dans l'environnement.", dvaltype.val.user);
      return ret;
    }
    return pdvalt::pdvalt_of_pdvaltype(tempdvaltype, i, dvalt);
    break;
  case pdvaltype::PDTDummy: assert(false); return -1; break;
  case pdvaltype::PDTVar: assert(false); return -1; break;
  default:
    pmesserr("pdvalt::pdvalt_of_pdvaltype(): type inconnu.");
    return -9999;
  }

  //pmesserr("pdvalt::pdvalt_of_pdvaltype(): on ne devrait pas être là.");
  return -1;
}





// Fonction qui donne le nombre de case mémoire qu'utilise ce type.
unsigned int pdvaltype::pdvaltype_sizeof(void) {
  int ret;
  pdvaltype tempdvaltype;
  unsigned int taille;
  class pliste<struct pascal_dval_type::tpdtrecord::champ> *tempchamps;

  switch (type) {
  case PDTConstante: return 0; break;
  case PDTBoolean: return 1; break;
  case PDTInteger: return 1; break;
  case PDTSubrange: return 1; break;
  case PDTReal: return 1; break;
  case PDTString: return 1; break;
  case PDTPointer: return 1; break;
  case PDTArray: return ((val.array.indice.max - val.array.indice.min + 1) * val.array.type -> pdvaltype_sizeof());
  case PDTRecord:
    taille = 0;
    tempchamps = val.record.champs;
    while (tempchamps != NULL) {
      if (tempchamps -> a == NULL) {
        pmesserr("pdvaltype::pdvaltype_sizeof: PDTRecord : null pointer on ' -> a'.");
      }
      else if (tempchamps -> a -> type == NULL) {
        pmesserr("pdvaltype::pdvaltype_sizeof: PDTRecord : null pointer on ' -> a -> type'.");
      }
      else {
        taille += tempchamps -> a -> type -> pdvaltype_sizeof();
      }
      tempchamps = tempchamps -> suivant;
    }
    return taille;
    break;
  case PDTProcedure: return 1; break;
  case PDTFunction: return 1; break;
  case PDTRetour: 
    pmesserr("pdvaltype::pdvaltype_sizeof: PDTRetour : non applicable ; rend 1 quand meme.");
    return 1;
    break;
  case PDTUser:
    ret = ptabdvaltypeuser_lookup(tabdvaltypeuser, this -> val.user, tempdvaltype);
    if (ret != 0) {
      pmesserr("pdvalt::pdvalt_sizeof(): PDTUser: impossible de trouver le type %s dans l'environnement.", this -> val.user);
      return 0;
    }
    //pmessage(tempdvaltype.toString());
    return tempdvaltype.pdvaltype_sizeof();
    break;
  case PDTDummy: assert(false); return 0; break;
  case PDTVar: assert(false); return 0; break;
  default:
    pmesserr("pdvaltype::pdvaltype_sizeof: type inconnu : rend 0.");
    return 0;
  }

  //pmesserr("pdvaltype::pdvaltype_sizeof: on ne devrait pas être ici : rend 0.");
  return 0;
}
 





// Pas de constructeur, donc pas de destructeur.
// On ne détruit que les objets que l'on construit.
int pdvaltype::del_pascal_dval_type(void) {
  switch (type) {
  case PDTConstante:
  case PDTBoolean:
  case PDTInteger:
  case PDTSubrange:
  case PDTReal:
  case PDTString:
    break;
  case PDTPointer:
    // --1-- delete val.ptr;
    break;
  case PDTArray:
    // --1-- delete val.array.type;
    break;
  case PDTRecord:
    {
      pliste<pascal_dval_type::tpdtrecord::champ> *temp, *tamp;
      
      temp = val.record.champs;
      while (temp != NULL) {
        tamp = temp -> suivant;
        // --1-- delete temp -> a -> nom;
        // --1-- delete temp -> a -> type;
        // --1-- delete temp -> a;
        // --1-- delete temp;
        temp = tamp;
      }
    }
    break;
  case PDTProcedure:
    {
      class pliste<struct pascal_dval_type::tpdtprocedure::param> *temp, *tamp;
      
      temp = val.proc.params;
      while (temp != NULL) {
        tamp = temp -> suivant;
        // --1-- delete temp -> a;
        // --1-- delete temp;
        temp = tamp;
      }
    }
    break;
  case PDTFunction:
    {
      class pliste<struct pascal_dval_type::tpdtprocedure::param> *temp, *tamp;
      
      temp = val.func.params;
      while (temp != NULL) {
        tamp = temp -> suivant;
        // --1-- delete temp -> a;
        // --1-- delete temp;
        temp = tamp;
      }
    }
    // --1-- delete val.func.type;
    break;
  case PDTRetour: {
    class pliste<struct pascal_dval_type::tpdtprocedure::param> *temp, *tamp;
    
    temp = val.ret.params;
    while (temp != NULL) {
      tamp = temp -> suivant;
      // --1-- delete temp -> a;
      // --1-- delete temp;
      temp = tamp;
    }
  }
    // --1-- delete val.ret.type;
    break;
  case PDTUser:
    break;
  case PDTDummy: assert(false); return -1; break;
  case PDTVar: assert(false); return -1; break;
  default:
    pmesserr("del_pdvaltype: Impossible de détruire une valeur que l'on ne connait pas (%d).", type);
    return -1;
  }
  return 0;
}













// L'équivalent de penvdel & co.
extern void pdvaltdel(pdvalt &dvalt) {
  //// --1-- delete &(dvalt.val);
  //dvalt.type.pdvaltype::del_pascal_dval_type();
  //// --1-- delete &(dvalt);
}
































const penv env0 = NULL;



int penvupdate(penv env, const char * const ident, pdvalt dvalt, penv &res) {
  struct env_cell *elt;

  if (ident == NULL) {
    pmesserr("penvupdate: Impossible d'ajouter un élément sans nom.");
    return -1;
  }

  if (ident[0] == '\0') {
    pmesserr("penvupdate: là c'est pas mieux, tu me file un ident qui est une chaîne vide.");
    return -2;
  }

  //  elt = new struct env_cell;
  //  elt -> ident = new char[strlen(ident)+1];
  //elt -> ident = strcopy(ident);
  //elt -> dvalt = *(dvalt.copy());
  //  elt = new struct env_cell;
  //  elt -> ident = ident;
  //  elt -> dvalt = dvalt;
  elt = new struct env_cell(ident, dvalt);
  
  res = mp(elt, env);
  return 0;
}


int penvmodify(penv env, const char *const ident, pdvalt dvalt) {
  penv temp;

  if (ident == NULL) {
    pmesserr("penvmodify: impossible de recherher un ident NULL.");
    return -1;
  }

  temp = env;

  while (temp != NULL) {
    if (strcmp(temp -> a -> ident, ident) == 0) {
      temp -> a -> dvalt = dvalt;
      return 0;
    }
    temp = temp -> suivant;
  }

  pmesserr("penvmofify: Impossible de trouver l'ident \"%s\" dans l'environnement.", ident);
  return -2;
}


int penvlookup(const penv env, const char * const ident, pdvalt &dvalt) {
  penv temp;

  if (ident == NULL) {
    pmesserr("penvlookup: impossible de rechercher un ident NULL.");
    return -1;
  }

  temp = env;

#if 0
  fprintf(stderr, "TEMP = '%p'\n", temp);
  if (temp != NULL)
    fprintf(stderr, "\t IDENT = '%s'\n", temp -> a -> ident);
#endif
  
  while (temp != NULL) {
    if (0 == strcmp(temp -> a -> ident, ident)) {
      dvalt = temp -> a -> dvalt;
      return 0;
    }

    temp = temp -> suivant;
  }

  pmesserr("penvlookup: Impossible de trouver l'ident \"%s\" dans l'environnement.", ident);
  return -2;
}



int penvfree(penv &env, const penv env0) {
  penv temp, tamp;

  temp = env;

  while (temp != env0 && temp != NULL) {
    temp = temp -> suivant;
  }

  if (temp != env0) {
    pmesserr("penvfree: impossible de trouver env0 [%p] dans env [%p]. On ne fait rien.", env0, env);
    return -1;
  }


  temp = env;

  while (temp != env0) {
    tamp = temp -> suivant;
    // --1-- delete temp -> a;
    // --1-- delete temp;
    temp = tamp;
  }

  env = env0;

  return 0;
}




// Cette fonction est l'équivalente de pmemdel.
// Elle est à exécuter avant pmemdel si on veut un gain de mémoire plus important.
// cf pascal.mem.hpp pour plus d'info.
extern void penvdel(penv &env) {
  penv temp, tamp;

  temp = env;

  while (temp != NULL) {
    tamp = temp -> suivant;
    // --1-- delete [] temp -> a -> ident;
    pdvaltdel(temp -> a -> dvalt);
    // --1-- delete temp -> a;
    // --1-- delete temp;
    temp = tamp;
  }

  env = env0;
}
  


