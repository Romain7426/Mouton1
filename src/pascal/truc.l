# 1 "pascal.lexer.l"
#pragma GCC set_debug_pwd "/Users/romain/Projet/Zelda/pascal"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "pascal.lexer.l"
%{

  // Fichier lexer du compilateur PASCAL et de la machine virtuelle PASCAL.


# 1 "/usr/include/stdio.h" 1 3 4

# 23 "/usr/include/stdio.h" 3 4

# 60 "/usr/include/stdio.h" 3 4





# 1 "/usr/include/sys/types.h" 1 3 4

# 22 "/usr/include/sys/types.h" 3 4


# 62 "/usr/include/sys/types.h" 3 4




# 1 "/usr/include/sys/appleapiopts.h" 1 3 4

# 22 "/usr/include/sys/appleapiopts.h" 3 4



































# 67 "/usr/include/sys/types.h" 2 3 4


# 1 "/usr/include/sys/cdefs.h" 1 3 4

# 22 "/usr/include/sys/cdefs.h" 3 4


# 60 "/usr/include/sys/cdefs.h" 3 4













# 99 "/usr/include/sys/cdefs.h" 3 4









# 116 "/usr/include/sys/cdefs.h" 3 4








# 144 "/usr/include/sys/cdefs.h" 3 4





































# 70 "/usr/include/sys/types.h" 2 3 4


# 1 "/usr/include/machine/types.h" 1 3 4

# 22 "/usr/include/machine/types.h" 3 4








# 1 "/usr/include/ppc/types.h" 1 3 4

# 22 "/usr/include/ppc/types.h" 3 4




# 59 "/usr/include/ppc/types.h" 3 4










typedef	__signed char		int8_t;
typedef	unsigned char		u_int8_t;
typedef	short			int16_t;
typedef	unsigned short		u_int16_t;
typedef	int			int32_t;
typedef	unsigned int		u_int32_t;
typedef	long long		int64_t;
typedef	unsigned long long	u_int64_t;

typedef int32_t			register_t;

typedef long int		intptr_t;
typedef unsigned long int	uintptr_t;






# 31 "/usr/include/machine/types.h" 2 3 4









# 73 "/usr/include/sys/types.h" 2 3 4

# 1 "/usr/include/machine/ansi.h" 1 3 4

# 22 "/usr/include/machine/ansi.h" 3 4











# 1 "/usr/include/ppc/ansi.h" 1 3 4

# 35 "/usr/include/ppc/ansi.h" 3 4





# 50 "/usr/include/ppc/ansi.h" 3 4
# 68 "/usr/include/ppc/ansi.h" 3 4


# 86 "/usr/include/ppc/ansi.h" 3 4







typedef union {
	char		__mbstate8[128];
	long long	_mbstateL;              
} __mbstate_t;



# 34 "/usr/include/machine/ansi.h" 2 3 4














# 75 "/usr/include/sys/types.h" 2 3 4
# 1 "/usr/include/machine/endian.h" 1 3 4

# 22 "/usr/include/machine/endian.h" 3 4








# 1 "/usr/include/ppc/endian.h" 1 3 4

# 23 "/usr/include/ppc/endian.h" 3 4

# 57 "/usr/include/ppc/endian.h" 3 4

























unsigned long	htonl ();
unsigned short	htons ();
unsigned long	ntohl ();
unsigned short	ntohs ();

















# 119 "/usr/include/ppc/endian.h" 3 4

# 31 "/usr/include/machine/endian.h" 2 3 4









# 76 "/usr/include/sys/types.h" 2 3 4


typedef	unsigned char	u_char;
typedef	unsigned short	u_short;
typedef	unsigned int	u_int;
typedef	unsigned long	u_long;
typedef	unsigned short	ushort;		
typedef	unsigned int	uint;		


typedef	u_int64_t	u_quad_t;	
typedef	int64_t		quad_t;
typedef	quad_t *	qaddr_t;

typedef	char *		caddr_t;	
typedef	int32_t		daddr_t;	
typedef	int32_t		dev_t;		
typedef	u_int32_t	fixpt_t;	
typedef	u_int32_t	gid_t;		
typedef	u_int32_t	in_addr_t;	
typedef	u_int16_t	in_port_t;
typedef	u_int32_t	ino_t;		
typedef	long		key_t;		
typedef	u_int16_t	mode_t;		
typedef	u_int16_t	nlink_t;	
typedef	quad_t		off_t;		
typedef	int32_t		pid_t;		
typedef quad_t		rlim_t;		
typedef	int32_t		segsz_t;	
typedef	int32_t		swblk_t;	
typedef	u_int32_t	uid_t;		
typedef u_int32_t	useconds_t;	










typedef	unsigned long	clock_t;




typedef	long unsigned int	size_t;




typedef	int	ssize_t;




typedef	long	time_t;













typedef int32_t	fd_mask;






typedef	struct fd_set {
	fd_mask	fds_bits[(((1024) + (( (sizeof(fd_mask) * 8)) - 1)) / ( (sizeof(fd_mask) * 8)))];
} fd_set;







# 179 "/usr/include/sys/types.h" 3 4




struct _pthread_handler_rec
{
	void           (*routine)(void *);  
	void           *arg;                 
	struct _pthread_handler_rec *next;
};



# 201 "/usr/include/sys/types.h" 3 4


typedef struct _opaque_pthread_t { long sig; struct _pthread_handler_rec  *cleanup_stack; char opaque[596];} *pthread_t;

typedef struct _opaque_pthread_attr_t { long sig; char opaque[36]; } pthread_attr_t;

typedef struct _opaque_pthread_mutexattr_t { long sig; char opaque[8]; } pthread_mutexattr_t;

typedef struct _opaque_pthread_mutex_t { long sig; char opaque[40]; } pthread_mutex_t;

typedef struct _opaque_pthread_condattr_t { long sig; char opaque[4]; } pthread_condattr_t;

typedef struct _opaque_pthread_cond_t { long sig;  char opaque[24]; } pthread_cond_t;

typedef struct _opaque_pthread_rwlockattr_t { long sig; char opaque[12]; } pthread_rwlockattr_t;

typedef struct _opaque_pthread_rwlock_t { long sig;  char opaque[124]; } pthread_rwlock_t;

typedef struct { long sig; char opaque[4]; } pthread_once_t;



typedef unsigned long pthread_key_t;    



# 66 "/usr/include/stdio.h" 2 3 4















typedef off_t fpos_t;














struct __sbuf {
	unsigned char *_base;
	int	_size;
};


struct __sFILEX;


# 130 "/usr/include/stdio.h" 3 4
typedef	struct __sFILE {
	unsigned char *_p;	
	int	_r;		
	int	_w;		
	short	_flags;		
	short	_file;		
	struct	__sbuf _bf;	
	int	_lbfsize;	

	
	void	*_cookie;	
	int	(*_close)(void *);
	int	(*_read) (void *, char *, int);
	fpos_t	(*_seek) (void *, fpos_t, int);
	int	(*_write)(void *, __const char *, int);

	
	struct	__sbuf _ub;	
	struct __sFILEX *_extra; 
	int	_ur;		

	
	unsigned char _ubuf[3];	
	unsigned char _nbuf[1];	

	
	struct	__sbuf _lb;	

	
	int	_blksize;	
	fpos_t	_offset;	
} FILE;


extern FILE __sF[];






	
# 184 "/usr/include/stdio.h" 3 4


# 197 "/usr/include/stdio.h" 3 4









				




























void	 clearerr(FILE *);
int	 fclose(FILE *);
int	 feof(FILE *);
int	 ferror(FILE *);
int	 fflush(FILE *);
int	 fgetc(FILE *);
int	 fgetpos(FILE *, fpos_t *);
char	*fgets(char *, int, FILE *);
FILE	*fopen(__const char *, __const char *);
int	 fprintf(FILE *, __const char *, ...);
int	 fputc(int, FILE *);
int	 fputs(__const char *, FILE *);
size_t	 fread(void *, size_t, size_t, FILE *);
FILE	*freopen(__const char *, __const char *, FILE *);
int	 fscanf(FILE *, __const char *, ...);
int	 fseek(FILE *, long, int);
int	 fsetpos(FILE *, __const fpos_t *);
long	 ftell(FILE *);
size_t	 fwrite(__const void *, size_t, size_t, FILE *);
int	 getc(FILE *);
int	 getchar(void);
char	*gets(char *);

extern __const int sys_nerr;		
extern __const char *__const sys_errlist[];

void	 perror(__const char *);
int	 printf(__const char *, ...);
int	 putc(int, FILE *);
int	 putchar(int);
int	 puts(__const char *);
int	 remove(__const char *);
int	 rename (__const char *, __const char *);
void	 rewind(FILE *);
int	 scanf(__const char *, ...);
void	 setbuf(FILE *, char *);
int	 setvbuf(FILE *, char *, int, size_t);
int	 sprintf(char *, __const char *, ...);
int	 sscanf(__const char *, __const char *, ...);
FILE	*tmpfile(void);
char	*tmpnam(char *);
int	 ungetc(int, FILE *);
int	 vfprintf(FILE *, __const char *, char *);
int	 vprintf(__const char *, char *);
int	 vsprintf(char *, __const char *, char *);
int	 asprintf(char **, __const char *, ...);
int	 vasprintf(char **, __const char *, char *);










char	*ctermid(char *);
char	*ctermid_r(char *);
FILE	*fdopen(int, __const char *);
int	 fileno(FILE *);








char	*fgetln(FILE *, size_t *);
void	 flockfile(FILE *);
__const char 
	*fmtcheck(__const char *, __const char *);
int	 fpurge(FILE *);
int	 fseeko(FILE *, fpos_t, int);
fpos_t	 ftello(FILE *);
int	 ftrylockfile(FILE *);
void	 funlockfile(FILE *);
int	 getc_unlocked(FILE *);
int	 getchar_unlocked(void);
int	 getw(FILE *);
int	 pclose(FILE *);
FILE	*popen(__const char *, __const char *);
int	 putc_unlocked(int, FILE *);
int	 putchar_unlocked(int);
int	 putw(int, FILE *);
void	 setbuffer(FILE *, char *, int);
int	 setlinebuf(FILE *);
char	*tempnam(__const char *, __const char *);
int	 snprintf(char *, size_t, __const char *, ...);
int	 vfscanf(FILE *, __const char *, char *);
int	 vsnprintf(char *, size_t, __const char *, char *);
int	 vscanf(__const char *, char *);
int	 vsscanf(__const char *, __const char *, char *);
FILE	*zopen(__const char *, __const char *, int);






FILE	*funopen(__const void *,
		int (*)(void *, char *, int),
		int (*)(void *, __const char *, int),
		fpos_t (*)(void *, fpos_t, int),
		int (*)(void *));









int	__srget(FILE *);
int	__svfscanf(FILE *, __const char *, char *);
int	__swbuf(int, FILE *);



# 368 "/usr/include/stdio.h" 3 4

# 380 "/usr/include/stdio.h" 3 4























# 7 "pascal.lexer.l" 2

# 1 "pascal.tools.hpp" 1



# 1 "/usr/include/stdlib.h" 1 3 4

# 23 "/usr/include/stdlib.h" 3 4

# 57 "/usr/include/stdlib.h" 3 4







# 1 "/usr/include/alloca.h" 1 3 4

# 23 "/usr/include/alloca.h" 3 4













void	*alloca(size_t);		












# 65 "/usr/include/stdlib.h" 2 3 4










typedef	int	ct_rune_t;




typedef int   rune_t;







typedef	int	wchar_t;








typedef	int	wint_t;


typedef struct {
	int quot;		
	int rem;		
} div_t;

typedef struct {
	long quot;		
	long rem;		
} ldiv_t;










extern int __mb_cur_max;





void	 abort(void) ;
int	 abs(int) ;
int	 atexit(void (*)(void));
double	 atof(__const char *);
int	 atoi(__const char *);
long	 atol(__const char *);
void	*bsearch(__const void *, __const void *, size_t,
	    size_t, int (*)(__const void *, __const void *));
void	*calloc(size_t, size_t);
div_t	 div(int, int) ;
void	 exit(int) ;
void	 free(void *);
char	*getenv(__const char *);
long	 labs(long) ;
ldiv_t	 ldiv(long, long) ;
void	*malloc(size_t);
int	 mblen(__const char *, size_t);
size_t	 mbstowcs(wchar_t * __restrict , __const char * __restrict, size_t);
int	 mbtowc(wchar_t * __restrict, __const char * __restrict, size_t);
void	 qsort(void *, size_t, size_t,
	    int (*)(__const void *, __const void *));
int	 rand(void);
void	*realloc(void *, size_t);
void	 srand(unsigned);
double	 strtod(__const char *, char **);
float	 strtof(__const char *, char **);
long	 strtol(__const char *, char **, int);
long double
	 strtold(__const char *, char **);
unsigned long
	 strtoul(__const char *, char **, int);
int	 system(__const char *);
void	*valloc(size_t);
int	 wctomb(char *, wchar_t);
size_t	 wcstombs(char * __restrict, __const wchar_t * __restrict, size_t);


int	 putenv(__const char *);
int	 setenv(__const char *, __const char *, int);



u_int32_t
	 arc4random(void);
void	 arc4random_addrandom(unsigned char *dat, int datlen);
void	 arc4random_stir(void);
double	 drand48(void);
double	 erand48(unsigned short[3]); 
long	 jrand48(unsigned short[3]);
void	 lcong48(unsigned short[7]);
long	 lrand48(void);
long	 mrand48(void); 
long	 nrand48(unsigned short[3]);
unsigned short
	*seed48(unsigned short[3]);
void	 srand48(long);

	 
char	*cgetcap(char *, __const char *, int);
int	 cgetclose(void);
int	 cgetent(char **, char **, __const char *);
int	 cgetfirst(char **, char **);
int	 cgetmatch(__const char *, __const char *);
int	 cgetnext(char **, char **);
int	 cgetnum(char *, __const char *, long *);
int	 cgetset(__const char *);
int	 cgetstr(char *, __const char *, char **);
int	 cgetustr(char *, __const char *, char **);

int	 daemon(int, int);
char	*devname(int, int);
char	*getbsize(int *, long *);
int	 getloadavg(double [], int);
__const char
	*getprogname(void);

long	 a64l(__const char *);
char	*l64a(long);


int	 heapsort(void *, size_t, size_t,
	    int (*)(__const void *, __const void *));
char	*initstate(unsigned long, char *, long);
int	 mergesort(void *, size_t, size_t,
	    int (*)(__const void *, __const void *));


void	 qsort_r(void *, size_t, size_t, void *,
	    int (*)(void *, __const void *, __const void *));
int	 radixsort(__const unsigned char **, int, __const unsigned char *,
	    unsigned);
void	 setprogname(__const char *);
int	 sradixsort(__const unsigned char **, int, __const unsigned char *,
	    unsigned);
void	 sranddev(void);
void	 srandomdev(void);
int	 rand_r(unsigned *);
long	 random(void);
void	*reallocf(void *, size_t);
char	*realpath(__const char *, char resolved_path[]);
char	*setstate(char *);
void	 srandom(unsigned long);


typedef struct {
	long long quot;
	long long rem;
} lldiv_t;

long long
	 atoll(__const char *);
long long
	 llabs(long long);
lldiv_t	 lldiv(long long, long long);
long long 
	 strtoll(__const char *, char **, int);
unsigned long long
	 strtoull(__const char *, char **, int);
long long
	 strtoq(__const char *, char **, int);
unsigned long long
	 strtouq(__const char *, char **, int);

void	 unsetenv(__const char *);





# 5 "pascal.tools.hpp" 2


                    // plus le caractère nul. Lors du passage à 64 bits, 
                    // il faudra changer cette valeur ;-).
                    // Là, j'ai mis grand pour être sûr qu'il n'y ait pas de problème
                    // avant un moment (à 128 bits => pb !)
                    // En fait, c'est maintenant !!!!
                    // La fonction itoa calcule dynamiquement la taille de la chaîne,
                    // avec une fonction logarithmique (argh).
                    // Malheureusement, cela ne marche pas avec les virgules flottantes.
                    // En effet, il faut connaître la spécification IEEE associée.
                    // On reste avec un 128 // taille du plus grand nombre 32 bits en base 10 grand donc.
// Convertit un nombre en chaîne de caractère.
// Chaîne de caractère allouée avec NEW.
// Donc à détruire avec DELETE[].
extern char *itoa(int i);
// Convertit un float en chaîne de caractère.
// À détruire avec DELETE[].
extern char *ftoa(float f);
// Convertit un booléen en chaîne de caractère.
// À détruire avec DELETE [].
//typedef __const char aqw;
//typedef aqw *aqw_ptr;
//typedef __const aqw_ptr const_aqw_ptr;
//extern __const char * __const (* __const btoa)  (bool __const b) __const;
extern char * btoa(bool __const b);



extern void pmessage(__const char *mess, ...);
extern void pmesserr(__const char *mess, ...);
extern int pmessinit(__const char *nom);
extern void pmessend(void);


extern char *strcopy(__const char *str);


typedef float corps;


// Cette structure sert pour le débogage.
// Elle contient la position de l'expression,
// ou de l'instruction.
// (Comme en DrScheme.)
// Les conventions sont comme partout : 
//  les lignes commencent à 1,
//  et les colonnes à 0.
struct pascal_position {
  unsigned int deb_ligne; // La ligne de début.
  unsigned int fin_ligne; // La ligne de fin.
  unsigned int deb_car; // Le numéro du caractère de début depuis le début de la ligne de début.
  unsigned int fin_car; // Le numéro du caractère de fin depuis le début de la ligne de fin.
  unsigned int deb_car_tot; // Le numéro du caractère de début depuis le début du fichier.
  unsigned int fin_car_tot; // Le numéro du caractère de fin depuis le début du fichier.
  
  pascal_position(unsigned int deb_ligne, unsigned int fin_ligne, unsigned int deb_car, unsigned int fin_car, unsigned int deb_car_tot, unsigned int fin_car_tot) {
    this->deb_ligne = deb_ligne;
    this->fin_ligne = fin_ligne;
    this->deb_car = deb_car;
    this->fin_car = fin_car;
    this->deb_car_tot = deb_car_tot;
    this->fin_car_tot = fin_car_tot;
  }

  char *toString(void);
};
typedef pascal_position ppos;






template <class alpha> class pliste {
  //friend pliste<alpha> *mp(alpha *a, pliste<alpha> *l);
public:
  alpha *a;
  pliste<alpha> *suivant;

public:
  pliste<alpha>(void);
  ~pliste<alpha>(void);
  void raz(void);
  pliste<alpha> *copy(void);
};

template <class alpha> extern pliste<alpha> *mp(alpha *a, pliste<alpha> *l);

template <class alpha> pliste<alpha>::pliste(void) {
  a = 0;
  suivant = 0;
}

template <class alpha> pliste<alpha>::~pliste(void) {
  //raz();
}

template <class alpha> void pliste<alpha>::raz(void) {
  //if (suivant != 0) {
    delete suivant;
  //}
}

template <class alpha> static pliste<alpha> *mp(alpha *a, pliste<alpha> *l) {
  pliste<alpha> *temp;

  temp = new pliste<alpha>;
  temp->a = a;
  temp->suivant = l;
  return temp;
}

template <class alpha> pliste<alpha> *pliste<alpha>::copy(void) {
  pliste<alpha> *temp;

  temp = new pliste<alpha>;

  temp->a = a->copy();
  temp->suivant = suivant->copy();
  
  return temp;
}





template <class beta> class pfifo : public pliste<beta> {
  class pliste<beta> *fin;

public:
  class pfifo<beta> *mf(beta *b, class pfifo<beta> *lb);
};


template <class beta> class pfifo<beta> *mf(beta *b, class pfifo<beta> *lb) {
  class pliste<beta> *temp;

  if (lb == 0) {
    lb = new class pfifo<beta>;
    lb->a = b;
    lb->suivant = 0;
    lb->fin = lb;
    return lb;
  }
  else {
    temp = new class pliste<beta>;
    temp->a = b;
    temp->suivant = 0;
    lb->fin->suivant = temp;
    lb->fin = temp;
    return lb;
  }
}

    
    






# 9 "pascal.lexer.l" 2







  static int nb_lignes = 0, nb_char_ligne = 0, nb_char_tot = 0;

  // La file des TOKEN.
  struct stoken {
    int token;
    YYSTYPE yylval;
    int nb_lignes, nb_char_ligne, nb_char_tot;
  };
    
  static class pfifo<stoken> tokens = 0;



  static char symbole[4095 + 1];
  static unsigned int taille_tampon_symbole = 0;


  static __const char *__const string_of_token(int token) {
    switch (token) {
    case TOKEN_AND: return "AND"; break;
    case TOKEN_OR: return "OR"; break;
    case TOKEN_IDIV: return "DIV"; break;
    case TOKEN_IMOD: return "IMOD"; break;
    case TOKEN_NOT: return "NOT"; break;
    case TOKEN_IF: return "IF"; break;
    case TOKEN_THEN: return "THEN"; break;
    case TOKEN_ELSE: return "ELSE"; break;
    case TOKEN_BEGIN: return "BEGIN"; break;
    case TOKEN_END: return "END"; break;
    case TOKEN_WHILE: return "WHILE"; break;
    case TOKEN_DO: return "DO"; break;
    case TOKEN_REPEAT: return "REPEAT"; break;
    case TOKEN_UNTIL: return "UNTIL"; break;
    case TOKEN_FOR: return "FOR"; break;
    case TOKEN_TO: return "TO"; break;
    case TOKEN_IPLUS: return "IPLUS"; break;
    case TOKEN_IMOINS: return "IMOINS"; break;
    case TOKEN_RPLUS: return "RPLUS"; break;
    case TOKEN_RMOINS: return "RMOINS"; break;
    case TOKEN_ENTIER: return "ENTIER"; break;
    case TOKEN_REEL: return "REEL"; break;
    case TOKEN_VIRG: return "VIRGULE"; break;
    case TOKEN_PTVIRG: return "POINT VIRGULE"; break;
    case TOKEN_CHAINE: return "CHAINE"; break;
    case TOKEN_OPENPAR: return "PARENTHESE OUVRANTE"; break;
    case TOKEN_CLOSEPAR: return "PARENTHESE FERMANTE"; break;
    case TOKEN_BLANC: return "BLANCS"; break;
    case TOKEN_COMMENT: return "COMMENTAIRE"; break;
    case TOKEN_EQUAL: return "EQUAL"; break;
    case TOKEN_INF: return "INF"; break;
    case TOKEN_SUP: return "SUP"; break;
    case TOKEN_INFEQ: return "INFEQ"; break;
    case TOKEN_SUPEQ: return "SUPEQ"; break;
    case TOKEN_PTR: return "PTR"; break;
    case TOKEN_AFFECTATION: return "AFFECTATION"; break;
    case TOKEN_ARRAY: return "ARRAY"; break;
    case TOKEN_OF: return "OF"; break;
    case TOKEN_RECORD: return "RECORD"; break;
    case TOKEN_WRITE: return "WRITE"; break;
    case TOKEN_WRITELN: return "WRITELN"; break;
    case TOKEN_READ: return "READ"; break;
    case TOKEN_READLN: return "READLN"; break;
    default:
      return "INCONNU";
    }
  }








# 113 "pascal.lexer.l"





  // Fonction qui matche un symbole, le convertit en minuscule 
  // (le langage est case insensitive pour les mots-clefs,
  // mais pas pour le reste).
  static int match_symbol(void) {
    symbole[taille_tampon_symbole] = '\0';

    if (strcase("not", symbole) == 0) {return TOKEN_NOT;}
    else if (strcasecmp("and"    , symbole) == 0) {return TOKEN_AND;}
    else if (strcasecmp("or"     , symbole) == 0) {return TOKEN_OR;}
    else if (strcasecmp("div"    , symbole) == 0) {return TOKEN_IDIV;}
    else if (strcasecmp("mod"    , symbole) == 0) {return TOKEN_IMOD;}
    else if (strcasecmp("if"     , symbole) == 0) {return TOKEN_IF;}
    else if (strcasecmp("then"   , symbole) == 0) {return TOKEN_THEN;}
    else if (strcasecmp("else"   , symbole) == 0) {return TOKEN_ELSE;}
    else if (strcasecmp("while"  , symbole) == 0) {return TOKEN_WHILE;}
    else if (strcasecmp("do"     , symbole) == 0) {return TOKEN_DO;}
    else if (strcasecmp("for"    , symbole) == 0) {return TOKEN_FOR;}
    else if (strcasecmp("to"     , symbole) == 0) {return TOKEN_TO;}
    else if (strcasecmp("begin"  , symbole) == 0) {return TOKEN_BEGIN;}
    else if (strcasecmp("end"    , symbole) == 0) {return TOKEN_END;}
    else if (strcasecmp("repeat" , symbole) == 0) {return TOKEN_REPEAT;}
    else if (strcasecmp("until"  , symbole) == 0) {return TOKEN_UNTIL;}
    else if (strcasecmp("array"  , symbole) == 0) {return TOKEN_ARRAY;}
    else if (strcasecmp("record" , symbole) == 0) {return TOKEN_RECORD;}
    else if (strcasecmp("write"  , symbole) == 0) {return TOKEN_WRITE;}
    else if (strcasecmp("writeln", symbole) == 0) {return TOKEN_WRITELN;}
    else if (strcasecmp("read"   , symbole) == 0) {return TOKEN_READ;}
    else if (strcasecmp("readln" , symbole) == 0) {return TOKEN_READLN;}
    else {return TOKEN_IDENT;}
  }



%}

