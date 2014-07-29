#ifndef lint
/*static char yysccsid[] = "from: @(#)yaccpar	1.9 (Berkeley) 02/21/93";*/
static char yyrcsid[]
#if __GNUC__ >= 2
  __attribute__ ((unused))
#endif /* __GNUC__ >= 2 */
  = "$OpenBSD: skeleton.c,v 1.29 2008/07/08 15:06:50 otto Exp $";
#endif
#include <stdlib.h>
#include <string.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
#define yyparse yycarteparse
#define yylex yycartelex
#define yyerror yycarteerror
#define yychar yycartechar
#define yyval yycarteval
#define yylval yycartelval
#define yydebug yycartedebug
#define yynerrs yycartenerrs
#define yyerrflag yycarteerrflag
#define yyss yycartess
#define yysslim yycartesslim
#define yyssp yycartessp
#define yyvs yycartevs
#define yyvsp yycartevsp
#define yystacksize yycartestacksize
#define yylhs yycartelhs
#define yylen yycartelen
#define yydefred yycartedefred
#define yydgoto yycartedgoto
#define yysindex yycartesindex
#define yyrindex yycarterindex
#define yygindex yycartegindex
#define yytable yycartetable
#define yycheck yycartecheck
#define yyname yycartename
#define yyrule yycarterule
#define YYPREFIX "yycarte"
#line 1 "carte.parser.y"
 /* Header */
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

