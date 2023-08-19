#include "global.h"
#include <anime.h>
#include "anime_database.h"
#include <time.h>

enum { ANIME_DATABASE__MAX = 32 }; 

static const char * anime_database__filename_at_compile_time[ANIME_DATABASE__MAX] = { 
  "bob.anime", 
  "heros.anime", 
  "pere.anime", 
  "brigitte.anime", 
  "juliette.anime", 
  "mouton.anime", 
  "chaman.anime", 
  "dinotore.anime", 
  "heros.anime", 
  "pecu.anime", 
  "prokofiev.anime", 
  "sang.anime", 
  "chapinmechant.anime", 
  "fantome.anime", 
  "moutonmechant.anime", 
  "pierre.anime", 
  "saintexupery.anime", 
  "y.anime", 
  "m.anime", 
  "c.anime", 
  "a.anime", 
  "bizarre1.anime", 
  "bizarre2.anime", 
  "bucheron.anime", 
  "chapin.anime", 
  "eclaboussures.anime", 
  "homme_bizarre.anime", 
  "puit_boss.anime", 
  "squelette.anime", 
  NULL  
}; 

static const char * anime_database__filecontent_at_compile_time[ANIME_DATABASE__MAX] = { 
#include "bob.anime.ci" 
,
#include "heros.anime.ci" 
,
#include "pere.anime.ci" 
,
#include "brigitte.anime.ci" 
,
#include "juliette.anime.ci" 
,
#include "mouton.anime.ci" 
,
#include "chaman.anime.ci" 
,
#include "dinotore.anime.ci" 
,
#include "heros.anime.ci" 
,
#include "pecu.anime.ci" 
,
#include "prokofiev.anime.ci" 
,
#include "sang.anime.ci" 
,
#include "chapinmechant.anime.ci" 
,
#include "fantome.anime.ci" 
,
#include "moutonmechant.anime.ci" 
,
#include "pierre.anime.ci" 
,
#include "saintexupery.anime.ci" 
,
#include "y.anime.ci" 
,
#include "m.anime.ci" 
,
#include "c.anime.ci" 
,
#include "a.anime.ci" 
,
#include "bizarre1.anime.ci" 
,
#include "bizarre2.anime.ci" 
,
#include "bucheron.anime.ci" 
,
#include "chapin.anime.ci" 
,
#include "eclaboussures.anime.ci" 
,
#include "homme_bizarre.anime.ci" 
,
#include "puit_boss.anime.ci" 
,
#include "squelette.anime.ci" 
,
NULL 
};

static const time_t anime_database__mtime_at_compile_time[ANIME_DATABASE__MAX] = { 
#include "bob.anime.mtime" 
,
#include "heros.anime.mtime" 
,
#include "pere.anime.mtime" 
,
#include "brigitte.anime.mtime" 
,
#include "juliette.anime.mtime" 
,
#include "mouton.anime.mtime" 
,
#include "chaman.anime.mtime" 
,
#include "dinotore.anime.mtime" 
,
#include "heros.anime.mtime" 
,
#include "pecu.anime.mtime" 
,
#include "prokofiev.anime.mtime" 
,
#include "sang.anime.mtime" 
,
#include "chapinmechant.anime.mtime" 
,
#include "fantome.anime.mtime" 
,
#include "moutonmechant.anime.mtime" 
,
#include "pierre.anime.mtime" 
,
#include "saintexupery.anime.mtime" 
,
#include "y.anime.mtime" 
,
#include "m.anime.mtime" 
,
#include "c.anime.mtime" 
,
#include "a.anime.mtime" 
,
#include "bizarre1.anime.mtime" 
,
#include "bizarre2.anime.mtime" 
,
#include "bucheron.anime.mtime" 
,
#include "chapin.anime.mtime" 
,
#include "eclaboussures.anime.mtime" 
,
#include "homme_bizarre.anime.mtime" 
,
#include "puit_boss.anime.mtime" 
,
#include "squelette.anime.mtime" 
,
0
};


