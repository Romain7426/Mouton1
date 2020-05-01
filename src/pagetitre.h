#ifndef CPageTitre_H 
#define CPageTitre_H 

struct CPageTitre; 
enum TPageTitreAction; 
TYPEDEF_TYPENAME_WITHOUT_ENUM(TPageTitreAction); 

enum { 
  PageTitre_UserToldMe_NothingYet, 
  PageTitre_UserToldMe_Bye, 
  PageTitre_UserToldMe_QuickGame, 
  PageTitre_UserToldMe_NewGame, 
  PageTitre_UserToldMe_LoadGame, 
}; 


// RL: Automaton states. 
enum TPageTitreAction { 
  ptDONE, // RL: Everything done. 
  ptFADEIN, // RL: We get in. 
  ptTITRE,  // RL: Cruise time. 
  ptAUTEURS,  // RL: Displaying authors 
  ptCOPYRIGHT,  // RL: Displaying copyright 
  ptFADEOUT // RL: We get out. 
}; 

struct CPageTitre { 
  TPageTitreAction Action; // RL: Actually, it's an automaton, and these are the three states of the automaton. 
  //int Action; // RL: Actually, it's an automaton, and these are the three states of the automaton. 
  CTexture * DessineMoiUnMouton; 
  CTexture * Titre; 
  int t; // RL: Which is? // RL: Ok, it's to control the displayed-sheep speed. 
  int fade; 
  float Ligne_Courante; 
  CMiniMenu * MiniMenu; // RL: Main choice 
  int the_user_told_me; 
  int copyright_page; 
  
  void (* Render)(const struct CPageTitre * this); 
  void (* Life)(struct CPageTitre * this); 
  int  (* Input)(struct CPageTitre * this); 
};

extern CPageTitre * CPageTitre_make(void);
extern void CPageTitre_delete(CPageTitre * this);
extern void CPageTitre__Render(const CPageTitre * this);
extern void CPageTitre__Life(CPageTitre * this);
extern int  CPageTitre__Input(CPageTitre * this);





#if 0 

static int a[sizeof(enum TPageTitreAction) == 4 ? 1 : -1] = { 0 }; // RL: This is true. So clang compiles it as an 'int', as it should. 

#endif 

#if 0 

//RL: Too bad that there's no simple way of having class methods (or attributes). 

struct CPageTitre_method_t { 
  void (* Render)(const struct CPageTitre * this); 
  void (* Life)(struct CPageTitre * this); 
  int  (* Input)(struct CPageTitre * this); 
}; 

static const struct CPageTitre_method_t CPageTitre_method = { 
&CPageTitre__Render,
&CPageTitre__Life,
&CPageTitre__Input
}; 

enum { CPageTitre__Render__Offset = 0 }; 
enum { CPageTitre__Life__Offset = sizeof(void*) }; 
enum { CPageTitre__Input__Offset = 2*sizeof(void*) }; 

#define CALL_METHOD(this,method_ident,...) 

#endif 

#endif /* CPageTitre_H */ 
