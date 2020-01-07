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
#include <langinfo.h> 

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

//#include <OpenGL/gl.h>


#ifdef SYS_MACOSX
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#endif /* MACOSX */

//#ifdef SYS_OPENBSD
//#ifdef BSD 
#ifdef __OpenBSD__
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

#define _STRINGIFY(s) #s
#define STRINGIFY(s) _STRINGIFY(s)

#define BYTELEN(s)   (sizeof(s)) 
#define ARRAYLEN(s)  (sizeof(s)/sizeof(*s)) 
#define ARRAY_SIZE    ARRAYLEN 
//#define STRLEN(s)  (ARRAYLEN(s)-1) 
// Beware of a string like "bob\0and\0mary", whose the preprocessor STRLEN will never behave like the compile-one (12 vs 3). 
// Therefore this one is kind of more accurate. 

#include "biglib.h"
#include "biglib_suppl.h"
#include "biglib.h"


#if 0
#define TYPEDEF_TYPENAME_WITHOUT_STRUCT(TYPENAME)	\
  struct TYPENAME;					\
  #ifndef glue3(TYPE_,TYPENAME,_IS_DEFINED)		\
  #define glue3(TYPE_,TYPENAME,_IS_DEFINED)		\
  typedef struct TYPENAME TYPENAME;			\
  #endif
#else
#define TYPEDEF_TYPENAME_WITHOUT_STRUCT(TYPENAME)	\
  struct TYPENAME;					\
  typedef struct TYPENAME TYPENAME;			
#endif

#define TYPEDEF_TYPENAME_WITHOUT_ENUM(TYPENAME)	\
  typedef enum TYPENAME TYPENAME;

#define DECLARE_NEW_OPERATOR_FOR_STRUCT(TYPENAME)			\
  extern struct TYPENAME * glue(new_,TYPENAME)(void);			\
					      
#define DEFINE_NEW_OPERATOR_FOR_STRUCT DEFINE_NEW_OPERATOR_FOR_STRUCT0

#define DEFINE_NEW_OPERATOR_FOR_STRUCT0(TYPENAME)			\
  static struct TYPENAME * glue(new_,TYPENAME)(void) {			\
    struct TYPENAME * this = NULL;					\
    this = (struct TYPENAME *) malloc(sizeof(struct TYPENAME));		\
    bzero(this, sizeof(struct TYPENAME));				\
    return this;							\
  }

#define MALLOC_BZERO(ctype_t,this) ctype_t * this = NULL; this = (ctype_t *) malloc(sizeof(*this)); bzero(this, sizeof(*this)); 
#define ASSIGN_METHOD(ctype_t,this,method_name) this -> method_name = glue3(ctype_t,__,method_name); 

