#include "global.h" 
#include "script_c.h" 


// *** SCRIPT_C_ENV *** 

enum { SCRIPT_C__SIZE               = INT8_MAX  - 1 }; // RL: So that 'INT8_MAX' is an invalid value. 
enum { SCRIPT_C__STRING_BUFFER_SIZE = MIN(INT16_MAX - 1,(1 << 12)) }; // RL: So that 'INT16_MAX' is an invalid value. 
enum { SCRIPT_C__TEMP_DATA_SIZE     = INT8_MAX  - 1 }; // RL: So that 'INT8_MAX' is an invalid value. 

struct script_c_env_t { 
  int8_t malloced_huh; 
  int_script_c_t nb; 
  int_script_c_t active; 
  int8_t  running_huh; 
  char    string_buffer[SCRIPT_C__STRING_BUFFER_SIZE]; 
  int16_t string_buffer_nb; 
  const char * script_c_name[SCRIPT_C__SIZE]; 
  int       (* script_c_fun [SCRIPT_C__SIZE])(script_c_env_t * this, api_contexte_t * api_contexte); 
  char    data_temp    [SCRIPT_C__TEMP_DATA_SIZE]; // RL: Local temp data stack. 
  int8_t  data_temp_nb; 
}; 

enum {    script_c_env__sizeof__compiler_const = sizeof(struct script_c_env_t) }; 
const int script_c_env__sizeof                 = sizeof(struct script_c_env_t); 

static void assert_compile__check_type_size_gsa43ky837643iduy(void) {
  ASSERT_COMPILE__LOCAL(SCRIPT_C__SIZE               < INT8_MAX ); // RL: So that 'INT8_MAX' is an invalid value. 
  ASSERT_COMPILE__LOCAL(SCRIPT_C__STRING_BUFFER_SIZE < INT16_MAX); // RL: So that 'INT16_MAX' is an invalid value. 
  ASSERT_COMPILE__LOCAL(SCRIPT_C__TEMP_DATA_SIZE     < INT8_MAX ); // RL: So that 'INT8_MAX' is an invalid value. 
  script_c_env_t * this = NULL; 
  ASSERT_COMPILE__LOCAL(sizeof(this -> nb              ) >= sizeof(int8_t )); 
  ASSERT_COMPILE__LOCAL(sizeof(this -> string_buffer_nb) >= sizeof(int16_t)); 
  ASSERT_COMPILE__LOCAL(sizeof(this -> data_temp_nb    ) >= sizeof(int8_t )); 
}; 


script_c_env_t * script_c_env__make_r(script_c_env_t * this) { 
  bzero(this, sizeof(*this)); 
  this -> active = -1; 
  
  // RL: We allocate the trivial string. 
  this -> string_buffer[0] = '\0'; 
  this -> string_buffer_nb = 1; 
  
  return this; 
}; 

script_c_env_t * script_c_env__make(void) { 
  script_c_env_t * this; 
  this = (script_c_env_t *) malloc(sizeof(*this)); 
  script_c_env__make_r(this); 
  this -> malloced_huh = true; 
  return this; 
}; 

void script_c_env__delete_r(script_c_env_t * this) { 
  bzero(this, sizeof(*this)); 
}; 
 
void script_c_env__delete(script_c_env_t * this) { 
  const int malloced_huh = this -> malloced_huh; 
  script_c_env__delete_r(this); 
  if (malloced_huh) free(this); 
}; 
 
void script_c_env__print_d(const int fileno, const script_c_env_t * this) { 
  dprintf(fileno, "script_c_env_t: this = %p - sizeof = %d\n", this, (int)sizeof(this)); 
}; 




// *** SCRIPT_C *** 

enum { int_script_c_max__compiler_const = INT8_MAX }; 
const int_script_c_t int_script_c_max = int_script_c_max__compiler_const; 

int_script_c_t script_c__count(const script_c_env_t * this) { 
  return this -> nb; 
}; 

