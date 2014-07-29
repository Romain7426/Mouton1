/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

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

/* Bison version.  */
#define YYBISON_VERSION "2.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse yypascalparse
#define yylex   yypascallex
#define yyerror yypascalerror
#define yylval  yypascallval
#define yychar  yypascalchar
#define yydebug yypascaldebug
#define yynerrs yypascalnerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOKEN_ENTIER = 258,
     TOKEN_REEL = 259,
     TOKEN_CHAINE = 260,
     TOKEN_IDENT = 261,
     TOKEN_NIL = 262,
     TOKEN_EOF = 263,
     TOKEN_TRUE = 264,
     TOKEN_FALSE = 265,
     TOKEN_NOT = 266,
     TOKEN_AND = 267,
     TOKEN_OR = 268,
     TOKEN_EQUAL = 269,
     TOKEN_DIFF = 270,
     TOKEN_INF = 271,
     TOKEN_SUP = 272,
     TOKEN_INFEQ = 273,
     TOKEN_SUPEQ = 274,
     TOKEN_IPLUS = 275,
     TOKEN_IMOINS = 276,
     TOKEN_IMULT = 277,
     TOKEN_IDIV = 278,
     TOKEN_IMOD = 279,
     TOKEN_RPLUS = 280,
     TOKEN_RMOINS = 281,
     TOKEN_RMULT = 282,
     TOKEN_RDIV = 283,
     TOKEN_PTR = 284,
     TOKEN_TYPE = 285,
     TOKEN_BOOLEAN = 286,
     TOKEN_INTEGER = 287,
     TOKEN_SUBRANGE = 288,
     TOKEN_REAL = 289,
     TOKEN_STRING = 290,
     TOKEN_ARRAY = 291,
     TOKEN_OF = 292,
     TOKEN_RECORD = 293,
     TOKEN_PTVIRG = 294,
     TOKEN_AFFECTATION = 295,
     TOKEN_IF = 296,
     TOKEN_THEN = 297,
     TOKEN_ELSE = 298,
     TOKEN_WHILE = 299,
     TOKEN_DO = 300,
     TOKEN_FOR = 301,
     TOKEN_TO = 302,
     TOKEN_REPEAT = 303,
     TOKEN_UNTIL = 304,
     TOKEN_BEGIN = 305,
     TOKEN_END = 306,
     TOKEN_WRITE = 307,
     TOKEN_WRITELN = 308,
     TOKEN_READ = 309,
     TOKEN_READLN = 310,
     TOKEN_NEW = 311,
     TOKEN_PROCEDURE = 312,
     TOKEN_FUNCTION = 313,
     TOKEN_CONST = 314,
     TOKEN_VAR = 315,
     TOKEN_OPENPAR = 316,
     TOKEN_CLOSEPAR = 317,
     TOKEN_OPENBRACKET = 318,
     TOKEN_CLOSEBRACKET = 319,
     TOKEN_DEUXPOINTS = 320,
     TOKEN_BLANC = 321,
     TOKEN_COMMENT = 322,
     TOKEN_VIRGULE = 323,
     TOKEN_POINT = 324,
     TOKEN_MUSIQUE = 325,
     TOKEN_MENU = 326,
     TOKEN_ITEM = 327,
     TOKEN_FLECHE = 328,
     TOKEN_HEROS = 329,
     TOKEN_CAMERA = 330,
     TOKEN_WAIT = 331,
     TOKEN_HALT = 332,
     TOKEN_RESTART = 333,
     TOKEN_FONDU = 334,
     TOKEN_FRAPPER = 335,
     TOKEN_RECOBJET = 336,
     TOKEN_RECARME = 337,
     TOKEN_SUPOBJET = 338,
     TOKEN_CARTE = 339,
     TOKEN_SETPOSITION = 340,
     TOKEN_SETPOSITIONZ = 341,
     TOKEN_DEPLACER = 342,
     TOKEN_DEPLACERZ = 343,
     TOKEN_ROTATE = 344,
     TOKEN_SOLIDARISER = 345,
     TOKEN_DESOLIDARISER = 346,
     TOKEN_DEFAUT = 347,
     TOKEN_ZOOM = 348,
     TOKEN_AJOUTERANIME = 349,
     TOKEN_AJOUTERNONANIME = 350,
     TOKEN_SETTEMPS = 351,
     TOKEN_SETORIENTATION = 352,
     TOKEN_NOMCARTE = 353,
     TOKEN_WAITFOR = 354,
     TOKEN_BLOQUERTEMPS = 355,
     TOKEN_DEBLOQUERTEMPS = 356,
     TOKEN_CARTEZ = 357
   };
#endif
/* Tokens.  */
#define TOKEN_ENTIER 258
#define TOKEN_REEL 259
#define TOKEN_CHAINE 260
#define TOKEN_IDENT 261
#define TOKEN_NIL 262
#define TOKEN_EOF 263
#define TOKEN_TRUE 264
#define TOKEN_FALSE 265
#define TOKEN_NOT 266
#define TOKEN_AND 267
#define TOKEN_OR 268
#define TOKEN_EQUAL 269
#define TOKEN_DIFF 270
#define TOKEN_INF 271
#define TOKEN_SUP 272
#define TOKEN_INFEQ 273
#define TOKEN_SUPEQ 274
#define TOKEN_IPLUS 275
#define TOKEN_IMOINS 276
#define TOKEN_IMULT 277
#define TOKEN_IDIV 278
#define TOKEN_IMOD 279
#define TOKEN_RPLUS 280
#define TOKEN_RMOINS 281
#define TOKEN_RMULT 282
#define TOKEN_RDIV 283
#define TOKEN_PTR 284
#define TOKEN_TYPE 285
#define TOKEN_BOOLEAN 286
#define TOKEN_INTEGER 287
#define TOKEN_SUBRANGE 288
#define TOKEN_REAL 289
#define TOKEN_STRING 290
#define TOKEN_ARRAY 291
#define TOKEN_OF 292
#define TOKEN_RECORD 293
#define TOKEN_PTVIRG 294
#define TOKEN_AFFECTATION 295
#define TOKEN_IF 296
#define TOKEN_THEN 297
#define TOKEN_ELSE 298
#define TOKEN_WHILE 299
#define TOKEN_DO 300
#define TOKEN_FOR 301
#define TOKEN_TO 302
#define TOKEN_REPEAT 303
#define TOKEN_UNTIL 304
#define TOKEN_BEGIN 305
#define TOKEN_END 306
#define TOKEN_WRITE 307
#define TOKEN_WRITELN 308
#define TOKEN_READ 309
#define TOKEN_READLN 310
#define TOKEN_NEW 311
#define TOKEN_PROCEDURE 312
#define TOKEN_FUNCTION 313
#define TOKEN_CONST 314
#define TOKEN_VAR 315
#define TOKEN_OPENPAR 316
#define TOKEN_CLOSEPAR 317
#define TOKEN_OPENBRACKET 318
#define TOKEN_CLOSEBRACKET 319
#define TOKEN_DEUXPOINTS 320
#define TOKEN_BLANC 321
#define TOKEN_COMMENT 322
#define TOKEN_VIRGULE 323
#define TOKEN_POINT 324
#define TOKEN_MUSIQUE 325
#define TOKEN_MENU 326
#define TOKEN_ITEM 327
#define TOKEN_FLECHE 328
#define TOKEN_HEROS 329
#define TOKEN_CAMERA 330
#define TOKEN_WAIT 331
#define TOKEN_HALT 332
#define TOKEN_RESTART 333
#define TOKEN_FONDU 334
#define TOKEN_FRAPPER 335
#define TOKEN_RECOBJET 336
#define TOKEN_RECARME 337
#define TOKEN_SUPOBJET 338
#define TOKEN_CARTE 339
#define TOKEN_SETPOSITION 340
#define TOKEN_SETPOSITIONZ 341
#define TOKEN_DEPLACER 342
#define TOKEN_DEPLACERZ 343
#define TOKEN_ROTATE 344
#define TOKEN_SOLIDARISER 345
#define TOKEN_DESOLIDARISER 346
#define TOKEN_DEFAUT 347
#define TOKEN_ZOOM 348
#define TOKEN_AJOUTERANIME 349
#define TOKEN_AJOUTERNONANIME 350
#define TOKEN_SETTEMPS 351
#define TOKEN_SETORIENTATION 352
#define TOKEN_NOMCARTE 353
#define TOKEN_WAITFOR 354
#define TOKEN_BLOQUERTEMPS 355
#define TOKEN_DEBLOQUERTEMPS 356
#define TOKEN_CARTEZ 357




/* Copy the first part of user declarations.  */
#line 1 "pascal.parser.y"
 /* Header */
  /* SetOrientation  ; NomCarte */
#include <stdlib.h>
#include <stdio.h>
#include "global.hpp"
#include "pascal.tools.hpp"
#include "pascal.env.hpp"
#include "pascal.expr.hpp"
#include "pascal.prog.hpp"


static const void yyerror(char s[]);

extern int yypascallex(void);
extern FILE *yypascalout;

CPprog *prog;


//ppos position(pascal_position((unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1));

