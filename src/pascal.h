#ifndef PASCAL_HPP
#define PASCAL_HPP

class CPprog;

#include "global.hpp"
#include "pascal/pascal.mem.hpp"
#include "pascal/pascal.env.hpp"
#include "pascal/pascal.prog.hpp"



/* C'est ici qu'on fournit l'interface avec le jeu pour le moteur pascal.
   Un objet pascal est un fichier.
   Pour l'instant ça ne gère pas les includes dans les fichiers pascal.
   Un fichier se trouve dans le répertoire pascal du projet.
   L'extension est en .pml (Pascal + OCaml).
*/

/* Pour créer un objet pascal, il faut lui passer un nom de fichier 
   (avec l'extension !).
   Le fichier est alors parsé puis exécuté (ça remplit les tables +
   initialisation).
   On renvoie un code d'erreur en cas de problème.
   Ensuite, pour accéder à une variable du fichier (fonctionnelle ou pas),
   il suffit d'appeler la fonction correspondante.
   Elle ira chercher la variable dans la table, retourne un code d'erreur si nécessaire.
   Ensuite, elle réalise le traitement associée.
   
   En fait il y aura une fonction pour chaque type de variable.
   C'est mieux et plus propre.
   Mais de cette manière on ne pourra pas que les types primitifs
   (booléen, entier, intervalle, réel, chaîne et pointeur).
*/



class CPascal {
private:
  // Le fichier que l'on lit.
  const char * const filename;
      
  // La mémoire du script courant.
  pmem mem;
        
  // L'environnement du script courant.
  penv env;

  // la pile du script courant
  pascal_stack_t * stack;
        
  // L'environnement des noms de type.
  // MOI: ne pas oublier de le traiter correctement.
  // Il suppose qu'un seul script ne peut s'exécuter à la fois.
  ptabdvaltypeuser tabdvaltypeuser;
       
  // Code de retour du constructeur.
  int code_erreur;


public:
  // programme en cours d'exécution
  CPprog * prog_exec;
  //void * prog_exec;
  penv env_exec;

  // Le constructeur.
  // Le code d'erreur rend un nombre négatif en cas d'erreur.
  CPascal(const char * const filename);
       
  // Le destructeur.
  // Etant donné que j'ai beaucoup merdé sur la structure générale du machin,
  // ca ne libérera pas beaucoup de mémoire.
  ~CPascal(void);
       
       
  // Fonction qui donne la valeur du code de retour.
  int get_code_erreur(void) { return code_erreur; }
       
       
  // Les fonctions de recherche.
  // Elles retournent toute un code d'erreur. 
  // Il y a erreur si négatif.


  // La lecture.

  // La recherhe d'un booléen.
  int getBoolean(const char *const ident, bool &res);
       
  // La fonction de recherche d'un entier dans l'environnement.
  int getInteger(const char *const ident, int &res);
       
  // La fonction de recherche d'un intervalle dans l'environnement.
  int getSubrange(const char *const ident, int &res);
       
  // La fonction de recherche d'un réel dans l'environnement.
  int getReal(const char *const ident, corps &res);
       
  // La fonction de recherche d'une chaîne de caractères dans l'environnement.
  int getString(const char *const ident, const char *&res);
       
       
  // L'écriture.

  // La recherhe d'un booléen.
  int setBoolean(const char *const ident, bool what);
       
  // La fonction de recherche d'un entier dans l'environnement.
  int setInteger(const char *const ident, int what);
       
  // La fonction de recherche d'un intervalle dans l'environnement.
  int setSubrange(const char *const ident, int what);
       
  // La fonction de recherche d'un réel dans l'environnement.
  int setReal(const char *const ident, corps what);
       
  // La fonction de recherche d'une chaîne de caractères dans l'environnement.
  int setString(const char *const ident, const char *what);



  // L'exécution de code.
  // On ne peut exécuter que des procédures et des fonctions sans paramètres.
  // Pour le passage de parmètre, il faut utiliser les fonctions ci-dessus
  // et prévoir une interface.

  int next_step(bool &fini_huh);

  // La fonction d'exécution d'une procédure.
  int execProcedure(const char *const ident);
  int execProcedure_step(const char *const ident);
       
  // La fonction d'exécution d'une fonction.
  // Il y a une fonction par type de valeur de retour.

  // Exécution d'une fonction booléenne.
  int execFunctionBoolean(const char *const ident, bool &res);
       
  // Exécution d'une fonction entière.
  int execFunctionInteger(const char *const ident, int &res);
       
  // Exécution d'une fonction scalaire.
  int execFunctionSubrange(const char *const ident, int &res);
       
  // Exécution d'une fonction numérique.
  int execFunctionReal(const char *const ident, corps &res);
       
  // Exécution d'une fonction qui retourne une chaîne de caratère.
  int execFunctionString(const char *const ident, const char *&res);



  void stack_push_int(int a);
  void stack_push_string(const char * str);

       
};
       

#endif /* PASCAL_HPP */
