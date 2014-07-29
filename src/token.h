#ifndef TOKEN_H
#define TOKEN_H

enum token_type_t { 
  TOKEN_TYPE_LETTRE,
  TOKEN_TYPE_LETTRE_ANY,
  TOKEN_TYPE_BANG,
  TOKEN_TYPE_HUH,
  TOKEN_TYPE_PLUS,
  TOKEN_TYPE_STAR,
  TOKEN_TYPE_OPENPAR,
  TOKEN_TYPE_CLOSEPAR,
  TOKEN_TYPE_OPENBRACE,
  TOKEN_TYPE_CLOSEBRACE,
  TOKEN_TYPE_OPENBRACKET,
  TOKEN_TYPE_CLOSEBRACKET,
  TOKEN_TYPE_EOF,
  TOKEN_TYPE_NOMBRE
};

struct token_t {
  token_type_t type;
  char * lexeme;
};

extern const char * token_type_string_tab[TOKEN_TYPE_NOMBRE+1];
extern const char * token_type_string_const(const token_type_t token_type);
extern char * token_type_string(const token_type_t token_type);



extern token_t * token_make(const token_type_t type, const char * lexeme);
extern token_t * token_make_nocopy(const token_type_t type, char * lexeme);
extern void token_free(token_t * token);
extern token_t * token_copy(const token_t * token);

extern bool token_equal(const token_t * token1, const token_t * token2);

extern const char * token_string_const(const token_t * token);
extern char * token_string(const token_t * token);


#endif /* TOKEN_H */
