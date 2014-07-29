#include "global.hpp"
#include "bonhomme.hpp"
#include "main.hpp"
#include "map.hpp"
#include "anime/anime.hpp"
#include "camera.hpp"
#include <assert.h>



#define FACT_PIXEL_OPENGL 0.38

TPoint3D DirectionToVecteur(TDirection d) {
  switch(d) {
  case DOS: return Point3D(0.0f, 1.0f, 0.0f); break;
  case FACE:  return Point3D(0.0f, -1.0f, 0.0f); break;
  case PROFIL_VERS_G:  return Point3D(-1.0f,0.0f, 0.0f); break;
  case PROFIL_VERS_D:  return Point3D(1.0f, 0.0f, 0.0f); break;
  default: assert(false);
  }      
       
  return Point3D(0.0f, 0.0f, 0.0f);
}


CPantin* CPantin::GetPantinFils(int i) {
  if (Membre[i].Pantin == NULL) {
    printf("On va créer un pantin intermédiaire au membre n° %i \n", i);
    Membre[i].Pantin = new CPantin();
  }    
    
  return Membre[i].Pantin;   
}



CPantin::CPantin() : NbMembres(0) {
  printf("Création du pantin...(pointeur = %p) \n", this); 
  for (int i = 0; i<MAX_MEMBRE; i++)
    Membre[i].Pantin = NULL;  
}

CPantin::~CPantin()  {
  printf("Destruction du pantin (CPantin::~CPantin() ) %p\n", this);                  
  for (int i = 0; i<NbMembres; i++)
    delete Membre[i].resTexture;
    
  printf("    Fin de la destruction du pantin %p\n", this);
}

int CPantin::GetNbMembres() const {
  return NbMembres;
}    


void CPantin::SetPantinFils(int i, CPantin* pantin) {
  printf("  On accroche le pantin n° %p au membre n° %i du pantin %p \n", pantin, i, this);  
  
  if (Membre[i].Pantin != NULL) {
    printf("    Destruction du pantin du membre n° %i \n", i);   
    delete Membre[i].Pantin; //on supprime au préalable l'éventuel pantin fils       
  }    
  
  Membre[i].Pantin = pantin;     
}        


void CPantin::DetruirePantinFils(int i) {
  printf("  On retire le pantin n° %p au membre n° %i du pantin %p \n", Membre[i].Pantin, i, this);
  
  delete Membre[i].Pantin;
  Membre[i].Pantin = NULL;
}



void CPantin::SetPantinFilsAuDernierMembre(CPantin* pantin) {
  SetPantinFils(NbMembres-1, pantin);
}    



void CPantin::SetAngleMembre(int i, float angle) {
  Membre[i].angle = angle;  
}    


int CPantin::AjouterMembre(const char * fichier_image,
                           float px, float py, float pz,
                           float tx, float ty, float angle)
{
  printf("  Ajout du membre (%s, %f, %f, %f, %f, %f, %f) au pantin %p\n", fichier_image,
         px,  py,  pz,
         tx,  ty,  angle, this); 
                         
  if (NbMembres >= MAX_MEMBRE) {
    printf("ERREUR : Ajout du membre impossible!!!!\n");
    return -1;
  }    
    
  int i = NbMembres;
  printf("  (Membre numéro %i)\n", i);   
  /*ma façon à moi d'ajouter un nouveau membre*/
  NbMembres++;    
    
  /*on remplit les champs...*/
  /* if (px == -1.0f)
     Membre[i].texture = NULL;
     
     else*/
  {
    Membre[i].resTexture = gestionTexture.prendre(fichier_image);
    Membre[i].taille_x = tx / Membre[i].resTexture -> getObject() -> taillex;
    Membre[i].taille_y = ty / Membre[i].resTexture -> getObject() -> tailley;
  }    
  printf("arf\n");
  Membre[i].px = px*FACT_PIXEL_OPENGL;
  Membre[i].py = py*FACT_PIXEL_OPENGL;
  Membre[i].pz = pz*FACT_PIXEL_OPENGL;
  Membre[i].taille_pixelx = tx;
  Membre[i].taille_pixely = ty;
  printf("arf2\n");
    
  printf("arf3\n");
  Membre[i].angle_max = angle;
  Membre[i].Pantin = NULL;
    
  printf("  Fin de l'ajout du membre réussi !!\n");

  return i;
}    




