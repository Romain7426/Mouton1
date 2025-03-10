#include "global.h"
#include "script_pscript.h"
#include <pscript/pscript.h>
#include "script_api.h"
#include "script_pscript_callbacks.ci" 
 
// ***** DB ***** 
enum           { CPascal_dico__size = 128 }; 
static char *    CPascal_dico__filename[CPascal_dico__size] = {}; 
static CPascal * CPascal_dico__object  [CPascal_dico__size] = {}; 
static int       CPascal_dico__usersnb [CPascal_dico__size] = {}; 
static int       CPascal_dico__nb = 0; 

static int CPascal_dico__push(const char * filename, CPascal * objet_non_copie) {
  assert(CPascal_dico__nb < CPascal_dico__size); 
  const int index = CPascal_dico__nb; 
  CPascal_dico__filename[index] = strcopy_malloc(filename); 
  CPascal_dico__object  [index] = objet_non_copie; 
  CPascal_dico__usersnb [index] = 1; 
  CPascal_dico__nb++; 
  return index; 
}; 

static int CPascal_dico__lookup(const char * filename) {
  char * * p = CPascal_dico__filename; 
  for (int i = 0; i < CPascal_dico__nb; i++) {
    if (0 == strcmp(*p, filename)) return i; 
    p++; 
  };
  return -1;
}; 

static CPascal * CPascal_dico__get(const int i) {
  CPascal_dico__usersnb[i] ++; 
  return CPascal_dico__object[i];
}; 

static void CPascal_dico__release(const int i) {
  CPascal_dico__usersnb[i] --; 
}; 



// ***** OBJECT ***** 

CPascal * CPascal__make_empty(void) { 
  MALLOC_BZERO(CPascal,this);
  
  ASSIGN_METHOD(CPascal,this,make_empty); 
  ASSIGN_METHOD(CPascal,this,make_with_file); 
  ASSIGN_METHOD(CPascal,this,delete); 
  ASSIGN_METHOD(CPascal,this,read_file_no_init); 
  ASSIGN_METHOD(CPascal,this,link_writeln); 
  ASSIGN_METHOD(CPascal,this,link_menu); 
  ASSIGN_METHOD(CPascal,this,link_methods); 
  ASSIGN_METHOD(CPascal,this,link_ffiprocs); 
  ASSIGN_METHOD(CPascal,this,init_file); 
  
  ASSIGN_METHOD(CPascal,this,execProcedure); 
  ASSIGN_METHOD(CPascal,this,execProcedure_step); 
  ASSIGN_METHOD(CPascal,this,next_step); 
  ASSIGN_METHOD(CPascal,this,busy_huh); 
  ASSIGN_METHOD(CPascal,this,stack_push_int); 
  ASSIGN_METHOD(CPascal,this,stack_push_string); 
#if 0
#endif 

  this -> funproc_i = -1; 
  this -> next_ipc0 = -1; 
  this -> dico_i    = -1; 
  
  return this; 
}; 

#define LOGFILE_EXTENSION ".out" 
#if 1 
static int CPascal__read_file_no_init__aux(pscript_t * this, const char * filename) { 
  LOCAL_ALLOCA__DECLARE(int16_t,INT16_MAX); 
  int allright_huh; 
  const int logfile_len = ARRAY_SIZE(LOGDIR) + strlen(filename) + ARRAY_SIZE(LOGFILE_EXTENSION); 
  char logfile_name[logfile_len + 1]; 
  strcat(strcat(strcpy(logfile_name, LOGDIR), filename), LOGFILE_EXTENSION); 
  message("%s: " "logfile_name: %s" "\n", __func__, logfile_name); 
  const int stdlog_d = open(logfile_name, O_WRONLY | O_CREAT | O_TRUNC, (mode_t) 0666); 
  assert(stdlog_d >= 0); 
  //char stdlog_buffer[1 << 12]; 
  //setvbuf(stdlog_d, stdlog_buffer, _IOLBF, sizeof(stdlog_buffer)); // RL: Line buffered. 
#if 1 
  {
    const int status = fcntl(stdlog_d, F_GETFL, 0); 
    printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " status of stdlog_d = %d ---" "\n", __func__, status); 
    printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " O_SYNC of stdlog_d = %d ---" "\n", __func__, status & O_SYNC); 
    fflush(NULL); 
  }; 
