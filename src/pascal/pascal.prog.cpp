#include <stdio.h>
#include "global.hpp"
#include "main.hpp"
#include "pascal/pascal.prog.hpp"
#include "pascal/pascal.tools.hpp"
#include "apiscript.hpp"
#include "camera.hpp"
#include "moteurteleportation.hpp"

//enum direction {HAUT, BAS, GAUCHE, DROITE};


const char * string_of_enum_direction(enum direction dir) {
  const char * retour;

  switch (dir) {
  case HAUT:   return retour = ("HAUT  "); break;
  case BAS:    return retour = ("BAS   "); break;
  case GAUCHE: return retour = ("GAUCHE"); break;
  case DROITE: return retour = ("DROITE"); break;
  default: assert(false); retour = NULL;
  }

  return retour;
}
   
//enum methode {ABSOLU, RELATIF};
const char * string_of_enum_methode(enum methode meth) {
  const char * retour;

  switch (meth) {
  case ABSOLU:  return retour = ("ABSOLU"); break;
  case RELATIF: return retour = ("RELATIF"); break;
  default: assert(false); retour = NULL;
  }

  return retour;
}


static inline TDirection int_to_direction(int i) {
  TDirection direction;

  switch (i) {
  case 1: direction = FACE; break;
  case 2: direction = DOS; break;
  case 3: direction = PROFIL_VERS_D; break;
  case 4: direction = PROFIL_VERS_G; break;
  default: assert(false); break;
  }

  return direction;
}



static inline TMethodePlacement int_to_MethodePlacement(int i) {
  TMethodePlacement mp;

  switch (i) {
  case 1: mp = mpRELATIF; break;
  case 2: mp = mpABSOLU; break;
  default: assert(false);
  }

  return mp;
}




const char * cprog_type_string(enum CPprog::etype type) {
  const char * retour;
  switch (type) {
  case CPprog::PStop: retour = "PStop"; break;
  case CPprog::PSkip: retour = "PSkip"; break;
  case CPprog::PSeq: retour = "PSeq"; break;
  case CPprog::PIf: retour = "PIf"; break;
  case CPprog::PWhile: retour = "PWhile"; break;
  case CPprog::PFor: retour = "PFor"; break;
  case CPprog::PRepeat: retour = "PRepeat"; break;
  case CPprog::PBegin: retour = "PBegin"; break;
  case CPprog::PVar: retour = "PVar"; break;
  case CPprog::PConst: retour = "PConst"; break;
  case CPprog::PAffectation: retour = "PAffectation"; break;
  case CPprog::PWrite: retour = "PWrite"; break;
  case CPprog::PWriteln: retour = "PWriteln"; break;
  case CPprog::PRead: retour = "PRead"; break;
  case CPprog::PReadln: retour = "PReadln"; break;
  case CPprog::PType: retour = "PType"; break;
  case CPprog::PNew: retour = "PNew"; break;
  case CPprog::PCall: retour = "PCall"; break;
  case CPprog::PMusique: retour = "PMusique"; break;
  case CPprog::PWait: retour = "PWait"; break;
  case CPprog::PHalt: retour = "PHalt"; break;
  case CPprog::PRestart: retour = "PRestart"; break;
  case CPprog::PFondu: retour = "PFondu"; break;
  case CPprog::PRecObjet: retour = "PRecObjet"; break;
  case CPprog::PRecArme: retour = "PRecArme"; break;
  case CPprog::PSupObjet: retour = "PSupObjet"; break;
  case CPprog::PCarte: retour = "PCarte"; break;
  case CPprog::PCarteZ: retour = "PCarteZ"; break;
  case CPprog::PSetPosition: retour = "PSetPosition"; break;
  case CPprog::PSetPositionZ: retour = "PSetPositionZ"; break;
  case CPprog::PDeplacer: retour = "PDeplacer"; break;
  case CPprog::PDeplacerZ: retour = "PDeplacerZ"; break;
  case CPprog::PSetHerosPosition: retour = "PSetHerosPosition"; break;
  case CPprog::PSetHerosPositionZ: retour = "PSetHerosPositionZ"; break;
  case CPprog::PHerosDeplacer: retour = "PHerosDeplacer"; break;
  case CPprog::PHerosDeplacerZ: retour = "PHerosDeplacerZ"; break;
  case CPprog::PCameraDeplacer: retour = "PCameraDeplacer"; break;
  case CPprog::PSetCameraPosition: retour = "PSetCameraPosition"; break;
  case CPprog::PCameraRotate: retour = "PCameraRotate"; break;
  case CPprog::PCameraSolidariser: retour = "PCameraSolidariser"; break;
  case CPprog::PCameraDesolidariser: retour = "PCameraDesolidariser"; break;
  case CPprog::PCameraDefaut: retour = "PCameraDefaut"; break;
  case CPprog::PCameraZoom: retour = "PCameraZoom"; break;
  case CPprog::PFrapper: retour = "PFrapper"; break;
  case CPprog::PAjouterAnime: retour = "PAjouterAnime"; break;
  case CPprog::PAjouterNonAnime: retour = "PAjouterNonAnime"; break;
  case CPprog::PSetTemps: retour = "PSetTemps"; break;
  case CPprog::PSetOrientation: retour = "PSetOrientation"; break;
  case CPprog::PWaitFor: retour = "PWaitFor"; break;
  case CPprog::PBloquerTemps: retour = "PBloquerTemps"; break;
  case CPprog::PDebloquerTemps: retour = "PDebloquerTemps"; break;

  case CPprog::PWritelnStack: retour = "PWritelnStack"; break;
  case CPprog::PReadlnStack: retour = "PReadlnStack"; break;
  case CPprog::PMusiqueStack: retour = "PMusiqueStack"; break;
  case CPprog::PWaitStack: retour = "PWaitStack"; break;
  case CPprog::PFonduStack: retour = "PFonduStack"; break;
  case CPprog::PRecArmeStack: retour = "PRecArmeStack"; break;
  case CPprog::PSupObjetStack: retour = "PSupObjetStack"; break;
  case CPprog::PCarteStack: retour = "PCarteStack"; break;
  case CPprog::PCarteZStack: retour = "PCarteZStack"; break;
  case CPprog::PSetPositionStack: retour = "PSetPositionStack"; break;
  case CPprog::PSetPositionZStack: retour = "PSetPositionZStack"; break;
  case CPprog::PDeplacerStack: retour = "PDeplacerStack"; break;
  case CPprog::PSetCameraPositionStack: retour = "PSetCameraPositionStack"; break;
  case CPprog::PCameraRotateStack: retour = "PCameraRotateStack"; break;
  case CPprog::PCameraZoomStack: retour = "PCameraZoomStack"; break;
  case CPprog::PFrapperStack: retour = "PFrapperStack"; break;
  case CPprog::PAjouterAnimeStack: retour = "PAjouterAnimeStack"; break;
  case CPprog::PAjouterNonAnimeStack: retour = "PAjouterNonAnimeStack"; break;
  case CPprog::PSetOrientationStack: retour = "PSetOrientationStack"; break;
  case CPprog::PWaitForStack: retour = "PWaitForStack"; break;
  case CPprog::PExprStack: retour = "PExprStack"; break;
  case CPprog::PIfStack: retour = "PIfStack"; break;
  case CPprog::PWhileStack: retour = "PWhileStack"; break;
  case CPprog::PForStack: retour = "PForStack"; break;
  case CPprog::PConstStack: retour = "PConstStack"; break;
  case CPprog::PAffectationStack: retour = "PAffectationStack"; break;
  case CPprog::PCallStack: retour = "PCallStack"; break;
  case CPprog::PSetTempsStack: retour = "PSetTempsStack"; break;

  default: assert(false); return false;
  }

  return retour;
}














//  enum etype {PStop, PSkip, PSeq, PIf, PWhile, PFor, PRepeat, PBegin, PVar, PConst, PAffectation, PWrite, PWriteln, PRead, PReadln};
static unsigned int prof = (unsigned int) -2;
static char * indent(const char * str) {
  const unsigned int taille = (str ? strlen(str) : 0);
  char * temp = new char[prof + 2 + taille];

  temp[0] = '\n';
  for (unsigned int i = 1; i <= prof; i++) {
    temp[i] = ' ';
  }
  for (unsigned int i = 0; i < taille; i ++) {
    temp[i + prof + 1] = str[i];
  }
  temp[taille + prof + 1] = '\0';
  return temp;
}

