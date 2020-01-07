#ifndef PASCAL_MEM_HPP
#define PASCAL_MEM_HPP

union pascal_sval;
typedef union pascal_sval pascal_sval;
typedef union pascal_sval psval;





// Définition ici de la mémoire.
typedef unsigned int pascal_location;
typedef pascal_location ploc;




// La mémoire contient des éléments de type SVal.
// Dans la mémoire, il n'y a aucune information de type.
// C'est dans EVal et DVal qu'il y a des types.
//
// En fait soyons clair, les valeurs sont dans la mémoire et donc dans les SVal.
// Les types eux se trouvent dans l'environnement et donc dans les DVal.
// En plus ils n'ont pas forcément quelque chose de commun étant donné 
// que la mémoire ne contient que des données simples et du code.
// Or on propose à l'utilisateur bien plus de choses que ce qui est mis en mémoire.
// (Sans parler des constantes.)
//
// Ensuite, une sortie d'une expression, pour permettre une vérification de type
// (ici dynamique), il y a la valeur mais aussi le type.
// Donc, à compile-time, c reparti,
// et en runtime c localisé;



typedef bool psboolean;
typedef int psinteger;
typedef int pssubrange;
typedef corps psreal;
typedef char *psstring;
typedef ploc pspointer;
struct psprocedure {
  //struct param {
  //char *nom;
  // Dans DVal en fait.
  //petype type;
  //};
  //pliste<param> *lparams;
  //void *prog; // c du type prog pascal
  CPprog * prog;
};
typedef struct psprocedure psprocedure;
// En fait, une fonction, en mémoire c'est comme une procédure.
// La seule différence est la variable spéciale qui servira de valeur de retour.
//struct psfunction : public psprocedure {
//  pfuncrett retour; // type de la valeur de retour
//};

union pascal_sval {
  psboolean b;
  psinteger i;
  pssubrange s;
  psreal r;
  psstring str;
  pspointer ptr;
  psprocedure proc;
  //psfunction func;
};



enum { pascal_mem_size = 2048 }; 
struct pascal_mem {
  ploc adresse[pascal_mem_size];
  psval contenu[pascal_mem_size];
  int nb; 
};

//friend extern int pnew(pmem mem, unsigned int size, pmem &res);
//friend int pmemlookup(pmem mem, ploc i, psval &val);






// Dans la mémoire, tous les éléments y sont par recopie.
// Ainsi, ceux qui sont passés en paramètre des fonctions de manipulation
// de la mémoire sont des éléments de la mémoire (lecture + écriture).
// La mémoire considère que les SVal lui appartiennent.
// Donc faire des copies si nécessaire !!!!!!!!!
// En fait c'est surtout le cas des éléments avec pointeurs comme les procédures.
// Le reste c'est bon.
//
// En fait c'est plus compliqué.
// Une SVal est une case mémoire. Et les cases mémoires appartiennent à la mémoire.
// Seule la mémoire a droit de vie et de mort sur ses cases mémoires.
// Cependant, comme la mémoire ne connait rien de ce qu'elle porte.
// Donc tous les pointeurs sont gérés ailleurs et ont intérêt à bien être fait.
// D'ailleurs, reste à débattre du bien fondé de mettre le nom des paramètres
// dans la mémoire. Plutôt du ressort de DVal.
// (On peut considéré que les fonctions ont tjs un seul paramètre,
// de type record.)
//
// Donc, la mémoire a autorité sur une SVal,
// mais pas sur son contenu.



// Cette fonction alloue 'size' cases mémoires.
// Elle renvoie un code d'erreur.
// 0 => OKI
// négatif => MDR
extern int pnew(pmem mem, unsigned int size, pmem * res_ref, ploc * i_ref);

extern const pmem mem0;
extern const ploc nil_; // Le pointeur pascal nil.
// Il a un nom aussi pourri à cause du compilateur G++ sur mon MACOSX qui a déjà une variable nil de définit !!!! :(



#define PASCAL_MEM_SIZE1 ((unsigned int) ((0U - 1U)))
#define PASCAL_MEM_SIZE2 ((unsigned int) (!(0U))) // Non, ne marche pas.
#define PASCAL_MEM_SIZE3 ((unsigned int) (~(0U)))
#define PASCAL_MEM_SIZE4 ((unsigned int) (-1))
#define PASCAL_MEM_SIZE PASCAL_MEM_SIZE4



// Cette fonction renvoie la valeur associée à l'adresse i.
// Plus un code d'erreur.
extern int pmemread(const pmem * mem, ploc i, psval * val_ref);


// Cette fonction associe la valeur à l'adresse.
// Renvoie un code d'erreur selon les conventions habituelles.
extern int pmemwrite(pmem * mem, ploc i, psval val);


// Cette fonction libère toute la mémoire jusqu'à l'adresse i comprise.
// Renvoie un code d'erreur.
// Ne libère pas la mémoire si pas trouvée.
extern int pmemfree(pmem * mem, ploc i);
    



// Cette fonction détruit la mémoire.
// Le but est de libérer de la mémoire.
// Là on détruit tout ce que contient la mémoire.
// La mémoire considère que tout lui appartient.
// Juste un problème : la mémoire ne sait pas ce qu'elle contient.
// Il lui est donc impossible de supprimer ce qu'il y a dedans.
// Notamment, tout sera détruit sauf les procédures et les chaînes de caractères.
// Et encore, comme la partie environnement a été mal codée, on peut détruire des procédures.
// Une façon plus propre, est de procéder d'abord à la destruction de l'environnement,
// et lorsqu'elle croise une procédure (+ fonction) ou une string, hop elle détruit.
// Mais cela ne détruira pas les variables locales qui n'ont pas été détruites au bon moment. :(
extern void pmemdel(pmem * mem);    



  


#endif /* PASCAL_MEM_HPP */
