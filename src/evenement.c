#include "global.h"
#include "evenement.h"
#include "map.h"
#include "apiscript.h"

#define liste_traitement__array (this -> liste_traitement__array ) 
#define liste_traitement__nb    (this -> liste_traitement__nb    ) 
#define liste_traitement__head  (this -> liste_traitement__head  ) 
#define liste_traitement__tail  (this -> liste_traitement__tail  ) 

const unsigned int nb_evts = EVT_NOMBRE;


CEvenement * CEvenement_make(void) {
  MALLOC_BZERO(CEvenement,this);
  
  ASSIGN_METHOD(CEvenement,this,AjouterTraitement); 
  ASSIGN_METHOD(CEvenement,this,Vider); 
  ASSIGN_METHOD(CEvenement,this,execute); 
  
  liste_traitement__nb = 0;
  liste_traitement__head = 0; 
  liste_traitement__tail = 0; 
  
  return this; 
}; 

void CEvenement_delete(CEvenement * this) { 
  free(this); 
};


void CEvenement__liste_traitement__push(CEvenement * this, CScriptLauncher * sl) { 
  assert(liste_traitement__nb < CEvenement__liste_traitement__size); 
  if (liste_traitement__tail == CEvenement__liste_traitement__size) { 
    liste_traitement__tail = 0; 
  }; 
  *(liste_traitement__array + liste_traitement__tail) = sl; 
  liste_traitement__tail++; 
  liste_traitement__nb++; 
}; 

void CEvenement__Vider(CEvenement * this) {
  liste_traitement__nb = 0;
  liste_traitement__head = 0; 
  liste_traitement__tail = 0; 
};

CScriptLauncher * CEvenement__liste_traitement__top(CEvenement * this) { 
  if (liste_traitement__nb == 0) return NULL; 
  return *(liste_traitement__array + liste_traitement__head); 
}; 



void CEvenement__AjouterTraitement(CEvenement * this, const char * file, const char * proc) {
  CScriptLauncher * launcher = CScriptLauncher_make(file, proc); 
  CEvenement__liste_traitement__push(this, launcher); 
};


void CEvenement__execute(CEvenement * this) {
  if (SCRIPT_EstEnTrainDExecuterUnScript()) { return; }; 
  
  CScriptLauncher * sl = CEvenement__liste_traitement__top(this); 
  
#if 1
  if (!(sl == NULL)) { 
    sl -> Execute(sl); 
  }; 
  
#elif 0
  if (not(acc.IsFin())) {
    acc.Element() -> Execute();
  }
#else
  while (not(acc.IsFin())) {
    acc.Element() -> Execute();
    acc.AllerSuivant();
  }
#endif
};





// Le tableau de tous les évènements globaux qui ont été produites.
//static bool tab_evt_global[nb_evt] = {false,false,false,false,false};
static struct tab_evt_bool tab_evt;

// Les événements
evenements_t evts;

// Met le traitement sur la liste des globaux.
void RaiseEvenement(type_evt t) {
  if (!SCRIPT_EstEnTrainDExecuterUnScript())
    tab_evt.tab[t] = true;
};

void ViderEvenement(type_evt t) {
  evts[t].Vider(&evts[t]);
};


void AddTraitementEvenement(type_evt t, const char * nom_fichier, const char * proc) {
  evts[t].AjouterTraitement(&evts[t], nom_fichier, proc);
};



// La fonction de traitement des evenements globaux.
void handle_evts(void) {
  if (SCRIPT_EstEnTrainDExecuterUnScript())
    return;
  
  for (unsigned int i = 0; i < nb_evts; i++) {
    if (tab_evt.tab[i]) {
      printf("EVENEMENT n° %i déclenché!\n", i);
      fflush(NULL);
      tab_evt.tab[i] = false;
      evts[i].execute(&evts[i]);
    }
  }
};



