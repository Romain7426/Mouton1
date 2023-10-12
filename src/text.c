#include "global.h"
//#include <math.h>
#include "text.h"   

//#include "pascal/pascal.tools.hpp"
    
#define TAILLE_CHAR_PIXEL 24
#define TAILLEX_CHAR 16  
#define TAILLEY_CHAR 20                                                          

//extern char * ansi2oem(const char *str);


#ifdef SRCFILE_LATIN1 
unsigned char conversionpourrie(const unsigned char c) {
  unsigned char d; 
  if (c == 224) d = 133; //à
  if (c == 226) d = 131; //â
  if (c == 231) d = 135; //ç
  if (c == 233) d = 130; //é
  if (c == 232) d = 138; //è
  if (c == 234) d = 136; //ê    
  if (c == 238) d = 140; //î
  if (c == 244) d = 131+16; //ô
  return d;
}; 
#elif SRCFILE_UTF8 
#if 1 
unsigned char conversionpourrie_(const uint8_t c0, const uint8_t c1, int * used_ref) {
#if 0 
  messerr("conversionpourrie: c0: %d" "\n", c0); 
  messerr("conversionpourrie: c1: %d" "\n", c1); 
#endif 
  unsigned char d = c0; 
  *used_ref = 1; 
  switch (c0) {
  case '	': d = ' '; break; // TAB 
  case 195:  
    if (137 == c1) { d = 'E'; *used_ref = 2; break; };  // É 
    if (138 == c1) { d = 'E'; *used_ref = 2; break; };  // Ê 
    if (160 == c1) { d = 133; *used_ref = 2; break; };  // à 
    if (162 == c1) { d = 131; *used_ref = 2; break; };  // â 
    if (167 == c1) { d = 135; *used_ref = 2; break; };  // ç 
    if (168 == c1) { d = 138; *used_ref = 2; break; };  // è 
    if (169 == c1) { d = 130; *used_ref = 2; break; };  // é 
    if (170 == c1) { d = 136; *used_ref = 2; break; };  // ê 
    if (174 == c1) { d = 140; *used_ref = 2; break; };  // î 
    if (180 == c1) { d = 147; *used_ref = 2; break; };  // ô 
    if (185 == c1) { d = 'u'; *used_ref = 2; break; };  // ù 
    if (187 == c1) { d = 'u'; *used_ref = 2; break; };  // û 
    break;
  }; 
  return d;
}; 
#define conversionpourrie(c) conversionpourrie_((c),*((&(c))+1),&used_bytes)
#else
unsigned char conversionpourrie(const uint16_t c) {
  const unsigned char c0 = c & 0xFF; 
  const unsigned char c1 = c >> 8; 
#if 1
  messerr("conversionpourrie: c0: %d" "\n", c0); 
  messerr("conversionpourrie: c1: %d" "\n", c1); 
#endif 
  unsigned char d; 
  if (c == 224) d = 133; //à
  if (c == 226) d = 131; //â
  if (c == 231) d = 135; //ç
  if (c == 233) d = 130; //é
  if (c == 232) d = 138; //è
  if (c == 234) d = 136; //ê    
  if (c == 238) d = 140; //î
  if (c == 244) d = 131+16; //ô
  return d;
}; 
#endif 
#else 
unsigned char conversionpourrie(const unsigned char c) {
  return c; 
}; 
#endif 


#if 0 
// RL: ??? 
CText * Text;
CMessageTexte * MessageTexte;
#endif 


void glEnable2D(void) {
  // passe en mode 2D écran/pixel
  GLint vPort[4];
  
  glGetIntegerv(GL_VIEWPORT, vPort);
  
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
  
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glDisable(GL_LIGHTING);
};

void glDisable2D(void) {
  // revient au mode d'avant...(à priori 3D normal, comme d'hab)
  glEnable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
};



CText * CText_make(void) {
  MALLOC_BZERO(CText,this); 

  //assert(false); 
  ASSIGN_METHOD(CText,this,print1); 
  ASSIGN_METHOD(CText,this,print2); 

  printf("Création du moteur d'affichage de texte (chargement de l'image font.png)\n");
  this -> tex = CTexture_make("./font.png"); 
  printf("Chargement de font.png réussi\n"); 
  return this; 
}; 


