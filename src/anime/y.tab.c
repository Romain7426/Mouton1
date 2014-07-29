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
     Token_OpenPar = 264,
     Token_OpenBrace = 265,
     Token_OpenBracket = 266,
     Token_ClosePar = 267,
     Token_CloseBrace = 268,
     Token_CloseBracket = 269,
     Token_Ptvirg = 270,
     Token_Virgule = 271,
     Token_EOF = 272,
     Token_Zone = 273,
     Token_Choc = 274,
     Token_Masse = 275,
     Token_Invinsible = 276,
     Token_Membres = 277,
     Token_Racines = 278,
     Token_Action = 279,
     Token_Menu = 280,
     Token_Affichage = 281,
     Token_Gestionnaire = 282,
     Token_Evenement = 283,
     Token_Genere = 284,
     Token_Par = 285,
     Token_Traitement = 286,
     Token_Membre = 287,
     Token_Fils = 288,
     Token_Angle = 289,
     Token_Max = 290,
     Token_Qui = 291,
     Token_X = 292,
     Token_Y = 293,
     Token_Z = 294,
     Token_Tous = 295,
     Token_Aucun = 296,
     Token_Image = 297,
     Token_Points = 298,
     Token_De = 299,
     Token_Vie = 300,
     Token_Hostile = 301,
     Token_Largeur = 302,
     Token_Longueur = 303,
     Token_Hauteur = 304,
     Token_Physique = 305,
     Token_Gameplay = 306,
     Token_Graphique = 307,
     Token_Begin = 308,
     Token_End = 309,
     Token_If = 310,
     Token_Then = 311,
     Token_Else = 312,
     Token_While = 313,
     Token_Do = 314,
     Token_Repeat = 315,
     Token_Until = 316,
     Token_For = 317,
     Token_To = 318,
     Token_Assign = 319,
     Token_Write = 320,
     Token_Writeln = 321,
     Token_Read = 322,
     Token_Readln = 323,
     Token_DeuxPoints = 324,
     Token_Plus = 325,
     Token_Minus = 326,
     Token_Mult = 327,
     Token_Div = 328,
     Token_Mod = 329,
     Token_Ou = 330,
     Token_Et = 331,
     Token_Equal = 332,
     Token_Diff = 333,
     Token_Inf = 334,
     Token_Sup = 335,
     Token_InfEq = 336,
     Token_SupEq = 337,
     Token_Not = 338,
     Token_Pascal = 339,
     Token_Function = 340,
     Token_Procedure = 341,
     Token_Var = 342,
     Token_Integer = 343,
     Token_Real = 344,
     Token_Boolean = 345
   };
#endif
#define Token_Booleen 258
#define Token_Entier 259
#define Token_Reel 260
#define Token_Chaine 261
#define Token_Ident 262
#define Token_LAction 263
#define Token_OpenPar 264
#define Token_OpenBrace 265
#define Token_OpenBracket 266
#define Token_ClosePar 267
#define Token_CloseBrace 268
#define Token_CloseBracket 269
#define Token_Ptvirg 270
#define Token_Virgule 271
#define Token_EOF 272
#define Token_Zone 273
#define Token_Choc 274
#define Token_Masse 275
#define Token_Invinsible 276
#define Token_Membres 277
#define Token_Racines 278
#define Token_Action 279
#define Token_Menu 280
#define Token_Affichage 281
#define Token_Gestionnaire 282
#define Token_Evenement 283
#define Token_Genere 284
#define Token_Par 285
#define Token_Traitement 286
#define Token_Membre 287
#define Token_Fils 288
#define Token_Angle 289
#define Token_Max 290
#define Token_Qui 291
#define Token_X 292
#define Token_Y 293
#define Token_Z 294
#define Token_Tous 295
#define Token_Aucun 296
#define Token_Image 297
#define Token_Points 298
#define Token_De 299
#define Token_Vie 300
#define Token_Hostile 301
#define Token_Largeur 302
#define Token_Longueur 303
#define Token_Hauteur 304
#define Token_Physique 305
#define Token_Gameplay 306
#define Token_Graphique 307
#define Token_Begin 308
#define Token_End 309
#define Token_If 310
#define Token_Then 311
#define Token_Else 312
#define Token_While 313
#define Token_Do 314
#define Token_Repeat 315
#define Token_Until 316
#define Token_For 317
#define Token_To 318
#define Token_Assign 319
#define Token_Write 320
#define Token_Writeln 321
#define Token_Read 322
#define Token_Readln 323
#define Token_DeuxPoints 324
#define Token_Plus 325
#define Token_Minus 326
#define Token_Mult 327
#define Token_Div 328
#define Token_Mod 329
#define Token_Ou 330
#define Token_Et 331
#define Token_Equal 332
#define Token_Diff 333
#define Token_Inf 334
#define Token_Sup 335
#define Token_InfEq 336
#define Token_SupEq 337
#define Token_Not 338
#define Token_Pascal 339
#define Token_Function 340
#define Token_Procedure 341
#define Token_Var 342
#define Token_Integer 343
#define Token_Real 344
#define Token_Boolean 345




