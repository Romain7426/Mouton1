#ifndef CAffichageMainPierre_H
#define CAffichageMainPierre_H

/*******************************************************************************
 Affichage de la main et de la pierre (qui indique l'heure)
 ******************************************************************************/

struct CAffichageMainPierre; 
//typedef struct CAffichageMainPierre CAffichageMainPierre; 

enum {              CAffichageMainPierre_bytesize = 32 }; 
extern const int8_t CAffichageMainPierre_bytesize_actual; 
static void CAffichageMainPierre__check_and_assert(const int8_t debug_print_huh, const int stderr_d) { 
  if (debug_print_huh) { 
    //fprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "I failed to clean up the log subdir.' " "\n", __func__); 
    write_string4(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<", __func__, "()>}: ", "CAffichageMainPierre_bytesize: "); write_long_long_int(stderr_d, CAffichageMainPierre_bytesize); write_eol(stderr_d); 
    write_string4(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<", __func__, "()>}: ", "CAffichageMainPierre_bytesize_actual: "); write_long_long_int(stderr_d, CAffichageMainPierre_bytesize_actual); write_eol(stderr_d); 
  }; 
  assert(CAffichageMainPierre_bytesize >= CAffichageMainPierre_bytesize_actual); 
}; 

extern CAffichageMainPierre * CAffichageMainPierre_make(void); 
extern void                   CAffichageMainPierre_delete(CAffichageMainPierre * this); 
extern void                   CAffichageMainPierre__Render(const CAffichageMainPierre * this, const float y, const float FacteurCompression); //const CMap * Map); 

#endif