void script_c__print_d(const int fileno, const script_c_env_t * this, const int script_c) { 
  dprintf(fileno, "script_c: %d\n", (int) script_c); 
}; 

const char *   script_c__get_name(const script_c_env_t * this, const int script_c) { 
  if (script_c < 0) return NULL; 
  if (script_c >= this -> nb) return NULL; 
  return this -> script_c_name[script_c]; 
}; 

int_script_c_t script_c__lookup(const script_c_env_t * this, const char * script_c_name) { 
  LOCAL_ALLOCA__DECLARE(int16_t,INT16_MAX); 
  if (script_c_name == NULL) { return -1; }; 
  const char * script_c_name__lower = cstring__tolower__stack(script_c_name); 
  for (int i = 0; i < this -> nb; i++) { 
    if (0 == strcmp(this -> script_c_name[i], script_c_name__lower)) return i; 
  }; 
  return -1; 
}; 

static const char * script_c__strcopy_malloc(script_c_env_t * this, const char * cstr) { 
  if (cstr == NULL) { return NULL; }; 
  if (*cstr == '\0') { return this -> string_buffer; }; 
  const int cstr_sizeof = 1 + strlen(cstr); 
  if (this -> string_buffer_nb + cstr_sizeof > SCRIPT_C__STRING_BUFFER_SIZE) { return NULL; }; 
  const int index = this -> string_buffer_nb; 
  this -> string_buffer_nb += cstr_sizeof; 
  char * retval = this -> string_buffer + index; 
  bcopy(cstr, retval, cstr_sizeof); 
  return retval; 
}; 

static int_script_c_t script_c__push(script_c_env_t * this, const char * script_c_name, int (* script_c_fun)(script_c_env_t * this, api_contexte_t * api_contexte)) { 
  LOCAL_ALLOCA__DECLARE(int16_t,INT16_MAX); 
  if (this -> nb >= SCRIPT_C__SIZE) { return -1; }; 
  const int index = this -> nb; 
  const char * script_c_name__lower = cstring__tolower__stack(script_c_name); 
  const char * copied_name = script_c__strcopy_malloc(this, script_c_name__lower); 
  if (copied_name == NULL) { return -2; }; 
  for (int i = 0; i < this -> nb; i++) { 
    if (0 == strcmp(this -> script_c_name[i], script_c_name__lower)) { return -3; }; 
  }; 
  this -> nb++; 
  this -> script_c_name[index] = copied_name; 
  this -> script_c_fun [index] = script_c_fun; 
  return index; 
}; 


int script_c__set(script_c_env_t * this, const int target_script_c) { 
  if (this -> running_huh) { return -1; }; 
  this -> active = target_script_c; 
  return 0; 
}; 
 
int_script_c_t script_c__get(const script_c_env_t * this) { 
  return this -> active; 
}; 
 
int script_c__busy_huh(const script_c_env_t * this) { 
  return this -> running_huh; 
};   

int script_c__run(script_c_env_t * this, api_contexte_t * api_contexte) { 
  if (this -> running_huh) { return -1; }; 
  const int index = this -> active; 
  if (index < 0)           { return -2; }; 
  if (index >= this -> nb) { return -3; }; 
  
  this -> running_huh = true; // RL: This is not trivial as the function will yield to the kernel. 
  
  const int retval = this -> script_c_fun[index](this, api_contexte); 
  
  this -> running_huh = false; 
  
  return retval; 
}; 


// --- DATA TEMP --- 

int script_c__data_temp__get_size(const script_c_env_t * this) { 
  return SCRIPT_C__TEMP_DATA_SIZE; 
}; 

int script_c__data_temp__get_used(const script_c_env_t * this) { 
  return this -> data_temp_nb; 
}; 

int script_c__data_temp__get_avail(const script_c_env_t * this) { 
  return SCRIPT_C__TEMP_DATA_SIZE - this -> data_temp_nb; 
}; 

int script_c__data_temp__reset(script_c_env_t * this) { 
  this -> data_temp_nb = 0; 
  return 0; 
}; 