/*
#define NEW_EXPR new CPexpr($1.position.nb_lignes, $1.position.nb_lignes, $1.position.nb_char_ligne, $1.position.nb_char_ligne + $1.position.longueur, $1.position.nb_char_tot, $1.position.nb_char_tot + $1.position.longueur)

#define CODE_CONSTANTE_BOOLEENNE { $$.position = $1.position; $$.val.expr = NEW_EXPR; $$.val.expr->type = CPexpr::PConst; $$.val.expr->val.upconst.pconst.type.type = pevaltype::PETBoolean; $$.val.expr->val.upconst.pconst.val.val.b = $1.val.booleen; }
*/


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

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 30 "pascal.parser.y"
typedef union YYSTYPE {
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
} YYSTYPE;
/* Line 196 of yacc.c.  */
#line 360 "pascal.parser.cpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 219 of yacc.c.  */
#line 372 "pascal.parser.cpp"

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T) && (defined (__STDC__) || defined (__cplusplus))
# include <stddef.h> /* INFRINGES ON USER NAME SPACE */
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if defined (__STDC__) || defined (__cplusplus)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     define YYINCLUDED_STDLIB_H
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2005 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM ((YYSIZE_T) -1)
#  endif
#  ifdef __cplusplus
extern "C" {
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if (! defined (malloc) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if (! defined (free) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifdef __cplusplus
}
#  endif
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
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
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   508

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  103
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  90
/* YYNRULES -- Number of rules. */
#define YYNRULES  195
/* YYNRULES -- Number of states. */
#define YYNSTATES  441

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   357

#define YYTRANSLATE(YYX)						\
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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     6,     9,    10,    12,    14,    16,    18,
      20,    22,    25,    28,    30,    35,    38,    41,    43,    48,
      51,    54,    56,    61,    65,    67,    69,    71,    75,    77,
      79,    81,    83,    85,    87,    90,    99,   103,   109,   110,
     120,   132,   134,   135,   138,   139,   143,   144,   146,   148,
     152,   157,   159,   162,   164,   168,   171,   173,   175,   177,
     179,   181,   183,   185,   187,   189,   191,   193,   195,   197,
     199,   201,   203,   205,   207,   209,   211,   213,   215,   217,
     219,   221,   223,   225,   227,   229,   231,   233,   235,   237,
     238,   242,   246,   252,   260,   265,   274,   279,   284,   289,
     294,   299,   304,   309,   314,   319,   330,   343,   354,   367,
     373,   384,   390,   396,   403,   410,   417,   422,   427,   431,
     435,   437,   439,   441,   443,   445,   447,   453,   459,   465,
     478,   491,   498,   503,   508,   512,   515,   516,   520,   521,
     523,   527,   531,   533,   537,   541,   545,   549,   553,   557,
     559,   563,   567,   571,   575,   577,   581,   585,   589,   593,
     597,   599,   602,   605,   608,   611,   614,   616,   619,   624,
     628,   630,   632,   634,   636,   638,   642,   644,   646,   648,
     650,   652,   654,   662,   664,   666,   669,   671,   672,   676,
     679,   682,   684,   686,   688,   693
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
     104,     0,    -1,   105,     8,    -1,   105,   106,    -1,    -1,
     107,    -1,   110,    -1,   113,    -1,   122,    -1,   123,    -1,
     135,    -1,    59,   108,    -1,   109,   108,    -1,   109,    -1,
       6,    14,   178,    39,    -1,    30,   111,    -1,   112,   111,
      -1,   112,    -1,     6,    14,   117,    39,    -1,    60,   114,
      -1,   114,   115,    -1,   115,    -1,   116,    65,   117,    39,
      -1,   116,    68,     6,    -1,     6,    -1,    31,    -1,    32,
      -1,   178,    33,   178,    -1,    34,    -1,    35,    -1,   118,
      -1,   119,    -1,   120,    -1,     6,    -1,    29,   117,    -1,
      36,    63,   178,    33,   178,    64,    37,   117,    -1,    38,
     121,    51,    -1,   121,     6,    65,   117,    39,    -1,    -1,
      57,     6,    61,   125,    62,    39,   124,   130,    39,    -1,
      58,     6,    61,   125,    62,    65,   117,    39,   124,   130,
      39,    -1,   113,    -1,    -1,   127,   126,    -1,    -1,    39,
     127,   126,    -1,    -1,   128,    -1,   129,    -1,     6,    65,
     117,    -1,    60,     6,    65,   117,    -1,   135,    -1,   132,
     133,    -1,   133,    -1,   132,   133,    39,    -1,   133,    39,
      -1,   134,    -1,   135,    -1,   136,    -1,   137,    -1,   138,
      -1,   139,    -1,   140,    -1,   141,    -1,   142,    -1,   143,
      -1,   144,    -1,   145,    -1,   146,    -1,   172,    -1,   147,
      -1,   148,    -1,   149,    -1,   165,    -1,   150,    -1,   152,
      -1,   153,    -1,   154,    -1,   155,    -1,   156,    -1,   157,
      -1,   159,    -1,   160,    -1,   161,    -1,   158,    -1,   162,
      -1,   164,    -1,   163,    -1,   151,    -1,    -1,    50,   131,
      51,    -1,   178,    40,   178,    -1,    41,   178,    42,   131,
      51,    -1,    41,   178,    42,   131,    43,   131,    51,    -1,
      44,   178,    45,   133,    -1,    46,     6,    40,   178,    47,
     178,    45,   133,    -1,    48,   131,    49,   178,    -1,    52,
      61,   175,    62,    -1,    53,    61,   175,    62,    -1,    54,
      61,   175,    62,    -1,    55,    61,   175,    62,    -1,    56,
      61,     6,    62,    -1,    70,    61,   178,    62,    -1,    76,
      61,   178,    62,    -1,    79,    61,   178,    62,    -1,    84,
      61,   178,    68,   178,    68,   178,    68,   178,    62,    -1,
     102,    61,   178,    68,   178,    68,   178,    68,   178,    68,
     178,    62,    -1,   178,    73,    85,    61,   178,    68,   178,
      68,   178,    62,    -1,   178,    73,    86,    61,   178,    68,
     178,    68,   178,    68,   178,    62,    -1,   178,    73,    80,
      61,    62,    -1,   178,    73,    87,    61,   178,    68,   178,
      68,   178,    62,    -1,   178,    73,    83,    61,    62,    -1,
     178,    73,    82,    61,    62,    -1,   178,    73,    97,    61,
     178,    62,    -1,    94,    61,   178,    68,   178,    62,    -1,
      95,    61,   178,    68,   178,    62,    -1,    96,    61,   178,
      62,    -1,    99,    61,   178,    62,    -1,   100,    61,    62,
      -1,   101,    61,    62,    -1,   166,    -1,   167,    -1,   168,
      -1,   169,    -1,   170,    -1,   171,    -1,    75,    73,    92,
      61,    62,    -1,    75,    73,    90,    61,    62,    -1,    75,
      73,    91,    61,    62,    -1,    75,    73,    85,    61,   178,
      68,   178,    68,   178,    68,   178,    62,    -1,    75,    73,
      89,    61,   178,    68,   178,    68,   178,    68,   178,    62,
      -1,    75,    73,    93,    61,   178,    62,    -1,     6,    61,
     175,    62,    -1,     6,    61,   175,    62,    -1,    98,    61,
      62,    -1,   177,   176,    -1,    -1,    68,   177,   176,    -1,
      -1,   178,    -1,   178,    13,   179,    -1,   178,    12,   179,
      -1,   179,    -1,   179,    14,   180,    -1,   179,    15,   180,
      -1,   179,    16,   180,    -1,   179,    17,   180,    -1,   179,
      18,   180,    -1,   179,    19,   180,    -1,   180,    -1,   180,
      20,   181,    -1,   180,    21,   181,    -1,   180,    25,   181,
      -1,   180,    26,   181,    -1,   181,    -1,   181,    22,   182,
      -1,   181,    23,   182,    -1,   181,    24,   182,    -1,   181,
      27,   182,    -1,   181,    28,   182,    -1,   182,    -1,    11,
     182,    -1,    20,   182,    -1,    21,   182,    -1,    25,   182,
      -1,    26,   182,    -1,   183,    -1,   183,    29,    -1,   183,
      63,   178,    64,    -1,   183,    69,     6,    -1,   184,    -1,
     173,    -1,   174,    -1,   185,    -1,   186,    -1,    61,   178,
      62,    -1,   187,    -1,     3,    -1,     4,    -1,     5,    -1,
       6,    -1,     7,    -1,    71,    61,     5,    62,    50,   188,
      51,    -1,     9,    -1,    10,    -1,   190,   189,    -1,   190,
      -1,    -1,    39,   190,   189,    -1,    39,   189,    -1,    39,
     190,    -1,    39,    -1,   191,    -1,   192,    -1,    72,    61,
       5,    62,    -1,    72,    61,     5,    68,     5,    62,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   173,   173,   176,   182,   189,   190,   191,   192,   193,
     194,   198,   202,   208,   212,   221,   225,   231,   235,   245,
     249,   255,   259,   289,   294,   302,   303,   304,   310,   311,
     312,   317,   318,   319,   328,   332,   342,   350,   357,   361,
     379,   398,   399,   406,   407,   411,   412,   416,   417,   421,
     430,   440,   443,   449,   453,   459,   463,   464,   465,   466,
     467,   468,   469,   470,   471,   472,   473,   474,   475,   476,
     477,   478,   479,   480,   481,   482,   483,   484,   485,   486,
     487,   488,   489,   490,   491,   492,   493,   494,   495,   499,
     506,   514,   523,   534,   544,   553,   564,   573,   580,   587,
     594,   602,   610,   618,   626,   635,   645,   657,   670,   684,
     694,   706,   716,   724,   734,   743,   752,   760,   768,   774,
     782,   783,   784,   785,   786,   787,   791,   798,   805,   814,
     825,   836,   850,   859,   868,   874,   875,   879,   880,   884,
     890,   896,   902,   907,   913,   919,   925,   931,   937,   943,
     947,   953,   959,   965,   971,   975,   981,   987,   993,   999,
    1005,  1009,  1014,  1019,  1024,  1029,  1034,  1038,  1043,  1049,
    1055,  1059,  1060,  1061,  1065,  1066,  1081,  1082,  1088,  1094,
    1100,  1105,  1113,  1122,  1128,  1139,  1140,  1141,  1145,  1146,
    1147,  1148,  1152,  1153,  1157,  1165
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_ENTIER", "TOKEN_REEL",
  "TOKEN_CHAINE", "TOKEN_IDENT", "TOKEN_NIL", "TOKEN_EOF", "TOKEN_TRUE",
  "TOKEN_FALSE", "TOKEN_NOT", "TOKEN_AND", "TOKEN_OR", "TOKEN_EQUAL",
  "TOKEN_DIFF", "TOKEN_INF", "TOKEN_SUP", "TOKEN_INFEQ", "TOKEN_SUPEQ",
  "TOKEN_IPLUS", "TOKEN_IMOINS", "TOKEN_IMULT", "TOKEN_IDIV", "TOKEN_IMOD",
  "TOKEN_RPLUS", "TOKEN_RMOINS", "TOKEN_RMULT", "TOKEN_RDIV", "TOKEN_PTR",
  "TOKEN_TYPE", "TOKEN_BOOLEAN", "TOKEN_INTEGER", "TOKEN_SUBRANGE",
  "TOKEN_REAL", "TOKEN_STRING", "TOKEN_ARRAY", "TOKEN_OF", "TOKEN_RECORD",
  "TOKEN_PTVIRG", "TOKEN_AFFECTATION", "TOKEN_IF", "TOKEN_THEN",
  "TOKEN_ELSE", "TOKEN_WHILE", "TOKEN_DO", "TOKEN_FOR", "TOKEN_TO",
  "TOKEN_REPEAT", "TOKEN_UNTIL", "TOKEN_BEGIN", "TOKEN_END", "TOKEN_WRITE",
  "TOKEN_WRITELN", "TOKEN_READ", "TOKEN_READLN", "TOKEN_NEW",
  "TOKEN_PROCEDURE", "TOKEN_FUNCTION", "TOKEN_CONST", "TOKEN_VAR",
  "TOKEN_OPENPAR", "TOKEN_CLOSEPAR", "TOKEN_OPENBRACKET",
  "TOKEN_CLOSEBRACKET", "TOKEN_DEUXPOINTS", "TOKEN_BLANC", "TOKEN_COMMENT",
  "TOKEN_VIRGULE", "TOKEN_POINT", "TOKEN_MUSIQUE", "TOKEN_MENU",
  "TOKEN_ITEM", "TOKEN_FLECHE", "TOKEN_HEROS", "TOKEN_CAMERA",
  "TOKEN_WAIT", "TOKEN_HALT", "TOKEN_RESTART", "TOKEN_FONDU",
  "TOKEN_FRAPPER", "TOKEN_RECOBJET", "TOKEN_RECARME", "TOKEN_SUPOBJET",
  "TOKEN_CARTE", "TOKEN_SETPOSITION", "TOKEN_SETPOSITIONZ",
  "TOKEN_DEPLACER", "TOKEN_DEPLACERZ", "TOKEN_ROTATE", "TOKEN_SOLIDARISER",
  "TOKEN_DESOLIDARISER", "TOKEN_DEFAUT", "TOKEN_ZOOM",
  "TOKEN_AJOUTERANIME", "TOKEN_AJOUTERNONANIME", "TOKEN_SETTEMPS",
  "TOKEN_SETORIENTATION", "TOKEN_NOMCARTE", "TOKEN_WAITFOR",
  "TOKEN_BLOQUERTEMPS", "TOKEN_DEBLOQUERTEMPS", "TOKEN_CARTEZ", "$accept",
  "main", "liste_declaration", "declaration", "decl_constante",
  "liste_decl_constante1", "decl_constante1", "decl_type",
  "liste_decl_type1", "decl_type1", "decl_variable",
  "liste_decl_variable1", "decl_variable1", "liste_ident", "type",
  "pointer", "array", "record", "liste_decl_champ", "decl_procedure",
  "decl_fonction", "decl_variable2", "liste_parametre", "liste_parametre1",
  "parametre", "parametre_copier", "parametre_ref", "corps",
  "liste_instruction", "liste_instruction1", "instruction", "skip",
  "begin", "affectation", "if", "ifelse", "while", "for", "repeat",
  "write", "writeln", "read", "readln", "pnew", "musique", "wait", "fondu",
  "carte", "cartez", "setpos", "setposz", "frapper", "deplacer",
  "supobjet", "recarme", "setorientation", "ajouteranime",
  "ajouternonanime", "settemps", "waitfor", "bloquertemps",
  "debloquertemps", "camera", "camera_defaut", "camera_solidariser",
  "camera_desolidariser", "camera_setpos", "camera_rotate", "camera_zoom",
  "appel_prog", "appel_expr", "nom_carte", "liste_argument",
  "liste_argument1", "argument", "expr", "expr1", "expr2", "expr3",
  "expr4", "expr5", "expr6", "expr7", "valeur", "booleen", "menu_items",
  "menu_items1", "menu_item", "additem1", "additem2", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
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
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   103,   104,   105,   105,   106,   106,   106,   106,   106,
     106,   107,   108,   108,   109,   110,   111,   111,   112,   113,
     114,   114,   115,   116,   116,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   118,   119,   120,   121,   121,   122,
     123,   124,   124,   125,   125,   126,   126,   127,   127,   128,
     129,   130,   131,   131,   132,   132,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   165,   165,   165,   165,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   175,   176,   176,   177,
     178,   178,   178,   179,   179,   179,   179,   179,   179,   179,
     180,   180,   180,   180,   180,   181,   181,   181,   181,   181,
     181,   182,   182,   182,   182,   182,   182,   183,   183,   183,
     183,   184,   184,   184,   185,   185,   186,   186,   186,   186,
     186,   186,   186,   187,   187,   188,   188,   188,   189,   189,
     189,   189,   190,   190,   191,   192
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     2,     0,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     4,     2,     2,     1,     4,     2,
       2,     1,     4,     3,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     2,     8,     3,     5,     0,     9,
      11,     1,     0,     2,     0,     3,     0,     1,     1,     3,
       4,     1,     2,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       3,     3,     5,     7,     4,     8,     4,     4,     4,     4,
       4,     4,     4,     4,     4,    10,    12,    10,    12,     5,
      10,     5,     5,     6,     6,     6,     4,     4,     3,     3,
       1,     1,     1,     1,     1,     1,     5,     5,     5,    12,
      12,     6,     4,     4,     3,     2,     0,     3,     0,     1,
       3,     3,     1,     3,     3,     3,     3,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     3,     3,     3,
       1,     2,     2,     2,     2,     2,     1,     2,     4,     3,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     7,     1,     1,     2,     1,     0,     3,     2,
       2,     1,     1,     1,     4,     6
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       4,     0,     0,     1,     2,     0,    89,     0,     0,     0,
       0,     3,     5,     6,     7,     8,     9,    10,     0,    15,
      17,   177,   178,   179,   180,   181,   183,   184,     0,     0,
       0,     0,     0,     0,     0,     0,    89,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    89,    53,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    70,    71,    72,    74,    88,    75,    76,
      77,    78,    79,    80,    84,    81,    82,    83,    85,    87,
      86,    73,   120,   121,   122,   123,   124,   125,    69,   171,
     172,     0,   142,   149,   154,   160,   166,   170,   173,   174,
     176,     0,     0,     0,    11,    13,    24,    19,    21,     0,
       0,    16,   136,   180,   161,   162,   163,   164,   165,     0,
       0,     0,     0,   136,   136,   136,   136,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    90,    52,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   167,     0,     0,    44,    44,
       0,    12,    20,     0,     0,   180,     0,    25,    26,    28,
      29,     0,    38,     0,    30,    31,    32,     0,     0,   138,
     139,   136,    89,    89,     0,     0,     0,     0,     0,     0,
       0,   175,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   134,     0,   118,   119,
       0,    54,   141,   140,    91,     0,     0,     0,     0,     0,
       0,     0,   143,   144,   145,   146,   147,   148,   150,   151,
     152,   153,   155,   156,   157,   158,   159,     0,   169,     0,
       0,     0,    46,    47,    48,     0,     0,     0,    23,    34,
       0,     0,    18,     0,   133,     0,   135,     0,     0,    94,
       0,    96,    97,    98,    99,   100,   101,   102,     0,     0,
       0,     0,     0,     0,     0,   103,   104,     0,     0,     0,
     116,   117,     0,     0,     0,     0,     0,     0,     0,     0,
     168,     0,     0,     0,     0,    43,     0,    14,    22,     0,
       0,    36,    27,   138,   133,    89,    92,     0,   187,     0,
       0,   127,   128,   126,     0,     0,     0,     0,     0,   109,
     112,   111,     0,     0,     0,     0,    49,     0,    42,    46,
       0,     0,     0,   137,     0,     0,     0,     0,   186,   192,
     193,     0,     0,   131,     0,   114,   115,     0,     0,     0,
       0,   113,    50,    41,     0,    45,     0,     0,     0,    93,
      89,     0,   182,   191,   185,     0,     0,     0,     0,     0,
       0,     0,     0,    51,    42,     0,    37,    95,     0,   189,
     190,     0,     0,     0,     0,     0,     0,     0,    39,     0,
       0,   194,     0,   188,     0,     0,     0,     0,     0,     0,
       0,     0,    35,     0,     0,     0,   105,     0,   107,     0,
     110,    40,   195,     0,     0,     0,     0,   129,   130,   106,
     108
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     1,     2,    11,    12,   114,   115,    13,    19,    20,
     373,   117,   118,   119,   193,   194,   195,   196,   271,    15,
      16,   374,   261,   315,   262,   263,   264,   392,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   198,   276,   199,   197,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   357,   384,   358,   359,   360
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -323
static const short int yypact[] =
{
    -323,    10,   171,  -323,  -323,    23,   406,    74,    95,   118,
     198,  -323,  -323,  -323,  -323,  -323,  -323,  -323,    81,  -323,
      23,  -323,  -323,  -323,    54,  -323,  -323,  -323,    87,    87,
      87,    87,    87,    87,    87,   202,   406,   149,   162,   166,
     173,   178,    87,   192,   257,   144,   261,   266,   271,   272,
     273,   282,   283,   293,   296,   298,   299,   186,   406,   212,
    -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,
    -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,
    -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,
    -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,
    -323,     0,   334,   321,   289,  -323,   151,  -323,  -323,  -323,
    -323,   310,   311,   249,  -323,   118,  -323,   198,  -323,   126,
      28,  -323,    87,   318,  -323,  -323,  -323,  -323,  -323,    72,
     231,   221,   217,    87,    87,    87,    87,   268,    70,    87,
     276,   246,    87,    87,    87,    87,    87,    87,   319,    87,
     320,   322,    87,  -323,   269,  -323,    87,    87,    87,   243,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,  -323,    87,   374,    -2,    -2,
      87,  -323,  -323,    28,   377,    26,    28,  -323,  -323,  -323,
    -323,   323,  -323,   346,  -323,  -323,  -323,   265,   325,   324,
     274,    87,   406,   406,    87,    87,   326,   327,   328,   329,
     331,  -323,   180,   332,   341,   342,   343,   344,   345,   353,
     190,   194,     3,    11,    13,   200,  -323,   203,  -323,  -323,
      32,  -323,   334,   334,   274,   359,   361,   363,   364,   367,
     368,   369,   321,   321,   321,   321,   321,   321,   289,   289,
     289,   289,  -323,  -323,  -323,  -323,  -323,   174,  -323,   370,
     401,   371,   395,  -323,  -323,   375,   267,   397,  -323,  -323,
      87,    35,  -323,    87,   133,    87,  -323,   376,   -40,  -323,
      30,   274,  -323,  -323,  -323,  -323,  -323,  -323,   389,    87,
      87,   378,   379,   380,    87,  -323,  -323,    87,    87,    87,
    -323,  -323,    87,   381,   382,   383,    87,    87,    87,    87,
    -323,    28,   384,   407,    -2,  -323,   386,  -323,  -323,   277,
     388,  -323,   274,   324,  -323,   406,  -323,    87,   385,    34,
      38,  -323,  -323,  -323,   206,    43,   213,   220,    55,  -323,
    -323,  -323,    57,    63,    91,   223,  -323,    28,   403,   395,
      28,    87,    28,  -323,   404,   260,   387,   413,   426,  -323,
    -323,    87,    87,  -323,    87,  -323,  -323,    87,    87,    87,
      87,  -323,  -323,  -323,   416,  -323,   429,   176,   430,  -323,
     406,   465,  -323,    33,  -323,    97,   105,   107,   109,   122,
     132,   137,   432,  -323,   403,   435,  -323,  -323,    89,  -323,
     426,    87,    87,    87,    87,    87,    87,    87,  -323,   416,
      28,  -323,   468,  -323,   141,   143,   233,   154,   235,   156,
     237,   436,  -323,   412,    87,    87,  -323,    87,  -323,    87,
    -323,  -323,  -323,   242,   245,   247,   258,  -323,  -323,  -323,
    -323
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -323,  -323,  -323,  -323,  -323,   365,  -323,  -323,   458,  -323,
     477,  -323,   366,  -323,  -169,  -323,  -323,  -323,  -323,  -323,
    -323,    90,   307,   138,   175,  -323,  -323,    79,   -31,  -323,
     -56,  -323,    -1,  -323,  -323,  -323,  -323,  -323,  -323,  -323,
    -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,
    -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,
    -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,
    -323,  -323,  -127,   168,   218,    -6,   158,   205,   209,   -10,
    -323,  -323,  -323,  -323,  -323,  -323,  -322,   111,  -323,  -323
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -133
static const short int yytable[] =
{
     101,    17,   154,   325,   259,   132,   206,   207,   208,   209,
       3,   326,   156,   157,   267,   156,   157,   269,   124,   125,
     126,   127,   128,   156,   157,   156,   157,   129,   130,    18,
     101,    21,    22,    23,   185,    25,   138,    26,    27,    28,
     158,   320,   156,   157,   156,   157,   156,   157,    29,    30,
     156,   157,   101,    31,    32,   156,   157,   186,   260,   187,
     188,   399,   189,   190,   191,   -33,   192,   156,   157,   156,
     157,   297,   383,   159,   277,   156,   157,   327,   413,   298,
     111,   299,   156,   157,   156,   157,   321,   201,   -33,    42,
      21,    22,    23,   123,    25,   120,    26,    27,    28,    44,
     302,   112,   361,   156,   157,   356,   362,    29,    30,   156,
     157,   364,    31,    32,   202,   122,   200,   156,   157,   156,
     157,   156,   157,   367,   113,   368,    52,   200,   200,   200,
     200,   369,   211,   212,   156,   157,   220,   221,   222,   223,
     224,   225,   346,   227,   156,   157,   230,   279,    42,   156,
     157,   411,   234,   156,   157,   156,   157,   412,    44,   370,
     252,   253,   254,   255,   256,   401,   156,   157,   156,   157,
     257,   278,  -132,   402,   266,   403,  -132,   404,   372,     4,
     175,   376,  -132,   378,  -132,    52,   156,   157,   156,   157,
     405,   183,   156,   157,   184,   200,   101,   101,   280,   281,
     406,     5,   156,   157,   116,   407,   156,   157,   131,   424,
     133,   425,   156,   157,   176,   156,   157,   141,   156,   157,
     177,     6,   427,   134,   429,   156,   157,   135,     7,     8,
       9,    10,   156,   157,   136,   156,   157,   153,   310,   137,
     395,   422,   287,   156,   157,   156,   157,   156,   157,   156,
     157,   155,   295,   139,   156,   157,   296,   156,   157,   156,
     157,   204,   300,   180,   319,   301,   205,   322,   363,   200,
     156,   157,   156,   157,   210,   365,   203,   156,   157,   156,
     157,   213,   366,   329,   330,   371,   156,   157,   334,   156,
     157,   335,   336,   337,   354,   426,   338,   428,   273,   430,
     342,   343,   344,   345,   437,   380,   317,   438,   231,   439,
     351,   170,   171,   172,   232,   233,   173,   174,   140,   101,
     440,   355,   142,   235,   397,   236,   237,   143,   238,   239,
     240,   214,   144,   145,   146,   215,   216,   217,   218,   219,
     241,   166,   167,   147,   148,   377,   168,   169,   160,   161,
     162,   163,   164,   165,   149,   385,   386,   150,   387,   151,
     152,   388,   389,   390,   391,   242,   243,   244,   245,   246,
     247,   178,   179,   393,   101,   248,   249,   250,   251,   201,
     258,   226,   228,   268,   229,   272,   270,   274,   282,   283,
     284,   285,   275,   286,   288,   414,   415,   416,   417,   418,
     419,   420,   289,   290,   291,   292,   293,   312,   393,    21,
      22,    23,    24,    25,   294,    26,    27,    28,   433,   434,
     303,   435,   304,   436,   305,   306,    29,    30,   307,   308,
     309,    31,    32,   313,   314,   311,   318,   316,   324,   328,
     331,   332,   333,   339,   340,   341,   348,    33,   381,   347,
      34,   350,    35,   352,    36,   379,     6,   356,    37,    38,
      39,    40,    41,    10,   382,   383,     6,    42,   394,   396,
     398,   408,   410,   423,   432,   431,    43,    44,   121,    14,
     181,    45,    46,   182,   409,    47,   265,   375,   421,   349,
      48,   353,     0,   323,   400,     0,     0,     0,     0,     0,
      49,    50,    51,     0,    52,    53,    54,    55,    56
};

static const short int yycheck[] =
{
       6,     2,    58,    43,     6,    36,   133,   134,   135,   136,
       0,    51,    12,    13,   183,    12,    13,   186,    28,    29,
      30,    31,    32,    12,    13,    12,    13,    33,    34,     6,
      36,     3,     4,     5,     6,     7,    42,     9,    10,    11,
      40,     6,    12,    13,    12,    13,    12,    13,    20,    21,
      12,    13,    58,    25,    26,    12,    13,    29,    60,    31,
      32,   383,    34,    35,    36,    39,    38,    12,    13,    12,
      13,    68,    39,    73,   201,    12,    13,    47,   400,    68,
       6,    68,    12,    13,    12,    13,    51,    61,    62,    61,
       3,     4,     5,     6,     7,    14,     9,    10,    11,    71,
      68,     6,    68,    12,    13,    72,    68,    20,    21,    12,
      13,    68,    25,    26,    42,    61,   122,    12,    13,    12,
      13,    12,    13,    68,     6,    68,    98,   133,   134,   135,
     136,    68,    62,   139,    12,    13,   142,   143,   144,   145,
     146,   147,   311,   149,    12,    13,   152,   203,    61,    12,
      13,    62,   158,    12,    13,    12,    13,    68,    71,    68,
     170,   171,   172,   173,   174,    68,    12,    13,    12,    13,
     176,   202,    39,    68,   180,    68,    43,    68,   347,     8,
      29,   350,    49,   352,    51,    98,    12,    13,    12,    13,
      68,    65,    12,    13,    68,   201,   202,   203,   204,   205,
      68,    30,    12,    13,     6,    68,    12,    13,     6,    68,
      61,    68,    12,    13,    63,    12,    13,    73,    12,    13,
      69,    50,    68,    61,    68,    12,    13,    61,    57,    58,
      59,    60,    12,    13,    61,    12,    13,    51,    64,    61,
      64,   410,    62,    12,    13,    12,    13,    12,    13,    12,
      13,    39,    62,    61,    12,    13,    62,    12,    13,    12,
      13,    40,    62,    14,   270,    62,    49,   273,    62,   275,
      12,    13,    12,    13,     6,    62,    45,    12,    13,    12,
      13,     5,    62,   289,   290,    62,    12,    13,   294,    12,
      13,   297,   298,   299,   325,    62,   302,    62,    33,    62,
     306,   307,   308,   309,    62,    45,    39,    62,    39,    62,
      33,    22,    23,    24,   156,   157,    27,    28,    61,   325,
      62,   327,    61,    80,   380,    82,    83,    61,    85,    86,
      87,    85,    61,    61,    61,    89,    90,    91,    92,    93,
      97,    20,    21,    61,    61,   351,    25,    26,    14,    15,
      16,    17,    18,    19,    61,   361,   362,    61,   364,    61,
      61,   367,   368,   369,   370,   160,   161,   162,   163,   164,
     165,    61,    61,   374,   380,   166,   167,   168,   169,    61,
       6,    62,    62,     6,    62,    39,    63,    62,    62,    62,
      62,    62,    68,    62,    62,   401,   402,   403,   404,   405,
     406,   407,    61,    61,    61,    61,    61,     6,   409,     3,
       4,     5,     6,     7,    61,     9,    10,    11,   424,   425,
      61,   427,    61,   429,    61,    61,    20,    21,    61,    61,
      61,    25,    26,    62,    39,    65,    39,    62,    62,    50,
      62,    62,    62,    62,    62,    62,    39,    41,    61,    65,
      44,    65,    46,    65,    48,    51,    50,    72,    52,    53,
      54,    55,    56,    60,    51,    39,    50,    61,    39,    39,
       5,    39,    37,     5,    62,    39,    70,    71,    20,     2,
     115,    75,    76,   117,   394,    79,   179,   349,   409,   314,
      84,   323,    -1,   275,   383,    -1,    -1,    -1,    -1,    -1,
      94,    95,    96,    -1,    98,    99,   100,   101,   102
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,   104,   105,     0,     8,    30,    50,    57,    58,    59,
      60,   106,   107,   110,   113,   122,   123,   135,     6,   111,
     112,     3,     4,     5,     6,     7,     9,    10,    11,    20,
      21,    25,    26,    41,    44,    46,    48,    52,    53,    54,
      55,    56,    61,    70,    71,    75,    76,    79,    84,    94,
      95,    96,    98,    99,   100,   101,   102,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,     6,     6,     6,   108,   109,     6,   114,   115,   116,
      14,   111,    61,     6,   182,   182,   182,   182,   182,   178,
     178,     6,   131,    61,    61,    61,    61,    61,   178,    61,
      61,    73,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    51,   133,    39,    12,    13,    40,    73,
      14,    15,    16,    17,    18,    19,    20,    21,    25,    26,
      22,    23,    24,    27,    28,    29,    63,    69,    61,    61,
      14,   108,   115,    65,    68,     6,    29,    31,    32,    34,
      35,    36,    38,   117,   118,   119,   120,   178,   175,   177,
     178,    61,    42,    45,    40,    49,   175,   175,   175,   175,
       6,    62,   178,     5,    85,    89,    90,    91,    92,    93,
     178,   178,   178,   178,   178,   178,    62,   178,    62,    62,
     178,    39,   179,   179,   178,    80,    82,    83,    85,    86,
      87,    97,   180,   180,   180,   180,   180,   180,   181,   181,
     181,   181,   182,   182,   182,   182,   182,   178,     6,     6,
      60,   125,   127,   128,   129,   125,   178,   117,     6,   117,
      63,   121,    39,    33,    62,    68,   176,   175,   131,   133,
     178,   178,    62,    62,    62,    62,    62,    62,    62,    61,
      61,    61,    61,    61,    61,    62,    62,    68,    68,    68,
      62,    62,    68,    61,    61,    61,    61,    61,    61,    61,
      64,    65,     6,    62,    39,   126,    62,    39,    39,   178,
       6,    51,   178,   177,    62,    43,    51,    47,    50,   178,
     178,    62,    62,    62,   178,   178,   178,   178,   178,    62,
      62,    62,   178,   178,   178,   178,   117,    65,    39,   127,
      65,    33,    65,   176,   131,   178,    72,   188,   190,   191,
     192,    68,    68,    62,    68,    62,    62,    68,    68,    68,
      68,    62,   117,   113,   124,   126,   117,   178,   117,    51,
      45,    61,    51,    39,   189,   178,   178,   178,   178,   178,
     178,   178,   130,   135,    39,    64,    39,   133,     5,   189,
     190,    68,    68,    68,    68,    68,    68,    68,    39,   124,
      37,    62,    68,   189,   178,   178,   178,   178,   178,   178,
     178,   130,   117,     5,    68,    68,    62,    68,    62,    68,
      62,    39,    62,   178,   178,   178,   178,    62,    62,    62,
      62
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
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (0)


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
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
    while (0)
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
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
} while (0)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr,					\
                  Type, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
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
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname[yyr1[yyrule]]);
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
  const char *yys = yystr;

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
      size_t yyn = 0;
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

#endif /* YYERROR_VERBOSE */



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
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);


# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

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
    ;
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

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



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
	short int *yyss1 = yyss;


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
	short int *yyss1 = yyss;
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

/* Do appropriate processing given the current state.  */
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

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

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

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
#line 173 "pascal.parser.y"
    { prog = (yyvsp[-1].prog); fprintf(yypascalout, "Analyse r�ussie."); pmessage("Analyse r�ussie !"); return 0; ;}
    break;

  case 3:
#line 176 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-1].prog)->position.deb_ligne, (yyvsp[0].prog)->position.fin_ligne, (yyvsp[-1].prog)->position.deb_car, (yyvsp[0].prog)->position.fin_car, (yyvsp[-1].prog)->position.deb_car_tot, (yyvsp[0].prog)->position.fin_car_tot);
  (yyval.prog)->type = CPprog::PSeq;
  (yyval.prog)->val.upseq.p1 = (yyvsp[-1].prog);
  (yyval.prog)->val.upseq.p2 = (yyvsp[0].prog);
;}
    break;

  case 4:
#line 182 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1);
  (yyval.prog)->type = CPprog::PSkip;
;}
    break;

  case 5:
#line 189 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 6:
#line 190 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 7:
#line 191 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 8:
#line 192 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 9:
#line 193 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 10:
#line 194 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 11:
#line 198 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 12:
#line 202 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-1].prog)->position.deb_ligne, (yyvsp[0].prog)->position.fin_ligne, (yyvsp[-1].prog)->position.deb_car, (yyvsp[0].prog)->position.fin_car, (yyvsp[-1].prog)->position.deb_car_tot, (yyvsp[0].prog)->position.fin_car_tot);
  (yyval.prog)->type = CPprog::PSeq;
  (yyval.prog)->val.upseq.p1 = (yyvsp[-1].prog);
  (yyval.prog)->val.upseq.p2 = (yyvsp[0].prog);
;}
    break;

  case 13:
#line 208 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 14:
#line 212 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-3].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-3].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-3].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PConst;
  (yyval.prog)->val.upconst.nom = (yyvsp[-3].token).val.ident;
  (yyval.prog)->val.upconst.val = (yyvsp[-1].expr);
;}
    break;

  case 15:
#line 221 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 16:
#line 225 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-1].prog)->position.deb_ligne, (yyvsp[0].prog)->position.fin_ligne, (yyvsp[-1].prog)->position.deb_car, (yyvsp[0].prog)->position.fin_car, (yyvsp[-1].prog)->position.deb_car_tot, (yyvsp[0].prog)->position.fin_car_tot);
  (yyval.prog)->type = CPprog::PSeq;
  (yyval.prog)->val.upseq.p1 = (yyvsp[-1].prog);
  (yyval.prog)->val.upseq.p2 = (yyvsp[0].prog);
