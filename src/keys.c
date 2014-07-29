#include "global.h"
#include "keys.h"


  CKey(char kkk);
  bool Enfoncee(void);
  bool Appuye(void);


CKey::CKey(char kkk) : kk(kkk), previous(0) {}


bool CKey::Enfoncee(void) {
  bool b;

  b = (KeyBoard[kk] != 0);
  previous = KeyBoard[kk]; 
  return b;
}


bool CKey::Appuye(void) {
  bool b;

  b = (previous == 0) && (KeyBoard[kk] != 0);
  previous = KeyBoard[kk];
  return b;
} 



unsigned char * KeyBoard;


CKey KeySpace = CKey(SDLK_SPACE);
CKey KeyEchap = CKey(SDLK_ESCAPE);
CKey KeyReturn = CKey(SDLK_RETURN);
CKey KeyF12 = CKey('g');

CKey KeyI = CKey('i');
CKey KeyL = CKey('l');
CKey KeyM = CKey('m');
CKey KeyO = CKey('o');
CKey KeyP = CKey('p');
CKey KeyK = CKey('k');
