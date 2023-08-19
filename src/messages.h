#ifndef MESSAGES_H
#define MESSAGES_H


#if 1

#define messlog(...) { 							\
    const char   __file__[]   = "" __FILE__ "";				\
    const char * __function__ = __func__;				\
    const int    __line__     = __LINE__;				\
    { fprintf(stdout, "{" __FILE__ ": " BIGLIB_STRING(__LINE__) ":<%s>}: ", __func__); fprintf(stdout, __VA_ARGS__); }; \
  }; 

#define messerr(...) {							\
    { fprintf(stderr , "ERREUR: {" __FILE__ ": " BIGLIB_STRING(__LINE__) ":<%s>}: ", __func__); fprintf(stderr , __VA_ARGS__); }; \
  }; 


#define message messlog 

//extern void message__init(void);
//extern void message__dispose(void);



#else 

#ifdef __GNUC__
#define MESSAGE_FORMAT_ATTRIBUT __attribute__ ((format (printf, 1, 2)))
#else
#define MESSAGE_FORMAT_ATTRIBUT 
#endif


extern FILE * zeldafnotice;
extern FILE * zeldaferror;
#define stdout_FILE stdout
#define stderr_FILE stderr

// Note: __func__ (C99) & __FUNCTION__ (GCC) are not macros, but constant variables. :-( 
//extern void message(const char * mess, ...) MESSAGE_FORMAT_ATTRIBUT;
//extern void messerr(const char * mess, ...) MESSAGE_FORMAT_ATTRIBUT;
#if 1 
#define message(...) { 							\
    const char   __file__[]   = "" __FILE__ "";				\
    const char * __function__ = __func__;				\
    const int    __line__     = __LINE__;				\
  { if (zeldafnotice) { fprintf(zeldafnotice, "{" __FILE__ ": " BIGLIB_STRING(__LINE__) ":<%s>}: ", __func__); fprintf(zeldafnotice, __VA_ARGS__); }; }; \
  {                   { fprintf(stdout_FILE , "{" __FILE__ ": " BIGLIB_STRING(__LINE__) ":<%s>}: ", __func__); fprintf(stdout_FILE , __VA_ARGS__); }; }; \
  }; 
#else 
#define message(...) { 							\
  { if (zeldafnotice) { fprintf(zeldafnotice, "" __FILE__ ": " BIGLIB_STRING(__LINE__) ": " BIGLIB_STRING(__func__) ": " __VA_ARGS__); }; }; \
  {                   { fprintf(stdout_FILE , "" __FILE__ ": " BIGLIB_STRING(__LINE__) ": " BIGLIB_STRING(__func__) ": " __VA_ARGS__); }; }; \
  }; 
#endif 

#define messerr(...) {							\
  { if (zeldafnotice) { fprintf(zeldafnotice, "ERREUR: {" __FILE__ ": " BIGLIB_STRING(__LINE__) ":<%s>}: ", __func__); fprintf(zeldafnotice, __VA_ARGS__); }; }; \
  { if (zeldaferror ) { fprintf(zeldaferror , "ERREUR: {" __FILE__ ": " BIGLIB_STRING(__LINE__) ":<%s>}: ", __func__); fprintf(zeldaferror , __VA_ARGS__); }; }; \
  {                   { fprintf(stdout_FILE , "ERREUR: {" __FILE__ ": " BIGLIB_STRING(__LINE__) ":<%s>}: ", __func__); fprintf(stdout_FILE , __VA_ARGS__); }; }; \
  {                   { fprintf(stderr_FILE , "ERREUR: {" __FILE__ ": " BIGLIB_STRING(__LINE__) ":<%s>}: ", __func__); fprintf(stderr_FILE , __VA_ARGS__); }; }; \
  }; 
  //putc('\n', yycarteout); 





#define messlog message

//extern void vmessage(const char * mess, va_list args);
//extern void vmesserr(const char * mess, va_list args);

extern void message__init(void);
extern void message__dispose(void);

#endif 

#endif /* MESSAGES_H */
