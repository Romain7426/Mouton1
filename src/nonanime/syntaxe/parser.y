%{ /* Header */
#include <stdlib.h>
#include "global.h"

const static void yyerror(char s[]);

#define VERIF_NOT_NULL(a,b) if (a == NULL) {yyerror("Manque de mémoire."); return b;}

%}

/* Le type de yylval. */
/* Attention !!!!!!!!
   Si problème de définition de type, bien regardé le makefile,
   mais surtout avant chaque #include "parser.h"
   avoir mis un #include "le fichier de description des types.h"
*/
%union {
booleen booleen;
int entier;
double reel;
char *chaine;
char *ident;
action laction;

tcode code;
sgenere genere;
tfils fils;
telement element;
tevent event;
taction action;
liste liste;
tnonanime nonanime;
tphysique physique;
tgameplay gameplay;
tgraphique graphique;
}

%token <booleen> Token_Booleen
%token <entier>  Token_Entier
%token <reel>    Token_Reel
%token <chaine>  Token_Chaine
%token <ident>   Token_Ident
%token <action>  Token_LAction

%token Token_Assign
%token Token_Plus Token_Moins
%token Token_Mult Token_Div

%token Token_OpenPar Token_OpenBrace Token_OpenBracket
%token Token_ClosePar Token_CloseBrace Token_CloseBracket

%token Token_Ptvirg Token_Virgule
%token Token_EOF

%token Token_Zone Token_Choc Token_Masse Token_Invinsible
%token Token_Elements Token_Racines
%token Token_Action
%token Token_Menu Token_Affichage Token_Gestionnaire
%token Token_Evenement Token_Genere Token_Par Token_Traitement
%token Token_Element Token_Fils Token_Angle
%token Token_Qui Token_X Token_Y Token_Z
%token Token_Tous Token_Aucun
%token Token_Image

%token Token_Points Token_De Token_Vie

%token Token_Largeur Token_Longueur Token_Hauteur

%token Token_Physique Token_Gameplay Token_Graphique

%token Token_Compressible Token_Fixe Token_Coefficient Token_Rebondissement


/*
%type <code> code
%type <genere> genere
%type <fils> fils
%type <element> element
%type <event> evenement 
%type <action> action

%type <liste> liste_element
%type <liste> liste_elements_racines
%type <liste> liste_fils
%type <liste> liste_evenement
%type <liste> liste_action

%type <physique> physique 
%type <gameplay> gameplay 
%type <graphique> graphique
%type <nonanime> main
*/

%start main

%%

main: physique gameplay graphique {return 0;};

physique: 
Token_Physique Token_OpenBrace
 Token_Zone Token_De Token_Choc Token_Assign Token_OpenBrace
  Token_Largeur  Token_Assign Token_Reel Token_Ptvirg
  Token_Hauteur  Token_Assign Token_Reel Token_Ptvirg
  Token_Longueur Token_Assign Token_Reel Token_Ptvirg
 Token_CloseBrace Token_Ptvirg
Token_Masse Token_Assign Token_Reel Token_Ptvirg
Token_Compressible Token_Assign Token_Booleen Token_Ptvirg
Token_Fixe Token_Assign Token_Booleen Token_Ptvirg
Token_Coefficient Token_De Token_Rebondissement Token_Assign Token_Reel Token_Ptvirg
Token_CloseBrace
;

gameplay:
Token_Gameplay Token_OpenBrace 
 Token_Points Token_De Token_Vie Token_Assign Token_Entier Token_Ptvirg
 Token_Invinsible Token_Assign Token_Booleen Token_Ptvirg
 liste_action
 liste_evenement
Token_CloseBrace
;

graphique:
Token_Graphique Token_OpenBrace 
 liste_element
 Token_Elements Token_Racines Token_Assign liste_elements_racines Token_Ptvirg
Token_CloseBrace
;


liste_action:
liste_action action 
| 
;

action:
Token_Action Token_LAction Token_OpenBrace
 Token_Menu Token_Assign Token_Booleen Token_Ptvirg
 Token_Affichage Token_Assign Token_Chaine Token_Ptvirg
 Token_Gestionnaire Token_Assign code Token_Ptvirg
Token_CloseBrace
;

liste_evenement:
  liste_evenement evenement
| 
;

evenement:
Token_Evenement Token_Ident Token_OpenBrace
 Token_Genere Token_Par Token_Assign genere Token_Ptvirg
 Token_Traitement Token_Assign code Token_Ptvirg
Token_CloseBrace
;

liste_element:
  liste_element element
| 
;

element:
Token_Element Token_Ident Token_OpenBrace
 Token_Fils Token_Assign liste_fils Token_Ptvirg
 Token_Image Token_Assign Token_Chaine Token_Ptvirg
Token_CloseBrace
;

liste_elements_racines: liste_fils

liste_fils:
  liste_fils fils liste_virg
| liste_virg
;

fils:
Token_OpenBrace
 Token_Qui Token_Assign Token_Ident Token_Ptvirg
 Token_X Token_Assign Token_Reel Token_Ptvirg
 Token_Y Token_Assign Token_Reel Token_Ptvirg
 Token_Z Token_Assign Token_Reel Token_Ptvirg
 Token_Angle Token_X Token_Assign Token_Reel Token_Ptvirg
 Token_Angle Token_Y Token_Assign Token_Reel Token_Ptvirg
 Token_Angle Token_Z Token_Assign Token_Reel Token_Ptvirg
Token_CloseBrace
;


liste_virg:
  liste_virg Token_Virgule
| 
  ;


genere:
  Token_Aucun
| Token_Tous
| code
;

code: ;

%%

/*extern void yyerror(char *msg);*/
#include <stdio.h>
const static void yyerror(char s[]) {
  int a, b, c;
  a = get_nb_chars();
  b = get_nb_chars_tot();
  c = get_yyleng();
  (void) fprintf(stdout, "Erreur d'analyse syntaxique sur le lexème \"%s\" à la ligne %d (caractères %d (%d) à %d (%d)) [%s]\n", get_yytext(), get_nb_lignes() + 1, a - c, b - c, a - 1, b - 1, s);
}

