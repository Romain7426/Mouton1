#include "global.h"
#include "pascal.h"
#include "pascal/pascal.h"



CPascal * CPascal_make(const char * filename) { 
  MALLOC_BZERO(CPascal,this);

  assert(false); 
  
#if 0
  ASSIGN_METHOD(CPascal,this,execProcedure); 
  ASSIGN_METHOD(CPascal,this,execProcedure_step); 
  ASSIGN_METHOD(CPascal,this,next_step); 
  ASSIGN_METHOD(CPascal,this,stack_push_int); 
  ASSIGN_METHOD(CPascal,this,stack_push_string); 
#endif 


  if (filename == NULL) {
    messerr("Constructeur de CPascal: le nom de fichier est le pointeur NULL.");
    this -> code_erreur = -1;
    assert(false);
    //throw ((void *) NULL);
    free(this); 
    return NULL;
  }
  if (filename[0] == '\0') {
    messerr("Constructeur de CPascal: le nom de fichier est la chaîne vide.");
    this -> code_erreur = -2;
    assert(false);
    //throw ((void *) NULL);
    free(this); 
    return NULL;
  }  
  printf("  nom de fichier correct!\n");
  
  this -> filename = strcopy(filename); 
  this -> prog_exec = NULL; 

  printf("Constructeur CPascal__CPascal(%s)\n", this -> filename); 
  
  


#define clexing_ ".lexing.out"
  static const char * const clexing = clexing_;
  static const int pastaille = ARRAY_SIZE(PASCALDIR) - 1;
  static const int lextaille = ARRAY_SIZE(clexing_) - 1; 
  const int taille = pastaille + strlen(filename);
  char reelname[taille+1];
  char lexing[taille+1];
  strcat(strcpy(reelname, PASCALDIR), filename);
  strcat(strcpy(lexing, reelname), clexing);
  printf("  nom de fichier réel: %s\n", reelname);

  assert(false); 
  
  message("Constructeur de CPascal: C'est bon, l'initialisation du fichier de script pascalml '%s' s'est bien passée.", filename);
  return this; 
}; 


void CPascal_delete(CPascal * this) {
  // Il faut fermer les flux de message d'erreur,
  // et détruire l'environnement,
  // et détruire la mémoire.

  assert(false); 
  
  //pascal_stack_free(this -> stack);
  //penvdel(this->env);
  //ptabdvaltypeuser_del(tabdvaltypeuser);
  //pmemdel(this->mem);
  //pmessend();
  free(this -> filename); 
  free(this); 
}; 











#if 0 
#include "pascal/pascal.tools.hpp"
#include "pascal/pascal.prog.hpp"
#include "pascal/pascal.mem.hpp"
#include "pascal/pascal.expr.hpp"
#include "pascal/pascal.env.hpp"

// Les trucs du lexer et du parser.
extern FILE * yypascalout;
extern int yypascalparse(void);
extern void yypascalrestart(FILE * new_file);
extern void yypascallexerinit(void);
extern CPprog * prog;


extern void pmessage(const char *mess, ...);
extern void pmesserr(const char *mess, ...);
extern int pmessinit(const char *nom);
extern void pmessend(void);

//extern penv * env0; 
//extern pmem * mem0; 
extern pdvaltypeuser * tabdvaltypeuser0;
extern pdvaltypeuser * tabdvaltypeuser; 
//typedef float corps;


