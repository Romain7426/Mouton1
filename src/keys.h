#ifndef KEYS_H
#define KEYS_H


// RL: TODO XXX FIXME: Bad
extern unsigned char * KeyBoard;


struct CKey {
  char kk;
  char previous;

  bool (* Enfoncee)(struct CKey * this); 
  bool (* Appuye)(struct CKey * this); 
};
extern CKey * CKey_make(char kkk);
extern void CKey_delete(CKey * this); 
extern bool CKey__Enfoncee(CKey * this);
extern bool CKey__Appuye(CKey * this);




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

#ifdef KBD_AZERTY

#define KEY_UP    (KeyBoard[SDLK_UP]    || KeyBoard['z'])
#define KEY_DOWN  (KeyBoard[SDLK_DOWN]  || KeyBoard['s'])
#define KEY_LEFT  (KeyBoard[SDLK_LEFT]  || KeyBoard['q'])
#define KEY_RIGHT (KeyBoard[SDLK_RIGHT] || KeyBoard['d'])

#define KEY_VUE_ANGLE_PLUS  (KeyBoard[SDLK_PAGEDOWN] || KeyBoard['c'])
#define KEY_VUE_ANGLE_MOINS (KeyBoard[SDLK_PAGEUP]   || KeyBoard['w'])
           
#elif defined KBD_QWERTY

#define KEY_UP    (KeyBoard[SDLK_UP]    || KeyBoard['w'])
#define KEY_DOWN  (KeyBoard[SDLK_DOWN]  || KeyBoard['s'])
#define KEY_LEFT  (KeyBoard[SDLK_LEFT]  || KeyBoard['a'])
#define KEY_RIGHT (KeyBoard[SDLK_RIGHT] || KeyBoard['d'])

#define KEY_VUE_ANGLE_PLUS    (KeyBoard['c'])
#define KEY_VUE_ANGLE_MOINS   (KeyBoard['z'])

#else

#define KEY_UP    (KeyBoard[SDLK_UP]    || KeyBoard['z'])
#define KEY_DOWN  (KeyBoard[SDLK_DOWN]  || KeyBoard['s'])
#define KEY_LEFT  (KeyBoard[SDLK_LEFT]  || KeyBoard['q'])
#define KEY_RIGHT (KeyBoard[SDLK_RIGHT] || KeyBoard['d'])

#define KEY_VUE_ANGLE_PLUS  (KeyBoard['c'])
#define KEY_VUE_ANGLE_MOINS (KeyBoard['w'])

#endif


#define KEY_CAMERA_DIST_PLUS  (KeyBoard[SDLK_PAGEDOWN])
#define KEY_CAMERA_DIST_MOINS (KeyBoard[SDLK_PAGEUP])

#define KEY_CAMERA_ANGLE_Z_PLUS  (KeyBoard['o'])
#define KEY_CAMERA_ANGLE_Z_MOINS (KeyBoard['l'])






#define KEY_JUMP  (KeySpace.Appuye(&KeySpace) || KeyM.Appuye(&KeyM))

#define KEY_VAISSEAU_UP   (KeyBoard[SDLK_PAGEDOWN] || KeyBoard['i'])
#define KEY_VAISSEAU_DOWN (KeyBoard[SDLK_PAGEUP]   || KeyBoard['p'])

#define KEY_MENU_JEU (KeyI.Appuye(&KeyI))
#define KEY_FRAPPER  (KeyK.Appuye(&KeyK))
  
#define KEY_MENU_VALIDER (KeyReturn.Appuye(&KeyReturn) || KeySpace.Appuye(&KeySpace) || KeyK.Appuye(&KeyK)) 
#define KEY_MENU_ECHAP   (KeyP.Appuye(&KeyP)      || KeyEchap.Appuye(&KeyEchap)) 

#define KEY_PASSER_TITRE KEY_MENU_VALIDER

#define KEY_MENU_SYSTEME (KeyEchap.Appuye(&KeyEchap))

#if 1 
#define KEY_ACTION1 (KeyI.Appuye(&KeyO))
#define KEY_ACTION2 (KeyO.Appuye(&KeyL)) // || KeyL.Appuye())
#define KEY_ACTION3 (KeyP.Appuye(&KeyP))
#else 
#define KEY_ACTION1 (KeyI.Appuye(&KeyI))
#define KEY_ACTION2 (KeyO.Appuye(&KeyO)) // || KeyL.Appuye())
#define KEY_ACTION3 (KeyP.Appuye(&KeyP))
#endif 

#define KEY_ACTIVEDESACTIVEMOTEURPHYSIQUE (KeyF12.Appuye(&KeyF12))





#endif /* KEYS_H */