#endif 

  this -> stdlog__set__fdes(this, stdlog_d); 
  //this -> stderr__set__fdes(this, fileno(zeldaferror ? zeldaferror : stderr), true); 
  this -> stderr__set__fdes(this, fileno(stderr), true); 
  this -> stdout__set__fdes(this, STDOUT_FILENO); 
  const int input_file_len = ARRAY_SIZE(PASCALDIR) + strlen(filename); 
  char input_file_name[input_file_len + 1]; 
  strcat(strcpy(input_file_name, PASCALDIR), filename); 

  const int input_file_fd = open(input_file_name, O_RDONLY); 
  if (input_file_fd < 0) { messerr("Something got wrong while trying to open the file '%s'." "\n", input_file_name); return false; }; 
  do { 
    // RL: Buffering the input 
    const int input_i = pscript_input__make_from_fileno(this -> input_env, input_file_fd, input_file_name); 
    if (input_i < 0) { allright_huh = input_i; messerr("Something got wrong while buffering the file '%s': %s." "\n", input_file_name, int_string__stack(allright_huh)); break; }; 
    
    // RL: Token-parsing the file 
    allright_huh = pscript_token__parser(this -> input_env, input_i, this -> token_env); 
    if (not(allright_huh)) { messerr("Something got wrong while tokenizing the file '%s'." "\n", input_file_name); break; }; 
    { 
      dputs_array(stdlog_d, "TOTAL READ CHARS      : ", int_string__stack(this -> input_env -> cumulated_read_nb[input_i]), "\n"); 
      dputs_array(stdlog_d, "TOTAL READ LINES      : ", "TODO XXX FIXME", "\n"); 
      dputs_array(stdlog_d, "TOTAL COMPUTED STRINGS: ", int_string__stack(pscript_string__get_count(this -> string_env)), "\n"); 
      dputs_array(stdlog_d, "TOTAL COMPUTED TOKENS : ", int_string__stack(pscript_token__get_count(this -> token_env)), "\n"); 
      pscript_string__print_stats      (stdlog_d, this -> string_env); 
      pscript_token__print_stats       (stdlog_d, this ->  token_env); 
#if 0 
      // As of 2023-07-27, these functions became very slow...???? 
      pscript_string__print_all_strings(stdlog_d, this -> string_env); 
      pscript_token__print_all_tokens  (stdlog_d, this ->  token_env); 
#endif 
    }; 
      
    // RL: Checking whether parenthesis are well-balanced. 
    allright_huh = pscript_parser__parenthesis__check(this -> token_env); 
    if (allright_huh < 0) { messerr("Something got wrong while checking whether the file '%s' was well parenthesized: %s." "\n", input_file_name, int_string__stack(allright_huh)); break; }; 
    
    // RL: Parsing syntax into structured data. 
    allright_huh = pscript_parser__automaton(this -> parser_env, this -> token_env); 
    if (allright_huh < 0) { messerr("Something got wrong while parsing the file '%s': %s." "\n", input_file_name, int_string__stack(allright_huh)); break; }; 
    { 
#if 0 
      // As of 2023-07-27, these functions became very slow...???? 
      pscript_parser__print_stats (stdlog_d, this -> parser_env); 
      pscript_parser__print_all   (stdlog_d, this -> parser_env); 
      pscript_parser__print_pretty(stdlog_d, this -> string_env, this -> token_env, this -> parser_env); 
#endif 
    }; 
    
    // RL: Filling up the symbols table, initializing data, and generating bytecode. 
    allright_huh = pscript_code_parser(this, this -> parser_env); 
    if (allright_huh < 0) { messerr("File '%s' - Something got wrong while filling up the symbols table, initializing data, and generating bytecode: %s." "\n", input_file_name, int_string__stack(allright_huh)); break; }; 
    { 
      dputs_array(stdlog_d, "TOTAL COMPUTED TYPES     : ", int_string__stack(pscript_type__get_count    (this ->     type_env)), "\n"); 
      dputs_array(stdlog_d, "TOTAL COMPUTED CONSTANTS : ", int_string__stack(pscript_const__get_count   (this ->    const_env)), "\n"); 
      dputs_array(stdlog_d, "TOTAL COMPUTED VARIABLES : ", int_string__stack(pscript_var__get_count     (this ->      var_env)), "\n"); 
      dputs_array(stdlog_d, "TOTAL COMPUTED FUNPROC   : ", int_string__stack(pscript_funproc__get_count (this ->  funproc_env)), "\n"); 
      dputs_array(stdlog_d, "TOTAL COMPUTED MAINPROC  : ", int_string__stack(pscript_mainproc__get_count(this -> mainproc_env)), "\n"); 
      dputs_array(stdlog_d, "TOTAL COMPUTED FFIPROC   : ", int_string__stack(pscript_ffiproc__get_count (this ->  ffiproc_env)), "\n"); 
      dputs_array(stdlog_d, "TOTAL COMPUTED LIBPROC   : ", int_string__stack(pscript_libproc__get_count (this ->  libproc_env)), "\n"); 
      dputs_array(stdlog_d, "TOTAL COMPUTED GLOBAL ENV: ", int_string__stack(pscript_env__get_count     (this ->          env)), "\n"); 
      funproc_stack__print_all (stdlog_d, this ->  funproc_env, this -> string_env); 
      ffiproc_stack__print_all (stdlog_d, this ->  ffiproc_env, this -> string_env); 
      mainproc_stack__print_all(stdlog_d, this -> mainproc_env, this -> string_env); 
      pscript_env__print_all   (stdlog_d, this ->          env, this -> string_env); 


      dputs_array(stdlog_d, "TOTAL COMPUTED BYTEDATA(BSS): "  , int_string__stack(pscript_mem__toplevel_compiletime__bss__used(this -> mem_env)), "\n"); 
      dputs_array(stdlog_d, "TOTAL COMPUTED BYTEDATA(ZSS): "  , int_string__stack(pscript_mem__toplevel_compiletime__zss__used(this -> mem_env)), "\n"); 
      dputs_array(stdlog_d, "TOTAL COMPUTED BYTEDATA(ISS): "  , int_string__stack(pscript_mem__toplevel_compiletime__iss__used(this -> mem_env)), "\n"); 
      // RL: TODO XXX FIXME: Missing bytedata printing. 
      
      dputs_array(stdlog_d, "TOTAL COMPUTED BYTECODES: " , int_string__stack(pscript_bytecode__get_count(this -> bytecode_env)), "\n"); 
#if 0 
      // RL: As of 2023-07-27, these functions became very slow...???? 
      // RL: 2023-08-15: Yes, because it prints word by word - and it’s not buffered. 
      bytecode_stack__print_all(stdlog_d, this -> bytecode_env, this -> type_env); 
#endif 
    };  
    
    allright_huh = true; 
  } while (false); 
  close(input_file_fd); 
  return (allright_huh > 0); 
}; 
#else 
static int CPascal__read_file_no_init__aux(pscript_t * this, const char * filename) { 
  int allright_huh; 
  const int logfile_len = ARRAY_SIZE(LOGDIR) + strlen(filename) + ARRAY_SIZE(LOGFILE_EXTENSION); 
  char logfile_name[logfile_len + 1]; 
  strcat(strcat(strcpy(logfile_name, LOGDIR), filename), LOGFILE_EXTENSION); 
  message("%s: " "logfile_name: %s" "\n", __func__, logfile_name); 
  const int fdes_log = open(logfile_name, O_WRONLY | O_CREAT | O_TRUNC, (mode_t) 0666); 
  assert(fdes_log >= 0); 
  this -> stdlog__set__fdes(this, fdes_log); 
  this -> stderr__set__fdes(this, fileno(zeldaferror), true); 
  this -> stdout__set__fdes(this, STDOUT_FILENO); 
  const int input_file_len = ARRAY_SIZE(PASCALDIR) + strlen(filename); 
  char input_file_name[input_file_len + 1]; 
  strcat(strcpy(input_file_name, PASCALDIR), filename); 
  const int input_file_fd = open(input_file_name, O_RDONLY); 
  allright_huh = this -> ReadDescriptionFile_fd(this, input_file_fd, input_file_name); 
  close(input_file_fd); 
  return allright_huh; 
}; 
#endif 

