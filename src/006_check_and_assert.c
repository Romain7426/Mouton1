#include "global.h"
#include "006_check_and_assert.h"
#include "texture.h"
#include "camera.h"




void check_and_assert(const int8_t debug_print_huh, const int stderr_d) { 
  CTexture__check_and_assert(debug_print_huh, stderr_d); 
  CCamera__check_and_assert(debug_print_huh, stderr_d); 
  CMoteurTeleportation__check_and_assert(debug_print_huh, stderr_d); 
  CZoneTeleportation__check_and_assert(debug_print_huh, stderr_d); 
  CMap__check_and_assert(debug_print_huh, stderr_d); 
  CSol__check_and_assert(debug_print_huh, stderr_d); 
  CAffichageCoeur__check_and_assert(debug_print_huh, stderr_d); 
  CAffichageMainPierre__check_and_assert(debug_print_huh, stderr_d); 
  CPageTitre__check_and_assert(debug_print_huh, stderr_d); 
}; 

