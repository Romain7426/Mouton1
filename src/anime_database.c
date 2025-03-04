#include "global.h"
#include <anime.h>
#include "anime_database.h"
#include <time.h>


//static const char * anime_database_at_compile_time__filename[ANIME_DATABASE_AT_COMPILE_TIME__MAX];
//static const char * anime_database_at_compile_time__filecontent[ANIME_DATABASE_AT_COMPILE_TIME__MAX];
//static const time_t anime_database_at_compile_time__mtime[ANIME_DATABASE_AT_COMPILE_TIME__MAX];
//static int8_t anime_database_at_compile_time__lookup_by_filename(const char * filename_sought);
#include "anime_database_at_compile_time.ci"








enum { ANIME_DATABASE_AT_RUNTIME__MAX = 32 }; 
static const char * anime_database_at_runtime__filename   [ANIME_DATABASE_AT_RUNTIME__MAX] = { }; 
static const char * anime_database_at_runtime__filecontent[ANIME_DATABASE_AT_RUNTIME__MAX] = { }; 
static time_t       anime_database_at_runtime__mtime      [ANIME_DATABASE_AT_RUNTIME__MAX] = { }; 
//static anime_t      anime_database_at_runtime__data       [ANIME_DATABASE_AT_RUNTIME__MAX] = { }; 
static char         anime_database_at_runtime__data_buffer[ANIME_BYTESIZE]       [ANIME_DATABASE_AT_RUNTIME__MAX] = { }; 
static anime_t *    anime_database_at_runtime__data       [ANIME_DATABASE_AT_RUNTIME__MAX] = { }; 
static bool_t       anime_database_at_runtime__init_huh = false; 
static int8_t       anime_database_at_runtime__data_huh   [ANIME_DATABASE_AT_RUNTIME__MAX] = { }; 
static int8_t       anime_database_at_runtime__nb = 0; 

enum { anime_database_at_runtime__filename_buffer_bytesize = 1 << 10 }; 
ASSERT_COMPILE__TOPLEVEL(anime_database_at_runtime__filename_buffer_bytesize > 0); 
static char    anime_database_at_runtime__filename_buffer[anime_database_at_runtime__filename_buffer_bytesize]; 
static int16_t anime_database_at_runtime__filename_buffer_nb = 0; 

enum { anime_database_at_runtime__filecontent_buffer_bytesize = 1 << 16 }; 
ASSERT_COMPILE__TOPLEVEL(anime_database_at_runtime__filecontent_buffer_bytesize > 0); 
static char    anime_database_at_runtime__filecontent_buffer[anime_database_at_runtime__filecontent_buffer_bytesize]; 
static int32_t anime_database_at_runtime__filecontent_buffer_nb = 0; 


static void anime_database_at_runtime__anime_data__init(void) { 
  if (anime_database_at_runtime__init_huh) return;
  anime_database_at_runtime__nb = 0; 
  for (int8_t i = 0; i < ANIME_DATABASE_AT_RUNTIME__MAX; i++) {
    anime_database_at_runtime__data    [i] = (anime_t *)(((char *)anime_database_at_runtime__data_buffer) + i*ANIME_BYTESIZE);
#if 0
      fprintf(stderr, "anime_database_at_runtime__data[i] = %p" "\n", anime_database_at_runtime__data[i]);
#endif 

    anime_database_at_runtime__data_huh[i] = false;
    anime_database_at_runtime__filename[i] = NULL;
    anime_database_at_runtime__filecontent[i] = NULL;
  }; 
  anime_database_at_runtime__filename_buffer[0] = '\0';
  anime_database_at_runtime__filename_buffer_nb = 1; 
  anime_database_at_runtime__filecontent_buffer[0] = '\0';
  anime_database_at_runtime__filecontent_buffer_nb = 1; 
  anime_database_at_runtime__init_huh = true;
};


// FILENAME_STRING_STACK

int16_t anime_database_at_runtime__filename_buffer__lookup(const char * filename_sought) { 
  if (NULL ==  filename_sought) return -2; 
  if ('\0' == *filename_sought) return -3; 
  
  const size_t a_len = strlen(filename_sought); 
  
  for (int i = 0; i < anime_database_at_runtime__filename_buffer_nb; ) { 
    const char * b = anime_database_at_runtime__filename_buffer + i; 
    const size_t b_len = strlen(b); 
    if (a_len != b_len) { i += b_len + 1; continue; }; 
    if (0 == strcmp(filename_sought, b)) return i; 
    i += b_len + 1; 
    continue; 
  }; 
  
  return -1; 
}; 