#define DEFINE_NEW_OPERATOR_FOR_STRUCT1(TYPENAME,FIELDNAME1,FUNNAME_FOR_ATTRIBUTS) \
  struct TYPENAME * glue(new_,TYPENAME)(void) {				\
    struct TYPENAME * this = NULL;					\
    this = (struct TYPENAME *) malloc(sizeof(struct TYPENAME));		\
    bzero(this, sizeof(struct TYPENAME));				\
    this -> FIELDNAME1 = FIELDNAME1;					\
    FUNNAME_FOR_ATTRIBUTS(this);					\
    return this;							\
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








                                  
#include "biglib.h"
#include "biglib_rm_recursive.h"
#include "biglib_suppl.h"

#include "messages.h"
#include "utilities.h"
#include "structures.h"
#include "constantes.h"

#include "asprintf.h"

struct CSon;
typedef struct CSon CSon; 
 
struct CMusique;
typedef struct CMusique CMusique; 

struct CCamera; 
typedef struct CCamera CCamera; 

struct CAffichageCoeur;
typedef struct CAffichageCoeur CAffichageCoeur; 

struct CMap; 
typedef struct CMap CMap; 

struct CEvenement; 
typedef struct CEvenement CEvenement; 

struct CBonhomme; 
typedef struct CBonhomme CBonhomme; 
 
struct CTexture; 
typedef struct CTexture CTexture; 

struct CPascal;
typedef struct CPascal CPascal; 

struct pascal_mem;
typedef struct pascal_mem pascal_mem;
typedef struct pascal_mem pmem;

struct pascal_env; 
typedef struct pascal_env pascal_env; 
typedef pascal_env penv;

struct CPprog; 
typedef struct CPprog CPprog; 

struct pascal_eval_type;
typedef struct pascal_eval_type pascal_eval_type;
typedef struct pascal_eval_type pevaltype;

struct pascal_evalt;
typedef struct pascal_evalt pascal_evalt;
typedef struct pascal_evalt pevalt;

struct pascal_dval_type_user; 
typedef struct pascal_dval_type_user pascal_dval_type_user;
typedef pascal_dval_type_user pdvaltypeuser;

struct pascal_dvalt;
typedef struct pascal_dvalt pascal_dvalt; 
typedef pascal_dvalt pdvalt;

struct pascal_dval_type;
typedef struct pascal_dval_type pascal_dval_type;
typedef pascal_dval_type pdvaltype;


struct CPexpr;
typedef struct CPexpr CPexpr;

struct pascal_stack_t; 
typedef struct pascal_stack_t pascal_stack_t; 

struct CScriptLauncher;
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CScriptLauncher);

struct CObjActionnable;
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CObjActionnable);

struct MenuItem; 
TYPEDEF_TYPENAME_WITHOUT_STRUCT(MenuItem);

struct CMenuAbstrait; 
typedef struct CMenuAbstrait CMenuAbstrait; 

struct CMenu; 
typedef struct CMenu CMenu; 

struct CMiniMenu; 
typedef struct CMiniMenu CMiniMenu; 
 
struct CActionsMenu; 
typedef struct CActionsMenu CActionsMenu; 

struct CMenuEntreeNom; 
typedef struct CMenuEntreeNom CMenuEntreeNom; 
 
struct CText; 
typedef struct CText CText; 

struct CMessageTexte; 
typedef struct CMessageTexte CMessageTexte; 

struct CKey; 
typedef struct CKey CKey; 

struct CAffichageMainPierre; 
typedef struct CAffichageMainPierre CAffichageMainPierre; 

struct CObjNonAnime;
typedef struct CObjNonAnime CObjNonAnime; 
 
struct api_contexte_t; 
TYPEDEF_TYPENAME_WITHOUT_STRUCT(api_contexte_t);

struct CMoteurTeleportation; 
typedef struct CMoteurTeleportation CMoteurTeleportation; 
 
struct CPageTitre;
typedef struct CPageTitre CPageTitre; 

struct COrdresDeplacement; 
typedef struct COrdresDeplacement COrdresDeplacement; 

struct C3DS;
typedef struct C3DS C3DS; 


#include "vectors.h" // pour pouvoir utiliser des vecteurs 2D et 3D
#include "keys.h"

#include "3ds.h"
#include "texture.h"
#include "sol.h"
#include "menu.h"
#include "action.h"
#include "physicalobj.h"
#include "bonhomme.h"
#include "evenement.h"
#include "evenements.h"
#include "map.h"
#include "menuentreenom.h"

#include "arme.h"


#include "camera.h"
#include "coeurs.h"
#include "constantes.h"
#include "dico.h"
#include "global.h"
#include "kernel.h"
#include "keys.h"
#include "liste.h"
#include "main.h"
#include "messages.h"
#include "moteurdeplacement.h"
#include "moteurteleportation.h"
#include "obj3ds.h"
#include "objnonanime.h"
#include "pagetitre.h"
#include "pascal.h"
#include "ressource.h"
#include "son.h"
#include "structures.h"
#include "text.h"
#include "timer.h"
#include "utilities.h"

#include "apiscript.h"
#include "affichagemainpierre.h"



#endif /* GLOBAL_H */
