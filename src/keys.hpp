#ifndef KEYS_HPP
#define KEYS_HPP


// TODO XXX Bad
extern unsigned char * KeyBoard;


class CKey {
private:
  char kk;
  char previous;
  
public:  
  //  CKey::CKey(char kkk);
  CKey(char kkk);
  bool Enfoncee(void);
  bool Appuye(void);
};


extern CKey KeySpace;
extern CKey KeyEchap;
extern CKey KeyReturn;

extern CKey KeyP;
extern CKey KeyI;

extern CKey KeyK;
extern CKey KeyO;
extern CKey KeyM;

extern CKey KeyL;

extern CKey KeyF12;



/*** les touches ************/

#ifdef LIBPROG_SYS_MACOSX

#define KEY_UP    (KeyBoard[SDLK_UP]    || KeyBoard['z'])
#define KEY_DOWN  (KeyBoard[SDLK_DOWN]  || KeyBoard['s'])
#define KEY_LEFT  (KeyBoard[SDLK_LEFT]  || KeyBoard['q'])
#define KEY_RIGHT (KeyBoard[SDLK_RIGHT] || KeyBoard['d'])

#define KEY_VUE_ANGLE_PLUS  (KeyBoard[SDLK_PAGEDOWN] || KeyBoard['c'])
#define KEY_VUE_ANGLE_MOINS (KeyBoard[SDLK_PAGEUP]   || KeyBoard['w'])
           
#else

#define KEY_UP    (KeyBoard[SDLK_UP]    || KeyBoard['w'])
#define KEY_DOWN  (KeyBoard[SDLK_DOWN]  || KeyBoard['s'])
#define KEY_LEFT  (KeyBoard[SDLK_LEFT]  || KeyBoard['a'])
#define KEY_RIGHT (KeyBoard[SDLK_RIGHT] || KeyBoard['d'])

#define KEY_VUE_ANGLE_PLUS  (KeyBoard[SDLK_PAGEDOWN] || KeyBoard['c'])
#define KEY_VUE_ANGLE_MOINS (KeyBoard[SDLK_PAGEUP]   || KeyBoard['z'])
           
#endif





#define KEY_JUMP  (KeySpace.Appuye() || KeyM.Appuye())

#define KEY_VAISSEAU_UP   (KeyBoard[SDLK_PAGEDOWN] || KeyBoard['i'])
#define KEY_VAISSEAU_DOWN (KeyBoard[SDLK_PAGEUP]   || KeyBoard['p'])

#define KEY_MENU_JEU (KeyI.Appuye())
#define KEY_FRAPPER  (KeyK.Appuye())
           
#define KEY_MENU_VALIDER (KeyReturn.Appuye() || KeySpace.Appuye() || KeyK.Appuye()) 
#define KEY_MENU_ECHAP   (KeyP.Appuye()      || KeyEchap.Appuye()) 

#define KEY_PASSER_TITRE KEY_MENU_VALIDER

#define KEY_MENU_SYSTEME (KeyEchap.Appuye())

#define KEY_ACTION1 (KeyI.Appuye())
#define KEY_ACTION2 (KeyO.Appuye()) // || KeyL.Appuye())
#define KEY_ACTION3 (KeyP.Appuye())

#define KEY_ACTIVEDESACTIVEMOTEURPHYSIQUE (KeyF12.Appuye())





#endif /* KEYS_HPP */