// Le constructeur.
// Le code d'erreur rend un nombre négatif en cas d'erreur.
CPascal * CPascal_make(const char * filename) { 
  MALLOC_BZERO(CPascal,this);
  
  ASSIGN_METHOD(CPascal,this,execProcedure); 
  ASSIGN_METHOD(CPascal,this,execProcedure_step); 
  ASSIGN_METHOD(CPascal,this,next_step); 
  ASSIGN_METHOD(CPascal,this,stack_push_int); 
  ASSIGN_METHOD(CPascal,this,stack_push_string); 


  if (filename == NULL) {
    messerr("Constructeur de CPascal: le nom de fichier est le pointeur NULL.");
    this -> code_erreur = -1;
    assert(false);
    //throw ((void *) NULL);
    free(this); 
    return NULL;
  }
  else if (filename[0] == '\0') {
    messerr("Constructeur de CPascal: le nom de fichier est la chaîne vide.");
    this -> code_erreur = -2;
    assert(false);
    //throw ((void *) NULL);
    free(this); 
    return NULL;
  }  
  else {
    printf("  nom de fichier correct!\n");
  }; 
 

  this -> filename = strcopy(filename); 
  this -> prog_exec = NULL; 


  printf("Constructeur CPascal__CPascal(%s)\n", this -> filename);                     

  char * reelname;
  char * lexing;
#define clexing_ ".lexing.out"
  static const char * const clexing = clexing_;
  static const unsigned int pastaille = ARRAY_SIZE(PASCALDIR) - 1;
  static const unsigned int lextaille = ARRAY_SIZE(clexing_) - 1; 
  unsigned int taille;
  int ret;
  FILE * yypascalin;
 
#if 1
  reelname = strconcat2(PASCALDIR, filename);
  lexing = strconcat3(LOGDIR, filename, clexing);
#else
  taille = pastaille + strlen(filename);
  reelname = strcat(strcpy(new char[taille + 1], PASCALDIR), filename);
  lexing = strcat(strcpy(new char[taille + lextaille + 1], reelname), clexing);
#endif

  printf("  nom de fichier réel: %s\n", reelname);

  // Initialisation des fonctions de messages pour l'exécution du script.
  // .notice et .error
  //ret = pmessinit(reelname);
  ret = pmessinit(filename);
  if (ret < 0) {
    messerr("Constructeur de CPascal: Impossible de créer les fichiers de sorties pour l'exécution du script (reelname = '%s').", reelname);
    this -> code_erreur = -3;
    assert(false);
    //throw ((void *) NULL);
    free(this -> filename); 
    free(this); 
    return NULL;
  }; 
 
 
  messerr("HEREHERE: reelname: %s ; lexing: %s", reelname, lexing);
  // Ouverture des flux d'entrées et de sorties pour le lexer.
  yypascalout = fopen(lexing, "w");
  if (yypascalout == NULL) {
    messerr("Constructeur de CPascal: Impossible d'ouvrir en écriture le fichier '%s' pour les sorties du lexer.", lexing);
    this -> code_erreur = -4;
    assert(false);
    //throw ((void *) NULL);
    free(this -> filename); 
    free(this); 
    return NULL;
  };
 
  yypascalin = fopen(reelname, "r");
  if (yypascalin == NULL) {
    messerr("Constructeur de CPascal: Impossible d'ouvrir en lecture le fichier '%s'.", reelname);
    fclose(yypascalout);
    assert(false);
    this -> code_erreur = -5;
    //throw ((void *) NULL);
    free(this -> filename); 
    free(this); 
    return NULL;
  }; 
 
  //messerr("HEREHERE: flux reelname: %p ; flux lexing: %p", yypascalin, yypascalout);
  // On initialise le lexer.
  yypascallexerinit();
  yypascalrestart(yypascalin);
  //messerr("HEREHERE: flux reelname: %p ; flux lexing: %p", yypascalin, yypascalout);
  // On parse le fichier.
  ret = yypascalparse();
  //messerr("HEREHERE: ret = %d", ret);
  // On ferme les flux qui ne serviront plus.
  // Même chose avec les noms associés.
  fclose(yypascalin);
  fclose(yypascalout);
  free(reelname);
  free(lexing);
  if (ret != 0) {
    /*-------------------------------------.
      | yyacceptlab -- YYACCEPT comes here.  |
      `-------------------------------------*/
    //  yyresult = 0;
    /*-----------------------------------.
      | yyabortlab -- YYABORT comes here.  |
      `-----------------------------------*/
    //yyresult = 1;
    /*----------------------------------------------.
      | yyoverflowlab -- parser overflow comes here.  |
      `----------------------------------------------*/
    //yyresult = 2;
    messerr("Constructeur de CPascal: L'analyse du fichier '%s' a ratée. Vérifiez donc sa syntaxe. (ret = %d)", filename, ret);
    this -> code_erreur = -6;
    assert(false);
    //throw ((void *) NULL);
    free(this -> filename); 
    free(this); 
    return NULL;
  }
 
  if (prog == NULL) {
    messerr("Constructeur de CPascal: Erreur interne: L'analyse du fichier '%s' a réussie, mais elle a produit un programme NULL.", filename);
    this -> code_erreur = -7;
    assert(false);
    //throw ((void *) NULL);
    free(this -> filename); 
    free(this); 
    return NULL;
  };
  
  pmessage("Affichage du programme.");
  pmessage("-----------------------");
  pmessage(prog -> toString(prog));
  pmessage("-----------------------");
 
  // Initialisation des variables.
  *(this -> env) = env0;
  *(this -> mem) = mem0;
  this -> stack = pascal_stack_make();
 
  // Mise en place du tableau de type.
  this -> tabdvaltypeuser = tabdvaltypeuser0;
  // Exécution du script.
  ret = prog -> execute(prog, this -> env, this -> mem);
  // On récupère le tableau de type.
  this -> tabdvaltypeuser = tabdvaltypeuser;
  // On n'a plus besoin de prog après.
  prog = NULL;
  if (ret < 0) {
    messerr("Constructeur de CPascal: L'exécution de l'initialisation du fichier de script PascalML '%s'a merdé.", filename);
    this -> code_erreur = -8;
    assert(false);
    //throw ((void *) NULL);
    free(this -> filename); 
    free(this); 
    return NULL;
  }; 
  
  message("Constructeur de CPascal: C'est bon, l'initialisation du fichier de script pascalml '%s' s'est bien passée.", filename);
  return this; 
}; 




