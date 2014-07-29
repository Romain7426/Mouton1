#include "global.hpp"
#include "pascal.hpp"
#include "pascal/pascal.prog.hpp"




// Les trucs du lexer et du parser.
extern FILE * yypascalout;
extern int yypascalparse(void);
extern void yypascalrestart(FILE * new_file);
extern void yypascallexerinit(void);
extern CPprog * prog;


// Le constructeur.
// Le code d'erreur rend un nombre négatif en cas d'erreur.
CPascal::CPascal(const char * const filename) : filename(strcopy(filename)), prog_exec(NULL) {
  printf("Constructeur CPascal::CPascal(%s)\n", this -> filename);                     

  char * reelname;
  char * lexing;
  static const char * const clexing = ".lexing.out";
  static const unsigned int pastaille = strlen(PASCALDIR);
  static const unsigned int lextaille = strlen(clexing);
  unsigned int taille;
  int ret;
  FILE * yypascalin;
 
 
  if (filename == NULL) {
    messerr("Constructeur de CPascal: le nom de fichier est le pointeur NULL.");
    code_erreur = -1;
    assert(false);
    //throw ((void *) NULL);
    return;
  }
  else if (filename[0] == '\0') {
    messerr("Constructeur de CPascal: le nom de fichier est la chaîne vide.");
    code_erreur = -2;
    assert(false);
    //throw ((void *) NULL);
    return;
  }  
  else
    printf("  nom de fichier correct!\n");
 
  message("Constructeur de CPascal: appel avec filename = '%s'.", filename);
 
#if 1
  reelname = STRCAT2_(PASCALDIR, filename);
  lexing = STRCAT3_(LOGDIR, filename, clexing);
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
    delete [] reelname;
    delete [] lexing;
    code_erreur = -3;
    assert(false);
    //throw ((void *) NULL);
    return;
  }
 
 
  messerr("HEREHERE: reelname: %s ; lexing: %s", reelname, lexing);
  // Ouverture des flux d'entrées et de sorties pour le lexer.
  yypascalout = fopen(lexing, "w");
  if (yypascalout == NULL) {
    messerr("Constructeur de CPascal: Impossible d'ouvrir en écriture le fichier '%s' pour les sorties du lexer.", lexing);
    delete [] reelname;
    delete [] lexing;
    code_erreur = -4;
    assert(false);
    //throw ((void *) NULL);
    return;
  }
 
  yypascalin = fopen(reelname, "r");
  if (yypascalin == NULL) {
    messerr("Constructeur de CPascal: Impossible d'ouvrir en lecture le fichier '%s'.", reelname);
    fclose(yypascalout);
    delete [] reelname;
    delete [] lexing;
    code_erreur = -5;
    assert(false);
    //throw ((void *) NULL);
    return;
  }
 
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
  delete [] reelname;
  delete [] lexing;
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
    code_erreur = -6;
    assert(false);
    //throw ((void *) NULL);
    return;
  }
 
  if (prog == NULL) {
    messerr("Constructeur de CPascal: Erreur interne: L'analyse du fichier '%s' a réussie, mais elle a produit un programme NULL.", filename);
    code_erreur = -7;
    assert(false);
    //throw ((void *) NULL);
    return;
  }
  
  pmessage("Affichage du programme.");
  pmessage("-----------------------");
  pmessage(prog->toString());
  pmessage("-----------------------");
 
  // Initialisation des variables.
  this->env = env0;
  this->mem = mem0;
  this -> stack = pascal_stack_make();
 
  // Mise en place du tableau de type.
  tabdvaltypeuser = tabdvaltypeuser0;
  // Exécution du script.
  ret = prog->execute(this->env, this->mem);
  // On récupère le tableau de type.
  this->tabdvaltypeuser = tabdvaltypeuser;
  // On n'a plus besoin de prog après.
  prog = NULL;
  if (ret < 0) {
    messerr("Constructeur de CPascal: L'exécution de l'initialisation du fichier de script PascalML '%s'a merdé.", filename);
    code_erreur = -8;
    assert(false);
    //throw ((void *) NULL);
    return;
  }
  
  message("Constructeur de CPascal: C'est bon, l'initialisation du fichier de script pascalml '%s' s'est bien passée.", filename);
}




