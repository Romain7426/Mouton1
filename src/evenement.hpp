#ifndef EVENEMENT_HPP
#define EVENEMENT_HPP

class CScriptLauncher;
#include "liste.hpp"
#include "action.hpp" // class CScriptLauncher;



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

typedef enum type_evt type_evt;
extern const unsigned int nb_evts;


class CEvenement {
private:
  CListe<CScriptLauncher> * liste_traitement;
public:
  CEvenement(void) : liste_traitement(new CListe<CScriptLauncher>()) {};
  ~CEvenement(void) { delete liste_traitement; };

  void AjouterTraitement(const char * file, const char * proc);
  void Vider(void);
  void execute(void);
};





// Le type 'evenements' qui est pour le traitement des evt.
typedef CEvenement evenements_t[EVT_NOMBRE];

// Les evts globaux.
extern evenements_t evts;

// La liste des évènements globaux qui ont été lancés.
//static bool tab
struct tab_evt_bool {
  bool tab[EVT_NOMBRE];
  tab_evt_bool(void) {
    //printf("tab_evt_bool::tab_evt_bool()\n");
    for (unsigned int i = 0; i < nb_evts; i++)
      tab[i] = false;
  }
};



// Déclenche un événement (en fait, ça le fait pas de suite, ça met juste un flag puis après c'est traité dans handle_evts
extern void RaiseEvenement(type_evt t);

// supprimer tous les traitements d'un événement
extern void ViderEvenement(type_evt t);

// ajoute un traitement à effectuer lors d'un certain événement
extern void AddTraitementEvenement(type_evt t, const char * nom_fichier, const char * proc);




extern void handle_evts(void);



#endif /* EVENEMENT.HPP */

