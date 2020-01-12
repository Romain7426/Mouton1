#include "global.h"
#include "map.h"
#include "physicalobj.h"
#include "objnonanime.h"
#include "bonhomme.h"
#include "evenement.h"
#include "carte.h"


#ifdef VOISINAGE_IS_TAB
static int voisinage_nbelt(const CMap * map, int iii);
static void voisinage_ajouter(CMap * map, int iii, CPhysicalObj * o);
static void voisinage_detruire(CMap * map, int iii, int jjj);
#endif


#define taille_case 5
#define nb_voisinage_traitee 3
#define nb_voisinage_traitee_toutproche 1

#if 0 

#define PARCOURS_OBJETS                                         \
  if (Voisinages != NULL)                                       \
    for (int iii = 0; iii < maxindvoisinages; iii++)            \
      for (int jjj = 0; jjj < VOISINAGE_TAILLE; jjj++)          \
        {                                                       \
          CPhysicalObj * o_parcours = Voisinages[iii][jjj];     \
          if (o_parcours == NULL)                               \
            continue;

#elif 0 

#define PARCOURS_OBJETS                                                 \
  if (Voisinages != NULL)                                               \
    for (int iii = 0; iii < maxindvoisinages; iii++)                    \
      for (CAccesseur<CPhysicalObj> a = Voisinages[iii].Objets.ObtenirAcces(); !a.IsFin(); a.AllerSuivant()) \
        {                                                               \
          CPhysicalObj * o_parcours = a.Element();                      \
          if (o_parcours == NULL)                                       \
            continue;

#elif 1
#define PARCOURS_OBJETS                                         \
  for (int iii = 0; iii < VOISINAGE_X_SIZE; iii++)		\
    for (int jjj = 0; jjj < VOISINAGE_Y_SIZE; jjj++)		\
      for (int kkk = 0; kkk < VOISINAGE_SIZE; kkk++)		\
        {                                                       \
  CPhysicalObj * o_parcours = this -> Voisinages_array[iii][jjj][kkk];	\
          if (o_parcours == NULL)                               \
            continue;


#endif


#define PARCOURS_OBJETS_FIN }



#if 0 

#define PARCOURS_ZONESTELEPORTATIONS                                    \
  for (CAccesseur<CZoneTeleportation> a = ZonesTeleportation.ObtenirAcces(); not(a.IsFin()); a.AllerSuivant())
 
#else 

#define PARCOURS_ZONESTELEPORTATIONS                                    \
  for (int izt = 0; izt < this -> ZonesTeleportation_nb; izt++) {	\
  CZoneTeleportation * zt_parcours = this -> ZonesTeleportation_array[izt];	

#define PARCOURS_ZONESTELEPORTATIONS_FIN } 

#endif 



//#define maxindvoisinages_fun(ttt) ((((int) (((ttt) -> TailleX) / taille_case)) + 1) * (((int) (((ttt) -> TailleY) / taille_case)) + 1))
#define maxindvoisinages_fun(ttt) ((((int) (((ttt) -> TailleX) / taille_case))) * (((int) (((ttt) -> TailleY) / taille_case))))
#define maxindvoisinages  maxindvoisinages_fun(&this -> parent)
#define maxindvoisinages2 maxindvoisinages_fun(map)


// On affiche la case sur laquelle nous sommes
// et les cases à rayon de nbnb
// ainsi que le voisinage trivial (indicé 0)
#define PARCOURS_OBJETS_VOISINAGES__OLD(pos_A, nbnb_A)			\
  {                                                                     \
  const TPoint3D pos_ = (pos_A);					\
  int nbnb_ = (nbnb_A);                                                 \
  int current_case_ix = (int) (((real) pos_.x) / ((real) taille_case)); \
  int current_case_iy = (int) (((real) pos_.y) / ((real) taille_case)); \
  for (int biz = 0; biz <= 1; biz++)					\
    for (int ix = biz*(current_case_ix - nbnb_); ix <= biz*(current_case_ix + nbnb_); ix++) \
      if (ix >= 0)							\
	for (int iy = biz*(current_case_iy - nbnb_); iy <= biz*(current_case_iy + nbnb_); iy++) \
	  if (iy >= 0)							\
	    {								\
  int iii = ix + iy * ((int) (((real) TailleX) / ((real) taille_case))); \
  if ((iii >= 0) && (iii < maxindvoisinages))				\
    {									\
  iii += biz;								\
  if (Voisinages != NULL)						\
    for (CAccesseur<CPhysicalObj> a = Voisinages[iii].Objets.ObtenirAcces(); not(a.IsFin()); a.AllerSuivant()) \
      {									\
  CPhysicalObj * o_parcours = a.Element();				\
  if (o_parcours == NULL)						\
    continue;

#define PARCOURS_OBJETS_VOISINAGES_FIN__OLD }}}}

#define PARCOURS_OBJETS_VOISINAGES(pos_A, nbnb_A)			\
  {                                                                     \
  const TPoint3D pos_ = (pos_A);					\
  int nbnb_ = (nbnb_A);                                                 \
  int current_case_ix = (int) (((real) pos_.x) / ((real) taille_case)); \
  int current_case_iy = (int) (((real) pos_.y) / ((real) taille_case)); \
  for (int biz = 0; biz <= 1; biz++)					\
    for (int ix = biz*(current_case_ix - nbnb_); ix <= biz*(current_case_ix + nbnb_); ix++) \
      if (ix < 0) continue; else					\
	for (int iy = biz*(current_case_iy - nbnb_); iy <= biz*(current_case_iy + nbnb_); iy++) \
	  if (iy < 0) continue; else					\
	    for (int iv = 0; iv < VOISINAGE_SIZE; iv++)			\
	      {								\
  CPhysicalObj * o_parcours = this -> Voisinages_array[ix][iy][iv]; \
  if (o_parcours == NULL)						\
    continue;

#define PARCOURS_OBJETS_VOISINAGES_FIN }} 


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



CZoneTeleportation * CZoneTeleportation_make(TPoint3D in_position, TPoint3D in_dimension, TDirection in_depart_direction, const char * in_destination_carte, TPoint3D in_destination_position, TDirection in_destination_direction) { 
  MALLOC_BZERO(CZoneTeleportation,this);
  
  this -> position = in_position;
  this -> dimension = in_dimension;
  this -> depart_direction = in_depart_direction;

  this -> destination_carte = strcopy(in_destination_carte);
  this -> destination_position = in_destination_position;
  this -> destination_direction = in_destination_direction;

  return this; 
}; 

void CZoneTeleportation_delete(CZoneTeleportation * this) {
  free(this); 
}; 

CZoneTeleportation * CZoneTeleportation_copy(const CZoneTeleportation * zt_src) {
  MALLOC_BZERO(CZoneTeleportation,this);
  *this = *zt_src; 
  this -> destination_carte = strcopy(zt_src -> destination_carte); 
  return this; 
}; 




#define NomCarte (this -> NomCarte) 
#define ZonesTeleportation (this -> ZonesTeleportation) 
#define evt_carte (this -> evt_carte) 
//#define Voisinages_array[VOISINAGE_X_SIZE][VOISINAGE_Y_SIZE][VOISINAGE_SIZE]; 
//#define DicoObjets


CMap * CMap__make(const char * filename, const bool EnVaisseau) {
  MALLOC_BZERO(CMap,this);
  
  //ASSIGN_METHOD(CMap,this,parse);
  //ASSIGN_METHOD(CMap,this,yycarteparse);
  ASSIGN_METHOD(CMap,this,GetNomCarte);
  ASSIGN_METHOD(CMap,this,Render);
  ASSIGN_METHOD(CMap,this,ChargerZ);
  ASSIGN_METHOD(CMap,this,AjouterObjet);
  ASSIGN_METHOD(CMap,this,AjouterObjet_nom);
  ASSIGN_METHOD(CMap,this,RetrouverObjetViaSonNom);
  ASSIGN_METHOD(CMap,this,AjouterZoneTeleportation);
  ASSIGN_METHOD(CMap,this,AjouterParticules);
  ASSIGN_METHOD(CMap,this,TesterPosition);
  ASSIGN_METHOD(CMap,this,TesterPositionHero);
  ASSIGN_METHOD(CMap,this,TraiterOrdresDeplacement);
  ASSIGN_METHOD(CMap,this,VaTonBouger);
  //ASSIGN_METHOD(CMap,this,tab_evt_carte);

  // CSol(EnVaisseau)
  CSol_make_aux(&this -> parent, EnVaisseau); 
  

  if (filename == NULL) return this;

  NomCarte = strcopy(filename); 
  
#if 1
  ViderEvenement(EVT_ChargementCarte);
  ViderEvenement(EVT_EntreeSurCarte);
  ViderEvenement(EVT_PlusEnnemi);
#endif

  printf("Constructeur CMap(%s)\n", filename);

  // Nous devons attendre avant de l'allouer car nous avons besoin de TailleX et TailleY (donc attendre le ChargerZ)
  //this -> Voisinages = NULL;

  this -> objets_nb = 0; 

  this -> ZonesTeleportation_nb = 0; 
 
  {
    char * reelfile;
    //reelfile = STRCAT2_(CARTESDIR, filename);
    reelfile = strconcat2(CARTESDIR, filename);
    printf("nom de fichier réel: %s\n", reelfile);
    
    //int ret = CMap__parse(this, CARTESDIR, filename);
    const int ret = CMap__ReadDescriptionFile(this, CARTESDIR, filename);
    if (ret){
      messerr("pas bonne analyse du fichier \"%s\".", reelfile);
      assert(false);
    }
    else {
      message("analyse ok du fichier \"%s\".", reelfile);
    }
    free(reelfile);
  }; 

  printf("Fin de la construction CMap__CMap()\n");

  return this; 
};


void CMap_delete(CMap * this) {
  printf("Destruction de la carte %p\n", this);

  for (int i = 0; i < this -> ZonesTeleportation_nb; i++) { 
    CZoneTeleportation_delete(this -> ZonesTeleportation_array[i]); 
  }; 

  for (int i = 0; i < this -> objets_nb; i++) { 
    //CPhysicalObj_delete(this -> objets_array[i]); // Ils sont dans Voisinage. 
    free(this -> objets_noms_array[i]); 
  }; 

  //delete[] Voisinages;
  for (int i = 0; i < VOISINAGE_X_SIZE; i++) 
    for (int j = 0; j < VOISINAGE_Y_SIZE; j++) 
      for (int k = 0; k < VOISINAGE_SIZE; k++) 
	if (NULL != this -> Voisinages_array[i][j][k]) {
	  CPhysicalObj_delete(this -> Voisinages_array[i][j][k]);
	}; 
	
  free(NomCarte); 
  // TextureSol, Objets, ZonesTeleportation sont détruits automatiquement car ce ne sont pas des pointeurs
  CSol_delete(&this -> parent);
  free(this); 
};


const char * CMap__GetNomCarte(const CMap * this) {
  return NomCarte;
};




void CMap__ChargerZ(CMap * this, const char * filename) {
  printf("CMap__ChargerZ(%s)\n", filename);
  this -> parent.ChargerZ(&this -> parent, filename);


#if 0
#ifndef VOISINAGE_IS_TAB
  // On ne peut l'allouer que maintenant car nous avons besoin de TailleX et TailleY
  Voisinages = new TVoisinage[maxindvoisinages + 1];
#if 0
  for (int i = 0; i < (maxindvoisinages + 1) ; i++) {
    //Voisinages[i].Objets = NULL;
    fprintf(stderr, "Voisinages[%d]: %p\n", i, Voisinages[i].Objets.debutliste);
  }
#endif
#elif 0 
  Voisinages = new CPhysicalObj * [maxindvoisinages + 1][VOISINAGE_TAILLE];
  for (int i = 0; i < (maxindvoisinages + 1); i++)
    for (int j = 0; j < VOISINAGE_TAILLE; j++)
      Voisinages[i][j] = NULL;
#endif
#endif

  printf(" fin CMap__ChargerZ(%s)\n", filename);
};












void CMap__AjouterObjet(CMap * this, CPhysicalObj * o) {
  printf("Ajout de l'objet physique (pointeur: %p; filename: %s) à la carte\n", o, o == NULL ? NULL : o -> filename);

  //assert(Voisinages != NULL); // ChargerZ doit avoir lieu auparavant!

#if 0
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
#endif 

#if 0
  if (CBonhomme * b = dynamic_cast<CBonhomme *>(o)) {
    fprintf(stdout, "Ajout de Bonhomme: Adding: %s\n", b -> filename);
  };
#endif 




  TPoint3D pos = o -> GetPosition(o);

  pos.z = this -> parent.GETZ(&this -> parent, pos.x, pos.y);
  o -> SetPosition_vP3D(o, pos);


  printf("Taille de la carte en real: %d x %d\n", this -> parent.TailleX, this -> parent.TailleY);
  printf("Taille de la carte en case: %d x %d\n", ((int) (this -> parent.TailleX / taille_case)), ((int) (this -> parent.TailleY / taille_case)));
  printf("Position de l'objet: %f x %f\n", pos.x, pos.y);
  printf("Coordonnées de la case contenant l'objet: %d x %d\n", ((int) (pos.x / taille_case)), ((int) (pos.y / taille_case)));



  if (o -> Fixe) {
    //int iii = ((int) (pos.y / taille_case)) * ((int) (TailleX / taille_case)) + ((int) pos.x / taille_case);
    //int iii = ((int) (pos.x / taille_case))  +  ((int) (pos.y / taille_case)) * ((int) (this -> parent.TailleX / taille_case));
    const int ix = ((int) (pos.x / taille_case)); 
    const int iy = ((int) (pos.y / taille_case)); 
    int iii = ix + iy * ((int) (this -> parent.TailleX / taille_case)); 
    
    if ((iii < 0) || (iii >= maxindvoisinages))
      iii = -1; // un +1 est fait ensuite, donc tout va bien :-)

    printf("On ajoute dans le voisinage n° %i (coord. x = %f, y %f)\n", iii, pos.x, pos.y);
#if 0 
    Voisinages[iii+1].Objets.Empiler_sans_copie(o);
#elif 0
    voisinage_ajouter(this, iii+1, o);
#elif 1 
    for (int iv = 0; iv < VOISINAGE_SIZE; iv++) {
      if (NULL != this -> Voisinages_array[ix][iy][iv]) continue; 
      this -> Voisinages_array[ix][iy][iv] = o; 
    };
#endif
  }

  else {
    printf("On ajoute dans le voisinage trivial.\n");
#if 0 
    Voisinages[0].Objets.Empiler_sans_copie(o);
#elif 0
    voisinage_ajouter(this, 0, o);
#elif 1 
    for (int iv = 0; iv < VOISINAGE_SIZE; iv++) {
      if (NULL != this -> Voisinages_array[0][0][iv]) continue; 
      this -> Voisinages_array[0][0][iv] = o; 
    };
#endif
  };
  
  
  printf("Ajout de l'objet physique réussi!!\n");
};



void CMap__AjouterObjet_nom(CMap * this, const char * nom, CPhysicalObj * o) {
  printf("Ajout de l'objet physique (pointeur %p) à la carte, de nom %s \n", o, nom);
  this -> AjouterObjet(this, o);
  
  assert(this -> objets_nb < DicoObjets_SIZE); 
  this -> objets_array[this -> objets_nb] = o;
  this -> objets_noms_array[this -> objets_nb] = strcopy(nom);
  this -> objets_nb++; 
  
  printf("Ajout de l'objet physique réussi !!\n");
};



CPhysicalObj * CMap__RetrouverObjetViaSonNom(CMap * this, const char * nom) {
  for (int i = 0; i < this -> objets_nb; i++) {
    if (0 != strcmp(nom, this -> objets_noms_array[i])) continue; 
    return this -> objets_array[i]; 
  }; 
  return NULL;
};



/* exemple d'utilisation

   TPoint3D pos, dim, posdest;

   pos = Point3D(0.0f, 0.0f,0.0f);
   dim = Point3D(2.0f, 2.0f, 128.0f);
   posdest = Point3D(0.0f, 4.0f, 0.0f);

   Map -> AjouterZoneTeleportation(pos, dim, DOS, "carte.carte", posdest, DOS);
*/
void CMap__AjouterZoneTeleportation(CMap * this, TPoint3D position, TPoint3D dimension, TDirection depart_direction, const char * destination_carte, TPoint3D destination_position, TDirection destination_direction) {
  CZoneTeleportation * zt = CZoneTeleportation_make(position, dimension, depart_direction, destination_carte, destination_position, destination_direction);

  printf("Ajout d'une zone de téléportation \n");
  printf(" position: (%f, %f, %f)\n", position.x, position.y, position.z);
  printf(" dimension: (%f, %f, %f)\n", dimension.x, dimension.y, dimension.z);

  assert(this -> ZonesTeleportation_nb < ZonesTeleportation_SIZE); 
  this -> ZonesTeleportation_array[this -> ZonesTeleportation_nb] = zt;
  this -> ZonesTeleportation_nb++; 
}; 



void CMap__AjouterParticules(CMap * this, TPoint3D p, const char * nom, const bool MoteurPhysiqueActif) {
#define NB_PARTICULES 10
  printf("Ajout d'une flopée de particules au point (%f, %f, %f,) \n...", p.x, p.y, p.z);

#ifdef NB_PARTICULES
  for (int i = 0; i<NB_PARTICULES; i++) {

    CBonhomme * b = CBonhomme_make(nom);
    CPhysicalObj * o = &b -> parent1; 
    o->SetDimension(o, 0.0f,0.0f,0.0f);

    o->SetPosition_vP3D(o, p);
    o->SetObjetEphemere(o, 32);
    o->Hostile = false;
    TPoint3D pp = o->GetPosition(o);
    printf("Coordonnée des particules : (%f, %f, %f,) \n", pp.x, pp.y, pp.z);
    o->InitForce(o);

#define GENPOS ((float) (rand()%2000-1000)) / 200.0f
    o->AddForce_vXYZ(o, GENPOS, GENPOS, 100.0f);
    o->CalcNewPosition(o);
    o->ValiderPosition(o, MoteurPhysiqueActif);
    this -> AjouterObjet(this, o);

  }
#endif

  printf("Ajout des particules effectuées!\n");
};




TDirection DirectionAleatoire(void) {
  return (TDirection) (rand() % 4);
}



const CZoneTeleportation * CMap__VaTonBouger(const CMap * this, const CPhysicalObj * aHero) { 
  TPoint3D p = aHero -> GetPosition(aHero);

  PARCOURS_ZONESTELEPORTATIONS
    {
      if ((zt_parcours->position.x <= p.x) &&
          (zt_parcours->position.y <= p.y) &&
          (zt_parcours->position.z <= p.z) &&
          (p.x <= zt_parcours->position.x + zt_parcours->dimension.x) &&
          (p.y <= zt_parcours->position.y + zt_parcours->dimension.y) &&
          (p.z <= zt_parcours->position.z + zt_parcours->dimension.z) )
        return zt_parcours;

    }
  PARCOURS_ZONESTELEPORTATIONS_FIN;

  return NULL;
}; 




void CMap__TraiterOrdresDeplacement(CMap * this, CBonhomme * aHero, const bool MoteurPhysiqueActif) {
  aHero -> TraiterOrdresDeplacement(aHero, this, MoteurPhysiqueActif);

  PARCOURS_OBJETS
    {
#if 0
      CBonhomme * b = dynamic_cast<CBonhomme *>(a.Element());
#elif 0
      CBonhomme * b = dynamic_cast<CBonhomme *>(o_parcours);
#elif 1 
      if (!(CPhysicalObj_subtype_CBonhomme == o_parcours -> subtype)) continue; 
      CBonhomme * b = (CBonhomme *) o_parcours; 
#endif
      b -> TraiterOrdresDeplacement(b, this, MoteurPhysiqueActif);
    }
  PARCOURS_OBJETS_FIN;
}; 



/*on informe la carte de la position du héro

  en retour, elle nous offre un pointeur vers l'élément le plus proche
  OU NULL si trop loin
*/
// En fait cette fonction est le moteur physique…………
CPhysicalObj * CMap__TesterPositionHero(CMap * this, CPhysicalObj * aHero, const bool MoteurPhysiqueActif) {

  CBonhomme * Hero = (CBonhomme *) aHero;

  this -> TesterPosition(this, aHero, MoteurPhysiqueActif);
  aHero -> ValiderPosition(aHero, MoteurPhysiqueActif);
  aHero -> InitForce(aHero);


  // on fait bouger les objets
  PARCOURS_OBJETS
    {
      if (CPhysicalObj_subtype_CBonhomme == o_parcours -> subtype) {  
	CBonhomme * b = (CBonhomme *) o_parcours; 
        if (rand() % 20 == 1)
          b -> SetDirection(b, DirectionAleatoire());

        b -> Avancer(b, b -> GetDirection(b), this); 
      }

      if (!(o_parcours -> Fixe)) {
        this -> TesterPosition(this, o_parcours, MoteurPhysiqueActif);
        if (!o_parcours -> TesterPosition(o_parcours, &this -> parent, aHero)) {
          if (o_parcours -> Hostile)
            if (not(Hero -> EstInvisible(Hero))) {
              //le héros se fait toucher par un ennemi
              aHero -> PerdrePV(aHero, 5);
              Hero -> DevenirInvisible(Hero, 200);
            }
        }
        o_parcours -> ValiderPosition(o_parcours, MoteurPhysiqueActif);
        o_parcours -> InitForce(o_parcours);
      }
    }
  //FIN_PARCOURS_OBJETS_VOISINAGES;
  PARCOURS_OBJETS_FIN;


  // la phsyique de l'épée
#if 1
  {
    if (Hero -> EnTrainDeFrapper(Hero)) {
      CPhysicalObj zoneepee = *(aHero);
      TPoint3D d = aHero -> GetDimension(aHero, &this -> parent);
      zoneepee.SetDimension(&zoneepee, d.x, d.y, d.z);

      TPoint3D dir;
      switch (Hero -> GetDirection(Hero)) {
      case FACE: dir = TPoint3D_make_struct(0.0f, -1.0f, 0.0f); break;
      case DOS: dir = TPoint3D_make_struct(0.0f, 1.0f, 0.0f); break;
      case PROFIL_VERS_D: dir = TPoint3D_make_struct(1.0f, 0.0f, 0.0f); break;
      case PROFIL_VERS_G: dir = TPoint3D_make_struct(-1.0f, 0.0f, 0.0f); break;
      default: assert(false);
      }
      
      //zoneepee.SetPosition(&zoneepee, aHero -> GetPosition(aHero) + dir);
      TPoint3D hero_pos = aHero -> GetPosition(aHero); 
      zoneepee.SetPosition_vP3D(&zoneepee, TPoint3D_add(hero_pos, dir));

      //PARCOURS_OBJETS_VOISINAGES_PROCHE(Hero->GetPosition())
      PARCOURS_OBJETS
        {
	  if (CPhysicalObj_subtype_CBonhomme != o_parcours -> subtype) continue; 
	  CBonhomme * b = (CBonhomme *) o_parcours; 

          if (!o_parcours -> IsVolumeNul(o_parcours))
            if ((!(o_parcours->TesterPosition(o_parcours, &this -> parent, &zoneepee))) && (!(b->EstInvisible(b)))) {
              //on a frappé a.Element()
              printf("Le héros a frappé un bonhomme\n");
              o_parcours -> PerdrePV(o_parcours, 1);
              this -> AjouterParticules(this, o_parcours -> GetPosition(o_parcours), "sang.anime", MoteurPhysiqueActif);
              o_parcours -> AddForce_vP3D(o_parcours, TPoint3D_scalar_mul(10.0f, dir));
              b -> DevenirInvisible(b, 50);
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
      if (not(o_parcours -> Fixe) && o_parcours -> Is0PV(o_parcours)) {
#if 0 
        a.DetruireElementCourant();
#elif 0
        voisinage_detruire(this, iii, jjj);
#else 
	CPhysicalObj_delete(this -> Voisinages_array[iii][jjj][kkk]); 
	this -> Voisinages_array[iii][jjj][kkk] = NULL; 
	// Et dans le dico? 
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
        float norme_courante = TPoint3D_Norme1(TPoint3D_sub(o_parcours -> GetPosition(o_parcours), aHero -> GetPosition(aHero)));

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
      if (o_parcours -> Is0PV(o_parcours)) {
        if (o_parcours -> Hostile)
          unennemiestdecede = true;
#if 0
        a.DetruireElementCourant();
#elif 0
        voisinage_detruire(this, iii, jjj);
#elif 1 
	CPhysicalObj_delete(this -> Voisinages_array[iii][jjj][kkk]); 
	this -> Voisinages_array[iii][jjj][kkk] = NULL; 
	// Et dans le dico? 
#endif
      }
      else {
        if (o_parcours -> Hostile) nb_ennemis++;

        float norme_courante = TPoint3D_Norme1(TPoint3D_sub(o_parcours -> GetPosition(o_parcours), aHero -> GetPosition(aHero)));

        if (norme_courante < norme_du_proche) {
          norme_du_proche = norme_courante;
          elementproche = o_parcours;
        }
      }
    }
  PARCOURS_OBJETS_FIN;

  if (unennemiestdecede && (nb_ennemis == 0))
    RaiseEvenement(EVT_PlusEnnemi);



  if (Hero -> EnTrainDeFrapper(Hero)) {
    CPhysicalObj zoneepee = (*aHero);
    TPoint3D d = aHero -> GetDimension(aHero, &this -> parent);
    zoneepee.SetDimension(&zoneepee, d.x, d.y, d.z);

    TPoint3D dir;
    switch (Hero -> GetDirection(Hero)) {
    case FACE: dir = TPoint3D_make_struct(0.0f, -1.0f, 0.0f); break;
    case DOS: dir = TPoint3D_make_struct(0.0f, 1.0f, 0.0f); break;
    case PROFIL_VERS_D: dir = TPoint3D_make_struct(1.0f, 0.0f, 0.0f); break;
    case PROFIL_VERS_G: dir = TPoint3D_make_struct(-1.0f, 0.0f, 0.0f); break;
    default: assert(false);
    }

    TPoint3D hero_pos = aHero -> GetPosition(aHero); 
    zoneepee.SetPosition_vP3D(&zoneepee, TPoint3D_add(hero_pos, dir));
    
    //PARCOURS_OBJETS_VOISINAGES_PROCHE(Hero->GetPosition())
    PARCOURS_OBJETS
      {
	if (CPhysicalObj_subtype_CBonhomme != o_parcours -> subtype) continue; 
        if (o_parcours -> IsVolumeNul(o_parcours)) continue;
	
        CBonhomme* b = (CBonhomme *) o_parcours;

	if ((!(o_parcours -> TesterPosition(o_parcours, &this -> parent, &zoneepee))) && (!(b -> EstInvisible(b)))) {
	  //on a frappé a.Element()
	  printf("Le héros a frappé un bonhomme\n");
	  o_parcours -> PerdrePV(o_parcours, 1);
	  this -> AjouterParticules(this, o_parcours -> GetPosition(o_parcours), "sang.anime", MoteurPhysiqueActif);
	  o_parcours -> AddForce_vP3D(o_parcours, TPoint3D_scalar_mul(10.0f,dir));
	  b -> DevenirInvisible(b, 50);
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
      //if (CBonhomme* b = dynamic_cast<CBonhomme *>(o_parcours)) {
      if (CPhysicalObj_subtype_CBonhomme == o_parcours -> subtype) { 
	CBonhomme* b = (CBonhomme *) o_parcours;
	if (rand() % 20 == 1)
	  b -> SetDirection(b, DirectionAleatoire());
	
	b -> Avancer(b, b -> GetDirection(b), this);
      }
      
      if (!(o_parcours->Fixe)) {
	this -> TesterPosition(this, o_parcours, MoteurPhysiqueActif);
	if (!o_parcours -> TesterPosition(o_parcours, &this -> parent, aHero)) {
	  if (o_parcours -> Hostile)
	    if (!Hero -> EstInvisible(Hero)) {
	      //le héros se fait toucher par un ennemi
	      aHero -> PerdrePV(aHero, 5);
	      Hero -> DevenirInvisible(Hero, 200);
	    }
        }
        o_parcours -> ValiderPosition(o_parcours, MoteurPhysiqueActif);
        o_parcours -> InitForce(o_parcours);
      }
    }
  //FIN_PARCOURS_OBJETS_VOISINAGES;
  PARCOURS_OBJETS_FIN;

  
  return elementproche;
}; 




void CMap__TesterPosition(CMap * this, CPhysicalObj * o, const bool MoteurPhysiqueActif) {
  // on teste si la position temporaire de o est correct
  TPoint3D pp = o -> GetPosition(o);
  float i = pp.x;
  float j = pp.y;
  float z = pp.z;

  if (this -> parent.yatilEau(&this -> parent, i, j, z)) {
    if (!(o -> DansEau)) {
      printf(" L'objet %p va rentrer dans l'eau. Sa position est la suivante : %f, %f, %f. Nous allons générer une floppée de particules d'eau.\n", o, i, j, z);

      if (not(o -> IsVolumeNul(o)))
        this -> AjouterParticules(this, o -> GetPosition(o), "eclaboussures.anime", MoteurPhysiqueActif);

      o -> DansEau = true;
    }; 

    o -> AddForce_vXYZ(o, 0.0f, 0.0f, -1.0f);

    if (this -> parent.yatilEau(&this -> parent, i, j, z+20.0f))
      o -> Immerge = true;
    else
      o -> Immerge = false;

    //dans l'eau les frottements fluides sont plus importants
    o -> CoeffFrottementFluide = 3.0f;
    o -> CoeffFrottementFluideZ = 1.0f;

  }

  else {
    o -> DansEau = false;
    o -> AddForce_vXYZ(o, 0.0f, 0.0f, -10.0f);
    o -> Immerge = false;
    //dans l'air, les frottements fluides sont assez petits
    o -> CoeffFrottementFluide = 1.0f;
    o -> CoeffFrottementFluideZ = 0.0f;
  }

  o -> CalcNewPosition(o);
  o -> TesterSol(o, &this -> parent);

  //PARCOURS_OBJETS_VOISINAGES_TOUTPROCHE(o->GetPosition())
  PARCOURS_OBJETS {
    if (o_parcours == o) continue; 
    o -> TesterPosition(o, &this -> parent, o_parcours);
  } PARCOURS_OBJETS_FIN;
  //FIN_PARCOURS_OBJETS_VOISINAGES;
  
}; 





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




void CMap__Render(CMap * this, const int i1, const int j1, const int i2, const int j2, const bool EnVaisseau) {
  // on affiche le sol (on appelle la fonction Render de la classe CSol dont hérite CMap)
  this -> parent.Render(&this -> parent, i1, j1, i2, j2);

  const TPoint3D pos = TPoint3D_make_struct((i1 + i2) / 2, (j1 + j2) / 2, 0.  ); 
  
  
  if (not(EnVaisseau)) {
    //PARCOURS_OBJETS
    PARCOURS_OBJETS_VOISINAGES_PROCHE(pos)
      {
        int i = (int) o_parcours -> GetPosition(o_parcours).x;
        int j = (int) o_parcours -> GetPosition(o_parcours).y;

#if 0
        const char * filename = o_parcours -> filename;
        if (filename != NULL)
          if (0 != strcmp(filename, "./heros.anime")) {
            fprintf(stderr, "ObjPhys: Rendering: %s\n", filename);
            fflush(NULL);
          }
        //fprintf(stderr, "iii = %d - jjj = %d - ", iii, jjj);
#endif

        //bool test = ((i1 <= i) && (i <= i2) && (j1 <= j) && (j <= j2));
        //if (test)
        //if (CBonhomme * b = dynamic_cast<CBonhomme *>(o_parcours)) {
        if (CPhysicalObj_subtype_CBonhomme == o_parcours -> subtype) {
          //fprintf(stderr, "Bonhomme: Rendering: %s\n", b -> filename);
	  CBonhomme * b = (CBonhomme *) o_parcours; 
          b -> Render(b, &this -> parent); // b cannot be 'const' as b is animated as the same time it's rendered. 
        }
        //else if (CObjNonAnime * nonanime = dynamic_cast<CObjNonAnime *>(o_parcours)) {
        else if (CPhysicalObj_subtype_CObjNonAnime == o_parcours -> subtype) {
	  CObjNonAnime * nonanime = (CObjNonAnime *) o_parcours; 
          nonanime -> Render(nonanime, &this -> parent); 
        }
        else {
          o_parcours -> Render(o_parcours, &this -> parent);
	}; 

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
        int i = (int) o_parcours->GetPosition(o_parcours).x;
        int j = (int) o_parcours->GetPosition(o_parcours).y;


        bool b = ((i1 <= i) && (i <= i2) && (j1 <= j) && (j <= j2));
        if (b)
          o_parcours -> Render(o_parcours, &this -> parent);
      }
    PARCOURS_OBJETS_FIN;
  }; // _ en vaisseau _ 

  

  {
    //fprintf(stderr, "ZoneTeleportationBlit\n");
    //int i = 0;
    PARCOURS_ZONESTELEPORTATIONS {
      //fprintf(stderr, "ZoneTeleportationRender: i = %d\n", i++);
      this -> parent.AfficherCube(&this -> parent, zt_parcours -> position.x, zt_parcours -> position.y, zt_parcours -> position.z, zt_parcours -> dimension.x, zt_parcours -> dimension.y, zt_parcours -> dimension.z); 
    } PARCOURS_ZONESTELEPORTATIONS_FIN;
  };
  
};





int CMap__ReadDescriptionFile(CMap * this, const char * dir, const char * filename) {
  carte_t * carte_data = NULL; 
  CSol * this_parent = &this -> parent; 

  { 
    char carte_fullpath[strlen(dir) + strlen(filename) + 1];
    strcat(strcpy(carte_fullpath, dir), filename);
    carte_data = carte_make_from_file(carte_fullpath); 
  }; 
  
  if (!SCRIPT_EstEnTrainDExecuterUnScript()) {
    SCRIPT_JouerMusique(carte_data -> musique);
  }; 

  this_parent -> ZEau = carte_data -> niveau_eau; 

  for (int i = 0; i < carte_data -> teleportation_nb; i++) { 
    this -> AjouterZoneTeleportation(this, 
        TPoint3D_make_struct(carte_data -> teleportation_x[i], carte_data -> teleportation_y[i], carte_data -> teleportation_z[i]), 
        TPoint3D_make_struct(carte_data -> teleportation_longueur[i], carte_data -> teleportation_largeur[i], carte_data -> teleportation_hauteur[i]), 
        carte_data -> teleportation_direction[i], 
        carte_data -> teleportation_destination[i], 
        TPoint3D_make_struct(carte_data -> teleportation_destination_x[i], carte_data -> teleportation_destination_y[i], carte_data -> teleportation_destination_z[i]), 
        carte_data -> teleportation_destination_direction[i]); 
  }; 

  for (int i = 0; i < carte_data -> events_nb; i++) { 
    AddTraitementEvenement((type_evt)carte_data -> events_genere[i], carte_data -> events_gestion_fichier[i], carte_data -> events_gestion_proc[i]);
  }; 
  
  this -> ChargerZ(this, carte_data -> fichier_de_zone_de_niveau);
  
  this_parent -> ChargerIndiceTextureBitmap(this_parent, carte_data -> fichier_de_zone_de_texture); 

  if ((this_parent -> nb_texture + carte_data -> texture_nb) >= NB_MAX_TEXTURESOL) {
    messerr("Il n'y pas assez de place pour mettre la texture. Il faut changer NB_MAX_TEXTURESOL.");
    message("[nb_textures = %d][carte_data_textures = %d][NB_MAX_TEXTURES = %d]", this_parent -> nb_texture, carte_data -> texture_nb, NB_MAX_TEXTURESOL);
  }
  else {
    for (int i = 0; i < carte_data -> texture_nb; i++) { 
      ///carte_mess("Chargement en mémoire de la texture (image = \"%s\", couleur associée = %d).", $6, $10);
      //carte->TextureSol = gestionTexture.prendre($6);
      this_parent -> AjouterTextureSol(this_parent, carte_data -> texture_image[i], carte_data -> texture_indice[i]); 
    };
  }; 

  for (int i = 0; i < carte_data -> objet_nb; i++) { 
    if (carte_data -> objet_anime_huh[i]) {
      CBonhomme * bonhomme = CBonhomme_make(carte_data -> objet_fichier[i]);
      CPhysicalObj * o = (CPhysicalObj *) bonhomme; 
      o -> SetPosition_vP3D(o, TPoint3D_make_struct(carte_data -> objet_x[i], carte_data -> objet_y[i], carte_data -> objet_z[i])); 
      this -> AjouterObjet_nom(this, carte_data -> objet_nom[i], o);
      continue; 
    }
    else {
      CObjNonAnime * nonanime = CObjNonAnime_make(carte_data -> objet_fichier[i]);
      CPhysicalObj * o = (CPhysicalObj *) nonanime; 
      o -> SetPosition_vP3D(o, TPoint3D_make_struct(carte_data -> objet_x[i], carte_data -> objet_y[i], carte_data -> objet_z[i])); 
      this -> AjouterObjet_nom(this, carte_data -> objet_nom[i], o);
      continue; 
    };
  }; 
  
  carte_delete(carte_data); 
  
  return 0; 
}; 














