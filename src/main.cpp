#include "global.hpp"
#include "main.hpp"
#include "kernel.hpp"
#include "map.hpp"
#include "menu.hpp"
#include "bonhomme.hpp"
#include "son.hpp"
#include "text.hpp"
#include "objnonanime.hpp"
#include "coeurs.hpp"
#include "pagetitre.hpp"
#include "affichagemainpierre.hpp"
#include "evenement.hpp"
#include "action.hpp"
#include "apiscript.hpp"
#include "moteurteleportation.hpp"
#include "camera.hpp"
#include "menuentreenom.hpp"



static void RenderCiel(const CMap * Map, float heros_y);
static void RenderModeScript(void);
static void RenderModeScript_step(void);


static const bool ExecuterScriptDeDebut = true;

static bool MoteurPhysiqueActif = true;

static bool EnVaisseau = false;
static float AngleXY = 0;

static CMap * Map = NULL;
static CMenuAbstrait * Menu = NULL;
CMenuAbstrait * MiniMenu = NULL; // accédé directement au sein du Pascal
static CBonhomme * Hero = NULL;
static CMusique * Musique = NULL;
static CObjNonAnime * Vaisseau = NULL;

CMenuEntreeNom * MenuEntreeNom = NULL;
CMoteurTeleportation MoteurTeleportation;
//static TTypeInstructionCourante TypeInstructionCourante;
static TTypeInstructionCourante TypeInstructionCourante = ticInstructionScript;
CCamera Camera;

static CSon * son_bouton_espace = NULL;
static CSon * son_bouton_saut = NULL;

// objet interface (GUI)
static CPageTitre * PageTitre = NULL;
static CAffichageMainPierre * AffichageMainPierre = NULL;



/***************
 ÉTAT DU JEU
 Un jeu vidéo c'est un grand automate...
**************************************************************************/

static bool ModeMenuSysteme = false;
static TModeJeu ModeJeu = mjTITRE;

static float Temps = 0.0f;
static float marche_compression = marche_compression_defaut;

static bool SCRIPT_SystemeRendMainAuScript = false;


static CScriptLauncher * script = NULL;



api_contexte_t api_contexte = {
  &ModeJeu, &SCRIPT_SystemeRendMainAuScript, &Map, &Musique, &Menu, &Hero, &Temps, &marche_compression, &TypeInstructionCourante, &MiniMenu, 0, NULL
};



static void gestion_menu(void);
static void DebutDePartie(void);



void DebutDePartie(void) {
  printf("\n\n");
  printf("Création du menu\n");
  Menu = new CMenu();
  //Menu = new CMiniMenu(100,300,200);
  Menu -> NomSousMenu[0] = strcopy("Armes");
  Menu -> NomSousMenu[1] = strcopy("Objets");
  Menu -> NomSousMenu[2] = strcopy("Magies");

  SCRIPT_RecevoirUneArme("menu/epee");
  SCRIPT_RecevoirUneArme("menu/arc");


  printf("Création du héros\n");
  Hero = new CBonhomme("./heros.anime");
  printf("Héros créé. Son pointeur est %p\n", Hero);
  //Hero -> SetPVMax(1/*3*7*/);
  Hero -> SetPVMax(4*7);


  //initialisation de la caméra
  Camera.InitCamera();
  Camera.SolidariserAuHeros();
  
  Map = NULL;

  // TODO Normalement, c ici le pt de départ!
#if 1
  // *** on run le script! La fonction «début» pour être précis. ***
  if (ExecuterScriptDeDebut) {
    //fprintf(stderr, "Lancement du script de démarrage...\n");
    ModeJeu = mjSCRIPT;
    script = new CScriptLauncher("script.pml", "debut");
    assert(script != NULL);
    script -> init_step();
    //p.Execute();
  }
#else
  // si le script de démarrage n'a pas chargé de carte, en charger une 
  if (Map == NULL) {
    printf("ERREUR: Le script de début de jeu ne charge pas de carte. Par défaut, on charge 'village.carte'.\n");
    Map = new CMap("./village.carte", false);
    Hero -> SetPosition(10.0f, 10.0f, mpABSOLU, Map);
  }
#endif  

  
}



