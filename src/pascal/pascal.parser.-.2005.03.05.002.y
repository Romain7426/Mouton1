%{ /* Header */
#include <stdlib.h>
#include <stdio.h>
#include "pascal.expr.hpp"
#include "pascal.tools.hpp"

const static void yyerror(char s[]);

extern int yypascallex(void);

//ppos position(pascal_position((unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1));

/*
#define NEW_EXPR new CPexpr($1.position.nb_lignes, $1.position.nb_lignes, $1.position.nb_char_ligne, $1.position.nb_char_ligne + $1.position.longueur, $1.position.nb_char_tot, $1.position.nb_char_tot + $1.position.longueur)

#define CODE_CONSTANTE_BOOLEENNE { $$.position = $1.position; $$.val.expr = NEW_EXPR; $$.val.expr->type = CPexpr::PConst; $$.val.expr->val.upconst.pconst.type.type = pevaltype::PETBoolean; $$.val.expr->val.upconst.pconst.val.val.b = $1.val.booleen; }
*/
%}

/* Le type de yylval. */

%union {
  struct {
    struct {
      unsigned int nb_lignes;
      unsigned int nb_char_ligne;
      unsigned int nb_char_tot;
      unsigned int longueur;
    } position;
    union {
      bool booleen;
      int entier;
      double reel;
      char *chaine;
      char *ident;
    } val;
  } token;

  struct CPexpr *expr;
}

/*
%union {
  boolt *booleen;
  intt *entier;
  doublet *reel;
  chart *chaine;
  chart *ident;
  
  cpexprt *expr;
}
*/
// Les terminaux.
%token <token> TOKEN_TRUE
%token <token> TOKEN_FALSE
%token <token> TOKEN_ENTIER
%token <token> TOKEN_REEL
%token <token> TOKEN_CHAINE
%token <token> TOKEN_IDENT


%token TOKEN_EOF
%token TOKEN_TRUE TOKEN_FALSE
%token <token> TOKEN_NOT TOKEN_AND TOKEN_OR
%token <token> TOKEN_EQUAL TOKEN_DIFF TOKEN_INF TOKEN_SUP TOKEN_INFEQ TOKEN_SUPEQ
%token <token> TOKEN_IPLUS TOKEN_IMOINS TOKEN_IMULT TOKEN_IDIV TOKEN_IMOD
%token <token> TOKEN_RPLUS TOKEN_RMOINS TOKEN_RMULT TOKEN_RDIV
%token <token> TOKEN_PTR
%token <token> TOKEN_TYPE TOKEN_BOOLEAN TOKEN_INTEGER TOKEN_SUBRANGE TOKEN_REAL TOKEN_STRING
%token <token> TOKEN_ARRAY TOKEN_OF TOKEN_RECORD
%token <token> TOKEN_PTVIRG
%token <token> TOKEN_AFFECTATION
%token <token> TOKEN_IF TOKEN_THEN TOKEN_ELSE
%token <token> TOKEN_WHILE TOKEN_DO
%token <token> TOKEN_FOR TOKEN_TO
%token <token> TOKEN_REPEAT TOKEN_UNTIL
%token <token> TOKEN_BEGIN TOKEN_END
%token <token> TOKEN_WRITE TOKEN_WRITELN TOKEN_READ TOKEN_READLN

%token <token> TOKEN_PROCEDURE TOKEN_FUNCTION

%token <token> TOKEN_CONST TOKEN_VAR
%token <token> TOKEN_OPENPAR TOKEN_CLOSEPAR
%token <token> TOKEN_OPENBRACKET TOKEN_CLOSEBRACKET
%token <token> TOKEN_VIRG TOKEN_DEUXPOINTS TOKEN_BLANC TOKEN_COMMENT TOKEN_VIRGULE TOKEN_POINT


// Les productions ou non terminals.
%type <expr> booleen
%type <expr> valeur
%type <expr> expr7 expr6 expr5 expr4 expr3 expr2 expr1 expr








