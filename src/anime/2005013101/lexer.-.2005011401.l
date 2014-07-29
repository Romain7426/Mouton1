%{

#include <stdio.h>
#include "parser.h"
/* yytext yyleng ECHO */
/* Pour faire le pipe, on fait option + maj + l
   Maintenant, on chercher le tilde. */
/* Le tilde, il faut faire option + n + la touche appropriee. */
/* yytext, yyleng, yymore(), yyless, unput(), %array, input(), yyinput(), yyterminate(), yyin, yyout, yyrestart(), yywrap(), yy_scan_string(), yy_scan_buffer(), yy_scan_bytes(), 
*/
/* #define YY_DECL float lexscan( a, b ) float a, b; */
/* int yylex(void) */

static int nb_lignes = 0, nb_char = 0;



%}


eol \n
blanc [\t\r\ ]
comment (\/\/[^\n]*)|(#[^\n]*)|(\/\*[^"*/"]*\*\/)

chiffre  [0-9]
entier  {chiffre}+

lettre [a-zA-Z]
symbole {lettre}({lettre}|[\-\_\.]|{chiffre})+
chaine \"[^\"]\"

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
egal \=


%option noyywrap
%option nounput
%%

<<EOF>>        (void) printf("Fin.\nNombre de lignes : %d\nNombre de caractères : %d\n", nb_lignes, nb_char); return Token_EOF;

{eol}          printf("EOL.\n"); nb_lignes++; nb_char++; 

{blanc}        printf("Blanc.\n"); nb_char += yyleng; 

{comment}      printf("Commentaire.\n"); nb_char += yyleng; 

{entier}       printf("Entier.\n"); nb_char += yyleng; 

{symbole}      printf("Symbole.\n"); nb_char += yyleng; 

{chaine}       printf("Chaine.\n"); nb_char += yyleng; 

{open_par}     printf("Open_Par.\n"); nb_char += yyleng; 
 
{close_par}    printf("Close_Par.\n"); nb_char += yyleng; 

{plus}         printf("Plus.\n"); nb_char += yyleng; 

{moins}        printf("Moins.\n"); nb_char += yyleng; 

{mult}         printf("Mult.\n"); nb_char += yyleng; 

{div}          printf("Div.\n"); nb_char += yyleng; 

.              printf("Autre.\n"); nb_char += yyleng; 

%%
/*
// Fonction qui est appelée lorsque EOF est atteint.
// Retourne 0 (false) si on continue.
// Sinon, ça termine et renvoie 0 à l'appelant.
// %option noyywrap
//yywrap(){}
*/
