%{ 
 /* Header */
 /* SetOrientation  ; NomCarte */
#include "global.hpp"
#include "pascal/pascal.tools.hpp"
#include "pascal/pascal.mem.hpp"
#include "pascal/pascal.env.hpp"
#include "pascal/pascal.expr.hpp"
#include "pascal/pascal.prog.hpp"


static const void yyerror(char s[]);

extern int yypascallex(void);
extern FILE *yypascalout;
//extern int yylex(void);
//#define yylex yypascallex

CPprog *prog;

//#define _YY(str) (str)

//ppos position(pascal_position((unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1));

/*
#define NEW_EXPR new CPexpr($1.position.nb_lignes, $1.position.nb_lignes, $1.position.nb_char_ligne, $1.position.nb_char_ligne + $1.position.longueur, $1.position.nb_char_tot, $1.position.nb_char_tot + $1.position.longueur)

#define CODE_CONSTANTE_BOOLEENNE { $$.position = $1.position; $$.val.expr = NEW_EXPR; $$.val.expr->type = CPexpr::PConst; $$.val.expr->val.upconst.pconst.type.type = pevaltype::PETBoolean; $$.val.expr->val.upconst.pconst.val.val.b = $1.val.booleen; }
*/
%}

/* Le type de yylval. */

%union {
  struct ttoken {
    struct {
      unsigned int nb_lignes;
      unsigned int nb_char_ligne;
      unsigned int nb_char_tot;
      unsigned int longueur;
    } position;
    union {
      int entier;
      double reel;
      char *chaine;
      char *ident;
    } val;
  } token;

  class CPexpr *expr;

  class pliste<CPexpr> *lexpr;

  class CPprog *prog;

  class pliste<struct ttoken> *ltoken;

  struct pascal_dval_type *dvaltype;

  class pliste<struct pascal_dval_type::tpdtrecord::champ> *lchamp;

  class pliste<struct pascal_dval_type::tpdtprocedure::param> *params;

  struct pascal_dval_type::tpdtprocedure::param *param;

  struct CPexpr::utype::SPMenu::item *item;
  class pliste<struct CPexpr::utype::SPMenu::item> *pitems;
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
%token <token> TOKEN_ENTIER
%token <token> TOKEN_REEL
%token <token> TOKEN_CHAINE
%token <token> TOKEN_IDENT
%token <token> TOKEN_NIL


%token TOKEN_EOF
%token <token> TOKEN_TRUE TOKEN_FALSE
%token <token> TOKEN_NOT TOKEN_AND TOKEN_OR
%token <token> TOKEN_EQUAL TOKEN_DIFF TOKEN_INF TOKEN_SUP TOKEN_INFEQ TOKEN_SUPEQ
%token <token> TOKEN_IPLUS TOKEN_IMOINS TOKEN_IMULT TOKEN_IDIV TOKEN_IMOD
%token <token> TOKEN_RPLUS TOKEN_RMOINS TOKEN_RMULT TOKEN_RDIV
%token <token> TOKEN_PTR TOKEN_REF
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
%token <token> TOKEN_NEW

%token <token> TOKEN_PROCEDURE TOKEN_FUNCTION

%token <token> TOKEN_CONST TOKEN_VAR
%token <token> TOKEN_OPENPAR TOKEN_CLOSEPAR
%token <token> TOKEN_OPENBRACKET TOKEN_CLOSEBRACKET
%token <token> TOKEN_DEUXPOINTS TOKEN_BLANC TOKEN_COMMENT TOKEN_VIRGULE TOKEN_POINT

%token <token> TOKEN_MUSIQUE
%token <token> TOKEN_MENU TOKEN_ITEM


%token <token> TOKEN_FLECHE TOKEN_HEROS TOKEN_CAMERA
%token <token> TOKEN_WAIT TOKEN_HALT TOKEN_RESTART TOKEN_FONDU TOKEN_FRAPPER
%token <token> TOKEN_RECOBJET TOKEN_RECARME TOKEN_SUPOBJET TOKEN_CARTE
%token <token> TOKEN_SETPOSITION TOKEN_SETPOSITIONZ TOKEN_DEPLACER TOKEN_DEPLACERZ
%token <token> TOKEN_ROTATE TOKEN_SOLIDARISER TOKEN_DESOLIDARISER TOKEN_DEFAUT TOKEN_ZOOM
%token <token> TOKEN_AJOUTERANIME TOKEN_AJOUTERNONANIME
%token <token> TOKEN_SETTEMPS TOKEN_SETORIENTATION TOKEN_NOMCARTE TOKEN_WAITFOR TOKEN_BLOQUERTEMPS TOKEN_DEBLOQUERTEMPS
%token <token> TOKEN_CARTEZ


// Les productions ou non terminals.

// Les expressions.
%type <expr> booleen
%type <expr> valeur
%type <expr> appel_expr
%type <expr> expr7 expr6 expr5 expr4 expr3 expr2 expr1 expr
%type <expr> nom_carte

%type <expr> argument
%type <lexpr> liste_argument liste_argument1


// Les instructions.
%type <prog> skip begin affectation if ifelse while for repeat write writeln read readln pnew appel_prog
%type <prog> liste_instruction liste_instruction1 instruction

%type <prog> liste_declaration declaration
%type <prog> decl_variable liste_decl_variable1 decl_variable1 decl_variable2

%type <ltoken> liste_ident
%type <dvaltype> type pointer array record
%type <lchamp> liste_decl_champ

%type <prog> decl_constante liste_decl_constante1 decl_constante1
%type <prog> decl_type liste_decl_type1 decl_type1

%type <params> liste_parametre liste_parametre1
%type <param> parametre parametre_copier parametre_ref

%type <prog> corps decl_procedure decl_fonction



%type <prog> musique
%type <prog> wait fondu camera carte setpos setposz frapper deplacer supobjet recarme ajouteranime ajouternonanime
%type <prog> settemps setorientation waitfor debloquertemps bloquertemps cartez
%type <prog> camera_defaut camera_solidariser camera_desolidariser camera_setpos camera_rotate camera_zoom



%type <pitems> menu_items menu_items1
%type <item> menu_item additem1 additem2

%start main

%%

main: liste_declaration TOKEN_EOF { prog = $1; fprintf(yypascalout, "Analyse réussie."); pmessage("Analyse réussie !"); return 0; };

liste_declaration: 
liste_declaration declaration {
  $$ = new class CPprog($1->position.deb_ligne, $2->position.fin_ligne, $1->position.deb_car, $2->position.fin_car, $1->position.deb_car_tot, $2->position.fin_car_tot);
  $$->type = CPprog::PSeq;
  $$->val.upseq.p1 = $1;
  $$->val.upseq.p2 = $2;
}
| {
  $$ = new class CPprog((unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1);
  $$->type = CPprog::PSkip;
}
;

declaration:
decl_constante { $$ = $1; }
| decl_type { $$ = $1; }
| decl_variable { $$ = $1; }
| decl_procedure { $$ = $1; }
| decl_fonction { $$ = $1; }
| begin { $$ = $1; }
;

decl_constante: 
TOKEN_CONST liste_decl_constante1 { $$ = $2; }
;

liste_decl_constante1:
decl_constante1 liste_decl_constante1 {
  $$ = new class CPprog($1->position.deb_ligne, $2->position.fin_ligne, $1->position.deb_car, $2->position.fin_car, $1->position.deb_car_tot, $2->position.fin_car_tot);
  $$->type = CPprog::PSeq;
  $$->val.upseq.p1 = $1;
  $$->val.upseq.p2 = $2;
}
| decl_constante1 { $$ = $1; }
;

decl_constante1:
TOKEN_IDENT TOKEN_EQUAL expr TOKEN_PTVIRG {
  $$ = new class CPprog($1.position.nb_lignes, $4.position.nb_lignes, $1.position.nb_char_ligne, $4.position.nb_char_ligne + $4.position.longueur, $1.position.nb_char_tot, $4.position.nb_char_tot + $4.position.longueur);
  $$->type = CPprog::PConst;
  $$->val.upconst.nom = $1.val.ident;
  $$->val.upconst.val = $3;
}
;

decl_type:
TOKEN_TYPE liste_decl_type1 { $$ = $2; }
;

liste_decl_type1:
decl_type1 liste_decl_type1 {
  $$ = new class CPprog($1->position.deb_ligne, $2->position.fin_ligne, $1->position.deb_car, $2->position.fin_car, $1->position.deb_car_tot, $2->position.fin_car_tot);
  $$->type = CPprog::PSeq;
  $$->val.upseq.p1 = $1;
  $$->val.upseq.p2 = $2;
}  
| decl_type1 { $$ = $1; }
;

decl_type1:
TOKEN_IDENT TOKEN_EQUAL type TOKEN_PTVIRG {
  $$ = new class CPprog($1.position.nb_lignes, $4.position.nb_lignes, $1.position.nb_char_ligne, $4.position.nb_char_ligne + $4.position.longueur, $1.position.nb_char_tot, $4.position.nb_char_tot + $4.position.longueur);
  $$->type = CPprog::PType;
  $$->val.uptype.ident = $1.val.ident;
  $$->val.uptype.dvaltype = *($3);
}
;


decl_variable:
TOKEN_VAR liste_decl_variable1 { $$ = $2; }
;

liste_decl_variable1:
liste_decl_variable1 decl_variable1 {
  $$ = new class CPprog($1->position.deb_ligne, $2->position.fin_ligne, $1->position.deb_car, $2->position.fin_car, $1->position.deb_car_tot, $2->position.fin_car_tot);
  $$->type = CPprog::PSeq;
  $$->val.upseq.p1 = $1;
  $$->val.upseq.p2 = $2;
}
| decl_variable1 { $$ = $1; }
;

decl_variable1:
liste_ident TOKEN_DEUXPOINTS type TOKEN_PTVIRG {
  class pliste<struct YYSTYPE::ttoken> *temp = $1;
  if (temp == NULL) {
    pmesserr("Dans le parser, à la regle decl_variable1, liste_ident est NULL !!");
    return -1;
  }
  struct YYSTYPE::ttoken *p = temp->a;
  class CPprog *pr, *ps;
  $$ = new class CPprog(p->position.nb_lignes, $4.position.nb_lignes, p->position.nb_char_ligne, $4.position.nb_char_ligne + $4.position.longueur, p->position.nb_char_tot, $4.position.nb_char_tot + $4.position.longueur);
  $$->type = CPprog::PVar;
  $$->val.upvar.nom = p->val.ident;
  $$->val.upvar.t = *($3);
  
  while (temp->suivant != NULL) {
    temp = temp->suivant;
    p = temp->a;
    pr = new class CPprog(p->position.nb_lignes, $4.position.nb_lignes, p->position.nb_char_ligne, $4.position.nb_char_ligne + $4.position.longueur, p->position.nb_char_tot, $4.position.nb_char_tot + $4.position.longueur);
    pr->type = CPprog::PVar;
    pr->val.upvar.nom = p->val.ident;
    pr->val.upvar.t = *($3);
    ps = $$;
    $$ = new class CPprog(p->position.nb_lignes, $4.position.nb_lignes, p->position.nb_char_ligne, $4.position.nb_char_ligne + $4.position.longueur, p->position.nb_char_tot, $4.position.nb_char_tot + $4.position.longueur);
    $$->type = CPprog::PSeq;
    $$->val.upseq.p1 = pr;
    $$->val.upseq.p2 = ps;
  }
}
  ;

liste_ident:
liste_ident TOKEN_VIRGULE TOKEN_IDENT { 
  struct YYSTYPE::ttoken *temp = new struct YYSTYPE::ttoken;
  *temp = $3;
  $$ = mp(temp, $1); 
}
| TOKEN_IDENT { 
  struct YYSTYPE::ttoken *temp = new struct YYSTYPE::ttoken;
  *temp = $1;
  $$ = mp(temp, (class pliste<struct YYSTYPE::ttoken> *)NULL); 
}
  ;

type:
TOKEN_BOOLEAN { $$ = new pdvaltype; $$->type = pdvaltype::PDTBoolean; }
| TOKEN_INTEGER { $$ = new pdvaltype; $$->type = pdvaltype::PDTInteger; }
| expr TOKEN_SUBRANGE expr { // subrange
  $$ = new pdvaltype; 
  $$->type = pdvaltype::PDTSubrange;
  $$->val.s.mine = $1;
  $$->val.s.maxe = $3;
}
| TOKEN_REAL { $$ = new pdvaltype; $$->type = pdvaltype::PDTReal; }
| TOKEN_STRING { $$ = new pdvaltype; $$->type = pdvaltype::PDTString; }
| pointer {
  $$ = new pdvaltype; 
  $$->type = pdvaltype::PDTPointer;
  $$->val.ptr = $1;
}
| array { $$ = $1; }
| record { $$ = $1; }
| TOKEN_IDENT {
  $$ = new pdvaltype; 
  $$->type = pdvaltype::PDTUser;
  $$->val.user = $1.val.ident;
}
;


pointer:
TOKEN_PTR type { $$ = $2; }
;

array:
TOKEN_ARRAY TOKEN_OPENBRACKET expr TOKEN_SUBRANGE expr TOKEN_CLOSEBRACKET TOKEN_OF type {
  $$ = new pdvaltype; 
  $$->type = pdvaltype::PDTArray;
  $$->val.array.indice.mine = $3;
  $$->val.array.indice.maxe = $5;
  $$->val.array.type = $8;
}
;

record:
TOKEN_RECORD liste_decl_champ TOKEN_END {
  $$ = new pdvaltype;
  $$->type = pdvaltype::PDTRecord;
  $$->val.record.champs = $2;
}
;

liste_decl_champ:
liste_decl_champ TOKEN_IDENT TOKEN_DEUXPOINTS type TOKEN_PTVIRG {
  struct pascal_dval_type::tpdtrecord::champ *temp;
  temp = new struct pascal_dval_type::tpdtrecord::champ;
  temp->nom = $2.val.ident;
  temp->type = $4;
  $$ = mp(temp, $1);
}
| { $$ = (class pliste<struct pascal_dval_type::tpdtrecord::champ> *) NULL; }
;

decl_procedure: 
TOKEN_PROCEDURE TOKEN_IDENT TOKEN_OPENPAR liste_parametre TOKEN_CLOSEPAR TOKEN_PTVIRG 
decl_variable2
corps
TOKEN_PTVIRG {
  $$ = new class CPprog($1.position.nb_lignes, $9.position.nb_lignes, $1.position.nb_char_ligne, $9.position.nb_char_ligne + $9.position.longueur, $1.position.nb_char_tot, $9.position.nb_char_tot + $9.position.longueur);
  $$->type = CPprog::PVar;
  $$->val.upvar.nom = $2.val.ident;
  $$->val.upvar.t.type = pdvaltype::PDTProcedure;
  $$->val.upvar.t.val.proc.env = NULL;
  $$->val.upvar.t.val.proc.params = $4;
  $$->val.upvar.t.val.proc.corps = new class CPprog($7->position.deb_ligne, $8->position.fin_ligne, $7->position.deb_car, $8->position.fin_car, $7->position.deb_car_tot, $8->position.fin_car_tot);
  $$->val.upvar.t.val.proc.corps->type = CPprog::PSeq;
  $$->val.upvar.t.val.proc.corps->val.upseq.p1 = $7;
  $$->val.upvar.t.val.proc.corps->val.upseq.p2 = $8;
}
;

decl_fonction: 
TOKEN_FUNCTION TOKEN_IDENT TOKEN_OPENPAR liste_parametre TOKEN_CLOSEPAR TOKEN_DEUXPOINTS type TOKEN_PTVIRG 
decl_variable2
corps
TOKEN_PTVIRG {
  $$ = new class CPprog($1.position.nb_lignes, $11.position.nb_lignes, $1.position.nb_char_ligne, $11.position.nb_char_ligne + $11.position.longueur, $1.position.nb_char_tot, $11.position.nb_char_tot + $11.position.longueur);
  $$->type = CPprog::PVar;
  $$->val.upvar.nom = $2.val.ident;
  $$->val.upvar.t.type = pdvaltype::PDTFunction;
  $$->val.upvar.t.val.func.env = NULL;
  $$->val.upvar.t.val.func.params = $4;
  $$->val.upvar.t.val.func.type = $7;
  $$->val.upvar.t.val.func.corps = new class CPprog($9->position.deb_ligne, $10->position.fin_ligne, $9->position.deb_car, $10->position.fin_car, $9->position.deb_car_tot, $10->position.fin_car_tot);
  $$->val.upvar.t.val.func.corps->type = CPprog::PSeq;
  $$->val.upvar.t.val.func.corps->val.upseq.p1 = $9;
  $$->val.upvar.t.val.func.corps->val.upseq.p2 = $10;
}
;

decl_variable2:
  decl_variable { $$ = $1; }
| {
    $$ = new class CPprog((unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1);
    $$->type = CPprog::PSkip;
  }
;

liste_parametre:
  parametre liste_parametre1 { $$ = mp($1,$2); }
| { $$ = (class pliste<struct pascal_dval_type::tpdtprocedure::param> *) NULL; }
;

liste_parametre1:
  TOKEN_PTVIRG parametre liste_parametre1 { $$ = mp($2,$3); }
| { $$ = (class pliste<struct pascal_dval_type::tpdtprocedure::param> *) NULL; }
;

parametre: 
  parametre_copier { $$ = $1; }
| parametre_ref { $$ = $1; }
  ;

parametre_copier:
TOKEN_IDENT TOKEN_DEUXPOINTS type {
  $$ = new struct pascal_dval_type::tpdtprocedure::param;
  $$->var = false;
  $$->nom = $1.val.ident;
  $$->dvaltype_ptr = $3;
}
;

parametre_ref:
TOKEN_VAR TOKEN_IDENT TOKEN_DEUXPOINTS type
{
  $$ = new struct pascal_dval_type::tpdtprocedure::param;
  $$->var = true;
  $$->nom = $2.val.ident;
  $$->dvaltype_ptr = $4;
}
;


corps: begin { $$ = $1; };

liste_instruction: 
  liste_instruction1 instruction {
    $$ = new class CPprog($1->position.deb_ligne, $2->position.fin_ligne, $1->position.deb_car, $2->position.fin_car, $1->position.deb_car_tot, $2->position.fin_car_tot);
    $$->type = CPprog::PSeq;
    $$->val.upseq.p1 = $1;
    $$->val.upseq.p2 = $2;
  }
| instruction { $$ = $1; }
;

liste_instruction1:
liste_instruction1 instruction TOKEN_PTVIRG {
  $$ = new class CPprog($1->position.deb_ligne, $2->position.fin_ligne, $1->position.deb_car, $2->position.fin_car, $1->position.deb_car_tot, $2->position.fin_car_tot);
  $$->type = CPprog::PSeq;
  $$->val.upseq.p1 = $1;
  $$->val.upseq.p2 = $2;
}
| instruction TOKEN_PTVIRG { $$ = $1; }
  ;

instruction:
  skip  { $$ = $1; }
| begin { $$ = $1; }
| affectation { $$ = $1; }
| if     { $$ = $1; }
| ifelse { $$ = $1; }
| while  { $$ = $1; }
| for    { $$ = $1; }
| repeat { $$ = $1; }
| write  { $$ = $1; }
| writeln { $$ = $1; }
| read    { $$ = $1; }
| readln  { $$ = $1; }
| pnew    { $$ = $1; }
| appel_prog { $$ = $1; }
| musique { $$ = $1; }
| wait { $$ = $1; }
| fondu { $$ = $1; }
| camera { $$ = $1; }
| carte { $$ = $1; }
| setpos { $$ = $1; }
| setposz { $$ = $1; }
| frapper { $$ = $1; }
| deplacer { $$ = $1; }
| supobjet { $$ = $1; }
| recarme { $$ = $1; }
| ajouteranime { $$ = $1; }
| ajouternonanime { $$ = $1; }
| settemps { $$ = $1; }
| setorientation { $$ = $1; }
| waitfor { $$ = $1; }
| debloquertemps { $$ = $1; }
| bloquertemps { $$ = $1; }
| cartez { $$ = $1; }
;

skip:
{
  /* ... */
  $$ = new class CPprog((unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1);
  $$->type = CPprog::PSkip;
};

begin:
TOKEN_BEGIN liste_instruction TOKEN_END {
  $$ = new class CPprog($1.position.nb_lignes, $3.position.nb_lignes, $1.position.nb_char_ligne, $3.position.nb_char_ligne + $3.position.longueur, $1.position.nb_char_tot, $3.position.nb_char_tot + $3.position.longueur);
  $$->type = CPprog::PBegin;
  $$->val.upbegin.p = $2;
}
  ;

affectation:
expr TOKEN_AFFECTATION expr {
  $$ = new class CPprog($1->position.deb_ligne, $3->position.fin_ligne, $1->position.deb_car, $3->position.fin_car, $1->position.deb_car_tot, $3->position.fin_car_tot);
  $$->type = CPprog::PAffectation;
  $$->val.upaffectation.lval = $1;
  $$->val.upaffectation.e = $3;
}
;

if:
TOKEN_IF expr TOKEN_THEN liste_instruction TOKEN_END {
  $$ = new class CPprog($1.position.nb_lignes, $5.position.nb_lignes, $1.position.nb_char_ligne, $5.position.nb_char_ligne + $5.position.longueur, $1.position.nb_char_tot, $5.position.nb_char_tot + $5.position.longueur);
  $$->type = CPprog::PIf;
  $$->val.upif.b = $2;
  $$->val.upif.p = $4;
  $$->val.upif.q = new class CPprog((unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1);
  $$->val.upif.q->type = CPprog::PSkip;
}
;

ifelse:
TOKEN_IF expr TOKEN_THEN liste_instruction TOKEN_ELSE liste_instruction TOKEN_END {
  $$ = new class CPprog($1.position.nb_lignes, $7.position.nb_lignes, $1.position.nb_char_ligne, $7.position.nb_char_ligne + $7.position.longueur, $1.position.nb_char_tot, $7.position.nb_char_tot + $7.position.longueur);
  $$->type = CPprog::PIf;
  $$->val.upif.b = $2;
  $$->val.upif.p = $4;
  $$->val.upif.q = $6;
}
;

while:
TOKEN_WHILE expr TOKEN_DO instruction {
  $$ = new class CPprog($1.position.nb_lignes, $4->position.fin_ligne, $1.position.nb_char_ligne, $4->position.fin_car, $1.position.nb_char_tot, $4->position.fin_car_tot);
  $$->type = CPprog::PWhile;
  $$->val.upwhile.b = $2;
  $$->val.upwhile.p = $4;
}
;

for:
TOKEN_FOR TOKEN_IDENT TOKEN_AFFECTATION expr TOKEN_TO expr TOKEN_DO instruction {
  $$ = new class CPprog($1.position.nb_lignes, $8->position.fin_ligne, $1.position.nb_char_ligne, $8->position.fin_car, $1.position.nb_char_tot, $8->position.fin_car_tot);
  $$->type = CPprog::PFor;
  $$->val.upfor.i = $2.val.ident;
  $$->val.upfor.e1 = $4;
  $$->val.upfor.e2 = $6;
  $$->val.upfor.p = $8;
}
;

repeat:
TOKEN_REPEAT liste_instruction TOKEN_UNTIL expr {
  $$ = new class CPprog($1.position.nb_lignes, $4->position.fin_ligne, $1.position.nb_char_ligne, $4->position.fin_car, $1.position.nb_char_tot, $4->position.fin_car_tot);
  $$->type = CPprog::PRepeat;
  $$->val.uprepeat.b = $4;
  $$->val.uprepeat.p = $2;
}
;

write:
TOKEN_WRITE TOKEN_OPENPAR liste_argument TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $4.position.nb_lignes, $1.position.nb_char_ligne, $4.position.nb_char_ligne + $4.position.longueur, $1.position.nb_char_tot, $4.position.nb_char_tot + $4.position.longueur);
  $$->type = CPprog::PWrite;
  $$->val.upwrite.le = $3;
}
;
writeln:
TOKEN_WRITELN TOKEN_OPENPAR liste_argument TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $4.position.nb_lignes, $1.position.nb_char_ligne, $4.position.nb_char_ligne + $4.position.longueur, $1.position.nb_char_tot, $4.position.nb_char_tot + $4.position.longueur);
  $$->type = CPprog::PWriteln;
  $$->val.upwriteln.le = $3;
}
;
read:
TOKEN_READ TOKEN_OPENPAR liste_argument TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $4.position.nb_lignes, $1.position.nb_char_ligne, $4.position.nb_char_ligne + $4.position.longueur, $1.position.nb_char_tot, $4.position.nb_char_tot + $4.position.longueur);
  $$->type = CPprog::PRead;
  $$->val.upread.llval = $3;
}
;
readln:
TOKEN_READLN TOKEN_OPENPAR liste_argument TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $4.position.nb_lignes, $1.position.nb_char_ligne, $4.position.nb_char_ligne + $4.position.longueur, $1.position.nb_char_tot, $4.position.nb_char_tot + $4.position.longueur);
  $$->type = CPprog::PReadln;
  $$->val.upreadln.llval = $3;
}
;