int16_t anime_database_at_runtime__filename_buffer__push_no_lookup(const char * filename_sought) { 
  if (NULL ==  filename_sought) return -2; 
  if ('\0' == *filename_sought) return -3; 
  
  const int16_t a_len = strlen(filename_sought); 
  const int16_t available = anime_database_at_runtime__filename_buffer_bytesize - anime_database_at_runtime__filename_buffer_nb; 
  if (a_len + 1 > available) return -4; 
  
  const int16_t filename_buffer_id = anime_database_at_runtime__filename_buffer_nb; 
  strlcpy(anime_database_at_runtime__filename_buffer + filename_buffer_id, filename_sought, available); 
  
  anime_database_at_runtime__filename_buffer_nb += a_len + 1; 
  
  return filename_buffer_id; 
}; 


// FILENAME_STACK

int8_t anime_database_at_runtime__filename__lookup(const char * filename_sought) { 
  if (NULL ==  filename_sought) return -2; 
  if ('\0' == *filename_sought) return -3; 
  for (int i = 0; i < anime_database_at_runtime__nb; i++) { 
    if (0 == strcmp(filename_sought, anime_database_at_runtime__filename[i])) return i; 
  }; 
  return -1; 
}; 

int8_t anime_database_at_runtime__filename__push_no_lookup(const char * filename) { 
  if (NULL ==  filename) return -2; 
  if ('\0' == *filename) return -3; 
  if (ANIME_DATABASE_AT_RUNTIME__MAX <= anime_database_at_runtime__nb) return -4; 
  
  int8_t db_id = anime_database_at_runtime__nb; 
  
  int16_t buffer_id; 
#if 0
  buffer_id = anime_database_at_runtime__filename_buffer__lookup(filename); 
  if (0 > buffer_id) { 
    buffer_id = anime_database_at_runtime__filename_buffer__push_no_lookup(filename); 
    if (0 > buffer_id) return -1; 
  }; 
#else
  buffer_id = anime_database_at_runtime__filename_buffer__push_no_lookup(filename); 
  if (0 > buffer_id) return -1; 
#endif
  
  anime_database_at_runtime__filename[db_id] = anime_database_at_runtime__filename_buffer + buffer_id; 
  anime_database_at_runtime__nb++; 
  return db_id; 
}; 




// FILENAME_CONTENT_STACK

int8_t anime_database_at_runtime__filecontent__lookup(const char * filecontent_sought) { 
  if (NULL ==  filecontent_sought) return -2; 
  if ('\0' == *filecontent_sought) return -3; 
  for (int i = 0; i < anime_database_at_runtime__nb; i++) { 
    if (0 == strcmp(filecontent_sought, anime_database_at_runtime__filecontent[i])) return i; 
  }; 
  return -1; 
}; 

int32_t anime_database_at_runtime__filecontent_buffer__lookup(const char * filecontent_sought) { 
  if (NULL ==  filecontent_sought) return -2; 
  if ('\0' == *filecontent_sought) return -3; 
  
  const size_t a_len = strlen(filecontent_sought); 
  
  for (int i = 0; i < anime_database_at_runtime__filecontent_buffer_nb; ) { 
    const char * b = anime_database_at_runtime__filecontent_buffer + i; 
    const size_t b_len = strlen(b); 
    if (a_len != b_len) { i += b_len + 1; continue; }; 
    if (0 == strcmp(filecontent_sought, 0)) return i; 
    i += b_len + 1; 
    continue; 
  }; 
  
  return -1; 
}; 

int32_t anime_database_at_runtime__filecontent_buffer__push_no_lookup(const char * filecontent_sought) { 
  if (NULL ==  filecontent_sought) return -2; 
  if ('\0' == *filecontent_sought) return -3; 
  
  const int16_t a_len = strlen(filecontent_sought); 
  const int16_t available = anime_database_at_runtime__filecontent_buffer_bytesize - anime_database_at_runtime__filecontent_buffer_nb; 
  if (a_len + 1 > available) return -4; 
  
  const int32_t filecontent_buffer_id = anime_database_at_runtime__filecontent_buffer_nb; 
  strlcpy(anime_database_at_runtime__filecontent_buffer + filecontent_buffer_id, filecontent_sought, available); 
  
  anime_database_at_runtime__filecontent_buffer_nb += a_len + 1; 
  
  return filecontent_buffer_id; 
}; 






// XXXXX_STACK


