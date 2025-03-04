#include "global.h"
#include "son.h"
//#include "pascal/pascal.tools.hpp"

#define DEBUG_TRACE 0

static char * fichier_nom_sans_extension(const char * filename);

static Mix_Music * try_to_load(const char * rep, const char * file_sans_ext, const char * ext);


// si filename == NULL ou "", alors c'est un peu comme si on avait une musique vide
CMusique * CMusique_make(const char * filename) {
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  MALLOC_BZERO(CMusique,this); 
  
  ASSIGN_METHOD(CMusique,this,Jouer); 

  this -> NomMusique = NULL;

  if (NULL == filename) { return this; }; 

  if (0 == *filename) { return this; }; 

  this -> NomMusique = strcopy(filename);
  
  char * nom_sans_ext = fichier_nom_sans_extension(filename);
  //messerr("nom_sans_ext: '%s'" "\n", nom_sans_ext); 
  
  do {
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
    this -> music = try_to_load(SONSDIR, nom_sans_ext, ".ogg");
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
    if (this -> music != NULL) { break; }; 
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
    messerr("SDL_mixer: %s" "\n", Mix_GetError()); 
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
    
    this -> music = try_to_load(SONSDIR, nom_sans_ext, ".mp3");
    if (this -> music != NULL) { break; }; 
    messerr("SDL_mixer: %s" "\n", Mix_GetError()); 
    
    this -> music = try_to_load(SONSDIR, nom_sans_ext, ".wav"); 
    if (this -> music != NULL) { break; }; 
    messerr("SDL_mixer: %s" "\n", Mix_GetError()); 
    
    this -> music = try_to_load(SONSDIR, nom_sans_ext, ".mid");
    if (this -> music != NULL) { break; }; 
    messerr("SDL_mixer: %s" "\n", Mix_GetError()); 
    
  } while (false); 
  
  if (this -> music == NULL) {
    messerr("Impossible de charger la musique %s!\n", filename);
#if 1 
    {
      char filename_realpath[PATH_MAX]; 
      messerr("REALPATH: %s" "\n", realpath(filename, filename_realpath)); 
    }; 
#endif 
  };
  
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  free(nom_sans_ext);
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  
  return this; 
};


Mix_Music * try_to_load(const char * rep, const char * file_sans_ext, const char * ext) {
  LOCAL_ALLOCA__DECLARE(int16_t,INT16_MAX); 
  char * reelfile;
  Mix_Music * retour;

  reelfile = strconcat3__alloca(rep, file_sans_ext, ext);
  
  retour = Mix_LoadMUS(reelfile);
  
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
  if (this == NULL || this -> NomMusique == NULL) {
    Mix_HaltMusic();
    return; 
  }; 

  if (-1 == Mix_PlayMusic(this -> music, -1)) {
    messerr("Impossible de jouer le son: %s" "\n", this -> NomMusique); 
    messerr("SDL_mixer: %s" "\n", Mix_GetError()); 
  };
};


void CMusique_delete(CMusique * this) {
  printf("Destruction de la musique...\n");  
  Mix_HaltMusic(); 
#if 1 
  // RL: 2020-01-12: Crashes if ogg 
  if (this -> music != NULL) Mix_FreeMusic(this -> music);  
#endif 
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
    messerr("Mix_LoadMUS a fait pouf: %s" "\n", filename); 
#if 1 
    {
      char filename_realpath[PATH_MAX]; 
      messerr("REALPATH: %s" "\n", realpath(filename, filename_realpath));
    }; 
#endif 
    messerr("SDL_mixer: %s" "\n", Mix_GetError()); 
    return this;
  };

  printf("    réussi!\n");
  return this; 
};


void CSon__Jouer(CSon * this) {
  int alright_huh;
  alright_huh = Mix_PlayChannel(-1, this -> son, 0); 
  if (alright_huh == -1) {
    messerr("Impossible de jouer le son\n");
    messerr("SDL_mixer: %s" "\n", Mix_GetError()); 
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
  bits = audio_format & 0xFF;
  
  printf("Opened audio at %d Hz %d bit %s, %d bytes audio buffer" "\n", audio_rate, bits, audio_channels > 1 ? "stereo" : "mono", audio_buffers); 
  
  return 0; // ça rend quoi cette fonction ???  
}; 


void close_audio(void) {
#if 1 
  //RL: 2020-01-12: It crashes...
  Mix_CloseAudio(); 
#endif 
}; 