pnew:
TOKEN_NEW TOKEN_OPENPAR TOKEN_IDENT TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $4.position.nb_lignes, $1.position.nb_char_ligne, $4.position.nb_char_ligne + $4.position.longueur, $1.position.nb_char_tot, $4.position.nb_char_tot + $4.position.longueur);
  $$->type = CPprog::PNew;
  $$->val.upnew.ident = $3.val.ident;
}
;

musique:
TOKEN_MUSIQUE TOKEN_OPENPAR expr TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $4.position.nb_lignes, $1.position.nb_char_ligne, $4.position.nb_char_ligne + $4.position.longueur, $1.position.nb_char_tot, $4.position.nb_char_tot + $4.position.longueur);
  $$->type = CPprog::PMusique;
  $$->val.upmusique.musique = $3;
}
;

wait:
TOKEN_WAIT TOKEN_OPENPAR expr TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $4.position.nb_lignes, $1.position.nb_char_ligne, $4.position.nb_char_ligne + $4.position.longueur, $1.position.nb_char_tot, $4.position.nb_char_tot + $4.position.longueur);
  $$->type = CPprog::PWait;
  $$->val.upwait.nbpasses = $3;
}
;

fondu:
TOKEN_FONDU TOKEN_OPENPAR expr TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $4.position.nb_lignes, $1.position.nb_char_ligne, $4.position.nb_char_ligne + $4.position.longueur, $1.position.nb_char_tot, $4.position.nb_char_tot + $4.position.longueur);
  $$->type = CPprog::PFondu;
  $$->val.upfondu.couleur = $3;
}
;


