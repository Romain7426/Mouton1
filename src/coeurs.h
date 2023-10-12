#ifndef COEURS_H
#define COEURS_H

/*******************************************************************************
 Affichage des coeurs
 (animés et tout...)
 ******************************************************************************/

struct CAffichageCoeur;

enum {              CAffichageCoeur_bytesize = 64 }; 
extern const int8_t CAffichageCoeur_bytesize_actual; 
static void CAffichageCoeur__check_and_assert(const int8_t debug_print_huh, const int stderr_d) { 
  if (debug_print_huh) { 
    //fprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "I failed to clean up the log subdir.' " "\n", __func__); 
    write_string4(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<", __func__, "()>}: ", "CAffichageCoeur_bytesize: "); write_long_long_int(stderr_d, CAffichageCoeur_bytesize); write_eol(stderr_d); 
    write_string4(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<", __func__, "()>}: ", "CAffichageCoeur_bytesize_actual: "); write_long_long_int(stderr_d, CAffichageCoeur_bytesize_actual); write_eol(stderr_d); 
  }; 
  assert(CAffichageCoeur_bytesize >= CAffichageCoeur_bytesize_actual); 
}; 

extern CAffichageCoeur * CAffichageCoeur_make(void); 
extern void CAffichageCoeur_delete(CAffichageCoeur * this); 
extern void CAffichageCoeur__InformerNbPV(struct CAffichageCoeur * this, int inpv);  
extern void CAffichageCoeur__Render(const struct CAffichageCoeur * this);
extern void CAffichageCoeur__Life(struct CAffichageCoeur * this); 




// RL: TODO FIXME XXX: Cette variable globale ne devrait pas être ici. 
extern struct CAffichageCoeur * AffichageCoeur; 


#endif

