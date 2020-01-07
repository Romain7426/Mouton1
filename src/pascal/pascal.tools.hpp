#ifndef PASCAL_TOOLS_HPP
#define PASCAL_TOOLS_HPP

#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define VERIF_OK(a) {int ret; if ((ret = (a)) < 0) {return ret;}}
#define VERIF_OK_B(a) {if (not(a)) {return false;}}
#define VERIF_TYPE(eee,ttt) {                                           \
    if ((eee).type.type != (ttt)) {                                     \
      pmesserr("position: %s", position.toString());                    \
      pmesserr("Cette expression n'est pas de type %s.", STRING(ttt));  \
      return -11;                                                       \
    }                                                                   \
  }
#define VERIF_TYPE_EQUAL(eee1,eee2)                     \
  VERIF_TYPE_EQUAL3((eee1).type, (eee2).type)

#define VERIF_TYPE2(eee,ttt)                    \
  VERIF_TYPE3((eee) -> type.type, (ttt))

#define VERIF_TYPE3(ttt1,ttt2) {                                        \
    if ((ttt1) != (ttt2)) {                                             \
      pmesserr("[FILE: %s LINE: %s]", __FILE__, STRING(__LINE__));      \
      pmesserr("Cette expression n'est pas de type %s.", STRING(ttt2)); \
      return -11;                                                       \
    }                                                                   \
  }

#define VERIF_TYPE_EQUAL2(eee1,eee2) {                                \
    if (!(pevaltype_equal((eee1) -> type, (eee2) -> type))) {         \
      pmesserr("Les expressions ne sont pas de même type.");          \
      return -11;                                                     \
    }                                                                 \
  }

#define VERIF_TYPE_EQUAL3(eee1,eee2) {                           \
    if (!(pevaltype_equal((eee1), (eee2)))) {                    \
      pmesserr("position: %s", position.toString());            \
      pmesserr("Les expressions ne sont pas de même type.");    \
      return -11;                                               \
    }                                                           \
  }


#define VERIF_SUBRANGE2(res)                                            \
  if (res -> val.val.s < res -> type.val.s.min || res -> val.val.s > res -> type.val.s.max) { \
    pmesserr("Alors, ici on a un petit probleme. En effet, nous sommes en train de considerer une addition sur des elements d'un intervalle [%d ; %d]. Cependant, l'evaluation du premier membre donne %d, et le deuxieme membre donne %d, ce qui nous un resultat de %d, et cet element n'appartient pas a l'intervalle.", res -> type.val.s.min, res -> type.val.s.max, res -> val.val.s, res -> val.val.s, res -> val.val.s); \
    return false;                                                       \
                                                                                            }




#define STRCAT2_(a,b)                                                   \
  strcat(strcpy(new char[strlen(a) + strlen(b) + 1], (a)), (b))

#define STRCAT3_(a,b,c)                                                 \
  strcat(strcat(strcpy(new char[strlen(a) + strlen(b) + strlen(c) + 1], (a)), (b)), (c))

#define STRCAT4_(a,b,c,d)                                               \
  strcat(strcat(strcat(strcpy(new char[strlen(a) + strlen(b) + strlen(c) + strlen(d) + 1], (a)), (b)), (c)), (d))

#define STRCAT5_(a,b,c,d,e)                                             \
  strcat(strcat(strcat(strcat(strcpy(new char[strlen(a) + strlen(b) + strlen(c) + strlen(d) + strlen(e) + 1], (a)), (b)), (c)), (d)), (e))

#define STRCAT6_(a,b,c,d,e,f)                                           \
  strcat(strcat(strcat(strcat(strcat(strcpy(new char[strlen(a) + strlen(b) + strlen(c) + strlen(d) + strlen(e) + strlen(f) + 1], (a)), (b)), (c)), (d)), (e)), (f))

#define STRCAT7_(a,b,c,d,e,f,g)                                         \
  strcat(strcat(strcat(strcat(strcat(strcat(strcpy(new char[strlen(a) + strlen(b) + strlen(c) + strlen(d) + strlen(e) + strlen(f) + strlen(g) + 1], (a)), (b)), (c)), (d)), (e)), (f)), (g))

#define STRCAT8_(a,b,c,d,e,f,g,h)                                       \
  strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcpy(new char[strlen(a) + strlen(b) + strlen(c) + strlen(d) + strlen(e) + strlen(f) + strlen(g) + strlen(h) + 1], (a)), (b)), (c)), (d)), (e)), (f)), (g)), (h))