carte:
TOKEN_CARTE TOKEN_OPENPAR expr TOKEN_VIRGULE expr TOKEN_VIRGULE expr TOKEN_VIRGULE expr TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  $$->type = CPprog::PCarte;
  $$->val.upcarte.nom = $3;
  $$->val.upcarte.x = $5;
  $$->val.upcarte.y = $7;
  $$->val.upcarte.direction = $9;
};

cartez:
TOKEN_CARTEZ TOKEN_OPENPAR expr TOKEN_VIRGULE expr TOKEN_VIRGULE expr TOKEN_VIRGULE expr TOKEN_VIRGULE expr TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $12.position.nb_lignes, $1.position.nb_char_ligne, $12.position.nb_char_ligne + $12.position.longueur, $1.position.nb_char_tot, $12.position.nb_char_tot + $12.position.longueur);
  $$->type = CPprog::PCarteZ;
  $$->val.upcartez.nom = $3;
  $$->val.upcartez.x = $5;
  $$->val.upcartez.y = $7;
  $$->val.upcartez.z = $9;
  $$->val.upcartez.direction = $11;
};


setpos:
expr TOKEN_FLECHE TOKEN_SETPOSITION TOKEN_OPENPAR expr TOKEN_VIRGULE expr TOKEN_VIRGULE expr TOKEN_CLOSEPAR {
  $$ = new class CPprog($1->position.deb_ligne, $10.position.nb_lignes, $1->position.deb_car, $10.position.nb_char_ligne + $10.position.longueur, $1->position.deb_car_tot, $10.position.nb_char_tot + $10.position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  $$->type = CPprog::PSetPosition;
  $$->val.upsetpos.nom = $1;
  $$->val.upsetpos.x = $5;
  $$->val.upsetpos.y = $7;
  $$->val.upsetpos.relatif = $9;
}
;


setposz:
expr TOKEN_FLECHE TOKEN_SETPOSITIONZ TOKEN_OPENPAR expr TOKEN_VIRGULE expr TOKEN_VIRGULE expr TOKEN_VIRGULE expr TOKEN_CLOSEPAR {
  $$ = new class CPprog($1->position.deb_ligne, $12.position.nb_lignes, $1->position.deb_car, $12.position.nb_char_ligne + $12.position.longueur, $1->position.deb_car_tot, $12.position.nb_char_tot + $12.position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  $$->type = CPprog::PSetPositionZ;
  $$->val.upsetposz.nom = $1;
  $$->val.upsetposz.x = $5;
  $$->val.upsetposz.y = $7;
  $$->val.upsetposz.z = $9;
  $$->val.upsetposz.relatif = $11;
}
;


frapper:
expr TOKEN_FLECHE TOKEN_FRAPPER TOKEN_OPENPAR TOKEN_CLOSEPAR {
  $$ = new class CPprog($1->position.deb_ligne, $5.position.nb_lignes, $1->position.deb_car, $5.position.nb_char_ligne + $5.position.longueur, $1->position.deb_car_tot, $5.position.nb_char_tot + $5.position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  $$->type = CPprog::PFrapper;
  $$->val.upfrapper.nom = $1;
}
;


deplacer:
expr TOKEN_FLECHE TOKEN_DEPLACER TOKEN_OPENPAR expr TOKEN_VIRGULE expr TOKEN_VIRGULE expr TOKEN_CLOSEPAR {
  $$ = new class CPprog($1->position.deb_ligne, $10.position.nb_lignes, $1->position.deb_car, $10.position.nb_char_ligne + $10.position.longueur, $1->position.deb_car_tot, $10.position.nb_char_tot + $10.position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  $$->type = CPprog::PDeplacer;
  $$->val.updeplacer.nom = $1;
  $$->val.updeplacer.x = $5;
  $$->val.updeplacer.y = $7;
  $$->val.updeplacer.relatif = $9;
}
;

supobjet:
expr TOKEN_FLECHE TOKEN_SUPOBJET TOKEN_OPENPAR TOKEN_CLOSEPAR {
  $$ = new class CPprog($1->position.deb_ligne, $5.position.nb_lignes, $1->position.deb_car, $5.position.nb_char_ligne + $5.position.longueur, $1->position.deb_car_tot, $5.position.nb_char_tot + $5.position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  $$->type = CPprog::PSupObjet;
  $$->val.upsupobjet.nom = $1;
}
;


recarme:
expr TOKEN_FLECHE TOKEN_RECARME TOKEN_OPENPAR TOKEN_CLOSEPAR {
  $$ = new class CPprog($1->position.deb_ligne, $5.position.nb_lignes, $1->position.deb_car, $5.position.nb_char_ligne + $5.position.longueur, $1->position.deb_car_tot, $5.position.nb_char_tot + $5.position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  $$->type = CPprog::PRecArme;
  $$->val.uprecarme.nom = $1;
};

setorientation:
expr TOKEN_FLECHE TOKEN_SETORIENTATION TOKEN_OPENPAR expr TOKEN_CLOSEPAR {
  $$ = new class CPprog($1->position.deb_ligne, $6.position.nb_lignes, $1->position.deb_car, $6.position.nb_char_ligne + $6.position.longueur, $1->position.deb_car_tot, $6.position.nb_char_tot + $6.position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  $$->type = CPprog::PSetOrientation;
  $$->val.upsetorientation.nom = $1;
  $$->val.upsetorientation.orientation = $5;  
};


ajouteranime:
TOKEN_AJOUTERANIME TOKEN_OPENPAR expr TOKEN_VIRGULE expr TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $6.position.nb_lignes, $1.position.nb_char_ligne, $6.position.nb_char_ligne + $6.position.longueur, $1.position.nb_char_tot, $6.position.nb_char_tot + $6.position.longueur);
  $$->type = CPprog::PAjouterAnime;
  $$->val.upajouteranime.nom = $3;
  $$->val.upajouteranime.fichier = $5;
};


ajouternonanime:
TOKEN_AJOUTERNONANIME TOKEN_OPENPAR expr TOKEN_VIRGULE expr TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $6.position.nb_lignes, $1.position.nb_char_ligne, $6.position.nb_char_ligne + $6.position.longueur, $1.position.nb_char_tot, $6.position.nb_char_tot + $6.position.longueur);
  $$->type = CPprog::PAjouterNonAnime;
  $$->val.upajouternonanime.nom = $3;
  $$->val.upajouternonanime.fichier = $5;
};


settemps:
TOKEN_SETTEMPS TOKEN_OPENPAR expr TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $4.position.nb_lignes, $1.position.nb_char_ligne, $4.position.nb_char_ligne + $4.position.longueur, $1.position.nb_char_tot, $4.position.nb_char_tot + $4.position.longueur);
  $$->type = CPprog::PSetTemps;
  $$->val.upsettemps.temps = $3;
};
  

waitfor:
TOKEN_WAITFOR TOKEN_OPENPAR expr TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $4.position.nb_lignes, $1.position.nb_char_ligne, $4.position.nb_char_ligne + $4.position.longueur, $1.position.nb_char_tot, $4.position.nb_char_tot + $4.position.longueur);
  $$->type = CPprog::PWaitFor;
  $$->val.upwaitfor.nom = $3;
};
  

