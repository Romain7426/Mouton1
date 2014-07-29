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
extern YYSTYPE yycartelval;
