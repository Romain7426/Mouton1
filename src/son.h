#ifndef SON_H
#define SON_H

extern int init_audio(void);
extern void close_audio(void);

struct CSon {
  Mix_Chunk * son;    
  char * filename;
  void (* Jouer)(struct CSon * this);
};
extern CSon * CSon_make(const char * filename);   
extern void CSon_delete(CSon * this);
extern void CSon__Jouer(CSon * this);

struct CMusique {
  Mix_Music * music;
  char * NomMusique;
  void (* Jouer)(CMusique * this);
};
extern CMusique * CMusique_make(const char * filename); 
extern void CMusique_delete(CMusique * this);
extern void CMusique__Jouer(CMusique * this);

//extern void mixaudio(void * unused, Uint8 * stream, int len);

#endif /* SON_H */
