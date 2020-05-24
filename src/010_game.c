#include "global.h"
#include "010_game.h"
#include "015_game_events.h"
#include "map.h"
#include "menu.h"
#include "bonhomme.h"
#include "text.h"
#include "objnonanime.h"
#include "coeurs.h"
#include "pagetitre.h"
#include "affichagemainpierre.h"
#include "evenement.h"
#include "action.h"
#include "moteurteleportation.h"
#include "camera.h"
#include "menuentreenom.h"

static int  Game_ProcessEvents(const int current_mj, api_contexte_t * api_contexte); 
static int  Game_ProcessInputs(const int current_mj); 
static void Game_Life(const int animate_but_do_not_aliven_huh); 
static void Game_Blit(void); 

static void RenderCiel(const CMap * Map, const float heros_y); 

enum { nb_cases_afficheesX       = 1000 }; //25 }; 
enum { nb_cases_afficheesYfond   = 1000 }; //20 }; 
enum { nb_cases_afficheesYdevant = 1000 }; //10 }; 

static bool EnVaisseau = false;

//static riemann_t our_manifold[1]; 
static riemann_t      * our_manifold         = NULL; 
static CMap           * Map                  = NULL; 
static CMenu          * Menu_InventaireArmes = NULL; 
static CMiniMenu      * MiniMenu             = NULL; 
static CBonhomme      * Hero                 = NULL; 
static CMusique       * Musique              = NULL; 
static CObjNonAnime   * Vaisseau             = NULL; 
static CMenuEntreeNom * MenuEntreeNom        = NULL; 
//static CMoteurTeleportation MoteurTeleportation;
static CMoteurTeleportation MoteurTeleportation[1];
//static CCamera Camera[1] = {};
static CCamera * Camera = NULL;

static CSon * son_bouton_espace = NULL; 
static CSon * son_bouton_saut   = NULL; 

static CPageTitre * PageTitre = NULL; 
static CAffichageMainPierre * AffichageMainPierre = NULL; 

bool show_choc_cube_huh = false; 
static bool disable_choc_huh = false; 

static int fullscreen_mode = 0; 

static bool MoteurPhysiqueActif = true; 

//static 
CText * Text = NULL; 
static CMessageTexte * MessageTexte = NULL; 

static game_events_env_t * game_events_env = NULL; 



/***************
 ÉTAT DU JEU
 Un jeu vidéo c'est un grand automate...
**************************************************************************/

static bool ModeMenuSysteme = false;
static TModeJeu ModeJeu = mjTITRE;


static void Inventaire__Gestion(void);


int Game_Loop(const int animate_but_do_not_aliven_huh, api_contexte_t * api_contexte) { 
  const int current_mj = ModeJeu; 
  
  if (animate_but_do_not_aliven_huh) { 
    
    // RL: TODO XXX FIXME: We should be able to differentiate between 'animate' & 'aliven'. 
    const int next_ModeJeu_Life = (Game_Life(animate_but_do_not_aliven_huh), ModeJeu); 
    
    Game_Blit(); 
    
  } 
  else { 
    const int next_ModeJeu_events = Game_ProcessEvents(ModeJeu, api_contexte); 
    if (next_ModeJeu_events != (int) ModeJeu) { 
      return next_ModeJeu_events; 
    }; 
    
    const int next_ModeJeu_inputs = Game_ProcessInputs(ModeJeu); 
    
    const int next_ModeJeu_Life = (Game_Life(animate_but_do_not_aliven_huh), ModeJeu); 
    
    Game_Blit(); 
    
    if (current_mj != next_ModeJeu_inputs) { 
      ModeJeu = next_ModeJeu_inputs; 
    } 
    else { 
      ModeJeu = next_ModeJeu_Life; 
    }; 
  }; 
  
  return ModeJeu; 
}; 





int Game_Init(api_contexte_t * api_contexte) { 
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " >>> " "\n", __func__); 

  //{ dprintf(fileno(stdout), "STDOUT BUFFER: %p - %s - %d \n", stdout -> _bf._base, __FILE__, __LINE__); }; 

  {
    api_contexte -> ModeJeu              = &ModeJeu;  
    //api_contexte -> SCRIPT_SystemeRendMainAuScript = &useless_bool_data;  
    api_contexte -> Map                  = &Map;  
    api_contexte -> Musique              = &Musique;  
    api_contexte -> Menu_InventaireArmes = &Menu_InventaireArmes;  
    api_contexte -> Hero                 = &Hero;  
    //api_contexte -> Temps = NULL;  
    //api_contexte -> marche_compression = NULL;  
    //api_contexte -> TypeInstructionCourante = NULL;  
    api_contexte -> MiniMenu            = &MiniMenu;  
    //api_contexte -> nbpasses = 0;  
    //api_contexte -> b = NULL;  
    api_contexte -> our_manifold_ref    = &our_manifold;  
    //api_contexte -> Camera_ref          = (CCamera**)&Camera;  
    api_contexte -> Camera_ref          = &Camera;  
    api_contexte -> MoteurTeleportation = MoteurTeleportation;  
    api_contexte -> MenuEntreeNom_ref   = &MenuEntreeNom;  
    api_contexte -> EnVaisseau_ref      = &EnVaisseau; 
    api_contexte -> Text_ref            = &Text; 
    api_contexte -> MessageTexte_ref    = &MessageTexte; 
  }; 
  
  //{ dprintf(fileno(stdout), "STDOUT BUFFER: %p - %s - %d \n", stdout -> _bf._base, __FILE__, __LINE__); }; 

  game_events_env = game_events_env__make(); 
  game_events__handlers__push0(game_events_env, /*evt_type*/GAME_EVENTS__MAP__HERO_NO_MORE_PV, /*handler_type*/GAME_HANDLERS__STANDARD__HEROS_MORT); 
  
#if 1 
  //our_manifold = riemann__make_rectangle(/*nb_maps_on_width*/4, /*nb_maps_on_height*/4, /*rectangle_width*/2400, /*rectangle_height*/2400); 
  //our_manifold = riemann__make_rectangle(/*nb_maps_on_width*/8, /*nb_maps_on_height*/1, /*rectangle_width*/4800, /*rectangle_height*/150); 
  //our_manifold = riemann__make_rectangle(/*nb_maps_on_width*/8, /*nb_maps_on_height*/2, /*rectangle_width*/4800, /*rectangle_height*/600); 
  //our_manifold = riemann__make_torus(/*nb_maps_on_width*/4, /*nb_maps_on_height*/2, /*primary_circle_radius*/900, /*secondary_circle_radius*/300); 
  our_manifold = riemann__make_torus(/*nb_maps_on_width*/3, /*nb_maps_on_height*/2, /*primary_circle_radius*/900, /*secondary_circle_radius*/600); 
#else 
  if (!EnVaisseau) { 
    our_manifold = riemann__make_torus(/*nb_maps_on_width*/4, /*nb_maps_on_height*/2, /*primary_circle_radius*/900, /*secondary_circle_radius*/300); 
  } 
  else { 
    our_manifold = riemann__make_torus(/*nb_maps_on_width*/63, /*nb_maps_on_height*/31, /*primary_circle_radius*/384, /*secondary_circle_radius*/384.0 / 4.0); 
  }; 
#endif 
  
  our_manifold -> manifold_z_scale_factor__set(our_manifold, /*new_manifold_z_scale_factor*/1.125f); 
  //our_manifold -> temps__bloque(our_manifold); 
  //our_manifold -> temps__set(our_manifold, 0.25f); // RL: 'UTC time = 0.5f' = mid-day 
  our_manifold -> temps__set(our_manifold, 0.5f); // RL: 'UTC time = 0.5f' = mid-day 
  our_manifold -> temps__debloque(our_manifold); 
  
  //{ dprintf(fileno(stdout), "STDOUT BUFFER: %p - %s - %d \n", stdout -> _bf._base, __FILE__, __LINE__); }; 

  init_actions(); 
  
  EvenementsModule -> Init(); 
  
  Text = CText_make(); 
  MessageTexte = CMessageTexte_make(); 
  PageTitre = CPageTitre_make(); 
  MenuEntreeNom = CMenuEntreeNom_make(); 
  
  //fprintf(stderr, "Init: ModeJeu = %d\n", ModeJeu);
  
  //{ dprintf(fileno(stdout), "STDOUT BUFFER: %p - %s - %d \n", stdout -> _bf._base, __FILE__, __LINE__); }; 

  Musique = CMusique_make("intro.mid");
  Musique -> Jouer(Musique);
  //son_bouton_espace = CSon_make("./frappe.wav");
  son_bouton_espace = CSon_make("epee.wav");
  //son_bouton_saut = CSon_make("./frappe.wav");
  son_bouton_saut = CSon_make("epee.wav");
  //son_bouton_saut = new CSon("./plaisir.wav");
  
  //fprintf(stderr, "Init: ModeJeu = %d\n", ModeJeu);
  
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  
  AffichageCoeur = CAffichageCoeur_make();
  
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  
  AffichageMainPierre = CAffichageMainPierre_make();  
  
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  
  //fprintf(stderr, "Init4: ModeJeu = %d\n", ModeJeu);
  
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 

  //CMoteurTeleportation__make_content(&MoteurTeleportation); 
  CMoteurTeleportation__make_content(MoteurTeleportation); 
  
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 

  //{ dprintf(fileno(stdout), "STDOUT BUFFER: %p - %s - %d \n", stdout -> _bf._base, __FILE__, __LINE__); }; 

  Vaisseau = CObjNonAnime__make("vaisseau.nonanime");
  
  //{ dprintf(fileno(stdout), "STDOUT BUFFER: %p - %s - %d \n", stdout -> _bf._base, __FILE__, __LINE__); }; 

  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  
  // Inventory 
  printf("Création de l'inventaire\n");
  Menu_InventaireArmes = CMenu_make();
  //Menu_InventaireArmes = new CMiniMenu(100,300,200);
  Menu_InventaireArmes -> parent.NomSousMenu[0] = strcopy("Armes");
  Menu_InventaireArmes -> parent.NomSousMenu[1] = strcopy("Objets");
  Menu_InventaireArmes -> parent.NomSousMenu[2] = strcopy("Magies");
  SCRIPT_RecevoirUneArme("menu/epee"); 
  SCRIPT_RecevoirUneArme("menu/arc"); 
  
  // Hero 
  printf("Création du héros\n"); 
  Hero = CBonhomme__make("./heros.anime"); 
  printf("Héros créé. Son pointeur est %p\n", Hero); 
  //Hero -> SetPVMax(1/*3*7*/); 
  //Hero -> parent1.SetPVMax(&Hero -> parent1, 4*7, /*set_pv_as_well_huh*/true); 
  Hero -> parent1.SetPVMax(&Hero -> parent1, 3*7, /*set_pv_as_well_huh*/true); 
  // RL: TODO XXX FIXME: 'AffichageCoeur' should be updated about that. 
  Hero -> force_marche = 16.0f; 

  
  // Camera 
  //CCamera__make_aux(Camera); 
  Camera = CCamera__make(); 
  Camera -> InitCamera(Camera); 
  Camera -> SolidariserAuHeros(Camera); 
  
  Map = NULL;   