;}
    break;

  case 17:
#line 231 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 18:
#line 235 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-3].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-3].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-3].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PType;
  (yyval.prog)->val.uptype.ident = (yyvsp[-3].token).val.ident;
  (yyval.prog)->val.uptype.dvaltype = *((yyvsp[-1].dvaltype));
;}
    break;

  case 19:
#line 245 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 20:
#line 249 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-1].prog)->position.deb_ligne, (yyvsp[0].prog)->position.fin_ligne, (yyvsp[-1].prog)->position.deb_car, (yyvsp[0].prog)->position.fin_car, (yyvsp[-1].prog)->position.deb_car_tot, (yyvsp[0].prog)->position.fin_car_tot);
  (yyval.prog)->type = CPprog::PSeq;
  (yyval.prog)->val.upseq.p1 = (yyvsp[-1].prog);
  (yyval.prog)->val.upseq.p2 = (yyvsp[0].prog);
;}
    break;

  case 21:
#line 255 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 22:
#line 259 "pascal.parser.y"
    {
  class pliste<struct YYSTYPE::ttoken> *temp = (yyvsp[-3].ltoken);
  if (temp == NULL) {
    pmesserr("Dans le parser, � la regle decl_variable1, liste_ident est NULL !!");
    return -1;
  }
  struct YYSTYPE::ttoken *p = temp->a;
  class CPprog *pr, *ps;
  (yyval.prog) = new class CPprog(p->position.nb_lignes, (yyvsp[0].token).position.nb_lignes, p->position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, p->position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PVar;
  (yyval.prog)->val.upvar.nom = p->val.ident;
  (yyval.prog)->val.upvar.t = *((yyvsp[-1].dvaltype));
  
  while (temp->suivant != NULL) {
    temp = temp->suivant;
    p = temp->a;
    pr = new class CPprog(p->position.nb_lignes, (yyvsp[0].token).position.nb_lignes, p->position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, p->position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
    pr->type = CPprog::PVar;
    pr->val.upvar.nom = p->val.ident;
    pr->val.upvar.t = *((yyvsp[-1].dvaltype));
    ps = (yyval.prog);
    (yyval.prog) = new class CPprog(p->position.nb_lignes, (yyvsp[0].token).position.nb_lignes, p->position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, p->position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
    (yyval.prog)->type = CPprog::PSeq;
    (yyval.prog)->val.upseq.p1 = pr;
    (yyval.prog)->val.upseq.p2 = ps;
  }
;}
    break;

  case 23:
#line 289 "pascal.parser.y"
    { 
  struct YYSTYPE::ttoken *temp = new struct YYSTYPE::ttoken;
  *temp = (yyvsp[0].token);
  (yyval.ltoken) = mp(temp, (yyvsp[-2].ltoken)); 
;}
    break;

  case 24:
#line 294 "pascal.parser.y"
    { 
  struct YYSTYPE::ttoken *temp = new struct YYSTYPE::ttoken;
  *temp = (yyvsp[0].token);
  (yyval.ltoken) = mp(temp, (class pliste<struct YYSTYPE::ttoken> *)NULL); 
;}
    break;

  case 25:
#line 302 "pascal.parser.y"
    { (yyval.dvaltype) = new pdvaltype; (yyval.dvaltype)->type = pdvaltype::PDTBoolean; ;}
    break;

  case 26:
#line 303 "pascal.parser.y"
    { (yyval.dvaltype) = new pdvaltype; (yyval.dvaltype)->type = pdvaltype::PDTInteger; ;}
    break;

  case 27:
#line 304 "pascal.parser.y"
    { // subrange
  (yyval.dvaltype) = new pdvaltype; 
  (yyval.dvaltype)->type = pdvaltype::PDTSubrange;
  (yyval.dvaltype)->val.s.mine = (yyvsp[-2].expr);
  (yyval.dvaltype)->val.s.maxe = (yyvsp[0].expr);
;}
    break;

  case 28:
#line 310 "pascal.parser.y"
    { (yyval.dvaltype) = new pdvaltype; (yyval.dvaltype)->type = pdvaltype::PDTReal; ;}
    break;

  case 29:
#line 311 "pascal.parser.y"
    { (yyval.dvaltype) = new pdvaltype; (yyval.dvaltype)->type = pdvaltype::PDTString; ;}
    break;

  case 30:
#line 312 "pascal.parser.y"
    {
  (yyval.dvaltype) = new pdvaltype; 
  (yyval.dvaltype)->type = pdvaltype::PDTPointer;
  (yyval.dvaltype)->val.ptr = (yyvsp[0].dvaltype);
;}
    break;

  case 31:
#line 317 "pascal.parser.y"
    { (yyval.dvaltype) = (yyvsp[0].dvaltype); ;}
    break;

  case 32:
#line 318 "pascal.parser.y"
    { (yyval.dvaltype) = (yyvsp[0].dvaltype); ;}
    break;

  case 33:
#line 319 "pascal.parser.y"
    {
  (yyval.dvaltype) = new pdvaltype; 
  (yyval.dvaltype)->type = pdvaltype::PDTUser;
  (yyval.dvaltype)->val.user = (yyvsp[0].token).val.ident;
;}
    break;

  case 34:
#line 328 "pascal.parser.y"
    { (yyval.dvaltype) = (yyvsp[0].dvaltype); ;}
    break;

  case 35:
#line 332 "pascal.parser.y"
    {
  (yyval.dvaltype) = new pdvaltype; 
  (yyval.dvaltype)->type = pdvaltype::PDTArray;
  (yyval.dvaltype)->val.array.indice.mine = (yyvsp[-5].expr);
  (yyval.dvaltype)->val.array.indice.maxe = (yyvsp[-3].expr);
  (yyval.dvaltype)->val.array.type = (yyvsp[0].dvaltype);
;}
    break;

  case 36:
#line 342 "pascal.parser.y"
    {
  (yyval.dvaltype) = new pdvaltype;
  (yyval.dvaltype)->type = pdvaltype::PDTRecord;
  (yyval.dvaltype)->val.record.champs = (yyvsp[-1].lchamp);
;}
    break;

  case 37:
#line 350 "pascal.parser.y"
    {
  struct pascal_dval_type::tpdtrecord::champ *temp;
  temp = new struct pascal_dval_type::tpdtrecord::champ;
  temp->nom = (yyvsp[-3].token).val.ident;
  temp->type = (yyvsp[-1].dvaltype);
  (yyval.lchamp) = mp(temp, (yyvsp[-4].lchamp));
;}
    break;

  case 38:
#line 357 "pascal.parser.y"
    { (yyval.lchamp) = (class pliste<struct pascal_dval_type::tpdtrecord::champ> *) NULL; ;}
    break;

  case 39:
#line 364 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-8].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-8].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-8].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PVar;
  (yyval.prog)->val.upvar.nom = (yyvsp[-7].token).val.ident;
  (yyval.prog)->val.upvar.t.type = pdvaltype::PDTProcedure;
  (yyval.prog)->val.upvar.t.val.proc.env = NULL;
  (yyval.prog)->val.upvar.t.val.proc.params = (yyvsp[-5].params);
  (yyval.prog)->val.upvar.t.val.proc.corps = new class CPprog((yyvsp[-2].prog)->position.deb_ligne, (yyvsp[-1].prog)->position.fin_ligne, (yyvsp[-2].prog)->position.deb_car, (yyvsp[-1].prog)->position.fin_car, (yyvsp[-2].prog)->position.deb_car_tot, (yyvsp[-1].prog)->position.fin_car_tot);
  (yyval.prog)->val.upvar.t.val.proc.corps->type = CPprog::PSeq;
  (yyval.prog)->val.upvar.t.val.proc.corps->val.upseq.p1 = (yyvsp[-2].prog);
  (yyval.prog)->val.upvar.t.val.proc.corps->val.upseq.p2 = (yyvsp[-1].prog);
;}
    break;

  case 40:
#line 382 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-10].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-10].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-10].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PVar;
  (yyval.prog)->val.upvar.nom = (yyvsp[-9].token).val.ident;
  (yyval.prog)->val.upvar.t.type = pdvaltype::PDTFunction;
  (yyval.prog)->val.upvar.t.val.func.env = NULL;
  (yyval.prog)->val.upvar.t.val.func.params = (yyvsp[-7].params);
  (yyval.prog)->val.upvar.t.val.func.type = (yyvsp[-4].dvaltype);
  (yyval.prog)->val.upvar.t.val.func.corps = new class CPprog((yyvsp[-2].prog)->position.deb_ligne, (yyvsp[-1].prog)->position.fin_ligne, (yyvsp[-2].prog)->position.deb_car, (yyvsp[-1].prog)->position.fin_car, (yyvsp[-2].prog)->position.deb_car_tot, (yyvsp[-1].prog)->position.fin_car_tot);
  (yyval.prog)->val.upvar.t.val.func.corps->type = CPprog::PSeq;
  (yyval.prog)->val.upvar.t.val.func.corps->val.upseq.p1 = (yyvsp[-2].prog);
  (yyval.prog)->val.upvar.t.val.func.corps->val.upseq.p2 = (yyvsp[-1].prog);
;}
    break;

  case 41:
#line 398 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 42:
#line 399 "pascal.parser.y"
    {
    (yyval.prog) = new class CPprog((unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1);
    (yyval.prog)->type = CPprog::PSkip;
  ;}
    break;

  case 43:
#line 406 "pascal.parser.y"
    { (yyval.params) = mp((yyvsp[-1].param),(yyvsp[0].params)); ;}
    break;

  case 44:
#line 407 "pascal.parser.y"
    { (yyval.params) = (class pliste<struct pascal_dval_type::tpdtprocedure::param> *) NULL; ;}
    break;

  case 45:
#line 411 "pascal.parser.y"
    { (yyval.params) = mp((yyvsp[-1].param),(yyvsp[0].params)); ;}
    break;

  case 46:
#line 412 "pascal.parser.y"
    { (yyval.params) = (class pliste<struct pascal_dval_type::tpdtprocedure::param> *) NULL; ;}
    break;

  case 47:
#line 416 "pascal.parser.y"
    { (yyval.param) = (yyvsp[0].param); ;}
    break;

  case 48:
#line 417 "pascal.parser.y"
    { (yyval.param) = (yyvsp[0].param); ;}
    break;

  case 49:
#line 421 "pascal.parser.y"
    {
  (yyval.param) = new struct pascal_dval_type::tpdtprocedure::param;
  (yyval.param)->var = false;
  (yyval.param)->nom = (yyvsp[-2].token).val.ident;
  (yyval.param)->dvaltype_ptr = (yyvsp[0].dvaltype);
;}
    break;

  case 50:
#line 431 "pascal.parser.y"
    {
  (yyval.param) = new struct pascal_dval_type::tpdtprocedure::param;
  (yyval.param)->var = true;
  (yyval.param)->nom = (yyvsp[-2].token).val.ident;
  (yyval.param)->dvaltype_ptr = (yyvsp[0].dvaltype);
;}
    break;

  case 51:
#line 440 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 52:
#line 443 "pascal.parser.y"
    {
    (yyval.prog) = new class CPprog((yyvsp[-1].prog)->position.deb_ligne, (yyvsp[0].prog)->position.fin_ligne, (yyvsp[-1].prog)->position.deb_car, (yyvsp[0].prog)->position.fin_car, (yyvsp[-1].prog)->position.deb_car_tot, (yyvsp[0].prog)->position.fin_car_tot);
    (yyval.prog)->type = CPprog::PSeq;
    (yyval.prog)->val.upseq.p1 = (yyvsp[-1].prog);
    (yyval.prog)->val.upseq.p2 = (yyvsp[0].prog);
  ;}
    break;

  case 53:
#line 449 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 54:
#line 453 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-2].prog)->position.deb_ligne, (yyvsp[-1].prog)->position.fin_ligne, (yyvsp[-2].prog)->position.deb_car, (yyvsp[-1].prog)->position.fin_car, (yyvsp[-2].prog)->position.deb_car_tot, (yyvsp[-1].prog)->position.fin_car_tot);
  (yyval.prog)->type = CPprog::PSeq;
  (yyval.prog)->val.upseq.p1 = (yyvsp[-2].prog);
  (yyval.prog)->val.upseq.p2 = (yyvsp[-1].prog);
;}
    break;

  case 55:
#line 459 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[-1].prog); ;}
    break;

  case 56:
#line 463 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 57:
#line 464 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 58:
#line 465 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 59:
#line 466 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 60:
#line 467 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 61:
#line 468 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 62:
#line 469 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 63:
#line 470 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 64:
#line 471 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 65:
#line 472 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 66:
#line 473 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 67:
#line 474 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 68:
#line 475 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 69:
#line 476 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 70:
#line 477 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 71:
#line 478 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 72:
#line 479 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 73:
#line 480 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 74:
#line 481 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 75:
#line 482 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 76:
#line 483 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 77:
#line 484 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 78:
#line 485 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 79:
#line 486 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 80:
#line 487 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 81:
#line 488 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 82:
#line 489 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 83:
#line 490 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 84:
#line 491 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 85:
#line 492 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 86:
#line 493 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 87:
#line 494 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 88:
#line 495 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 89:
#line 499 "pascal.parser.y"
    {
  /* ... */
  (yyval.prog) = new class CPprog((unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1);
  (yyval.prog)->type = CPprog::PSkip;
;}
    break;

  case 90:
#line 506 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-2].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-2].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-2].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PBegin;
  (yyval.prog)->val.upbegin.p = (yyvsp[-1].prog);
;}
    break;

  case 91:
#line 514 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-2].expr)->position.deb_ligne, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-2].expr)->position.deb_car, (yyvsp[0].expr)->position.fin_car, (yyvsp[-2].expr)->position.deb_car_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.prog)->type = CPprog::PAffectation;
  (yyval.prog)->val.upaffectation.lval = (yyvsp[-2].expr);
  (yyval.prog)->val.upaffectation.e = (yyvsp[0].expr);
;}
    break;

  case 92:
#line 523 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-4].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-4].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-4].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PIf;
  (yyval.prog)->val.upif.b = (yyvsp[-3].expr);
  (yyval.prog)->val.upif.p = (yyvsp[-1].prog);
  (yyval.prog)->val.upif.q = new class CPprog((unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1);
  (yyval.prog)->val.upif.q->type = CPprog::PSkip;
;}
    break;

  case 93:
#line 534 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-6].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-6].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-6].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PIf;
  (yyval.prog)->val.upif.b = (yyvsp[-5].expr);
  (yyval.prog)->val.upif.p = (yyvsp[-3].prog);
  (yyval.prog)->val.upif.q = (yyvsp[-1].prog);
;}
    break;

  case 94:
#line 544 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-3].token).position.nb_lignes, (yyvsp[0].prog)->position.fin_ligne, (yyvsp[-3].token).position.nb_char_ligne, (yyvsp[0].prog)->position.fin_car, (yyvsp[-3].token).position.nb_char_tot, (yyvsp[0].prog)->position.fin_car_tot);
  (yyval.prog)->type = CPprog::PWhile;
  (yyval.prog)->val.upwhile.b = (yyvsp[-2].expr);
  (yyval.prog)->val.upwhile.p = (yyvsp[0].prog);
;}
    break;

  case 95:
#line 553 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-7].token).position.nb_lignes, (yyvsp[0].prog)->position.fin_ligne, (yyvsp[-7].token).position.nb_char_ligne, (yyvsp[0].prog)->position.fin_car, (yyvsp[-7].token).position.nb_char_tot, (yyvsp[0].prog)->position.fin_car_tot);
  (yyval.prog)->type = CPprog::PFor;
  (yyval.prog)->val.upfor.i = (yyvsp[-6].token).val.ident;
  (yyval.prog)->val.upfor.e1 = (yyvsp[-4].expr);
  (yyval.prog)->val.upfor.e2 = (yyvsp[-2].expr);
  (yyval.prog)->val.upfor.p = (yyvsp[0].prog);
;}
    break;

  case 96:
#line 564 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-3].token).position.nb_lignes, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-3].token).position.nb_char_ligne, (yyvsp[0].expr)->position.fin_car, (yyvsp[-3].token).position.nb_char_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.prog)->type = CPprog::PRepeat;
  (yyval.prog)->val.uprepeat.b = (yyvsp[0].expr);
  (yyval.prog)->val.uprepeat.p = (yyvsp[-2].prog);
;}
    break;

  case 97:
#line 573 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-3].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-3].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-3].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PWrite;
  (yyval.prog)->val.upwrite.le = (yyvsp[-1].lexpr);
;}
    break;

  case 98:
#line 580 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-3].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-3].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-3].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PWriteln;
  (yyval.prog)->val.upwriteln.le = (yyvsp[-1].lexpr);
;}
    break;

  case 99:
#line 587 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-3].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-3].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-3].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PRead;
  (yyval.prog)->val.upread.llval = (yyvsp[-1].lexpr);
;}
    break;

  case 100:
#line 594 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-3].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-3].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-3].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PReadln;
  (yyval.prog)->val.upreadln.llval = (yyvsp[-1].lexpr);
;}
    break;

  case 101:
#line 602 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-3].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-3].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-3].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PNew;
  (yyval.prog)->val.upnew.ident = (yyvsp[-1].token).val.ident;
;}
    break;

  case 102:
#line 610 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-3].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-3].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-3].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PMusique;
  (yyval.prog)->val.upmusique.musique = (yyvsp[-1].expr);
;}
    break;

  case 103:
#line 618 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-3].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-3].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-3].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PWait;
  (yyval.prog)->val.upwait.nbpasses = (yyvsp[-1].expr);
;}
    break;

  case 104:
#line 626 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-3].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-3].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-3].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PFondu;
  (yyval.prog)->val.upfondu.couleur = (yyvsp[-1].expr);
;}
    break;

  case 105:
#line 635 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-9].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-9].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-9].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PCarte;
  (yyval.prog)->val.upcarte.nom = (yyvsp[-7].expr);
  (yyval.prog)->val.upcarte.x = (yyvsp[-5].expr);
  (yyval.prog)->val.upcarte.y = (yyvsp[-3].expr);
  (yyval.prog)->val.upcarte.direction = (yyvsp[-1].expr);
;}
    break;

  case 106:
#line 645 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-11].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-11].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-11].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PCarteZ;
  (yyval.prog)->val.upcartez.nom = (yyvsp[-9].expr);
  (yyval.prog)->val.upcartez.x = (yyvsp[-7].expr);
  (yyval.prog)->val.upcartez.y = (yyvsp[-5].expr);
  (yyval.prog)->val.upcartez.z = (yyvsp[-3].expr);
  (yyval.prog)->val.upcartez.direction = (yyvsp[-1].expr);
;}
    break;

  case 107:
#line 657 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-9].expr)->position.deb_ligne, (yyvsp[0].token).position.nb_lignes, (yyvsp[-9].expr)->position.deb_car, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-9].expr)->position.deb_car_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  (yyval.prog)->type = CPprog::PSetPosition;
  (yyval.prog)->val.upsetpos.nom = (yyvsp[-9].expr);
  (yyval.prog)->val.upsetpos.x = (yyvsp[-5].expr);
  (yyval.prog)->val.upsetpos.y = (yyvsp[-3].expr);
  (yyval.prog)->val.upsetpos.relatif = (yyvsp[-1].expr);
;}
    break;

  case 108:
#line 670 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-11].expr)->position.deb_ligne, (yyvsp[0].token).position.nb_lignes, (yyvsp[-11].expr)->position.deb_car, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-11].expr)->position.deb_car_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  (yyval.prog)->type = CPprog::PSetPositionZ;
  (yyval.prog)->val.upsetposz.nom = (yyvsp[-11].expr);
  (yyval.prog)->val.upsetposz.x = (yyvsp[-7].expr);
  (yyval.prog)->val.upsetposz.y = (yyvsp[-5].expr);
  (yyval.prog)->val.upsetposz.z = (yyvsp[-3].expr);
  (yyval.prog)->val.upsetposz.relatif = (yyvsp[-1].expr);
;}
    break;

  case 109:
#line 684 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-4].expr)->position.deb_ligne, (yyvsp[0].token).position.nb_lignes, (yyvsp[-4].expr)->position.deb_car, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-4].expr)->position.deb_car_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  (yyval.prog)->type = CPprog::PFrapper;
  (yyval.prog)->val.upfrapper.nom = (yyvsp[-4].expr);
;}
    break;

  case 110:
#line 694 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-9].expr)->position.deb_ligne, (yyvsp[0].token).position.nb_lignes, (yyvsp[-9].expr)->position.deb_car, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-9].expr)->position.deb_car_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  (yyval.prog)->type = CPprog::PDeplacer;
  (yyval.prog)->val.updeplacer.nom = (yyvsp[-9].expr);
  (yyval.prog)->val.updeplacer.x = (yyvsp[-5].expr);
  (yyval.prog)->val.updeplacer.y = (yyvsp[-3].expr);
  (yyval.prog)->val.updeplacer.relatif = (yyvsp[-1].expr);
;}
    break;

  case 111:
#line 706 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-4].expr)->position.deb_ligne, (yyvsp[0].token).position.nb_lignes, (yyvsp[-4].expr)->position.deb_car, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-4].expr)->position.deb_car_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  (yyval.prog)->type = CPprog::PSupObjet;
  (yyval.prog)->val.upsupobjet.nom = (yyvsp[-4].expr);
;}
    break;

  case 112:
#line 716 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-4].expr)->position.deb_ligne, (yyvsp[0].token).position.nb_lignes, (yyvsp[-4].expr)->position.deb_car, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-4].expr)->position.deb_car_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  (yyval.prog)->type = CPprog::PRecArme;
  (yyval.prog)->val.uprecarme.nom = (yyvsp[-4].expr);
;}
    break;

  case 113:
#line 724 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-5].expr)->position.deb_ligne, (yyvsp[0].token).position.nb_lignes, (yyvsp[-5].expr)->position.deb_car, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-5].expr)->position.deb_car_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  (yyval.prog)->type = CPprog::PSetOrientation;
  (yyval.prog)->val.upsetorientation.nom = (yyvsp[-5].expr);
  (yyval.prog)->val.upsetorientation.orientation = (yyvsp[-1].expr);  
;}
    break;

  case 114:
#line 734 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-5].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-5].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-5].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PAjouterAnime;
  (yyval.prog)->val.upajouteranime.nom = (yyvsp[-3].expr);
  (yyval.prog)->val.upajouteranime.fichier = (yyvsp[-1].expr);
;}
    break;

  case 115:
#line 743 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-5].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-5].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-5].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PAjouterNonAnime;
  (yyval.prog)->val.upajouternonanime.nom = (yyvsp[-3].expr);
  (yyval.prog)->val.upajouternonanime.fichier = (yyvsp[-1].expr);
;}
    break;

  case 116:
#line 752 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-3].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-3].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-3].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PSetTemps;
  (yyval.prog)->val.upsettemps.temps = (yyvsp[-1].expr);