void CText_delete(CText * this) {
  CTexture_delete(this -> tex);
  free(this);
};



// RL: What does it return? 
float CText__print2(CText * this, float l, const int nblignes, const int nbcaracmax, const int x, const int y, const int w, const int h, const char * c_src, bool * toutaffiche_ref) {
  int lignecourante  = 0;

#if 0
  message("CText__print: %s\n", c);
  printf("CText__print: %s\n", c);
  fflush(NULL);
  *((int*) NULL) = 1;
#endif
#if 0 
  fprintf(stderr, "CText__print: %s\n", c_src);
  fflush(NULL);
#endif 
  
  *toutaffiche_ref = true;

  if (l < 0) { l = 0; }; 
  
  assert(c_src != NULL);
  if (c_src == NULL) { return 0; }; 

  const int c_src_len = strlen(c_src); 
  char c[c_src_len+1]; 
  int c_len = 0; 
  int used_bytes = 1; 
  for (int i = 0; i < c_src_len; ) {
    c[c_len] = conversionpourrie(c_src[i]); 
    i += used_bytes; 
    c_len++; 
  }; 
  c[c_len] = '\0';
#if 0 
  for (int i = 0; i < c_len; i++) {
    write(0, c + i, 1); 
  }; 
  putc('\n', stdout); 
#elif 0 
  for (int i = 0; i < c_src_len; i++) {
    write(0, c_src + i, 1); 
  }; 
  putc('\n', stdout); 
  strcpy(c, c_src); 
#endif 

  glEnable2D(); {
    this -> cx = x;
    this -> cy = y + (int) (l*TAILLEY_CHAR);
    // this -> cx, this -> cy représentent la position courante. 
    // Au début on l'initialise via (x, y)
    // on décale également avec l (pour commencer à écrire à la ligne l 
    
    glEnable(GL_TEXTURE_2D);
    CTexture__GLTextureCourante(this -> tex);
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS); {
    
      int i = 0;
      while ((c[i] != 0) && ((lignecourante - l) < nblignes) && (i <= nbcaracmax)) {
        int j = i;
        while ((c[j] !=0 ) && (c[j] != ' ') && (c[j] != 10) && (c[j] != 13)) j++; 
	
        // de i, à j on a un mot avec le caractère ' ' ou #0 à la fin 
            
        if ((this -> cx + (j-i)*TAILLEX_CHAR >= x + w)) { 
          // si le mot dépasse du cadre, on va à la ligne 
	  this -> cx = x;
	  this -> cy-=TAILLEY_CHAR;
	  lignecourante++;
	}; 
             
        //lignecourante+1 = l : on est sur une ligne limite au début
        //lignecourante = l : c'est bon, celle là il faut l'afficher en entier
        if ((l-1<= lignecourante) && (lignecourante <= l)) 
          glColor4f(1.0f, 1.0f, 1.0f, min(1.0f, max((lignecourante+1 - l), 0.0f)));
        else if ((l+nblignes<=lignecourante ) && (lignecourante<= l + nblignes+1))
          glColor4f(1.0f, 1.0f, 1.0f, min(1.0f, max(((l+nblignes+1)-lignecourante), 0.0f)));
        else     
          glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	
        // on écrit que si on est déjà arrivé sur la ligne à écrire 
        if (l-1 <= lignecourante) {
          for (; (i < j) && (i <= nbcaracmax); i++) {
            /*on parcourt le mot sans le caractère final (' ' ou #0), et on l'écrit
              en avançant à chaque fois vers la droite*/
	    const unsigned char conversionc = conversionpourrie(c[i]); 
#if 0
	    //const unsigned char conversionc = conversionpourrie(c[i]); 
	    //const unsigned char conversionc = (c[i]); 
	    messerr("CText__print: c[i]: %c" "\n", c[i]); 
	    messerr("CText__print: conversionc: %c" "\n", (char) conversionc); 
	    //messerr("CText__print: ç: %c" "\n", 'ç'); // UTF-8: "character too large for enclosing literal type" 
	    messerr("CText__print: ç: %c" "\n", L'ç'); // UTF-8: "character too large for enclosing literal type" 
	    messerr("CText__print: sizeof(ç): %d" "\n", sizeof(L'ç')); // UTF-8: sizeof(L'ç'): 4 
	    {
#if 0 
  if (c == 224) d = 133; //à
  if (c == 226) d = 131; //â
  if (c == 231) d = 135; //ç
  if (c == 233) d = 130; //é
  if (c == 232) d = 138; //è
  if (c == 234) d = 136; //ê    
  if (c == 238) d = 140; //î
  if (c == 244) d = 131+16; //ô
#endif 
	      static const unsigned char c_cedille[] = "ô"; //"î"; //"ê"; //"è"; //"â";//"à";//"é";//"ç"; 
	      messerr("CText__print: c_cedille[]: %s" "\n", c_cedille); // UTF-8: sizeof(L'ç'): 4 
	      messerr("CText__print: sizeof(c_cedille[]): %d" "\n", sizeof(c_cedille)); // UTF-8: sizeof(c_cedille): 3 
	      messerr("CText__print: ARRAY_SIZE(c_cedille[]): %d" "\n", ARRAY_SIZE(c_cedille)); // UTF-8: ARRAY_SIZE(c_cedille): 3 
	      messerr("CText__print: c_cedille[0]: %d" "\n", c_cedille[0]); // UTF-8: c_cedille[0]: 195 - C3 
	      messerr("CText__print: c_cedille[1]: %d" "\n", c_cedille[1]); // UTF-8: c_cedille[1]: 167 - A7 
	      messerr("CText__print: c_cedille[2]: %d" "\n", c_cedille[2]); // UTF-8: c_cedille[2]: '\0'- 00
	      messerr("CText__print: c_cedille[0]: %x" "\n", c_cedille[0]); // UTF-8: c_cedille[0]: 195 - C3 
	      messerr("CText__print: c_cedille[1]: %x" "\n", c_cedille[1]); // UTF-8: c_cedille[1]: 167 - A7 
	      messerr("CText__print: c_cedille[2]: %x" "\n", c_cedille[2]); // UTF-8: c_cedille[2]: '\0'- 00 
	      assert(false); 
	    };
	    {
	      static const unsigned char c_cedille[] = "ą"; 
	      messerr("CText__print: c_cedille[]: %s" "\n", c_cedille); // UTF-8: sizeof(L'ç'): 4 
	      messerr("CText__print: sizeof(c_cedille[]): %d" "\n", sizeof(c_cedille)); // UTF-8: sizeof(c_cedille): 3 
	      messerr("CText__print: ARRAY_SIZE(c_cedille[]): %d" "\n", ARRAY_SIZE(c_cedille)); // UTF-8: ARRAY_SIZE(c_cedille): 3 
	      messerr("CText__print: c_cedille[0]: %d" "\n", c_cedille[0]); // UTF-8: c_cedille[0]: 195 - C3 
	      messerr("CText__print: c_cedille[1]: %d" "\n", c_cedille[1]); // UTF-8: c_cedille[1]: 167 - A7 
	      messerr("CText__print: c_cedille[2]: %d" "\n", c_cedille[2]); // UTF-8: c_cedille[2]: '\0'- 00
	      messerr("CText__print: c_cedille[0]: %x" "\n", c_cedille[0]); // UTF-8: c_cedille[0]: 195 - C3 
	      messerr("CText__print: c_cedille[1]: %x" "\n", c_cedille[1]); // UTF-8: c_cedille[1]: 167 - A7 
	      messerr("CText__print: c_cedille[2]: %x" "\n", c_cedille[2]); // UTF-8: c_cedille[2]: '\0'- 00 
	    };
	    {
	      static const unsigned char c_cedille[] = "b"; 
	      messerr("CText__print: c_cedille[]: %s" "\n", c_cedille); // UTF-8: 
	      messerr("CText__print: sizeof(c_cedille[]): %d" "\n", sizeof(c_cedille)); // UTF-8: sizeof(c_cedille): 2 
	      messerr("CText__print: ARRAY_SIZE(c_cedille[]): %d" "\n", ARRAY_SIZE(c_cedille)); // UTF-8: ARRAY_SIZE(c_cedille): 2 
	      messerr("CText__print: c_cedille[0]: %d" "\n", c_cedille[0]); // UTF-8: c_cedille[0]: 98 - 0x62 
	      messerr("CText__print: c_cedille[1]: %d" "\n", c_cedille[1]); // UTF-8: c_cedille[1]: '\0'- 00 
	      messerr("CText__print: c_cedille[0]: %x" "\n", c_cedille[0]); // UTF-8: c_cedille[0]: 98 - 0x62 
	      messerr("CText__print: c_cedille[1]: %x" "\n", c_cedille[1]); // UTF-8: c_cedille[1]: '\0'- 00 
	    };
	    {
	      static const unsigned char c_cedille[] = "û"; 
	      messerr("CText__print: c_cedille[]: %s" "\n", c_cedille); // UTF-8: 
	      messerr("CText__print: sizeof(c_cedille[]): %d" "\n", sizeof(c_cedille)); // UTF-8: sizeof(c_cedille): 2 
	      messerr("CText__print: ARRAY_SIZE(c_cedille[]): %d" "\n", ARRAY_SIZE(c_cedille)); // UTF-8: ARRAY_SIZE(c_cedille): 2 
	      messerr("CText__print: c_cedille[0]: %d" "\n", c_cedille[0]); // UTF-8: c_cedille[0]: 98 - 0x62 
	      messerr("CText__print: c_cedille[1]: %d" "\n", c_cedille[1]); // UTF-8: c_cedille[1]: '\0'- 00 
	      messerr("CText__print: c_cedille[0]: %x" "\n", c_cedille[0]); // UTF-8: c_cedille[0]: 98 - 0x62 
	      messerr("CText__print: c_cedille[1]: %x" "\n", c_cedille[1]); // UTF-8: c_cedille[1]: '\0'- 00 
	    };
	    {
	      static const unsigned char c_cedille[] = "É"; 
	      messerr("CText__print: c_cedille[]: %s" "\n", c_cedille); // UTF-8: 
	      messerr("CText__print: sizeof(c_cedille[]): %d" "\n", sizeof(c_cedille)); // UTF-8: sizeof(c_cedille): 2 
	      messerr("CText__print: ARRAY_SIZE(c_cedille[]): %d" "\n", ARRAY_SIZE(c_cedille)); // UTF-8: ARRAY_SIZE(c_cedille): 2 
	      messerr("CText__print: c_cedille[0]: %d" "\n", c_cedille[0]); // UTF-8: c_cedille[0]: 98 - 0x62 
	      messerr("CText__print: c_cedille[1]: %d" "\n", c_cedille[1]); // UTF-8: c_cedille[1]: '\0'- 00 
	      messerr("CText__print: c_cedille[0]: %x" "\n", c_cedille[0]); // UTF-8: c_cedille[0]: 98 - 0x62 
	      messerr("CText__print: c_cedille[1]: %x" "\n", c_cedille[1]); // UTF-8: c_cedille[1]: '\0'- 00 
	    };
	    {
	      static const unsigned char c_cedille[] = "ù"; 
	      messerr("CText__print: c_cedille[]: %s" "\n", c_cedille); // UTF-8: 
	      messerr("CText__print: sizeof(c_cedille[]): %d" "\n", sizeof(c_cedille)); // UTF-8: sizeof(c_cedille): 2 
	      messerr("CText__print: ARRAY_SIZE(c_cedille[]): %d" "\n", ARRAY_SIZE(c_cedille)); // UTF-8: ARRAY_SIZE(c_cedille): 2 
	      messerr("CText__print: c_cedille[0]: %d" "\n", c_cedille[0]); // UTF-8: c_cedille[0]: 98 - 0x62 
	      messerr("CText__print: c_cedille[1]: %d" "\n", c_cedille[1]); // UTF-8: c_cedille[1]: '\0'- 00 
	      messerr("CText__print: c_cedille[0]: %x" "\n", c_cedille[0]); // UTF-8: c_cedille[0]: 98 - 0x62 
	      messerr("CText__print: c_cedille[1]: %x" "\n", c_cedille[1]); // UTF-8: c_cedille[1]: '\0'- 00 
	    };
	    {
	      static const unsigned char c_cedille[] = "Ê"; 
	      messerr("CText__print: c_cedille[]: %s" "\n", c_cedille); // UTF-8: 
	      messerr("CText__print: sizeof(c_cedille[]): %d" "\n", sizeof(c_cedille)); // UTF-8: sizeof(c_cedille): 2 
	      messerr("CText__print: ARRAY_SIZE(c_cedille[]): %d" "\n", ARRAY_SIZE(c_cedille)); // UTF-8: ARRAY_SIZE(c_cedille): 2 
	      messerr("CText__print: c_cedille[0]: %d" "\n", c_cedille[0]); // UTF-8: c_cedille[0]: 98 - 0x62 
	      messerr("CText__print: c_cedille[1]: %d" "\n", c_cedille[1]); // UTF-8: c_cedille[1]: '\0'- 00 
	      messerr("CText__print: c_cedille[0]: %x" "\n", c_cedille[0]); // UTF-8: c_cedille[0]: 98 - 0x62 
	      messerr("CText__print: c_cedille[1]: %x" "\n", c_cedille[1]); // UTF-8: c_cedille[1]: '\0'- 00 
	    };
#elif 0
	    messerr("CText__print: sizeof(ç): %d" "\n", *(0 + (unsigned char *)(L'ç'))); // UTF-8: sizeof(L'ç'): 4 
	    messerr("CText__print: sizeof(ç): %d" "\n", *(1 + (unsigned char *)(L'ç'))); // UTF-8: sizeof(L'ç'): 4 
	    messerr("CText__print: sizeof(ç): %d" "\n", *(2 + (unsigned char *)(L'ç'))); // UTF-8: sizeof(L'ç'): 4 
	    messerr("CText__print: sizeof(ç): %d" "\n", *(3 + (unsigned char *)(L'ç'))); // UTF-8: sizeof(L'ç'): 4 
#endif 
	    //messerr("CText__print: conversionc: %c" "\n", conversionpourrie(L'ç')); 
	    //messerr("CText__print: conversionc: %c" "\n", conversionpourrie("ç"[0])); 
	    //messerr("CText__print: conversionc: %c" "\n", conversionpourrie("ç"[0], "ç"[1])); 
	    const float tx = (float) (conversionc % 16) / 16.0f;
	    const float ty = (float) (conversionc / 16) / 16.0f;
	    glTexCoord2f(tx,ty+0.0625f);  
	    glVertex2i(this -> cx,this -> cy);
	    glTexCoord2f(tx+0.0625f,ty+0.0625f);
	    glVertex2i(this -> cx+TAILLE_CHAR_PIXEL, this -> cy);
	    glTexCoord2f(tx+0.0625f,ty);  
	    glVertex2i(this -> cx+TAILLE_CHAR_PIXEL, this -> cy+TAILLE_CHAR_PIXEL);          
	    glTexCoord2f(tx,ty);
	    glVertex2i(this -> cx, this -> cy+TAILLE_CHAR_PIXEL);
	    this -> cx += TAILLEX_CHAR;
	  }
        }
        else {
          this -> cx += (j-i)*TAILLEX_CHAR;
          i = j;
        };    
	
        // si le dernier caractère étant ' ', on avance encore pour faire un espace 
        if (c[i] == ' ') {
          this -> cx += TAILLEX_CHAR;
          i++;
        };
      
        if ((c[i] == 10) || (c[i] == 13)) { 
          // si le dernier caractère était #10, on va à la ligne
	  this -> cx  = x;
	  this -> cy -= TAILLEY_CHAR;
	  lignecourante++;
	  i++;
	}; 
      
        // sinon, c[i] = #0 et la boucle général s'arrête 
      }; 
    
    } glEnd();
    glEnable(GL_LIGHTING);
  } glDisable2D();
  
  if (l > lignecourante - nblignes+1) {
    *toutaffiche_ref = false;
    l = lignecourante - nblignes+1;
  }
  else {
    *toutaffiche_ref = true;
  }; 
 
  return l;
}; 


