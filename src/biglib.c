#include "global.h"
#include "biglib.h"



real real_of_integer(integer n) {
  return ((real) n);
}






void stradd1(char * * str0) {
#pragma unused (str0)
}

void stradd2(char * * str0, const char * str1) {
  char * temp;
  temp = strconcat2(*str0, str1);
  strfree(*str0);
  *str0 = temp;
}

void stradd3(char * * str0, const char * str1, const char * str2) {
  char * temp;
  temp = strconcat3(*str0, str1, str2);
  strfree(*str0);
  *str0 = temp;
}

void stradd4(char * * str0, const char * str1, const char * str2, const char * str3) {
  char * temp;
  temp = strconcat4(*str0, str1, str2, str3);
  strfree(*str0);
  *str0 = temp;
}

void stradd5(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4) {
  char * temp;
  temp = strconcat5(*str0, str1, str2, str3, str4);
  strfree(*str0);
  *str0 = temp;
}

void stradd6(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4, const char * str5) {
  char * temp;
  temp = strconcat6(*str0, str1, str2, str3, str4, str5);
  strfree(*str0);
  *str0 = temp;
}

void stradd7(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6) {
  char * temp;
  temp = strconcat7(*str0, str1, str2, str3, str4, str5, str6);
  strfree(*str0);
  *str0 = temp;
}

void stradd8(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7) {
  char * temp;
  temp = strconcat8(*str0, str1, str2, str3, str4, str5, str6, str7);
  strfree(*str0);
  *str0 = temp;
}

void stradd9(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8) {
  char * temp;
  temp = strconcat9(*str0, str1, str2, str3, str4, str5, str6, str7, str8);
  strfree(*str0);
  *str0 = temp;
}

void stradd10(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8, const char * str9) {
  char * temp;
  temp = strconcat10(*str0, str1, str2, str3, str4, str5, str6, str7, str8, str9);
  strfree(*str0);
  *str0 = temp;
}

void stradd11(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8, const char * str9, const char * str10) {
  char * temp;
  temp = strconcat11(*str0, str1, str2, str3, str4, str5, str6, str7, str8, str9, str10);
  strfree(*str0);
  *str0 = temp;
}

void stradd12(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8, const char * str9, const char * str10, const char * str11) {
  char * temp;
  temp = strconcat12(*str0, str1, str2, str3, str4, str5, str6, str7, str8, str9, str10, str11);
  strfree(*str0);
  *str0 = temp;
}

void stradd13(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8, const char * str9, const char * str10, const char * str11, const char * str12) {
  char * temp;
  temp = strconcat13(*str0, str1, str2, str3, str4, str5, str6, str7, str8, str9, str10, str11, str12);
  strfree(*str0);
  *str0 = temp;
}

void stradd14(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8, const char * str9, const char * str10, const char * str11, const char * str12, const char * str13) {
  char * temp;
  temp = strconcat14(*str0, str1, str2, str3, str4, str5, str6, str7, str8, str9, str10, str11, str12, str13);
  strfree(*str0);
  *str0 = temp;
}

void stradd15(char * * str0, const char * str1, const char * str2, const char * str3, const char * str4, const char * str5, const char * str6, const char * str7, const char * str8, const char * str9, const char * str10, const char * str11, const char * str12, const char * str13, const char * str14) {
  char * temp;
  temp = strconcat15(*str0, str1, str2, str3, str4, str5, str6, str7, str8, str9, str10, str11, str12, str13, str14);
  strfree(*str0);
  *str0 = temp;
}






char * strallouer(unsigned int taille) {
  char * alpha; 

  alpha = (char *) malloc((sizeof (char)) * (taille + 1));
  
  if (taille > 0) 
    alpha[0] = '\0'; 

  return alpha; 
}


void strfree(char * str) {
  free((char *) str);
}


void str_free(char * str) {
  strfree(str);
}



bool strnull_huh(const char * str) {
  return (str == NULL);
}

bool strempty_huh(const char * str) {
  if (str == NULL) return false;
  
  if (str[0] == '\0') return true;

  return false;
}




char * strlower(const char * str) {
  return strmap(tolower, str);
}

char * strupper(const char * str) {
  return strmap(toupper, str);
}

