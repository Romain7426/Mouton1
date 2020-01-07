/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
/* Line 1529 of yacc.c.  */
#line 291 "pascal.parser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yypascallval;

