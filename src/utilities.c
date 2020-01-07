#include "global.h"
#include "utilities.h"



#ifdef LIBPROG_ENDIAN_BIG

#define _r32mask 0xff000000
#define _g32mask 0x00ff0000
#define _b32mask 0x0000ff00
#define _a32mask 0x000000ff

#define _r24mask 0x00ff0000
#define _g24mask 0x0000ff00
#define _b24mask 0x000000ff
#define _a24mask 0x00000000

#else

#define _r32mask 0x000000ff
#define _g32mask 0x0000ff00
#define _b32mask 0x00ff0000
#define _a32mask 0xff000000

#define _r24mask 0x000000ff
#define _g24mask 0x0000ff00
#define _b24mask 0x00ff0000
#define _a24mask 0x00000000

#endif

const Uint32 r32mask = _r32mask;
const Uint32 g32mask = _g32mask; 
const Uint32 b32mask = _b32mask; 
const Uint32 a32mask = _a32mask; 

const Uint32 r24mask = _r24mask; 
const Uint32 g24mask = _g24mask; 
const Uint32 b24mask = _b24mask; 
const Uint32 a24mask = _a24mask; 




#if 0
typedef struct {
  SDL_Palette *palette;
  Uint8  BitsPerPixel;
  Uint8  BytesPerPixel;
  Uint8  Rloss, Gloss, Bloss, Aloss;
  Uint8  Rshift, Gshift, Bshift, Ashift;
  Uint32 Rmask, Gmask, Bmask, Amask;
  Uint32 colorkey;
  Uint8  alpha;
} SDL_PixelFormat;
#endif

SDL_PixelFormat sdl_pixel_format_rgb = {
  NULL,
  24,
  3,
  0, // Loss
  0,
  0,
  8,
  16, // Shift
  8,
  0,
  0,
  _r24mask,
  _g24mask,
  _b24mask,
  _a24mask,
  // champs qui ont disparu dans les versions avancées de SDL (la 1.3.0 en l'occurrence)
  0, // colorkey
  255 // alpha
};

SDL_PixelFormat sdl_pixel_format_rgba = {
  NULL,
  32,
  4,
  0, // Loss
  0,
  0,
  0,
  24, // Shift
  16,
  8,
  0,
  _r32mask,
  _g32mask,
  _b32mask,
  _a32mask,
  0,
  255
};


#if 0
char * strcopy(const char * str) {
  if (str == NULL) { return NULL; }; 
  const size_t len = strlen(str); 
  char * temp = (char *) malloc(sizeof(char) * (len+1));
  return strcpy(temp, str);
}; 
#endif 



// Fonction de conversion du format de caractère ANSI to OEM.
// Utilie car notre font est en OEM.
static const unsigned char table_ansi2oem[256] = {
  0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
  0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
  0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
  0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x000,0x0AD,0x09B,0x09C,0x000,0x09D,0x000,0x000,0x000,0x000,0x000,0x0AE,0x0AA,0x0A9,0x000,0x000,0x0F8,0x0F1,0x0FD,0x000,0x000,0x0E6,0x014,0x000,0x000,0x000,0x0F8,0x0AF,0x0AC,0x0AB,0x000,0x0A8,
  0x041,0x041,0x041,0x041,0x08E,0x08F,0x092,0x080,0x045,0x090,0x045,0x045,0x049,0x049,0x049,0x049,0x044,0x0A5,0x04F,0x04F,0x04F,0x04F,0x099,0x078,0x0ED,0x055,0x055,0x055,0x09A,0x059,0x000,0x0E1,
  0x85,0x0A0,0x083,0x061,0x084,0x086,0x091,0x087,0x08A,0x082,0x088,0x089,0x08D,0x0A1,0x08C,0x08B,0x000,0x0A4,0x095,0x0A2,0x093,0x06F,0x094,0x0F6,0x0ED,0x097,0x0A3,0x096,0x075,0x079,0x000,0x098
};

static const unsigned char table_oem2ansi[256] = {
  0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
  0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x2F,
  0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
  0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
  0x0C7,0x0FC,0x0E9,0x0E2,0x0E4,0x0E0,0x0E5,0x0E7,0x0EA,0x0EB,0x0E8,0x0EF,0x0EE,0x0EC,0x0C4,0x0C5,0x0C9,0x0E6,0x0C6,0x0F4,0x0F6,0x0F2,0x0FB,0x0F9,0x0FF,0x0D6,0x0DC,0x0A2,0x0A3,0x0A5,0x09E,0x9F,
  0x0E1,0x0ED,0x0F3,0x0FA,0x0F1,0x0D1,0x000,0x000,0x0BF,0x0AD,0x0AC,0x0BD,0x0BC,0x0A1,0x0AB,0x0BB,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x0DF,0x00,0x00,0x00,0x00,0x0B5,0x00,0x00,0x00,0x00,0x00,0x00,0x0F8,0x00,0x00,0x00,0x0B1,0x00,0x00,0x00,0x00,0x0F7,0x00,0x0F8,0x00,0x00,0x00,0x00,0x0B2,0x00,0x00
};



static inline char * factorize_oem(const unsigned char tab[], const char * str);
char * factorize_oem(const unsigned char tab[], const char * str_) {
  if (str_ == NULL) { return NULL; }; 
  
  const unsigned char * str = str_;     
  const size_t len = strlen(str); 
  unsigned char * temp = (unsigned char *) malloc(sizeof(unsigned char) * (len+1));

  for (size_t i = 0; i < len; i++) {
    temp[i] = tab[str[i]];
  }; 
  temp[len] = '\0';

  return temp;
};

char * ansi2oem(const char * str) {
  return factorize_oem(table_ansi2oem, str);
};

char * oem2ansi(const char *str) {
  return factorize_oem(table_oem2ansi, str);
};