int script_c__data_temp__alloc(script_c_env_t * this, const int data_sizeof) { 
  const int offset    = this -> data_temp_nb; 
  const int available = SCRIPT_C__TEMP_DATA_SIZE - offset; 
  if (data_sizeof > available) return -1; 
  this -> data_temp_nb += data_sizeof; 
  return offset; 
}; 

int script_c__data_temp__write(script_c_env_t * this, const int data_offset, const int data_sizeof, const char * data_value) { 
  bcopy(data_value, this -> data_temp + data_offset, data_sizeof); 
  return 0; 
}; 

int script_c__data_temp__push(script_c_env_t * this, const int data_sizeof, const char * data_value) { 
  const int data_offset = script_c__data_temp__alloc(this, data_sizeof); 
  if (data_sizeof < 0) return data_sizeof; 
  const int retval = script_c__data_temp__write(this, data_offset, data_sizeof, data_value); 
  return retval; 
}; 

int script_c__data_temp__read(const script_c_env_t * this, const int data_offset, const int data_sizeof, char * data_value_allocated) { 
  if (data_offset < 0) { return -1; }; 
  if (data_offset + data_sizeof > this -> data_temp_nb) { return -2; }; 
  bcopy(this -> data_temp + data_offset, data_value_allocated, data_sizeof); 
  return 0; 
}; 

int script_c__data_temp__read_top(const script_c_env_t * this, const int data_sizeof, char * data_value_allocated) { 
  return script_c__data_temp__read(this, /*data_offset*/ this -> data_temp_nb - data_sizeof, data_sizeof, data_value_allocated); 
}; 
 
int script_c__data_temp__drop(script_c_env_t * this, const int data_sizeof) { 
  if (data_sizeof > this -> data_temp_nb) { return -1; }; 
  this -> data_temp_nb -= data_sizeof; 
  return 0; 
}; 


const char * script_c__data_temp__get_ptr(const script_c_env_t * this, const int data_offset) { 
  return this -> data_temp + data_offset; 
}; 

char * script_c__data_temp__get_ptr_data__temp_writable(script_c_env_t * this, const int data_offset) { 
  return this -> data_temp + data_offset; 
}; 




// *** SCRIPT_C_LIB1 *** 

#define READ_ARG(__type_t__,__var__)					\
  if (0 > script_c__data_temp__read_top(this, /*data_sizeof*/sizeof(__type_t__), (char *) &(__var__))) { \
    messerr("Expecting at least %d bytes of data on the temp-data stack, but there are only %d." "\n", sizeof(__type_t__), this -> data_temp_nb); \
    return -1;								\
  };									\
  script_c__data_temp__drop(this, sizeof(__type_t__)); 

#define PUSH_ARG(__type_t__,__var__)					\
  if (0 > script_c__data_temp__push(this, /*data_sizeof*/sizeof(__type_t__), (const char *) &(__var__))) { \
    messerr("Expecting at least %d bytes of data on the temp-data stack, but there are only %d." "\n", sizeof(__type_t__), this -> data_temp_nb); \
    return -2;								\
  }; 



static int script_c__lib1__hello(script_c_env_t * this, api_contexte_t * api_contexte) { 
  fprintf(stderr, "Hello world!\n"); 
  return 0; 
}; 




static int script_c__lib1__afficher_message_aux(script_c_env_t * this, api_contexte_t * api_contexte, const char * msg_given) { 
  //messerr("I was given the message: '%s'" "\n", msg_given); 
  
  SCRIPT_AfficherMessage(msg_given); 
  
  return 0; 
}; 