int8_t anime_database__filename_at_compile__lookup(const char * filename_sought) { 
  if (NULL == filename_sought) return -2; 
  if ('\0' == *filename_sought) return -3; 
  
  for (int i = 0; ; i++) { 
    const char * u = anime_database__filename_at_compile_time[i]; 
    if (NULL == u) return -1; 
    if (0 == strcmp(filename_sought, u)) return i; 
  }; 
  
}; 



static const char * anime_database__filename[ANIME_DATABASE__MAX] = { }; 
static const char * anime_database__filecontent[ANIME_DATABASE__MAX] = { }; 
static anime_t      anime_database__data[ANIME_DATABASE__MAX] = { }; 
static int8_t       anime_database__data_huh[ANIME_DATABASE__MAX] = { }; 
static time_t       anime_database__mtime[ANIME_DATABASE__MAX] = { }; 
static int8_t       anime_database__nb = 0; 


enum { anime_database__filename__buffer_bytesize = 1 << 10 }; 
ASSERT_COMPILE_TOPLEVEL(anime_database__filename__buffer_bytesize > 0); 
static char    anime_database__filename__buffer[anime_database__filename__buffer_bytesize]; 
static int16_t anime_database__filename__buffer_nb = 0; 

int8_t anime_database__filename__lookup(const char * filename_sought) { 
  if (NULL == filename_sought) return -2; 
  if ('\0' == *filename_sought) return -3; 
  
  for (int i = 0; i < anime_database__nb; i++) { 
    if (0 == strcmp(filename_sought, anime_database__filename[i])) return i; 
  }; 
  
  return -1; 
}; 

int16_t anime_database__filename_buffer__lookup(const char * filename_sought) { 
  if (NULL == filename_sought) return -2; 
  if ('\0' == *filename_sought) return -3; 
  
  const size_t a_len = strlen(filename_sought); 
  
  for (int i = 0; i < anime_database__filename__buffer_nb; ) { 
    const char * b = anime_database__filename__buffer + i; 
    const size_t b_len = strlen(b); 
    if (a_len != b_len) { 
      i += b_len + 1; 
      continue; 
    }; 
    if (0 == strcmp(filename_sought, b)) return i; 
    i += b_len + 1; 
    continue; 
  }; 
  
  return -1; 
}; 

int16_t anime_database__filename_buffer__push_no_lookup(const char * filename_sought) { 
  if (NULL == filename_sought) return -2; 
  if ('\0' == *filename_sought) return -3; 
  
  const int16_t a_len = strlen(filename_sought); 
  const int16_t available = anime_database__filename__buffer_bytesize - anime_database__filename__buffer_nb; 
  if (a_len > available) return -4; 
  
  const int16_t filename_buffer_id = anime_database__filename__buffer_nb; 
  strlcpy(anime_database__filename__buffer + filename_buffer_id, filename_sought, available); 
  
  anime_database__filename__buffer_nb += a_len + 1; 
  
  return filename_buffer_id; 
}; 

int8_t anime_database__filename__push_no_lookup(const char * filename) { 
  if (NULL == filename) return -2; 
  if ('\0' == *filename) return -3; 
  if (ANIME_DATABASE__MAX <= anime_database__nb) return -4; 
  
  int8_t id = anime_database__nb; 
  
  int16_t buffer_id; 
  buffer_id = anime_database__filename_buffer__lookup(filename); 
  if (0 <= buffer_id) { 
    anime_database__filename[id] = anime_database__filename__buffer + buffer_id; 
    anime_database__nb++; 
    return id; 
  }; 
  
  buffer_id = anime_database__filename_buffer__push_no_lookup(filename); 
  if (0 <= buffer_id) { 
    anime_database__filename[id] = anime_database__filename__buffer + buffer_id; 
    anime_database__nb++; 
    return id; 
  }; 
  
  return -1; 
}; 