CBonhomme::CBonhomme(const char * filename) : CPhysicalObj(filename),
                                              iangle(0), sens_iangle(1),
                                              Direction(PROFIL_VERS_D), Etat(ebPretAMarcher), EtapeEtat(0),
                                              invinsible_etape(0),
                                              filename(strcopy(filename))
{
  //fprintf(stderr, "Bonhomme: Constructeur: %s - pv = %d\n", filename, pv);

  Compressible = false;
  Fixe = false;
  Hostile = true;
  printf("Création d'un petit bonhomme...\n"); 
   
  // si jamais on ne donne pas de nom de fichier, alors on ne charge pas de script
  if (filename == NULL) return;
   
  ViderOrdresDeplacement();
  
  int ret = LireAnime(ANIMESDIR, filename, this);


  char * reelfile;
  reelfile = new char[strlen(ANIMESDIR) + strlen(filename) + 1];
  strcat(strcpy(reelfile, ANIMESDIR), filename);
  filename = reelfile;



  if (0 == ret) {
    printf("ANIME: Lecture réussie du fichier %s !\n", filename);
  }
  else {
    printf("ANIME: Lecture avec erreur du fichier %s .\n", filename);
    assert(false);
  }
   
  delete[] reelfile;

  //fprintf(stderr, "Bonhomme: Constructeur: %s - pv = %d\n", filename, pv);
};


CBonhomme::~CBonhomme(void) {
  printf("Destruction du bonhomme (CBonhomme::~CBonhomme() ) %p\n", this); 
};


void CBonhomme::TexCoord(int i, float tx, float ty) const {
  TDirection direction_affichee = ConvertirDirectionAvecVue2(Direction, Camera);

  if (PROFIL_VERS_G == direction_affichee)
    glTexCoord2f(PROFIL_VERS_D * Membre[i].taille_x + (1-tx) * Membre[i].taille_x, ty * Membre[i].taille_y);

  else
    glTexCoord2f(direction_affichee * Membre[i].taille_x + tx * Membre[i].taille_x, ty * Membre[i].taille_y);
    
}    



void CBonhomme::AfficherPantin(const CPantin * pantin) const {
  if (pantin == NULL)
    return;
      
  //printf("Affichage du pantin n° %i \n", pantin);
      
  /*le gars regarde dans la direction x*/
  for (int i = 0; i<pantin -> GetNbMembres(); i++) {
      //printf("Affichage du membre n° %i\n", i);
      float a = pantin -> Membre[i].angle;
        
      //        if (pantin -> Membre[i].texture != NULL) 
      pantin -> Membre[i].resTexture -> getObject() -> GLTextureCourante();   
        
        
      glPushMatrix();
      
      TDirection direction_affichee = ConvertirDirectionAvecVue2(Direction, Camera); 
      
      if ((direction_affichee == PROFIL_VERS_G) || (direction_affichee == PROFIL_VERS_D))
        glTranslatef(pantin -> Membre[i].px,pantin -> Membre[i].py*0.05f, pantin -> Membre[i].pz);
      else
        glTranslatef(pantin -> Membre[i].px,pantin -> Membre[i].py, pantin -> Membre[i].pz);
      
      glRotatef(a, 0.0f, 1.0f, 0.0f);
#define TX pantin -> Membre[i].taille_pixelx*FACT_PIXEL_OPENGL
#define TY pantin -> Membre[i].taille_pixely*FACT_PIXEL_OPENGL
         
      glBegin(GL_QUADS);
         
           
      
      if ((direction_affichee == PROFIL_VERS_D))
        {
          TexCoord(i, 0.0f, 0.0f);
          glVertex3f(-TX, 0.0f, 0.0f);
               
          TexCoord(i, 1.0f, 0.0f);
          glVertex3f(TX, 0.0f, 0.0f);
                    
          TexCoord(i, 1.0f, 1.0f);
          glVertex3f(TX, 0.0f, -TY);
               
          TexCoord(i, 0.0f, 1.0f);
          glVertex3f(-TX, 0.0f, -TY);
        }    
            
            
      if ((direction_affichee == PROFIL_VERS_G))
        {
          TexCoord(i, 0.0f, 0.0f);
          glVertex3f(TX, 0.0f, 0.0f);
               
          TexCoord(i, 1.0f, 0.0f);
          glVertex3f(-TX, 0.0f, 0.0f);
                    
          TexCoord(i, 1.0f, 1.0f);
          glVertex3f(-TX, 0.0f, -TY);
               
          TexCoord(i, 0.0f, 1.0f);
          glVertex3f(TX, 0.0f, -TY);
        }   
            
      if (direction_affichee == FACE)
        {
          TexCoord(i, 0.0f, 0.0f);
          glVertex3f(0.0f, -TX, 0.0f);
               
          TexCoord(i, 1.0f, 0.0f);
          glVertex3f(0.0f, TX, 0.0f);
                    
          TexCoord(i, 1.0f, 1.0f);
          glVertex3f(0.0f, TX, -TY);
               
          TexCoord(i, 0.0f, 1.0f);
          glVertex3f(0.0f, -TX, -TY);
        }    
            
      if (direction_affichee == DOS)
        {
          TexCoord(i, 0.0f, 0.0f);
          glVertex3f(0.0f, TX, 0.0f);
               
          TexCoord(i, 1.0f, 0.0f);
          glVertex3f(0.0f, -TX, 0.0f);
                    
          TexCoord(i, 1.0f, 1.0f);
          glVertex3f(0.0f, -TX, -TY);
               
          TexCoord(i, 0.0f, 1.0f);
          glVertex3f(0.0f, TX, -TY);
        } 
            
              
        
      glEnd(); 
         
      AfficherPantin(pantin -> Membre[i].Pantin);
         
      glPopMatrix(); 
           
            
             
    }    
    
    
}    