// Procédure d'initialisation 
void Init(void) {
  //fprintf(stderr, "Init: ModeJeu = %d\n", ModeJeu);

  //Musique = new CMusique("a.mp3");
  //Musique = new CMusique("zelda.mid");
  init_actions();

  Text = new CText();
  MessageTexte = new CMessageTexte();
  PageTitre = new CPageTitre;
  MenuEntreeNom = new CMenuEntreeNom();

  //fprintf(stderr, "Init: ModeJeu = %d\n", ModeJeu);

  Musique = new CMusique("intro.mid");
  Musique -> Jouer();
  son_bouton_espace = new CSon("./frappe.wav");
  son_bouton_saut = new CSon("./frappe.wav");
  //son_bouton_saut = new CSon("./plaisir.wav");

  //fprintf(stderr, "Init: ModeJeu = %d\n", ModeJeu);

  AffichageCoeur = new CAffichageCoeur();
  AffichageMainPierre = new CAffichageMainPierre();  

  //fprintf(stderr, "Init4: ModeJeu = %d\n", ModeJeu);

  Vaisseau = new CObjNonAnime("vaisseau.nonanime");

  //fprintf(stderr, "Init: ModeJeu = %d\n", ModeJeu);

  // *** OpenGL stuffs… ***
  glEnable(GL_BLEND) ;
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;   
  glEnable(GL_TEXTURE_2D);
  //MessageTexte -> SetMsg("Bonjour!! Bienvenue dans le jeu le plus révolutionnaire du 24e millénaire. C'est vraiment que c'est cool et que c'est trop bien. Heureusement que ça marche nickel... j'avais peur un moment. Mais j'avoue que tout est bien qui finit bien.");
  glEnable(GL_LIGHTING);
  // on active le calcul de la lumière
  glEnable(GL_LIGHT0); 
  // on dit que la lumière n°0 est allumée
  // Affichage de la lumière: flou ou pas
  glShadeModel(GL_SMOOTH);
  //glShadeModel(GL_FLAT);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  // on dit que les appels glColor modifie en fait la couleur d'ambiance et de diffusion du matériau
  glPolygonMode(GL_FRONT, GL_FILL);
  glPolygonMode(GL_BACK, GL_FILL);
  // Cause l'apparition des triangles.
  // Donc, l'antialising on enlève.
  //glEnable(GL_POLYGON_SMOOTH);
  glDisable(GL_POLYGON_SMOOTH);
  float mat_amb[] = {1.0, 1.0, 1.0, 1.0};
  float mat_diff[] = {1.0, 1.0, 1.0, 1.0};
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diff);
  float mat_em[] = {0.0, 0.0, 0.0, 1.0};
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_em);
  // les deux lignes qui suivent sont là pour éviter les bugs de chevauchements
  // pour les images avec des parties entièrement translucides (en fait,
  // un pixel entièrement transparent ne touche pas le Z-buffer)
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GREATER, 0.0f);
  glFogi(GL_FOG_MODE, GL_LINEAR);
  //glFogi(GL_FOG_MODE, GL_EXP);   // exponentiel
  //glFogf(GL_FOG_DENSITY, 0.001); 
  //glFogf(GL_FOG_DENSITY, 0.0f); // GL_FOG_DENSITY CA MARCHE PAS en mode linéaire  !!
  glFogf(GL_FOG_START, 0);
  glFogf(GL_FOG_END, 500); //500
  glEnable(GL_FOG);
#if 0
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
#endif
  
  printf("Fin de l'initialisation!! YOUPI!!\n");
  //fprintf(stderr, "Init: ModeJeu = %d\n", ModeJeu);
}