enum { anime_database__filecontent__buffer_bytesize = 1 << 16 }; 
ASSERT_COMPILE_TOPLEVEL(anime_database__filecontent__buffer_bytesize > 0); 
static char    anime_database__filecontent__buffer[anime_database__filecontent__buffer_bytesize]; 
static int32_t anime_database__filecontent__buffer_nb = 0; 

int8_t anime_database__filecontent__lookup(const char * filecontent_sought) { 
  if (NULL == filecontent_sought) return -2; 
  if ('\0' == *filecontent_sought) return -3; 
  
  for (int i = 0; i < anime_database__nb; i++) { 
    if (0 == strcmp(filecontent_sought, anime_database__filecontent[i])) return i; 
  }; 
  
  return -1; 
}; 

int32_t anime_database__filecontent_buffer__lookup(const char * filecontent_sought) { 
  if (NULL == filecontent_sought) return -2; 
  if ('\0' == *filecontent_sought) return -3; 
  
  const size_t a_len = strlen(filecontent_sought); 
  
  for (int i = 0; i < anime_database__filecontent__buffer_nb; ) { 
    const char * b = anime_database__filecontent__buffer + i; 
    const size_t b_len = strlen(b); 
    if (a_len != b_len) { 
      i += b_len + 1; 
      continue; 
    }; 
    if (0 == strcmp(filecontent_sought, 0)) return i; 
  }; 
  
  return -1; 
}; 

int32_t anime_database__filecontent_buffer__push_no_lookup(const char * filecontent_sought) { 
  if (NULL == filecontent_sought) return -2; 
  if ('\0' == *filecontent_sought) return -3; 
  
  const int16_t a_len = strlen(filecontent_sought); 
  const int16_t available = anime_database__filecontent__buffer_bytesize - anime_database__filecontent__buffer_nb; 
  if (a_len > available) return -4; 
  
  const int32_t filecontent_buffer_id = anime_database__filecontent__buffer_nb; 
  strlcpy(anime_database__filecontent__buffer + filecontent_buffer_id, filecontent_sought, available); 
  
  anime_database__filecontent__buffer_nb += a_len + 1; 
  
  return filecontent_buffer_id; 
}; 









static int32_t anime_database__ReadDescriptionFile_into_buffer(const int anime_stdlog_d, const char * anime_datadir, const char * anime_filename, char * buffer, int32_t buffer_bytesize) { 
  int anime_file_d = -1; 
  int32_t read_bytesize = -1; 
  goto label__start; 

  assert(false); 

 label__error__exit_fail: { 
    if (0 <= anime_file_d) close(anime_file_d); 
    return -1; 
  }; 
  
 label__exit_success: { 
    if (0 <= anime_file_d) close(anime_file_d); 
    return read_bytesize; 
  }; 
  
  assert(false); 

label__start: { 
    // For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
    //char anime_fullpath[strlen(anime_datadir) + strlen(anime_filename) + 1];
    enum { anime_fullpath__bytesize = (1 << 10) }; 
    const size_t anime_fullpath__cstrlen = strlen(anime_datadir) + strlen(anime_filename); 
    assert(anime_fullpath__bytesize > anime_fullpath__cstrlen); 
    char anime_fullpath[anime_fullpath__bytesize]; 
    strcat(strcpy(anime_fullpath, anime_datadir), anime_filename); 
    dprintf(fileno(stdout), "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: INFO: " "Chargement d'un anime décrit par le fichier: %s" "\n", __func__, anime_fullpath); 
    
#define LOG_SUFF ".log"
    // For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
    //char anime_log[strlen(LOGDIR) + strlen(anime_filename) + strlen(LOG_SUFF) + 1];
    enum { anime_log__bytesize = (1 << 10) }; 
    const size_t anime_log__cstrlen = strlen(LOGDIR) + strlen(anime_filename) + strlen(LOG_SUFF); 
    assert(anime_log__bytesize > anime_log__cstrlen); 
    char anime_log[anime_log__bytesize];
    strcat(strcat(strcpy(anime_log, LOGDIR), anime_filename), LOG_SUFF);
    dprintf(fileno(stdout), "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: INFO: " "Fichier log de l'analyse de ce fichier anime: %s" "\n", __func__, anime_log); 
    fflush(NULL); 

  label__anime_file__open: { 
      anime_file_d = -1; 
      for (;;) { 
	anime_file_d = open(anime_fullpath, O_RDONLY); 
	if (0 <= anime_file_d) break; 
	messerr("ERREUR: Le fichier de description de l'objet animé n'a pas pu être ouvert: '%s'" "\n", anime_fullpath); 
	messerr("        Voulez-vous réessayer?" "\n"); 
	{ 
	  char c; 
	  const int nb_read = read(stdin_d, &c, 1); 
	  if (0 == nb_read) { continue; }; 
	  if (c == 'n') { goto label__error__exit_fail; }; 
	  continue; 
	}; 
	goto label__error__exit_fail; 
      }; 
    }; 
    
  label__anime_file__read: { 
      read_bytesize = read(anime_file_d, buffer, buffer_bytesize); 
      if (-1 == read_bytesize) goto label__error__exit_fail; 
      if ( 0 == read_bytesize) goto label__error__exit_fail; 
      char c; 
      const ssize_t status = read(anime_file_d, &c, 1); 
      if (-1 == status) goto label__error__exit_fail; 
      if ( 0 <  status) goto label__error__exit_fail; 
      if ( 0 == status) goto label__exit_success; 
      /* NOT REACHED */ 
      assert(false); 
    }; 
    
  }; 

}; 



