%{

  // Fichier lexer du compilateur PASCAL et de la machine virtuelle PASCAL.


#include "global.hpp"
#include "pascal/pascal.tools.hpp"
#include "pascal/pascal.expr.hpp"
#include "pascal/pascal.parser.hpp"


/* yytext yyleng ECHO */
/* Pour faire le pipe, on fait option + maj + l
   Maintenant, on chercher le tilde. option + n + espace */
/* Le tilde, il faut faire option + n + la touche appropriee. */

  static int nb_lignes = 0, nb_char_ligne = 0, nb_char_tot = 0;

  // La file des TOKEN.
  struct stoken {
    int token;
    YYSTYPE yylval;
    unsigned int nb_lignes, nb_char_ligne, nb_char_tot, longueur;
  };
    
  static class pfifo<stoken> *tokens = NULL;

  static int match_symbol(void);


#define TAILLE_TAMPON_SYMBOLE_MAX 4095
  static char symbole[TAILLE_TAMPON_SYMBOLE_MAX + 1];
  static unsigned int taille_tampon_symbole = 0;



  void yypascallexerinit(void) {
    nb_lignes = 0, nb_char_ligne = 0, nb_char_tot = 0;
    while (tokens != NULL) delete popf(tokens);
    taille_tampon_symbole = 0;
  }




  static const char * const string_of_token(int token) {
    switch (token) {
    case TOKEN_EOF: return "EOF"; break;
    case TOKEN_TRUE: return "TRUE"; break;
    case TOKEN_FALSE: return "FALSE"; break;
    case TOKEN_IDENT: return "IDENT"; break;
    case TOKEN_AND: return "AND"; break;
    case TOKEN_OR: return "OR"; break;
    case TOKEN_NOT: return "NOT"; break;
    case TOKEN_IF: return "IF"; break;
    case TOKEN_THEN: return "THEN"; break;
    case TOKEN_ELSE: return "ELSE"; break;
    case TOKEN_BEGIN: return "BEGIN"; break;
    case TOKEN_END: return "END"; break;
    case TOKEN_WHILE: return "WHILE"; break;
    case TOKEN_DO: return "DO"; break;
    case TOKEN_REPEAT: return "REPEAT"; break;
    case TOKEN_UNTIL: return "UNTIL"; break;
    case TOKEN_FOR: return "FOR"; break;
    case TOKEN_TO: return "TO"; break;
    case TOKEN_IPLUS: return "IPLUS"; break;
    case TOKEN_IMOINS: return "IMOINS"; break;
    case TOKEN_IMULT: return "IMULT"; break;
    case TOKEN_IDIV: return "DIV"; break;
    case TOKEN_IMOD: return "IMOD"; break;
    case TOKEN_RPLUS: return "RPLUS"; break;
    case TOKEN_RMOINS: return "RMOINS"; break;
    case TOKEN_RMULT: return "RMULT"; break;
    case TOKEN_RDIV: return "RDIV"; break;
    case TOKEN_ENTIER: return "ENTIER"; break;
    case TOKEN_REEL: return "REEL"; break;
    case TOKEN_PTVIRG: return "POINT VIRGULE"; break;
    case TOKEN_CHAINE: return "CHAINE"; break;
    case TOKEN_OPENPAR: return "PARENTHESE OUVRANTE"; break;
    case TOKEN_CLOSEPAR: return "PARENTHESE FERMANTE"; break;
    case TOKEN_BLANC: return "BLANCS"; break;
    case TOKEN_COMMENT: return "COMMENTAIRE"; break;
    case TOKEN_EQUAL: return "EQUAL"; break;
    case TOKEN_INF: return "INF"; break;
    case TOKEN_SUP: return "SUP"; break;
    case TOKEN_INFEQ: return "INFEQ"; break;
    case TOKEN_SUPEQ: return "SUPEQ"; break;
    case TOKEN_TYPE: return "TYPE"; break;
    case TOKEN_PTR: return "PTR"; break;
    case TOKEN_REF: return "REF"; break;
    case TOKEN_ARRAY: return "ARRAY"; break;
    case TOKEN_OF: return "OF"; break;
    case TOKEN_RECORD: return "RECORD"; break;
    case TOKEN_AFFECTATION: return "AFFECTATION"; break;
    case TOKEN_WRITE: return "WRITE"; break;
    case TOKEN_WRITELN: return "WRITELN"; break;
    case TOKEN_READ: return "READ"; break;
    case TOKEN_READLN: return "READLN"; break;
    case TOKEN_DEUXPOINTS: return "DEUX POINTS"; break;
    case TOKEN_OPENBRACKET: return "CROCHET OUVRANT"; break;
    case TOKEN_CLOSEBRACKET: return "CROCHET FERMANT"; break;
    case TOKEN_VAR: return "VAR"; break;
    case TOKEN_CONST: return "CONST"; break;
    case TOKEN_BOOLEAN: return "BOOLEAN"; break;
    case TOKEN_INTEGER: return "INTEGER"; break;
    case TOKEN_SUBRANGE: return "SUBRANGE"; break;
    case TOKEN_REAL: return "REAL"; break;
    case TOKEN_PROCEDURE: return "PROCEDURE"; break;
    case TOKEN_FUNCTION: return "FUNCTION"; break;
    case TOKEN_VIRGULE: return "VIRGULE"; break;
    case TOKEN_POINT: return "POINT"; break;
    case TOKEN_DIFF: return "DIFF"; break;
    case TOKEN_NIL: return "NIL"; break;
    case TOKEN_NEW: return "NEW"; break;
    case TOKEN_MUSIQUE: return "MUSIQUE"; break;
    case TOKEN_MENU: return "MENU"; break;
    case TOKEN_ITEM: return "ITEM"; break;
    case TOKEN_STRING: return "STRING"; break;

    case TOKEN_FLECHE: return "FLECHE"; break;
      //case TOKEN_HEROS: return "HEROS"; break;
    case TOKEN_CAMERA: return "CAMERA"; break;
    case TOKEN_WAIT: return "WAIT"; break;
    case TOKEN_HALT: return "HALT"; break;
    case TOKEN_RESTART: return "RESTART"; break;
    case TOKEN_FONDU: return "FONDU"; break;
    case TOKEN_RECOBJET: return "RECEVOIROBJET"; break;
    case TOKEN_RECARME: return "RECEVOIRARME"; break;
    case TOKEN_SUPOBJET: return "SUPPRIMEROBJET"; break;
    case TOKEN_CARTE: return "CARTE"; break;
    case TOKEN_SETPOSITION: return "SETPOSITION"; break;
    case TOKEN_DEPLACER: return "DEPLACER"; break;
    case TOKEN_SETPOSITIONZ: return "SETPOSITIONZ"; break;
    case TOKEN_DEPLACERZ: return "DEPLACER"; break;
    case TOKEN_ROTATE: return "ROTATE"; break;
    case TOKEN_SOLIDARISER: return "SOLIDARISER"; break;
    case TOKEN_DESOLIDARISER: return "DESOLIDARISER"; break;
    case TOKEN_DEFAUT: return "DEFAUT"; break;
    case TOKEN_ZOOM: return "ZOOM"; break;
    case TOKEN_FRAPPER: return "FRAPPER"; break;
    case TOKEN_AJOUTERANIME: return "AJOUTERANIME"; break;
    case TOKEN_AJOUTERNONANIME: return "AJOUTERNONANIME"; break;
    case TOKEN_SETTEMPS: return "SETTEMPS"; break;
    case TOKEN_SETORIENTATION: return "SETORIENTATION"; break;
    case TOKEN_NOMCARTE: return "NOMCARTE"; break;
    case TOKEN_WAITFOR: return "WAITFOR"; break;
    case TOKEN_BLOQUERTEMPS: return "BLOQUERTEMPS"; break;
    case TOKEN_DEBLOQUERTEMPS: return "DEBLOQUERTEMPS"; break;
    case TOKEN_CARTEZ: return "CARTEZ"; break;
    default:
      return "INCONNU";
    }
  }



#define _PRINT_OUT(a,b,c)						\
  {									\
    fprintf(yyout, "{{ symbole %s [ %s ] }}", string_of_token(a), (b));	\
    fflush(yyout);                                                      \
    nb_char_tot += (c);							\
    nb_char_ligne += (c);						\
  }

#define __PRINT_OUT(a)  						\
  {									\
    fprintf(yyout, "\n---> symbole %s \n", string_of_token(a));         \
  }

#define PRINT_OUT(a,b)											\
  {													\
    {													\
      if (taille_tampon_symbole > 0)									\
	{												\
	  struct stoken* temp;										\
	  temp = new struct stoken;									\
	  temp->nb_lignes = nb_lignes;									\
	  temp->nb_char_ligne = nb_char_ligne;								\
	  temp->nb_char_tot = nb_char_tot;								\
	  temp->longueur = taille_tampon_symbole;							\
	  temp->token = match_symbol();									\
	  {												\
	    if (temp->token == TOKEN_IDENT)								\
	      {                                                         				\
		temp->yylval.token.val.ident = strcpy(new char[taille_tampon_symbole + 1], symbole);	\
              }                            								\
          }												\
	  tokens = mf(temp, tokens);									\
	  _PRINT_OUT(temp->token, symbole, taille_tampon_symbole);					\
	  taille_tampon_symbole = 0;									\
	}												\
    }													\
    _PRINT_OUT(a, b, yyleng);										\
  }													\



#define DO_ACTION(TOKEN,TEXT,WHAT)              \
  {						\
  struct stoken  *temp;				\
						\
  PRINT_OUT(TOKEN, TEXT);                       \
						\
  temp = new struct stoken;			\
  temp->token = TOKEN;				\
  temp->yylval.token.val.WHAT; 		        \
  temp->nb_lignes = nb_lignes;			\
  temp->nb_char_ligne = nb_char_ligne;		\
  temp->nb_char_tot = nb_char_tot;		\
  temp->longueur = yyleng;       		\
			                        \
  tokens = mf(temp, tokens);			\
						\
  temp = popf(tokens);				\
						\
  yypascallval = temp->yylval;			\
  int ret =  temp->token;			\
  delete temp;					\
  __PRINT_OUT(ret);                             \
  return ret;					\
}





  // Fonction qui matche un symbole, le convertit en minuscule 
  // (le langage est case insensitive pour les mots-clefs,
  // mais pas pour le reste).
  static int match_symbol(void) {
    symbole[taille_tampon_symbole] = '\0';

    if (strcasecmp("not", symbole) == 0) {return TOKEN_NOT;}
    else if (strcasecmp("true"   , symbole) == 0) {return TOKEN_TRUE;}
    else if (strcasecmp("false"  , symbole) == 0) {return TOKEN_FALSE;}
    else if (strcasecmp("and"    , symbole) == 0) {return TOKEN_AND;}
    else if (strcasecmp("or"     , symbole) == 0) {return TOKEN_OR;}
    else if (strcasecmp("div"    , symbole) == 0) {return TOKEN_IDIV;}
    else if (strcasecmp("mod"    , symbole) == 0) {return TOKEN_IMOD;}
    else if (strcasecmp("if"     , symbole) == 0) {return TOKEN_IF;}
    else if (strcasecmp("then"   , symbole) == 0) {return TOKEN_THEN;}
    else if (strcasecmp("else"   , symbole) == 0) {return TOKEN_ELSE;}
    else if (strcasecmp("while"  , symbole) == 0) {return TOKEN_WHILE;}
    else if (strcasecmp("do"     , symbole) == 0) {return TOKEN_DO;}
    else if (strcasecmp("for"    , symbole) == 0) {return TOKEN_FOR;}
    else if (strcasecmp("to"     , symbole) == 0) {return TOKEN_TO;}
    else if (strcasecmp("begin"  , symbole) == 0) {return TOKEN_BEGIN;}
    else if (strcasecmp("var"    , symbole) == 0) {return TOKEN_VAR;}
    else if (strcasecmp("end"    , symbole) == 0) {return TOKEN_END;}
    else if (strcasecmp("repeat" , symbole) == 0) {return TOKEN_REPEAT;}
    else if (strcasecmp("until"  , symbole) == 0) {return TOKEN_UNTIL;}
    else if (strcasecmp("type"   , symbole) == 0) {return TOKEN_TYPE;}
    else if (strcasecmp("boolean", symbole) == 0) {return TOKEN_BOOLEAN;}
    else if (strcasecmp("integer", symbole) == 0) {return TOKEN_INTEGER;}
    else if (strcasecmp("real"   , symbole) == 0) {return TOKEN_REAL;}
    else if (strcasecmp("string" , symbole) == 0) {return TOKEN_STRING;}
    else if (strcasecmp("array"  , symbole) == 0) {return TOKEN_ARRAY;}
    else if (strcasecmp("of"     , symbole) == 0) {return TOKEN_OF;}
    else if (strcasecmp("record" , symbole) == 0) {return TOKEN_RECORD;}
    else if (strcasecmp("write"  , symbole) == 0) {return TOKEN_WRITE;}
    else if (strcasecmp("writeln", symbole) == 0) {return TOKEN_WRITELN;}
    else if (strcasecmp("read"   , symbole) == 0) {return TOKEN_READ;}
    else if (strcasecmp("readln" , symbole) == 0) {return TOKEN_READLN;}
    else if (strcasecmp("const"  , symbole) == 0) {return TOKEN_CONST;}
    else if (strcasecmp("procedure", symbole) == 0) {return TOKEN_PROCEDURE;}
    else if (strcasecmp("function", symbole) == 0) {return TOKEN_FUNCTION;}
    else if (strcasecmp("virgule", symbole) == 0) {return TOKEN_VIRGULE;}
    else if (strcasecmp("nil"    , symbole) == 0) {return TOKEN_NIL;}
    else if (strcasecmp("new"    , symbole) == 0) {return TOKEN_NEW;}
    else if (strcasecmp("musique", symbole) == 0) {return TOKEN_MUSIQUE;}
    else if (strcasecmp("menu"   , symbole) == 0) {return TOKEN_MENU;}
    else if (strcasecmp("item"   , symbole) == 0) {return TOKEN_ITEM;}

    //    else if (strcasecmp("héros"         , symbole) == 0) {return TOKEN_HEROS;}
    //else if (strcasecmp("heros"         , symbole) == 0) {return TOKEN_HEROS;}
    else if (strcasecmp("caméra"        , symbole) == 0) {return TOKEN_CAMERA;}
    else if (strcasecmp("camera"        , symbole) == 0) {return TOKEN_CAMERA;}
    else if (strcasecmp("wait"          , symbole) == 0) {return TOKEN_WAIT;}
    else if (strcasecmp("halt"          , symbole) == 0) {return TOKEN_HALT;}
    else if (strcasecmp("restart"       , symbole) == 0) {return TOKEN_RESTART;}
    else if (strcasecmp("fondu"         , symbole) == 0) {return TOKEN_FONDU;}
    else if (strcasecmp("recevoirobjet" , symbole) == 0) {return TOKEN_RECOBJET;}
    else if (strcasecmp("recevoirarme"  , symbole) == 0) {return TOKEN_RECARME;}
    else if (strcasecmp("supprimerobjet", symbole) == 0) {return TOKEN_SUPOBJET;}
    else if (strcasecmp("carte"         , symbole) == 0) {return TOKEN_CARTE;}
    else if (strcasecmp("setposition"   , symbole) == 0) {return TOKEN_SETPOSITION;}
    else if (strcasecmp("setpositionz"  , symbole) == 0) {return TOKEN_SETPOSITIONZ;}
    else if (strcasecmp("deplacer"      , symbole) == 0) {return TOKEN_DEPLACER;}
    else if (strcasecmp("déplacer"      , symbole) == 0) {return TOKEN_DEPLACER;}
    else if (strcasecmp("deplacerz"     , symbole) == 0) {return TOKEN_DEPLACERZ;}
    else if (strcasecmp("déplacerz"     , symbole) == 0) {return TOKEN_DEPLACERZ;}
    else if (strcasecmp("rotate"        , symbole) == 0) {return TOKEN_ROTATE;}
    else if (strcasecmp("solidariser"   , symbole) == 0) {return TOKEN_SOLIDARISER;}
    else if (strcasecmp("désolidariser" , symbole) == 0) {return TOKEN_DESOLIDARISER;}
    else if (strcasecmp("desolidariser" , symbole) == 0) {return TOKEN_DESOLIDARISER;}
    else if (strcasecmp("defaut"        , symbole) == 0) {return TOKEN_DEFAUT;}
    else if (strcasecmp("défaut"        , symbole) == 0) {return TOKEN_DEFAUT;}
    else if (strcasecmp("zoom"          , symbole) == 0) {return TOKEN_ZOOM;}
    else if (strcasecmp("frapper"       , symbole) == 0) {return TOKEN_FRAPPER;}
    else if (strcasecmp("ajouteranime"  , symbole) == 0) {return TOKEN_AJOUTERANIME;}
    else if (strcasecmp("ajouternonanime", symbole) == 0) {return TOKEN_AJOUTERNONANIME;}
    else if (strcasecmp("settemps"      , symbole) == 0) {return TOKEN_SETTEMPS;}
    else if (strcasecmp("setorientation", symbole) == 0) {return TOKEN_SETORIENTATION;}
    else if (strcasecmp("nomcarte"      , symbole) == 0) {return TOKEN_NOMCARTE;}
    else if (strcasecmp("waitfor"       , symbole) == 0) {return TOKEN_WAITFOR;}
    else if (strcasecmp("bloquertemps"  , symbole) == 0) {return TOKEN_BLOQUERTEMPS;}
    else if (strcasecmp("debloquertemps", symbole) == 0) {return TOKEN_DEBLOQUERTEMPS;}
    else if (strcasecmp("cartez"        , symbole) == 0) {return TOKEN_CARTEZ;}
    else {return TOKEN_IDENT;}
  }



%}

