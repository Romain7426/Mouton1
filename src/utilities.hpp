#ifndef UTILITIES_HPP
#define UTILITIES_HPP

//#include "global.hpp"

#define RGBA(r,v,b,a) (((a * 256 + v) * 256 + b) * 256 + r)
#define sqr(a) ((a)*(a))

#define STRING(s) STRINGX(s)
#define STRINGX(s) #s

#ifndef _WIN32
// Sous Windows, ces fonctions sont définies dans windef.h
// Je ne sais pas où sont défénies ces fonctions, mais il y en a besoin dans text.cpp
//Sous windows, ça met des warnings
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) < (b) ? (b) : (a))
#endif 


extern char * strcopy(const char *str);
extern char * ansi2oem(const char *str);
extern char * oem2ansi(const char *str);


extern SDL_PixelFormat sdl_pixel_format_rgb;
extern SDL_PixelFormat sdl_pixel_format_rgba;

#define GDB_BREAK ((*((int *) NULL)) = 0)

#endif /* UTILITIES_HPP */
