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
}

%token <booleen> Token_Booleen
%token <entier>  Token_Entier
%token <reel>    Token_Reel
%token <chaine>  Token_Chaine
%token <ident>   Token_Ident

%token Token_Assign
%token Token_Plus Token_Moins
%token Token_Mult Token_Div

%token Token_OpenPar Token_OpenBrace Token_OpenBracket
%token Token_ClosePar Token_CloseBrace Token_CloseBracket

%token Token_Ptvirg Token_Virgule
%token Token_EOF

%token Token_Zone 
%token Token_Evenement Token_Genere Token_Par Token_Traitement
%token Token_Objet Token_Objets Token_Angle
%token Token_Qui Token_X Token_Y Token_Z
%token Token_Tous Token_Aucun
%token Token_Image

%token Token_Physique Token_Gameplay Token_Graphique

%token Token_Texture Token_Textures Token_Anime Token_Niveau Token_De
%token Token_Fichier Token_Indice Token_Position Token_Arme


%start main

%%

main: physique gameplay graphique {return 0;};

physique: 
Token_Physique Token_OpenBrace
Token_CloseBrace
;

gameplay:
Token_Gameplay Token_OpenBrace 
 Token_Arme Token_Assign Token_Booleen Token_Ptvirg
 liste_evenement
Token_CloseBrace
;

graphique:
Token_Graphique Token_OpenBrace 
 Token_Fichier Token_De Token_Zone Token_De Token_Niveau Token_Assign Token_Chaine Token_Ptvirg
 Token_Fichier Token_De Token_Zone Token_De Token_Texture Token_Assign Token_Chaine Token_Ptvirg
 liste_texture
 liste_objet
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


liste_texture:
  liste_texture texture
| 
;

texture:
Token_Texture Token_Ident Token_OpenBrace
 Token_Image Token_Assign Token_Chaine Token_Ptvirg
 Token_Indice Token_Assign Token_Entier Token_Ptvirg
Token_CloseBrace
;


liste_objet:
  liste_objet objet
| 
;

objet:
Token_Objet Token_Ident Token_OpenBrace
 Token_Anime Token_Assign Token_Booleen Token_Ptvirg
 Token_Fichier Token_Assign Token_Chaine Token_Ptvirg
 Token_Position Token_Assign Token_OpenBrace
  Token_X Token_Assign Token_Reel Token_Ptvirg
  Token_Y Token_Assign Token_Reel Token_Ptvirg
  Token_Z Token_Assign Token_Reel Token_Ptvirg
  Token_Angle Token_X Token_Assign Token_Reel Token_Ptvirg
  Token_Angle Token_Y Token_Assign Token_Reel Token_Ptvirg
  Token_Angle Token_Z Token_Assign Token_Reel Token_Ptvirg
 Token_CloseBrace Token_Ptvirg
Token_CloseBrace
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