static int anime_database__ParseDescriptionFile(const char * anime_datadir, const char * anime_filename, anime_t * anime_data) { 
  int     anime_stdlog_d = -1; 
  int     anime_file_d   = -1; 
  goto label__start; 

  assert(false); 

 label__error__exit_fail: { 
    if (0 <= anime_stdlog_d) close(anime_stdlog_d); 
    if (0 <= anime_file_d) close(anime_file_d); 
    return -1; 
  }; 
  
  assert(false); 

label__start: {}; 
  { 
    // For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
    //char anime_fullpath[strlen(anime_datadir) + strlen(anime_filename) + 1];
    enum { anime_fullpath__bytesize = (1 << 10) }; 
    const size_t anime_fullpath__cstrlen = strlen(anime_datadir) + strlen(anime_filename); 
    assert(anime_fullpath__bytesize > anime_fullpath__cstrlen); 
    char anime_fullpath[anime_fullpath__bytesize]; 
    strcat(strcpy(anime_fullpath, anime_datadir), anime_filename); 
    dprintf(fileno(stdout), "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: INFO: " "Chargement d'un anime décrit par le fichier: %s" "\n", __func__, anime_fullpath); 
    
#define LOG_SUFF ".log"
    // For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
    //char anime_log[strlen(LOGDIR) + strlen(anime_filename) + strlen(LOG_SUFF) + 1];
    enum { anime_log__bytesize = (1 << 10) }; 
    const size_t anime_log__cstrlen = strlen(LOGDIR) + strlen(anime_filename) + strlen(LOG_SUFF); 
    assert(anime_log__bytesize > anime_log__cstrlen); 
    char anime_log[anime_log__bytesize];
    strcat(strcat(strcpy(anime_log, LOGDIR), anime_filename), LOG_SUFF);
    dprintf(fileno(stdout), "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: INFO: " "Fichier log de l'analyse de ce fichier anime: %s" "\n", __func__, anime_log); 
    fflush(NULL); 

  label__anime_both_file_and_log__open: 
    
  label__anime_log__open: { 
      anime_stdlog_d = -1; 
      for (;;) { 
#if 1 
	static char anime_stdlog_buffer[INT16_MAX] = {}; 
	FILE * anime_stdlog_stream = fopen(anime_log, "wb"); 
	if (NULL != anime_stdlog_stream) { 
	  anime_stdlog_d = fileno(anime_stdlog_stream); 
	  setvbuf(anime_stdlog_stream, anime_stdlog_buffer, _IOFBF, sizeof(anime_stdlog_buffer)); 
	}; 
	// RL: TODO FIXME XXX: The FILE* stream is not closed. 
#else 
	anime_stdlog_d = open(anime_log, O_WRONLY | O_CREAT | O_TRUNC, (mode_t)0666); 
#endif 
	if (0 <= anime_stdlog_d) break; 
	messerr("ERREUR: Le fichier pour écrire le log de l'analyse de la description de l'objet animé n'a pas pu être ouvert: '%s'" "\n", anime_log); 
	messerr("        Voulez-vous réessayer?" "\n"); 
	{
	  char c; 
	  const int nb_read = read(stdin_d, &c, 1); 
	  if (0 == nb_read) { continue; }; 
	  if (c == 'n') { goto label__error__exit_fail; }; 
	  continue; 
	}; 
	goto label__error__exit_fail; 
      }; 
    }; 
    
  label__anime_file__open: { 
      anime_file_d = -1; 
      for (;;) { 
	anime_file_d = open(anime_fullpath, O_RDONLY); 
	if (0 <= anime_file_d) break; 
	messerr("ERREUR: Le fichier de description de l'objet animé n'a pas pu être ouvert: '%s'" "\n", anime_fullpath); 
	messerr("        Voulez-vous réessayer?" "\n"); 
	{
	  char c; 
	  const int nb_read = read(stdin_d, &c, 1); 
	  if (0 == nb_read) { continue; }; 
	  if (c == 'n') { goto label__error__exit_fail; }; 
	  continue; 
	}; 
	goto label__error__exit_fail; 
      }; 
    }; 
      
    fflush(NULL); 
    anime__make_r(anime_data, anime_stdlog_d); 
    fflush(NULL); 

    for(;;) { 
      // int_anime_error_t anime__fill_from_buffer(anime_t * this, const char * input_name, const char * buffer, const int16_t buffer_bytesize, const int stduser_d) { 
      const int_anime_error_t anime_error_id = anime__fill_from_file(anime_data, anime_filename, anime_file_d, anime_stdlog_d); 
      if (ANIME__OK == anime_error_id) break; 
      if (0 < anime_error_id) { 
	dprintf(fileno(stdout), "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: WARNING: %s: %s" "\n", __func__, anime_filename, int_anime_error__get_cstr(anime_error_id)); 
	break; 
      }; 
      { 
	messerr("ERREUR: Le fichier de description de l'objet animé n'a pas pu être lu et/ou analysé: '%s'" "\n", anime_fullpath); 
	messerr("        ERROR_ID: %s" "\n", int_anime_error__get_cstr(anime_error_id)); 
	messerr("        ERROR_DESC: %s" "\n", anime_data -> error_str); 
	messerr("        Pour plus d'informations, veuillez vous reporter au compte-rendu rendant compte de cette tentative échouée: '%s'" "\n", anime_log); 
	messerr("        Voulez-vous réessayer? (o/n)" "\n"); 
	{
	  char c; 
	  for (;;) { 
	    const ssize_t nb_read = read(stdin_d, &c, 1); 
	    if (0 == nb_read) { continue; }; 
	    if (-1 == nb_read) goto label__error__exit_fail; 
	    break; 
	  }; 
	  if (c == 'n') { goto label__error__exit_fail; }; 
	  close(anime_file_d); anime_file_d = -1; 
	  close(anime_stdlog_d); anime_stdlog_d = -1; 
	  goto label__anime_both_file_and_log__open; 
	};
	assert(false); 
      }; 
      assert(false); 
    }; 
    
    // Success 
    fflush(NULL); 
    anime__print_d(anime_data, anime_stdlog_d); 
    fflush(NULL); 
 
    // Closing files. 
    close(anime_file_d); anime_file_d = -1; 
    close(anime_stdlog_d); anime_stdlog_d = -1; 
  }; 
  
  
  return 0; 
}; 



