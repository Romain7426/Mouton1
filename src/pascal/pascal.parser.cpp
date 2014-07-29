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
     TOKEN_REF = 285,
     TOKEN_TYPE = 286,
     TOKEN_BOOLEAN = 287,
     TOKEN_INTEGER = 288,
     TOKEN_SUBRANGE = 289,
     TOKEN_REAL = 290,
     TOKEN_STRING = 291,
     TOKEN_ARRAY = 292,
     TOKEN_OF = 293,
     TOKEN_RECORD = 294,
     TOKEN_PTVIRG = 295,
     TOKEN_AFFECTATION = 296,
     TOKEN_IF = 297,
     TOKEN_THEN = 298,
     TOKEN_ELSE = 299,
     TOKEN_WHILE = 300,
     TOKEN_DO = 301,
     TOKEN_FOR = 302,
     TOKEN_TO = 303,
     TOKEN_REPEAT = 304,
     TOKEN_UNTIL = 305,
     TOKEN_BEGIN = 306,
     TOKEN_END = 307,
     TOKEN_WRITE = 308,
     TOKEN_WRITELN = 309,
     TOKEN_READ = 310,
     TOKEN_READLN = 311,
     TOKEN_NEW = 312,
     TOKEN_PROCEDURE = 313,
     TOKEN_FUNCTION = 314,
     TOKEN_CONST = 315,
     TOKEN_VAR = 316,
     TOKEN_OPENPAR = 317,
     TOKEN_CLOSEPAR = 318,
     TOKEN_OPENBRACKET = 319,
     TOKEN_CLOSEBRACKET = 320,
     TOKEN_DEUXPOINTS = 321,
     TOKEN_BLANC = 322,
     TOKEN_COMMENT = 323,
     TOKEN_VIRGULE = 324,
     TOKEN_POINT = 325,
     TOKEN_MUSIQUE = 326,
     TOKEN_MENU = 327,
     TOKEN_ITEM = 328,
     TOKEN_FLECHE = 329,
     TOKEN_HEROS = 330,
     TOKEN_CAMERA = 331,
     TOKEN_WAIT = 332,
     TOKEN_HALT = 333,
     TOKEN_RESTART = 334,
     TOKEN_FONDU = 335,
     TOKEN_FRAPPER = 336,
     TOKEN_RECOBJET = 337,
     TOKEN_RECARME = 338,
     TOKEN_SUPOBJET = 339,
     TOKEN_CARTE = 340,
     TOKEN_SETPOSITION = 341,
     TOKEN_SETPOSITIONZ = 342,
     TOKEN_DEPLACER = 343,
     TOKEN_DEPLACERZ = 344,
     TOKEN_ROTATE = 345,
     TOKEN_SOLIDARISER = 346,
     TOKEN_DESOLIDARISER = 347,
     TOKEN_DEFAUT = 348,
     TOKEN_ZOOM = 349,
     TOKEN_AJOUTERANIME = 350,
     TOKEN_AJOUTERNONANIME = 351,
     TOKEN_SETTEMPS = 352,
     TOKEN_SETORIENTATION = 353,
     TOKEN_NOMCARTE = 354,
     TOKEN_WAITFOR = 355,
     TOKEN_BLOQUERTEMPS = 356,
     TOKEN_DEBLOQUERTEMPS = 357,
     TOKEN_CARTEZ = 358
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
#define TOKEN_REF 285
#define TOKEN_TYPE 286
#define TOKEN_BOOLEAN 287
#define TOKEN_INTEGER 288
#define TOKEN_SUBRANGE 289
#define TOKEN_REAL 290
#define TOKEN_STRING 291
#define TOKEN_ARRAY 292
#define TOKEN_OF 293
#define TOKEN_RECORD 294
#define TOKEN_PTVIRG 295
#define TOKEN_AFFECTATION 296
#define TOKEN_IF 297
#define TOKEN_THEN 298
#define TOKEN_ELSE 299
#define TOKEN_WHILE 300
#define TOKEN_DO 301
#define TOKEN_FOR 302
#define TOKEN_TO 303
#define TOKEN_REPEAT 304
#define TOKEN_UNTIL 305
#define TOKEN_BEGIN 306
#define TOKEN_END 307
#define TOKEN_WRITE 308
#define TOKEN_WRITELN 309
#define TOKEN_READ 310
#define TOKEN_READLN 311
#define TOKEN_NEW 312
#define TOKEN_PROCEDURE 313
#define TOKEN_FUNCTION 314
#define TOKEN_CONST 315
#define TOKEN_VAR 316
#define TOKEN_OPENPAR 317
#define TOKEN_CLOSEPAR 318
#define TOKEN_OPENBRACKET 319
#define TOKEN_CLOSEBRACKET 320
#define TOKEN_DEUXPOINTS 321
#define TOKEN_BLANC 322
#define TOKEN_COMMENT 323
#define TOKEN_VIRGULE 324
#define TOKEN_POINT 325
#define TOKEN_MUSIQUE 326
#define TOKEN_MENU 327
#define TOKEN_ITEM 328
#define TOKEN_FLECHE 329
#define TOKEN_HEROS 330
#define TOKEN_CAMERA 331
#define TOKEN_WAIT 332
#define TOKEN_HALT 333
#define TOKEN_RESTART 334
#define TOKEN_FONDU 335
#define TOKEN_FRAPPER 336
#define TOKEN_RECOBJET 337
#define TOKEN_RECARME 338
#define TOKEN_SUPOBJET 339
#define TOKEN_CARTE 340
#define TOKEN_SETPOSITION 341
#define TOKEN_SETPOSITIONZ 342
#define TOKEN_DEPLACER 343
#define TOKEN_DEPLACERZ 344
#define TOKEN_ROTATE 345
#define TOKEN_SOLIDARISER 346
#define TOKEN_DESOLIDARISER 347
#define TOKEN_DEFAUT 348
#define TOKEN_ZOOM 349
#define TOKEN_AJOUTERANIME 350
#define TOKEN_AJOUTERNONANIME 351
#define TOKEN_SETTEMPS 352
#define TOKEN_SETORIENTATION 353
#define TOKEN_NOMCARTE 354
#define TOKEN_WAITFOR 355
#define TOKEN_BLOQUERTEMPS 356
#define TOKEN_DEBLOQUERTEMPS 357
#define TOKEN_CARTEZ 358