// Procédure pour récupérer les commandes clavier et souris
void RaiseInput(void) {
  //fprintf(stderr, "ModeJeu = %d\n", ModeJeu);

  if (ModeJeu == mjJEU && !ModeMenuSysteme) {

    if (KEY_ACTIVEDESACTIVEMOTEURPHYSIQUE)
      MoteurPhysiqueActif = !MoteurPhysiqueActif;

        
    // si on est à pied, les touches sont…
    if (!EnVaisseau) {

      if (KEY_VUE_ANGLE_PLUS)
        Camera.angleXY += PI/32.0f;
      
      if (KEY_VUE_ANGLE_MOINS)
        Camera.angleXY -= PI/32.0f;
      
      if (KEY_UP)
        Hero -> Avancer(ConvertirDirectionAvecVue(DOS, Camera), Map);
      
      if (KEY_DOWN) 
        Hero -> Avancer(ConvertirDirectionAvecVue(FACE, Camera), Map);
      
      if (KEY_LEFT)
        Hero -> Avancer(ConvertirDirectionAvecVue(PROFIL_VERS_G, Camera), Map);
      
      if (KEY_RIGHT)
        Hero -> Avancer(ConvertirDirectionAvecVue(PROFIL_VERS_D, Camera), Map);
      
      if (KEY_JUMP) {
        printf("On saute. (pagedown appuyé…)\n");
   
        if (Hero -> Immerge) {
          if (Hero -> GetVitesse().z < 0) {
            Hero -> AddForce(0.0f, 0.0f,50.1f);
            son_bouton_saut -> Jouer();
          }
          else
            Hero -> AddForce(0.0f, 0.0f,1.5f);
        } // if (Hero -> Immerge)
   
        else if (Hero -> AuSol) {
          son_bouton_saut -> Jouer();
          Hero -> AddForce(0.0f, 0.0f, 180.0f);
        } // if (Hero -> AuSol)

      } // if (KEY_JUMP)
      
      if (KEY_MENU_JEU)
        ModeJeu = mjMENU;

    }

    // else de «if (!EnVaisseau)»
    else {
#define pas_angle_vaisseau 0.1f 

      if (KEY_LEFT)
        AngleXY += pas_angle_vaisseau;

      if (KEY_RIGHT)
        AngleXY -= pas_angle_vaisseau;
      
#define force_vaisseau 10.0f
#define force_vaisseau_altitude 80.0f
      if (KEY_UP)
        Hero -> AddForce(Point3D(force_vaisseau*cosf(AngleXY), force_vaisseau*sinf(AngleXY), 0.0f));  
        
      if (KEY_DOWN)
        Hero -> AddForce(Point3D(-force_vaisseau*cosf(AngleXY), -force_vaisseau*sinf(AngleXY), 0.0f));  
      
      if (KEY_VAISSEAU_UP)
        Hero -> AddForce(Point3D(0.0f, 0.0f, force_vaisseau_altitude));
      
      if (KEY_VAISSEAU_DOWN)
        Hero -> AddForce(Point3D(0.0f, 0.0f, -force_vaisseau_altitude));   
    }

     

    if (KEY_FRAPPER) {
      /*TPoint2D d = Map -> Differentiel(Hero -> GetPosition()); 
        printf("Ahhh je glisse dans la direction (%f, %f)\n", -d.x, -d.y);
        Hero -> AddForce(-d.x/3.0f, -d.y/3.0f, 0.0f);*/
      son_bouton_espace -> Jouer();
      Hero -> Frapper();
      
      /*création d'un projectile*/
      /*CPhysicalObj* projectile = new CBonhomme("sang.anime");
   
      projectile -> SetPosition(Hero -> GetPosition() + Point3D(0.0f, 0.0f, 20.0f));
      projectile -> AddForce(50*DirectionToVecteur(Hero -> GetDirection() ) + Point3D(0.0f, 0.0f, 300.0f));
      projectile -> SetObjetEphemere(300);
      projectile -> Hostile = false;
	     
      Map -> AjouterObjet(projectile);*/
      
    }
        
      
    
    if (KEY_MENU_SYSTEME) {
      delete MiniMenu;
      
      MiniMenu = new CMiniMenu(100, 300,1000);         
      MiniMenu -> Add(0,"Continuer à jouer",NULL);
      MiniMenu -> Add(0,"Quitter",NULL);
      
      ModeMenuSysteme = true;
    }

  }    


  // Qu'est-ce que ça fout là?
  // À quoi ça sert?
  // …
  // Après tests, ça permet au héros et aux ennemis de ne pas être sombres.
  // Bien.
  // Mais qu'est-ce que ça fout là?
  // Nous sommes dans la fonction «RaiseInput» bordel de merde!!
#if 1
  float light_diffuse[] = {0.1f, 1.0f, 1.0f, 1.0f};
  float light_amb[] = {0.4f, 0.4f, 0.4f, 1.0f};
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
  // modifie la couleur anbiante de la lumière n°0
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  // modifie la couleur de lumière diffuse
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  /*glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, (float *) &Camera.dir); 
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 128.0);
    glLightfv(GL_LIGHT0, GL_POSITION, (float *) &Camera.pos);*/
  
  
  float pos[] = {0.0f, 0.0f, 0.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, (float *) &pos);
#endif

}



