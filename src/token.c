#include "global.h"
#include "token.h"

static inline token_t * token_allouer(void);


token_t * token_allouer(void) {
  return (token_t *) malloc((sizeof (token_t)));
}

token_t * token_make(const token_type_t type, const char * lexeme) {
  return token_make_nocopy(type, strcopy(lexeme));
}

token_t * token_make_nocopy(token_type_t type, char * lexeme) {
  token_t * retour;
  retour = token_allouer();
  retour -> type = type;
  retour -> lexeme = lexeme;
  return retour;
}

void token_free(token_t * token) {
  free(token -> lexeme);
  free(token);
}

token_t * token_copy(const token_t * token) {
  return token_make(token -> type, token -> lexeme);
}


const char * token_type_string_tab[TOKEN_TYPE_NOMBRE+1] = {
  "TOKEN_TYPE_LETTRE",
  "TOKEN_TYPE_LETTRE_ANY",
  "TOKEN_TYPE_BANG",
  "TOKEN_TYPE_HUH",
  "TOKEN_TYPE_PLUS",
  "TOKEN_TYPE_STAR",
  "TOKEN_TYPE_OPENPAR",
  "TOKEN_TYPE_CLOSEPAR",
  "TOKEN_TYPE_OPENBRACE",
  "TOKEN_TYPE_CLOSEBRACE",
  "TOKEN_TYPE_OPENBRACKET",
  "TOKEN_TYPE_CLOSEBRACKET",
  "TOKEN_TYPE_EOF",
  "TOKEN_TYPE_NOMBRE"
};

const char * token_type_string_const(const token_type_t token_type) {
  return token_type_string_tab[token_type];
}

char * token_type_string(const token_type_t token_type) {
  return strcopy(token_type_string_tab[token_type]);
}


const char * token_string_const(const token_t * token) {
  return token_type_string_tab[token -> type];
}

char * token_string(const token_t * token) {
  return strconcat4(token_type_string_tab[token -> type], "[", token -> lexeme, "]");
}



bool token_equal(const token_t * token1, const token_t * token2) {
  if (token1 -> type != token2 -> type) return false;

  return strequal(token1 -> lexeme, token2 -> lexeme);
}

