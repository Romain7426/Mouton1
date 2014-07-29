/* A Bison parser, made by GNU Bison 1.875b.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     Token_Booleen = 258,
     Token_Entier = 259,
     Token_Reel = 260,
     Token_Chaine = 261,
     Token_Ident = 262,
     Token_LAction = 263,
     Token_Assign = 264,
     Token_Plus = 265,
     Token_Moins = 266,
     Token_Mult = 267,
     Token_Div = 268,
     Token_OpenPar = 269,
     Token_OpenBrace = 270,
     Token_OpenBracket = 271,
     Token_ClosePar = 272,
     Token_CloseBrace = 273,
     Token_CloseBracket = 274,
     Token_Ptvirg = 275,
     Token_Virgule = 276,
     Token_EOF = 277,
     Token_Zone = 278,
     Token_Choc = 279,
     Token_Masse = 280,
     Token_Invinsible = 281,
     Token_Membres = 282,
     Token_Racines = 283,
     Token_Action = 284,
     Token_Menu = 285,
     Token_Affichage = 286,
     Token_Gestionnaire = 287,
     Token_Evenement = 288,
     Token_Genere = 289,
     Token_Par = 290,
     Token_Traitement = 291,
     Token_Membre = 292,
     Token_Fils = 293,
     Token_Angle = 294,
     Token_Max = 295,
     Token_Qui = 296,
     Token_X = 297,
     Token_Y = 298,
     Token_Z = 299,
     Token_Tous = 300,
     Token_Aucun = 301,
     Token_Image = 302,
     Token_Points = 303,
     Token_De = 304,
     Token_Vie = 305,
     Token_Hostile = 306,
     Token_Largeur = 307,
     Token_Longueur = 308,
     Token_Hauteur = 309,
     Token_Physique = 310,
     Token_Gameplay = 311,
     Token_Graphique = 312
   };
#endif
#define Token_Booleen 258
#define Token_Entier 259
#define Token_Reel 260
#define Token_Chaine 261
#define Token_Ident 262
#define Token_LAction 263
#define Token_Assign 264
#define Token_Plus 265
#define Token_Moins 266
#define Token_Mult 267
#define Token_Div 268
#define Token_OpenPar 269
#define Token_OpenBrace 270
#define Token_OpenBracket 271
#define Token_ClosePar 272
#define Token_CloseBrace 273
#define Token_CloseBracket 274
#define Token_Ptvirg 275
#define Token_Virgule 276
#define Token_EOF 277
#define Token_Zone 278
#define Token_Choc 279
#define Token_Masse 280
#define Token_Invinsible 281
#define Token_Membres 282
#define Token_Racines 283
#define Token_Action 284
#define Token_Menu 285
#define Token_Affichage 286
#define Token_Gestionnaire 287
#define Token_Evenement 288
#define Token_Genere 289
#define Token_Par 290
#define Token_Traitement 291
#define Token_Membre 292
#define Token_Fils 293
#define Token_Angle 294
#define Token_Max 295
#define Token_Qui 296
#define Token_X 297
#define Token_Y 298
#define Token_Z 299
#define Token_Tous 300
#define Token_Aucun 301
#define Token_Image 302
#define Token_Points 303
#define Token_De 304
#define Token_Vie 305
#define Token_Hostile 306
#define Token_Largeur 307
#define Token_Longueur 308
#define Token_Hauteur 309
#define Token_Physique 310
#define Token_Gameplay 311
#define Token_Graphique 312




/* Copy the first part of user declarations.  */
#line 1 "parser.y"
 /* Header */
#include <stdlib.h>
#include "anime.h"
#include "global.h"

const extern int get_nb_lignes(void);
const extern int get_nb_chars(void);
const extern int get_nb_chars_tot(void);
const extern int get_yyleng(void);
const extern char * get_yytext(void);
const extern int yylex(void);
const static void yyerror(char s[]);


#define VERIF_NOT_NULL(a,b) if (a == NULL) {yyerror("Manque de mémoire."); return b;}


 CBonhomme *bongars;


#define MAXMEMBRE 32
static memdesc memtab[MAXMEMBRE];
static int memnbelts = 0;
const static int memlookup(char *nom) {
  for (int i = 0; i < memnbelts; i++) {
    if (strcmp(nom, memtab[i].nom) == 0) {
      return i;
    }
  }
  return -1;
}