void gestion_menu(void) {
  /* le menu a été affiché et le joueur a sélectionné un élément
   * (ou à annuler ce qui revient à avoir (Menu -> iphi == -1)
   *
   * là gestion_menu() s'occupe de réaliser l'action correspondante au menu
   */
  
  if (!Menu -> Canceled) {
    switch (Menu -> iphi) {
    case ANNEAU_MENU_ARME: {
      CPantin * Epee = new CPantin();
      
      if (Menu -> itheta == 0)      
        Epee -> AjouterMembre("./heros/epee.png", -0.0f, 0.0f, -22.0f, 9.0f , 32.0f, 10.0f);
      else
        Epee -> AjouterMembre("./heros/arc.png", -0.0f, 0.0f, -22.0f, 7.0f , 37.0f, 10.0f);
      
      Hero -> SetPantinFils(MEMBRE_AVEC_ARME , Epee);
    }
      break; 
      
    case ANNEAU_MENU_OBJET:
      break;

    default: assert(false);
    }
  }
}



void RaiseLife(void) {
  //fprintf(stderr, "ModeJeu = %d\n", ModeJeu);

  if (ModeJeu == mjTITRE) {
    if (PageTitre -> Life()) {
      ModeJeu = mjJEU;
      DebutDePartie();
    }
  }



  if (Map != NULL) {
    // on gère le temps
    Temps += marche_compression;      
    Map -> SetTemps(Temps);


#if 1
    // vérifie si l'on va changer de carte…
    if (CZoneTeleportation * pzt = Map -> VaTonBouger(Hero))
      if (EnVaisseau || (Hero -> GetDirection() == pzt -> depart_direction))
        if (not(MoteurTeleportation.IsTeleportationEnCours())) {
          CZoneTeleportation zt = *pzt;
     
          printf("On arrive sur une zone de téléportation:\n");
          printf("Direction du héros %i, de la zone %i\n", Hero -> GetDirection(), pzt -> depart_direction);
          printf("   position: (%f, %f, %f)\n", zt.position.x, zt.position.y, zt.position.z);
          ModeJeu = mjTELEPORTATION;
          SCRIPT_ChangerDeCarte(&MoteurTeleportation, zt);
        }
#endif
     

    // *** Calculs à faire avant l'affichage ***
    if (EnVaisseau) {
      Hero -> CoeffFrottementFluide = 1.0f;
      Hero -> CoeffFrottementFluideZ = 0.5f;
      Hero -> CalcNewPosition();
      Hero -> ValiderPosition(MoteurPhysiqueActif);
      Hero -> InitForce();
      float zcarte = Map -> GETZ(Hero -> GetPosition().x, Hero -> GetPosition().y);
      float z = Hero -> GetPosition().z;
  
#define ZMAXVAISSEAU 200.0f
      if (z < zcarte)
        z = zcarte;

      if (z > ZMAXVAISSEAU)
        z = ZMAXVAISSEAU;

      Hero -> SetPosition(Point3D(Hero -> GetPosition().x, Hero -> GetPosition().y, z));
      Camera.angleXY = AngleXY;
    }
     
    else { // pas en vaisseau

      if (ModeJeu == mjSCRIPT)
        Map -> TraiterOrdresDeplacement(Hero, MoteurPhysiqueActif);
      
      if (ModeJeu == mjJEU)
        if (CObjActionnable * objetproche = Map -> TesterPositionHero(Hero, MoteurPhysiqueActif))
          objetproche -> InputAndRenderActionMenu();
  
      if (Hero -> Is0PV()) {
        Hero -> SetPVMax(4*7);
        RaiseEvenement(EVT_Mort);
      }
  
    } // fin de «if-else (en_vaisseau)»
     
    
    AffichageCoeur -> InformerNbPV(Hero -> GetPV());
    AffichageCoeur -> Life();
  }


  if (ModeJeu == mjTELEPORTATION) {
    bool teleportation_terminee_huh = false;
    MoteurTeleportation.Life(Map, EnVaisseau, Hero, teleportation_terminee_huh);
    if (teleportation_terminee_huh) {
      //fprintf(stderr, "TELEPORTATION_TERMINEE_HUH\n");
      ModeJeu = mjJEU;
    }
  }
  
}



