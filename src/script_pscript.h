#ifndef CPASCAL_H
#define CPASCAL_H

#include "pscript/pscript.h"

struct CPascal {
  char * filename; 
  int dico_i; 
  
  pscript_t * pscript_env; 
  
  int funproc_i; // RL: The function currently being run; -1 is none. 
  int next_ipc0; 
  
  
  // RL: These are temporary data for 'readln'. 
#if 1 
  int    readln__arg_nb; 
  char   readln__arg_type[pscript_ffiproc__arg__size]; 
  int    readln__arg_sizeof[pscript_ffiproc__arg__size]; 
  int    readln__arg_offset[pscript_ffiproc__arg__size]; 
  int    readln__arg_mem_size; 
  char * readln__arg_mem; 
  int    readln__retval_allocated_size; 
  char * readln__retval_value; 
#else   
  int          readln__arg_nb; 
  const char * readln__arg_type; 
  const int  * readln__arg_sizeof; 
  const int  * readln__arg_offset; 
  int          readln__arg_mem_size; 
  const char * readln__arg_mem; 
  int          readln__retval_allocated_size; 
  char *       readln__retval_value; 
#endif 
  
  
  
  // *** METHODS *** 
  
  CPascal * (* make_empty)(void); 
  CPascal * (* make_with_file)(const char * filename); 
  void (* delete)(CPascal * this);
  int (* read_file_no_init)(CPascal * this, const char * filename); 
  int (* link_writeln)(CPascal * this); 
  int (* link_menu)(CPascal * this); 
  int (* link_methods)(CPascal * this); 
  int (* link_ffiprocs)(CPascal * this); 
  int (* init_file)(CPascal * this); 
  
  int (* execProcedure     )(CPascal * this, const char * ident); 
  int (* execProcedure_step)(CPascal * this, const char * ident); 
  int (* next_step         )(CPascal * this, bool * fini_huh); 
  int (* busy_huh          )(const CPascal * this);

  void (* stack_push_int   )(CPascal * this, const int a); 
  void (* stack_push_string)(CPascal * this, const char * cstr); 
#if 0   
#endif 
}; 

extern CPascal * CPascal__make_empty(void); 
extern CPascal * CPascal__make_with_file(const char * filename); 
#define CPascal__make CPascal__make_with_file 
#define CPascal_make CPascal__make 
extern void CPascal__delete(CPascal * this); 
#define CPascal_delete CPascal__delete 
extern int CPascal__read_file_no_init(CPascal * this, const char * filename); 
extern int CPascal__link_writeln(CPascal * this);
extern int CPascal__link_menu(CPascal * this);
extern int CPascal__link_methods(CPascal * this);
extern int CPascal__link_ffiprocs(CPascal * this);
extern int CPascal__init_file(CPascal * this);

extern int CPascal__execProcedure(CPascal * this, const char * ident);
extern int CPascal__execProcedure_step(CPascal * this, const char * ident);
extern int CPascal__next_step(CPascal * this, bool * fini_huh);
extern int CPascal__busy_huh(const CPascal * this);

extern void CPascal__stack_push_int(CPascal * this, int a);
extern void CPascal__stack_push_string(CPascal * this, const char * cstr);

extern int CPascal__ffiproc_callback__Readln__async_reverse_callback__push_return_value(CPascal * this, const char * readln_cstr); 
extern int CPascal__ffiproc_callback__Menu__async_reverse_callback__push_return_value(CPascal * this, const int choice); 



#endif /* CPASCAL_H */