%start main

%%

main: liste_declaration TOKEN_EOF { return 0; };

liste_declaration: 
  liste_declaration declaration
| 
  ;

declaration:
  decl_constante
| decl_type
| decl_variable
| decl_procedure
| decl_fonction
  ;

decl_constante: 
  TOKEN_CONST liste_decl_constante1
  ;

liste_decl_constante1:
  decl_constante1 liste_decl_constante1
| decl_constante1
  ;

decl_constante1:
  TOKEN_IDENT TOKEN_EQUAL expr TOKEN_PTVIRG
  ;

decl_type:
  TOKEN_TYPE liste_decl_type1
  ;

liste_decl_type1:
  decl_type1 liste_decl_type1
| decl_type1
  ;

decl_type1:
  TOKEN_IDENT TOKEN_EQUAL type TOKEN_PTVIRG
  ;

decl_variable:
  TOKEN_VAR liste_decl_variable1
  ;

liste_decl_variable1:
  liste_decl_variable1 decl_variable1
| decl_variable1
  ;

decl_variable1:
  liste_ident TOKEN_DEUXPOINTS type TOKEN_PTVIRG
  ;

liste_ident:
  liste_ident TOKEN_IDENT
| TOKEN_IDENT
  ;

type:
  TOKEN_BOOLEAN
| TOKEN_INTEGER
| subrange
| TOKEN_REAL
| TOKEN_STRING
| pointer
| array
| record
| TOKEN_IDENT
  ;

subrange:
  valeur TOKEN_SUBRANGE valeur
  ;

pointer:
  TOKEN_PTR type
  ;

array:
  TOKEN_ARRAY TOKEN_OPENBRACKET subrange TOKEN_CLOSEBRACKET TOKEN_OF type
  ;

record:
  TOKEN_RECORD liste_decl_champ TOKEN_END
  ;

liste_decl_champ:
  liste_decl_champ TOKEN_IDENT TOKEN_DEUXPOINTS type TOKEN_PTVIRG
|
  ;

decl_procedure: 
  TOKEN_PROCEDURE TOKEN_IDENT TOKEN_OPENPAR liste_parametre TOKEN_CLOSEPAR TOKEN_PTVIRG 
  decl_variable2
  corps
  TOKEN_PTVIRG
  ;

decl_fonction: 
  TOKEN_FUNCTION TOKEN_IDENT TOKEN_OPENPAR liste_parametre TOKEN_CLOSEPAR TOKEN_DEUXPOINTS type TOKEN_PTVIRG 
  decl_variable2
  corps
  TOKEN_PTVIRG
  ;

decl_variable2:
  decl_variable
|
  ;

liste_parametre:
  parametre liste_parametre1
| 
  ;

liste_parametre1:
  liste_parametre1 TOKEN_PTVIRG parametre
| 
  ;

parametre: 
  parametre_copier
| parametre_ref
  ;

parametre_copier:
  TOKEN_IDENT TOKEN_DEUXPOINTS type
  ;

parametre_ref:
  TOKEN_VAR TOKEN_IDENT TOKEN_DEUXPOINTS type
  ;


corps: 
  begin
  ;

liste_instruction: 
  liste_instruction1 instruction
| instruction
  ;

liste_instruction1:
  liste_instruction1 instruction TOKEN_PTVIRG
| instruction TOKEN_PTVIRG
  ;

instruction:
  begin
| skip
| if
| ifelse
| while
| for
| affectation 
| repeat
| write
| writeln
| read
| readln
| appel
  ;

skip: ;

begin:
  TOKEN_BEGIN liste_instruction TOKEN_END
  ;


if:
TOKEN_IF expr TOKEN_THEN instruction TOKEN_END
;

ifelse:
TOKEN_IF expr TOKEN_THEN instruction TOKEN_ELSE instruction TOKEN_END
;

while:
TOKEN_WHILE expr TOKEN_DO instruction
;

