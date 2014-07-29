%{ /* Header */
#include <stdlib.h>
#include "global.hpp"
#include "carte/carte.global.hpp"
#include "bonhomme.hpp"
#include "objnonanime.hpp"
#include "apiscript.hpp"
#include "evenement.hpp"

static const void yyerror(char s[]);

#define VERIF_NOT_NULL(a,b) {if (a == NULL) {yyerror("Manque de mémoire."); return b;}}

CMap *carte = NULL;

void carte_parser_reset(void) {
  /* Nothing to do. */
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

carte_tcode *code;
carte_sgenere *genere;
carte_tobjet *objet;
carte_ttexture *texture;
carte_tevent *yyevent;
liste *yyliste;
carte_tphysique *physique;
carte_tgameplay *gameplay;
carte_tgraphique *graphique;
carte_tcarte *carte;
TDirection dir;
}

%token <yybooleen> Token_Booleen
%token <yyentier>  Token_Entier
%token <yyreel>    Token_Reel
%token <yychaine>  Token_Chaine
%token <yyident>   Token_Ident

%token Token_Assign
//%token Token_Plus Token_Moins
//%token Token_Mult Token_Div

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


%token Token_Musique Token_Eau Token_Vie Token_Teleportation Token_Dimension
%token Token_Longueur Token_Largeur Token_Hauteur Token_Direction Token_Parcours
%token Token_Destination Token_Gauche Token_Droite Token_Haut Token_Bas


%type <yyentier> expr_entier expr_entier1 expr_entier2 
%token Token_PlusEntier Token_MoinsEntier Token_MultEntier Token_DivEntier Token_ModEntier

%type <yyreel> expr_reel expr_reel1 expr_reel2
//%token Token_ZSol
%token Token_PlusReel Token_MoinsReel Token_MultReel Token_DivReel

%token Token_Procedure


%type <dir> direction

%type <code> code
%type <genere> genere
//%type <texture> texture
//%type <objet> objet
%type <yyevent> evenement 

//%type <yyliste> liste_objet
//%type <yyliste> liste_texture
%type <yyliste> liste_evenement

/*
  %type <physique> physique 
  %type <gameplay> gameplay 
  %type <graphique> graphique
  %type <carte> main
*/

%start main

%%

main: physique gameplay graphique {
  carte_mess("Le parser a reconnu un fichier de type .carte. Victoire !");
  return 0;
};

physique: 
Token_Physique Token_OpenBrace
Token_CloseBrace
{
  carte_mess("Le parser a reconnu la partie physique d'un .carte.");
};

gameplay:
Token_Gameplay Token_OpenBrace 
 Token_Arme Token_Assign Token_Booleen Token_Ptvirg
 Token_Musique Token_Assign Token_Chaine Token_Ptvirg
 Token_Niveau Token_Eau Token_Assign expr_reel Token_Ptvirg
//Token_Couleur Token_Eau Token_Assign Token_VCouleur Token_Ptvirg
 Token_Vie Token_Eau Token_Assign expr_entier Token_Ptvirg
 liste_teleportation
 liste_evenement
Token_CloseBrace
{
  carte_mess("Le parser a reconnu la partie gameplay d'un .carte.");
  if (SCRIPT_EstEnTrainDExecuterUnScript()) {
  }   
  else {
    SCRIPT_JouerMusique($9);
  }
  carte->ZEau = $14;
  carte_mess("Done.");
};

graphique:
Token_Graphique Token_OpenBrace 
 zone_niveau
 Token_Fichier Token_De Token_Zone Token_De Token_Texture Token_Assign Token_Chaine Token_Ptvirg
 liste_texture
 liste_objet
Token_CloseBrace
{
  carte_mess("Le parser a reconnu la partie graphique d'un .carte.");
  carte_mess("Chargement du fichier de description des textures du sol \"%s\".", $10);
  carte->ChargerIndiceTextureBitmap($10);
  carte_mess("Chargement terminé.");
  carte_mess("Au fait, c'est la première texture qui est chargée par le programme pour le sol, étant donné que pour l'instant ça ne supporte pas une multiplicité de textures.");
};

zone_niveau:
Token_Fichier Token_De Token_Zone Token_De Token_Niveau Token_Assign Token_Chaine Token_Ptvirg
{
  carte_mess("Chargement du fichier de niveau \"%s\".", $7);
  carte->ChargerZ($7);
  carte_mess("Chargement terminé.");
}


liste_teleportation:
  liste_teleportation teleportation {}
| {}
;

teleportation:
Token_Teleportation Token_Ident Token_OpenBrace
 Token_Destination Token_Assign Token_Chaine Token_Ptvirg
 Token_Position Token_Assign Token_OpenBrace
  Token_X Token_Assign expr_entier Token_Ptvirg
  Token_Y Token_Assign expr_entier Token_Ptvirg
  Token_Z Token_Assign expr_entier Token_Ptvirg
 Token_CloseBrace Token_Ptvirg
 Token_Dimension Token_Assign Token_OpenBrace
  Token_Longueur Token_Assign expr_entier Token_Ptvirg
  Token_Largeur Token_Assign expr_entier Token_Ptvirg
  Token_Hauteur Token_Assign expr_entier Token_Ptvirg
 Token_CloseBrace Token_Ptvirg
 Token_Direction Token_Parcours Token_Assign direction Token_Ptvirg
 Token_Destination Token_Position Token_Assign Token_OpenBrace
  Token_X Token_Assign expr_entier Token_Ptvirg
  Token_Y Token_Assign expr_entier Token_Ptvirg
  Token_Z Token_Assign expr_entier Token_Ptvirg
 Token_CloseBrace Token_Ptvirg
 Token_Destination Token_Direction Token_Parcours Token_Assign direction Token_Ptvirg
Token_CloseBrace
{
  carte_mess("Ajout de la zone de téléportation %s", $2);
  carte->AjouterZoneTeleportation(
				  Point3D((float)$13,(float)$17,(float)$21), // position
				  Point3D((float)$30,(float)$34,(float)$38), // dimension
				  $45, // direction
				  $6, // la carte de destination
				  Point3D((float)$53,(float)$57,(float)$61), // position d'arrivée
				  $69); // direction d'arrivée
				  
				  
  
  carte_mess("Zone de téléportation ajoutée.");
}
;

direction: 
  Token_Gauche {$$ = PROFIL_VERS_G;} 
| Token_Droite {$$ = PROFIL_VERS_D;} 
| Token_Haut {$$ = DOS;} 
| Token_Bas {$$ = FACE;} 
;



liste_evenement:
liste_evenement evenement {}
| {}
;

evenement:
Token_Evenement Token_Ident Token_OpenBrace
 Token_Genere Token_Par Token_Assign Token_Entier Token_Ptvirg
 Token_Traitement Token_Assign code Token_Ptvirg
Token_CloseBrace
{
//   $$ = carte_new_event();
//   VERIF_NOT_NULL($$,-9)

//   $$->genere = $7->type;
//   if ($7->type == CODE) {
//     $$->par = NULL;
//   }

//   else {
//     $$->par = $7->code;
//   }

//   carte_del_sgenere(&($7));
//   $$->traitement = $11;
  //extern void AddTraitementEvenement(type_evt t, const char* nom_fichier, const char* proc);
  AddTraitementEvenement((type_evt)$7, $11->fichier, $11->nom);
  carte_del_code($11);
};


liste_texture:
  liste_texture texture {}
| {}
;

texture:
Token_Texture Token_Ident Token_OpenBrace
 Token_Image Token_Assign Token_Chaine Token_Ptvirg
 Token_Indice Token_Assign expr_entier Token_Ptvirg
Token_CloseBrace
{
  carte_mess("Reconnaissance d'un champ de description de texture par le parser. Cette texture s'appelle \"%s\".", $2);
  carte_mess("Chargement de la texture en mémoire (image = \"%s\", couleur associée = %d).", $6, $10);
  //carte->TextureSol = gestionTexture.prendre($6);
  if (carte->nb_texture < NB_MAX_TEXTURESOL) {
    carte_mess("C'est bon. Il y a assez de places pour mettre la texture.");
    //carte->indices_dans_bitmap[carte->nb_texture] = $10;
    //carte->TextureSol[(carte->nb_texture)++] = gestionTexture.prendre($6);
    carte->AjouterTextureSol($6, $10);
  }
  else {
    carte_err("Il n'y pas assez de place pour mettre la texture. Il faut changer NB_MAX_TEXTURESOL.");
  }
  carte_mess("[nb_textures = %d][NB_MAX_TEXTURES = %d]", carte->nb_texture, NB_MAX_TEXTURESOL);

  carte_mess("Fin du traitement de la texture \"%s\".", $2);
};


liste_objet:
  liste_objet objet {}
| {}
;

objet:
Token_Objet Token_Ident Token_OpenBrace
 Token_Anime Token_Assign Token_Booleen Token_Ptvirg
 Token_Fichier Token_Assign Token_Chaine Token_Ptvirg
 Token_Position Token_Assign Token_OpenBrace
  Token_X Token_Assign expr_reel Token_Ptvirg
  Token_Y Token_Assign expr_reel Token_Ptvirg
  Token_Z Token_Assign expr_reel Token_Ptvirg
  Token_Angle Token_X Token_Assign expr_reel Token_Ptvirg
  Token_Angle Token_Y Token_Assign expr_reel Token_Ptvirg
  Token_Angle Token_Z Token_Assign expr_reel Token_Ptvirg
 Token_CloseBrace Token_Ptvirg
Token_CloseBrace
{
  carte_mess("Le parser a reconnu un champ objet. Il s'appelle \"%s\".", $2);
  if ($6) {
    carte_mess("C'est un objet animé.");
    carte_mess("Chargement du fichier \"%s\".", $10);
    CBonhomme *bonhomme = new CBonhomme($10);
    carte_mess("Chargement du fichier terminé. On positionne les autres attributs (x, y, z).");
    TPoint3D pos;
    pos.x = $17;
    pos.y = $21;
    pos.z = $25;
    bonhomme->SetPosition(pos);
    carte_mess("Done. Ajout de l'objet à la carte.");
    carte->AjouterObjet($2, bonhomme);
    carte_mess("Done. Les paramètres d'angles ne sont pas encore utilisés.");
  }

  else {
    carte_mess("C'est un objet non animé.");
    carte_mess("Chargement du fichier \"%s\".", $10);
    CObjNonAnime* o = new CObjNonAnime($10);
    carte_mess("Chargement du fichier terminé. On positionne les autres attributs (x, y, z).");
    TPoint3D pos;
    pos.x = $17;
    pos.y = $21;
    pos.z = $25;
    o->SetPosition(pos);
    carte_mess("Done. Ajout de l'objet à la carte.");
    carte->AjouterObjet($2, o);
    carte_mess("Done. Les paramètres d'angles ne sont pas encore utilisés.");
  }

  /*  
      $$->angle_x = $30;
      $$->angle_y = $35;
      $$->angle_z = $40;
  */
};


genere:
  Token_Aucun
{$$ = carte_new_sgenere(); VERIF_NOT_NULL($$,-14); $$->type = AUCUN; $$->code =NULL;}
| Token_Tous
{$$ = carte_new_sgenere(); VERIF_NOT_NULL($$,-15); $$->type = TOUS; $$->code = NULL;}
| code
{$$ = carte_new_sgenere(); VERIF_NOT_NULL($$,-16); $$->type = CODE; $$->code = $1;}
;

code:
Token_OpenBrace 
Token_Fichier Token_Assign Token_Chaine Token_Ptvirg 
Token_Procedure Token_Assign Token_Chaine Token_Ptvirg
Token_CloseBrace
{ $$ = carte_new_code(); $$->fichier = $4; $$->nom = $8; };







expr_entier:
expr_entier Token_PlusEntier expr_entier1 { $$ = $1 + $3; }
| expr_entier Token_MoinsEntier expr_entier1 { $$ = $1 - $3; }
| expr_entier1 { $$= $1; }
;

expr_entier1:
expr_entier1 Token_MultEntier expr_entier2 { $$ = $1 * $3; }
| expr_entier1 Token_DivEntier expr_entier2 { $$ = $1 / $3; }
| expr_entier1 Token_ModEntier expr_entier2 { $$ = $1 % $3; }
| expr_entier2 { $$ = $1; }
;

expr_entier2:
Token_Entier { $$ = $1; }
| Token_PlusEntier expr_entier2 { $$ = $2; }
| Token_MoinsEntier expr_entier2 { $$ = - $2; }
| Token_OpenPar expr_entier Token_ClosePar { $$ = $2; }
;


expr_reel:
expr_reel Token_PlusReel expr_reel1 { $$ = $1 + $3; }
| expr_reel Token_MoinsReel expr_reel1 { $$ = $1 - $3; }
| expr_reel1 { $$= $1; }
;

expr_reel1:
expr_reel1 Token_MultReel expr_reel2 { $$ = $1 * $3; }
| expr_reel1 Token_DivReel expr_reel2 { $$ = $1 / $3; }
| expr_reel2 { $$ = $1; }
;

expr_reel2:
Token_Reel { $$ = $1; }
| Token_PlusReel expr_reel2 { $$ = $2; }
| Token_MoinsReel expr_reel2 { $$ = - $2; }
| Token_OpenPar expr_reel Token_ClosePar { $$ = $2; }
;






%%

/*extern void yyerror(char *msg);*/
#include <stdio.h>
static const void yyerror(char s[]) {
  int a, b, c;
  a = carte_get_nb_chars();
  b = carte_get_nb_chars_tot();
  c = carte_get_yyleng();
  carte_err( "Erreur d'analyse syntaxique sur le lexème \"%s\" à la ligne %d (caractères %d (%d) à %d (%d)) [%s]\n", carte_get_yytext(), carte_get_nb_lignes() + 1, a - c, b - c, a - 1, b - 1, s);
}

