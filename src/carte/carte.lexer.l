%{
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "global.hpp"
#include "carte/carte.global.hpp"
#include "carte/carte.parser.hpp"

/* yytext yyleng ECHO */
/* Pour faire le pipe, on fait option + maj + l
   Maintenant, on chercher le tilde. */
/* Le tilde, il faut faire option + n + la touche appropriee. */
/* yytext, yyleng, yymore(), yyless, unput(), %array, input(), yyinput(), yyterminate(), yyin, yyout, yyrestart(), yywrap(), yy_scan_string(), yy_scan_buffer(), yy_scan_bytes(), 
*/
/* #define YY_DECL float lexscan( a, b ) float a, b; */
/* int yylex(void) */


#define PRINT_OUT(a)  nb_chars += yyleng; nb_chars_tot += yyleng; (void) fprintf(yyout, "%s[%s] ", a, yytext);

static int nb_lignes = 0, nb_chars = 0, nb_chars_tot = 0;

extern const void carte_restart_lexer(void) {
  nb_lignes = nb_chars = nb_chars_tot = 0;
}   

extern const int carte_get_nb_lignes(void) {
 return nb_lignes;
}   

extern const int carte_get_nb_chars(void) {
 return nb_chars;
}   

extern const int carte_get_nb_chars_tot(void) {
 return nb_chars_tot;
}   

extern const int carte_get_yyleng(void) {
 return yyleng;
}   

extern const char * carte_get_yytext(void) {
 return yytext;
}   


static const int match_symbole(char symbole[]) {
  char *temp;
  size_t taille;
  size_t i;

  taille = strlen(symbole);
  temp = (char *) malloc((taille + 1) * sizeof(char));

  if (temp == NULL) {
    carte_err("Manque de mémoire. On s'arrête.");
    return Token_EOF;
  }

  for (i = 0; i < taille; i++) {
    temp[i] = (char) tolower((int) symbole[i]);
  }
  temp[i] = '\0';
  /* fprintf(yyout, "%s%d%s", symbole, taille, temp); */

  
  /* Maintenant on compare le contenu du symbole aux mots-clefs
     en minuscule. C'est très moche comparé à l'OCaml. */
  /* if (strcmp(temp, "") == 0) {free(temp); return Token_;} */
  if (strcmp(temp, "physique") == 0) {free(temp); return Token_Physique;}
  if (strcmp(temp, "gameplay") == 0) {free(temp); return Token_Gameplay;}
  if (strcmp(temp, "graphique") == 0) {free(temp); return Token_Graphique;}
  if (strcmp(temp, "zone") == 0) {free(temp); return Token_Zone;}
  if (strcmp(temp, "objets") == 0) {free(temp); return Token_Objets;}
  if (strcmp(temp, "evenement") == 0) {free(temp); return Token_Evenement;}
  if (strcmp(temp, "genere") == 0) {free(temp); return Token_Genere;}
  if (strcmp(temp, "par") == 0) {free(temp); return Token_Par;}
  if (strcmp(temp, "traitement") == 0) {free(temp); return Token_Traitement;}
  if (strcmp(temp, "objet") == 0) {free(temp); return Token_Objet;}
  if (strcmp(temp, "texture") == 0) {free(temp); return Token_Texture;}
  if (strcmp(temp, "textures") == 0) {free(temp); return Token_Textures;}
  if (strcmp(temp, "angle") == 0) {free(temp); return Token_Angle;}
  if (strcmp(temp, "qui") == 0) {free(temp); return Token_Qui;}
  if (strcmp(temp, "x") == 0) {free(temp); return Token_X;}
  if (strcmp(temp, "y") == 0) {free(temp); return Token_Y;}
  if (strcmp(temp, "z") == 0) {free(temp); return Token_Z;}
  if (strcmp(temp, "tous") == 0) {free(temp); return Token_Tous;}
  if (strcmp(temp, "aucun") == 0) {free(temp); return Token_Aucun;}
  if (strcmp(temp, "de") == 0) {free(temp); return Token_De;}
  if (strcmp(temp, "image") == 0) {free(temp); return Token_Image;}

  if (strcmp(temp, "anime") == 0) {free(temp); return Token_Anime;}
  if (strcmp(temp, "fichier") == 0) {free(temp); return Token_Fichier;}
  if (strcmp(temp, "niveau") == 0) {free(temp); return Token_Niveau;}
  if (strcmp(temp, "indice") == 0) {free(temp); return Token_Indice;}
  if (strcmp(temp, "arme") == 0) {free(temp); return Token_Arme;}
  if (strcmp(temp, "position") == 0) {free(temp); return Token_Position;}

  if (strcmp(temp, "musique") == 0) {free(temp); return Token_Musique;}
  if (strcmp(temp, "eau") == 0) {free(temp); return Token_Eau;}
  if (strcmp(temp, "vie") == 0) {free(temp); return Token_Vie;}
  if (strcmp(temp, "teleportation") == 0) {free(temp); return Token_Teleportation;}
  if (strcmp(temp, "destination") == 0) {free(temp); return Token_Destination;}
  if (strcmp(temp, "dimension") == 0) {free(temp); return Token_Dimension;}
  if (strcmp(temp, "longueur") == 0) {free(temp); return Token_Longueur;}
  if (strcmp(temp, "largeur") == 0) {free(temp); return Token_Largeur;}
  if (strcmp(temp, "hauteur") == 0) {free(temp); return Token_Hauteur;}
  if (strcmp(temp, "direction") == 0) {free(temp); return Token_Direction;}
  if (strcmp(temp, "parcours") == 0) {free(temp); return Token_Parcours;}
  if (strcmp(temp, "gauche") == 0) {free(temp); return Token_Gauche;}
  if (strcmp(temp, "droite") == 0) {free(temp); return Token_Droite;}
  if (strcmp(temp, "haut") == 0) {free(temp); return Token_Haut;}
  if (strcmp(temp, "bas") == 0) {free(temp); return Token_Bas;}

  if (strcmp(temp, "div") == 0) {free(temp); return Token_DivEntier;}
  if (strcmp(temp, "mod") == 0) {free(temp); return Token_ModEntier;}

  if (strcmp(temp, "vrai") == 0) {free(temp); yycartelval.yybooleen = vrai; return Token_Booleen;}
  if (strcmp(temp, "faux") == 0) {free(temp); yycartelval.yybooleen = faux; return Token_Booleen;}

  if (strcmp(temp, "pi") == 0) {free(temp); yycartelval.yyreel = (double) pi; return Token_Reel;}
  if (strcmp(temp, "e") == 0) {free(temp); yycartelval.yyreel = (double) e; return Token_Reel;}

  if (strcmp(temp, "procedure") == 0) {free(temp); return Token_Procedure;}
  if (strcmp(temp, "procédure") == 0) {free(temp); return Token_Procedure;}

  free(temp);
  return Token_Ident;
}
  

%}


