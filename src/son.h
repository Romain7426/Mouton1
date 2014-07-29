#ifndef SON_HPP
#define SON_HPP




extern int init_audio(void);
extern void close_audio(void);

class CSon;
class CMusique;


class CSon {
private:
  Mix_Chunk * son;
    
public:
  CSon(const char * filename);   
  ~CSon(void);
  void Jouer(void);
};




class CMusique {
private:
  Mix_Music * music;
  
public:
  const char * NomMusique;
  CMusique(const char * filename);
  ~CMusique(void);
  void Jouer(void);
};


//extern void mixaudio(void * unused, Uint8 * stream, int len);



#endif /* SON_HPP */

