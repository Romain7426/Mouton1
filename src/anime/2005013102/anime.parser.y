%{ /* Header */
#include <stdlib.h>
#include "anime.global.hpp"
/*
const extern int get_nb_lignes(void);
const extern int get_nb_chars(void);
const extern int get_nb_chars_tot(void);
const extern int get_yyleng(void);
const extern char * get_yytext(void);
extern int yylex(void);
*/
const static void yyerror(char s[]);


#define VERIF_NOT_NULL(a,b) if (a == NULL) {yyerror("Manque de mémoire."); return b;}


 CBonhomme *bongars;


#define MAXMEMBRE 32
static memdesc memtab[MAXMEMBRE];
static int memnbelts = 0;
const static int memlookup(char *nom) {
  for (int i = 0; i < memnbelts; i++) {
    if (strcmp(nom, memtab[i].nom) == 0) {
      return i;
    }
  }
  return -1;
}

const static void memempiler(CPantin *pere, liste *fils) {
  filsdesc *temp;
  while (fils != NULL) {
    int j;
    temp = (filsdesc*) fils->contenu;

    if ((j = memlookup(temp->qui)) < 0) {
      yyerror(strcat(strcat("Le membre \"", temp->qui), " n'a pas ete defini. On continue néanmoins.\n"));
    }
    
    else {
      CPantin *p = new CPantin;
      p->AjouterMembre(memtab[j].image, temp->x, temp->y, temp->z, memtab[j].largeur, memtab[j].hauteur, memtab[j].angle_max_y);
      pere->SetPantinFilsAuDernierMembre(p);
      memempiler(p, memtab[j].fils);
    }
    fils = fils->suivant;
  }
}




%}

/* Le type de yylval. */
/* Attention !!!!!!!!
   Si problème de définition de type, bien regardé le makefile,
   mais surtout avant chaque #include "parser.h"
   avoir mis un #include "le fichier de description des types.h"
*/
%union {
booleen yybooleen;
int yyentier;
double yyreel;
char *yychaine;
char *yyident;
action yylaction;

tcode yycode;
sgenere *yygenere;
filsdesc *yyfils;
tmembre *yymembre;
tevent *yyevent;
taction *yyaction;
liste *yyliste;
}

%token <yybooleen> Token_Booleen
%token <yyentier>  Token_Entier
%token <yyreel>    Token_Reel
%token <yychaine>  Token_Chaine
%token <yyident>   Token_Ident
%token <yyaction>  Token_LAction

%token Token_Assign
%token Token_Plus Token_Moins
%token Token_Mult Token_Div

%token Token_OpenPar Token_OpenBrace Token_OpenBracket
%token Token_ClosePar Token_CloseBrace Token_CloseBracket

%token Token_Ptvirg Token_Virgule
%token Token_EOF

%token Token_Zone Token_Choc Token_Masse Token_Invinsible
%token Token_Membres Token_Racines
%token Token_Action
%token Token_Menu Token_Affichage Token_Gestionnaire
%token Token_Evenement Token_Genere Token_Par Token_Traitement
%token Token_Membre Token_Fils Token_Angle Token_Max
%token Token_Qui Token_X Token_Y Token_Z
%token Token_Tous Token_Aucun
%token Token_Image

%token Token_Points Token_De Token_Vie Token_Hostile

%token Token_Largeur Token_Longueur Token_Hauteur

%token Token_Physique Token_Gameplay Token_Graphique


%type <yycode> code
%type <yygenere> genere
%type <yyfils> fils
%type <yymembre> membre
%type <yyevent> evenement 
%type <yyaction> action

%type <yyliste> liste_membre
%type <yyliste> liste_membres_racines
%type <yyliste> liste_fils
%type <yyliste> liste_evenement
%type <yyliste> liste_action

//%type <physique> physique 
//%type <gameplay> gameplay 
//%type <graphique> graphique
//%type <anime> main

%start main

%%

main: physique gameplay graphique {
  return 0;
};

physique: 
Token_Physique Token_OpenBrace
 Token_Zone Token_De Token_Choc Token_Assign Token_OpenBrace
  Token_Longueur Token_Assign Token_Reel Token_Ptvirg
  Token_Largeur  Token_Assign Token_Reel Token_Ptvirg
  Token_Hauteur  Token_Assign Token_Reel Token_Ptvirg
 Token_CloseBrace Token_Ptvirg
Token_Masse Token_Assign Token_Reel Token_Ptvirg
Token_CloseBrace
{
  bongars->SetDimension($10, $14, $18);
};

gameplay:
Token_Gameplay Token_OpenBrace 
 Token_Points Token_De Token_Vie Token_Assign Token_Entier Token_Ptvirg
 Token_Invinsible Token_Assign Token_Booleen Token_Ptvirg
 Token_Hostile    Token_Assign Token_Booleen Token_Ptvirg
 liste_action
 liste_evenement
Token_CloseBrace
{
};

graphique:
Token_Graphique Token_OpenBrace 
 liste_membre
 Token_Membres Token_Racines Token_Assign liste_membres_racines Token_Ptvirg