bool strequal(const char * str1, const char * str2) {
  return (0 == strcmp(str1, str2));
}




char * strcopy(const char * str) {
  // le code suivant plante!!!!!
  // dans strcpy()! il suffit de lui filer le contenu de «mettre_a_jour.sh» 
  //   return strcpy(malloc(strlen(str) + 1), str);
  // 
  // le code suivant fonctionne cette fois-ci
  //
  // C'est à cause de la fonction de gcc qui fait de la merde.
  // Pour les désactiver:  -fno-builtin-strcpy -fno-builtin-strlen
  if (NULL == str) return NULL;
  const size_t len = strlen(str);
  const size_t len_octet = (len+1) * (sizeof(char));
  char * retour;

  retour = (char *) malloc(len_octet);
  
  memcpy(retour, str, len_octet);

  return retour;
}





char * bool_string(bool b) {
  //return strcopy(bool_string_const(b));
  return strcopy(bool_string_tab[b]);
}

const char * bool_string_const(bool b) {
  //  return (b ? "VRAI" : "FAUX");
  return bool_string_tab[b];
}



char * bool_string_c(bool b) {
  return strcopy(bool_string_c_tab[b]);
}

const char * bool_string_c_const(bool b) {
  return bool_string_c_tab[b];
}




unsigned int puissance2(unsigned int x) {
  unsigned int p = 1;

  while (p < x) {
    //p *= 2;
    //p = p << 1;
    p <<= 1;;
  }
  
  return p; 
}






void biglib_assert_aux(const char * expression, const char * fichier, unsigned int ligne) {
  static unsigned int count = 0;
  
  // on teste qu'il n'y a pas de boucle
  if (count != 0) {
    fprintf(stderr, "\n");
    fprintf(stderr, "biglib_assert_aux: TRES GRAVE: on boucle dans la fonction d'assertion!!!!\n");
    abort();
  }
  count ++;
  
  fflush(NULL);
  
  fprintf(stderr, "%s:%u: assertion failed: `%s'\n", fichier, ligne, expression);
  
  // permet de backtracer avec gdb lorsqu'on enlève les commentaires
  //GDB_BREAK;
  abort();
}




#define TEST_SIZEOF(type_t,taille) {static int test_array[((sizeof (type_t)) == (taille)) ? 1 : -1];}

#ifdef SIZE_T_IS_UL
# define size_t__type(n) n ## UL
#else
# define size_t__type(n) n ## U
#endif

void biglib_structures_base_test(void) {
  TEST_SIZEOF(uint8_t,  size_t__type(1));
  TEST_SIZEOF(uint16_t, size_t__type(2));
  TEST_SIZEOF(uint32_t, size_t__type(4));
  TEST_SIZEOF(uint64_t, size_t__type(8));
  //TEST_SIZEOF(uint128_t, size_t__type(16));
  
  TEST_SIZEOF(int8_t,  size_t__type(1));
  TEST_SIZEOF(int16_t, size_t__type(2));
  TEST_SIZEOF(int32_t, size_t__type(4));
  TEST_SIZEOF(int64_t, size_t__type(8));
  //TEST_SIZEOF(int128_t, size_t__type(16));
}

#undef size_t__type 


const real biglib_constantes_pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068;
const real biglib_constantes_e = 2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178525166427;



#ifdef ASPRINTF_IS_NOT_PROVIDED 

// fait en gros comme printf mais ecrit dans la chaine `strp' (elle l'alloue)
// retourne le nombre de caracteres ecrits (ex : "bon" --> 3)
// en cas d'erreur, ça retourne -1 et *strp = NULL
int asprintf(char * * strp, const char * format, ...) {

#if 0    
  {
    int retour;
    va_list args;
    
    va_start(args, format);
    retour = vasprintf(strp, format, args);
    va_end(args);
    
    return retour;
  }
#else
  {
    int retour;
    va_list args;
    
    // realise un premier appel pour avoir la taille de la chaine a allouer
    va_start(args, format);
    retour = vsnprintf(NULL, 0, format, args);
    va_end(args);
    
    if (retour == -1) {
      *strp = NULL; 
      return -1;
    }
    
    // retour designe ici la taille du buffer (le '\0' final compris)
    retour ++;
    
    // on alloue la chaîne
    *strp = (char *) malloc(retour);
    
    va_start(args, format);
    retour = vsnprintf(*strp, retour, format, args);
    va_end(args);
    
    return retour - 1;
  }
#endif

}