int CPascal__read_file_no_init(CPascal * this, const char * filename) { 
  if (NULL ==  filename) { return -1; }; 
  if ('\0' == *filename) { return -2; }; 
  if (this -> pscript_env == NULL) 
    this -> pscript_env = pscript_make(); 
  if (this -> filename != NULL) { free(this -> filename); }; 
  this -> filename = strcopy_malloc(filename); 
  return CPascal__read_file_no_init__aux(this -> pscript_env, filename); 
}; 

static int CPascal__writeln_callback(void * writeln_data, const char * cstr) {
  SCRIPT_AfficherMessage(cstr); 
  return 0; 
}; 
  
int CPascal__link_writeln(CPascal * this) {
  this -> pscript_env -> writeln_set(this -> pscript_env, /* writeln_data */ NULL, CPascal__writeln_callback); 
  return 0; 
}; 

//extern CMenuAbstrait * MiniMenu; 
#if 0 
static int CPascal__menu_callback(void * menu_data, const char * menu_title, const int menu_item_nb, const char * item[]) {
  messerr("%s: " "msg = %s" "\n", __func__, menu_title); 
  CMenuAbstrait * MiniMenu = NULL; 
  MiniMenu = SCRIPT_BeginAfficherMenu(); 
  for (int i = 0; i < menu_item_nb; i++) { 
#if 1 
    messerr("%s: " "\t" "item = %s" "\n", __func__, item[i]); 
#endif 
    MiniMenu -> Add(MiniMenu, 0, item[i], NULL); 
  }; 
  // RL: The return value is async. 
  // The game called a pscript function, which in turn called a game function. 
  // That last game function is async - it changed the game mode at the top level - and when the PScript came back to the top level, 
  // the code for the nested function is actually run. 
  // But, then, a consequence is that this function must push the value on its own on the stack. 
  // Therefore the PScript VM does not see the returned value. And it won't see it. 
  // It will be there at the next PScript VM instruction, but the VM did not push it. 
  // It was pushed on the stack by the game (as this call is async). 
#if 1 
  SCRIPT_AfficherMenu(menu_title); 
  return 0; 
#else 
  const int choice = SCRIPT_AfficherMenu(menu_title); 
  return choice; 
#endif 
}; 
#endif 
  


