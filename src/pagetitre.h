#ifndef CPageTitre_H 
#define CPageTitre_H 

struct CPageTitre; 

enum {              CPageTitre_bytesize = 96 }; 
extern const int8_t CPageTitre_bytesize_actual; 
static void CPageTitre__check_and_assert(const int8_t debug_print_huh, const int stderr_d) { 
  if (debug_print_huh) { 
    //fprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "I failed to clean up the log subdir.' " "\n", __func__); 
    write_string4(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<", __func__, "()>}: ", "CPageTitre_bytesize: "); write_long_long_int(stderr_d, CPageTitre_bytesize); write_eol(stderr_d); 
    write_string4(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<", __func__, "()>}: ", "CPageTitre_bytesize_actual: "); write_long_long_int(stderr_d, CPageTitre_bytesize_actual); write_eol(stderr_d); 
  }; 
  assert(CPageTitre_bytesize >= CPageTitre_bytesize_actual); 
}; 

enum { 
  PageTitre_UserToldMe_NothingYet, 
  PageTitre_UserToldMe_Bye, 
  PageTitre_UserToldMe_QuickGame, 
  PageTitre_UserToldMe_NewGame, 
  PageTitre_UserToldMe_LoadGame, 
}; 

extern CPageTitre * CPageTitre_make(void);
extern void         CPageTitre_delete(CPageTitre * this);
extern void         CPageTitre__Render(const CPageTitre * this);
extern void         CPageTitre__Life(CPageTitre * this);
extern int          CPageTitre__Input(CPageTitre * this);





























#if 0 

static int a[sizeof(enum TPageTitreAction) == 4 ? 1 : -1] = { 0 }; // RL: This is true. So clang compiles it as an 'int', as it should. 

#endif 
















#if 0 

//RL: Too bad that there's no simple way of having class methods (or attributes). 

struct CPageTitre_method_t { 
  void (* Render)(const struct CPageTitre * this); 
  void (* Life)(struct CPageTitre * this); 
  int  (* Input)(struct CPageTitre * this); 
}; 

static const struct CPageTitre_method_t CPageTitre_method = { 
&CPageTitre__Render,
&CPageTitre__Life,
&CPageTitre__Input
}; 

enum { CPageTitre__Render__Offset = 0 }; 
enum { CPageTitre__Life__Offset = sizeof(void*) }; 
enum { CPageTitre__Input__Offset = 2*sizeof(void*) }; 

#define CALL_METHOD(this,method_ident,...) 

#endif 

#endif /* CPageTitre_H */ 