for:
TOKEN_FOR TOKEN_IDENT TOKEN_AFFECTATION expr TOKEN_TO expr TOKEN_DO instruction
;

affectation:
expr TOKEN_AFFECTATION expr
;

repeat:
TOKEN_REPEAT liste_instruction TOKEN_UNTIL expr
;

write:
TOKEN_WRITE TOKEN_OPENPAR liste_argument TOKEN_CLOSEPAR
;
writeln:
TOKEN_WRITELN TOKEN_OPENPAR liste_argument TOKEN_CLOSEPAR
;
read:
TOKEN_READ TOKEN_OPENPAR liste_argument TOKEN_CLOSEPAR
;
readln:
TOKEN_READLN TOKEN_OPENPAR liste_argument TOKEN_CLOSEPAR
;

appel:
TOKEN_IDENT TOKEN_OPENPAR liste_argument TOKEN_CLOSEPAR
;



liste_argument:
  liste_argument1 argument
| 
  ;

liste_argument1:
  liste_argument1 argument TOKEN_VIRGULE
|
  ;

argument:
  expr
  ;


expr: 
  expr TOKEN_OR  expr1 {}
| expr TOKEN_AND expr1 {}
| expr1 {}
  ;


expr1:
  expr1 TOKEN_EQUAL expr2 {}
| expr1 TOKEN_DIFF  expr2 {}
| expr1 TOKEN_INF   expr2 {}
| expr1 TOKEN_SUP   expr2 {}
| expr1 TOKEN_INFEQ expr2 {}
| expr1 TOKEN_SUPEQ expr2 {}
| expr2 {}
  ;

expr2:
  expr2 TOKEN_IPLUS  expr3 {}
| expr2 TOKEN_IMOINS expr3 {}
| expr2 TOKEN_RPLUS  expr3 {}
| expr2 TOKEN_RMOINS expr3 {}
| expr3 {}
  ;

expr3:
  expr3 TOKEN_IMULT expr4 {}
| expr3 TOKEN_IDIV  expr4 {}
| expr3 TOKEN_IMOD  expr4 {}
| expr3 TOKEN_RMULT expr4 {}
| expr3 TOKEN_RDIV  expr4 {}
| expr4 {}
  ;

expr4:
TOKEN_NOT    expr4 {}
| TOKEN_IPLUS  expr4 {}
| TOKEN_IMOINS expr4 {}
| TOKEN_RPLUS  expr4 {}
| TOKEN_RMOINS expr4 { $$.val.expr = }
| expr5 { $$ = $1; }
;

expr5:
expr5 TOKEN_PTR {
  $$.val.expr = new CPexpr($1.val.expr->position.deb_ligne, $2.position.nb_lignes, $1.val.expr->position.deb_car, $2.position.nb_char_ligne + $2.position.longueur, $1.val.expr->position.deb_car_tot, $2.position.nb_char_tot + $2.position.longueur); 
  $$.val.expr->type = CPexpr::PInd;
  $$.val.expr->val.upind.e = $1.val.expr;
}
| expr5 TOKEN_OPENBRACKET expr5 TOKEN_CLOSEBRACKET { 
  $$.val.expr = new CPexpr($1.val.expr->position.deb_ligne, $4.position.nb_lignes, $1.val.expr->position.deb_car, $4.position.nb_char_ligne + $4.position.longueur, $1.val.expr->position.deb_car_tot, $4.position.nb_char_tot + $4.position.longueur); 
  $$.val.expr->type = CPexpr::PTab;
  $$.val.expr->val.uptab.e1 = $1.val.expr;
  $$.val.expr->val.uptab.e2 = $2.val.expr;
}
| expr5 TOKEN_POINT expr6 { /* !!!!!!! */ }
| expr6 { $$ = $1; }
;

expr6:
  appel { /* !!!!!!!!!!! */ }
| expr7 { $$ = $1; }
  ;

expr7:
  valeur { $$ = $1; }