#if 1 
int CPascal__link_menu(CPascal * this) { 
  // RL: Grammar 
  pscript_token_env_t  *  token_env = this -> pscript_env ->  token_env; 
  pscript_parser_env_t * parser_env = this -> pscript_env -> parser_env; 
  { 
    // RL: Tokens 
    const int token_menu = pscript_token__master_push_cstr(token_env, "menu"); 
    const int token_item = pscript_token__syntax_keyword_push_cstr(token_env, "item"); 
    
    // RL: Non-terminal 
    const int node__item_arg_list__tail  = pscript_parser__custom_syntax__node_push(parser_env); 
    const int node__item_arg_list__head  = pscript_parser__custom_syntax__node_push(parser_env); 
    const int node__item_content         = pscript_parser__custom_syntax__node_push(parser_env); 
    const int node__item_list            = pscript_parser__custom_syntax__node_push(parser_env); 
    const int node__menu2                = pscript_parser__custom_syntax__node_push(parser_env); 
    const int node__menu                 = pscript_parser__custom_syntax__node_push(parser_env); 
    
    // RL: Syntax rules 
    const int rule__item_arg_list__tail2 = pscript_parser__custom_syntax__rule_push_array(parser_env, node__item_arg_list__tail, PSCRIPT_TOKEN_COMMA, 0, node__item_arg_list__tail); 
    const int rule__item_arg_list__tail1 = pscript_parser__custom_syntax__rule_push_array(parser_env, node__item_arg_list__tail); 
    const int rule__item_arg_list__head  = pscript_parser__custom_syntax__rule_push_array(parser_env, node__item_arg_list__head, 0, node__item_arg_list__tail); 
    const int rule__item_content__cons   = pscript_parser__custom_syntax__rule_push_array(parser_env, node__item_content, PSCRIPT_TOKEN_OPENPAR, node__item_arg_list__head, PSCRIPT_TOKEN_CLOSEPAR); 
    const int rule__item_list__cons2     = pscript_parser__custom_syntax__rule_push_array(parser_env, node__item_list, token_item, node__item_content, PSCRIPT_TOKEN_PTVIRG, node__item_list); 
    const int rule__item_list__cons1     = pscript_parser__custom_syntax__rule_push_array(parser_env, node__item_list); 
    const int rule__menu2__cons1         = pscript_parser__custom_syntax__rule_push_array(parser_env, node__menu2, 0, PSCRIPT_TOKEN_BEGIN, node__item_list, PSCRIPT_TOKEN_END); 
    const int rule__menu__cons1          = pscript_parser__custom_syntax__rule_push_array(parser_env, node__menu, token_menu, node__menu2); 
    
    // RL: Tree building 
    pscript_parser__custom_syntax__tree_set__array(parser_env, rule__item_arg_list__tail2, PSCRIPT_EXPR_TREE__TYPE__COMMA_LIST, 1, 2); 
    pscript_parser__custom_syntax__tree_set__array(parser_env, rule__item_arg_list__tail1, 0); 
    pscript_parser__custom_syntax__tree_set__array(parser_env, rule__item_arg_list__head , PSCRIPT_EXPR_TREE__TYPE__COMMA_LIST, 0, 1); 
    pscript_parser__custom_syntax__tree_set__array(parser_env, rule__item_content__cons  , 0, 1); 
    pscript_parser__custom_syntax__tree_set__array(parser_env, rule__item_list__cons2    , PSCRIPT_EXPR_TREE__TYPE__COMMA_LIST, 1, 3); 
    pscript_parser__custom_syntax__tree_set__array(parser_env, rule__item_list__cons1    , 0, -1); 
    pscript_parser__custom_syntax__tree_set__array(parser_env, rule__menu2__cons1        , PSCRIPT_EXPR_TREE__TYPE__COMMA_LIST, 0, 2); 
    pscript_parser__custom_syntax__tree_set__array(parser_env, rule__menu__cons1         , PSCRIPT_EXPR_TREE__TYPE__FUNCALL,    0, 1); 
    
    // RL: LL(1) key 
    pscript_parser__custom_syntax__master_root_set(parser_env, token_menu, rule__menu__cons1); 
  }; 

  return 0; 
}; 
#else 
int CPascal__link_menu(CPascal * this) { 
  this -> pscript_env -> menu_set(this -> pscript_env, /* menu_data */ NULL, /* async? */ true, CPascal__menu_callback); 
  return 0; 
}; 
#endif 