int vasprintf(char * * strp, const char * format, va_list args) {
  va_list args_copy;
  int retour;

  // la gestion du nombre variable d'argument est toute pourrie en C
  // très mal spécifiée, alors que printf l'utilise!!!
  // il faut voir que sur certain système, c'est juste une liste,
  // sur d'autres il y a allocation dynamique de tableau, etc.!
  va_copy(args_copy, args);
  
  // réalise un premier appel pour avoir la taille de la chaîne à allouer
  retour = vsnprintf(NULL, 0, format, args);
  
  if (retour == -1) {
    va_end(args_copy);
    *strp = NULL; 
    return -1;
  }
  
  // retour désigne ici la taille du buffer (le '\0' final compris)
  retour ++;
  
  // on alloue la chaîne
  *strp = (char *) malloc(retour);
  
  retour = vsnprintf(*strp, retour, format, args_copy);
  
  va_end(args_copy);
  
  assert(*strp[retour] = '\0');
  
  return (retour - 1);
}


#endif






#ifdef BZERO_IS_NOT_PROVIDED
// The bzero() function writes n zeroed bytes to the string s.  If n is zero, bzero() does nothing.
void bzero(void * s, size_t n) {
  memset(s, 0, n);
}
#endif 








char * substring(const char * str, unsigned int debut, unsigned int fin) {
  unsigned int len;
  unsigned int taille;
  char * retour;
  
  assert(debut <= fin);

  len = fin - debut;

  taille = (len + 1) * (sizeof (char));

  retour = (char *) malloc(taille);

  memcpy(retour, str + debut, taille);

  retour[len] = '\0';

  return retour;
}



char * strmap(int (*f)(int), const char * const str) {
  char * retour;
  size_t i;
  size_t len;

  len = strlen(str);

  retour = (char *) malloc(len + 1);

  for (i = 0; i < len; i++) {
    retour[i] = ((char) (f(((int) (str[i])))));
  }

  retour[len] = '\0';

  return retour;
}

bool striequal(const char * const str1, const char * const str2) {
  bool retour;
  char * lower1;
  char * lower2;
  
  lower1 = strlower(str1);
  lower2 = strlower(str2);

  retour = strequal(lower1, lower2);

  strfree(lower2);
  strfree(lower1);

  return retour;
}




char * strconcat2(const char * const str1, const char * const str2) {
  const unsigned int len = strlen(str1) + strlen(str2);
  return strcat(strcpy(malloc(len + 1), str1), str2);
}

char * strconcat3(const char * const str1, const char * const str2, const char * const str3) {
  const unsigned int len = strlen(str1) + strlen(str2) + strlen(str3);
  return strcat(strcat(strcpy(malloc(len + 1), str1), str2), str3);
}

char * strconcat4(const char * const str1, const char * const str2, const char * const str3, const char * const str4) {
  const unsigned int len = strlen(str1) + strlen(str2) + strlen(str3) + strlen(str4);
  return strcat(strcat(strcat(strcpy(malloc(len + 1), str1), str2), str3), str4);
}

char * strconcat5(const char * const str1, const char * const str2, const char * const str3, const char * const str4, const char * const str5) {
  const unsigned int len = strlen(str1) + strlen(str2) + strlen(str3) + strlen(str4) + strlen(str5);
  return strcat(strcat(strcat(strcat(strcpy(malloc(len + 1), str1), str2), str3), str4), str5);
}

char * strconcat6(const char * const str1, const char * const str2, const char * const str3, const char * const str4, const char * const str5, const char * const str6) {
  const unsigned int len = strlen(str1) + strlen(str2) + strlen(str3) + strlen(str4) + strlen(str5) + strlen(str6);
  return strcat(strcat(strcat(strcat(strcat(strcpy(malloc(len + 1), str1), str2), str3), str4), str5), str6);
}

