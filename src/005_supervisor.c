#include "global.h" 
#include "005_supervisor.h" 
#include "text.h"

// *** SUPERVISOR_MODE_TYPE *** 
 
const int_supervisor_mode_type_t int_supervisor_mode_type_max = INT8_MAX; 

const int_supervisor_mode_type_t supervisor_mode__count = SUPERVISOR_MODE__COUNT; 
 
static const char * supervisor_mode__type_cstr_array[] = { 
  "IDLE", 
  "MESSAGE", 
  "MENU", 
  NULL 
}; 

const char * supervisor_mode__type_get_cstr(const int supervisor_mode_type) { 
  if (supervisor_mode_type < 0) { return NULL; }; 
  if (supervisor_mode_type >= SUPERVISOR_MODE__COUNT) { return NULL; }; 
  return supervisor_mode__type_cstr_array[supervisor_mode_type]; 
}; 


// *** SUPERVISOR_ENV *** 

enum { MESSAGE_SIZE = (1 << 12) };  
struct supervisor_env_t { 
  int8_t malloced_huh; 
  int_supervisor_mode_type_t automaton_state; 
  char message_buffer[MESSAGE_SIZE]; 
  CMessageTexte * MessageTexte; 
  CMiniMenu * MiniMenu; 
  int * where_to_write_the_result_ref; 
}; 
 
enum { supervisor_env__sizeof__compiler_const = sizeof(struct supervisor_env_t) }; 

const int supervisor_env__sizeof = sizeof(struct supervisor_env_t); 

supervisor_env_t * supervisor_env__make_r(supervisor_env_t * this) { 
  bzero(this, sizeof(*this)); 

  this -> MessageTexte = CMessageTexte_make(); 
  
  this -> MiniMenu = NULL; 

  return this; 
}; 

supervisor_env_t * supervisor_env__make(void) { 
  supervisor_env_t * this = (supervisor_env_t *) malloc(sizeof(*this)); 
  supervisor_env__make_r(this); 
  this -> malloced_huh = true; 
  return this; 
};  

void supervisor_env__delete_r(supervisor_env_t * this) { 
  if (this -> MiniMenu != NULL) { CMiniMenu_delete(this -> MiniMenu); }; 
  CMessageTexte_delete(this -> MessageTexte); 
  bzero(this, sizeof(*this)); 
}; 

void supervisor_env__delete(supervisor_env_t * this) { 
  const int malloced_huh = this -> malloced_huh; 
  supervisor_env__delete_r(this); 
  if (malloced_huh) free(this); 
}; 



// *** SUPERVISOR_MODE *** 
 
static int supervisor__automaton(supervisor_env_t * this) { 
  int next_state = -1; 
  switch (this -> automaton_state) { 

  default: assert(false); break; 

  case SUPERVISOR_MODE__IDLE: next_state = SUPERVISOR_MODE__IDLE; break; 

  case SUPERVISOR_MODE__MESSAGE: { 
    CMessageTexte * MessageTexte = this -> MessageTexte; 
    const int text_was_read_huh = MessageTexte -> Input(MessageTexte); 
    MessageTexte -> Life(MessageTexte); 
    MessageTexte -> Render(MessageTexte); 
    //fprintf(stderr, "<%s:" STRINGIFY(__LINE__) ">: " "text_was_read_huh = %s" "\n", __func__, bool_string(text_was_read_huh)); fflush(NULL); 
    next_state = text_was_read_huh ? SUPERVISOR_MODE__IDLE : SUPERVISOR_MODE__MESSAGE; 
  }; break; 
    
  case SUPERVISOR_MODE__MENU: { 
    CMessageTexte * MessageTexte = this -> MessageTexte; 
    MessageTexte -> Life(MessageTexte); 
    MessageTexte -> Render(MessageTexte); // RL: Menu title. 
    
    CMiniMenu * MiniMenu = this -> MiniMenu; 
    const int choice_made_huh = MiniMenu -> Input(MiniMenu); 
    MiniMenu -> Life(MiniMenu); 
    MiniMenu -> Render(MiniMenu); 
    if (choice_made_huh) { 
      const int choice = MiniMenu -> parent.Canceled ? 0 : 1 + MiniMenu -> parent.itheta; 
      *(this -> where_to_write_the_result_ref) = choice; 
      next_state = SUPERVISOR_MODE__IDLE; 
    } 
    else { 
      next_state = SUPERVISOR_MODE__MENU; 
    }; 
  }; break; 
    
  }; 
  
  return next_state; 
}; 

int supervisor__loop(supervisor_env_t * this) { 
  const int next_state = supervisor__automaton(this); 
  this -> automaton_state = next_state; 
  return next_state; 
}; 


int supervisor__message(supervisor_env_t * this, const char * message) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " sizeof(this -> message_buffer) = %d "   "\n", __func__, (int) sizeof(this -> message_buffer)); 
  
  if (this -> automaton_state != SUPERVISOR_MODE__IDLE) { return -1; }; 
  if (message == NULL) { return -2; }; 
  
#if 0 
  strlcpy(this -> message_buffer, message, sizeof(this -> message_buffer)); 
#endif 
  
  this -> automaton_state = SUPERVISOR_MODE__MESSAGE; 
  
  this -> MessageTexte -> SetMsg(this -> MessageTexte, message); 
  
  return 0; 
}; 


int supervisor__menu(supervisor_env_t * this, int * where_to_write_the_result_ref, const char * message, const int choix_nb, const char * choix_array[]) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " sizeof(this -> message_buffer) = %d "   "\n", __func__, (int) sizeof(this -> message_buffer)); 
  
  if (this -> automaton_state != SUPERVISOR_MODE__IDLE) { return -1; }; 
  if (message == NULL) { return -2; }; 
  if (where_to_write_the_result_ref == NULL) { return -3; }; 
  
#if 0 
  strlcpy(this -> message_buffer, message, sizeof(this -> message_buffer)); 
#endif 
  
  this -> MessageTexte -> SetMsg(this -> MessageTexte, message); 
  
  this -> automaton_state = SUPERVISOR_MODE__MENU; 
  
  CMiniMenu * MiniMenu = CMiniMenu_make(/*x*/100, /*y*/300,/*w*/1000); 
  for (int i = 0; i < choix_nb; i++) { 
    MiniMenu -> parent.Add(&MiniMenu -> parent, /*colonne*/0, /*nom*/choix_array[i], /*nom_texture*/NULL); 
  }; 
  
  this -> MiniMenu = MiniMenu; 
  
  this -> where_to_write_the_result_ref = where_to_write_the_result_ref; 
  
  return 0; 
}; 