int CPascal__link_methods(CPascal * this) {
#if 0 
  { 
    const int ffiproc_name = pscript_string__push(this -> pscript_env -> string_env, "setposition"); 
    const int ffiproc_i = pscript_ffiproc__push(this -> pscript_env -> ffiproc_env, ffiproc_name, /* retval_sizeof */0, this, CPascal__method_callback__CBonhomme_setposition); 
    
    const int type_name = pscript_string__push(this -> pscript_env -> string_env, "CBonhomme"); 
    const int type_name_i = pscript_type__name__lookup(this -> pscript_env -> type_env, type_name); 
    const int type_i = pscript_type__name__get_value(this -> pscript_env -> type_env, type_name_i); 
    const int method_i = pscript_type__methode__push_ffiproc(this -> pscript_env -> type_env, type_i, ffiproc_name, ffiproc_i); 
    
    pscript_ffiproc__set_method_of(this -> pscript_env -> ffiproc_env, ffiproc_i, method_i); 
  }; 
#endif 

  
#define LINK_METHOD(__object_type__,__meth_name__,__callback_fun__)	\
  {									\
    const int ffiproc_name_pstr = pscript_string__push(this -> pscript_env -> string_env, __meth_name__); \
    const int ffiproc_i         = pscript_ffiproc__push(this -> pscript_env -> ffiproc_env, ffiproc_name_pstr, /*arg_atleast*/-1,/*retval_type*/0, /*callback_data*/this, /*ffiproc_callback*/__callback_fun__); \
									\
    const int type_name_pstr = pscript_string__push               (this -> pscript_env -> string_env, __object_type__); \
    const int type_name_i    = pscript_type__name__lookup         (this -> pscript_env -> type_env, type_name_pstr); \
    const int type_i         = pscript_type__name__get_value      (this -> pscript_env -> type_env, type_name_i); \
    const int method_i       = pscript_type__methode__push_ffiproc(this -> pscript_env -> type_env, type_i, ffiproc_name_pstr, ffiproc_i); \
									\
    pscript_ffiproc__set_method_of(this -> pscript_env -> ffiproc_env, ffiproc_i, method_i); \
  }; 
  
  //LINK_METHOD("CBonhomme","setpositionz", ???); 
  //LINK_METHOD("CBonhomme","setz",SCRIPT_SetZ); 
  LINK_METHOD("CBonhomme","SetPosition"   ,CPascal__method_callback__CBonhomme_setposition   ); 
  LINK_METHOD("CBonhomme","setz"          ,CPascal__method_callback__CBonhomme_setz          ); 
  LINK_METHOD("CBonhomme","setpositionz"  ,CPascal__method_callback__CBonhomme_setpositionz  ); 
  LINK_METHOD("CBonhomme","deplacer"      ,CPascal__method_callback__CBonhomme_deplacer      ); 
  LINK_METHOD("CBonhomme","SupprimerObjet",CPascal__method_callback__CBonhomme_SupprimerObjet); 
  LINK_METHOD("CBonhomme","Frapper"       ,CPascal__method_callback__CBonhomme_Frapper       ); 
  LINK_METHOD("CBonhomme","SetDirection"  ,CPascal__method_callback__CBonhomme_SetDirection  ); 
  LINK_METHOD("CBonhomme","SetOrientation",CPascal__method_callback__CBonhomme_SetDirection  ); 

  LINK_METHOD("CObjNonAnime","SetPosition"   ,CPascal__method_callback__CObjNonAnime_setposition); 
  
  LINK_METHOD("CCamera","SetPosition"     ,CPascal__method_callback__CCamera_SetPosition     ); 
  LINK_METHOD("CCamera","Rotate"          ,CPascal__method_callback__CCamera_Rotate          ); 
  LINK_METHOD("CCamera","Zoom"            ,CPascal__method_callback__CCamera_Zoom            ); 
  LINK_METHOD("CCamera","Defaut"          ,CPascal__method_callback__CCamera_Defaut          ); 
  LINK_METHOD("CCamera","Solidariser"     ,CPascal__method_callback__CCamera_Solidariser     ); 
  LINK_METHOD("CCamera","DeSolidariser"   ,CPascal__method_callback__CCamera_DeSolidariser   ); 
  
  LINK_METHOD("CMouton1","WaitFor"        ,CPascal__method_callback__CMouton1_WaitFor        ); 
  LINK_METHOD("CMouton1","Wait"           ,CPascal__method_callback__CMouton1_Wait           ); 
  LINK_METHOD("CMouton1","Musique"        ,CPascal__method_callback__CMouton1_Musique        ); 
  LINK_METHOD("CMouton1","AjouterAnime"   ,CPascal__method_callback__CMouton1_AjouterAnime   ); 
  LINK_METHOD("CMouton1","AjouterNonAnime",CPascal__method_callback__CMouton1_AjouterNonAnime); 
  LINK_METHOD("CMouton1","SetTemps"       ,CPascal__method_callback__CMouton1_SetTemps       ); 
  LINK_METHOD("CMouton1","BloquerTemps"   ,CPascal__method_callback__CMouton1_BloquerTemps   ); 
  LINK_METHOD("CMouton1","DebloquerTemps" ,CPascal__method_callback__CMouton1_DebloquerTemps ); 
  LINK_METHOD("CMouton1","carte"          ,CPascal__method_callback__CMouton1_carte          ); 
  
  return 0; 
}; 