static int anime_database__compute_fullpath_into_buffer(const char * anime_datadir, const char * anime_filename, char * buffer, int32_t buffer_bytesize) { 
  const size_t anime_filename_len = strlen(anime_filename); 
  const size_t anime_datadir_len = strlen(anime_datadir); 
  const int    anime_datadir__slash_required_huh = ('/' != *(anime_datadir + anime_datadir_len - 1)); 
  const size_t anime_fullpath__cstrlen = anime_datadir_len + (anime_datadir__slash_required_huh?1:0) + anime_filename_len; 
  char * anime_fullpath = buffer; 
  if (buffer_bytesize < (int32_t) anime_fullpath__cstrlen) return -1; 
  strcpy(anime_fullpath, anime_datadir); 
  if (anime_datadir__slash_required_huh) strcat(anime_fullpath, "/"); 
  strcat(anime_fullpath, anime_filename); 
  return 1+anime_fullpath__cstrlen; 
}; 


static int32_t anime_database__read_filecontent_from_disk_into_buffer(const char * anime_fullpath, char * buffer, int32_t buffer_bytesize) { 
  const int anime_file_d = open(anime_fullpath, O_RDONLY); 
  if (0 > anime_file_d) return -1; 
  const ssize_t read_bytesize = read(anime_file_d, buffer, buffer_bytesize); 
  close(anime_file_d); 
  if (read_bytesize <= 0) return read_bytesize; 
  if (read_bytesize >= buffer_bytesize) return -2; 
  buffer[read_bytesize] = '\0'; 
  return (int32_t)(1+read_bytesize); 
}; 