#if 0 
  if (Map == NULL) {
    printf("ERREUR: Le script de début de jeu ne charge pas de carte. Par défaut, on charge 'village.carte'.\n");
    Map = new CMap("./village.carte", false);
    Hero -> SetPosition(10.0f, 10.0f, mpABSOLU, Map);
  }
#endif  
  
  //ModeJeu = mjSCRIPT; 
  ModeJeu = mjTITRE; 
  

  
  
  message("%s: " "END" "\n", __func__); 
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " <<< " "\n", __func__);   
  return 0; 
}; 








// ***************************** EVENTS ***************************** 

int Game_ProcessEvents(const int current_mj, api_contexte_t * api_contexte) {
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " >>> current_mj = %d " "\n", __func__, current_mj); 
  int ModeJeu = current_mj; 
  
  const int retval = game_events__process(game_events_env, api_contexte); 
  
  
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " <<< " "\n", __func__); 
  return ModeJeu; 
}; 

void Game_EventsHandlers__reset(void) { 
  //game_events__handlers__reset(game_events_env); 
  for (int i = 0; i < GAME_EVENTS__COUNT; i++) { 
    game_events__handlers__empty(game_events_env, /*evt_type*/i); 
  }; 
  game_events__handlers__push0(game_events_env, /*evt_type*/GAME_EVENTS__MAP__HERO_NO_MORE_PV, /*handler_type*/GAME_HANDLERS__STANDARD__HEROS_MORT); 
}; 

int Game_Events_Raise(const int evt_type) { 
  //dprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " evt_type = %d " "\n", __func__, evt_type); 
  const int retval = game_events__stack__push(game_events_env, evt_type); 
  return retval; 
}; 

int Game_EventsHandlers__push(const int evt_type, const int handler_type, const int int_argc, const int int_argv[int_argc], const int ptr_argc, void * ptr_argv[ptr_argc], const int cptr_argc, const void * cptr_argv[ptr_argc]) { 
  const int retval = game_events__handlers__push(game_events_env, evt_type, handler_type, int_argc, int_argv, ptr_argc, ptr_argv, cptr_argc, cptr_argv); 
  return retval; 
}; 

int Game_EventsHandlers__push0(const int evt_type, const int handler_type) { 
  const int retval = game_events__handlers__push0(game_events_env, evt_type, handler_type); 
  return retval; 
}; 

int Game_EventsHandlers__push_script(const int evt_type, const char * script_file, const char * script_name) {
  const int retval = game_events__handlers__push_script(game_events_env, evt_type, script_file, script_name); 
  return retval; 
}; 


// ***************************** INPUTS ***************************** 

int Game_ProcessInputs_EnVaisseau(const int current_mj) { 
#define pas_angle_vaisseau 0.1f 
  CPhysicalObj * Hero_o = &Hero -> parent1; 
  int Mode_Jeu = current_mj; 

#if 0 
  if (KEY_LEFT)
    AngleXY += pas_angle_vaisseau;
  
  if (KEY_RIGHT)
    AngleXY -= pas_angle_vaisseau;
  
#define force_vaisseau 10.0f
#define force_vaisseau_altitude 80.0f
  if (KEY_UP) 
    Hero_o -> AddForce_vXYZ(Hero_o, force_vaisseau*cosf(AngleXY), force_vaisseau*sinf(AngleXY), 0.0f);  
  
  if (KEY_DOWN)
    Hero_o -> AddForce_vXYZ(Hero_o, -force_vaisseau*cosf(AngleXY), -force_vaisseau*sinf(AngleXY), 0.0f);  
  
  if (KEY_VAISSEAU_UP)
    Hero_o -> AddForce_vXYZ(Hero_o, 0.0f, 0.0f, force_vaisseau_altitude);
  
  if (KEY_VAISSEAU_DOWN)
    Hero_o -> AddForce_vXYZ(Hero_o, 0.0f, 0.0f, -force_vaisseau_altitude); 
  
#endif 
  return Mode_Jeu; 
}; 


static int Game_ProcessInputs_Oeil(const int current_mj) { 
  CPhysicalObj * Hero_o = &Hero -> parent1; 
  int ModeJeu = current_mj; 
  
  
  do { 

    if (KEY_VUE_ANGLE_PLUS) { 
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "KEY_CAMERA_ANGLE_XY_PLUS: Camera -> angleXY = %f"  "\n", __func__, Camera -> angleXY); 
      Camera -> angleXY += PI/32.0f; 
      break; 
    }; 
      
    if (KEY_VUE_ANGLE_MOINS) {  
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "KEY_CAMERA_ANGLE_XY_PLUS: Camera -> angleXY = %f"  "\n", __func__, Camera -> angleXY); 
      Camera -> angleXY -= PI/32.0f; 
      break; 
    }; 
      
    if (KEY_CAMERA_DIST_PLUS) { 
      Camera -> lattice__dist += 0.1f; 
      break; 
    }; 
      
    if (KEY_CAMERA_DIST_MOINS) { 
      Camera -> lattice__dist -= 0.1f; 
      break; 
    }; 

    if (KEY_CAMERA_ANGLE_Z_PLUS) { 
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "KEY_CAMERA_ANGLE_Z_PLUS: Camera -> angleZ = %f"  "\n", __func__, Camera -> angleZ); 
      Camera -> angleZ -= PI/32.0f; 
      break; 
    }; 
      
    if (KEY_CAMERA_ANGLE_Z_MOINS) { 
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "KEY_CAMERA_ANGLE_Z_MOINS: Camera -> angleZ = %f"  "\n", __func__, Camera -> angleZ); 
      Camera -> angleZ += PI/32.0f; 
      break; 
    }; 
      

      
    if (KEY_UP) { 
      //Hero -> Avancer(Hero, ConvertirDirectionAvecVue(DOS, Camera), our_manifold); 
      Camera -> lattice__target_position.y += 0.5f ; 
      break; 
    }; 
      
    if (KEY_DOWN) { 
      //Hero -> Avancer(Hero, ConvertirDirectionAvecVue(FACE, Camera), our_manifold); 
      Camera -> lattice__target_position.y -= 0.5f ; 
      break; 
    }; 
      
    if (KEY_LEFT) { 
      //Hero -> Avancer(Hero, ConvertirDirectionAvecVue(PROFIL_VERS_G, Camera), our_manifold); 
      Camera -> lattice__target_position.x -= 0.5f ; 
      break; 
    }; 
      
    if (KEY_RIGHT) { 
      //Hero -> Avancer(Hero, ConvertirDirectionAvecVue(PROFIL_VERS_D, Camera), our_manifold); 
      Camera -> lattice__target_position.x += 0.5f ; 
      break; 
    }; 
      
    if (KEY_JUMP) { 
#if 0 
      printf("On saute. (pagedown appuyé…)\n");

      if (Hero_o -> Immerge_huh) {
	if (Hero_o -> GetVitesse(Hero_o).z < 0) {
	  Hero_o -> AddForce_vXYZ(Hero_o, 0.0f, 0.0f, 50.1f);
	  son_bouton_saut -> Jouer(son_bouton_saut);
	} 
	else { 
	  Hero_o -> AddForce_vXYZ(Hero_o, 0.0f, 0.0f, 1.5f);
	}; 
      } // if (Hero -> Immerge) 
	
      else if (Hero_o -> AuSol_huh) { 
	son_bouton_saut -> Jouer(son_bouton_saut); 
	Hero_o -> AddForce_vXYZ(Hero_o,0.0f, 0.0f, 180.0f); 
      } // if (Hero -> AuSol) 
#endif 	
      break; 
    }; // if (KEY_JUMP) 
      
    if (KEY_MENU_JEU) { 
#if 0 
      //ModeJeu = mjCARTE; 
      ModeJeu = mjINVENTAIRE; 
#endif 
      break; 
    }; 

    if (KEY_FRAPPER) { 
#if 0 
      /*TPoint2D d = Map -> Differentiel(Hero -> GetPosition()); 
        printf("Ahhh je glisse dans la direction (%f, %f)\n", -d.x, -d.y);
        Hero -> AddForce(-d.x/3.0f, -d.y/3.0f, 0.0f);*/
      son_bouton_espace -> Jouer(son_bouton_espace);
      Hero -> Frapper(Hero);
      
      //*création d'un projectile*/
      /*CPhysicalObj* projectile = new CBonhomme("sang.anime");
	
	projectile -> SetPosition(Hero -> GetPosition() + Point3D(0.0f, 0.0f, 20.0f));
	projectile -> AddForce(50*DirectionToVecteur(Hero -> GetDirection() ) + Point3D(0.0f, 0.0f, 300.0f));
	projectile -> SetObjetEphemere(300);
	projectile -> Hostile = false;
      
	Map -> AjouterObjet(projectile);*/
#endif 
      break; 
    }; 

  } while (false); 

  return ModeJeu; 
}; 