char * strconcat7(const char * const str1, const char * const str2, const char * const str3, const char * const str4, const char * const str5, const char * const str6, const char * const str7) {
  const unsigned int len = strlen(str1) + strlen(str2) + strlen(str3) + strlen(str4) + strlen(str5) + strlen(str6) + strlen(str7);
  return strcat(strcat(strcat(strcat(strcat(strcat(strcpy(malloc(len + 1), str1), str2), str3), str4), str5), str6), str7);
}

char * strconcat8(const char * const str1, const char * const str2, const char * const str3, const char * const str4, const char * const str5, const char * const str6, const char * const str7, const char * const str8) {
  const unsigned int len = strlen(str1) + strlen(str2) + strlen(str3) + strlen(str4) + strlen(str5) + strlen(str6) + strlen(str7) + strlen(str8);
  return strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcpy(malloc(len + 1), str1), str2), str3), str4), str5), str6), str7), str8);
}




char * strconcat9(const char * const str1, const char * const str2, const char * const str3, const char * const str4, const char * const str5, const char * const str6, const char * const str7, const char * const str8, const char * const str9) {
  const unsigned int len = strlen(str1) + strlen(str2) + strlen(str3) + strlen(str4) + strlen(str5) + strlen(str6) + strlen(str7) + strlen(str8) + strlen(str9);
  char * temp1;
  temp1 = strcpy(malloc(len + 1), "");
  temp1 = strcat(strcat(strcat(strcat(strcat(strcat(temp1, str1), str2), str3), str4), str5), str6);
  temp1 = strcat(strcat(strcat(temp1, str7), str8), str9);
  return temp1;
}

char * strconcat10(const char * const str1, const char * const str2, const char * const str3, const char * const str4, const char * const str5, const char * const str6, const char * const str7, const char * const str8, const char * const str9, const char * const str10) {
  const unsigned int len = strlen(str1) + strlen(str2) + strlen(str3) + strlen(str4) + strlen(str5) + strlen(str6) + strlen(str7) + strlen(str8) + strlen(str9) + strlen(str10);
  char * temp1;
  temp1 = strcpy(malloc(len + 1), "");
  temp1 = strcat(strcat(strcat(strcat(strcat(strcat(temp1, str1), str2), str3), str4), str5), str6);
  temp1 = strcat(strcat(strcat(strcat(temp1, str7), str8), str9), str10);
  return temp1;
}

char * strconcat11(const char * const str1, const char * const str2, const char * const str3, const char * const str4, const char * const str5, const char * const str6, const char * const str7, const char * const str8, const char * const str9, const char * const str10, const char * const str11) {
  const unsigned int len = strlen(str1) + strlen(str2) + strlen(str3) + strlen(str4) + strlen(str5) + strlen(str6) + strlen(str7) + strlen(str8) + strlen(str9) + strlen(str10) + strlen(str11);
  char * temp1;
  temp1 = strcpy(malloc(len + 1), "");
  temp1 = strcat(strcat(strcat(strcat(strcat(strcat(temp1, str1), str2), str3), str4), str5), str6);
  temp1 = strcat(strcat(strcat(strcat(strcat(temp1, str7), str8), str9), str10), str11);
  return temp1;
}

char * strconcat12(const char * const str1, const char * const str2, const char * const str3, const char * const str4, const char * const str5, const char * const str6, const char * const str7, const char * const str8, const char * const str9, const char * const str10, const char * const str11, const char * const str12) {
  const unsigned int len = strlen(str1) + strlen(str2) + strlen(str3) + strlen(str4) + strlen(str5) + strlen(str6) + strlen(str7) + strlen(str8) + strlen(str9) + strlen(str10) + strlen(str11) + strlen(str12);
  char * temp1;
  temp1 = strcpy(malloc(len + 1), "");
  temp1 = strcat(strcat(strcat(strcat(strcat(strcat(temp1, str1), str2), str3), str4), str5), str6);
  temp1 = strcat(strcat(strcat(strcat(strcat(strcat(temp1, str7), str8), str9), str10), str11), str12);
  return temp1;
}

