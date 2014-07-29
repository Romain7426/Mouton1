%{

#include "global.h" 
#include "parser.h"
#include "token.h"
#include "token_liste.h"
#include "arbre.h"
#include "arbre_liste.h"



%}

// type de yylval
// yylval est la valeur du terminal ou du non-terminal courant.
// le lexer doit ecrire dedans la valeur de son terminal.
%union {
  const token_t * token;
  arbre_t * arbre;
  arbre_liste_t * arbre_liste;
}

// Tokens declaration
%token <token> Token_EOF
 //%token <token> Token_Inconnu
%token <token> Token_Lettre
%token <token> Token_LettreAny
%token <token> Token_OpenPar Token_ClosePar
%token <token> Token_OpenBracket Token_CloseBracket
%token <token> Token_OpenBrace Token_CloseBrace
%token <token> Token_Bang
%token <token> Token_Huh
%token <token> Token_Plus
%token <token> Token_Star

// Type d'un non-terminal
%type <arbre_liste> expression_liste
%type <arbre> expression

// non-terminal/terminal de debut
%start main

// option
%debug
//%defines // genere un .h
%name-prefix="parser_"
%output="parser.c"
%pure-parser
%verbose

// Nombre de shift/reduce conflicts expected
//%expect 0
// Nombre de reduce/reduce conflicts expected
//%expect-rr 0

%parse-param {const token_liste_t * liste}
//%parse-param {syntax_tree_liste_t * * exprs}
%parse-param {arbre_t * * arbre}
%parse-param {char * * err}
%parse-param {location_t * * loc}

%lex-param {const token_liste_t * * tokens}
//%lex-param {&liste}

%error-verbose


%{

// TODO c moche, ça m'emmerde comme façon, mais ça marche
// Mais pourquoi ce n'est pas documenté?
#define YYLEX_PARAM &liste

extern int yyparse(const token_liste_t * tokens, arbre_t * * arbre, char * * err, location_t * * loc);

static int yylex(YYSTYPE * lvalp, const token_liste_t * * tokens);
static void yyerror(const token_liste_t * tokens, arbre_t * * arbre, char * * err, location_t * * loc, const char * msg);

static inline int parser_token_of_lexer_token(const token_type_t type);
static inline char token_lexeme_lettre(const char * lexeme);

#define MAKE_ARBRE(z_arbre,z_type,z_liste) {                           \
    arbre_liste_reverse_surplace(&(z_liste));                          \
    (z_arbre) = arbre_make_liste_nocopy((z_type), (z_liste));          \
    arbre_liste_free_nocopy((z_liste));                                \
  }
 
#define MAKE_ARBRE1(z_arbre,z_type,z_fils) {                   \
    (z_arbre) = arbre_make_noeud((z_type), 1);                 \
    arbre_make_fils_add((z_arbre), (z_fils));                  \
  }
    

%}



%%

main:
  expression_liste Token_EOF { 
    MAKE_ARBRE(*arbre,ARBRE_NOEUD_CONCATENATION,($1));
    return 0; // succès
  }
;

expression_liste:
expression_liste expression { $$ = arbre_liste_cons($2,$1); }
|  { $$ = arbre_liste_vide(); }
;

expression:
  Token_Lettre    { $$ = arbre_make_feuille_lettre(token_lexeme_lettre($1 -> lexeme), false); }
| Token_LettreAny { $$ = arbre_make_feuille_any(false); }
| Token_OpenPar     expression_liste Token_ClosePar     { MAKE_ARBRE($$,ARBRE_NOEUD_CONCATENATION,$2); }
| Token_OpenBracket expression_liste Token_CloseBracket { MAKE_ARBRE($$,ARBRE_NOEUD_OU,$2); }
| Token_OpenBrace   expression_liste Token_CloseBrace   { MAKE_ARBRE($$,ARBRE_NOEUD_ET,$2); }
| Token_Bang expression { MAKE_ARBRE1($$,ARBRE_NOEUD_NON,$2); }
| expression Token_Star { MAKE_ARBRE1($$,ARBRE_NOEUD_ETOILE,$1); }
| expression Token_Plus { MAKE_ARBRE1($$,ARBRE_NOEUD_PLUS,$1); }
| expression Token_Huh  { MAKE_ARBRE1($$,ARBRE_NOEUD_01,$1); }
;



%%

int yylex(YYSTYPE * lvalp, const token_liste_t * * tokens) {
  int token;

  if (not(token_liste_vide_huh(*tokens))) {
    token = parser_token_of_lexer_token((*tokens) -> car -> type);
    lvalp -> token = (*tokens) -> car;
    (*tokens) = (*tokens) -> cdr;
  }
  
  else {
    token = Token_EOF;
    lvalp -> token = NULL;
  }

  return token;
}

void yyerror(const token_liste_t * liste, arbre_t * * arbre, char * * err, location_t * * loc, const char * msg) {
  char * s;
  s = token_liste_string(liste);
  asprintf(err, "%s (tokens restants: [%s])", msg, s);
  strfree(s);
}

int parser_token_of_lexer_token(token_type_t type) {
  switch (type) {
  case TOKEN_TYPE_LETTRE:       return Token_Lettre; break;
  case TOKEN_TYPE_LETTRE_ANY:   return Token_LettreAny; break;
  case TOKEN_TYPE_BANG:         return Token_Bang; break;
  case TOKEN_TYPE_HUH:          return Token_Huh; break;
  case TOKEN_TYPE_PLUS:         return Token_Plus; break;
  case TOKEN_TYPE_STAR:         return Token_Star; break;
  case TOKEN_TYPE_OPENPAR:      return Token_OpenPar; break;
  case TOKEN_TYPE_CLOSEPAR:     return Token_ClosePar; break;
  case TOKEN_TYPE_OPENBRACE:    return Token_OpenBrace; break;
  case TOKEN_TYPE_CLOSEBRACE:   return Token_CloseBrace; break;
  case TOKEN_TYPE_OPENBRACKET:  return Token_OpenBracket; break;
  case TOKEN_TYPE_CLOSEBRACKET: return Token_CloseBracket; break;
  case TOKEN_TYPE_EOF:          return Token_EOF; break;
  case TOKEN_TYPE_NOMBRE:       assert(false); break;
  default:                      assert(false); break;
  }
  assert(false);
  return 0;
}


char token_lexeme_lettre(const char * lexeme) {
  const size_t len = strlen(lexeme);

  assert(len == 1 || len == 2);

  if (len == 1)
    return lexeme[0];

  if (len == 2) {
    assert(lexeme[0] == '\\');
    const char c = lexeme[1];
    switch (c) {
    case '0': return '\0'; break;
    case 'a': return '\a'; break;
    case 'b': return '\b'; break;
    case 't': return '\t'; break;
    case 'n': return '\n'; break;
    case 'v': return '\v'; break;
    case 'f': return '\f'; break;
    case 'r': return '\r'; break;
    case 'e': return '\e'; break;
    default: return c; break;
    }
    assert(false);
    return '\0';
  }

  assert(false);
  return '\0';
}