bloquertemps:
TOKEN_BLOQUERTEMPS TOKEN_OPENPAR TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $3.position.nb_lignes, $1.position.nb_char_ligne, $3.position.nb_char_ligne + $3.position.longueur, $1.position.nb_char_tot, $3.position.nb_char_tot + $3.position.longueur);
  $$->type = CPprog::PBloquerTemps;
};
  
debloquertemps:
TOKEN_DEBLOQUERTEMPS TOKEN_OPENPAR TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $3.position.nb_lignes, $1.position.nb_char_ligne, $3.position.nb_char_ligne + $3.position.longueur, $1.position.nb_char_tot, $3.position.nb_char_tot + $3.position.longueur);
  $$->type = CPprog::PDebloquerTemps;
};
  


camera:
camera_defaut { $$ = $1; }
| camera_solidariser { $$ = $1; }
| camera_desolidariser { $$ = $1; }
| camera_setpos { $$ = $1; }
| camera_rotate { $$ = $1; }
| camera_zoom { $$ = $1; }
;

camera_defaut:
TOKEN_CAMERA TOKEN_FLECHE TOKEN_DEFAUT TOKEN_OPENPAR TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $5.position.nb_lignes, $1.position.nb_char_ligne, $5.position.nb_char_ligne + $5.position.longueur, $1.position.nb_char_tot, $5.position.nb_char_tot + $5.position.longueur);
  $$->type = CPprog::PCameraDefaut;
}
;