static int anime_database__parse_from_buffer(const char * anime_filename, const char * buffer, const uint16_t buffer_bytesize, anime_t * anime_data) { 
  enum { anime_stdlog__bytesize = (1 << 10) }; 
  char   anime_stdlog[anime_stdlog__bytesize]; 
  int    anime_stdlog_d = -1; 
  enum { anime_stdlog__buffer_bytesize = INT16_MAX }; 
  char   anime_stdlog__buffer[anime_stdlog__buffer_bytesize]; 
  goto label__body; 

  assert(false); 

 label__error__exit_fail: { 
    //if (0 <= anime_stdlog_d) close(anime_stdlog_d); 
    return -1; 
  }; 
  
 label__exit_success: { 
    //if (0 <= anime_stdlog_d) close(anime_stdlog_d); 
    return 0; 
  }; 
  
 label__body: { 
#define LOG_SUFF ".log"
    // For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
    const size_t anime_filename_len = strlen(anime_filename); 
    const size_t anime_logdir_len = strlen(LOGDIR); 
    const int    anime_logdir__slash_required_huh = ('/' != *((*(&LOGDIR)) + anime_logdir_len - 1)); 
    const size_t anime_logsuffix_len = strlen(LOG_SUFF); 
    const size_t anime_stdlog__cstrlen = anime_logdir_len + (anime_logdir__slash_required_huh?1:0) + anime_filename_len + anime_logsuffix_len; 
    assert(anime_stdlog__bytesize > anime_stdlog__cstrlen); 
    strcpy(anime_stdlog, LOGDIR); 
    if (anime_logdir__slash_required_huh) strcat(anime_stdlog, "/"); 
    strcat(anime_stdlog, anime_filename); 
    strcat(anime_stdlog, LOG_SUFF);
    //if (anime_stdlog_d > 0) { dprintf(anime_stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: INFO: " "Fichier log de l'analyse de ce fichier anime: %s" "\n", __func__, anime_log); }; 
    //fflush(NULL); 
    
#if 0
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 

    const int anime_stdlog_write_fd = open(anime_stdlog, O_WRONLY | O_CREAT | O_TRUNC, (mode_t)0600); 
    if (0 > anime_stdlog_write_fd) return -1; 
    
#if 0
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
    anime_stdlog_d = buffered_outstream__open(anime_stdlog_write_fd, anime_stdlog__buffer, anime_stdlog__buffer_bytesize); 
    if (0 > anime_stdlog_d) { close(anime_stdlog_write_fd); return -2; }; 
    
#if 0
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
    dputs_array(anime_stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<", __func__, "()>}: INFO: " "-- Ouverture --" "\n"); 
    buffered_outstream__flush(anime_stdlog_d); 
    
#if 0
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
    //anime__make_r(anime_data, -1); 
    anime__make_r(anime_data, anime_stdlog_d); 

#if 0
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 

    for(;;) { 
#if 0
      int len = 0;
      { const char * p = buffer; for (;;) { if (*p == '\0') break; p++; len++; }; };
      fprintf(stderr, "buffer_bytesize = %d" "\n", buffer_bytesize); 
      fprintf(stderr, "strlen(buffer) = %d" "\n", strlen(buffer)); 
      fprintf(stderr, "len-p = %d" "\n", len); 
      //fprintf(stderr, "buffer = %s" "\n", buffer); 
      fprintf(stderr, "HERE-----------------------" "\n");
      return -1; 
#endif 
#if 0
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
      fprintf(stderr, "strlen(buffer) = %d" "\n", strlen(buffer)); 
#endif 
      //const int_anime_error_t anime_error_id = anime__fill_from_file  (anime_data, anime_filename, anime_file_d, anime_stdlog_d); 
      //const int_anime_error_t anime_error_id = anime__fill_from_buffer(anime_data, anime_filename, buffer, buffer_bytesize, -1); 
      //const int_anime_error_t anime_error_id = anime__fill_from_buffer(anime_data, anime_filename, buffer, buffer_bytesize, anime_stdlog_d); 
      
      // Cette fonction d'analyse passe son temps à écrire les lexèmes dans le fichier log. 
      // Donc, si il n'y a pas d'erreur, le fichier de log ne sera pas écrit.
      int_anime_error_t anime_error_id;
      { 
	anime__stdlog_d__set(anime_data, -1); 
	anime_error_id = anime__fill_from_buffer(anime_data, anime_filename, buffer, strlen(buffer), anime_stdlog_d); 
	anime__stdlog_d__set(anime_data, anime_stdlog_d); 
      };
      if (0 > anime_error_id) {
	anime_error_id = anime__fill_from_buffer(anime_data, anime_filename, buffer, strlen(buffer), anime_stdlog_d); 
      }; 
#if 0
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
#if 0
      fprintf(stderr, "anime_error_id = %s" "\n", int_anime_error__get_cstr(anime_error_id)); 
      fprintf(stderr, "strlen(buffer) = %d" "\n", strlen(buffer)); 
#endif 


      if (ANIME__OK == anime_error_id) break; 
      if (0 < anime_error_id) { 
	dprintf(fileno(stdout), "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: WARNING: %s: %s" "\n", __func__, anime_filename, int_anime_error__get_cstr(anime_error_id)); 
	break; 
      }; 
      assert(0 > anime_error_id); { 
	messerr("ERREUR: Le fichier de description de l'objet animé n'a pas pu être lu et/ou analysé: '%s'" "\n", anime_filename); 
	messerr("        ERROR_ID: %s" "\n", int_anime_error__get_cstr(anime_error_id)); 
	messerr("        ERROR_DESC: %s" "\n", anime__error_cstr_get(anime_data)); 
	messerr("        Pour plus d'informations, veuillez vous reporter au compte-rendu rendant compte de cette tentative échouée: '%s'" "\n", anime_stdlog); 
	buffered_outstream__close(anime_stdlog_d,/*flush_huh*/true); 
	close(anime_stdlog_write_fd); 
	goto label__error__exit_fail; 
      }; 
    }; 
    
    // Success 
    fflush(NULL); 
    anime__print_d(anime_data, anime_stdlog_d); 
    fflush(NULL); 
    
    buffered_outstream__close(anime_stdlog_d,/*flush_huh*/true); 
    close(anime_stdlog_write_fd); 
    
    goto label__exit_success; 
  }; 
  
}; 













static time_t anime_database__mtime_disk(const char * filename) { 
  struct stat sb; 
  if (0 != stat(filename, &sb)) return -1; 
  const time_t mtime_sec = sb.st_mtim.tv_sec; 
  return mtime_sec;
}; 


