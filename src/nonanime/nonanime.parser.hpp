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
     Token_Booleen = 258,
     Token_Entier = 259,
     Token_Reel = 260,
     Token_Chaine = 261,
     Token_Ident = 262,
     Token_LAction = 263,
     Token_Assign = 264,
     Token_OpenPar = 265,
     Token_OpenBrace = 266,
     Token_OpenBracket = 267,
     Token_ClosePar = 268,
     Token_CloseBrace = 269,
     Token_CloseBracket = 270,
     Token_Ptvirg = 271,
     Token_Virgule = 272,
     Token_EOF = 273,
     Token_Zone = 274,
     Token_Choc = 275,
     Token_Masse = 276,
     Token_Invinsible = 277,
     Token_Elements = 278,
     Token_Racines = 279,
     Token_Action = 280,
     Token_Menu = 281,
     Token_Affichage = 282,
     Token_Gestionnaire = 283,
     Token_Evenement = 284,
     Token_Genere = 285,
     Token_Par = 286,
     Token_Traitement = 287,
     Token_Element = 288,
     Token_Fils = 289,
     Token_Angle = 290,
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
     Token_Largeur = 301,
     Token_Longueur = 302,
     Token_Hauteur = 303,
     Token_Physique = 304,
     Token_Gameplay = 305,
     Token_Graphique = 306,
     Token_Compressible = 307,
     Token_Fixe = 308,
     Token_Coefficient = 309,
     Token_Rebondissement = 310,
     Token_Fichier = 311,
     Token_Procedure = 312,
     Token_Icone = 313,
     Token_PlusEntier = 314,
     Token_MoinsEntier = 315,
     Token_MultEntier = 316,
     Token_DivEntier = 317,
     Token_ModEntier = 318,
     Token_PlusReel = 319,
     Token_MoinsReel = 320,
     Token_MultReel = 321,
     Token_DivReel = 322
   };
#endif
/* Tokens.  */
#define Token_Booleen 258
#define Token_Entier 259
#define Token_Reel 260
#define Token_Chaine 261
#define Token_Ident 262
#define Token_LAction 263
#define Token_Assign 264
#define Token_OpenPar 265
#define Token_OpenBrace 266
#define Token_OpenBracket 267
#define Token_ClosePar 268
#define Token_CloseBrace 269
#define Token_CloseBracket 270
#define Token_Ptvirg 271
#define Token_Virgule 272
#define Token_EOF 273
#define Token_Zone 274
#define Token_Choc 275
#define Token_Masse 276
#define Token_Invinsible 277
#define Token_Elements 278
#define Token_Racines 279
#define Token_Action 280
#define Token_Menu 281
#define Token_Affichage 282
#define Token_Gestionnaire 283
#define Token_Evenement 284
#define Token_Genere 285
#define Token_Par 286
#define Token_Traitement 287
#define Token_Element 288
#define Token_Fils 289
#define Token_Angle 290
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
#define Token_Largeur 301
#define Token_Longueur 302
#define Token_Hauteur 303
#define Token_Physique 304
#define Token_Gameplay 305
#define Token_Graphique 306
#define Token_Compressible 307
#define Token_Fixe 308
#define Token_Coefficient 309
#define Token_Rebondissement 310
#define Token_Fichier 311
#define Token_Procedure 312
#define Token_Icone 313
#define Token_PlusEntier 314
#define Token_MoinsEntier 315
#define Token_MultEntier 316
#define Token_DivEntier 317
#define Token_ModEntier 318
#define Token_PlusReel 319
#define Token_MoinsReel 320
#define Token_MultReel 321
#define Token_DivReel 322




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 65 "nonanime.parser.y"
{
booleen yybooleen;
int yyentier;
double yyreel;
char *yychaine;
char *yyident;
char *yynom;
nonanime_action yylaction;

nonanime_tcode *code;
nonanime_sgenere *genere;
nonanime_filsdesc *yyfilsdesc;
nonanime_tfils *fils;
nonanime_telement *element;
nonanime_tevent *event;
nonanime_taction *yyaction;
liste *yyliste;
nonanime_tnonanime *nonanime;
nonanime_tphysique *physique;
nonanime_tgameplay *gameplay;
nonanime_tgraphique *graphique;
}
/* Line 1529 of yacc.c.  */
#line 206 "nonanime.parser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yynonanimelval;

