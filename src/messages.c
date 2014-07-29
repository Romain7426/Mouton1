#include <stdarg.h>
#include "global.hpp"
#include "messages.hpp"


// Dans ce qui suit, on d�finit les fonctions de messages. */

#define FILENOTICE (LOGDIR "messages.log")
#define FILEERROR  (LOGDIR "erreurs.log")

static FILE * zeldafnotice;
static FILE * zeldaferror;

/*
static void vmessage(const char * mess, va_list args);
static void vmesserr(const char * mess, va_list args);
*/


void init_message(void) {
  (void) fprintf(stdout, "Initialisation des fonctions de message.\n");
 
  (void) (zeldafnotice = fopen(FILENOTICE, "w"));
  if (zeldafnotice == NULL) {
      (void) fprintf(stdout, "Ouverture impossible en �criture du fichier \"%s\".\nFin de  l'ex�cution.\n", FILENOTICE);
      assert(false);
    }
 
  (void) fprintf(stdout, "Ouverture en �criture du fichier \"%s\" r�ussie.\n", FILENOTICE);
  (void) fprintf(zeldafnotice, "Ouverture en �criture du fichier \"%s\" r�ussie.\n", FILENOTICE);

  (void) (zeldaferror = fopen(FILEERROR, "w"));
  if (zeldaferror == NULL) {
      (void) fprintf(stdout, "Ouverture impossible en �criture du fichier \"%s\".\nFin de  l'ex�cution.\n", FILEERROR);
      (void) fprintf(zeldafnotice, "Ouverture impossible en �criture du fichier \"%s\".\nFin de  l'ex�cution.\n", FILEERROR);
      (void) fclose(zeldafnotice);
      assert(false);
    }
    
  (void) fprintf(stdout, "Ouverture en �criture du fichier \"%s\" r�ussie.\n\n", FILEERROR);
  (void) fprintf(zeldafnotice, "Ouverture en �criture du fichier \"%s\" r�ussie.\n\n\n", FILEERROR);
  (void) fprintf(zeldaferror, "Ouverture en �criture du fichier \"%s\" r�ussie.\n\n\n", FILEERROR);

}


void end_message(void) {
  (void) fprintf(stdout, "Fermeture du fichier \"%s\".\n", FILEERROR);
  (void) fprintf(zeldafnotice, "Fermeture du fichier \"%s\".\n", FILEERROR);
  (void) fprintf(zeldaferror, "Fermeture du fichier \"%s\".\n", FILEERROR);

  (void) fclose(zeldaferror);
  (void) (zeldaferror = NULL);
 

  (void) fprintf(stdout, "Fermeture du fichier \"%s\".\n", FILENOTICE);
  (void) fprintf(zeldafnotice, "Fermeture du fichier \"%s\".\n", FILENOTICE);

  (void) fclose(zeldafnotice);
  (void) (zeldafnotice = NULL); 
 
  (void) fprintf(stdout, "Fichiers ferm�s.\n");
}

void vmessage(const char * mess, va_list args) {
  (void) vfprintf(zeldafnotice, mess, args);
  (void) fprintf(zeldafnotice, "\n");
  fflush(NULL);
}

void message(const char * mess, ...) {
  va_list args;
  
  va_start(args, mess);
  vmessage(mess, args);
  va_end(args);
}

void vmesserr(const char * mess, va_list args) {
  va_list tmp;

  va_copy(tmp, args);
  
  (void) fprintf(zeldafnotice, "ERREUR: ");
  (void) vfprintf(zeldafnotice, mess, tmp);
  (void) fprintf(zeldafnotice, "\n");
  
  (void) vfprintf(zeldaferror, mess, args);
  (void) fprintf(zeldaferror, "\n");
  
  fflush(NULL);

  va_end(tmp);
}

void messerr(const char * mess, ...) {
  va_list args;
  
  va_start(args, mess);
  vmesserr(mess, args);
  va_end(args);
}

