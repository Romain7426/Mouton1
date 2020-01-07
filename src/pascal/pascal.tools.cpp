#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "global.hpp"
#include "pascal/pascal.tools.hpp"
#include "apiscript.hpp"
#include "asprintf.hpp"


static FILE *pascal_notice_fout;
static FILE *pascal_error_fout;
//static char *pascal_notice_name;
//static char *pascal_error_name;
#define PASCAL_NOTICE_NAME_SUFFIX ".pascal.notice.txt"
#define PASCAL_ERROR_NAME_SUFFIX ".pascal.error.txt"



char * itoa(int i) {
  char * temp;
  asprintf(&temp, "%d", i);
  return temp;
}

char * ftoa(float f) {
  char * temp;
  asprintf(&temp, "%f", ((double) f));
  return temp;
}

char * btoa(bool b) {
  return strcopy(btoa_tab[b]);
}

const char * btoa_const(bool b) {
  return btoa_tab[b];
}

#if ((0 != 0) == 0) && ((0 == 0) == 1)
const char * btoa_tab[2] = {"FAUX", "VRAI"};
#elif ((0 != 0) == 1) && ((0 == 0) == 0)
const char * btoa_tab[2] = {"VRAI", "FAUX"};
#else
#error "Cannot get the value of 'true' and 'false'"
#endif





void pmessage(const char *mess, ...) {
  va_list args;
  
  va_start(args, mess);
  (void) vfprintf(pascal_notice_fout, mess, args);
  (void) fprintf(pascal_notice_fout, "\n");
  va_end(args);
  fflush(NULL);
}

void pmesserr(const char *mess, ...) {
  va_list args;
  
  va_start(args, mess);
  (void) fprintf(pascal_notice_fout, "ERREUR: ");
  (void) vfprintf(pascal_notice_fout, mess, args);
  (void) fprintf(pascal_notice_fout, "\n");
  va_end(args);
  va_start(args, mess);
  (void) vfprintf(pascal_error_fout, mess, args);
  (void) fprintf(pascal_error_fout, "\n");
  va_end(args);
  fflush(NULL);

  // Pour débugage plus facile selon C'Min.
  // On a aucune idée de la taille et aucun moyen de contrôle !!!
  // Formaidable le C/C++ !!!!
  // On espère quand que 1ko devrait aller...
  // En fait, ça marche pas car elle peut être lancée alors que le render n'est
  // pas fait.

  /*
  char *buffer;


  buffer = new char[10240];
  va_start(args, mess);
  vsprintf(buffer, mess, args);
  va_end(args);
  //SCRIPT_AfficherMessage(buffer);
  delete [] buffer;
  */
}

int pmessinit(const char *nom) {
  char *notice_name, *error_name;

  if (nom == NULL) {
    //messerr("Impossible de créer les fichiers d'erreurs car le nom pour générer le fichier de message est un pointeur NULL.");
    return -1;
  }

#if 0
  notice_name = new char[strlen(nom) + strlen(PASCAL_NOTICE_NAME_SUFFIX) + 1];
  strcat(strcpy(notice_name, nom), PASCAL_NOTICE_NAME_SUFFIX);
  
  error_name = new char[strlen(nom) + strlen(PASCAL_ERROR_NAME_SUFFIX) + 1];
  strcat(strcpy(error_name, nom), PASCAL_ERROR_NAME_SUFFIX);
#endif

  //fprintf(stderr, "pmessinit: %s\n", nom);

  notice_name = STRCAT3_(LOGDIR, nom, PASCAL_NOTICE_NAME_SUFFIX);
  error_name = STRCAT3_(LOGDIR, nom, PASCAL_ERROR_NAME_SUFFIX);
  
  pascal_notice_fout = NULL;
  pascal_error_fout = NULL;

  pascal_notice_fout = fopen(notice_name, "w");
  if (pascal_notice_fout == NULL) {
    //messerr("Impossible d'ouvrir en écriture le fichier \"%s\".", notice_name);
    delete[] error_name;
    delete[] notice_name;
    return -2;
  }

  pascal_error_fout = fopen(error_name, "w");
  if (pascal_error_fout == NULL) {
    //messerr("Impossible d'ouvrir en écriture le fichier \"%s\".", error_name);
    delete[] error_name;
    delete[] notice_name;
    return -3;
  }

  pmesserr("! Ouverture des fichiers de log de compilation réussie ! (\"%s\" et \"%s\").", notice_name, error_name);

  return 0;

}


void pmessend(void) {
  pmesserr("! Fermeture des fichiers de log.");
  (void) fclose(pascal_error_fout);
  (void) fclose(pascal_notice_fout);
}






/*

char *strcopy(const char *str) {
  char *temp;

  if (str == NULL) {
    pmessage("Passage d'un paramètre NULL à strcopy().");
    return NULL;
  }
  
  temp = strcpy(new char[strlen(str)+1], str);

  return temp;
}
*/

/*
static const double ln2 = log(((double)2));
#define log2(d) (log((d)) / (ln2))
*/







#define PPOS_STR1 "Considérons ce qu'il y écrit depuis le caractère "
#define PPOS_STR2 " de la ligne "
#define PPOS_STR3 " jusqu'au caractère "
#define PPOS_STR4 " de la ligne "
#define PPOS_STR5 " (du caractère "
#define PPOS_STR6 " au caractère "
#define PPOS_STR7 " lorsqu'on compte depuis le début du fichier)."
//#define NB_SIZE 11 // taille du plus grand nombre 32 bits en base 10
                   // plus le caractère nul. Lors du passage à 64 bits, 
                   // il faudra changer cette valeur ;-).
char * ppos::toString(void) const {
  char * resultat;
  char * nombre[6];
  unsigned int taille;

  (void) asprintf(&(nombre[0]), "%u", deb_ligne);
  (void) asprintf(&(nombre[1]), "%u", fin_ligne);
  (void) asprintf(&(nombre[2]), "%u", deb_car);
  (void) asprintf(&(nombre[3]), "%u", fin_car);
  (void) asprintf(&(nombre[4]), "%u", deb_car_tot);
  (void) asprintf(&(nombre[5]), "%u", fin_car_tot);

  taille = strlen(nombre[0]) + strlen(nombre[1]) + strlen(nombre[2]) + strlen(nombre[3]) + strlen(nombre[4]) + strlen(nombre[5]) + strlen(PPOS_STR1) + strlen(PPOS_STR2) + strlen(PPOS_STR3) + strlen(PPOS_STR4) + strlen(PPOS_STR5) + strlen(PPOS_STR6) + strlen(PPOS_STR7);

  resultat = new char[taille + 1];
  
  strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcpy(resultat, PPOS_STR1), nombre[0]), PPOS_STR2), nombre[1]), PPOS_STR3), nombre[2]), PPOS_STR4), nombre[3]), PPOS_STR5), nombre[4]), PPOS_STR6), nombre[5]), PPOS_STR7);

  free(nombre[0]);
  free(nombre[1]);
  free(nombre[2]);
  free(nombre[3]);
  free(nombre[4]);
  free(nombre[5]);

  return resultat;
}

  