static int anime_database__ParseDescriptionBuffer(const char * anime_filename, const char * buffer, const uint16_t buffer_bytesize, anime_t * anime_data) { 
  int     anime_stdlog_d = -1; 
  goto label__start; 

  assert(false); 

 label__error__exit_fail: { 
    if (0 <= anime_stdlog_d) close(anime_stdlog_d); 
    return -1; 
  }; 
  
 label__exit_success: { 
    if (0 <= anime_stdlog_d) close(anime_stdlog_d); 
    return 0; 
  }; 
  
 label__start: { 
#define LOG_SUFF ".log"
    // For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
    //char anime_log[strlen(LOGDIR) + strlen(anime_filename) + strlen(LOG_SUFF) + 1];
    enum { anime_log__bytesize = (1 << 10) }; 
    const size_t anime_log__cstrlen = strlen(LOGDIR) + strlen(anime_filename) + strlen(LOG_SUFF); 
    assert(anime_log__bytesize > anime_log__cstrlen); 
    char anime_log[anime_log__bytesize];
    strcat(strcat(strcpy(anime_log, LOGDIR), anime_filename), LOG_SUFF);
    dprintf(fileno(stdout), "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: INFO: " "Fichier log de l'analyse de ce fichier anime: %s" "\n", __func__, anime_log); 
    fflush(NULL); 

  label__anime_log__open: { 
      anime_stdlog_d = -1; 
      for (;;) { 
#if 1 
	static char anime_stdlog_buffer[INT16_MAX] = {}; 
	FILE * anime_stdlog_stream = fopen(anime_log, "wb"); 
	if (NULL != anime_stdlog_stream) { 
	  anime_stdlog_d = fileno(anime_stdlog_stream); 
	  setvbuf(anime_stdlog_stream, anime_stdlog_buffer, _IOFBF, sizeof(anime_stdlog_buffer)); 
	}; 
	// RL: TODO FIXME XXX: The FILE* stream is not closed. 	
#else 
	anime_stdlog_d = open(anime_log, O_WRONLY | O_CREAT | O_TRUNC, (mode_t)0666); 
#endif 
	if (0 <= anime_stdlog_d) break; 
	messerr("ERREUR: Le fichier pour écrire le log de l'analyse de la description de l'objet animé n'a pas pu être ouvert: '%s'" "\n", anime_log); 
	messerr("        Voulez-vous réessayer?" "\n"); 
	{
	  char c; 
	  const int nb_read = read(stdin_d, &c, 1); 
	  if (0 == nb_read) { continue; }; 
	  if (c == 'n') { goto label__error__exit_fail; }; 
	  continue; 
	}; 
	goto label__error__exit_fail; 
      }; 
    }; 
    
    fflush(NULL); 
    anime__make_r(anime_data, anime_stdlog_d); 
    fflush(NULL); 

    for(;;) { 
      //const int_anime_error_t anime_error_id = anime__fill_from_file  (anime_data, anime_filename, anime_file_d, anime_stdlog_d); 
      const int_anime_error_t anime_error_id = anime__fill_from_buffer(anime_data, anime_filename, buffer, buffer_bytesize, anime_stdlog_d); 
      if (ANIME__OK == anime_error_id) break; 
      if (0 < anime_error_id) { 
	dprintf(fileno(stdout), "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: WARNING: %s: %s" "\n", __func__, anime_filename, int_anime_error__get_cstr(anime_error_id)); 
	break; 
      }; 
      assert(0 > anime_error_id); { 
	messerr("ERREUR: Le fichier de description de l'objet animé n'a pas pu être lu et/ou analysé: '%s'" "\n", anime_filename); 
	messerr("        ERROR_ID: %s" "\n", int_anime_error__get_cstr(anime_error_id)); 
	messerr("        ERROR_DESC: %s" "\n", anime_data -> error_str); 
	messerr("        Pour plus d'informations, veuillez vous reporter au compte-rendu rendant compte de cette tentative échouée: '%s'" "\n", anime_log); 
	goto label__error__exit_fail; 
      }; 
    }; 
    
    // Success 
    fflush(NULL); 
    anime__print_d(anime_data, anime_stdlog_d); 
    fflush(NULL); 

    goto label__exit_success; 
  }; 
  
}; 