static int script_c__lib1__afficher_message(script_c_env_t * this, api_contexte_t * api_contexte) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " this = %p, api_contexte = %p, this -> data_temp_nb = %d "   "\n", __func__, this, api_contexte, this -> data_temp_nb); 

  int int_argc; 
  READ_ARG(int,int_argc); 
  // For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
  //int int_argv[int_argc]; 
  enum { int_argv__unitsize = 127 }; 
  assert(int_argv__unitsize >= int_argc); 
  int int_argv[int_argv__unitsize]; 
  for (int i = 0; i < int_argc; i++) { 
    READ_ARG(int,int_argv[i]); 
  }; 

  int ptr_argc; 
  READ_ARG(int,ptr_argc); 
  // For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
  //void * ptr_argv[ptr_argc]; 
  enum { ptr_argv__unitsize = 127 }; 
  assert(ptr_argv__unitsize >= ptr_argc); 
  void * ptr_argv[ptr_argv__unitsize]; 
  for (int i = 0; i < ptr_argc; i++) { 
    READ_ARG(void *,ptr_argv[i]); 
  }; 

  int cptr_argc; 
  READ_ARG(int,cptr_argc); 
  // For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
  //const void * cptr_argv[cptr_argc]; 
  enum { cptr_argv__unitsize = 127 }; 
  assert(cptr_argv__unitsize >= cptr_argc); 
  const void * cptr_argv[cptr_argv__unitsize]; 
  for (int i = 0; i < cptr_argc; i++) { 
    READ_ARG(void *,cptr_argv[i]); 
  }; 
  
  if (int_argc != 0) { 
    messerr("Too many int_arg - expecting %d int_arg - got %d " "\n", 0, int_argc); 
    return -3; 
  }; 

  if (ptr_argc != 0) { 
    messerr("Too many ptr_arg - expecting %d ptr_arg - got %d " "\n", 0, ptr_argc); 
    return -4; 
  }; 

  if (cptr_argc < 1) { 
    messerr("Not enough cptr_arg - expecting %d cptr_arg - got %d " "\n", 1, cptr_argc); 
    return -5; 
  }; 

  if (cptr_argc > 1) { 
    messerr("Too many cptr_arg - expecting %d cptr_arg - got %d " "\n", 1, cptr_argc); 
    return -6; 
  }; 

  const char * msg_given = cptr_argv[0]; 
  const int retval = script_c__lib1__afficher_message_aux(this, api_contexte, msg_given); 

  script_c__data_temp__reset(this); 
  PUSH_ARG(int,retval); 

  return retval; 
}; 









static int script_c__lib1__menu_aux(script_c_env_t * this, api_contexte_t * api_contexte, const char * msg_given, const int choix_nb, const char * choix_cstr[]) { 
  //messerr("I was given the message: '%s'" "\n", msg_given); 
  
  //CMiniMenu * MiniMenu = NULL; 
  CMenuAbstrait * MiniMenu = NULL; 
  MiniMenu = SCRIPT_BeginAfficherMenu(); // RL: Deleted by 'SCRIPT_BeginAfficherMenu'. 
  for (int i = 0; i < choix_nb; i++) { 
    MiniMenu -> Add(MiniMenu, 0, choix_cstr[i], NULL); 
  }; 

#if 0   
  fprintf(stderr, "XXX Tic: instruction courante = %d" "\n", *(int*)api_contexte -> TypeInstructionCourante);
  fprintf(stderr, "XXX Tic: instruction courante = %d" "\n", *(int*)api_contexte -> TypeInstructionCourante);
  fprintf(stderr, "XXX Tic: instruction courante = %d" "\n", *(int*)api_contexte -> TypeInstructionCourante);
  fprintf(stderr, "XXX Tic: instruction courante = %d" "\n", *(int*)api_contexte -> TypeInstructionCourante);
  fprintf(stderr, "XXX Tic: instruction courante = %d" "\n", *(int*)api_contexte -> TypeInstructionCourante);
  fprintf(stderr, "XXX Tic: instruction courante = %d" "\n", *(int*)api_contexte -> TypeInstructionCourante);
  fprintf(stderr, "XXX Tic: instruction courante = %d" "\n", *(int*)api_contexte -> TypeInstructionCourante);
  fprintf(stderr, "XXX Tic: instruction courante = %d" "\n", *(int*)api_contexte -> TypeInstructionCourante);
#endif 
  
  SCRIPT_AfficherMenu(msg_given); 
  
  const int choix = MiniMenu -> Canceled ? 0 : 1 + MiniMenu -> itheta; 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " choix = %d"   "\n", __func__, choix); 
  
  return choix; 
}; 

