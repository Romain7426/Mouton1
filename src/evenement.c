#include "global.h"
#include "evenement.h"
#include "map.h"
#include "script_api.h"

static const struct CEvenement methodes; 

#ifndef TYPE__PEVENEMENT 
#define TYPE__PEVENEMENT 
struct PEvenement; 
typedef struct PEvenement PEvenement; 
#endif 

enum { CEvenement__liste_traitement__size = 127 }; 
struct PEvenement {
  struct CEvenement methodes; 
  CScriptLauncher * liste_traitement__array[CEvenement__liste_traitement__size];
  int liste_traitement__nb;
  int liste_traitement__head; 
  int liste_traitement__tail; 
}; 



#define liste_traitement__array (this -> liste_traitement__array ) 
#define liste_traitement__nb    (this -> liste_traitement__nb    ) 
#define liste_traitement__head  (this -> liste_traitement__head  ) 
#define liste_traitement__tail  (this -> liste_traitement__tail  ) 

const unsigned int nb_evts = EVT_NOMBRE;


static CEvenement * CEvenement__make_content(CEvenement * this_m) {
  PEvenement * this = (PEvenement *) this_m; 
  BZERO_THIS(this); 
  
  this -> methodes = methodes; 

#if 0   
  ASSIGN_METHOD(CEvenement,this,AjouterTraitement); 
  ASSIGN_METHOD(CEvenement,this,Vider); 
  ASSIGN_METHOD(CEvenement,this,execute); 
#endif 
  
  liste_traitement__nb = 0;
  liste_traitement__head = 0; 
  liste_traitement__tail = 0; 
  
  return (CEvenement *) this; 
}; 

static CEvenement * CEvenement__make(void) {
  MALLOC_THIS(PEvenement,this); 
  return CEvenement__make_content((CEvenement *) this); 
}; 

static void CEvenement__delete_content(CEvenement * this_m) { 
  PEvenement * this = (PEvenement *) this_m; 
  BZERO_THIS(this); 
}; 

static void CEvenement__delete(CEvenement * this) { 
  CEvenement__delete_content(this); 
  free(this); 
}; 
 
 
static void CEvenement__liste_traitement__push(CEvenement * this_m, CScriptLauncher * sl) { 
  PEvenement * this = (PEvenement *) this_m; 
  assert(liste_traitement__nb < CEvenement__liste_traitement__size); 
  if (liste_traitement__tail == CEvenement__liste_traitement__size) { 
    liste_traitement__tail = 0; 
  }; 
  *(liste_traitement__array + liste_traitement__tail) = sl; 
  liste_traitement__tail++; 
  liste_traitement__nb++; 
}; 

static void CEvenement__Vider(CEvenement * this_m) { 
  PEvenement * this = (PEvenement *) this_m; 
  liste_traitement__nb = 0;
  liste_traitement__head = 0; 
  liste_traitement__tail = 0; 
};

static CScriptLauncher * CEvenement__liste_traitement__top(CEvenement * this_m) { 
  PEvenement * this = (PEvenement *) this_m; 
  if (liste_traitement__nb == 0) return NULL; 
  return *(liste_traitement__array + liste_traitement__head); 
}; 



static void CEvenement__AjouterTraitement(CEvenement * this_m, const char * file, const char * proc) {
  PEvenement * this = (PEvenement *) this_m; 
  CScriptLauncher * launcher = CScriptLauncher_make(file, proc); 
  CEvenement__liste_traitement__push(this_m, launcher); 
};


static void CEvenement__execute(CEvenement * this_m) { 
#if 0 
  PEvenement * this = (PEvenement *) this_m; 
  if (SCRIPT_EstEnTrainDExecuterUnScript()) { return; }; 
  
  CScriptLauncher * sl = CEvenement__liste_traitement__top(this_m); 
  
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
#endif 
};





// ********************************************************************* 
 
// Les evts globaux. 
//extern evenements_t evts; 
 
// La liste des évènements globaux qui ont été lancés. 
//static bool tab 
struct tab_evt_bool {
  bool tab[EVT_NOMBRE];
};




// Le tableau de tous les évènements globaux qui ont été produites.
//static bool tab_evt_global[nb_evt] = {false,false,false,false,false};
static struct tab_evt_bool tab_evt;

// Les événements 
// RL: Ceux-ci sont globaux. 
//evenements_t evts;
static struct PEvenement evts[EVT_NOMBRE]; 


// Met le traitement sur la liste des globaux.
static void RaiseEvenement(type_evt t) { 
#if 0 
  if (!SCRIPT_EstEnTrainDExecuterUnScript())
    tab_evt.tab[t] = true;
#endif 
};

static void ViderEvenement(type_evt t) {
  evts[t].methodes.Vider((CEvenement *) &evts[t]);
};

static void AddTraitementEvenement(type_evt t, const char * nom_fichier, const char * proc) {
  evts[t].methodes.AjouterTraitement((CEvenement *) &evts[t], nom_fichier, proc);
};

// La fonction de traitement des evenements globaux.
static void handle_evts(void) {
#if 0 
  if (SCRIPT_EstEnTrainDExecuterUnScript())
    return;
  
  for (unsigned int i = 0; i < nb_evts; i++) {
    if (tab_evt.tab[i]) {
      printf("EVENEMENT n° %i déclenché!\n", i);
      fflush(NULL);
      tab_evt.tab[i] = false;
      evts[i].methodes.execute((CEvenement *) &evts[i]);
    }
  }
#endif 
};

static void EvenementsInit(void) { 
  for (int i = 0; i < EVT_NOMBRE; i++) { 
    EvenementModule -> make_content((CEvenement *) &evts[i]); 
  }; 
  for (unsigned int i = 0; i < nb_evts; i++) { 
    tab_evt.tab[i] = false; 
  }; 
}; 
 
static void EvenementsEnd(void) { 
  for (int i = 0; i < EVT_NOMBRE; i++) { 
    EvenementModule -> delete_content((CEvenement *) &evts[i]); 
  };  
}; 

static const struct CEvenement methodes = { 
  CEvenement__make, 
  CEvenement__make_content, 
  CEvenement__delete, 
  CEvenement__delete_content, 
  CEvenement__AjouterTraitement, 
  CEvenement__Vider, 
  CEvenement__execute 
}; 
 
static const struct MEvenement EvenementModule__content = { 
  CEvenement__make, 
  CEvenement__make_content, 
  CEvenement__delete, 
  CEvenement__delete_content, 
}; 
const struct MEvenement * EvenementModule = &EvenementModule__content; 




static const struct MEvenements EvenementsModule_content = {
  EvenementsInit, 
  EvenementsEnd, 
  RaiseEvenement, 
  ViderEvenement, 
  AddTraitementEvenement, 
  handle_evts
}; 
const struct MEvenements * EvenementsModule = &EvenementsModule_content; 
  