#define STRCAT9_(a,b,c,d,e,f,g,h,i)                                      \
  strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcpy(new char[strlen(a) + strlen(b) + strlen(c) + strlen(d) + strlen(e) + strlen(f) + strlen(g) + strlen(h) + strlen(i) + 1], (a)), (b)), (c)), (d)), (e)), (f)), (g)), (h)), (i))

#define STRCAT10_(a,b,c,d,e,f,g,h,i,j)                                  \
  strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcpy(new char[strlen(a) + strlen(b) + strlen(c) + strlen(d) + strlen(e) + strlen(f) + strlen(g) + strlen(h) + strlen(i) + strlen(j) + 1], (a)), (b)), (c)), (d)), (e)), (f)), (g)), (h)), (i)), (j))

#define STRCAT11_(a,b,c,d,e,f,g,h,i,j,k)                                \
  strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcpy(new char[strlen(a) + strlen(b) + strlen(c) + strlen(d) + strlen(e) + strlen(f) + strlen(g) + strlen(h) + strlen(i) + strlen(j) + strlen(k) + 1], (a)), (b)), (c)), (d)), (e)), (f)), (g)), (h)), (i)), (j)), (k))






#define STRCAT2(a,b,c) {                                \
    unsigned int taille = strlen(a) + strlen(b);        \
    c = strcat(strcpy(new char[taille + 1], a), b);	\
  }
  
#define STRCAT3(a,b,c,d) {					\
    unsigned int taille = strlen(a) + strlen(b) + strlen(c);	\
    d = strcat(strcat(strcpy(new char[taille + 1], a), b), c);	\
  }
  
#define STRCAT4(a,b,c,d,e) {					        \
    unsigned int taille = strlen(a) + strlen(b) + strlen(c) + strlen(d); \
    e = strcat(strcat(strcat(strcpy(new char[taille + 1], a), b), c), d); \
  }

#define STRCAT5(a,b,c,d,e,f) {                                          \
    unsigned int taille = strlen(a) + strlen(b) + strlen(c) + strlen(d) + strlen(e); \
    f = strcat(strcat(strcat(strcat(strcpy(new char[taille + 1], a), b), c), d), e); \
  }

#define STRCAT6(a,b,c,d,e,f,g) {                                        \
    unsigned int taille = strlen(a) + strlen(b) + strlen(c) + strlen(d) + strlen(e) + strlen(f); \
    g = strcat(strcat(strcat(strcat(strcat(strcpy(new char[taille + 1], a), b), c), d), e), f); \
  }

#define STRCAT7(a,b,c,d,e,f,g,h) {                                      \
    unsigned int taille = strlen(a) + strlen(b) + strlen(c) + strlen(d) + strlen(e) + strlen(f) + strlen(g); \
    h = strcat(strcat(strcat(strcat(strcat(strcat(strcpy(new char[taille + 1], a), b), c), d), e), f), g); \
  }

#define STRCAT8(a,b,c,d,e,f,g,h,i) {                                    \
    unsigned int taille = strlen(a) + strlen(b) + strlen(c) + strlen(d) + strlen(e) + strlen(f) + strlen(g) + strlen(h); \
    i = strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcpy(new char[taille + 1], a), b), c), d), e), f), g), h); \
  }

#define STRCAT9(a,b,c,d,e,f,g,h,i,j) {                                  \
    unsigned int taille = strlen(a) + strlen(b) + strlen(c) + strlen(d) + strlen(e) + strlen(f) + strlen(g) + strlen(h) + strlen(i); \
    j = strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcpy(new char[taille + 1], a), b), c), d), e), f), g), h), i); \
  }

#define STRCAT10(a,b,c,d,e,f,g,h,i,j,k) {                               \
    unsigned int taille = strlen(a) + strlen(b) + strlen(c) + strlen(d) + strlen(e) + strlen(f) + strlen(g) + strlen(h) + strlen(i) + strlen(j); \
    k = strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcpy(new char[taille + 1], a), b), c), d), e), f), g), h), i), j); \
  }

#define STRCAT11(a,b,c,d,e,f,g,h,i,j,k,l) {                             \
    unsigned int taille = strlen(a) + strlen(b) + strlen(c) + strlen(d) + strlen(e) + strlen(f) + strlen(g) + strlen(h) + strlen(i) + strlen(j) + strlen(k); \
    l = strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcpy(new char[taille + 1], a), b), c), d), e), f), g), h), i), j), k); \
  }

#define STRCAT12(a,b,c,d,e,f,g,h,i,j,k,l,m) {                           \
    unsigned int taille = strlen(a) + strlen(b) + strlen(c) + strlen(d) + strlen(e) + strlen(f) + strlen(g) + strlen(h) + strlen(i) + strlen(j) + strlen(k) + strlen(l); \
    m = strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcpy(new char[taille + 1], a), b), c), d), e), f), g), h), i), j), k), l); \
  }

