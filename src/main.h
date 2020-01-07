#ifndef MAIN_HPP
#define MAIN_HPP

extern void Init(void);
extern void Free(void);

extern void RaiseInput(void);
extern void RaiseLife(void);
extern void RaiseRender(void);

extern api_contexte_t api_contexte;
extern CCamera Camera;
extern CMoteurTeleportation MoteurTeleportation;
extern CMenuEntreeNom * MenuEntreeNom;

#endif /* MAIN_HPP */
