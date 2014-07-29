#ifndef MESSAGES_HPP
#define MESSAGES_HPP


#ifdef __GNUC__
#define MESSAGE_FORMAT_ATTRIBUT __attribute__ ((format (printf, 1, 2)))
#else
#define MESSAGE_FORMAT_ATTRIBUT 
#endif


extern void message(const char * mess, ...) MESSAGE_FORMAT_ATTRIBUT;
extern void messerr(const char * mess, ...) MESSAGE_FORMAT_ATTRIBUT;

extern void vmessage(const char * mess, va_list args);
extern void vmesserr(const char * mess, va_list args);

extern void init_message(void);
extern void end_message(void);

#endif /* MESSAGES_HPP */
