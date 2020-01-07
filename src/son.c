#include "global.h"
#include "son.h"
//#include "pascal/pascal.tools.hpp"

static char * fichier_nom_sans_extension(const char * filename);

static Mix_Music * try_to_load(const char * rep, const char * file_sans_ext, const char * ext);


// si filename == NULL ou "", alors c'est un peu comme si on avait une musique vide
CMusique * CMusique_make(const char * filename) {
  MALLOC_BZERO(CMusique,this); 
  
  ASSIGN_METHOD(CMusique,this,Jouer); 

  this -> NomMusique = NULL;

  if (NULL == filename) { return this; }; 

  if (0 == *filename) { return this; }; 

  this -> NomMusique = strcopy(filename);
  

  char * nom_sans_ext = fichier_nom_sans_extension(filename);
  
  this -> music = try_to_load(SONSDIR, nom_sans_ext, ".ogg");
  
  if (this -> music == NULL)
    this -> music = try_to_load(SONSDIR, nom_sans_ext, ".mp3");
  
  if (this -> music == NULL)
    this -> music = try_to_load(SONSDIR, nom_sans_ext, ".wav");
  
  if (this -> music == NULL)
    this -> music = try_to_load(SONSDIR, nom_sans_ext, ".mid");
  
  if (this -> music == NULL)
    printf("ERREUR: Impossible de charger la musique %s!\n", filename);
  
  free(nom_sans_ext);
  
  return this; 
};


Mix_Music * try_to_load(const char * rep, const char * file_sans_ext, const char * ext) {
  char * reelfile;
  Mix_Music * retour;

  reelfile = strconcat3(rep, file_sans_ext, ext);
  
  retour = Mix_LoadMUS(reelfile);
  
  free(reelfile); 
  
  return retour;
}; 


char * fichier_nom_sans_extension(const char * filename) {
  const size_t len = strlen(filename);
  char * filename_sans_extension = strcopy(filename);
  char * p = filename_sans_extension + len - 1; 
  for (size_t i = 0; i < len; i++) { 
    if (*p != '.') { p--; continue; }; 
    *p = '\0';
    break; 
  }; 
  return filename_sans_extension; 
}; 


void CMusique__Jouer(CMusique * this) {
  if (this -> NomMusique == NULL)
    Mix_HaltMusic();
  else
    if (Mix_PlayMusic(this -> music, -1)==-1)
      printf("ERREUR: Impossible de jouer le son\n");
};


void CMusique_delete(CMusique * this) {
  printf("Destruction de la musique...\n");  
  Mix_HaltMusic(); 
  Mix_FreeMusic(this -> music);  
  free(this -> NomMusique); 
  free(this); 
  printf("   Destruction de la musique REUSSIE !!!\n");
};






/*SON**************************************************************************/

CSon * CSon_make(const char * filename) {
  printf("Chargement du fichier son %s...\n", filename);
  
  MALLOC_BZERO(CSon,this); 
  
  ASSIGN_METHOD(CSon,this,Jouer); 
  
  this -> filename = strcopy(filename); 
  
  char reelfile[strlen(SONSDIR) + strlen(filename) + 1];
  strcat(strcpy(reelfile, SONSDIR), filename);
  filename = reelfile;
  
  this -> son = Mix_LoadWAV(filename);
  if (!this -> son) {
    printf("ERREUR: Mix_LoadMUS a fait pouf!\n");
    return this;
  };

  printf("    réussi!\n");
  return this; 
};


void CSon__Jouer(CSon * this) {
  int alright_huh;
  alright_huh = Mix_PlayChannel(-1, this -> son, 0); 
  if (alright_huh == -1) {
    printf("ERREUR: Impossible de jouer le son\n");
  };
};  

void CSon_delete(CSon * this) {
  Mix_FreeChunk(this -> son);  
  free(this -> filename); 
  free(this); 
};




int init_audio(void) {
  printf("Initialisation de la carte son (via SDL)...\n");
  
  int audio_rate, audio_channels,
    // set this to any of 512,1024,2048,4096
    // the higher it is, the more FPS shown and CPU needed
  audio_buffers = 512;
  Uint16 audio_format;
  //int volume=SDL_MIX_MAXVOLUME;
  int bits = 0;
  
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, audio_buffers) < 0) {
    printf("Mix_OpenAudio a fait pouf !\n"); // On devrait peut etre quitter la ?
  }; 
  
  // print out some info on the audio device and stream
  
  Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
  bits = audio_format&0xFF;
  
  printf("Opened audio at %d Hz %d bit %s, %d bytes audio buffer\n", audio_rate, bits, audio_channels > 1 ? "stereo" : "mono", audio_buffers);
  
  return 0; // ca rend quoi cette fonction ???  
}; 


void close_audio(void) {
  Mix_CloseAudio(); 
}; 