char * CPprog::toString(void) const {
  char * a, * b, * c, * d, * e, * f, * g, * h, * i, * j, * k, * l, * m;
  const char * aa, * bb, * cc, * dd, * ee, * ff, * gg, * hh, * ii, * jj, * kk, * ll, * mm;
  char * ret;
  class pliste<CPexpr> * temp;

  //pmessage("Appel de CPprog::toString(void) ; prof = %d", prof);

  prof += 2;
  switch (type) {
  case PStop: pmessage("STOP"); ret = indent("Stop"); break;
  case PSkip: pmessage("SKIP"); ret = indent("Skip"); break;
  case PSeq: pmessage("SEQ"); 
    prof -= 2;
    a = val.upseq.p1->toString();
    bb = ";";
    c = val.upseq.p2->toString();
    prof += 2;
    ret = STRCAT3_(a,bb,c);
    // --1-- delete [] a;
    // --1-- delete [] c;
    break;

  case PIf:pmessage("IF"); 
    a = indent("If ");
    b = val.upif.b->toString();
    cc = " Then";
    d = val.upif.p->toString();
    e = indent("Else");
    f = val.upif.q->toString();
    g = indent("End");
    ret = STRCAT7_(a,b,cc,d,e,f,g);
    // --1-- delete [] a;
    // --1-- delete [] b;
    // --1-- delete [] d;
    // --1-- delete [] e;
    // --1-- delete [] f;
    // --1-- delete [] g;
    break;

  case PWhile:pmessage("WHILE"); 
    a = indent("While ");
    b = val.upwhile.b->toString();
    cc = " Do";
    d = val.upwhile.p->toString();
    ret = STRCAT4_(a,b,cc,d);
    // --1-- delete [] a;
    // --1-- delete [] b;
    // --1-- delete [] d;
    break;

  case PFor:pmessage("FOR"); 
    a = indent("For ");
    b = val.upfor.i;
    cc = " := ";
    d = val.upfor.e1->toString();
    ee = " To ";
    f = val.upfor.e2->toString();
    gg = " Do";
    h = val.upfor.p->toString();
    ret = STRCAT8_(a,b,cc,d,ee,f,gg,h);
    // --1-- delete [] a;
    // --1-- delete [] d;
    // --1-- delete [] f;
    // --1-- delete [] h;
    break;

  case PRepeat:pmessage("REPEAT"); 
    a = indent("Repeat");
    b = val.uprepeat.p->toString();
    c = indent("Until ");
    d = val.uprepeat.b->toString();
    ret = STRCAT4_(a,b,c,d);
    // --1-- delete [] a;
    // --1-- delete [] b;
    // --1-- delete [] c;
    // --1-- delete [] d;
    break;

  case PBegin:pmessage("BEGIN");
    a = indent("Begin");
    b = val.upbegin.p->toString();
    c = indent("End");
    ret = STRCAT3_(a,b,c);
    // --1-- delete [] a;
    // --1-- delete [] b;
    // --1-- delete [] c;
    break;

  case PVar:pmessage("VAR"); 
    a = indent("Var ");
    b = val.upvar.nom;
    cc = " : ";
    d = val.upvar.t.toString();
    ret = STRCAT4_(a,b,cc,d);
    // --1-- delete [] a;
    // --1-- delete [] d;
    break;

  case PConst:pmessage("CONST"); 
    a = indent("Const ");
    b = val.upconst.nom;
    cc = " = ";
    d = val.upconst.val->toString();
    ret = STRCAT4_(a,b,cc,d);
    // --1-- delete [] a;
    // --1-- delete [] d;
    break;

  case PAffectation:pmessage("AFFECTATION"); 
    b = val.upaffectation.lval->toString();
    a = indent(b);
    // --1-- delete [] b;
    bb = " := ";
    c = val.upaffectation.e->toString();
    ret = STRCAT3_(a,bb,c);
    // --1-- delete a;
    // --1-- delete c;
    break;

  case PWrite:pmessage("WRITE"); 
    a = indent("Write(");
    temp = val.upwrite.le;
    cc = ", ";
    while (temp != NULL) {
      b = temp->a->toString();
      d = STRCAT3_(a,b,cc);
      // --1-- delete [] a;
      // --1-- delete [] b;
      a = d;
      temp = temp->suivant;
    }
    bb = ")";
    ret = STRCAT2_(a,bb);
    // --1-- delete [] a;
    break;

  case PWriteln:pmessage("WRITELN"); 
    a = indent("Writeln(");
    temp = val.upwriteln.le;
    cc = ", ";
    while (temp != NULL) {
      b = temp->a->toString();
      pmessage("%s ; temp->suivant : %p", b, temp->suivant);
      d = STRCAT3_(a,b,cc);
      // --1-- delete [] a;
      // --1-- delete [] b;
      a = d;
      temp = temp->suivant;
    }
    bb = ")";
    ret = STRCAT2_(a,bb);
    // --1-- delete [] a;
    pmessage("Fin Writeln");
    break;

  case PRead:pmessage("READ"); 
    a = indent("Read(");
    temp = val.upread.llval;
    cc = ", ";
    while (temp != NULL) {
      b = temp->a->toString();
      d = STRCAT3_(a,b,cc);
      // --1-- delete [] a;
      // --1-- delete [] b;
      a = d;
      temp = temp->suivant;
    }
    bb = ")";
    ret = STRCAT2_(a,bb);
    // --1-- delete [] a;
    break;

  case PReadln:pmessage("READLN"); 
    a = indent("Readln(");
    temp = val.upreadln.llval;
    cc = ", ";
    while (temp != NULL) {
      b = temp->a->toString();
      d = STRCAT3_(a,b,cc);
      // --1-- delete [] a;
      // --1-- delete [] b;
      a = d;
      temp = temp->suivant;
    }
    bb = ")";
    ret = STRCAT2_(a,bb);
    // --1-- delete [] a;
    break;

  case PType:pmessage("TYPE"); 
    a = indent("Type ");
    b = val.uptype.ident;
    cc = " = ";
    d = val.uptype.dvaltype.toString();
    ret = STRCAT4_(a,b,cc,d);
    // --1-- delete [] a;
    // --1-- delete [] d;
    break;

  case PNew:pmessage("NEW"); 
    a = indent("New ( ");
    b = val.upnew.ident;
    cc = " ) ";
    ret = STRCAT3_(a,b,cc);
    // --1-- delete [] a;
    break;

  case PCall:pmessage("CALL"); 
    a = indent(val.upcall.ident);
    bb = " ( ";
    c = STRCAT2_(a,bb);
    // --1-- delete [] a;
    a = c;
    cc = " , ";
    temp = val.upcall.args;
    while (temp != NULL) {
      b = temp->a->toString();
      d = STRCAT3_(a,b,cc);
      // --1-- delete [] a;
      // --1-- delete [] b;
      a = d;
      temp = temp->suivant;
    }
    bb = " ) ";
    ret = STRCAT2_(a,bb);
    // --1-- delete [] a;
    break;

  case PMusique:pmessage("MUSIQUE"); 
    a = indent("Musique (");
    b = val.upmusique.musique->toString();
    cc = " ) ";
    ret = STRCAT3_(a,b,cc);
    // --1-- delete [] a;
    // --1-- delete [] b;
    break;

  case PWait: ret = indent("Wait()"); break;
  case PHalt: ret = indent("Halt()"); break;
  case PRestart: ret = indent("Restart()"); break;

  case PFondu:
    a = indent("Fondu(");
    b = val.upfondu.couleur->toString();
    cc = ")";
    ret = STRCAT3_(a,b,cc);
    // --1-- delete [] a;
    // --1-- delete [] b;
    break;

  case PRecObjet:
    a = indent("RecevoirObjet(");
    b = val.uprecobjet.nom;
    cc = ")";
    ret = STRCAT3_(a,b,cc);
    // --1-- delete [] a;
    break;

  case PRecArme:
    a = indent("RecevoirArme(");
    b = val.uprecarme.nom->toString();
    cc = ")";
    ret = STRCAT3_(a,b,cc);
    // --1-- delete [] a;
    break;

  case PSupObjet:
    a = indent("DetruireObjet(");
    b = val.upsupobjet.nom->toString();
    cc = ")";
    ret = STRCAT3_(a,b,cc);
    // --1-- delete [] a;
    break;

  case PCarte:
    a = indent("Carte(");
    b = val.upcarte.nom->toString();
    cc = ")";
    ret = STRCAT3_(a,b,cc);
    // --1-- delete [] a;
    break;

  case PSetPosition:
    b = val.upsetpos.nom -> toString () ;
    a = indent(b);
    // --1-- delete [] b;
    bb = " -> SetPosition ( ";
    c = val.upsetpos.x -> toString () ;
    dd = " , ";
    e = val.upsetpos.y -> toString () ;
    ff = " , ";
    g = val.upsetpos.relatif -> toString () ;
    hh = " ) ";
    ret = STRCAT8_(a,bb,c,dd,e,ff,g,hh);
    // --1-- delete [] a;
    // --1-- delete [] c;
    // --1-- delete [] e;
    // --1-- delete [] g;
    break;

  case PSetPositionZ:
    b = val.upsetposz.nom -> toString () ;
    a = indent(b);
    // --1-- delete [] b;
    bb = " -> SetPositionZ ( ";
    c = val.upsetposz.x -> toString () ;
    dd = " , ";
    e = val.upsetposz.y -> toString () ;
    ff = " , ";
    g = val.upsetposz.z -> toString () ;
    hh = " , ";
    i = val.upsetpos.relatif -> toString () ;
    jj = ")"; 
    ret = STRCAT10_(a,bb,c,dd,e,ff,g,hh,i,jj);
    // --1-- delete [] a;
    // --1-- delete [] c;
    // --1-- delete [] e;
    // --1-- delete [] g;
    // --1-- delete [] i;
    break;

  case PDeplacer:
    b = val.updeplacer.nom -> toString();
    a = indent(b);
    // --1-- delete [] b;
    bb = " -> Deplacer ( ";
    c = val.updeplacer.x -> toString () ;
    dd = " , ";
    e = val.updeplacer.y -> toString () ;
    ff = " , ";
    g = val.updeplacer.relatif -> toString () ;
    hh = " ) ";
    ret = STRCAT8_(a,bb,c,dd,e,ff,g,hh);
    // --1-- delete [] a;
    // --1-- delete [] c;
    // --1-- delete [] e;
    // --1-- delete [] g;
    break;

  case PDeplacerZ:
    b = val.updeplacerz.nom -> toString () ;
    a = indent(b);
    // --1-- delete [] b;
    bb = " -> DeplacerZ ( ";
    c = val.updeplacerz.x -> toString ();
    dd = " , ";
    e = val.updeplacerz.y -> toString () ;
    ff = " , ";
    g = val.updeplacerz.z -> toString () ;
    hh = " , ";
    i = val.updeplacerz.relatif -> toString () ;
    jj = " ) ";
    ret = STRCAT10_(a,bb,c,dd,e,ff,g,hh,i,jj);
    // --1-- delete [] a;
    // --1-- delete [] c;
    // --1-- delete [] e;
    // --1-- delete [] g;
    // --1-- delete [] i;
    break;

  case PSetHerosPosition:
    b = indent("Heros -> SetPosition ( ");
    c = ftoa(val.upsetherospos.x);
    dd = " , ";
    e = ftoa(val.upsetherospos.y);
    ff = " , ";
    gg = string_of_enum_methode(val.upsetherospos.relatif);
    hh = " , ";
    ii = string_of_enum_direction(val.upsetherospos.dir);
    jj = " ) ";
    ret = STRCAT9_(b,c,dd,e,ff,gg,hh,ii,jj);
    // --1-- delete [] b;
    // --1-- delete [] c;
    // --1-- delete [] e;
    // --1-- delete [] g;
    // --1-- delete [] i;
    break;

  case PSetHerosPositionZ:
    b = indent("Heros -> SetPositionZ ( ");
    c = ftoa(val.upsetherosposz.x);
    dd = " , ";
    e = ftoa(val.upsetherosposz.y);
    ff = " , ";
    g = ftoa(val.upsetherosposz.z);
    hh = " , ";
    ii = string_of_enum_methode(val.upsetherosposz.relatif);
    jj = " , ";
    kk = string_of_enum_direction(val.upsetherosposz.dir);
    ll = " ) ";
    ret = STRCAT11_(b,c,dd,e,ff,g,hh,ii,jj,kk,ll);
    // --1-- delete [] b;
    // --1-- delete [] c;
    // --1-- delete [] e;
    // --1-- delete [] g;
    // --1-- delete [] i;
    // --1-- delete [] k;
    break;

  case PHerosDeplacer:
    b = indent("Heros -> Deplacer ( ");
    c = ftoa(val.upherosdeplacer.x);
    dd = " , ";
    e = ftoa(val.upherosdeplacer.y);
    ff = " , ";
    gg = string_of_enum_methode(val.upherosdeplacer.relatif);
    hh = " , ";
    ii = string_of_enum_direction(val.upherosdeplacer.dir);
    jj = " ) ";
    ret = STRCAT9_(b,c,dd,e,ff,gg,hh,ii,jj);
    // --1-- delete [] b;
    // --1-- delete [] c;
    // --1-- delete [] e;
    // --1-- delete [] g;
    // --1-- delete [] i;
    break;

  case PHerosDeplacerZ:
    b = indent("Heros -> DeplacerZ ( ");
    c = ftoa(val.upherosdeplacerz.x);
    dd = " , ";
    e = ftoa(val.upherosdeplacerz.y);
    ff = " , ";
    g = ftoa(val.upherosdeplacerz.z);
    hh = " , ";
    ii = string_of_enum_methode(val.upherosdeplacerz.relatif);
    jj = " , ";
    kk = string_of_enum_direction(val.upherosdeplacerz.dir);
    ll = " ) ";
    ret = STRCAT11_(b,c,dd,e,ff,g,hh,ii,jj,kk,ll);
    // --1-- delete [] b;
    // --1-- delete [] c;
    // --1-- delete [] e;
    // --1-- delete [] g;
    // --1-- delete [] i;
    // --1-- delete [] k;
    break;

  case PCameraDeplacer:
    a = indent("Camera -> Deplacer ( ");
    b = val.upcameradeplacer.x -> toString () ;
    cc = " , ";
    d = val.upcameradeplacer.y -> toString () ;
    ee = " , ";
    f = val.upcameradeplacer.z -> toString () ;
    gg = " , ";
    h = val.upcameradeplacer.relatif -> toString () ;
    ii = " ) ";
    ret = STRCAT9_(a,b,cc,d,ee,f,gg,h,ii);
    // --1-- delete [] a;
    // --1-- delete [] b;
    // --1-- delete [] d;
    // --1-- delete [] f;
    // --1-- delete [] h;
    break;

  case PSetCameraPosition:
    a = indent("Camera -> SetPosition ( ");
    b = val.upsetcamerapos.x -> toString () ;
    cc = " , ";
    d = val.upsetcamerapos.y -> toString () ;
    ee = " , ";
    f = val.upsetcamerapos.z -> toString () ;
    gg = " , ";
    h = val.upsetcamerapos.relatif -> toString () ;
    ii = " ) ";
    ret = STRCAT9_(a,b,cc,d,ee,f,gg,h,ii);
    // --1-- delete [] a;
    // --1-- delete [] b;
    // --1-- delete [] d;
    // --1-- delete [] f;
    // --1-- delete [] h;
    break;

  case PCameraRotate:
    a = indent("Camera -> Rotate ( ");
    b = val.upcamerarotate.angle_x -> toString () ;
    cc = " , ";
    d = val.upcamerarotate.angle_y -> toString () ;
    ee = " , ";
    f = val.upcamerarotate.angle_z -> toString () ;
    gg = " , ";
    h = val.upcamerarotate.relatif -> toString () ;
    ii = " ) ";
    ret = STRCAT9_(a,b,cc,d,ee,f,gg,h,ii);
    // --1-- delete [] a;
    // --1-- delete [] b;
    // --1-- delete [] d;
    // --1-- delete [] f;
    // --1-- delete [] h;
    break;

  case PCameraSolidariser: ret = indent("Camera -> Solidariser()"); break;
  case PCameraDesolidariser: ret = indent("Camera -> Desolidariser()"); break;
  case PCameraDefaut: ret = indent("Camera -> Defaut()"); break;

  case PCameraZoom:
    a = indent("Camera -> Zoom ( ");
    b = val.upcamerazoom.coeff -> toString () ;
    cc = " ) ";
    ret = STRCAT3_(a,b,cc);
    // --1-- delete [] a;
    // --1-- delete [] b;
    break;

  case PFrapper:
    b = val.upfrapper.nom -> toString ();
    a = indent(b);
    // --1-- delete [] b;
    bb = " -> Frapper ( ) ";
    ret = STRCAT2_(a,bb);
    // --1-- delete [] a;
    break;

  case PAjouterAnime:
    a = indent("AjouterAnime ( ");
    b = val.upajouteranime.nom -> toString () ;
    cc = " , ";
    d = val.upajouteranime.fichier -> toString () ;
    ee = " ) ";
    ret = STRCAT5_(a,b,cc,d,ee);
    // --1-- delete [] a;
    // --1-- delete [] b;
    // --1-- delete [] d;
    break;

  case PAjouterNonAnime:
    a = indent("AjouterNonAnime ( ");
    b = val.upajouternonanime.nom -> toString () ;
    cc = " , ";
    d = val.upajouternonanime.fichier -> toString () ;
    ee = " ) ";
    ret = STRCAT5_(a,b,cc,d,ee);
    // --1-- delete [] a;
    // --1-- delete [] b;
    // --1-- delete [] d;
    break;

  case PSetTemps:
    a = indent("SetTemps ( ");
    b = val.upsettemps.temps ->toString();
    cc = " ) ";
    ret = STRCAT3_(a,b,cc);
    // --1-- delete [] a;
    // --1-- delete [] b;
    break;

  case PSetOrientation:
    b = val.upsetorientation.nom -> toString () ;
    a = indent(b);
    // --1-- delete [] b;
    bb = " -> SetOrientation ( ";
    c = val.upsetorientation.orientation -> toString();
    dd = " ) ";
    ret = STRCAT4_(a,bb,c,dd);
    // --1-- delete [] a;
    // --1-- delete [] c;
    break;

  case PWaitFor:
    a = indent("WaitFor ( ");
    b = val.upwaitfor.nom -> toString ();
    cc = " ) ";
    ret = STRCAT3_(a,b,cc);
    // --1-- delete [] a;
    // --1-- delete [] b;
    break;

  case PBloquerTemps: ret = indent("BloquerTemps (  ) "); break;
  case PDebloquerTemps: ret = indent("DebloquerTemps ( ) "); break;

  case PCarteZ:
    a = indent("CarteZ ( ");
    b = val.upcartez.nom -> toString () ;
    cc = " , ";
    d = val.upcartez.x -> toString () ;
    ee = " , ";
    f = val.upcartez.y -> toString ();
    gg = " , ";
    h = val.upcartez.z -> toString () ;
    ii = " , ";
    j = val.upcartez.direction -> toString () ;
    ret = STRCAT10_(a,b,cc,d,ee,f,gg,h,ii,j);
    // --1-- delete [] a;
    // --1-- delete [] b;
    // --1-- delete [] d;
    // --1-- delete [] f;
    // --1-- delete [] h;
    // --1-- delete [] j;
    break;



  case CPprog::PWritelnStack: ret = strcopy("PWritelnStack"); break;
  case CPprog::PReadlnStack: ret = strcopy("PReadlnStack"); break;
  case CPprog::PMusiqueStack: ret = strcopy("PMusiqueStack"); break;
  case CPprog::PWaitStack: ret = strcopy("PWaitStack"); break;
  case CPprog::PFonduStack: ret = strcopy("PFonduStack"); break;
  case CPprog::PRecArmeStack: ret = strcopy("PRecArmeStack"); break;
  case CPprog::PSupObjetStack: ret = strcopy("PSupObjetStack"); break;
  case CPprog::PCarteStack: ret = strcopy("PCarteStack"); break;
  case CPprog::PCarteZStack: ret = strcopy("PCarteZStack"); break;
  case CPprog::PSetPositionStack: ret = strcopy("PSetPositionStack"); break;
  case CPprog::PSetPositionZStack: ret = strcopy("PSetPositionZStack"); break;
  case CPprog::PDeplacerStack: ret = strcopy("PDeplacerStack"); break;
  case CPprog::PSetCameraPositionStack: ret = strcopy("PSetCameraPositionStack"); break;
  case CPprog::PCameraRotateStack: ret = strcopy("PCameraRotateStack"); break;
  case CPprog::PCameraZoomStack: ret = strcopy("PCameraZoomStack"); break;
  case CPprog::PFrapperStack: ret = strcopy("PFrapperStack"); break;
  case CPprog::PAjouterAnimeStack: ret = strcopy("PAjouterAnimeStack"); break;
  case CPprog::PAjouterNonAnimeStack: ret = strcopy("PAjouterNonAnimeStack"); break;
  case CPprog::PSetOrientationStack: ret = strcopy("PSetOrientationStack"); break;
  case CPprog::PWaitForStack: ret = strcopy("PWaitForStack"); break;
  case CPprog::PExprStack: ret = strcopy("PExprStack"); break;
  case CPprog::PIfStack: ret = strcopy("PIfStack"); break;
  case CPprog::PWhileStack: ret = strcopy("PWhileStack"); break;
  case CPprog::PForStack: ret = strcopy("PForStack"); break;
  case CPprog::PConstStack: ret = strcopy("PConstStack"); break;
  case CPprog::PAffectationStack: ret = strcopy("PAffectationStack"); break;
  case CPprog::PCallStack: ret = strcopy("PCallStack"); break;
  case CPprog::PSetTempsStack: ret = strcopy("PSetTempsStack"); break;

  default: pmesserr("CPprog::toString(): instruction inconnue"); ret = NULL; assert(false);
  }

  prof -= 2;
  return ret;
}



int CPprog::execute(void) {
  penv env = env0;
  pmem mem = mem0;

  return execute(env, mem);
}