#line 28 "carte.parser.y"
#ifndef YYSTYPE_DEFINED
#define YYSTYPE_DEFINED
typedef union {
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
} YYSTYPE;
#endif /* YYSTYPE_DEFINED */
#line 90 "carte.parser.cpp"
#define Token_Booleen 257
#define Token_Entier 258
#define Token_Reel 259
#define Token_Chaine 260
#define Token_Ident 261
#define Token_Assign 262
#define Token_OpenPar 263
#define Token_OpenBrace 264
#define Token_OpenBracket 265
#define Token_ClosePar 266
#define Token_CloseBrace 267
#define Token_CloseBracket 268
#define Token_Ptvirg 269
#define Token_Virgule 270
#define Token_EOF 271
#define Token_Zone 272
#define Token_Evenement 273
#define Token_Genere 274
#define Token_Par 275
#define Token_Traitement 276
#define Token_Objet 277
#define Token_Objets 278
#define Token_Angle 279
#define Token_Qui 280
#define Token_X 281
#define Token_Y 282
#define Token_Z 283
#define Token_Tous 284
#define Token_Aucun 285
#define Token_Image 286
#define Token_Physique 287
#define Token_Gameplay 288
#define Token_Graphique 289
#define Token_Texture 290
#define Token_Textures 291
#define Token_Anime 292
#define Token_Niveau 293
#define Token_De 294
#define Token_Fichier 295
#define Token_Indice 296
#define Token_Position 297
#define Token_Arme 298
#define Token_Musique 299
#define Token_Eau 300
#define Token_Vie 301
#define Token_Teleportation 302
#define Token_Dimension 303
#define Token_Longueur 304
#define Token_Largeur 305
#define Token_Hauteur 306
#define Token_Direction 307
#define Token_Parcours 308
#define Token_Destination 309
#define Token_Gauche 310
#define Token_Droite 311
#define Token_Haut 312
#define Token_Bas 313
#define Token_PlusEntier 314
#define Token_MoinsEntier 315
#define Token_MultEntier 316
#define Token_DivEntier 317
#define Token_ModEntier 318
#define Token_PlusReel 319
#define Token_MoinsReel 320
#define Token_MultReel 321
#define Token_DivReel 322
#define Token_Procedure 323
#define YYERRCODE 256
#if defined(__cplusplus) || defined(__STDC__)
const short yycartelhs[] =
#else
short yycartelhs[] =
#endif
	{                                        -1,
    0,   12,   13,   14,   16,   15,   15,   19,    7,    7,
    7,    7,   11,   11,   10,   17,   17,   20,   18,   18,
   21,    9,    9,    9,    8,    1,    1,    1,    2,    2,
    2,    2,    3,    3,    3,    3,    4,    4,    4,    5,
    5,    5,    6,    6,    6,    6,
};
#if defined(__cplusplus) || defined(__STDC__)
const short yycartelen[] =
#else
short yycartelen[] =
#endif
	{                                         2,
    3,    3,   23,   14,    8,    2,    0,   71,    1,    1,
    1,    1,    2,    0,   13,    2,    0,   12,    2,    0,
   44,    1,    1,    1,   10,    3,    3,    1,    3,    3,
    3,    1,    1,    2,    2,    3,    3,    3,    1,    3,
    3,    1,    1,    2,    2,    3,
};
#if defined(__cplusplus) || defined(__STDC__)
const short yycartedefred[] =
#else
short yycartedefred[] =
#endif
	{                                      0,
    0,    0,    0,    0,    0,    0,    2,    0,    0,    1,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    5,    0,    0,   17,    0,    0,
   43,    0,    0,    0,    0,    0,   42,    0,    0,   16,
    0,   44,   45,    0,    0,    0,    0,    0,    0,    4,
    0,   19,   46,    0,    0,    0,   40,   41,    0,    0,
    0,    0,    0,    0,    0,    0,   33,    0,    0,    0,
    0,    0,   32,    0,    0,    0,   34,   35,    7,    0,
    0,    0,    0,    0,    0,    0,   36,    0,    0,    0,
   29,   30,   31,    0,    0,    0,    0,    6,    0,    0,
    0,    3,    0,   13,    0,    0,    0,    0,    0,    0,
    0,    0,   18,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   15,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   25,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   21,
    0,    0,    0,    0,    0,    0,    0,    9,   10,   11,
   12,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    8,
};
#if defined(__cplusplus) || defined(__STDC__)
const short yycartedgoto[] =
#else
short yycartedgoto[] =
#endif
	{                                       2,
   81,   82,   83,   45,   46,   47,  222,  148,    0,  114,
  107,    3,    6,   10,   98,   15,   40,   49,  108,   50,
   62,
};
#if defined(__cplusplus) || defined(__STDC__)
const short yycartesindex[] =
#else
short yycartesindex[] =
#endif
	{                                   -276,
 -238,    0, -271, -217, -197, -208,    0, -204, -154,    0,
 -156, -183, -143, -177, -176, -145, -147, -165, -167, -164,
 -139, -125, -155, -152, -121, -115, -136, -128, -102,  -95,
 -124, -101,  -90, -129,    0,  -97,  -89,    0, -258, -116,
    0, -258, -258, -258, -248, -269,    0,  -86, -253,    0,
 -250,    0,    0, -123, -258, -258, -258, -258,  -88,    0,
  -84,    0,    0, -120, -269, -269,    0,    0, -107,  -83,
  -80,  -79, -108, -255,  -75,  -76,    0, -255, -255, -255,
 -218, -279,    0,  -82,  -69, -222,    0,    0,    0, -255,
 -255, -255, -255, -255, -106,  -77,    0, -113, -279, -279,
    0,    0,    0,  -71, -100,  -68, -245,    0, -255,  -66,
  -70,    0,  -64,    0, -213,  -62, -110,  -63,  -67,  -65,
  -60,  -61,    0,  -94,  -55,  -59,  -56,  -58,  -54,  -57,
  -87,  -49,  -53,  -50,  -52,  -48,  -46,  -51, -258,  -47,
  -43, -246,  -42,  -41,  -45, -255,  -74,  -39,  -38, -187,
  -36,  -35, -258,  -44,  -33,    0, -244,  -31,  -34,  -37,
 -255,  -81,  -29, -171,  -26, -258,  -32,  -21, -242,  -22,
  -28,  -30, -255,  -24,  -27, -169,    0,  -18,  -20, -258,
  -19, -240,  -23,  -17,  -14,  -16,  -12,   -9,  -15, -258,
   -7, -235, -255,  -11, -166,  -13,  -10,   -6,   -5, -258,
 -255, -233, -162,   -8,  -91,   -4,   -2,   -3, -255,    0,
 -158,    2,    3,  -85,   -1,    1, -264,    0,    0,    0,
    0,    4,    5,    6,    9,   10,    7,   13, -255, -153,
    8,   15, -255, -151,   11,   16, -255, -149,   12,   17,
   18,   19,   20,   21, -264,   22,   25,    0,};
#if defined(__cplusplus) || defined(__STDC__)
const short yycarterindex[] =
#else
short yycarterindex[] =
#endif
	{                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -247,
    0,    0,    0,    0,    0, -262,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -256, -254,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -260,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -232, -226, -224,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,};