;}
    break;

  case 117:
#line 760 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-3].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-3].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-3].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PWaitFor;
  (yyval.prog)->val.upwaitfor.nom = (yyvsp[-1].expr);
;}
    break;

  case 118:
#line 768 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-2].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-2].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-2].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PBloquerTemps;
;}
    break;

  case 119:
#line 774 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-2].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-2].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-2].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PDebloquerTemps;
;}
    break;

  case 120:
#line 782 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 121:
#line 783 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 122:
#line 784 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 123:
#line 785 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 124:
#line 786 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 125:
#line 787 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[0].prog); ;}
    break;

  case 126:
#line 791 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-4].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-4].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-4].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PCameraDefaut;
;}
    break;

  case 127:
#line 798 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-4].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-4].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-4].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PCameraSolidariser;
;}
    break;

  case 128:
#line 805 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-4].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-4].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-4].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PCameraDesolidariser;
;}
    break;

  case 129:
#line 814 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-11].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-11].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-11].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PSetCameraPosition;
  (yyval.prog)->val.upsetcamerapos.x = (yyvsp[-7].expr);
  (yyval.prog)->val.upsetcamerapos.y = (yyvsp[-5].expr);
  (yyval.prog)->val.upsetcamerapos.z = (yyvsp[-3].expr);
  (yyval.prog)->val.upsetcamerapos.relatif = (yyvsp[-1].expr);
;}
    break;

  case 130:
#line 825 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-11].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-11].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-11].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PCameraRotate;
  (yyval.prog)->val.upcamerarotate.angle_x = (yyvsp[-7].expr);
  (yyval.prog)->val.upcamerarotate.angle_y = (yyvsp[-5].expr);
  (yyval.prog)->val.upcamerarotate.angle_z = (yyvsp[-3].expr);
  (yyval.prog)->val.upcamerarotate.relatif = (yyvsp[-1].expr);
;}
    break;

  case 131:
#line 836 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-5].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-5].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-5].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PCameraZoom;
  (yyval.prog)->val.upcamerazoom.coeff = (yyvsp[-1].expr);
;}
    break;

  case 132:
#line 850 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[-3].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-3].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-3].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.prog)->type = CPprog::PCall;
  (yyval.prog)->val.upcall.ident = (yyvsp[-3].token).val.ident;
  (yyval.prog)->val.upcall.args = (yyvsp[-1].lexpr);
;}
    break;

  case 133:
#line 859 "pascal.parser.y"
    { /* !!!!!!!!!!!!!!!!!! */
  (yyval.expr) = new CPexpr((yyvsp[-3].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-3].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-3].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.expr)->type = CPexpr::PCall; 
  (yyval.expr)->val.upcall.ident = (yyvsp[-3].token).val.ident;
  (yyval.expr)->val.upcall.args = (yyvsp[-1].lexpr);
;}
    break;

  case 134:
#line 868 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-2].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-2].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-2].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur);
  (yyval.expr)->type = CPexpr::PNomCarte; 
;}
    break;

  case 135:
#line 874 "pascal.parser.y"
    { (yyval.lexpr) = mp((yyvsp[-1].expr), (yyvsp[0].lexpr)); ;}
    break;

  case 136:
#line 875 "pascal.parser.y"
    { (yyval.lexpr) = (class pliste<CPexpr> *)NULL; ;}
    break;

  case 137:
#line 879 "pascal.parser.y"
    { (yyval.lexpr) = mp((yyvsp[-1].expr), (yyvsp[0].lexpr)); ;}
    break;

  case 138:
#line 880 "pascal.parser.y"
    { (yyval.lexpr) = (class pliste<CPexpr> *)NULL; ;}
    break;

  case 139:
#line 884 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[0].expr); ;}
    break;

  case 140:
#line 890 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-2].expr)->position.deb_ligne, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-2].expr)->position.deb_car, (yyvsp[0].expr)->position.fin_car, (yyvsp[-2].expr)->position.deb_car_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::POu;
  (yyval.expr)->val.upou.e1 = (yyvsp[-2].expr);
  (yyval.expr)->val.upou.e2 = (yyvsp[0].expr);
;}
    break;

  case 141:
#line 896 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-2].expr)->position.deb_ligne, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-2].expr)->position.deb_car, (yyvsp[0].expr)->position.fin_car, (yyvsp[-2].expr)->position.deb_car_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PEt;
  (yyval.expr)->val.upet.e1 = (yyvsp[-2].expr);
  (yyval.expr)->val.upet.e2 = (yyvsp[0].expr);
;}
    break;

  case 142:
#line 902 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[0].expr); ;}
    break;

  case 143:
#line 907 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-2].expr)->position.deb_ligne, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-2].expr)->position.deb_car, (yyvsp[0].expr)->position.fin_car, (yyvsp[-2].expr)->position.deb_car_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PEqual;
  (yyval.expr)->val.upequal.e1 = (yyvsp[-2].expr);
  (yyval.expr)->val.upequal.e2 = (yyvsp[0].expr);
;}
    break;

  case 144:
#line 913 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-2].expr)->position.deb_ligne, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-2].expr)->position.deb_car, (yyvsp[0].expr)->position.fin_car, (yyvsp[-2].expr)->position.deb_car_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PDiff;
  (yyval.expr)->val.updiff.e1 = (yyvsp[-2].expr);
  (yyval.expr)->val.updiff.e2 = (yyvsp[0].expr);
;}
    break;

  case 145:
#line 919 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-2].expr)->position.deb_ligne, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-2].expr)->position.deb_car, (yyvsp[0].expr)->position.fin_car, (yyvsp[-2].expr)->position.deb_car_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PInf;
  (yyval.expr)->val.upinf.e1 = (yyvsp[-2].expr);
  (yyval.expr)->val.upinf.e2 = (yyvsp[0].expr);
;}
    break;

  case 146:
#line 925 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-2].expr)->position.deb_ligne, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-2].expr)->position.deb_car, (yyvsp[0].expr)->position.fin_car, (yyvsp[-2].expr)->position.deb_car_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PSup;
  (yyval.expr)->val.upsup.e1 = (yyvsp[-2].expr);
  (yyval.expr)->val.upsup.e2 = (yyvsp[0].expr);
;}
    break;

  case 147:
#line 931 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-2].expr)->position.deb_ligne, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-2].expr)->position.deb_car, (yyvsp[0].expr)->position.fin_car, (yyvsp[-2].expr)->position.deb_car_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PInfEq;
  (yyval.expr)->val.upinfeq.e1 = (yyvsp[-2].expr);
  (yyval.expr)->val.upinfeq.e2 = (yyvsp[0].expr);
;}
    break;

  case 148:
#line 937 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-2].expr)->position.deb_ligne, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-2].expr)->position.deb_car, (yyvsp[0].expr)->position.fin_car, (yyvsp[-2].expr)->position.deb_car_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PSupEq;
  (yyval.expr)->val.upsupeq.e1 = (yyvsp[-2].expr);
  (yyval.expr)->val.upsupeq.e2 = (yyvsp[0].expr);
;}
    break;

  case 149:
#line 943 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[0].expr); ;}
    break;

  case 150:
#line 947 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-2].expr)->position.deb_ligne, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-2].expr)->position.deb_car, (yyvsp[0].expr)->position.fin_car, (yyvsp[-2].expr)->position.deb_car_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PIPlus;
  (yyval.expr)->val.upiplus.e1 = (yyvsp[-2].expr);
  (yyval.expr)->val.upiplus.e2 = (yyvsp[0].expr);
;}
    break;

  case 151:
#line 953 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-2].expr)->position.deb_ligne, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-2].expr)->position.deb_car, (yyvsp[0].expr)->position.fin_car, (yyvsp[-2].expr)->position.deb_car_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PIMoins;
  (yyval.expr)->val.upimoins.e1 = (yyvsp[-2].expr);
  (yyval.expr)->val.upimoins.e2 = (yyvsp[0].expr);
;}
    break;

  case 152:
#line 959 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-2].expr)->position.deb_ligne, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-2].expr)->position.deb_car, (yyvsp[0].expr)->position.fin_car, (yyvsp[-2].expr)->position.deb_car_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PRPlus;
  (yyval.expr)->val.uprplus.e1 = (yyvsp[-2].expr);
  (yyval.expr)->val.uprplus.e2 = (yyvsp[0].expr);
;}
    break;

  case 153:
#line 965 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-2].expr)->position.deb_ligne, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-2].expr)->position.deb_car, (yyvsp[0].expr)->position.fin_car, (yyvsp[-2].expr)->position.deb_car_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PRMoins;
  (yyval.expr)->val.uprmoins.e1 = (yyvsp[-2].expr);
  (yyval.expr)->val.uprmoins.e2 = (yyvsp[0].expr);
;}
    break;

  case 154:
#line 971 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[0].expr); ;}
    break;

  case 155:
#line 975 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-2].expr)->position.deb_ligne, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-2].expr)->position.deb_car, (yyvsp[0].expr)->position.fin_car, (yyvsp[-2].expr)->position.deb_car_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PIMult;
  (yyval.expr)->val.upimult.e1 = (yyvsp[-2].expr);
  (yyval.expr)->val.upimult.e2 = (yyvsp[0].expr);
;}
    break;

  case 156:
#line 981 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-2].expr)->position.deb_ligne, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-2].expr)->position.deb_car, (yyvsp[0].expr)->position.fin_car, (yyvsp[-2].expr)->position.deb_car_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PIDiv;
  (yyval.expr)->val.upidiv.e1 = (yyvsp[-2].expr);
  (yyval.expr)->val.upidiv.e2 = (yyvsp[0].expr);
;}
    break;

  case 157:
#line 987 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-2].expr)->position.deb_ligne, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-2].expr)->position.deb_car, (yyvsp[0].expr)->position.fin_car, (yyvsp[-2].expr)->position.deb_car_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PIMod;
  (yyval.expr)->val.upimod.e1 = (yyvsp[-2].expr);
  (yyval.expr)->val.upimod.e2 = (yyvsp[0].expr);
;}
    break;

  case 158:
#line 993 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-2].expr)->position.deb_ligne, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-2].expr)->position.deb_car, (yyvsp[0].expr)->position.fin_car, (yyvsp[-2].expr)->position.deb_car_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PRMult;
  (yyval.expr)->val.uprmult.e1 = (yyvsp[-2].expr);
  (yyval.expr)->val.uprmult.e2 = (yyvsp[0].expr);
;}
    break;

  case 159:
#line 999 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-2].expr)->position.deb_ligne, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-2].expr)->position.deb_car, (yyvsp[0].expr)->position.fin_car, (yyvsp[-2].expr)->position.deb_car_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PRDiv;
  (yyval.expr)->val.uprdiv.e1 = (yyvsp[-2].expr);
  (yyval.expr)->val.uprdiv.e2 = (yyvsp[0].expr);
;}
    break;

  case 160:
#line 1005 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[0].expr); ;}
    break;

  case 161:
#line 1009 "pascal.parser.y"
    { 
  (yyval.expr) = new CPexpr((yyvsp[-1].token).position.nb_lignes, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-1].token).position.nb_char_ligne, (yyvsp[0].expr)->position.fin_car, (yyvsp[-1].token).position.nb_char_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PNot;
  (yyval.expr)->val.upnot.e = (yyvsp[0].expr);
;}
    break;

  case 162:
#line 1014 "pascal.parser.y"
    { 
  (yyval.expr) = new CPexpr((yyvsp[-1].token).position.nb_lignes, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-1].token).position.nb_char_ligne, (yyvsp[0].expr)->position.fin_car, (yyvsp[-1].token).position.nb_char_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PUIPlus;
  (yyval.expr)->val.upuiplus.e = (yyvsp[0].expr);
