#define _PRECALCUL_TYPE(WHAT) {
  /* PRECALCUL de SUBRANGE. */
  if (WHAT .type == pdvaltype::PDTSubrange) {
    
    if (WHAT .val.s.mine != NULL) {
      VERIF_OK(WHAT .val.s.mine->r_evaluate(env, mem, e1));
      delete WHAT .val.s.mine;
      WHAT .val.s.mine = NULL;
      
      if (e1.type.type == pevaltype::PETInteger) {
	WHAT .val.s.min = e1.val.val.i;
      }
      else if (e1.type.type == pevaltype::PETSubrange) {
	WHAT .val.s.min = e1.val.val.s;
      }
      else {
	pmesserr(position.toString());
	pmesserr("CPprog:execute: PType: lors de la création d'un type subrange, mine n'est pas de type scalaire (%s).",e1.type.toString());
	return -97;
      }
      
    }
    
    if (WHAT .val.s.maxe != NULL) {
      VERIF_OK(WHAT .val.s.maxe->r_evaluate(env, mem, e2));	
      delete WHAT .val.s.maxe;
      WHAT .val.s.maxe = NULL;
      
      if (e2.type.type == pevaltype::PETInteger) {
	WHAT .val.s.max = e2.val.val.i;
      }
      else if (e2.type.type == pevaltype::PETSubrange) {
	WHAT .val.s.max = e2.val.val.s;
      }
      else {
	pmesserr(position.toString());
	pmesserr("CPprog:execute: PType: lors de la création d'un type subrange, maxe n'est pas de type scalaire (%s).",e2.type.toString());
	return -95;
      }
      
    }
    
    if (WHAT .val.s.min > WHAT .val.s.max) {
      pmesserr(position.toString());
      pmesserr("CPprog:execute: PType: lors de la création d'un type subrange, min de valeur %d est supérieur à max %d !", WHAT .val.s.min, WHAT .val.s.max);
      return -98;
    }
  }
  
  
  /* PRECALCUL DE ARRAY. */
  else if (WHAT .type == pdvaltype::PDTArray) {
    
    if (WHAT .val.array.indice.mine != NULL) {
      VERIF_OK(WHAT .val.array.indice.mine->r_evaluate(env, mem, e1));
      pmesserr("e1: %s", e1.toString());
      delete WHAT .val.array.indice.mine;
      WHAT .val.array.indice.mine = NULL;
      
      if (e1.type.type == pevaltype::PETInteger) {
	WHAT .val.array.indice.min = e1.val.val.i;				
      }
      else if (e1.type.type == pevaltype::PETSubrange) {
	WHAT .val.array.indice.min = e1.val.val.s;
      }
      else {
	pmesserr(position.toString());
	pmesserr("CPprog:execute: PType: lors de la création d'un type array, mine n'est pas de type scalaire (%s).",e1.type.toString());
	return -922;
      }
      
    }
    
    if (WHAT .val.array.indice.maxe != NULL) {
      VERIF_OK(WHAT .val.array.indice.maxe->r_evaluate(env, mem, e2));
      pmesserr("e2: %s", e2.toString());
      delete WHAT .val.array.indice.maxe;
      WHAT .val.array.indice.maxe = NULL;

      if (e2.type.type == pevaltype::PETInteger) {
	WHAT .val.array.indice.max = e2.val.val.i;
      }
      else if (e2.type.type == pevaltype::PETSubrange) {
	WHAT .val.array.indice.max = e2.val.val.s;
      }
      else {
	pmesserr(position.toString());
	pmesserr("CPprog:execute: PType: lors de la création d'un type array, maxe n'est pas de type scalaire (%s).",e2.type.toString());
	return -917;
      }
      
    }
    
    if (WHAT .val.array.indice.min > WHAT .val.array.indice.max) {
      pmesserr(position.toString());
      pmesserr("CPprog:execute: PType: lors de la création d'un type array, min de valeur %d est supérieur à max %d !", WHAT .val.array.indice.min, WHAT .val.array.indice.max);
      return -915;
    }
  }
}


