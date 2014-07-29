/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse yyanimeparse
#define yylex   yyanimelex
#define yyerror yyanimeerror
#define yylval  yyanimelval
#define yychar  yyanimechar
#define yydebug yyanimedebug
#define yynerrs yyanimenerrs


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
     Token_Fichier = 308,
     Token_Procedure = 309,
     Token_Icone = 310,
     Token_Assign = 311,
     Token_PlusEntier = 312,
     Token_MoinsEntier = 313,
     Token_MultEntier = 314,
     Token_DivEntier = 315,
     Token_ModEntier = 316,
     Token_PlusReel = 317,
     Token_MoinsReel = 318,
     Token_MultReel = 319,
     Token_DivReel = 320
   };
#endif
/* Tokens.  */
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
#define Token_Fichier 308
#define Token_Procedure 309
#define Token_Icone 310
#define Token_Assign 311
#define Token_PlusEntier 312
#define Token_MoinsEntier 313
#define Token_MultEntier 314
#define Token_DivEntier 315
#define Token_ModEntier 316
#define Token_PlusReel 317
#define Token_MoinsReel 318
#define Token_MultReel 319
#define Token_DivReel 320




/* Copy the first part of user declarations.  */
#line 1 "anime.parser.y"
 /* Header */
#include <stdlib.h>
#include <stdio.h>
#include "global.hpp"
#include "anime/anime.global.hpp"
#include "action.hpp"

/*
extern const int get_nb_lignes(void);
extern const int get_nb_chars(void);
extern const int get_nb_chars_tot(void);
extern const int get_yyleng(void);
extern const char * get_yytext(void);
extern int yylex(void);
*/
static void yyerror(const char s[]);
static inline void yyerror3(const char * str1, const char * str2, const char * str3);


#define VERIF_NOT_NULL(a,b) if (a == NULL) {yyerror("Manque de mémoire."); return b;}


 CBonhomme * bongars;


#define MAXMEMBRE 32
static anime_memdesc memtab[MAXMEMBRE];
static int memnbelts = 0;
static const int memlookup(char * nom) {
  for (int i = 0; i < memnbelts; i++) {
    if (strcmp(nom, memtab[i].nom) == 0) {
      return i;
    }
  }
  return -1;
}


static const void memempiler(CPantin * pere, liste * fils) {
  anime_filsdesc * temp;

  while (fils != NULL) {
    int j;
    temp = (anime_filsdesc *) fils -> contenu;

    if ((j = memlookup(temp -> qui)) < 0) {
      yyerror3("Le membre \"", temp -> qui, " n'a pas ete defini. On continue néanmoins.\n");
    }
    
    else {
      CPantin * p = new CPantin;
      p -> AjouterMembre(memtab[j].image, temp -> x, temp -> y, temp -> z, memtab[j].largeur, memtab[j].hauteur, memtab[j].angle_max_y);
      pere -> SetPantinFilsAuDernierMembre(p);
      memempiler(p, memtab[j].fils);
    }
    fils = fils -> suivant;
  }
}


