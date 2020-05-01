#ifndef EVENEMENT_H
#define EVENEMENT_H

//struct CScriptLauncher;

//#include "liste.h"
//#include "action.h" // class CScriptLauncher;



/* Ce fichier va contenir plusieurs choses,
   que j'ai réussies à obtenir de François.
   
   Tout d'abord, une classe CEvenement.
   Cette classe est la classe de description d'un évènement.
   Elle contient sa liste de processus à exécuter
   (des CScriptLauncher.).
   
   Ensuite elle contiendra une description de tous les évènements possibles,
   qu'ils soient globaux, locaux à une carte, locaux à un anime,
   ou locaux à un nonanime.
   
   Enfin une abstraction de tous les événements.
*/

// rem: le début de jeu n'est plus un événement, c'est la procédure main()

enum type_evt {
  EVT_Mort,
  EVT_ChargementCarte,
  EVT_EntreeSurCarte,
  EVT_PlusEnnemi,
  EVT_Epouvantail,
  EVT_NOMBRE
};
TYPEDEF_TYPENAME_WITHOUT_ENUM(type_evt);
extern const unsigned int nb_evts;

struct MEvenement {
  CEvenement * (* make)(void); 
  CEvenement * (* make_content)(CEvenement * this); 
  void (* delete)(CEvenement * this); 
  void (* delete_content)(CEvenement * this); 
}; 
extern const struct MEvenement * EvenementModule; 

struct CEvenement { // Problem with that is that the struct does not have the right size on declaration: "struct CEvenement e;" does not have space to hold the private data. It's not a problem when it's a pointer, it is when it's a struct. 
  CEvenement * (* make)(void); 
  CEvenement * (* make_content)(CEvenement * this); 
  void (* delete)(CEvenement * this); 
  void (* delete_content)(CEvenement * this); 

  void (* AjouterTraitement)(struct CEvenement * this, const char * file, const char * proc);
  void (* Vider)(struct CEvenement * this);
  void (* execute)(struct CEvenement * this);
}; 




struct MEvenements {
  void (* Init)(void); 
  void (* End)(void); 
  void (* Raise)(type_evt t); 
  void (* Vider)(type_evt t); 
  void (* AddTraitement)(type_evt t, const char * nom_fichier, const char * proc); 
  void (* handle_evts)(void);
}; 
extern const struct MEvenements * EvenementsModule; 



// Le type 'evenements' qui est pour le traitement des evt. 
//typedef struct CEvenement evenements_t[EVT_NOMBRE]; 


#if 0 
#if 0
  tab_evt_bool(void) {
    //printf("tab_evt_bool::tab_evt_bool()\n");
    for (unsigned int i = 0; i < nb_evts; i++)
      tab[i] = false;
  }
#endif

extern void EvenementsInit(void); 
extern void EvenementsEnd(void); 

// Déclenche un événement (en fait, ça le fait pas de suite, ça met juste un flag puis après c'est traité dans handle_evts) 
extern void RaiseEvenement(type_evt t);

// supprimer tous les traitements d'un événement
extern void ViderEvenement(type_evt t);

// ajoute un traitement à effectuer lors d'un certain événement
extern void AddTraitementEvenement(type_evt t, const char * nom_fichier, const char * proc);




extern void handle_evts(void);
#endif 


#endif /* EVENEMENT_H */