// Le destructeur.
CPascal::~CPascal(void) {
  // Il faut fermer les flux de message d'erreur,
  // et détruire l'environnement,
  // et détruire la mémoire.
  // On ne détruit pas le nom du fichier car il ne nous appartient pas.

  pascal_stack_free(stack);
  //penvdel(this->env);
  //ptabdvaltypeuser_del(tabdvaltypeuser);
  //pmemdel(this->mem);
  pmessend();
}
 




// Les fonctions de recherche.
// Elles retournent toute un code d'erreur. 
// Il y a erreur si négatif.


// La lecture.

// La recherhe d'un booléen.
int CPascal::getBoolean(const char *const ident, bool &res) {
  pdvalt dvalt;
  psval sval;
  int ret;
    
  ret = penvlookup(this->env, ident, dvalt);
  if (ret < 0) {
    messerr("CPascal::getBoolean: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != pdvaltype::PDTBoolean) {
    messerr("CPascal::getBoolean: L'identifiant '%s' n'a pas le type booléen, mais le type %s.", ident, dvalt.type.toString());
    return -2;
  }

  ret = pmemread(this->mem, dvalt.val.val.b, sval);
  if (ret < 0) {
    messerr("CPascal::getBoolean: L'identifiant '%s' n'a pas pu être trouvé dans la mémoire.", ident);
    return -3;
  }
    
  res = sval.b;
  return 0;
}


// La fonction de recherche d'un entier dans l'environnement.
int CPascal::getInteger(const char *const ident, int &res) {
  pdvalt dvalt;
  psval sval;
  int ret;
    
  ret = penvlookup(this->env, ident, dvalt);
  if (ret < 0) {
    messerr("CPascal::getInteger: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != pdvaltype::PDTInteger) {
    messerr("CPascal::getInteger: L'identifiant '%s' n'a pas le type entier, mais le type %s.", ident, dvalt.type.toString());
    return -2;
  }

  ret = pmemread(this->mem, dvalt.val.val.i, sval);
  if (ret < 0) {
    messerr("CPascal::getInteger: L'identifiant '%s' n'a pas pu être trouvé dans la mémoire.", ident);
    return -3;
  }
    
  res = sval.i;
  return 0;
}


       
// La fonction de recherche d'un intervalle dans l'environnement.
int CPascal::getSubrange(const char *const ident, int &res) {
  pdvalt dvalt;
  psval sval;
  int ret;
    
  ret = penvlookup(this->env, ident, dvalt);
  if (ret < 0) {
    messerr("CPascal::getSubrange: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != pdvaltype::PDTSubrange) {
    messerr("CPascal::getSubrange: L'identifiant '%s' n'a pas le type intervalle, mais le type %s.", ident, dvalt.type.toString());
    return -2;
  }

  ret = pmemread(this->mem, dvalt.val.val.s, sval);
  if (ret < 0) {
    messerr("CPascal::getSubrange: L'identifiant '%s' n'a pas pu être trouvé dans la mémoire.", ident);
    return -3;
  }
    
  res = sval.i;
  return 0;
}



// La fonction de recherche d'un réel dans l'environnement.
int CPascal::getReal(const char *const ident, corps &res) {
  pdvalt dvalt;
  psval sval;
  int ret;
    
  ret = penvlookup(this->env, ident, dvalt);
  if (ret < 0) {
    messerr("CPascal::getReal: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != pdvaltype::PDTReal) {
    messerr("CPascal::getReal: L'identifiant '%s' n'a pas le type réel, mais le type %s.", ident, dvalt.type.toString());
    return -2;
  }

  ret = pmemread(this->mem, dvalt.val.val.r, sval);
  if (ret < 0) {
    messerr("CPascal::getReal: L'identifiant '%s' n'a pas pu être trouvé dans la mémoire.", ident);
    return -3;
  }
    
  res = sval.r;
  return 0;
}




       
// La fonction de recherche d'une chaîne de caractères dans l'environnement.
int CPascal::getString(const char *const ident, const char *&res) {
  pdvalt dvalt;
  psval sval;
  int ret;
    
  ret = penvlookup(this->env, ident, dvalt);
  if (ret < 0) {
    messerr("CPascal::getString: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != pdvaltype::PDTString) {
    messerr("CPascal::getString: L'identifiant '%s' n'a pas le type chaîne de caractère, mais le type %s.", ident, dvalt.type.toString());
    return -2;
  }

  ret = pmemread(this->mem, dvalt.val.val.str, sval);
  if (ret < 0) {
    messerr("CPascal::getString: L'identifiant '%s' n'a pas pu être trouvé dans la mémoire.", ident);
    return -3;
  }
    
  res = sval.str;
  return 0;
}







// L'écriture.

// La recherhe d'un booléen.
int CPascal::setBoolean(const char *const ident, bool what) {
  pdvalt dvalt;
  psval sval;
  int ret;
    
  ret = penvlookup(this->env, ident, dvalt);
  if (ret < 0) {
    messerr("CPascal::setBoolean: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != pdvaltype::PDTBoolean) {
    messerr("CPascal::setBoolean: L'identifiant '%s' n'a pas le type booléen, mais le type %s.", ident, dvalt.type.toString());
    return -2;
  }

  sval.b = what;
  ret = pmemwrite(this->mem, dvalt.val.val.b, sval);
  if (ret < 0) {
    messerr("CPascal::setBoolean: L'identifiant '%s' n'a pas pu être trouvé dans la mémoire.", ident);
    return -3;
  }
    
  return 0;
}





// La fonction de recherche d'un entier dans l'environnement.
int CPascal::setInteger(const char *const ident, int what) {
  pdvalt dvalt;
  psval sval;
  int ret;
    
  ret = penvlookup(this->env, ident, dvalt);
  if (ret < 0) {
    messerr("CPascal::setInteger: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != pdvaltype::PDTInteger) {
    messerr("CPascal::setInteger: L'identifiant '%s' n'a pas le type entier, mais le type %s.", ident, dvalt.type.toString());
    return -2;
  }

  sval.i = what;
  ret = pmemwrite(this->mem, dvalt.val.val.i, sval);
  if (ret < 0) {
    messerr("CPascal::setInteger: L'identifiant '%s' n'a pas pu être trouvé dans la mémoire.", ident);
    return -3;
  }
    
  return 0;
}






// La fonction de recherche d'un intervalle dans l'environnement.
int CPascal::setSubrange(const char *const ident, int what) {
  pdvalt dvalt;
  psval sval;
  int ret;
    
  ret = penvlookup(this->env, ident, dvalt);
  if (ret < 0) {
    messerr("CPascal::setSubrange: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != pdvaltype::PDTSubrange) {
    messerr("CPascal::setSubrange: L'identifiant '%s' n'a pas le type intervalle, mais le type %s.", ident, dvalt.type.toString());
    return -2;
  }

  if (what < dvalt.type.val.s.min) {
    messerr("CPascal::setSubrange: L'identifiant '%s' a bien été trouvé dans la mémoire, mais il n'a pas le bon type. En effet c'est un intervalle entier et la valeur passée en paramètre est trop petite (intervalle = [ %d ; %d ], valeur = %d).", ident, dvalt.type.val.s.min, dvalt.type.val.s.max, what);
    return -4;
  }
  if (what > dvalt.type.val.s.max) {
    messerr("CPascal::setSubrange: L'identifiant '%s' a bien été trouvé dans la mémoire, mais il n'a pas le bon type. En effet c'est un intervalle entier et la valeur passée en paramètre est trop grande (intervalle = [ %d ; %d ], valeur = %d).", ident, dvalt.type.val.s.min, dvalt.type.val.s.max, what);
    return -5;
  }
  sval.i = what;
  ret = pmemwrite(this->mem, dvalt.val.val.s, sval);
  if (ret < 0) {
    messerr("CPascal::setSubrange: L'identifiant '%s' n'a pas pu être trouvé dans la mémoire.", ident);
    return -3;
  }
    
  return 0;
}







// La fonction de recherche d'un réel dans l'environnement.
int CPascal::setReal(const char *const ident, corps what) {
  pdvalt dvalt;
  psval sval;
  int ret;
    
  ret = penvlookup(this->env, ident, dvalt);
  if (ret < 0) {
    messerr("CPascal::setReal: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != pdvaltype::PDTReal) {
    messerr("CPascal::setReal: L'identifiant '%s' n'a pas le type réel, mais le type %s.", ident, dvalt.type.toString());
    return -2;
  }

  sval.r = what;
  ret = pmemwrite(this->mem, dvalt.val.val.r, sval);
  if (ret < 0) {
    messerr("CPascal::setReal: L'identifiant '%s' n'a pas pu être trouvé dans la mémoire.", ident);
    return -3;
  }
    
  return 0;
}








// La fonction de recherche d'une chaîne de caractères dans l'environnement.
int CPascal::setString(const char *const ident, const char * const what) {
  pdvalt dvalt;
  psval sval;
  int ret;
    
  ret = penvlookup(this->env, ident, dvalt);
  if (ret < 0) {
    messerr("CPascal::setString: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != pdvaltype::PDTString) {
    messerr("CPascal::setString: L'identifiant '%s' n'a pas le type chaîne de caractère, mais le type %s.", ident, dvalt.type.toString());
    return -2;
  }

  sval.str = strcopy(what);
  ret = pmemwrite(this->mem, dvalt.val.val.str, sval);
  if (ret < 0) {
    messerr("CPascal::setString: L'identifiant '%s' n'a pas pu être trouvé dans la mémoire.", ident);
    return -3;
  }
    
  return 0;
}








// La fonction d'exécution d'une procédure.
int CPascal::execProcedure(const char * const ident) {
  pdvalt dvalt;
  int ret;
    
  ret = penvlookup(this->env, ident, dvalt);
  if (ret < 0) {
    messerr("CPascal::execProcedure: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != pdvaltype::PDTProcedure) {
    messerr("CPascal::execProcedure: L'identifiant '%s' n'a pas le type procédure, mais le type %s.", ident, dvalt.type.toString());
    return -2;
  }
  
  if (dvalt.type.val.proc.params != NULL) {
    messerr("CPascal::execProcedure: L'identifiant '%s' est une procédure à paramètre, or elle devrait être sans paramètre.", ident);
    return -3;
  }
    
  tabdvaltypeuser = this->tabdvaltypeuser;
  // !!!! PAS BIEN !!! >:-(
  ret = dvalt.type.val.proc.corps->execute(dvalt.type.val.proc.env, this->mem);
  //this->tabdvaltypeuser = tabdvaltypeuser;
  //tabdvaltypeuser = tabdvaltypeuser0;
  if (ret < 0) {
    messerr("CPascal::execProcedure: Lors de l'exécution de la procédure '%s', une erreur s'est produite.", ident);
    return -4;
  }
    
  return 0;
}




// La fonction d'exécution d'une procédure.
int CPascal::execProcedure_step(const char *const ident) {
  pdvalt dvalt;
  int ret;
    
  ret = penvlookup(this->env, ident, dvalt);
  if (ret < 0) {
    messerr("CPascal::execProcedure_step: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != pdvaltype::PDTProcedure) {
    messerr("CPascal::execProcedure_step: L'identifiant '%s' n'a pas le type procédure, mais le type %s.", ident, dvalt.type.toString());
    return -2;
  }
  
  if (dvalt.type.val.proc.params != NULL) {
    messerr("CPascal::execProcedure_step: L'identifiant '%s' est une procédure à paramètre, or elle devrait être sans paramètre.", ident);
    return -3;
  }
    

  //tabdvaltypeuser = this -> tabdvaltypeuser;

  // !!!! PAS BIEN !!! >:-(
  //ret = dvalt.type.val.proc.corps->execute_step(dvalt.type.val.proc.env, this->mem, prog_this);
  this -> env_exec = dvalt.type.val.proc.env -> copy();
  prog_exec = dvalt.type.val.proc.corps;
    
  return 0;
}








int CPascal::next_step(bool &fini_huh) {
  fini_huh = false;

  if (prog_exec == NULL) {
    fini_huh = true;
    return 0;
  }

  int ret;
  CPprog * futur;

  ret = prog_exec -> execute_step(this -> env_exec, this -> mem, this -> stack, futur);
  
  prog_exec = futur;


  if (ret < 0) {
    messerr("CPascal::next_step: Lors de l'exécution du code, une erreur s'est produite: ret = %d", ret);
  }

  return ret;
}











// La fonction d'exécution d'une fonction.
// Il y a une fonction par type de valeur de retour.

// Exécution d'une fonction booléenne.
int CPascal::execFunctionBoolean(const char *const ident, bool &res) {
  pdvalt dvalt;
  int ret;
    
  ret = penvlookup(this->env, ident, dvalt);
  if (ret < 0) {
    messerr("CPascal::execFunctionBoolean: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != pdvaltype::PDTFunction) {
    messerr("CPascal::execFunctionBoolean: L'identifiant '%s' n'a pas le type fonction, mais le type %s.", ident, dvalt.type.toString());
    return -2;
  }

  if (dvalt.type.val.func.params != NULL) {
    messerr("CPascal::execFunctionBoolean: L'identifiant '%s' est une fonction à paramètre, or elle devrait être sans paramètre.", ident);
    return -3;
  }

  if (dvalt.type.val.func.type->type != pdvaltype::PDTBoolean) {
    messerr("CPascal::execFunctionBoolean: L'identifiant '%s' est une fonction dont la valeur de retour n'est pas un booléen, mais de type %s.", ident, dvalt.type.val.func.type->toString());
    return -5;
  }

    
  // PAS TERRIBLE
  tabdvaltypeuser = this->tabdvaltypeuser;
    
  CPexpr *call;
  call = new CPexpr(0U,0U,0U,0U,0U,0U);
  call->type = CPexpr::PCall;
  call->val.upcall.ident = strcopy(ident);
  call->val.upcall.args = NULL;

  pevalt e;
  ret = call->r_evaluate(env, mem, e);
  if (ret < 0) {
    messerr("CPascal::execFunctionBoolean: Une erreur s'est produite pendant l'exécution de la fonction '%s'.", ident);
    return -6;
  }

  res = e.val.val.b;    
    
  return 0;
}







// Exécution d'une fonction entière.
int CPascal::execFunctionInteger(const char *const ident, int &res) {
  pdvalt dvalt;
  int ret;
    
  ret = penvlookup(this->env, ident, dvalt);
  if (ret < 0) {
    messerr("CPascal::execFunctionInteger: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != pdvaltype::PDTFunction) {
    messerr("CPascal::execFunctionInteger: L'identifiant '%s' n'a pas le type fonction, mais le type %s.", ident, dvalt.type.toString());
    return -2;
  }

  if (dvalt.type.val.func.params != NULL) {
    messerr("CPascal::execFunctionInteger: L'identifiant '%s' est une fonction à paramètre, or elle devrait être sans paramètre.", ident);
    return -3;
  }

  if (dvalt.type.val.func.type->type != pdvaltype::PDTInteger) {
    messerr("CPascal::execFunctionInteger: L'identifiant '%s' est une fonction dont la valeur de retour n'est pas un entier, mais de type %s.", ident, dvalt.type.val.func.type->toString());
    return -5;
  }

    
  // PAS TERRIBLE
  tabdvaltypeuser = this->tabdvaltypeuser;
    
  CPexpr *call;
  call = new CPexpr(0U,0U,0U,0U,0U,0U);
  call->type = CPexpr::PCall;
  call->val.upcall.ident = strcopy(ident);
  call->val.upcall.args = NULL;

  pevalt e;
  ret = call->r_evaluate(this->env, this->mem, e);
  if (ret < 0) {
    messerr("CPascal::execFunctionInteger: Une erreur s'est produite pendant l'exécution de la fonction '%s'.", ident);
    return -6;
  }

  res = e.val.val.i;

  return 0;
}







// Exécution d'une fonction scalaire.
int CPascal::execFunctionSubrange(const char *const ident, int &res) {
  pdvalt dvalt;
  int ret;
    
  ret = penvlookup(this->env, ident, dvalt);
  if (ret < 0) {
    messerr("CPascal::execFunctionSubrange: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != pdvaltype::PDTFunction) {
    messerr("CPascal::execFunctionBoolean: L'identifiant '%s' n'a pas le type fonction, mais le type %s.", ident, dvalt.type.toString());
    return -2;
  }

  if (dvalt.type.val.func.params != NULL) {
    messerr("CPascal::execFunctionBoolean: L'identifiant '%s' est une fonction à paramètre, or elle devrait être sans paramètre.", ident);
    return -3;
  }

  if (dvalt.type.val.func.type->type != pdvaltype::PDTSubrange) {
    messerr("CPascal::execFunctionBoolean: L'identifiant '%s' est une fonction dont la valeur de retour n'est pas un intervalle entier, mais de type %s.", ident, dvalt.type.val.func.type->toString());
    return -5;
  }

    
  // PAS TERRIBLE
  tabdvaltypeuser = this->tabdvaltypeuser;
    
  CPexpr *call;
  call = new CPexpr(0U,0U,0U,0U,0U,0U);
  call->type = CPexpr::PCall;
  call->val.upcall.ident = strcopy(ident);
  call->val.upcall.args = NULL;

  pevalt e;
  ret = call->r_evaluate(env, mem, e);
  if (ret < 0) {
    messerr("CPascal::execFunctionSubrange: Une erreur s'est produite pendant l'exécution de la fonction '%s'.", ident);
    return -6;
  }

  res = e.val.val.b;    
    
  return 0;
}







// Exécution d'une fonction numérique.
int CPascal::execFunctionReal(const char *const ident, corps &res) {
  pdvalt dvalt;
  int ret;
    
  ret = penvlookup(this->env, ident, dvalt);
  if (ret < 0) {
    messerr("CPascal::execFunctionReal: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != pdvaltype::PDTFunction) {
    messerr("CPascal::execFunctionReal: L'identifiant '%s' n'a pas le type fonction, mais le type %s.", ident, dvalt.type.toString());
    return -2;
  }

  if (dvalt.type.val.func.params != NULL) {
    messerr("CPascal::execFunctionReal: L'identifiant '%s' est une fonction à paramètre, or elle devrait être sans paramètre.", ident);
    return -3;
  }

  if (dvalt.type.val.func.type->type != pdvaltype::PDTReal) {
    messerr("CPascal::execFunctionReal: L'identifiant '%s' est une fonction dont la valeur de retour n'est pas un réel, mais de type %s.", ident, dvalt.type.val.func.type->toString());
    return -5;
  }

    
  // PAS TERRIBLE
  tabdvaltypeuser = this->tabdvaltypeuser;
    
  CPexpr *call;
  call = new CPexpr(0U,0U,0U,0U,0U,0U);
  call->type = CPexpr::PCall;
  call->val.upcall.ident = strcopy(ident);
  call->val.upcall.args = NULL;

  pevalt e;
  ret = call->r_evaluate(env, mem, e);
  if (ret < 0) {
    messerr("CPascal::execFunctionReal: Une erreur s'est produite pendant l'exécution de la fonction '%s'.", ident);
    return -6;
  }

  res = e.val.val.r;    
    
  return 0;
}







// Exécution d'une fonction qui retourne une chaîne de caratère.
int CPascal::execFunctionString(const char *const ident, const char *&res) {
  pdvalt dvalt;
  int ret;
    
  ret = penvlookup(this->env, ident, dvalt);
  if (ret < 0) {
    messerr("CPascal::execFunctionString: L'identifiant '%s' n'a pas pu être trouvé dans l'environnement.", ident);
    return -1;
  }
    
  if (dvalt.type.type != pdvaltype::PDTFunction) {
    messerr("CPascal::execFunctionString: L'identifiant '%s' n'a pas le type fonction, mais le type %s.", ident, dvalt.type.toString());
    return -2;
  }

  if (dvalt.type.val.func.params != NULL) {
    messerr("CPascal::execFunctionString: L'identifiant '%s' est une fonction à paramètre, or elle devrait être sans paramètre.", ident);
    return -3;
  }

  if (dvalt.type.val.func.type->type != pdvaltype::PDTString) {
    messerr("CPascal::execFunctionBoolean: L'identifiant '%s' est une fonction dont la valeur de retour n'est pas une chaîne de caractère, mais de type %s.", ident, dvalt.type.val.func.type->toString());
    return -5;
  }

    
  // PAS TERRIBLE
  tabdvaltypeuser = this->tabdvaltypeuser;
    
  CPexpr *call;
  call = new CPexpr(0U,0U,0U,0U,0U,0U);
  call->type = CPexpr::PCall;
  call->val.upcall.ident = strcopy(ident);
  call->val.upcall.args = NULL;

  pevalt e;
  ret = call->r_evaluate(env, mem, e);
  if (ret < 0) {
    messerr("CPascal::execFunctionString: Une erreur s'est produite pendant l'exécution de la fonction '%s'.", ident);
    return -6;
  }

  res = e.val.val.str;    
    
  return 0;
}







void CPascal::stack_push_int(int a) {
  pevalt * e = new pevalt;
  e -> type.type = pevaltype::PETInteger;
  e -> val.val.i = a;
  pascal_stack_push(stack, e);
}

void CPascal::stack_push_string(const char * str) {
  pevalt * e = new pevalt;
  e -> type.type = pevaltype::PETString;
  e -> val.val.str = strcopy(str);
  pascal_stack_push(stack, e);
}