#define _PRECALCUL_TYPE(WHAT) {                                         \
    /* PRECALCUL de SUBRANGE. */                                        \
    if (WHAT .type == pdvaltype::PDTSubrange) {                         \
                                                                        \
      if (WHAT .val.s.mine != NULL) {                                   \
        VERIF_OK(WHAT .val.s.mine->r_evaluate(env, mem, e1));           \
        /* --1-- delete WHAT .val.s.mine; */                            \
        WHAT .val.s.mine = NULL;                                        \
                                                                        \
        if (e1.type.type == pevaltype::PETInteger) {                    \
          WHAT .val.s.min = e1.val.val.i;                               \
        }                                                               \
        else if (e1.type.type == pevaltype::PETSubrange) {              \
          WHAT .val.s.min = e1.val.val.s;                               \
        }                                                               \
        else {                                                          \
          pmesserr(position.toString());                                \
          pmesserr("CPprog:execute: PType: lors de la création d'un type subrange, mine n'est pas de type scalaire (%s).",e1.type.toString()); \
          return -97;                                                   \
        }                                                               \
                                                                        \
      }                                                                 \
                                                                        \
      if (WHAT .val.s.maxe != NULL) {                                   \
        VERIF_OK(WHAT .val.s.maxe->r_evaluate(env, mem, e2));           \
        /* --1-- delete WHAT .val.s.maxe; */                            \
        WHAT .val.s.maxe = NULL;                                        \
      	                                                                \
        if (e2.type.type == pevaltype::PETInteger) {                    \
          WHAT .val.s.max = e2.val.val.i;                               \
        }                                                               \
        else if (e2.type.type == pevaltype::PETSubrange) {              \
          WHAT .val.s.max = e2.val.val.s;                               \
        }                                                               \
        else {                                                          \
          pmesserr(position.toString());                                \
          pmesserr("CPprog:execute: PType: lors de la création d'un type subrange, maxe n'est pas de type scalaire (%s).",e2.type.toString()); \
          return -95;                                                   \
        }                                                               \
                                                                        \
      }                                                                 \
                                                                        \
      if (WHAT .val.s.min > WHAT .val.s.max) {                          \
        pmesserr(position.toString());                                  \
        pmesserr("CPprog:execute: PType: lors de la création d'un type subrange, min de valeur %d est supérieur à max %d !", WHAT .val.s.min, WHAT .val.s.max); \
        return -98;                                                     \
      }                                                                 \
    }                                                                   \
                                                                        \
                                                                        \
    /* PRECALCUL DE ARRAY. */                                           \
    else if (WHAT .type == pdvaltype::PDTArray) {                       \
                                                                        \
      if (WHAT .val.array.indice.mine != NULL) {                        \
        VERIF_OK(WHAT .val.array.indice.mine->r_evaluate(env, mem, e1)); \
        pmesserr("e1: %s", e1.toString());                              \
        /* --1-- delete WHAT .val.array.indice.mine; */                 \
        WHAT .val.array.indice.mine = NULL;                             \
                                                                        \
        if (e1.type.type == pevaltype::PETInteger) {                    \
          WHAT .val.array.indice.min = e1.val.val.i;                    \
        }                                                               \
        else if (e1.type.type == pevaltype::PETSubrange) {              \
          WHAT .val.array.indice.min = e1.val.val.s;                    \
        }                                                               \
        else {                                                          \
          pmesserr(position.toString());                                \
          pmesserr("CPprog:execute: PType: lors de la création d'un type array, mine n'est pas de type scalaire (%s).",e1.type.toString()); \
          return -922;                                                  \
        }                                                               \
                                                                        \
      }                                                                 \
                                                                        \
      if (WHAT .val.array.indice.maxe != NULL) {                        \
        VERIF_OK(WHAT .val.array.indice.maxe->r_evaluate(env, mem, e2)); \
        pmesserr("e2: %s", e2.toString());                              \
        /* --1-- delete WHAT .val.array.indice.maxe; */                 \
        WHAT .val.array.indice.maxe = NULL;                             \
	                                                                \
        if (e2.type.type == pevaltype::PETInteger) {                    \
          WHAT .val.array.indice.max = e2.val.val.i;                    \
        }                                                               \
        else if (e2.type.type == pevaltype::PETSubrange) {              \
          WHAT .val.array.indice.max = e2.val.val.s;                    \
        }                                                               \
        else {                                                          \
          pmesserr(position.toString());                                \
          pmesserr("CPprog:execute: PType: lors de la création d'un type array, maxe n'est pas de type scalaire (%s).",e2.type.toString()); \
          return -917;                                                  \
        }                                                               \
                                                                        \
      }                                                                 \
                                                                        \
      if (WHAT .val.array.indice.min > WHAT .val.array.indice.max) {    \
        pmesserr(position.toString());                                  \
        pmesserr("CPprog:execute: PType: lors de la création d'un type array, min de valeur %d est supérieur à max %d !", WHAT .val.array.indice.min, WHAT .val.array.indice.max); \
        return -915;                                                    \
      }                                                                 \
    }                                                                   \
  }                                                                     \
                                                                        \
    


#define PRECALCUL_TYPE(WHAT) 				\
  {if (WHAT .type == pdvaltype::PDTFunction) {          \
      _PRECALCUL_TYPE((*(WHAT .val.func.type)));        \
    }							\
    else {                                              \
      _PRECALCUL_TYPE(WHAT);				\
    }}                                                  \








bool futur_expr_to_prog(pascal_expr_futur_t * futur_expr, CPprog * &futur_prog) {
  CPprog * prog = new class CPprog(0, 0, 0, 0, 0, 0);
  prog -> type = CPprog::PExprStack;
  prog -> val.upexprstack.futur_expr = futur_expr;
  futur_prog = prog;
  return true;
}




CPprog * prog_seq2(CPprog * p1, CPprog * p2);
CPprog * prog_seq2(CPprog * p1, CPprog * p2) {
  CPprog * seq2 = new class CPprog(0, 0, 0, 0, 0, 0);
  seq2 -> type = CPprog::PSeq;
  seq2 -> val.upseq.p1 = p1;
  seq2 -> val.upseq.p2 = p2;
  return seq2;
}

CPprog * prog_seq3(CPprog * p1, CPprog * p2, CPprog * p3) {
  return prog_seq2(p1, prog_seq2(p2, p3));
}

CPprog * prog_seq4(CPprog * p1, CPprog * p2, CPprog * p3, CPprog * p4) {
  return prog_seq2(p1, prog_seq3(p2, p3, p4));
}




int CPprog::execute(penv &env, pmem &mem) {
  CPprog * futur, * current;
  int ret;
  pascal_stack_t * stack;
  
  stack = pascal_stack_make();

  futur = this;

  do {
    current = futur;
    futur = NULL;
    ret = current -> execute_step(env, mem, stack, futur);
    if (ret != 0)
      return ret;
  } while (futur != NULL);

  return 0;
}





#define PROG_FUTUR_PUSH_EXPR(eeeeee) {                                  \
      CPexpr * expr = (eeeeee);                                         \
      CPprog * futur_l = NULL;                                          \
      pascal_expr_futur_t * futur_expr_l = NULL;                        \
      VERIF_OK_B(pascal_expr_compile(expr, futur_expr_l));              \
      VERIF_OK_B(futur_expr_to_prog(futur_expr_l, futur_l));            \
      futur = prog_seq2(futur_l, futur);                                \
    }