eol \n

blanc [\t\r\ ]
blancs {blanc}+
comment \{[^\}]\}

chiffre  [0-9]
entier  {chiffre}+
reel ({entier}\.{chiffre}*)|({chiffre}*\.{entier})

chaine \'[^\']\'

open_par \(
close_par \)

iplus \+
imoins \-
imult \*

rplus \+\.
rmoins \-\.
rmult \*\.
rdiv \/.

egal \=\=
inf \<
sup \>
infeq \<\=
supeq \>\=

ptr \^



affectation \:\=

  // En l'occurrence, comme j'ai une interface avec une file de tokens,
  // je recommence tout le temps en rempilant à chaque fois.
  // NON. En fait, on fait comme avant.
  // Ce qui permet de matcher la règle <<(-1)>> comme toutes les autres.
%option noyywrap
%option nounput
%%

<<(-1)>>        printf("Fin.\n"); exit(0);

{eol}          { { if (taille_tampon_symbole > 0) { struct stoken* temp; temp = new struct stoken; temp->nb_lignes = nb_lignes; temp->nb_char_lignes = nb_char_lignes; temp->nb_char_tot = nb_char_tot; temp->token = match_symbole(); {if (temp->token == TOKEN_IDENT) { temp->yylval.ident = symbol; } } tokens = mf(temp, tokens); { fprintf(yyout, " symbole %s [ %s ] ", string_of_token(temp->token), ( symbole)); nb_char_tot += ( taille_tampon_symbole); nb°char_ligne += ( taille_tampon_symbole); }; taille_tampon_symbole = 0; } } { fprintf(yyout, " symbole %s [ %s ] ", string_of_token(TOKEN_BLANC), (  "EOL")); nb_char_tot += ( yyleng); nb°char_ligne += ( yyleng); }; }; nb_lignes++; nb_char_ligne = 0; yycontinue();