int CPascal__link_ffiprocs(CPascal * this) {
#if 0  
  const int ffiproc_name = pscript_string__push(this -> string_env, "writeln"); 
  const int ffiproc_i = pscript_ffiproc__push(this -> ffiproc_env, ffiproc_name, 0, pscript_ffiproc_callback__writeln); 
  pscript_env__push_ffi(this -> env, ffiproc_name, ffiproc_i); 
#endif 

  
#define LINK_FFIPROC(__ffiproc_name__,__callback_fun__)			\
  {									\
    const int ffiproc_name_pstr = pscript_string__push (this -> pscript_env -> string_env, __ffiproc_name__); \
    const int ffiproc_i         = pscript_ffiproc__push(this -> pscript_env -> ffiproc_env, ffiproc_name_pstr, /*arg_atleast*/-1, /*retval_type*/0, /*callback_data*/this, /*ffiproc_callback*/__callback_fun__); \
    pscript_env__push_ffi(this -> pscript_env -> env, ffiproc_name_pstr, ffiproc_i); \
  }; 
  
  LINK_FFIPROC("WaitFor"        ,CPascal__ffiproc_callback__WaitFor        ); 
  LINK_FFIPROC("Wait"           ,CPascal__ffiproc_callback__Wait           ); 
  LINK_FFIPROC("Musique"        ,CPascal__ffiproc_callback__Musique        ); 
  LINK_FFIPROC("AjouterAnime"   ,CPascal__ffiproc_callback__AjouterAnime   ); 
  LINK_FFIPROC("AjouterNonAnime",CPascal__ffiproc_callback__AjouterNonAnime); 
  LINK_FFIPROC("SetTemps"       ,CPascal__ffiproc_callback__SetTemps       ); 
  LINK_FFIPROC("BloquerTemps"   ,CPascal__ffiproc_callback__BloquerTemps   ); 
  LINK_FFIPROC("DebloquerTemps" ,CPascal__ffiproc_callback__DebloquerTemps ); 
  LINK_FFIPROC("carte"          ,CPascal__ffiproc_callback__carte          ); 
  LINK_FFIPROC("Readln"         ,CPascal__ffiproc_callback__Readln         ); 
  LINK_FFIPROC("Menu"           ,CPascal__ffiproc_callback__Menu           ); 
  
  
  // RL: Setting arg[0] type for 'Readln'. 
  { 
    const int ffiproc_name_pstr = pscript_string__lookup (this -> pscript_env ->  string_env, "Readln"); 
    const int ffiproc_i         = pscript_ffiproc__lookup(this -> pscript_env -> ffiproc_env, ffiproc_name_pstr); 
    assert(ffiproc_i >= 0); 
    const int arg_name_pstr = pscript_string__push(this -> pscript_env -> string_env, "arg0"); 
    const int arg_i         = pscript_ffiproc__set_arg_push(this -> pscript_env -> ffiproc_env, ffiproc_i, /*arg_name*/arg_name_pstr, /*byref_huh*/true, /*arg_type*/pscript_type__get__any(this -> pscript_env -> type_env)); 
    //messerr("%s: " "ffiproc_i: %d - arg_name [ %d ] - arg_i = %d " "\n", __func__, ffiproc_i, arg_name, arg_i);
  }; 
  
  return 0; 
}; 


int CPascal__init_file(CPascal * this) {
  int allright_huh = PSCRIPT_VM__ERROR__HALT; 
  const int mainproc_nb = pscript_mainproc__get_count(this -> pscript_env -> mainproc_env); 
  for (int i = 0; i < mainproc_nb; i++) { 
    const int offset = pscript_mainproc__get_bytecode_offset(this -> pscript_env -> mainproc_env, i); 
    allright_huh = this -> pscript_env -> vm -> run(this -> pscript_env -> vm, offset); 
    if (allright_huh == PSCRIPT_VM__ERROR__HALT) { continue; }; 
    this -> pscript_env -> vm -> print_error(this -> pscript_env -> vm, allright_huh);
    break; 
  }; 
  return (allright_huh == PSCRIPT_VM__ERROR__HALT); 
}; 