char * strconcat13(const char * const str1, const char * const str2, const char * const str3, const char * const str4, const char * const str5, const char * const str6, const char * const str7, const char * const str8, const char * const str9, const char * const str10, const char * const str11, const char * const str12, const char * const str13) {
  const unsigned int len = strlen(str1) + strlen(str2) + strlen(str3) + strlen(str4) + strlen(str5) + strlen(str6) + strlen(str7) + strlen(str8) + strlen(str9) + strlen(str10) + strlen(str11) + strlen(str12) + strlen(str13);
  char * temp1;
  temp1 = strcpy(malloc(len + 1), "");
  temp1 = strcat(strcat(strcat(strcat(strcat(strcat(temp1, str1), str2), str3), str4), str5), str6);
  temp1 = strcat(strcat(strcat(strcat(strcat(strcat(temp1, str7), str8), str9), str10), str11), str12);
  temp1 = strcat(temp1, str13);
  return temp1;
}

char * strconcat14(const char * const str1, const char * const str2, const char * const str3, const char * const str4, const char * const str5, const char * const str6, const char * const str7, const char * const str8, const char * const str9, const char * const str10, const char * const str11, const char * const str12, const char * const str13, const char * const str14) {
  const unsigned int len = strlen(str1) + strlen(str2) + strlen(str3) + strlen(str4) + strlen(str5) + strlen(str6) + strlen(str7) + strlen(str8) + strlen(str9) + strlen(str10) + strlen(str11) + strlen(str12) + strlen(str13) + strlen(str14);
  char * temp1;
  temp1 = strcpy(malloc(len + 1), "");
  temp1 = strcat(strcat(strcat(strcat(strcat(strcat(temp1, str1), str2), str3), str4), str5), str6);
  temp1 = strcat(strcat(strcat(strcat(strcat(strcat(temp1, str7), str8), str9), str10), str11), str12);
  temp1 = strcat(strcat(temp1, str13), str14);
  return temp1;
}

char * strconcat15(const char * const str1, const char * const str2, const char * const str3, const char * const str4, const char * const str5, const char * const str6, const char * const str7, const char * const str8, const char * const str9, const char * const str10, const char * const str11, const char * const str12, const char * const str13, const char * const str14, const char * const str15) {
  const unsigned int len = strlen(str1) + strlen(str2) + strlen(str3) + strlen(str4) + strlen(str5) + strlen(str6) + strlen(str7) + strlen(str8) + strlen(str9) + strlen(str10) + strlen(str11) + strlen(str12) + strlen(str13) + strlen(str14) + strlen(str15);
  //unsigned int len = 20;
  char * temp1;
  temp1 = strcpy(malloc(len + 1), "");
  temp1 = strcat(strcat(strcat(strcat(strcat(strcat(temp1, str1), str2), str3), str4), str5), str6);
  temp1 = strcat(strcat(strcat(strcat(strcat(strcat(temp1, str7), str8), str9), str10), str11), str12);
  temp1 = strcat(strcat(strcat(temp1, str13), str14), str15);
  //return strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcpy(malloc(len + 1), str1), str2), str3), str4), str5), str6), str7), str8), str9), str10), str11), str12), str13), str14), str15);
  return temp1;
}











// TODO Ça devrait être dans un fichier bool_type.h / bool_type.c (comme les types token etc.)
// type bool défini dans "biglib_structures_base.h" 
//#if (false == 0) && (true == 1)
#if ((0 != 0) == 0) && ((0 == 0) == 1)
const char * bool_string_tab[2] = { "FAUX", "VRAI"};
const char * bool_string_c_tab[2] = { "false", "true"};
//#elif (false == 1) && (true == 0)
#elif ((0 != 0) == 1) && ((0 == 0) == 0)
const char * bool_string_tab[2] = {"VRAI", "FAUX"};
const char * bool_string_c_tab[2] = {"true", "false"};
#else
#error "Cannot get the value of 'true' and 'false'"
#endif



//char * str_of_char(char c) {
char * char_string(const char c) {
  char * retour;

  retour = malloc(2 * sizeof(char));

  retour[0] = c;
  retour[1] = '\0';

  return retour;
}