//int CPprog::execute(penv &env, pmem &mem) {
//int CPprog::execute_step(penv &env, pmem &mem, CPprog * &futur) {
int CPprog::execute_step(penv &env, pmem &mem, pascal_stack_t * stack, CPprog * &futur) {
  pevalt b, e, e1, e2, lval;
  pevalt * b_ptr, * e_ptr, * e1_ptr, * e2_ptr, * lval_ptr;
  psval sval;
  ploc i;
  int ret;
  pdvalt dvalt;
  pdval dval;
  pdvaltype dvaltype;
  struct pascal_dval_type_user *dvaltypeuser_ptr;
  unsigned int taille;


  CPprog * futur1 = NULL;
  CPprog * futur2 = NULL;
  CPprog * futur3 = NULL;
  pascal_prog_futur_cell_t * futur_cell = NULL;
  pascal_prog_futur_cell_t * futur_cell1 = NULL;
  pascal_prog_futur_cell_t * futur_cell2 = NULL;
  pascal_expr_futur_t * futur_expr1 = NULL;
  pascal_expr_futur_t * futur_expr2 = NULL;
  CPexpr * expr = NULL;

  if (this == NULL)
    return 0;


  futur = NULL;

  //return 0;
  //fprintf(stderr, "TYPE: %s\n", cprog_etype(type));



  switch (type) {
    
    // Cette instruction interne arrête l'exécution courante.
    // Plus de futur.
  case PStop: return 0;  break;

    // Cette instruction magique ne fait rien.
    // Elle est pseudo-interne, puisqu'elle peut-être atteinte indirectement avec un ";;".
  case PSkip: return 0;  break;

  case PSeq:
    VERIF_OK(val.upseq.p1->execute_step(env, mem, stack, futur1));
    futur2 = val.upseq.p2;

    if (futur1 == NULL)
      futur = futur2;
    else 
      futur = prog_seq2(futur1, futur2);

    return 0; 
    break;

  case PExprStack: {
    futur_expr1 = this -> val.upexprstack.futur_expr;
    if (futur_expr1 == NULL)
      return 0;

    VERIF_OK_B(r_evaluate_futur_step(futur_expr1 -> a, stack, env, mem));

    futur_expr2 = futur_expr1 -> suivant;
    VERIF_OK_B(futur_expr_to_prog(futur_expr2, futur2));
    futur = futur2;

    return 0;
  }
    break;

  case PIf: {
    VERIF_OK_B(pascal_expr_compile(this -> val.upif.b, futur_expr1));
    VERIF_OK_B(futur_expr_to_prog(futur_expr1, futur1));

    CPprog * futur2 = new class CPprog(0, 0, 0, 0, 0, 0);
    futur2 -> type = CPprog::PIfStack;
    futur2 -> val.upif.p = val.upif.p;
    futur2 -> val.upif.q = val.upif.q;
    
    futur = prog_seq2(futur1, futur2);
        
    return 0;
  }
    break;

  case PIfStack:
    b_ptr = pascal_stack_pop(stack);
    
    VERIF_TYPE2(b_ptr,pevaltype::PETBoolean);
    
    if (b_ptr -> val.val.b) 
      futur = val.upif.p;
    else 
      futur = val.upif.q;
    
    return 0;
    break;

  case PWhile: {
    VERIF_OK_B(pascal_expr_compile(this -> val.upwhile.b, futur_expr1));
    VERIF_OK_B(futur_expr_to_prog(futur_expr1, futur1));

    CPprog * futur2 = new class CPprog(0, 0, 0, 0, 0, 0);
    futur2 -> type = CPprog::PWhileStack;
    futur2 -> val.upwhile.b = val.upwhile.b;
    futur2 -> val.upwhile.p = val.upwhile.p;
    
    futur = prog_seq2(futur1, futur2);
        
    return 0;
  }
    break;    

  case PWhileStack: {
    b_ptr = pascal_stack_pop(stack);

    VERIF_TYPE2(b_ptr,pevaltype::PETBoolean);

    if (b_ptr -> val.val.b) {
      futur1 = val.upwhile.p;

      CPprog * futur2 = new class CPprog(0, 0, 0, 0, 0, 0);
      futur2 -> type = CPprog::PWhile;
      futur2 -> val.upwhile.b = val.upwhile.b;
      futur2 -> val.upwhile.p = val.upwhile.p;

      futur = prog_seq2(futur1, futur2);
    }
    return 0;
  }
    break;

  case PFor: {
    futur = new class CPprog(this -> position);
    futur -> type = CPprog::PForStack;
    futur -> val = this -> val;

    PROG_FUTUR_PUSH_EXPR(this -> val.upfor.e1);
    PROG_FUTUR_PUSH_EXPR(this -> val.upfor.e2);
        
    return 0;
  }
    break;

  case PForStack:
    e1_ptr = pascal_stack_pop(stack);
    e2_ptr = pascal_stack_pop(stack);

    VERIF_TYPE2(e1_ptr,pevaltype::PETInteger);
    VERIF_TYPE2(e2_ptr,pevaltype::PETInteger);

    //fprintf(stderr, "PForStack: min = %d max = %d\n", e1_ptr -> val.val.i, e2_ptr -> val.val.i);
    futur = NULL;
    for (int j = e1_ptr -> val.val.i; j <= e2_ptr -> val.val.i; j++) {
      futur = prog_seq2(val.upfor.p, futur);
    }

    return 0;
    break;

  case PRepeat: {
    CPprog * futur2 = new class CPprog(0, 0, 0, 0, 0, 0);
    futur2->type = CPprog::PWhile;
    futur2->val.upwhile.b = val.uprepeat.b;
    futur2->val.upwhile.p = val.uprepeat.p;

    futur = prog_seq2(val.uprepeat.p, futur2);

    return 0;
  }
    break;

  case PBegin: futur = val.upbegin.p; return 0; break;

  case PVar:
    PRECALCUL_TYPE(val.upvar.t);
    
    pnew(mem, val.upvar.t.pdvaltype_sizeof(), mem, i);
    VERIF_OK(pdvalt::pdvalt_of_pdvaltype((val.upvar.t), i, dvalt));

    if (val.upvar.t.type == pdvaltype::PDTFunction) {
      // Ajout de la variable de retour.
      class CPprog * tempprog;
      tempprog = new class CPprog(0,0,0,0,0,0);
      tempprog->type = CPprog::PVar;
      tempprog->val.upvar.nom = this->val.upvar.nom;
      tempprog->val.upvar.t.type = pdvaltype::PDTRetour;
      tempprog->val.upvar.t.val.ret.type = &(this->val.upvar.t);
      
      class CPprog * tempprog2;
      tempprog2 = prog_seq2(tempprog, this->val.upvar.t.val.func.corps);

      // En fait on va rajouter la valeur de retour lors de l'appel,
      // car sinon on ne peut pas récupérer la valeur de retour.
      //this->val.upvar.t.val.func.corps = tempprog2;
      //dvalt.type.val.func.corps = tempprog2;
    }
    else if (val.upvar.t.type == pdvaltype::PDTRetour) {
      // positionnement de l'adresse de lecture.
      // vérifier celui de l'adresse d'écriture.
      pdvalt tempdvalt;
      VERIF_OK(penvlookup(env, val.upvar.nom, tempdvalt));

      if (tempdvalt.type.type == pdvaltype::PDTRetour) {
	dvalt.val.val.ret.read = tempdvalt.val.val.ret.read;
      }
      else if (tempdvalt.type.type == pdvaltype::PDTFunction) {
	dvalt.val.val.ret.read = tempdvalt.val.val.func;
      }
      else {
	pmesserr(position.toString());
	pmesserr("Bon c'est la dèche. En effet, apparemment il existe une fonction s'appelant '%s', mais on trouve dans l'environnement qu'un truc de type non fonctionnel (%s).", val.upvar.nom, tempdvalt.type.toString());
	return -95;
      }
    }

    penvupdate(env, val.upvar.nom, dvalt, env);

    // Ici pour etre sur que la recursivite marche.
    if (val.upvar.t.type == pdvaltype::PDTProcedure) {
      sval.proc.prog = val.upvar.t.val.proc.corps;
      pmemwrite(mem, i, sval);
      dvalt.type.val.proc.env = env; // implementation dependant :||
      VERIF_OK(penvmodify(env, val.upvar.nom, dvalt));
    }
    else if (val.upvar.t.type == pdvaltype::PDTFunction) {
      // Ajustement des variables comme pour le bon fonctionnement.
      sval.proc.prog = val.upvar.t.val.func.corps;
      pmemwrite(mem, i, sval);
    }

    return 0;
    break;


  case PConst: {
    pmessage("Ajout de la constante %s à l'environnement.", val.upconst.nom);
    //VERIF_OK(val.upconst.val->r_evaluate(env, mem, e));
    VERIF_OK_B(pascal_expr_compile(this -> val.upconst.val, futur_expr1));
    VERIF_OK_B(futur_expr_to_prog(futur_expr1, futur1));

    CPprog * futur3 = new class CPprog(0, 0, 0, 0, 0, 0);
    futur3 -> type = CPprog::PConstStack;
    futur3 -> val = this -> val;

    futur = prog_seq2(futur1, futur3);

    return 0;
  }
    break;

  case PConstStack:
    e_ptr = pascal_stack_pop(stack);

    // Allocation d'une valeur constante dans la table des symboles.
    // On ne touche donc pas à la mémoire.
    // On vérifie d'abord que le type donné est bien un type
    // que l'on peut mettre dans les constantes.
    // (Un jour lorsque le langage marchera, on pourra mettre autre chose que de simples types).
    dvaltype.type = pdvaltype::PDTConstante;
    switch (e_ptr -> type.type) {
    case pevaltype::PETBoolean: dvaltype.val.c = pdvaltype::PCTBoolean; dval.val.c.b = e_ptr -> val.val.b; break;
    case pevaltype::PETInteger: dvaltype.val.c = pdvaltype::PCTInteger; dval.val.c.i = e_ptr -> val.val.i; break;
    case pevaltype::PETReal:    dvaltype.val.c = pdvaltype::PCTReal;    dval.val.c.r = e_ptr -> val.val.r; break;
    case pevaltype::PETString:  dvaltype.val.c = pdvaltype::PCTString;  dval.val.c.str = e_ptr -> val.val.str; break;
    case pevaltype::PETDummy:
    case pevaltype::PETSubrange:
    case pevaltype::PETPointer:
    case pevaltype::PETArray:
    case pevaltype::PETRecord:
    case pevaltype::PETVide:
    default: pmesserr(position.toString()); pmesserr("Désolé, mais le type \"%s\" ne peut pas encore être choisi comme constante. Attend encore un peu.", e_ptr -> type.toString()); return -101;
    }

    dvalt.type = dvaltype;
    dvalt.val = dval;
    penvupdate(env, val.upconst.nom, dvalt, env);
    return 0;
    break;


  case PAffectation: {
    // On a des vérifications à faire des deux côtés du symbole: 
    //  - il faut vérifier que le type du membre de gauche est bien un pointeur
    //  - et que le type de chaque côté est le même.
    VERIF_OK_B(pascal_expr_compile(this -> val.upaffectation.e, futur_expr1));
    VERIF_OK_B(pascal_expr_compile_l(this -> val.upaffectation.lval, futur_expr2));
    VERIF_OK_B(futur_expr_to_prog(futur_expr1, futur1));
    VERIF_OK_B(futur_expr_to_prog(futur_expr2, futur2));
    // TODO l-évalué normalement…

    CPprog * futur3 = new class CPprog(0, 0, 0, 0, 0, 0);
    futur3 -> type = CPprog::PAffectationStack;
    futur3 -> val.upaffectation.e = val.upaffectation.e;
    futur3 -> val.upaffectation.lval = val.upaffectation.lval;

    futur = prog_seq3(futur1, futur2, futur3);

    return 0;
  }
    break;


  case PAffectationStack:
    lval_ptr = pascal_stack_pop(stack);
    e_ptr = pascal_stack_pop(stack);

    VERIF_TYPE2(lval_ptr,pevaltype::PETPointer);
    VERIF_TYPE_EQUAL3(*(lval_ptr -> type.val.ptr),e_ptr -> type);

    VERIF_OK(e_ptr -> toPSVal(sval));

    VERIF_OK(pmemwrite(mem, lval_ptr -> val.val.ptr, sval));

    return 0;
    break;


  case PWrite:
  case PWriteln: {
      futur = new class CPprog(this -> position);
      futur -> type = CPprog::PWritelnStack;
      futur -> val = this -> val;

      class pliste<CPexpr> *temp;
      class pliste<CPprog> *args, *p;
      
      temp = val.upwrite.le;
      args = NULL;
      
      while (temp != NULL) {
        VERIF_OK_B(pascal_expr_compile(temp -> a, futur_expr1));
        VERIF_OK_B(futur_expr_to_prog(futur_expr1, futur1));

        args = mp(futur1, args);

	temp = temp->suivant;
      }

      p = args;

      while (p != NULL) {
        futur = prog_seq2(p -> a, futur);
        p = p -> suivant;
      }

      args -> delete_les_boites();
      
      return 0;
    }
    break;


  case PWritelnStack: {
      int len = val.upwrite.le -> length();

      pevalt * * args_tab = new pevalt *[len];

      for (int i = 0; i < len; i++)
        args_tab[(len - 1) - i] = pascal_stack_pop(stack);
      
      char *message, *a1, *a2;
      message = strcopy("");
      for (int i = 0; i < len; i++) {
        e_ptr = args_tab[i];

        if (e_ptr -> type.type == pevaltype::PETString)
          a1 = strcopy(e_ptr -> val.val.str);
        else
          a1 = e_ptr -> toString();

	a2 = STRCAT2_(message, a1);

	delete message;
	delete a1;
	message = a2;
      }

      SCRIPT_AfficherMessage(message);

      delete message;
      
      return 0;
    }
      break;

  case PRead:
  case PReadln: {
    class pliste<CPexpr> *ltemp;

    ltemp = val.upreadln.llval;
    
    while (ltemp != NULL) {
      CPprog * futur3 = new class CPprog(this -> position);
      futur3 -> type = CPprog::PReadlnStack;
      futur3 -> val = this -> val;

      VERIF_OK_B(pascal_expr_compile_l(ltemp -> a, futur_expr1));
      VERIF_OK_B(futur_expr_to_prog(futur_expr1, futur1));
    
      CPprog * futur4 = new class CPprog(this -> position);
      futur4 -> type = CPprog::PAffectationStack;
      futur4 -> val = this -> val;

      futur = prog_seq4(futur3, futur1, futur4, futur);

      ltemp = ltemp -> suivant;
    }

    return 0; 
  }
    break;

  case PReadlnStack: {

#if 1
    // on a setté le tick correctement (script en mode pause donc, en attente du résultat :-)
    // il va y avoir des passes de boucle tant que choix pas fait
    // quand choix fait, le résultat devrait être pushé sur la stack puis le tick être remis en mode normal et l'exécution du script peut reprendre
    // (le script possède un état… :-p)
    SCRIPT_Readln(MenuEntreeNom);
#else
    lval_ptr = pascal_stack_pop(stack);
    VERIF_TYPE2(lval_ptr,pevaltype::PETPointer);
    VERIF_TYPE3(lval_ptr -> type.val.ptr -> type,pevaltype::PETString);

    char * str = SCRIPT_Readln(MenuEntreeNom);
    psval sval;
    sval.str = str;
    pmemwrite(mem, lval_ptr -> val.val.ptr, sval);
#endif

    return 0; 
  }
    break;


  case PType:
    pmessage("Ajout du type %s à l'environnement.", val.uptype.ident);

    PRECALCUL_TYPE(val.uptype.dvaltype);

    dvaltypeuser_ptr = new pdvaltypeuser;
    dvaltypeuser_ptr->nom = val.uptype.ident;
    dvaltypeuser_ptr->dvaltype = val.uptype.dvaltype;
    tabdvaltypeuser = mp(dvaltypeuser_ptr, tabdvaltypeuser);
    return 0;
    break;


  case PNew:
    pmessage("Allocation de mémoire.");
    VERIF_OK_B(val.upnew.ident != NULL);
    VERIF_OK_B(val.upnew.ident[0] != '\0');
    VERIF_OK(penvlookup(env, val.upnew.ident, dvalt));
    VERIF_OK_B(dvalt.type.type == pdvaltype::PDTPointer);

    taille = dvalt.type.val.ptr -> pdvaltype_sizeof();
    VERIF_OK(pnew(mem, taille, mem, i));
    sval.ptr = i;
    VERIF_OK(pmemwrite(mem, dvalt.val.val.ptr, sval));

    return 0;
    break;


  case PCall:
    pmessage("Appel avec nom = %s", val.upcall.ident);
    
    VERIF_OK(penvlookup(env, val.upcall.ident, dvalt));
    VERIF_OK_B(dvalt.type.type == pdvaltype::PDTProcedure);

    {
      // Evaluation des paramètres.
      // Une fois évalués dans l'environnement d'appel (faire attention à var), 
      // on les associe dans l'environnement de la fonction.
      // Pour cela, on déclare, puis on associe.
      class pliste<CPexpr> *tempargs;
      class pliste<struct pdvaltype::tpdtprocedure::param> *tempparams;
      
      tempargs = val.upcall.args;
      tempparams = dvalt.type.val.proc.params;
      
      int args_len = tempargs -> length();
      int params_len = tempparams -> length();

      VERIF_OK_B(params_len == args_len);

    
      CPprog * futur3 = new class CPprog(0, 0, 0, 0, 0, 0);
      futur3 -> type = CPprog::PCallStack;
      futur3 -> val.upcall.ident = this -> val.upcall.ident;
      futur3 -> val.upcall.args = this -> val.upcall.args;

      futur = futur3;


      while (tempargs != NULL) {

	if (tempparams->a->var) {
          VERIF_OK_B(pascal_expr_compile_l(tempargs -> a, futur_expr1));
	}
	else {
          VERIF_OK_B(pascal_expr_compile(tempargs -> a, futur_expr1));
	}

        VERIF_OK_B(futur_expr_to_prog(futur_expr1, futur1));

        futur = prog_seq2(futur1, futur);

	tempparams = tempparams -> suivant;
	tempargs = tempargs -> suivant;
      }

      return 0;
    }
    break;


  case PCallStack:
    pmessage("Appel avec nom = %s", val.upcall.ident);
    
    VERIF_OK(penvlookup(env, val.upcall.ident, dvalt));
    VERIF_OK_B(dvalt.type.type == pdvaltype::PDTProcedure);

    {
      // Evaluation des paramètres.
      // Une fois évalués dans l'environnement d'appel (faire attention à var), 
      // on les associe dans l'environnement de la fonction.
      // Pour cela, on déclare, puis on associe.
      class pliste<struct pdvaltype::tpdtprocedure::param> *tempparams;
      penv tempenv;
      pdvalt tempdvalt;
      
      tempparams = dvalt.type.val.proc.params;
      tempenv = dvalt.type.val.proc.env;

      int len = tempparams -> length();

      pevalt * * args_tab = new pevalt *[len];

      for (int i = 0; i < len; i++)
        args_tab[(len - 1) - i] = pascal_stack_pop(stack);


      int i = 0;
      while (tempparams != NULL) {
        e_ptr = args_tab[i];

	if (tempparams->a->var) {
          VERIF_TYPE2(e_ptr,pevaltype::PETPointer);
        }

	// À la main.
        ploc where;
        psval sval;
	taille = tempparams -> a-> dvaltype_ptr -> pdvaltype_sizeof();
	VERIF_OK(pnew(mem, taille, mem, where));
	VERIF_OK(e_ptr -> toPSVal(sval));
	VERIF_OK(pmemwrite(mem, where, sval));

	if (tempparams->a->var) {
	  tempdvalt.type.type = pdvaltype::PDTVar;
	  tempdvalt.type.val.var = tempparams -> a -> dvaltype_ptr;
	  tempdvalt.val.val.var = where;
	}
	else {
	  VERIF_OK(pdvalt::pdvalt_of_pdvaltype(*(tempparams->a->dvaltype_ptr), where, tempdvalt));
	}

	VERIF_OK(penvupdate(tempenv, tempparams->a->nom, tempdvalt, tempenv));

	tempparams = tempparams->suivant;
        i++;
      }

      delete args_tab;

     
#if 0
      dvalt.type.val.proc.corps -> execute(tempenv, mem);
#else
      // TODO l'environnement n'est pas le bon!!!!
      // le futur devrait donc être un couple code+env, avec env!=NULL si ce code soit s'exécuter dans cet env spécifique -- dans le normal sinon
      futur = dvalt.type.val.proc.corps;
#endif
    }
    return 0;
    break;


  case PMusique: {
    VERIF_OK_B(pascal_expr_compile(this -> val.upmusique.musique, futur_expr1));
    VERIF_OK_B(futur_expr_to_prog(futur_expr1, futur1));

    CPprog * futur3 = new class CPprog(0, 0, 0, 0, 0, 0);
    futur3 -> type = CPprog::PMusiqueStack;
    futur3 -> val.upmusique.musique = this -> val.upmusique.musique;

    futur = prog_seq2(futur1, futur3);

    return 0;
  }
    break;

  case PMusiqueStack:
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETString);
    SCRIPT_JouerMusique(e_ptr -> val.val.str);
    return 0;
    break;


  case PWait: {
    //fprintf(stderr, "PWait\n");
    VERIF_OK_B(pascal_expr_compile(this -> val.upwait.nbpasses, futur_expr1));
    VERIF_OK_B(futur_expr_to_prog(futur_expr1, futur1));

    CPprog * futur3 = new class CPprog(this -> position);
    futur3 -> type = CPprog::PWaitStack;
    futur3 -> val = this -> val;

    futur = prog_seq2(futur1, futur3);

    return 0;
  }
    break;


  case PWaitStack: {
    //fprintf(stderr, "PWaitStack\n");
    e_ptr = pascal_stack_pop(stack);

    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETInteger || e_ptr -> type.type == pevaltype::PETSubrange);
    
    int duree;
    if (e_ptr -> type.type == pevaltype::PETInteger)
      duree = e_ptr -> val.val.i;
    else 
      duree = e_ptr -> val.val.s;

    SCRIPT_Wait(duree);

    return 0;
  }
    break;


  case PHalt:
    pmesserr(position.toString());
    pmesserr("L'instruction Halt n'est pas encore implémentée.");
    return -240;
    break;

  case PRestart:
    pmesserr(position.toString());
    pmesserr("L'instruction Restart n'est pas encore implantée.");
    return -250;
    break;

  case PFondu: {
    VERIF_OK_B(pascal_expr_compile(this -> val.upfondu.couleur, futur_expr1));
    VERIF_OK_B(futur_expr_to_prog(futur_expr1, futur1));

    CPprog * futur3 = new class CPprog(0, 0, 0, 0, 0, 0);
    futur3 -> type = CPprog::PFonduStack;
    futur3 -> val.upfondu.couleur = this -> val.upfondu.couleur;

    futur = prog_seq2(futur1, futur3);

    return 0;
  }
    break;

  case PFonduStack: {
    e_ptr = pascal_stack_pop(stack);

    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETInteger || e_ptr -> type.type == pevaltype::PETSubrange);
    
    int couleur;
    if (e_ptr -> type.type == pevaltype::PETInteger)
      couleur = e_ptr -> val.val.i;
    else 
      couleur = e_ptr -> val.val.s;

    SCRIPT_SetCouleurFondu(&MoteurTeleportation, couleur);
    SCRIPT_fondu(&MoteurTeleportation);

    return 0;
  }
    break;

  case PRecObjet:
    pmesserr(position.toString());
    pmesserr("L'instruction RecevoirObjet n'est pas encore implémentée.");
    return -270;
    break;

  case PRecArme: {
    VERIF_OK_B(pascal_expr_compile(this -> val.uprecarme.nom, futur_expr1));
    VERIF_OK_B(futur_expr_to_prog(futur_expr1, futur1));

    CPprog * futur3 = new class CPprog(0, 0, 0, 0, 0, 0);
    futur3 -> type = CPprog::PRecArmeStack;
    futur3 -> val.uprecarme.nom = this -> val.uprecarme.nom;

    futur = prog_seq2(futur1, futur3);

    return 0;
  }
    break;

  case PRecArmeStack:
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETString);
    SCRIPT_RecevoirUneArme(e_ptr -> val.val.str);
    return 0;
    break;

  case PSupObjet: {
    VERIF_OK_B(pascal_expr_compile(this -> val.upsupobjet.nom, futur_expr1));
    VERIF_OK_B(futur_expr_to_prog(futur_expr1, futur1));

    CPprog * futur3 = new class CPprog(0, 0, 0, 0, 0, 0);
    futur3 -> type = CPprog::PSupObjetStack;
    futur3 -> val.upsupobjet.nom = this -> val.upsupobjet.nom;

    futur = prog_seq2(futur1, futur3);

    return 0;
  }
    break;

  case PSupObjetStack:
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETString);
    SCRIPT_SupprimerObjet(e_ptr -> val.val.str);
    return 0;
    break;

  case PCarte: {
    futur = new class CPprog(this -> position);
    futur -> type = CPprog::PCarteStack;
    futur -> val = this -> val;

    expr = val.upcarte.nom;
    VERIF_OK_B(pascal_expr_compile(expr, futur_expr1));
    VERIF_OK_B(futur_expr_to_prog(futur_expr1, futur1));
    futur = prog_seq2(futur1, futur);

    expr = val.upcarte.x;
    VERIF_OK_B(pascal_expr_compile(expr, futur_expr1));
    VERIF_OK_B(futur_expr_to_prog(futur_expr1, futur1));
    futur = prog_seq2(futur1, futur);

    expr = val.upcarte.y;
    VERIF_OK_B(pascal_expr_compile(expr, futur_expr1));
    VERIF_OK_B(futur_expr_to_prog(futur_expr1, futur1));
    futur = prog_seq2(futur1, futur);

    expr = val.upcarte.direction;
    VERIF_OK_B(pascal_expr_compile(expr, futur_expr1));
    VERIF_OK_B(futur_expr_to_prog(futur_expr1, futur1));
    futur = prog_seq2(futur1, futur);

    return 0;
  }
    break;

  case PCarteStack: {
    char * nom;
    real x, y;
    TDirection direction;
    int n;
    
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETString);
    nom = e_ptr -> val.val.str;

    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETReal);
    x = e_ptr -> val.val.r;

    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETReal);
    y = e_ptr -> val.val.r;

    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETInteger || e_ptr -> type.type == pevaltype::PETSubrange);
    if (e_ptr -> type.type == pevaltype::PETInteger)
      n = e_ptr -> val.val.i;
    else
      n = e_ptr -> val.val.s;

    direction = int_to_direction(n);

    //fprintf(stderr, "Changer de carte: %s %f %f %i\n", nom, x, y, n);
    SCRIPT_ChangerDeCarte(&MoteurTeleportation, nom, x, y, direction);

    return 0;
  }
    break;




  case PCarteZ: {
    futur = new class CPprog(this -> position);
    futur -> type = CPprog::PCarteZStack;
    futur -> val = this -> val;

    PROG_FUTUR_PUSH_EXPR(this -> val.upcartez.nom);
    PROG_FUTUR_PUSH_EXPR(this -> val.upcartez.x);
    PROG_FUTUR_PUSH_EXPR(this -> val.upcartez.y);
    PROG_FUTUR_PUSH_EXPR(this -> val.upcartez.z);
    PROG_FUTUR_PUSH_EXPR(this -> val.upcartez.direction);

    return 0;
  }
    break;


  case PCarteZStack: {
    char * nom;
    real x, y, z;
    TDirection direction;
    int n;
    
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETString);
    nom =  e_ptr -> val.val.str;

    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETReal);
    x =  e_ptr -> val.val.r;

    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETReal);
    y =  e_ptr -> val.val.r;

    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETReal);
    z =  e_ptr -> val.val.r;

    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETInteger || e_ptr -> type.type == pevaltype::PETSubrange);
    if (e_ptr -> type.type == pevaltype::PETInteger)
      n = e_ptr -> val.val.i;
    else
      n = e_ptr -> val.val.s;

    direction = int_to_direction(n);

    SCRIPT_ChangerDeCarte(&MoteurTeleportation, nom, x, y, z, direction);

    return 0;
  }
    break;


  case PSetPosition: {
    futur = new class CPprog(this -> position);
    futur -> type = CPprog::PSetPositionStack;
    futur -> val = this -> val;

    PROG_FUTUR_PUSH_EXPR(this -> val.upsetpos.nom);
    PROG_FUTUR_PUSH_EXPR(this -> val.upsetpos.x);
    PROG_FUTUR_PUSH_EXPR(this -> val.upsetpos.y);
    PROG_FUTUR_PUSH_EXPR(this -> val.upsetpos.relatif);

    return 0;
  }
    break;


  case PSetPositionStack: {
    char * nom;
    real x, y;
    TMethodePlacement mp;
    int n;
    
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETString);
    nom = e_ptr -> val.val.str;
      
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETReal);
    x = e_ptr -> val.val.r;

    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETReal);
    y = e_ptr -> val.val.r;
      
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETInteger || e_ptr -> type.type == pevaltype::PETSubrange);
    if (e_ptr -> type.type == pevaltype::PETInteger)
      n = e_ptr -> val.val.i;
    else
      n = e_ptr -> val.val.s;

    mp = int_to_MethodePlacement(n);
      
    SCRIPT_SetPosition(nom, x, y, mp);

    return 0;
  }
    break;


  case PSetPositionZ: {
    futur = new class CPprog(this -> position);
    futur -> type = CPprog::PSetPositionZStack;
    futur -> val = this -> val;

    PROG_FUTUR_PUSH_EXPR(this -> val.upsetposz.nom);
    PROG_FUTUR_PUSH_EXPR(this -> val.upsetposz.x);
    PROG_FUTUR_PUSH_EXPR(this -> val.upsetposz.y);
    PROG_FUTUR_PUSH_EXPR(this -> val.upsetposz.z);
    PROG_FUTUR_PUSH_EXPR(this -> val.upsetposz.relatif);

    return 0;
  }
    break;

  case PSetPositionZStack: {
    char * nom;
    corps x, y, z;
    TMethodePlacement mp;
    int n;
      
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETString);
    nom = e_ptr -> val.val.str;
      
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETReal);
    x = e_ptr -> val.val.r;

    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETReal);
    y = e_ptr -> val.val.r;
      
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETReal);
    z = e_ptr -> val.val.r;
      
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETInteger || e_ptr -> type.type == pevaltype::PETSubrange);
    if (e_ptr -> type.type == pevaltype::PETInteger)
      n = e_ptr -> val.val.i;
    else
      n = e_ptr -> val.val.s;

    mp = int_to_MethodePlacement(n);

    SCRIPT_SetZ(nom, z, mp);

    return 0;
  }
    break;


  case PDeplacer: {
    futur = new class CPprog(this -> position);
    futur -> type = CPprog::PDeplacerStack;
    futur -> val = this -> val;

    PROG_FUTUR_PUSH_EXPR(this -> val.updeplacer.nom);
    PROG_FUTUR_PUSH_EXPR(this -> val.updeplacer.x);
    PROG_FUTUR_PUSH_EXPR(this -> val.updeplacer.y);
    PROG_FUTUR_PUSH_EXPR(this -> val.updeplacer.relatif);

    return 0;
  }
    break;


  case PDeplacerStack: {
    char * nom;
    corps x, y;
    TMethodePlacement mp;
    int n;  
    
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETString);
    nom = e_ptr -> val.val.str;
      
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETReal);
    x = e_ptr -> val.val.r;

    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETReal);
    y = e_ptr -> val.val.r;
      
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETInteger || e_ptr -> type.type == pevaltype::PETSubrange);
    if (e_ptr -> type.type == pevaltype::PETInteger)
      n = e_ptr -> val.val.i;
    else
      n = e_ptr -> val.val.s;
    
    mp = int_to_MethodePlacement(n);
      
    SCRIPT_Deplacer(nom, x, y, mp);

    return 0;
  }
    break;


  case PDeplacerZ: pmesserr(position.toString()); pmesserr("L'instruction DeplacerZ n'est pas encore implémentée."); return -340; break;
  case PSetHerosPosition: pmesserr(position.toString()); pmesserr("L'instruction SetHerosPosition n'est pas encore implémentée."); return -350; break;
  case PSetHerosPositionZ: pmesserr(position.toString()); pmesserr("L'instruction SetHerosPositionZ n'est pas encore implémentée."); return -360; break;
  case PHerosDeplacer: pmesserr(position.toString()); pmesserr("L'instruction HerosDeplacer n'est pas encore implémentée."); return -370; break;
  case PHerosDeplacerZ: pmesserr(position.toString()); pmesserr("L'instruction HerosDeplacerZ n'est pas encore implémentée."); return -380; break;
  case PCameraDeplacer: pmesserr(position.toString()); pmesserr("L'instruction CameraDeplacer n'est pas encore implémentée."); return -390; break;

  case PSetCameraPosition: {
    futur = new class CPprog(this -> position);
    futur -> type = CPprog::PSetCameraPositionStack;
    futur -> val = this -> val;

    PROG_FUTUR_PUSH_EXPR(this -> val.upsetcamerapos.x);
    PROG_FUTUR_PUSH_EXPR(this -> val.upsetcamerapos.y);
    PROG_FUTUR_PUSH_EXPR(this -> val.upsetcamerapos.z);
    PROG_FUTUR_PUSH_EXPR(this -> val.upsetcamerapos.relatif);

    return 0;
  }
    break;

  case PSetCameraPositionStack: {
    real x, y, z;
    TMethodePlacement mp;
    int n;
    
    pmessage("Instruction Camera -> SetPosition.");
    
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETReal);
    x = e_ptr -> val.val.r;

    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETReal);
    y = e_ptr -> val.val.r;

    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETReal);
    z = e_ptr -> val.val.r;

    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETInteger || e_ptr -> type.type == pevaltype::PETSubrange);
    if (e_ptr -> type.type == pevaltype::PETInteger)
      n = e_ptr -> val.val.i;
    else
      n = e_ptr -> val.val.s;

    mp = int_to_MethodePlacement(n);
    
    SCRIPT_Camera_SetPosition(x,y,z,mp);

    return 0;
  }
    break;

  case PCameraRotate: {
    futur = new class CPprog(this -> position);
    futur -> type = CPprog::PCameraRotateStack;
    futur -> val = this -> val;

    PROG_FUTUR_PUSH_EXPR(this -> val.upcamerarotate.angle_x);
    PROG_FUTUR_PUSH_EXPR(this -> val.upcamerarotate.angle_y);
    PROG_FUTUR_PUSH_EXPR(this -> val.upcamerarotate.angle_z);
    PROG_FUTUR_PUSH_EXPR(this -> val.upcamerarotate.relatif);

    return 0;
  }
    break;
 
  case PCameraRotateStack: {
    real angle_x, angle_y, angle_z;
    TMethodePlacement mp;
    int n;
    
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETReal);
    angle_x = e_ptr -> val.val.r;

    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETReal);
    angle_y = e_ptr -> val.val.r;

    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETReal);
    angle_z = e_ptr -> val.val.r;

    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETInteger || e_ptr -> type.type == pevaltype::PETSubrange);
    if (e_ptr -> type.type == pevaltype::PETInteger)
      n = e_ptr -> val.val.i;
    else
      n = e_ptr -> val.val.s;

    //fprintf(stderr, "Rotate: angle_x = %f, angle_y = %f, angle_z = %f, mp = %d\n", angle_x, angle_y, angle_z, n);
    mp = int_to_MethodePlacement(n);
    
    SCRIPT_Camera_Rotate(angle_x,angle_y,angle_z,mp);

    return 0;
  }
    break;
 
  case PCameraSolidariser: pmessage("Instruction CameraSolidariser"); Camera.SolidariserAuHeros(); return 0; break;
  case PCameraDesolidariser: pmessage("Instruction CameraSolidariser."); Camera.DeSolidariser(); return 0; break;
  case PCameraDefaut: pmessage("Instruction CameraDefaut"); Camera.InitCamera(); return 0; break;

  case PCameraZoom:
    futur = new class CPprog(this -> position);
    futur -> type = CPprog::PCameraZoomStack;
    futur -> val = this -> val;
    PROG_FUTUR_PUSH_EXPR(this -> val.upcamerazoom.coeff);
    return 0;
    break;

  case PCameraZoomStack:
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETReal);
    SCRIPT_Camera_Zoom(e_ptr -> val.val.r);
    return 0;
    break;

  case PFrapper:
    futur = new class CPprog(this -> position);
    futur -> type = CPprog::PFrapperStack;
    futur -> val = this -> val;
    PROG_FUTUR_PUSH_EXPR(this -> val.upfrapper.nom);
    return 0;
    break;

  case PFrapperStack:
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETString);
    SCRIPT_Frapper(e_ptr -> val.val.str);
    return 0;
    break;

  case PAjouterAnime: {
    futur = new class CPprog(this -> position);
    futur -> type = CPprog::PAjouterAnimeStack;
    futur -> val = this -> val;

    PROG_FUTUR_PUSH_EXPR(this -> val.upajouteranime.nom);
    PROG_FUTUR_PUSH_EXPR(this -> val.upajouteranime.fichier);
    return 0;
  }
    break;

  case PAjouterAnimeStack: {
    char * nom, * fichier;
    
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETString);
    nom = e_ptr -> val.val.str;

    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETString);
    fichier = e_ptr -> val.val.str;

    SCRIPT_AjouterObjetAnime(nom, fichier);

    return 0;
  }
    break;


  case PAjouterNonAnime: {
    futur = new class CPprog(this -> position);
    futur -> type = CPprog::PAjouterNonAnimeStack;
    futur -> val = this -> val;

    PROG_FUTUR_PUSH_EXPR(this -> val.upajouternonanime.nom);
    PROG_FUTUR_PUSH_EXPR(this -> val.upajouternonanime.nom);

    return 0;
  }
    break;

  case PAjouterNonAnimeStack: {
    char * nom, * fichier;
    
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETString);
    nom = e_ptr -> val.val.str;

    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETString);
    fichier = e_ptr -> val.val.str;

    SCRIPT_AjouterObjetNonAnime(nom, fichier);

    return 0;
  }
    break;

  case PSetTemps:
    futur = new class CPprog(this -> position);
    futur -> type = CPprog::PSetTempsStack;
    futur -> val = this -> val;
    PROG_FUTUR_PUSH_EXPR(this -> val.upsettemps.temps);
    return 0;
    break;

  case PSetTempsStack:
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETReal);
    SCRIPT_SetTemps(e_ptr -> val.val.r);
    return 0;
    break;

  case PSetOrientation: {
    futur = new class CPprog(this -> position);
    futur -> type = CPprog::PSetOrientationStack;
    futur -> val = this -> val;
    PROG_FUTUR_PUSH_EXPR(this -> val.upsetorientation.nom);
    PROG_FUTUR_PUSH_EXPR(this -> val.upsetorientation.orientation);
    return 0;
  }
    break;


  case PSetOrientationStack: {
    int orientation;
    char * nom;
    enum TDirection direction;

    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETString);
    nom = e_ptr -> val.val.str;

    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETInteger || e_ptr -> type.type == pevaltype::PETSubrange);
    if (e_ptr -> type.type == pevaltype::PETSubrange)
      orientation = e_ptr -> val.val.s;
    else
      orientation = e_ptr -> val.val.i;

    direction = int_to_direction(orientation);
 
    SCRIPT_SetDirection(nom, (enum TDirection) (orientation - 1));

    return 0;
  }
    break;


  case PWaitFor:
    futur = new class CPprog(this -> position);
    futur -> type = CPprog::PWaitForStack;
    futur -> val = this -> val;
    PROG_FUTUR_PUSH_EXPR(this -> val.upwaitfor.nom);
    return 0;
    break;

  case PWaitForStack:
    e_ptr = pascal_stack_pop(stack);
    VERIF_OK_B(e_ptr -> type.type == pevaltype::PETString);
    SCRIPT_WaitFor(e_ptr -> val.val.str);
    return 0;
    break;

  case PBloquerTemps: pmessage("Instruction BloquerTemps."); SCRIPT_BloquerTemps(); return 0; break; 
  case PDebloquerTemps: pmessage("Instruction DebloquerTemps"); SCRIPT_DebloquerTemps(); return 0; break;

  default:
    pmesserr("Bon, c'est la dèche car ton programme comporte une instruction que cette machine virtuelle ne connait pas. Ce qui est étrange c'est qu'elle a été analysée... Il s'agit donc plutôt d'une erreur interne.");
    assert(false);
    return -9999;
  }

  assert(false);
  return -1;
}
