{blancs}       { { if (taille_tampon_symbole > 0) { struct stoken* temp; temp = new struct stoken; temp->nb_lignes = nb_lignes; temp->nb_char_lignes = nb_char_lignes; temp->nb_char_tot = nb_char_tot; temp->token = match_symbole(); {if (temp->token == TOKEN_IDENT) { temp->yylval.ident = symbol; } } tokens = mf(temp, tokens); { fprintf(yyout, " symbole %s [ %s ] ", string_of_token(temp->token), ( symbole)); nb_char_tot += ( taille_tampon_symbole); nb°char_ligne += ( taille_tampon_symbole); }; taille_tampon_symbole = 0; } } { fprintf(yyout, " symbole %s [ %s ] ", string_of_token(TOKEN_BLANC), (  yytext)); nb_char_tot += ( yyleng); nb°char_ligne += ( yyleng); }; }; yycontinue();

{comment}      { { if (taille_tampon_symbole > 0) { struct stoken* temp; temp = new struct stoken; temp->nb_lignes = nb_lignes; temp->nb_char_lignes = nb_char_lignes; temp->nb_char_tot = nb_char_tot; temp->token = match_symbole(); {if (temp->token == TOKEN_IDENT) { temp->yylval.ident = symbol; } } tokens = mf(temp, tokens); { fprintf(yyout, " symbole %s [ %s ] ", string_of_token(temp->token), ( symbole)); nb_char_tot += ( taille_tampon_symbole); nb°char_ligne += ( taille_tampon_symbole); }; taille_tampon_symbole = 0; } } { fprintf(yyout, " symbole %s [ %s ] ", string_of_token(TOKEN_COMMENT), (  yytext)); nb_char_tot += ( yyleng); nb°char_ligne += ( yyleng); }; }; yycontinue();