#if defined(__cplusplus) || defined(__STDC__)
const short yycartegindex[] =
#else
short yycartegindex[] =
#endif
	{                                      0,
  -78,   14,   42,  -40,   53,  -25,   31,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,
};
#define YYTABLESIZE 328
#if defined(__cplusplus) || defined(__STDC__)
const short yycartetable[] =
#else
short yycartetable[] =
#endif
	{                                      86,
   41,   51,   77,   39,   42,   28,   39,   78,   28,   37,
    1,   38,   37,   60,   38,   63,    5,   52,   53,   20,
   54,  112,  145,   61,  160,    4,  172,  113,  184,   20,
  115,   67,   68,  194,   14,  204,   92,   93,   94,   26,
   14,   27,   26,   97,   27,  218,  219,  220,  221,    7,
   89,   57,   58,   28,   28,  119,   39,   39,   79,   80,
   43,   44,   37,   37,   38,   38,    8,  150,   55,   56,
   55,   56,   55,   56,   55,   56,   55,   56,   55,   56,
    9,  154,  164,   55,   56,   55,   56,   26,   26,   27,
   27,   90,   91,   11,  176,   90,   91,  167,  142,  179,
   90,   91,  197,   99,  100,   13,  205,   65,   66,   12,
  212,   14,  157,   16,  195,  231,   17,  235,   18,  239,
   87,   88,  203,   19,   20,  169,   90,   91,   21,   23,
  211,   22,   24,  101,  102,  103,   25,   26,   28,  182,
   31,   27,   90,   91,   90,   91,   29,   90,   91,  192,
  230,   90,   91,   30,  234,   90,   91,   32,  238,  202,
   90,   91,   90,   91,   90,   91,   33,   35,   34,   36,
   37,   38,   39,   48,   59,   69,   70,   64,   72,   71,
   73,   74,   75,   76,   84,   85,   95,   96,  106,  104,
  109,  105,  111,  117,  110,  116,  118,  120,  121,  123,
  122,  125,  127,  124,  128,  130,  133,  132,  135,  134,
  131,  137,  126,  139,  207,  129,  138,  140,  144,  146,
  151,  215,  147,  153,  141,  155,  159,  136,    0,  152,
  161,  156,  166,  143,  162,  168,  149,  158,  171,  173,
  174,  165,  177,  180,    0,  163,  181,  187,  175,  183,
  170,  189,  190,  178,  193,  200,  201,    0,  206,  209,
    0,  186,  217,  210,  208,  188,    0,  196,  213,  198,
  226,  214,  223,  227,  229,  246,  233,  237,  240,  185,
    0,    0,  245,    0,    0,  241,    0,  228,  191,  232,
  247,  248,    0,  236,  199,    0,    0,    0,    0,    0,
    0,    0,  225,    0,    0,    0,  216,    0,    0,    0,
    0,    0,    0,  224,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  243,  242,  244,
};
#if defined(__cplusplus) || defined(__STDC__)
const short yycartecheck[] =
#else
short yycartecheck[] =
#endif
	{                                      78,
  259,   42,  258,  266,  263,  266,  269,  263,  269,  266,
  287,  266,  269,  267,  269,  266,  288,   43,   44,  267,
  269,  267,  269,  277,  269,  264,  269,  273,  269,  277,
  109,   57,   58,  269,  267,  269,  316,  317,  318,  266,
  273,  266,  269,  266,  269,  310,  311,  312,  313,  267,
  269,  321,  322,  314,  315,  269,  319,  320,  314,  315,
  319,  320,  319,  320,  319,  320,  264,  146,  319,  320,
  319,  320,  319,  320,  319,  320,  319,  320,  319,  320,
  289,  269,  161,  319,  320,  319,  320,  314,  315,  314,
  315,  314,  315,  298,  173,  314,  315,  269,  139,  269,
  314,  315,  269,   90,   91,  262,  269,   55,   56,  264,
  269,  295,  153,  257,  193,  269,  294,  269,  295,  269,
   79,   80,  201,  269,  272,  166,  314,  315,  294,  294,
  209,  299,  272,   92,   93,   94,  262,  293,  260,  180,
  269,  294,  314,  315,  314,  315,  262,  314,  315,  190,
  229,  314,  315,  290,  233,  314,  315,  260,  237,  200,
  314,  315,  314,  315,  314,  315,  262,  269,  293,  260,
  300,  269,  262,  290,  261,  264,  261,  301,  286,  300,
  264,  262,  262,  292,  260,  262,  269,  257,  302,  296,
  262,  269,  261,  264,  295,  262,  261,  260,  309,  267,
  264,  262,  297,  269,  260,  262,  264,  262,  258,  297,
  269,  262,  274,  262,  306,  275,  269,  264,  262,  262,
  295,  307,  264,  262,  276,  262,  260,  281,   -1,  269,
  262,  267,  262,  281,  269,  262,  282,  282,  260,  262,
  269,  323,  267,  262,   -1,  283,  267,  262,  279,  269,
  283,  264,  262,  281,  262,  262,  262,   -1,  267,  262,
   -1,  279,  262,  267,  269,  282,   -1,  279,  267,  283,
  262,  269,  269,  264,  262,  245,  262,  262,  267,  303,
   -1,   -1,  262,   -1,   -1,  269,   -1,  281,  304,  282,
  269,  267,   -1,  283,  305,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  297,   -1,   -1,   -1,  308,   -1,   -1,   -1,
   -1,   -1,   -1,  309,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  307,  309,  308,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 323
#if YYDEBUG
#if defined(__cplusplus) || defined(__STDC__)
const char * const yycartename[] =
#else
char *yycartename[] =
#endif
	{
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Token_Booleen","Token_Entier",
"Token_Reel","Token_Chaine","Token_Ident","Token_Assign","Token_OpenPar",
"Token_OpenBrace","Token_OpenBracket","Token_ClosePar","Token_CloseBrace",
"Token_CloseBracket","Token_Ptvirg","Token_Virgule","Token_EOF","Token_Zone",
"Token_Evenement","Token_Genere","Token_Par","Token_Traitement","Token_Objet",
"Token_Objets","Token_Angle","Token_Qui","Token_X","Token_Y","Token_Z",
"Token_Tous","Token_Aucun","Token_Image","Token_Physique","Token_Gameplay",
"Token_Graphique","Token_Texture","Token_Textures","Token_Anime","Token_Niveau",
"Token_De","Token_Fichier","Token_Indice","Token_Position","Token_Arme",
"Token_Musique","Token_Eau","Token_Vie","Token_Teleportation","Token_Dimension",
"Token_Longueur","Token_Largeur","Token_Hauteur","Token_Direction",
"Token_Parcours","Token_Destination","Token_Gauche","Token_Droite","Token_Haut",
"Token_Bas","Token_PlusEntier","Token_MoinsEntier","Token_MultEntier",
"Token_DivEntier","Token_ModEntier","Token_PlusReel","Token_MoinsReel",
"Token_MultReel","Token_DivReel","Token_Procedure",
};
#if defined(__cplusplus) || defined(__STDC__)
const char * const yycarterule[] =
#else
char *yycarterule[] =
#endif
	{"$accept : main",
"main : physique gameplay graphique",
"physique : Token_Physique Token_OpenBrace Token_CloseBrace",
"gameplay : Token_Gameplay Token_OpenBrace Token_Arme Token_Assign Token_Booleen Token_Ptvirg Token_Musique Token_Assign Token_Chaine Token_Ptvirg Token_Niveau Token_Eau Token_Assign expr_reel Token_Ptvirg Token_Vie Token_Eau Token_Assign expr_entier Token_Ptvirg liste_teleportation liste_evenement Token_CloseBrace",
"graphique : Token_Graphique Token_OpenBrace zone_niveau Token_Fichier Token_De Token_Zone Token_De Token_Texture Token_Assign Token_Chaine Token_Ptvirg liste_texture liste_objet Token_CloseBrace",
"zone_niveau : Token_Fichier Token_De Token_Zone Token_De Token_Niveau Token_Assign Token_Chaine Token_Ptvirg",
"liste_teleportation : liste_teleportation teleportation",
"liste_teleportation :",
"teleportation : Token_Teleportation Token_Ident Token_OpenBrace Token_Destination Token_Assign Token_Chaine Token_Ptvirg Token_Position Token_Assign Token_OpenBrace Token_X Token_Assign expr_entier Token_Ptvirg Token_Y Token_Assign expr_entier Token_Ptvirg Token_Z Token_Assign expr_entier Token_Ptvirg Token_CloseBrace Token_Ptvirg Token_Dimension Token_Assign Token_OpenBrace Token_Longueur Token_Assign expr_entier Token_Ptvirg Token_Largeur Token_Assign expr_entier Token_Ptvirg Token_Hauteur Token_Assign expr_entier Token_Ptvirg Token_CloseBrace Token_Ptvirg Token_Direction Token_Parcours Token_Assign direction Token_Ptvirg Token_Destination Token_Position Token_Assign Token_OpenBrace Token_X Token_Assign expr_entier Token_Ptvirg Token_Y Token_Assign expr_entier Token_Ptvirg Token_Z Token_Assign expr_entier Token_Ptvirg Token_CloseBrace Token_Ptvirg Token_Destination Token_Direction Token_Parcours Token_Assign direction Token_Ptvirg Token_CloseBrace",
"direction : Token_Gauche",
"direction : Token_Droite",
"direction : Token_Haut",
"direction : Token_Bas",
"liste_evenement : liste_evenement evenement",
"liste_evenement :",
"evenement : Token_Evenement Token_Ident Token_OpenBrace Token_Genere Token_Par Token_Assign Token_Entier Token_Ptvirg Token_Traitement Token_Assign code Token_Ptvirg Token_CloseBrace",
"liste_texture : liste_texture texture",
"liste_texture :",
"texture : Token_Texture Token_Ident Token_OpenBrace Token_Image Token_Assign Token_Chaine Token_Ptvirg Token_Indice Token_Assign expr_entier Token_Ptvirg Token_CloseBrace",
"liste_objet : liste_objet objet",
"liste_objet :",
"objet : Token_Objet Token_Ident Token_OpenBrace Token_Anime Token_Assign Token_Booleen Token_Ptvirg Token_Fichier Token_Assign Token_Chaine Token_Ptvirg Token_Position Token_Assign Token_OpenBrace Token_X Token_Assign expr_reel Token_Ptvirg Token_Y Token_Assign expr_reel Token_Ptvirg Token_Z Token_Assign expr_reel Token_Ptvirg Token_Angle Token_X Token_Assign expr_reel Token_Ptvirg Token_Angle Token_Y Token_Assign expr_reel Token_Ptvirg Token_Angle Token_Z Token_Assign expr_reel Token_Ptvirg Token_CloseBrace Token_Ptvirg Token_CloseBrace",
"genere : Token_Aucun",
"genere : Token_Tous",
"genere : code",
"code : Token_OpenBrace Token_Fichier Token_Assign Token_Chaine Token_Ptvirg Token_Procedure Token_Assign Token_Chaine Token_Ptvirg Token_CloseBrace",
"expr_entier : expr_entier Token_PlusEntier expr_entier1",
"expr_entier : expr_entier Token_MoinsEntier expr_entier1",
"expr_entier : expr_entier1",
"expr_entier1 : expr_entier1 Token_MultEntier expr_entier2",
"expr_entier1 : expr_entier1 Token_DivEntier expr_entier2",
"expr_entier1 : expr_entier1 Token_ModEntier expr_entier2",
"expr_entier1 : expr_entier2",
"expr_entier2 : Token_Entier",
"expr_entier2 : Token_PlusEntier expr_entier2",
"expr_entier2 : Token_MoinsEntier expr_entier2",
"expr_entier2 : Token_OpenPar expr_entier Token_ClosePar",
"expr_reel : expr_reel Token_PlusReel expr_reel1",
"expr_reel : expr_reel Token_MoinsReel expr_reel1",
"expr_reel : expr_reel1",
"expr_reel1 : expr_reel1 Token_MultReel expr_reel2",
"expr_reel1 : expr_reel1 Token_DivReel expr_reel2",
"expr_reel1 : expr_reel2",
"expr_reel2 : Token_Reel",
"expr_reel2 : Token_PlusReel expr_reel2",
"expr_reel2 : Token_MoinsReel expr_reel2",
"expr_reel2 : Token_OpenPar expr_reel Token_ClosePar",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
/* LINTUSED */
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
int yystacksize;
#line 408 "carte.parser.y"


/*extern void yyerror(char *msg);*/
#include <stdio.h>
static const void yyerror(char s[]) {
  int a, b, c;
  a = carte_get_nb_chars();
  b = carte_get_nb_chars_tot();
  c = carte_get_yyleng();
  carte_err( "Erreur d'analyse syntaxique sur le lexème \"%s\" à la ligne %d (caractères %d (%d) à %d (%d)) [%s]\n", carte_get_yytext(), carte_get_nb_lignes() + 1, a - c, b - c, a - 1, b - 1, s);
}

#line 452 "carte.parser.cpp"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
#if defined(__cplusplus) || defined(__STDC__)
static int yygrowstack(void)
#else
static int yygrowstack()
#endif
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    i = yyssp - yyss;
#ifdef SIZE_MAX
#define YY_SIZE_MAX SIZE_MAX
#else
#define YY_SIZE_MAX 0xffffffffU
#endif
    if (newsize && YY_SIZE_MAX / newsize < sizeof *newss)
        goto bail;
    newss = yyss ? (short *)realloc(yyss, newsize * sizeof *newss) :
      (short *)malloc(newsize * sizeof *newss); /* overflow check above */
    if (newss == NULL)
        goto bail;
    yyss = newss;
    yyssp = newss + i;
    if (newsize && YY_SIZE_MAX / newsize < sizeof *newvs)
        goto bail;
    newvs = yyvs ? (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs) :
      (YYSTYPE *)malloc(newsize * sizeof *newvs); /* overflow check above */
    if (newvs == NULL)
        goto bail;
    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
bail:
    if (yyss)
            free(yyss);
    if (yyvs)
            free(yyvs);
    yyss = yyssp = NULL;
    yyvs = yyvsp = NULL;
    yystacksize = 0;
    return -1;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
#if defined(__cplusplus) || defined(__STDC__)
yyparse(void)
#else
yyparse()
#endif
{
    int yym, yyn, yystate;
#if YYDEBUG
#if defined(__cplusplus) || defined(__STDC__)
    const char *yys;
#else /* !(defined(__cplusplus) || defined(__STDC__)) */
    char *yys;
#endif /* !(defined(__cplusplus) || defined(__STDC__)) */

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif /* YYDEBUG */

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#if defined(lint) || defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 115 "carte.parser.y"
{
  carte_mess("Le parser a reconnu un fichier de type .carte. Victoire !");
  return 0;
}
break;
case 2:
#line 123 "carte.parser.y"
{
  carte_mess("Le parser a reconnu la partie physique d'un .carte.");
}
break;
case 3:
#line 137 "carte.parser.y"
{
  carte_mess("Le parser a reconnu la partie gameplay d'un .carte.");
  if (SCRIPT_EstEnTrainDExecuterUnScript()) {
  }   
  else {
    SCRIPT_JouerMusique(yyvsp[-14].yychaine);
  }
  carte->ZEau = yyvsp[-9].yyreel;
  carte_mess("Done.");
}
break;
case 4:
#line 155 "carte.parser.y"
{
  carte_mess("Le parser a reconnu la partie graphique d'un .carte.");
  carte_mess("Chargement du fichier de description des textures du sol \"%s\".", yyvsp[-4].yychaine);
  carte->ChargerIndiceTextureBitmap(yyvsp[-4].yychaine);
  carte_mess("Chargement terminé.");
  carte_mess("Au fait, c'est la première texture qui est chargée par le programme pour le sol, étant donné que pour l'instant ça ne supporte pas une multiplicité de textures.");
}
break;
case 5:
#line 165 "carte.parser.y"
{
  carte_mess("Chargement du fichier de niveau \"%s\".", yyvsp[-1].yychaine);
  carte->ChargerZ(yyvsp[-1].yychaine);
  carte_mess("Chargement terminé.");
}
break;
case 6:
#line 173 "carte.parser.y"
{}
break;
case 7:
#line 174 "carte.parser.y"
{}
break;
case 8:
#line 198 "carte.parser.y"
{
  carte_mess("Ajout de la zone de téléportation %s", yyvsp[-69].yyident);
  carte->AjouterZoneTeleportation(
				  Point3D((float)yyvsp[-58].yyentier,(float)yyvsp[-54].yyentier,(float)yyvsp[-50].yyentier), /* position*/
				  Point3D((float)yyvsp[-41].yyentier,(float)yyvsp[-37].yyentier,(float)yyvsp[-33].yyentier), /* dimension*/
				  yyvsp[-26].dir, /* direction*/
				  yyvsp[-65].yychaine, /* la carte de destination*/
				  Point3D((float)yyvsp[-18].yyentier,(float)yyvsp[-14].yyentier,(float)yyvsp[-10].yyentier), /* position d'arrivée*/
				  yyvsp[-2].dir); /* direction d'arrivée*/
				  
				  
  
  carte_mess("Zone de téléportation ajoutée.");
}
break;
case 9:
#line 215 "carte.parser.y"
{yyval.dir = PROFIL_VERS_G;}
break;
case 10:
#line 216 "carte.parser.y"
{yyval.dir = PROFIL_VERS_D;}
break;
case 11:
#line 217 "carte.parser.y"
{yyval.dir = DOS;}
break;
case 12:
#line 218 "carte.parser.y"
{yyval.dir = FACE;}
break;
case 13:
#line 224 "carte.parser.y"
{}
break;
case 14:
#line 225 "carte.parser.y"
{}
break;
case 15:
#line 233 "carte.parser.y"
{
/*   $$ = carte_new_event();*/
/*   VERIF_NOT_NULL($$,-9)*/

/*   $$->genere = $7->type;*/
/*   if ($7->type == CODE) {*/
/*     $$->par = NULL;*/
/*   }*/

/*   else {*/
/*     $$->par = $7->code;*/
/*   }*/

/*   carte_del_sgenere(&($7));*/
/*   $$->traitement = $11;*/
  /*extern void AddTraitementEvenement(type_evt t, const char* nom_fichier, const char* proc);*/
  AddTraitementEvenement((type_evt)yyvsp[-6].yyentier, yyvsp[-2].code->fichier, yyvsp[-2].code->nom);
  carte_del_code(yyvsp[-2].code);
}
break;
case 16:
#line 255 "carte.parser.y"
{}
break;
case 17:
#line 256 "carte.parser.y"
{}
break;
case 18:
#line 264 "carte.parser.y"
{
  carte_mess("Reconnaissance d'un champ de description de texture par le parser. Cette texture s'appelle \"%s\".", yyvsp[-10].yyident);
  carte_mess("Chargement de la texture en mémoire (image = \"%s\", couleur associée = %d).", yyvsp[-6].yychaine, yyvsp[-2].yyentier);
  /*carte->TextureSol = gestionTexture.prendre($6);*/
  if (carte->nb_texture < NB_MAX_TEXTURESOL) {
    carte_mess("C'est bon. Il y a assez de places pour mettre la texture.");
    /*carte->indices_dans_bitmap[carte->nb_texture] = $10;*/
    /*carte->TextureSol[(carte->nb_texture)++] = gestionTexture.prendre($6);*/
    carte->AjouterTextureSol(yyvsp[-6].yychaine, yyvsp[-2].yyentier);
  }
  else {
    carte_err("Il n'y pas assez de place pour mettre la texture. Il faut changer NB_MAX_TEXTURESOL.");
  }
  carte_mess("[nb_textures = %d][NB_MAX_TEXTURES = %d]", carte->nb_texture, NB_MAX_TEXTURESOL);

  carte_mess("Fin du traitement de la texture \"%s\".", yyvsp[-10].yyident);
}
break;
case 19:
#line 284 "carte.parser.y"
{}
break;
case 20:
#line 285 "carte.parser.y"
{}
break;
case 21:
#line 301 "carte.parser.y"
{
  carte_mess("Le parser a reconnu un champ objet. Il s'appelle \"%s\".", yyvsp[-42].yyident);
  if (yyvsp[-38].yybooleen) {
    carte_mess("C'est un objet animé.");
    carte_mess("Chargement du fichier \"%s\".", yyvsp[-34].yychaine);
    CBonhomme *bonhomme = new CBonhomme(yyvsp[-34].yychaine);
    carte_mess("Chargement du fichier terminé. On positionne les autres attributs (x, y, z).");
    TPoint3D pos;
    pos.x = yyvsp[-27].yyreel;
    pos.y = yyvsp[-23].yyreel;
    pos.z = yyvsp[-19].yyreel;
    bonhomme->SetPosition(pos);
    carte_mess("Done. Ajout de l'objet à la carte.");
    carte->AjouterObjet(yyvsp[-42].yyident, bonhomme);
    carte_mess("Done. Les paramètres d'angles ne sont pas encore utilisés.");
  }

  else {
    carte_mess("C'est un objet non animé.");
    carte_mess("Chargement du fichier \"%s\".", yyvsp[-34].yychaine);
    CObjNonAnime* o = new CObjNonAnime(yyvsp[-34].yychaine);
    carte_mess("Chargement du fichier terminé. On positionne les autres attributs (x, y, z).");
    TPoint3D pos;
    pos.x = yyvsp[-27].yyreel;
    pos.y = yyvsp[-23].yyreel;
    pos.z = yyvsp[-19].yyreel;
    o->SetPosition(pos);
    carte_mess("Done. Ajout de l'objet à la carte.");
    carte->AjouterObjet(yyvsp[-42].yyident, o);
    carte_mess("Done. Les paramètres d'angles ne sont pas encore utilisés.");
  }

  /*  
      $$->angle_x = $30;
      $$->angle_y = $35;
      $$->angle_z = $40;
  */
}
break;
case 22:
#line 343 "carte.parser.y"
{yyval.genere = carte_new_sgenere(); VERIF_NOT_NULL(yyval.genere,-14); yyval.genere->type = AUCUN; yyval.genere->code =NULL;}
break;
case 23:
#line 345 "carte.parser.y"
{yyval.genere = carte_new_sgenere(); VERIF_NOT_NULL(yyval.genere,-15); yyval.genere->type = TOUS; yyval.genere->code = NULL;}
break;
case 24:
#line 347 "carte.parser.y"
{yyval.genere = carte_new_sgenere(); VERIF_NOT_NULL(yyval.genere,-16); yyval.genere->type = CODE; yyval.genere->code = yyvsp[0].code;}
break;
case 25:
#line 355 "carte.parser.y"
{ yyval.code = carte_new_code(); yyval.code->fichier = yyvsp[-6].yychaine; yyval.code->nom = yyvsp[-2].yychaine; }
break;
case 26:
#line 364 "carte.parser.y"
{ yyval.yyentier = yyvsp[-2].yyentier + yyvsp[0].yyentier; }
break;
case 27:
#line 365 "carte.parser.y"
{ yyval.yyentier = yyvsp[-2].yyentier - yyvsp[0].yyentier; }
break;
case 28:
#line 366 "carte.parser.y"
{ yyval.yyentier= yyvsp[0].yyentier; }
break;
case 29:
#line 370 "carte.parser.y"
{ yyval.yyentier = yyvsp[-2].yyentier * yyvsp[0].yyentier; }
break;
case 30:
#line 371 "carte.parser.y"
{ yyval.yyentier = yyvsp[-2].yyentier / yyvsp[0].yyentier; }
break;
case 31:
#line 372 "carte.parser.y"
{ yyval.yyentier = yyvsp[-2].yyentier % yyvsp[0].yyentier; }
break;
case 32:
#line 373 "carte.parser.y"
{ yyval.yyentier = yyvsp[0].yyentier; }
break;
case 33:
#line 377 "carte.parser.y"
{ yyval.yyentier = yyvsp[0].yyentier; }
break;
case 34:
#line 378 "carte.parser.y"
{ yyval.yyentier = yyvsp[0].yyentier; }
break;
case 35:
#line 379 "carte.parser.y"
{ yyval.yyentier = - yyvsp[0].yyentier; }
break;
case 36:
#line 380 "carte.parser.y"
{ yyval.yyentier = yyvsp[-1].yyentier; }
break;
case 37:
#line 385 "carte.parser.y"
{ yyval.yyreel = yyvsp[-2].yyreel + yyvsp[0].yyreel; }
break;
case 38:
#line 386 "carte.parser.y"
{ yyval.yyreel = yyvsp[-2].yyreel - yyvsp[0].yyreel; }
break;
case 39:
#line 387 "carte.parser.y"
{ yyval.yyreel= yyvsp[0].yyreel; }
break;
case 40:
#line 391 "carte.parser.y"
{ yyval.yyreel = yyvsp[-2].yyreel * yyvsp[0].yyreel; }
break;
case 41:
#line 392 "carte.parser.y"
{ yyval.yyreel = yyvsp[-2].yyreel / yyvsp[0].yyreel; }
break;
case 42:
#line 393 "carte.parser.y"
{ yyval.yyreel = yyvsp[0].yyreel; }
break;
case 43:
#line 397 "carte.parser.y"
{ yyval.yyreel = yyvsp[0].yyreel; }
break;
case 44:
#line 398 "carte.parser.y"
{ yyval.yyreel = yyvsp[0].yyreel; }
break;
case 45:
#line 399 "carte.parser.y"
{ yyval.yyreel = - yyvsp[0].yyreel; }
break;
case 46:
#line 400 "carte.parser.y"
{ yyval.yyreel = yyvsp[-1].yyreel; }
break;
#line 949 "carte.parser.cpp"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    if (yyss)
            free(yyss);
    if (yyvs)
            free(yyvs);
    yyss = yyssp = NULL;
    yyvs = yyvsp = NULL;
    yystacksize = 0;
    return (1);
yyaccept:
    if (yyss)
            free(yyss);
    if (yyvs)
            free(yyvs);
    yyss = yyssp = NULL;
    yyvs = yyvsp = NULL;
    yystacksize = 0;
    return (0);
}