char * char_string_filtre(const char c) {
  char * retour;

  retour = malloc(3 * sizeof(char));
  retour[2] = '\0';
  retour[0] = '\\';

  switch (c) {
  default:
    retour[0] = c;
    retour[1] = '\0';
    break;

  case '\0': retour[1] = '0'; break;
  case '\a': retour[1] = 'a'; break;
  case '\b': retour[1] = 'b'; break;
  case '\t': retour[1] = 't'; break;
  case '\n': retour[1] = 'n'; break;
  case '\v': retour[1] = 'v'; break;
  case '\f': retour[1] = 'f'; break;
  case '\r': retour[1] = 'r'; break;
  case '\e': retour[1] = 'e'; break;
  case '\\': retour[1] = '\\'; break;
  case '"': retour[1] = '"'; break;
  }
  
  return retour;
}
/*
\\	Literal backslash
\"	Double quote
\'	Single quote
\n	Newline (line feed)
\r	Carriage return
\b	Backspace
\t	Horizontal tab
\f	Form feed // == saut de page OR page break
\a	Alert (bell)
\v	Vertical tab
\?	Question mark (used to escape trigraphs)
\nnn	Character with octal value nnn
\xhh	Character with hexadecimal value hh
*/

char * str_of_integer(integer n) {
  char * retour;
  asprintf(&retour, "%d", n);
  return retour;
}

char * str_of_pointeur(const void * ptr) {
  char * retour;
  asprintf(&retour, "%p", ptr);
  return retour;
}

char * str_of_real(real x) {
  char * retour;
  asprintf(&retour, "%f", x);
  return retour;
}

char * uint8_string(uint8_t byte) {
  char * retour;
  asprintf(&retour, "%02X", (unsigned int) byte);
  return retour;
}

char * uint_string(uint_t byte) {
  char * retour;
  asprintf(&retour, "%u", byte);
  return retour;
}

char * float_string(const float x) {
  char * retour;
  asprintf(&retour, "%f", x);
  return retour;
}

char * double_string(const double x) {
  char * retour;
  asprintf(&retour, "%f", x);
  return retour;
}

char * pointeur_string(const void * ptr) {
  char * retour;
  //asprintf(&retour, "%n", ptr);
  asprintf(&retour, "%p", ptr);
  return retour;
}





unsigned int puissance2_tab[32] = {
  1, 2, 4, 8, 16, 32, 64, 128, 
  256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 
  65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 
  16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648
};

bool a_une_extension(const char * fichier) {
  size_t taille;

  taille = strlen(fichier);

  if (taille < 5) {
    return false;
  }

  return (fichier[taille - 4] == '.');
}

char * generer_nom(const char * str, unsigned int i) {
  char * buffer;
  
  asprintf(&buffer, "%s_%03u.bmp", str, i);
  
  return buffer;
}








extern unsigned int texte_newline_rechercher(const char * str);
extern unsigned int texte_blanc_rechercher(const char * str);






//void texte_en_ligne(const char * str, unsigned int * lignes_nombre, char * * * ligne_tableau) {
str_tableau_t * texte_en_ligne(const char * str) {
  unsigned int nb_lignes;
  unsigned int i;
  unsigned int l;
  char * temp;
  //char * * tableau;
  str_tableau_t * tableau;

  nb_lignes = texte_lignes_nombre(str);

  //fprintf(stderr, " $ %u $ -- %s\n", nb_lignes, str); 

  //tableau = (char * *) malloc(nb_lignes * (sizeof (*tableau)));
  tableau = str_tableau_make(nb_lignes);
  tableau -> nb = nb_lignes;

  for (i = 0; i < nb_lignes; i++) {
    l = texte_newline_rechercher(str);

    temp = (char *) malloc((l + 1) * sizeof(char));
    memcpy(temp, str, l * sizeof(char));
    temp[l] = '\0';

    tableau -> tab[i] = temp;

    // on avance: on skippe la ligne et le '\n'
    str += l + 1;
  }

  //*lignes_nombre = nb_lignes;
  //*ligne_tableau = tableau;

  tableau -> nb = nb_lignes;

  return tableau;
}


unsigned int texte_lignes_nombre(const char * str) {
  unsigned int len;
  unsigned int i;
  unsigned int nb;

  len = strlen(str);

  nb = 0;

  for (i = 0; i < len; i ++) {
    if (str[i] == '\n') nb ++;
  }

  return nb;
}