eol \n

blanc [\t\r\ ]
blancs {blanc}+
comment \{[^\}]*\}

chiffre  [0-9]
entier  {chiffre}+
		 //reel ({entier}\.{chiffre}*)|({chiffre}*\.{entier})
reel ({entier}\.{entier})

chaine (\'[^\']*\')|(\"[^\"]*\")

open_par \(
open_bracket \[
close_par \)
close_bracket \]

iplus \+
imoins \-
imult \*

rplus \+\.
rmoins \-\.
rmult \*\.
rdiv \/.

equal \=
inf \<
sup \>
infeq \<\=
supeq \>\=


ptr \^
ref \&

deuxpoints \:
subrange \.\.
ptvirg \;
virgule \,
point \.
diff \<\>

affectation \:\=

fleche \-\>


  // En l'occurrence, comme j'ai une interface avec une file de tokens,
  // je recommence tout le temps en rempilant à chaque fois.
  // NON. En fait, on fait comme avant.
  // Ce qui permet de matcher la règle <<EOF>> comme toutes les autres.
%option noyywrap
%option nounput

  
  // ter   {						
  //   struct stoken  *temp;				
  
  //   PRINT_OUT(TOKEN_EGAL, "TEXT");                       
  
  //   temp = new struct stoken;			
  //   temp->token = TOKEN_EGAL;				
  //   temp->yylval.entier = 0;				
  //   temp->nb_lignes = nb_lignes;			
  //   temp->nb_char_ligne = nb_char_ligne;		
  //   temp->nb_char_tot = nb_char_tot;		
  
  //   tokens = mf(temp, tokens);			
  
  //   temp = tokens->a;				
  //   //tokens = tokens->suivant;			
  //   tokens->a = tokens->suivant->a;               
  //   tokens->suivant = tokens->suivant->suivant;   
  
  //   yypascallval = temp->yylval;			
  //   int ret =  temp->token;			
  //   delete temp;					
  //   return ret;					
  // }
%%


<<EOF>>        DO_ACTION(TOKEN_EOF, "EOF", entier = 0);

{eol}          PRINT_OUT(TOKEN_BLANC, "EOL"); nb_lignes++; nb_char_ligne = 0;// yypascalcontinue();

{blancs}       PRINT_OUT(TOKEN_BLANC, yytext); //yycontinue();

{comment}      PRINT_OUT(TOKEN_COMMENT, yytext); //yycontinue();

{entier}       DO_ACTION(TOKEN_ENTIER,yytext,entier = atoi(yytext));

{reel}         DO_ACTION(TOKEN_REEL,yytext,reel = ((double) atof(yytext)));

{chaine}       {
                 char *ctemp;
		 ctemp = new char [yyleng - 2 + 1];
		 strncpy(ctemp, &(yytext[1]), yyleng - 2);
		 ctemp[yyleng - 2] = '\0';
		 DO_ACTION(TOKEN_CHAINE,yytext,chaine = ctemp);
               }

{open_par}     DO_ACTION(TOKEN_OPENPAR,yytext,entier = 0);

{open_bracket} DO_ACTION(TOKEN_OPENBRACKET,yytext,entier = 0);

{close_par}    DO_ACTION(TOKEN_CLOSEPAR,yytext,entier = 0);

{close_bracket} DO_ACTION(TOKEN_CLOSEBRACKET,yytext,entier = 0);

{iplus}        DO_ACTION(TOKEN_IPLUS,yytext,entier = 0);

{imoins}       DO_ACTION(TOKEN_IMOINS,yytext,entier = 0);

{imult}        DO_ACTION(TOKEN_IMULT,yytext,entier = 0);

{rplus}        DO_ACTION(TOKEN_RPLUS,yytext,entier = 0);

{rmoins}       DO_ACTION(TOKEN_RMOINS,yytext,entier = 0);

{rmult}        DO_ACTION(TOKEN_RMULT,yytext,entier = 0);

{rdiv}         DO_ACTION(TOKEN_RDIV,yytext,entier = 0);

{equal}        DO_ACTION(TOKEN_EQUAL,yytext,entier = 0);

{inf}          DO_ACTION(TOKEN_INF,yytext,entier = 0);

{sup}          DO_ACTION(TOKEN_SUP,yytext,entier = 0);

{infeq}        DO_ACTION(TOKEN_INFEQ,yytext,entier = 0);

{supeq}        DO_ACTION(TOKEN_SUPEQ,yytext,entier = 0);

{ptr}          DO_ACTION(TOKEN_PTR,yytext,entier = 0);

{ref}          DO_ACTION(TOKEN_REF,yytext,entier = 0);

{affectation}  DO_ACTION(TOKEN_AFFECTATION,yytext,entier = 0);

{subrange}     DO_ACTION(TOKEN_SUBRANGE,yytext,entier = 0);

{deuxpoints}   DO_ACTION(TOKEN_DEUXPOINTS,yytext,entier = 0);

{ptvirg}       DO_ACTION(TOKEN_PTVIRG,yytext,entier = 0);

{virgule}      DO_ACTION(TOKEN_VIRGULE,yytext,entier = 0);

{point}        DO_ACTION(TOKEN_POINT,yytext,entier = 0);

{diff}         DO_ACTION(TOKEN_DIFF,yytext,entier = 0);

{fleche}       DO_ACTION(TOKEN_FLECHE,yytext,entier = 0);


.              {
                 if (taille_tampon_symbole >= TAILLE_TAMPON_SYMBOLE_MAX) {
		   fprintf(yyout, "Erreur de lexing. On a un symbole de plus de %u caractères. On skippe le caractère '%s'.", TAILLE_TAMPON_SYMBOLE_MAX, yytext);
		 }
		 else {
		   symbole[taille_tampon_symbole++] = yytext[0];
		 }
		 //yycontinue();
               }

%%
/*
// Fonction qui est appelée lorsque EOF est atteint.
// Retourne 0 (false) si on continue.
// Sinon, ça termine et renvoie 0 à l'appelant.
// %option noyywrap --> scanner behave as if it returns always true (1).
//
// La règle spéciale <<EOF>> est matchée lorsqu'on rencontre une fin de fichier,
// et que la fonction yywrap() retourne vrai (valeur différente de zéro ; i.e.,
// no further file to process).
//yywrap(){}
*/