const anime_t * anime_database__get(const char * filename) { 
  int16_t id; 
  goto label__start; 

  label__error__could_not_push_filename: { 
    return NULL; 
  }; 
  
  label__error__could_not_parse_anime_data_file: { 
    return NULL; 
  }; 
  
  label__error__could_not_read_anime_data_file: { 
    return NULL; 
  }; 
  
 label__start: { 
    id = anime_database__filename__lookup(filename); 
    if (0 <= id) goto label__id_found; 
    id = anime_database__filename__push_no_lookup(filename); 
    if (0 <= id) goto label__id_found; 
    goto label__error__could_not_push_filename;
  };  
  
 label__id_found: {
    if (NULL != anime_database__filecontent[id]) goto label__got_content; 
    char *        buffer          = anime_database__filecontent__buffer          + anime_database__filecontent__buffer_nb; 
    const int32_t buffer_bytesize = anime_database__filecontent__buffer_bytesize - anime_database__filecontent__buffer_nb; 
    const int32_t buffer_nb       = anime_database__ReadDescriptionFile_into_buffer(0, ANIMESDIR, filename,  buffer, buffer_bytesize); 
    if (buffer_nb <= 0) goto label__error__could_not_read_anime_data_file; 
    const int32_t old_id = anime_database__filecontent_buffer__lookup(buffer); 
    if (old_id >= 0) { 
      anime_database__filecontent[id] = anime_database__filecontent__buffer + old_id; 
      goto label__got_content; 
    } 
    else { 
      anime_database__filecontent__buffer_nb += buffer_nb; 
      anime_database__filecontent[id] = buffer; 
      goto label__got_content; 
    }; 
  }; 
  
 label__got_content: { 
    if (anime_database__data_huh[id]) goto label__got_data; 
    anime_database__data_huh[id] = (0 == anime_database__ParseDescriptionBuffer(filename, anime_database__filecontent[id], strlen(anime_database__filecontent[id]), &anime_database__data[id])); 
    if (anime_database__data_huh[id]) goto label__got_data; 
    goto label__error__could_not_parse_anime_data_file; 
  }; 
  
 label__got_data: { 
    return &(anime_database__data[id]); 
  }; 
  
}; 


