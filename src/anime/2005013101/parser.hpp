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
/* Line 1252 of yacc.c.  */
#line 168 "parser.hpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