//glEnable(GL_DEPTH_TEST);
//glDisable(GL_DEPTH_TEST);


// *** Procédure pour afficher ***
void RaiseRender(void) {
  //fprintf(stderr, "RaiseRender: ModeJeu = %d\n", ModeJeu);
  // On efface l'écran et le Z-buffer.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  //glEnable(GL_TEXTURE_2D);
  

  if (ModeMenuSysteme) {
    if (MiniMenu -> InputAndRender()) {
      if (not(MiniMenu -> Canceled))
        if (MiniMenu -> itheta == 1)
          DemanderAQuitterLeJeu();
      
      ModeMenuSysteme = false;          
    }
  }
  
  
  if (ModeJeu == mjTITRE) {
    PageTitre -> Render();
    SDL_GL_SwapBuffers();
    return;
  }


  // *** affichage de l'inventaire ("menu" n'est pas un bon nom :-) ***
  if (ModeJeu == mjMENU) {
    if (Menu -> InputAndRender()) {
      gestion_menu();
      ModeJeu = mjJEU;
    }

    //fprintf(stderr, "HERE\n");
    //SDL_GL_SwapBuffers();
    //return;
  } // mjMenu


  // *** Render en mode script ***
  if (ModeJeu == mjSCRIPT) {
    RenderModeScript();
  } 
   


  //fprintf(stderr, "Map = %p\n", Map);
  if (Map != NULL) {
    float i;
    float j;
    {
      TPoint3D pp = Hero -> GetPosition();
      i = pp.x;
      j = pp.y;
    }
  
    RenderCiel(Map, j);

    // !! Bien laisser cette instruction en premier sinon rien ne s'affiche… ???
    Camera.CalcCamera(Hero, Map);
    
    Map -> RenderEau((int) i-nb_cases_afficheesX, (int) j-nb_cases_afficheesYdevant, (int) i+nb_cases_afficheesX, (int) j+nb_cases_afficheesYfond);

    if (!EnVaisseau) {
      Map -> Render((int) i-nb_cases_afficheesX, (int) j-nb_cases_afficheesYdevant, (int) i+nb_cases_afficheesX, (int) j+nb_cases_afficheesYfond, EnVaisseau);
      Hero -> Render(Map);
    }
    else { // _en vaisseau_
      TPoint3D p;

      /* pour l'instant c un peu de la magouille:
       * j'utilise l'objet Hero en interface (histoire de pas tout rechanger)
       * et après je transfère la position de Hero sur le vaisseau
       */
      p = Hero -> GetPosition();
      Map -> PositionModulo(p.x, p.y);
      Hero -> SetPosition(p);
      p.z -= 50;
      Vaisseau -> SetPosition(p);
      Vaisseau -> SetAngleZ(AngleXY + 90.0f);
      //Vaisseau -> SetAngleZ(AngleXY);
      
      //Map -> LookAt(i, j, Hero -> GetPosition().z, AngleXY, 0.0f);
      Map -> Render(0, 0, 1000, 1000, EnVaisseau);
      Vaisseau -> Render(Map);
    } // end de else de «if (Envaisseau)»

    
    // *** affichage des coeurs ***
    AffichageCoeur -> Render();
    
    // *** affichage de la main ***
    AffichageMainPierre -> Render(Hero -> GetPosition().y, Map);

  } // end de «if (Map != NULL)»
  


#if 1
  if (ModeJeu == mjTELEPORTATION) {
    MoteurTeleportation.Render(Map, EnVaisseau, Hero);
  }
#endif
  
  
  SDL_GL_SwapBuffers();
   
} // RaiseRender()








