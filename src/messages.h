#ifndef MESSAGES_HPP
#define MESSAGES_HPP


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
#define message(...)							\
  if (!zeldafnotice) fprintf(zeldafnotice, __FILE__ ": " BIGLIB_STRING(__LINE__) ": " BIGLIB_STRING(__func__) ": " __VA_ARGS__); \
  fprintf                   (stdout_FILE,  __FILE__ ": " BIGLIB_STRING(__LINE__) ": " BIGLIB_STRING(__func__) ": " __VA_ARGS__); \
  //putc('\n', yycarteout); 
#define messerr(...)							\
  if (!zeldafnotice) fprintf(zeldafnotice, "ERREUR: " __FILE__ ": " BIGLIB_STRING(__LINE__) ": " BIGLIB_STRING(__func__) ": " __VA_ARGS__); \
  if (!zeldaferror)  fprintf(zeldaferror,  "ERREUR: " __FILE__ ": " BIGLIB_STRING(__LINE__) ": " BIGLIB_STRING(__func__) ": " __VA_ARGS__); \
  fprintf                   (stdout_FILE,  "ERREUR: " __FILE__ ": " BIGLIB_STRING(__LINE__) ": " BIGLIB_STRING(__func__) ": " __VA_ARGS__); \
  fprintf                   (stderr_FILE,  "ERREUR: " __FILE__ ": " BIGLIB_STRING(__LINE__) ": " BIGLIB_STRING(__func__) ": " __VA_ARGS__); \
  //putc('\n', yycarteout); 


//extern void vmessage(const char * mess, va_list args);
//extern void vmesserr(const char * mess, va_list args);

extern void init_message(void);
extern void end_message(void);

#endif /* MESSAGES_HPP */
