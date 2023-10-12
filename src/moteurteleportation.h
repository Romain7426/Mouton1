#ifndef MOTEURTELEPORTATION_H
#define MOTEURTELEPORTATION_H

/****************************************************
   ZONE DE TELEPORTATION
******************************************/
enum {              CZoneTeleportation_bytesize = 96 }; 
extern const int8_t CZoneTeleportation_bytesize_actual; 
static void CZoneTeleportation__check_and_assert(const int8_t debug_print_huh, const int stderr_d) { 

  if (debug_print_huh) { 
    //fprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "I failed to clean up the log subdir.' " "\n", __func__); 
    write_string4(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<", __func__, "()>}: ", "CZoneTeleportation_bytesize: "); write_long_long_int(stderr_d, CZoneTeleportation_bytesize); write_eol(stderr_d); 
    write_string4(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<", __func__, "()>}: ", "CZoneTeleportation_bytesize_actual: "); write_long_long_int(stderr_d, CZoneTeleportation_bytesize_actual); write_eol(stderr_d); 
  }; 
  assert(CZoneTeleportation_bytesize >= CZoneTeleportation_bytesize_actual); 
  
}; 

//CZoneTeleportation(void) {}; 
extern CZoneTeleportation * CZoneTeleportation_make(TPoint3D in_position, TPoint3D in_dimension, TDirection in_depart_direction, const char * in_destination_carte, TPoint3D in_destination_position, TDirection in_destination_direction); 
extern CZoneTeleportation * CZoneTeleportation_copy(const CZoneTeleportation * this); 
extern void                 CZoneTeleportation_delete(CZoneTeleportation * this); 

extern       bool           CZoneTeleportation__dedans_huh(const CZoneTeleportation * this, const TPoint3D p); 
extern const char *         CZoneTeleportation__destination_carte(const CZoneTeleportation * this);
extern       TDirection     CZoneTeleportation__depart_direction (const CZoneTeleportation * this);
extern       TPoint3D       CZoneTeleportation__position         (const CZoneTeleportation * this);
extern       TPoint3D       CZoneTeleportation__dimension        (const CZoneTeleportation * this);


/****************************************************
   MOTEUR DE TELEPORTATION
******************************************/

enum {              CMoteurTeleportation_bytesize = 96 }; 
extern const int8_t CMoteurTeleportation_bytesize_actual; 
static void CMoteurTeleportation__check_and_assert(const int8_t debug_print_huh, const int stderr_d); 

extern CMoteurTeleportation * CMoteurTeleportation__make(void);
extern CMoteurTeleportation * CMoteurTeleportation__make_content(CMoteurTeleportation * this);
extern void                   CMoteurTeleportation__delete(CMoteurTeleportation * this);
extern void                   CMoteurTeleportation__delete_content(CMoteurTeleportation * this);

extern void                   CMoteurTeleportation__DebuterTeleportation(CMoteurTeleportation * this, const CZoneTeleportation * in_zt);
extern bool                   CMoteurTeleportation__IsTeleportationEnCours(const CMoteurTeleportation * this);
extern void                   CMoteurTeleportation__SetCouleurFondu(CMoteurTeleportation * this, int in_couleur);
extern void                   CMoteurTeleportation__Life(CMoteurTeleportation * this, CMap * * Map_ptr, bool * EnVaisseau_ptr, CBonhomme * * Hero_ptr, bool * SCRIPT_SystemeRendMainAuScript_ptr);
extern void                   CMoteurTeleportation__Render(const CMoteurTeleportation * this, CMap * * Map_ptr, bool * EnVaisseau_ptr, CBonhomme * * Hero_ptr, const riemann_t * our_manifold);

static void CMoteurTeleportation__check_and_assert(const int8_t debug_print_huh, const int stderr_d) { 

  if (debug_print_huh) { 
    //fprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "I failed to clean up the log subdir.' " "\n", __func__); 
    write_string4(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<", __func__, "()>}: ", "CMoteurTeleportation_bytesize: "); write_long_long_int(stderr_d, CMoteurTeleportation_bytesize); write_eol(stderr_d); 
    write_string4(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<", __func__, "()>}: ", "CMoteurTeleportation_bytesize_actual: "); write_long_long_int(stderr_d, CMoteurTeleportation_bytesize_actual); write_eol(stderr_d); 
  }; 
  assert(CMoteurTeleportation_bytesize >= CMoteurTeleportation_bytesize_actual); 
  
}; 


#endif