Token_CloseBrace
{
  filsdesc *temp;
  while ($7 != NULL) {
    int j;
    temp = (filsdesc*) $7->contenu;

    if ((j = memlookup(temp->qui)) < 0) {
      yyerror(strcat(strcat("Le membre \"", temp->qui), "\" n'a pas ete defini. On continue néanmoins.\n"));
    }
    
    else {
      bongars->AjouterMembre(memtab[j].image, temp->x, temp->y, temp->z, memtab[j].largeur, memtab[j].hauteur, memtab[j].angle_max_y);
      memempiler(bongars, memtab[j].fils);
    }
    $7 = $7->suivant;
  }
};


liste_action:
liste_action action {$$ = mp($2, $1); VERIF_NOT_NULL($$,-6)}
| {$$ = liste_vide();}
;

action:
Token_Action Token_LAction Token_OpenBrace
 Token_Menu Token_Assign Token_Booleen Token_Ptvirg
 Token_Affichage Token_Assign Token_Chaine Token_Ptvirg
 Token_Gestionnaire Token_Assign code Token_Ptvirg
Token_CloseBrace
{
  $$ = new_action();
  VERIF_NOT_NULL($$,-7)
  $$->menu = $6;
  $$->affichage = $10;
  $$->gestionnaire = $14;
};

liste_evenement:
  liste_evenement evenement {$$ = mp($2, $1); VERIF_NOT_NULL($$,-8)}
| {$$ = liste_vide();}
;

evenement:
Token_Evenement Token_Ident Token_OpenBrace
 Token_Genere Token_Par Token_Assign genere Token_Ptvirg
 Token_Traitement Token_Assign code Token_Ptvirg
Token_CloseBrace
{
  $$ = new_event();
  VERIF_NOT_NULL($$,-9)

  $$->genere = $7->type;
  if ($7->type == CODE) {
    $$->par = NULL;
  }

  else {
    $$->par = $7->code;
  }

  del_sgenere($7);
  $$->traitement = $11;
};

liste_membre:
  liste_membre membre {$$ = mp($2, $1); VERIF_NOT_NULL($$,-10)}
| {$$ = liste_vide();}
;

membre:
Token_Membre Token_Ident Token_OpenBrace
 Token_Fils Token_Assign liste_fils Token_Ptvirg
 Token_Image Token_Assign Token_Chaine Token_Ptvirg
 Token_Largeur Token_Assign Token_Reel Token_Ptvirg
 Token_Hauteur Token_Assign Token_Reel Token_Ptvirg
 Token_Angle Token_Max Token_Y Token_Assign Token_Reel Token_Ptvirg
Token_CloseBrace
{
  if (memnbelts < MAXMEMBRE) {
    memtab[memnbelts].nom = $2;
    memtab[memnbelts].image = $10;
    memtab[memnbelts].fils = $6;
    memtab[memnbelts].largeur = $14;
    memtab[memnbelts].hauteur = $18;
    memtab[memnbelts].angle_max_y = $24;
    memnbelts++;
  }
};

liste_membres_racines: liste_fils {$$ = $1;};

liste_fils:
  liste_fils fils liste_virg {$$ = mp($2, $1); VERIF_NOT_NULL($$,-12)}
| liste_virg {$$ = liste_vide();}
;

fils:
Token_OpenBrace
 Token_Qui Token_Assign Token_Ident Token_Ptvirg
 Token_X Token_Assign Token_Reel Token_Ptvirg
 Token_Y Token_Assign Token_Reel Token_Ptvirg
 Token_Z Token_Assign Token_Reel Token_Ptvirg
 Token_Angle Token_Y Token_Assign Token_Reel Token_Ptvirg
Token_CloseBrace
{
  $$ = new filsdesc;
  $$->qui = $4;
  $$->x = $8;
  $$->y = $12;
  $$->z = $16;
  $$->angle_y = $21;
};


liste_virg:
  liste_virg Token_Virgule
| 
  ;


genere:
  Token_Aucun
{$$ = new_sgenere(); VERIF_NOT_NULL($$,-14); $$->type = AUCUN; $$->code = NULL;}
| Token_Tous
{$$ = new_sgenere(); VERIF_NOT_NULL($$,-15); $$->type = TOUS; $$->code = NULL;}
| code
{$$ = new_sgenere(); VERIF_NOT_NULL($$,-16); $$->type = CODE; $$->code = $1;}
;

code: {$$ = NULL;};

%%

/*extern void yyerror(char *msg);*/
#include <stdio.h>
const static void yyerror(char s[]) {
  int a, b, c;
  a = get_nb_chars();
  b = get_nb_chars_tot();
  c = get_yyleng();
  (void) fprintf(stderr, "Erreur d'analyse syntaxique sur le lexème \"%s\" à la ligne %d (caractères %d (%d) à %d (%d)) [%s]\n", get_yytext(), get_nb_lignes() + 1, a - c, b - c, a - 1, b - 1, s);
}