camera_solidariser:
TOKEN_CAMERA TOKEN_FLECHE TOKEN_SOLIDARISER TOKEN_OPENPAR TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $5.position.nb_lignes, $1.position.nb_char_ligne, $5.position.nb_char_ligne + $5.position.longueur, $1.position.nb_char_tot, $5.position.nb_char_tot + $5.position.longueur);
  $$->type = CPprog::PCameraSolidariser;
}
;

camera_desolidariser:
TOKEN_CAMERA TOKEN_FLECHE TOKEN_DESOLIDARISER TOKEN_OPENPAR TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $5.position.nb_lignes, $1.position.nb_char_ligne, $5.position.nb_char_ligne + $5.position.longueur, $1.position.nb_char_tot, $5.position.nb_char_tot + $5.position.longueur);
  $$->type = CPprog::PCameraDesolidariser;
}
;



camera_setpos:
TOKEN_CAMERA TOKEN_FLECHE TOKEN_SETPOSITION TOKEN_OPENPAR expr TOKEN_VIRGULE expr TOKEN_VIRGULE expr TOKEN_VIRGULE expr TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $12.position.nb_lignes, $1.position.nb_char_ligne, $12.position.nb_char_ligne + $12.position.longueur, $1.position.nb_char_tot, $12.position.nb_char_tot + $12.position.longueur);
  $$->type = CPprog::PSetCameraPosition;
  $$->val.upsetcamerapos.x = $5;
  $$->val.upsetcamerapos.y = $7;
  $$->val.upsetcamerapos.z = $9;
  $$->val.upsetcamerapos.relatif = $11;
};


