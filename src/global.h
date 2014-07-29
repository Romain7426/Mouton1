#ifndef GLOBAL_H
#define GLOBAL_H

#define _GNU_SOURCE // pour avoir asprintf sous Debian qui est dans <stdio.h>

#ifdef WINDOWS_DEV_CPP
# define ASPRINTF_IS_NOT_PROVIDED
# define BZERO_IS_NOT_PROVIDED
# define USE_FREAD_INSTEAD_OF_STAT
# define random rand
# define srandom srand
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

#ifndef FENV_H_EXISTS
#  include <fenv.h> // floating-point environment 
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
# define ctime_r(a,b) ((b == NULL ? 0 : strcpy(b, "FAILED ")), *a = time(NULL), ctime(a))
#endif
#endif





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
typedef real reel;

#ifndef REAL_T
#define REAL_T
typedef real real_t;
#endif


typedef char str_t;

struct str_liste_t;
#ifndef STR_LISTE_T
#define STR_LISTE_T
#ifndef __cplusplus
typedef struct str_liste_t str_liste_t;
#endif
#endif

struct str_tableau_t;
typedef struct str_tableau_t str_tableau_t;


#include "tableau.h"
#include "str_tableau.h"
#include "str_liste.h"
#include "biglib.h"
#include "biglib_suppl.h"
#include "structures.h"




#endif /* GLOBAL_H */