bool char_blanc_huh(char c) {
  return (c == ' ' || c == '\n' || c == '\0' || c == '\r' || c == '\t');
}


unsigned int texte_mots_nombre(const char * str) {
  unsigned int len;
  unsigned int i, j;
  unsigned int nb;

  len = strlen(str);

  nb = 0;


  //unsigned int texte_blanc_rechercher(const char * str);

  for (i = 0; i < len; i ++) {
    j = texte_blanc_rechercher(str + i);
    if (0 == j) 
      continue;
    
    nb ++;
    i += j;
  }

  return nb;
}


unsigned int texte_newline_rechercher(const char * str) {
  unsigned int i;
  char c;

  for (i = 0; ; i++) {
    c = str[i];

    if (c == '\n' || c == '\0') return i;
  }

  assert(false);
  return (uint_t) -1;
}


unsigned int texte_blanc_rechercher(const char * str) {
  unsigned int i;
  char c;

  for (i = 0; ; i++) {
    c = str[i];

    if (char_blanc_huh(c)) return i;
  }

  assert(false);
  return (uint_t) -1;
}





str_tableau_t *  texte_en_mot(const char * str) {
  unsigned int nb_mots;
  unsigned int i;
  unsigned int pos_c, len;
  //  unsigned int pos_n;
  char * temp;
  str_tableau_t * tableau;

  nb_mots = texte_mots_nombre(str);

  //fprintf(stderr, "nb mots = %u\n", nb_mots);

  tableau = str_tableau_make(nb_mots);
  tableau -> nb = nb_mots;

  pos_c = 0;
  for (i = 0; i < nb_mots; i++) {
    len = texte_blanc_rechercher(str + pos_c);
    if (0 == len) {
      pos_c ++;
      i--;
      continue;
    }

    temp = (char *) malloc((len + 1) * sizeof(char));
    memcpy(temp, str+pos_c, len * sizeof(char));
    temp[len] = '\0';

    tableau -> tab[i] = temp;

    pos_c += len + 1;
  }

  tableau -> nb = nb_mots;

  return tableau;
}

char * str_liste_concat(const str_liste_t * l) {
  char * cdr;
  char * res;

  if (str_liste_vide_huh(l)) {
    return strcopy("");
  }

  cdr = str_liste_concat(l -> cdr);

  res = strconcat3(l -> car, "\n", cdr);

  strfree(cdr);

  return res;
}

bool string_contains_char_huh(const char * str, const char c) {
  unsigned int pos = 0;
  while (str[pos] != '\0') {
    if (str[pos] == c) return true;
    pos++;
  }
  return false;
}

char * string_char_replace(const char * str, const char c1, const char c2) {
  char * retour;
  retour = strcopy(str);
  string_char_replace_nocopy(retour, c1, c2);
  return retour;
}

void string_char_replace_nocopy(char * str, const char c1, const char c2) {
  unsigned int pos = 0;
  while (str[pos] != '\0') {
    if (str[pos] == c1) str[pos] = c2;
    pos++;
  }
}
















bool biglib_fichier_existe_huh(const char * fichier_nom) {
  int ret; 
  struct stat sb;

  ret = stat(fichier_nom, &sb); 
  return (ret == 0);
}


uint64_t biglib_fichier_taille(const char * fichier_nom) { 
  // moyen primitif: 
  //  fopen
  //  fseek(SEEK_END)
  //  ftell
  //  fclose
  // moyen évolué
  //  stat
#ifndef USE_FSEEK_INSTEAD_OF_STAT
#ifndef USE_FREAD_INSTEAD_OF_STAT
  {
    int ret; 
    struct stat sb;
    
    ret = stat(fichier_nom, &sb); 
    assert(ret == 0);
    
    return ((uint64_t) sb.st_size);
  }
#else
  {
    //fprintf(stderr, "FREAD\n");
    FILE * fichier;
    int ret; 
    fichier = fopen(fichier_nom, "r"); 
    if (fichier == NULL) return 0;
    uint64_t len = 0;
    for (;;) {
      char octet;
      ret = fread(&octet, 1, 1, fichier);
      if (ret == 0) break;
      len ++;
    }
    fclose(fichier);
    return len;
  }
#endif
#else
  {
    FILE * fichier;
    int ret; 
    fichier = fopen(fichier_nom, "r"); 
    if (fichier == NULL) return 0;
    ret = fseek(fichier, 0, SEEK_END);
    assert(ret == 0);
    long int taille = -1;
    taille = ftell(fichier);
    assert(taille >= 0);
    return ((uint64_t) taille);
  }
#endif
}


