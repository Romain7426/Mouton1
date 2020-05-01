#ifndef CPASCAL_H
#define CPASCAL_H

#include "pscript/pscript.h"

struct CPascal {
  char * filename; 
  int dico_i; 
  
  pscript_t * pscript_env; 
  
  int funproc_i; 
  int next_ipc0; 
  

#if 1 
  int    readln__arg_nb; 
  char   readln__arg_type[pscript_ffiproc__arg__size]; 
  int    readln__arg_sizeof[pscript_ffiproc__arg__size]; 
  int    readln__arg_offset[pscript_ffiproc__arg__size]; 
  int    readln__arg_mem_size; 
  char * readln__arg_mem; 
  int    readln__retval_allocated_size; 
  char * readln__retval_value; 
#else   
  int          readln__arg_nb; 
  const char * readln__arg_type; 
  const int  * readln__arg_sizeof; 
  const int  * readln__arg_offset; 
  int          readln__arg_mem_size; 
  const char * readln__arg_mem; 
  int          readln__retval_allocated_size; 
  char *       readln__retval_value; 
#endif 
  
  CPascal * (* make_empty)(void); 
  CPascal * (* make_with_file)(const char * filename); 
  void (* delete)(CPascal * this);
  int (* read_file_no_init)(CPascal * this, const char * filename); 
  int (* link_writeln)(CPascal * this);
  int (* link_menu)(CPascal * this);
  int (* link_methods)(CPascal * this);
  int (* link_ffiprocs)(CPascal * this);
  int (* init_file)(CPascal * this);

  int (* execProcedure)(CPascal * this, const char * ident);
  int (* execProcedure_step)(CPascal * this, const char * ident);
  int (* next_step)(CPascal * this, bool * fini_huh);
  void (* stack_push_int)(CPascal * this, int a);
  void (* stack_push_string)(CPascal * this, const char * str);
#if 0   
#endif 
}; 

extern CPascal * CPascal__make_empty(void); 
extern CPascal * CPascal__make_with_file(const char * filename); 
#define CPascal__make CPascal__make_with_file 
#define CPascal_make CPascal__make 
extern void CPascal__delete(CPascal * this); 
#define CPascal_delete CPascal__delete 
extern int CPascal__read_file_no_init(CPascal * this, const char * filename); 
extern int CPascal__link_writeln(CPascal * this);
extern int CPascal__link_menu(CPascal * this);
extern int CPascal__link_methods(CPascal * this);
extern int CPascal__link_ffiprocs(CPascal * this);
extern int CPascal__init_file(CPascal * this);

extern int CPascal__execProcedure(CPascal * this, const char * ident);
extern int CPascal__execProcedure_step(CPascal * this, const char * ident);
extern int CPascal__next_step(CPascal * this, bool * fini_huh);

extern void CPascal__stack_push_int(CPascal * this, int a);
extern void CPascal__stack_push_string(CPascal * this, const char * str);
#if 0 
#endif 

extern int CPascal__ffiproc_callback__Readln__async_reverse_callback__push_return_value(CPascal * this, const char * readln_cstr); 
extern int CPascal__ffiproc_callback__Menu__async_reverse_callback__push_return_value(CPascal * this, const int choice); 



























#if 0
struct CPascal {
  //private:
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
       


  //public:
  //void * prog_exec;
  penv env_exec;

#if 0
  // Le constructeur.
  // Le code d'erreur rend un nombre négatif en cas d'erreur.
  CPascal(const char * const filename);
       
  // Le destructeur.
  // Etant donné que j'ai beaucoup merdé sur la structure générale du machin,
  // ca ne libérera pas beaucoup de mémoire.
  ~CPascal(void);
#endif
       
       
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
#endif 



       

#endif /* CPASCAL_H */