camera_rotate:
TOKEN_CAMERA TOKEN_FLECHE TOKEN_ROTATE TOKEN_OPENPAR expr TOKEN_VIRGULE expr TOKEN_VIRGULE expr TOKEN_VIRGULE expr TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $12.position.nb_lignes, $1.position.nb_char_ligne, $12.position.nb_char_ligne + $12.position.longueur, $1.position.nb_char_tot, $12.position.nb_char_tot + $12.position.longueur);
  $$->type = CPprog::PCameraRotate;
  $$->val.upcamerarotate.angle_x = $5;
  $$->val.upcamerarotate.angle_y = $7;
  $$->val.upcamerarotate.angle_z = $9;
  $$->val.upcamerarotate.relatif = $11;
};


camera_zoom:
TOKEN_CAMERA TOKEN_FLECHE TOKEN_ZOOM TOKEN_OPENPAR expr TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $6.position.nb_lignes, $1.position.nb_char_ligne, $6.position.nb_char_ligne + $6.position.longueur, $1.position.nb_char_tot, $6.position.nb_char_tot + $6.position.longueur);
  $$->type = CPprog::PCameraZoom;
  $$->val.upcamerazoom.coeff = $5;
};








appel_prog:
TOKEN_IDENT TOKEN_OPENPAR liste_argument TOKEN_CLOSEPAR {
  $$ = new class CPprog($1.position.nb_lignes, $4.position.nb_lignes, $1.position.nb_char_ligne, $4.position.nb_char_ligne + $4.position.longueur, $1.position.nb_char_tot, $4.position.nb_char_tot + $4.position.longueur);
  $$->type = CPprog::PCall;
  $$->val.upcall.ident = $1.val.ident;
  $$->val.upcall.args = $3;
}
;

appel_expr:
TOKEN_IDENT TOKEN_OPENPAR liste_argument TOKEN_CLOSEPAR { /* !!!!!!!!!!!!!!!!!! */
  $$ = new CPexpr($1.position.nb_lignes, $4.position.nb_lignes, $1.position.nb_char_ligne, $4.position.nb_char_ligne + $4.position.longueur, $1.position.nb_char_tot, $4.position.nb_char_tot + $4.position.longueur);
  $$->type = CPexpr::PCall; 
  $$->val.upcall.ident = $1.val.ident;
  $$->val.upcall.args = $3;
}


nom_carte:
TOKEN_NOMCARTE TOKEN_OPENPAR TOKEN_CLOSEPAR {
  $$ = new CPexpr($1.position.nb_lignes, $3.position.nb_lignes, $1.position.nb_char_ligne, $3.position.nb_char_ligne + $3.position.longueur, $1.position.nb_char_tot, $3.position.nb_char_tot + $3.position.longueur);
  $$->type = CPexpr::PNomCarte; 
}

liste_argument:
argument liste_argument1 { $$ = mp($1, $2); }
| { $$ = (class pliste<CPexpr> *)NULL; }
;

liste_argument1:
TOKEN_VIRGULE argument liste_argument1 { $$ = mp($2, $3); }
| { $$ = (class pliste<CPexpr> *)NULL; }
;

argument:
expr { $$ = $1; }
;



expr: 
  expr TOKEN_OR  expr1 {
  $$ = new CPexpr($1->position.deb_ligne, $3->position.fin_ligne, $1->position.deb_car, $3->position.fin_car, $1->position.deb_car_tot, $3->position.fin_car_tot);
  $$->type = CPexpr::POu;
  $$->val.upou.e1 = $1;
  $$->val.upou.e2 = $3;
}
| expr TOKEN_AND expr1 {
  $$ = new CPexpr($1->position.deb_ligne, $3->position.fin_ligne, $1->position.deb_car, $3->position.fin_car, $1->position.deb_car_tot, $3->position.fin_car_tot);
  $$->type = CPexpr::PEt;
  $$->val.upet.e1 = $1;
  $$->val.upet.e2 = $3;
}
| expr1 { $$ = $1; }
  ;


expr1:
  expr1 TOKEN_EQUAL expr2 {
  $$ = new CPexpr($1->position.deb_ligne, $3->position.fin_ligne, $1->position.deb_car, $3->position.fin_car, $1->position.deb_car_tot, $3->position.fin_car_tot);
  $$->type = CPexpr::PEqual;
  $$->val.upequal.e1 = $1;
  $$->val.upequal.e2 = $3;
}
| expr1 TOKEN_DIFF  expr2 {
  $$ = new CPexpr($1->position.deb_ligne, $3->position.fin_ligne, $1->position.deb_car, $3->position.fin_car, $1->position.deb_car_tot, $3->position.fin_car_tot);
  $$->type = CPexpr::PDiff;
  $$->val.updiff.e1 = $1;
  $$->val.updiff.e2 = $3;
}
| expr1 TOKEN_INF   expr2 {
  $$ = new CPexpr($1->position.deb_ligne, $3->position.fin_ligne, $1->position.deb_car, $3->position.fin_car, $1->position.deb_car_tot, $3->position.fin_car_tot);
  $$->type = CPexpr::PInf;
  $$->val.upinf.e1 = $1;
  $$->val.upinf.e2 = $3;
}
| expr1 TOKEN_SUP   expr2 {
  $$ = new CPexpr($1->position.deb_ligne, $3->position.fin_ligne, $1->position.deb_car, $3->position.fin_car, $1->position.deb_car_tot, $3->position.fin_car_tot);
  $$->type = CPexpr::PSup;
  $$->val.upsup.e1 = $1;
  $$->val.upsup.e2 = $3;
}
| expr1 TOKEN_INFEQ expr2 {
  $$ = new CPexpr($1->position.deb_ligne, $3->position.fin_ligne, $1->position.deb_car, $3->position.fin_car, $1->position.deb_car_tot, $3->position.fin_car_tot);
  $$->type = CPexpr::PInfEq;
  $$->val.upinfeq.e1 = $1;
  $$->val.upinfeq.e2 = $3;
}
| expr1 TOKEN_SUPEQ expr2 {
  $$ = new CPexpr($1->position.deb_ligne, $3->position.fin_ligne, $1->position.deb_car, $3->position.fin_car, $1->position.deb_car_tot, $3->position.fin_car_tot);
  $$->type = CPexpr::PSupEq;
  $$->val.upsupeq.e1 = $1;
  $$->val.upsupeq.e2 = $3;
}
| expr2 { $$ = $1; }
  ;

