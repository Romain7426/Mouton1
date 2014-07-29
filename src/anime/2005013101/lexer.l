%{
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "anime.h"
#include "global.h"
#include "parser.hpp"

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

const extern int get_nb_lignes(void) {
 return nb_lignes;
}   

const extern int get_nb_chars(void) {
 return nb_chars;
}   

const extern int get_nb_chars_tot(void) {
 return nb_chars_tot;
}   

const extern int get_yyleng(void) {
 return yyleng;
}   

const extern char * get_yytext(void) {
 return yytext;
}   


const static int match_symbole(char symbole[]) {
  char *temp;
  size_t taille;
  size_t i;

  taille = strlen(symbole);
  temp = (char *) malloc((taille + 1) * sizeof(char));

  if (temp == NULL) {
    PRINT_OUT("Manque de mémoire. On s'arrête.");
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
  if (strcmp(temp, "choc") == 0) {free(temp); return Token_Choc;}
  if (strcmp(temp, "largeur") == 0) {free(temp); return Token_Largeur;}
  if (strcmp(temp, "longueur") == 0) {free(temp); return Token_Longueur;}
  if (strcmp(temp, "hauteur") == 0) {free(temp); return Token_Hauteur;}
  if (strcmp(temp, "masse") == 0) {free(temp); return Token_Masse;}
  if (strcmp(temp, "invinsible") == 0) {free(temp); return Token_Invinsible;}
  if (strcmp(temp, "membres") == 0) {free(temp); return Token_Membres;}
  if (strcmp(temp, "racines") == 0) {free(temp); return Token_Racines;}
  if (strcmp(temp, "action") == 0) {free(temp); return Token_Action;}
  if (strcmp(temp, "laction") == 0) {free(temp); return Token_LAction;}
  if (strcmp(temp, "menu") == 0) {free(temp); return Token_Menu;}
  if (strcmp(temp, "affichage") == 0) {free(temp); return Token_Affichage;}
  if (strcmp(temp, "gestionnaire") == 0) {free(temp); return Token_Gestionnaire;}
  if (strcmp(temp, "evenement") == 0) {free(temp); return Token_Evenement;}
  if (strcmp(temp, "genere") == 0) {free(temp); return Token_Genere;}
  if (strcmp(temp, "par") == 0) {free(temp); return Token_Par;}
  if (strcmp(temp, "traitement") == 0) {free(temp); return Token_Traitement;}
  if (strcmp(temp, "membre") == 0) {free(temp); return Token_Membre;}
  if (strcmp(temp, "fils") == 0) {free(temp); return Token_Fils;}
  if (strcmp(temp, "angle") == 0) {free(temp); return Token_Angle;}
  if (strcmp(temp, "max") == 0) {free(temp); return Token_Max;}
  if (strcmp(temp, "qui") == 0) {free(temp); return Token_Qui;}
  if (strcmp(temp, "x") == 0) {free(temp); return Token_X;}
  if (strcmp(temp, "y") == 0) {free(temp); return Token_Y;}
  if (strcmp(temp, "z") == 0) {free(temp); return Token_Z;}
  if (strcmp(temp, "tous") == 0) {free(temp); return Token_Tous;}
  if (strcmp(temp, "aucun") == 0) {free(temp); return Token_Aucun;}
  if (strcmp(temp, "points") == 0) {free(temp); return Token_Points;}
  if (strcmp(temp, "de") == 0) {free(temp); return Token_De;}
  if (strcmp(temp, "vie") == 0) {free(temp); return Token_Vie;}
  if (strcmp(temp, "hostile") == 0) {free(temp); return Token_Hostile;}
  if (strcmp(temp, "image") == 0) {free(temp); return Token_Image;}

  if (strcmp(temp, "vrai") == 0) {free(temp); yylval.yybooleen = faux; return Token_Booleen;}
  if (strcmp(temp, "faux") == 0) {free(temp); yylval.yybooleen = vrai; return Token_Booleen;}

  if (strcmp(temp, "pi") == 0) {free(temp); yylval.yyreel = (double) pi; return Token_Reel;}
  if (strcmp(temp, "e") == 0) {free(temp); yylval.yyreel = (double) e; return Token_Reel;}

  if (strcmp(temp, "parler") == 0) {free(temp); yylval.yylaction = parler; return Token_LAction;}
  if (strcmp(temp, "voler") == 0) {free(temp); yylval.yylaction = voler; return Token_LAction;}

  free(temp);
  return Token_Ident;
}
  

%}


eol \n
blancs [\t\r\ ]+
comment (\/\/[^\n]*)|(#[^\n]*)|(\/\*[^"*/"]*\*\/)

chiffre  [0-9]
entier  {chiffre}+
reel    (\-?\.{chiffre}+)|(\-?{chiffre}+\.{chiffre}*)

lettre [a-zA-Z]
symbole {lettre}({lettre}|[\-\_\.]|{chiffre})*

chaine \"[^\"]*\"

open_par \(
open_brace \{
open_bracket \[
close_par \)
close_brace \}
close_bracket \]

plus \+
moins \-
mult \*
div \/

assign \:\=
virgule \,
ptvirg \;



%option noyywrap
%option nounput
%%

<<EOF>>        (void) fprintf(yyout, "Fin.\nNombre de lignes : %d\nNombre de caractères dans la ligne courante : %d\nNombre total de caractères : %d\n", nb_lignes, nb_chars, nb_chars_tot); BEGIN(INITIAL); return Token_EOF;

{eol}          PRINT_OUT("EOL "); nb_lignes++; nb_chars = 0; 

{blancs}       PRINT_OUT("Blancs ");

{comment}      PRINT_OUT("Commentaire ");

{entier} {
  PRINT_OUT("Entier "); 
  yylval.yyentier = atoi(yytext); 
  return Token_Entier;
}

{reel} {
  PRINT_OUT("Reel ");
  yylval.yyreel = atof(yytext);
  return Token_Reel;
}

{symbole} {
  int token;
  PRINT_OUT("Symbole ");
  token = match_symbole(yytext);

  if (token != Token_Ident) {
    return token;
  }

  yylval.yyident = (char *) malloc((yyleng + 1) * sizeof(char));

  if (yylval.yyident == NULL) {
    PRINT_OUT("Pas assez de mémoire pour continuer.");
    return Token_EOF;
  }

  strcpy(yylval.yyident, yytext);
  return token;
}

{chaine} {
  PRINT_OUT("Chaine ");
  yylval.yychaine = (char *) malloc((yyleng - 1) * sizeof(char));

  if (yylval.yychaine == NULL) {
    PRINT_OUT("Pas assez de mémoire pour continuer.");
    return Token_EOF;
  }
  
  strncpy(yylval.yychaine, &(yytext[1]), yyleng - 2);
  yylval.yychaine[yyleng - 2] = '\0';
  return Token_Chaine;
}
  

{open_par}     PRINT_OUT("Open_Par "); return Token_OpenPar;
{open_brace}   PRINT_OUT("Open_Brace "); return Token_OpenBrace;
{open_bracket} PRINT_OUT("Open_Bracket "); return Token_OpenBracket;
 
{close_par}     PRINT_OUT("Close_Par "); return Token_ClosePar;
{close_brace}   PRINT_OUT("Close_Brace "); return Token_CloseBrace;
{close_bracket} PRINT_OUT("Close_Bracket "); return Token_CloseBracket;

{plus}         PRINT_OUT("Plus ");  return Token_Plus;
{moins}        PRINT_OUT("Moins "); return Token_Moins;
{mult}         PRINT_OUT("Mult ");  return Token_Mult;
{div}          PRINT_OUT("Div ");   return Token_Div;

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