static int Game_ProcessInputs_HerosSurUneMap(const int current_mj) { 
  CPhysicalObj * Hero_o = &Hero -> parent1; 
  int ModeJeu = current_mj; 

  do { 
    if (KEY_MENU_JEU) { 
      // RL: TODO XXX FIXME: There should be a MJ stack, to come back to the prevailing mjMODE.  
      //ModeJeu = mjCARTE; 
      ModeJeu = mjINVENTAIRE; 
      break; 
    }; 

    if (KeyBoard['y']           ) { show_choc_cube_huh = !show_choc_cube_huh; }; 
    if (KeyBoard['t']           ) { disable_choc_huh   = !disable_choc_huh; };   

#if 0 
    // RL: Fullscreen mode absolutely does not work. 
    //if (KeyBoard['f']           ) { fullscreen_mode = fullscreen_mode == 0 ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0; if (0 != SDL_SetWindowFullScreen(SDL_Screen, fullscreen_mode)) { fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " SDL_GetError = %s"   "\n", __func__,     SDL_GetError()); };   
    //if (KeyBoard['f']           ) { fullscreen_mode = fullscreen_mode == 0 ? 2 : 0; if (0 != SDL_SetWindowFullScreen(SDL_Screen, fullscreen_mode)) { fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " SDL_GetError = %s"   "\n", __func__,     SDL_GetError()); };   
    // RL: SDL_WM_ToggleFullScreen is hell. 
    //if (KeyBoard['f']           ) { fullscreen_mode = fullscreen_mode == 0 ? 2 : 0; if (0 != SDL_WM_ToggleFullScreen(SDL_Screen)) { fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " SDL_GetError = %s"   "\n", __func__,     SDL_GetError()); };  }; 
    if (KeyBoard['f']           ) { 
      fullscreen_mode = fullscreen_mode == 0 ? SDL_FULLSCREEN | SDL_NOFRAME : 0; 
        if (0 == SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BITSPERPIXEL, SDL_OPENGL | SCREEN_MODE | SDL_DOUBLEBUF | SDL_HWSURFACE | fullscreen_mode/*| SDL_NOFRAME*/)) { 
	  messerr("SDL_SetVideoMode failed: %s" "\n", SDL_GetError()); 
	  return false; 
	}; 
    }; 
#endif 


    if (KEY_VUE_ANGLE_PLUS      ) { Camera -> angleXY       += PI/32.0f; }; 
    if (KEY_VUE_ANGLE_MOINS     ) { Camera -> angleXY       -= PI/32.0f; }; 
    if (KEY_CAMERA_DIST_PLUS    ) { Camera -> lattice__dist +=     0.1f; }; 
    if (KEY_CAMERA_DIST_MOINS   ) { Camera -> lattice__dist -=     0.1f; }; 
    if (KEY_CAMERA_ANGLE_Z_PLUS ) { Camera -> angleZ        -= PI/32.0f; }; 
    if (KEY_CAMERA_ANGLE_Z_MOINS) { Camera -> angleZ        += PI/32.0f; }; 
    
    const bool slow_walk_huh = KeyBoard[SDLK_RSHIFT] || KeyBoard[SDLK_LSHIFT]; 
    
    if (KEY_UP   ) { Hero -> Avancer(Hero, ConvertirDirectionAvecVue(DOS          , Camera), slow_walk_huh); }; 
    if (KEY_DOWN ) { Hero -> Avancer(Hero, ConvertirDirectionAvecVue(FACE         , Camera), slow_walk_huh); }; 
    if (KEY_LEFT ) { Hero -> Avancer(Hero, ConvertirDirectionAvecVue(PROFIL_VERS_G, Camera), slow_walk_huh); }; 
    if (KEY_RIGHT) { Hero -> Avancer(Hero, ConvertirDirectionAvecVue(PROFIL_VERS_D, Camera), slow_walk_huh); }; 
    
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " HERE? = "  "\n", __func__ ); 
    
    if (KEY_JUMP) { 
      son_bouton_saut -> Jouer(son_bouton_saut); 
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " AuSol? = %s"  "\n", __func__, Hero_o -> AuSol_huh ? "TRUE" : "FALSE" ); 
      if (Hero_o -> AuSol_huh) { 
	//Hero_o -> AddForce_vXYZ(Hero_o,0.0f, 0.0f, 180.0f); 
	//Hero_o -> Acceleration_add_vXYZ(Hero_o, 0.0f, 0.0f, 900.0f); 
	Hero_o -> Force_massique__add_vXYZ(Hero_o, 0.0f, 0.0f, 125.0f); 
      } // if (Hero -> AuSol) 
      else if (Hero_o -> Immerge_huh) { 
	if (Hero_o -> GetVitesse(Hero_o).z < 0) { 
	  //Hero_o -> AddForce_vXYZ(Hero_o, 0.0f, 0.0f, 50.1f); 
	  Hero_o -> Acceleration_add_vXYZ(Hero_o, 0.0f, 0.0f, 50.1f); 
	} 
	else { 
	  //Hero_o -> AddForce_vXYZ(Hero_o, 0.0f, 0.0f, 1.5f); 
	  Hero_o -> Acceleration_add_vXYZ(Hero_o, 0.0f, 0.0f, 1.5f); 
	}; 
      }; // if (Hero -> Immerge) 
    }; // if (KEY_JUMP) 
      
    if (KEY_FRAPPER) { 
      son_bouton_espace -> Jouer(son_bouton_espace); 
      Hero -> Frapper(Hero); 
    }; 
    
  } while (false); 
  
  return ModeJeu; 
}; 

int Game_ProcessInputs(const int current_mj) {
  //fprintf(stderr, "ModeJeu = %d\n", ModeJeu);
  int ModeJeu = current_mj; 
  CPhysicalObj * Hero_o = &Hero -> parent1; 

  do { 
    
    if (ModeMenuSysteme) { 
      const int done_huh = MiniMenu -> Input(MiniMenu); 
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "ModeMenuSysteme = %s - done_huh = %s" "\n", __func__, bool_string(ModeMenuSysteme), bool_string(done_huh)); 
      if (!done_huh) { 
	break; 
      }; 
      if (MiniMenu -> parent.Canceled) { 
	ModeMenuSysteme = false; 
	break; 
      }; 
      const int choice_made = MiniMenu -> parent.itheta; 
      if (choice_made == 1) { 
	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "ModeMenuSysteme = %s - choice_made = %s" "\n", __func__, bool_string(ModeMenuSysteme), int_string__stack(choice_made)); 
	Kernel_DemanderAQuitterLeJeu(); 
	ModeJeu = mjIDLE; 
	//TypeInstructionCourante = ticInstructionScript; 
	ModeMenuSysteme = false; 
	break; 
      } 
      else { 
	ModeMenuSysteme = false; 
	break; 
      }; 
      break; 
    }; 
    
    if (ModeJeu == mjTITRE) {
      const int next = PageTitre -> Input(PageTitre); 
      if (PageTitre_UserToldMe_NothingYet == next) { 
	break; 
      } 
      else if (10 == next) { 
	ModeJeu = mjIDLE; 
#if 1 
	// RL: TODO XXX FIXME 
	fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "TO_BE_IMPLEMENTED"  "\n", __func__); 
#else 
	TypeInstructionCourante = ticInstructionScript; 
#endif 
	break; 
      } 
      else if (PageTitre_UserToldMe_Bye == next) { 
	Kernel_DemanderAQuitterLeJeu(); 
	ModeJeu = mjIDLE; 
	//TypeInstructionCourante = Script_Automaton_Idle; 
	break; 
      } 
      else if (PageTitre_UserToldMe_NewGame == next) { 
	//ModeJeu = mjIDLE; //mjSCRIPT; 
	ModeJeu = mjCARTE; 
#if 1 
	// RL: TODO XXX FIXME 
	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "TO_BE_IMPLEMENTED"  "\n", __func__); 
	Kernel_Script_Start(/*script_file_name*/"script.pml", /*script_function_name*/"debutvrai"); 
#else 
	TypeInstructionCourante = ticInstructionScript; 
#endif 
	break; 
      } 
      else if (PageTitre_UserToldMe_LoadGame == next) { 
	ModeJeu = mjIDLE; 
#if 1 
	// RL: TODO XXX FIXME 
	fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "TO_BE_IMPLEMENTED"  "\n", __func__); 
#else 
	TypeInstructionCourante = Script_Automaton_Idle; 
