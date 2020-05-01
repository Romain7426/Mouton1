#include "global.h"
#include "pagetitre.h"
#include "copyright.h"



enum { NB_ETAPE_FADING = 32 }; //64 }; 

static const char * CHAINE_AUTEURS = 
#if 0
  "Scripts de descriptions des personnages\nRomain (mainmain)\n\n\n"
  "Scripts des bonhommes\nRomain (mainmain)\n\n\n"
  "Scripts des objets\nRomain (mainmain)\n\n\n"
  "Scripts de  descriptions\nRomain (mainmain)\n\n\n"
  "Scripts des cartes\nRomain (mainmain)\n\n\n"
  "Scripts des cartesplans\nFrançois (c'min)\n\n\n"
#endif
  "Bonhommes\n  Pierre\n  Mathilde (Tilda)\n\n"
  "Objets 3D\n  Ludovic (Mac Do)\n\n"
  "Musiques\n  François (c'min)\n\n"
  "Moteur 3D\n  François (c'min)\n\n"
  "Scripts \n  Romain (mainmain)\n\n"
;


CPageTitre * CPageTitre_make(void) {
  MALLOC_BZERO(CPageTitre,this);
  
  ASSIGN_METHOD(CPageTitre,this,Render); 
  ASSIGN_METHOD(CPageTitre,this,Life); 
  ASSIGN_METHOD(CPageTitre,this,Input); 
  
  this -> Action = ptFADEIN; 
  this -> t = 0; 
  this -> fade = 0;
  this -> Ligne_Courante = 0.0f; 
  this -> DessineMoiUnMouton = CTexture_make("titre/dessine.moi.un.mouton.jpg"); 
  this -> Titre = CTexture_make("titre/titre.png"); 
  
  this -> MiniMenu = CMiniMenu_make(/*x*/50, /*y*/165,/*w*/1000); 
  this -> MiniMenu -> parent.Add(&this -> MiniMenu -> parent, /*colonne*/0, "Commencer une nouvelle partie", /*nom_texture*/NULL); 
  this -> MiniMenu -> parent.Add(&this -> MiniMenu -> parent, /*colonne*/0, "Continuer une partie en cours", /*nom_texture*/NULL); 
  this -> MiniMenu -> parent.Add(&this -> MiniMenu -> parent, /*colonne*/0, "Jouer une partie rapide", /*nom_texture*/NULL); 
  this -> MiniMenu -> parent.Add(&this -> MiniMenu -> parent, /*colonne*/0, "   ", /*nom_texture*/NULL); 
  this -> MiniMenu -> parent.Add(&this -> MiniMenu -> parent, /*colonne*/0, "Auteurs", /*nom_texture*/NULL); 
  this -> MiniMenu -> parent.Add(&this -> MiniMenu -> parent, /*colonne*/0, "Propriété intellectuelle", /*nom_texture*/NULL); 
  this -> MiniMenu -> parent.itheta = 2; // RL: Unfortunately, it does not work. 

  this -> the_user_told_me = PageTitre_UserToldMe_NothingYet; 
  
  return this; 
}; 


void CPageTitre_delete(CPageTitre * this) {
  CMiniMenu_delete(this -> MiniMenu); 
  CTexture_delete(this -> DessineMoiUnMouton); 
  CTexture_delete(this -> Titre); 
  free(this); 
}; 