// Le destructeur.
void CPascal_delete(CPascal * this) {
  // Il faut fermer les flux de message d'erreur,
  // et détruire l'environnement,
  // et détruire la mémoire.
  // On ne détruit pas le nom du fichier car il ne nous appartient pas.

  pascal_stack_free(this -> stack);
  //penvdel(this->env);
  //ptabdvaltypeuser_del(tabdvaltypeuser);
  //pmemdel(this->mem);
  pmessend();
  free(this -> filename); 
  free(this); 
}; 
 

int CPascal__getBoolean(const CPascal * this, const char * ident, bool * res_ref) {
  pdvalt dvalt;
  psval sval;
  int ret;
    
  ret = penvlookup(this -> env, ident, &dvalt);
  if (ret < 0) {
    messerr("CPascal__getBoolean: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  };
    
  if (dvalt.type.type != PDTBoolean) {
    messerr("CPascal__getBoolean: L'identifiant '%s' n'a pas le type booléen, mais le type %s.", ident, dvalt.type.toString(&dvalt.type));
    return -2;
  };

  ret = pmemread(this->mem, dvalt.val.val.b, &sval);
  if (ret < 0) {
    messerr("CPascal__getBoolean: L'identifiant '%s' n'a pas pu être trouvé dans la mémoire.", ident);
    return -3;
  };
    
  *res_ref = sval.b;
  return 0;
}; 


int CPascal__getInteger(const CPascal * this, const char * ident, int * res_ref) {
  pdvalt dvalt;
  psval sval;
  int ret;
    
  ret = penvlookup(this->env, ident, &dvalt);
  if (ret < 0) {
    messerr("CPascal__getInteger: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != PDTInteger) {
    messerr("CPascal__getInteger: L'identifiant '%s' n'a pas le type entier, mais le type %s.", ident, dvalt.type.toString(&dvalt.type));
    return -2;
  }

  ret = pmemread(this->mem, dvalt.val.val.i, &sval);
  if (ret < 0) {
    messerr("CPascal__getInteger: L'identifiant '%s' n'a pas pu être trouvé dans la mémoire.", ident);
    return -3;
  }
    
  *res_ref = sval.i;
  return 0;
};


       
// La fonction de recherche d'un intervalle dans l'environnement.
int CPascal__getSubrange(const CPascal * this, const char *const ident, int * res_ref) {
  pdvalt dvalt;
  psval sval;
  int ret;
    
  ret = penvlookup(this->env, ident, &dvalt);
  if (ret < 0) {
    messerr("CPascal__getSubrange: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != PDTSubrange) {
    messerr("CPascal__getSubrange: L'identifiant '%s' n'a pas le type intervalle, mais le type %s.", ident, dvalt.type.toString(&dvalt.type));
    return -2;
  }

  ret = pmemread(this->mem, dvalt.val.val.s, &sval);
  if (ret < 0) {
    messerr("CPascal__getSubrange: L'identifiant '%s' n'a pas pu être trouvé dans la mémoire.", ident);
    return -3;
  }
    
  *res_ref = sval.i;
  return 0;
};



// La fonction de recherche d'un réel dans l'environnement.
int CPascal__getReal(const CPascal * this, const char *const ident, corps * res_ref) {
  pdvalt dvalt;
  psval sval;
  int ret;
    
  ret = penvlookup(this->env, ident, &dvalt);
  if (ret < 0) {
    messerr("CPascal__getReal: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != PDTReal) {
    messerr("CPascal__getReal: L'identifiant '%s' n'a pas le type réel, mais le type %s.", ident, dvalt.type.toString(&dvalt.type));
    return -2;
  }

  ret = pmemread(this->mem, dvalt.val.val.r, &sval);
  if (ret < 0) {
    messerr("CPascal__getReal: L'identifiant '%s' n'a pas pu être trouvé dans la mémoire.", ident);
    return -3;
  }
    
  *res_ref = sval.r;
  return 0;
};




       
// La fonction de recherche d'une chaîne de caractères dans l'environnement.
int CPascal__getString(const CPascal * this, const char *const ident, const char ** res_ref) {
  pdvalt dvalt;
  psval sval;
  int ret;
    
  ret = penvlookup(this->env, ident, &dvalt);
  if (ret < 0) {
    messerr("CPascal__getString: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != PDTString) {
    messerr("CPascal__getString: L'identifiant '%s' n'a pas le type chaîne de caractère, mais le type %s.", ident, dvalt.type.toString(&dvalt.type));
    return -2;
  }

  ret = pmemread(this->mem, dvalt.val.val.str, &sval);
  if (ret < 0) {
    messerr("CPascal__getString: L'identifiant '%s' n'a pas pu être trouvé dans la mémoire.", ident);
    return -3;
  }
    
  *res_ref = sval.str;
  return 0;
};







// L'écriture.

// La recherhe d'un booléen.
int CPascal__setBoolean(CPascal * this, const char *const ident, bool what) {
  pdvalt dvalt;
  psval sval;
  int ret;
    
  ret = penvlookup(this->env, ident, &dvalt);
  if (ret < 0) {
    messerr("CPascal__setBoolean: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != PDTBoolean) {
    messerr("CPascal__setBoolean: L'identifiant '%s' n'a pas le type booléen, mais le type %s.", ident, dvalt.type.toString(&dvalt.type));
    return -2;
  }

  sval.b = what;
  ret = pmemwrite(this->mem, dvalt.val.val.b, sval);
  if (ret < 0) {
    messerr("CPascal__setBoolean: L'identifiant '%s' n'a pas pu être trouvé dans la mémoire.", ident);
    return -3;
  }
    
  return 0;
};





// La fonction de recherche d'un entier dans l'environnement.
int CPascal__setInteger(CPascal * this, const char *const ident, int what) {
  pdvalt dvalt;
  psval sval;
  int ret;
    
  ret = penvlookup(this->env, ident, &dvalt);
  if (ret < 0) {
    messerr("CPascal__setInteger: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != PDTInteger) {
    messerr("CPascal__setInteger: L'identifiant '%s' n'a pas le type entier, mais le type %s.", ident, dvalt.type.toString(&dvalt.type));
    return -2;
  }

  sval.i = what;
  ret = pmemwrite(this->mem, dvalt.val.val.i, sval);
  if (ret < 0) {
    messerr("CPascal__setInteger: L'identifiant '%s' n'a pas pu être trouvé dans la mémoire.", ident);
    return -3;
  }
    
  return 0;
};






// La fonction de recherche d'un intervalle dans l'environnement.
int CPascal__setSubrange(CPascal * this, const char *const ident, int what) {
  pdvalt dvalt;
  psval sval;
  int ret;
    
  ret = penvlookup(this->env, ident, &dvalt);
  if (ret < 0) {
    messerr("CPascal__setSubrange: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != PDTSubrange) {
    messerr("CPascal__setSubrange: L'identifiant '%s' n'a pas le type intervalle, mais le type %s.", ident, dvalt.type.toString(&dvalt.type));
    return -2;
  }

  if (what < dvalt.type.val.s.min) {
    messerr("CPascal__setSubrange: L'identifiant '%s' a bien été trouvé dans la mémoire, mais il n'a pas le bon type. En effet c'est un intervalle entier et la valeur passée en paramètre est trop petite (intervalle = [ %d ; %d ], valeur = %d).", ident, dvalt.type.val.s.min, dvalt.type.val.s.max, what);
    return -4;
  }
  if (what > dvalt.type.val.s.max) {
    messerr("CPascal__setSubrange: L'identifiant '%s' a bien été trouvé dans la mémoire, mais il n'a pas le bon type. En effet c'est un intervalle entier et la valeur passée en paramètre est trop grande (intervalle = [ %d ; %d ], valeur = %d).", ident, dvalt.type.val.s.min, dvalt.type.val.s.max, what);
    return -5;
  }
  sval.i = what;
  ret = pmemwrite(this->mem, dvalt.val.val.s, sval);
  if (ret < 0) {
    messerr("CPascal__setSubrange: L'identifiant '%s' n'a pas pu être trouvé dans la mémoire.", ident);
    return -3;
  }
    
  return 0;
};







// La fonction de recherche d'un réel dans l'environnement.
int CPascal__setReal(CPascal * this, const char *const ident, corps what) {
  pdvalt dvalt;
  psval sval;
  int ret;
    
  ret = penvlookup(this->env, ident, &dvalt);
  if (ret < 0) {
    messerr("CPascal__setReal: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != PDTReal) {
    messerr("CPascal__setReal: L'identifiant '%s' n'a pas le type réel, mais le type %s.", ident, dvalt.type.toString(&dvalt.type));
    return -2;
  }

  sval.r = what;
  ret = pmemwrite(this->mem, dvalt.val.val.r, sval);
  if (ret < 0) {
    messerr("CPascal__setReal: L'identifiant '%s' n'a pas pu être trouvé dans la mémoire.", ident);
    return -3;
  }
    
  return 0;
};








// La fonction de recherche d'une chaîne de caractères dans l'environnement.
int CPascal__setString(CPascal * this, const char *const ident, const char * const what) {
  pdvalt dvalt;
  psval sval;
  int ret;
    
  ret = penvlookup(this->env, ident, &dvalt);
  if (ret < 0) {
    messerr("CPascal__setString: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != PDTString) {
    messerr("CPascal__setString: L'identifiant '%s' n'a pas le type chaîne de caractère, mais le type %s.", ident, dvalt.type.toString(&dvalt.type));
    return -2;
  }

  sval.str = strcopy(what);
  ret = pmemwrite(this->mem, dvalt.val.val.str, sval);
  if (ret < 0) {
    messerr("CPascal__setString: L'identifiant '%s' n'a pas pu être trouvé dans la mémoire.", ident);
    return -3;
  }
    
  return 0;
};








// La fonction d'exécution d'une procédure.
int CPascal__execProcedure(CPascal * this, const char * const ident) {
  pdvalt dvalt;
  int ret;
    
  ret = penvlookup(this->env, ident, &dvalt);
  if (ret < 0) {
    messerr("CPascal__execProcedure: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != PDTProcedure) {
    messerr("CPascal__execProcedure: L'identifiant '%s' n'a pas le type procédure, mais le type %s.", ident, dvalt.type.toString(&dvalt.type));
    return -2;
  }
  
  if (dvalt.type.val.proc.param_nb != 0) {
    messerr("CPascal__execProcedure: L'identifiant '%s' est une procédure à paramètre, or elle devrait être sans paramètre.", ident);
    return -3;
  }
  
  tabdvaltypeuser = this->tabdvaltypeuser;
  // !!!! PAS BIEN !!! >:-(
  ret = dvalt.type.val.proc.corps->execute(dvalt.type.val.proc.corps, dvalt.type.val.proc.env, this->mem);
  //this->tabdvaltypeuser = tabdvaltypeuser;
  //tabdvaltypeuser = tabdvaltypeuser0;
  if (ret < 0) {
    messerr("CPascal__execProcedure: Lors de l'exécution de la procédure '%s', une erreur s'est produite.", ident);
    return -4;
  }
    
  return 0;
};




// La fonction d'exécution d'une procédure.
int CPascal__execProcedure_step(CPascal * this, const char *const ident) {
  pdvalt dvalt;
  int ret;
    
  ret = penvlookup(this->env, ident, &dvalt);
  if (ret < 0) {
    messerr("CPascal__execProcedure_step: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != PDTProcedure) {
    messerr("CPascal__execProcedure_step: L'identifiant '%s' n'a pas le type procédure, mais le type %s.", ident, dvalt.type.toString(&dvalt.type));
    return -2;
  }
  
  if (dvalt.type.val.proc.param_nb != 0) {
    messerr("CPascal__execProcedure_step: L'identifiant '%s' est une procédure à paramètre, or elle devrait être sans paramètre.", ident);
    return -3;
  }
    

  //tabdvaltypeuser = this -> tabdvaltypeuser;

  // !!!! PAS BIEN !!! >:-(
  //ret = dvalt.type.val.proc.corps->execute_step(dvalt.type.val.proc.env, this->mem, prog_this);
  this -> env_exec = dvalt.type.val.proc.env -> copy(dvalt.type.val.proc.env);
  this -> prog_exec = dvalt.type.val.proc.corps;
    
  return 0;
};








int CPascal__next_step(CPascal * this, bool * fini_huh_ref) {
  *fini_huh_ref = false;

  if (this -> prog_exec == NULL) {
    *fini_huh_ref = true;
    return 0;
  }

  int ret;
  CPprog * futur = NULL;

  ret = this -> prog_exec -> execute_step(this -> prog_exec, this -> env_exec, this -> mem, this -> stack, &futur);
  
  this -> prog_exec = futur;


  if (ret < 0) {
    messerr("CPascal__next_step: Lors de l'exécution du code, une erreur s'est produite: ret = %d", ret);
  }

  return ret;
};











// La fonction d'exécution d'une fonction.
// Il y a une fonction par type de valeur de retour.

// Exécution d'une fonction booléenne.
int CPascal__execFunctionBoolean(CPascal * this, const char *const ident, bool * res_ref) {
  pdvalt dvalt;
  int ret;
    
  ret = penvlookup(this->env, ident, &dvalt);
  if (ret < 0) {
    messerr("CPascal__execFunctionBoolean: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != PDTFunction) {
    messerr("CPascal__execFunctionBoolean: L'identifiant '%s' n'a pas le type fonction, mais le type %s.", ident, dvalt.type.toString(&dvalt.type));
    return -2;
  }

  if (dvalt.type.val.func.param_nb != 0) {
    messerr("CPascal__execFunctionBoolean: L'identifiant '%s' est une fonction à paramètre, or elle devrait être sans paramètre.", ident);
    return -3;
  }

  if (dvalt.type.val.func.type->type != PDTBoolean) {
    messerr("CPascal__execFunctionBoolean: L'identifiant '%s' est une fonction dont la valeur de retour n'est pas un booléen, mais de type %s.", ident, dvalt.type.val.func.type->toString(dvalt.type.val.func.type));
    return -5;
  }

    
  // PAS TERRIBLE
  tabdvaltypeuser = this->tabdvaltypeuser;
    
  CPexpr *call;
  call = CPexpr_make(0U,0U,0U,0U,0U,0U);
  call -> type = CPexpr_PCall;
  call -> val.upcall.ident = strcopy(ident);
  call -> val.upcall.args_nb = 0;

  pevalt e;
  ret = call->r_evaluate(call, this -> env, this -> mem, &e);
  if (ret < 0) {
    messerr("CPascal__execFunctionBoolean: Une erreur s'est produite pendant l'exécution de la fonction '%s'.", ident);
    return -6;
  }

  *res_ref = e.val.val.b;    
    
  return 0;
};







// Exécution d'une fonction entière.
int CPascal__execFunctionInteger(CPascal * this, const char *const ident, int * res_ref) {
  pdvalt dvalt;
  int ret;
    
  ret = penvlookup(this->env, ident, &dvalt);
  if (ret < 0) {
    messerr("CPascal__execFunctionInteger: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != PDTFunction) {
    messerr("CPascal__execFunctionInteger: L'identifiant '%s' n'a pas le type fonction, mais le type %s.", ident, dvalt.type.toString(&dvalt.type));
    return -2;
  }

  if (dvalt.type.val.func.param_nb != 0) {
    messerr("CPascal__execFunctionInteger: L'identifiant '%s' est une fonction à paramètre, or elle devrait être sans paramètre.", ident);
    return -3;
  }

  if (dvalt.type.val.func.type->type != PDTInteger) {
    messerr("CPascal__execFunctionInteger: L'identifiant '%s' est une fonction dont la valeur de retour n'est pas un entier, mais de type %s.", ident, dvalt.type.val.func.type->toString(dvalt.type.val.func.type));
    return -5;
  }

    
  // PAS TERRIBLE
  tabdvaltypeuser = this->tabdvaltypeuser;
    
  CPexpr *call;
  call = CPexpr_make(0U,0U,0U,0U,0U,0U);
  call->type = CPexpr_PCall;
  call->val.upcall.ident = strcopy(ident);
  call->val.upcall.args_nb = 0;

  pevalt e;
  ret = call->r_evaluate(call, this->env, this->mem, &e);
  if (ret < 0) {
    messerr("CPascal__execFunctionInteger: Une erreur s'est produite pendant l'exécution de la fonction '%s'.", ident);
    return -6;
  }

  *res_ref = e.val.val.i;

  return 0;
};







// Exécution d'une fonction scalaire.
int CPascal__execFunctionSubrange(CPascal * this, const char *const ident, int * res_ref) {
  pdvalt dvalt;
  int ret;
    
  ret = penvlookup(this->env, ident, &dvalt);
  if (ret < 0) {
    messerr("CPascal__execFunctionSubrange: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != PDTFunction) {
    messerr("CPascal__execFunctionBoolean: L'identifiant '%s' n'a pas le type fonction, mais le type %s.", ident, dvalt.type.toString(&dvalt.type));
    return -2;
  }

  if (dvalt.type.val.func.param_nb != 0) {
    messerr("CPascal__execFunctionBoolean: L'identifiant '%s' est une fonction à paramètre, or elle devrait être sans paramètre.", ident);
    return -3;
  }

  if (dvalt.type.val.func.type->type != PDTSubrange) {
    messerr("CPascal__execFunctionBoolean: L'identifiant '%s' est une fonction dont la valeur de retour n'est pas un intervalle entier, mais de type %s.", ident, dvalt.type.val.func.type->toString(dvalt.type.val.func.type));
    return -5;
  }

    
  // PAS TERRIBLE
  tabdvaltypeuser = this->tabdvaltypeuser;
    
  CPexpr *call;
  call = CPexpr_make(0U,0U,0U,0U,0U,0U);
  call->type = CPexpr_PCall;
  call->val.upcall.ident = strcopy(ident);
  call->val.upcall.args_nb = 0;

  pevalt e;
  ret = call->r_evaluate(call, this -> env, this -> mem, &e);
  if (ret < 0) {
    messerr("CPascal__execFunctionSubrange: Une erreur s'est produite pendant l'exécution de la fonction '%s'.", ident);
    return -6;
  }

  *res_ref = e.val.val.b;    
    
  return 0;
};







// Exécution d'une fonction numérique.
int CPascal__execFunctionReal(CPascal * this, const char *const ident, corps * res_ref) {
  pdvalt dvalt;
  int ret;
    
  ret = penvlookup(this->env, ident, &dvalt);
  if (ret < 0) {
    messerr("CPascal__execFunctionReal: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != PDTFunction) {
    messerr("CPascal__execFunctionReal: L'identifiant '%s' n'a pas le type fonction, mais le type %s.", ident, dvalt.type.toString(&dvalt.type));
    return -2;
  }

  if (dvalt.type.val.func.param_nb != 0) {
    messerr("CPascal__execFunctionReal: L'identifiant '%s' est une fonction à paramètre, or elle devrait être sans paramètre.", ident);
    return -3;
  }

  if (dvalt.type.val.func.type->type != PDTReal) {
    messerr("CPascal__execFunctionReal: L'identifiant '%s' est une fonction dont la valeur de retour n'est pas un réel, mais de type %s.", ident, dvalt.type.val.func.type->toString(dvalt.type.val.func.type));
    return -5;
  }

    
  // PAS TERRIBLE
  tabdvaltypeuser = this->tabdvaltypeuser;
    
  CPexpr *call;
  call = CPexpr_make(0U,0U,0U,0U,0U,0U);
  call->type = CPexpr_PCall;
  call->val.upcall.ident = strcopy(ident);
  call->val.upcall.args_nb = 0;

  pevalt e;
  ret = call->r_evaluate(call, this -> env, this -> mem, &e);
  if (ret < 0) {
    messerr("CPascal__execFunctionReal: Une erreur s'est produite pendant l'exécution de la fonction '%s'.", ident);
    return -6;
  }

  *res_ref = e.val.val.r;    
    
  return 0;
};







// Exécution d'une fonction qui retourne une chaîne de caratère.
int CPascal__execFunctionString(CPascal * this, const char *const ident, const char ** res_ref) {
  pdvalt dvalt;
  int ret;
    
  ret = penvlookup(this->env, ident, &dvalt);
  if (ret < 0) {
    messerr("CPascal__execFunctionString: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != PDTFunction) {
    messerr("CPascal__execFunctionString: L'identifiant '%s' n'a pas le type fonction, mais le type %s.", ident, dvalt.type.toString(&dvalt.type));
    return -2;
  }

  if (dvalt.type.val.func.param_nb != 0) {
    messerr("CPascal__execFunctionString: L'identifiant '%s' est une fonction à paramètre, or elle devrait être sans paramètre.", ident);
    return -3;
  }

  if (dvalt.type.val.func.type->type != PDTString) {
    messerr("CPascal__execFunctionBoolean: L'identifiant '%s' est une fonction dont la valeur de retour n'est pas une chaîne de caractère, mais de type %s.", ident, dvalt.type.val.func.type->toString(dvalt.type.val.func.type));
    return -5;
  }

    
  // PAS TERRIBLE
  tabdvaltypeuser = this->tabdvaltypeuser;
    
  CPexpr *call;
  call = CPexpr_make(0U,0U,0U,0U,0U,0U);
  call->type = CPexpr_PCall;
  call->val.upcall.ident = strcopy(ident);
  call->val.upcall.args_nb = 0;

  pevalt e;
  ret = call->r_evaluate(call, this -> env, this -> mem, &e);
  if (ret < 0) {
    messerr("CPascal__execFunctionString: Une erreur s'est produite pendant l'exécution de la fonction '%s'.", ident);
    return -6;
  }

  *res_ref = e.val.val.str;    
    
  return 0;
};







void CPascal__stack_push_int(CPascal * this, int a) {
  pevalt * e = pevalt_make();
  e -> type.type = PETInteger;
  e -> val.val.i = a;
  pascal_stack_push(this -> stack, e);
};

void CPascal__stack_push_string(CPascal * this, const char * str) {
  pevalt * e = pevalt_make();
  e -> type.type = PETString;
  e -> val.val.str = strcopy(str);
  pascal_stack_push(this -> stack, e);
};

#endif 