expr2:
  expr2 TOKEN_IPLUS  expr3 {
  $$ = new CPexpr($1->position.deb_ligne, $3->position.fin_ligne, $1->position.deb_car, $3->position.fin_car, $1->position.deb_car_tot, $3->position.fin_car_tot);
  $$->type = CPexpr::PIPlus;
  $$->val.upiplus.e1 = $1;
  $$->val.upiplus.e2 = $3;
}
| expr2 TOKEN_IMOINS expr3 {
  $$ = new CPexpr($1->position.deb_ligne, $3->position.fin_ligne, $1->position.deb_car, $3->position.fin_car, $1->position.deb_car_tot, $3->position.fin_car_tot);
  $$->type = CPexpr::PIMoins;
  $$->val.upimoins.e1 = $1;
  $$->val.upimoins.e2 = $3;
}
| expr2 TOKEN_RPLUS  expr3 {
  $$ = new CPexpr($1->position.deb_ligne, $3->position.fin_ligne, $1->position.deb_car, $3->position.fin_car, $1->position.deb_car_tot, $3->position.fin_car_tot);
  $$->type = CPexpr::PRPlus;
  $$->val.uprplus.e1 = $1;
  $$->val.uprplus.e2 = $3;
}
| expr2 TOKEN_RMOINS expr3 {
  $$ = new CPexpr($1->position.deb_ligne, $3->position.fin_ligne, $1->position.deb_car, $3->position.fin_car, $1->position.deb_car_tot, $3->position.fin_car_tot);
  $$->type = CPexpr::PRMoins;
  $$->val.uprmoins.e1 = $1;
  $$->val.uprmoins.e2 = $3;
}
| expr3 { $$ = $1; }
  ;

expr3:
  expr3 TOKEN_IMULT expr4 {
  $$ = new CPexpr($1->position.deb_ligne, $3->position.fin_ligne, $1->position.deb_car, $3->position.fin_car, $1->position.deb_car_tot, $3->position.fin_car_tot);
  $$->type = CPexpr::PIMult;
  $$->val.upimult.e1 = $1;
  $$->val.upimult.e2 = $3;
}
| expr3 TOKEN_IDIV  expr4 {
  $$ = new CPexpr($1->position.deb_ligne, $3->position.fin_ligne, $1->position.deb_car, $3->position.fin_car, $1->position.deb_car_tot, $3->position.fin_car_tot);
  $$->type = CPexpr::PIDiv;
  $$->val.upidiv.e1 = $1;
  $$->val.upidiv.e2 = $3;
}
| expr3 TOKEN_IMOD  expr4 {
  $$ = new CPexpr($1->position.deb_ligne, $3->position.fin_ligne, $1->position.deb_car, $3->position.fin_car, $1->position.deb_car_tot, $3->position.fin_car_tot);
  $$->type = CPexpr::PIMod;
  $$->val.upimod.e1 = $1;
  $$->val.upimod.e2 = $3;
}
| expr3 TOKEN_RMULT expr4 {
  $$ = new CPexpr($1->position.deb_ligne, $3->position.fin_ligne, $1->position.deb_car, $3->position.fin_car, $1->position.deb_car_tot, $3->position.fin_car_tot);
  $$->type = CPexpr::PRMult;
  $$->val.uprmult.e1 = $1;
  $$->val.uprmult.e2 = $3;
}
| expr3 TOKEN_RDIV  expr4 {
  $$ = new CPexpr($1->position.deb_ligne, $3->position.fin_ligne, $1->position.deb_car, $3->position.fin_car, $1->position.deb_car_tot, $3->position.fin_car_tot);
  $$->type = CPexpr::PRDiv;
  $$->val.uprdiv.e1 = $1;
  $$->val.uprdiv.e2 = $3;
}
| expr4 { $$ = $1; }
  ;

expr4:
TOKEN_NOT    expr4 { 
  $$ = new CPexpr($1.position.nb_lignes, $2->position.fin_ligne, $1.position.nb_char_ligne, $2->position.fin_car, $1.position.nb_char_tot, $2->position.fin_car_tot);
  $$->type = CPexpr::PNot;
  $$->val.upnot.e = $2;
}
| TOKEN_IPLUS  expr4 { 
  $$ = new CPexpr($1.position.nb_lignes, $2->position.fin_ligne, $1.position.nb_char_ligne, $2->position.fin_car, $1.position.nb_char_tot, $2->position.fin_car_tot);
  $$->type = CPexpr::PUIPlus;
  $$->val.upuiplus.e = $2;
}
| TOKEN_IMOINS expr4 { 
  $$ = new CPexpr($1.position.nb_lignes, $2->position.fin_ligne, $1.position.nb_char_ligne, $2->position.fin_car, $1.position.nb_char_tot, $2->position.fin_car_tot);
  $$->type = CPexpr::PUIMoins;
  $$->val.upuimoins.e = $2;
}
| TOKEN_RPLUS  expr4 {
  $$ = new CPexpr($1.position.nb_lignes, $2->position.fin_ligne, $1.position.nb_char_ligne, $2->position.fin_car, $1.position.nb_char_tot, $2->position.fin_car_tot);
  $$->type = CPexpr::PURPlus;
  $$->val.upurplus.e = $2;
}
| TOKEN_RMOINS expr4 { 
  $$ = new CPexpr($1.position.nb_lignes, $2->position.fin_ligne, $1.position.nb_char_ligne, $2->position.fin_car, $1.position.nb_char_tot, $2->position.fin_car_tot);
  $$->type = CPexpr::PURMoins;
  $$->val.upurmoins.e = $2;
}
| expr5 { $$ = $1; }
;

expr5:
expr5 TOKEN_PTR {
  $$ = new CPexpr($1->position.deb_ligne, $2.position.nb_lignes, $1->position.deb_car, $2.position.nb_char_ligne + $2.position.longueur, $1->position.deb_car_tot, $2.position.nb_char_tot + $2.position.longueur); 
  $$->type = CPexpr::PInd;
  $$->val.upind.e = $1;
}
| TOKEN_REF expr5 {
  $$ = new CPexpr($2->position.deb_ligne, $1.position.nb_lignes, $2->position.deb_car, $1.position.nb_char_ligne + $1.position.longueur, $2->position.deb_car_tot, $1.position.nb_char_tot + $1.position.longueur); 
  $$->type = CPexpr::PRef;
  $$->val.upref.e = $2;
}
| expr5 TOKEN_OPENBRACKET expr TOKEN_CLOSEBRACKET { 
  $$ = new CPexpr($1->position.deb_ligne, $4.position.nb_lignes, $1->position.deb_car, $4.position.nb_char_ligne + $4.position.longueur, $1->position.deb_car_tot, $4.position.nb_char_tot + $4.position.longueur); 
  $$->type = CPexpr::PTab;
  $$->val.uptab.e1 = $1;
  $$->val.uptab.e2 = $3;
}
| expr5 TOKEN_POINT TOKEN_IDENT {/*!!!!!!!!!!!!!*/
  $$ = new CPexpr($1->position.deb_ligne, $3.position.nb_lignes, $1->position.deb_car, $3.position.nb_char_ligne + $3.position.longueur, $1->position.deb_car_tot, $3.position.nb_char_tot + $3.position.longueur); 
  $$->type = CPexpr::PRecord; 
  $$->val.uprecord.e = $1;
  $$->val.uprecord.champ = $3.val.ident;
}
| expr6 { $$ = $1; }
;