int CPageTitre__Input(CPageTitre * this) { 
  do { 
    if (KEY_MENU_ECHAP || KeyBoard['q']) { 
      return PageTitre_UserToldMe_Bye; 
      break; 
    }; 
    
    if (this -> Action == ptDONE) { 
      return this -> the_user_told_me; 
      break; 
    }; 
    
    if (this -> Action == ptFADEOUT) { 
      if (this -> fade < 0) { 
	this -> Action = ptDONE; 
      }; 
      break; 
    }; 
    
    if (this -> Action == ptFADEIN) { 
      const int choice_made_huh = this -> MiniMenu -> Input(this -> MiniMenu); 
      break; 
    }; 
    
    if (this -> Action == ptTITRE) { 
#if 0 
      if (KEY_PASSER_TITRE) { 
	this -> Action = ptFADEOUT; 
	this -> fade = NB_ETAPE_FADING; 
	return 0; 
      }; 
#endif 
      
      const int choice_made_huh = this -> MiniMenu -> Input(this -> MiniMenu); 
      if (choice_made_huh) { 
	const int choice = this -> MiniMenu -> parent.Canceled ? -1 : this -> MiniMenu -> parent.itheta; 
	if (-1 == choice) { 
	  this -> Action = ptFADEOUT; 
	  this -> fade = NB_ETAPE_FADING; 
	} 
	else if (0 == choice) { 
	  // RL: New game 
	  this -> the_user_told_me = PageTitre_UserToldMe_NewGame; 
	  this -> Action = ptFADEOUT;   
	} 
	else if (1 == choice) { 
	  // RL: Load game 
	  this -> the_user_told_me = PageTitre_UserToldMe_LoadGame; 
	  this -> Action = ptFADEOUT;   
	} 
	else if (2 == choice) { 
	  // RL: Quick game 
	  this -> the_user_told_me = PageTitre_UserToldMe_QuickGame; 
	  this -> Action = ptFADEOUT;   
	} 
	else if (3 == choice) { 
	  // RL: Nothing 
	} 
	else if (4 == choice) { 
	  // RL: Authors 
	  this -> Action = ptAUTEURS; 
	} 
	else if (5 == choice) { 
	  // RL: Copyright 
	  this -> Action = ptCOPYRIGHT; 
	  this -> copyright_page = 0; 
	} 
	else { 
	  assert(false); 
	}; 
      }; 

      break;
    }; 

    if (this -> Action == ptAUTEURS) { 
      if (KEY_PASSER_TITRE) { 
	this -> Action = ptTITRE; 
	break; 
      }; 
      break; 
    }; 
    
    if (this -> Action == ptCOPYRIGHT) { 
      if (KEY_PASSER_TITRE) { 
	this -> copyright_page++; 
	if (this -> copyright_page >= 2) { 
	  this -> Action = ptTITRE; 
	  break; 
	}; 
      }; 
      break; 
    }; 
    

  
  } while (false); 

  return PageTitre_UserToldMe_NothingYet; 
}; 


void CPageTitre__Life(CPageTitre * this) { 
  do { 
    if (this -> Action == ptFADEIN) { 
      this -> fade++; 
      if (this -> fade >= NB_ETAPE_FADING) {
	this -> Action = ptTITRE; 
	//this -> fade = NB_ETAPE_FADING; 
      }; 
      break; 
    }; 
    
    if (this -> Action == ptFADEOUT) { 
      this -> fade--; 
      break; 
    }; 
    
    if (this -> Action == ptTITRE) { 
      this -> Ligne_Courante += 0.01f; 
      break; 
    }; 

    if (this -> Action == ptAUTEURS) { 
      break; 
    }; 
    
    if (this -> Action == ptCOPYRIGHT) { 
      break; 
    }; 
    
    if (this -> Action == ptDONE) { 
      break; 
    }; 
    
    
  } while (false); 

  this -> MiniMenu -> Life(this -> MiniMenu); 
  
  this -> t++; 
}; 