#endif 
	break; 
      } 
      else if (PageTitre_UserToldMe_QuickGame == next) { 
#if 0 
	ModeJeu = mjOEIL; 
	Camera -> DeSolidariser(Camera); 
	Camera -> lattice__target_position.x = 1.0f; 
	Camera -> lattice__target_position.y = 1.0f; 
#else 
	ModeJeu = mjCARTE; 
#endif 
	//TypeInstructionCourante = Script_Automaton_Idle; 
	if (Map != NULL) { Map -> delete(Map); }; 
#if 0 
	Map = CMap__make("niveau1_0.carte", /*map_i*/0, /*map_j*/0, our_manifold, /*EnVaisseau*/false); 
	Hero -> parent1.SetPosition_vXY(&Hero -> parent1, 6.0f, 6.0f, mpABSOLU, Map); 
#elif 0 
	Map = CMap__make("niveau1_3.carte", /*map_i*/0, /*map_j*/0, our_manifold, /*EnVaisseau*/false); 
	Hero -> parent1.SetPosition_vXY(&Hero -> parent1, 22.0f, 16.0f, mpABSOLU, Map); 
#elif 1 
	Map = CMap__make("village.carte", /*map_i*/0, /*map_j*/0, our_manifold, /*EnVaisseau*/false); 
	Hero -> parent1.SetPosition_vXY(&Hero -> parent1, 10.0f, 10.0f, mpABSOLU, Map); 
#elif 1
	Map = CMap__make("foret.carte", /*map_i*/0, /*map_j*/0, our_manifold, /*EnVaisseau*/false); 
	Hero -> parent1.SetPosition_vXY(&Hero -> parent1, 3.0f, 30.0f, mpABSOLU, Map); 
        Hero -> parent1.SetPV(&Hero -> parent1, 3);
#elif 1
	Map = CMap__make("cimetiere.carte", /*map_i*/0, /*map_j*/0, our_manifold, /*EnVaisseau*/false); 
	Hero -> parent1.SetPosition_vXY(&Hero -> parent1, 8.5f, 1.5f, mpABSOLU, Map); 
#elif 1
	Map = CMap__make("chezmoi.carte", /*map_i*/0, /*map_j*/0, our_manifold, /*EnVaisseau*/false); 
	Hero -> parent1.SetPosition_vXY(&Hero -> parent1, 8.0f, 1.5f, mpABSOLU, Map); 
#else  
	Map = CMap__make("village.carte", /*map_i*/0, /*map_j*/0, our_manifold, /*EnVaisseau*/false); 
	Hero -> parent1.SetPosition_vXY(&Hero -> parent1, 10.0f, 10.0f, mpABSOLU, Map); 
#endif 	
	Camera -> lattice__target_position.z = Map -> GETZ0_vP3D(Map, Camera -> lattice__target_position); 
	//TypeInstructionCourante = Script_Automaton_Idle; 
	break; 
      } 
      else { 
	assert(false); 
	break; 
      } 
      break; 
    }; 

    
    if (ModeJeu == mjINVENTAIRE) {
      //if (Menu_InventaireArmes -> InputAndRender(Menu_InventaireArmes)) { 
      const int key_was_hit_huh = Menu_InventaireArmes -> Input(Menu_InventaireArmes); 
      if (!key_was_hit_huh) break; 
      if (Menu_InventaireArmes -> parent.Canceled) { 
	ModeJeu = mjCARTE; 
	break; 
      }; 
      Inventaire__Gestion(); 
      ModeJeu = mjCARTE; 
      break; 
    }; 
    
    
    if (KEY_MENU_SYSTEME) { 
      if (MiniMenu != NULL) { 
	CMiniMenu_delete(MiniMenu); 
	MiniMenu = NULL; 
      }; 
      //MiniMenu = CMiniMenu_make(100, 300,1000); 
      MiniMenu = CMiniMenu_make(/*x*/100, /*y*/300,/*w*/1000); 
      MiniMenu -> parent.Add(&MiniMenu -> parent, /*ssMenu*/0, /*nom*/"Continuer", /*nom_texture*/NULL); 
      MiniMenu -> parent.Add(&MiniMenu -> parent, /*ssMenu*/0, "Quitter", /*nom_texture*/NULL); 
      
      ModeMenuSysteme = true; // RL: To be improved. 
      break; 
    }; 
    
    
    if (ModeJeu == mjOEIL) { 
      ModeJeu = Game_ProcessInputs_Oeil(current_mj); 
      break; 
    }; 

    if (ModeJeu == mjCARTE) { 
      if (Map == NULL) { ModeJeu = mjIDLE; break; }; 
      if (EnVaisseau) { ModeJeu = mjAEROTHEIERE; break; }; 
      
      
      if (KEY_ACTIVEDESACTIVEMOTEURPHYSIQUE) { 
	MoteurPhysiqueActif = !MoteurPhysiqueActif; 
      }; 
      
      ModeJeu = Game_ProcessInputs_HerosSurUneMap(current_mj); 
      
      const CPhysicalObj * nearest_o = CMap__GetNearestInteractingObject(Map, Hero_o); 
      if (nearest_o != NULL) { 
	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " nearest_o -> filename = %s "  "\n", __func__, nearest_o -> filename); 
	nearest_o -> actions -> ActionMenu_Input(nearest_o -> actions); 
      }; 
      
      //ModeJeu = Game_Life_TeleportationStartHuh(ModeJeu); 
      
      break; 
    }; 
    
    
    if (ModeJeu == mjAEROTHEIERE) { 
      ModeJeu = Game_ProcessInputs_EnVaisseau(current_mj); 
      break; 
    }; 


    if (ModeJeu == mjIDLE) { 
      break; 
    }; 
    
    
    if (ModeJeu == mjTELEPORTATION) { 
      // RL: Nothing. 
      break; 
    }; 
    
    
    if (ModeJeu == mjHEROS_MORT) { 
      // RL: TODO XXX FIXME 
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " --- TODO XXX FIXME - ModeJeu = %s"  "\n", __func__, int_string__stack(ModeJeu)); 
      //CMessageTexte * MessageTexte = *(api_contexte.MessageTexte_ref); 
      const int text_was_read_huh = MessageTexte -> Input(MessageTexte); 
      if (text_was_read_huh) { 
	CPageTitre_delete(PageTitre); 
	PageTitre = CPageTitre_make(); 
	CMusique_delete(Musique); 
	Musique = CMusique_make("intro.mid");
	Musique -> Jouer(Musique);
	ModeJeu = mjTITRE; 
      }; 
      break; 
    }; 
    
    
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "ModeJeu = %s"  "\n", __func__, int_string__stack(ModeJeu)); 
    assert(false); 



  } while (false);   

#if 0 
  if (current_mj == mjINVENTAIRE) { 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "ModeJeu = %s"  "\n", __func__, int_string__stack(ModeJeu)); 
  }; 

  if (ModeJeu == mjINVENTAIRE) { 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "current_mj = %s"  "\n", __func__, int_string__stack(current_mj)); 
  }; 
#endif 

  return ModeJeu; 
}; 



void Inventaire__Gestion(void) { 
#if 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Menu_InventaireArmes -> parent.iphi   = %d"   "\n", __func__, Menu_InventaireArmes -> parent.iphi); 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Menu_InventaireArmes -> parent.itheta = %d"   "\n", __func__, Menu_InventaireArmes -> parent.itheta); 
#endif 

  /* le menu a été affiché et le joueur a sélectionné un élément
   * (ou à annuler ce qui revient à avoir (Menu -> iphi == -1)
   *
   * là gestion_menu() s'occupe de réaliser l'action correspondante au menu
   */
  
  // RL: 'iphi' is the column. 
  // RL: 'itheta' is the item in the column. 
  
  //if (!Menu_InventaireArmes -> parent.Canceled) {
  {
    switch (Menu_InventaireArmes -> parent.iphi) { 
    case ANNEAU_MENU_ARME: { 
      CPantin * Epee = CPantin__make(); 
      
      if (Menu_InventaireArmes -> parent.itheta == 0) 
        Epee -> AjouterMembre(Epee, "./heros/epee.png", -0.0f, 0.0f, -22.0f, 9.0f , 32.0f, 10.0f);
      else
        Epee -> AjouterMembre(Epee, "./heros/arc.png" , -0.0f, 0.0f, -22.0f, 7.0f , 37.0f, 10.0f);
      
      Hero -> pantin.SetPantinFils(&Hero -> pantin, MEMBRE_AVEC_ARME , Epee); 
    }; break; 
      
    case ANNEAU_MENU_OBJET:
      break;

    default: assert(false);
    }; 
  }; 
}; 







// ***************************** LIFE ***************************** 


void Game_Life_Aerotheiere(CMap * Map, CBonhomme * Hero, CObjNonAnime * Vaisseau) { 
  //fprintf(stderr, "Map = %p\n", Map);
  if (Map == NULL) { return; }; 
  if (!EnVaisseau) { return; }; 

#if 0 
  
#if 1 
  our_manifold -> life(our_manifold); 
#else 
  // on gère le temps 
  Temps += marche_compression; 
  Map -> Sol -> SetTemps(Map -> Sol, Temps); 
  Map -> Sol -> SetTemps(Map -> Sol, Temps); 
#endif 
  
  
  Hero -> parent1.CoeffFrottementFluide  = 1.0f; 
  Hero -> parent1.CoeffFrottementFluideZ = 0.5f; 
  Hero -> parent1.CalcNewPosition(&Hero -> parent1); 
  Hero -> parent1.ValiderPosition(&Hero -> parent1, MoteurPhysiqueActif); 
  Hero -> parent1.InitForce(&Hero -> parent1); 
  const float zcarte = Map -> Sol -> GETZ(Map -> Sol, Hero -> parent1.GetPosition(&Hero -> parent1).x, Hero -> parent1.GetPosition(&Hero -> parent1).y); 
  float z = Hero -> parent1.GetPosition(&Hero -> parent1).z; 
  
#define ZMAXVAISSEAU 200.0f 
  if (z < zcarte) z = zcarte; 
  
  if (z > ZMAXVAISSEAU) z = ZMAXVAISSEAU; 
  
  Hero -> parent1.SetPosition_vP3D(&Hero -> parent1, TPoint3D_make_struct(Hero -> parent1.GetPosition(&Hero -> parent1).x, Hero -> parent1.GetPosition(&Hero -> parent1).y, z ) ); 
  Camera -> angleXY = AngleXY; 
  
  TPoint3D p; 
  
  /* pour l'instant c un peu de la magouille: 
   * j'utilise l'objet Hero en interface (histoire de pas tout rechanger) 
   * et après je transfère la position de Hero sur le vaisseau 
   */
  p = Hero -> parent1.GetPosition(&Hero -> parent1); 
#if 0 
  Map  -> parent.PositionModulo(Map -> Sol, &p.x, &p.y); 
  Hero -> parent1.SetPosition_vP3D(&Hero -> parent1, p); 
#endif 
  p.z -= 50; 
  Vaisseau -> parent.SetPosition_vP3D(&Vaisseau -> parent, p); 
  Vaisseau -> SetAngleZ(Vaisseau, AngleXY + 90.0f); 
  //Vaisseau -> SetAngleZ(AngleXY); 
  
  //Map -> LookAt(i, j, Hero -> GetPosition().z, AngleXY, 0.0f); 
  Map -> Life(Map, 0, 0, 1000, 1000, EnVaisseau); 
  //Vaisseau -> Life(Vaisseau, Map -> Sol); 



#endif 
}; 

