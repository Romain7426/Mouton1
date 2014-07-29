#ifndef GLOBAL_HPP
#define GLOBAL_HPP

/* 
 * GLOBAL.H contient les références à SDL, et OpenGL… tous les
 * fichiers du projets peuvent utiliser ce fichier, dès qu'ils veulent
 * utiliser SDL ou OpenGL
 */
/*
* IMPORTANT: dans les options de compilations de DevCpp, il faut que
* la case ANSI C soit décochée.  Le jeu perd ainsi 500ko d'un coup, et
* les fichiers stdout.txt et stderr.txt sont générés.
*/

#include "biglib.h"

#define DEFINE_NEW_OPERATOR_FOR_STRUCT(TYPENAME)		\
  static struct TYPENAME * glue(new_,TYPENAME)(void) {		\
    struct TYPENAME * this = NULL;				\
    this = (struct TYPENAME *) malloc(sizeof struct NAME);	\
    bzero(this, sizeof struct NAME);				\
    return this;						\
  }



#define AFFICHER_CUBE_DEBUG true
#define DEBUG_MOTEUR_PHYSIQUE true

#if 0
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#else
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#endif
#define SCREEN_DEPTH 24

#ifndef MACOSX
#define SCREEN_MODE SDL_RESIZABLE/*SDL_RESIZABLE, SDL_FULLSCREEN*/
#else
#define SCREEN_MODE SDL_RESIZABLE/*SDL_RESIZABLE, SDL_FULLSCREEN*/
#endif

#define BINDIR "."
#define ROOTDIR BINDIR "/" ".."
//#define SRCDIR ROOTDIR  "/src/"
//#define INCLUDEDIR ROOTDIR  "/include/"
#define LOGDIR ROOTDIR  "/log/"
#define DATADIR ROOTDIR "/" "data"

#define SONSDIR DATADIR  "/sons/"
#define MUSIQUESDIR DATADIR  "/musiques/"
#define ANIMESDIR DATADIR  "/" "animes/"
#define NONANIMESDIR DATADIR  "/nonanimes/"
#define CARTESDIR DATADIR  "/cartes/"
#define NIVEAUXDIR CARTESDIR
#define T3DSDIR DATADIR "/3ds/"
#define TEXTURESDIR DATADIR  "/textures/"
#define TEXTURESICONEMENUDIR DATADIR  "/textures/menu/"
#define PASCALDIR DATADIR "/pascal/"



#include <SDL.h> //bibliothèque graphique 2D...
#include <SDL_image.h> /* pour ouvrir des images d'autres formats que BMP (notamment des images au format PNG) */
#include <SDL_mixer.h>
  

#ifdef LIBPROG_SYS_MACOSX
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#endif /* MACOSX */

#ifdef LIBPROG_SYS_OPENBSD
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif /* MACOSX */

#ifdef _WIN32
 #include <winsock2.h>
 #include <windows.h>
 #undef _MAC
 #undef _LINUX
 #include <GL/gl.h>
 #include <GL/glu.h>
#endif //_WIN32

#ifdef _MAC
 #include <GLUT/glut.h>
#endif //_MAC

#ifdef _LINUX
 #include <GL/gl.h>
 #include <GL/glu.h>
#endif //_LINUX

#ifdef _CYGWIN
 #include <GL/gl.h>
 #include <GL/glu.h>
#endif //_CYGWIN

#ifdef _WIN32
 #define GL_BGR GL_BGR_EXT
 #define GL_BGRA GL_BGRA_EXT
#endif




#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // besoin pour les parsers et les lexers; va savoir pourquoi...
                    //  besoin de la fonction isatty(int)
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include <locale.h>
#ifndef WIN
# include <langinfo.h> // pas fournie sous WIN
# include <errno.h> // déjà défini dans stdlib.h
#endif 
#include <time.h> // time_t, time(), ctime() ;  ("man 3 time") donne la date d'ajd
// Attention !!!!! ctime n'est pas n'est pas thread safe !!!!
// il retourne un pointeur vers une chaine allouee statiquement et c'est la meme a chaque fois.
// utilise plutot ctime_r() qui l'est.
//  char * ctime(const time_t *clock)
//  char * ctime_r(const time_t *clock, char *buf);
// La taille de buf doit etre au minimum de 26 octets.
#ifdef WIN
//# define ctime_r(a,b) ((b == NULL ? 0 : strcpy(b, "FAILED")), ctime(a))
# define ctime_r(a,b) ((b == NULL ? 0 : strcpy(b, "FAILED ")), *a = time(NULL), ctime(a))
#endif

                                  

#include <math.h>
#include "vectors.hpp" // pour pouvoir utiliser des vecteurs 2D et 3D
#include "keys.hpp"

#include "messages.hpp"
#include "utilities.hpp"
#include "structures.hpp"
#include "constantes.hpp"


//#include "son.h"

//#include "text.h" 
// pour pouvoir afficher du texte
// je sais…
// c'est un peu la honte de devoir écrire qch pour pouvoir
// juste afficher du texte :( mais bon…

//#include "map.h"
//#include "texture.h" // contient la classe pour utiliser des textures
//#include "texture.h"



//extern void DemanderAQuitterLeJeu();
//extern bool isrunning;
//extern TMouse Mouse;



#endif /* GLOBAL_HPP */
