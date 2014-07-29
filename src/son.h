#ifndef SON_H
#define SON_H




extern int init_audio(void);
extern void close_audio(void);

struct CSon;
struct CMusique;


struct CSon {
private:
  Mix_Chunk * son;
    
public:
  CSon(const char * filename);   
  ~CSon(void);
  void Jouer(void);
};
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CSon);




struct CMusique {
private:
  Mix_Music * music;
  
public:
  const char * NomMusique;
  CMusique(const char * filename);
  ~CMusique(void);
  void Jouer(void);
};
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CMusique);


//extern void mixaudio(void * unused, Uint8 * stream, int len);



#endif /* SON_H */