static int script_c__lib1__menu(script_c_env_t * this, api_contexte_t * api_contexte) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " this = %p, api_contexte = %p, this -> data_temp_nb = %d "   "\n", __func__, this, api_contexte, this -> data_temp_nb); 

  int int_argc; 
  READ_ARG(int,int_argc); 
  // For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
  //int int_argv[int_argc]; 
  enum { int_argv__unitsize = 127 }; 
  assert(int_argv__unitsize >= int_argc); 
  int int_argv[int_argv__unitsize]; 
  for (int i = 0; i < int_argc; i++) { 
    READ_ARG(int,int_argv[i]); 
  }; 

  int ptr_argc; 
  READ_ARG(int,ptr_argc); 
  // For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
  //void * ptr_argv[ptr_argc]; 
  enum { ptr_argv__unitsize = 127 }; 
  assert(ptr_argv__unitsize >= ptr_argc); 
  void * ptr_argv[ptr_argv__unitsize]; 
  for (int i = 0; i < ptr_argc; i++) { 
    READ_ARG(void *,ptr_argv[i]); 
  }; 

  int cptr_argc; 
  READ_ARG(int,cptr_argc); 
  // For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
  //const void * cptr_argv[cptr_argc]; 
  enum { cptr_argv__unitsize = 127 }; 
  assert(cptr_argv__unitsize >= cptr_argc); 
  const void * cptr_argv[cptr_argv__unitsize]; 
  for (int i = 0; i < cptr_argc; i++) { 
    READ_ARG(void *,cptr_argv[i]); 
  }; 
  
  if (int_argc != 0) { 
    messerr("Too many int_arg - expecting %d int_arg - got %d " "\n", 0, int_argc); 
    return -3; 
  }; 

  if (ptr_argc != 0) { 
    messerr("Too many ptr_arg - expecting %d ptr_arg - got %d " "\n", 0, ptr_argc); 
    return -4; 
  }; 

  if (cptr_argc < 2) { 
    messerr("Not enough cptr_arg - expecting %d cptr_arg - got %d " "\n", 2, cptr_argc); 
    return -5; 
  }; 
  
  const char * msg_given = cptr_argv[0]; 
  const int retval = script_c__lib1__menu_aux(this, api_contexte, msg_given, cptr_argc - 1, (const char * *)&cptr_argv[1]); 
  
  script_c__data_temp__reset(this); 
  PUSH_ARG(int,retval); 
  
  return retval; 
}; 










static int script_c__lib1__brigitte_bonjour(script_c_env_t * this, api_contexte_t * api_contexte) { 
  const char msg_given[] = "Bonjour Brigitte! Comment vas-tu? Cela fait plaisir de te voir!";  
 
  SCRIPT_AfficherMessage(msg_given); 
  
  SCRIPT_AfficherMessage("Brigitte: Le feu, ça brûle; et l'eau¸ ça mouille; tous les oiseaux volent dans le ciel."); 
  
  return 0; 
}; 


