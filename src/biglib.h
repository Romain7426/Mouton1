#ifndef BIGLIB_H
#define BIGLIB_H


#define xglue(a,b) a ## b
#define glue(a,b) xglue(a,b)
#if 0
#define glue3(a,b,c) glue(glue(a,b),c)
#else
#define xglue3(a,b,c) a##b##c
#define glue3(a,b,c) xglue3(a,b,c)
#endif


#ifndef not
// defined dans <iso646.h> 
#  define not(a) (!(a))
#endif
#define non not

#define when(condition) if(condition)
#define unless(condition) if(not(condition))

#define sqr(a) ((a) * (a))
#define carre sqr

#define div /
#define mod %

#define skip(...) 

#ifndef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#endif

#ifndef max
#define max(a,b) ((a) < (b) ? (b) : (a))
#endif

#define COMPILE_BREAK {int tab[-1];}
#define COMPILE_BREAK_HUH(b) {int tab[(b)?-1:1];}

#define GDB_BREAK ((*((int *) NULL)) = 0)

#define BIGLIB_STRING(s) BIGLIB_STRINGX(s)
#define BIGLIB_STRINGX(s) #s


#ifdef __GNUC__
#define NORETURN_ATTRIBUT __attribute__ ((noreturn))
#else
#define NORETURN_ATTRIBUT
#endif

extern void biglib_assert_aux(const char * expression, const char * fichier, unsigned int ligne) NORETURN_ATTRIBUT;
#define biglib_assert(expression) { if (expression) {} else  { biglib_assert_aux(#expression, __FILE__, __LINE__); } }
#undef assert
#define assert biglib_assert




#ifdef ASPRINTF_IS_NOT_PROVIDED
extern int asprintf(char * * strp, const char * format, ...);
extern int vasprintf(char * * strp, const char * format, va_list args);   
#endif 

#ifdef BZERO_IS_NOT_PROVIDED
extern void bzero(void *s, size_t n);
#endif 




enum { CR = ('\r'), LF = ('\n') };


extern char * str_alloc(int char_nb);
extern char * stralloc(int char_nb);
extern void strfree(char * str);
extern void str_free(char * str);

extern char * strcopy(const char * str);

extern bool strnull_huh(const char * str);
extern bool strempty_huh(const char * str);

#define str_copy strcopy
#define str_string strcopy
#define str_equal strequal

extern char * substring(const char * str, int starting_index, int ending_index);

#define strconcat1 strcopy
extern char * strconcat2(const char * str1, const char * str2);
#define strconcat strconcat2
extern char * strconcat3(const char * str1, const char * str2, const char * str3);
extern char * strconcat4(const char * str1, const char * str2, const char * str3, const char * str4);
extern char * strconcat5(const char * str1, const char * str2, const char * str3, const char * str4, const char * str5);
extern char * strconcat6(const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6);
extern char * strconcat7(const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7);
extern char * strconcat8(const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8);
extern char * strconcat9(const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8, const char * str9);
extern char * strconcat10(const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8, const char * str9, const char * str10);
extern char * strconcat11(const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8, const char * str9, const char * str10, const char * str11);
extern char * strconcat12(const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8, const char * str9, const char * str10, const char * str11, const char * str12);
extern char * strconcat13(const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8, const char * str9, const char * str10, const char * str11, const char * str12, const char * str13);
extern char * strconcat14(const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8, const char * str9, const char * str10, const char * str11, const char * str12, const char * str13, const char * str14);
extern char * strconcat15(const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8, const char * str9, const char * str10, const char * str11, const char * str12, const char * str13, const char * str14, const char * str15);

