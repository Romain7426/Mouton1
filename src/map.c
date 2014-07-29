#include "global.hpp"
#include "map.hpp"
#include "physicalobj.hpp"
#include "objnonanime.hpp"
#include "bonhomme.hpp"
#include "evenement.hpp"


#ifdef VOISINAGE_IS_TAB
static int voisinage_nbelt(const CMap * map, int iii);
static void voisinage_ajouter(CMap * map, int iii, CPhysicalObj * o);
static void voisinage_detruire(CMap * map, int iii, int jjj);
#endif


#define taille_case 5
#define nb_voisinage_traitee 3
#define nb_voisinage_traitee_toutproche 1

#ifdef VOISINAGE_IS_TAB

#define PARCOURS_OBJETS                                         \
  if (Voisinages != NULL)                                       \
    for (int iii = 0; iii < maxindvoisinages; iii++)            \
      for (int jjj = 0; jjj < VOISINAGE_TAILLE; jjj++)          \
        {                                                       \
          CPhysicalObj * o_parcours = Voisinages[iii][jjj];     \
          if (o_parcours == NULL)                               \
            continue;

#else

#define PARCOURS_OBJETS                                                 \
  if (Voisinages != NULL)                                               \
    for (int iii = 0; iii < maxindvoisinages; iii++)                    \
      for (CAccesseur<CPhysicalObj> a = Voisinages[iii].Objets.ObtenirAcces(); !a.IsFin(); a.AllerSuivant()) \
        {                                                               \
          CPhysicalObj * o_parcours = a.Element();                      \
          if (o_parcours == NULL)                                       \
            continue;

#endif


#define PARCOURS_OBJETS_FIN }




#define PARCOURS_ZONESTELEPORTATIONS                                    \
  for (CAccesseur<CZoneTeleportation> a = ZonesTeleportation.ObtenirAcces(); not(a.IsFin()); a.AllerSuivant())


//#define maxindvoisinages_fun(ttt) ((((int) (((ttt) -> TailleX) / taille_case)) + 1) * (((int) (((ttt) -> TailleY) / taille_case)) + 1))
#define maxindvoisinages_fun(ttt) ((((int) (((ttt) -> TailleX) / taille_case))) * (((int) (((ttt) -> TailleY) / taille_case))))
#define maxindvoisinages  maxindvoisinages_fun(this)
#define maxindvoisinages2 maxindvoisinages_fun(map)


// On affiche la case sur laquelle nous sommes
// et les cases à rayon de nbnb
// ainsi que le voisinage trivial (indicé 0)
#define PARCOURS_OBJETS_VOISINAGES(pos_A, nbnb_A)                         \
  {                                                                     \
    const TPoint3D pos_ = (pos_A);                                             \
    int nbnb_ = (nbnb_A);                                                 \
    int current_case_ix = (int) (((real) pos_.x) / ((real) taille_case)); \
    int current_case_iy = (int) (((real) pos_.y) / ((real) taille_case)); \
    for (int biz = 0; biz <= 1; biz++)                                  \
      for (int ix = biz*(current_case_ix - nbnb_); ix <= biz*(current_case_ix + nbnb_); ix++) \
        if (ix >= 0)                                                    \
          for (int iy = biz*(current_case_iy - nbnb_); iy <= biz*(current_case_iy + nbnb_); iy++) \
            if (iy >= 0)                                                \
              {                                                         \
                int iii = ix + iy * ((int) (((real) TailleX) / ((real) taille_case))); \
                if ((iii >= 0) && (iii < maxindvoisinages))             \
                  {                                                     \
                    iii += biz;                                         \
                    if (Voisinages != NULL)                             \
                      for (CAccesseur<CPhysicalObj> a = Voisinages[iii].Objets.ObtenirAcces(); not(a.IsFin()); a.AllerSuivant()) \
                        {                                               \
                          CPhysicalObj * o_parcours = a.Element();      \
                          if (o_parcours == NULL)                       \
                            continue;



#define PARCOURS_OBJETS_VOISINAGES_PROCHE(pos)     PARCOURS_OBJETS_VOISINAGES(pos, nb_voisinage_traitee)
#define PARCOURS_OBJETS_VOISINAGES_TOUTPROCHE(pos) PARCOURS_OBJETS_VOISINAGES(pos, nb_voisinage_traitee_toutproche)

/*\
  int ppppx = (pos).x; int ppppy = (pos).y; \
  for (int biz = 1; biz<= 1; biz++)                                     \
  for (int ix = biz*(ppppx / taille_case - nb_voisinage_traitee); ix <= biz*(ppppx / taille_case + nb_voisinage_traitee); ix++) \
  for (int iy = biz*(ppppy / taille_case - nb_voisinage_traitee); iy <= biz*(ppppy / taille_case + nb_voisinage_traitee); iy++) \
  { \
  int iii = (iy *TailleX/ taille_case + ix + 1)*biz; \
  if ((iii >= biz*1) && (iii < maxindvoisinages))                       \
  for (CAccesseur<CPhysicalObj> a = Voisinages[iii].Objets.ObtenirAcces(); !a.IsFin(); a.AllerSuivant())
*/
#define PARCOURS_OBJETS_VOISINAGES_FIN }}}}



CZoneTeleportation::CZoneTeleportation(TPoint3D in_position, TPoint3D in_dimension, TDirection in_depart_direction, const char * in_destination_carte, TPoint3D in_destination_position, TDirection in_destination_direction) {
  position = in_position;
  dimension = in_dimension;
  depart_direction = in_depart_direction;

  destination_carte = strcopy(in_destination_carte);
  destination_position = in_destination_position;
  destination_direction = in_destination_direction;
}



CMap::CMap(const char * filename, const bool EnVaisseau) : CSol(EnVaisseau), NomCarte(strcopy(filename)) {
  if (filename == NULL) return;

#if 1
  ViderEvenement(EVT_ChargementCarte);
  ViderEvenement(EVT_EntreeSurCarte);
  ViderEvenement(EVT_PlusEnnemi);
#endif

  printf("Constructeur CMap(%s)\n", filename);

  char * reelfile;
  reelfile = STRCAT2_(CARTESDIR, filename);
  printf("nom de fichier réel: %s\n", reelfile);

  // Nous devons attendre avant de l'allouer car nous avons besoin de TailleX et TailleY (donc attendre le ChargerZ)
  Voisinages = NULL;

  int ret = parse(CARTESDIR, filename);
  if (ret){
    messerr("pas bonne analyse du fichier \"%s\".", reelfile);
    assert(false);
  }
  else {
    message("analyse ok du fichier \"%s\".", reelfile);
  }


  printf("Fin de la construction CMap::CMap()\n");

  delete reelfile;
}


CMap::~CMap(void) {
  printf("Destruction de la carte %p\n", this);

  delete[] Voisinages;
  // TextureSol, Objets, ZonesTeleportation sont détruits automatiquement car ce ne sont pas des pointeurs
}


const char * CMap::GetNomCarte(void) const {
  return NomCarte;
}



void CMap::Render(const int i1, const int j1, const int i2, const int j2, const bool EnVaisseau) {
  // on affiche le sol (on appelle la fonction Render de la classe CSol dont hérite CMap)
  CSol::Render(i1, j1, i2, j2);

#if 0
  TPoint3D pos;
  pos.x = (i1 + i2) / 2;
  pos.y = (j1 + j2) / 2;
#else
  const TPoint3D pos = {(i1 + i2) / 2, (j1 + j2) / 2, 0., 0.};
#endif

  if (not(EnVaisseau)) {

    PARCOURS_OBJETS_VOISINAGES_PROCHE(pos)
    //PARCOURS_OBJETS
      {
#if 0
        int i = (int) a.Element()->GetPosition().x;
        int j = (int) a.Element()->GetPosition().y;
#else
        int i = (int) o_parcours->GetPosition().x;
        int j = (int) o_parcours->GetPosition().y;
#endif

#if 0
        const char * filename = o_parcours -> filename;
        if (filename != NULL)
          if (0 != strcmp(filename, "./heros.anime")) {
            fprintf(stderr, "ObjPhys: Rendering: %s\n", filename);
            fflush(NULL);
          }
        //fprintf(stderr, "iii = %d - jjj = %d - ", iii, jjj);
#endif

#if 1
        //bool test = ((i1 <= i) && (i <= i2) && (j1 <= j) && (j <= j2));
        //if (test)
        if (CBonhomme * b = dynamic_cast<CBonhomme *>(o_parcours)) {
          //fprintf(stderr, "Bonhomme: Rendering: %s\n", b -> filename);
          b -> Render(this);
        }
        else if (CObjNonAnime * nonanime = dynamic_cast<CObjNonAnime *>(o_parcours)) {
          nonanime -> Render(this);
        }
        else
#endif
          o_parcours -> Render(this);

      }
    //PARCOURS_OBJETS_FIN;
    PARCOURS_OBJETS_VOISINAGES_FIN;

  }

  else { // _ en vaisseau _
    PARCOURS_OBJETS
      {
#if 0
        int i = (int) a.Element()->GetPosition().x;
        int j = (int) a.Element()->GetPosition().y;
#endif
        int i = (int) o_parcours->GetPosition().x;
        int j = (int) o_parcours->GetPosition().y;


        bool b = ((i1 <= i) && (i <= i2) && (j1 <= j) && (j <= j2));
        if (b)
          o_parcours->Render(this);
      }
    PARCOURS_OBJETS_FIN;
  }



  {
    //fprintf(stderr, "ZoneTeleportationBlit\n");
    //int i = 0;
    PARCOURS_ZONESTELEPORTATIONS
      {
        //fprintf(stderr, "ZoneTeleportationRender: i = %d\n", i++);

        CZoneTeleportation * o = a.Element();
        
        AfficherCube(o->position.x, o->position.y, o->position.z, o->dimension.x, o->dimension.y, o->dimension.z);
      }
  }

}




void CMap::ChargerZ(const char * filename) {
  printf("CMap::ChargerZ(%s)\n", filename);
  CSol::ChargerZ(filename);


#ifndef VOISINAGE_IS_TAB
  // On ne peut l'allouer que maintenant car nous avons besoin de TailleX et TailleY
  Voisinages = new TVoisinage[maxindvoisinages + 1];
#if 0
  for (int i = 0; i < (maxindvoisinages + 1) ; i++) {
    //Voisinages[i].Objets = NULL;
    fprintf(stderr, "Voisinages[%d]: %p\n", i, Voisinages[i].Objets.debutliste);
  }
#endif
#else
  Voisinages = new CPhysicalObj * [maxindvoisinages + 1][VOISINAGE_TAILLE];
  for (int i = 0; i < (maxindvoisinages + 1); i++)
    for (int j = 0; j < VOISINAGE_TAILLE; j++)
      Voisinages[i][j] = NULL;
#endif

  printf(" fin CMap::ChargerZ(%s)\n", filename);
}




void CMap::AjouterObjet(CPhysicalObj * o) {
  printf("Ajout de l'objet physique (pointeur: %p; filename: %s) à la carte\n", o, o == NULL ? NULL : o -> filename);

  assert(Voisinages != NULL); // ChargerZ doit avoir lieu auparavant!

  {
    int nbelts;
#ifndef VOISINAGE_IS_TAB
    nbelts = 0;
    PARCOURS_OBJETS
      nbelts ++;
    PARCOURS_OBJETS_FIN;
#else
    nbelts = voisinage_nbelt(this, 0);
#endif
    fprintf(stdout, "Ajout de l'objet physique %p (%s) - nb objets = %u\n", o, o -> filename, nbelts);
  }

  if (CBonhomme * b = dynamic_cast<CBonhomme *>(o)) {
    fprintf(stdout, "Ajout de Bonhomme: Adding: %s\n", b -> filename);
  }




  TPoint3D pos = o -> GetPosition();

  pos.z = GETZ(pos.x, pos.y);
  o -> SetPosition(pos);


#if 1
  printf("Taille de la carte en real: %d x %d\n", TailleX, TailleY);
  printf("Taille de la carte en case: %d x %d\n", ((int) (TailleX / taille_case)), ((int) (TailleY / taille_case)));
  printf("Position de l'objet: %f x %f\n", pos.x, pos.y);
  printf("Coordonnées de la case contenant l'objet: %d x %d\n", ((int) (pos.x / taille_case)), ((int) (pos.y / taille_case)));



  if (o -> Fixe) {
    //int iii = ((int) (pos.y / taille_case)) * ((int) (TailleX / taille_case)) + ((int) pos.x / taille_case);
    int iii = ((int) (pos.x / taille_case))  +  ((int) (pos.y / taille_case)) * ((int) (TailleX / taille_case));

    if ((iii < 0) || (iii >= maxindvoisinages))
      iii = -1; // un +1 est fait ensuite, donc tout va bien :-)

    printf("On ajoute dans le voisinage n° %i (coord. x = %f, y %f)\n", iii, pos.x, pos.y);
#ifndef VOISINAGE_IS_TAB
    Voisinages[iii+1].Objets.Empiler_sans_copie(o);
#else
    voisinage_ajouter(this, iii+1, o);
#endif
  }

  else {
    printf("On ajoute dans le voisinage trivial.\n");
#ifndef VOISINAGE_IS_TAB
    Voisinages[0].Objets.Empiler_sans_copie(o);
#else
    voisinage_ajouter(this, 0, o);
#endif
  }



#else



#ifndef VOISINAGE_IS_TAB
  Voisinages[0].Objets.Empiler_sans_copie(o);
#else
  voisinage_ajouter(this, 0, o);
#endif



#endif

  printf("Ajout de l'objet physique réussi!!\n");
}



void CMap::AjouterObjet(const char * nom, CPhysicalObj * o) {
  printf("Ajout de l'objet physique (pointeur %p) à la carte, de nom %s \n", o, nom);
  AjouterObjet(o);

  DicoObjets.Set(nom, o);
  printf("Ajout de l'objet physique réussi !!\n");
}



CPhysicalObj * CMap::RetrouverObjetViaSonNom(const char * nom) {
  return DicoObjets.Get(nom);
}



/* exemple d'utilisation

   TPoint3D pos, dim, posdest;

   pos = Point3D(0.0f, 0.0f,0.0f);
   dim = Point3D(2.0f, 2.0f, 128.0f);
   posdest = Point3D(0.0f, 4.0f, 0.0f);

   Map -> AjouterZoneTeleportation(pos, dim, DOS, "carte.carte", posdest, DOS);
*/
void CMap::AjouterZoneTeleportation(TPoint3D position, TPoint3D dimension, TDirection depart_direction, const char * destination_carte, TPoint3D destination_position, TDirection destination_direction) {
  CZoneTeleportation * o = new CZoneTeleportation(position, dimension, depart_direction, destination_carte, destination_position, destination_direction);

  printf("Ajout d'une zone de téléportation \n");
  printf(" position: (%f, %f, %f)\n", position.x, position.y, position.z);
  printf(" dimension: (%f, %f, %f)\n", dimension.x, dimension.y, dimension.z);
  ZonesTeleportation.Empiler_sans_copie(o);
}



void CMap::AjouterParticules(TPoint3D p, const char * nom, const bool MoteurPhysiqueActif) {
#define NB_PARTICULES 10
  printf("Ajout d'une flopée de particules au point (%f, %f, %f,) \n...", p.x, p.y, p.z);

#ifdef NB_PARTICULES
  for (int i = 0; i<NB_PARTICULES; i++) {

    CPhysicalObj * o = new CBonhomme(nom);
    o->SetDimension(0.0f,0.0f,0.0f);

    o->SetPosition(p);
    o->SetObjetEphemere(32);
    o->Hostile = false;
    TPoint3D pp = o->GetPosition();
    printf("Coordonnée des particules : (%f, %f, %f,) \n", pp.x, pp.y, pp.z);
    o->InitForce();

#define GENPOS ((float) (rand()%2000-1000)) / 200.0f
    o->AddForce(GENPOS,GENPOS,100.0f );
    o->CalcNewPosition();
    o->ValiderPosition(MoteurPhysiqueActif);
    AjouterObjet(o);

  }
#endif

  printf("Ajout des particules effectuées!\n");

}




TDirection DirectionAleatoire(void) {
  return (TDirection) (rand() % 4);
}



CZoneTeleportation * CMap::VaTonBouger(CPhysicalObj* aHero) {
  TPoint3D p = aHero->GetPosition();

  PARCOURS_ZONESTELEPORTATIONS
    {
      CZoneTeleportation* o = a.Element();

      if ((o->position.x <= p.x) &&
          (o->position.y <= p.y) &&
          (o->position.z <= p.z) &&
          (p.x <= o->position.x + o->dimension.x) &&
          (p.y <= o->position.y + o->dimension.y) &&
          (p.z <= o->position.z + o->dimension.z) )
        return o;

    }

  return NULL;
}




void CMap::TraiterOrdresDeplacement(CBonhomme * aHero, const bool MoteurPhysiqueActif) {
  aHero -> TraiterOrdresDeplacement(this, MoteurPhysiqueActif);

  PARCOURS_OBJETS
    {
#if 0
      CBonhomme * b = dynamic_cast<CBonhomme *>(a.Element());
#else
      CBonhomme * b = dynamic_cast<CBonhomme *>(o_parcours);
#endif

      if (b) {
        b -> TraiterOrdresDeplacement(this, MoteurPhysiqueActif);
      }
    }
  PARCOURS_OBJETS_FIN;

}



/*on informe la carte de la position du héro

  en retour, elle nous offre un pointeur vers l'élément le plus proche
  OU NULL si trop loin
*/
// En fait cette fonction est le moteur physique…………
CPhysicalObj * CMap::TesterPositionHero(CPhysicalObj * aHero, const bool MoteurPhysiqueActif) {

  CBonhomme * Hero = dynamic_cast<CBonhomme *>(aHero);

  TesterPosition(Hero, MoteurPhysiqueActif);
  Hero->ValiderPosition(MoteurPhysiqueActif);
  Hero->InitForce();


  // on fait bouger les objets
  PARCOURS_OBJETS
    {
      if (CBonhomme* b = dynamic_cast<CBonhomme *>(o_parcours)) {
        if (rand() % 20 == 1)
          b->SetDirection(DirectionAleatoire());

        b->Avancer(b->GetDirection(), this);
      }

      if (!(o_parcours->Fixe)) {
        TesterPosition(o_parcours, MoteurPhysiqueActif);
        if (!o_parcours->TesterPosition(this, Hero)) {
          if (o_parcours->Hostile)
            if (not(Hero->EstInvinsible())) {
              //le héros se fait toucher par un ennemi
              Hero->PerdrePV(5);
              Hero->DevenirInvinsible(200);
            }
        }
        o_parcours->ValiderPosition(MoteurPhysiqueActif);
        o_parcours->InitForce();
      }
    }
  //FIN_PARCOURS_OBJETS_VOISINAGES;
  PARCOURS_OBJETS_FIN;


  // la phsyique de l'épée
#if 1
  {
    if (Hero->EnTrainDeFrapper()) {
      CPhysicalObj zoneepee = (*aHero);
      TPoint3D d = Hero->GetDimension(this);
      zoneepee.SetDimension(d.x, d.y, d.z);

      TPoint3D dir;
      switch (Hero->GetDirection()) {
      case FACE: dir = Point3D(0.0f, -1.0f, 0.0f); break;
      case DOS: dir = Point3D(0.0f, 1.0f, 0.0f); break;
      case PROFIL_VERS_D: dir = Point3D(1.0f, 0.0f, 0.0f); break;
      case PROFIL_VERS_G: dir = Point3D(-1.0f, 0.0f, 0.0f); break;
      default: assert(false);
      }

      zoneepee.SetPosition(Hero->GetPosition() + dir);

      //PARCOURS_OBJETS_VOISINAGES_PROCHE(Hero->GetPosition())
      PARCOURS_OBJETS
        {
          CBonhomme* b = dynamic_cast<CBonhomme *> (o_parcours);

          if (b && (!b->IsVolumeNul()))
            if ((!(b->TesterPosition(this, &zoneepee))) && (!(b->EstInvinsible()))) {
              //on a frappé a.Element()
              printf("Le héros a frappé un bonhomme\n");
              b->PerdrePV(1);
              AjouterParticules(b->GetPosition(), "sang.anime", MoteurPhysiqueActif);
              b->AddForce(10.0f*dir);
              b->DevenirInvinsible(50);
            }

        }
      //FIN_PARCOURS_OBJETS_VOISINAGES;
      PARCOURS_OBJETS_FIN;
    }
  }
#endif

  // on enlève les éléments qui n'ont plus de vie
  PARCOURS_OBJETS
    {
      if (not(o_parcours -> Fixe) && o_parcours -> Is0PV()) {
#ifndef VOISINAGE_IS_TAB
        a.DetruireElementCourant();
#else
        voisinage_detruire(this, iii, jjj);
#endif
      }
    }
  PARCOURS_OBJETS_FIN;




  // on trouve l'élément le plus proche
  CPhysicalObj * elementproche = NULL;
  {
#define norme_minimum_pour_etre_proche 50.0f
    float norme_du_proche = norme_minimum_pour_etre_proche;

    PARCOURS_OBJETS
      {
        float norme_courante = Norme1(o_parcours->GetPosition() - Hero->GetPosition());

        if (norme_courante < norme_du_proche) {
          norme_du_proche = norme_courante;
          elementproche = o_parcours;
        }
      }
    PARCOURS_OBJETS_FIN;
  }


  return elementproche;
  return NULL;



  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


  //CPhysicalObj * elementproche = NULL; /*ce qu'on rend à la fin de cette fonction*/


  // on nettoie la liste des objets... on vire ceux qui ont 0 PV
  bool unennemiestdecede = false;
  int nb_ennemis = 0;
  float norme_du_proche = norme_minimum_pour_etre_proche;
  PARCOURS_OBJETS
    {

      //fprintf(stderr, "ACC: courant: %p - precedent: %p - liste: %p\n", a.pointeurcourant, a.pointeurprecedent, a.maliste);
      if (o_parcours->Is0PV()) {
        if (o_parcours->Hostile)
          unennemiestdecede = true;
#ifndef VOISINAGE_IS_TAB
        a.DetruireElementCourant();
#else
        voisinage_detruire(this, iii, jjj);
#endif
      }
      else {
        if (o_parcours->Hostile) nb_ennemis++;

        float norme_courante = Norme1(o_parcours->GetPosition() - Hero->GetPosition());

        if (norme_courante < norme_du_proche) {
          norme_du_proche = norme_courante;
          elementproche = o_parcours;
        }
      }
    }
  PARCOURS_OBJETS_FIN;

  if (unennemiestdecede && (nb_ennemis == 0))
    RaiseEvenement(EVT_PlusEnnemi);



  if (Hero->EnTrainDeFrapper()) {
    CPhysicalObj zoneepee = (*aHero);
    TPoint3D d = Hero->GetDimension(this);
    zoneepee.SetDimension(d.x, d.y, d.z);

    TPoint3D dir;
    switch (Hero->GetDirection()) {
    case FACE: dir = Point3D(0.0f, -1.0f, 0.0f); break;
    case DOS: dir = Point3D(0.0f, 1.0f, 0.0f); break;
    case PROFIL_VERS_D: dir = Point3D(1.0f, 0.0f, 0.0f); break;
    case PROFIL_VERS_G: dir = Point3D(-1.0f, 0.0f, 0.0f); break;
    default: assert(false);
    }

    zoneepee.SetPosition(Hero->GetPosition() + dir);

    //PARCOURS_OBJETS_VOISINAGES_PROCHE(Hero->GetPosition())
    PARCOURS_OBJETS
      {
        CBonhomme* b = dynamic_cast<CBonhomme *> (o_parcours);

        if (b && (!b->IsVolumeNul()))
          if ((!(b->TesterPosition(this, &zoneepee))) && (!(b->EstInvinsible()))) {
            //on a frappé a.Element()
            printf("Le héros a frappé un bonhomme\n");
            b->PerdrePV(1);
            AjouterParticules(b->GetPosition(), "sang.anime", MoteurPhysiqueActif);
            b->AddForce(10.0f*dir);
            b->DevenirInvinsible(50);
          }

      }
    //FIN_PARCOURS_OBJETS_VOISINAGES;
    PARCOURS_OBJETS_FIN;

  }


  // on ne fait bouger que les ennemis près du héros: le reste du monde n'évolue pas!!!!
  //PARCOURS_OBJETS_VOISINAGES_PROCHE(Hero->GetPosition())
  PARCOURS_OBJETS
    {
      /*si l'objet courant est un bonhomme*/
      if (CBonhomme* b = dynamic_cast<CBonhomme *>(o_parcours)) {
        if (rand() % 20 == 1)
          b->SetDirection(DirectionAleatoire());

        b->Avancer(b->GetDirection(), this);
      }

      if (!(o_parcours->Fixe)) {
        TesterPosition(o_parcours, MoteurPhysiqueActif);
        if (!o_parcours->TesterPosition(this, Hero)) {
          if (o_parcours->Hostile)
            if (!Hero->EstInvinsible()) {
              //le héros se fait toucher par un ennemi
              Hero->PerdrePV(5);
              Hero->DevenirInvinsible(200);
            }
        }
        o_parcours->ValiderPosition(MoteurPhysiqueActif);
        o_parcours->InitForce();
      }
    }
  //FIN_PARCOURS_OBJETS_VOISINAGES;
  PARCOURS_OBJETS_FIN;


  return elementproche;
}




void CMap::TesterPosition(CPhysicalObj * o, const bool MoteurPhysiqueActif) {
  // on teste si la position temporaire de o est correct
  TPoint3D pp = o->GetPosition();
  float i = pp.x;
  float j = pp.y;
  float z = pp.z;

  if (yatilEau(i, j, z)) {
    if (!(o->DansEau)) {
      printf(" L'objet %p va rentrer dans l'eau. Sa position est la suivante : %f, %f, %f. Nous allons générer une floppée de particules d'eau.\n", o, i, j, z);

      if (not(o->IsVolumeNul()))
        AjouterParticules(o->GetPosition(), "eclaboussures.anime", MoteurPhysiqueActif);

      o->DansEau = true;

    }

    o->AddForce(0.0f, 0.0f, -1.0f);

    if (yatilEau(i, j, z+20.0f))
      o->Immerge = true;
    else
      o->Immerge = false;

    //dans l'eau les frottements fluides sont plus importants
    o->CoeffFrottementFluide = 3.0f;
    o->CoeffFrottementFluideZ = 1.0f;

  }

  else {
    o->DansEau = false;
    o->AddForce(0.0f, 0.0f, -10.0f);
    o->Immerge = false;
    //dans l'air, les frottements fluides sont assez petits
    o->CoeffFrottementFluide = 1.0f;
    o->CoeffFrottementFluideZ = 0.0f;
  }

  o->CalcNewPosition();
  o->TesterSol(this);

  //PARCOURS_OBJETS_VOISINAGES_TOUTPROCHE(o->GetPosition())
  PARCOURS_OBJETS
    if (o_parcours!=o)
      o->TesterPosition(this, o_parcours);
  PARCOURS_OBJETS_FIN;
  //FIN_PARCOURS_OBJETS_VOISINAGES;

}



#ifdef VOISINAGE_IS_TAB

int voisinage_nbelt(const CMap * map, int iii) {
  int i;
  assert(iii < maxindvoisinages2);
  for (i = 0; i < VOISINAGE_TAILLE; i++) {
    if (map -> Voisinages[iii][i] == NULL) break;
  }
  assert(i < VOISINAGE_TAILLE);

  return i;
}

void voisinage_ajouter(CMap * map, int iii, CPhysicalObj * o) {
  int i = voisinage_nbelt(map, iii);
  map -> Voisinages[iii][i] = o;
}

void voisinage_detruire(CMap * map, int iii, int jjj) {
  int i = voisinage_nbelt(map, iii);
  assert(jjj < i);
  delete map -> Voisinages[iii][jjj];
  map -> Voisinages[iii][jjj] = map -> Voisinages[iii][i-1];
  map -> Voisinages[iii][i-1] = NULL;
}


#endif