void CText__print1(CText * this, const int x, const int y, const int w, const int h, const char * s) {
  bool b;
  this -> print2(this, 0.0f, 10000, 10000,x, y, w, h, s, &b);   
};







static void CMessageTexte__SetMsg(CMessageTexte * this, const char * inS) { 
#if 0 
  fprintf(stderr, "%s : Argot s = %p ", __func__, this -> s); 
  fflush(NULL);
  fprintf(stderr, " - '%s' " "\n", this -> s); 
  if (0 == strcasecmp("Chapitre", this -> s)) { assert(false); }; 
  if (0 == strcasecmp("Chapitre", inS)) { assert(false); }; 
#endif 
  
  //if(s != NULL)
  //          delete[] s;
  //s = NULL
  
  if (this -> s != NULL) { 
    free(this -> s); 
  }; 
  this -> s = strcopy(inS); 
  //fprintf(stderr, "%s : this -> s = %s " "\n", __func__, this -> s); 
  //s = oem2ansi(s); 
  this -> lignedebut = 0; 
  this -> nbcaracaffiche = 0; 
}; 



static void CMessageTexte__Life(CMessageTexte * this) { 
  this -> nbcaracaffiche++;  
}; 

static void CMessageTexte__Render(CMessageTexte * this) {
enum { MSGTXT_X = 60 }; //100 }; 
enum { MSGTXT_Y = 320 }; //300 }; 
enum { MSGTXT_W = 540 }; //500 }; 
enum { MSGTXT_W2 = 220 }; 
enum { MSGTXT_H = 150 }; 
enum { MSGTXTDECAL_Y = 56 }; 
enum { MSGTXTDECAL_X = 32 }; 
  
  glEnable2D(); { 
    glDisable(GL_LIGHTING);
    
    bool toutafficheenbas;
    this -> lignedebut = Text -> print2(Text, this -> lignedebut, 4, this -> nbcaracaffiche,
                             MSGTXT_X + MSGTXTDECAL_X, MSGTXT_Y + MSGTXT_H - MSGTXTDECAL_Y,
                             MSGTXT_W - 2*MSGTXTDECAL_X, MSGTXT_H, this -> s, &toutafficheenbas);
  
    /*if(!toutafficheenbas)
      {*/
    /* glEnable2D();
    
       texFlecheBas->GLTextureCourante();
       glDisable(GL_LIGHTING);
    
       BEGIN_RECTANGLE_END(MSGTXT_X + MSGTXT_W2, MSGTXT_Y - MSGTXTDECAL_Y, 32, 32);  */             
                    
    /*}*/


    CTexture__GLTextureCourante(this -> texfond);
    
    glBegin(GL_QUADS); {
      BLIT(MSGTXT_X,MSGTXT_Y,MSGTXT_W,MSGTXT_H,0,0,1,1); 
    } glEnd();
  

    glEnable(GL_LIGHTING);
  } glDisable2D();
  
}; 