const anime_t * anime_database__load__compile_time(const char * filename) { 
  int8_t id_at_c; 
  int16_t id; 
  goto label__start; 

  label__error__could_not_push_filename: { 
    return NULL; 
  }; 
  
  label__error__could_not_parse_anime_data_file: { 
    return NULL; 
  }; 
  
  label__error__could_not_read_anime_data_file: { 
    return NULL; 
  }; 
  
 label__error__not_in_compile_time_database: {
    return NULL;
  }; 
  
 label__error_already_in_database: { 
    return NULL;
  }; 
  
 label__start: { 
    id_at_c = anime_database__filename_at_compile__lookup(filename); 
    if (0 > id_at_c) goto label__error__not_in_compile_time_database; 
    
    id = anime_database__filename__lookup(filename); 
    if (0 <= id) goto label__error_already_in_database; 
    
    id = anime_database__filename__push_no_lookup(filename); 
    if (0 <= id) goto label__id_found; 
    goto label__error__could_not_push_filename; 
  };  
  
 label__id_found: { 
    anime_database__filecontent[id] = anime_database__filecontent_at_compile_time[id_at_c]; 
    goto label__got_content; 
  }; 
  
 label__got_content: { 
    anime_database__data_huh[id] = (0 == anime_database__ParseDescriptionBuffer(filename, anime_database__filecontent[id], strlen(anime_database__filecontent[id]), &anime_database__data[id])); 
    if (anime_database__data_huh[id]) goto label__got_data; 
    goto label__error__could_not_parse_anime_data_file; 
  }; 
  
 label__got_data: { 
    return &(anime_database__data[id]); 
  }; 
  
}; 
