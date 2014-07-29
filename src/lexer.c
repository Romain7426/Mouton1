#include "global.h"
#include "lexer.h"
#include "token.h"
#include "token_liste.h"


static inline token_t * lex_step(const char * str, size_t * pos, const size_t len, char * * err);



token_liste_t * lex(const char * str, bool * pas_erreur, char * * err) {
  const size_t len = strlen(str);
  token_liste_t * retour;
  token_t * token;

  *pas_erreur = false;
  
  retour = token_liste_vide();
  for (size_t pos = 0; pos < len; pos++) {
    token = lex_step(str, &pos, len, err);
    if (token == NULL) {
      *pas_erreur = false;
      token_liste_free(retour);
      return NULL;
    }
    retour = token_liste_cons_nocopy(token, retour);
  }

  token_liste_reverse_surplace(&retour);
  *pas_erreur = true;
  return retour;
}




token_t * lex_step(const char * str, size_t * pos, const size_t len, char * * err) {
  token_t * retour;
  int c;

  c = str[*pos];

  switch (c) {

    //case '\0': retour = token_liste_vide(); break;

    //case '\\': pos++; c = str[pos]; if (c == '\n') { (state -> fin.ligne) ++; (state -> fin.colonne) = 0; }; retour = token_make_nocopy(TOKEN_TYPE_LETTRE, char_string(c)); break;
  case '\\': 
    (*pos)++; 
    if (len == *pos) {
      asprintf(err, "La chaîne à analyser se termine par un '\\'; or un caractère est attendu après un '\\'.");
      return NULL;
    }
    c = str[*pos];
    switch (c) {
    default: break;
    case '0': c = '\0'; break;
    case 'a': c = '\a'; break;
    case 'b': c = '\b'; break;
    case 't': c = '\t'; break;
    case 'n': c = '\n'; break;
    case 'v': c = '\v'; break;
    case 'f': c = '\f'; break;
    case 'r': c = '\r'; break;
    case 'e': c = '\e'; break;
    }
    retour = token_make_nocopy(TOKEN_TYPE_LETTRE, char_string(c)); 
    break;

    //case '\n': (state -> fin.ligne) ++; (state -> fin.colonne) = 0; /* FALLTHROUGH */
  default: retour = token_make_nocopy(TOKEN_TYPE_LETTRE, char_string(c)); break;

  case '.': retour = token_make_nocopy(TOKEN_TYPE_LETTRE_ANY, char_string(c)); break;
  case '!': retour = token_make_nocopy(TOKEN_TYPE_BANG, char_string(c)); break;
  case '?': retour = token_make_nocopy(TOKEN_TYPE_HUH, char_string(c)); break;
  case '+': retour = token_make_nocopy(TOKEN_TYPE_PLUS, char_string(c)); break;
  case '*': retour = token_make_nocopy(TOKEN_TYPE_STAR, char_string(c)); break;

  case '(': retour = token_make_nocopy(TOKEN_TYPE_OPENPAR, char_string(c)); break;
  case '[': retour = token_make_nocopy(TOKEN_TYPE_OPENBRACKET, char_string(c)); break;
  case '{': retour = token_make_nocopy(TOKEN_TYPE_OPENBRACE, char_string(c)); break;

  case ')': retour = token_make_nocopy(TOKEN_TYPE_CLOSEPAR, char_string(c)); break;
  case ']': retour = token_make_nocopy(TOKEN_TYPE_CLOSEBRACKET, char_string(c)); break;
  case '}': retour = token_make_nocopy(TOKEN_TYPE_CLOSEBRACE, char_string(c)); break;

  }
  
  return retour;
}