void CPageTitre__Render(const CPageTitre * this) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
  
  glDisable(GL_DEPTH_TEST); 
  
  glEnable2D(); { 
    glEnable(GL_TEXTURE_2D); 
    
    const float f = (float) this -> fade/NB_ETAPE_FADING; 
    glColor3f(f, f, f); 
    this -> Titre -> GLTextureCourante(this -> Titre); 
    BEGIN_BLIT_END(200,320,500,150,0.0f, 0.0f, 1.0f, 1.0f); 
    
    this -> DessineMoiUnMouton -> GLTextureCourante(this -> DessineMoiUnMouton); 
    //const float v = ((float) this -> t)/512.0f; 
    const float v = ((float) this -> t)/3072.0f; 
    //const float v = ((float) this -> t)/4096.0f; 
    BEGIN_BLIT_END(0, 100, SCREEN_WIDTH, 200, 0.0f + v, 0.0f, 1.0f, 1.0f);//t/512.0f, 0.0f, 640.0f/512.0f + t/512.0f, 640.0f); 

    do { 
      if (this -> Action == ptFADEIN) { 
	  this -> MiniMenu -> Render(this -> MiniMenu); 
	  break; 
      }; 
      if (this -> Action == ptTITRE) { 
#if 1 
	{
	  //const int choice_made_huh = this -> MiniMenu -> Input(this -> MiniMenu); 
	  //this -> MiniMenu -> Life(this -> MiniMenu); 
	  this -> MiniMenu -> Render(this -> MiniMenu); 
	}; 
#else 
	{ 
	  bool b; // RL: Unused 
	  Text -> print2(Text, this -> Ligne_Courante, 7, 100000, 100, 100, 5000, 300, CHAINE_AUTEURS, &b); 
	}; 
#endif 
	break; 
      }; 
      
      if (this -> Action == ptAUTEURS) { 
	bool toutaffiche_huh; // RL: Unused 
	Text -> print2(Text, /*l*/0, /*nblignes*/16, /*nbcaracmax*/100000, /*x*/145, /*y*/310, /*w*/5000, /*h*/300, CHAINE_AUTEURS, /*toutaffiche_ref*/&toutaffiche_huh); 
	break; 
      }; 
      
      if (this -> Action == ptCOPYRIGHT) { 
	static const char disclaimer[] = 
	  "Bonjour! :-)" "\n" 
	  "Nous espérons que vous portez bien. :-)" "\n" 
	  "Concernant la propriété intellectuelle et les droits d'auteur du présent logiciel et de son code source, sentez-vous libre d'en user et d'en faire ce que bon vous semble." " "
	  "Nous émettons une restriction toutefois: si vous pouvez protéger de la façon qui vous plaît le travail que vous aurez ajouté au Logiciel et à son code source, " 
	  "vous ne pouvez pas restreindre l'utilisation du Logiciel en tant que tel, ni de son code source. " "\n" 
	  "C'est la raison pour laquelle ceux-ci ne sont pas dans le domaine public: il semblerait que d'aucuns pourraient se les approprier, ainsi en réclamer des droits intellectuels dessus, voire empêcher notre utilisation de ceux-ci. Afin de nous couvrir contre ce risque, le présent logiciel et son code source sont sous licence ISC (cf. page suivante), qui nous semble remplir cet office." "\n" 
	  "Merci! Puissent les vents vous être favorables. :-)" 
	  ""; 
	if (0 == this -> copyright_page) { 
	  bool toutaffiche_huh; // RL: Unused 
	  Text -> print2(Text, /*l*/0, /*nblignes*/30, /*nbcaracmax*/100000, /*x*/3, /*y*/SCREEN_HEIGHT-37, /*w*/630, /*h*/470, disclaimer, /*toutaffiche_ref*/&toutaffiche_huh); 
	}
	else if (1 == this -> copyright_page) { 
	  bool toutaffiche_huh; // RL: Unused 
	  Text -> print2(Text, /*l*/0, /*nblignes*/30, /*nbcaracmax*/100000, /*x*/3, /*y*/SCREEN_HEIGHT-5, /*w*/5000, /*h*/300, program_copyright, /*toutaffiche_ref*/&toutaffiche_huh); 
	}
	else { 
	  bool toutaffiche_huh; // RL: Unused 
	  const char wrong[] = "Something got wrong"; 
	  Text -> print2(Text, /*l*/0, /*nblignes*/30, /*nbcaracmax*/100000, /*x*/3, /*y*/SCREEN_HEIGHT-37, /*w*/630, /*h*/470, wrong, /*toutaffiche_ref*/&toutaffiche_huh); 
	}; 
	break; 
      }; 
    
      
    } while (false); 
    
  } glDisable2D(); 
  
  glEnable(GL_DEPTH_TEST); 
}; 

