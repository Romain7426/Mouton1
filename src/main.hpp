#ifndef MAIN_HPP
#define MAIN_HPP

extern void Init(void);
extern void Free(void);

extern void RaiseInput(void);
extern void RaiseLife(void);
extern void RaiseRender(void);


struct api_contexte_t;
//extern const api_contexte_t api_contexte;
extern api_contexte_t api_contexte;

class CCamera;
class CMoteurTeleportation;
class CMenuEntreeNom;
extern CCamera Camera;
extern CMoteurTeleportation MoteurTeleportation;
extern CMenuEntreeNom * MenuEntreeNom;



#endif /* MAIN_HPP */