char * biglib_fichier_lire(const char * fichier_nom) { 
  FILE * fichier;
  uint64_t len;
  size_t ret;
  //  int64_t len_read;
  char * fichier_contenu;

  assert(fichier_nom != NULL);

  assert(biglib_fichier_existe_huh(fichier_nom)); 
  
  len = biglib_fichier_taille(fichier_nom); 


  if (len == 0) {
    return strcopy("");
  }

  fichier = fopen(fichier_nom, "r"); 

  assert(fichier != NULL);

  
  //fichier_contenu = (char *) malloc(sizeof(char) * (len + 1)); 
  //fichier_contenu = strallouer(len);
#define UINT_MAX_LOCAL ((uint64_t) ((unsigned) ((int) -1)))
  assert(len <= UINT_MAX_LOCAL);
#undef UINT_MAX_LOCAL
  
  fichier_contenu = strallouer(((unsigned) len));
  
  //size_t fread(void * restrict ptr, size_t size, size_t nmemb, FILE * restrict stream);
  //     The functions fread() and fwrite() advance the file position indicator
  //     for the stream by the number of bytes read or written.  They return the
  //     number of objects read or written.  If an error occurs, or the end-of-
  //     file is reached, the return value is a short object count (or zero).
  // en clair, il retourne le nombre exact de blocs qui ont été lus

#define SIZE_T_MAX_LOCAL (~ ((size_t) 0))
  assert(len <= SIZE_T_MAX_LOCAL);
#undef SIZE_T_MAX_LOCAL

  ret = fread(fichier_contenu, (size_t) len, 1, fichier);

    
  
  fclose(fichier);

  assert(ret == 1);
  fichier_contenu[len] = '\0';

  return fichier_contenu;
}



void biglib_fichier_ecrire(const char * fichier_nom, const char * fichier_contenu) { 
  FILE * fichier;

  assert(fichier_nom != NULL);
  assert(fichier_contenu != NULL); 

  fichier = fopen(fichier_nom, "w"); 
  assert(fichier != NULL);

#if 0  
  fprintf(fichier, "%s\n", fichier_contenu);

  fflush(fichier);

  fclose(fichier);
#else 
  int ret; 

  ret = fwrite(fichier_contenu, strlen(fichier_contenu), 1, fichier); 
  
  fclose(fichier);
  
  assert(ret == 1);
#endif 
  
}




void biglib_fichier_rendre_executable(const char * fichier_nom) { 
  struct stat st; 
  int ret;
  mode_t mode;

  ret = stat(fichier_nom, &st);
  assert(ret == 0);

  mode = st.st_mode | S_IXUSR;
//#define S_IXUSR 0000100 /* [XSI] X for owner */

#if 0
/* /usr/include/sys/stat.h:424:NC */ extern int chmod (const char *, mode_t);
/* /usr/include/sys/stat.h:425:NC */ extern int fchmod (int, mode_t);
/* /usr/include/sys/stat.h:446:NC */ extern int lchmod (const char *, mode_t);
#endif

  ret = chmod(fichier_nom, mode);
  //ret = chmod(fichier_nom, S_IRWXU | S_IRWXG | S_IRWXO);
  //ret = chmod(fichier_nom, st.st_mode);
  assert(ret == 0);
} 





void biglib_repertoire_creer(const char * dir_nom) { 
  int ret;

#ifdef WINDOWS_DEV_CPP
  ret = mkdir(dir_nom);
#else
  ret = mkdir(dir_nom, ((uint8_t) 0777)); 
#endif

  assert(ret == 0);
}
 
void biglib_repertoire_changer(const char * projet_nom) { 
  int ret;

  ret = chdir(projet_nom); 

  assert(ret == 0);
}