void Free(void) {
  printf("On quitte le jeu et on va tranquillement désallouer TOUT!\n"); 
  
  free_actions();
  
  printf("-------- on détruit l'interface pour entrer les noms --------\n");
  delete MenuEntreeNom;
  
  printf("-------- on détruit le héros ----------------\n");
  delete Hero;
  
  printf("-------- on détruit le vaisseau ----------------\n");
  delete Vaisseau;
  
  printf("-------- on détruit le moteur d'affichage de texte ---------\n");
  delete Text;
  
  printf("-------- on détruit le moteur d'affichage de message de texte ---------\n");
  delete MessageTexte;
  
  printf("-------- on détruit la carte courante ---------\n");
  delete Map;
  
  printf("-------- on détruit le moteur d'affichage de coeurs ---------\n");
  delete AffichageCoeur;
  
  printf("-------- on détruit les sons... ---------\n");
  delete son_bouton_espace;
  delete son_bouton_saut;
  
  printf("-------- on détruit le moteur d'affichage de pierre ---------\n");
  delete AffichageMainPierre;
  
  printf("-------- on détruit la musique ---------\n");
  delete Musique;
  
  printf("-------- on détruit le moteur d'affichage de page de titre ---------\n");
  delete PageTitre;
} // Free()




void RenderCiel(const CMap * Map, float heros_y) {
  float f = Map -> IndiceTemps(heros_y);
  GLfloat couleurduciel[4] = {0.5f*f, 0.6f*f, 1.0f*f, 1.0f};
  glClearColor(couleurduciel[0], couleurduciel[1], couleurduciel[2], couleurduciel[3]);
  glFogfv(GL_FOG_COLOR, couleurduciel);
}





void RenderModeScript(void) {
  do {
    RenderModeScript_step();

    if (ModeJeu != mjSCRIPT) break;
    if (TypeInstructionCourante != ticInstructionScript) break;

  } while (true);
}