#if 0

//int CPprog::execute(penv &env, pmem &mem) {
//int CPprog::execute_step(penv &env, pmem &mem, CPprog * &futur) {
int CPprog::execute_step(penv &env, pmem &mem, pascal_stack_t * stack, CPprog * &futur) {
  pevalt b, e, e1, e2, lval;
  pevalt * b_ptr, e_ptr, e1_ptr, e2_ptr, lval_ptr;
  psval sval;
  ploc i;
  int ret;
  pdvalt dvalt;
  pdval dval;
  pdvaltype dvaltype;
  struct pascal_dval_type_user *dvaltypeuser_ptr;
  unsigned int taille;


  CPprog * futur1;
  CPprog * futur2;
  CPprog * futur3;
  pascal_prog_futur_cell_t * futur_cell;
  pascal_prog_futur_cell_t * futur_cell1;
  pascal_prog_futur_cell_t * futur_cell2;
  pascal_expr_futur_t * futur_expr1;
  pascal_expr_futur_t * futur_expr2;

  futur = NULL;

  //return 0;
  //fprintf(stderr, "TYPE: %s\n", cprog_etype(type));



  switch (type) {
    
    // Cette instruction interne arrête l'exécution courante.
    // Plus de futur.
  case PStop: return 0;  break;

    // Cette instruction magique ne fait rien.
    // Elle est pseudo-interne, puisqu'elle peut-être atteinte indirectement avec un ";;".
  case PSkip: return 0;  break;

  case PSeq:
    VERIF_OK(val.upseq.p1->execute_step(env, mem, stack, futur));

    if (futur == NULL)
      futur = val.upseq.p2;
    else {
      CPprog * futur2 = new class CPprog(0, 0, 0, 0, 0, 0);
      futur2->type = CPprog::PSeq;
      futur2->val.upseq.p1 = futur;
      futur2->val.upseq.p2 = val.upseq.p2;
      futur = futur2;
    }
    return 0; 
    break;

  case PExprStack: {
    futur_expr1 = this -> val.upexprstack.futur_expr;
    if (futur_expr1 == NULL)
      return 0;

    VERIF_OK_B(r_evaluate_futur_step(futur_expr1 -> a, stack, env, mem));

    futur_expr2 = futur_expr1 -> suivant;
    VERIF_OK_B(futur_expr_to_prog(futur_expr2, futur2));
    futur = futur2;
    return 0;
  }
    break;

  case PIf: {
    VERIF_OK_B(pascal_expr_compile(this -> val.upif.b, futur_expr1));
    VERIF_OK_B(futur_expr_to_prog(futur_expr1, futur1));

    CPprog * futur2 = new class CPprog(0, 0, 0, 0, 0, 0);
    futur2 -> type = CPprog::PIfStack;
    futur2 -> val.upif.p = val.upif.p;
    futur2 -> val.upif.q = val.upif.q;
    
    CPprog * futur3 = new class CPprog(0, 0, 0, 0, 0, 0);
    futur3 -> type = CPprog::PSeq;
    futur3 -> val.upseq.p1 = futur1;
    futur3 -> val.upseq.p2 = futur2;

    futur = futur3;
        
    return 0;
  }
    break;

  case PIfStack:
    b_ptr = pascal_stack_pop(stack);
    
    VERIF_TYPE2(b_ptr,pevaltype::PETBoolean);
    
    if (b_ptr -> val.val.b) 
      futur = val.upif.p;
    else 
      futur = val.upif.q;
    
    return 0;
    break;

  case PWhile: {
    VERIF_OK_B(pascal_expr_compile(this -> val.upwhile.b, futur_expr1));
    VERIF_OK_B(futur_expr_to_prog(futur_expr1, futur1));

    CPprog * futur2 = new class CPprog(0, 0, 0, 0, 0, 0);
    futur2 -> type = CPprog::PWhileStack;
    futur2 -> val.upwhile.b = val.upwhile.b;
    futur2 -> val.upwhile.p = val.upwhile.p;
    
    CPprog * futur3 = new class CPprog(0, 0, 0, 0, 0, 0);
    futur3 -> type = CPprog::PSeq;
    futur3 -> val.upseq.p1 = futur1;
    futur3 -> val.upseq.p2 = futur2;

    futur = futur3;
        
    return 0;
  }
    break;    

  case PWhileStack: {
    b_ptr = pascal_stack_pop(stack);

    VERIF_TYPE2(b_ptr,pevaltype::PETBoolean);

    if (b_ptr -> val.val.b) {
      futur1 = val.upwhile.p;

      CPprog * futur2 = new class CPprog(0, 0, 0, 0, 0, 0);
      futur2 -> type = CPprog::PWhile;
      futur2 -> val.upwhile.b = val.upwhile.b;
      futur2 -> val.upwhile.p = val.upwhile.p;
    
      CPprog * futur3 = new class CPprog(0, 0, 0, 0, 0, 0);
      futur3 -> type = CPprog::PSeq;
      futur3 -> val.upseq.p1 = futur1;
      futur3 -> val.upseq.p2 = futur2;
      
      futur = futur3;
    }
    return 0;
  }
    break;

  case PFor:
    VERIF_OK(val.upfor.e1->r_evaluate(env, mem, e1));
    VERIF_OK(val.upfor.e2->r_evaluate(env, mem, e2));

    VERIF_TYPE(e1,pevaltype::PETInteger);
    VERIF_TYPE(e2,pevaltype::PETInteger);

    for (int j = e1.val.val.i; j <= e2.val.val.i; j++) {
      CPprog * futur2 = new class CPprog(0, 0, 0, 0, 0, 0);
      futur2->type = CPprog::PSeq;
      futur2->val.upseq.p1 = val.upfor.p;
      futur2->val.upseq.p2 = futur;
      futur = futur2;
    }

    return 0;
    break;

  case PRepeat: {
    CPprog * futur2 = new class CPprog(0, 0, 0, 0, 0, 0);
    futur2->type = CPprog::PWhile;
    futur2->val.upwhile.b = val.uprepeat.b;
    futur2->val.upwhile.p = val.uprepeat.p;
    
    futur = new class CPprog(0, 0, 0, 0, 0, 0);
    futur->type = CPprog::PSeq;
    futur->val.upseq.p1 = val.uprepeat.p;
    futur->val.upseq.p2 = futur2;
    return 0;
  }
    break;

  case PBegin:
    futur = val.upbegin.p;
    return 0;
    break;

  case PVar:
    PRECALCUL_TYPE(val.upvar.t);
    
    pnew(mem, val.upvar.t.pdvaltype_sizeof(), mem, i);
    VERIF_OK(pdvalt::pdvalt_of_pdvaltype((val.upvar.t), i, dvalt));

    if (val.upvar.t.type == pdvaltype::PDTFunction) {
      // Ajout de la variable de retour.
      class CPprog * tempprog;
      tempprog = new class CPprog(0,0,0,0,0,0);
      tempprog->type = CPprog::PVar;
      tempprog->val.upvar.nom = this->val.upvar.nom;
      tempprog->val.upvar.t.type = pdvaltype::PDTRetour;
      tempprog->val.upvar.t.val.ret.type = &(this->val.upvar.t);
      
      class CPprog * tempprog2;
      tempprog2 = new class CPprog(0,0,0,0,0,0);
      tempprog2->type = CPprog::PSeq;
      tempprog2->val.upseq.p1 = tempprog;
      tempprog2->val.upseq.p2 = this->val.upvar.t.val.func.corps;

      // En fait on va rajouter la valeur de retour lors de l'appel,
      // car sinon on ne peut pas récupérer la valeur de retour.
      //this->val.upvar.t.val.func.corps = tempprog2;
      //dvalt.type.val.func.corps = tempprog2;
    }
    else if (val.upvar.t.type == pdvaltype::PDTRetour) {
      // positionnement de l'adresse de lecture.
      // vérifier celui de l'adresse d'écriture.
      pdvalt tempdvalt;
      VERIF_OK(penvlookup(env, val.upvar.nom, tempdvalt));

      if (tempdvalt.type.type == pdvaltype::PDTRetour) {
	dvalt.val.val.ret.read = tempdvalt.val.val.ret.read;
      }
      else if (tempdvalt.type.type == pdvaltype::PDTFunction) {
	dvalt.val.val.ret.read = tempdvalt.val.val.func;
      }
      else {
	pmesserr(position.toString());
	pmesserr("Bon c'est la dèche. En effet, apparemment il existe une fonction s'appelant '%s', mais on trouve dans l'environnement qu'un truc de type non fonctionnel (%s).", val.upvar.nom, tempdvalt.type.toString());
	return -95;
      }
    }

    penvupdate(env, val.upvar.nom, dvalt, env);

    // Ici pour etre sur que la recursivite marche.
    if (val.upvar.t.type == pdvaltype::PDTProcedure) {
      sval.proc.prog = val.upvar.t.val.proc.corps;
      pmemwrite(mem, i, sval);
      dvalt.type.val.proc.env = env; // implementation dependant :||
      VERIF_OK(penvmodify(env, val.upvar.nom, dvalt));
    }
    else if (val.upvar.t.type == pdvaltype::PDTFunction) {
      // Ajustement des variables comme pour le bon fonctionnement.
      sval.proc.prog = val.upvar.t.val.func.corps;
      pmemwrite(mem, i, sval);
    }

    return 0;
    break;


  case PConst:
    pmessage("Ajout de la constante %s à l'environnement.", val.upconst.nom);
    VERIF_OK(val.upconst.val->r_evaluate(env, mem, e));
    // Allocation d'une valeur constante dans la table des symboles.
    // On ne touche donc pas à la mémoire.
    // On vérifie d'abord que le type donné est bien un type
    // que l'on peut mettre dans les constantes.
    // (Un jour lorsque le langage marchera, on pourra mettre autre chose que de simples types).
    dvaltype.type = pdvaltype::PDTConstante;
    switch (e.type.type) {
    case pevaltype::PETBoolean: dvaltype.val.c = pdvaltype::PCTBoolean; dval.val.c.b = e.val.val.b; break;
    case pevaltype::PETInteger: dvaltype.val.c = pdvaltype::PCTInteger; dval.val.c.i = e.val.val.i; break;
    case pevaltype::PETReal:    dvaltype.val.c = pdvaltype::PCTReal;    dval.val.c.r = e.val.val.r; break;
    case pevaltype::PETString:  dvaltype.val.c = pdvaltype::PCTString;  dval.val.c.str = e.val.val.str; break;
    default: pmesserr(position.toString()); pmesserr("Désolé, mais le type \"%s\" ne peut pas encore être choisi comme constante. Attend encore un peu.", e.type.toString()); return -101;
    }

    dvalt.type = dvaltype;
    dvalt.val = dval;
    penvupdate(env, val.upconst.nom, dvalt, env);
    return 0;
    break;


  case PAffectation:
    // L'instruction d'affectation.
    // On a des vérifications à faire des deux côtés du symbole.
    // il faut vérifier que le type du membre de gauche est bien un pointeur
    // et que le type de chaque côté est le même.
    pmessage("On entre dans PAffectation. r_eval du membre droit.");
    VERIF_OK(val.upaffectation.e->r_evaluate(env, mem, e));
      
    //fprintf(stderr, "Affectation: %s [%d] = %s\n", val.upaffectation.e->toString(), val.upaffectation.e -> type, e.toString());
    
    pmessage("C'est bon pour le membre droit. On passe au membre gauche qui est l_evaluate.");
    VERIF_OK(val.upaffectation.lval->l_evaluate(env, mem, lval));

    pmessage("PAffectation: c bon, l'évaluation des deux parties est OK.");

    VERIF_TYPE(lval,pevaltype::PETPointer);

    VERIF_TYPE_EQUAL3(*(lval.type.val.ptr),e.type);

    VERIF_OK(e.toPSVal(sval));

    VERIF_OK(pmemwrite(mem, lval.val.val.ptr, sval));

    return 0;
    break;


  case PWrite:
  case PWriteln:
    {
      class pliste<CPexpr> *temp;
      
      temp = val.upwrite.le;
      
      if (temp == NULL) {
	return 0;
      }

      char *message, *a1, *a2;
      message = strcopy("");
      while (temp != NULL) {
	VERIF_OK(temp->a->r_evaluate(env, mem, e));
        //fprintf(stderr, "WRITE: %s", temp->a->toString());
	//pmessage("WRITE: %s", e.toString());
        if (e.type.type == pevaltype::PETString)
          a1 = e.val.val.str;
        else
          a1 = e.toString();
	a2 = STRCAT2_(message, a1);
	//// --1-- delete [] message;
	//// --1-- delete [] a1;
	message = a2;
	temp = temp->suivant;
      }

      SCRIPT_AfficherMessage(message);
      // --1-- delete [] message;
      
      return 0;
      break;
    }


  case PRead:
  case PReadln: {
    class pliste<CPexpr> *ltemp;
    
    ltemp = val.upreadln.llval;
    
    while (ltemp != NULL) {
      VERIF_OK(ltemp->a->l_evaluate(env, mem, lval));
      //pmessage("READLN: %s", lval.toString());
      char * str = SCRIPT_Readln(MenuEntreeNom);
      psval sval;
      sval.str = str;
      pmemwrite(mem, lval.val.val.ptr, sval);
      ltemp = ltemp->suivant;
    }
    //pmessage("READLN: \\n");
    return 0; 
  }
    break;


  case PType:
    pmessage("Ajout du type %s à l'environnement.", val.uptype.ident);

    PRECALCUL_TYPE(val.uptype.dvaltype);

    dvaltypeuser_ptr = new pdvaltypeuser;
    dvaltypeuser_ptr->nom = val.uptype.ident;
    dvaltypeuser_ptr->dvaltype = val.uptype.dvaltype;
    tabdvaltypeuser = mp(dvaltypeuser_ptr, tabdvaltypeuser);
    return 0;
    break;


  case PNew:
    pmessage("Allocation de mémoire.");
    VERIF_OK_B(val.upnew.ident != NULL);
    VERIF_OK_B(val.upnew.ident[0] != '\0');
    VERIF_OK(penvlookup(env, val.upnew.ident, dvalt));
    VERIF_OK_B(dvalt.type.type == pdvaltype::PDTPointer);

    taille = dvalt.type.val.ptr->pdvaltype_sizeof();
    VERIF_OK(pnew(mem, taille, mem, i));
    sval.ptr = i;
    VERIF_OK(pmemwrite(mem, dvalt.val.val.ptr, sval));
    return 0;
    break;


  case PCall:
    pmessage("Appel avec nom = %s", val.upcall.ident);
    
    VERIF_OK(penvlookup(env, val.upcall.ident, dvalt));
    VERIF_OK_B(dvalt.type.type == pdvaltype::PDTProcedure);

    {
      // Evaluation des paramètres.
      // Une fois évalués dans l'environnement d'appel (faire attention à var), 
      // on les associe dans l'environnement de la fonction.
      // Pour cela, on déclare, puis on associe.
      class pliste<CPexpr> *tempargs;
      class pliste<struct pdvaltype::tpdtprocedure::param> *tempparams;
      penv tempenv;
      pdvalt tempdvalt;
      
      tempargs = val.upcall.args;
      tempparams = dvalt.type.val.proc.params;
      tempenv = dvalt.type.val.proc.env;
      
      while (tempargs != NULL) {
	if (tempparams == NULL) {
	  pmesserr(position.toString());
	  pmesserr("CPprog::execute: PCall: dans l'appel à procédure %s, il y a trop d'arguments en paramètre.", val.upcall.ident);
	  return -213;
	}

	if (tempparams->a->var) {
	  VERIF_OK(tempargs->a->l_evaluate(env, mem, e));
	}
	else {
	  VERIF_OK(tempargs->a->r_evaluate(env, mem, e));
	}

	// À la main.
	taille = tempparams->a->dvaltype_ptr->pdvaltype_sizeof();
	VERIF_OK(pnew(mem, taille, mem, i));
	VERIF_OK(e.toPSVal(sval));
	VERIF_OK(pmemwrite(mem, i, sval));

	if (tempparams->a->var) {
	  tempdvalt.type.type = pdvaltype::PDTVar;
	  tempdvalt.type.val.var = tempparams->a->dvaltype_ptr;
	  tempdvalt.val.val.var = i;
	}
	else {
	  VERIF_OK(pdvalt::pdvalt_of_pdvaltype(*(tempparams->a->dvaltype_ptr), i, tempdvalt));
	}

	VERIF_OK(penvupdate(tempenv, tempparams->a->nom, tempdvalt, tempenv));

	// C bon. suivant.
	tempparams = tempparams->suivant;
	tempargs = tempargs->suivant;
      }

      if (tempparams != NULL) {
	pmesserr(position.toString());
	pmesserr("CPprog::execute: PCall: dans l'appel à procédure %s, il n'y a pas assez d'arguments en paramètre [%s].", val.upcall.ident, tempparams->a->nom);
	return -219;
      }
     
#if 0
      dvalt.type.val.proc.corps -> execute(tempenv, mem);
#else
      // TODO l'environnement n'est pas le bon!!!!
      // le futur devrait donc être un couple code+env, avec env!=NULL si ce code soit s'exécuter dans cet env spécifique -- dans le normal sinon
      futur = dvalt.type.val.proc.corps;
#endif
    }
    return 0;
    break;


  case PMusique:
    VERIF_OK(val.upmusique.musique->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    SCRIPT_JouerMusique(e.val.val.str);
    return 0;
    break;


  case PWait: {
    VERIF_OK(val.upwait.nbpasses->r_evaluate(env, mem, e));

    VERIF_OK_B(e.type.type == pevaltype::PETInteger || e.type.type == pevaltype::PETSubrange);
    
    int duree;
    if (e.type.type == pevaltype::PETInteger)
      duree = e.val.val.i;
    else 
      duree = e.val.val.s;

    SCRIPT_Wait(duree);
    return 0;
  }
    break;

  case PHalt:
    pmesserr(position.toString());
    pmesserr("L'instruction Halt n'est pas encore implémentée.");
    return -240;
    break;

  case PRestart:
    pmesserr(position.toString());
    pmesserr("L'instruction Restart n'est pas encore implantée.");
    return -250;
    break;

  case PFondu: {
    pmessage("Instruction Fondu.");
    VERIF_OK(val.upfondu.couleur->r_evaluate(env, mem, e));

    VERIF_OK_B(e.type.type == pevaltype::PETInteger || e.type.type == pevaltype::PETSubrange);
    
    int couleur;
    if (e.type.type == pevaltype::PETInteger)
      couleur = e.val.val.i;
    else 
      couleur = e.val.val.s;

    SCRIPT_SetCouleurFondu(&MoteurTeleportation, couleur);
    SCRIPT_fondu(&MoteurTeleportation);
    return 0;
  }
    break;

  case PRecObjet:
    pmesserr(position.toString());
    pmesserr("L'instruction RecevoirObjet n'est pas encore implémentée.");
    return -270;
    break;

  case PRecArme:
    pmessage("Instruction RecevoirArme.");
    VERIF_OK(val.uprecarme.nom->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    SCRIPT_RecevoirUneArme(e.val.val.str);
    return 0;
    break;

  case PSupObjet:
    pmessage("Instruction SupprimerObjet.");
    VERIF_OK(val.upsupobjet.nom->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    SCRIPT_SupprimerObjet(e.val.val.str);
    return 0;
    break;

  case PCarte: {
    char * nom;
    real x, y;
    TDirection direction;
    int n;
    
    pmessage("Instruction Carte.");
    
    VERIF_OK(val.upcarte.nom->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    nom = e.val.val.str;

    VERIF_OK(val.upcarte.x->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    x = e.val.val.r;

    VERIF_OK(val.upcarte.y->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    y = e.val.val.r;

    VERIF_OK(val.upcarte.direction->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETInteger || e.type.type == pevaltype::PETSubrange);
    if (e.type.type == pevaltype::PETInteger)
      n = e.val.val.i;
    else
      n = e.val.val.s;

    direction = int_to_direction(e.val.val.s); 

    SCRIPT_ChangerDeCarte(&MoteurTeleportation, nom, x, y, direction);

    return 0;
    break;
  }


  case PCarteZ: {
    char * nom;
    real x, y, z;
    TDirection direction;
    int n;
    
    pmessage("Instruction CarteZ.");
    
    VERIF_OK(val.upcartez.nom->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    nom =  e.val.val.str;

    VERIF_OK(val.upcartez.x->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    x =  e.val.val.r;

    VERIF_OK(val.upcartez.y->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    y =  e.val.val.r;

    VERIF_OK(val.upcartez.z->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    z =  e.val.val.r;

    VERIF_OK(val.upcartez.direction->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETInteger || e.type.type == pevaltype::PETSubrange);
    if (e.type.type == pevaltype::PETInteger)
      n = e.val.val.i;
    else
      n = e.val.val.s;

    direction = int_to_direction(e.val.val.s); 

    SCRIPT_ChangerDeCarte(&MoteurTeleportation, nom, x, y, z, direction);

    return 0;
  }
    break;


  case PSetPosition: {
    char * nom;
    real x, y;
    TMethodePlacement mp;
    int n;
    
    pmessage("Instruction SetPosition.");
    
    VERIF_OK(val.upsetpos.nom->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    nom = e.val.val.str;
      
    VERIF_OK(val.upsetpos.x->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    x = e.val.val.r;

    VERIF_OK(val.upsetpos.y->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    y = e.val.val.r;
      
    VERIF_OK(val.upsetpos.relatif->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETInteger || e.type.type == pevaltype::PETSubrange);
    if (e.type.type == pevaltype::PETInteger)
      n = e.val.val.i;
    else
      n = e.val.val.s;

    mp = int_to_MethodePlacement(n);
      
    SCRIPT_SetPosition(nom, x, y, mp);

    return 0;
  }
    break;


  case PSetPositionZ: {
    char * nom;
    corps x, y, z;
    TMethodePlacement mp;
    int n;
      
    pmessage("Instruction SetPositionZ.");
    
    VERIF_OK(val.upsetposz.nom->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    nom = e.val.val.str;
      
    VERIF_OK(val.upsetposz.x->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    x = e.val.val.r;

    VERIF_OK(val.upsetposz.y->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    y = e.val.val.r;
      
    VERIF_OK(val.upsetposz.z->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    z = e.val.val.r;
      
    VERIF_OK(val.upsetposz.relatif->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETInteger || e.type.type == pevaltype::PETSubrange);
    if (e.type.type == pevaltype::PETInteger)
      n = e.val.val.i;
    else
      n = e.val.val.s;

    mp = int_to_MethodePlacement(n);

    SCRIPT_SetZ(nom, z, mp);

    return 0;
  }
    break;


  case PDeplacer: {
    char * nom;
    corps x, y;
    TMethodePlacement mp;
    int n;  
    
    pmessage("Instruction Deplacer.");

    VERIF_OK(val.updeplacer.nom->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    nom = e.val.val.str;
      
    VERIF_OK(val.updeplacer.x->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    x = e.val.val.r;

    VERIF_OK(val.updeplacer.y->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    y = e.val.val.r;
      
    VERIF_OK(val.updeplacer.relatif->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETInteger || e.type.type == pevaltype::PETSubrange);
    if (e.type.type == pevaltype::PETInteger)
      n = e.val.val.i;
    else
      n = e.val.val.s;
    
    mp = int_to_MethodePlacement(n);
      
    SCRIPT_Deplacer(nom, x, y, mp);

    return 0;
  }
    break;


  case PDeplacerZ: pmesserr(position.toString()); pmesserr("L'instruction DeplacerZ n'est pas encore implémentée."); return -340; break;
  case PSetHerosPosition: pmesserr(position.toString()); pmesserr("L'instruction SetHerosPosition n'est pas encore implémentée."); return -350; break;
  case PSetHerosPositionZ: pmesserr(position.toString()); pmesserr("L'instruction SetHerosPositionZ n'est pas encore implémentée."); return -360; break;
  case PHerosDeplacer: pmesserr(position.toString()); pmesserr("L'instruction HerosDeplacer n'est pas encore implémentée."); return -370; break;
  case PHerosDeplacerZ: pmesserr(position.toString()); pmesserr("L'instruction HerosDeplacerZ n'est pas encore implémentée."); return -380; break;
  case PCameraDeplacer: pmesserr(position.toString()); pmesserr("L'instruction CameraDeplacer n'est pas encore implémentée."); return -390; break;

  case PSetCameraPosition: {
    real x, y, z;
    TMethodePlacement mp;
    int n;
    
    pmessage("Instruction Camera -> SetPosition.");
    
    VERIF_OK(val.upsetcamerapos.x->r_evaluate(env,mem,e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    x = e.val.val.r;

    VERIF_OK(val.upsetcamerapos.y->r_evaluate(env,mem,e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    y = e.val.val.r;

    VERIF_OK(val.upsetcamerapos.z->r_evaluate(env,mem,e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    z = e.val.val.r;

    VERIF_OK(val.upsetcamerapos.relatif->r_evaluate(env,mem,e));
    VERIF_OK_B(e.type.type == pevaltype::PETInteger || e.type.type == pevaltype::PETSubrange);
    if (e.type.type == pevaltype::PETInteger)
      n = e.val.val.i;
    else
      n = e.val.val.s;

    mp = int_to_MethodePlacement(n);
    
    SCRIPT_Camera_SetPosition(x,y,z,mp);

    return 0;
  }
    break;

  case PCameraRotate: {
    real angle_x, angle_y, angle_z;
    TMethodePlacement mp;
    int n;
    
    pmessage("Instruction Camera -> Rotate.");
    
    VERIF_OK(val.upcamerarotate.angle_x->r_evaluate(env,mem,e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    angle_x = e.val.val.r;

    VERIF_OK(val.upcamerarotate.angle_y->r_evaluate(env,mem,e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    angle_y = e.val.val.r;

    VERIF_OK(val.upcamerarotate.angle_z->r_evaluate(env,mem,e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    angle_z = e.val.val.r;

    VERIF_OK(val.upcamerarotate.relatif->r_evaluate(env,mem,e));
    VERIF_OK_B(e.type.type == pevaltype::PETInteger || e.type.type == pevaltype::PETSubrange);
    if (e.type.type == pevaltype::PETInteger)
      n = e.val.val.i;
    else
      n = e.val.val.s;

    mp = int_to_MethodePlacement(n);
    
    SCRIPT_Camera_Rotate(angle_x,angle_y,angle_z,mp);

    return 0;
  }
    break;
 
  case PCameraSolidariser: pmessage("Instruction CameraSolidariser"); Camera.SolidariserAuHeros(); return 0; break;
  case PCameraDesolidariser: pmessage("Instruction CameraSolidariser."); Camera.DeSolidariser(); return 0; break;
  case PCameraDefaut: pmessage("Instruction CameraDefaut"); Camera.InitCamera(); return 0; break;

  case PCameraZoom:
    pmessage("Instruction CameraZoom.");
    VERIF_OK(val.upcamerazoom.coeff -> r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    SCRIPT_Camera_Zoom(e.val.val.r);
    return 0;
    break;

  case PFrapper:
    pmessage("L'instruction Frapper.");
    VERIF_OK(val.upfrapper.nom->r_evaluate(env,mem,e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    SCRIPT_Frapper(e.val.val.str);
    return 0;
    break;

  case PAjouterAnime: {
    pmessage("Instruction Ajouter Anime.");
    
    char * nom, * fichier;
    
    VERIF_OK(val.upajouteranime.nom->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    nom = e.val.val.str;

    VERIF_OK(val.upajouteranime.fichier->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    fichier = e.val.val.str;

    SCRIPT_AjouterObjetAnime(nom, fichier);
    return 0;
  }
    break;

  case PAjouterNonAnime: {
    pmessage("Instruction Ajouter NonAnime.");
    
    char * nom, * fichier;
    
    VERIF_OK(val.upajouteranime.nom->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    nom = e.val.val.str;

    VERIF_OK(val.upajouteranime.fichier->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    fichier = e.val.val.str;

    SCRIPT_AjouterObjetNonAnime(nom, fichier);
    return 0;
  }
    break;

  case PSetTemps:
    pmessage("Instruction SetTemps.");
    VERIF_OK(val.upsettemps.temps->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    SCRIPT_SetTemps(e.val.val.r);
    return 0;
    break;

  case PSetOrientation: {
    int orientation;
    char * nom;
    enum TDirection direction;

    pmessage("Instruction SetOrientation.");

    VERIF_OK(val.upsetorientation.nom->r_evaluate(env,mem,e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    nom = e.val.val.str;

    VERIF_OK(val.upsetorientation.orientation->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETInteger || e.type.type == pevaltype::PETSubrange);
    if (e.type.type == pevaltype::PETSubrange)
      orientation = e.val.val.s;
    else
      orientation = e.val.val.i;

    direction = int_to_direction(orientation);
 
    SCRIPT_SetDirection(nom, (enum TDirection) (orientation - 1));

    return 0;
  }
    break;


  case PWaitFor:
    pmessage("Instruction WaitFor");
    VERIF_OK(val.upwaitfor.nom -> r_evaluate(env, mem, e) );
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    SCRIPT_WaitFor(e.val.val.str);
    return 0;
    break;

  case PBloquerTemps:
    pmessage("Instruction BloquerTemps.");
    SCRIPT_BloquerTemps();
    return 0;
    break;
    
  case PDebloquerTemps:
    pmessage("Instruction DebloquerTemps");
    SCRIPT_DebloquerTemps();
    return 0;
    break;

  default:
    pmesserr("Bon, c'est la dèche car ton programme comporte une instruction que cette machine virtuelle ne connait pas. Ce qui est étrange c'est qu'elle a été analysée... Il s'agit donc plutôt d'une erreur interne.");
    assert(false);
    return -9999;
  }

  assert(false);
  return -1;
}

#endif
























#if 0

bool pascal_prog_compile(const CPprog * prog, pascal_prog_futur_t * &futur) {
  pevalt b, e, e1, e2, lval;
  psval sval;
  ploc i;
  int ret;
  pdvalt dvalt;
  pdval dval;
  pdvaltype dvaltype;
  struct pascal_dval_type_user *dvaltypeuser_ptr;
  unsigned int taille;

  pascal_prog_futur_t * futur1;
  pascal_prog_futur_t * futur2;
  pascal_prog_futur_t * futur3;
  pascal_prog_futur_cell_t * futur_cell;
  pascal_prog_futur_cell_t * futur_cell1;
  pascal_prog_futur_cell_t * futur_cell2;
  pascal_expr_futur_t * futur_expr1;
  pascal_expr_futur_t * futur_expr2;

  futur_cell = new struct pascal_prog_futur_cell_t;
  futur_cell -> type = prog -> type;
  futur = mp(futur_cell, (pliste<pascal_prog_futur_cell_t> *) NULL);

  switch (prog -> type) {
  case CPprog::PStop: return true;  break;
  case CPprog::PSkip: return true;  break;

  case CPprog::PSeq:
    delete futur_cell;
    delete futur;
    VERIF_OK_B(pascal_prog_compile(prog -> val.upseq.p1, futur1));
    VERIF_OK_B(pascal_prog_compile(prog -> val.upseq.p2, futur2));
    pliste_concat2_surplace(futur1, futur2);
    futur = futur1;
    return true;
    break;

  case CPprog::PIf:
    VERIF_OK_B(pascal_expr_compile(prog -> val.upif.b, futur_expr1));
    VERIF_OK_B(pascal_prog_compile(prog -> val.upif.p, futur1));
    VERIF_OK_B(pascal_prog_compile(prog -> val.upif.q, futur2));
    futur_cell -> futur1 = futur1;
    futur_cell -> futur2 = futur2;
    VERIF_OK_B(futur_expr_to_futur_prog(futur_expr1, futur1));
    pliste_concat2_surplace(futur1, futur);
    futur = futur1;
    return true;
    break;

  case CPprog::PWhile:
    VERIF_OK_B(pascal_expr_compile(prog -> val.upwhile.b, futur_expr1));
    VERIF_OK_B(pascal_prog_compile(prog -> val.upwhile.p, futur2));
    futur_cell -> futur1 = futur2;
    VERIF_OK_B(futur_expr_to_futur_prog(futur_expr1, futur1));
    pliste_concat2_surplace(futur1, futur);
    futur = futur1;
    return true;
    break;

  case CPprog::PFor:
    VERIF_OK_B(pascal_expr_compile(prog -> val.upfor.e1, futur_expr1));
    VERIF_OK_B(pascal_expr_compile(prog -> val.upfor.e2, futur_expr2));
    VERIF_OK_B(pascal_prog_compile(prog -> val.upfor.p, futur3));
    futur_cell -> futur1 = futur3;
    VERIF_OK_B(futur_expr_to_futur_prog(futur_expr1, futur1));
    VERIF_OK_B(futur_expr_to_futur_prog(futur_expr1, futur2));
    pliste_concat3_surplace(futur1, futur2, futur);
    futur = futur1;
    return true;
    break;

  case CPprog::PRepeat:
    VERIF_OK_B(pascal_prog_compile(prog -> val.uprepeat.p, futur1));
    VERIF_OK_B(pascal_expr_compile(prog -> val.uprepeat.b, futur_expr2));
    VERIF_OK_B(futur_expr_to_futur_prog(futur_expr2, futur2));
    pliste_concat3_surplace(futur1, futur2, futur);
    futur_cell -> futur1 = futur1;
    futur = futur1;
    return true;
    break;

  case CPprog::PBegin:
    VERIF_OK_B(pascal_prog_compile(prog -> val.upbegin.p, futur1));
    pliste_concat2_surplace(futur1, futur);
    futur = futur1;
    return true;

  case CPprog::PVar:
    // C'est l'instruction de déclaration de variables!!
    // Malheureusement, ça contient aussi la définition de fonction et de procédure… :-/
    // le corps des fonctions et des procédures est inclus dans le type………!!! (le dvalt…)
    //
    // puis on fait des calculs pour les fonctions, mais pour les procédures…??
    futur_cell -> dvaltype = prog -> val.upvar.t;
    futur_cell -> str1 = prog -> val.upvar.nom;
    return true;
    break;

  case CPprog::PConst:
    VERIF_OK_B(pascal_expr_compile(prog -> val.upconst.val, futur_expr1));
    VERIF_OK_B(futur_expr_to_futur_prog(futur_expr1, futur1));
    pliste_concat2_surplace(futur1, futur);
    futur = futur1;
    return true;

  case CPprog::PAffectation:
    VERIF_OK_B(pascal_expr_compile(prog -> val.upaffectation.lval, futur_expr1));
    VERIF_OK_B(pascal_expr_compile(prog -> val.upaffectation.e, futur_expr2));
    VERIF_OK_B(futur_expr_to_futur_prog(futur_expr1, futur1));
    VERIF_OK_B(futur_expr_to_futur_prog(futur_expr2, futur2));
    pliste_concat3_surplace(futur1, futur2, futur);
    futur = futur1;
    return true;
    break;


  case CPprog::PWrite:
  case CPprog::PWriteln: {
    class pliste<CPexpr> * temp;
    
    temp = prog -> val.upwrite.le;

    futur_cell -> n1 = temp -> length();

    futur1 = NULL;

    while (temp != NULL) {
      VERIF_OK_B(pascal_expr_compile(temp -> a, futur_expr2));
      VERIF_OK_B(futur_expr_to_futur_prog(futur_expr2, futur2));
      pliste_concat2_surplace(futur1, futur2);
      temp = temp->suivant;
    }

    pliste_concat2_surplace(futur1, futur);
    futur = futur1;
    return true;
  }
    break;

  case CPprog::PRead:
  case CPprog::PReadln: {
    class pliste<CPexpr> * ltemp;
    
    ltemp = prog -> val.upreadln.llval;

    delete futur;
    delete futur_cell;
    futur1 = NULL;
    
    while (ltemp != NULL) {
      VERIF_OK_B(pascal_expr_compile(temp -> a, futur_expr2));
      VERIF_OK_B(futur_expr_to_futur_prog(futur_expr2, futur2));

      futur_cell = new struct pascal_prog_futur_cell_t;
      futur_cell -> type = prog -> type;
      futur3 = mp(futur_cell, (pliste<pascal_prog_futur_cell_t> *) NULL);

      pliste_concat3_surplace(futur1, futur2, futur3);

      ltemp = ltemp->suivant;
    }

    futur = futur1;
    return true;
  }
    break;


  case CPprog::PType:
    PRECALCUL_TYPE(prog -> val.uptype.dvaltype);

    dvaltypeuser_ptr = new pdvaltypeuser;
    dvaltypeuser_ptr->nom = prog -> val.uptype.ident;
    dvaltypeuser_ptr->dvaltype = prog -> val.uptype.dvaltype;
    tabdvaltypeuser = mp(dvaltypeuser_ptr, tabdvaltypeuser);
    return true;
    break;


  case CPprog::PNew:
    futur_cell -> str1 = prog -> val.upnew.ident;
    return true;
    break;


  case CPprog::PCall:
    VERIF_OK(penvlookup(env, val.upcall.ident, dvalt));
    VERIF_OK_B(dvalt.type.type == pdvaltype::PDTProcedure);

    {
      // Evaluation des paramètres.
      // Une fois évalués dans l'environnement d'appel (faire attention à var), 
      // on les associe dans l'environnement de la fonction.
      // Pour cela, on déclare, puis on associe.
      class pliste<CPexpr> *tempargs;
      class pliste<struct pdvaltype::tpdtprocedure::param> *tempparams;
      penv tempenv;
      pdvalt tempdvalt;
      
      tempargs = val.upcall.args;
      tempparams = dvalt.type.val.proc.params;
      tempenv = dvalt.type.val.proc.env;
      
      while (tempargs != NULL) {
	if (tempparams == NULL) {
	  pmesserr(position.toString());
	  pmesserr("CPprog::execute: PCall: dans l'appel à procédure %s, il y a trop d'arguments en paramètre.", val.upcall.ident);
	  return -213;
	}

	if (tempparams->a->var) {
	  VERIF_OK(tempargs->a->l_evaluate(env, mem, e));
	}
	else {
	  VERIF_OK(tempargs->a->r_evaluate(env, mem, e));
	}

	// À la main.
	taille = tempparams->a->dvaltype_ptr->pdvaltype_sizeof();
	VERIF_OK(pnew(mem, taille, mem, i));
	VERIF_OK(e.toPSVal(sval));
	VERIF_OK(pmemwrite(mem, i, sval));

	if (tempparams->a->var) {
	  tempdvalt.type.type = pdvaltype::PDTVar;
	  tempdvalt.type.val.var = tempparams->a->dvaltype_ptr;
	  tempdvalt.val.val.var = i;
	}
	else {
	  VERIF_OK(pdvalt::pdvalt_of_pdvaltype(*(tempparams->a->dvaltype_ptr), i, tempdvalt));
	}

	VERIF_OK(penvupdate(tempenv, tempparams->a->nom, tempdvalt, tempenv));

	// C bon. suivant.
	tempparams = tempparams->suivant;
	tempargs = tempargs->suivant;
      }

      if (tempparams != NULL) {
	pmesserr(position.toString());
	pmesserr("CPprog::execute: PCall: dans l'appel à procédure %s, il n'y a pas assez d'arguments en paramètre [%s].", val.upcall.ident, tempparams->a->nom);
	return -219;
      }
     
#if 0
      dvalt.type.val.proc.corps -> execute(tempenv, mem);
#else
      // TODO l'environnement n'est pas le bon!!!!
      // le futur devrait donc être un couple code+env, avec env!=NULL si ce code soit s'exécuter dans cet env spécifique -- dans le normal sinon
      futur = dvalt.type.val.proc.corps;
#endif
    }
    return 0;
    break;


  case CPprog::PMusique:
    VERIF_OK(val.upmusique.musique->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    SCRIPT_JouerMusique(e.val.val.str);
    break;


  case CPprog::PWait: {
    VERIF_OK(val.upwait.nbpasses->r_evaluate(env, mem, e));

    VERIF_OK_B(e.type.type == pevaltype::PETInteger || e.type.type == pevaltype::PETSubrange);
    
    int duree;
    if (e.type.type == pevaltype::PETInteger)
      duree = e.val.val.i;
    else 
      duree = e.val.val.s;

    SCRIPT_Wait(duree);
    return 0;
  }
    break;

  case CPprog::PHalt:
    pmesserr(position.toString());
    pmesserr("L'instruction Halt n'est pas encore implémentée.");
    return -240;
    break;

  case CPprog::PRestart:
    pmesserr(position.toString());
    pmesserr("L'instruction Restart n'est pas encore implantée.");
    return -250;
    break;

  case CPprog::PFondu: {
    pmessage("Instruction Fondu.");
    VERIF_OK(val.upfondu.couleur->r_evaluate(env, mem, e));

    VERIF_OK_B(e.type.type == pevaltype::PETInteger || e.type.type == pevaltype::PETSubrange);
    
    int couleur;
    if (e.type.type == pevaltype::PETInteger)
      couleur = e.val.val.i;
    else 
      couleur = e.val.val.s;

    SCRIPT_SetCouleurFondu(&MoteurTeleportation, couleur);
    SCRIPT_fondu(&MoteurTeleportation);
    return 0;
  }
    break;

  case CPprog::PRecObjet:
    pmesserr(position.toString());
    pmesserr("L'instruction RecevoirObjet n'est pas encore implémentée.");
    return -270;
    break;

  case CPprog::PRecArme:
    pmessage("Instruction RecevoirArme.");
    VERIF_OK(val.uprecarme.nom->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    SCRIPT_RecevoirUneArme(e.val.val.str);
    return 0;
    break;

  case CPprog::PSupObjet:
    pmessage("Instruction SupprimerObjet.");
    VERIF_OK(val.upsupobjet.nom->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    SCRIPT_SupprimerObjet(e.val.val.str);
    return 0;
    break;

  case CPprog::PCarte: {
    char * nom;
    real x, y;
    TDirection direction;
    int n;
    
    pmessage("Instruction Carte.");
    
    VERIF_OK(val.upcarte.nom->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    nom = e.val.val.str;

    VERIF_OK(val.upcarte.x->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    x = e.val.val.r;

    VERIF_OK(val.upcarte.y->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    y = e.val.val.r;

    VERIF_OK(val.upcarte.direction->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETInteger || e.type.type == pevaltype::PETSubrange);
    if (e.type.type == pevaltype::PETInteger)
      n = e.val.val.i;
    else
      n = e.val.val.s;

    direction = int_to_direction(e.val.val.s); 

    SCRIPT_ChangerDeCarte(&MoteurTeleportation, nom, x, y, direction);

    return 0;
    break;
  }


  case CPprog::PCarteZ: {
    char * nom;
    real x, y, z;
    TDirection direction;
    int n;
    
    pmessage("Instruction CarteZ.");
    
    VERIF_OK(val.upcartez.nom->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    nom =  e.val.val.str;

    VERIF_OK(val.upcartez.x->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    x =  e.val.val.r;

    VERIF_OK(val.upcartez.y->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    y =  e.val.val.r;

    VERIF_OK(val.upcartez.z->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    z =  e.val.val.r;

    VERIF_OK(val.upcartez.direction->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETInteger || e.type.type == pevaltype::PETSubrange);
    if (e.type.type == pevaltype::PETInteger)
      n = e.val.val.i;
    else
      n = e.val.val.s;

    direction = int_to_direction(e.val.val.s); 

    SCRIPT_ChangerDeCarte(&MoteurTeleportation, nom, x, y, z, direction);

    return 0;
  }
    break;


  case CPprog::PSetPosition: {
    char * nom;
    real x, y;
    TMethodePlacement mp;
    int n;
    
    pmessage("Instruction SetPosition.");
    
    VERIF_OK(val.upsetpos.nom->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    nom = e.val.val.str;
      
    VERIF_OK(val.upsetpos.x->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    x = e.val.val.r;

    VERIF_OK(val.upsetpos.y->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    y = e.val.val.r;
      
    VERIF_OK(val.upsetpos.relatif->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETInteger || e.type.type == pevaltype::PETSubrange);
    if (e.type.type == pevaltype::PETInteger)
      n = e.val.val.i;
    else
      n = e.val.val.s;

    mp = int_to_MethodePlacement(n);
      
    SCRIPT_SetPosition(nom, x, y, mp);

    return 0;
  }
    break;


  case CPprog::PSetPositionZ: {
    char * nom;
    corps x, y, z;
    TMethodePlacement mp;
    int n;
      
    pmessage("Instruction SetPositionZ.");
    
    VERIF_OK(val.upsetposz.nom->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    nom = e.val.val.str;
      
    VERIF_OK(val.upsetposz.x->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    x = e.val.val.r;

    VERIF_OK(val.upsetposz.y->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    y = e.val.val.r;
      
    VERIF_OK(val.upsetposz.z->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    z = e.val.val.r;
      
    VERIF_OK(val.upsetposz.relatif->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETInteger || e.type.type == pevaltype::PETSubrange);
    if (e.type.type == pevaltype::PETInteger)
      n = e.val.val.i;
    else
      n = e.val.val.s;

    mp = int_to_MethodePlacement(n);

    SCRIPT_SetZ(nom, z, mp);

    return 0;
  }
    break;


  case CPprog::PDeplacer: {
    char * nom;
    corps x, y;
    TMethodePlacement mp;
    int n;  
    
    pmessage("Instruction Deplacer.");

    VERIF_OK(val.updeplacer.nom->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    nom = e.val.val.str;
      
    VERIF_OK(val.updeplacer.x->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    x = e.val.val.r;

    VERIF_OK(val.updeplacer.y->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    y = e.val.val.r;
      
    VERIF_OK(val.updeplacer.relatif->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETInteger || e.type.type == pevaltype::PETSubrange);
    if (e.type.type == pevaltype::PETInteger)
      n = e.val.val.i;
    else
      n = e.val.val.s;
    
    mp = int_to_MethodePlacement(n);
      
    SCRIPT_Deplacer(nom, x, y, mp);

    return 0;
  }
    break;


  case CPprog::PDeplacerZ: pmesserr(position.toString()); pmesserr("L'instruction DeplacerZ n'est pas encore implémentée."); return -340; break;
  case CPprog::PSetHerosPosition: pmesserr(position.toString()); pmesserr("L'instruction SetHerosPosition n'est pas encore implémentée."); return -350; break;
  case CPprog::PSetHerosPositionZ: pmesserr(position.toString()); pmesserr("L'instruction SetHerosPositionZ n'est pas encore implémentée."); return -360; break;
  case CPprog::PHerosDeplacer: pmesserr(position.toString()); pmesserr("L'instruction HerosDeplacer n'est pas encore implémentée."); return -370; break;
  case CPprog::PHerosDeplacerZ: pmesserr(position.toString()); pmesserr("L'instruction HerosDeplacerZ n'est pas encore implémentée."); return -380; break;
  case CPprog::PCameraDeplacer: pmesserr(position.toString()); pmesserr("L'instruction CameraDeplacer n'est pas encore implémentée."); return -390; break;

  case CPprog::PSetCameraPosition: {
    real x, y, z;
    TMethodePlacement mp;
    int n;
    
    pmessage("Instruction Camera -> SetPosition.");
    
    VERIF_OK(val.upsetcamerapos.x->r_evaluate(env,mem,e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    x = e.val.val.r;

    VERIF_OK(val.upsetcamerapos.y->r_evaluate(env,mem,e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    y = e.val.val.r;

    VERIF_OK(val.upsetcamerapos.z->r_evaluate(env,mem,e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    z = e.val.val.r;

    VERIF_OK(val.upsetcamerapos.relatif->r_evaluate(env,mem,e));
    VERIF_OK_B(e.type.type == pevaltype::PETInteger || e.type.type == pevaltype::PETSubrange);
    if (e.type.type == pevaltype::PETInteger)
      n = e.val.val.i;
    else
      n = e.val.val.s;

    mp = int_to_MethodePlacement(n);
    
    SCRIPT_Camera_SetPosition(x,y,z,mp);

    return 0;
  }
    break;

  case CPprog::PCameraRotate: {
    real angle_x, angle_y, angle_z;
    TMethodePlacement mp;
    int n;
    
    pmessage("Instruction Camera -> Rotate.");
    
    VERIF_OK(val.upcamerarotate.angle_x->r_evaluate(env,mem,e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    angle_x = e.val.val.r;

    VERIF_OK(val.upcamerarotate.angle_y->r_evaluate(env,mem,e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    angle_y = e.val.val.r;

    VERIF_OK(val.upcamerarotate.angle_z->r_evaluate(env,mem,e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    angle_z = e.val.val.r;

    VERIF_OK(val.upcamerarotate.relatif->r_evaluate(env,mem,e));
    VERIF_OK_B(e.type.type == pevaltype::PETInteger || e.type.type == pevaltype::PETSubrange);
    if (e.type.type == pevaltype::PETInteger)
      n = e.val.val.i;
    else
      n = e.val.val.s;

    mp = int_to_MethodePlacement(n);
    
    SCRIPT_Camera_Rotate(angle_x,angle_y,angle_z,mp);

    return 0;
  }
    break;
 
  case CPprog::PCameraSolidariser: pmessage("Instruction CameraSolidariser"); Camera.SolidariserAuHeros(); return 0; break;
  case CPprog::PCameraDesolidariser: pmessage("Instruction CameraSolidariser."); Camera.DeSolidariser(); return 0; break;
  case CPprog::PCameraDefaut: pmessage("Instruction CameraDefaut"); Camera.InitCamera(); return 0; break;

  case CPprog::PCameraZoom:
    pmessage("Instruction CameraZoom.");
    VERIF_OK(val.upcamerazoom.coeff -> r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    SCRIPT_Camera_Zoom(e.val.val.r);
    return 0;
    break;

  case CPprog::PFrapper:
    pmessage("L'instruction Frapper.");
    VERIF_OK(val.upfrapper.nom->r_evaluate(env,mem,e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    SCRIPT_Frapper(e.val.val.str);
    return 0;
    break;

  case CPprog::PAjouterAnime: {
    pmessage("Instruction Ajouter Anime.");
    
    char * nom, * fichier;
    
    VERIF_OK(val.upajouteranime.nom->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    nom = e.val.val.str;

    VERIF_OK(val.upajouteranime.fichier->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    fichier = e.val.val.str;

    SCRIPT_AjouterObjetAnime(nom, fichier);
    return 0;
  }
    break;

  case CPprog::PAjouterNonAnime: {
    pmessage("Instruction Ajouter NonAnime.");
    
    char * nom, * fichier;
    
    VERIF_OK(val.upajouteranime.nom->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    nom = e.val.val.str;

    VERIF_OK(val.upajouteranime.fichier->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    fichier = e.val.val.str;

    SCRIPT_AjouterObjetNonAnime(nom, fichier);
    return 0;
  }
    break;

  case CPprog::PSetTemps:
    pmessage("Instruction SetTemps.");
    VERIF_OK(val.upsettemps.temps->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETReal);
    SCRIPT_SetTemps(e.val.val.r);
    return 0;
    break;

  case CPprog::PSetOrientation: {
    int orientation;
    char * nom;
    enum TDirection direction;

    pmessage("Instruction SetOrientation.");

    VERIF_OK(val.upsetorientation.nom->r_evaluate(env,mem,e));
    VERIF_OK_B(e.type.type == pevaltype::PETString);
    nom = e.val.val.str;

    VERIF_OK(val.upsetorientation.orientation->r_evaluate(env, mem, e));
    VERIF_OK_B(e.type.type == pevaltype::PETInteger || e.type.type == pevaltype::PETSubrange);
    if (e.type.type == pevaltype::PETSubrange)
      orientation = e.val.val.s;
    else
      orientation = e.val.val.i;

    direction = int_to_direction(orientation);
 
    SCRIPT_SetDirection(nom, (enum TDirection) (orientation - 1));

    return 0;
  }
    break;


  case CPprog::PWaitFor:
    VERIF_OK_B(pascal_expr_compile(prog -> val.upwaitfor.nom, futur_expr1));
    VERIF_OK_B(futur_expr_to_futur_prog(futur_expr1, futur1));
    pliste_concat2_surplace(futur1, futur);
    futur = futur1;
    return true;
    break;

  case CPprog::PBloquerTemps: return true; break; 
  case CPprog::PDebloquerTemps: return true; break;
  default: assert(false); return false;
  }

  assert(false);
  return false;
}

#endif