static bool CMessageTexte__Input(CMessageTexte * this) {
  
  // gestion de l'entrée clavier 
#define PAS_MESSAGE_TEXTE 0.2f
  if (KEY_UP) this -> lignedebut -= PAS_MESSAGE_TEXTE;
  if (KEY_DOWN) this -> lignedebut += PAS_MESSAGE_TEXTE;
  
  if (this -> nbcaracaffiche > 10)
    if (KEY_MENU_VALIDER) return true;
  
  return false;    
}; 
 
static bool CMessageTexte__InputAndRender(CMessageTexte * this) {
  this -> Render(this);
  return this -> Input(this); 
}; 




CMessageTexte * CMessageTexte_make(void) {
  MALLOC_BZERO(CMessageTexte,this); 
  
  ASSIGN_METHOD(CMessageTexte,this,SetMsg); 
  ASSIGN_METHOD(CMessageTexte,this,Render); 
  ASSIGN_METHOD(CMessageTexte,this,Input); 
  ASSIGN_METHOD(CMessageTexte,this,Life); 
  //ASSIGN_METHOD(CMessageTexte,this,InputAndRender); 
  
  printf("CMessageTexte__CMessageTexte()" "\n");                         
  this -> texfond = CTexture_make("parchemin.png");  
  this -> texFlecheBas = CTexture_make("flechebas.png");  
  this -> s = NULL;

  return this; 
};

void CMessageTexte_delete(CMessageTexte * this) {
  CTexture_delete(this -> texFlecheBas);
  CTexture_delete(this -> texfond);
  free(this -> s);   
  free(this); 
};