void anime_parser_reset(void) {
  memnbelts = 0;
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

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 76 "anime.parser.y"
{
booleen yybooleen;
int yyentier;
corps yyreel;
char * yychaine;
char * yyident;
char * yynom;
anime_action yylaction;

anime_tcode * yycode;
anime_sgenere * yygenere;
anime_filsdesc * yyfils;
anime_tmembre * yymembre;
anime_tevent * yyevent;
anime_taction * yyaction;
liste * yyliste;
}
/* Line 193 of yacc.c.  */
#line 321 "anime.parser.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 334 "anime.parser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
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
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   217

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  47
/* YYNRULES -- Number of states.  */
#define YYNSTATES  199

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   320

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      65
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    34,    54,    64,    67,    68,    85,
      88,    89,   103,   106,   107,   134,   136,   140,   142,   166,
     169,   170,   172,   174,   176,   187,   191,   195,   197,   201,
     205,   209,   211,   213,   216,   219,   223,   227,   231,   233,
     237,   241,   243,   245,   248,   251,   255,   257
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      67,     0,    -1,    68,    69,    70,    -1,    50,    10,    18,
      44,    19,    56,    10,    48,    56,    86,    15,    47,    56,
      86,    15,    49,    56,    86,    15,    13,    15,    20,    56,
      86,    15,    13,    -1,    51,    10,    43,    44,    45,    56,
      83,    15,    21,    56,     3,    15,    46,    56,     3,    15,
      71,    73,    13,    -1,    52,    10,    75,    22,    23,    56,
      77,    15,    13,    -1,    71,    72,    -1,    -1,    24,    89,
      10,    26,    56,     6,    15,    55,    56,     6,    15,    27,
      56,    82,    15,    13,    -1,    73,    74,    -1,    -1,    28,
      89,    10,    29,    30,    56,    81,    15,    31,    56,    82,
      15,    13,    -1,    75,    76,    -1,    -1,    32,     7,    10,
      33,    56,    78,    15,    42,    56,     6,    15,    47,    56,
      86,    15,    49,    56,    86,    15,    34,    35,    38,    56,
      86,    15,    13,    -1,    78,    -1,    78,    79,    80,    -1,
      80,    -1,    10,    36,    56,     7,    15,    37,    56,    86,
      15,    38,    56,    86,    15,    39,    56,    86,    15,    34,
      38,    56,    86,    15,    13,    -1,    80,    16,    -1,    -1,
      41,    -1,    40,    -1,    82,    -1,    10,    53,    56,     6,
      15,    54,    56,     6,    15,    13,    -1,    83,    57,    84,
      -1,    83,    58,    84,    -1,    84,    -1,    84,    59,    85,
      -1,    84,    60,    85,    -1,    84,    61,    85,    -1,    85,
      -1,     4,    -1,    57,    85,    -1,    58,    85,    -1,     9,
      83,    12,    -1,    86,    62,    87,    -1,    86,    63,    87,
      -1,    87,    -1,    87,    64,    88,    -1,    87,    65,    88,
      -1,    88,    -1,     5,    -1,    62,    88,    -1,    63,    88,
      -1,     9,    86,    12,    -1,     6,    -1,     7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   191,   191,   196,   209,   221,   245,   246,   250,   261,
     262,   266,   288,   289,   293,   312,   315,   316,   320,   338,
     339,   344,   346,   348,   353,   363,   364,   365,   369,   370,
     371,   372,   376,   377,   378,   379,   384,   385,   386,   390,
     391,   392,   396,   397,   398,   399,   405,   406
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "Token_Booleen", "Token_Entier",
  "Token_Reel", "Token_Chaine", "Token_Ident", "Token_LAction",
  "Token_OpenPar", "Token_OpenBrace", "Token_OpenBracket",
  "Token_ClosePar", "Token_CloseBrace", "Token_CloseBracket",
  "Token_Ptvirg", "Token_Virgule", "Token_EOF", "Token_Zone", "Token_Choc",
  "Token_Masse", "Token_Invinsible", "Token_Membres", "Token_Racines",
  "Token_Action", "Token_Menu", "Token_Affichage", "Token_Gestionnaire",
  "Token_Evenement", "Token_Genere", "Token_Par", "Token_Traitement",
  "Token_Membre", "Token_Fils", "Token_Angle", "Token_Max", "Token_Qui",
  "Token_X", "Token_Y", "Token_Z", "Token_Tous", "Token_Aucun",
  "Token_Image", "Token_Points", "Token_De", "Token_Vie", "Token_Hostile",
  "Token_Largeur", "Token_Longueur", "Token_Hauteur", "Token_Physique",
  "Token_Gameplay", "Token_Graphique", "Token_Fichier", "Token_Procedure",
  "Token_Icone", "Token_Assign", "Token_PlusEntier", "Token_MoinsEntier",
  "Token_MultEntier", "Token_DivEntier", "Token_ModEntier",
  "Token_PlusReel", "Token_MoinsReel", "Token_MultReel", "Token_DivReel",
  "$accept", "main", "physique", "gameplay", "graphique", "liste_action",
  "action", "liste_evenement", "evenement", "liste_membre", "membre",
  "liste_membres_racines", "liste_fils", "fils", "liste_virg", "genere",
  "code", "expr_entier", "expr_entier1", "expr_entier2", "expr_reel",
  "expr_reel1", "expr_reel2", "nom", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    66,    67,    68,    69,    70,    71,    71,    72,    73,
      73,    74,    75,    75,    76,    77,    78,    78,    79,    80,
      80,    81,    81,    81,    82,    83,    83,    83,    84,    84,
      84,    84,    85,    85,    85,    85,    86,    86,    86,    87,
      87,    87,    88,    88,    88,    88,    89,    89
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,    26,    19,     9,     2,     0,    16,     2,
       0,    13,     2,     0,    26,     1,     3,     1,    23,     2,
       0,     1,     1,     1,    10,     3,     3,     1,     3,     3,
       3,     1,     1,     2,     2,     3,     3,     3,     1,     3,
       3,     1,     1,     2,     2,     3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     1,     0,     0,     0,     0,
       0,     2,     0,     0,    13,     0,     0,     0,     0,     0,
       0,     0,    12,     0,     0,     0,     0,     0,    32,     0,
       0,     0,     0,    27,    31,    20,     0,     0,     0,    33,
      34,     0,     0,     0,     0,     0,     0,     0,    15,    17,
       0,    42,     0,     0,     0,     0,    38,    41,    35,     0,
      25,    26,    28,    29,    30,     0,     0,    20,    19,    20,
       0,    43,    44,     0,     0,     0,     0,     0,     0,     5,
       0,    16,     0,    45,     0,    36,    37,    39,    40,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     7,
       0,     0,     0,    10,     0,     0,     0,     0,     6,     0,
       0,     0,     0,    46,    47,     0,     4,     0,     9,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     0,     0,    22,
      21,     0,    23,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    14,
       0,     0,    11,    18,     0,     0,     8,     0,    24
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     7,    11,   113,   118,   119,   128,    17,
      22,    47,    48,    67,    49,   161,   162,    32,    33,    34,
      55,    56,    57,   125
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -168
static const yytype_int16 yypact[] =
{
     -44,    -1,    11,   -38,    14,  -168,    26,   -32,   -22,   -19,
      32,  -168,    36,    13,  -168,    40,    17,    -6,    66,    48,
      69,    98,  -168,    59,     3,    50,    99,    52,  -168,     3,
       3,     3,   -11,    34,  -168,  -168,    77,    -4,    29,  -168,
    -168,    90,     3,     3,     3,     3,     3,    97,   105,   100,
      61,  -168,    -4,    -4,    -4,   -12,   -20,  -168,  -168,    62,
      34,    34,  -168,  -168,  -168,   106,    84,  -168,  -168,  -168,
     -10,  -168,  -168,    74,    -4,    -4,    -4,    -4,   120,  -168,
      68,   100,    33,  -168,    71,   -20,   -20,  -168,  -168,   110,
     121,    87,    -4,    85,   115,    76,     2,    78,    96,   129,
      88,   133,    82,   124,    86,   125,    -4,    94,    -4,  -168,
       4,    89,     6,   119,   108,    -4,   131,    92,  -168,    21,
      91,     8,   134,  -168,  -168,   138,  -168,    92,  -168,    -4,
     101,   132,   127,   141,    10,   102,   103,   104,   126,   117,
      -4,    -4,   148,   135,   107,    12,    16,   142,   111,    -4,
     128,   151,   113,    -2,    18,   136,  -168,   114,   116,  -168,
    -168,   146,  -168,   139,   137,   160,   118,   145,   140,   123,
     157,   171,   130,   143,    -4,   153,   166,   172,    -4,    20,
     144,   147,   168,    22,   174,   172,   149,   175,   176,  -168,
     169,   179,  -168,  -168,   177,   178,  -168,   181,  -168
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,   122,  -168,   150,  -168,  -167,   163,    58,   -16,
     -52,    28,    37,    70
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      70,    51,    83,    73,    41,    52,     1,    28,   158,     4,
     182,     5,    29,     6,    39,    40,    20,   100,   190,   114,
      10,   116,    12,   130,    13,   139,    21,   150,    62,    63,
      64,   151,     8,   163,   126,   184,     9,   188,   159,   160,
      96,    58,    14,    66,    76,    77,    42,    43,    91,   127,
      74,    75,    74,    75,   110,    15,   112,    16,    53,    54,
      30,    31,    19,   121,    74,    75,    74,    75,    74,    75,
      74,    75,    74,    75,    74,    75,    23,   134,    74,    75,
      74,    75,    74,    75,    74,    75,    42,    43,   145,   146,
      71,    72,    25,    44,    45,    46,    18,   154,   123,   124,
      60,    61,    85,    86,    24,    26,    35,    27,    37,    36,
      50,    59,    65,    87,    88,    66,    68,    69,    78,    79,
      80,    84,   179,    89,    90,    93,   183,    92,    94,    95,
      98,    97,    99,   102,   101,   103,   105,   104,   106,   107,
     109,   111,   108,   117,   122,   115,   120,   129,   132,   131,
     135,   138,   136,   137,   147,   143,   144,   152,   140,   141,
     142,   167,   155,   149,   156,   148,   170,   153,   157,   166,
     165,   164,   175,   168,   171,   169,   172,   176,   173,   174,
     180,   181,   158,   187,   194,   195,   177,   189,   192,   193,
     196,    82,    38,   197,   198,     0,     0,   133,     0,   178,
     185,   186,     0,     0,     0,   191,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    81
};

static const yytype_int16 yycheck[] =
{
      52,     5,    12,    15,    15,     9,    50,     4,    10,    10,
     177,     0,     9,    51,    30,    31,    22,    15,   185,    15,
      52,    15,    44,    15,    43,    15,    32,    15,    44,    45,
      46,    15,    18,    15,    13,    15,    10,    15,    40,    41,
      92,    12,    10,    10,    64,    65,    57,    58,    15,    28,
      62,    63,    62,    63,   106,    19,   108,    44,    62,    63,
      57,    58,    45,   115,    62,    63,    62,    63,    62,    63,
      62,    63,    62,    63,    62,    63,    10,   129,    62,    63,
      62,    63,    62,    63,    62,    63,    57,    58,   140,   141,
      53,    54,    23,    59,    60,    61,    56,   149,     6,     7,
      42,    43,    74,    75,    56,     7,    56,    48,    56,    10,
      33,    21,    15,    76,    77,    10,    16,    56,    56,    13,
      36,    47,   174,     3,    56,    15,   178,    56,     7,    42,
      15,    46,    56,    37,    56,     6,     3,    49,    56,    15,
      15,    47,    56,    24,    13,    56,    38,    56,    10,    15,
      49,    10,    20,    26,     6,    29,    39,    15,    56,    56,
      56,    15,    34,    56,    13,    30,     6,    56,    55,    53,
      56,    35,    15,    34,    56,    38,    31,     6,    38,    56,
      27,    15,    10,    15,    15,     6,    56,    13,    13,    13,
      13,    69,    29,    15,    13,    -1,    -1,   127,    -1,    56,
      56,    54,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    50,    67,    68,    10,     0,    51,    69,    18,    10,
      52,    70,    44,    43,    10,    19,    44,    75,    56,    45,
      22,    32,    76,    10,    56,    23,     7,    48,     4,     9,
      57,    58,    83,    84,    85,    56,    10,    56,    83,    85,
      85,    15,    57,    58,    59,    60,    61,    77,    78,    80,
      33,     5,     9,    62,    63,    86,    87,    88,    12,    21,
      84,    84,    85,    85,    85,    15,    10,    79,    16,    56,
      86,    88,    88,    15,    62,    63,    64,    65,    56,    13,
      36,    80,    78,    12,    47,    87,    87,    88,    88,     3,
      56,    15,    56,    15,     7,    42,    86,    46,    15,    56,
      15,    56,    37,     6,    49,     3,    56,    15,    56,    15,
      86,    47,    86,    71,    15,    56,    15,    24,    72,    73,
      38,    86,    13,     6,     7,    89,    13,    28,    74,    56,
      15,    15,    10,    89,    86,    49,    20,    26,    10,    15,
      56,    56,    56,    29,    39,    86,    86,     6,    30,    56,
      15,    15,    15,    56,    86,    34,    13,    55,    10,    40,
      41,    81,    82,    15,    35,    56,    53,    15,    34,    38,
       6,    56,    31,    38,    56,    15,     6,    56,    56,    86,
      27,    15,    82,    86,    15,    56,    54,    15,    15,    13,
      82,    56,    13,    13,    15,     6,    13,    15,    13
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


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
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

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
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
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

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
#line 191 "anime.parser.y"
    {
  return 0;
}
    break;

  case 3:
#line 204 "anime.parser.y"
    {
  bongars->SetDimension((yyvsp[(10) - (26)].yyreel), (yyvsp[(14) - (26)].yyreel), (yyvsp[(18) - (26)].yyreel));
}
    break;

  case 4:
#line 216 "anime.parser.y"
    {
  bongars->Hostile = (yyvsp[(15) - (19)].yybooleen);
}
    break;

  case 5:
#line 225 "anime.parser.y"
    {
  anime_filsdesc * temp;
  while ((yyvsp[(7) - (9)].yyliste) != NULL) {
    int j;
    temp = (anime_filsdesc *) (yyvsp[(7) - (9)].yyliste)->contenu;

    if ((j = memlookup(temp -> qui)) < 0) {
      yyerror3("Le membre \"", temp -> qui, "\" n'a pas ete defini. On continue néanmoins.\n");
    }
    
    else {
      bongars -> AjouterMembre(memtab[j].image, temp -> x, temp -> y, temp -> z, memtab[j].largeur, memtab[j].hauteur, memtab[j].angle_max_y);
      memempiler(bongars, memtab[j].fils);
    }
    (yyvsp[(7) - (9)].yyliste) = (yyvsp[(7) - (9)].yyliste) -> suivant;
  }
}
    break;

  case 8:
#line 255 "anime.parser.y"
    {
  bongars->AjouterAction((yyvsp[(6) - (16)].yychaine), (yyvsp[(10) - (16)].yychaine), (yyvsp[(14) - (16)].yycode)->fichier, (yyvsp[(14) - (16)].yycode)->proc);
  anime_del_code(&((yyvsp[(14) - (16)].yycode)));
}
    break;

  case 9:
#line 261 "anime.parser.y"
    {(yyval.yyliste) = mp((yyvsp[(2) - (2)].yyevent), (yyvsp[(1) - (2)].yyliste)); VERIF_NOT_NULL((yyval.yyliste),-8)}
    break;

  case 10:
#line 262 "anime.parser.y"
    {(yyval.yyliste) = liste_vide();}
    break;

  case 11:
#line 270 "anime.parser.y"
    {
  (yyval.yyevent) = anime_new_event();
  VERIF_NOT_NULL((yyval.yyevent),-9)

  (yyval.yyevent)->genere = (yyvsp[(7) - (13)].yygenere)->type;
  if ((yyvsp[(7) - (13)].yygenere)->type == CODE) {
    (yyval.yyevent)->par = (anime_tcode *)NULL;
  }

  else {
    (yyval.yyevent)->par = (yyvsp[(7) - (13)].yygenere)->code;
  }

  anime_del_sgenere((yyvsp[(7) - (13)].yygenere));
  (yyval.yyevent)->traitement = (yyvsp[(11) - (13)].yycode);
}
    break;

  case 12:
#line 288 "anime.parser.y"
    {(yyval.yyliste) = mp((yyvsp[(2) - (2)].yymembre), (yyvsp[(1) - (2)].yyliste)); VERIF_NOT_NULL((yyval.yyliste),-10)}
    break;

  case 13:
#line 289 "anime.parser.y"
    {(yyval.yyliste) = liste_vide();}
    break;

  case 14:
#line 300 "anime.parser.y"
    {
  if (memnbelts < MAXMEMBRE) {
    memtab[memnbelts].nom = (yyvsp[(2) - (26)].yyident);
    memtab[memnbelts].image = (yyvsp[(10) - (26)].yychaine);
    memtab[memnbelts].fils = (yyvsp[(6) - (26)].yyliste);
    memtab[memnbelts].largeur = (yyvsp[(14) - (26)].yyreel);
    memtab[memnbelts].hauteur = (yyvsp[(18) - (26)].yyreel);
    memtab[memnbelts].angle_max_y = (yyvsp[(24) - (26)].yyreel);
    memnbelts++;
  }
}
    break;

  case 15:
#line 312 "anime.parser.y"
    {(yyval.yyliste) = (yyvsp[(1) - (1)].yyliste);}
    break;

  case 16:
#line 315 "anime.parser.y"
    {(yyval.yyliste) = mp((yyvsp[(2) - (3)].yyfils), (yyvsp[(1) - (3)].yyliste)); VERIF_NOT_NULL((yyval.yyliste),-12)}
    break;

  case 17:
#line 316 "anime.parser.y"
    {(yyval.yyliste) = liste_vide();}
    break;

  case 18:
#line 327 "anime.parser.y"
    {
  (yyval.yyfils) = new anime_filsdesc;
  (yyval.yyfils)->qui = (yyvsp[(4) - (23)].yyident);
  (yyval.yyfils)->x = (yyvsp[(8) - (23)].yyreel);
  (yyval.yyfils)->y = (yyvsp[(12) - (23)].yyreel);
  (yyval.yyfils)->z = (yyvsp[(16) - (23)].yyreel);
  (yyval.yyfils)->angle_y = (yyvsp[(21) - (23)].yyreel);
}
    break;

  case 21:
#line 345 "anime.parser.y"
    {(yyval.yygenere) = anime_new_sgenere(); VERIF_NOT_NULL((yyval.yygenere),-14); (yyval.yygenere)->type = AUCUN; (yyval.yygenere)->code = NULL;}
    break;

  case 22:
#line 347 "anime.parser.y"
    {(yyval.yygenere) = anime_new_sgenere(); VERIF_NOT_NULL((yyval.yygenere),-15); (yyval.yygenere)->type = TOUS; (yyval.yygenere)->code = NULL;}
    break;

  case 23:
#line 349 "anime.parser.y"
    {(yyval.yygenere) = anime_new_sgenere(); VERIF_NOT_NULL((yyval.yygenere),-16); (yyval.yygenere)->type = CODE; (yyval.yygenere)->code = (yyvsp[(1) - (1)].yycode);}
    break;

  case 24:
#line 357 "anime.parser.y"
    { (yyval.yycode) = anime_new_code(); (yyval.yycode)->fichier = (yyvsp[(4) - (10)].yychaine); (yyval.yycode)->proc = (yyvsp[(8) - (10)].yychaine); }
    break;

  case 25:
#line 363 "anime.parser.y"
    { (yyval.yyentier) = (yyvsp[(1) - (3)].yyentier) + (yyvsp[(3) - (3)].yyentier); }
    break;

  case 26:
#line 364 "anime.parser.y"
    { (yyval.yyentier) = (yyvsp[(1) - (3)].yyentier) - (yyvsp[(3) - (3)].yyentier); }
    break;

  case 27:
#line 365 "anime.parser.y"
    { (yyval.yyentier)= (yyvsp[(1) - (1)].yyentier); }
    break;

  case 28:
#line 369 "anime.parser.y"
    { (yyval.yyentier) = (yyvsp[(1) - (3)].yyentier) * (yyvsp[(3) - (3)].yyentier); }
    break;

  case 29:
#line 370 "anime.parser.y"
    { (yyval.yyentier) = (yyvsp[(1) - (3)].yyentier) / (yyvsp[(3) - (3)].yyentier); }
    break;

  case 30:
#line 371 "anime.parser.y"
    { (yyval.yyentier) = (yyvsp[(1) - (3)].yyentier) % (yyvsp[(3) - (3)].yyentier); }
    break;

  case 31:
#line 372 "anime.parser.y"
    { (yyval.yyentier) = (yyvsp[(1) - (1)].yyentier); }
    break;

  case 32:
#line 376 "anime.parser.y"
    { (yyval.yyentier) = (yyvsp[(1) - (1)].yyentier); }
    break;

  case 33:
#line 377 "anime.parser.y"
    { (yyval.yyentier) = (yyvsp[(2) - (2)].yyentier); }
    break;

  case 34:
#line 378 "anime.parser.y"
    { (yyval.yyentier) = - (yyvsp[(2) - (2)].yyentier); }
    break;

  case 35:
#line 379 "anime.parser.y"
    { (yyval.yyentier) = (yyvsp[(2) - (3)].yyentier); }
    break;

  case 36:
#line 384 "anime.parser.y"
    { (yyval.yyreel) = (yyvsp[(1) - (3)].yyreel) + (yyvsp[(3) - (3)].yyreel); }
    break;

  case 37:
#line 385 "anime.parser.y"
    { (yyval.yyreel) = (yyvsp[(1) - (3)].yyreel) - (yyvsp[(3) - (3)].yyreel); }
    break;

  case 38:
#line 386 "anime.parser.y"
    { (yyval.yyreel)= (yyvsp[(1) - (1)].yyreel); }
    break;

  case 39:
#line 390 "anime.parser.y"
    { (yyval.yyreel) = (yyvsp[(1) - (3)].yyreel) * (yyvsp[(3) - (3)].yyreel); }
    break;

  case 40:
#line 391 "anime.parser.y"
    { (yyval.yyreel) = (yyvsp[(1) - (3)].yyreel) / (yyvsp[(3) - (3)].yyreel); }
    break;

  case 41:
#line 392 "anime.parser.y"
    { (yyval.yyreel) = (yyvsp[(1) - (1)].yyreel); }
    break;

  case 42:
#line 396 "anime.parser.y"
    { (yyval.yyreel) = (yyvsp[(1) - (1)].yyreel); }
    break;

  case 43:
#line 397 "anime.parser.y"
    { (yyval.yyreel) = (yyvsp[(2) - (2)].yyreel); }
    break;

  case 44:
#line 398 "anime.parser.y"
    { (yyval.yyreel) = - (yyvsp[(2) - (2)].yyreel); }
    break;

  case 45:
#line 399 "anime.parser.y"
    { (yyval.yyreel) = (yyvsp[(2) - (3)].yyreel); }
    break;

  case 46:
#line 405 "anime.parser.y"
    { (yyval.yynom) = (yyvsp[(1) - (1)].yychaine); }
    break;

  case 47:
#line 406 "anime.parser.y"
    { (yyval.yynom) = (yyvsp[(1) - (1)].yyident); }
    break;


/* Line 1267 of yacc.c.  */
#line 1956 "anime.parser.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
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
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 411 "anime.parser.y"


void yyerror(const char s[]) {
  int a, b, c;
  a = anime_get_nb_chars();
  b = anime_get_nb_chars_tot();
  c = anime_get_yyleng();
  (void) fprintf(stderr, "Erreur d'analyse syntaxique sur le lexème \"%s\" à la ligne %d (caractères %d (%d) à %d (%d)) [%s]\n", anime_get_yytext(), anime_get_nb_lignes() + 1, a - c, b - c, a - 1, b - 1, s);
}


void yyerror3(const char * str1, const char * str2, const char * str3) {
  size_t len, len1, len2, len3;
  char * str;
  
  len1 = strlen(str1);
  len2 = strlen(str2);
  len3 = strlen(str3);
  
  len = len1 + len2 + len3;
  
  str = (char *) malloc(len + 1);
  
  yyerror(strcat(strcat(strcpy(str, str1), str2), str3));
  
  free(str);
}