;}
    break;

  case 163:
#line 1019 "pascal.parser.y"
    { 
  (yyval.expr) = new CPexpr((yyvsp[-1].token).position.nb_lignes, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-1].token).position.nb_char_ligne, (yyvsp[0].expr)->position.fin_car, (yyvsp[-1].token).position.nb_char_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PUIMoins;
  (yyval.expr)->val.upuimoins.e = (yyvsp[0].expr);
;}
    break;

  case 164:
#line 1024 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-1].token).position.nb_lignes, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-1].token).position.nb_char_ligne, (yyvsp[0].expr)->position.fin_car, (yyvsp[-1].token).position.nb_char_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PURPlus;
  (yyval.expr)->val.upurplus.e = (yyvsp[0].expr);
;}
    break;

  case 165:
#line 1029 "pascal.parser.y"
    { 
  (yyval.expr) = new CPexpr((yyvsp[-1].token).position.nb_lignes, (yyvsp[0].expr)->position.fin_ligne, (yyvsp[-1].token).position.nb_char_ligne, (yyvsp[0].expr)->position.fin_car, (yyvsp[-1].token).position.nb_char_tot, (yyvsp[0].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PURMoins;
  (yyval.expr)->val.upurmoins.e = (yyvsp[0].expr);
;}
    break;

  case 166:
#line 1034 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[0].expr); ;}
    break;

  case 167:
#line 1038 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-1].expr)->position.deb_ligne, (yyvsp[0].token).position.nb_lignes, (yyvsp[-1].expr)->position.deb_car, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-1].expr)->position.deb_car_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur); 
  (yyval.expr)->type = CPexpr::PInd;
  (yyval.expr)->val.upind.e = (yyvsp[-1].expr);
;}
    break;

  case 168:
#line 1043 "pascal.parser.y"
    { 
  (yyval.expr) = new CPexpr((yyvsp[-3].expr)->position.deb_ligne, (yyvsp[0].token).position.nb_lignes, (yyvsp[-3].expr)->position.deb_car, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-3].expr)->position.deb_car_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur); 
  (yyval.expr)->type = CPexpr::PTab;
  (yyval.expr)->val.uptab.e1 = (yyvsp[-3].expr);
  (yyval.expr)->val.uptab.e2 = (yyvsp[-1].expr);
;}
    break;

  case 169:
#line 1049 "pascal.parser.y"
    {/*!!!!!!!!!!!!!*/
  (yyval.expr) = new CPexpr((yyvsp[-2].expr)->position.deb_ligne, (yyvsp[0].token).position.nb_lignes, (yyvsp[-2].expr)->position.deb_car, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-2].expr)->position.deb_car_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur); 
  (yyval.expr)->type = CPexpr::PRecord; 
  (yyval.expr)->val.uprecord.e = (yyvsp[-2].expr);
  (yyval.expr)->val.uprecord.champ = (yyvsp[0].token).val.ident;
;}
    break;

  case 170:
#line 1055 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[0].expr); ;}
    break;

  case 171:
#line 1059 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[0].expr); ;}
    break;

  case 172:
#line 1060 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[0].expr); ;}
    break;

  case 173:
#line 1061 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[0].expr); ;}
    break;

  case 174:
#line 1065 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[0].expr); ;}
    break;

  case 175:
#line 1066 "pascal.parser.y"
    { 
  /* !!!!  */ 
  //$$ = $2; 
  /*
  $$->position = *(new pascal_position($1.position.nb_lignes, $3.position.nb_lignes, $1.position.nb_char_ligne, $3.position.nb_char_ligne + $3.position.longueur, $1.position.nb_char_tot, $3.position.nb_char_tot + $3.position.longueur));
  */
  (yyval.expr) = (yyvsp[-1].expr);
;}
    break;

  case 176:
#line 1081 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[0].expr); ;}
    break;

  case 177:
#line 1082 "pascal.parser.y"
    { 
  (yyval.expr) = new CPexpr((yyvsp[0].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[0].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[0].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur); 
  (yyval.expr)->type = CPexpr::PConst; 
  (yyval.expr)->val.upconst.pconst.type.type = pevaltype::PETInteger; 
  (yyval.expr)->val.upconst.pconst.val.val.i = (yyvsp[0].token).val.entier; 
;}
    break;

  case 178:
#line 1088 "pascal.parser.y"
    { 
  (yyval.expr) = new CPexpr((yyvsp[0].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[0].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[0].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur); 
  (yyval.expr)->type = CPexpr::PConst; 
  (yyval.expr)->val.upconst.pconst.type.type = pevaltype::PETReal; 
  (yyval.expr)->val.upconst.pconst.val.val.r = (yyvsp[0].token).val.reel; 
;}
    break;

  case 179:
#line 1094 "pascal.parser.y"
    { 
  (yyval.expr) = new CPexpr((yyvsp[0].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[0].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[0].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur); 
  (yyval.expr)->type = CPexpr::PConst; 
  (yyval.expr)->val.upconst.pconst.type.type = pevaltype::PETString; 
  (yyval.expr)->val.upconst.pconst.val.val.str = (yyvsp[0].token).val.chaine; 
;}
    break;

  case 180:
#line 1100 "pascal.parser.y"
    { 
  (yyval.expr) = new CPexpr((yyvsp[0].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[0].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[0].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur); 
  (yyval.expr)->type = CPexpr::PIdent; 
  (yyval.expr)->val.upident.pident = (yyvsp[0].token).val.ident;
;}
    break;

  case 181:
#line 1105 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[0].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[0].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[0].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur); 
  (yyval.expr)->type = CPexpr::PConst; 
  (yyval.expr)->val.upconst.pconst.type.type = pevaltype::PETPointer;
  (yyval.expr)->val.upconst.pconst.type.val.ptr = new pevaltype;
  (yyval.expr)->val.upconst.pconst.type.val.ptr->type = pevaltype::PETVide;
  (yyval.expr)->val.upconst.pconst.val.val.ptr = 0;
;}
    break;

  case 182:
#line 1113 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[-6].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[-6].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[-6].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur); 
  (yyval.expr)->type = CPexpr::PMenu;
  (yyval.expr)->val.upmenu.nom = (yyvsp[-4].token).val.chaine;
  (yyval.expr)->val.upmenu.pitems = (yyvsp[-1].pitems);
;}
    break;

  case 183:
#line 1122 "pascal.parser.y"
    { 
    (yyval.expr) = new CPexpr((yyvsp[0].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[0].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[0].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur); 
    (yyval.expr)->type = CPexpr::PConst; 
    (yyval.expr)->val.upconst.pconst.type.type = pevaltype::PETBoolean; 
    (yyval.expr)->val.upconst.pconst.val.val.b = true; 
  ;}
    break;

  case 184:
#line 1128 "pascal.parser.y"
    { 
    (yyval.expr) = new CPexpr((yyvsp[0].token).position.nb_lignes, (yyvsp[0].token).position.nb_lignes, (yyvsp[0].token).position.nb_char_ligne, (yyvsp[0].token).position.nb_char_ligne + (yyvsp[0].token).position.longueur, (yyvsp[0].token).position.nb_char_tot, (yyvsp[0].token).position.nb_char_tot + (yyvsp[0].token).position.longueur); 
    (yyval.expr)->type = CPexpr::PConst; 
    (yyval.expr)->val.upconst.pconst.type.type = pevaltype::PETBoolean; 
    (yyval.expr)->val.upconst.pconst.val.val.b = false; 
  ;}
    break;

  case 185:
#line 1139 "pascal.parser.y"
    { (yyval.pitems) = mp((yyvsp[-1].item), (yyvsp[0].pitems)); ;}
    break;

  case 186:
#line 1140 "pascal.parser.y"
    { (yyval.pitems) = mp((yyvsp[0].item), (class pliste<struct CPexpr::utype::SPMenu::item> *)NULL); ;}
    break;

  case 187:
#line 1141 "pascal.parser.y"
    { (yyval.pitems) = (class pliste<struct CPexpr::utype::SPMenu::item> *)NULL; ;}
    break;

  case 188:
#line 1145 "pascal.parser.y"
    { (yyval.pitems) = mp((yyvsp[-1].item), (yyvsp[0].pitems)); ;}
    break;

  case 189:
#line 1146 "pascal.parser.y"
    { (yyval.pitems) = (yyvsp[0].pitems); ;}
    break;

  case 190:
#line 1147 "pascal.parser.y"
    { (yyval.pitems) = mp((yyvsp[0].item), (class pliste<struct CPexpr::utype::SPMenu::item> *)NULL); ;}
    break;

  case 191:
#line 1148 "pascal.parser.y"
    { (yyval.pitems) = (class pliste<struct CPexpr::utype::SPMenu::item> *)NULL; ;}
    break;

  case 192:
#line 1152 "pascal.parser.y"
    { (yyval.item) = (yyvsp[0].item); ;}
    break;

  case 193:
#line 1153 "pascal.parser.y"
    { (yyval.item) = (yyvsp[0].item); ;}
    break;

  case 194:
#line 1157 "pascal.parser.y"
    {
  (yyval.item) = new CPexpr::utype::SPMenu::item;
  (yyval.item)->message = (yyvsp[-1].token).val.chaine;
  (yyval.item)->iconfile = NULL;
;}
    break;

  case 195:
#line 1165 "pascal.parser.y"
    {
  (yyval.item) = new CPexpr::utype::SPMenu::item;
  (yyval.item)->message = (yyvsp[-3].token).val.chaine;
  (yyval.item)->iconfile = (yyvsp[-1].token).val.chaine;
;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 3287 "pascal.parser.cpp"

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
	  int yytype = YYTRANSLATE (yychar);
	  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
	  YYSIZE_T yysize = yysize0;
	  YYSIZE_T yysize1;
	  int yysize_overflow = 0;
	  char *yymsg = 0;
#	  define YYERROR_VERBOSE_ARGS_MAXIMUM 5
	  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
	  int yyx;

#if 0
	  /* This is so xgettext sees the translatable formats that are
	     constructed on the fly.  */
	  YY_("syntax error, unexpected %s");
	  YY_("syntax error, unexpected %s, expecting %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
#endif
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
	  int yychecklim = YYLAST - yyn;
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
		yysize_overflow |= yysize1 < yysize;
		yysize = yysize1;
		yyfmt = yystpcpy (yyfmt, yyprefix);
		yyprefix = yyor;
	      }

	  yyf = YY_(yyformat);
	  yysize1 = yysize + yystrlen (yyf);
	  yysize_overflow |= yysize1 < yysize;
	  yysize = yysize1;

	  if (!yysize_overflow && yysize <= YYSTACK_ALLOC_MAXIMUM)
	    yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg)
	    {
	      /* Avoid sprintf, as that infringes on the user's name space.
		 Don't have undefined behavior even if the translation
		 produced a string with the wrong number of "%s"s.  */
	      char *yyp = yymsg;
	      int yyi = 0;
	      while ((*yyp = *yyf))
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
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    {
	      yyerror (YY_("syntax error"));
	      goto yyexhaustedlab;
	    }
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (YY_("syntax error"));
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
	  yydestruct ("Error: discarding", yytoken, &yylval);
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
  if (0)
     goto yyerrorlab;

yyvsp -= yylen;
  yyssp -= yylen;
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


      yydestruct ("Error: popping", yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token. */
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
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK;
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 1177 "pascal.parser.y"




static const void yyerror(char s[]) {
  //(void) printf("Erreur PARSING.");
  pmesserr("Erreur d'analyse syntaxique.");
  (void) fprintf(yypascalout, "Erreur d'analyse syntaxique.");
}