| TOKEN_OPENPAR expr TOKEN_CLOSEPAR { /* !!!!  */ $$ = $1; $$.val.expr->position = *(new pascal_position($1.position.nb_lignes, $3.position.nb_lignes, $1.position.nb_char_ligne, $3.position.nb_char_ligne + $3.position.longueur, $1.position.nb_char_tot, $3.position.nb_char_tot + $3.position.longueur)); }
  ;





valeur:
  booleen { $$ = $1; }
| TOKEN_ENTIER { 
    $$.position = $1.position; 
    $$.val.expr = new CPexpr($1.position.nb_lignes, $1.position.nb_lignes, $1.position.nb_char_ligne, $1.position.nb_char_ligne + $1.position.longueur, $1.position.nb_char_tot, $1.position.nb_char_tot + $1.position.longueur); 
    $$.val.expr->type = CPexpr::PConst; 
    $$.val.expr->val.upconst.pconst.type.type = pevaltype::PETInteger; 
    $$.val.expr->val.upconst.pconst.val.val.i = $1.val.entier; 
  }
| TOKEN_REEL { 
    $$.position = $1.position; 
    $$.val.expr = new CPexpr($1.position.nb_lignes, $1.position.nb_lignes, $1.position.nb_char_ligne, $1.position.nb_char_ligne + $1.position.longueur, $1.position.nb_char_tot, $1.position.nb_char_tot + $1.position.longueur); 
    $$.val.expr->type = CPexpr::PConst; 
    $$.val.expr->val.upconst.pconst.type.type = pevaltype::PETReal; 
    $$.val.expr->val.upconst.pconst.val.val.r = $1.val.reel; 
  }
| TOKEN_CHAINE { 
    $$.position = $1.position; 
    $$.val.expr = new CPexpr($1.position.nb_lignes, $1.position.nb_lignes, $1.position.nb_char_ligne, $1.position.nb_char_ligne + $1.position.longueur, $1.position.nb_char_tot, $1.position.nb_char_tot + $1.position.longueur); 
    $$.val.expr->type = CPexpr::PConst; 
    $$.val.expr->val.upconst.pconst.type.type = pevaltype::PETString; 
    $$.val.expr->val.upconst.pconst.val.val.str = $1.val.chaine; 
  }
| TOKEN_IDENT { 
    $$.position = $1.position; 
    $$.val.expr = new CPexpr($1.position.nb_lignes, $1.position.nb_lignes, $1.position.nb_char_ligne, $1.position.nb_char_ligne + $1.position.longueur, $1.position.nb_char_tot, $1.position.nb_char_tot + $1.position.longueur); 
    $$.val.expr->type = CPexpr::PIdent; 
    $$.val.expr->val.upident.pident = $1.val.ident;
  }
  ;



booleen: 
  TOKEN_TRUE { 
    $$.position = $1.position; 
    $$.val.expr = new CPexpr($1.position.nb_lignes, $1.position.nb_lignes, $1.position.nb_char_ligne, $1.position.nb_char_ligne + $1.position.longueur, $1.position.nb_char_tot, $1.position.nb_char_tot + $1.position.longueur); 
    $$.val.expr->type = CPexpr::PConst; 
    $$.val.expr->val.upconst.pconst.type.type = pevaltype::PETBoolean; 
    $$.val.expr->val.upconst.pconst.val.val.b = $1.val.booleen; 
  }
| TOKEN_FALSE  { 
    $$ = new CPexpr($1.position.nb_lignes, $1.position.nb_lignes, $1.position.nb_char_ligne, $1.position.nb_char_ligne + $1.position.longueur, $1.position.nb_char_tot, $1.position.nb_char_tot + $1.position.longueur); 
    $$->type = CPexpr::PConst; 
    $$->val.upconst.pconst.type.type = pevaltype::PETBoolean; 
    $$->val.upconst.pconst.val.val.b = $1.val.booleen; 
  }

;

%%



const static void yyerror(char s[]) {
  (void) printf("Erreur PARSING.");
}
