#ifndef PASCAL_PROG_HPP
#define PASCAL_PROG_HPP


#include "pascal/pascal.tools.hpp"
#include "pascal/pascal.mem.hpp"
#include "pascal/pascal.env.hpp"
#include "pascal/pascal.expr.hpp"



/*
 * Enfin!!!!
 * La classe qui va définir ce qu'est qu'un programme Pascal!!!!
 */

class CPprog;
enum direction {HAUT, BAS, GAUCHE, DROITE};
enum methode {ABSOLU, RELATIF};



class CPprog {
public:
  enum etype {PStop, PSkip, PSeq, PIf, PWhile, PFor, PRepeat, PBegin, PVar, PConst, PAffectation, PWrite, PWriteln, PRead, PReadln, PType, PNew, PCall, PMusique, PWait, PHalt, PRestart, PFondu, PRecObjet, PRecArme, PSupObjet, PCarte, PSetPosition, PSetPositionZ, PDeplacer, PDeplacerZ, PSetHerosPosition, PSetHerosPositionZ, PHerosDeplacer, PHerosDeplacerZ, PSetCameraPosition, PCameraDeplacer, PCameraRotate, PCameraSolidariser, PCameraDesolidariser, PCameraDefaut, PCameraZoom, PFrapper, PAjouterAnime, PAjouterNonAnime, PSetTemps, PSetOrientation, PWaitFor, PBloquerTemps, PDebloquerTemps, PCarteZ,
              PExprStack, PIfStack, PWhileStack, PForStack, PConstStack, PAffectationStack, PWritelnStack, PReadlnStack, PCallStack, PMusiqueStack, PWaitStack, PFonduStack, PRecArmeStack, PSupObjetStack, PCarteStack, PCarteZStack, PSetPositionStack, PSetPositionZStack, PDeplacerStack, PSetCameraPositionStack, PCameraRotateStack, PCameraZoomStack, PFrapperStack, PAjouterAnimeStack, PAjouterNonAnimeStack, PSetTempsStack, PSetOrientationStack, PWaitForStack};


  union utype {

    struct SPSeq {
      CPprog *p1, *p2;
    };
    struct SPIf {
      CPexpr *b;
      CPprog *p, *q;
    };
    struct SPWhile {
      CPexpr *b;
      CPprog *p;
    };
    struct SPFor {
      char *i;
      CPexpr *e1, *e2;
      CPprog *p;
    };
    struct SPRepeat {
      CPprog *p;
      CPexpr *b;
    };
    struct SPBegin {
      CPprog *p;
    };
    struct SPVar {
      char * nom;
      //pevaltype t;
      pdvaltype t;
    };
    
    struct SPConst {
      char *nom;
      //pevalt val;
      CPexpr *val;
    };
    struct SPAffectation {
      CPexpr *lval;
      CPexpr *e;
    };
    struct SPWrite {
      pliste<CPexpr> *le;
    };
    struct SPWriteln {
      pliste<CPexpr> *le;
    };
    struct SPRead {
      pliste<CPexpr> *llval;
    };
    struct SPReadln {
      pliste<CPexpr> *llval;
    };
    struct SPType {
      char *ident;
      pdvaltype dvaltype;
    };
    struct SPNew {
      char *ident;
    };
    struct SPCall {
      char *ident;
      class pliste<CPexpr> *args;
    };

    struct SPMusique {
      CPexpr *musique;
    };
    struct SPWait {
      CPexpr *nbpasses;
    };
    struct SPFondu {
      CPexpr *couleur;
    };
    struct SPCarte {
      //const char * nom;
      CPexpr *nom, *x, *y, *direction;
    };
    struct SPRecObjet {
      char * nom;
    };
    struct SPRecArme {
      //const char * nom;
      CPexpr *nom;
    };
    struct SPSupObjet {
      //const char * nom;
      CPexpr * nom;
    };