/* Copy the first part of user declarations.  */
#line 1 "anime.parser.y"
 /* Header */
#include <stdlib.h>
#include "anime.global.hpp"
/*
const extern int get_nb_lignes(void);
const extern int get_nb_chars(void);
const extern int get_nb_chars_tot(void);
const extern int get_yyleng(void);
const extern char * get_yytext(void);
extern int yylex(void);
*/
const static void yyerror(char s[]);


#define VERIF_NOT_NULL(a,b) if (a == NULL) {yyerror("Manque de mémoire."); return b;}


 CBonhomme *bongars;


#define MAXMEMBRE 32
static anime_memdesc memtab[MAXMEMBRE];
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
  anime_filsdesc *temp;
  while (fils != NULL) {
    int j;
    temp = (anime_filsdesc *) fils->contenu;

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


void anime_parser_reset(void) {
  memnbelts = 0;
}






/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 69 "anime.parser.y"
typedef union YYSTYPE {
booleen yybooleen;
int yyentier;
corps yyreel;
char *yychaine;
char *yyident;
anime_action yylaction;

anime_tcode yycode;
anime_sgenere *yygenere;
anime_filsdesc *yyfils;
anime_tmembre *yymembre;
anime_tevent *yyevent;
anime_taction *yyaction;
liste *yyliste;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 335 "y.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 347 "y.tab.c"

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
#define YYLAST   362

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  91
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  58
/* YYNRULES -- Number of rules. */
#define YYNRULES  115
/* YYNRULES -- Number of states. */
#define YYNSTATES  306

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   345

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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     8,    35,    55,    65,    68,    69,    86,
      89,    90,   104,   107,   108,   135,   137,   141,   143,   167,
     170,   171,   173,   175,   177,   179,   181,   182,   184,   185,
     190,   194,   195,   197,   199,   206,   211,   215,   216,   218,
     219,   223,   225,   230,   232,   233,   236,   239,   242,   244,
     248,   251,   253,   257,   260,   262,   264,   266,   268,   270,
     272,   274,   276,   278,   279,   283,   287,   288,   293,   300,
     305,   310,   319,   322,   326,   327,   331,   333,   335,   339,
     342,   345,   348,   351,   353,   354,   358,   360,   364,   368,
     370,   374,   378,   382,   386,   390,   394,   396,   400,   404,
     406,   410,   414,   418,   420,   422,   424,   426,   428,   431,
     434,   437,   441,   443,   445,   447
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
      92,     0,    -1,    93,    94,    95,   109,    -1,    50,    10,
      18,    44,    19,    64,    10,    48,    64,     5,    15,    47,
      64,     5,    15,    49,    64,     5,    15,    13,    15,    20,
      64,     5,    15,    13,    -1,    51,    10,    43,    44,    45,
      64,     4,    15,    21,    64,     3,    15,    46,    64,     3,
      15,    96,    98,    13,    -1,    52,    10,   100,    22,    23,
      64,   102,    15,    13,    -1,    96,    97,    -1,    -1,    24,
       8,    10,    25,    64,     3,    15,    26,    64,     6,    15,
      27,    64,   107,    15,    13,    -1,    98,    99,    -1,    -1,
      28,     7,    10,    29,    30,    64,   106,    15,    31,    64,
     107,    15,    13,    -1,   100,   101,    -1,    -1,    32,     7,
      10,    33,    64,   103,    15,    42,    64,     6,    15,    47,
      64,     5,    15,    49,    64,     5,    15,    34,    35,    38,
      64,     5,    15,    13,    -1,   103,    -1,   103,   104,   105,
      -1,   105,    -1,    10,    36,    64,     7,    15,    37,    64,
       5,    15,    38,    64,     5,    15,    39,    64,     5,    15,
      34,    38,    64,     5,    15,    13,    -1,   105,    16,    -1,
      -1,    41,    -1,    40,    -1,   107,    -1,   108,    -1,     7,
      -1,    -1,   110,    -1,    -1,    84,    10,   111,    13,    -1,
     111,    15,   112,    -1,    -1,   113,    -1,   114,    -1,    85,
       7,   115,    69,   148,   120,    -1,    86,     7,   115,   120,
      -1,     9,   116,    12,    -1,    -1,   117,    -1,    -1,   118,
      15,   117,    -1,   118,    -1,   119,     7,    69,   148,    -1,
      87,    -1,    -1,   121,   127,    -1,    87,   122,    -1,   123,
     122,    -1,   123,    -1,   124,    69,    15,    -1,     7,   125,
      -1,     7,    -1,   125,    16,     7,    -1,    16,     7,    -1,
     137,    -1,   138,    -1,   139,    -1,   133,    -1,   129,    -1,
     130,    -1,   132,    -1,   131,    -1,   127,    -1,    -1,    53,
     128,    54,    -1,   126,    15,   128,    -1,    -1,    55,   142,
      56,   126,    -1,    55,   142,    56,   126,    57,   126,    -1,
      58,   142,    59,   126,    -1,    60,   128,    61,   142,    -1,
      62,     7,    64,   142,    63,   142,    59,   126,    -1,     7,
     134,    -1,     9,   135,    12,    -1,    -1,   136,    16,   135,
      -1,   136,    -1,   142,    -1,   147,    64,   142,    -1,    65,
     134,    -1,    66,   134,    -1,    67,   140,    -1,    68,   140,
      -1,   141,    -1,    -1,   147,    16,   141,    -1,   147,    -1,
     142,    75,   143,    -1,   142,    76,   143,    -1,   143,    -1,
     143,    77,   144,    -1,   143,    78,   144,    -1,   143,    79,
     144,    -1,   143,    80,   144,    -1,   143,    81,   144,    -1,
     143,    82,   144,    -1,   144,    -1,   144,    70,   145,    -1,
     144,    71,   145,    -1,   145,    -1,   145,    72,   146,    -1,
     145,    73,   146,    -1,   145,    74,   146,    -1,   146,    -1,
     147,    -1,     3,    -1,     4,    -1,     5,    -1,    83,   146,
      -1,    70,   146,    -1,    71,   146,    -1,     9,   142,    12,
      -1,     7,    -1,    88,    -1,    89,    -1,    90,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   169,   169,   174,   187,   198,   222,   223,   227,   241,
     242,   246,   268,   269,   273,   292,   295,   296,   300,   318,
     319,   324,   326,   328,   332,   336,   337,   353,   354,   360,
     366,   367,   371,   372,   381,   386,   392,   393,   397,   398,
     402,   403,   408,   412,   413,   420,   424,   428,   429,   433,
     438,   439,   443,   444,   448,   449,   450,   451,   452,   453,
     454,   455,   456,   457,   463,   468,   469,   473,   474,   478,
     482,   487,   492,   496,   497,   501,   502,   506,   512,   516,
     517,   521,   522,   526,   527,   531,   532,   540,   541,   542,
     547,   548,   549,   550,   551,   552,   553,   557,   558,   559,
     563,   564,   565,   566,   570,   571,   572,   573,   574,   575,
     576,   577,   582,   649,   650,   651
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "Token_Booleen", "Token_Entier", 
  "Token_Reel", "Token_Chaine", "Token_Ident", "Token_LAction", 
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
  "Token_Physique", "Token_Gameplay", "Token_Graphique", "Token_Begin", 
  "Token_End", "Token_If", "Token_Then", "Token_Else", "Token_While", 
  "Token_Do", "Token_Repeat", "Token_Until", "Token_For", "Token_To", 
  "Token_Assign", "Token_Write", "Token_Writeln", "Token_Read", 
  "Token_Readln", "Token_DeuxPoints", "Token_Plus", "Token_Minus", 
  "Token_Mult", "Token_Div", "Token_Mod", "Token_Ou", "Token_Et", 
  "Token_Equal", "Token_Diff", "Token_Inf", "Token_Sup", "Token_InfEq", 
  "Token_SupEq", "Token_Not", "Token_Pascal", "Token_Function", 
  "Token_Procedure", "Token_Var", "Token_Integer", "Token_Real", 
  "Token_Boolean", "$accept", "main", "physique", "gameplay", "graphique", 
  "liste_action", "action", "liste_evenement", "evenement", 
  "liste_membre", "membre", "liste_membres_racines", "liste_fils", "fils", 
  "liste_virg", "genere", "code", "pascal_ident", "pascall", "pascal", 
  "liste_definitions", "definition", "fonction", "procedure", "lparams", 
  "llparams", "lllparams", "param", "ppvar", "pdcorps", "pdecl", "ltdecl", 
  "tdecl", "lidents", "llidents", "instruction", "begin", "linstructions", 
  "pif", "pwhile", "prepeat", "pfor", "appel_proc", "largs", "llargs", 
  "arg", "affectation", "affichage", "lecture", "lreadargs", "llreadargs", 
  "pexpr", "pexpr1", "pexpr2", "pexpr3", "pexpr4", "plvar", "pascal_type", 0
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    91,    92,    93,    94,    95,    96,    96,    97,    98,
      98,    99,   100,   100,   101,   102,   103,   103,   104,   105,
     105,   106,   106,   106,   107,   108,   108,   109,   109,   110,
     111,   111,   112,   112,   113,   114,   115,   115,   116,   116,
     117,   117,   118,   119,   119,   120,   121,   122,   122,   123,
     124,   124,   125,   125,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   127,   128,   128,   129,   129,   130,
     131,   132,   133,   134,   134,   135,   135,   136,   137,   138,
     138,   139,   139,   140,   140,   141,   141,   142,   142,   142,
     143,   143,   143,   143,   143,   143,   143,   144,   144,   144,
     145,   145,   145,   145,   146,   146,   146,   146,   146,   146,
     146,   146,   147,   148,   148,   148
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     4,    26,    19,     9,     2,     0,    16,     2,
       0,    13,     2,     0,    26,     1,     3,     1,    23,     2,
       0,     1,     1,     1,     1,     1,     0,     1,     0,     4,
       3,     0,     1,     1,     6,     4,     3,     0,     1,     0,
       3,     1,     4,     1,     0,     2,     2,     2,     1,     3,
       2,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     3,     3,     0,     4,     6,     4,
       4,     8,     2,     3,     0,     3,     1,     1,     3,     2,
       2,     2,     2,     1,     0,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     1,     1,     1,     1,     1,     2,     2,
       2,     3,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     0,     1,     0,     0,     0,     0,
       0,    28,     0,     0,    13,     0,     2,    27,     0,     0,
       0,    31,     0,     0,     0,     0,    12,     0,     0,     0,
       0,     0,    29,     0,     0,     0,    20,     0,     0,     0,
      30,    32,    33,     0,     0,     0,    15,    17,     0,    37,
      37,     0,     0,     0,     0,    20,    19,    20,    39,     0,
       0,     0,     0,     5,     0,    16,     0,    43,     0,    38,
      41,     0,     0,     0,    35,     0,     0,     0,     0,     0,
      36,    44,     0,   113,   114,   115,     0,    51,    46,    48,
       0,    63,    45,     0,     0,     0,     0,    40,     0,    34,
       0,    50,    47,     0,    74,     0,     0,    63,     0,    74,
      74,    84,    84,     0,    62,     0,    58,    59,    61,    60,
      57,    54,    55,    56,     0,     0,     0,     0,     0,    42,
      53,     0,    49,     0,    72,   105,   106,   107,   112,     0,
       0,     0,     0,     0,    89,    96,    99,   103,   104,     0,
       0,     0,    79,    80,    81,    83,    86,    82,    66,    64,
       0,     0,     0,     0,     0,    52,     0,    76,    77,     0,
     109,   110,   108,    63,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    63,     0,     0,
       0,    65,    78,     0,     0,     0,     0,    73,     0,   111,
      67,    87,    88,    90,    91,    92,    93,    94,    95,    97,
      98,   100,   101,   102,    69,    70,     0,    85,     0,     7,
       0,     0,    75,    63,     0,     0,    10,     0,     0,    68,
       0,     0,     0,     6,     0,     0,     0,    63,     0,     0,
       4,     0,     9,     0,     0,    71,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    26,     0,
       0,     3,     0,    25,    22,    21,     0,    23,    24,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      26,     0,     0,     0,     0,     0,     0,    26,     0,     0,
      14,     0,    11,    18,     0,     8
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     2,     3,     7,    11,   226,   233,   234,   242,    20,
      26,    45,    46,    55,    47,   276,   277,   278,    16,    17,
      27,    40,    41,    42,    59,    68,    69,    70,    71,    74,
      75,    88,    89,    90,   101,   113,   114,   115,   116,   117,
     118,   119,   120,   134,   166,   167,   121,   122,   123,   154,
     155,   168,   144,   145,   146,   147,   148,    86
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -272
static const short yypact[] =
{
     -26,    24,    18,   -10,    39,  -272,    52,    13,    43,    38,
      84,    14,    91,    69,  -272,   105,  -272,  -272,    55,    80,
      -7,  -272,   117,    65,   107,   127,  -272,    15,    88,   133,
      78,   134,  -272,   -37,    79,   130,  -272,   114,   141,   142,
    -272,  -272,  -272,   146,   132,   139,   148,   140,    96,   152,
     152,   163,   115,   167,   145,  -272,  -272,  -272,    -1,   113,
      98,   136,   181,  -272,   122,   140,    37,  -272,   175,  -272,
     173,   182,   -35,   183,  -272,   138,   128,   178,   187,   153,
    -272,   109,   129,  -272,  -272,  -272,    98,   184,  -272,   183,
     135,    35,  -272,   192,   155,   188,   143,  -272,   -35,  -272,
     195,   189,  -272,   191,     2,     0,     0,    56,   201,   190,
     190,   202,   202,   196,  -272,   156,  -272,  -272,  -272,  -272,
    -272,  -272,  -272,  -272,   149,   197,   150,   179,   209,  -272,
    -272,   210,  -272,     0,  -272,  -272,  -272,  -272,  -272,     0,
       0,     0,     0,   -39,    89,     8,   -13,  -272,  -272,   -36,
     157,   158,  -272,  -272,  -272,  -272,   203,  -272,    97,  -272,
       0,   171,   218,   159,   211,  -272,   212,   213,    16,    -2,
    -272,  -272,  -272,    73,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    73,     0,     0,
     202,  -272,    16,   161,   215,   222,   185,  -272,     0,  -272,
     174,    89,    89,     8,     8,     8,     8,     8,     8,   -13,
     -13,  -272,  -272,  -272,  -272,    16,   -25,  -272,   223,  -272,
     219,   169,  -272,    73,     0,   220,   214,   198,   232,  -272,
     -32,   226,   233,  -272,     1,   176,   227,    73,   228,   234,
    -272,   238,  -272,   241,   199,  -272,   229,   225,   237,   236,
     193,   194,   200,   224,   216,   247,   249,   253,   230,   204,
     244,   246,   248,   205,   257,   231,   254,   240,     5,   255,
     239,  -272,   207,  -272,  -272,  -272,   258,  -272,  -272,   242,
     243,   266,   251,   245,   221,   260,   235,   250,   272,   252,
     271,   275,   269,   256,   273,   274,   277,   271,   278,   279,
    -272,   280,  -272,  -272,   281,  -272
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -272,  -272,  -272,  -272,  -272,  -272,  -272,  -272,  -272,  -272,
    -272,  -272,   259,  -272,   262,  -272,  -271,  -272,  -272,  -272,
    -272,  -272,  -272,  -272,   261,  -272,   206,  -272,  -272,   217,
    -272,   208,  -272,  -272,  -272,  -165,   263,   -94,  -272,  -272,
    -272,  -272,  -272,   -41,    95,  -272,  -272,  -272,  -272,   186,
     106,  -104,   -69,    -4,   -75,  -109,   -91,   264
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -113
static const short yytable[] =
{
     124,   143,   149,   135,   136,   137,   -44,   138,   200,   139,
     199,   133,   273,   150,   240,    24,   124,   173,     5,   294,
     156,   156,   214,   187,     1,    25,   301,   237,    32,   241,
      33,   170,   171,   172,     4,   169,   174,   175,   224,   174,
     175,     6,   104,   174,   175,   274,   275,    54,    38,    39,
     174,   175,    79,    83,    84,    85,   192,     8,   229,   184,
     185,   186,     9,   104,   191,    10,  -112,   124,   152,   153,
     140,   141,   245,   174,   175,   211,   212,   213,   182,   183,
     104,    13,   124,   142,   215,   216,    67,    12,    91,   -66,
     105,   174,   175,   106,    14,   107,   124,   108,    15,   156,
     109,   110,   111,   112,   104,   201,   202,   209,   210,    91,
      18,   105,   -63,    19,   106,    21,   107,   -66,   108,    22,
     230,   109,   110,   111,   112,    23,    91,    28,   105,    29,
      30,   106,   124,   107,    31,   108,    34,    35,   109,   110,
     111,   112,    36,    43,    37,    44,   124,    48,    49,    50,
      91,    51,   105,    52,    53,   106,    56,   107,    54,   108,
      57,    58,   109,   110,   111,   112,   176,   177,   178,   179,
     180,   181,   203,   204,   205,   206,   207,   208,    61,    62,
      63,    64,    72,    76,    77,    73,    78,    80,    81,    82,
      87,    91,    93,    94,    95,    96,    67,   125,    98,   133,
     100,   126,   130,   127,   103,   131,   132,   128,   151,   138,
     159,   158,   161,   160,   162,   164,   163,   165,   188,   190,
     193,   194,   189,   195,   197,   218,   196,   220,   225,   198,
     219,   223,   221,   228,   227,   231,   235,   236,   232,   238,
     243,   239,   244,   246,   247,   248,   249,   253,   250,   251,
     252,   254,   260,   258,   261,   259,   262,   255,   256,   265,
     263,   266,   269,   267,   257,   270,   272,   271,   264,   268,
     279,   281,   285,   282,   280,   289,   283,   292,   273,   293,
     295,   284,   286,   287,   296,   288,     0,    97,   298,   299,
     300,   302,   303,   222,   305,   304,   217,   102,   157,   290,
       0,     0,     0,    99,     0,     0,     0,     0,     0,     0,
       0,    60,     0,     0,   291,     0,    66,    65,     0,     0,
     297,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    92,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   129
};

static const short yycheck[] =
{
      91,   105,   106,     3,     4,     5,     7,     7,   173,     9,
      12,     9,     7,   107,    13,    22,   107,    56,     0,   290,
     111,   112,   187,    59,    50,    32,   297,    59,    13,    28,
      15,   140,   141,   142,    10,   139,    75,    76,    63,    75,
      76,    51,     7,    75,    76,    40,    41,    10,    85,    86,
      75,    76,    15,    88,    89,    90,   160,    18,   223,    72,
      73,    74,    10,     7,   158,    52,    64,   158,   109,   110,
      70,    71,   237,    75,    76,   184,   185,   186,    70,    71,
       7,    43,   173,    83,   188,   189,    87,    44,    53,    54,
      55,    75,    76,    58,    10,    60,   187,    62,    84,   190,
      65,    66,    67,    68,     7,   174,   175,   182,   183,    53,
      19,    55,    15,    44,    58,    10,    60,    61,    62,    64,
     224,    65,    66,    67,    68,    45,    53,    10,    55,    64,
      23,    58,   223,    60,     7,    62,    48,     4,    65,    66,
      67,    68,    64,    64,    10,    15,   237,    33,     7,     7,
      53,     5,    55,    21,    15,    58,    16,    60,    10,    62,
      64,     9,    65,    66,    67,    68,    77,    78,    79,    80,
      81,    82,   176,   177,   178,   179,   180,   181,    15,    64,
      13,    36,    69,    47,     3,    87,    64,    12,    15,     7,
       7,    53,    64,    15,     7,    42,    87,     5,    69,     9,
      16,    46,     7,    15,    69,    16,    15,    64,     7,     7,
      54,    15,    15,    64,    64,     6,    37,     7,    61,    16,
      49,     3,    64,    64,    12,    64,    15,     5,     5,    16,
      15,    57,    47,    64,    15,    15,    38,     5,    24,    13,
      64,     8,    15,    15,    10,     7,     5,    10,    49,    20,
      25,    15,     5,    29,     5,    39,     3,    64,    64,    15,
      30,    15,     5,    15,    64,    34,    26,    13,    64,    64,
      15,    64,     6,    15,    35,    15,    34,     5,     7,    27,
       5,    38,    31,    38,    15,    64,    -1,    81,    15,    15,
      13,    13,    13,   198,    13,    15,   190,    89,   112,    64,
      -1,    -1,    -1,    86,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    64,    -1,    57,    55,    -1,    -1,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    98
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    50,    92,    93,    10,     0,    51,    94,    18,    10,
      52,    95,    44,    43,    10,    84,   109,   110,    19,    44,
     100,    10,    64,    45,    22,    32,   101,   111,    10,    64,
      23,     7,    13,    15,    48,     4,    64,    10,    85,    86,
     112,   113,   114,    64,    15,   102,   103,   105,    33,     7,
       7,     5,    21,    15,    10,   104,    16,    64,     9,   115,
     115,    15,    64,    13,    36,   105,   103,    87,   116,   117,
     118,   119,    69,    87,   120,   121,    47,     3,    64,    15,
      12,    15,     7,    88,    89,    90,   148,     7,   122,   123,
     124,    53,   127,    64,    15,     7,    42,   117,    69,   120,
      16,   125,   122,    69,     7,    55,    58,    60,    62,    65,
      66,    67,    68,   126,   127,   128,   129,   130,   131,   132,
     133,   137,   138,   139,   147,     5,    46,    15,    64,   148,
       7,    16,    15,     9,   134,     3,     4,     5,     7,     9,
      70,    71,    83,   142,   143,   144,   145,   146,   147,   142,
     128,     7,   134,   134,   140,   141,   147,   140,    15,    54,
      64,    15,    64,    37,     6,     7,   135,   136,   142,   142,
     146,   146,   146,    56,    75,    76,    77,    78,    79,    80,
      81,    82,    70,    71,    72,    73,    74,    59,    61,    64,
      16,   128,   142,    49,     3,    64,    15,    12,    16,    12,
     126,   143,   143,   144,   144,   144,   144,   144,   144,   145,
     145,   146,   146,   146,   126,   142,   142,   141,    64,    15,
       5,    47,   135,    57,    63,     5,    96,    15,    64,   126,
     142,    15,    24,    97,    98,    38,     5,    59,    13,     8,
      13,    28,    99,    64,    15,   126,    15,    10,     7,     5,
      49,    20,    25,    10,    15,    64,    64,    64,    29,    39,
       5,     5,     3,    30,    64,    15,    15,    15,    64,     5,
      34,    13,    26,     7,    40,    41,   106,   107,   108,    15,
      35,    64,    15,    34,    38,     6,    31,    38,    64,    15,
      64,    64,     5,    27,   107,     5,    15,    64,    15,    15,
      13,   107,    13,    13,    15,    13
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
#line 169 "anime.parser.y"
    {
  return 0;
}
    break;

  case 3:
#line 182 "anime.parser.y"
    {
  bongars->SetDimension(yyvsp[-16].yyreel, yyvsp[-12].yyreel, yyvsp[-8].yyreel);
}
    break;

  case 4:
#line 194 "anime.parser.y"
    {
}
    break;

  case 5:
#line 202 "anime.parser.y"
    {
  anime_filsdesc *temp;
  while (yyvsp[-2].yyliste != NULL) {
    int j;
    temp = (anime_filsdesc *) yyvsp[-2].yyliste->contenu;

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
#line 222 "anime.parser.y"
    {yyval.yyliste = mp(yyvsp[0].yyaction, yyvsp[-1].yyliste); VERIF_NOT_NULL(yyval.yyliste,-6)}
    break;

  case 7:
#line 223 "anime.parser.y"
    {yyval.yyliste = liste_vide();}
    break;

  case 8:
#line 232 "anime.parser.y"
    {
  yyval.yyaction = anime_new_action();
  VERIF_NOT_NULL(yyval.yyaction,-7)
  yyval.yyaction->menu = yyvsp[-10].yybooleen;
  yyval.yyaction->affichage = yyvsp[-6].yychaine;
  yyval.yyaction->gestionnaire = yyvsp[-2].yycode;
}
    break;

  case 9:
#line 241 "anime.parser.y"
    {yyval.yyliste = mp(yyvsp[0].yyevent, yyvsp[-1].yyliste); VERIF_NOT_NULL(yyval.yyliste,-8)}
    break;

  case 10:
#line 242 "anime.parser.y"
    {yyval.yyliste = liste_vide();}
    break;

  case 11:
#line 250 "anime.parser.y"
    {
  yyval.yyevent = anime_new_event();
  VERIF_NOT_NULL(yyval.yyevent,-9)

  yyval.yyevent->genere = yyvsp[-6].yygenere->type;
  if (yyvsp[-6].yygenere->type == CODE) {
    yyval.yyevent->par = NULL;
  }

  else {
    yyval.yyevent->par = yyvsp[-6].yygenere->code;
  }

  anime_del_sgenere(yyvsp[-6].yygenere);
  yyval.yyevent->traitement = yyvsp[-2].yycode;
}
    break;

  case 12:
#line 268 "anime.parser.y"
    {yyval.yyliste = mp(yyvsp[0].yymembre, yyvsp[-1].yyliste); VERIF_NOT_NULL(yyval.yyliste,-10)}
    break;

  case 13:
#line 269 "anime.parser.y"
    {yyval.yyliste = liste_vide();}
    break;

  case 14:
#line 280 "anime.parser.y"
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
#line 292 "anime.parser.y"
    {yyval.yyliste = yyvsp[0].yyliste;}
    break;

  case 16:
#line 295 "anime.parser.y"
    {yyval.yyliste = mp(yyvsp[-1].yyfils, yyvsp[-2].yyliste); VERIF_NOT_NULL(yyval.yyliste,-12)}
    break;

  case 17:
#line 296 "anime.parser.y"
    {yyval.yyliste = liste_vide();}
    break;

  case 18:
#line 307 "anime.parser.y"
    {
  yyval.yyfils = new anime_filsdesc;
  yyval.yyfils->qui = yyvsp[-19].yyident;
  yyval.yyfils->x = yyvsp[-15].yyreel;
  yyval.yyfils->y = yyvsp[-11].yyreel;
  yyval.yyfils->z = yyvsp[-7].yyreel;
  yyval.yyfils->angle_y = yyvsp[-2].yyreel;
}
    break;

  case 21:
#line 325 "anime.parser.y"
    {yyval.yygenere = anime_new_sgenere(); VERIF_NOT_NULL(yyval.yygenere,-14); yyval.yygenere->type = AUCUN; yyval.yygenere->code = NULL;}
    break;

  case 22:
#line 327 "anime.parser.y"
    {yyval.yygenere = anime_new_sgenere(); VERIF_NOT_NULL(yyval.yygenere,-15); yyval.yygenere->type = TOUS; yyval.yygenere->code = NULL;}
    break;

  case 23:
#line 329 "anime.parser.y"
    {yyval.yygenere = anime_new_sgenere(); VERIF_NOT_NULL(yyval.yygenere,-16); yyval.yygenere->type = CODE; yyval.yygenere->code = yyvsp[0].yycode;}
    break;

  case 24:
#line 332 "anime.parser.y"
    {yyval.yycode = NULL;}
    break;


    }

/* Line 999 of yacc.c.  */
#line 1679 "y.tab.c"

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


#line 666 "anime.parser.y"


/*extern void yyerror(char *msg);*/
#include <stdio.h>
const static void yyerror(char s[]) {
  int a, b, c;
  a = anime_get_nb_chars();
  b = anime_get_nb_chars_tot();
  c = anime_get_yyleng();
  (void) fprintf(stderr, "Erreur d'analyse syntaxique sur le lexème \"%s\" à la ligne %d (caractères %d (%d) à %d (%d)) [%s]\n", anime_get_yytext(), anime_get_nb_lignes() + 1, a - c, b - c, a - 1, b - 1, s);
}