//extern char * strcopy(const char * str);


/*
  #define NB_SIZE 128 // taille du plus grand nombre 32 bits en base 10
  // plus le caractère nul. Lors du passage à 64 bits, 
  // il faudra changer cette valeur ;-).
  // Là, j'ai mis grand pour être sûr qu'il n'y ait pas de problème
  // avant un moment (à 128 bits => pb !)
  // En fait, c'est maintenant !!!!
  // La fonction itoa calcule dynamiquement la taille de la chaîne,
  // avec une fonction logarithmique (argh).
  // Malheureusement, cela ne marche pas avec les virgules flottantes.
  // En effet, il faut connaître la spécification IEEE associée.
  // On reste avec un NB_SIZE grand donc.
  */

// Convertit un nombre en chaîne de caractère.
// Chaîne de caractère allouée avec NEW.
// Donc à détruire avec DELETE[].
extern char * itoa(int i);
// Convertit un float en chaîne de caractère.
// À détruire avec DELETE[].
extern char * ftoa(float f);
// Convertit un booléen en chaîne de caractère.
// À détruire avec DELETE [].
//typedef const char aqw;
//typedef aqw *aqw_ptr;
//typedef const aqw_ptr const_aqw_ptr;
//extern const char * const (* const btoa)  (bool const b) const;

extern char * btoa(bool const b);
extern const char * btoa_const(bool b);
extern const char * btoa_tab[2];






extern void pmessage(const char *mess, ...);
extern void pmesserr(const char *mess, ...);
extern int pmessinit(const char *nom);
extern void pmessend(void);



typedef float corps;
//typedef float real;



// Cette structure sert pour le débogage.
// Elle contient la position de l'expression,
// ou de l'instruction.
// (Comme en DrScheme.)
// Les conventions sont comme partout: 
//  les lignes commencent à 1,
//  et les colonnes à 0.
struct pascal_position;
typedef struct pascal_position pascal_position;
typedef pascal_position ppos;
struct pascal_position {
  unsigned int deb_ligne; // La ligne de début.
  unsigned int fin_ligne; // La ligne de fin.
  unsigned int deb_car; // Le numéro du caractère de début depuis le début de la ligne de début.
  unsigned int fin_car; // Le numéro du caractère de fin depuis le début de la ligne de fin.
  unsigned int deb_car_tot; // Le numéro du caractère de début depuis le début du fichier.
  unsigned int fin_car_tot; // Le numéro du caractère de fin depuis le début du fichier.
  char * (* toString)(const pascal_position * this); 
};

static pascal_position * pascal_position_make(unsigned int deb_ligne, unsigned int fin_ligne, unsigned int deb_car, unsigned int fin_car, unsigned int deb_car_tot, unsigned int fin_car_tot) {
  pascal_position * this = NULL; 
  this->deb_ligne = deb_ligne;
  this->fin_ligne = fin_ligne;
  this->deb_car = deb_car;
  this->fin_car = fin_car;
  this->deb_car_tot = deb_car_tot;
  this->fin_car_tot = fin_car_tot;
  return this; 
};










#if 0

template <class alpha> class pliste {
  //friend pliste<alpha> *mp(alpha *a, pliste<alpha> *l);
public:
  alpha * a;
  pliste<alpha> * suivant;

public:
  pliste<alpha>(void);
  ~pliste<alpha>(void);
  void raz(void);
  void delete_les_boites(void);
  pliste<alpha> * copy(void) const;
  pliste<alpha> * reverse(void) const;
  int length(void) const;
  void print(void) const;
};

template <class alpha> extern pliste<alpha> * mp(alpha * a, pliste<alpha> * l);
template <class alpha> static void pliste_reverse_surplace(pliste<alpha> * &l);
template <class alpha> static pliste<alpha> * pliste_concat2(const pliste<alpha> * l1, const pliste<alpha> * l2);
template <class alpha> static pliste<alpha> * pliste_concat3(const pliste<alpha> * l1, const pliste<alpha> * l2, const pliste<alpha> * l3);
template <class alpha> static void pliste_concat2_surplace(pliste<alpha> * &l1, pliste<alpha> * l2);
template <class alpha> static void pliste_concat3_surplace(pliste<alpha> * &l1, pliste<alpha> * &l2, pliste<alpha> * l3);



template <class alpha> pliste<alpha>::pliste(void) {
  a = NULL;
  suivant = NULL;
}

template <class alpha> pliste<alpha>::~pliste(void) {
  //raz();
}