void CPascal__delete(CPascal * this) { 
  CPascal_dico__release(this -> dico_i); 
}; 

static CPascal * CPascal__copy(const CPascal * this) { 
  return CPascal_dico__get(this -> dico_i); 
}; 

static void CPascal__delete_hard(CPascal * this) {
  // Il faut fermer les flux de message d'erreur,
  // et détruire l'environnement,
  // et détruire la mémoire.
  
  if (this -> pscript_env != NULL) { 
    //close(this -> pscript_env -> stdlog__get__fdes(this -> pscript_env)); 
    close(this -> pscript_env -> stdlog_d); 
    pscript_delete(this -> pscript_env); 
  }; 
  
  if (this -> filename != NULL) {
    free(this -> filename); 
  }; 
  
  free(this); 
}; 



#if 1
CPascal * CPascal__make_with_file(const char * filename) { 
  int allright_huh; 
  const int lookedup_index = CPascal_dico__lookup(filename); 
  if (lookedup_index >= 0) { return CPascal_dico__get(lookedup_index); }; 
  
  CPascal * this = NULL; 
  this = CPascal__make_empty(); 
  this -> pscript_env = pscript_make(); 
  this -> link_writeln(this); 
  this -> link_menu(this); 
  this -> link_ffiprocs(this); 
  allright_huh = this -> read_file_no_init(this, filename); assert(allright_huh); 
  this -> link_methods(this); 
  allright_huh = this -> init_file(this); assert(allright_huh); 
  
  this -> dico_i = CPascal_dico__push(filename, this); 
  return this; 
}; 
#else 
CPascal * CPascal__make_with_file(const char * filename) { 
  const int lookedup_index = CPascal_dico__lookup(filename); 
  if (lookedup_index >= 0) { return CPascal_dico__get(lookedup_index); }; 
  
  CPascal * this = NULL; 
  this = CPascal__make_empty(); 
  this -> pscript_env = pscript_make(); 
  this -> link_writeln(this); 
  this -> link_menu(this); 
  this -> link_ffiprocs(this); 
  this -> read_file_no_init(this, filename); 
  this -> link_methods(this); 
  this -> init_file(this); 

  this -> dico_i = CPascal_dico__push(filename, this); 
  return this; 
}; 
#endif 










