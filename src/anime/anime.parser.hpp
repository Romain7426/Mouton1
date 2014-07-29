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
/* Line 1529 of yacc.c.  */
#line 197 "anime.parser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yyanimelval;