extern void stradd1(char * * str0);
extern void stradd2(char * * str0, const char * str1);
extern void stradd3(char * * str0, const char * str1, const char * str2);
extern void stradd4(char * * str0, const char * str1, const char * str2, const char * str3);
extern void stradd5(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4);
extern void stradd6(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4, const char * str5);
extern void stradd7(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6);
extern void stradd8(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7);
extern void stradd9(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8);
extern void stradd10(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8, const char * str9);
extern void stradd11(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8, const char * str9, const char * str10);
extern void stradd12(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8, const char * str9, const char * str10, const char * str11);
extern void stradd13(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8, const char * str9, const char * str10, const char * str11, const char * str12);
extern void stradd14(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8, const char * str9, const char * str10, const char * str11, const char * str12, const char * str13);
extern void stradd15(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8, const char * str9, const char * str10, const char * str11, const char * str12, const char * str13, const char * str14);

extern char * strmap(int (*f)(int), const char * str);
extern char * strlower(const char * str);
extern char * strupper(const char * str);
extern bool strequal(const char * str1, const char * str2);
extern bool striequal(const char * str1, const char * str2);
#define string_equal strequal










extern char * bool_string(bool b);
extern const char * bool_string_const(bool b);
extern const char * bool_string_tab[2];

extern char * bool_string_c(bool b);
extern const char * bool_string_c_const(bool b);
extern const char * bool_string_c_tab[2];

#define str_of_bool bool_string
#define str_of_boolean str_of_bool

extern char * str_of_integer(integer n);
extern char * str_of_real(real x);
extern char * str_of_pointeur(const void * ptr);

extern char * float_string(const float x);
extern char * double_string(const double x);
extern char * char_string(const char c);
extern char * char_string_filtre(const char c);
//extern char * str_of_char(char c);
//#define str_of_char

#define str_of_entier str_of_integer
#define str_of_reel   str_of_real
#define str_of_int    str_of_integer

#define real_string str_of_real
#define int_string str_of_integer


extern char * uint_string(uint_t n);
extern char * uint8_string(uint8_t byte);
#define str_of_uint8 uint8_string
#define str_of_uint uint_string
#define unsigned_string uint_string

// atoi(3), atof(3), atol(3), strtod(3), strtol(3), strtoul(3)
#define entier_of_str atoi
#define reel_of_str atof

extern char * pointeur_string(const void * ptr);


// permet de détecter si un nom de fichier porte une extension
extern bool a_une_extension(const char * fichier);

// génère un nom de fichier
//  retourne `str' ^ "_00" ^ `i'
//  chaîne allouée dynamiquement,
//  donc il faut la libérer après utilisation
extern char * generer_nom(const char * str, unsigned int i);

// calcule la puissance de 2 superieure ou egale a x.
extern unsigned int puissance2(unsigned int x);
extern unsigned int puissance2_tab[32];

#define int_copy(a) (a)
#define bool_copy(a) (a)
#define int_free(a) (void)
#define bool_free(a) (void)

#define int_equal(a,b) (a == b)
#define bool_equal(a,b) (a == b)
#define unsigned_equal(a,b) (a == b)
#define pointeur_equal(a,b) (a == b)




extern int texte_lignes_nombre(const char * str);
extern int texte_mots_nombre(const char * str);

extern bool string_contains_char_huh(const char * str, const char c);
extern char * string_char_replace(const char * str, const char c1, const char c2);
extern void string_char_replace_nocopy(char * str, const char c1, const char c2);



// BUGS: fonction texte, pas données!!! 
extern bool biglib_fichier_existe_huh(const char * fichier_nom); 
extern uint64_t biglib_fichier_taille(const char * fichier_nom); 
extern char * biglib_fichier_lire(const char * fichier_nom); 
extern void biglib_fichier_ecrire(const char * fichier_nom, const char * fichier_contenu); 
extern void biglib_fichier_rendre_executable(const char * fichier_nom); 
extern void biglib_repertoire_creer(const char * repertoire_nom); 
extern void biglib_repertoire_changer(const char * repertoire_nom); 

extern bool char_blanc_huh(char c);












#endif /* BIGLIB_H */

