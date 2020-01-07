#include "global.hpp"
#include "pascal/pascal.tools.hpp"
#include "pascal/pascal.mem.hpp"


const pmem mem0 = {1, NULL};
const ploc nil_ = 0;

int pnew(const pmem mem, const unsigned int size, pmem &res, ploc &i) {
  struct pascal_mem_case *pcase;

  if (size > (PASCAL_MEM_SIZE - mem.next)) {
    pmesserr("Plus de mémoire disponible !");
    pmesserr("Demande d'allocation pour %u cases mémoires, alors qu'il en restait %u.\n", size, PASCAL_MEM_SIZE - mem.next);
    return -1;
  }

  i = mem.next;

  res.next = mem.next + size;

  res.mem = mem.mem;

  for (unsigned int i = 0; i < size; i++) {
    pcase = new pascal_mem_case;
    pcase -> adresse = mem.next + i;
    res.mem = mp(pcase, res.mem);
  }

  return 0;
}


int pmemread(const pmem mem, const ploc i, psval &sval) {
  pliste<struct pascal_mem_case> *temp;

  if (i == nil_) {
    pmesserr("Essai de lecture dans de la mémoire avec le pointeur NIL.");
    return -3;
  }

  if (i >= mem.next) {
    pmesserr("Lecture dans de la mémoire non allouée.");
    return -1;
  }

  temp = mem.mem;
  while (temp != NULL) {
    if (temp -> a -> adresse == i) {
      sval = temp -> a -> contenu;
      return 0;
    }

    temp = temp -> suivant;
  }

  pmesserr("Erreur bizarre. Impossible de trouver l'adresse %u dans l'espace mémoire.", i);
  return -2;
}


int pmemwrite(pmem mem, const ploc i, const psval sval) {
  class pliste<struct pascal_mem_case> *temp;

  if (i == nil_) {
    pmesserr("Essai d'écriture dans de la mémoire avec le pointeur NIL.");
    return -3;
  }

  if (i >= mem.next) {
    pmesserr("Ecriture dans de la mémoire non allouée.");
    return -1;
  }

  temp = mem.mem;
  while (temp != NULL) {
    if (temp -> a -> adresse == i) {
      temp -> a -> contenu = sval;
      return 0;
    }

    temp = temp -> suivant;
  }

  pmesserr("Erreur étrange lors de l'écriture. Impossible de trouver l'adresse %u dans l'espace mémoire.", i);

  return -2;
}



int pmemfree(pmem &mem, const ploc i) {
  psval pstemp;
  pliste<struct pascal_mem_case> *temp, *temp2;
  int ret;

  ret = pmemread(mem, i, pstemp);
  if (ret < 0) {
    pmesserr("Libération de la mémoire impossible, l'adresse spécifiée (%u) est introuvable.", i);
    return -1;
  }

  mem.next = i;
  temp = mem.mem;
  while (temp != NULL) {
    if (temp -> a -> adresse == i) {
      temp2 = temp;
      mem.mem = temp -> suivant;
      // --1-- delete temp2 -> a;
      // --1-- delete temp2;
      return 0;
    }

    temp2 = temp;
    temp = temp -> suivant;
    // --1-- delete temp2 -> a;
    // --1-- delete temp2;
  }

  pmesserr("Argh!!! Erreur interne. On est arrivé au bout de la mémoire alors que l'adresse %u était sensée exister!!!", i);
  return -2;
}



// Cette fonction détruit la mémoire.
// Le but est de libérer de la mémoire.
// Là on détruit tout ce que contient la mémoire.
// La mémoire considère que tout lui appartient.
// cf le .hpp
extern void pmemdel(pmem &mem) {
  pliste<struct pascal_mem_case> *temp, *temp2;

  temp = mem.mem;
  while (temp != NULL) {
    temp2 = temp;
    temp = temp -> suivant;
    // --1-- delete temp2 -> a;
    // --1-- delete temp2;
  }

  mem = mem0;
}