void RenderModeScript_step(void) {
  //fprintf(stderr, "Tic\n");
  //fprintf(stderr, "Tic: instruction courante = %d\n", TypeInstructionCourante);

  switch (TypeInstructionCourante) {
  case ticInstructionScript: {
    /*on place le "execute", fonction
      qui quitte dès qu'elle rencontre une instruction
      nécessitant un affichage (par exemple afficher
      un message...)
    
      Alors execute initialise les valeurs avec
      les fonctions SCRIPT_... puis c bon
      (yora après par exemple
      TypeInstructionCourante = ticAfficherMessage)
    */
    /***********************<<<<<<<<<<<<<<<<<<<<<<<ICI*/
    //script -> Execute();
    bool fini_huh = script -> execute_step();
    //fprintf(stderr, "HARO!\n");
    if (fini_huh) {
      //fprintf(stderr, " -> HARO?\n");
      ModeJeu = mjJEU;
    }
  }
    break;

  case ticWait: {
    api_contexte.nbpasses--;
    if (api_contexte.nbpasses == 0)
      TypeInstructionCourante = ticInstructionScript;
  }
    break;
    
  case ticWaitFor: {
    if (not (api_contexte.b -> IsSoumisADesOrdres()))
      TypeInstructionCourante = ticInstructionScript;
  }
    break;
    
  case ticAfficherMessage:
    if (MessageTexte -> InputAndRender()) {
      TypeInstructionCourante = ticInstructionScript;
    }
    break;

  case ticMiniMenu:
    MessageTexte -> SetMsg("Chapitre");
    MessageTexte -> Render();
  
    if (MiniMenu -> InputAndRender()) {
      script -> stack_push_int(MiniMenu -> itheta);
      TypeInstructionCourante = ticInstructionScript;
    }
    break;
  
  case ticChangerDeCarte: {
#if 1
    //fprintf(stderr, "HERE\n");
    bool teleportation_terminee_huh = false;
    MoteurTeleportation.Life(Map, EnVaisseau, Hero, teleportation_terminee_huh);
    if (teleportation_terminee_huh) {
      //fprintf(stderr, "TELEPORTATION_TERMINEE_HUH\n");
      TypeInstructionCourante = ticInstructionScript;
    }
    MoteurTeleportation.Render(Map, EnVaisseau, Hero);
#else
    //fprintf(stderr, "--TELEPORTATION_TERMINEE_HUH\n");
    delete Map;
    Map = new CMap("./village.carte", false);
    Hero -> SetPosition(10.0f, 10.0f, mpABSOLU, Map);
    TypeInstructionCourante = ticInstructionScript;
#endif
  }
    break;
  
  case ticReadln:
#if 0
    glClearColor(0.5f, 0.5f, 0.8f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif
    if (MenuEntreeNom -> InputAndRender()) {
      script -> stack_push_string(MenuEntreeNom -> buffer);
      // on rend la main au script
      //SCRIPT_SystemeRendMainAuScript = true;
      TypeInstructionCourante = ticInstructionScript;
    }
    break;

  case ticNOMBRE: assert(false); break;
  default: assert(false);
  } // switch

}











#if 0
  bool b = false;
  CPprog * prog;
  CPprog::etype type;

    prog = script -> resPascal -> getObject() -> prog_exec;
    if (prog == NULL) break;
    type = prog -> type;
    //fprintf(stderr, "TYPE = %d\n", type);
    //fprintf(stderr, "TYPE = %s\n", cprog_type_string(type));

    switch (type) {
    case CPprog::PStop:
    case CPprog::PSkip:
    case CPprog::PSeq:
    case CPprog::PIf:
    case CPprog::PWhile:
    case CPprog::PFor:
    case CPprog::PRepeat:
    case CPprog::PBegin:
    case CPprog::PVar:
    case CPprog::PConst:
    case CPprog::PAffectation:
    case CPprog::PWrite:
    case CPprog::PWriteln:
    case CPprog::PRead:
    case CPprog::PReadln:
    case CPprog::PType:
    case CPprog::PNew:
    case CPprog::PCall:
    case CPprog::PMusique:
    case CPprog::PWait:
    case CPprog::PHalt:
    case CPprog::PRestart:
    case CPprog::PFondu:
    case CPprog::PRecObjet:
    case CPprog::PRecArme:
    case CPprog::PSupObjet:
    case CPprog::PCarte:
    case CPprog::PSetPosition:
    case CPprog::PSetPositionZ:
    case CPprog::PDeplacer:
    case CPprog::PDeplacerZ:
    case CPprog::PSetHerosPosition:
    case CPprog::PSetHerosPositionZ:
    case CPprog::PHerosDeplacer:
    case CPprog::PHerosDeplacerZ:
    case CPprog::PSetCameraPosition:
    case CPprog::PCameraDeplacer:
    case CPprog::PCameraRotate:
    case CPprog::PCameraSolidariser:
    case CPprog::PCameraDesolidariser:
    case CPprog::PCameraDefaut:
    case CPprog::PCameraZoom:
    case CPprog::PFrapper:
    case CPprog::PAjouterAnime:
    case CPprog::PAjouterNonAnime:
    case CPprog::PSetTemps:
    case CPprog::PSetOrientation:
    case CPprog::PWaitFor:
    case CPprog::PBloquerTemps:
    case CPprog::PDebloquerTemps:
    case CPprog::PCarteZ:
    case CPprog::PExprStack:
    case CPprog::PIfStack:
    case CPprog::PWhileStack:
    case CPprog::PForStack:
    case CPprog::PConstStack:
    case CPprog::PAffectationStack:
    case CPprog::PCallStack:
    case CPprog::PSetTempsStack:
      b = true;
      break;

    case CPprog::PWritelnStack:
    case CPprog::PReadlnStack:
    case CPprog::PMusiqueStack:
    case CPprog::PWaitStack:
    case CPprog::PFonduStack:
    case CPprog::PRecArmeStack:
    case CPprog::PSupObjetStack:
    case CPprog::PCarteStack:
    case CPprog::PCarteZStack:
    case CPprog::PSetPositionStack:
    case CPprog::PSetPositionZStack:
    case CPprog::PDeplacerStack:
    case CPprog::PSetCameraPositionStack:
    case CPprog::PCameraRotateStack:
    case CPprog::PCameraZoomStack:
    case CPprog::PFrapperStack:
    case CPprog::PAjouterAnimeStack:
    case CPprog::PAjouterNonAnimeStack:
    case CPprog::PSetOrientationStack:
    case CPprog::PWaitForStack:
      b = false;
      break;

    default: assert(false); b = false;
    }
#endif