static int script_c__lib1__brigitte_pastas(script_c_env_t * this, api_contexte_t * api_contexte) { 
  const char msg_given[] = "Brigitte: Aimes-tu les pastas?";  
 
  CMenuAbstrait * MiniMenu = NULL; 
  MiniMenu = SCRIPT_BeginAfficherMenu(); // RL: 'MiniMenu' object will be deleted by 'SCRIPT_BeginAfficherMenu'. 
  MiniMenu -> Add(MiniMenu, 0, "Beaucoup!", NULL); 
  MiniMenu -> Add(MiniMenu, 0, "Je préfère le riz au curry.", NULL); 
  MiniMenu -> Add(MiniMenu, 0, "Non merci, j'ai une thèse à écrire et je suis allé acheter un KFC.", NULL); 
  
  SCRIPT_AfficherMenu(msg_given); 
  
  const int choix = MiniMenu -> Canceled ? 0 : 1 + MiniMenu -> itheta; 
  
  if (0 == choix) { 
    SCRIPT_AfficherMessage("Brigitte: Hé! Tu peux me répondre quand je te parle au lieu de m'ignorer!"); 
  }
  else if (1 == choix) { 
    SCRIPT_AfficherMessage("Brigitte: Super. Je t'en fais pour ce soir."); 
  }
  else if (2 == choix) { 
    SCRIPT_AfficherMessage("Brigitte: Décidément, nous n'avons pas les mêmes valeurs."); 
  }
  else if (3 == choix) { 
    SCRIPT_AfficherMessage("Brigitte: Non mais tu vas en faire quoi de ta thèse?"); 
  }; 

  
  return 0; 
}; 