/* Copy the first part of user declarations.  */
#line 1 "pascal.parser.y"
 
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
typedef union
#line 34 "pascal.parser.y"
{
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
/* Line 193 of yacc.c.  */
#line 377 "pascal.parser.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 390 "pascal.parser.cpp"

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   516

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  104
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  90
/* YYNRULES -- Number of rules.  */
#define YYNRULES  196
/* YYNRULES -- Number of states.  */
#define YYNSTATES  443

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   358

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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
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
     597,   599,   602,   605,   608,   611,   614,   616,   619,   622,
     627,   631,   633,   635,   637,   639,   641,   645,   647,   649,
     651,   653,   655,   657,   665,   667,   669,   672,   674,   675,
     679,   682,   685,   687,   689,   691,   696
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     105,     0,    -1,   106,     8,    -1,   106,   107,    -1,    -1,
     108,    -1,   111,    -1,   114,    -1,   123,    -1,   124,    -1,
     136,    -1,    60,   109,    -1,   110,   109,    -1,   110,    -1,
       6,    14,   179,    40,    -1,    31,   112,    -1,   113,   112,
      -1,   113,    -1,     6,    14,   118,    40,    -1,    61,   115,
      -1,   115,   116,    -1,   116,    -1,   117,    66,   118,    40,
      -1,   117,    69,     6,    -1,     6,    -1,    32,    -1,    33,
      -1,   179,    34,   179,    -1,    35,    -1,    36,    -1,   119,
      -1,   120,    -1,   121,    -1,     6,    -1,    29,   118,    -1,
      37,    64,   179,    34,   179,    65,    38,   118,    -1,    39,
     122,    52,    -1,   122,     6,    66,   118,    40,    -1,    -1,
      58,     6,    62,   126,    63,    40,   125,   131,    40,    -1,
      59,     6,    62,   126,    63,    66,   118,    40,   125,   131,
      40,    -1,   114,    -1,    -1,   128,   127,    -1,    -1,    40,
     128,   127,    -1,    -1,   129,    -1,   130,    -1,     6,    66,
     118,    -1,    61,     6,    66,   118,    -1,   136,    -1,   133,
     134,    -1,   134,    -1,   133,   134,    40,    -1,   134,    40,
      -1,   135,    -1,   136,    -1,   137,    -1,   138,    -1,   139,
      -1,   140,    -1,   141,    -1,   142,    -1,   143,    -1,   144,
      -1,   145,    -1,   146,    -1,   147,    -1,   173,    -1,   148,
      -1,   149,    -1,   150,    -1,   166,    -1,   151,    -1,   153,
      -1,   154,    -1,   155,    -1,   156,    -1,   157,    -1,   158,
      -1,   160,    -1,   161,    -1,   162,    -1,   159,    -1,   163,
      -1,   165,    -1,   164,    -1,   152,    -1,    -1,    51,   132,
      52,    -1,   179,    41,   179,    -1,    42,   179,    43,   132,
      52,    -1,    42,   179,    43,   132,    44,   132,    52,    -1,
      45,   179,    46,   134,    -1,    47,     6,    41,   179,    48,
     179,    46,   134,    -1,    49,   132,    50,   179,    -1,    53,
      62,   176,    63,    -1,    54,    62,   176,    63,    -1,    55,
      62,   176,    63,    -1,    56,    62,   176,    63,    -1,    57,
      62,     6,    63,    -1,    71,    62,   179,    63,    -1,    77,
      62,   179,    63,    -1,    80,    62,   179,    63,    -1,    85,
      62,   179,    69,   179,    69,   179,    69,   179,    63,    -1,
     103,    62,   179,    69,   179,    69,   179,    69,   179,    69,
     179,    63,    -1,   179,    74,    86,    62,   179,    69,   179,
      69,   179,    63,    -1,   179,    74,    87,    62,   179,    69,
     179,    69,   179,    69,   179,    63,    -1,   179,    74,    81,
      62,    63,    -1,   179,    74,    88,    62,   179,    69,   179,
      69,   179,    63,    -1,   179,    74,    84,    62,    63,    -1,
     179,    74,    83,    62,    63,    -1,   179,    74,    98,    62,
     179,    63,    -1,    95,    62,   179,    69,   179,    63,    -1,
      96,    62,   179,    69,   179,    63,    -1,    97,    62,   179,
      63,    -1,   100,    62,   179,    63,    -1,   101,    62,    63,
      -1,   102,    62,    63,    -1,   167,    -1,   168,    -1,   169,
      -1,   170,    -1,   171,    -1,   172,    -1,    76,    74,    93,
      62,    63,    -1,    76,    74,    91,    62,    63,    -1,    76,
      74,    92,    62,    63,    -1,    76,    74,    86,    62,   179,
      69,   179,    69,   179,    69,   179,    63,    -1,    76,    74,
      90,    62,   179,    69,   179,    69,   179,    69,   179,    63,
      -1,    76,    74,    94,    62,   179,    63,    -1,     6,    62,
     176,    63,    -1,     6,    62,   176,    63,    -1,    99,    62,
      63,    -1,   178,   177,    -1,    -1,    69,   178,   177,    -1,
      -1,   179,    -1,   179,    13,   180,    -1,   179,    12,   180,
      -1,   180,    -1,   180,    14,   181,    -1,   180,    15,   181,
      -1,   180,    16,   181,    -1,   180,    17,   181,    -1,   180,
      18,   181,    -1,   180,    19,   181,    -1,   181,    -1,   181,
      20,   182,    -1,   181,    21,   182,    -1,   181,    25,   182,
      -1,   181,    26,   182,    -1,   182,    -1,   182,    22,   183,
      -1,   182,    23,   183,    -1,   182,    24,   183,    -1,   182,
      27,   183,    -1,   182,    28,   183,    -1,   183,    -1,    11,
     183,    -1,    20,   183,    -1,    21,   183,    -1,    25,   183,
      -1,    26,   183,    -1,   184,    -1,   184,    29,    -1,    30,
     184,    -1,   184,    64,   179,    65,    -1,   184,    70,     6,
      -1,   185,    -1,   174,    -1,   175,    -1,   186,    -1,   187,
      -1,    62,   179,    63,    -1,   188,    -1,     3,    -1,     4,
      -1,     5,    -1,     6,    -1,     7,    -1,    72,    62,     5,
      63,    51,   189,    52,    -1,     9,    -1,    10,    -1,   191,
     190,    -1,   191,    -1,    -1,    40,   191,   190,    -1,    40,
     190,    -1,    40,   191,    -1,    40,    -1,   192,    -1,   193,
      -1,    73,    62,     5,    63,    -1,    73,    62,     5,    69,
       5,    63,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   177,   177,   180,   186,   193,   194,   195,   196,   197,
     198,   202,   206,   212,   216,   225,   229,   235,   239,   249,
     253,   259,   263,   293,   298,   306,   307,   308,   314,   315,
     316,   321,   322,   323,   332,   336,   346,   354,   361,   365,
     383,   402,   403,   410,   411,   415,   416,   420,   421,   425,
     434,   444,   447,   453,   457,   463,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   478,   479,   480,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   503,
     510,   518,   527,   538,   548,   557,   568,   577,   584,   591,
     598,   606,   614,   622,   630,   639,   649,   661,   674,   688,
     698,   710,   720,   728,   738,   747,   756,   764,   772,   778,
     786,   787,   788,   789,   790,   791,   795,   802,   809,   818,
     829,   840,   854,   863,   872,   878,   879,   883,   884,   888,
     894,   900,   906,   911,   917,   923,   929,   935,   941,   947,
     951,   957,   963,   969,   975,   979,   985,   991,   997,  1003,
    1009,  1013,  1018,  1023,  1028,  1033,  1038,  1042,  1047,  1052,
    1058,  1064,  1068,  1069,  1070,  1074,  1075,  1090,  1091,  1097,
    1103,  1109,  1114,  1122,  1131,  1137,  1148,  1149,  1150,  1154,
    1155,  1156,  1157,  1161,  1162,  1166,  1174
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_ENTIER", "TOKEN_REEL",
  "TOKEN_CHAINE", "TOKEN_IDENT", "TOKEN_NIL", "TOKEN_EOF", "TOKEN_TRUE",
  "TOKEN_FALSE", "TOKEN_NOT", "TOKEN_AND", "TOKEN_OR", "TOKEN_EQUAL",
  "TOKEN_DIFF", "TOKEN_INF", "TOKEN_SUP", "TOKEN_INFEQ", "TOKEN_SUPEQ",
  "TOKEN_IPLUS", "TOKEN_IMOINS", "TOKEN_IMULT", "TOKEN_IDIV", "TOKEN_IMOD",
  "TOKEN_RPLUS", "TOKEN_RMOINS", "TOKEN_RMULT", "TOKEN_RDIV", "TOKEN_PTR",
  "TOKEN_REF", "TOKEN_TYPE", "TOKEN_BOOLEAN", "TOKEN_INTEGER",
  "TOKEN_SUBRANGE", "TOKEN_REAL", "TOKEN_STRING", "TOKEN_ARRAY",
  "TOKEN_OF", "TOKEN_RECORD", "TOKEN_PTVIRG", "TOKEN_AFFECTATION",
  "TOKEN_IF", "TOKEN_THEN", "TOKEN_ELSE", "TOKEN_WHILE", "TOKEN_DO",
  "TOKEN_FOR", "TOKEN_TO", "TOKEN_REPEAT", "TOKEN_UNTIL", "TOKEN_BEGIN",
  "TOKEN_END", "TOKEN_WRITE", "TOKEN_WRITELN", "TOKEN_READ",
  "TOKEN_READLN", "TOKEN_NEW", "TOKEN_PROCEDURE", "TOKEN_FUNCTION",
  "TOKEN_CONST", "TOKEN_VAR", "TOKEN_OPENPAR", "TOKEN_CLOSEPAR",
  "TOKEN_OPENBRACKET", "TOKEN_CLOSEBRACKET", "TOKEN_DEUXPOINTS",
  "TOKEN_BLANC", "TOKEN_COMMENT", "TOKEN_VIRGULE", "TOKEN_POINT",
  "TOKEN_MUSIQUE", "TOKEN_MENU", "TOKEN_ITEM", "TOKEN_FLECHE",
  "TOKEN_HEROS", "TOKEN_CAMERA", "TOKEN_WAIT", "TOKEN_HALT",
  "TOKEN_RESTART", "TOKEN_FONDU", "TOKEN_FRAPPER", "TOKEN_RECOBJET",
  "TOKEN_RECARME", "TOKEN_SUPOBJET", "TOKEN_CARTE", "TOKEN_SETPOSITION",
  "TOKEN_SETPOSITIONZ", "TOKEN_DEPLACER", "TOKEN_DEPLACERZ",
  "TOKEN_ROTATE", "TOKEN_SOLIDARISER", "TOKEN_DESOLIDARISER",
  "TOKEN_DEFAUT", "TOKEN_ZOOM", "TOKEN_AJOUTERANIME",
  "TOKEN_AJOUTERNONANIME", "TOKEN_SETTEMPS", "TOKEN_SETORIENTATION",
  "TOKEN_NOMCARTE", "TOKEN_WAITFOR", "TOKEN_BLOQUERTEMPS",
  "TOKEN_DEBLOQUERTEMPS", "TOKEN_CARTEZ", "$accept", "main",
  "liste_declaration", "declaration", "decl_constante",
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
static const yytype_uint16 yytoknum[] =
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
     355,   356,   357,   358
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   104,   105,   106,   106,   107,   107,   107,   107,   107,
     107,   108,   109,   109,   110,   111,   112,   112,   113,   114,
     115,   115,   116,   117,   117,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   119,   120,   121,   122,   122,   123,
     124,   125,   125,   126,   126,   127,   127,   128,   128,   129,
     130,   131,   132,   132,   133,   133,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   166,   166,   166,   166,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   176,   177,   177,   178,
     179,   179,   179,   180,   180,   180,   180,   180,   180,   180,
     181,   181,   181,   181,   181,   182,   182,   182,   182,   182,
     182,   183,   183,   183,   183,   183,   183,   184,   184,   184,
     184,   184,   185,   185,   185,   186,   186,   187,   187,   187,
     187,   187,   187,   187,   188,   188,   189,   189,   189,   190,
     190,   190,   190,   191,   191,   192,   193
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
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
       1,     2,     2,     2,     2,     2,     1,     2,     2,     4,
       3,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     7,     1,     1,     2,     1,     0,     3,
       2,     2,     1,     1,     1,     4,     6
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     1,     2,     0,    89,     0,     0,     0,
       0,     3,     5,     6,     7,     8,     9,    10,     0,    15,
      17,   178,   179,   180,   181,   182,   184,   185,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    89,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    89,
      53,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    70,    71,    72,    74,    88,    75,
      76,    77,    78,    79,    80,    84,    81,    82,    83,    85,
      87,    86,    73,   120,   121,   122,   123,   124,   125,    69,
     172,   173,     0,   142,   149,   154,   160,   166,   171,   174,
     175,   177,     0,     0,     0,    11,    13,    24,    19,    21,
       0,     0,    16,   136,   181,   161,   162,   163,   164,   165,
     168,     0,     0,     0,     0,   136,   136,   136,   136,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    90,    52,    55,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   167,     0,     0,
      44,    44,     0,    12,    20,     0,     0,   181,     0,    25,
      26,    28,    29,     0,    38,     0,    30,    31,    32,     0,
       0,   138,   139,   136,    89,    89,     0,     0,     0,     0,
       0,     0,     0,   176,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   134,     0,
     118,   119,     0,    54,   141,   140,    91,     0,     0,     0,
       0,     0,     0,     0,   143,   144,   145,   146,   147,   148,
     150,   151,   152,   153,   155,   156,   157,   158,   159,     0,
     170,     0,     0,     0,    46,    47,    48,     0,     0,     0,
      23,    34,     0,     0,    18,     0,   133,     0,   135,     0,
       0,    94,     0,    96,    97,    98,    99,   100,   101,   102,
       0,     0,     0,     0,     0,     0,     0,   103,   104,     0,
       0,     0,   116,   117,     0,     0,     0,     0,     0,     0,
       0,     0,   169,     0,     0,     0,     0,    43,     0,    14,
      22,     0,     0,    36,    27,   138,   133,    89,    92,     0,
     188,     0,     0,   127,   128,   126,     0,     0,     0,     0,
       0,   109,   112,   111,     0,     0,     0,     0,    49,     0,
      42,    46,     0,     0,     0,   137,     0,     0,     0,     0,
     187,   193,   194,     0,     0,   131,     0,   114,   115,     0,
       0,     0,     0,   113,    50,    41,     0,    45,     0,     0,
       0,    93,    89,     0,   183,   192,   186,     0,     0,     0,
       0,     0,     0,     0,     0,    51,    42,     0,    37,    95,
       0,   190,   191,     0,     0,     0,     0,     0,     0,     0,
      39,     0,     0,   195,     0,   189,     0,     0,     0,     0,
       0,     0,     0,     0,    35,     0,     0,     0,   105,     0,
     107,     0,   110,    40,   196,     0,     0,     0,     0,   129,
     130,   106,   108
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    11,    12,   115,   116,    13,    19,    20,
     375,   118,   119,   120,   195,   196,   197,   198,   273,    15,
      16,   376,   263,   317,   264,   265,   266,   394,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   200,   278,   201,   199,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   359,   386,   360,   361,   362
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -361
static const yytype_int16 yypact[] =
{
    -361,     7,   216,  -361,  -361,    24,    13,    26,    46,    51,
      53,  -361,  -361,  -361,  -361,  -361,  -361,  -361,    77,  -361,
      24,  -361,  -361,  -361,    49,  -361,  -361,  -361,   200,   200,
     200,   200,   200,   234,   200,   200,   114,    13,    64,    71,
      74,    88,    91,   200,   103,   126,   100,   129,   133,   140,
     146,   150,   153,   174,   180,   199,   203,   206,   211,    13,
     243,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,
    -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,
    -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,
    -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,
    -361,  -361,    32,   444,   431,   416,  -361,    57,  -361,  -361,
    -361,  -361,   220,   225,   264,  -361,    51,  -361,    53,  -361,
      35,   157,  -361,   200,   227,  -361,  -361,  -361,  -361,  -361,
      57,   370,   134,   256,   258,   200,   200,   200,   200,   309,
     247,   200,   327,   356,   200,   200,   200,   200,   200,   200,
     257,   200,   259,   283,   200,  -361,   310,  -361,   200,   200,
     200,   347,   200,   200,   200,   200,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,  -361,   200,   353,
       2,     2,   200,  -361,  -361,   157,   362,    25,   157,  -361,
    -361,  -361,  -361,   285,  -361,   333,  -361,  -361,  -361,   395,
     307,   305,   233,   200,    13,    13,   200,   200,   314,   316,
     318,   323,   329,  -361,   268,   342,   364,   365,   375,   379,
     391,   392,   288,   304,    -8,    14,    23,   306,  -361,   315,
    -361,  -361,    28,  -361,   444,   444,   233,   393,   408,   409,
     410,   411,   412,   413,   431,   431,   431,   431,   431,   431,
     416,   416,   416,   416,  -361,  -361,  -361,  -361,  -361,    87,
    -361,   345,   384,   346,   436,  -361,  -361,   361,   312,   437,
    -361,  -361,   200,     4,  -361,   200,   344,   200,  -361,   369,
      30,  -361,   300,   233,  -361,  -361,  -361,  -361,  -361,  -361,
     427,   200,   200,   417,   418,   419,   200,  -361,  -361,   200,
     200,   200,  -361,  -361,   200,   420,   421,   422,   200,   200,
     200,   200,  -361,   157,   423,   439,     2,  -361,   424,  -361,
    -361,   402,   425,  -361,   233,   305,  -361,    13,  -361,   200,
     414,    34,    36,  -361,  -361,  -361,   317,    38,   322,   324,
      59,  -361,  -361,  -361,    68,    82,   110,   326,  -361,   157,
     432,   436,   157,   200,   157,  -361,   434,   172,   426,   440,
     454,  -361,  -361,   200,   200,  -361,   200,  -361,  -361,   200,
     200,   200,   200,  -361,  -361,  -361,   445,  -361,   455,   106,
     457,  -361,    13,   493,  -361,   -19,  -361,   112,   201,   204,
     210,   215,   219,   222,   459,  -361,   432,   462,  -361,  -361,
      33,  -361,   454,   200,   200,   200,   200,   200,   200,   200,
    -361,   445,   157,  -361,   496,  -361,   238,   240,   328,   242,
     330,   245,   332,   463,  -361,   441,   200,   200,  -361,   200,
    -361,   200,  -361,  -361,  -361,   341,   343,   349,   359,  -361,
    -361,  -361,  -361
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -361,  -361,  -361,  -361,  -361,   386,  -361,  -361,   485,  -361,
     504,  -361,   389,  -361,  -179,  -361,  -361,  -361,  -361,  -361,
    -361,   113,   331,   159,   192,  -361,  -361,   102,   -35,  -361,
     -56,  -361,    -1,  -361,  -361,  -361,  -361,  -361,  -361,  -361,
    -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,
    -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,
    -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,
    -361,  -361,   -59,   186,   237,    -6,    90,   302,   248,   -17,
     482,  -361,  -361,  -361,  -361,  -361,  -360,   131,  -361,  -361
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -133
static const yytype_int16 yytable[] =
{
     102,    17,   134,   156,   158,   159,   269,     3,   261,   271,
     322,   125,   126,   127,   128,   129,    21,    22,    23,    24,
      25,   385,    26,    27,    28,   401,   158,   159,   131,   132,
      18,   102,   112,    29,    30,   158,   159,   140,    31,    32,
     158,   159,   415,    33,   158,   159,   158,   159,   158,   159,
     158,   159,   113,   102,   358,    34,   323,   114,    35,   117,
      36,   299,    37,   262,     6,   -33,    38,    39,    40,    41,
      42,   158,   159,   160,   327,    43,   208,   209,   210,   211,
     158,   159,   328,   300,    44,    45,   177,   203,   -33,    46,
      47,   121,   301,    48,   158,   159,   413,   304,    49,   158,
     159,   185,   414,   363,   186,   364,   161,   366,    50,    51,
      52,   123,    53,    54,    55,    56,    57,   202,   158,   159,
     133,   178,   158,   159,   158,   159,   135,   179,   369,   202,
     202,   202,   202,   136,   348,   214,   137,   370,   222,   223,
     224,   225,   226,   227,   279,   229,   158,   159,   232,   281,
     138,   371,   312,   139,   236,   254,   255,   256,   257,   258,
      21,    22,    23,   187,    25,   141,    26,    27,    28,   280,
     374,   397,   259,   378,   143,   380,   268,    29,    30,   372,
     205,   403,    31,    32,   158,   159,   188,    33,   142,   189,
     190,   144,   191,   192,   193,   145,   194,   202,   102,   102,
     282,   283,   146,    21,    22,    23,   124,    25,   147,    26,
      27,    28,   148,   158,   159,   149,   158,   159,   382,    43,
      29,    30,   158,   159,     4,    31,    32,   158,   159,    45,
      33,   158,   159,   424,   158,   159,   150,    21,    22,    23,
     124,    25,   151,    26,    27,   158,   159,     5,   234,   235,
     158,   159,   158,   159,   158,   159,    53,   158,   159,   158,
     159,   152,    43,   155,    33,   153,   321,     6,   154,   324,
     404,   202,    45,   405,     7,     8,     9,    10,   182,   406,
     158,   159,   180,   157,   407,   331,   332,   181,   408,   203,
     336,   409,   356,   337,   338,   339,    43,   206,   340,    53,
     158,   159,   344,   345,   346,   347,    45,   426,   207,   427,
     213,   429,   158,   159,   431,   212,   158,   159,   158,   159,
     228,   102,   230,   357,   158,   159,   399,   158,   159,   158,
     159,   289,   215,    53,   158,   159,   158,   159,   158,   159,
     158,   159,   158,   159,   158,   159,   231,   379,   329,   272,
     233,   297,   319,   158,   159,   158,   159,   387,   388,   260,
     389,   158,   159,   390,   391,   392,   393,   298,   270,   302,
     276,   158,   159,   274,   277,   395,   102,   284,   303,   285,
     365,   286,   158,   159,  -132,   367,   287,   368,  -132,   373,
     314,   428,   288,   430,  -132,   432,  -132,   416,   417,   418,
     419,   420,   421,   422,   439,   290,   440,   158,   159,   315,
     395,   313,   441,   204,   158,   159,   250,   251,   252,   253,
     435,   436,   442,   437,   318,   438,   291,   292,   237,   275,
     238,   239,   326,   240,   241,   242,   353,   293,   172,   173,
     174,   294,   216,   175,   176,   243,   217,   218,   219,   220,
     221,   168,   169,   295,   296,   305,   170,   171,   162,   163,
     164,   165,   166,   167,   244,   245,   246,   247,   248,   249,
     306,   307,   308,   309,   310,   311,   316,   320,   330,   350,
     333,   334,   335,   341,   342,   343,   381,   358,   383,   349,
     352,   354,   384,    10,   385,   396,     6,   398,   400,   410,
     412,   425,   183,   433,   434,   122,    14,   184,   351,   411,
     377,   355,   267,   423,   325,   130,   402
};

static const yytype_uint16 yycheck[] =
{
       6,     2,    37,    59,    12,    13,   185,     0,     6,   188,
       6,    28,    29,    30,    31,    32,     3,     4,     5,     6,
       7,    40,     9,    10,    11,   385,    12,    13,    34,    35,
       6,    37,     6,    20,    21,    12,    13,    43,    25,    26,
      12,    13,   402,    30,    12,    13,    12,    13,    12,    13,
      12,    13,     6,    59,    73,    42,    52,     6,    45,     6,
      47,    69,    49,    61,    51,    40,    53,    54,    55,    56,
      57,    12,    13,    41,    44,    62,   135,   136,   137,   138,
      12,    13,    52,    69,    71,    72,    29,    62,    63,    76,
      77,    14,    69,    80,    12,    13,    63,    69,    85,    12,
      13,    66,    69,    69,    69,    69,    74,    69,    95,    96,
      97,    62,    99,   100,   101,   102,   103,   123,    12,    13,
       6,    64,    12,    13,    12,    13,    62,    70,    69,   135,
     136,   137,   138,    62,   313,   141,    62,    69,   144,   145,
     146,   147,   148,   149,   203,   151,    12,    13,   154,   205,
      62,    69,    65,    62,   160,   172,   173,   174,   175,   176,
       3,     4,     5,     6,     7,    62,     9,    10,    11,   204,
     349,    65,   178,   352,    74,   354,   182,    20,    21,    69,
      46,    69,    25,    26,    12,    13,    29,    30,    62,    32,
      33,    62,    35,    36,    37,    62,    39,   203,   204,   205,
     206,   207,    62,     3,     4,     5,     6,     7,    62,     9,
      10,    11,    62,    12,    13,    62,    12,    13,    46,    62,
      20,    21,    12,    13,     8,    25,    26,    12,    13,    72,
      30,    12,    13,   412,    12,    13,    62,     3,     4,     5,
       6,     7,    62,     9,    10,    12,    13,    31,   158,   159,
      12,    13,    12,    13,    12,    13,    99,    12,    13,    12,
      13,    62,    62,    52,    30,    62,   272,    51,    62,   275,
      69,   277,    72,    69,    58,    59,    60,    61,    14,    69,
      12,    13,    62,    40,    69,   291,   292,    62,    69,    62,
     296,    69,   327,   299,   300,   301,    62,    41,   304,    99,
      12,    13,   308,   309,   310,   311,    72,    69,    50,    69,
      63,    69,    12,    13,    69,     6,    12,    13,    12,    13,
      63,   327,    63,   329,    12,    13,   382,    12,    13,    12,
      13,    63,     5,    99,    12,    13,    12,    13,    12,    13,
      12,    13,    12,    13,    12,    13,    63,   353,    48,    64,
      40,    63,    40,    12,    13,    12,    13,   363,   364,     6,
     366,    12,    13,   369,   370,   371,   372,    63,     6,    63,
      63,    12,    13,    40,    69,   376,   382,    63,    63,    63,
      63,    63,    12,    13,    40,    63,    63,    63,    44,    63,
       6,    63,    63,    63,    50,    63,    52,   403,   404,   405,
     406,   407,   408,   409,    63,    63,    63,    12,    13,    63,
     411,    66,    63,    43,    12,    13,   168,   169,   170,   171,
     426,   427,    63,   429,    63,   431,    62,    62,    81,    34,
      83,    84,    63,    86,    87,    88,    34,    62,    22,    23,
      24,    62,    86,    27,    28,    98,    90,    91,    92,    93,
      94,    20,    21,    62,    62,    62,    25,    26,    14,    15,
      16,    17,    18,    19,   162,   163,   164,   165,   166,   167,
      62,    62,    62,    62,    62,    62,    40,    40,    51,    40,
      63,    63,    63,    63,    63,    63,    52,    73,    62,    66,
      66,    66,    52,    61,    40,    40,    51,    40,     5,    40,
      38,     5,   116,    40,    63,    20,     2,   118,   316,   396,
     351,   325,   181,   411,   277,    33,   385
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   105,   106,     0,     8,    31,    51,    58,    59,    60,
      61,   107,   108,   111,   114,   123,   124,   136,     6,   112,
     113,     3,     4,     5,     6,     7,     9,    10,    11,    20,
      21,    25,    26,    30,    42,    45,    47,    49,    53,    54,
      55,    56,    57,    62,    71,    72,    76,    77,    80,    85,
      95,    96,    97,    99,   100,   101,   102,   103,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,     6,     6,     6,   109,   110,     6,   115,   116,
     117,    14,   112,    62,     6,   183,   183,   183,   183,   183,
     184,   179,   179,     6,   132,    62,    62,    62,    62,    62,
     179,    62,    62,    74,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    52,   134,    40,    12,    13,
      41,    74,    14,    15,    16,    17,    18,    19,    20,    21,
      25,    26,    22,    23,    24,    27,    28,    29,    64,    70,
      62,    62,    14,   109,   116,    66,    69,     6,    29,    32,
      33,    35,    36,    37,    39,   118,   119,   120,   121,   179,
     176,   178,   179,    62,    43,    46,    41,    50,   176,   176,
     176,   176,     6,    63,   179,     5,    86,    90,    91,    92,
      93,    94,   179,   179,   179,   179,   179,   179,    63,   179,
      63,    63,   179,    40,   180,   180,   179,    81,    83,    84,
      86,    87,    88,    98,   181,   181,   181,   181,   181,   181,
     182,   182,   182,   182,   183,   183,   183,   183,   183,   179,
       6,     6,    61,   126,   128,   129,   130,   126,   179,   118,
       6,   118,    64,   122,    40,    34,    63,    69,   177,   176,
     132,   134,   179,   179,    63,    63,    63,    63,    63,    63,
      63,    62,    62,    62,    62,    62,    62,    63,    63,    69,
      69,    69,    63,    63,    69,    62,    62,    62,    62,    62,
      62,    62,    65,    66,     6,    63,    40,   127,    63,    40,
      40,   179,     6,    52,   179,   178,    63,    44,    52,    48,
      51,   179,   179,    63,    63,    63,   179,   179,   179,   179,
     179,    63,    63,    63,   179,   179,   179,   179,   118,    66,
      40,   128,    66,    34,    66,   177,   132,   179,    73,   189,
     191,   192,   193,    69,    69,    63,    69,    63,    63,    69,
      69,    69,    69,    63,   118,   114,   125,   127,   118,   179,
     118,    52,    46,    62,    52,    40,   190,   179,   179,   179,
     179,   179,   179,   179,   131,   136,    40,    65,    40,   134,
       5,   190,   191,    69,    69,    69,    69,    69,    69,    69,
      40,   125,    38,    63,    69,   190,   179,   179,   179,   179,
     179,   179,   179,   131,   118,     5,    69,    69,    63,    69,
      63,    69,    63,    40,    63,   179,   179,   179,   179,    63,
      63,    63,    63
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
#line 177 "pascal.parser.y"
    { prog = (yyvsp[(1) - (2)].prog); fprintf(yypascalout, "Analyse réussie."); pmessage("Analyse réussie !"); return 0; ;}
    break;

  case 3:
#line 180 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (2)].prog)->position.deb_ligne, (yyvsp[(2) - (2)].prog)->position.fin_ligne, (yyvsp[(1) - (2)].prog)->position.deb_car, (yyvsp[(2) - (2)].prog)->position.fin_car, (yyvsp[(1) - (2)].prog)->position.deb_car_tot, (yyvsp[(2) - (2)].prog)->position.fin_car_tot);
  (yyval.prog)->type = CPprog::PSeq;
  (yyval.prog)->val.upseq.p1 = (yyvsp[(1) - (2)].prog);
  (yyval.prog)->val.upseq.p2 = (yyvsp[(2) - (2)].prog);
;}
    break;

  case 4:
#line 186 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1);
  (yyval.prog)->type = CPprog::PSkip;
;}
    break;

  case 5:
#line 193 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 6:
#line 194 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 7:
#line 195 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 8:
#line 196 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 9:
#line 197 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 10:
#line 198 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 11:
#line 202 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(2) - (2)].prog); ;}
    break;

  case 12:
#line 206 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (2)].prog)->position.deb_ligne, (yyvsp[(2) - (2)].prog)->position.fin_ligne, (yyvsp[(1) - (2)].prog)->position.deb_car, (yyvsp[(2) - (2)].prog)->position.fin_car, (yyvsp[(1) - (2)].prog)->position.deb_car_tot, (yyvsp[(2) - (2)].prog)->position.fin_car_tot);
  (yyval.prog)->type = CPprog::PSeq;
  (yyval.prog)->val.upseq.p1 = (yyvsp[(1) - (2)].prog);
  (yyval.prog)->val.upseq.p2 = (yyvsp[(2) - (2)].prog);
;}
    break;

  case 13:
#line 212 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 14:
#line 216 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (4)].token).position.nb_lignes, (yyvsp[(4) - (4)].token).position.nb_lignes, (yyvsp[(1) - (4)].token).position.nb_char_ligne, (yyvsp[(4) - (4)].token).position.nb_char_ligne + (yyvsp[(4) - (4)].token).position.longueur, (yyvsp[(1) - (4)].token).position.nb_char_tot, (yyvsp[(4) - (4)].token).position.nb_char_tot + (yyvsp[(4) - (4)].token).position.longueur);
  (yyval.prog)->type = CPprog::PConst;
  (yyval.prog)->val.upconst.nom = (yyvsp[(1) - (4)].token).val.ident;
  (yyval.prog)->val.upconst.val = (yyvsp[(3) - (4)].expr);
;}
    break;

  case 15:
#line 225 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(2) - (2)].prog); ;}
    break;

  case 16:
#line 229 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (2)].prog)->position.deb_ligne, (yyvsp[(2) - (2)].prog)->position.fin_ligne, (yyvsp[(1) - (2)].prog)->position.deb_car, (yyvsp[(2) - (2)].prog)->position.fin_car, (yyvsp[(1) - (2)].prog)->position.deb_car_tot, (yyvsp[(2) - (2)].prog)->position.fin_car_tot);
  (yyval.prog)->type = CPprog::PSeq;
  (yyval.prog)->val.upseq.p1 = (yyvsp[(1) - (2)].prog);
  (yyval.prog)->val.upseq.p2 = (yyvsp[(2) - (2)].prog);
;}
    break;

  case 17:
#line 235 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 18:
#line 239 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (4)].token).position.nb_lignes, (yyvsp[(4) - (4)].token).position.nb_lignes, (yyvsp[(1) - (4)].token).position.nb_char_ligne, (yyvsp[(4) - (4)].token).position.nb_char_ligne + (yyvsp[(4) - (4)].token).position.longueur, (yyvsp[(1) - (4)].token).position.nb_char_tot, (yyvsp[(4) - (4)].token).position.nb_char_tot + (yyvsp[(4) - (4)].token).position.longueur);
  (yyval.prog)->type = CPprog::PType;
  (yyval.prog)->val.uptype.ident = (yyvsp[(1) - (4)].token).val.ident;
  (yyval.prog)->val.uptype.dvaltype = *((yyvsp[(3) - (4)].dvaltype));
;}
    break;

  case 19:
#line 249 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(2) - (2)].prog); ;}
    break;

  case 20:
#line 253 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (2)].prog)->position.deb_ligne, (yyvsp[(2) - (2)].prog)->position.fin_ligne, (yyvsp[(1) - (2)].prog)->position.deb_car, (yyvsp[(2) - (2)].prog)->position.fin_car, (yyvsp[(1) - (2)].prog)->position.deb_car_tot, (yyvsp[(2) - (2)].prog)->position.fin_car_tot);
  (yyval.prog)->type = CPprog::PSeq;
  (yyval.prog)->val.upseq.p1 = (yyvsp[(1) - (2)].prog);
  (yyval.prog)->val.upseq.p2 = (yyvsp[(2) - (2)].prog);
;}
    break;

  case 21:
#line 259 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 22:
#line 263 "pascal.parser.y"
    {
  class pliste<struct YYSTYPE::ttoken> *temp = (yyvsp[(1) - (4)].ltoken);
  if (temp == NULL) {
    pmesserr("Dans le parser, à la regle decl_variable1, liste_ident est NULL !!");
    return -1;
  }
  struct YYSTYPE::ttoken *p = temp->a;
  class CPprog *pr, *ps;
  (yyval.prog) = new class CPprog(p->position.nb_lignes, (yyvsp[(4) - (4)].token).position.nb_lignes, p->position.nb_char_ligne, (yyvsp[(4) - (4)].token).position.nb_char_ligne + (yyvsp[(4) - (4)].token).position.longueur, p->position.nb_char_tot, (yyvsp[(4) - (4)].token).position.nb_char_tot + (yyvsp[(4) - (4)].token).position.longueur);
  (yyval.prog)->type = CPprog::PVar;
  (yyval.prog)->val.upvar.nom = p->val.ident;
  (yyval.prog)->val.upvar.t = *((yyvsp[(3) - (4)].dvaltype));
  
  while (temp->suivant != NULL) {
    temp = temp->suivant;
    p = temp->a;
    pr = new class CPprog(p->position.nb_lignes, (yyvsp[(4) - (4)].token).position.nb_lignes, p->position.nb_char_ligne, (yyvsp[(4) - (4)].token).position.nb_char_ligne + (yyvsp[(4) - (4)].token).position.longueur, p->position.nb_char_tot, (yyvsp[(4) - (4)].token).position.nb_char_tot + (yyvsp[(4) - (4)].token).position.longueur);
    pr->type = CPprog::PVar;
    pr->val.upvar.nom = p->val.ident;
    pr->val.upvar.t = *((yyvsp[(3) - (4)].dvaltype));
    ps = (yyval.prog);
    (yyval.prog) = new class CPprog(p->position.nb_lignes, (yyvsp[(4) - (4)].token).position.nb_lignes, p->position.nb_char_ligne, (yyvsp[(4) - (4)].token).position.nb_char_ligne + (yyvsp[(4) - (4)].token).position.longueur, p->position.nb_char_tot, (yyvsp[(4) - (4)].token).position.nb_char_tot + (yyvsp[(4) - (4)].token).position.longueur);
    (yyval.prog)->type = CPprog::PSeq;
    (yyval.prog)->val.upseq.p1 = pr;
    (yyval.prog)->val.upseq.p2 = ps;
  }
;}
    break;

  case 23:
#line 293 "pascal.parser.y"
    { 
  struct YYSTYPE::ttoken *temp = new struct YYSTYPE::ttoken;
  *temp = (yyvsp[(3) - (3)].token);
  (yyval.ltoken) = mp(temp, (yyvsp[(1) - (3)].ltoken)); 
;}
    break;

  case 24:
#line 298 "pascal.parser.y"
    { 
  struct YYSTYPE::ttoken *temp = new struct YYSTYPE::ttoken;
  *temp = (yyvsp[(1) - (1)].token);
  (yyval.ltoken) = mp(temp, (class pliste<struct YYSTYPE::ttoken> *)NULL); 
;}
    break;

  case 25:
#line 306 "pascal.parser.y"
    { (yyval.dvaltype) = new pdvaltype; (yyval.dvaltype)->type = pdvaltype::PDTBoolean; ;}
    break;

  case 26:
#line 307 "pascal.parser.y"
    { (yyval.dvaltype) = new pdvaltype; (yyval.dvaltype)->type = pdvaltype::PDTInteger; ;}
    break;

  case 27:
#line 308 "pascal.parser.y"
    { // subrange
  (yyval.dvaltype) = new pdvaltype; 
  (yyval.dvaltype)->type = pdvaltype::PDTSubrange;
  (yyval.dvaltype)->val.s.mine = (yyvsp[(1) - (3)].expr);
  (yyval.dvaltype)->val.s.maxe = (yyvsp[(3) - (3)].expr);
;}
    break;

  case 28:
#line 314 "pascal.parser.y"
    { (yyval.dvaltype) = new pdvaltype; (yyval.dvaltype)->type = pdvaltype::PDTReal; ;}
    break;

  case 29:
#line 315 "pascal.parser.y"
    { (yyval.dvaltype) = new pdvaltype; (yyval.dvaltype)->type = pdvaltype::PDTString; ;}
    break;

  case 30:
#line 316 "pascal.parser.y"
    {
  (yyval.dvaltype) = new pdvaltype; 
  (yyval.dvaltype)->type = pdvaltype::PDTPointer;
  (yyval.dvaltype)->val.ptr = (yyvsp[(1) - (1)].dvaltype);
;}
    break;

  case 31:
#line 321 "pascal.parser.y"
    { (yyval.dvaltype) = (yyvsp[(1) - (1)].dvaltype); ;}
    break;

  case 32:
#line 322 "pascal.parser.y"
    { (yyval.dvaltype) = (yyvsp[(1) - (1)].dvaltype); ;}
    break;

  case 33:
#line 323 "pascal.parser.y"
    {
  (yyval.dvaltype) = new pdvaltype; 
  (yyval.dvaltype)->type = pdvaltype::PDTUser;
  (yyval.dvaltype)->val.user = (yyvsp[(1) - (1)].token).val.ident;
;}
    break;

  case 34:
#line 332 "pascal.parser.y"
    { (yyval.dvaltype) = (yyvsp[(2) - (2)].dvaltype); ;}
    break;

  case 35:
#line 336 "pascal.parser.y"
    {
  (yyval.dvaltype) = new pdvaltype; 
  (yyval.dvaltype)->type = pdvaltype::PDTArray;
  (yyval.dvaltype)->val.array.indice.mine = (yyvsp[(3) - (8)].expr);
  (yyval.dvaltype)->val.array.indice.maxe = (yyvsp[(5) - (8)].expr);
  (yyval.dvaltype)->val.array.type = (yyvsp[(8) - (8)].dvaltype);
;}
    break;

  case 36:
#line 346 "pascal.parser.y"
    {
  (yyval.dvaltype) = new pdvaltype;
  (yyval.dvaltype)->type = pdvaltype::PDTRecord;
  (yyval.dvaltype)->val.record.champs = (yyvsp[(2) - (3)].lchamp);
;}
    break;

  case 37:
#line 354 "pascal.parser.y"
    {
  struct pascal_dval_type::tpdtrecord::champ *temp;
  temp = new struct pascal_dval_type::tpdtrecord::champ;
  temp->nom = (yyvsp[(2) - (5)].token).val.ident;
  temp->type = (yyvsp[(4) - (5)].dvaltype);
  (yyval.lchamp) = mp(temp, (yyvsp[(1) - (5)].lchamp));
;}
    break;

  case 38:
#line 361 "pascal.parser.y"
    { (yyval.lchamp) = (class pliste<struct pascal_dval_type::tpdtrecord::champ> *) NULL; ;}
    break;

  case 39:
#line 368 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (9)].token).position.nb_lignes, (yyvsp[(9) - (9)].token).position.nb_lignes, (yyvsp[(1) - (9)].token).position.nb_char_ligne, (yyvsp[(9) - (9)].token).position.nb_char_ligne + (yyvsp[(9) - (9)].token).position.longueur, (yyvsp[(1) - (9)].token).position.nb_char_tot, (yyvsp[(9) - (9)].token).position.nb_char_tot + (yyvsp[(9) - (9)].token).position.longueur);
  (yyval.prog)->type = CPprog::PVar;
  (yyval.prog)->val.upvar.nom = (yyvsp[(2) - (9)].token).val.ident;
  (yyval.prog)->val.upvar.t.type = pdvaltype::PDTProcedure;
  (yyval.prog)->val.upvar.t.val.proc.env = NULL;
  (yyval.prog)->val.upvar.t.val.proc.params = (yyvsp[(4) - (9)].params);
  (yyval.prog)->val.upvar.t.val.proc.corps = new class CPprog((yyvsp[(7) - (9)].prog)->position.deb_ligne, (yyvsp[(8) - (9)].prog)->position.fin_ligne, (yyvsp[(7) - (9)].prog)->position.deb_car, (yyvsp[(8) - (9)].prog)->position.fin_car, (yyvsp[(7) - (9)].prog)->position.deb_car_tot, (yyvsp[(8) - (9)].prog)->position.fin_car_tot);
  (yyval.prog)->val.upvar.t.val.proc.corps->type = CPprog::PSeq;
  (yyval.prog)->val.upvar.t.val.proc.corps->val.upseq.p1 = (yyvsp[(7) - (9)].prog);
  (yyval.prog)->val.upvar.t.val.proc.corps->val.upseq.p2 = (yyvsp[(8) - (9)].prog);
;}
    break;

  case 40:
#line 386 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (11)].token).position.nb_lignes, (yyvsp[(11) - (11)].token).position.nb_lignes, (yyvsp[(1) - (11)].token).position.nb_char_ligne, (yyvsp[(11) - (11)].token).position.nb_char_ligne + (yyvsp[(11) - (11)].token).position.longueur, (yyvsp[(1) - (11)].token).position.nb_char_tot, (yyvsp[(11) - (11)].token).position.nb_char_tot + (yyvsp[(11) - (11)].token).position.longueur);
  (yyval.prog)->type = CPprog::PVar;
  (yyval.prog)->val.upvar.nom = (yyvsp[(2) - (11)].token).val.ident;
  (yyval.prog)->val.upvar.t.type = pdvaltype::PDTFunction;
  (yyval.prog)->val.upvar.t.val.func.env = NULL;
  (yyval.prog)->val.upvar.t.val.func.params = (yyvsp[(4) - (11)].params);
  (yyval.prog)->val.upvar.t.val.func.type = (yyvsp[(7) - (11)].dvaltype);
  (yyval.prog)->val.upvar.t.val.func.corps = new class CPprog((yyvsp[(9) - (11)].prog)->position.deb_ligne, (yyvsp[(10) - (11)].prog)->position.fin_ligne, (yyvsp[(9) - (11)].prog)->position.deb_car, (yyvsp[(10) - (11)].prog)->position.fin_car, (yyvsp[(9) - (11)].prog)->position.deb_car_tot, (yyvsp[(10) - (11)].prog)->position.fin_car_tot);
  (yyval.prog)->val.upvar.t.val.func.corps->type = CPprog::PSeq;
  (yyval.prog)->val.upvar.t.val.func.corps->val.upseq.p1 = (yyvsp[(9) - (11)].prog);
  (yyval.prog)->val.upvar.t.val.func.corps->val.upseq.p2 = (yyvsp[(10) - (11)].prog);
;}
    break;

  case 41:
#line 402 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 42:
#line 403 "pascal.parser.y"
    {
    (yyval.prog) = new class CPprog((unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1);
    (yyval.prog)->type = CPprog::PSkip;
  ;}
    break;

  case 43:
#line 410 "pascal.parser.y"
    { (yyval.params) = mp((yyvsp[(1) - (2)].param),(yyvsp[(2) - (2)].params)); ;}
    break;

  case 44:
#line 411 "pascal.parser.y"
    { (yyval.params) = (class pliste<struct pascal_dval_type::tpdtprocedure::param> *) NULL; ;}
    break;

  case 45:
#line 415 "pascal.parser.y"
    { (yyval.params) = mp((yyvsp[(2) - (3)].param),(yyvsp[(3) - (3)].params)); ;}
    break;

  case 46:
#line 416 "pascal.parser.y"
    { (yyval.params) = (class pliste<struct pascal_dval_type::tpdtprocedure::param> *) NULL; ;}
    break;

  case 47:
#line 420 "pascal.parser.y"
    { (yyval.param) = (yyvsp[(1) - (1)].param); ;}
    break;

  case 48:
#line 421 "pascal.parser.y"
    { (yyval.param) = (yyvsp[(1) - (1)].param); ;}
    break;

  case 49:
#line 425 "pascal.parser.y"
    {
  (yyval.param) = new struct pascal_dval_type::tpdtprocedure::param;
  (yyval.param)->var = false;
  (yyval.param)->nom = (yyvsp[(1) - (3)].token).val.ident;
  (yyval.param)->dvaltype_ptr = (yyvsp[(3) - (3)].dvaltype);
;}
    break;

  case 50:
#line 435 "pascal.parser.y"
    {
  (yyval.param) = new struct pascal_dval_type::tpdtprocedure::param;
  (yyval.param)->var = true;
  (yyval.param)->nom = (yyvsp[(2) - (4)].token).val.ident;
  (yyval.param)->dvaltype_ptr = (yyvsp[(4) - (4)].dvaltype);
;}
    break;

  case 51:
#line 444 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 52:
#line 447 "pascal.parser.y"
    {
    (yyval.prog) = new class CPprog((yyvsp[(1) - (2)].prog)->position.deb_ligne, (yyvsp[(2) - (2)].prog)->position.fin_ligne, (yyvsp[(1) - (2)].prog)->position.deb_car, (yyvsp[(2) - (2)].prog)->position.fin_car, (yyvsp[(1) - (2)].prog)->position.deb_car_tot, (yyvsp[(2) - (2)].prog)->position.fin_car_tot);
    (yyval.prog)->type = CPprog::PSeq;
    (yyval.prog)->val.upseq.p1 = (yyvsp[(1) - (2)].prog);
    (yyval.prog)->val.upseq.p2 = (yyvsp[(2) - (2)].prog);
  ;}
    break;

  case 53:
#line 453 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 54:
#line 457 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (3)].prog)->position.deb_ligne, (yyvsp[(2) - (3)].prog)->position.fin_ligne, (yyvsp[(1) - (3)].prog)->position.deb_car, (yyvsp[(2) - (3)].prog)->position.fin_car, (yyvsp[(1) - (3)].prog)->position.deb_car_tot, (yyvsp[(2) - (3)].prog)->position.fin_car_tot);
  (yyval.prog)->type = CPprog::PSeq;
  (yyval.prog)->val.upseq.p1 = (yyvsp[(1) - (3)].prog);
  (yyval.prog)->val.upseq.p2 = (yyvsp[(2) - (3)].prog);
;}
    break;

  case 55:
#line 463 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (2)].prog); ;}
    break;

  case 56:
#line 467 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 57:
#line 468 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 58:
#line 469 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 59:
#line 470 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 60:
#line 471 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 61:
#line 472 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 62:
#line 473 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 63:
#line 474 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 64:
#line 475 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 65:
#line 476 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 66:
#line 477 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 67:
#line 478 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 68:
#line 479 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 69:
#line 480 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 70:
#line 481 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 71:
#line 482 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 72:
#line 483 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 73:
#line 484 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 74:
#line 485 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 75:
#line 486 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 76:
#line 487 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 77:
#line 488 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 78:
#line 489 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 79:
#line 490 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 80:
#line 491 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 81:
#line 492 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 82:
#line 493 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 83:
#line 494 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 84:
#line 495 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 85:
#line 496 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 86:
#line 497 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 87:
#line 498 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 88:
#line 499 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 89:
#line 503 "pascal.parser.y"
    {
  /* ... */
  (yyval.prog) = new class CPprog((unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1);
  (yyval.prog)->type = CPprog::PSkip;
;}
    break;

  case 90:
#line 510 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (3)].token).position.nb_lignes, (yyvsp[(3) - (3)].token).position.nb_lignes, (yyvsp[(1) - (3)].token).position.nb_char_ligne, (yyvsp[(3) - (3)].token).position.nb_char_ligne + (yyvsp[(3) - (3)].token).position.longueur, (yyvsp[(1) - (3)].token).position.nb_char_tot, (yyvsp[(3) - (3)].token).position.nb_char_tot + (yyvsp[(3) - (3)].token).position.longueur);
  (yyval.prog)->type = CPprog::PBegin;
  (yyval.prog)->val.upbegin.p = (yyvsp[(2) - (3)].prog);
;}
    break;

  case 91:
#line 518 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (3)].expr)->position.deb_ligne, (yyvsp[(3) - (3)].expr)->position.fin_ligne, (yyvsp[(1) - (3)].expr)->position.deb_car, (yyvsp[(3) - (3)].expr)->position.fin_car, (yyvsp[(1) - (3)].expr)->position.deb_car_tot, (yyvsp[(3) - (3)].expr)->position.fin_car_tot);
  (yyval.prog)->type = CPprog::PAffectation;
  (yyval.prog)->val.upaffectation.lval = (yyvsp[(1) - (3)].expr);
  (yyval.prog)->val.upaffectation.e = (yyvsp[(3) - (3)].expr);
;}
    break;

  case 92:
#line 527 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (5)].token).position.nb_lignes, (yyvsp[(5) - (5)].token).position.nb_lignes, (yyvsp[(1) - (5)].token).position.nb_char_ligne, (yyvsp[(5) - (5)].token).position.nb_char_ligne + (yyvsp[(5) - (5)].token).position.longueur, (yyvsp[(1) - (5)].token).position.nb_char_tot, (yyvsp[(5) - (5)].token).position.nb_char_tot + (yyvsp[(5) - (5)].token).position.longueur);
  (yyval.prog)->type = CPprog::PIf;
  (yyval.prog)->val.upif.b = (yyvsp[(2) - (5)].expr);
  (yyval.prog)->val.upif.p = (yyvsp[(4) - (5)].prog);
  (yyval.prog)->val.upif.q = new class CPprog((unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1);
  (yyval.prog)->val.upif.q->type = CPprog::PSkip;
;}
    break;

  case 93:
#line 538 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (7)].token).position.nb_lignes, (yyvsp[(7) - (7)].token).position.nb_lignes, (yyvsp[(1) - (7)].token).position.nb_char_ligne, (yyvsp[(7) - (7)].token).position.nb_char_ligne + (yyvsp[(7) - (7)].token).position.longueur, (yyvsp[(1) - (7)].token).position.nb_char_tot, (yyvsp[(7) - (7)].token).position.nb_char_tot + (yyvsp[(7) - (7)].token).position.longueur);
  (yyval.prog)->type = CPprog::PIf;
  (yyval.prog)->val.upif.b = (yyvsp[(2) - (7)].expr);
  (yyval.prog)->val.upif.p = (yyvsp[(4) - (7)].prog);
  (yyval.prog)->val.upif.q = (yyvsp[(6) - (7)].prog);
;}
    break;

  case 94:
#line 548 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (4)].token).position.nb_lignes, (yyvsp[(4) - (4)].prog)->position.fin_ligne, (yyvsp[(1) - (4)].token).position.nb_char_ligne, (yyvsp[(4) - (4)].prog)->position.fin_car, (yyvsp[(1) - (4)].token).position.nb_char_tot, (yyvsp[(4) - (4)].prog)->position.fin_car_tot);
  (yyval.prog)->type = CPprog::PWhile;
  (yyval.prog)->val.upwhile.b = (yyvsp[(2) - (4)].expr);
  (yyval.prog)->val.upwhile.p = (yyvsp[(4) - (4)].prog);
;}
    break;

  case 95:
#line 557 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (8)].token).position.nb_lignes, (yyvsp[(8) - (8)].prog)->position.fin_ligne, (yyvsp[(1) - (8)].token).position.nb_char_ligne, (yyvsp[(8) - (8)].prog)->position.fin_car, (yyvsp[(1) - (8)].token).position.nb_char_tot, (yyvsp[(8) - (8)].prog)->position.fin_car_tot);
  (yyval.prog)->type = CPprog::PFor;
  (yyval.prog)->val.upfor.i = (yyvsp[(2) - (8)].token).val.ident;
  (yyval.prog)->val.upfor.e1 = (yyvsp[(4) - (8)].expr);
  (yyval.prog)->val.upfor.e2 = (yyvsp[(6) - (8)].expr);
  (yyval.prog)->val.upfor.p = (yyvsp[(8) - (8)].prog);
;}
    break;

  case 96:
#line 568 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (4)].token).position.nb_lignes, (yyvsp[(4) - (4)].expr)->position.fin_ligne, (yyvsp[(1) - (4)].token).position.nb_char_ligne, (yyvsp[(4) - (4)].expr)->position.fin_car, (yyvsp[(1) - (4)].token).position.nb_char_tot, (yyvsp[(4) - (4)].expr)->position.fin_car_tot);
  (yyval.prog)->type = CPprog::PRepeat;
  (yyval.prog)->val.uprepeat.b = (yyvsp[(4) - (4)].expr);
  (yyval.prog)->val.uprepeat.p = (yyvsp[(2) - (4)].prog);
;}
    break;

  case 97:
#line 577 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (4)].token).position.nb_lignes, (yyvsp[(4) - (4)].token).position.nb_lignes, (yyvsp[(1) - (4)].token).position.nb_char_ligne, (yyvsp[(4) - (4)].token).position.nb_char_ligne + (yyvsp[(4) - (4)].token).position.longueur, (yyvsp[(1) - (4)].token).position.nb_char_tot, (yyvsp[(4) - (4)].token).position.nb_char_tot + (yyvsp[(4) - (4)].token).position.longueur);
  (yyval.prog)->type = CPprog::PWrite;
  (yyval.prog)->val.upwrite.le = (yyvsp[(3) - (4)].lexpr);
;}
    break;

  case 98:
#line 584 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (4)].token).position.nb_lignes, (yyvsp[(4) - (4)].token).position.nb_lignes, (yyvsp[(1) - (4)].token).position.nb_char_ligne, (yyvsp[(4) - (4)].token).position.nb_char_ligne + (yyvsp[(4) - (4)].token).position.longueur, (yyvsp[(1) - (4)].token).position.nb_char_tot, (yyvsp[(4) - (4)].token).position.nb_char_tot + (yyvsp[(4) - (4)].token).position.longueur);
  (yyval.prog)->type = CPprog::PWriteln;
  (yyval.prog)->val.upwriteln.le = (yyvsp[(3) - (4)].lexpr);
;}
    break;

  case 99:
#line 591 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (4)].token).position.nb_lignes, (yyvsp[(4) - (4)].token).position.nb_lignes, (yyvsp[(1) - (4)].token).position.nb_char_ligne, (yyvsp[(4) - (4)].token).position.nb_char_ligne + (yyvsp[(4) - (4)].token).position.longueur, (yyvsp[(1) - (4)].token).position.nb_char_tot, (yyvsp[(4) - (4)].token).position.nb_char_tot + (yyvsp[(4) - (4)].token).position.longueur);
  (yyval.prog)->type = CPprog::PRead;
  (yyval.prog)->val.upread.llval = (yyvsp[(3) - (4)].lexpr);
;}
    break;

  case 100:
#line 598 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (4)].token).position.nb_lignes, (yyvsp[(4) - (4)].token).position.nb_lignes, (yyvsp[(1) - (4)].token).position.nb_char_ligne, (yyvsp[(4) - (4)].token).position.nb_char_ligne + (yyvsp[(4) - (4)].token).position.longueur, (yyvsp[(1) - (4)].token).position.nb_char_tot, (yyvsp[(4) - (4)].token).position.nb_char_tot + (yyvsp[(4) - (4)].token).position.longueur);
  (yyval.prog)->type = CPprog::PReadln;
  (yyval.prog)->val.upreadln.llval = (yyvsp[(3) - (4)].lexpr);
;}
    break;

  case 101:
#line 606 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (4)].token).position.nb_lignes, (yyvsp[(4) - (4)].token).position.nb_lignes, (yyvsp[(1) - (4)].token).position.nb_char_ligne, (yyvsp[(4) - (4)].token).position.nb_char_ligne + (yyvsp[(4) - (4)].token).position.longueur, (yyvsp[(1) - (4)].token).position.nb_char_tot, (yyvsp[(4) - (4)].token).position.nb_char_tot + (yyvsp[(4) - (4)].token).position.longueur);
  (yyval.prog)->type = CPprog::PNew;
  (yyval.prog)->val.upnew.ident = (yyvsp[(3) - (4)].token).val.ident;
;}
    break;

  case 102:
#line 614 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (4)].token).position.nb_lignes, (yyvsp[(4) - (4)].token).position.nb_lignes, (yyvsp[(1) - (4)].token).position.nb_char_ligne, (yyvsp[(4) - (4)].token).position.nb_char_ligne + (yyvsp[(4) - (4)].token).position.longueur, (yyvsp[(1) - (4)].token).position.nb_char_tot, (yyvsp[(4) - (4)].token).position.nb_char_tot + (yyvsp[(4) - (4)].token).position.longueur);
  (yyval.prog)->type = CPprog::PMusique;
  (yyval.prog)->val.upmusique.musique = (yyvsp[(3) - (4)].expr);
;}
    break;

  case 103:
#line 622 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (4)].token).position.nb_lignes, (yyvsp[(4) - (4)].token).position.nb_lignes, (yyvsp[(1) - (4)].token).position.nb_char_ligne, (yyvsp[(4) - (4)].token).position.nb_char_ligne + (yyvsp[(4) - (4)].token).position.longueur, (yyvsp[(1) - (4)].token).position.nb_char_tot, (yyvsp[(4) - (4)].token).position.nb_char_tot + (yyvsp[(4) - (4)].token).position.longueur);
  (yyval.prog)->type = CPprog::PWait;
  (yyval.prog)->val.upwait.nbpasses = (yyvsp[(3) - (4)].expr);
;}
    break;

  case 104:
#line 630 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (4)].token).position.nb_lignes, (yyvsp[(4) - (4)].token).position.nb_lignes, (yyvsp[(1) - (4)].token).position.nb_char_ligne, (yyvsp[(4) - (4)].token).position.nb_char_ligne + (yyvsp[(4) - (4)].token).position.longueur, (yyvsp[(1) - (4)].token).position.nb_char_tot, (yyvsp[(4) - (4)].token).position.nb_char_tot + (yyvsp[(4) - (4)].token).position.longueur);
  (yyval.prog)->type = CPprog::PFondu;
  (yyval.prog)->val.upfondu.couleur = (yyvsp[(3) - (4)].expr);
;}
    break;

  case 105:
#line 639 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (10)].token).position.nb_lignes, (yyvsp[(10) - (10)].token).position.nb_lignes, (yyvsp[(1) - (10)].token).position.nb_char_ligne, (yyvsp[(10) - (10)].token).position.nb_char_ligne + (yyvsp[(10) - (10)].token).position.longueur, (yyvsp[(1) - (10)].token).position.nb_char_tot, (yyvsp[(10) - (10)].token).position.nb_char_tot + (yyvsp[(10) - (10)].token).position.longueur);
  (yyval.prog)->type = CPprog::PCarte;
  (yyval.prog)->val.upcarte.nom = (yyvsp[(3) - (10)].expr);
  (yyval.prog)->val.upcarte.x = (yyvsp[(5) - (10)].expr);
  (yyval.prog)->val.upcarte.y = (yyvsp[(7) - (10)].expr);
  (yyval.prog)->val.upcarte.direction = (yyvsp[(9) - (10)].expr);
;}
    break;

  case 106:
#line 649 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (12)].token).position.nb_lignes, (yyvsp[(12) - (12)].token).position.nb_lignes, (yyvsp[(1) - (12)].token).position.nb_char_ligne, (yyvsp[(12) - (12)].token).position.nb_char_ligne + (yyvsp[(12) - (12)].token).position.longueur, (yyvsp[(1) - (12)].token).position.nb_char_tot, (yyvsp[(12) - (12)].token).position.nb_char_tot + (yyvsp[(12) - (12)].token).position.longueur);
  (yyval.prog)->type = CPprog::PCarteZ;
  (yyval.prog)->val.upcartez.nom = (yyvsp[(3) - (12)].expr);
  (yyval.prog)->val.upcartez.x = (yyvsp[(5) - (12)].expr);
  (yyval.prog)->val.upcartez.y = (yyvsp[(7) - (12)].expr);
  (yyval.prog)->val.upcartez.z = (yyvsp[(9) - (12)].expr);
  (yyval.prog)->val.upcartez.direction = (yyvsp[(11) - (12)].expr);
;}
    break;

  case 107:
#line 661 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (10)].expr)->position.deb_ligne, (yyvsp[(10) - (10)].token).position.nb_lignes, (yyvsp[(1) - (10)].expr)->position.deb_car, (yyvsp[(10) - (10)].token).position.nb_char_ligne + (yyvsp[(10) - (10)].token).position.longueur, (yyvsp[(1) - (10)].expr)->position.deb_car_tot, (yyvsp[(10) - (10)].token).position.nb_char_tot + (yyvsp[(10) - (10)].token).position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  (yyval.prog)->type = CPprog::PSetPosition;
  (yyval.prog)->val.upsetpos.nom = (yyvsp[(1) - (10)].expr);
  (yyval.prog)->val.upsetpos.x = (yyvsp[(5) - (10)].expr);
  (yyval.prog)->val.upsetpos.y = (yyvsp[(7) - (10)].expr);
  (yyval.prog)->val.upsetpos.relatif = (yyvsp[(9) - (10)].expr);
;}
    break;

  case 108:
#line 674 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (12)].expr)->position.deb_ligne, (yyvsp[(12) - (12)].token).position.nb_lignes, (yyvsp[(1) - (12)].expr)->position.deb_car, (yyvsp[(12) - (12)].token).position.nb_char_ligne + (yyvsp[(12) - (12)].token).position.longueur, (yyvsp[(1) - (12)].expr)->position.deb_car_tot, (yyvsp[(12) - (12)].token).position.nb_char_tot + (yyvsp[(12) - (12)].token).position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  (yyval.prog)->type = CPprog::PSetPositionZ;
  (yyval.prog)->val.upsetposz.nom = (yyvsp[(1) - (12)].expr);
  (yyval.prog)->val.upsetposz.x = (yyvsp[(5) - (12)].expr);
  (yyval.prog)->val.upsetposz.y = (yyvsp[(7) - (12)].expr);
  (yyval.prog)->val.upsetposz.z = (yyvsp[(9) - (12)].expr);
  (yyval.prog)->val.upsetposz.relatif = (yyvsp[(11) - (12)].expr);
;}
    break;

  case 109:
#line 688 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (5)].expr)->position.deb_ligne, (yyvsp[(5) - (5)].token).position.nb_lignes, (yyvsp[(1) - (5)].expr)->position.deb_car, (yyvsp[(5) - (5)].token).position.nb_char_ligne + (yyvsp[(5) - (5)].token).position.longueur, (yyvsp[(1) - (5)].expr)->position.deb_car_tot, (yyvsp[(5) - (5)].token).position.nb_char_tot + (yyvsp[(5) - (5)].token).position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  (yyval.prog)->type = CPprog::PFrapper;
  (yyval.prog)->val.upfrapper.nom = (yyvsp[(1) - (5)].expr);
;}
    break;

  case 110:
#line 698 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (10)].expr)->position.deb_ligne, (yyvsp[(10) - (10)].token).position.nb_lignes, (yyvsp[(1) - (10)].expr)->position.deb_car, (yyvsp[(10) - (10)].token).position.nb_char_ligne + (yyvsp[(10) - (10)].token).position.longueur, (yyvsp[(1) - (10)].expr)->position.deb_car_tot, (yyvsp[(10) - (10)].token).position.nb_char_tot + (yyvsp[(10) - (10)].token).position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  (yyval.prog)->type = CPprog::PDeplacer;
  (yyval.prog)->val.updeplacer.nom = (yyvsp[(1) - (10)].expr);
  (yyval.prog)->val.updeplacer.x = (yyvsp[(5) - (10)].expr);
  (yyval.prog)->val.updeplacer.y = (yyvsp[(7) - (10)].expr);
  (yyval.prog)->val.updeplacer.relatif = (yyvsp[(9) - (10)].expr);
;}
    break;

  case 111:
#line 710 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (5)].expr)->position.deb_ligne, (yyvsp[(5) - (5)].token).position.nb_lignes, (yyvsp[(1) - (5)].expr)->position.deb_car, (yyvsp[(5) - (5)].token).position.nb_char_ligne + (yyvsp[(5) - (5)].token).position.longueur, (yyvsp[(1) - (5)].expr)->position.deb_car_tot, (yyvsp[(5) - (5)].token).position.nb_char_tot + (yyvsp[(5) - (5)].token).position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  (yyval.prog)->type = CPprog::PSupObjet;
  (yyval.prog)->val.upsupobjet.nom = (yyvsp[(1) - (5)].expr);
;}
    break;

  case 112:
#line 720 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (5)].expr)->position.deb_ligne, (yyvsp[(5) - (5)].token).position.nb_lignes, (yyvsp[(1) - (5)].expr)->position.deb_car, (yyvsp[(5) - (5)].token).position.nb_char_ligne + (yyvsp[(5) - (5)].token).position.longueur, (yyvsp[(1) - (5)].expr)->position.deb_car_tot, (yyvsp[(5) - (5)].token).position.nb_char_tot + (yyvsp[(5) - (5)].token).position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  (yyval.prog)->type = CPprog::PRecArme;
  (yyval.prog)->val.uprecarme.nom = (yyvsp[(1) - (5)].expr);
;}
    break;

  case 113:
#line 728 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (6)].expr)->position.deb_ligne, (yyvsp[(6) - (6)].token).position.nb_lignes, (yyvsp[(1) - (6)].expr)->position.deb_car, (yyvsp[(6) - (6)].token).position.nb_char_ligne + (yyvsp[(6) - (6)].token).position.longueur, (yyvsp[(1) - (6)].expr)->position.deb_car_tot, (yyvsp[(6) - (6)].token).position.nb_char_tot + (yyvsp[(6) - (6)].token).position.longueur);
  //$$ = new class CPprog($1.position.nb_lignes, $10.position.nb_lignes, $1.position.nb_char_ligne, $10.position.nb_char_ligne + $10.position.longueur, $1.position.nb_char_tot, $10.position.nb_char_tot + $10.position.longueur);
  (yyval.prog)->type = CPprog::PSetOrientation;
  (yyval.prog)->val.upsetorientation.nom = (yyvsp[(1) - (6)].expr);
  (yyval.prog)->val.upsetorientation.orientation = (yyvsp[(5) - (6)].expr);  
;}
    break;

  case 114:
#line 738 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (6)].token).position.nb_lignes, (yyvsp[(6) - (6)].token).position.nb_lignes, (yyvsp[(1) - (6)].token).position.nb_char_ligne, (yyvsp[(6) - (6)].token).position.nb_char_ligne + (yyvsp[(6) - (6)].token).position.longueur, (yyvsp[(1) - (6)].token).position.nb_char_tot, (yyvsp[(6) - (6)].token).position.nb_char_tot + (yyvsp[(6) - (6)].token).position.longueur);
  (yyval.prog)->type = CPprog::PAjouterAnime;
  (yyval.prog)->val.upajouteranime.nom = (yyvsp[(3) - (6)].expr);
  (yyval.prog)->val.upajouteranime.fichier = (yyvsp[(5) - (6)].expr);
;}
    break;

  case 115:
#line 747 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (6)].token).position.nb_lignes, (yyvsp[(6) - (6)].token).position.nb_lignes, (yyvsp[(1) - (6)].token).position.nb_char_ligne, (yyvsp[(6) - (6)].token).position.nb_char_ligne + (yyvsp[(6) - (6)].token).position.longueur, (yyvsp[(1) - (6)].token).position.nb_char_tot, (yyvsp[(6) - (6)].token).position.nb_char_tot + (yyvsp[(6) - (6)].token).position.longueur);
  (yyval.prog)->type = CPprog::PAjouterNonAnime;
  (yyval.prog)->val.upajouternonanime.nom = (yyvsp[(3) - (6)].expr);
  (yyval.prog)->val.upajouternonanime.fichier = (yyvsp[(5) - (6)].expr);
;}
    break;

  case 116:
#line 756 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (4)].token).position.nb_lignes, (yyvsp[(4) - (4)].token).position.nb_lignes, (yyvsp[(1) - (4)].token).position.nb_char_ligne, (yyvsp[(4) - (4)].token).position.nb_char_ligne + (yyvsp[(4) - (4)].token).position.longueur, (yyvsp[(1) - (4)].token).position.nb_char_tot, (yyvsp[(4) - (4)].token).position.nb_char_tot + (yyvsp[(4) - (4)].token).position.longueur);
  (yyval.prog)->type = CPprog::PSetTemps;
  (yyval.prog)->val.upsettemps.temps = (yyvsp[(3) - (4)].expr);
;}
    break;

  case 117:
#line 764 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (4)].token).position.nb_lignes, (yyvsp[(4) - (4)].token).position.nb_lignes, (yyvsp[(1) - (4)].token).position.nb_char_ligne, (yyvsp[(4) - (4)].token).position.nb_char_ligne + (yyvsp[(4) - (4)].token).position.longueur, (yyvsp[(1) - (4)].token).position.nb_char_tot, (yyvsp[(4) - (4)].token).position.nb_char_tot + (yyvsp[(4) - (4)].token).position.longueur);
  (yyval.prog)->type = CPprog::PWaitFor;
  (yyval.prog)->val.upwaitfor.nom = (yyvsp[(3) - (4)].expr);
;}
    break;

  case 118:
#line 772 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (3)].token).position.nb_lignes, (yyvsp[(3) - (3)].token).position.nb_lignes, (yyvsp[(1) - (3)].token).position.nb_char_ligne, (yyvsp[(3) - (3)].token).position.nb_char_ligne + (yyvsp[(3) - (3)].token).position.longueur, (yyvsp[(1) - (3)].token).position.nb_char_tot, (yyvsp[(3) - (3)].token).position.nb_char_tot + (yyvsp[(3) - (3)].token).position.longueur);
  (yyval.prog)->type = CPprog::PBloquerTemps;
;}
    break;

  case 119:
#line 778 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (3)].token).position.nb_lignes, (yyvsp[(3) - (3)].token).position.nb_lignes, (yyvsp[(1) - (3)].token).position.nb_char_ligne, (yyvsp[(3) - (3)].token).position.nb_char_ligne + (yyvsp[(3) - (3)].token).position.longueur, (yyvsp[(1) - (3)].token).position.nb_char_tot, (yyvsp[(3) - (3)].token).position.nb_char_tot + (yyvsp[(3) - (3)].token).position.longueur);
  (yyval.prog)->type = CPprog::PDebloquerTemps;
;}
    break;

  case 120:
#line 786 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 121:
#line 787 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 122:
#line 788 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 123:
#line 789 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 124:
#line 790 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 125:
#line 791 "pascal.parser.y"
    { (yyval.prog) = (yyvsp[(1) - (1)].prog); ;}
    break;

  case 126:
#line 795 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (5)].token).position.nb_lignes, (yyvsp[(5) - (5)].token).position.nb_lignes, (yyvsp[(1) - (5)].token).position.nb_char_ligne, (yyvsp[(5) - (5)].token).position.nb_char_ligne + (yyvsp[(5) - (5)].token).position.longueur, (yyvsp[(1) - (5)].token).position.nb_char_tot, (yyvsp[(5) - (5)].token).position.nb_char_tot + (yyvsp[(5) - (5)].token).position.longueur);
  (yyval.prog)->type = CPprog::PCameraDefaut;
;}
    break;

  case 127:
#line 802 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (5)].token).position.nb_lignes, (yyvsp[(5) - (5)].token).position.nb_lignes, (yyvsp[(1) - (5)].token).position.nb_char_ligne, (yyvsp[(5) - (5)].token).position.nb_char_ligne + (yyvsp[(5) - (5)].token).position.longueur, (yyvsp[(1) - (5)].token).position.nb_char_tot, (yyvsp[(5) - (5)].token).position.nb_char_tot + (yyvsp[(5) - (5)].token).position.longueur);
  (yyval.prog)->type = CPprog::PCameraSolidariser;
;}
    break;

  case 128:
#line 809 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (5)].token).position.nb_lignes, (yyvsp[(5) - (5)].token).position.nb_lignes, (yyvsp[(1) - (5)].token).position.nb_char_ligne, (yyvsp[(5) - (5)].token).position.nb_char_ligne + (yyvsp[(5) - (5)].token).position.longueur, (yyvsp[(1) - (5)].token).position.nb_char_tot, (yyvsp[(5) - (5)].token).position.nb_char_tot + (yyvsp[(5) - (5)].token).position.longueur);
  (yyval.prog)->type = CPprog::PCameraDesolidariser;
;}
    break;

  case 129:
#line 818 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (12)].token).position.nb_lignes, (yyvsp[(12) - (12)].token).position.nb_lignes, (yyvsp[(1) - (12)].token).position.nb_char_ligne, (yyvsp[(12) - (12)].token).position.nb_char_ligne + (yyvsp[(12) - (12)].token).position.longueur, (yyvsp[(1) - (12)].token).position.nb_char_tot, (yyvsp[(12) - (12)].token).position.nb_char_tot + (yyvsp[(12) - (12)].token).position.longueur);
  (yyval.prog)->type = CPprog::PSetCameraPosition;
  (yyval.prog)->val.upsetcamerapos.x = (yyvsp[(5) - (12)].expr);
  (yyval.prog)->val.upsetcamerapos.y = (yyvsp[(7) - (12)].expr);
  (yyval.prog)->val.upsetcamerapos.z = (yyvsp[(9) - (12)].expr);
  (yyval.prog)->val.upsetcamerapos.relatif = (yyvsp[(11) - (12)].expr);
;}
    break;

  case 130:
#line 829 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (12)].token).position.nb_lignes, (yyvsp[(12) - (12)].token).position.nb_lignes, (yyvsp[(1) - (12)].token).position.nb_char_ligne, (yyvsp[(12) - (12)].token).position.nb_char_ligne + (yyvsp[(12) - (12)].token).position.longueur, (yyvsp[(1) - (12)].token).position.nb_char_tot, (yyvsp[(12) - (12)].token).position.nb_char_tot + (yyvsp[(12) - (12)].token).position.longueur);
  (yyval.prog)->type = CPprog::PCameraRotate;
  (yyval.prog)->val.upcamerarotate.angle_x = (yyvsp[(5) - (12)].expr);
  (yyval.prog)->val.upcamerarotate.angle_y = (yyvsp[(7) - (12)].expr);
  (yyval.prog)->val.upcamerarotate.angle_z = (yyvsp[(9) - (12)].expr);
  (yyval.prog)->val.upcamerarotate.relatif = (yyvsp[(11) - (12)].expr);
;}
    break;

  case 131:
#line 840 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (6)].token).position.nb_lignes, (yyvsp[(6) - (6)].token).position.nb_lignes, (yyvsp[(1) - (6)].token).position.nb_char_ligne, (yyvsp[(6) - (6)].token).position.nb_char_ligne + (yyvsp[(6) - (6)].token).position.longueur, (yyvsp[(1) - (6)].token).position.nb_char_tot, (yyvsp[(6) - (6)].token).position.nb_char_tot + (yyvsp[(6) - (6)].token).position.longueur);
  (yyval.prog)->type = CPprog::PCameraZoom;
  (yyval.prog)->val.upcamerazoom.coeff = (yyvsp[(5) - (6)].expr);
;}
    break;

  case 132:
#line 854 "pascal.parser.y"
    {
  (yyval.prog) = new class CPprog((yyvsp[(1) - (4)].token).position.nb_lignes, (yyvsp[(4) - (4)].token).position.nb_lignes, (yyvsp[(1) - (4)].token).position.nb_char_ligne, (yyvsp[(4) - (4)].token).position.nb_char_ligne + (yyvsp[(4) - (4)].token).position.longueur, (yyvsp[(1) - (4)].token).position.nb_char_tot, (yyvsp[(4) - (4)].token).position.nb_char_tot + (yyvsp[(4) - (4)].token).position.longueur);
  (yyval.prog)->type = CPprog::PCall;
  (yyval.prog)->val.upcall.ident = (yyvsp[(1) - (4)].token).val.ident;
  (yyval.prog)->val.upcall.args = (yyvsp[(3) - (4)].lexpr);
;}
    break;

  case 133:
#line 863 "pascal.parser.y"
    { /* !!!!!!!!!!!!!!!!!! */
  (yyval.expr) = new CPexpr((yyvsp[(1) - (4)].token).position.nb_lignes, (yyvsp[(4) - (4)].token).position.nb_lignes, (yyvsp[(1) - (4)].token).position.nb_char_ligne, (yyvsp[(4) - (4)].token).position.nb_char_ligne + (yyvsp[(4) - (4)].token).position.longueur, (yyvsp[(1) - (4)].token).position.nb_char_tot, (yyvsp[(4) - (4)].token).position.nb_char_tot + (yyvsp[(4) - (4)].token).position.longueur);
  (yyval.expr)->type = CPexpr::PCall; 
  (yyval.expr)->val.upcall.ident = (yyvsp[(1) - (4)].token).val.ident;
  (yyval.expr)->val.upcall.args = (yyvsp[(3) - (4)].lexpr);
;}
    break;

  case 134:
#line 872 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (3)].token).position.nb_lignes, (yyvsp[(3) - (3)].token).position.nb_lignes, (yyvsp[(1) - (3)].token).position.nb_char_ligne, (yyvsp[(3) - (3)].token).position.nb_char_ligne + (yyvsp[(3) - (3)].token).position.longueur, (yyvsp[(1) - (3)].token).position.nb_char_tot, (yyvsp[(3) - (3)].token).position.nb_char_tot + (yyvsp[(3) - (3)].token).position.longueur);
  (yyval.expr)->type = CPexpr::PNomCarte; 
;}
    break;

  case 135:
#line 878 "pascal.parser.y"
    { (yyval.lexpr) = mp((yyvsp[(1) - (2)].expr), (yyvsp[(2) - (2)].lexpr)); ;}
    break;

  case 136:
#line 879 "pascal.parser.y"
    { (yyval.lexpr) = (class pliste<CPexpr> *)NULL; ;}
    break;

  case 137:
#line 883 "pascal.parser.y"
    { (yyval.lexpr) = mp((yyvsp[(2) - (3)].expr), (yyvsp[(3) - (3)].lexpr)); ;}
    break;

  case 138:
#line 884 "pascal.parser.y"
    { (yyval.lexpr) = (class pliste<CPexpr> *)NULL; ;}
    break;

  case 139:
#line 888 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 140:
#line 894 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (3)].expr)->position.deb_ligne, (yyvsp[(3) - (3)].expr)->position.fin_ligne, (yyvsp[(1) - (3)].expr)->position.deb_car, (yyvsp[(3) - (3)].expr)->position.fin_car, (yyvsp[(1) - (3)].expr)->position.deb_car_tot, (yyvsp[(3) - (3)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::POu;
  (yyval.expr)->val.upou.e1 = (yyvsp[(1) - (3)].expr);
  (yyval.expr)->val.upou.e2 = (yyvsp[(3) - (3)].expr);
;}
    break;

  case 141:
#line 900 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (3)].expr)->position.deb_ligne, (yyvsp[(3) - (3)].expr)->position.fin_ligne, (yyvsp[(1) - (3)].expr)->position.deb_car, (yyvsp[(3) - (3)].expr)->position.fin_car, (yyvsp[(1) - (3)].expr)->position.deb_car_tot, (yyvsp[(3) - (3)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PEt;
  (yyval.expr)->val.upet.e1 = (yyvsp[(1) - (3)].expr);
  (yyval.expr)->val.upet.e2 = (yyvsp[(3) - (3)].expr);
;}
    break;

  case 142:
#line 906 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 143:
#line 911 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (3)].expr)->position.deb_ligne, (yyvsp[(3) - (3)].expr)->position.fin_ligne, (yyvsp[(1) - (3)].expr)->position.deb_car, (yyvsp[(3) - (3)].expr)->position.fin_car, (yyvsp[(1) - (3)].expr)->position.deb_car_tot, (yyvsp[(3) - (3)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PEqual;
  (yyval.expr)->val.upequal.e1 = (yyvsp[(1) - (3)].expr);
  (yyval.expr)->val.upequal.e2 = (yyvsp[(3) - (3)].expr);
;}
    break;

  case 144:
#line 917 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (3)].expr)->position.deb_ligne, (yyvsp[(3) - (3)].expr)->position.fin_ligne, (yyvsp[(1) - (3)].expr)->position.deb_car, (yyvsp[(3) - (3)].expr)->position.fin_car, (yyvsp[(1) - (3)].expr)->position.deb_car_tot, (yyvsp[(3) - (3)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PDiff;
  (yyval.expr)->val.updiff.e1 = (yyvsp[(1) - (3)].expr);
  (yyval.expr)->val.updiff.e2 = (yyvsp[(3) - (3)].expr);
;}
    break;

  case 145:
#line 923 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (3)].expr)->position.deb_ligne, (yyvsp[(3) - (3)].expr)->position.fin_ligne, (yyvsp[(1) - (3)].expr)->position.deb_car, (yyvsp[(3) - (3)].expr)->position.fin_car, (yyvsp[(1) - (3)].expr)->position.deb_car_tot, (yyvsp[(3) - (3)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PInf;
  (yyval.expr)->val.upinf.e1 = (yyvsp[(1) - (3)].expr);
  (yyval.expr)->val.upinf.e2 = (yyvsp[(3) - (3)].expr);
;}
    break;

  case 146:
#line 929 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (3)].expr)->position.deb_ligne, (yyvsp[(3) - (3)].expr)->position.fin_ligne, (yyvsp[(1) - (3)].expr)->position.deb_car, (yyvsp[(3) - (3)].expr)->position.fin_car, (yyvsp[(1) - (3)].expr)->position.deb_car_tot, (yyvsp[(3) - (3)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PSup;
  (yyval.expr)->val.upsup.e1 = (yyvsp[(1) - (3)].expr);
  (yyval.expr)->val.upsup.e2 = (yyvsp[(3) - (3)].expr);
;}
    break;

  case 147:
#line 935 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (3)].expr)->position.deb_ligne, (yyvsp[(3) - (3)].expr)->position.fin_ligne, (yyvsp[(1) - (3)].expr)->position.deb_car, (yyvsp[(3) - (3)].expr)->position.fin_car, (yyvsp[(1) - (3)].expr)->position.deb_car_tot, (yyvsp[(3) - (3)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PInfEq;
  (yyval.expr)->val.upinfeq.e1 = (yyvsp[(1) - (3)].expr);
  (yyval.expr)->val.upinfeq.e2 = (yyvsp[(3) - (3)].expr);
;}
    break;

  case 148:
#line 941 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (3)].expr)->position.deb_ligne, (yyvsp[(3) - (3)].expr)->position.fin_ligne, (yyvsp[(1) - (3)].expr)->position.deb_car, (yyvsp[(3) - (3)].expr)->position.fin_car, (yyvsp[(1) - (3)].expr)->position.deb_car_tot, (yyvsp[(3) - (3)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PSupEq;
  (yyval.expr)->val.upsupeq.e1 = (yyvsp[(1) - (3)].expr);
  (yyval.expr)->val.upsupeq.e2 = (yyvsp[(3) - (3)].expr);
;}
    break;

  case 149:
#line 947 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 150:
#line 951 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (3)].expr)->position.deb_ligne, (yyvsp[(3) - (3)].expr)->position.fin_ligne, (yyvsp[(1) - (3)].expr)->position.deb_car, (yyvsp[(3) - (3)].expr)->position.fin_car, (yyvsp[(1) - (3)].expr)->position.deb_car_tot, (yyvsp[(3) - (3)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PIPlus;
  (yyval.expr)->val.upiplus.e1 = (yyvsp[(1) - (3)].expr);
  (yyval.expr)->val.upiplus.e2 = (yyvsp[(3) - (3)].expr);
;}
    break;

  case 151:
#line 957 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (3)].expr)->position.deb_ligne, (yyvsp[(3) - (3)].expr)->position.fin_ligne, (yyvsp[(1) - (3)].expr)->position.deb_car, (yyvsp[(3) - (3)].expr)->position.fin_car, (yyvsp[(1) - (3)].expr)->position.deb_car_tot, (yyvsp[(3) - (3)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PIMoins;
  (yyval.expr)->val.upimoins.e1 = (yyvsp[(1) - (3)].expr);
  (yyval.expr)->val.upimoins.e2 = (yyvsp[(3) - (3)].expr);
;}
    break;

  case 152:
#line 963 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (3)].expr)->position.deb_ligne, (yyvsp[(3) - (3)].expr)->position.fin_ligne, (yyvsp[(1) - (3)].expr)->position.deb_car, (yyvsp[(3) - (3)].expr)->position.fin_car, (yyvsp[(1) - (3)].expr)->position.deb_car_tot, (yyvsp[(3) - (3)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PRPlus;
  (yyval.expr)->val.uprplus.e1 = (yyvsp[(1) - (3)].expr);
  (yyval.expr)->val.uprplus.e2 = (yyvsp[(3) - (3)].expr);
;}
    break;

  case 153:
#line 969 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (3)].expr)->position.deb_ligne, (yyvsp[(3) - (3)].expr)->position.fin_ligne, (yyvsp[(1) - (3)].expr)->position.deb_car, (yyvsp[(3) - (3)].expr)->position.fin_car, (yyvsp[(1) - (3)].expr)->position.deb_car_tot, (yyvsp[(3) - (3)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PRMoins;
  (yyval.expr)->val.uprmoins.e1 = (yyvsp[(1) - (3)].expr);
  (yyval.expr)->val.uprmoins.e2 = (yyvsp[(3) - (3)].expr);
;}
    break;

  case 154:
#line 975 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 155:
#line 979 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (3)].expr)->position.deb_ligne, (yyvsp[(3) - (3)].expr)->position.fin_ligne, (yyvsp[(1) - (3)].expr)->position.deb_car, (yyvsp[(3) - (3)].expr)->position.fin_car, (yyvsp[(1) - (3)].expr)->position.deb_car_tot, (yyvsp[(3) - (3)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PIMult;
  (yyval.expr)->val.upimult.e1 = (yyvsp[(1) - (3)].expr);
  (yyval.expr)->val.upimult.e2 = (yyvsp[(3) - (3)].expr);
;}
    break;

  case 156:
#line 985 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (3)].expr)->position.deb_ligne, (yyvsp[(3) - (3)].expr)->position.fin_ligne, (yyvsp[(1) - (3)].expr)->position.deb_car, (yyvsp[(3) - (3)].expr)->position.fin_car, (yyvsp[(1) - (3)].expr)->position.deb_car_tot, (yyvsp[(3) - (3)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PIDiv;
  (yyval.expr)->val.upidiv.e1 = (yyvsp[(1) - (3)].expr);
  (yyval.expr)->val.upidiv.e2 = (yyvsp[(3) - (3)].expr);
;}
    break;

  case 157:
#line 991 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (3)].expr)->position.deb_ligne, (yyvsp[(3) - (3)].expr)->position.fin_ligne, (yyvsp[(1) - (3)].expr)->position.deb_car, (yyvsp[(3) - (3)].expr)->position.fin_car, (yyvsp[(1) - (3)].expr)->position.deb_car_tot, (yyvsp[(3) - (3)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PIMod;
  (yyval.expr)->val.upimod.e1 = (yyvsp[(1) - (3)].expr);
  (yyval.expr)->val.upimod.e2 = (yyvsp[(3) - (3)].expr);
;}
    break;

  case 158:
#line 997 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (3)].expr)->position.deb_ligne, (yyvsp[(3) - (3)].expr)->position.fin_ligne, (yyvsp[(1) - (3)].expr)->position.deb_car, (yyvsp[(3) - (3)].expr)->position.fin_car, (yyvsp[(1) - (3)].expr)->position.deb_car_tot, (yyvsp[(3) - (3)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PRMult;
  (yyval.expr)->val.uprmult.e1 = (yyvsp[(1) - (3)].expr);
  (yyval.expr)->val.uprmult.e2 = (yyvsp[(3) - (3)].expr);
;}
    break;

  case 159:
#line 1003 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (3)].expr)->position.deb_ligne, (yyvsp[(3) - (3)].expr)->position.fin_ligne, (yyvsp[(1) - (3)].expr)->position.deb_car, (yyvsp[(3) - (3)].expr)->position.fin_car, (yyvsp[(1) - (3)].expr)->position.deb_car_tot, (yyvsp[(3) - (3)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PRDiv;
  (yyval.expr)->val.uprdiv.e1 = (yyvsp[(1) - (3)].expr);
  (yyval.expr)->val.uprdiv.e2 = (yyvsp[(3) - (3)].expr);
;}
    break;

  case 160:
#line 1009 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 161:
#line 1013 "pascal.parser.y"
    { 
  (yyval.expr) = new CPexpr((yyvsp[(1) - (2)].token).position.nb_lignes, (yyvsp[(2) - (2)].expr)->position.fin_ligne, (yyvsp[(1) - (2)].token).position.nb_char_ligne, (yyvsp[(2) - (2)].expr)->position.fin_car, (yyvsp[(1) - (2)].token).position.nb_char_tot, (yyvsp[(2) - (2)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PNot;
  (yyval.expr)->val.upnot.e = (yyvsp[(2) - (2)].expr);
;}
    break;

  case 162:
#line 1018 "pascal.parser.y"
    { 
  (yyval.expr) = new CPexpr((yyvsp[(1) - (2)].token).position.nb_lignes, (yyvsp[(2) - (2)].expr)->position.fin_ligne, (yyvsp[(1) - (2)].token).position.nb_char_ligne, (yyvsp[(2) - (2)].expr)->position.fin_car, (yyvsp[(1) - (2)].token).position.nb_char_tot, (yyvsp[(2) - (2)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PUIPlus;
  (yyval.expr)->val.upuiplus.e = (yyvsp[(2) - (2)].expr);
;}
    break;

  case 163:
#line 1023 "pascal.parser.y"
    { 
  (yyval.expr) = new CPexpr((yyvsp[(1) - (2)].token).position.nb_lignes, (yyvsp[(2) - (2)].expr)->position.fin_ligne, (yyvsp[(1) - (2)].token).position.nb_char_ligne, (yyvsp[(2) - (2)].expr)->position.fin_car, (yyvsp[(1) - (2)].token).position.nb_char_tot, (yyvsp[(2) - (2)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PUIMoins;
  (yyval.expr)->val.upuimoins.e = (yyvsp[(2) - (2)].expr);
;}
    break;

  case 164:
#line 1028 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (2)].token).position.nb_lignes, (yyvsp[(2) - (2)].expr)->position.fin_ligne, (yyvsp[(1) - (2)].token).position.nb_char_ligne, (yyvsp[(2) - (2)].expr)->position.fin_car, (yyvsp[(1) - (2)].token).position.nb_char_tot, (yyvsp[(2) - (2)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PURPlus;
  (yyval.expr)->val.upurplus.e = (yyvsp[(2) - (2)].expr);
;}
    break;

  case 165:
#line 1033 "pascal.parser.y"
    { 
  (yyval.expr) = new CPexpr((yyvsp[(1) - (2)].token).position.nb_lignes, (yyvsp[(2) - (2)].expr)->position.fin_ligne, (yyvsp[(1) - (2)].token).position.nb_char_ligne, (yyvsp[(2) - (2)].expr)->position.fin_car, (yyvsp[(1) - (2)].token).position.nb_char_tot, (yyvsp[(2) - (2)].expr)->position.fin_car_tot);
  (yyval.expr)->type = CPexpr::PURMoins;
  (yyval.expr)->val.upurmoins.e = (yyvsp[(2) - (2)].expr);
;}
    break;

  case 166:
#line 1038 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 167:
#line 1042 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (2)].expr)->position.deb_ligne, (yyvsp[(2) - (2)].token).position.nb_lignes, (yyvsp[(1) - (2)].expr)->position.deb_car, (yyvsp[(2) - (2)].token).position.nb_char_ligne + (yyvsp[(2) - (2)].token).position.longueur, (yyvsp[(1) - (2)].expr)->position.deb_car_tot, (yyvsp[(2) - (2)].token).position.nb_char_tot + (yyvsp[(2) - (2)].token).position.longueur); 
  (yyval.expr)->type = CPexpr::PInd;
  (yyval.expr)->val.upind.e = (yyvsp[(1) - (2)].expr);
;}
    break;

  case 168:
#line 1047 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(2) - (2)].expr)->position.deb_ligne, (yyvsp[(1) - (2)].token).position.nb_lignes, (yyvsp[(2) - (2)].expr)->position.deb_car, (yyvsp[(1) - (2)].token).position.nb_char_ligne + (yyvsp[(1) - (2)].token).position.longueur, (yyvsp[(2) - (2)].expr)->position.deb_car_tot, (yyvsp[(1) - (2)].token).position.nb_char_tot + (yyvsp[(1) - (2)].token).position.longueur); 
  (yyval.expr)->type = CPexpr::PRef;
  (yyval.expr)->val.upref.e = (yyvsp[(2) - (2)].expr);
;}
    break;

  case 169:
#line 1052 "pascal.parser.y"
    { 
  (yyval.expr) = new CPexpr((yyvsp[(1) - (4)].expr)->position.deb_ligne, (yyvsp[(4) - (4)].token).position.nb_lignes, (yyvsp[(1) - (4)].expr)->position.deb_car, (yyvsp[(4) - (4)].token).position.nb_char_ligne + (yyvsp[(4) - (4)].token).position.longueur, (yyvsp[(1) - (4)].expr)->position.deb_car_tot, (yyvsp[(4) - (4)].token).position.nb_char_tot + (yyvsp[(4) - (4)].token).position.longueur); 
  (yyval.expr)->type = CPexpr::PTab;
  (yyval.expr)->val.uptab.e1 = (yyvsp[(1) - (4)].expr);
  (yyval.expr)->val.uptab.e2 = (yyvsp[(3) - (4)].expr);
;}
    break;

  case 170:
#line 1058 "pascal.parser.y"
    {/*!!!!!!!!!!!!!*/
  (yyval.expr) = new CPexpr((yyvsp[(1) - (3)].expr)->position.deb_ligne, (yyvsp[(3) - (3)].token).position.nb_lignes, (yyvsp[(1) - (3)].expr)->position.deb_car, (yyvsp[(3) - (3)].token).position.nb_char_ligne + (yyvsp[(3) - (3)].token).position.longueur, (yyvsp[(1) - (3)].expr)->position.deb_car_tot, (yyvsp[(3) - (3)].token).position.nb_char_tot + (yyvsp[(3) - (3)].token).position.longueur); 
  (yyval.expr)->type = CPexpr::PRecord; 
  (yyval.expr)->val.uprecord.e = (yyvsp[(1) - (3)].expr);
  (yyval.expr)->val.uprecord.champ = (yyvsp[(3) - (3)].token).val.ident;
;}
    break;

  case 171:
#line 1064 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 172:
#line 1068 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 173:
#line 1069 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 174:
#line 1070 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 175:
#line 1074 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 176:
#line 1075 "pascal.parser.y"
    { 
  /* !!!!  */ 
  //$$ = $2; 
  /*
  $$->position = *(new pascal_position($1.position.nb_lignes, $3.position.nb_lignes, $1.position.nb_char_ligne, $3.position.nb_char_ligne + $3.position.longueur, $1.position.nb_char_tot, $3.position.nb_char_tot + $3.position.longueur));
  */
  (yyval.expr) = (yyvsp[(2) - (3)].expr);
;}
    break;

  case 177:
#line 1090 "pascal.parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 178:
#line 1091 "pascal.parser.y"
    { 
  (yyval.expr) = new CPexpr((yyvsp[(1) - (1)].token).position.nb_lignes, (yyvsp[(1) - (1)].token).position.nb_lignes, (yyvsp[(1) - (1)].token).position.nb_char_ligne, (yyvsp[(1) - (1)].token).position.nb_char_ligne + (yyvsp[(1) - (1)].token).position.longueur, (yyvsp[(1) - (1)].token).position.nb_char_tot, (yyvsp[(1) - (1)].token).position.nb_char_tot + (yyvsp[(1) - (1)].token).position.longueur); 
  (yyval.expr)->type = CPexpr::PConst; 
  (yyval.expr)->val.upconst.pconst.type.type = pevaltype::PETInteger; 
  (yyval.expr)->val.upconst.pconst.val.val.i = (yyvsp[(1) - (1)].token).val.entier; 
;}
    break;

  case 179:
#line 1097 "pascal.parser.y"
    { 
  (yyval.expr) = new CPexpr((yyvsp[(1) - (1)].token).position.nb_lignes, (yyvsp[(1) - (1)].token).position.nb_lignes, (yyvsp[(1) - (1)].token).position.nb_char_ligne, (yyvsp[(1) - (1)].token).position.nb_char_ligne + (yyvsp[(1) - (1)].token).position.longueur, (yyvsp[(1) - (1)].token).position.nb_char_tot, (yyvsp[(1) - (1)].token).position.nb_char_tot + (yyvsp[(1) - (1)].token).position.longueur); 
  (yyval.expr)->type = CPexpr::PConst; 
  (yyval.expr)->val.upconst.pconst.type.type = pevaltype::PETReal; 
  (yyval.expr)->val.upconst.pconst.val.val.r = (yyvsp[(1) - (1)].token).val.reel; 
;}
    break;

  case 180:
#line 1103 "pascal.parser.y"
    { 
  (yyval.expr) = new CPexpr((yyvsp[(1) - (1)].token).position.nb_lignes, (yyvsp[(1) - (1)].token).position.nb_lignes, (yyvsp[(1) - (1)].token).position.nb_char_ligne, (yyvsp[(1) - (1)].token).position.nb_char_ligne + (yyvsp[(1) - (1)].token).position.longueur, (yyvsp[(1) - (1)].token).position.nb_char_tot, (yyvsp[(1) - (1)].token).position.nb_char_tot + (yyvsp[(1) - (1)].token).position.longueur); 
  (yyval.expr)->type = CPexpr::PConst; 
  (yyval.expr)->val.upconst.pconst.type.type = pevaltype::PETString; 
  (yyval.expr)->val.upconst.pconst.val.val.str = (yyvsp[(1) - (1)].token).val.chaine; 
;}
    break;

  case 181:
#line 1109 "pascal.parser.y"
    { 
  (yyval.expr) = new CPexpr((yyvsp[(1) - (1)].token).position.nb_lignes, (yyvsp[(1) - (1)].token).position.nb_lignes, (yyvsp[(1) - (1)].token).position.nb_char_ligne, (yyvsp[(1) - (1)].token).position.nb_char_ligne + (yyvsp[(1) - (1)].token).position.longueur, (yyvsp[(1) - (1)].token).position.nb_char_tot, (yyvsp[(1) - (1)].token).position.nb_char_tot + (yyvsp[(1) - (1)].token).position.longueur); 
  (yyval.expr)->type = CPexpr::PIdent; 
  (yyval.expr)->val.upident.pident = (yyvsp[(1) - (1)].token).val.ident;
;}
    break;

  case 182:
#line 1114 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (1)].token).position.nb_lignes, (yyvsp[(1) - (1)].token).position.nb_lignes, (yyvsp[(1) - (1)].token).position.nb_char_ligne, (yyvsp[(1) - (1)].token).position.nb_char_ligne + (yyvsp[(1) - (1)].token).position.longueur, (yyvsp[(1) - (1)].token).position.nb_char_tot, (yyvsp[(1) - (1)].token).position.nb_char_tot + (yyvsp[(1) - (1)].token).position.longueur); 
  (yyval.expr)->type = CPexpr::PConst; 
  (yyval.expr)->val.upconst.pconst.type.type = pevaltype::PETPointer;
  (yyval.expr)->val.upconst.pconst.type.val.ptr = new pevaltype;
  (yyval.expr)->val.upconst.pconst.type.val.ptr->type = pevaltype::PETVide;
  (yyval.expr)->val.upconst.pconst.val.val.ptr = 0;
;}
    break;

  case 183:
#line 1122 "pascal.parser.y"
    {
  (yyval.expr) = new CPexpr((yyvsp[(1) - (7)].token).position.nb_lignes, (yyvsp[(7) - (7)].token).position.nb_lignes, (yyvsp[(1) - (7)].token).position.nb_char_ligne, (yyvsp[(7) - (7)].token).position.nb_char_ligne + (yyvsp[(7) - (7)].token).position.longueur, (yyvsp[(1) - (7)].token).position.nb_char_tot, (yyvsp[(7) - (7)].token).position.nb_char_tot + (yyvsp[(7) - (7)].token).position.longueur); 
  (yyval.expr)->type = CPexpr::PMenu;
  (yyval.expr)->val.upmenu.nom = (yyvsp[(3) - (7)].token).val.chaine;
  (yyval.expr)->val.upmenu.pitems = (yyvsp[(6) - (7)].pitems);
;}
    break;

  case 184:
#line 1131 "pascal.parser.y"
    { 
    (yyval.expr) = new CPexpr((yyvsp[(1) - (1)].token).position.nb_lignes, (yyvsp[(1) - (1)].token).position.nb_lignes, (yyvsp[(1) - (1)].token).position.nb_char_ligne, (yyvsp[(1) - (1)].token).position.nb_char_ligne + (yyvsp[(1) - (1)].token).position.longueur, (yyvsp[(1) - (1)].token).position.nb_char_tot, (yyvsp[(1) - (1)].token).position.nb_char_tot + (yyvsp[(1) - (1)].token).position.longueur); 
    (yyval.expr)->type = CPexpr::PConst; 
    (yyval.expr)->val.upconst.pconst.type.type = pevaltype::PETBoolean; 
    (yyval.expr)->val.upconst.pconst.val.val.b = true; 
  ;}
    break;

  case 185:
#line 1137 "pascal.parser.y"
    { 
    (yyval.expr) = new CPexpr((yyvsp[(1) - (1)].token).position.nb_lignes, (yyvsp[(1) - (1)].token).position.nb_lignes, (yyvsp[(1) - (1)].token).position.nb_char_ligne, (yyvsp[(1) - (1)].token).position.nb_char_ligne + (yyvsp[(1) - (1)].token).position.longueur, (yyvsp[(1) - (1)].token).position.nb_char_tot, (yyvsp[(1) - (1)].token).position.nb_char_tot + (yyvsp[(1) - (1)].token).position.longueur); 
    (yyval.expr)->type = CPexpr::PConst; 
    (yyval.expr)->val.upconst.pconst.type.type = pevaltype::PETBoolean; 
    (yyval.expr)->val.upconst.pconst.val.val.b = false; 
  ;}
    break;

  case 186:
#line 1148 "pascal.parser.y"
    { (yyval.pitems) = mp((yyvsp[(1) - (2)].item), (yyvsp[(2) - (2)].pitems)); ;}
    break;

  case 187:
#line 1149 "pascal.parser.y"
    { (yyval.pitems) = mp((yyvsp[(1) - (1)].item), (class pliste<struct CPexpr::utype::SPMenu::item> *)NULL); ;}
    break;

  case 188:
#line 1150 "pascal.parser.y"
    { (yyval.pitems) = (class pliste<struct CPexpr::utype::SPMenu::item> *)NULL; ;}
    break;

  case 189:
#line 1154 "pascal.parser.y"
    { (yyval.pitems) = mp((yyvsp[(2) - (3)].item), (yyvsp[(3) - (3)].pitems)); ;}
    break;

  case 190:
#line 1155 "pascal.parser.y"
    { (yyval.pitems) = (yyvsp[(2) - (2)].pitems); ;}
    break;

  case 191:
#line 1156 "pascal.parser.y"
    { (yyval.pitems) = mp((yyvsp[(2) - (2)].item), (class pliste<struct CPexpr::utype::SPMenu::item> *)NULL); ;}
    break;

  case 192:
#line 1157 "pascal.parser.y"
    { (yyval.pitems) = (class pliste<struct CPexpr::utype::SPMenu::item> *)NULL; ;}
    break;

  case 193:
#line 1161 "pascal.parser.y"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 194:
#line 1162 "pascal.parser.y"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 195:
#line 1166 "pascal.parser.y"
    {
  (yyval.item) = new CPexpr::utype::SPMenu::item;
  (yyval.item)->message = (yyvsp[(3) - (4)].token).val.chaine;
  (yyval.item)->iconfile = NULL;
;}
    break;

  case 196:
#line 1174 "pascal.parser.y"
    {
  (yyval.item) = new CPexpr::utype::SPMenu::item;
  (yyval.item)->message = (yyvsp[(3) - (6)].token).val.chaine;
  (yyval.item)->iconfile = (yyvsp[(5) - (6)].token).val.chaine;
;}
    break;


/* Line 1267 of yacc.c.  */
#line 3524 "pascal.parser.cpp"
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


#line 1186 "pascal.parser.y"




static const void yyerror(char s[]) {
  //(void) printf("Erreur PARSING.");
  pmesserr("Erreur d'analyse syntaxique.");
  (void) fprintf(yypascalout, "Erreur d'analyse syntaxique.");
}