void Game_Life_Map(CMap * Map, CBonhomme * Hero) { 
  //fprintf(stderr, "Map = %p\n", Map);
  if (Map == NULL) { return; }; 
  if (EnVaisseau) { return; }; 
  
#if 1 
  our_manifold -> Life(our_manifold); 
#else 
  // on gère le temps 
  // RL: It should be done through 'RiemannManifold -> Life()'. 
  Temps += marche_compression; 
  Map -> Sol -> SetTemps(Map -> Sol, Temps); 
  Map -> Sol -> SetTemps(Map -> Sol, Temps); 
#endif 
  
  
  { 
    float i; 
    float j; 
    { 
      const TPoint3D pp = Hero -> parent1.GetPosition(&Hero -> parent1); 
      i = pp.x; 
      j = pp.y; 
    }; 
    
   //Map  -> Life(Map, (int) i-nb_cases_afficheesX, (int) j-nb_cases_afficheesYdevant, (int) i+nb_cases_afficheesX, (int) j+nb_cases_afficheesYfond, EnVaisseau); 
  }; 
  
  Hero -> Life(Hero); 
  
  // *** affichage des coeurs *** 
  AffichageCoeur -> InformerNbPV(AffichageCoeur, Hero -> parent1.GetPV(&Hero -> parent1)); 
  AffichageCoeur -> Life(AffichageCoeur); 
}; 


int Game_Life_TeleportationStartHuh(const int current_mj) { 
  static bool last_time = false; 
  
  int ModeJeu = current_mj; 
  // vérifie si l'on va changer de carte… 
  const CZoneTeleportation * pzt = Map -> VaTonBouger(Map, &Hero -> parent1); 
  if (pzt) { 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " last_time = %s "  "\n", __func__, bool_string(last_time)); 
    if (last_time) { return ModeJeu; }; 
#if 0 
    if (0 > Kernel_Supervisor_Message("Vous allez changer de carte. :-)")) { 
      messerr("'Kernel_Supervisor_Message' failed." "\n"); 
    }; 
#endif 
#if 0
    const int choix = Kernel_Supervisor_Menu("Voulez-vous changer de carte? :-)", 2, ((const char *[]) { "Non", "Oui", NULL })); 
    if (choix < 0) { 
      messerr("'Kernel_Supervisor_Menu' failed: %d" "\n", choix); 
    }; 
#elif 0  
    const int choix = 0; 
    //Kernel_Script_Start("", "Hello"); 
    //Kernel_Script_Start("", "Hello"); 
    Kernel_Script_Start_arg("", "AfficherMessage", /*int_argc*/0, ((int [0]){}), /*ptr_argc*/0, ((void * [0]) {}), /*cptr_argc*/1, ((const void *[1]) { (const void*)"Bonjour!! :-)" }), Kernel_Script_Modal__ScriptIsSlave); 
#elif 0 
    const int choix = Kernel_Script_Start_arg("", "Menu", /*int_argc*/0, ((int [0]){}), /*ptr_argc*/0, ((void * [0]) {}), /*cptr_argc*/3, (const void * *)((const char *[3]) { "Bonjour!! :-)" "\n" "Souhaites-tu changer de carte?", "Non", "Oui" }), Kernel_Script_Modal__ScriptIsSlave); 
#else 
    const int choix = 2; 
#endif 
    
    //if (EnVaisseau || (Hero -> GetDirection(Hero) == pzt -> depart_direction)) { 
    if (choix == 2) { 
      if (not(MoteurTeleportation -> IsTeleportationEnCours(MoteurTeleportation))) { 
	CZoneTeleportation zt = *pzt; 
	printf("On arrive sur une zone de téléportation:\n"); 
	printf("Direction du héros %i, de la zone %i\n", Hero -> GetDirection(Hero), pzt -> depart_direction); 
	printf("   position: (%f, %f, %f)\n", zt.position.x, zt.position.y, zt.position.z); 
	ModeJeu = mjTELEPORTATION; 
	SCRIPT_ChangerDeCarte_vZT(zt); 
      }; 
    }; 
    last_time = true; 
  } 
  else { 
    last_time = false; 
  }; 
  return ModeJeu;
}; 