const static void memempiler(CPantin *pere, liste *fils) {
  filsdesc *temp;
  while (fils != NULL) {
    int j;
    temp = (filsdesc*) fils->contenu;

    if ((j = memlookup(temp->qui)) < 0) {
      yyerror(strcat(strcat("Le membre \"", temp->qui), " n'a pas ete defini. On continue néanmoins.\n"));
    }
    
    else {
      CPantin *p = new CPantin;
      p->AjouterMembre(memtab[j].image, temp->x, temp->y, temp->z, memtab[j].largeur, memtab[j].hauteur, memtab[j].angle_max_y);
      pere->SetPantinFilsAuDernierMembre(p);
      memempiler(p, memtab[j].fils);
    }
    fils = fils->suivant;
  }
}






/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 64 "parser.y"
typedef union YYSTYPE {
booleen yybooleen;
int yyentier;
double yyreel;
char *yychaine;
char *yyident;
action yylaction;

tcode yycode;
sgenere *yygenere;
filsdesc *yyfils;
tmembre *yymembre;
tevent *yyevent;
taction *yyaction;
liste *yyliste;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 264 "parser.cpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 276 "parser.cpp"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   152

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  17
/* YYNRULES -- Number of rules. */
#define YYNRULES  24
/* YYNRULES -- Number of states. */
#define YYNSTATES  149

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   312

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     7,    34,    54,    64,    67,    68,    85,
      88,    89,   103,   106,   107,   134,   136,   140,   142,   166,
     169,   170,   172,   174,   176
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      59,     0,    -1,    60,    61,    62,    -1,    55,    15,    23,
      49,    24,     9,    15,    53,     9,     5,    20,    52,     9,
       5,    20,    54,     9,     5,    20,    18,    20,    25,     9,
       5,    20,    18,    -1,    56,    15,    48,    49,    50,     9,
       4,    20,    26,     9,     3,    20,    51,     9,     3,    20,
      63,    65,    18,    -1,    57,    15,    67,    27,    28,     9,
      69,    20,    18,    -1,    63,    64,    -1,    -1,    29,     8,
      15,    30,     9,     3,    20,    31,     9,     6,    20,    32,
       9,    74,    20,    18,    -1,    65,    66,    -1,    -1,    33,
       7,    15,    34,    35,     9,    73,    20,    36,     9,    74,
      20,    18,    -1,    67,    68,    -1,    -1,    37,     7,    15,
      38,     9,    70,    20,    47,     9,     6,    20,    52,     9,
       5,    20,    54,     9,     5,    20,    39,    40,    43,     9,
       5,    20,    18,    -1,    70,    -1,    70,    71,    72,    -1,
      72,    -1,    15,    41,     9,     7,    20,    42,     9,     5,
      20,    43,     9,     5,    20,    44,     9,     5,    20,    39,
      43,     9,     5,    20,    18,    -1,    72,    21,    -1,    -1,
      46,    -1,    45,    -1,    74,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   137,   137,   142,   155,   166,   190,   191,   195,   209,
     210,   214,   236,   237,   241,   260,   263,   264,   268,   286,
     287,   292,   294,   296,   300
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "Token_Booleen", "Token_Entier", 
  "Token_Reel", "Token_Chaine", "Token_Ident", "Token_LAction", 
  "Token_Assign", "Token_Plus", "Token_Moins", "Token_Mult", "Token_Div", 
  "Token_OpenPar", "Token_OpenBrace", "Token_OpenBracket", 
  "Token_ClosePar", "Token_CloseBrace", "Token_CloseBracket", 
  "Token_Ptvirg", "Token_Virgule", "Token_EOF", "Token_Zone", 
  "Token_Choc", "Token_Masse", "Token_Invinsible", "Token_Membres", 
  "Token_Racines", "Token_Action", "Token_Menu", "Token_Affichage", 
  "Token_Gestionnaire", "Token_Evenement", "Token_Genere", "Token_Par", 
  "Token_Traitement", "Token_Membre", "Token_Fils", "Token_Angle", 
  "Token_Max", "Token_Qui", "Token_X", "Token_Y", "Token_Z", "Token_Tous", 
  "Token_Aucun", "Token_Image", "Token_Points", "Token_De", "Token_Vie", 
  "Token_Hostile", "Token_Largeur", "Token_Longueur", "Token_Hauteur", 
  "Token_Physique", "Token_Gameplay", "Token_Graphique", "$accept", 
  "main", "physique", "gameplay", "graphique", "liste_action", "action", 
  "liste_evenement", "evenement", "liste_membre", "membre", 
  "liste_membres_racines", "liste_fils", "fils", "liste_virg", "genere", 
  "code", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    58,    59,    60,    61,    62,    63,    63,    64,    65,
      65,    66,    67,    67,    68,    69,    70,    70,    71,    72,
      72,    73,    73,    73,    74
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     3,    26,    19,     9,     2,     0,    16,     2,
       0,    13,     2,     0,    26,     1,     3,     1,    23,     2,
       0,     1,     1,     1,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     0,     1,     0,     0,     0,     0,
       0,     2,     0,     0,    13,     0,     0,     0,     0,     0,
       0,     0,    12,     0,     0,     0,     0,     0,     0,    20,
       0,     0,     0,     0,    15,    17,     0,     0,     0,     0,
       0,    20,    19,    20,     0,     0,     5,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     7,     0,     0,     0,    10,     0,     0,     0,     0,
       6,     0,     0,     0,     0,     0,     4,     0,     9,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    24,     0,     0,     3,     0,    22,    21,
       0,    23,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    24,     0,     0,     0,     0,     0,     0,
      24,     0,     0,    14,     0,    11,    18,     0,     8
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     2,     3,     7,    11,    75,    80,    81,    88,    17,
      22,    33,    34,    41,    35,   120,   121
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -132
static const short yypact[] =
{
     -49,    -8,    10,   -44,   -10,  -132,    -1,   -40,   -33,   -30,
       4,  -132,    -4,   -28,  -132,    13,   -27,   -26,     9,    16,
      -2,    20,  -132,   -25,    25,    21,    17,    22,    14,  -132,
      -5,    30,    11,    18,    24,    15,    31,    23,    32,    26,
       1,  -132,  -132,  -132,    -7,    43,  -132,    38,    15,   -12,
      39,    29,    44,     3,    47,     2,    34,    46,    36,    48,
      19,    52,     5,    57,    53,    45,    54,    49,    59,    27,
      61,  -132,    50,    58,    51,    55,    33,    63,    56,    64,
    -132,   -18,    66,    60,    62,    68,  -132,    70,  -132,    73,
      35,    65,    67,    71,    72,    76,    78,    79,    69,    37,
      86,    88,    91,    74,    87,    75,    80,    81,    89,    94,
      77,    84,    42,   -41,    85,    82,  -132,    95,  -132,  -132,
      90,  -132,    92,    83,   100,    93,    96,    98,    97,    99,
     102,   107,   101,  -132,   108,   103,   105,   104,   110,   109,
    -132,   114,   116,  -132,   115,  -132,  -132,   118,  -132
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,
    -132,  -132,   106,  -132,   111,  -132,  -131
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      86,    20,   137,    40,   118,   119,     1,     4,    53,   144,
       5,    21,     6,     8,     9,    87,    12,    10,    13,    14,
      15,    16,    18,    19,    23,    24,    25,    26,    27,    28,
      29,    31,    30,    36,    32,    37,    42,    38,    39,    40,
      43,    45,    47,    44,    46,    50,    51,    52,    54,    55,
      57,    56,    58,    59,    60,    61,    62,    63,    65,    66,
      67,    64,    68,    70,    72,    69,    74,    77,    83,    71,
      76,    78,    85,   117,    84,    89,    82,    93,    94,    73,
      90,   104,    91,    92,    79,   100,    98,   101,   102,    95,
      96,   105,    99,   106,   107,   110,   109,    97,   113,   114,
     111,   112,   116,   103,   124,   122,   128,   131,   133,   108,
     125,   134,   135,   138,   140,     0,   115,   132,     0,     0,
       0,     0,   123,   139,   141,     0,   127,   143,     0,   129,
     142,   126,   145,   136,   146,   147,   148,     0,     0,   130,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    49,
       0,     0,    48
};

static const short yycheck[] =
{
      18,    27,   133,    15,    45,    46,    55,    15,    20,   140,
       0,    37,    56,    23,    15,    33,    49,    57,    48,    15,
      24,    49,     9,    50,    15,     9,    28,     7,    53,     4,
       9,     9,    15,    38,    20,     5,    21,    26,    20,    15,
       9,     9,    41,    20,    18,    52,     3,     9,     9,    20,
      47,     7,     5,    51,    20,     9,    20,     9,     6,    54,
       3,    42,     9,     9,     5,    20,     5,     9,     5,    20,
      20,    20,     8,    31,    18,     9,    43,     7,     5,    52,
      20,    44,    20,    15,    29,     9,    15,     9,     9,    54,
      25,     5,    20,     5,     3,    20,     9,    30,     9,     5,
      20,    20,    18,    34,     9,    20,     6,     9,     9,    35,
      20,     9,     5,     5,     9,    -1,    39,    20,    -1,    -1,
      -1,    -1,    40,    20,    20,    -1,    43,    18,    -1,    36,
      20,    39,    18,    32,    18,    20,    18,    -1,    -1,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      -1,    -1,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    55,    59,    60,    15,     0,    56,    61,    23,    15,
      57,    62,    49,    48,    15,    24,    49,    67,     9,    50,
      27,    37,    68,    15,     9,    28,     7,    53,     4,     9,
      15,     9,    20,    69,    70,    72,    38,     5,    26,    20,
      15,    71,    21,     9,    20,     9,    18,    41,    72,    70,
      52,     3,     9,    20,     9,    20,     7,    47,     5,    51,
      20,     9,    20,     9,    42,     6,    54,     3,     9,    20,
       9,    20,     5,    52,     5,    63,    20,     9,    20,    29,
      64,    65,    43,     5,    18,     8,    18,    33,    66,     9,
      20,    20,    15,     7,     5,    54,    25,    30,    15,    20,
       9,     9,     9,    34,    44,     5,     5,     3,    35,     9,
      20,    20,    20,     9,     5,    39,    18,    31,    45,    46,
      73,    74,    20,    40,     9,    20,    39,    43,     6,    36,
      43,     9,    20,     9,     9,     5,    32,    74,     5,    20,
       9,    20,    20,    18,    74,    18,    18,    20,    18
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 137 "parser.y"
    {
  return 0;
}
    break;

  case 3:
#line 150 "parser.y"
    {
  bongars->SetDimension(yyvsp[-16].yyreel, yyvsp[-12].yyreel, yyvsp[-8].yyreel);
}
    break;

  case 4:
#line 162 "parser.y"
    {
}
    break;

  case 5:
#line 170 "parser.y"
    {
  filsdesc *temp;
  while (yyvsp[-2].yyliste != NULL) {
    int j;
    temp = (filsdesc*) yyvsp[-2].yyliste->contenu;

    if ((j = memlookup(temp->qui)) < 0) {
      yyerror(strcat(strcat("Le membre \"", temp->qui), "\" n'a pas ete defini. On continue néanmoins.\n"));
    }
    
    else {
      bongars->AjouterMembre(memtab[j].image, temp->x, temp->y, temp->z, memtab[j].largeur, memtab[j].hauteur, memtab[j].angle_max_y);
      memempiler(bongars, memtab[j].fils);
    }
    yyvsp[-2].yyliste = yyvsp[-2].yyliste->suivant;
  }
}
    break;

  case 6:
#line 190 "parser.y"
    {yyval.yyliste = mp(yyvsp[0].yyaction, yyvsp[-1].yyliste); VERIF_NOT_NULL(yyval.yyliste,-6)}
    break;

  case 7:
#line 191 "parser.y"
    {yyval.yyliste = liste_vide();}
    break;

  case 8:
#line 200 "parser.y"
    {
  yyval.yyaction = new_action();
  VERIF_NOT_NULL(yyval.yyaction,-7)
  yyval.yyaction->menu = yyvsp[-10].yybooleen;
  yyval.yyaction->affichage = yyvsp[-6].yychaine;
  yyval.yyaction->gestionnaire = yyvsp[-2].yycode;
}
    break;

  case 9:
#line 209 "parser.y"
    {yyval.yyliste = mp(yyvsp[0].yyevent, yyvsp[-1].yyliste); VERIF_NOT_NULL(yyval.yyliste,-8)}
    break;

  case 10:
#line 210 "parser.y"
    {yyval.yyliste = liste_vide();}
    break;

  case 11:
#line 218 "parser.y"
    {
  yyval.yyevent = new_event();
  VERIF_NOT_NULL(yyval.yyevent,-9)

  yyval.yyevent->genere = yyvsp[-6].yygenere->type;
  if (yyvsp[-6].yygenere->type == CODE) {
    yyval.yyevent->par = NULL;
  }

  else {
    yyval.yyevent->par = yyvsp[-6].yygenere->code;
  }

  del_sgenere(yyvsp[-6].yygenere);
  yyval.yyevent->traitement = yyvsp[-2].yycode;
}
    break;

  case 12:
#line 236 "parser.y"
    {yyval.yyliste = mp(yyvsp[0].yymembre, yyvsp[-1].yyliste); VERIF_NOT_NULL(yyval.yyliste,-10)}
    break;

  case 13:
#line 237 "parser.y"
    {yyval.yyliste = liste_vide();}
    break;

  case 14:
#line 248 "parser.y"
    {
  if (memnbelts < MAXMEMBRE) {
    memtab[memnbelts].nom = yyvsp[-24].yyident;
    memtab[memnbelts].image = yyvsp[-16].yychaine;
    memtab[memnbelts].fils = yyvsp[-20].yyliste;
    memtab[memnbelts].largeur = yyvsp[-12].yyreel;
    memtab[memnbelts].hauteur = yyvsp[-8].yyreel;
    memtab[memnbelts].angle_max_y = yyvsp[-2].yyreel;
    memnbelts++;
  }
}
    break;

  case 15:
#line 260 "parser.y"
    {yyval.yyliste = yyvsp[0].yyliste;}
    break;

  case 16:
#line 263 "parser.y"
    {yyval.yyliste = mp(yyvsp[-1].yyfils, yyvsp[-2].yyliste); VERIF_NOT_NULL(yyval.yyliste,-12)}
    break;

  case 17:
#line 264 "parser.y"
    {yyval.yyliste = liste_vide();}
    break;

  case 18:
#line 275 "parser.y"
    {
  yyval.yyfils = new filsdesc;
  yyval.yyfils->qui = yyvsp[-19].yyident;
  yyval.yyfils->x = yyvsp[-15].yyreel;
  yyval.yyfils->y = yyvsp[-11].yyreel;
  yyval.yyfils->z = yyvsp[-7].yyreel;
  yyval.yyfils->angle_y = yyvsp[-2].yyreel;
}
    break;

  case 21:
#line 293 "parser.y"
    {yyval.yygenere = new_sgenere(); VERIF_NOT_NULL(yyval.yygenere,-14); yyval.yygenere->type = AUCUN; yyval.yygenere->code = NULL;}
    break;

  case 22:
#line 295 "parser.y"
    {yyval.yygenere = new_sgenere(); VERIF_NOT_NULL(yyval.yygenere,-15); yyval.yygenere->type = TOUS; yyval.yygenere->code = NULL;}
    break;

  case 23:
#line 297 "parser.y"
    {yyval.yygenere = new_sgenere(); VERIF_NOT_NULL(yyval.yygenere,-16); yyval.yygenere->type = CODE; yyval.yygenere->code = yyvsp[0].yycode;}
    break;

  case 24:
#line 300 "parser.y"
    {yyval.yycode = NULL;}
    break;


    }

/* Line 999 of yacc.c.  */
#line 1427 "parser.cpp"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 302 "parser.y"


/*extern void yyerror(char *msg);*/
#include <stdio.h>
const static void yyerror(char s[]) {
  int a, b, c;
  a = get_nb_chars();
  b = get_nb_chars_tot();
  c = get_yyleng();
  (void) fprintf(stderr, "Erreur d'analyse syntaxique sur le lexème \"%s\" à la ligne %d (caractères %d (%d) à %d (%d)) [%s]\n", get_yytext(), get_nb_lignes() + 1, a - c, b - c, a - 1, b - 1, s);
}