int CPascal__execProcedure(CPascal * this, const char * ident_cstr) { 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " this = %p - ident_cstr = %p "   "\n", __func__, this, ident_cstr); 
  do { 
    const int ident_pstr = pscript_string__push(this -> pscript_env -> string_env, ident_cstr); 
    const int env_i      = pscript_env__lookup (this -> pscript_env -> env,        ident_pstr); 
    if (env_i < 0) { 
      messerr("%s: Could not find any item named '%s'." "\n", __func__, ident_cstr); 
      return -1; 
    }; 
    
    const int env_type  = pscript_env__get_type (this -> pscript_env -> env, env_i); 
    const int env_value = pscript_env__get_value(this -> pscript_env -> env, env_i); 
    if ((PSCRIPT_ENV__FUNPROC == env_type) || (PSCRIPT_ENV__FFIPROC == env_type)) { 
      const int funproc_i = env_value; 
      const int arg_nb    = pscript_funproc__get_arg_nb(this -> pscript_env -> funproc_env, funproc_i); 
      if (0 != arg_nb) { 
	messerr("%s: The function '%s' requires %d arguments, while we do not provide any." "\n", __func__, ident_cstr, arg_nb); 
	return -3; 
      }; 
      const int funproc_offset  = pscript_funproc__get_offset(this -> pscript_env -> funproc_env, funproc_i); 
      const int ret_address     = this -> pscript_env -> libproc_env -> halt_offset; 
      //const int base_mem_offset = pscript_mem__get_base_offset(this -> pscript_env -> mem_env); 
      const int caller_ebp      = pscript_vm__memory_frame__get(this -> pscript_env -> vm); 
      //pscript_vm__call_stack__push(this -> pscript_env -> vm, ret_address, arg_nb, base_mem_offset); 
      const int on_stack_arg_nb = 0; //BYTECODE_READ_ARG(int8_t); //bytecode_env -> bytecode_array[ipc0 + 1]; 
      pscript_vm__call_stack__push(this -> pscript_env -> vm, ret_address, on_stack_arg_nb, caller_ebp); 
      
      const int allright_huh = this -> pscript_env -> vm -> run(this -> pscript_env -> vm, funproc_offset); 
      if (allright_huh != PSCRIPT_VM__ERROR__HALT) { 
	this -> pscript_env -> vm -> print_error(this -> pscript_env -> vm, allright_huh);
	return allright_huh; 
      }; 
      
      const int retval_sizeof = pscript_funproc__get_retval_sizeof(this -> pscript_env -> funproc_env, funproc_i); 
      if (retval_sizeof > 0) {
	pscript_stack__drop(this -> pscript_env -> stack_env); 
      }; 
    } 
    else { 
      const char * env_type_cstr = pscript_env__type__get_cstr(this -> pscript_env -> env, env_type); 
      messerr("%s: The variable '%s' is not a function (but a %s)." "\n", __func__, ident_cstr, env_type_cstr); 
      return -2; 
    }; 
  } while (false); 
  return 0; 
}; 
 
 
int CPascal__execProcedure_step(CPascal * this, const char * ident_cstr) { 
  message("%s" "\n", __func__); 
  do { 
    const int ident_pstr = pscript_string__push(this -> pscript_env -> string_env, ident_cstr); 
    const int env_i      = pscript_env__lookup (this -> pscript_env -> env       , ident_pstr); 
    if (env_i < 0) { 
      messerr("%s: Could not find any item named '%s'." "\n", __func__, ident_cstr); 
      return -1; 
    }; 
    
    const int env_type  = pscript_env__get_type (this -> pscript_env -> env, env_i); 
    const int env_value = pscript_env__get_value(this -> pscript_env -> env, env_i); 
    if ((PSCRIPT_ENV__FUNPROC == env_type) || (PSCRIPT_ENV__FFIPROC == env_type)) { 
      const int funproc_i = env_value; 
      const int arg_nb    = pscript_funproc__get_arg_nb(this -> pscript_env -> funproc_env, funproc_i); 
      if (0 != arg_nb) { 
	messerr("%s: The function '%s' requires %d arguments, while we do not provide any." "\n", __func__, ident_cstr, arg_nb); 
	return -3; 
      }; 
      const int funproc_offset  = pscript_funproc__get_offset(this -> pscript_env -> funproc_env, funproc_i); 
      const int ret_address     = this -> pscript_env -> libproc_env -> halt_offset; 
      //const int base_mem_offset = pscript_mem__get_base_offset(this -> pscript_env -> mem_env); 
      const int caller_ebp      = pscript_vm__memory_frame__get(this -> pscript_env -> vm); 
      //pscript_vm__call_stack__push(this -> pscript_env -> vm, ret_address, arg_nb, base_mem_offset); 
      const int on_stack_arg_nb = 0; //BYTECODE_READ_ARG(int8_t); //bytecode_env -> bytecode_array[ipc0 + 1]; 
      pscript_vm__call_stack__push(this -> pscript_env -> vm, ret_address, on_stack_arg_nb, caller_ebp); 
      
      this -> funproc_i = funproc_i; 
      this -> next_ipc0 = this -> pscript_env -> vm -> step(this -> pscript_env -> vm, funproc_offset); 
    } 
    else { 
      const char * env_type_cstr = pscript_env__type__get_cstr(this -> pscript_env -> env, env_type); 
      messerr("%s: The variable '%s' is not a function (but a %s)." "\n", __func__, ident_cstr, env_type_cstr); 
      return -2; 
    }; 
  } while (false); 
  return 0; 
}; 


int CPascal__next_step(CPascal * this, bool * fini_huh_ref) {
  //message("%s" "\n", __func__); 
  if (this -> next_ipc0 == PSCRIPT_VM__ERROR__HALT) { 
    *fini_huh_ref = true;
    const int retval_sizeof = pscript_funproc__get_retval_sizeof(this -> pscript_env -> funproc_env, this -> funproc_i); 
    if (retval_sizeof > 0) {
      pscript_stack__drop(this -> pscript_env -> stack_env); 
    }; 
    return 0; 
  }; 
  
  if (this -> next_ipc0 < 0) { 
    *fini_huh_ref = true; 
    this -> pscript_env -> vm -> print_error(this -> pscript_env -> vm, this -> next_ipc0);
    return this -> next_ipc0; 
  }; 
  
  *fini_huh_ref = false; 
  this -> next_ipc0 = this -> pscript_env -> vm -> step(this -> pscript_env -> vm, this -> next_ipc0); 
  return 0; 
}; 

int CPascal__busy_huh(const CPascal * this) { 
  if (this -> next_ipc0 == PSCRIPT_VM__ERROR__HALT) { 
    return false; 
  }; 
  if (this -> next_ipc0 < 0) { 
    return false; 
  }; 
  return true; 
}; 




void CPascal__stack_push_int(CPascal * this, int a) { 
  assert(false); 
}; 
 
void CPascal__stack_push_string(CPascal * this, const char * cstr) { 
  assert(false); 
#if 0 
  const int pstr = pscript_string__push(this -> pscript_env -> string_env, cstr); 
  pscript_stack__push_value(this -> pscript_env -> stack_env, pscript_type__get__string(this -> pscript_env -> type_env), sizeof(pstr), (const char *) &pstr); 
#endif 
}; 
 


