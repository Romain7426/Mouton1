%{ /* Header */
#include "global.h"
const extern int get_nb_lignes(void);
const extern int get_nb_chars(void);
const extern int get_nb_chars_tot(void);
const extern int get_yyleng(void);
const extern char * get_yytext(void);
const extern int yylex(void);
const static void yyerror(char s[]);

%}

/* Le type de yylval. */
%union {
  booleen booleen;
  int entier;
  double reel;
  char *chaine;
  char *ident;
  action action;
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

 //%type physique gameplay graphique

 //%type main

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
Token_CloseBrace;

gameplay:
Token_Gameplay Token_OpenBrace 
 Token_Points Token_De Token_Vie Token_Assign Token_Entier Token_Ptvirg
 Token_Invinsible Token_Assign Token_Booleen Token_Ptvirg
 Token_Hostile    Token_Assign Token_Booleen Token_Ptvirg

/* Là, on arrive à deux choses différentes : 
   les actions du menu,
   et la définition d'évènements
   avec leur gestionnaire.

   Les actions concernent ce que le héros peut faire subir au décor,
   il y a une action volontaire.
   Les évènements sont des choses qui sont indépendantes de la volonté
   du héros, qui dépendent de tout un tas de variables et donc arrivent
   à peu près n'importe quand et touchent à peu près n'importe qui
   ou quoi.
   Ici, on parle d'évènements du GamePlay, qui n'ont à priori
   rien à voir avec les évènements physiques.
   Néanmoins, en pratique, un évènement du GamePlay est généré
   par un ou plusieurs évènement physique.
*/

/* On commence par définir les actions avec leur gestionnaire. */
 liste_action

/* Puis la liste des évènements avec leur traitement. */
 liste_evenement
 
Token_CloseBrace
;

graphique:
Token_Graphique Token_OpenBrace 
 liste_membre
 Token_Membres Token_Racines Token_Assign liste_membres_racines Token_Ptvirg
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

liste_membre:
  liste_membre membre
| 
;

membre:
Token_Membre Token_Ident Token_OpenBrace
 Token_Fils Token_Assign liste_fils Token_Ptvirg
 Token_Image Token_Assign Token_Chaine Token_Ptvirg
 Token_Largeur Token_Assign Token_Reel Token_Ptvirg
 Token_Hauteur Token_Assign Token_Reel Token_Ptvirg
 Token_Angle Token_Max Token_Y Token_Assign Token_Reel Token_Ptvirg
Token_CloseBrace
;

liste_membres_racines: liste_fils;

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
 Token_Angle Token_Y Token_Assign Token_Reel Token_Ptvirg
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

