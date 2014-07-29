%{

#include <stdio.h>
/* yytext yyleng ECHO */
/* Pour faire le pipe, on fait option + maj + l
   Maintenant, on chercher le tilde. */
/* Le tilde, il faut faire option + n + la touche appropriee. */

static int nb_lignes = 0, nb_char = 0;



%}


eol \n
blanc [\t\r\ ]
comment (\/\/[^\n]*)|(#[^\n]*)|(\/\*[^"*/"]*\*\/)

chiffre  [0-9]
entier  {chiffre}+

lettre [a-zA-Z]
symbole {lettre}[{lettre}\-\_\.{chiffre}]+
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

<<EOF>>        printf("Fin.\n"); exit(0);

{eol}          nb_lignes++; printf("EOL.\n");

{blanc}        printf("Blanc.\n");

{comment}      printf("Commentaire.\n");

{entier}       printf("Entier.\n");

{symbole}      printf("Symbole.\n");

{chaine}       printf("Chaine.\n");

{open_par}     printf("Open_Par.\n");

{close_par}    printf("Close_Par.\n");

{plus}         printf("Plus.\n");

{moins}        printf("Moins.\n");

{mult}         printf("Mult.\n");

{div}          printf("Div.\n");

.              printf("Autre.\n");

%%
/*
// Fonction qui est appelée lorsque EOF est atteint.
// Retourne 0 (false) si on continue.
// Sinon, ça termine et renvoie 0 à l'appelant.
// %option noyywrap
//yywrap(){}
*/
