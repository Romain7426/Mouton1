#include "global.hpp"
#include "evenement.hpp"
#include "map.hpp"
#include "apiscript.hpp"


const unsigned int nb_evts = EVT_NOMBRE;



void CEvenement::AjouterTraitement(const char * file, const char * proc) {
  CScriptLauncher * launcher;
  
  launcher = new CScriptLauncher(file, proc);
  liste_traitement -> Empiler_sans_copie(launcher);
}


void CEvenement::execute(void) {
  if (SCRIPT_EstEnTrainDExecuterUnScript()) {
    return;
  }

  
  CAccesseur<CScriptLauncher> acc = liste_traitement -> ObtenirAcces();

#if 1
  if (not(acc.IsFin())) {
    acc.Element() -> Execute();
  }
#else
  while (not(acc.IsFin())) {
    acc.Element() -> Execute();
    acc.AllerSuivant();
  }
#endif
}


void CEvenement::Vider(void) {
  liste_traitement -> Vider();
}



// Le tableau de tous les évènements globaux qui ont été produites.
//static bool tab_evt_global[nb_evt] = {false,false,false,false,false};
static tab_evt_bool tab_evt;

// Les événements
evenements_t evts;

// Met le traitement sur la liste des globaux.
void RaiseEvenement(type_evt t) {
  if (!SCRIPT_EstEnTrainDExecuterUnScript())
    tab_evt.tab[t] = true;
}

void ViderEvenement(type_evt t) {
  evts[t].Vider();
}


void AddTraitementEvenement(type_evt t, const char * nom_fichier, const char * proc) {
  evts[t].AjouterTraitement(nom_fichier, proc);
}



// La fonction de traitement des evenements globaux.
void handle_evts(void) {
  if (SCRIPT_EstEnTrainDExecuterUnScript())
    return;
  
  for (unsigned int i = 0; i < nb_evts; i++) {
    if (tab_evt.tab[i]) {
      printf("EVENEMENT n° %i déclenché!\n", i);
      fflush(NULL);
      tab_evt.tab[i] = false;
      evts[i].execute();
    }
  }
}