    struct SPSetPosition {
      //const char * nom;
      //corps x, y;
      //enum methode relatif;
      //enum direction dir;
      CPexpr *nom, *x, *y, *relatif; // *dir;
    };
    struct SPSetPositionZ : public SPSetPosition {
      //corps z;
      CPexpr *z;
    };
    struct SPDeplacer : public SPSetPosition {
    };
    struct SPDeplacerZ : public SPSetPositionZ {
    };
    struct SPSetHerosPosition {
      corps x, y;
      enum methode relatif;
      enum direction dir;
    };
    struct SPSetHerosPositionZ : public SPSetHerosPosition {
      corps z;
    };
    struct SPHerosDeplacer : public SPSetHerosPosition {
    };
    struct SPHerosDeplacerZ : public SPSetHerosPositionZ {
    };
    struct SPSetCameraPosition {
      //corps x, y, z;
      //enum methode relatif;
      CPexpr *x, *y, *z, *relatif;
    };
    struct SPCameraDeplacer : public SPSetCameraPosition {
    };
    struct SPCameraRotate {
      //corps angle_x, angle_y, angle_z;
      //enum methode relatif;
      CPexpr *angle_x, *angle_y, *angle_z, *relatif;
    };
    struct SPCameraZoom {
      //corps coeff;
      CPexpr *coeff;
    };
    struct SPFrapper {
      CPexpr *nom;
    };
    struct SPAjouterAnime {
      CPexpr *nom, *fichier;
    };
    struct SPAjouterNonAnime {
      CPexpr *nom, *fichier;
    };
    struct SPSetTemps {
      CPexpr *temps;
    };
    struct SPSetOrientation {
      CPexpr *orientation, *nom;
    };
    struct SPWaitFor {
      CPexpr *nom;
    };
    struct SPCarteZ : public SPCarte {
      CPexpr *z;
    };
    struct SPExprStack {
      pascal_expr_futur_t * futur_expr;
    };
     
    
    

             
    SPSeq upseq;
    SPIf upif;
    SPWhile upwhile;
    SPFor upfor;
    SPRepeat uprepeat;
    SPBegin upbegin;
    SPVar upvar;
    SPConst upconst;
    SPAffectation upaffectation;
    SPWrite upwrite;
    SPWriteln upwriteln;
    SPRead upread;
    SPReadln upreadln;
    SPType uptype;
    SPNew upnew;
    SPCall upcall;
    SPMusique upmusique;
    SPWait upwait;
    SPFondu upfondu;
    SPCarte upcarte;
    SPRecObjet uprecobjet;
    SPRecArme uprecarme;
    SPSupObjet upsupobjet;
    SPSetPosition upsetpos;
    SPSetPositionZ upsetposz;
    SPDeplacer updeplacer;
    SPDeplacerZ updeplacerz;
    SPSetHerosPosition upsetherospos;
    SPSetHerosPositionZ upsetherosposz;
    SPHerosDeplacer upherosdeplacer;
    SPHerosDeplacerZ upherosdeplacerz;
    SPSetCameraPosition upsetcamerapos;
    SPCameraDeplacer upcameradeplacer;
    SPCameraRotate upcamerarotate;
    SPCameraZoom upcamerazoom;
    SPFrapper upfrapper;
    SPAjouterAnime upajouteranime;
    SPAjouterNonAnime upajouternonanime;
    SPSetTemps upsettemps;
    SPSetOrientation upsetorientation;
    SPWaitFor upwaitfor;
    SPCarteZ upcartez;
    SPExprStack upexprstack;
  };



  enum etype type;
  union utype val;


  
public:
  // La vrai fonction d'exécution.
  // Elle rend un code d'erreur selon les conventions usuelles.
  // Contrairement aux expressions, une instruction modifie l'environnement et la mémoire.
  // Ainsi, là on n'a pas un const, mais carrément un passage par référence.
  // Cependant, lors d'un BEGIN, l'environnement n'est pas modifié, seul la mémoire
  // peut l'être. Toutes les variables qui y sont déclarées sont locales 
  // et sont désalloués à la fin du bloc.
  // Toutefois, en Pascal, le begin end au milieu d'un bloc n'a pas trop de sens 
  // car la définition de variables locales n'est pas trop possible.
  // C'est donc juste global et lors de la définition de fonction.
  // Aussi, on peut à priori définir des procédures locales.
  int execute(penv &env, pmem &mem);

  //int execute_step(penv &env, pmem &mem, CPprog * &futur);
  int execute_step(penv &env, pmem &mem, pascal_stack_t * stack, CPprog * &futur);

  // La position dans le code de cette commande.
  ppos position;

  // Constructeurs.
  CPprog(unsigned int deb_ligne, unsigned int fin_ligne, unsigned int deb_car, unsigned int fin_car, unsigned int deb_car_tot, unsigned int fin_car_tot) : position(pascal_position(deb_ligne, fin_ligne, deb_car, fin_car, deb_car_tot, fin_car_tot)) { }

  CPprog(ppos position) : position(position) { }


  // La fonction de conversion en chaîne de caractère.
  char * toString(void) const;

  // Un programme Pascal ne possède pas de réponse si ce n'est l'état de la mémoire et des E/S.
  // Code d'erreur comme d'habitude.
  int execute(void);

};




struct pascal_prog_futur_cell_t;
typedef pliste<pascal_prog_futur_cell_t> pascal_prog_futur_t;

struct pascal_prog_futur_cell_t {
  CPprog::etype type;
  pascal_prog_futur_t * futur1;
  pascal_prog_futur_t * futur2;
  pdvaltype dvaltype;
  char * str1;
  int n1;
};



extern bool pascal_prog_compile(const CPprog * prog, pascal_prog_futur_t * &futur);



extern bool futur_expr_to_prog(pascal_expr_futur_t * futur_expr, CPprog * &futur_prog);
extern bool futur_expr_to_futur_prog(pascal_expr_futur_t * futur_expr, pascal_prog_futur_t * &futur_prog);




extern const char * cprog_type_string(enum CPprog::etype type);




#endif /* PASCAL_PROG_HPP */
