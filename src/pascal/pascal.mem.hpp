#ifndef PASCAL_MEM_HPP
#define PASCAL_MEM_HPP

union pascal_sval;
typedef union pascal_sval pascal_sval;
typedef union pascal_sval psval;





// D�finition ici de la m�moire.
typedef unsigned int pascal_location;
typedef pascal_location ploc;




// La m�moire contient des �l�ments de type SVal.
// Dans la m�moire, il n'y a aucune information de type.
// C'est dans EVal et DVal qu'il y a des types.
//
// En fait soyons clair, les valeurs sont dans la m�moire et donc dans les SVal.
// Les types eux se trouvent dans l'environnement et donc dans les DVal.
// En plus ils n'ont pas forc�ment quelque chose de commun �tant donn� 
// que la m�moire ne contient que des donn�es simples et du code.
// Or on propose � l'utilisateur bien plus de choses que ce qui est mis en m�moire.
// (Sans parler des constantes.)
//
// Ensuite, une sortie d'une expression, pour permettre une v�rification de type
// (ici dynamique), il y a la valeur mais aussi le type.
// Donc, � compile-time, c reparti,
// et en runtime c localis�;



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
// En fait, une fonction, en m�moire c'est comme une proc�dure.
// La seule diff�rence est la variable sp�ciale qui servira de valeur de retour.
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






// Dans la m�moire, tous les �l�ments y sont par recopie.
// Ainsi, ceux qui sont pass�s en param�tre des fonctions de manipulation
// de la m�moire sont des �l�ments de la m�moire (lecture + �criture).
// La m�moire consid�re que les SVal lui appartiennent.
// Donc faire des copies si n�cessaire !!!!!!!!!
// En fait c'est surtout le cas des �l�ments avec pointeurs comme les proc�dures.
// Le reste c'est bon.
//
// En fait c'est plus compliqu�.
// Une SVal est une case m�moire. Et les cases m�moires appartiennent � la m�moire.
// Seule la m�moire a droit de vie et de mort sur ses cases m�moires.
// Cependant, comme la m�moire ne connait rien de ce qu'elle porte.
// Donc tous les pointeurs sont g�r�s ailleurs et ont int�r�t � bien �tre fait.
// D'ailleurs, reste � d�battre du bien fond� de mettre le nom des param�tres
// dans la m�moire. Plut�t du ressort de DVal.
// (On peut consid�r� que les fonctions ont tjs un seul param�tre,
// de type record.)
//
// Donc, la m�moire a autorit� sur une SVal,
// mais pas sur son contenu.



// Cette fonction alloue 'size' cases m�moires.
// Elle renvoie un code d'erreur.
// 0 => OKI
// n�gatif => MDR
extern int pnew(pmem mem, unsigned int size, pmem * res_ref, ploc * i_ref);

extern const pmem mem0;
extern const ploc nil_; // Le pointeur pascal nil.
// Il a un nom aussi pourri � cause du compilateur G++ sur mon MACOSX qui a d�j� une variable nil de d�finit !!!! :(



#define PASCAL_MEM_SIZE1 ((unsigned int) ((0U - 1U)))
#define PASCAL_MEM_SIZE2 ((unsigned int) (!(0U))) // Non, ne marche pas.
#define PASCAL_MEM_SIZE3 ((unsigned int) (~(0U)))
#define PASCAL_MEM_SIZE4 ((unsigned int) (-1))
#define PASCAL_MEM_SIZE PASCAL_MEM_SIZE4



// Cette fonction renvoie la valeur associ�e � l'adresse i.
// Plus un code d'erreur.
extern int pmemread(const pmem * mem, ploc i, psval * val_ref);


// Cette fonction associe la valeur � l'adresse.
// Renvoie un code d'erreur selon les conventions habituelles.
extern int pmemwrite(pmem * mem, ploc i, psval val);


// Cette fonction lib�re toute la m�moire jusqu'� l'adresse i comprise.
// Renvoie un code d'erreur.
// Ne lib�re pas la m�moire si pas trouv�e.
extern int pmemfree(pmem * mem, ploc i);
    



// Cette fonction d�truit la m�moire.
// Le but est de lib�rer de la m�moire.
// L� on d�truit tout ce que contient la m�moire.
// La m�moire consid�re que tout lui appartient.
// Juste un probl�me : la m�moire ne sait pas ce qu'elle contient.
// Il lui est donc impossible de supprimer ce qu'il y a dedans.
// Notamment, tout sera d�truit sauf les proc�dures et les cha�nes de caract�res.
// Et encore, comme la partie environnement a �t� mal cod�e, on peut d�truire des proc�dures.
// Une fa�on plus propre, est de proc�der d'abord � la destruction de l'environnement,
// et lorsqu'elle croise une proc�dure (+ fonction) ou une string, hop elle d�truit.
// Mais cela ne d�truira pas les variables locales qui n'ont pas �t� d�truites au bon moment. :(
extern void pmemdel(pmem * mem);    



  


#endif /* PASCAL_MEM_HPP */