{entier}       {						  struct stoken  *temp;										  { { if (taille_tampon_symbole > 0) { struct stoken* temp; temp = new struct stoken; temp->nb_lignes = nb_lignes; temp->nb_char_lignes = nb_char_lignes; temp->nb_char_tot = nb_char_tot; temp->token = match_symbole(); {if (temp->token == TOKEN_IDENT) { temp->yylval.ident = symbol; } } tokens = mf(temp, tokens); { fprintf(yyout, " symbole %s [ %s ] ", string_of_token(temp->token), ( symbole)); nb_char_tot += ( taille_tampon_symbole); nb°char_ligne += ( taille_tampon_symbole); }; taille_tampon_symbole = 0; } } { fprintf(yyout, " symbole %s [ %s ] ", string_of_token(TOKEN_ENTIER), (  yytext)); nb_char_tot += ( yyleng); nb°char_ligne += ( yyleng); }; };                       						  temp = new struct stoken;			  temp->token = TOKEN_ENTIER;				  temp->yylval.entier = atoi(yytext);				  temp->nb_lignes = nb_lignes;			  temp->nb_char_ligne = nb_char_ligne;		  temp->nb_char_tot = nb_char_tot;								  tokens = mf(temp, tokens);									  temp = tokens->a;				  tokens = token->suivant;									  yylval = temp->yylval;			  int ret =  temp->token;			  delete temp;					  return ret;					}
// {
//                   struct stoken  *temp;
		  
