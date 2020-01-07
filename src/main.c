#include "global.h"
#include "main.h"
#include "kernel.h"
#include "map.h"
#include "menu.h"
#include "bonhomme.h"
#include "son.h"
#include "text.h"
#include "objnonanime.h"
#include "coeurs.h"
#include "pagetitre.h"
#include "affichagemainpierre.h"
#include "evenement.h"
#include "action.h"
#include "apiscript.h"
#include "moteurteleportation.h"
#include "camera.h"
#include "menuentreenom.h"



static void RenderCiel(const CMap * Map, float heros_y);
static void RenderModeScript(void);
static void RenderModeScript_step(void);


static const bool ExecuterScriptDeDebut = true;

static bool MoteurPhysiqueActif = true;

static bool EnVaisseau = false;
static float AngleXY = 0;

static CMap * Map = NULL;
//static CMenuAbstrait * Menu = NULL;
static CMenu * Menu = NULL;
//CMenuAbstrait * MiniMenu = NULL; // accédé directement au sein du Pascal
CMiniMenu * MiniMenu = NULL; // accédé directement au sein du Pascal
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
  Menu = CMenu_make();
  //Menu = new CMiniMenu(100,300,200);
  Menu -> parent.NomSousMenu[0] = strcopy("Armes");
  Menu -> parent.NomSousMenu[1] = strcopy("Objets");
  Menu -> parent.NomSousMenu[2] = strcopy("Magies");

  SCRIPT_RecevoirUneArme("menu/epee");
  SCRIPT_RecevoirUneArme("menu/arc");


  printf("Création du héros\n");
  Hero = CBonhomme_make("./heros.anime");
  printf("Héros créé. Son pointeur est %p\n", Hero);
  //Hero -> SetPVMax(1/*3*7*/);
  Hero -> parent1.SetPVMax(&Hero -> parent1, 4*7);


  //initialisation de la caméra
  Camera.InitCamera(&Camera);
  Camera.SolidariserAuHeros(&Camera);
  
  Map = NULL;

  // TODO Normalement, c ici le pt de départ!
#if 1
  // *** on run le script! La fonction «début» pour être précis. ***
  if (ExecuterScriptDeDebut) {
    //fprintf(stderr, "Lancement du script de démarrage...\n");
    ModeJeu = mjSCRIPT;
    script = CScriptLauncher_make("script.pml", "debut");
    assert(script != NULL);
    script -> init_step(script);
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

  Text = CText_make();
  MessageTexte = CMessageTexte_make();
  PageTitre = CPageTitre_make();
  MenuEntreeNom = CMenuEntreeNom_make();

  //fprintf(stderr, "Init: ModeJeu = %d\n", ModeJeu);

  Musique = CMusique_make("intro.mid");
  Musique -> Jouer(Musique);
  son_bouton_espace = CSon_make("./frappe.wav");
  son_bouton_saut = CSon_make("./frappe.wav");
  //son_bouton_saut = new CSon("./plaisir.wav");

  //fprintf(stderr, "Init: ModeJeu = %d\n", ModeJeu);

  AffichageCoeur = CAffichageCoeur_make();
  AffichageMainPierre = CAffichageMainPierre_make();  

  //fprintf(stderr, "Init4: ModeJeu = %d\n", ModeJeu);

  Vaisseau = CObjNonAnime_make("vaisseau.nonanime");

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
}; 