void Game_Life(const int animate_but_do_not_aliven_huh) {
  //fprintf(stderr, "ModeJeu = %d\n", ModeJeu);

  do { 

    if (ModeMenuSysteme) { 
      MiniMenu -> Life(MiniMenu); 
      break; 
    }; 
    
    
    if (ModeJeu == mjTITRE) {
      PageTitre -> Life(PageTitre); 
      break; 
    }; 
    
    
    if (ModeJeu == mjOEIL) { 
      Game_Life_Map(Map, Hero); 
      Camera -> CalcCamera(Camera, Hero, Map -> lattice_to_map_scale_factor__x, Map -> lattice_to_map_scale_factor__y, Map -> lattice_to_map_scale_factor__z, our_manifold); 
      break; 
    }; 


    if (ModeJeu == mjCARTE) { 
      if (Map == NULL) break; 
      
      { 
	CPhysicalObj * Hero_o = &Hero -> parent1; 
	
	if (animate_but_do_not_aliven_huh) { 
	  Map -> TraiterOrdresDeplacement(Map, Hero, MoteurPhysiqueActif); 

	  CPhysicalObj__NewtonEngine__Frottements_apply(Hero_o); 
	  CPhysicalObj__NewtonEngine__OneStepFoward__NoValidationYet(Hero_o); 
	  CPhysicalObj__BordersAndGroundAndSlope__AdjustAndCorrectNP(Hero_o, Map); 
	  CMap__Life_NewtonEngine_Objects(Map, /*EnVaisseau*/EnVaisseau); 
	  CPhysicalObj__ValiderPosition(Hero_o, Map -> GET_ZEau(Map)); 
	  CMap__Life_Objects_ValiderPosition(Map, /*EnVaisseau*/EnVaisseau); 

	  CMap__Life_GamePlay(Map, animate_but_do_not_aliven_huh, /*EnVaisseau*/EnVaisseau); 

	  Camera -> CalcCamera(Camera, Hero, Map -> lattice_to_map_scale_factor__x, Map -> lattice_to_map_scale_factor__y, Map -> lattice_to_map_scale_factor__z, our_manifold); 
	} 
	else { 
	our_manifold -> Life(our_manifold); 

	//Hero_o -> Life(Hero_o); // GamePlay stuffs 
	Hero -> Life(Hero); // GamePlay stuffs 
#if 1 
	extern CBonhomme * particule; 
	if (particule != NULL) { fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Coordonnées de la particule %p : (%f, %f, %f) "  "\n", __func__, particule, particule -> parent1.p.x, particule -> parent1.p.y, particule -> parent1.p.z); }; 
	CMap__Life_Choc_Sword(Map, Hero_o); 
	if (particule != NULL) { fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Coordonnées de la particule %p : (%f, %f, %f) "  "\n", __func__, particule, particule -> parent1.p.x, particule -> parent1.p.y, particule -> parent1.p.z); }; 
	CMap__Life_RemoveDeads(Map, /*EnVaisseau*/EnVaisseau); 
	if (particule != NULL) { fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Coordonnées de la particule %p : (%f, %f, %f) "  "\n", __func__, particule, particule -> parent1.p.x, particule -> parent1.p.y, particule -> parent1.p.z); }; 
	
	CPhysicalObj__NewtonEngine__Frottements_apply(Hero_o); 
	if (particule != NULL) { fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Coordonnées de la particule %p : (%f, %f, %f) "  "\n", __func__, particule, particule -> parent1.p.x, particule -> parent1.p.y, particule -> parent1.p.z); }; 
	CPhysicalObj__NewtonEngine__OneStepFoward__NoValidationYet(Hero_o); 
	if (particule != NULL) { fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Coordonnées de la particule %p : (%f, %f, %f) "  "\n", __func__, particule, particule -> parent1.p.x, particule -> parent1.p.y, particule -> parent1.p.z); }; 
	CPhysicalObj__BordersAndGroundAndSlope__AdjustAndCorrectNP(Hero_o, Map); 
	if (particule != NULL) { fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Coordonnées de la particule %p : (%f, %f, %f) "  "\n", __func__, particule, particule -> parent1.p.x, particule -> parent1.p.y, particule -> parent1.p.z); }; 
	
	CMap__Life_GamePlay(Map, animate_but_do_not_aliven_huh, /*EnVaisseau*/EnVaisseau); 
	if (particule != NULL) { fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Coordonnées de la particule %p : (%f, %f, %f) "  "\n", __func__, particule, particule -> parent1.p.x, particule -> parent1.p.y, particule -> parent1.p.z); }; 
	CMap__Life_Simulate_Objects(Map, /*EnVaisseau*/EnVaisseau); 
	CMap__Life_NewtonEngine_Objects(Map, /*EnVaisseau*/EnVaisseau); 
	
	
	// RL: Chocs 	
	if (!disable_choc_huh) { 
	  if (!Hero -> EstInvisible(Hero)) { 
	    const bool hero_got_a_hostile_encounter_huh = CMap__ChocEngine_HeroGotHostileEncounterHuh_one(Map, Hero_o); 
	    if (hero_got_a_hostile_encounter_huh) { 
	      Hero_o -> PerdrePV(Hero_o, 1); 
	      AffichageCoeur -> InformerNbPV(AffichageCoeur, Hero_o -> GetPV(Hero_o)); 
	      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Hero_o -> GetPV(Hero_o) = %d "  "\n", __func__, Hero_o -> GetPV(Hero_o)); 
	      Hero -> DevenirInvisible(Hero, 50); //200); 
	    }; 
	  }; 
	  CMap__ChocEngine(Map, Hero_o); 
	}; 
	
	if (particule != NULL) { fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Coordonnées de la particule %p : (%f, %f, %f) "  "\n", __func__, particule, particule -> parent1.p.x, particule -> parent1.p.y, particule -> parent1.p.z); }; 
	CPhysicalObj__ValiderPosition(Hero_o, Map -> GET_ZEau(Map)); 
	if (particule != NULL) { fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Coordonnées de la particule %p : (%f, %f, %f) "  "\n", __func__, particule, particule -> parent1.p.x, particule -> parent1.p.y, particule -> parent1.p.z); }; 
	CMap__Life_Objects_ValiderPosition(Map, /*EnVaisseau*/EnVaisseau); 
	
	
	
#if 1 
	const CPhysicalObj * nearest_o = CMap__GetNearestInteractingObject(Map, Hero_o); 
	if (nearest_o != NULL) { 
	  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " nearest_o -> filename = %s "  "\n", __func__, nearest_o -> filename); 
	  nearest_o -> actions -> ActionMenu_Life(nearest_o -> actions); 
	}; 
#endif 
#endif 
	
	Map -> TraiterOrdresDeplacement(Map, Hero, MoteurPhysiqueActif); 
	
	ModeJeu = Game_Life_TeleportationStartHuh(ModeJeu); 
	
	// *** affichage des coeurs *** 
	AffichageCoeur -> InformerNbPV(AffichageCoeur, Hero -> parent1.GetPV(&Hero -> parent1)); 
	AffichageCoeur -> Life(AffichageCoeur); 
      }; 
      
#if 0 
      Map -> TraiterOrdresDeplacement(Map, Hero, our_manifold, MoteurPhysiqueActif); 
      
      Game_Life_Map(Map, Hero); 
      
      Game_Life_TeleportationStartHuh(); 
      
      if (Hero -> parent1.Is0PV(&Hero -> parent1)) {
        Hero -> parent1.SetPVMax(&Hero -> parent1, 4*7);
        //RaiseEvenement(EVT_Mort);
	EvenementsModule -> Raise(EVT_Mort); 
      }; 

#endif 

      if (Hero -> parent1.Is0PV(&Hero -> parent1)) {
        //Hero -> parent1.SetPVMax(&Hero -> parent1, 4*7);
        //RaiseEvenement(EVT_Mort);
	//EvenementsModule -> Raise(EVT_Mort); 
	//game_events__stack__push(game_events_env, GAME_EVENTS__MAP__HERO_NO_MORE_PV); 
	Game_Events_Raise(GAME_EVENTS__MAP__HERO_NO_MORE_PV); 
      }; 

      
      Camera -> CalcCamera(Camera, Hero, Map -> lattice_to_map_scale_factor__x, Map -> lattice_to_map_scale_factor__y, Map -> lattice_to_map_scale_factor__z, our_manifold); 
      };
      
      break; 
    }; 
     
    
    if (ModeJeu == mjAEROTHEIERE) { 
      Game_Life_Aerotheiere(Map, Hero, Vaisseau); 
      ModeJeu = Game_Life_TeleportationStartHuh(ModeJeu); 
      break; 
    }; 


    if (ModeJeu == mjTELEPORTATION) { 
      bool teleportation_terminee_huh = false; 
      MoteurTeleportation -> Life(MoteurTeleportation, &Map, &EnVaisseau, &Hero, &teleportation_terminee_huh); 
      if (teleportation_terminee_huh) { 
	//fprintf(stderr, "TELEPORTATION_TERMINEE_HUH\n"); 
	ModeJeu = EnVaisseau ? mjAEROTHEIERE : mjCARTE; 
	Game_Events_Raise(GAME_EVENTS__MAP__LOADED_READY); 
      }; 
      break; 
    }; 
    
    
    if (ModeJeu == mjIDLE) { 
      break; 
    }; 
    

    if (ModeJeu == mjINVENTAIRE) {
      Menu_InventaireArmes -> Life(Menu_InventaireArmes); 
      break; 
    }; 

    if (ModeJeu == mjHEROS_MORT) { 
      // RL: TODO XXX FIXME 
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " --- TODO XXX FIXME - ModeJeu = %s"  "\n", __func__, int_string__stack(ModeJeu)); 
      //CMessageTexte * MessageTexte = *(api_contexte.MessageTexte_ref); 
      MessageTexte -> Life(MessageTexte); 
      break; 
    }; 
    
    
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "ModeJeu = %s"  "\n", __func__, int_string__stack(ModeJeu)); 
    assert(false); 
    
  } while (false); 
}; 









// ***************************** RENDERING ***************************** 

//glEnable(GL_DEPTH_TEST);
//glDisable(GL_DEPTH_TEST);


static void Game_Blit_Sky(const CMap * Map, const float heros_y) { 
#if 1 
  const float f = 1.5f * our_manifold -> temps__get_sunshine_intensity_at_y(our_manifold, /*map_y*/0, heros_y / Map -> lattice_height); 
#else 
  const float f = Map -> Sol -> IndiceTemps(Map -> Sol, heros_y); 
#endif 
  const GLfloat couleurduciel[4] = {0.5f*f, 0.6f*f, 1.0f*f, 1}; //1.0f}; 
  glClearColor(couleurduciel[0], couleurduciel[1], couleurduciel[2], couleurduciel[3]); 
  glFogfv(GL_FOG_COLOR, couleurduciel); 
}; 

void Game_Blit_Map(const CMap * Map, const CBonhomme * Hero, const CObjNonAnime * Vaisseau) { 
  //fprintf(stderr, "Map = %p\n", Map);
  if (Map == NULL) { return; }; 
  
  {
      float heros_x; 
      float heros_y; 
      { 
	const TPoint3D pp = Hero -> parent1.GetPosition(&Hero -> parent1); 
	heros_x = pp.x; 
	heros_y = pp.y; 
	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Hero.map_z = %f "  "\n", __func__, pp.z * Map -> lattice_to_map_scale_factor__z); 
	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Hero.map_z = %f "  "\n", __func__, Hero -> parent1.GetPosition_z(&Hero -> parent1) * Map -> lattice_to_map_scale_factor__z); 
      }; 
      
      Game_Blit_Sky(Map, heros_y); 
      
      // !! Bien - laisser cette instruction en premier sinon rien ne s'affiche… ??? 
      // RL: Theoritically, it places the camera - where the user looks from. 
      Camera -> Blit(Camera, our_manifold); 
      
      const int nb_cells_displayed_x = nb_cases_afficheesX << 1; 
      const int nb_cells_displayed_y = nb_cases_afficheesYdevant + nb_cases_afficheesYfond; 
      //Map -> Sol -> RenderEau(Map -> Sol, (int) heros_x-nb_cases_afficheesX, (int) heros_y-nb_cases_afficheesYdevant, (int) heros_x+nb_cases_afficheesX, (int) heros_y+nb_cases_afficheesYfond); 
      //Map -> Sol -> RenderEau(Map -> Sol, our_manifold, nb_cases_afficheesX << 1, nb_cases_afficheesYdevant + nb_cases_afficheesYfond, /*target_map_i*/0, /*target_map_j*/0, heros_x / (float) Map -> lattice_width, heros_y / (float) Map -> lattice_height); 
	Map -> Sol -> RenderEau(Map -> Sol, our_manifold, /*target_map_i*/Map -> global_map_i, /*target_map_j*/Map -> global_map_j, /*target_map_x*/heros_x / ((float) Map -> lattice_width), /*target_map_y*/heros_y / ((float) Map -> lattice_height), /*target_map_dx*/((float) nb_cells_displayed_x) / ((float) Map -> lattice_width), /*target_map_dy*/((float) nb_cells_displayed_y) / ((float) Map -> lattice_height)); 
      
      if (!EnVaisseau) { 
	//Map -> Sol -> Render(Map -> Sol, (int) heros_x-nb_cases_afficheesX, (int) heros_y-nb_cases_afficheesYdevant, (int) heros_x+nb_cases_afficheesX, (int) heros_y+nb_cases_afficheesYfond); 
	//Map -> Sol -> Render__pre_computations(Map -> Sol, our_manifold, nb_cases_afficheesX << 1, nb_cases_afficheesYdevant + nb_cases_afficheesYfond, /*target_map_i*/0, /*target_map_j*/0, heros_x, heros_y); 
	//Map -> Sol -> Render(Map -> Sol, our_manifold, nb_cases_afficheesX << 1, nb_cases_afficheesYdevant + nb_cases_afficheesYfond, /*target_map_i*/0, /*target_map_j*/0, heros_x / (float) Map -> lattice_width, heros_y / (float) Map -> lattice_height); 

	
	//Map -> Render(Map, (int) i-nb_cases_afficheesX, (int) j-nb_cases_afficheesYdevant, (int) i+nb_cases_afficheesX, (int) j+nb_cases_afficheesYfond, EnVaisseau); 
	Map -> Render(Map, Camera, our_manifold, nb_cases_afficheesX << 1, nb_cases_afficheesYdevant + nb_cases_afficheesYfond, /*target_map_i*/0, /*target_map_j*/0, /*target_lattice_x*/heros_x, /*target_lattice_y*/heros_y, EnVaisseau); 
	
	
	//Hero -> Render(Hero, Map -> lattice_width, Map -> lattice_height, our_manifold, Camera); 
	Hero -> Render(Hero, Map -> lattice_to_map_scale_factor__x, Map -> lattice_to_map_scale_factor__y, Map -> lattice_to_map_scale_factor__z, our_manifold, Camera); 
	
	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Hero.map_z = %f "  "\n", __func__, Hero -> parent1.GetPosition_z(&Hero -> parent1) * Map -> lattice_to_map_scale_factor__z); 
	
      } 
      else { // _en vaisseau_ 
	//Map -> Render(Map, our_manifold, 0, 0, 1000, 1000, EnVaisseau); 
	Map -> Render(Map, Camera, our_manifold, /*nb_cells_displayed_x*/1000, /*nb_cells_displayed_y*/1000, /*target_map_i*/0, /*target_map_j*/0, /*target_map_x*/0.5, /*target_map_y*/0.5, EnVaisseau); 
	//Vaisseau -> Render(Vaisseau, Map -> lattice_width, Map -> lattice_height, our_manifold); 
	Vaisseau -> Render(Vaisseau, Map -> lattice_to_map_scale_factor__x, Map -> lattice_to_map_scale_factor__y, Map -> lattice_to_map_scale_factor__z, our_manifold); 
      }; // end de else de «if (Envaisseau)» 
      
      
      // *** affichage des coeurs *** 
      AffichageCoeur -> Render(AffichageCoeur); 
      
      // *** affichage de la main *** 
      const float FacteurCompression = our_manifold -> FacteurCompression(our_manifold, /*map_j*/0, heros_y * Map -> lattice_to_map_scale_factor__y); 
      AffichageMainPierre -> Render(AffichageMainPierre, heros_y, FacteurCompression); //Map); 
      
    }; // end de «if (Map != NULL)»
}; 


void Game_Blit(void) { 
#if 1 
  { 
    // RL: Après tests, ça permet au héros et aux ennemis de ne pas être sombres.
    const float light_diffuse[] = {0.1f, 1.0f, 1.0f, 1.0f};
    const float light_amb[] = {0.4f, 0.4f, 0.4f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
    // modifie la couleur anbiante de la lumière n°0
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    // modifie la couleur de lumière diffuse
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /*glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, (float *) &Camera -> dir); 
      glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 128.0);
      glLightfv(GL_LIGHT0, GL_POSITION, (float *) &Camera -> pos);*/
    
    const float pos[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, (const float *) &pos);
  }; 
#endif 
  






  // RL: Cleaning up the screen and the z-buffer 
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  //glEnable(GL_TEXTURE_2D);
  CPhysicalObj * Hero_o = &Hero -> parent1; 

  do { 
    if (ModeMenuSysteme) { 
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "ModeMenuSysteme = %s" "\n", __func__, bool_string(ModeMenuSysteme)); 
      MiniMenu -> Render(MiniMenu); 
      break; 
    }; 
    

    if (ModeJeu == mjTITRE) {
      PageTitre -> Render(PageTitre); 
      break; 
    };
    
    
    if (ModeJeu == mjINVENTAIRE) {
      //if (Menu_InventaireArmes -> InputAndRender(Menu_InventaireArmes)) {
      Menu_InventaireArmes -> Render(Menu_InventaireArmes); 
      break; 
    }; 
    
  
    if (ModeJeu == mjIDLE) { 
      break; 
    }; 
    

    if ((ModeJeu == mjOEIL) || (ModeJeu == mjCARTE)) { 
#if 0 
      { 
	const TPoint3D pp = Hero -> parent1.p; 
	const TPoint3D vv = Hero -> parent1.v; 
	const TPoint3D aa = Hero -> parent1.a; 
	fprintf(stderr, "HEROS  LATTICE  POSITION        : %3f %3f %3f " "\n", pp.x, pp.y, pp.z); 
	fprintf(stderr, "HEROS  LATTICE  SPEED           : %3f %3f %3f " "\n", vv.x, vv.y, vv.z); 
	fprintf(stderr, "HEROS  LATTICE  ACCELERATION    : %3f %3f %3f " "\n", aa.x, aa.y, aa.z); 
      }; 
#endif 
#if 0 
      { 
	//Hero -> parent1.p.x += 0.1f; 
	//Hero -> parent1.p.y += 0.1f; 
	const TPoint3D pp = Hero -> parent1.GetPosition(&Hero -> parent1); 
	const TPoint3D manifold_pp = our_manifold -> get_manifold_coordinates(our_manifold, /*map_i*/0, /*map_j*/0, /*map_x*/pp.x  / (float) Map -> lattice_width, /*map_y*/pp.y  / (float) Map -> lattice_height, /*map_z*/pp.z); 
	fprintf(stderr, "HEROS  LATTICE  POSITION        : %3f %3f %3f " "\n", pp.x, pp.y, pp.z); 
	fprintf(stderr, "HEROS  MAP      POSITION        : %3f %3f %3f " "\n", pp.x / (float) Map -> lattice_width, pp.y / (float) Map -> lattice_height, pp.z); 
	fprintf(stderr, "HEROS  MANIFOLD POSITION        : %3f %3f %3f " "\n", manifold_pp.x, manifold_pp.y, manifold_pp.z); 
      }; 
#endif 
#if 0 
      { 
	const TPoint3D dd = Hero -> parent1.dimension; 
	fprintf(stderr, "HEROS  LATTICE  DIMENSION       : %3f %3f %3f " "\n", dd.x, dd.y, dd.z); 
      }; 
#endif 
#if 0 
      { 
	static int count = 0; count++; 
	if (5 == count) { 
 	  fprintf(stderr, "MANIFOLD W_NB x H_NB            : %d x %d " "\n", our_manifold -> w_nb, our_manifold -> h_nb); 
	  if (our_manifold -> type == RIEMANN_TYPE__RECTANGLE) { 
	    fprintf(stderr, "MANIFOLD IS A RECTANGLE " "\n"); 
	    const float (* data)[4] = (const float (*)[4]) (our_manifold -> rectangle_data); 
	    fprintf(stderr, "MANIFOLD W x H                  : %3f x %3f " "\n", (*data)[0], (*data)[1]); 
	    fprintf(stderr, "MANIFOLD W_ONE_MAP x H_ONE_MAP  : %3f x %3f " "\n", (*data)[2], (*data)[3]); 
	  }; 
	  fprintf(stderr, "GROUND LATTICE VERTEX W x H     : %d x %d " "\n", Map -> Sol -> TailleX, Map -> Sol -> TailleY); 
	  const TPoint3D pp = Hero -> parent1.GetPosition(&Hero -> parent1); 
	  const TPoint3D manifold_pp = our_manifold -> get_manifold_coordinates(our_manifold, /*map_i*/0, /*map_j*/0, /*map_x*/pp.x  / (float) Map -> lattice_width, /*map_y*/pp.y  / (float) Map -> lattice_height, /*map_z*/pp.z); 
	  fprintf(stderr, "HEROS  LATTICE  POSITION        : %3f %3f %3f " "\n", pp.x, pp.y, pp.z); 
	  fprintf(stderr, "HEROS  MAP      POSITION        : %3f %3f %3f " "\n", pp.x / (float) Map -> lattice_width, pp.y / (float) Map -> lattice_height, pp.z); 
	  fprintf(stderr, "HEROS  MANIFOLD POSITION        : %3f %3f %3f " "\n", manifold_pp.x, manifold_pp.y, manifold_pp.z); 
	  fprintf(stderr, "CAMERA LATTICE  POSITION        : %3f %3f %3f " "\n", Camera -> lattice_position.x, Camera -> lattice_position.y, Camera -> lattice_position.z); 
	  fprintf(stderr, "CAMERA MAP      POSITION        : %3f %3f %3f " "\n", Camera ->     map_position.x, Camera ->     map_position.y, Camera ->     map_position.z); 
	  fprintf(stderr, "CAMERA MANIFOLD POSITION        : %3f %3f %3f " "\n", Camera -> manifold__camera_position[0], Camera -> manifold__camera_position[1], Camera -> manifold__camera_position[2]); 
	  fprintf(stderr, "CAMERA MANIFOLD TARGET_POSITION : %3f %3f %3f " "\n", Camera -> manifold__target_position[0], Camera -> manifold__target_position[1], Camera -> manifold__target_position[2]); 
	  fprintf(stderr, "CAMERA MANIFOLD UPWARD_DIRECTION: %3f %3f %3f " "\n", Camera -> manifold__upward_direction[0], Camera -> manifold__upward_direction[1], Camera -> manifold__upward_direction[2]); 
	  
	  const CSol * Sol = Map -> Sol; 
	  { 
	    fprintf(stderr, "SOL GLOBAL MAP POSITION X: [ " ); 
	    for (int vertex_i = 0; vertex_i < Sol -> TailleX; vertex_i++) { 
	      fprintf(stderr, "%f ", Sol -> global_map__x[vertex_i]); 
	    }; 
	    fprintf(stderr, "] " "\n" ); 
	  }; 
	  { 
	    fprintf(stderr, "SOL GLOBAL MAP POSITION Y: [ " ); 
	    for (int vertex_j = 0; vertex_j < Sol -> TailleY; vertex_j++) { 
	      fprintf(stderr, "%f ", Sol -> global_map__y[vertex_j]); 
	    }; 
	    fprintf(stderr, "] " "\n" ); 
	  }; 
#if 0 
	  { 
	    fprintf(stderr, "SOL MANIFOLD VERTEX POSITION:  " "\n"); 
	    for (int vertex_j = 0; vertex_j < Sol -> TailleY; vertex_j++) { 
	      fprintf(stderr, "  [ "); 
	      for (int vertex_i = 0; vertex_i < Sol -> TailleX; vertex_i++) { 
		const int index = vertex_j * Sol -> TailleX + vertex_i; 
		fprintf(stderr, "%d-%d-%d ", (int) Sol -> manifold__vertex[index][0], (int) Sol -> manifold__vertex[index][1], (int) Sol -> manifold__vertex[index][2]); 
	      }; 
	      fprintf(stderr, "] " "\n" ); 
	    }; 
	    fprintf(stderr, " " "\n" ); 
	  }; 
#endif 
#if 0 
	  { 
	    fprintf(stderr, "SOL MANIFOLD VERTEX Z:  " "\n"); 
	    for (int vertex_j = 0; vertex_j < Sol -> TailleY; vertex_j++) { 
	      fprintf(stderr, "  [ "); 
	      for (int vertex_i = 0; vertex_i < Sol -> TailleX; vertex_i++) { 
		const int index = vertex_j * Sol -> TailleX + vertex_i; 
		fprintf(stderr, "%d ", (int) Sol -> manifold__vertex[index][2]); 
	      }; 
	      fprintf(stderr, "] " "\n" ); 
	    }; 
	    fprintf(stderr, " " "\n" ); 
	  }; 
#endif 
#if 0 
	  { 
	    fprintf(stderr, "SOL MANIFOLD VERTEX POSITION:  " "\n"); 
	    for (int vertex_j = 0; vertex_j < Sol -> TailleY; vertex_j++) { 
	      fprintf(stderr, "  [ "); 
	      for (int vertex_i = 0; vertex_i < Sol -> TailleX; vertex_i++) { 
		const int index = vertex_j * Sol -> TailleX + vertex_i; 
		fprintf(stderr, "%d-%d ", (int) Sol -> manifold__vertex[index][0], (int) Sol -> manifold__vertex[index][1]); 
	      }; 
	      fprintf(stderr, "] " "\n" ); 
	    }; 
	    fprintf(stderr, " " "\n" ); 
	  }; 
#endif 
	  
	  
	  
	  
	  
	  
	  
	}; 
      }; 
#endif 
    }; 
    
    if (ModeJeu == mjOEIL) { 
      const float target_map_x = Camera -> map__target_position.x; // / (float) Map -> lattice_width; 
      const float target_map_y = Camera -> map__target_position.y; // / (float) Map -> lattice_height; 
      Map -> Sol -> Render__pre_computations(Map -> Sol, our_manifold, /*global_map_i*/0, /*global_map_j*/0, target_map_x, target_map_y, /*target_map_dx*/4.0f, /*target_map_dy*/4.0f); 
#if 1 
      Game_Blit_Map(Map, Hero, Vaisseau); 
#elif 1 
      Game_Blit_Sky(Map, /*heros_y*/0); 
      Camera -> Blit(Camera, our_manifold); 
      Map -> Sol -> RenderEau(Map -> Sol, our_manifold, /*target_map_i*/Map -> global_map_i, /*target_map_j*/Map -> global_map_j, /*target_map_x*/target_map_x, /*target_map_y*/target_map_y, /*target_map_dx*/4.0f, /*target_map_dy*/4.0f); 
      //Map -> Sol -> Render(Map -> Sol, our_manifold, /*target_map_i*/Map -> global_map_i, /*target_map_j*/Map -> global_map_j, /*target_map_x*/target_map_x, /*target_map_y*/target_map_y, /*target_map_dx*/4.0f, /*target_map_dy*/4.0f); 
      Map -> Render(Map, Camera, our_manifold, /*nb_cells_displayed_x*/128, /*nb_cells_displayed_y*/128, /*target_map_i*/0, /*target_map_j*/0, /*target_lattice_x*/0, /*target_lattice_y*/0, /*EnVaisseau*/false); 
#else 
      Game_Blit_Sky(Map, /*heros_y*/0); 
      Camera -> Blit(Camera, our_manifold); 
      Map -> Sol -> RenderEau(Map -> Sol, our_manifold, /*target_map_i*/Map -> global_map_i, /*target_map_j*/Map -> global_map_j, /*target_map_x*/target_map_x, /*target_map_y*/target_map_y, /*target_map_dx*/4.0f, /*target_map_dy*/4.0f); 
      Map -> Render(Map, Camera, our_manifold, /*nb_cells_displayed_x*/128, /*nb_cells_displayed_y*/128, /*target_map_i*/0, /*target_map_j*/0, /*target_lattice_x*/0, /*target_lattice_y*/0, /*EnVaisseau*/false); 
      Hero -> Render(Hero, Map -> lattice_to_map_scale_factor__x, Map -> lattice_to_map_scale_factor__y, Map -> lattice_to_map_scale_factor__z, our_manifold, Camera); 
      AffichageCoeur -> Render(AffichageCoeur); 
      AffichageMainPierre -> Render(AffichageMainPierre, /*heros_y*/0, /*FacteurCompression*/1.0f); 
#endif 
      break; 
    }; 
    
    if (ModeJeu == mjCARTE) { 
      if (Map == NULL) break; 
      const TPoint3D pp = Hero -> parent1.GetPosition(&Hero -> parent1); 
      const float heros_x = pp.x; 
      const float heros_y = pp.y; 
      const float target_map_x = heros_x / (float) Map -> lattice_width; 
      const float target_map_y = heros_y / (float) Map -> lattice_height; 
      //Map -> Sol -> Render__pre_computations(Map -> Sol, our_manifold, nb_cases_afficheesX << 1, nb_cases_afficheesYdevant + nb_cases_afficheesYfond, /*target_map_i*/0, /*target_map_j*/0, /*target_map_x*/heros_x / (float) Map -> lattice_width, /*target_map_y*/heros_y / (float) Map -> lattice_height); 
      //Map -> Sol -> Render__pre_computations(Map -> Sol, our_manifold, 64, 64, /*target_map_i*/0, /*target_map_j*/0, /*target_map_x*/heros_x, /*target_map_y*/heros_y); 
      //Map -> Sol -> Render__pre_computations(Map -> Sol, our_manifold, nb_cases_afficheesX << 1, nb_cases_afficheesYdevant + nb_cases_afficheesYfond, /*target_map_i*/0, /*target_map_j*/0, /*target_map_x*/target_map_x, /*target_map_y*/target_map_y); 
      Map -> Sol -> Render__pre_computations(Map -> Sol, our_manifold, /*global_map_i*/0, /*global_map_j*/0, target_map_x, target_map_y, /*target_map_dx*/1.0f, /*target_map_dy*/1.0f); 
      
      Game_Blit_Map(Map, Hero, Vaisseau); 
      
      // RL: Menu de l'objet le plus proche 
      const CPhysicalObj * nearest_o = CMap__GetNearestInteractingObject(Map, Hero_o); 
      if (nearest_o != NULL) { 
	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " nearest_o -> filename = %s "  "\n", __func__, nearest_o -> filename); 
	nearest_o -> actions -> ActionMenu_Render(nearest_o -> actions); 
      }; 
      break; 
    }; 
    
    
    if (ModeJeu == mjAEROTHEIERE) { 
      Game_Blit_Map(Map, Hero, Vaisseau); 
      break; 
    }; 
    
    
    if (ModeJeu == mjTELEPORTATION) { 
      Game_Blit_Map(Map, Hero, Vaisseau); 
      MoteurTeleportation -> Render(MoteurTeleportation, &Map, &EnVaisseau, &Hero, our_manifold); 
      break; 
    }; 
    
    
    if (ModeJeu == mjHEROS_MORT) { 
      // RL: TODO XXX FIXME 
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " --- TODO XXX FIXME - ModeJeu = %s"  "\n", __func__, int_string__stack(ModeJeu)); 
      //CMessageTexte * MessageTexte = *(api_contexte.MessageTexte_ref); 
      MessageTexte -> Render(MessageTexte); 
      break; 
    }; 
    
    
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "ModeJeu = %s"  "\n", __func__, int_string__stack(ModeJeu)); 
    assert(false); 
    

  } while (false);   
  
}; // RaiseRender() 

























void Game_Dispose(void) { 
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " >>> " "\n", __func__); 
  printf("On quitte le jeu et on va tranquillement désallouer TOUT!\n"); 
  fflush(NULL); 
  
  printf("-------- on détruit la carte courante ---------\n"); 
  if (Map != NULL) CMap__delete(Map); 
  
  printf("-------- on détruit la caméra ----------------\n"); 
  if (Camera != NULL) CCamera__delete(Camera); 
  
  printf("-------- on détruit le héros ----------------\n"); 
  if (Hero != NULL) CBonhomme__delete(Hero); 
  
  printf("-------- on détruit le vaisseau ----------------\n"); 
  CObjNonAnime__delete(Vaisseau); 
  
  printf("-------- on détruit le moteur de téléportation ----------------\n"); 
  CMoteurTeleportation__delete_content(MoteurTeleportation); 
  
  printf("-------- on détruit le moteur d'affichage de pierre ---------\n"); 
  if (AffichageMainPierre != NULL) CAffichageMainPierre_delete(AffichageMainPierre); 
  
  printf("-------- on détruit le moteur d'affichage de coeurs ---------\n"); 
  CAffichageCoeur_delete(AffichageCoeur); 
  
  printf("-------- on détruit les sons... ---------\n"); 
  if (son_bouton_saut   != NULL) CSon_delete(son_bouton_saut); 
  if (son_bouton_espace != NULL) CSon_delete(son_bouton_espace); 
  
  printf("-------- on détruit la musique ---------\n"); 
  if (Musique != NULL) CMusique_delete(Musique); 
  
  printf("-------- on détruit l'interface pour entrer les noms --------\n"); 
  CMenuEntreeNom_delete(MenuEntreeNom); 
  
  printf("-------- on détruit le moteur d'affichage de page de titre ---------\n"); 
  CPageTitre_delete(PageTitre); 
  
  printf("-------- on détruit le moteur d'affichage de message de texte ---------\n"); 
  CMessageTexte_delete(MessageTexte); 
  
  printf("-------- on détruit le moteur d'affichage de texte ---------\n"); 
  CText_delete(Text); 
  
  EvenementsModule -> End(); 
  
  free_actions(); 
  
  if (our_manifold != NULL) { our_manifold -> delete(our_manifold); }; 
  
  game_events_env__delete(&game_events_env); 
  
  printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " <<< " "\n", __func__); 
}; 