eol \n
blancs [\t\r\ ]+
comment (\/\/[^\n]*)|(#[^\n]*)

chiffre  [0-9]
entier  {chiffre}+
reel    (\.{chiffre}+)|({chiffre}+\.{chiffre}*)

lettre [a-zA-Z]
symbole {lettre}({lettre}|[\-\_\.]|{chiffre})*

chaine \"[^\"]*\"

open_par \(
open_brace \{
open_bracket \[
close_par \)
close_brace \}
close_bracket \]

plusentier \+
moinsentier \-
multentier \*
 //diventier 'd' 'i' 'v'
 //modentier 'm' 'o'd

plusreel \+\.
moinsreel \-\.
multreel \*\.
divreel \/\.


assign \:\=
virgule \,
ptvirg \;



%option noyywrap
%option nounput
%%

<<EOF>>        carte_mess("Fin de fichier atteinte.\nNombre de lignes : %d\nNombre de caractères dans la ligne courante : %d\nNombre total de caractères : %d\n", nb_lignes, nb_chars, nb_chars_tot); return Token_EOF;

{eol}          PRINT_OUT("EOL "); nb_lignes++; nb_chars = 0; 

{blancs}       PRINT_OUT("Blancs ");

{comment}      PRINT_OUT("Commentaire one-line");


"/*"        {
              PRINT_OUT("Commentaire multi-lines");
              int c;

              for (;;) {
                do { c = yyinput(); } while (c != '*' && c != EOF);

                if (c == EOF) {
                  fprintf(yyout, "EOF in comment" );
                  break;
                }

                do c = yyinput(); while (c == '*');

                if (c == '/') break;
              }
            }


{entier} {
  PRINT_OUT("Entier "); 
  yycartelval.yyentier = atoi(yytext); 
  return Token_Entier;
}

{reel} {
  PRINT_OUT("Reel ");
  yycartelval.yyreel = atof(yytext);
  return Token_Reel;
}

{symbole} {
  int token;
  PRINT_OUT("Symbole ");
  token = match_symbole(yytext);

  if (token != Token_Ident) {
    return token;
  }

  //yycartelval.yyident = (char *) malloc((yyleng + 1) * sizeof(char));
  yycartelval.yyident = new char[yyleng + 1];

  if (yycartelval.yyident == NULL) {
    carte_err("Pas assez de mémoire pour continuer.");
    return Token_EOF;
  }

  strcpy(yycartelval.yyident, yytext);
  return token;
}

{chaine} {
  PRINT_OUT("Chaine ");
  //yycartelval.yychaine = (char *) malloc((yyleng - 1) * sizeof(char));
  yycartelval.yychaine = new char[yyleng - 2 + 1];

  if (yycartelval.yychaine == NULL) {
    carte_err("Pas assez de mémoire pour continuer.");
    return Token_EOF;
  }
  
  strncpy(yycartelval.yychaine, &(yytext[1]), yyleng - 2);
  yycartelval.yychaine[yyleng - 2] = '\0';
  return Token_Chaine;
}
  

{open_par}     PRINT_OUT("Open_Par "); return Token_OpenPar;
{open_brace}   PRINT_OUT("Open_Brace "); return Token_OpenBrace;
{open_bracket} PRINT_OUT("Open_Bracket "); return Token_OpenBracket;
 
{close_par}     PRINT_OUT("Close_Par "); return Token_ClosePar;
{close_brace}   PRINT_OUT("Close_Brace "); return Token_CloseBrace;
{close_bracket} PRINT_OUT("Close_Bracket "); return Token_CloseBracket;

{plusreel}         PRINT_OUT("PlusReel ");  return Token_PlusReel;
{moinsreel}        PRINT_OUT("MoinsReel "); return Token_MoinsReel;
{multreel}         PRINT_OUT("MultReel ");  return Token_MultReel;
{divreel}          PRINT_OUT("Div ");   return Token_DivReel;

{plusentier}         PRINT_OUT("PlusEntier ");  return Token_PlusEntier;
{moinsentier}        PRINT_OUT("MoinsEntier "); return Token_MoinsEntier;
{multentier}         PRINT_OUT("MultEntier ");  return Token_MultEntier;


{assign}       PRINT_OUT("Assign ");  return Token_Assign;
{virgule}      PRINT_OUT("Virgule ");  return Token_Virgule;
{ptvirg}       PRINT_OUT("Ptvirg ");  return Token_Ptvirg;

.              PRINT_OUT("Autre ");

%%
/*
// Fonction qui est appelée lorsque EOF est atteint.
// Retourne 0 (false) si on continue.
// Sinon, ça termine et renvoie 0 à l'appelant.
// %option noyywrap
//yywrap(){}
*/