const anime_t * anime_database__get(const char * filename) { 
  anime_database_at_runtime__anime_data__init();
  int8_t  id_at_c; 
  int16_t id_at_r; 
  time_t disk_mtime;
  enum { anime_fullpath__bytesize = (1 << 10) }; 
  char anime_fullpath[anime_fullpath__bytesize]; 

#if 0
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  goto label__body; 

  label__error__could_not_push_filename: { 
    return NULL; 
  }; 
  
  label__error__could_not_parse_anime_data_file: { 
    return NULL; 
  }; 
  
  label__error__could_not_read_anime_data_file: { 
    return NULL; 
  }; 

 label__error__no_content_anywhere: { 
    return NULL; 
  }; 
  
 label__error__could_not_compute_fullpath: { 
    return NULL; 
  }; 
  
 label__body: { 
    if (NULL ==  filename) return NULL; 
    if ('\0' == *filename) return NULL; 
    
#if 0
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
    id_at_r = anime_database_at_runtime__filename__lookup(filename); 
#if 1
    if (0 <= id_at_r) goto label__id_found; 
#endif

    id_at_r = anime_database_at_runtime__filename__push_no_lookup(filename); 
#if 1
    if (0 <= id_at_r) goto label__id_found; 
#endif 
    
    goto label__error__could_not_push_filename; 
  };  

    
    


 label__id_found: { 
    const int buffer_used = anime_database__compute_fullpath_into_buffer(ANIMESDIR, filename, anime_fullpath, anime_fullpath__bytesize); 
    if (buffer_used <= 0) goto label__error__could_not_compute_fullpath; 
    
    if (NULL != anime_database_at_runtime__filecontent[id_at_r]) goto label__got_content; 
    
    goto label__load_content_from_compile_time; 
  }; 

 label__load_content_from_compile_time: { 
    const int8_t id_at_c = anime_database_at_compile_time__lookup_by_filename(filename); 

    if (0 > id_at_c) {
      disk_mtime = anime_database__mtime_disk(anime_fullpath); 
      if (-1 == disk_mtime) goto label__error__no_content_anywhere; 
      goto label__load_content_from_disk; 
    };

    
    {
      anime_database_at_runtime__filecontent[id_at_r] = anime_database_at_compile_time__filecontent[id_at_c]; 
      anime_database_at_runtime__data_huh[id_at_r] = false; 
      anime_database_at_runtime__mtime[id_at_r] = anime_database_at_compile_time__mtime[id_at_c]; 
      goto label__got_content; 
    }; 

  }; 
  
 label__load_content_from_disk: { 
    assert(-1 != disk_mtime); 
    char *        buffer          = anime_database_at_runtime__filecontent_buffer          + anime_database_at_runtime__filecontent_buffer_nb; 
    const int32_t buffer_bytesize = anime_database_at_runtime__filecontent_buffer_bytesize - anime_database_at_runtime__filecontent_buffer_nb; 
    const int32_t buffer_nb       = anime_database__read_filecontent_from_disk_into_buffer(anime_fullpath, buffer, buffer_bytesize); 
    if (buffer_nb <= 0) goto label__error__could_not_read_anime_data_file; 
    const int32_t existing_id     = anime_database_at_runtime__filecontent_buffer__lookup(buffer); 
    if (existing_id >= 0) { 
      anime_database_at_runtime__filecontent[id_at_r] = anime_database_at_runtime__filecontent_buffer + existing_id; 
    } 
    else { 
      anime_database_at_runtime__filecontent_buffer_nb += buffer_nb; 
      anime_database_at_runtime__filecontent[id_at_r] = buffer; 
    }; 
    anime_database_at_runtime__data_huh[id_at_r] = false; 
    anime_database_at_runtime__mtime[id_at_r] = disk_mtime; 
    goto label__got_fresh_content; 
  }; 
  
 label__got_content: { 
    disk_mtime = anime_database__mtime_disk(anime_fullpath); 
    if (-1 != disk_mtime) { 
      if (disk_mtime > anime_database_at_runtime__mtime[id_at_r]) goto label__load_content_from_disk; 
    }; 
    goto label__got_fresh_content; 
  }; 
  
 label__got_fresh_content: { 
#if 0
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 

    if (anime_database_at_runtime__data_huh[id_at_r]) goto label__got_data; 
#if 0
      fprintf(stderr, "strlen(anime_database_at_runtime__filecontent[id_at_r]) = %d" "\n", strlen(anime_database_at_runtime__filecontent[id_at_r])); 
      //fprintf(stderr, "buffer = %s" "\n", buffer); 
#endif 

    const int parse_error = anime_database__parse_from_buffer(filename, anime_database_at_runtime__filecontent[id_at_r], 1+strlen(anime_database_at_runtime__filecontent[id_at_r]), anime_database_at_runtime__data[id_at_r]); 
    anime_database_at_runtime__data_huh[id_at_r] = (0 == parse_error); 
    if (anime_database_at_runtime__data_huh[id_at_r]) goto label__got_data; 
    goto label__error__could_not_parse_anime_data_file; 
  }; 
  
 label__got_data: { 
    return anime_database_at_runtime__data[id_at_r]; 
  };   
  
}; 
















#if 0 
static int anime_database_at_runtime__ParseDescriptionFile(const char * anime_datadir, const char * anime_filename, anime_t * anime_data) { 
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
#endif 
