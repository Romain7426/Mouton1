#include "global.hpp"
#include "objnonanime.hpp"
#include "nonanime/nonanime.hpp"


CObjNonAnime::CObjNonAnime(const CObjNonAnime * o) : angleZ(0.0f), filename(strcopy(o -> filename)) {
  Compressible = o->Compressible;
  Hostile = o->Hostile;
  Fixe = o->Fixe;
  
  resobj3ds = o->resobj3ds->AvoirAutreRessource();
}

CObjNonAnime::~CObjNonAnime(void) {
  delete resobj3ds;        
}

CObjNonAnime::CObjNonAnime(const char * filename) : CPhysicalObj(filename), resobj3ds(NULL), angleZ(0.0f), filename(strcopy(filename)) {
  Compressible = true;  
  Hostile = false;
  Fixe = true;
  
  int ret;
  ret = parse(NONANIMESDIR, filename);

  if (0 == ret)
    printf("Création de l'objet non animé réalisé avec succès!!\n");
  else {
    messerr("Erreur lors de la lecture du fichier de description l'objet non-anime.");
    assert(false);
  }
  
}



void CObjNonAnime::Render(const CSol * sol) const {
#if 0
  if (0 != strcmp(filename, "./heros.anime")) {
    fprintf(stderr, "ObjNonAnime: Rendering: %s\n", filename);
    fflush(NULL);
  }
#endif

  CPhysicalObj::Render(sol);   
  
  glPushMatrix(); {

    sol -> MatricePour2D(p.x, p.y, p.z);

    glRotatef(90.0f, 1.0, 0.0, 0.0);
    glRotatef(angleZ * 180.0f/PI, 0.0, 1.0, 0.0);

    if (Compressible)
      glScalef(1.0f, 1.0f, sol -> FacteurCompression(p.y));
    
    resobj3ds -> getObject() -> Render();

  } glPopMatrix();
}



void CObjNonAnime::SetAngleZ(float thetaZ) {  
  angleZ = thetaZ;
}