//                   { { if (taille_tampon_symbole > 0) { struct stoken* temp; temp = new struct stoken; temp->nb_lignes = nb_lignes; temp->nb_char_lignes = nb_char_lignes; temp->nb_char_tot = nb_char_tot; temp->token = match_symbole(); {if (temp->token == TOKEN_IDENT) { temp->yylval.ident = symbol; } } tokens = mf(temp, tokens); { fprintf(yyout, " symbole %s [ %s ] ", string_of_token(temp->token), ( symbole)); nb_char_tot += ( taille_tampon_symbole); nb°char_ligne += ( taille_tampon_symbole); }; taille_tampon_symbole = 0; } } { fprintf(yyout, " symbole %s [ %s ] ", string_of_token(TOKEN_ENTIER), (  yytext)); nb_char_tot += ( yyleng); nb°char_ligne += ( yyleng); }; }; 

// 		  temp = new struct stoken;
// 		  temp->token = TOKEN_ENTIER;
// 		  temp->yylval.entier = atoi(yytext);
// 		  temp->nb_lignes = nb_lignes;
// 		  temp->nb_char_ligne = nb_char_ligne;
// 		  temp->nb_char_tot = nb_char_tot;
		  
// 		  tokens = mf(temp, tokens);
		  
// 		  temp = tokens->a;
// 		  tokens = token->suivant;

// 		  yylval = temp->yylval;
// 		  int ret =  temp->token;
// 		  delete temp;
// 		  return ret;
//                }

{reel}         printf("Reel.\n");

{chaine}       printf("Chaine.\n");

{open_par}     printf("Open_Par.\n");

{close_par}    printf("Close_Par.\n");

{iplus}        printf("IPlus.\n");

{imoins}       printf("IMoins.\n");

{imult}        printf("IMult.\n");

{rplus}        printf("RPlus.\n");

{rmoins}       printf("RMoins.\n");

{rmult}        printf("RMult.\n");

{rdiv}         printf("RDiv.\n");

{egal}         printf("EGAL.\n");

{inf}          printf("INF.\n");

{sup}          printf("SUP.\n");

{infeq}        printf("INFEQ.\n");

{supeq}        printf("SUPEQ.\n");

{ptr}          printf("PTR\n");

{affectation}  printf("Affectation.\n");

.              printf("Autre.\n");

%%

