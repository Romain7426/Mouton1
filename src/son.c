#include "global.hpp"
#include "son.hpp"
#include "pascal/pascal.tools.hpp"

static char * fichier_nom_sans_extension(const char * filename);

static Mix_Music * try_to_load(const char * rep, const char * file_sans_ext, const char * ext);


// si filename == NULL ou "", alors c'est un peu comme si on avait une musique vide
CMusique::CMusique(const char * filename) {
  NomMusique = NULL;

  if (filename == NULL)
    return;

  if (0 == strcmp(filename, ""))
    return;

  NomMusique = strcopy(filename);


  char * nom_sans_ext = fichier_nom_sans_extension(filename);

  music = try_to_load(SONSDIR, nom_sans_ext, ".ogg");

  if (music == NULL)
    music = try_to_load(SONSDIR, nom_sans_ext, ".mp3");
  
  if (music == NULL)
    music = try_to_load(SONSDIR, nom_sans_ext, ".wav");
  
#ifndef LIBPROG_SYS_MACOSX
  if (music == NULL)
    music = try_to_load(SONSDIR, nom_sans_ext, ".mid");
#endif
  
  if (music == NULL)
    printf("ERREUR: Impossible de charger la musique %s!\n", filename);

  delete nom_sans_ext;
}


Mix_Music * try_to_load(const char * rep, const char * file_sans_ext, const char * ext) {
  char * reelfile;
  Mix_Music * retour;

  reelfile = STRCAT3_(rep, file_sans_ext, ext);
  
  retour = Mix_LoadMUS(reelfile);

  delete[] reelfile;
  
  return retour;
}


char * fichier_nom_sans_extension(const char * filename) {
  size_t len = strlen(filename);
  if (len < 4)
    return strcopy(filename);

  if (filename[len-4] != '.')
    return strcopy(filename);

  char * filename_sans_extension = strcopy(filename);
  filename_sans_extension[len-4] = '\0';
  return filename_sans_extension;
}


void CMusique::Jouer(void) {
  if (NomMusique == NULL)
    Mix_HaltMusic();
  else
    if (Mix_PlayMusic(music, -1)==-1)
      printf("ERREUR: Impossible de jouer le son\n");
}


CMusique::~CMusique(void) {
  if (NomMusique != NULL) {                   
    printf("Destruction de la musique...\n");  
    Mix_HaltMusic(); 
    Mix_FreeMusic(music);  
    delete[] NomMusique;
    printf("   Destruction de la musique REUSSIE !!!\n");
  }
}






/*SON**************************************************************************/

CSon::CSon(const char * filename) {
  char * reelfile;
  reelfile = new char[strlen(SONSDIR) + strlen(filename) + 1];
  strcat(strcpy(reelfile, SONSDIR), filename);
  filename = reelfile;

  printf("Chargement du fichier son %s...\n", filename);
  if (!(son=Mix_LoadWAV(filename))) {
    printf("ERREUR: Mix_LoadMUS a fait pouf!\n");
    delete[] reelfile;
    return;
  };

  printf("    réussi!\n");
}    


void CSon::Jouer(void) {
  if (Mix_PlayChannel(-1, son, 0) == -1) {
    printf("ERREUR: Impossible de jouer le son\n");
  }
}   

CSon::~CSon(void) {
  Mix_FreeChunk(son);  
}




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
  }
  
  // print out some info on the audio device and stream
  
  Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
  bits = audio_format&0xFF;
  
  printf("Opened audio at %d Hz %d bit %s, %d bytes audio buffer\n", audio_rate, bits, audio_channels > 1 ? "stereo" : "mono", audio_buffers);
  
  return 0; // ca rend quoi cette fonction ???  
} 


void close_audio(void) {
  Mix_CloseAudio(); 
}

