#include <stdlib.h>
#include <stdio.h>
#include "global.hpp"
#include "nonanime/nonanime.global.hpp"
#include "nonanime/nonanime.parser.hpp"
#include "objnonanime.hpp"


#define SUFF_NONANIMEOUT ".lexing.out"

extern FILE *yynonanimein;
extern FILE *yynonanimeout;
extern int yynonanimeparse(void);
extern CObjNonAnime *objet;

//int CObjNonAnime::parse(const char * filename) {
int CObjNonAnime::parse(const char * dir, const char * filename) {
  int res;
  FILE *entrin;
  char *nonanime_out;


  if (filename == NULL) {
    (void)fprintf(stderr, "Erreur: impossible 'filename' est le pointeur NULL.\n");
    return -1;
  }
  


  //nonanime_out = strcat(strcpy(new char[strlen(filename) + strlen(SUFF_NONANIMEOUT) + 1], filename), SUFF_NONANIMEOUT);
  nonanime_out = STRCAT3_(LOGDIR,filename,SUFF_NONANIMEOUT);
#if 0
  fprintf(stderr, "fout = %s\n", nonanime_out);
  yynonanimeout = fopen(nonanime_out, "wb");
  assert(yynonanimeout != NULL);
  assert(false);
#endif

  message("On essaye d'ouvrir en lecture le fichier '%s'.", nonanime_out);
  yynonanimeout = fopen(nonanime_out, "wb");
  if (yynonanimeout == NULL) {
    (void) fprintf(stderr, "Erreur: impossible d'ouvrir en écriture le fichier \"%s\".\n", nonanime_out);
    (void) fclose(entrin);
    return -3;
  }
  delete [] nonanime_out;



  //yynonanimein
  filename = STRCAT2_(dir, filename);
  entrin = fopen(filename, "rb");
  if (entrin == NULL) {
    (void)fprintf(stderr, "Erreur : impossible d'ouvrir en lecture le fichier \"%s\".\n", filename);
    return -2;
  }


  nonanime_restart_lexer();
  yynonanimerestart(entrin);
  nonanime_reset_parser();

  /* L'analyse elle meme. */
  objet = this;
#if 1
  res = yynonanimeparse();
#else
  res = 0;
#endif

  /* On ferme les flux. */
  (void) fclose(yynonanimeout); 
  (void) fclose(yynonanimein);
  
  /* On match. */
  switch (res) {
  case 0:  (void) fprintf(stdout, "Analyse réussie !!!\n"); return 0;
  default: (void) fprintf(stdout, "Analyse ratée...\n"); return res - 128;
  }
  
}