expr6:
appel_expr { $$ = $1; }
| nom_carte { $$ = $1; }
| expr7 { $$ = $1; }
;

expr7:
  valeur { $$ = $1; }
| TOKEN_OPENPAR expr TOKEN_CLOSEPAR { 
  /* !!!!  */ 
  //$$ = $2; 
  /*
  $$->position = *(new pascal_position($1.position.nb_lignes, $3.position.nb_lignes, $1.position.nb_char_ligne, $3.position.nb_char_ligne + $3.position.longueur, $1.position.nb_char_tot, $3.position.nb_char_tot + $3.position.longueur));
  */
  $$ = $2;
}
  ;





valeur:
booleen { $$ = $1; }
| TOKEN_ENTIER { 
  $$ = new CPexpr($1.position.nb_lignes, $1.position.nb_lignes, $1.position.nb_char_ligne, $1.position.nb_char_ligne + $1.position.longueur, $1.position.nb_char_tot, $1.position.nb_char_tot + $1.position.longueur); 
  $$->type = CPexpr::PConst; 
  $$->val.upconst.pconst.type.type = pevaltype::PETInteger; 
  $$->val.upconst.pconst.val.val.i = $1.val.entier; 
}
| TOKEN_REEL { 
  $$ = new CPexpr($1.position.nb_lignes, $1.position.nb_lignes, $1.position.nb_char_ligne, $1.position.nb_char_ligne + $1.position.longueur, $1.position.nb_char_tot, $1.position.nb_char_tot + $1.position.longueur); 
  $$->type = CPexpr::PConst; 
  $$->val.upconst.pconst.type.type = pevaltype::PETReal; 
  $$->val.upconst.pconst.val.val.r = $1.val.reel; 
}
| TOKEN_CHAINE { 
  $$ = new CPexpr($1.position.nb_lignes, $1.position.nb_lignes, $1.position.nb_char_ligne, $1.position.nb_char_ligne + $1.position.longueur, $1.position.nb_char_tot, $1.position.nb_char_tot + $1.position.longueur); 
  $$->type = CPexpr::PConst; 
  $$->val.upconst.pconst.type.type = pevaltype::PETString; 
  $$->val.upconst.pconst.val.val.str = $1.val.chaine; 
}
| TOKEN_IDENT { 
  $$ = new CPexpr($1.position.nb_lignes, $1.position.nb_lignes, $1.position.nb_char_ligne, $1.position.nb_char_ligne + $1.position.longueur, $1.position.nb_char_tot, $1.position.nb_char_tot + $1.position.longueur); 
  $$->type = CPexpr::PIdent; 
  $$->val.upident.pident = $1.val.ident;
}
| TOKEN_NIL {
  $$ = new CPexpr($1.position.nb_lignes, $1.position.nb_lignes, $1.position.nb_char_ligne, $1.position.nb_char_ligne + $1.position.longueur, $1.position.nb_char_tot, $1.position.nb_char_tot + $1.position.longueur); 
  $$->type = CPexpr::PConst; 
  $$->val.upconst.pconst.type.type = pevaltype::PETPointer;
  $$->val.upconst.pconst.type.val.ptr = new pevaltype;
  $$->val.upconst.pconst.type.val.ptr->type = pevaltype::PETVide;
  $$->val.upconst.pconst.val.val.ptr = 0;
}
| TOKEN_MENU TOKEN_OPENPAR TOKEN_CHAINE TOKEN_CLOSEPAR TOKEN_BEGIN menu_items TOKEN_END {
  $$ = new CPexpr($1.position.nb_lignes, $7.position.nb_lignes, $1.position.nb_char_ligne, $7.position.nb_char_ligne + $7.position.longueur, $1.position.nb_char_tot, $7.position.nb_char_tot + $7.position.longueur); 
  $$->type = CPexpr::PMenu;
  $$->val.upmenu.nom = $3.val.chaine;
  $$->val.upmenu.pitems = $6;
}
;

booleen: 
  TOKEN_TRUE { 
    $$ = new CPexpr($1.position.nb_lignes, $1.position.nb_lignes, $1.position.nb_char_ligne, $1.position.nb_char_ligne + $1.position.longueur, $1.position.nb_char_tot, $1.position.nb_char_tot + $1.position.longueur); 
    $$->type = CPexpr::PConst; 
    $$->val.upconst.pconst.type.type = pevaltype::PETBoolean; 
    $$->val.upconst.pconst.val.val.b = true; 
  }
| TOKEN_FALSE  { 
    $$ = new CPexpr($1.position.nb_lignes, $1.position.nb_lignes, $1.position.nb_char_ligne, $1.position.nb_char_ligne + $1.position.longueur, $1.position.nb_char_tot, $1.position.nb_char_tot + $1.position.longueur); 
    $$->type = CPexpr::PConst; 
    $$->val.upconst.pconst.type.type = pevaltype::PETBoolean; 
    $$->val.upconst.pconst.val.val.b = false; 
  }

;


menu_items:
menu_item menu_items1 { $$ = mp($1, $2); }
| menu_item { $$ = mp($1, (class pliste<struct CPexpr::utype::SPMenu::item> *)NULL); }
| { $$ = (class pliste<struct CPexpr::utype::SPMenu::item> *)NULL; }
;

menu_items1:
TOKEN_PTVIRG menu_item  menu_items1  { $$ = mp($2, $3); }
| TOKEN_PTVIRG  menu_items1  { $$ = $2; }
| TOKEN_PTVIRG menu_item { $$ = mp($2, (class pliste<struct CPexpr::utype::SPMenu::item> *)NULL); }
| TOKEN_PTVIRG { $$ = (class pliste<struct CPexpr::utype::SPMenu::item> *)NULL; }
;

menu_item:
additem1 { $$ = $1; }
| additem2 { $$ = $1; }
;

additem1:
TOKEN_ITEM TOKEN_OPENPAR TOKEN_CHAINE TOKEN_CLOSEPAR {
  $$ = new CPexpr::utype::SPMenu::item;
  $$->message = $3.val.chaine;
  $$->iconfile = NULL;
}
;

additem2:
TOKEN_ITEM TOKEN_OPENPAR TOKEN_CHAINE TOKEN_VIRGULE TOKEN_CHAINE TOKEN_CLOSEPAR {
  $$ = new CPexpr::utype::SPMenu::item;
  $$->message = $3.val.chaine;
  $$->iconfile = $5.val.chaine;
}
;






%%



static const void yyerror(char s[]) {
  //(void) printf("Erreur PARSING.");
  pmesserr("Erreur d'analyse syntaxique.");
  (void) fprintf(yypascalout, "Erreur d'analyse syntaxique.");
}
