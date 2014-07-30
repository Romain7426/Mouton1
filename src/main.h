#ifndef MAIN_HPP
#define MAIN_HPP

extern void Init(void);
extern void Free(void);

extern void RaiseInput(void);
extern void RaiseLife(void);
extern void RaiseRender(void);


struct api_contexte_t;
//extern const api_contexte_t api_contexte;
extern struct api_contexte_t api_contexte;

struct CCamera;
struct CMoteurTeleportation;
struct CMenuEntreeNom;
extern struct CCamera Camera;
extern struct CMoteurTeleportation MoteurTeleportation;
extern struct CMenuEntreeNom * MenuEntreeNom;



#endif /* MAIN_HPP */