// Procédure pour récupérer les commandes clavier et souris
void RaiseInput(void) {
  //fprintf(stderr, "ModeJeu = %d\n", ModeJeu);

  CPhysicalObj * Hero_o = &Hero -> parent1; 

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
        Hero -> Avancer(Hero, ConvertirDirectionAvecVue(DOS, Camera), Map);
      
      if (KEY_DOWN) 
        Hero -> Avancer(Hero, ConvertirDirectionAvecVue(FACE, Camera), Map);
      
      if (KEY_LEFT)
        Hero -> Avancer(Hero, ConvertirDirectionAvecVue(PROFIL_VERS_G, Camera), Map);
      
      if (KEY_RIGHT)
        Hero -> Avancer(Hero, ConvertirDirectionAvecVue(PROFIL_VERS_D, Camera), Map);
      
      if (KEY_JUMP) {
        printf("On saute. (pagedown appuyé…)\n");

        if (Hero_o -> Immerge) {
          if (Hero_o -> GetVitesse(Hero_o).z < 0) {
            Hero_o -> AddForce_vXYZ(Hero_o, 0.0f, 0.0f, 50.1f);
            son_bouton_saut -> Jouer(son_bouton_saut);
          }
          else { 
            Hero_o -> AddForce_vXYZ(Hero_o, 0.0f, 0.0f, 1.5f);
	  };
        } // if (Hero -> Immerge)
   
        else if (Hero_o -> AuSol) {
          son_bouton_saut -> Jouer(son_bouton_saut);
          Hero_o -> AddForce_vXYZ(Hero_o,0.0f, 0.0f, 180.0f);
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
        Hero_o -> AddForce_vXYZ(Hero_o, force_vaisseau*cosf(AngleXY), force_vaisseau*sinf(AngleXY), 0.0f);  
        
      if (KEY_DOWN)
        Hero_o -> AddForce_vXYZ(Hero_o, -force_vaisseau*cosf(AngleXY), -force_vaisseau*sinf(AngleXY), 0.0f);  
      
      if (KEY_VAISSEAU_UP)
        Hero_o -> AddForce_vXYZ(Hero_o, 0.0f, 0.0f, force_vaisseau_altitude);
      
      if (KEY_VAISSEAU_DOWN)
        Hero_o -> AddForce_vXYZ(Hero_o, 0.0f, 0.0f, -force_vaisseau_altitude); 
    }

     

    if (KEY_FRAPPER) {
      /*TPoint2D d = Map -> Differentiel(Hero -> GetPosition()); 
        printf("Ahhh je glisse dans la direction (%f, %f)\n", -d.x, -d.y);
        Hero -> AddForce(-d.x/3.0f, -d.y/3.0f, 0.0f);*/
      son_bouton_espace -> Jouer(son_bouton_espace);
      Hero -> Frapper(Hero);
      
      /*création d'un projectile*/
      /*CPhysicalObj* projectile = new CBonhomme("sang.anime");
   
      projectile -> SetPosition(Hero -> GetPosition() + Point3D(0.0f, 0.0f, 20.0f));
      projectile -> AddForce(50*DirectionToVecteur(Hero -> GetDirection() ) + Point3D(0.0f, 0.0f, 300.0f));
      projectile -> SetObjetEphemere(300);
      projectile -> Hostile = false;
	     
      Map -> AjouterObjet(projectile);*/
      
    }
        
      
    
    if (KEY_MENU_SYSTEME) {
      CMiniMenu_delete(MiniMenu);
      
      MiniMenu = CMiniMenu_make(100, 300,1000);         
      MiniMenu -> parent.Add(&MiniMenu -> parent, 0,"Continuer à jouer",NULL);
      MiniMenu -> parent.Add(&MiniMenu -> parent, 0,"Quitter",NULL);
      
      ModeMenuSysteme = true;
    };

  }; // if (ModeJeu == mjJEU && !ModeMenuSysteme) 
  
  
  // Qu'est-ce que ça fout là?
  // À quoi ça sert?
  // …
  // Après tests, ça permet au héros et aux ennemis de ne pas être sombres.
  // Bien.
  // Mais qu'est-ce que ça fout là?
  // Nous sommes dans la fonction «RaiseInput»!!
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
  
  if (!Menu -> parent.Canceled) {
    switch (Menu -> parent.iphi) {
    case ANNEAU_MENU_ARME: {
      CPantin * Epee = CPantin_make();
      
      if (Menu -> parent.itheta == 0)      
        Epee -> AjouterMembre(Epee, "./heros/epee.png", -0.0f, 0.0f, -22.0f, 9.0f , 32.0f, 10.0f);
      else
        Epee -> AjouterMembre(Epee, "./heros/arc.png", -0.0f, 0.0f, -22.0f, 7.0f , 37.0f, 10.0f);
      
      Hero -> parent2.SetPantinFils(&Hero -> parent2, MEMBRE_AVEC_ARME , Epee);
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
    if (PageTitre -> Life(PageTitre)) {
      ModeJeu = mjJEU;
      DebutDePartie();
    }
  }



  if (Map != NULL) {
    // on gère le temps
    Temps += marche_compression;      
    Map -> parent.SetTemps(&Map -> parent, Temps);


#if 1
    // vérifie si l'on va changer de carte…
    const CZoneTeleportation * pzt = Map -> VaTonBouger(Map, &Hero -> parent1); 
    if (pzt) 
      if (EnVaisseau || (Hero -> GetDirection(Hero) == pzt -> depart_direction))
        if (not(MoteurTeleportation.IsTeleportationEnCours(&MoteurTeleportation))) {
          CZoneTeleportation zt = *pzt;
	  
          printf("On arrive sur une zone de téléportation:\n");
          printf("Direction du héros %i, de la zone %i\n", Hero -> GetDirection(Hero), pzt -> depart_direction);
          printf("   position: (%f, %f, %f)\n", zt.position.x, zt.position.y, zt.position.z);
          ModeJeu = mjTELEPORTATION;
          SCRIPT_ChangerDeCarte_vZT(&MoteurTeleportation, zt);
        }
#endif
     

    // *** Calculs à faire avant l'affichage ***
    if (EnVaisseau) {
      Hero -> parent1.CoeffFrottementFluide = 1.0f;
      Hero -> parent1.CoeffFrottementFluideZ = 0.5f;
      Hero -> parent1.CalcNewPosition(&Hero -> parent1);
      Hero -> parent1.ValiderPosition(&Hero -> parent1, MoteurPhysiqueActif);
      Hero -> parent1.InitForce(&Hero -> parent1);
      float zcarte = Map -> parent.GETZ(&Map -> parent, Hero -> parent1.GetPosition(&Hero -> parent1).x, Hero -> parent1.GetPosition(&Hero -> parent1).y);
      float z = Hero -> parent1.GetPosition(&Hero -> parent1).z;
  
#define ZMAXVAISSEAU 200.0f
      if (z < zcarte) z = zcarte;

      if (z > ZMAXVAISSEAU) z = ZMAXVAISSEAU;

      Hero -> parent1.SetPosition_vTPoint3D(&Hero -> parent1, TPoint3D_make_struct(Hero -> parent1.GetPosition(&Hero -> parent1).x, Hero -> parent1.GetPosition(&Hero -> parent1).y, z ) );
      Camera.angleXY = AngleXY;
    }
     
    else { // pas en vaisseau

      if (ModeJeu == mjSCRIPT)
        Map -> TraiterOrdresDeplacement(Map, Hero, MoteurPhysiqueActif);
      
      if (ModeJeu == mjJEU) {
	CPhysicalObj * objetproche_o = Map -> TesterPositionHero(Map, &Hero -> parent1, MoteurPhysiqueActif); 
	CObjActionnable * objetproche = (CObjActionnable *) objetproche_o; 
        if (objetproche) 
          objetproche -> InputAndRenderActionMenu(objetproche);
      };
  
      if (Hero -> parent1.Is0PV(&Hero -> parent1)) {
        Hero -> parent1.SetPVMax(&Hero -> parent1, 4*7);
        RaiseEvenement(EVT_Mort);
      }
  
    } // fin de «if-else (en_vaisseau)»
     
    
    AffichageCoeur -> InformerNbPV(AffichageCoeur, Hero -> parent1.GetPV(&Hero -> parent1));
    AffichageCoeur -> Life(AffichageCoeur);
  }


  if (ModeJeu == mjTELEPORTATION) {
    bool teleportation_terminee_huh = false;
    MoteurTeleportation.Life(&MoteurTeleportation, &Map, &EnVaisseau, &Hero, &teleportation_terminee_huh);
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
    if (MiniMenu -> InputAndRender(MiniMenu)) {
      if (not(MiniMenu -> parent.Canceled))
        if (MiniMenu -> parent.itheta == 1)
          DemanderAQuitterLeJeu();
      
      ModeMenuSysteme = false;          
    }
  };
  
  
  if (ModeJeu == mjTITRE) {
    PageTitre -> Render(PageTitre);
    SDL_GL_SwapBuffers();
    return;
  };


  // *** affichage de l'inventaire ("menu" n'est pas un bon nom :-) ***
  if (ModeJeu == mjMENU) {
    if (Menu -> InputAndRender(Menu)) {
      gestion_menu();
      ModeJeu = mjJEU;
    }

    //fprintf(stderr, "HERE\n");
    //SDL_GL_SwapBuffers();
    //return;
  }; // mjMenu


  // *** Render en mode script ***
  if (ModeJeu == mjSCRIPT) {
    RenderModeScript();
  } 
   


  //fprintf(stderr, "Map = %p\n", Map);
  if (Map != NULL) {
    float i;
    float j;
    {
      TPoint3D pp = Hero -> parent1.GetPosition(&Hero -> parent1);
      i = pp.x;
      j = pp.y;
    }
  
    RenderCiel(Map, j);

    // !! Bien laisser cette instruction en premier sinon rien ne s'affiche… ???
    Camera.CalcCamera(&Camera, Hero, Map);
    
    Map -> parent.RenderEau(&Map -> parent, (int) i-nb_cases_afficheesX, (int) j-nb_cases_afficheesYdevant, (int) i+nb_cases_afficheesX, (int) j+nb_cases_afficheesYfond);

    if (!EnVaisseau) {
      Map -> Render(Map, (int) i-nb_cases_afficheesX, (int) j-nb_cases_afficheesYdevant, (int) i+nb_cases_afficheesX, (int) j+nb_cases_afficheesYfond, EnVaisseau);
      Hero -> Render(Hero, &Map -> parent);
    }
    else { // _en vaisseau_
      TPoint3D p;

      /* pour l'instant c un peu de la magouille:
       * j'utilise l'objet Hero en interface (histoire de pas tout rechanger)
       * et après je transfère la position de Hero sur le vaisseau
       */
      p = Hero -> parent1.GetPosition(&Hero -> parent1);
      Map -> parent.PositionModulo(&Map -> parent, &p.x, &p.y);
      Hero -> parent1.SetPosition_vTPoint3D(&Hero -> parent1, p);
      p.z -= 50;
      Vaisseau -> parent.SetPosition_vTPoint3D(&Vaisseau -> parent, p);
      Vaisseau -> SetAngleZ(Vaisseau, AngleXY + 90.0f);
      //Vaisseau -> SetAngleZ(AngleXY);
      
      //Map -> LookAt(i, j, Hero -> GetPosition().z, AngleXY, 0.0f);
      Map -> Render(Map, 0, 0, 1000, 1000, EnVaisseau);
      Vaisseau -> Render(Vaisseau, &Map -> parent);
    } // end de else de «if (Envaisseau)»

    
    // *** affichage des coeurs ***
    AffichageCoeur -> Render(AffichageCoeur);
    
    // *** affichage de la main ***
    AffichageMainPierre -> Render(AffichageMainPierre, Hero -> parent1.GetPosition(&Hero -> parent1).y, Map);

  }; // end de «if (Map != NULL)»
  


#if 1
  if (ModeJeu == mjTELEPORTATION) {
    MoteurTeleportation.Render(&MoteurTeleportation, &Map, &EnVaisseau, &Hero);
  };
#endif
  
  
  SDL_GL_SwapBuffers();
   
}; // RaiseRender()








void Free(void) {
  printf("On quitte le jeu et on va tranquillement désallouer TOUT!\n"); 
  
  free_actions();
  
  printf("-------- on détruit l'interface pour entrer les noms --------\n");
  CMenuEntreeNom_delete(MenuEntreeNom);
  
  printf("-------- on détruit le héros ----------------\n");
  CBonhomme_delete(Hero);
  
  printf("-------- on détruit le vaisseau ----------------\n");
  CObjNonAnime_delete(Vaisseau);
  
  printf("-------- on détruit le moteur d'affichage de texte ---------\n");
  CText_delete(Text);
  
  printf("-------- on détruit le moteur d'affichage de message de texte ---------\n");
  CMessageTexte_delete(MessageTexte);
  
  printf("-------- on détruit la carte courante ---------\n");
  CMap_delete(Map);
  
  printf("-------- on détruit le moteur d'affichage de coeurs ---------\n");
  CAffichageCoeur_delete(AffichageCoeur);
  
  printf("-------- on détruit les sons... ---------\n");
  CSon_delete(son_bouton_espace);
  CSon_delete(son_bouton_saut);
  
  printf("-------- on détruit le moteur d'affichage de pierre ---------\n");
  CAffichageMainPierre_delete(AffichageMainPierre);
  
  printf("-------- on détruit la musique ---------\n");
  CMusique_delete(Musique);
  
  printf("-------- on détruit le moteur d'affichage de page de titre ---------\n");
  CPageTitre_delete(PageTitre);
}; // Free()




void RenderCiel(const CMap * Map, float heros_y) {
  float f = Map -> parent.IndiceTemps(&Map -> parent, heros_y);
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
    bool fini_huh = script -> execute_step(script);
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
    if (not (api_contexte.b -> IsSoumisADesOrdres(api_contexte.b)))
      TypeInstructionCourante = ticInstructionScript;
  }
    break;
    
  case ticAfficherMessage:
    if (MessageTexte -> InputAndRender(MessageTexte)) {
      TypeInstructionCourante = ticInstructionScript;
    }
    break;

  case ticMiniMenu:
    MessageTexte -> SetMsg(MessageTexte, "Chapitre");
    MessageTexte -> Render(MessageTexte);
  
    if (MiniMenu -> InputAndRender(MiniMenu)) {
      script -> stack_push_int(script, MiniMenu -> parent.itheta);
      TypeInstructionCourante = ticInstructionScript;
    };
    break;
  
  case ticChangerDeCarte: {
#if 1
    //fprintf(stderr, "HERE\n");
    bool teleportation_terminee_huh = false;
    MoteurTeleportation.Life(&MoteurTeleportation, &Map, &EnVaisseau, &Hero, &teleportation_terminee_huh);
    if (teleportation_terminee_huh) {
      //fprintf(stderr, "TELEPORTATION_TERMINEE_HUH\n");
      TypeInstructionCourante = ticInstructionScript;
    }
    MoteurTeleportation.Render(&MoteurTeleportation, &Map, &EnVaisseau, &Hero);
#else
    //fprintf(stderr, "--TELEPORTATION_TERMINEE_HUH\n");
    CMap_delete(Map);
    Map = new CMap("./village.carte", false);
    Hero -> parent1.SetPosition(Hero -> parent1, 10.0f, 10.0f, mpABSOLU, Map);
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
    if (MenuEntreeNom -> InputAndRender(MenuEntreeNom)) {
      script -> stack_push_string(script, MenuEntreeNom -> buffer);
      // on rend la main au script
      //SCRIPT_SystemeRendMainAuScript = true;
      TypeInstructionCourante = ticInstructionScript;
    }
    break;

  case ticNOMBRE: assert(false); break;
  default: assert(false);
  } // switch

}; 











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
