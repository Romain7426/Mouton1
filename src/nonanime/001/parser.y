%{ /* Header */
#include <stdlib.h>
#include "global.hpp"

const static void yyerror(char s[]);
CObjNonAnime *objet = NULL;

#define VERIF_NOT_NULL(a,b) if (a == NULL) {yyerror("Manque de mémoire."); return b;}

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

tcode code;
sgenere *genere;
tfils *fils;
telement *element;
tevent *event;
taction *yyaction;
liste *yyliste;
tnonanime *nonanime;
tphysique *physique;
tgameplay *gameplay;
tgraphique *graphique;
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



%type <code> code
%type <genere> genere
%type <fils> fils
%type <element> element
%type <event> evenement 
%type <yyaction> action

%type <yyliste> liste_element
%type <yyliste> liste_elements_racines
%type <yyliste> liste_fils
%type <yyliste> liste_evenement
%type <yyliste> liste_action

%type <physique> physique 
%type <gameplay> gameplay 
%type <graphique> graphique
%type <nonanime> main

%start main

%%

main: physique gameplay graphique {
  tnonanime* temp = new_nonanime();
  VERIF_NOT_NULL(temp,-1);
  temp->physique = $1;
  temp->gameplay = $2;
  temp->graphique = $3;
  $$ = temp;
  return 0;
};

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
{
  tphysique *temp = new_physique();
  VERIF_NOT_NULL(temp,-2);
  temp->choc = new_vecteur();
  VERIF_NOT_NULL(temp->choc,-3);
  temp->choc->proj.x = $18;
  temp->choc->proj.y = $10;
  temp->choc->proj.z = $14;
  temp->masse = $24;
  temp->compressible = $28;
  temp->fixe = $32;
  temp->rebondissement = $38;
  $$ = temp;
};

gameplay:
Token_Gameplay Token_OpenBrace 
 Token_Points Token_De Token_Vie Token_Assign Token_Entier Token_Ptvirg
 Token_Invinsible Token_Assign Token_Booleen Token_Ptvirg
 liste_action
 liste_evenement
Token_CloseBrace
{
  tgameplay *temp = new_gameplay();
  VERIF_NOT_NULL(temp,-4);
  temp->vie = $7;
  temp->invinsible = $11;
  
  temp->actions = $13;
  temp->events = $14;
  
  $$ = temp;
};

graphique:
Token_Graphique Token_OpenBrace 
 liste_element
 Token_Elements Token_Racines Token_Assign liste_elements_racines Token_Ptvirg
Token_CloseBrace
{
  tgraphique *temp = new_graphique();
  VERIF_NOT_NULL(temp,-5);
  $$->racines = $7;
  $$ = temp;
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

  del_sgenere(&($7));
  $$->traitement = $11;
};

liste_element:
  liste_element element {$$ = mp($2, $1); VERIF_NOT_NULL($$,-10)}
| {$$ = liste_vide();}
;

element:
Token_Element Token_Ident Token_OpenBrace
 Token_Fils Token_Assign liste_fils Token_Ptvirg
 Token_Image Token_Assign Token_Chaine Token_Ptvirg
Token_CloseBrace
{
  $$ = new_element();
  VERIF_NOT_NULL($$,-11);
  $$->fils = $6;
  $$->image = $10;
};

liste_elements_racines: liste_fils {$$ = $1;};

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
 Token_Angle Token_X Token_Assign Token_Reel Token_Ptvirg
 Token_Angle Token_Y Token_Assign Token_Reel Token_Ptvirg
 Token_Angle Token_Z Token_Assign Token_Reel Token_Ptvirg
Token_CloseBrace
{
  $$ = new_fils();
  VERIF_NOT_NULL($$,-13);
  $$->qui = (telement) $4; /* lookup en realite */
  $$->x = $8;
  $$->y = $12;
  $$->z = $16;
  $$->angle_x = $21;
  $$->angle_y = $26;
  $$->angle_z = $31;
};


liste_virg:
  liste_virg Token_Virgule
| 
  ;


genere:
  Token_Aucun
{$$ = new_sgenere(); VERIF_NOT_NULL($$,-14); $$->type = AUCUN; $$->code =NULL;}
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