void CBonhomme::Frapper(void) {
  if (Etat == ebFrapper) return;
  Etat = ebFrapper;
  EtapeEtat = 0; 
}    


bool CBonhomme::EnTrainDeFrapper(void) const {
  return Etat == ebFrapper;
}    

void CBonhomme::Render(const CSol * Map) {
#if 0
  //fprintf(stderr, "HERE\n");
  if (0 != strcmp(filename, "./heros.anime")) {
    fprintf(stderr, "Bonhomme: Rendering: %s\n", filename);
    fflush(NULL);
  }
#endif

  CPhysicalObj::Render(Map);

  glEnable(GL_TEXTURE_2D);
  glDisable(GL_CULL_FACE); {
    
    // on anime le pantin en donnant les angles des membres
    for (int i = 0; i<GetNbMembres(); i++)
      SetAngleMembre(i, Membre[i].angle_max * iangle / MAX_IND_ANGLE);

    GetPantinFils(MEMBRE_AVEC_ARME) -> SetAngleMembre(0, -150); 
    
           
    if (Etat == ebFrapper) {
#define NB_ETAPE_ETAT 8
      iangle = 0;
      SetAngleMembre(MEMBRE_AVEC_ARME, -220*(2*NB_ETAPE_ETAT - EtapeEtat) / (3*NB_ETAPE_ETAT));
      GetPantinFils(MEMBRE_AVEC_ARME) -> SetAngleMembre(0, -90*(NB_ETAPE_ETAT - EtapeEtat) / (NB_ETAPE_ETAT)) ;
      EtapeEtat++;
      
      if (EtapeEtat > NB_ETAPE_ETAT) {
        Etat = ebPretAMarcher;
        EtapeEtat = 0;
      }
    }
    
    // clignotement quand on est invinsible
    if (invinsible_etape > 0) invinsible_etape--;
    if (invinsible_etape % 2 == 1) return;
    
  
    glPushMatrix(); {
      Map -> MatricePour2D(p.x, p.y, p.z);
      glRotatef(90.0f*Direction, 0.0f, 0.0f, 1.0f);
      //glRotatef(90.0f*Direction + 90.0f*((int) (2.0f * (Camera.angleXY - PI/4.0f) / PI)), 0.0f, 0.0f, 1.0f);
      
      AfficherPantin(this);
      
    } glPopMatrix();
    
    
    iangle += NormeVitesse()*sens_iangle*2.0f;
    if (Immerge)
      iangle += 1.0f*sens_iangle; //dans l'eau on bouge (on nage)
    else if (NormeVitesse() < 0.1f)
      iangle = 0;
    
    if (iangle >= MAX_IND_ANGLE)
      sens_iangle = -1;
    
    if (iangle <= -MAX_IND_ANGLE)
      sens_iangle = 1;      
  
  } glEnable(GL_CULL_FACE);  
};    



void CBonhomme::SetDirection(TDirection NouvelleDirection) {
  if ((NouvelleDirection < 0) || (NouvelleDirection > 3))
    printf("ERREUR : Direction spécifiée incorrecte\n");
  else
    Direction = NouvelleDirection;
}


