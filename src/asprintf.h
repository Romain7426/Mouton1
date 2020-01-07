#ifndef ASPRINTF_H
#define ASPRINTF_H

#ifdef WIN

#include <stdarg.h>

extern int asprintf(char * * strp, const char * format, ...);

extern int vasprintf(char * * strp, const char * format, va_list args);   


#endif /* ELSE WIN */


#endif /* ASPRINTF_H */
