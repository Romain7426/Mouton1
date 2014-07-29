#ifndef GLOBAL_H
#define GLOBAL_H

/*
* IMPORTANT: dans les options de compilations de DevCpp, il faut que
* la case ANSI C soit décochée.  Le jeu perd ainsi 500ko d'un coup, et
* les fichiers stdout.txt et stderr.txt sont générés.
*/

#ifdef WINDOWS_DEV_CPP
#  define ASPRINTF_IS_NOT_PROVIDED
#  define BZERO_IS_NOT_PROVIDED
#  define USE_FREAD_INSTEAD_OF_STAT
#  define random rand
#  define srandom srand
#endif

#include <stdlib.h>
#include <stdint.h> // int8_t, etc., intmax_t , uintmax_t, 
#include <inttypes.h> // uint8_t, ..., uintmax_t i = UINTMAX_MAX; // this type always exists 
//#include <stdbool.h> // define a «bool» type which extends to «_Bool»
#include <stddef.h> // offsetof(type, member-designator) 
#include <stdio.h> // remove, int rename(const char *old, const char *new); , 
#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include <math.h>     // cosf, ..., int signbit(real-floating x); , isnormal(neither zero, subnormal, infinite, nor NaN)., int isnan(real-floating x); , int isinf(real-floating x); int isfinite(real-floating x); 
#include <ctype.h>    // tolower, toupper
#include <assert.h>  // dépend de la valeur de la macro NDEBUG 
#include <complex.h>  // types «complex», «double complex», «long double complex», «float complex» 
#include <ctype.h> 
#include <errno.h> 
#include <float.h> // limits 
#include <iso646.h>  // Alternative spellings: and &&, xor ^, etc. 
#include <limits.h> 
#include <setjmp.h> 
#include <signal.h> 
#include <time.h> // clock & time --- 
#include <wchar.h> 
#include <wctype.h> 
#include <locale.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#ifdef FENV_H_EXISTS
#  include <fenv.h> // floating-point environment 
#endif

#ifdef SYS_FENV_H_EXISTS
#  include <sys/fenv.h> // floating-point environment 
#endif

#ifdef LANGINFO_H_EXISTS
#  include <langinfo.h> // pas fournie sous WIN
#endif 

#ifdef TGMATH_H_EXISTS
#  include <tgmath.h> // includes the headers <math.h> and <complex.h>
#endif


#ifdef CTIME_R_IS_NEEDED_AND_IS_NOT_PROVIDED
// CTIME
// Attention!!!!! ctime n'est pas n'est pas thread safe!!!!
// il retourne un pointeur vers une chaîne allouée statiquement et c'est la même à chaque fois
// faut mieux utiliser plutôt ctime_r() qui est thread safe
//  char * ctime(const time_t * clock)
//  char * ctime_r(const time_t * clock, char * buf);
// La taille de buf doit etre au minimum de 26 octets.
// De plus, apparemment, elle ne marche pas pareil sous MacOSX et sous Windows.
#ifndef ctime_r
// time_t time(time_t *tloc);
// char * ctime(const time_t * clock);
// char * ctime_r(const time_t * clock, char * buf);
#  define ctime_r(a,b) ((b == NULL ? 0 : strcpy(b, "FAILED ")), *a = time(NULL), ctime(a))
#endif
#endif




#include <SDL/SDL.h> //bibliothèque graphique 2D...
#include <SDL_image.h> /* pour ouvrir des images d'autres formats que BMP (notamment des images au format PNG) */
#include <SDL_mixer.h>

#ifdef SYS_MACOSX
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#endif /* MACOSX */

#ifdef SYS_OPENBSD
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif /* MACOSX */

#ifdef SYS_WIN32
 #include <winsock2.h>
 #include <windows.h>
 #include <GL/gl.h>
 #include <GL/glu.h>
#endif //_WIN32


  






enum bool {true = (0 == 0), false = (0 != 0)};
typedef enum bool bool;

#ifndef BOOL_T
#define BOOL_T
typedef bool bool_t;
#endif

#ifndef INT_T
#define INT_T
typedef int int_t;
#endif

#ifndef UINT_T
#define UINT_T
typedef unsigned int uint_t;
#endif

typedef uint8_t byte;
typedef uint16_t word;
typedef uint32_t dword;
typedef uint64_t qword;

typedef int32_t integer;
typedef integer entier;

typedef double real;

#ifndef REAL_T
#define REAL_T
typedef real real_t;
#endif


typedef char str_t;

#include "biglib.h"
#include "biglib_suppl.h"
#include "biglib.h"

#define TYPEDEF_TYPENAME_WITHOUT_STRUCT(TYPENAME)	\
  typedef struct TYPENAME TYPENAME;

#define DECLARE_NEW_OPERATOR_FOR_STRUCT(TYPENAME)		\
  extern struct TYPENAME * glue(new_,TYPENAME)(void);			\

#define DEFINE_NEW_OPERATOR_FOR_STRUCT DEFINE_NEW_OPERATOR_FOR_STRUCT0

#define DEFINE_NEW_OPERATOR_FOR_STRUCT0(TYPENAME)		\
  struct TYPENAME * glue(new_,TYPENAME)(void) {			\
    struct TYPENAME * this = NULL;				\
    this = (struct TYPENAME *) malloc(sizeof(struct TYPENAME)); \
    bzero(this, sizeof(struct TYPENAME));			\
    return this;						\
  }

#define DEFINE_NEW_OPERATOR_FOR_STRUCT1(TYPENAME,FIELDNAME1)	\
  struct TYPENAME * glue(new_,TYPENAME)(void) {			\
    struct TYPENAME * this = NULL;				\
    this = (struct TYPENAME *) malloc(sizeof(struct TYPENAME)); \
    bzero(this, sizeof(struct TYPENAME));			\
    this -> FIELDNAME1 = FIELDNAME1;				\
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

#define RGBA(r,v,b,a) (((a * 256 + v) * 256 + b) * 256 + r)


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




#ifdef _WIN32
 #define GL_BGR GL_BGR_EXT
 #define GL_BGRA GL_BGRA_EXT
#endif








                                  

#include "vectors.h" // pour pouvoir utiliser des vecteurs 2D et 3D
#include "keys.h"

#include "messages.h"
#include "utilities.h"
#include "structures.h"
#include "constantes.h"

#include "3ds.h"
#include "action.h"
#include "affichagemainpierre.h"
#include "apiscript.h"
#include "arme.h"
#include "asprintf.h"
#include "biglib.h"
#include "biglib_rm_recursive.h"
#include "biglib_suppl.h"
#include "bonhomme.h"
#include "camera.h"
#include "coeurs.h"
#include "constantes.h"
#include "dico.h"
#include "evenement.h"
#include "evenements.h"
#include "global.h"
#include "kernel.h"
#include "keys.h"
#include "liste.h"
#include "main.h"
#include "map.h"
#include "menu.h"
#include "menuentreenom.h"
#include "messages.h"
#include "moteurdeplacement.h"
#include "moteurteleportation.h"
#include "obj3ds.h"
#include "objnonanime.h"
#include "pagetitre.h"
#include "pascal.h"
#include "physicalobj.h"
#include "ressource.h"
#include "sol.h"
#include "son.h"
#include "structures.h"
#include "text.h"
#include "texture.h"
#include "timer.h"
#include "utilities.h"
#include "vectors.h"



#endif /* GLOBAL_H */