static int script_c__lib1__prendre_clef(script_c_env_t * this, api_contexte_t * api_contexte) { 
  LOCAL_ALLOCA__DECLARE(int16_t,INT16_MAX); 
  const char Perso[] = "Pourfendeur-de-dinotores"; 
  const char nom_boss[] = "Chouchou"; 
  
  SCRIPT_AfficherMessage(strconcat__stack(Perso, " : Cool !! J'ai gagné une clef !!")); 
  SCRIPT_JouerMusique(""); 
  SCRIPT_Wait(/*nbpasses*/25); 
  SCRIPT_Camera_Init(); // Camera->defaut(); 
  SCRIPT_Camera_Zoom(/*zoom_factor*/0.75f); 
  SCRIPT_Camera_Baisser(); 
  //SCRIPT_Camera_Baisser(); 
  SCRIPT_JouerMusique("secte.mid"); 
  
  SCRIPT_AjouterObjetAnime("homme_g"   , "homme_bizarre.anime"); 
  SCRIPT_AjouterObjetAnime("homme_d"   , "homme_bizarre.anime"); 
  SCRIPT_AjouterObjetAnime("homme_rien", "homme_bizarre.anime"); 
   
  SCRIPT_SetPosition_vXY("homme_g"   , 20.0f, 15.0f, mpABSOLU); 
  SCRIPT_SetPosition_vXY("homme_rien", 21.0f, 15.0f, mpABSOLU); 
  SCRIPT_SetPosition_vXY("homme_d"   , 22.0f, 15.0f, mpABSOLU); 
  
  SCRIPT_Deplacer("homme_g"   , 20.0f, 17.0f, mpABSOLU); 
  SCRIPT_Deplacer("homme_rien", 21.0f, 17.0f, mpABSOLU); 
  SCRIPT_Deplacer("homme_d"   , 22.0f, 17.0f, mpABSOLU); 
  
  SCRIPT_WaitFor("homme_g");
  
  SCRIPT_AfficherMessage("Homme de droite : Polisson !!"); 

  SCRIPT_Deplacer("heros", 21.1f, 18.2f, mpABSOLU); 
  
  SCRIPT_WaitFor("heros"); 
  
  SCRIPT_Deplacer("heros", 21.1f, 17.9f, mpABSOLU); 

  SCRIPT_WaitFor("heros"); 
  
  SCRIPT_AfficherMessage("Homme de gauche : Sacripan !!");
  SCRIPT_AfficherMessage("Homme de rien : Rends nous les clefs de la cuisine !! On a faim !!");
  SCRIPT_AfficherMessage("Homme de droite : Ah oui c'est vrai... d'ailleurs... ");
  SCRIPT_AfficherMessage("Homme de gauche : voici ici de la viande fraaaîiche !!!");
  SCRIPT_AfficherMessage("Homme de droite : Je dirai même plus : de la viande fraîche !!!");
  SCRIPT_AfficherMessage(strconcat__stack("Homme de rien : Mais pas pour nous !!!! Elle l'est pour ", nom_boss, "...")); 
   
  SCRIPT_Deplacer("heros", 15.0f, 20.0f, mpABSOLU); 

  SCRIPT_WaitFor("heros"); 
  
  SCRIPT_ChangerDeCarte_vXY("niveau1_2.carte", 15.0f, 20.0f, 1); 
  
  SCRIPT_SetPosition_vXYZ("heros", 15.0f, 20.0f, 200.0f, mpABSOLU);
  SCRIPT_Wait(/*nbpasses*/1); 
  
  for (int i = 0; i < 100; i++) { 
    //SCRIPT_SetPosition_vXYZ("heros", 0.0f, 0.0f, -0.5f, mpRELATIF); 
    SCRIPT_Wait(/*nbpasses*/1); 
  }; 
  
  SCRIPT_ChangerDeCarte_vXY("niveau1_1.carte", 15.0f, 23.0f, 1); 
  
  SCRIPT_SetPosition_vXYZ("heros", 15.0f, 23.0f, 200.0f, mpABSOLU);
  SCRIPT_Wait(/*nbpasses*/1); 
  
  for (int i = 0; i < 100; i++) { 
    SCRIPT_SetPosition_vXYZ("heros", 0.0f, 0.0f, -0.05f, mpRELATIF); 
    SCRIPT_Wait(/*nbpasses*/1); 
  }; 

  SCRIPT_ChangerDeCarte_vXY("niveau1_0.carte", 6.0f, 6.0f, 1); 
  
  SCRIPT_JouerMusique(""); 

  SCRIPT_AjouterObjetAnime("boss", "dinotore.anime"); 

  SCRIPT_SetPosition_vXY("boss", 6.0f, 10.0f, mpABSOLU); 

  SCRIPT_SetPosition_vXYZ("heros", 6.0f, 6.0f, 200.0f, mpABSOLU);
  SCRIPT_Wait(/*nbpasses*/1); 
  
  for (int i = 0; i < 100; i++) { 
    SCRIPT_SetPosition_vXYZ("heros", 0.0f, 0.0f, -0.05f, mpRELATIF); 
    SCRIPT_Wait(/*nbpasses*/1); 
  }; 

  
   SCRIPT_AfficherMessage(strconcat__stack(nom_boss, " : Tiens, tiens, mais qui voilà? Ah, tu dois être l'élu! Ecoute-moi! Il est encore temps de choisir la gloire; tu peux encore abandonner ta condition de misère et rallier notre cause.")); 
   SCRIPT_AfficherMessage(strconcat__stack(Perso, " : Tu veux dire abandonner mes amis, trahir mon père, faire le mal, répandre la terreur de par le monde, semer la panique, et tout et tout?")); 
   SCRIPT_AfficherMessage(strconcat__stack(nom_boss, " : Ouais!")); 
   SCRIPT_AfficherMessage(strconcat__stack(Perso, " : Ok.")); 
   SCRIPT_AfficherMessage(strconcat__stack(nom_boss, " : Bien joué petit, tu as fait le bon choix!")); 
   SCRIPT_AfficherMessage(strconcat__stack(Perso, " : Non mais je rêve, t'y as cru ?! HAHA, vilaine bête, viens par ici que je te botte les fesses pour venger la mort de mon père.")); 
   
   SCRIPT_JouerMusique("boss.mid"); 

  return 0; 
}; 


int script_c__lib1__fill(script_c_env_t * this) { 
  script_c__push(this, "Hello", script_c__lib1__hello); 
  script_c__push(this, "AfficherMessage", script_c__lib1__afficher_message); 
  script_c__push(this, "menu", script_c__lib1__menu); 
  script_c__push(this, "brigitte_bonjour", script_c__lib1__brigitte_bonjour); 
  script_c__push(this, "brigitte_pastas", script_c__lib1__brigitte_pastas); 
  script_c__push(this, "prendre_clef", script_c__lib1__prendre_clef); 
  return 0; 
}; 




