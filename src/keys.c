#include "global.h"
#include "keys.h"

unsigned char * KeyBoard = NULL;

#if 0
#define CKey__Enfoncee__NAME(cname) glue3(CKey__Enfoncee,__,cname)
#define CKey__Enfoncee__META(cname)			\
  bool glue3(CKey__Enfoncee,__,cname)(void) {		\
    bool b;						\
    							\
    b = (KeyBoard[(unsigned char) cname.kk] != 0);		\
    cname.previous = KeyBoard[(unsigned char) cname.kk];	\
    return b;							\
  };

CKey__Enfoncee__META(SDLK_SPACE); 
#endif 

#if defined(__clang__) 
#define CKey_StaticInit(kkk) ((struct CKey) { kkk, 0, CKey__Enfoncee, CKey__Appuye }) 
#elif defined(__GNUC__) 
#define CKey_StaticInit(kkk)                { kkk, 0, CKey__Enfoncee, CKey__Appuye } 
#else 
#define CKey_StaticInit(kkk) ((struct CKey) { kkk, 0, CKey__Enfoncee, CKey__Appuye }) 
#endif 
//CKey KeySpace  = { 0, 0, NULL, NULL }; //CKey_StaticInit(SDLK_SPACE); 
//CKey KeySpace  = { SDLK_SPACE, 0, CKey__Enfoncee, CKey__Appuye }; //CKey_StaticInit(SDLK_SPACE); 
CKey KeySpace  = CKey_StaticInit(SDLK_SPACE); 
CKey KeyEchap  = CKey_StaticInit(SDLK_ESCAPE);
CKey KeyReturn = CKey_StaticInit(SDLK_RETURN);
CKey KeyF12    = CKey_StaticInit('g');

CKey KeyI = CKey_StaticInit('i');
CKey KeyL = CKey_StaticInit('l');
CKey KeyM = CKey_StaticInit('m');
CKey KeyO = CKey_StaticInit('o');
CKey KeyP = CKey_StaticInit('p');
CKey KeyK = CKey_StaticInit('k');

#define kk       (this -> kk) 
#define previous (this -> previous) 

CKey * CKey_make(char kkk) {
  assert(false);
  MALLOC_BZERO(CKey,this);
  
  ASSIGN_METHOD(CKey,this,Enfoncee); 
  ASSIGN_METHOD(CKey,this,Appuye); 
  
  kk = kkk; 
  previous = 0;


#ifdef KBD_AZERTY
  fprintf(stderr, "KBD AZERTY" "\n");
#elif defined KBD_QWERTY
  fprintf(stderr, "KBD QWERTY" "\n");
#else
  fprintf(stderr, "KBD UNKNOWN" "\n");
#endif
  assert(false);

  
  return this; 
}; 

void CKey_delete(CKey * this) {
  assert(false);
  free(this); 
}; 


bool CKey__Enfoncee(CKey * this) {
  bool b;

  b = (KeyBoard[(unsigned char) kk] != 0);
  previous = KeyBoard[(unsigned char) kk]; 
  return b;
};


bool CKey__Appuye(CKey * this) {
  bool b;
  
  b = (previous == 0) && (KeyBoard[(unsigned char) kk] != 0);
  previous = KeyBoard[(unsigned char) kk];
  return b;
}; 