template <class alpha> void pliste<alpha>::raz(void) {
  //if (suivant != NULL) {
  delete suivant;
  //}
}

template <class alpha> void pliste<alpha>::delete_les_boites(void) {
  if (this == NULL)
    return;

  this -> suivant -> delete_les_boites();

  delete this;
}

template <class alpha> static pliste<alpha> * mp(alpha * a, pliste<alpha> * l) {
  pliste<alpha> * temp;

  temp = new pliste<alpha>;
  temp->a = a;
  temp->suivant = l;
  return temp;
}

template <class alpha> pliste<alpha> * pliste<alpha>::copy(void) const {
  pliste<alpha> * temp;

  temp = new pliste<alpha>;

  temp->a = this->a->copy();
  temp->suivant = (this->suivant == NULL) ? NULL : this->suivant->copy();
  
  return temp;
}

template <class alpha> pliste<alpha> * pliste<alpha>::reverse(void) const {
  pliste<alpha> * temp = NULL;
  const pliste<alpha> * p = this;

  while (p != NULL) {
    temp = mp(p->a->copy(), temp);
    p = p -> suivant;
  }
  
  return temp;
}

template <class alpha> int pliste<alpha>::length(void) const {
  const pliste<alpha> * p = this;
  
  int len = 0;
  while (p != NULL) {
    p = p -> suivant;
    len ++;
  }
  
  return len;
}

template <class alpha> void pliste<alpha>::print(void) const {
  const pliste<alpha> * p = this;
  
  while (p != NULL) {
    fprintf(stderr, "[a = %p, p = %p]", p -> a, p -> suivant);
    p = p -> suivant;
  }

  fprintf(stderr, "%%\n");
}


template <class alpha> static void pliste_reverse_surplace(pliste<alpha> * &liste) {
  pliste<alpha> * precedent;
  pliste<alpha> * courant;
  pliste<alpha> * suivant;

  if (NULL == (liste)) return;

  precedent = NULL;
  courant = liste;
  suivant = courant -> suivant;

  while (suivant != NULL) {
    courant -> suivant = precedent;

    precedent = courant;
    courant = suivant;
    suivant = suivant -> suivant;
  }

  courant -> suivant = precedent;

  liste = courant;
}



template <class alpha> pliste<alpha> * pliste_concat2(const pliste<alpha> * l1, const pliste<alpha> * l2) {
  assert(false);
  return NULL;
}

template <class alpha> pliste<alpha> * pliste_concat3(const pliste<alpha> * l1, const pliste<alpha> * l2, const pliste<alpha> * l3) {
  assert(false);
  return NULL;
}


template <class alpha> void pliste_concat2_surplace(pliste<alpha> * &l1, pliste<alpha> * l2) {
  if (l1 == NULL) {
    l1 = l2;
    return;
  }

  pliste<alpha> * p = l1;
  while (p -> suivant != NULL)
    p = p -> suivant;

  p -> suivant = l2;
}

template <class alpha> void pliste_concat3_surplace(pliste<alpha> * &l1, pliste<alpha> * &l2, pliste<alpha> * l3) {
  pliste_concat2_surplace(l2, l3);
  pliste_concat2_surplace(l1, l2);
}






























template <class beta> class pfifo : public pliste<beta> {
public:
  //friend class pfifo<beta> *mf(beta *b, class pfifo<beta> *lb);
  class pliste<beta> *fin;

public:
};


template <class beta> class pfifo<beta> *mf(beta *b, class pfifo<beta> *lb) {
  class pliste<beta> *temp;

  if (lb == NULL) {
    lb = new class pfifo<beta>;
    lb->a = b;
    lb->suivant = NULL;
    lb->fin = lb;
    return lb;
  }
  else {
    temp = new class pliste<beta>;
    temp->a = b;
    temp->suivant = NULL;
    lb->fin->suivant = temp;
    lb->fin = temp;
    return lb;
  }
}

template <class beta> beta *topf(class pfifo<beta> *lb) {
  if (lb == NULL) {
    return NULL;
  }
  return lb -> a;
}

template <class beta> beta *popf(class pfifo<beta> *(&lb)) {
  beta *res;
  class pliste<beta> *temp;

  if (lb == NULL) {
    return NULL;
  }

  res = lb -> a;

  if (lb -> suivant == NULL) {
    delete lb;
    lb = NULL;
    return res;
  }

  temp = lb -> suivant;
  lb -> a = temp -> a;
  lb -> suivant = temp -> suivant;
  delete temp;

  if (lb -> suivant == NULL) {
    lb -> fin = lb;
  }
  return res;
}


#endif     




#endif /* PASCAL_TOOLS_HPP */