TDirection CBonhomme::GetDirection(void) const {
  return Direction;
}


//void CBonhomme::Avancer(TDirection Direction, float FacteurCompression)
void CBonhomme::Avancer(TDirection Direction, const CMap * Map) {
  /*on n'avance pas si on frappe par exemple
    ATTENTION: cela n'empêche pas que le gars soit poussé s'il frappe car
    les poussages se font directement via AddForce
    Avancer n'est appelé que par les commandes*/
  if (Etat != ebPretAMarcher)
    return;
  
  float FacteurCompression;
  FacteurCompression = Map -> FacteurCompression(GetPosition().y);

#define force_marche 0.8f
  switch (Direction) {
  case DOS:  AddForce(0.0f,  force_marche, 0.0f); break;
  case FACE: AddForce(0.0f, -force_marche, 0.0f); break;
  case PROFIL_VERS_G: AddForce(- force_marche / FacteurCompression, 0.0f, 0.0f); break;
  case PROFIL_VERS_D: AddForce(  force_marche / FacteurCompression, 0.0f, 0.0f); break;
  default: assert(false);
  }
    
  SetDirection(Direction);
}




bool CBonhomme::EstInvinsible(void) const {
  return (invinsible_etape > 0);    
}

void CBonhomme::DevenirInvinsible(int nbetape) {
  invinsible_etape = nbetape;
}    


void CBonhomme::AjouterOrdresDeplacement(TPoint3D pos) {
  printf("CBonhomme::AjouterOrdresDeplacement(TPoint3D pos)\n");   
  printf("On ajoute un ordre de déplacement au bonhomme %p vers le point (%f, %f, %f).\n", this, pos.x, pos.y, pos.z);
#define epsilon 0.2f
   
  if (fabs(p.x - pos.x) > epsilon) {
      COrdreDeplacement * od = new COrdreDeplacement;
      od -> destination = pos;
      if (p.x  < pos.x)
        od -> direction =  PROFIL_VERS_D;
      else
        od -> direction =  PROFIL_VERS_G;
            
      printf("    minidéplacement de direction %i\n", od -> direction);
      liste.Empiler_sans_copie(od);  
    }
   
  if (fabs(p.y - pos.y) > epsilon) {
      COrdreDeplacement * od = new COrdreDeplacement;
      od -> destination = pos;
      if (p.y  < pos.y)
        od -> direction =  DOS;
      else
        od -> direction =  FACE;     
            
      printf("    puis minidéplacement de direction %i\n", od -> direction);
      liste.Empiler_sans_copie(od);
    }

  // rem: on s'en fout de pos.z…
}


void CBonhomme::AjouterOrdresDeplacement(float x, float y, TMethodePlacement mp) {
  TPoint3D pos = GetPosition(); 
   
  if (mp == mpABSOLU) {
    pos.x = x; pos.y = y;
  }
  else {
    pos.x += x; pos.y += y;
  }
       
  AjouterOrdresDeplacement(pos);
}


void CBonhomme::ViderOrdresDeplacement(void) {
  liste.Vider(); 
}


void CBonhomme::TraiterOrdresDeplacement(const CMap * Map, const bool MoteurPhysiqueActif) {
  COrdreDeplacement * od = liste.PremierElement();
    
  if (od) {
    printf("ordre de déplacement qu'on traite : %p (%i) \n", od, od -> direction); 
    
#define epsilon 0.2f
    bool b;
    
    switch (od -> direction) {
    case DOS: case FACE: b = fabs(od -> destination.y - p.y) < epsilon; break;
    case PROFIL_VERS_G: case PROFIL_VERS_D: b = fabs(od -> destination.x - p.x) < epsilon; break;
    default: b = true; assert(false); // C koi le bon `b' dans ce cas ?
    }
    
    InitForce();
    CoeffFrottementFluide = 1.0f; 
    CoeffFrottementFluideZ = 0.0f; 
    
    if (b) {
      printf("C'est bon le bonhomme %p arrête le mini-déplacement vers %i.\n", this, od -> direction);
      liste.Depiler();
    }
    else
      Avancer(od -> direction, Map);
    
    
    CalcNewPosition(); 
    TesterSol(Map);  
    ValiderPosition(MoteurPhysiqueActif);
    InitForce();     
  }
}




bool CBonhomme::IsSoumisADesOrdres() {
  return !liste.IsVide(); 
}




