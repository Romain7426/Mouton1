#include "global.h"
#include "programme.h"
#include "arbre.h"
#include "arbre_methode.h"
#include "automate.h"
#include "automate_methode.h"
#include "compilation.h"
#include "token.h"
#include "token_liste.h"
#include "parser.h"
#include "lexer.h"
#include "lexer_for_c_language.h"

static automate_t * programme_step(const char * const expression_a_compiler_en_automate);
static automate_t * compiler_une_expression_reguliere_en_automate(const char * expression_a_compiler_en_automate);

static void automate_show_with_dotty(const automate_t * automate, const char * automate_name);
#define AUTOMATE_SHOW(a) automate_show_with_dotty((a),(BIGLIB_STRING(a)))

static void arbre_show_with_dotty(const arbre_t * arbre, const char * arbre_name);
#define ARBRE_SHOW(a) arbre_show_with_dotty((a),(BIGLIB_STRING(a)))


static bool texte_decouper(const str_t * const str, const char c, str_t * * str_gauche, str_t * * str_droite);
static bool la_string_ne_contient_que_des_caracteres_blancs_huh(const str_t * str);
static str_t * gen_dotty_code(const int nb, str_t * * enum_name, str_t * * expr_reguliere, const bool * ligne_vide_huh, automate_t * * automates);
static bool_t gen_c_code(const str_t * lexer_name, const int nb, const str_tableau_t * lignes, str_t * * enum_name, str_t * * expr_reguliere, const bool * ligne_vide_huh, automate_t * * automates, str_t * * c_code_extern_declarations_ptr, str_t * * c_code_static_declarations_ptr, str_t * * c_code_definitions_ptr, str_t * * c_code_main_ptr);

static int type_du_plus_long_prefixe_reconnu(const unsigned int nb, str_t * * enum_name, str_t * * expr_reguliere, const bool * ligne_vide_huh, automate_t * * automates, const char * mot, int * longueur_du_plus_prefixe_reconnu);

static void read_eval_print_loop(const int nb, str_t * * enum_name, str_t * * expr_reguliere, const bool * ligne_vide_huh, automate_t * * automates);
static void analyse_de_la_ligne(const int nb, str_t * * enum_name, str_t * * expr_reguliere, const bool * ligne_vide_huh, automate_t * * automates, const char * mot);
static str_t * readline(void);


static void generation_code_c_pour_un_enum(const char * type_nom_sans_t, const int nb, str_t * * enum_name, char * * h_code, char * * c_code);
static char * type_enlever_t(const char * str);
static void generation_code_c_pour_un_struct(const char * lexer_name, const int nb, str_t * * type_name, bool_t * scalar_huh, str_t * * champ_name, char * * h_code, char * * c_code);

static const char * liste_pointeur_h_template = 
#include "liste_pointeur_template.h.ct"
  ;

static const char * liste_pointeur_c_template = 
#include "liste_pointeur_template.c.ct"
  ;

static void generation_code_c_pour_une_liste_pointeur(const char * typebase_name, char * * h_code, char * * c_code);
static char * string_replace(const char * text, const char c, const char * str);
static int nb_occurrences(const char * str, const char c);
static char * generation_code_c_pour_la_lib(const char * basename);
//static void generation_code_c_pour_la_fonction_auxliaire(const char * prepend_string, const int nb, str_t * * enum_basename, char * * h_code, char * * c_code);
static void generation_code_c_pour_la_fonction_auxliaire(const char * prepend_string, const char * prepend_string_for_automaton, const char * prepend_string_for_enum, const int nb, str_t * * enum_basename, char * * h_code, char * * c_code);
static void generation_code_c_pour_la_fonction_principale(const char * prepend_string, const int nb, str_t * * enum_basename, char * * h_code, char * * c_code);
static void generation_code_c_pour_la_fonction_readline(const char * prepend_string, char * * h_code, char * * c_code);
static void generation_code_c_pour_la_fonction_readevalprintloop(const char * prepend_string, char * * h_code, char * * c_code);
static void generation_code_c_pour_la_fonction_main(const char * prepend_string, const char * conditional_directive_name, const int nb, const str_tableau_t * lignes, const bool * ligne_vide_huh, char * * h_code, char * * c_code);

static const char * COPYING_at_start_of_c_files = 
#include "COPYING_at_start_of_c_files.ct"
  ;

static const char * lexer_example_lexer_type_ct = 
#include "lexer_example.lexer.type.ct"
  ;



static const char prog_test_hello1[] = 
"#include <stdio.h>\n"
"\n"
"int main(int argc, char * argv[]) {\n"
"  printf(\"Hello World!\\n\");\n"
"  return 0;\n"
"}\n"
  ;

static const char prog_test_hello2[] = 
"extern int puts(const char *s);\n"
"\n"
"int main(int argc, char * argv[]) {\n"
"#if 1 \n"
"  puts(\"Hello World! [then]\\n\");\n"
"#else\n"
"  puts(\"Hello World! [else]\\n\");\n"
"#endif\n"
"  return 0;\n"
"}\n"
  ;

static const char prog_test_hello3[] = 
"int tab[3];\n"
"\n"
"extern int puts(const char * str);\n"
"\n"
"a b;\n"
"\n"
";;;\n"
"\n"
"int main(int argc, char * argv[]) {\n"
"  puts(\"Hello World!\\n\");\n"
"  return 0;\n"
"}\n"
  ;

static const char prog_test_hello4[] = 
"//int tab1[2*3+1 == x & (x ^ MASK) << 2];\n"
"int tab11[2*3+1 == 9 & (12 ^ 43) << 2];\n"
"int tab2[2*3+1];\n"
"int tab3[(3)];\n"
"\n"
"extern int puts(const char * str);\n"
"\n"
"a b;\n"
"\n"
";;;\n"
"\n"
"int main(int argc, char * argv[]) {\n"
"  puts((\"Hello World!\\n\"));\n"
"  return 0;\n"
"}\n"
  ;

static const char prog_test_hello5[] = 
"//int tab1[2*3+1 == x & (x ^ MASK) << 2];\n"
"int tab11[2*3+1 == 9 & (12 ^ 43) << 2];\n"
"int tab2[2*3+1];\n"
"int tab3[(3)];\n"
"\n"
"extern int puts(const char * str);\n"
"\n"
"/* a b; */ \n"
"\n"
";;;\n"
"\n"
"int main(int argc, char * argv[]) {\n"
"  puts((\"Hello World!\\n\"));\n"
"  return 0;\n"
"}\n"
  ;

static const char prog_test_hello6[] = 
"\n"
"int main(int argc, char * argv[]) {\n"
"  return 0;\n"
"}\n"
  ;


static const char prog_test_hello7[] = 
"\n"
"extern int puts(const char * str);\n"
"\n"
"int main(int argc, char * argv[]) {\n"
"  puts((\"Hello World!\\n\"));\n"
"  return 0;\n"
"}\n"
  ;


static void analyze_to_fill_the_global_symbol_table(const lexer_lexer_for_c_language_token_liste_t * tokens);

static int lexer_lexer_for_c_language_token_liste_count_according_to_type(const lexer_lexer_for_c_language_token_type_t type, const lexer_lexer_for_c_language_token_liste_t * l);
static const lexer_lexer_for_c_language_token_liste_t * ensure_the_c_code_is_well_braced_list(const lexer_lexer_for_c_language_token_type_t open_type, const lexer_lexer_for_c_language_token_type_t close_type, const lexer_lexer_for_c_language_token_liste_t * l);
static const lexer_lexer_for_c_language_token_liste_t * ensure_the_c_code_is_well_braced_list_aux(const lexer_lexer_for_c_language_token_type_t open_type, const lexer_lexer_for_c_language_token_type_t close_type, const lexer_lexer_for_c_language_token_liste_t * l, const int stack_count, const lexer_lexer_for_c_language_token_liste_t * previous_open_brace);

enum token_tree_type_t {
  TOKEN_TREE_TYPE_NULL,
  TOKEN_TREE_TYPE_LEAF,
  TOKEN_TREE_TYPE_NODE_TOP_BRACE,
  TOKEN_TREE_TYPE_NODE_TOP_BRACKET,
  TOKEN_TREE_TYPE_NODE_TOP_PAREN,
};
typedef enum token_tree_type_t token_tree_type_t;
struct token_tree_t {
  token_tree_type_t type;
  lexer_lexer_for_c_language_token_t * token;
  lexer_lexer_for_c_language_token_liste_t * tokens; 
};
typedef struct token_tree_t token_tree_t;

static void token_tree_print(const token_tree_t * tree_after_top_level_braces_and_brackets_and_parenthesis_processing);

static int token_tree_count_tokens_according_to_type(const lexer_lexer_for_c_language_token_type_t type, const int nb_elt, const token_tree_t * tree);

static int token_tree_ensure_the_c_code_is_well_braced_or_bracketed(const lexer_lexer_for_c_language_token_type_t opening_type, const lexer_lexer_for_c_language_token_type_t closing_type, const int nb_elt, token_tree_t (* tree_ptr)[]);


static int skip_blanks_and_process_directives(const int current_index, const int nb_elt, token_tree_t (* tree_ptr)[]) {
  for (int i = current_index; i < nb_elt; i++) {
    if ((*tree_ptr)[i].type == TOKEN_TREE_TYPE_NULL) return i;
    
    if ((*tree_ptr)[i].type != TOKEN_TREE_TYPE_LEAF) return i;

    assert((*tree_ptr)[i].type == TOKEN_TREE_TYPE_LEAF);
    
    switch ((*tree_ptr)[i].token -> type) {
    default: assert(0 != 0); return -1; break;
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BLANK: 
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_MULTILINES: 
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_ONELINE_CPP:
      continue;
      break;
	  
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MONO_LINE: 
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MULTI_LINES: 
      assert(false);
      break;
	  
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT: 
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_ZERO:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC_V2:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_HEX:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_BIN:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VCC:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VC:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_SIMPLE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_WITH_EXP:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_HEX_WITH_EXP:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE_NEWLINE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_EMPTY:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_ESCAPE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_WIDE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_ENDED_BY_NEWLINE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE_ENDED_BY_NEWLINE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACKET:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_POINT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ARROW_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RDIV_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_TILDE_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PERLUETE_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PERLUETE_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PIPE_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PIPE_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_EQUAL_HUH_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HAT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PERCENT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BANG_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIFFERENT_HUH_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OR_EQUAL_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OR_EQUAL_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_PLUS_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_MINUS_OPERARTOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_LSHIFT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RSHIFT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HUH_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COLON_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ELLIPSIS:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_STAR_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RDIV_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERCENT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PLUS_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_MINUS_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_LSHIFT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RSHIFT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERLUETE_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_HAT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PIPE_OPERATOR:
      return i;
      break;
    }

    assert(i == nb_elt);
  }
  
  return nb_elt;
}


static int skip_blanks_and_process_directives_token_tree(const int current_index, const int nb_elt, const token_tree_t * tree) {
  for (int i = current_index; i < nb_elt; i++) {
    if (tree[i].type == TOKEN_TREE_TYPE_NULL) return i;
    
    if (tree[i].type != TOKEN_TREE_TYPE_LEAF) return i;

    assert(tree[i].type == TOKEN_TREE_TYPE_LEAF);
    
    switch (tree[i].token -> type) {
    default: assert(0 != 0); return -1; break;
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BLANK: 
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_MULTILINES: 
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_ONELINE_CPP:
      continue;
      break;
	  
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MONO_LINE: 
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MULTI_LINES: 
      assert(false);
      break;
	  
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT: 
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_ZERO:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC_V2:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_HEX:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_BIN:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VCC:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VC:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_SIMPLE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_WITH_EXP:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_HEX_WITH_EXP:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE_NEWLINE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_EMPTY:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_ESCAPE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_WIDE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_ENDED_BY_NEWLINE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE_ENDED_BY_NEWLINE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACKET:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_POINT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ARROW_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RDIV_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_TILDE_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PERLUETE_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PERLUETE_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PIPE_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PIPE_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_EQUAL_HUH_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HAT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PERCENT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BANG_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIFFERENT_HUH_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OR_EQUAL_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OR_EQUAL_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_PLUS_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_MINUS_OPERARTOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_LSHIFT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RSHIFT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HUH_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COLON_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ELLIPSIS:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_STAR_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RDIV_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERCENT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PLUS_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_MINUS_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_LSHIFT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RSHIFT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERLUETE_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_HAT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PIPE_OPERATOR:
      return i;
      break;
    }

    assert(i == nb_elt);
  }
  
  return nb_elt;
}


static const lexer_lexer_for_c_language_token_liste_t * skip_blanks_and_process_directives_tokens(const lexer_lexer_for_c_language_token_liste_t * tokens_given) {
  for (const lexer_lexer_for_c_language_token_liste_t * tokens = tokens_given; tokens != NULL; tokens = tokens -> cdr) {
    switch (tokens -> car -> type) {
    default: assert(0 != 0); return NULL; break;
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BLANK: 
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_MULTILINES: 
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_ONELINE_CPP:
      continue;
      break;
	  
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MONO_LINE: 
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MULTI_LINES: 
      assert(false);
      break;
	  
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT: 
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_ZERO:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC_V2:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_HEX:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_BIN:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VCC:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VC:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_SIMPLE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_WITH_EXP:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_HEX_WITH_EXP:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE_NEWLINE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_EMPTY:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_ESCAPE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_WIDE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_ENDED_BY_NEWLINE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE_ENDED_BY_NEWLINE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACKET:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACE:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_POINT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ARROW_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RDIV_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_TILDE_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PERLUETE_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PERLUETE_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PIPE_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PIPE_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_EQUAL_HUH_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HAT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PERCENT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BANG_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIFFERENT_HUH_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OR_EQUAL_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OR_EQUAL_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_PLUS_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_MINUS_OPERARTOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_LSHIFT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RSHIFT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HUH_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COLON_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ELLIPSIS:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_STAR_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RDIV_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERCENT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PLUS_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_MINUS_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_LSHIFT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RSHIFT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERLUETE_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_HAT_OPERATOR:
    case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PIPE_OPERATOR:
      return tokens;
      break;
    }

    assert(tokens == NULL);
  }
  
  return NULL;
}


const char * keywords_C99[] = {
  "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", 
  "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register",
  "restrict", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", 
  "unsigned", "void", "volatile", "while", "_Bool", "_Complex", "_Imaginary",
  NULL
};

const char * keywords_C99_implying_a_declaration[] = {
  "auto", "char", "const", "double", "else", 
  "enum", "extern", "float", "inline", "int", "long", "register",
  "restrict", "short", "signed", "static", "struct", "typedef", "union", 
  "unsigned", "void", "volatile", "_Bool", "_Complex", "_Imaginary",
  NULL
};

const char * keywords_C99_implying_a_statment[] = {
  "break", "case", "continue", "default", "do", "else", 
  "for", "goto", "if", 
  "return", "sizeof", "switch",  
  "while",
  NULL
};

static bool_t token_is_a_keyword_huh(const char * token) {
  for (int i = 0; keywords_C99[i] != NULL; i++) {
    if (0 == strcmp(token, keywords_C99[i])) return true;
  }
  return false;
}

static bool_t token_is_a_keyword_related_to_a_declaration_huh(const char * token) {
  for (int i = 0; keywords_C99_implying_a_declaration[i] != NULL; i++) {
    if (0 == strcmp(token, keywords_C99_implying_a_declaration[i])) return true;
  }
  return false;
}

static bool_t token_is_a_keyword_related_to_a_statment_huh(const char * token) {
  for (int i = 0; keywords_C99_implying_a_statment[i] != NULL; i++) {
    if (0 == strcmp(token, keywords_C99_implying_a_statment[i])) return true;
  }
  return false;
}


static char * lexer_lexer_for_c_language_token_liste_string_flat(const lexer_lexer_for_c_language_token_liste_t * tokens) {
  if (tokens == NULL) return strcopy("");
  char * temp_tail;
  temp_tail = lexer_lexer_for_c_language_token_liste_string_flat(tokens -> cdr);
  char * retour = strconcat(tokens -> car -> value, temp_tail);
  strfree(temp_tail);
  return retour;
}




    const char * STORAGE_CLASS_SPECIFIER_NULL = NULL;
    const char * STORAGE_CLASS_SPECIFIER_EXTERN = "extern";
    const char * STORAGE_CLASS_SPECIFIER_STATIC = "static";
    const char * STORAGE_CLASS_SPECIFIER_TYPEDEF = "typedef";
    
    const char * INLINE_CLASS_SPECIFIER_NULL = NULL;
    const char * INLINE_CLASS_SPECIFIER_INLINE = "inline";
    
    const char * CONST_CLASS_SPECIFIER_NULL = NULL;
    const char * CONST_CLASS_SPECIFIER_CONST = "const";
    
    const char * SIGNED_CLASS_SPECIFIER_NULL = NULL;
    const char * SIGNED_CLASS_SPECIFIER_SIGNED = "signed";
    const char * SIGNED_CLASS_SPECIFIER_UNSIGNED = "unsigned";
    
    const char * SIZE_CLASS_SPECIFIER_NULL = NULL;
    const char * SIZE_CLASS_SPECIFIER_SHORT_SHORT = "short short";
    const char * SIZE_CLASS_SPECIFIER_SHORT = "short";
    const char * SIZE_CLASS_SPECIFIER_LONG = "long";
    const char * SIZE_CLASS_SPECIFIER_LONG_LONG = "long long";
    
    const char * CORE_TYPE_SPECIFIER_NULL = NULL;
    const char * CORE_TYPE_SPECIFIER_VOID = "void";
    const char * CORE_TYPE_SPECIFIER_CHAR = "char";
    const char * CORE_TYPE_SPECIFIER_INT = "int";
    const char * CORE_TYPE_SPECIFIER_FLOAT = "float";
    const char * CORE_TYPE_SPECIFIER_DOUBLE = "double";
    const char * CORE_TYPE_SPECIFIER__BOOL = "_Bool";
    const char * CORE_TYPE_SPECIFIER__COMPLEX = "_Complex";

struct expression_tree_t;
typedef struct expression_tree_t expression_tree_t;
static expression_tree_t * build_the_expression_tree(const lexer_lexer_for_c_language_token_liste_t * tokens);

struct statment_tree_t;
typedef struct statment_tree_t statment_tree_t;

struct symbol_table_elt_t;
typedef struct symbol_table_elt_t symbol_table_elt_t;
struct symbol_table_elt_t {
#if 0
  char * name;
  char * storage_class;
  char * inline_class;
  char * const_class;
  char * signed_class;
  char * size_class;
  char * core_type;
#else
  char * name;
  char * asm_code; // for global var (… and local var?)
  int relative_addr_allocated; // for local var
  const char * storage_class;
  const char * inline_class;
  const char * const_class;
  const char * signed_class;
  const char * size_class;
  const char * core_type;
  int indirections_nb;
  bool_t array_huh;
  char * array_size_code_text;
  lexer_lexer_for_c_language_token_liste_t * array_size_code_tokens;
  expression_tree_t * array_size_code_tree;
  bool_t can_compute_array_size_constant_value_huh;
  int array_size_constant_value;
  // TODO macros defined before the code of array_size_code
  bool_t fun_param_huh;
  char * fun_param_code_text;
  lexer_lexer_for_c_language_token_liste_t * fun_param_code_tokens;
  symbol_table_elt_t * fun_param_code_table;
  int fun_param_code_table_nb;
  int fun_param_code_table_size;
  // TODO macros defined before the code of fun_param_code
  bool_t fun_def_huh;
  char * fun_def_code_text;
  lexer_lexer_for_c_language_token_liste_t * fun_def_code_tokens;
  statment_tree_t * fun_def_code_tree;
  // TODO macros defined before the code of fun_def_code
#endif
};
enum { GLOBAL_SYMBOL_TABLE_SIZE = 1022 };
static symbol_table_elt_t global_symbol_table[GLOBAL_SYMBOL_TABLE_SIZE+2]; // The 0e element is forbidden; The last element is a delimiter.
static const int global_symbol_table_base_index = 1;
static int global_symbol_table_nb = 0;
static void global_symbol_table_bzero(void) {
  bzero(global_symbol_table, (GLOBAL_SYMBOL_TABLE_SIZE + 2) * (sizeof(symbol_table_elt_t)));
}
static symbol_table_elt_t * symbol_table_make_on_the_heap(const int base, const int size) {
  symbol_table_elt_t * table;
  table = (symbol_table_elt_t *) malloc((base+size+1) * sizeof(symbol_table_elt_t));
  bzero(table, (base+size+1) * sizeof(symbol_table_elt_t));
  return table;
}
static int global_symbol_table_lookup(const char * name) {
  for (int i = global_symbol_table_base_index; i < global_symbol_table_base_index + global_symbol_table_nb; i++) {
    if (0 == strcmp(name, global_symbol_table[i].name)) return i;
  }
  return 0;
}
//static void global_symbol_table_push_nocopy(char * name, char * storage_class, char * inline_class, char * const_class, char * signed_class, char * size_class, char * core_type, int indirections_nb, bool_t array_huh, char * array_size_code_text, bool_t fun_param_huh, char * fun_param_code_text, bool_t fun_def_huh, char * fun_def_code_text) {
static int symbol_table_push_nocopy(symbol_table_elt_t * table, const int base, const int size, const int nb, char * name, const char * storage_class, const char * inline_class, const char * const_class, const char * signed_class, const char * size_class, const char * core_type, int indirections_nb, bool_t array_huh, char * array_size_code_text, lexer_lexer_for_c_language_token_liste_t * array_size_code_tokens, bool_t fun_param_huh, char * fun_param_code_text, lexer_lexer_for_c_language_token_liste_t * fun_param_code_tokens, bool_t fun_def_huh, char * fun_def_code_text, lexer_lexer_for_c_language_token_liste_t * fun_def_code_tokens) {
  assert(nb < size);

  assert(name != NULL);
  
  const int current_index = base + nb;
  table[current_index].name = name;
  table[current_index].storage_class = storage_class;
  table[current_index].inline_class = inline_class;
  table[current_index].const_class = const_class;
  table[current_index].signed_class = signed_class;
  table[current_index].size_class = size_class;
  table[current_index].core_type = core_type;
  table[current_index].indirections_nb = indirections_nb;
  table[current_index].array_huh = array_huh;
  table[current_index].array_size_code_text = array_size_code_text;
  table[current_index].array_size_code_tokens = array_size_code_tokens;
  table[current_index].fun_param_huh = fun_param_huh;
  table[current_index].fun_param_code_text = fun_param_code_text;
  table[current_index].fun_param_code_tokens = fun_param_code_tokens;
  table[current_index].fun_def_huh = fun_def_huh;
  table[current_index].fun_def_code_text = fun_def_code_text;
  table[current_index].fun_def_code_tokens = fun_def_code_tokens;

  return nb+1;
}
static void global_symbol_table_push_nocopy(char * name, const char * storage_class, const char * inline_class, const char * const_class, const char * signed_class, const char * size_class, const char * core_type, int indirections_nb, bool_t array_huh, char * array_size_code_text, lexer_lexer_for_c_language_token_liste_t * array_size_code_tokens, bool_t fun_param_huh, char * fun_param_code_text, lexer_lexer_for_c_language_token_liste_t * fun_param_code_tokens, bool_t fun_def_huh, char * fun_def_code_text, lexer_lexer_for_c_language_token_liste_t * fun_def_code_tokens) {
  global_symbol_table_nb = symbol_table_push_nocopy(global_symbol_table, global_symbol_table_base_index, GLOBAL_SYMBOL_TABLE_SIZE, global_symbol_table_nb, (name), (storage_class), (inline_class), (const_class), (signed_class), (size_class), (core_type), indirections_nb, array_huh, (array_size_code_text), (array_size_code_tokens), fun_param_huh, (fun_param_code_text), (fun_param_code_tokens), fun_def_huh, (fun_def_code_text), (fun_def_code_tokens));
}
static int symbol_table_push(symbol_table_elt_t * table, const int base, const int size, const int nb, const char * name, const char * storage_class, const char * inline_class, const char * const_class, const char * signed_class, const char * size_class,   const char * core_type, int indirections_nb, bool_t array_huh, const char * array_size_code_text, const lexer_lexer_for_c_language_token_liste_t * array_size_code_tokens, bool_t fun_param_huh, const char * fun_param_code_text, const lexer_lexer_for_c_language_token_liste_t * fun_param_code_tokens, bool_t fun_def_huh, const char * fun_def_code_text, const lexer_lexer_for_c_language_token_liste_t * fun_def_code_tokens) {
  //global_symbol_table_push_nocopy(strcopy(name), strcopy(storage_class), strcopy(inline_class), strcopy(const_class), strcopy(signed_class), strcopy(size_class), strcopy(core_type), indirections_nb, array_huh, strcopy(array_size_code), fun_param_huh, strcopy(fun_param_code), fun_def_huh, strcopy(fun_def_code));
  //global_symbol_table_push_nocopy(strcopy(name), (storage_class), (inline_class), (const_class), (signed_class), (size_class), (core_type), indirections_nb, array_huh, strcopy(array_size_code_text), lexer_lexer_for_c_language_token_liste_copy(array_size_code_tokens), fun_param_huh, strcopy(fun_param_code_text), lexer_lexer_for_c_language_token_liste_copy(fun_param_code_tokens), fun_def_huh, strcopy(fun_def_code_text));
  return symbol_table_push_nocopy(table, base, size, nb, strcopy(name), (storage_class), (inline_class), (const_class), (signed_class), (size_class), (core_type), indirections_nb, array_huh, strcopy(array_size_code_text), lexer_lexer_for_c_language_token_liste_copy(array_size_code_tokens), fun_param_huh, strcopy(fun_param_code_text), lexer_lexer_for_c_language_token_liste_copy(fun_param_code_tokens), fun_def_huh, strcopy(fun_def_code_text), lexer_lexer_for_c_language_token_liste_copy(fun_def_code_tokens));
}
static void global_symbol_table_push(const char * name, const char * storage_class, const char * inline_class, const char * const_class, const char * signed_class, const char * size_class,   const char * core_type, int indirections_nb, bool_t array_huh, const char * array_size_code_text, const lexer_lexer_for_c_language_token_liste_t * array_size_code_tokens, bool_t fun_param_huh, const char * fun_param_code_text, const lexer_lexer_for_c_language_token_liste_t * fun_param_code_tokens, bool_t fun_def_huh, const char * fun_def_code_text, const lexer_lexer_for_c_language_token_liste_t * fun_def_code_tokens) {
  global_symbol_table_nb = symbol_table_push(global_symbol_table, global_symbol_table_base_index, GLOBAL_SYMBOL_TABLE_SIZE, global_symbol_table_nb, (name), (storage_class), (inline_class), (const_class), (signed_class), (size_class), (core_type), indirections_nb, array_huh, (array_size_code_text), (array_size_code_tokens), fun_param_huh, (fun_param_code_text), (fun_param_code_tokens), fun_def_huh, (fun_def_code_text), (fun_def_code_tokens));
}

static char * symbol_table_elt_string(const symbol_table_elt_t elt) {
  char * retour;
  retour = strcopy("");
  stradd3(&retour, elt.name, " [");
  if (elt.storage_class != NULL) stradd4(&retour, "storage_class: ", elt.storage_class, ", ");
  if (elt.inline_class != NULL) stradd4(&retour, "inline_class: ", elt.inline_class, ", ");
  if (elt.const_class != NULL) stradd4(&retour, "const_class: ", elt.const_class, ", ");
  if (elt.signed_class != NULL) stradd4(&retour, "signed_class: ", elt.signed_class, ", ");
  if (elt.size_class != NULL) stradd4(&retour, "size_class: ", elt.size_class, ", ");
  if (elt.core_type != NULL) stradd4(&retour, "core_type: ", elt.core_type, ", ");
  if (elt.indirections_nb != 0) stradd4(&retour, "indirections_nb: ", int_string(elt.indirections_nb), ", ");
  if (elt.array_huh) stradd4(&retour, "array_size_code_text: ", elt.array_size_code_text, ", ");
  if (elt.fun_param_huh) stradd4(&retour, "fun_param_code_text: ", elt.fun_param_code_text, ", ");
  if (elt.fun_def_huh) stradd4(&retour, "fun_def_code_text: ", elt.fun_def_code_text, ", ");
  stradd2(&retour, "]\n");
  return retour;
}
static char * symbol_table_string(const int base, const int nb, const symbol_table_elt_t * table, const char * name) {
  char * retour;
  retour = strcopy("");
  char * nb_str = NULL;
  asprintf(&nb_str, "%d", nb);
  stradd5(&retour, name, " symbol table (", nb_str, " elements):\n");
  strfree(nb_str);
  for (int i = base; i < base + nb; i++) {
    char * temp;
    temp = symbol_table_elt_string(table[i]);
    char * i_str = NULL;
    asprintf(&i_str, "%04d", i);
    stradd4(&retour, i_str, ": ", temp);
    strfree(i_str);
    strfree(temp);
  }
  return retour;
}
static char * global_symbol_table_string(void) {
  return symbol_table_string(global_symbol_table_base_index, global_symbol_table_nb, global_symbol_table, "Global");
}


static void analyze_one_line_of_the_global_symbol_table(symbol_table_elt_t * elt);
static void analyze_each_line_of_the_global_symbol_table(void);
static void compile_the_code_for_a_constant_array_size(symbol_table_elt_t * elt);
static expression_tree_t * generate_the_tree_for_a_constant_array_size(const lexer_lexer_for_c_language_token_liste_t * const tokens_with_sq_brackets_to_remove);
static void display_expression_tree(const expression_tree_t * tree);
static void display_tree_with_the_dot_description(const char * dot_description);


static const lexer_lexer_for_c_language_token_t * lexer_lexer_for_c_language_token_liste_get_last(const lexer_lexer_for_c_language_token_liste_t * tokens) {
  assert(tokens != NULL);
  if (tokens -> cdr == NULL) return tokens -> car;
  return lexer_lexer_for_c_language_token_liste_get_last(tokens -> cdr);
}

static lexer_lexer_for_c_language_token_liste_t * lexer_lexer_for_c_language_token_liste_get_without_the_last(const lexer_lexer_for_c_language_token_liste_t * tokens) {
  assert(tokens != NULL);
  if (tokens -> cdr == NULL) return NULL;
  return lexer_lexer_for_c_language_token_liste_cons(tokens -> car, lexer_lexer_for_c_language_token_liste_get_without_the_last(tokens -> cdr));
}

static lexer_lexer_for_c_language_token_liste_t * lexer_lexer_for_c_language_token_liste_get_without_the_last_and_the_first(const lexer_lexer_for_c_language_token_liste_t * tokens) {
  assert(tokens != NULL);
  if (tokens -> cdr == NULL) return NULL;
  return lexer_lexer_for_c_language_token_liste_get_without_the_last(tokens -> cdr);
}



struct expression_tree_t {
  const char * type;
#if 0
  const lexer_lexer_for_c_language_token_t * content1;
  const lexer_lexer_for_c_language_token_t * content2;
  const lexer_lexer_for_c_language_token_t * content3;
#else
  lexer_lexer_for_c_language_token_t * content1;
  lexer_lexer_for_c_language_token_t * content2;
  lexer_lexer_for_c_language_token_t * content3;
#endif
  int children_nb;
  struct expression_tree_t * child1;
  struct expression_tree_t * child2;
  struct expression_tree_t * child3;
};

static expression_tree_t * expression_tree_make_on_the_heap(const char * type, const lexer_lexer_for_c_language_token_t * content1, const lexer_lexer_for_c_language_token_t * content2, const lexer_lexer_for_c_language_token_t * content3, int children_nb, expression_tree_t * child1, expression_tree_t * child2, expression_tree_t * child3) {
  expression_tree_t * tree;
  tree = (expression_tree_t *) malloc(sizeof(expression_tree_t));
  bzero(tree, sizeof(expression_tree_t));
  tree -> type = type;
#if 0
  tree -> content1 = content1;
  tree -> content2 = content2;
  tree -> content3 = content3;
#else
  tree -> content1 = lexer_lexer_for_c_language_token_copy(content1);
  tree -> content2 = lexer_lexer_for_c_language_token_copy(content2);
  tree -> content3 = lexer_lexer_for_c_language_token_copy(content3);
#endif
  tree -> children_nb = children_nb;
  tree -> child1 = child1;
  tree -> child2 = child2;
  tree -> child3 = child3;
  return tree;
}

#if 0
#define expression_tree_make_on_the_stack(type, content1, content2, content3, children_nb, child1, child2, child3) (&((expression_tree_t) {.type = type, .content1 = content1, .content2 = content2, .content3 = content3, .children_nb = children_nb, .child1 = child1, .child2 = child2, .child3 = child3}))
#else
#define expression_tree_make_on_the_stack(type, content1, content2, content3, children_nb, child1, child2, child3) (&((expression_tree_t) {.type = type, .content1 = lexer_lexer_for_c_language_token_copy(content1), .content2 = lexer_lexer_for_c_language_token_copy(content2), .content3 = lexer_lexer_for_c_language_token_copy(content3), .children_nb = children_nb, .child1 = child1, .child2 = child2, .child3 = child3}))
#endif


static char * expression_tree_write_a_dot_description_for_a_file_aux(const expression_tree_t * tree, const char * node_name) {
  char * retour;
  retour = strcopy("");
  stradd4(&retour, "  ", node_name, "[label = \"");
#if 1
  stradd3(&retour, tree -> type, "\n\n");
#endif
  //string_char_replace_nocopy(automate_name, '(', 'q');
  //char_string_filtre
#if 0
  char * label1 = (tree -> content1 == NULL ? NULL : char_string_filtre(tree -> content1 -> value));
  char * label2 = (tree -> content2 == NULL ? NULL : char_string_filtre(tree -> content2 -> value));
  char * label3 = (tree -> content3 == NULL ? NULL : char_string_filtre(tree -> content3 -> value));
#else
  char * label1 = (tree -> content1 == NULL ? NULL : string_char_replace(tree -> content1 -> value, '"', '\''));
  char * label2 = (tree -> content2 == NULL ? NULL : string_char_replace(tree -> content2 -> value, '"', '\''));
  char * label3 = (tree -> content3 == NULL ? NULL : string_char_replace(tree -> content3 -> value, '"', '\''));
#endif
  if (tree -> content1 != NULL) stradd2(&retour, label1);
  if (tree -> content2 != NULL) stradd2(&retour, label2);
  if (tree -> content3 != NULL) stradd2(&retour, label3);
  strfree(label1);
  strfree(label2);
  strfree(label3);
  stradd2(&retour, "\"];\n");
  char * name1 = strconcat(node_name, "1");
  char * name2 = strconcat(node_name, "2");
  char * name3 = strconcat(node_name, "3");
  char * temp1 = NULL;
  char * temp2 = NULL;
  char * temp3 = NULL;
  if (tree -> child1 != NULL) temp1 = expression_tree_write_a_dot_description_for_a_file_aux(tree -> child1, name1);
  if (tree -> child2 != NULL) temp2 = expression_tree_write_a_dot_description_for_a_file_aux(tree -> child2, name2);
  if (tree -> child3 != NULL) temp3 = expression_tree_write_a_dot_description_for_a_file_aux(tree -> child3, name3);
  if (tree -> child1 != NULL) stradd6(&retour, "  ", node_name, " -- ", name1, ";\n");
  if (tree -> child2 != NULL) stradd6(&retour, "  ", node_name, " -- ", name2, ";\n");
  if (tree -> child3 != NULL) stradd6(&retour, "  ", node_name, " -- ", name3, ";\n");
  if (tree -> child1 != NULL) stradd2(&retour, temp1);
  if (tree -> child2 != NULL) stradd2(&retour, temp2);
  if (tree -> child3 != NULL) stradd2(&retour, temp3);
  strfree(temp1);
  strfree(temp2);
  strfree(temp3);
  strfree(name1);
  strfree(name2);
  strfree(name3);
  return retour;
}

static char * expression_tree_write_a_dot_description_for_a_file(const expression_tree_t * tree) {
  char * retour;
  retour = strcopy("");
  stradd2(&retour, "graph {\n");
  char * temp;
  temp = expression_tree_write_a_dot_description_for_a_file_aux(tree, "root");
  stradd2(&retour, temp);
  strfree(temp);
  stradd2(&retour, "}\n");
  return retour;
}

struct constant_value_t {
  const char * type;
  char c;
  int i;
  float f;
  double d;
  char * s;
};
typedef struct constant_value_t constant_value_t;

static char * expression_tree_write_a_dot_description_for_a_file_aux(const expression_tree_t * tree, const char * node_name);
static char * expression_tree_write_a_dot_description_for_a_file(const expression_tree_t * tree);
static const char * token_type_of_the_constant_value(const lexer_lexer_for_c_language_token_type_t type);
static const char * expression_tree_compute_constant_value(const expression_tree_t * const tree, constant_value_t * const value);
static const char * expression_tree_compute_constant_value_old(const expression_tree_t * tree, char * const char_ptr, int * const int_ptr, float * const float_ptr, double * const double_ptr, char * (* const string_ptr));

static const char * const CONSTANT_VALUE_TYPE_NULL = NULL;
static const char * const CONSTANT_VALUE_TYPE_CHAR = "CHAR";
static const char * const CONSTANT_VALUE_TYPE_INT = "INT";
static const char * const CONSTANT_VALUE_TYPE_FLOAT = "FLOAT";
static const char * const CONSTANT_VALUE_TYPE_DOUBLE = "DOUBLE";
static const char * const CONSTANT_VALUE_TYPE_IDENT = "IDENT";
static const char * const CONSTANT_VALUE_TYPE_STRING = "STRING";

static void assert_type_of_the_first_token(const lexer_lexer_for_c_language_token_liste_t * tokens, lexer_lexer_for_c_language_token_type_t type);
static void assert_type_of_the_last_token(const lexer_lexer_for_c_language_token_liste_t * tokens, lexer_lexer_for_c_language_token_type_t type);
static token_tree_t * token_liste_2_token_tree(const lexer_lexer_for_c_language_token_liste_t * tokens);
static void * generate_the_tree_for_fun_param(const lexer_lexer_for_c_language_token_liste_t * const tokens_with_round_brackets_to_remove);
static token_tree_t * token_tree_make_on_the_heap(int tokens_nb);
static int token_tree_count(const token_tree_t * tree);
static token_tree_t * token_tree_grouping_paren_bracket_brace(const token_tree_t * const tree_initial);
static void write_asm_code_for_each_line(const char * preprend_str_for_variable_names, const int table_of_strings_size, int * table_of_strings_nb_ptr, char * * table_of_strings, const char * string_label_prepend);
static void write_asm_code_for_one_line(const char * preprend_str_for_variable_names, symbol_table_elt_t * elt, const int table_of_strings_size, int * table_of_strings_nb_ptr, char * * table_of_strings, const char * string_label_prepend);
static void print_asm_code_for_each_line(void);
static void print_asm_code_for_one_line(symbol_table_elt_t * elt);
static int compute_the_size_of_the_local_vars_and_set_the_relative_addresses_in_the_tree(int current_size, statment_tree_t * tree);
enum { PTR_SIZE = 4, CHAR_SIZE = 1, INT_SIZE = 4, SHORT_INT_SIZE = 2, LONG_INT_SIZE = 8, SHORT_SHORT_INT_SIZE = 1, LONG_LONG_INT_SIZE = 16 };
enum { STACK_UNIT_SIZE_IN_BYTES = INT_SIZE };
static const char * const STATMENT_TREE_TYPE_NULL = NULL;
static const char * const STATMENT_TREE_TYPE_SEQUENCE = "SEQUENCE";
static const char * const STATMENT_TREE_TYPE_EXPRESSION = "EXPRESSION";
static const char * const STATMENT_TREE_TYPE_DECLARATION = "DECLARATION";
static const char * const STATMENT_TREE_TYPE_RETURN = "RETURN";
struct statment_tree_t {
  const char * type;
  struct statment_tree_t * seq_stat1;
  struct statment_tree_t * seq_stat2;
  expression_tree_t * expr;
  symbol_table_elt_t * * declarations;
  int declarations_nb;
  int declarations_size;  
  lexer_lexer_for_c_language_token_t * token1;
  lexer_lexer_for_c_language_token_t * token2;
};
static char * expression_tree_write_asm_code(const char * preprend_str_for_variable_names, const expression_tree_t * tree, const int table_of_strings_size, int * table_of_strings_nb_ptr, char * * table_of_strings, const char * string_label_prepend);
static char * expression_tree_write_asm_code_alloca_protected(const char * preprend_str_for_variable_names, const expression_tree_t * tree, const int table_of_strings_size, int * table_of_strings_nb_ptr, char * * table_of_strings, const char * string_label_prepend);
static const char * const EXPRESSION_TREE_TYPE_NULL = NULL;
static const char * const EXPRESSION_TREE_TYPE_LEAF = "LEAF";
static const char * const EXPRESSION_TREE_TYPE_PREFIX_OPERATOR = "PREFIX";
static const char * const EXPRESSION_TREE_TYPE_INFIX_OPERATOR = "INFIX";
static const char * const EXPRESSION_TREE_TYPE_POSTFIX_OPERATOR = "POSTFIX";
static const char * const EXPRESSION_TREE_TYPE_PAREN = "PAREN";
static const char * const EXPRESSION_TREE_TYPE_FUNCALL = "FUNCALL";
static const char * const EXPRESSION_TREE_TYPE_NIL = "NIL";
static char * write_asm_code_for_a_leaf(const lexer_lexer_for_c_language_token_t * token, const int table_of_strings_size, int * table_of_strings_nb_ptr, char * * table_of_strings, const char * string_label_prepend);
static char * write_asm_code_of_prefix_operator(const lexer_lexer_for_c_language_token_type_t type);
static char * write_asm_code_of_infix_operator_alloca_protected(const lexer_lexer_for_c_language_token_type_t type, const char * first_operand);
static char * write_asm_code_of_postfix_operator(const lexer_lexer_for_c_language_token_type_t type);
static char * statment_tree_write_asm_code(const char * preprend_str_for_variable_names, const statment_tree_t * tree, const int table_of_strings_size, int * table_of_strings_nb_ptr, char * * table_of_strings, const char * string_label_prepend);

#if 0
, const int table_of_strings_size, int * table_of_strings_nb_ptr, char * * table_of_strings
, table_of_strings_size, table_of_strings_nb_ptr, table_of_strings
#endif


bool programme_boucle(const int argc, const char * argv[]) {
  const char * test_prog = prog_test_hello7;
  assert(test_prog != NULL);
  fprintf(stderr, "-------------------------------------------------------------------------------\n");
  fprintf(stderr, "%s\n", test_prog);
  fprintf(stderr, "-------------------------------------------------------------------------------\n");

  lexer_lexer_for_c_language_token_liste_t * tokens;
  tokens = lexer_lexer_for_c_language_do_the_job_bang(test_prog);
  //assert(tokens != NULL);
  if (tokens == NULL) {
    int nb_lettres_qui_ont_ete_reconnues = -1;
    tokens = lexer_lexer_for_c_language_analyse_de_la_ligne(test_prog, &nb_lettres_qui_ont_ete_reconnues);
    if (test_prog[nb_lettres_qui_ont_ete_reconnues] != '\0') {
      fprintf(stderr, "Error while reading the C program.\n");
      fprintf(stderr, "I was able to read the first %d characters but I do not recognize the following characters ('%c').\n", nb_lettres_qui_ont_ete_reconnues, test_prog[nb_lettres_qui_ont_ete_reconnues]);
#if 1
      fprintf(stderr, "I already recognized the following tokens:\n");
      const char * tokens_str = lexer_lexer_for_c_language_token_liste_string(tokens);
      assert(tokens_str != NULL);
      puts(tokens_str);
#endif      
      assert(false);
    }
  }
  
  const char * tokens_str = lexer_lexer_for_c_language_token_liste_string(tokens);
  assert(tokens_str != NULL);
#if 0
  puts(tokens_str);
  puts("\n");
#endif
  
  // Pour l'instant, nous oublions les directives.
  // On suppose que tout a été préprocessé correctement.
  
  analyze_to_fill_the_global_symbol_table(tokens);
  lexer_lexer_for_c_language_token_liste_free(tokens);
  
  //fprintf(stderr, "%s", global_symbol_table_string());
  
  
  // Now, we have all the declarations in the global symbol table.
  // And we have to compile each symbol in the global symbol table.
  
  // identifier[assigment-expression]
  // assigment-expression: (p. 423)
  //   | conditional-expression
  //   | unary-expression assignment-operator assignment-expression
  //
  // «static void f(void) { int a = 3; int b[a = 4];}» is C compliant.
  // However «int b[a = 4];» is not C compliant on top-level.
  //
  // An assignment-expression is the outermost expression.
  // Any expression is an assignment-expression.
  // "Expression" in the C99 draft is larger because it considers the comma-list…!
  //
  // p. 128: "an expression specifying an array size must have the int type."
  // p. 128: "If an identifier is declared to be an object with static storage duration, it shall not have a variable length array type."
  // p. 128: "If the size is an integer constant expression and the element type has a known constant size, the array type is not a variable length array type; otherwise, the array type is a variable length array type."
  //
  // Is there a definition of "integer constant expression"?
  // p. 107: "6.6 Constant expressions"
  // p. 107: "A constant expression can be evaluated during translation rather than runtime, and accordingly may be used in any place that a constant may be."
  // p. 107: "Constant expressions shall not contain assignment, increment, decrement, function-call, or comma operators."
  // p. 107: footnote 99: "An integer constant expression is used to specify the size of a bit-field member of a structure, the value of an enumeration constant, the size of an array, or the value of a case constant."
  // => An expression that we can evaluate at compile time, and it is needed to be evaluated at compile-time (size of a static array! case! enum constant!).
  
  analyze_each_line_of_the_global_symbol_table();

#if 0
//% ☺ and ☹
  fprintf(stderr, "VICTORY!!! Everything was analyzed and recognized!!! ☺ \n");
  fprintf(stderr, "Now let's think about the generation of the code.\n");
#endif


  //cf. srt0.S de boot
  //	.code16 -> mode réel
  //	.code32 -> après activation du mode protégé
#if 0
  __asm__ {
    pushl	%cs
      popl	%ds
      addr32 data32 lgdt	(Gdtr - LINKADDR)
      movl	%cr0, %eax
      orl $CR0_PE, %eax
      data32 movl %eax, %cr0 // passage en mode protégé
      data32 ljmp $8, $1f
      1:
    .code32
      }
#endif

  // compute the size and set the local address of each var in each function

  // fill the global string table

  // prepend variable names
  //const char * preprend_str_for_variable_names = "_";
  const char * preprend_str_for_variable_names = "_mycc_";
  //return write_asm_code_for_a_leaf(tree -> content1, table_of_strings_size, table_of_strings_nb_ptr, table_of_strings, "Lstr");
  enum { TABLE_OF_STRINGS_SIZE = 256 };
  int table_of_strings_nb = 0;
  char * table_of_strings[TABLE_OF_STRINGS_SIZE];
  bzero(table_of_strings, TABLE_OF_STRINGS_SIZE * sizeof(char *));
  const char * string_label_prepend = "Lstr";
  write_asm_code_for_each_line(preprend_str_for_variable_names, TABLE_OF_STRINGS_SIZE, &table_of_strings_nb, table_of_strings, string_label_prepend);
#if 1
  fprintf(stderr, "NB STRINGS: %d\n", table_of_strings_nb);
  for (int i = 0; i < table_of_strings_nb; i++)
    fprintf(stderr, "STRINGS[%d]: %s\n", i, table_of_strings[i]);    
  fprintf(stderr, "-------------------------------------------------------------------------------\n");
#endif
  
  
  print_asm_code_for_each_line();
  {
    printf("\t" ".text" "\n");
    for (int i = 0; i < table_of_strings_nb; i++) {
      printf("%s%d:\n", string_label_prepend, i);
      printf("\t" ".asciz %s\n", table_of_strings[i]);
    }
  }

  // REPNE SCASB
  // compare ES:[EDI] with AL
  // stop ECX is null or value found
  // EDI is automatically incremented or decremented according to DF flags (0: inc; 1: dec)
  // STD -> DF := 1 (dec)
  // CLD -> DF := 0 (inc)
  const char strlen_code[] = 
    ".text\n"
    "_mycc_strlen:\n"
    "movl 4(%esp),%edi\n"
    "xorl %eax,%eax\n"
    "xorl %ecx,%ecx\n"
    "decl %ecx\n"
    "cld\n"
    "repne scasb\n"
    "decl %edi\n"
    "subl 4(%esp),%edi\n"
    "movl %edi,%eax\n"
    //"movl $8,%eax\n" // TODO HERE XXX
    "ret\n"
    ;

  // stdout: 1
  // stdin: 0
  // stderr: 2
  // int _write(int fd, void *buf, int len);
#if 0
  const char puts_code[] = 
    ".text\n"
    "_mycc_puts:\n"
    "pushl 4(%esp)\n"
    "call _mycc_strlen\n"
    "addl $4,%esp\n"
    "pushl %eax\n"
    "pushl 4(%esp)\n"
    "pushl $1\n"
    //"call _write\n"
    "addl $12,%esp\n"
    "ret\n"
    ;
#elif 0
  const char puts_code[] = 
    ".text\n"
    "_mycc_puts:\n"
    "pushl %ebp\n"
    "movl %esp,%ebp\n"
    "\n"
    "pushl 8(%ebp)\n"
    "call _mycc_strlen\n"
    "addl $4,%esp\n"
    "\n"
    "movl %eax,StackAlignmentEAX\n"
    "movl %esp,StackAlignment\n"
    "subl $16,%esp\n"
    "movl %esp,%eax\n"
    "andb $240,%al\n"
    "orb InitialStackAlignment,%al\n"
    "movl %eax,%esp\n"
    "movl StackAlignmentEAX,%eax\n"
    "\n"
    "pushl %eax\n"
    "pushl 8(%ebp)\n"
    "pushl $1\n"
    "call _write\n"
    "addl $12,%esp\n"
    "\n"
    "movl StackAlignment,%esp\n"
    "\n"
    "movl %ebp,%esp\n"
    "popl %ebp\n"
    "ret\n"
;
#elif 1
  const char puts_code[] = 
    ".text\n"
    "_mycc_puts:\n"
    "pushl %ebp\n"
    "movl %esp,%ebp\n"
    "\n"
    "movl %esp,%eax\n"
    "subl $16,%eax\n"
    "andb $240,%al\n"
    "orb InitialStackAlignment,%al\n"
    "movl %eax,%esp\n"
    "\n"
    "pushl 8(%ebp)\n"
    "call _mycc_strlen\n"
    "addl $4,%esp\n"
    "\n"
    "pushl %eax\n"
    "pushl 8(%ebp)\n"
    "pushl $1\n"
    "call _write\n"
    "addl $12,%esp\n"
    "\n"
    "movl %ebp,%esp\n"
    "popl %ebp\n"
    "ret\n"
;
#else
  const char puts_code[] = 
    ".text\n"
    "_mycc_puts:\n"
    "pushl %ebp\n"
    "movl %esp,%ebp\n"
    "\n"
    "movb InitialStackAlignment,%ah\n"
    "subl $16,%esp\n"
    "movl %esp,%edx\n"
    "shr $3,%dx\n"
    "shld $3,%ax,%dx\n"
    "movl %edx,%esp\n"
    "\n"
    "pushl 8(%ebp)\n"
    "call _mycc_strlen\n"
    "addl $4,%esp\n"
    "\n"
    "pushl %eax\n"
    "pushl 8(%ebp)\n"
    "pushl $1\n"
    "call _write\n"
    "addl $12,%esp\n"
    "\n"
    "movl %ebp,%esp\n"
    "popl %ebp\n"
    "ret\n"
;
#endif


  const char underscore_main_code[] = 
#if 1
    "\n"
    ".data\n"
    "InitialStackAlignment:\n"
    ".byte 0\n"
    ".byte 0\n"
    ".byte 0\n"
    ".byte 0\n"
    "\n"
    ".text\n"
    ".globl _main\n"
    "_main:\n"
    "xorl %eax,%eax\n"
    "movl %eax,InitialStackAlignment\n"
    "movl %esp,%eax\n"
    "andb $15,%al\n"
    "movb %al,InitialStackAlignment\n"
    "jmp _mycc_main\n"
#else
    "\n"
    ".data\n"
    "InitialStackAlignment:\n"
    ".byte 0\n"
    ".byte 0\n"
    ".byte 0\n"
    ".byte 0\n"
    "\n"
    ".text\n"
    ".globl _main\n"
    "_main:\n"
    "xorl %eax,%eax\n"
    "movl %eax,InitialStackAlignment\n"
    "movl %esp,%eax\n"
    "shl $5,%ax\n"
    "movb %ah,InitialStackAlignment\n"
    "jmp _mycc_main\n"
#endif
    ;

  // make && ./run | gcc -arch i386 -x assembler - && ./a.out 


  // make && ../run | as -g -arch i386 && ld a.out -lSystem -lcrt1.10.6.o
  // gdb a.out
  // 
  // Program received signal EXC_BAD_ACCESS, Could not access memory.
  // Reason: 13 at address: 0x00000000
  // 0x9c3a7820 in misaligned_stack_error_ ()
  //
  // puis 'bt' dans gdb and then gdb seg fault

  printf("%s\n", strlen_code);
  printf("%s\n", puts_code);
  printf("%s\n", underscore_main_code);

  
  return false;
}


static void print_asm_code_for_each_line(void) {
  //fputs("-------------------------------------------------------------------------------\n", stdout);
  for (int i = global_symbol_table_base_index; i < global_symbol_table_base_index + global_symbol_table_nb; i++) {
    print_asm_code_for_one_line(&(global_symbol_table[i]));
  }
  //fputs("-------------------------------------------------------------------------------\n", stdout);
}

static void print_asm_code_for_one_line(symbol_table_elt_t * elt) {
  if (elt -> storage_class == STORAGE_CLASS_SPECIFIER_TYPEDEF) return;

  // We are neither a typdef nor a function => data!
  if (not(elt -> fun_param_huh) && not(elt -> fun_def_huh)) {
    fputs(elt -> asm_code, stdout);
    return;
  }

  if (elt -> fun_param_huh) {
    // Nothing to do here.
    // This part is used when calling a function and when running a function.
  }
  
  if (elt -> fun_def_huh) {
    fputs(elt -> asm_code, stdout);
    return;
  }
}




static int compute_the_size_of_the_root_type(const symbol_table_elt_t * elt) {
  if (elt -> indirections_nb > 0) return PTR_SIZE;
  assert(elt -> indirections_nb == 0);
  if (elt -> core_type == CORE_TYPE_SPECIFIER_CHAR) return CHAR_SIZE;
  if (elt -> core_type == CORE_TYPE_SPECIFIER_INT) {
    if (elt -> size_class == SIZE_CLASS_SPECIFIER_NULL) return INT_SIZE;
    if (elt -> size_class == SIZE_CLASS_SPECIFIER_SHORT_SHORT) return SHORT_SHORT_INT_SIZE;
    if (elt -> size_class == SIZE_CLASS_SPECIFIER_SHORT) return SHORT_INT_SIZE;
    if (elt -> size_class == SIZE_CLASS_SPECIFIER_LONG) return LONG_INT_SIZE;
    if (elt -> size_class == SIZE_CLASS_SPECIFIER_LONG_LONG) return LONG_LONG_INT_SIZE;
  }
  assert(false);
}


static void write_asm_code_for_each_line(const char * preprend_str_for_variable_names, const int table_of_strings_size, int * table_of_strings_nb_ptr, char * * table_of_strings, const char * string_label_prepend) {
  for (int i = global_symbol_table_base_index; i < global_symbol_table_base_index + global_symbol_table_nb; i++) {
    //printf("Write the assembler code %d -- ", i);
    write_asm_code_for_one_line(preprend_str_for_variable_names, &(global_symbol_table[i]), table_of_strings_size, table_of_strings_nb_ptr, table_of_strings, string_label_prepend);
    //printf("\n");
  }
}


static void write_asm_code_for_one_line(const char * preprend_str_for_variable_names, symbol_table_elt_t * elt, const int table_of_strings_size, int * table_of_strings_nb_ptr, char * * table_of_strings, const char * string_label_prepend) {
  if (elt -> storage_class == STORAGE_CLASS_SPECIFIER_TYPEDEF) return;
  
  char * asm_code;
  asm_code = strcopy("");
  if (not(elt -> fun_param_huh) && not(elt -> fun_def_huh)) {
    stradd2(&asm_code, "\t .data\n");
    if (elt -> storage_class == STORAGE_CLASS_SPECIFIER_EXTERN || elt -> storage_class == STORAGE_CLASS_SPECIFIER_NULL) {
      stradd5(&asm_code, "\t .globl ", preprend_str_for_variable_names, elt -> name, "\n");
    }
    // We are in a global context.
    // So, this is mainly obvious: 
    //  - We have to compute the size of the type.
    //  - The size of the array is already computed.
    int size_of_the_root_type = compute_the_size_of_the_root_type(elt);
    if (elt -> array_huh) {
      if (not(elt -> can_compute_array_size_constant_value_huh)) {
	assert(false);
      }
      size_of_the_root_type *= elt -> array_size_constant_value;
      if (elt -> array_size_constant_value == 0) size_of_the_root_type = 1;
    }
    stradd4(&asm_code, preprend_str_for_variable_names, elt -> name, ": \n");
    for (int i = 0; i < size_of_the_root_type; i++)
      stradd2(&asm_code, "\t .byte 0\n");
    //printf("asm_code: \n%s\n", asm_code);
    elt -> asm_code = asm_code;
    return;
  }

#if 0
  // BEWARE of tentative definitions (page 144 or 156)
  //
  // Specifically, "int my_var;" is different from "extern int my_var;" but similar to "extern int my_var = 0;".
  //
  int i1 = 1;         // definition, external linkage
  static int i2 = 2;  // definition, internal linkage
  extern int i3 = 3;  // definition, external linkage
  int i4;             // tentative definition, external linkage 
  static int i5;      // tentative definition, internal linkage
  
  int i1; // valid tentative definition, refers to previous 
  int i2; // 6.2.2 renders undefined, linkage disagreement 
  int i3; // valid tentative definition, refers to previous 
  int i4; // valid tentative definition, refers to previous 
  int i5; // 6.2.2 renders undefined, linkage disagreement
  
  extern int i1; // refers to previous, whose linkage is external 
  extern int i2; // refers to previous, whose linkage is internal  // THIS ONE IS VERY CONFUSING! For me, it is an error.
  extern int i3; // refers to previous, whose linkage is external 
  extern int i4; // refers to previous, whose linkage is external 
  extern int i5; // refers to previous, whose linkage is internal  // THIS ONE IS VERY CONFUSING! For me, it is an error.
#endif
  
  
  if (elt -> fun_param_huh) {
    // Nothing to do here.
    // This part is used when calling a function and when running a function.
  }
  
  
  if (elt -> fun_def_huh) {
    // Alright! Here is the fun part of the compiler.
    // The arguments are on the stack (on top: IP, then first arg, then 2nd arg, etc.).
    // The return value will be in EAX.
    // The caller is the one which deallocates the arg on the stack (not the callee function).
    stradd2(&asm_code, "\t" ".text" "\n");
    if (elt -> storage_class == STORAGE_CLASS_SPECIFIER_EXTERN || elt -> storage_class == STORAGE_CLASS_SPECIFIER_NULL) {
      stradd5(&asm_code, "\t" ".globl ", preprend_str_for_variable_names, elt -> name, "\n");
    }
    stradd4(&asm_code, preprend_str_for_variable_names, elt -> name, ": \n");
    stradd2(&asm_code, "\t" "pushl %ebp" "\n");
    stradd2(&asm_code, "\t" "movl %esp, %ebp" "\n");
    
    // Now we have to allocate the size on the stack for the local variables.
    // So, let's compute this size!
    //const int size_of_the_local_var = -1;//2359;
    const int size_of_the_local_var = compute_the_size_of_the_local_vars_and_set_the_relative_addresses_in_the_tree(0, elt -> fun_def_code_tree);
    assert(size_of_the_local_var >= 0);
#if 0
    fprintf(stderr, "LOCALS: %d\n", size_of_the_local_var);
    fflush(NULL);
    assert(false);
#endif
    assert((size_of_the_local_var % STACK_UNIT_SIZE_IN_BYTES) == 0); 
    if (size_of_the_local_var > 0)
      stradd4(&asm_code, "\t subl ", int4_string_on_the_stack(size_of_the_local_var), ", %esp\n");
    
    stradd2(&asm_code, "\t nop\n");

    char * fun_def_code_asm = NULL;
    fun_def_code_asm = statment_tree_write_asm_code(preprend_str_for_variable_names, elt -> fun_def_code_tree, table_of_strings_size, table_of_strings_nb_ptr, table_of_strings, string_label_prepend);
    stradd2(&asm_code, fun_def_code_asm);
    strfree(fun_def_code_asm);
    
    stradd2(&asm_code, "\t" "movl %ebp, %esp" "\n");
    stradd2(&asm_code, "\t" "popl %ebp" "\n");
    stradd2(&asm_code, "\t" "ret" "\n");
    
    //printf("asm_code: \n%s\n", asm_code);
    elt -> asm_code = asm_code;
    return;
  }
}



#if 0
    static const char * const STATMENT_TREE_TYPE_NULL = NULL;
    static const char * const STATMENT_TREE_TYPE_SEQUENCE = "SEQUENCE";
    static const char * const STATMENT_TREE_TYPE_EXPRESSION = "EXPRESSION";
    static const char * const STATMENT_TREE_TYPE_DECLARATION = "DECLARATION";
    static const char * const STATMENT_TREE_TYPE_RETURN = "RETURN";
#endif
static char * statment_tree_write_asm_code(const char * preprend_str_for_variable_names, const statment_tree_t * tree, const int table_of_strings_size, int * table_of_strings_nb_ptr, char * * table_of_strings, const char * string_label_prepend) {
  assert(tree != NULL);
  do {
    assert(tree -> type != STATMENT_TREE_TYPE_NULL);
    if (tree -> type == STATMENT_TREE_TYPE_SEQUENCE) {
      char * child1_asm_code = statment_tree_write_asm_code(preprend_str_for_variable_names, tree -> seq_stat1, table_of_strings_size, table_of_strings_nb_ptr, table_of_strings, string_label_prepend);
      char * child2_asm_code = statment_tree_write_asm_code(preprend_str_for_variable_names, tree -> seq_stat2, table_of_strings_size, table_of_strings_nb_ptr, table_of_strings, string_label_prepend);
      char * retour = NULL;
      retour = strconcat2(child1_asm_code, child2_asm_code);
      strfree(child1_asm_code);
      strfree(child2_asm_code);
      return retour;
    }
	
    if (tree -> type == STATMENT_TREE_TYPE_EXPRESSION) 
      return expression_tree_write_asm_code(preprend_str_for_variable_names, tree -> expr, table_of_strings_size, table_of_strings_nb_ptr, table_of_strings, string_label_prepend);
	
    if (tree -> type == STATMENT_TREE_TYPE_DECLARATION) {
      // We have to do sthg only if the variable is an array whose type is determined at run-time:
      //  1. compute the size of the array
      //  2. allocate the space
      //  3. set the address of the pointer
#if 0
      struct symbol_table_elt_t * declarations;
      int declarations_nb;
      int declarations_size;
#endif
      char * retour = strcopy("");
      for (int i = 0; i < tree -> declarations_nb; i++) {
	symbol_table_elt_t * elt = tree -> declarations[i];
	if (not(elt -> array_huh)) continue;
	if (elt -> can_compute_array_size_constant_value_huh) continue;
	// Ok, here we are. Let's go!
	char * array_size_code_asm = expression_tree_write_asm_code(preprend_str_for_variable_names, elt -> array_size_code_tree, table_of_strings_size, table_of_strings_nb_ptr, table_of_strings, string_label_prepend);
	const char * asm_to_allocate_space = "\t subl %eax, %esp\n";
	char * asm_to_set_the_pointer = strconcat3("\t movl %esp, -", int4_string_on_the_stack(elt -> relative_addr_allocated), "(%ebp)\n");
	char * asm_total = NULL;
	asm_total = strconcat3(array_size_code_asm, asm_to_allocate_space, asm_to_set_the_pointer);
	strfree(array_size_code_asm);
	strfree(asm_to_set_the_pointer);
	elt -> asm_code = asm_total;
	stradd2(&retour, asm_total);
      }
      return retour;
    }

    if (tree -> type == STATMENT_TREE_TYPE_RETURN) {
      char * child = expression_tree_write_asm_code(preprend_str_for_variable_names, tree -> expr, table_of_strings_size, table_of_strings_nb_ptr, table_of_strings, string_label_prepend);
      char * retour = NULL;
      retour = strconcat2(child, 
			  "\t" "movl %ebp, %esp" "\n"  
			  "\t" "popl %ebp" "\n"  
			  "\t" "ret" "\n");
      strfree(child);
      return retour;
    }
	
    assert(false);
  } while (false);
}


static int roundup(const int n, const int divisor) {
  assert(n >= 0);
  assert(divisor > 0);
  const int remainder = (n % divisor);
  if (remainder == 0) return n;
  return (n - remainder) + divisor;
}
static int local_stack_alloc(int * current_top, const int size_requested) {
  return (*current_top) += roundup(size_requested, STACK_UNIT_SIZE_IN_BYTES); 
}





static char * expression_tree_write_asm_code(const char * preprend_str_for_variable_names, const expression_tree_t * tree, const int table_of_strings_size, int * table_of_strings_nb_ptr, char * * table_of_strings, const char * string_label_prepend) {
  return expression_tree_write_asm_code_alloca_protected(preprend_str_for_variable_names, tree, table_of_strings_size, table_of_strings_nb_ptr, table_of_strings, string_label_prepend);
}

static char * expression_tree_write_asm_code_alloca_protected(const char * preprend_str_for_variable_names, const expression_tree_t * tree, const int table_of_strings_size, int * table_of_strings_nb_ptr, char * * table_of_strings, const char * string_label_prepend) {
  assert(tree != NULL);
  assert(tree -> type != EXPRESSION_TREE_TYPE_NULL);
  assert(table_of_strings != NULL);
      
  do {
    if (tree -> type == EXPRESSION_TREE_TYPE_LEAF) {
      return write_asm_code_for_a_leaf(tree -> content1, table_of_strings_size, table_of_strings_nb_ptr, table_of_strings, string_label_prepend);
    }
    if (tree -> type == EXPRESSION_TREE_TYPE_PREFIX_OPERATOR) {
      char * child1_asm = expression_tree_write_asm_code_alloca_protected(preprend_str_for_variable_names, tree -> child1, table_of_strings_size, table_of_strings_nb_ptr, table_of_strings, string_label_prepend);
      char * operation_asm = write_asm_code_of_prefix_operator(tree -> content1 -> type);
      char * expr_asm = NULL;
      expr_asm = strconcat2(child1_asm, operation_asm);
      strfree(operation_asm);
      strfree(child1_asm);
      return expr_asm;
    }
    if (tree -> type == EXPRESSION_TREE_TYPE_INFIX_OPERATOR) {
      char * child1_asm = expression_tree_write_asm_code_alloca_protected(preprend_str_for_variable_names, tree -> child1, table_of_strings_size, table_of_strings_nb_ptr, table_of_strings, string_label_prepend);
      char * child2_asm = expression_tree_write_asm_code_alloca_protected(preprend_str_for_variable_names, tree -> child2, table_of_strings_size, table_of_strings_nb_ptr, table_of_strings, string_label_prepend);
      const char * alloca_protection_prologue = 
	"\t pushl %ebx\n"
	"\t movl %esp,%ebx\n"
	"\t pushl %eax\n";
      char * first_operand_alloca_protected = strconcat3("-", int4_string_on_the_stack(1*STACK_UNIT_SIZE_IN_BYTES), "(%ebx)");
      char * alloca_protection_interlude = strconcat3("\t movl %eax, ", first_operand_alloca_protected, "\n");
      const char * alloca_protection_epilogue = "\t movl (%ebx),%ebx\n";
      char * operation_asm_alloca_protected = write_asm_code_of_infix_operator_alloca_protected(tree -> content1 -> type, first_operand_alloca_protected);
      // TODO XXX does not work for a lvalue 
      char * expr_asm = NULL;
      expr_asm = strconcat6(alloca_protection_prologue, child1_asm, alloca_protection_interlude, child2_asm, operation_asm_alloca_protected, alloca_protection_epilogue);
      strfree(operation_asm_alloca_protected);
      strfree(alloca_protection_interlude);
      strfree(first_operand_alloca_protected);
      strfree(child2_asm);
      strfree(child1_asm);
      return expr_asm;
    }
    if (tree -> type == EXPRESSION_TREE_TYPE_POSTFIX_OPERATOR) {
      char * child1_asm = expression_tree_write_asm_code_alloca_protected(preprend_str_for_variable_names, tree -> child1, table_of_strings_size, table_of_strings_nb_ptr, table_of_strings, string_label_prepend);
      char * operation_asm = write_asm_code_of_postfix_operator(tree -> content1 -> type);
      char * expr_asm = NULL;
      expr_asm = strconcat2(child1_asm, operation_asm);
      strfree(operation_asm);
      strfree(child1_asm);
      return expr_asm;
    }
    if (tree -> type == EXPRESSION_TREE_TYPE_PAREN) {
      return expression_tree_write_asm_code_alloca_protected(preprend_str_for_variable_names, tree -> child1, table_of_strings_size, table_of_strings_nb_ptr, table_of_strings, string_label_prepend);
    }
    if (tree -> type == EXPRESSION_TREE_TYPE_FUNCALL) {
      assert(tree -> child1 -> type == EXPRESSION_TREE_TYPE_LEAF);
      assert(tree -> child1 -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT);
      // TODO XXX on peut avoir un tableau contenant des pointeurs vers des fonctions, ou une fonction renvoyant un pointeur vers une fonction, etc.
      const char * ident = tree -> child1 -> content1 -> value;
      if (tree -> child2 -> type == EXPRESSION_TREE_TYPE_NIL) {
	return strconcat4("\t" "call ", preprend_str_for_variable_names, ident, "\n");
      }
      assert(tree -> child2 -> type == EXPRESSION_TREE_TYPE_PAREN);
      // Mmmm… We have to flatten the arguments.
      // First, let's count the number of arguments.
      int arg_nb = 1;
      expression_tree_t * current_arg = tree -> child2 -> child1;
      while (current_arg -> type == EXPRESSION_TREE_TYPE_INFIX_OPERATOR && current_arg -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA)
	arg_nb++, current_arg = current_arg -> child2;
      // TODO XXX check le nombre d'arguments avec la table des symboles.
      const expression_tree_t * arg_tree[arg_nb];
      bzero(arg_tree, arg_nb*(sizeof(expression_tree_t *)));
      // Now fill the array.
      current_arg = tree -> child2 -> child1;
      for (int i = 0; i < arg_nb-1; i++) 
	arg_tree[i] = current_arg -> child1;
      assert(not(current_arg -> type == EXPRESSION_TREE_TYPE_INFIX_OPERATOR && current_arg -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA));
      arg_tree[arg_nb-1] = current_arg;
      // Now produce the code!
      char * arg_asm[arg_nb];
      for (int i = 0; i < arg_nb; i++) 
	arg_asm[i] = expression_tree_write_asm_code_alloca_protected(preprend_str_for_variable_names, arg_tree[i], table_of_strings_size, table_of_strings_nb_ptr, table_of_strings, string_label_prepend);
      char * alloca_protection_prologue = strconcat3("\t" "pushl %ebx" "\n"
						     "\t" "movl %esp, %ebx" "\n"
						     "\t" "subl $", int4_string_on_the_stack(arg_nb*STACK_UNIT_SIZE_IN_BYTES), ", %esp" "\n");
      const char * alloca_protection_epilogue = "\t" "movl (%ebx), %ebx" "\n";
      //char * first_operand_alloca_protected = strconcat3("-", int4_string_on_the_stack(1*STACK_UNIT_SIZE_IN_BYTES), "(%ebx)");
      //char * alloca_protection_interlude = strconcat3("\t movl %eax, ", first_operand_alloca_protected, "\n");
      char * alloca_protection_interlude[arg_nb];
      for (int i = 0; i < arg_nb; i++) {
	alloca_protection_interlude[i] = strconcat3("\t" "movl %eax, -", int4_string_on_the_stack((arg_nb-i)*STACK_UNIT_SIZE_IN_BYTES), "(%ebx)" "\n");
      }
      char * alloca_protection_push_args_for_call[arg_nb];
      for (int i = 0; i < arg_nb; i++) {
	alloca_protection_push_args_for_call[i] = strconcat3("\t" "pushl -", int4_string_on_the_stack((i+1)*STACK_UNIT_SIZE_IN_BYTES), "(%ebx)" "\n");
      }
      char * unpush_args = strconcat3("\t" "addl $", int4_string_on_the_stack(arg_nb*STACK_UNIT_SIZE_IN_BYTES),", %esp" "\n");
      char * call_asm = NULL;
      call_asm = strcopy(alloca_protection_prologue);
      for (int i = 0; i < arg_nb; i++) {
	stradd2(&call_asm, arg_asm[i]);
	stradd2(&call_asm, alloca_protection_interlude[i]);
      }
      for (int i = 0; i < arg_nb; i++) {
	stradd2(&call_asm, alloca_protection_push_args_for_call[i]);
      }
      stradd2(&call_asm, alloca_protection_epilogue);
      stradd5(&call_asm, "\t" "call ", preprend_str_for_variable_names, ident, "\n");
      stradd2(&call_asm, unpush_args);
      
      for (int i = 0; i < arg_nb; i++) {
	strfree(arg_asm[i]);
	strfree(alloca_protection_interlude[i]);
	strfree(alloca_protection_push_args_for_call[i]);
      } 
      strfree(alloca_protection_prologue);
      //strfree(alloca_protection_epilogue);
      strfree(unpush_args);
      
      return call_asm;
    }
	
    assert(false);
  } while (false);
  assert(false);
  return NULL;
}
    
static char * write_asm_code_for_a_leaf(const lexer_lexer_for_c_language_token_t * token, const int table_of_strings_size, int * table_of_strings_nb_ptr, char * * table_of_strings, const char * string_label_prepend) {
  switch (token -> type) {
  default: assert(false); return NULL; break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BLANK: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_MULTILINES: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_ONELINE_CPP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MONO_LINE: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MULTI_LINES: 
    assert(false);
    break;
	  
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT: assert(false); break;
	  
    // Values following $ are decimal:
    //   echo "movl $$19,%eax" | as && hexdump a.out
    //   echo "movl $$20,%eax" | as && hexdump a.out
    //
    // TODO XXX
    // Well, I did not figure out a way to specify a number in other base.
    // I will have to write a converter…!
    //

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_ZERO: return strconcat1("\t" "xorl %eax, %eax" "\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC: return strconcat3("\t" "movl $", token -> value, ", %eax" "\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC_V2: return strconcat3("\t" "movl $", &(token -> value[2]), ", %eax" "\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_HEX: assert(false); return strconcat3("\t" "movl $", int_string_hex_2_int_string_dec__stack(token -> value), ", %eax" "\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_BIN:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VCC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_WITH_EXP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_HEX_WITH_EXP:
    assert(false);
    return NULL;
    break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE: return strconcat3("\t" "movl $", int4_string_on_the_stack(token -> value[1]), ", %eax\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_ESCAPE: return strconcat3("\t" "movl $", int4_string_on_the_stack(char_escape_str_2_char(token -> value)), ", %eax\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING: {
    // echo "int a = 'c'; int b = 2; void f(void) { int c = (a + b + 'c'); const char * u1 = \"Hello World1\"; const char * u2 = \"Hello World2\"; }" |   gcc -std=c99 -O0 -fno-builtin-alloca -mpush-args -x c -S -o - -  -arch i386 | head -40 
    assert((*table_of_strings_nb_ptr) < table_of_strings_size);
    table_of_strings[(*table_of_strings_nb_ptr)] = strcopy(token -> value);
    (*table_of_strings_nb_ptr)++;
    return strconcat4("\t" "leal ", string_label_prepend, int4_string_on_the_stack((*table_of_strings_nb_ptr)-1), ", %eax\n"); break;
  } break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE_NEWLINE: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_EMPTY:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_ENDED_BY_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE_ENDED_BY_NEWLINE:
    assert(false);
    return NULL;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACE:
    assert(false);
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ELLIPSIS:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON:
    assert(false);
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BANG_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_TILDE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_MINUS_OPERARTOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COLON_OPERATOR:
    assert(false);
    break;


  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_OPERATOR: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PIPE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HAT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_LSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RSHIFT_OPERATOR:

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RDIV_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PERCENT_OPERATOR:

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PIPE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_POINT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ARROW_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_EQUAL_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIFFERENT_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OR_EQUAL_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OR_EQUAL_OPERATOR:
    assert(false);
    break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_STAR_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_MINUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_LSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_HAT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PIPE_OPERATOR:

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RDIV_OPERATOR: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERCENT_OPERATOR:
    assert(false);
    return NULL;
    break;
  }

  assert(false);
  return NULL;
}

 
    
    
static char * write_asm_code_of_prefix_operator(const lexer_lexer_for_c_language_token_type_t type) {
  switch (type) {
  default: assert(false); return NULL; break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BLANK: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_MULTILINES: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_ONELINE_CPP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MONO_LINE: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MULTI_LINES: 
    assert(false);
    // must have been already skipped and processed
    break;
	  
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_ZERO:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC_V2:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_HEX:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_BIN:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VCC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_WITH_EXP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_HEX_WITH_EXP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_EMPTY:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_ESCAPE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_ENDED_BY_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE_ENDED_BY_NEWLINE:
    assert(false); 
    return NULL;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACE:
    assert(false); 
    return NULL;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ELLIPSIS:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON:
    assert(false); 
    return NULL;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR: return strconcat1("\t" "movl (%eax), %eax\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_OPERATOR: return strconcat1(""); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_OPERATOR: return strconcat1("\t" "negl %eax" "\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_TILDE_OPERATOR: return strconcat1("\t" "notl %eax" "\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BANG_OPERATOR: return strconcat1("\t" "movl %eax, %ecx" "\n" 
									      "\t" "xorl %eax, %eax" "\n" 
									      "\t" "orl %ecx, %ecx" "\n" 
									      "\t" "setz %al" "\n"); break;
    // TODO: lvalue!
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PERLUETE_OPERATOR: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_MINUS_OPERARTOR:
    assert(false); return NULL; break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PIPE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HAT_OPERATOR:
    assert(false); 
    return NULL;
    break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_POINT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ARROW_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RDIV_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PIPE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_EQUAL_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PERCENT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIFFERENT_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OR_EQUAL_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OR_EQUAL_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_LSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COLON_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_STAR_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RDIV_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERCENT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_MINUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_LSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_HAT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PIPE_OPERATOR:
    assert(false); 
    return NULL;
    break;
  }

  assert(false);
  return NULL;
}

 
    
static char * write_asm_code_of_postfix_operator(const lexer_lexer_for_c_language_token_type_t type) {
  switch (type) {
  default: assert(false); return NULL; break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BLANK: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_MULTILINES: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_ONELINE_CPP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MONO_LINE: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MULTI_LINES: 
    assert(false); return NULL; break;
	  
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_ZERO:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC_V2:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_HEX:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_BIN:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VCC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_WITH_EXP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_HEX_WITH_EXP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_EMPTY:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_ESCAPE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_ENDED_BY_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE_ENDED_BY_NEWLINE:
    assert(false); return NULL; break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACE:
    assert(false); return NULL; break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ELLIPSIS:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON:
    assert(false); return NULL; break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_OPERATOR: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_TILDE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BANG_OPERATOR:
    assert(false); return NULL; break;

    // TODO: lvalue!
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_MINUS_OPERARTOR:
    assert(false); return NULL; break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PIPE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HAT_OPERATOR:
    assert(false); return NULL; break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_POINT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ARROW_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RDIV_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PIPE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_EQUAL_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PERCENT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIFFERENT_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OR_EQUAL_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OR_EQUAL_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_LSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COLON_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_STAR_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RDIV_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERCENT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_MINUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_LSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_HAT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PIPE_OPERATOR:
    assert(false); return NULL; break;
  }

  assert(false);
  return NULL;
}

 
    
static char * write_asm_code_of_infix_operator_alloca_protected(const lexer_lexer_for_c_language_token_type_t type, const char * first_operand) {
  switch (type) {
  default: assert(false); return false; break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BLANK: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_MULTILINES: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_ONELINE_CPP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MONO_LINE: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MULTI_LINES: 
    assert(false);
    break;
	  
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_ZERO:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC_V2:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_HEX:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_BIN:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VCC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_WITH_EXP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_HEX_WITH_EXP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_EMPTY:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_ESCAPE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_ENDED_BY_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE_ENDED_BY_NEWLINE:
    assert(false);
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACE:
    assert(false);
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ELLIPSIS:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON:
    assert(false);
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BANG_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_TILDE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_MINUS_OPERARTOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COLON_OPERATOR:
    assert(false);
    break;

    // echo "int a = 1; int b = 2; void f(void) { int c = (a , b); }" |   gcc -std=c99 -O0 -fno-builtin-alloca -mpush-args -x c -S -o - -  | head -20
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA: return strcopy(""); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_OPERATOR: return strconcat3("\t addl ", first_operand, ", %eax\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_OPERATOR: return strconcat3("\t subl ", first_operand, ", %eax\n" "\t neg %eax\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR: return strconcat3("\t imull ", first_operand, ", %eax\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PERLUETE_OPERATOR: return strconcat3("\t andl ", first_operand, ", %eax\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PIPE_OPERATOR: return strconcat3("\t orl ", first_operand, ", %eax\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HAT_OPERATOR: return strconcat3("\t xorl ", first_operand, ", %eax\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_LSHIFT_OPERATOR: return strconcat3("\t shll %eax, ", first_operand, "\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RSHIFT_OPERATOR: return strconcat3("\t shrl %eax, ", first_operand, "\n"); break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RDIV_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PERCENT_OPERATOR:

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PIPE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_POINT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ARROW_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_EQUAL_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIFFERENT_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OR_EQUAL_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OR_EQUAL_OPERATOR:
    assert(false);
    break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_OPERATOR: return strconcat3("\t movl %eax,", first_operand, "\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_STAR_OPERATOR: return strconcat5("\t imull ", first_operand, ", %eax\n" "\t movl %eax,", first_operand, "\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PLUS_OPERATOR: return strconcat5("\t addl ", first_operand, ", %eax\n" "\t movl %eax,", first_operand, "\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_MINUS_OPERATOR: return strconcat5("\t subl %eax, ", first_operand, "\n" "\t movl ", first_operand, ", %eax\n\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_LSHIFT_OPERATOR: return strconcat5("\t shll %eax, ", first_operand, "\n" "\t movl ", first_operand, ", %eax\n\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RSHIFT_OPERATOR: return strconcat5("\t shrl %eax, ", first_operand, "\n" "\t movl ", first_operand, ", %eax\n\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERLUETE_OPERATOR: return strconcat5("\t andl ", first_operand, ", %eax\n" "\t movl %eax,", first_operand, "\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_HAT_OPERATOR: return strconcat5("\t xorl ", first_operand, ", %eax\n" "\t movl %eax,", first_operand, "\n"); break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PIPE_OPERATOR: return strconcat5("\t orl ", first_operand, ", %eax\n" "\t movl %eax,", first_operand, "\n"); break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RDIV_OPERATOR: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERCENT_OPERATOR:
    assert(false);
    return NULL;
    break;
  }

  assert(false);
  return NULL;
}

 
    

static int compute_the_size_of_the_local_vars_and_set_the_relative_addresses_in_the_tree(int current_size, statment_tree_t * tree) {
  assert(tree != NULL);
  do {
    assert(tree -> type != STATMENT_TREE_TYPE_NULL);
    if (tree -> type == STATMENT_TREE_TYPE_SEQUENCE) {
      const int size_after_child1 = compute_the_size_of_the_local_vars_and_set_the_relative_addresses_in_the_tree(current_size, tree -> seq_stat1);
      const int size_after_child2 = compute_the_size_of_the_local_vars_and_set_the_relative_addresses_in_the_tree(size_after_child1, tree -> seq_stat2);
      return size_after_child2;
    }
    if (tree -> type == STATMENT_TREE_TYPE_EXPRESSION) return current_size;
    if (tree -> type == STATMENT_TREE_TYPE_DECLARATION) {
#if 0
      symbol_table_elt_t * declarations;
      int declarations_nb;
      int declarations_size;
#endif
      for (int i = 0; i < tree -> declarations_nb; i++) {
	symbol_table_elt_t * elt = tree -> declarations[i];
	int size_of_the_root_type = compute_the_size_of_the_root_type(elt);
	if (elt -> array_huh) {
	  // If it is an array, we multiply the whole size if and only if its size is a value computable at compile time (a 'constant value').
	  constant_value_t v;
	  const char * type = NULL;
	  type = expression_tree_compute_constant_value(elt -> array_size_code_tree, &v);
	  assert(type == CONSTANT_VALUE_TYPE_INT);
	  elt -> array_size_constant_value = v.i;
	  elt -> can_compute_array_size_constant_value_huh = true;
	  //printf("ARRAY SIZE: %d", elt -> array_size_constant_value);
	  assert(elt -> array_size_constant_value >= 0);
	  size_of_the_root_type *= elt -> array_size_constant_value;
	  if (elt -> array_size_constant_value == 0) size_of_the_root_type = 1;
	}
	elt -> relative_addr_allocated = local_stack_alloc(&current_size, size_of_the_root_type);
      }
      return current_size;
    }

    if (tree -> type == STATMENT_TREE_TYPE_RETURN) return current_size;
    
    assert(false);
  } while (false);

  assert(false);
}










void analyze_each_line_of_the_global_symbol_table(void) {
  for (int i = global_symbol_table_base_index; i < global_symbol_table_base_index + global_symbol_table_nb; i++) {
    //printf("Building the tree %d -- ", i);
    analyze_one_line_of_the_global_symbol_table(&(global_symbol_table[i]));
    //printf("\n");
  }
}



static statment_tree_t * statment_tree_make_on_the_heap_bzero(void) {
  statment_tree_t * tree = NULL;
  tree = (statment_tree_t *) malloc(sizeof(statment_tree_t));
  bzero(tree, sizeof(statment_tree_t));
  assert(tree -> type == STATMENT_TREE_TYPE_NULL);
  return tree;
}

static char * statment_tree_write_a_dot_description_for_a_file_aux(const statment_tree_t * tree, const char * node_name) {
  assert(tree != NULL);
  char * retour;
  retour = strcopy("");
  stradd4(&retour, "  ", node_name, "[label = \"");
  stradd3(&retour, tree -> type, "\n\n");
  stradd2(&retour, "\"];\n");
  do {
    if (tree -> type == STATMENT_TREE_TYPE_NULL) break;
    if (tree -> type == STATMENT_TREE_TYPE_EXPRESSION) {
      char * name1 = strconcat(node_name, "1");
      char * temp1 = NULL;
      temp1 = expression_tree_write_a_dot_description_for_a_file_aux(tree -> expr, name1);
      stradd6(&retour, "  ", node_name, " -- ", name1, ";\n");
      stradd2(&retour, temp1);
      strfree(temp1);
      strfree(name1);
      break;
    }
    if (tree -> type == STATMENT_TREE_TYPE_RETURN) {
      char * name1 = strconcat(node_name, "1");
      char * name2 = strconcat(node_name, "2");
      char * temp1 = strconcat5("  ", name1, "[label = \"", tree -> token1 -> value, "\"];\n");
      char * temp2 = NULL;
      temp2 = expression_tree_write_a_dot_description_for_a_file_aux(tree -> expr, name2);
      stradd6(&retour, "  ", node_name, " -- ", name1, ";\n");
      stradd6(&retour, "  ", node_name, " -- ", name2, ";\n");
      stradd2(&retour, temp1);
      stradd2(&retour, temp2);
      strfree(temp1);
      strfree(temp2);
      strfree(name1);
      strfree(name2);
      break;
    }
    if (tree -> type == STATMENT_TREE_TYPE_SEQUENCE) {
      char * name1 = strconcat(node_name, "1");
      char * name2 = strconcat(node_name, "2");
      char * temp1 = NULL;
      char * temp2 = NULL;
      temp1 = statment_tree_write_a_dot_description_for_a_file_aux(tree -> seq_stat1, name1);
      temp2 = statment_tree_write_a_dot_description_for_a_file_aux(tree -> seq_stat2, name2);
      stradd6(&retour, "  ", node_name, " -- ", name1, ";\n");
      stradd6(&retour, "  ", node_name, " -- ", name2, ";\n");
      stradd2(&retour, temp1);
      stradd2(&retour, temp2);
      strfree(temp1);
      strfree(temp2);
      strfree(name1);
      strfree(name2);
      break;
    }
    assert(false);
  } while (false);
  return retour;
}

static char * statment_tree_write_a_dot_description_for_a_file(const statment_tree_t * tree) {
  char * retour;
  retour = strcopy("");
  stradd2(&retour, "graph {\n");
  char * temp;
  temp = statment_tree_write_a_dot_description_for_a_file_aux(tree, "root");
  stradd2(&retour, temp);
  strfree(temp);
  stradd2(&retour, "}\n");
  return retour;
}

static void display_statment_tree(const statment_tree_t * tree) {
  assert(tree != NULL);
  char * dot_description = statment_tree_write_a_dot_description_for_a_file(tree);
  //printf("\n\n\n%s\n", dot_description);
  display_tree_with_the_dot_description(dot_description);
  strfree(dot_description);
}



static int do_something_fun_param_analyze(const token_tree_t * tree, const int symbol_table_base, const int symbol_table_size, symbol_table_elt_t * symbol_table);
static statment_tree_t * do_something_for_a_list_of_statment_or_declaration(const token_tree_t * tree, const int start_index, const int tokens_nb);

void analyze_one_line_of_the_global_symbol_table(symbol_table_elt_t * elt) {
  if (elt -> array_huh) {
    //compile_the_code_for_a_constant_array_size(elt);
    elt -> array_size_code_tree = generate_the_tree_for_a_constant_array_size(elt -> array_size_code_tokens);
    //display_expression_tree(elt -> array_size_code_tree);
    constant_value_t v;
    const char * type = NULL;
    type = expression_tree_compute_constant_value(elt -> array_size_code_tree, &v);
    assert(type == CONSTANT_VALUE_TYPE_INT);
    elt -> array_size_constant_value = v.i;
    elt -> can_compute_array_size_constant_value_huh = true;
    //printf("ARRAY SIZE: %d", elt -> array_size_constant_value);
  }
  
  if (elt -> fun_param_huh) {
    assert(elt -> fun_param_code_tokens != NULL);
    assert_type_of_the_first_token(elt -> fun_param_code_tokens, LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR);
    assert_type_of_the_last_token(elt -> fun_param_code_tokens, LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR);
    lexer_lexer_for_c_language_token_liste_t * tokens = NULL;
    tokens = lexer_lexer_for_c_language_token_liste_get_without_the_last_and_the_first(elt -> fun_param_code_tokens);
    token_tree_t * tree_initial = NULL;
    tree_initial = token_liste_2_token_tree(tokens);
    token_tree_t * tree = NULL;
    tree = token_tree_grouping_paren_bracket_brace(tree_initial);
    //token_tree_print(tree);
    const int comma_nb = token_tree_count_tokens_according_to_type(LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA, token_tree_count(tree), tree);
    const int param_nb = comma_nb + 1; // TODO XXX false if void
    const int size_of_the_local_symbol_table = comma_nb + 1;
    symbol_table_elt_t * local_symbol_table = NULL;
    local_symbol_table = symbol_table_make_on_the_heap(1, size_of_the_local_symbol_table);
    // TODO XXX split according the comma
    int nb = 0;
    nb = do_something_fun_param_analyze(tree, 1, size_of_the_local_symbol_table, local_symbol_table);
    
    //printf("%s", symbol_table_string(1, nb, local_symbol_table, "<fun param>"));

    elt -> fun_param_code_table = local_symbol_table;
    elt -> fun_param_code_table_nb = nb;
    elt -> fun_param_code_table_size = size_of_the_local_symbol_table;
    
    //assert(false);
  }
  
  if (elt -> fun_def_huh) {
    assert(elt -> fun_def_code_tokens != NULL);
    assert_type_of_the_first_token(elt -> fun_def_code_tokens, LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE);
    assert_type_of_the_last_token(elt -> fun_def_code_tokens, LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACE);
    lexer_lexer_for_c_language_token_liste_t * tokens = NULL;
    tokens = lexer_lexer_for_c_language_token_liste_get_without_the_last_and_the_first(elt -> fun_def_code_tokens);
    token_tree_t * tree_initial = NULL;
    tree_initial = token_liste_2_token_tree(tokens);
    token_tree_t * tree = NULL;
    tree = token_tree_grouping_paren_bracket_brace(tree_initial);
    //token_tree_print(tree);
    const int tokens_nb = token_tree_count(tree);

    statment_tree_t * statment_tree = NULL;
    statment_tree = do_something_for_a_list_of_statment_or_declaration(tree, 0, tokens_nb);
    //display_statment_tree(statment_tree);

    elt -> fun_def_code_tree = statment_tree;
#if 0
    for(;;);
    (for(;;));
    (for(;;););
    for(;;);
  label_DDD:;
    (label_XXXX:);
    goto label_DDD;
    (goto label_DDD);
    if (true) {};
    (if (true){0;};);
    return;
    (return);
    (return;);
    (typedef int yyyyy;);
    (typedef int yyyyy);
    assert(false);
#endif
  }
  
}


static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_statment(const token_tree_t * tree, const int start_index, const int tokens_nb);
static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_label(const token_tree_t * tree, const int start_index, const int tokens_nb);
static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_compound_statment(const token_tree_t * tree, const int start_index, const int tokens_nb);
static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_an_expression(const token_tree_t * tree, const int start_index, const int tokens_nb);
static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_for(const token_tree_t * tree, const int start_index, const int tokens_nb);
static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_an_if(const token_tree_t * tree, const int start_index, const int tokens_nb);
static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_switch(const token_tree_t * tree, const int start_index, const int tokens_nb);
static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_while(const token_tree_t * tree, const int start_index, const int tokens_nb);
static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_do(const token_tree_t * tree, const int start_index, const int tokens_nb);
static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_goto(const token_tree_t * tree, const int start_index, const int tokens_nb);
static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_continue(const token_tree_t * tree, const int start_index, const int tokens_nb);
static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_break(const token_tree_t * tree, const int start_index, const int tokens_nb);
static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_return(const token_tree_t * tree, const int start_index, const int tokens_nb);
static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_declaration(const token_tree_t * tree, const int start_index, const int tokens_nb);



static statment_tree_t * do_something_for_a_list_of_statment_or_declaration(const token_tree_t * tree, const int start_index, const int tokens_nb) {
  // This is not a compound statment, so no { nor }.
  //
  // And the tree is already processed for {}, (), and [].
  //
  // So, the fucking problem with C is that we have no uniform syntax delimiter between instructions.
  // Semicolon is the common one, a for is not closed with a ;, neither a while, etc.
  // And braces are not all the times an end of instruction… It depends on the context.
  // So, we have to scan and analyze everything to determine if we are at the end of an instruction… So stupid…
  //
  // First, we have to determine if it is a declaration or an statment… (Another mad thing…!)
  // To determine so, we check the first token and we try to determine sthg up.
  statment_tree_t * statment_tree = NULL;
  do {
    int i = start_index;
    i = skip_blanks_and_process_directives_token_tree(i, tokens_nb, tree);
    assert(i < tokens_nb);
    if (tree[i].type != TOKEN_TREE_TYPE_LEAF) {
      statment_tree = do_something_for_a_list_of_statment_or_declaration_beginning_with_a_statment(tree, i, tokens_nb);
      break;
    }

    assert(tree[i].type == TOKEN_TREE_TYPE_LEAF);
    
    const lexer_lexer_for_c_language_token_type_t type_of_the_first_token = tree[i].token -> type;
    const bool_t is_the_first_token_an_ident = (LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT == type_of_the_first_token); // If not, it is not a declaration.
    
    if (LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT != type_of_the_first_token) {
      statment_tree = do_something_for_a_list_of_statment_or_declaration_beginning_with_a_statment(tree, i, tokens_nb);
      break;
    }

    assert(LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT == type_of_the_first_token);

    
    const char * ident = tree[i].token -> value;
    const bool_t Is_the_ident_a_type_keyword_huh = token_is_a_keyword_related_to_a_declaration_huh(ident);
    const bool_t Is_the_ident_a_statment_keyword_huh = token_is_a_keyword_related_to_a_statment_huh(ident);

    if (Is_the_ident_a_type_keyword_huh) {
      statment_tree = do_something_for_a_list_of_statment_or_declaration_beginning_with_a_declaration(tree, i, tokens_nb);
      break;
    }

    if (Is_the_ident_a_statment_keyword_huh) {
      statment_tree = do_something_for_a_list_of_statment_or_declaration_beginning_with_a_statment(tree, i, tokens_nb);
      break;
    }

    // TODO XXX do a lookup in the table of types

    // TODO XXX do a lookup in the table of variables

    // TODO XXX do a lookup in the table of labels
    
    const int index = global_symbol_table_lookup(ident);
    if (index != 0) {
      if (0 == strcmp(global_symbol_table[index].storage_class, "typedef")) {
	statment_tree = do_something_for_a_list_of_statment_or_declaration_beginning_with_a_declaration(tree, i, tokens_nb);
	break;
      }
      {
	statment_tree = do_something_for_a_list_of_statment_or_declaration_beginning_with_an_expression(tree, i, tokens_nb);
	break;
      }
    } 

    // Finally, if the ident is not known, the only possibility is that it is the declaration of a label.
    statment_tree = do_something_for_a_list_of_statment_or_declaration_beginning_with_a_label(tree, i, tokens_nb);

  } while (false);

  return statment_tree;
}


static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_statment(const token_tree_t * tree, const int start_index, const int tokens_nb) {
  // Allright. We have to determine which statment it is.
  // So, statment: label ("ident:") | compound ("{…}") | expression | if | switch | while | do | for | goto | continue | break | return 
  // So it is relatively easy.
  statment_tree_t * statment_tree = NULL;
  int i = start_index;
  i = skip_blanks_and_process_directives_token_tree(i, tokens_nb, tree);
  assert(i < tokens_nb);
  do {
    assert(tree[i].type != TOKEN_TREE_TYPE_NULL);
    if (tree[i].type == TOKEN_TREE_TYPE_NODE_TOP_BRACE) {
      do_something_for_a_list_of_statment_or_declaration_beginning_with_a_compound_statment(tree, i, tokens_nb);
      break;
    }
    if (tree[i].type == TOKEN_TREE_TYPE_NODE_TOP_BRACKET) {
      assert(false);
      break;
    }
    if (tree[i].type == TOKEN_TREE_TYPE_NODE_TOP_PAREN) {
      return do_something_for_a_list_of_statment_or_declaration_beginning_with_an_expression(tree, i, tokens_nb);
      break;
    }
    
    assert(tree[i].type == TOKEN_TREE_TYPE_LEAF);
    
    if (LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT != tree[i].token -> type) {
      return do_something_for_a_list_of_statment_or_declaration_beginning_with_an_expression(tree, i, tokens_nb);
      break;
    }
    
    const char * ident = tree[i].token -> value;

    if (0 == strcmp(ident, "for")) {
      do_something_for_a_list_of_statment_or_declaration_beginning_with_a_for(tree, i, tokens_nb);
      break;
    }
    
    if (0 == strcmp(ident, "if")) {
      do_something_for_a_list_of_statment_or_declaration_beginning_with_an_if(tree, i, tokens_nb);
      break;
    }
    
    if (0 == strcmp(ident, "switch")) {
      do_something_for_a_list_of_statment_or_declaration_beginning_with_a_switch(tree, i, tokens_nb);
      break;
    }
    
    if (0 == strcmp(ident, "while")) {
      do_something_for_a_list_of_statment_or_declaration_beginning_with_a_while(tree, i, tokens_nb);
      break;
    }
    
    if (0 == strcmp(ident, "do")) {
      do_something_for_a_list_of_statment_or_declaration_beginning_with_a_do(tree, i, tokens_nb);
      break;
    }
    
    if (0 == strcmp(ident, "goto")) {
      do_something_for_a_list_of_statment_or_declaration_beginning_with_a_goto(tree, i, tokens_nb);
      break;
    }
    
    if (0 == strcmp(ident, "continue")) {
      do_something_for_a_list_of_statment_or_declaration_beginning_with_a_continue(tree, i, tokens_nb);
      break;
    }
    
    if (0 == strcmp(ident, "break")) {
      do_something_for_a_list_of_statment_or_declaration_beginning_with_a_break(tree, i, tokens_nb);
      break;
    }
    
    if (0 == strcmp(ident, "return")) {
      statment_tree = do_something_for_a_list_of_statment_or_declaration_beginning_with_a_return(tree, i, tokens_nb);
      break;
    }

    // Now, the ident is not is keyword.
    // So it is obviously either an expression, either a label going to be defined.
    // TODO XXX lookup in the type table
    // TODO XXX lookup in the variable table
    // TODO XXX lookup in the label table

    {
      do_something_for_a_list_of_statment_or_declaration_beginning_with_a_label(tree, i, tokens_nb);
      break;
    }
  } while (false);

  return statment_tree;
}

static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_label(const token_tree_t * tree, const int start_index, const int tokens_nb) {
  fprintf(stderr, "LABEL: %s\n", tree[start_index].token -> value);
  assert(false);
}

static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_compound_statment(const token_tree_t * tree, const int start_index, const int tokens_nb) {
  assert(false);
}

static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_an_expression(const token_tree_t * tree, const int start_index, const int tokens_nb) {
#if 0
  expression_tree_t * build_the_expression_tree(const lexer_lexer_for_c_language_token_liste_t * tokens);
#endif
  // An expression always ends with a semicolon.
  // So, let look for it, then flatten the subtree, then building an expression tree.
  int index_of_the_semicolon = -1;
  for (int i = start_index; i < tokens_nb; i++) {
    if (tree[i].type != TOKEN_TREE_TYPE_LEAF) continue;
    assert(tree[i].type == TOKEN_TREE_TYPE_LEAF);
    if (tree[i].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON) {
      index_of_the_semicolon = i;
      break;
    }
  }
  assert(index_of_the_semicolon != -1);
  lexer_lexer_for_c_language_token_liste_t * expr_tokens = NULL;
  for (int i = index_of_the_semicolon; i >= start_index; i--) {
    if (tree[i].type != TOKEN_TREE_TYPE_LEAF) {
      lexer_lexer_for_c_language_token_liste_t * new_head = NULL;
      new_head = lexer_lexer_for_c_language_token_liste_copy(tree[i].tokens);
      lexer_lexer_for_c_language_token_liste_append_nocopy(&new_head, expr_tokens);
      expr_tokens = new_head;
      continue;
    }
    assert(tree[i].type == TOKEN_TREE_TYPE_LEAF);
    expr_tokens = lexer_lexer_for_c_language_token_liste_cons_nocopy(lexer_lexer_for_c_language_token_copy(tree[i].token), expr_tokens);
  }
  expression_tree_t * expr_tree = NULL;
  expr_tree = build_the_expression_tree(expr_tokens);
  lexer_lexer_for_c_language_token_liste_free(expr_tokens);
  //display_expression_tree(expr_tree);
  
  statment_tree_t * child1_tree = NULL;
  child1_tree = statment_tree_make_on_the_heap_bzero();
  child1_tree -> type = STATMENT_TREE_TYPE_EXPRESSION;
  child1_tree -> expr = expr_tree;
  
  
  // We are in a list, so we have to process the rest of the list.
  statment_tree_t * child2_tree = NULL;
  {
    int i = index_of_the_semicolon+1;
    i = skip_blanks_and_process_directives_token_tree(i, tokens_nb, tree);
    if (i == tokens_nb) {
      return child1_tree;
    }

    child2_tree = do_something_for_a_list_of_statment_or_declaration(tree, i, tokens_nb);
  }
  
  statment_tree_t * sequence_tree = NULL;
  sequence_tree = statment_tree_make_on_the_heap_bzero();
  sequence_tree -> type = STATMENT_TREE_TYPE_SEQUENCE;
  sequence_tree -> seq_stat1 = child1_tree;
  sequence_tree -> seq_stat2 = child2_tree;

  return sequence_tree;
}

static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_for(const token_tree_t * tree, const int start_index, const int tokens_nb) {
  assert(false);
}

static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_an_if(const token_tree_t * tree, const int start_index, const int tokens_nb) {
  assert(false);
}

static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_switch(const token_tree_t * tree, const int start_index, const int tokens_nb) {
  assert(false);
}

static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_while(const token_tree_t * tree, const int start_index, const int tokens_nb) {
  assert(false);
}

static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_do(const token_tree_t * tree, const int start_index, const int tokens_nb) {
  assert(false);
}

static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_goto(const token_tree_t * tree, const int start_index, const int tokens_nb) {
  assert(false);
}

static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_continue(const token_tree_t * tree, const int start_index, const int tokens_nb) {
  assert(false);
}

static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_break(const token_tree_t * tree, const int start_index, const int tokens_nb) {
  assert(false);
}

static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_return(const token_tree_t * tree, const int start_index, const int tokens_nb) {
  statment_tree_t * return_tree = NULL;
  {
    int i = start_index;
    assert(i < tokens_nb);
    assert(tree[i].type == TOKEN_TREE_TYPE_LEAF);
    return_tree = statment_tree_make_on_the_heap_bzero();
    return_tree -> type = STATMENT_TREE_TYPE_RETURN;
    return_tree -> token1 = lexer_lexer_for_c_language_token_copy(tree[i].token);
  }
  
  // An expression always ends with a semicolon.
  // So, let look for it, then flatten the subtree, then building an expression tree.
  int index_of_the_semicolon = -1;
  {
    for (int i = start_index+1; i < tokens_nb; i++) {
      if (tree[i].type != TOKEN_TREE_TYPE_LEAF) continue;
      assert(tree[i].type == TOKEN_TREE_TYPE_LEAF);
      if (tree[i].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON) {
	index_of_the_semicolon = i;
	break;
      }
    }
    assert(index_of_the_semicolon != -1);
    lexer_lexer_for_c_language_token_liste_t * expr_tokens = NULL;
    for (int i = index_of_the_semicolon; i >= start_index+1; i--) {
      if (tree[i].type != TOKEN_TREE_TYPE_LEAF) {
	lexer_lexer_for_c_language_token_liste_t * new_head = NULL;
	new_head = lexer_lexer_for_c_language_token_liste_copy(tree[i].tokens);
	lexer_lexer_for_c_language_token_liste_append_nocopy(&new_head, expr_tokens);
	expr_tokens = new_head;
	continue;
      }
      assert(tree[i].type == TOKEN_TREE_TYPE_LEAF);
      expr_tokens = lexer_lexer_for_c_language_token_liste_cons_nocopy(lexer_lexer_for_c_language_token_copy(tree[i].token), expr_tokens);
    }
    expression_tree_t * expr_tree = NULL;
    expr_tree = build_the_expression_tree(expr_tokens);
    lexer_lexer_for_c_language_token_liste_free(expr_tokens);
    //display_expression_tree(expr_tree);
    
    return_tree -> expr = expr_tree;
  }


  // We are in a list, so we have to process the rest of the list.
  statment_tree_t * child2_tree = NULL;
  {
    int i = index_of_the_semicolon+1;
    i = skip_blanks_and_process_directives_token_tree(i, tokens_nb, tree);
    if (i == tokens_nb) {
      return return_tree;
    }

    child2_tree = do_something_for_a_list_of_statment_or_declaration(tree, i, tokens_nb);
  }
  
  statment_tree_t * sequence_tree = NULL;
  sequence_tree = statment_tree_make_on_the_heap_bzero();
  sequence_tree -> type = STATMENT_TREE_TYPE_SEQUENCE;
  sequence_tree -> seq_stat1 = return_tree;
  sequence_tree -> seq_stat2 = child2_tree;

  return sequence_tree;
}

static statment_tree_t * do_something_for_a_list_of_statment_or_declaration_beginning_with_a_declaration(const token_tree_t * tree, const int start_index, const int tokens_nb) {
  // …
  assert(false);
  return false;
}

static int do_something_fun_param_analyze(const token_tree_t * tree, const int symbol_table_base, const int symbol_table_size, symbol_table_elt_t * symbol_table) {
  // First: NO class storage (nor typedef)
  // Second: NO inline
  // Third: constness
  // Fourth: signedness («signed short int»)
  // Fifth: sizeness («signed short int»)
  // Sixth: core-type
  // Seventh: structured-type with the name <this one is the complicated one>
  // Eighth: a COMMA or EOF
  //
  const int tokens_nb = token_tree_count(tree);
  int symbol_table_nb = 0;
  int i;
  i = 0;
  do {
    const char * storage_class = STORAGE_CLASS_SPECIFIER_NULL;
    const char * inline_class = INLINE_CLASS_SPECIFIER_NULL;
    const char * const_class = CONST_CLASS_SPECIFIER_NULL;
    const char * signed_class = SIGNED_CLASS_SPECIFIER_NULL;
    const char * size_class = SIZE_CLASS_SPECIFIER_NULL;
    const char * core_type = CORE_TYPE_SPECIFIER_NULL;
    int indirections_nb = 0;
    bool_t array_huh = false;
    const char * array_size_code = NULL;
    // TODO macros defined before the code of array_size_code
    bool_t fun_param_huh = false;
    const char * fun_param_code = NULL;
    // TODO macros defined before the code of fun_param_code
    bool_t fun_def_huh = false;
    const char * fun_def_code = NULL;
    
    
    // first state of the automaton: NO storage class
    
    // second state of the automaton: NO inline keyword
    
    // third state of the automaton: the const keyword
    do {
      i = skip_blanks_and_process_directives_token_tree(i, tokens_nb, tree);
      if (i == tokens_nb) break;
      if (tree[i].type != TOKEN_TREE_TYPE_LEAF) break;
      if (tree[i].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT) break;
      if (0 == strcmp(tree[i].token -> value, "const")) { const_class = CONST_CLASS_SPECIFIER_CONST; i++; }
    } while (false);
    
    // fourth state: signedness
    do {
      i = skip_blanks_and_process_directives_token_tree(i, tokens_nb, tree);
      if (i == tokens_nb) break;
      if (tree[i].type != TOKEN_TREE_TYPE_LEAF) break;
      if (tree[i].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT) break;
      if (0 == strcmp(tree[i].token -> value, "signed")) { signed_class = SIGNED_CLASS_SPECIFIER_SIGNED; i++; }
      if (0 == strcmp(tree[i].token -> value, "unsigned")) { signed_class = SIGNED_CLASS_SPECIFIER_UNSIGNED; i++; }
    } while (false);
    
    // fifth state: sizeness
    do {
      i = skip_blanks_and_process_directives_token_tree(i, tokens_nb, tree);
      if (i == tokens_nb) break;
      if (tree[i].type != TOKEN_TREE_TYPE_LEAF) break;
      if (tree[i].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT) break;
      if (0 == strcmp(tree[i].token -> value, "short")) { size_class = SIZE_CLASS_SPECIFIER_SHORT; i++; }
      if (0 == strcmp(tree[i].token -> value, "long")) { size_class = SIZE_CLASS_SPECIFIER_LONG; i++; }
    } while (false);
    
    // fifth state bis: sizeness double
    do {
      i = skip_blanks_and_process_directives_token_tree(i, tokens_nb, tree);
      if (i == tokens_nb) break;
      if (tree[i].type != TOKEN_TREE_TYPE_LEAF) break;
      if (tree[i].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT) break;
      if (0 == strcmp(tree[i].token -> value, "short")) { assert(size_class == SIZE_CLASS_SPECIFIER_SHORT); size_class = SIZE_CLASS_SPECIFIER_SHORT_SHORT; i++; }
      if (0 == strcmp(tree[i].token -> value, "long")) { assert(size_class == SIZE_CLASS_SPECIFIER_LONG); size_class = SIZE_CLASS_SPECIFIER_LONG_LONG; i++; }
    } while (false);
    
    // sixth state: core-type
    do {
      i = skip_blanks_and_process_directives_token_tree(i, tokens_nb, tree);
      if (i == tokens_nb) break;
      if (tree[i].type != TOKEN_TREE_TYPE_LEAF) break;
      if (tree[i].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT) break;
      if (0 == strcmp(tree[i].token -> value, "void")) { core_type = CORE_TYPE_SPECIFIER_VOID; i++; }
      if (0 == strcmp(tree[i].token -> value, "char")) { core_type = CORE_TYPE_SPECIFIER_CHAR; i++; }
      if (0 == strcmp(tree[i].token -> value, "int")) { core_type = CORE_TYPE_SPECIFIER_INT; i++; }
      if (0 == strcmp(tree[i].token -> value, "float")) { core_type = CORE_TYPE_SPECIFIER_FLOAT; i++; }
      if (0 == strcmp(tree[i].token -> value, "double")) { core_type = CORE_TYPE_SPECIFIER_DOUBLE; i++; }
      if (0 == strcmp(tree[i].token -> value, "_Bool")) { core_type = CORE_TYPE_SPECIFIER__BOOL; i++; }
      if (0 == strcmp(tree[i].token -> value, "_Complex")) { core_type = CORE_TYPE_SPECIFIER__COMPLEX; i++; }
      // test if a keyword
      if (core_type == CORE_TYPE_SPECIFIER_NULL) {
	if (token_is_a_keyword_huh(tree[i].token -> value)) { assert(false); }
	if (signed_class == SIGNED_CLASS_SPECIFIER_NULL && size_class == SIZE_CLASS_SPECIFIER_NULL) {
	  //core_type = CORE_TYPE_SPECIFIER_IDENT;
	  core_type = strcopy(tree[i].token -> value);
	  i++;
	}
      }
    } while (false);
    
    // seventh state: structured type (the complicated part)
    // This is the "declarator" of the C99 grammar.
    // declarator: * * * … puis NAME puis […] or (…)
    // For the moment, we forget the "( declarator )" part.
    // 7.a. Counting the number of *
    for (;;) {
      i = skip_blanks_and_process_directives_token_tree(i, tokens_nb, tree);
      if (i == tokens_nb) break;
      if (tree[i].type != TOKEN_TREE_TYPE_LEAF) break;
      if (tree[i].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR) break;
      indirections_nb++;
      i++;
    } 
    
    // 7.b. The name of the type
    const char * name_being_declared = NULL;
    do {
      i = skip_blanks_and_process_directives_token_tree(i, tokens_nb, tree);
      if (i == tokens_nb) break;
      if (tree[i].type != TOKEN_TREE_TYPE_LEAF) break;
      if (tree[i].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT) break;
      name_being_declared = tree[i].token -> value;
      i++;
    } while (false);
    
    // 7.c. Array
    const lexer_lexer_for_c_language_token_liste_t * array_size_code_tokens = NULL;
    do {
      i = skip_blanks_and_process_directives_token_tree(i, tokens_nb, tree);
      if (i == tokens_nb) break;
      if (tree[i].type == TOKEN_TREE_TYPE_NODE_TOP_BRACKET) {
	array_huh = true;
	array_size_code_tokens = tree[i].tokens;
	array_size_code = lexer_lexer_for_c_language_token_liste_string_flat(tree[i].tokens);
	i++;
      }
    } while (false);
    
    // 7.d. function param
    const lexer_lexer_for_c_language_token_liste_t * fun_param_code_tokens = NULL;
    do {
      i = skip_blanks_and_process_directives_token_tree(i, tokens_nb, tree);
      if (i == tokens_nb) break;
      if (tree[i].type == TOKEN_TREE_TYPE_NODE_TOP_PAREN) {
	fun_param_huh = true;
	fun_param_code_tokens = tree[i].tokens;
	fun_param_code = lexer_lexer_for_c_language_token_liste_string_flat(tree[i].tokens);
	i++;
      }
    } while (false);
    
    // eighth state: COMMA or EOF
    const lexer_lexer_for_c_language_token_liste_t * fun_def_code_tokens = NULL;
    do {
      i = skip_blanks_and_process_directives_token_tree(i, tokens_nb, tree);
      if (i == tokens_nb) break;
      if (tree[i].type == TOKEN_TREE_TYPE_LEAF) {
	assert(tree[i].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA);
	i++;
	break;
      }
      assert(false);
    } while (false);
    


    // Now, we have to push what we recognized the symbol table.
    if (name_being_declared != NULL) {
      symbol_table_nb = symbol_table_push(symbol_table, symbol_table_base, symbol_table_size, symbol_table_nb, name_being_declared, storage_class, inline_class, const_class, signed_class, size_class, core_type, indirections_nb, array_huh, array_size_code, array_size_code_tokens, fun_param_huh, fun_param_code, fun_param_code_tokens, fun_def_huh, fun_def_code, fun_def_code_tokens);
    }
    else {
      assert(name_being_declared == NULL);
      if (storage_class != STORAGE_CLASS_SPECIFIER_NULL) assert(false);
      if (inline_class != INLINE_CLASS_SPECIFIER_NULL) assert(false);
      if (const_class != CONST_CLASS_SPECIFIER_NULL) assert(false);
      if (signed_class != SIGNED_CLASS_SPECIFIER_NULL) assert(false);
      if (size_class != SIZE_CLASS_SPECIFIER_NULL) assert(false);
      if (core_type != CORE_TYPE_SPECIFIER_NULL) assert(false);
      if (indirections_nb != 0) assert(false);
      if (array_huh) assert(false);
      if (fun_param_huh) assert(false);
      if (fun_def_huh) assert(false);
    }
    
    
    // NEXT!
  } while (i < tokens_nb);
  
  
  return symbol_table_nb;
}


void assert_type_of_the_first_token(const lexer_lexer_for_c_language_token_liste_t * tokens, lexer_lexer_for_c_language_token_type_t type) {
  const lexer_lexer_for_c_language_token_t * first_token;
  first_token = tokens -> car;
  assert(first_token -> type == type);
}

void assert_type_of_the_last_token(const lexer_lexer_for_c_language_token_liste_t * tokens, lexer_lexer_for_c_language_token_type_t type) {
  const lexer_lexer_for_c_language_token_t * last_token;
  last_token = lexer_lexer_for_c_language_token_liste_get_last(tokens);
  assert(last_token -> type == type);
}

void * generate_the_tree_for_fun_param(const lexer_lexer_for_c_language_token_liste_t * const tokens_with_round_brackets_to_remove) {
  assert(tokens_with_round_brackets_to_remove != NULL);
  // First, we have to remove the first and the last tokens which are '(' and ')'.
  lexer_lexer_for_c_language_token_liste_t * tokens = NULL;
  {
    const lexer_lexer_for_c_language_token_t * first_token;
    const lexer_lexer_for_c_language_token_t * last_token;
    first_token = tokens_with_round_brackets_to_remove -> car;
    last_token = lexer_lexer_for_c_language_token_liste_get_last(tokens_with_round_brackets_to_remove);
    assert(first_token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR);
    assert(last_token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR);
  }
  tokens = lexer_lexer_for_c_language_token_liste_get_without_the_last_and_the_first(tokens_with_round_brackets_to_remove);
#if 0
  expression_tree_t * tree;
  tree = build_the_expression_tree(tokens);
  lexer_lexer_for_c_language_token_liste_free(tokens);
  return tree;
#else
  return NULL;
#endif
}


token_tree_t * token_tree_make_on_the_heap(int tokens_nb) {
  token_tree_t * tree = NULL;
  tree = (token_tree_t *) malloc((tokens_nb+1) * sizeof(token_tree_t));
  bzero(tree, (tokens_nb+1) * sizeof(token_tree_t));
  return tree;
}

token_tree_t * token_liste_2_token_tree(const lexer_lexer_for_c_language_token_liste_t * tokens) {
  const int tokens_nb = lexer_lexer_for_c_language_token_liste_longueur(tokens);
  token_tree_t * tree = token_tree_make_on_the_heap(tokens_nb);
  for (int i = 0; i < tokens_nb; i++) {
    tree[i].type = TOKEN_TREE_TYPE_LEAF;
    tree[i].token = lexer_lexer_for_c_language_token_copy(tokens -> car);
    tree[i].tokens = NULL;
    tokens = tokens -> cdr;
  }
  assert(tokens == NULL);
  assert(tree[tokens_nb].type == TOKEN_TREE_TYPE_NULL);
  return tree;
}

int token_tree_count(const token_tree_t * tree) {
  int count = 0;
  while (tree[count].type != TOKEN_TREE_TYPE_NULL) count++;
  return count;
}

#define token_copy lexer_lexer_for_c_language_token_copy
#define token_list_copy lexer_lexer_for_c_language_token_liste_copy

token_tree_t * token_tree_grouping_paren_bracket_brace(const token_tree_t * const tree_initial) {
  const int tokens_nb = token_tree_count(tree_initial);
  token_tree_t * tree_after_top_level_braces_and_brackets_and_parenthesis_processing = NULL;
  tree_after_top_level_braces_and_brackets_and_parenthesis_processing = token_tree_make_on_the_heap(tokens_nb);

  do {
    int index_in_tree_initial = 0;
    int index_in_tree_after_bracketing_and_parenthezing = 0;
    for (; index_in_tree_initial < tokens_nb; index_in_tree_initial++, index_in_tree_after_bracketing_and_parenthezing++) {
      if (tree_initial[index_in_tree_initial].type != TOKEN_TREE_TYPE_LEAF) {
	tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type = tree_initial[index_in_tree_initial].type;
	tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].token = NULL;
	tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = token_list_copy(tree_initial[index_in_tree_initial].tokens);
	continue;
      }

      assert(tree_initial[index_in_tree_initial].type == TOKEN_TREE_TYPE_LEAF);
	
      if (tree_initial[index_in_tree_initial].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE) {
	if (tree_initial[index_in_tree_initial].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET) {
	  if (tree_initial[index_in_tree_initial].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR) {
	    tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type = tree_initial[index_in_tree_initial].type;
	    tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].token = token_copy(tree_initial[index_in_tree_initial].token);
	    tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = NULL;
	    continue;
	  }
	}
      }
	
      if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE) {
	tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type = TOKEN_TREE_TYPE_NODE_TOP_BRACE;
	tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_vide();
	tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_cons(tree_initial[index_in_tree_initial].token, tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens);
	int stack_count = 1;
	while (stack_count != 0) {
	  index_in_tree_initial++;
	  assert(index_in_tree_initial < tokens_nb);
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_cons(tree_initial[index_in_tree_initial].token, tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens);
	  if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE) stack_count++;
	  if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACE) stack_count--;
	}
	lexer_lexer_for_c_language_token_liste_reverse_surplace(&(tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens));
	continue;
      }
      

      if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET) {
	tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type = TOKEN_TREE_TYPE_NODE_TOP_BRACKET;
	tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_vide();
	tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_cons(tree_initial[index_in_tree_initial].token, tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens);
	int stack_count = 1;
	while (stack_count != 0) {
	  index_in_tree_initial++;
	  assert(index_in_tree_initial < tokens_nb);
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_cons(tree_initial[index_in_tree_initial].token, tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens);
	  if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET) stack_count++;
	  if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACKET) stack_count--;
	}
	lexer_lexer_for_c_language_token_liste_reverse_surplace(&(tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens));
	continue;
      }
	


      if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR) {
	tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type = TOKEN_TREE_TYPE_NODE_TOP_PAREN;
	tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_vide();
	tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_cons(tree_initial[index_in_tree_initial].token, tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens);
	int stack_count = 1;
	while (stack_count != 0) {
	  index_in_tree_initial++;
	  assert(index_in_tree_initial < tokens_nb);
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_cons(tree_initial[index_in_tree_initial].token, tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens);
	  if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR) stack_count++;
	  if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR) stack_count--;
	}
	lexer_lexer_for_c_language_token_liste_reverse_surplace(&(tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens));
	continue;
      }

      assert(false);
    }
    
  } while (false);
  
  return tree_after_top_level_braces_and_brackets_and_parenthesis_processing;
}


void token_tree_print(const token_tree_t * tree_after_top_level_braces_and_brackets_and_parenthesis_processing) {
  for (int index_in_tree_after_bracketing_and_parenthezing = 0; tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type != TOKEN_TREE_TYPE_NULL; index_in_tree_after_bracketing_and_parenthezing++) {
    fprintf(stderr, "[%3d] ", index_in_tree_after_bracketing_and_parenthezing);
    
    if (tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type == TOKEN_TREE_TYPE_LEAF) {
      fprintf(stderr, "LEAF: '%s'\n", tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].token -> value);
      continue;
    }
    
    if (tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type == TOKEN_TREE_TYPE_NODE_TOP_BRACE) {
      fprintf(stderr, "NODE TOP BRACE: ");
      for (const lexer_lexer_for_c_language_token_liste_t * p = tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens; p != NULL; p = p-> cdr)
	fprintf(stderr, "%s", p -> car -> value);
      fprintf(stderr, "\n");
      continue;
    }
    
    if (tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type == TOKEN_TREE_TYPE_NODE_TOP_BRACKET) {
      fprintf(stderr, "NODE TOP BRACKET: ");
      for (const lexer_lexer_for_c_language_token_liste_t * p = tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens; p != NULL; p = p-> cdr)
	fprintf(stderr, "%s", p -> car -> value);
      fprintf(stderr, "\n");
      continue;
    }
    
    if (tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type == TOKEN_TREE_TYPE_NODE_TOP_PAREN) {
      fprintf(stderr, "NODE TOP PAREN: ");
      for (const lexer_lexer_for_c_language_token_liste_t * p = tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens; p != NULL; p = p-> cdr)
	fprintf(stderr, "%s", p -> car -> value);
      fprintf(stderr, "\n");
      continue;
    }
    
    puts("ERROR\n");
    assert(false);
  }
}











#if 0


  // *** Traitement des «{…}» top-level.
  const int tokens_nb = lexer_lexer_for_c_language_token_liste_longueur(tokens);
  token_tree_t tree_null[tokens_nb];
  token_tree_t tree_initial[tokens_nb];
  token_tree_t tree_after_top_level_braces_and_brackets_and_parenthesis_processing[tokens_nb];
  for (int i = 0; i < tokens_nb; i++) {
    tree_null[i].type = TOKEN_TREE_TYPE_NULL;
    tree_null[i].token = NULL;
    tree_null[i].tokens = NULL;
  }
  for (int i = 0; i < tokens_nb; i++) {
    tree_initial[i] = tree_null[i];
    tree_after_top_level_braces_and_brackets_and_parenthesis_processing[i] = tree_null[i];
  }
  
  {
    const lexer_lexer_for_c_language_token_liste_t * p;
    int i;
    for (i = 0, p = tokens; i < tokens_nb; i++, p = p-> cdr) {
      assert(p != NULL);
      tree_initial[i].type = TOKEN_TREE_TYPE_LEAF;
      tree_initial[i].token = p -> car;
      tree_initial[i].tokens = NULL;
    }
    assert(p == NULL);
  }

  
  

  

  // top-level braces and top-level brackets and top-level parenthesis
  // «int fun(int tab[])»
  do {

    {
      // tree_after_top_level_braces_and_brackets_and_parenthesis_processing
      int index_in_tree_initial = 0;
      int index_in_tree_after_bracketing_and_parenthezing = 0;
      for (; index_in_tree_initial < tokens_nb; index_in_tree_initial++, index_in_tree_after_bracketing_and_parenthezing++) {
	if (tree_initial[index_in_tree_initial].type != TOKEN_TREE_TYPE_LEAF) {
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing] = tree_initial[index_in_tree_initial];
	  continue;
	}
	
	if (tree_initial[index_in_tree_initial].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE) {
	  if (tree_initial[index_in_tree_initial].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET) {
	    if (tree_initial[index_in_tree_initial].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR) {
	    tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing] = tree_initial[index_in_tree_initial];
	    continue;
	    }
	  }
	}
	
	if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE) {
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type = TOKEN_TREE_TYPE_NODE_TOP_BRACE;
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_vide();
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_cons(tree_initial[index_in_tree_initial].token, tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens);
	  int stack_count = 1;
	  while (stack_count != 0) {
	    index_in_tree_initial++;
	    assert(index_in_tree_initial < tokens_nb);
	    tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_cons(tree_initial[index_in_tree_initial].token, tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens);
	    if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE) stack_count++;
	    if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACE) stack_count--;
	  }
	  lexer_lexer_for_c_language_token_liste_reverse_surplace(&(tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens));
	  continue;
	}
      

	if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET) {
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type = TOKEN_TREE_TYPE_NODE_TOP_BRACKET;
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_vide();
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_cons(tree_initial[index_in_tree_initial].token, tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens);
	  int stack_count = 1;
	  while (stack_count != 0) {
	    index_in_tree_initial++;
	    assert(index_in_tree_initial < tokens_nb);
	    tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_cons(tree_initial[index_in_tree_initial].token, tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens);
	    if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET) stack_count++;
	    if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACKET) stack_count--;
	  }
	  lexer_lexer_for_c_language_token_liste_reverse_surplace(&(tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens));
	  continue;
	}
      


	if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR) {
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type = TOKEN_TREE_TYPE_NODE_TOP_PAREN;
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_vide();
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_cons(tree_initial[index_in_tree_initial].token, tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens);
	  int stack_count = 1;
	  while (stack_count != 0) {
	    index_in_tree_initial++;
	    assert(index_in_tree_initial < tokens_nb);
	    tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_cons(tree_initial[index_in_tree_initial].token, tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens);
	    if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR) stack_count++;
	    if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR) stack_count--;
	  }
	  lexer_lexer_for_c_language_token_liste_reverse_surplace(&(tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens));
	  continue;
	}

	assert(false);
      }

      
#if 0
    // printing
    for (int index_in_tree_after_bracketing_and_parenthezing = 0; tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type != TOKEN_TREE_TYPE_NULL; index_in_tree_after_bracketing_and_parenthezing++) {
      fprintf(stderr, "[%3d] ", index_in_tree_after_bracketing_and_parenthezing);

      if (tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type == TOKEN_TREE_TYPE_LEAF) {
	fprintf(stderr, "LEAF: '%s'\n", tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].token -> value);
	continue;
      }
      
      if (tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type == TOKEN_TREE_TYPE_NODE_TOP_BRACE) {
	fprintf(stderr, "NODE TOP BRACE: ");
	for (const lexer_lexer_for_c_language_token_liste_t * p = tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens; p != NULL; p = p-> cdr)
	  fprintf(stderr, "%s", p -> car -> value);
	fprintf(stderr, "\n");
	continue;
      }

      if (tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type == TOKEN_TREE_TYPE_NODE_TOP_BRACKET) {
	fprintf(stderr, "NODE TOP BRACKET: ");
	for (const lexer_lexer_for_c_language_token_liste_t * p = tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens; p != NULL; p = p-> cdr)
	  fprintf(stderr, "%s", p -> car -> value);
	fprintf(stderr, "\n");
	continue;
      }

      if (tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type == TOKEN_TREE_TYPE_NODE_TOP_PAREN) {
	fprintf(stderr, "NODE TOP PAREN: ");
	for (const lexer_lexer_for_c_language_token_liste_t * p = tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens; p != NULL; p = p-> cdr)
	  fprintf(stderr, "%s", p -> car -> value);
	fprintf(stderr, "\n");
	continue;
      }

      puts("ERROR\n");
      assert(false);
    }
#endif
    }
  } while (false);
  // fin des brackets top-level
  



#endif











expression_tree_t * generate_the_tree_for_a_constant_array_size(const lexer_lexer_for_c_language_token_liste_t * const tokens_with_sq_brackets_to_remove) {
  assert(tokens_with_sq_brackets_to_remove != NULL);
  // First, we have to remove the first and the last tokens which are '[' and ']'.
  lexer_lexer_for_c_language_token_liste_t * tokens = NULL;
  {
    const lexer_lexer_for_c_language_token_t * first_token;
    const lexer_lexer_for_c_language_token_t * last_token;
    first_token = tokens_with_sq_brackets_to_remove -> car;
    last_token = lexer_lexer_for_c_language_token_liste_get_last(tokens_with_sq_brackets_to_remove);
    assert(first_token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET);
    assert(last_token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACKET);
  }
  tokens = lexer_lexer_for_c_language_token_liste_get_without_the_last_and_the_first(tokens_with_sq_brackets_to_remove);
  expression_tree_t * tree;
  tree = build_the_expression_tree(tokens);
  lexer_lexer_for_c_language_token_liste_free(tokens);
  return tree;
}

static void display_tree_with_the_dot_description(const char * dot_description) {
#if 1
  {
    FILE * f;
#if 0
    f = fopen("tree.dot", "w");
    //fwrite(dot_description, f);
    fputs(dot_description, f);
    fclose(f);
    system("dot -Tjpg tree.dot > tree.jpg && open tree.jpg");
#else
    char * filename = strcopy("tree");
    stradd3(&filename, "_rand", uint_string((unsigned)((uint16_t)random())));
    char * filename_dot = NULL;
    filename_dot = strconcat(filename, ".dot");
    char * cmd = NULL;
    asprintf(&cmd, "dot -Tjpg %s.dot > %s.jpg && open %s.jpg", filename, filename, filename);
    f = fopen(filename_dot, "w");
    fputs(dot_description, f);
    fclose(f);
    assert(0 == system(cmd));
    strfree(cmd);
    strfree(filename_dot);
    strfree(filename);
#endif
  }
#endif
}

void display_expression_tree(const expression_tree_t * tree) {
  assert(tree != NULL);
  char * dot_description = expression_tree_write_a_dot_description_for_a_file(tree);
  //printf("\n\n\n%s\n", dot_description);
  display_tree_with_the_dot_description(dot_description);
  strfree(dot_description);
}

void compile_the_code_for_a_constant_array_size(symbol_table_elt_t * elt) {
  assert(elt -> array_huh);
  assert(elt -> array_size_code_text != NULL);
  assert(elt -> array_size_code_tokens != NULL);
  // p. 409 or 421

  // p.107:
  // "An **integer constant expression** shall have integer type and 
  // shall only have operands that are integer constants, enumeration constants, 
  // character constants, sizeof expressions whose results are integer constants, 
  // and floating constants that are the immediate operands of casts."
  
  // Complicated without automated parser…!
  
  // It is possible to write:
  //  - "#define M 3 \n a = M \n #undef M \n #define M 2 + 4 \n * M;"
  //  - "a = #include "lll.c";"
  //  - 2 * 3^0 + 1
  //  - …
  //
  // => It is compulsory to run the preprocessor before the parser.
#if 0
#define MMM (*((int *)NULL)) = 3

#define NNN {int zzztab[-1];}
  
  MMM;
  NNN;
  NNN;
#endif
  // Similarly, the blanks and the comments have to be filtered out.
  //
  // => From the source token list, a new list in which blanks and comments are removed, and preprocessor run.

  // Instead of writing of parser, 
  // the LA(1)+LR(0) automaton tells us that the information we need to build the tree is local.
  // More, in reading the current token and the next token, we know if we have to shift (push on the stack) 
  // or reduce (pop from the stack, make the tree, and push the new tree on the stack).
  // 
  // For instance, we are reading the expression "2 * 3 ^ 4 + 1" (with ^ meaning power for the current sake).
  //  - We push 2 on the stack (think of the LR(1) automaton).
  //  - We read '*'. We do not have the second argument and we do not know if we will a parent or a child. We push '*' on the stack (think of the LR(1) automaton).
  //  - We read 3. First, we could think of making a tree with '*'; but the following operator might have priority. So we wait: we push 3 on the stack (think of the LR(1) automaton).
  //  - We read '^'. Same reasons, we push it (think of the LR(1) automaton).
  //  - We read 4. Same reasons, we push it (think of the LR(1) automaton).
  //  - We read '+'. Now, we actually know that the previous operator have priority (think of the LR(1) automaton). So we reduce! We make the tree and push it.
  //    And we iterate the reduction: the current operator is '+' and the previous one is '*'. We reduce again (think of the LR(1) automaton)! There is no more operator, so we shift now.
  //  - We read '1'. We push it.
  //  - We read EOF. Think of the LR(1) automaton: we read it.
  //
  // So, what does that mean?
  // That we can write a parser with our hands.
  // But it is preferable to automatize this step, and writing manually this function is allright for small grammars.

#if 0
  (void) (1 + (2, 3));

  // What is the meaning of "(void) (1 + (2, 3));"?
  // p. 106: "The left operand of a comma operator is evaluated as a void expression"
  // p. 106: "Then the right operand is evaluated; the result has its type and value."
  // p. 106: footnote 97: "A comma operator does not yield an lvalue."
  // => 4!
#endif

  // First, we have to remove the first and the last tokens which are '[' and ']'.
  lexer_lexer_for_c_language_token_liste_t * tokens = NULL;
  {
    const lexer_lexer_for_c_language_token_t * first_token;
    const lexer_lexer_for_c_language_token_t * last_token;
    first_token = elt -> array_size_code_tokens -> car;
    last_token = lexer_lexer_for_c_language_token_liste_get_last(elt -> array_size_code_tokens);
    assert(first_token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET);
    assert(last_token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACKET);
  }
  tokens = lexer_lexer_for_c_language_token_liste_get_without_the_last_and_the_first(elt -> array_size_code_tokens);
  expression_tree_t * tree;
  tree = build_the_expression_tree(tokens);


  char * dot_description = expression_tree_write_a_dot_description_for_a_file(tree);
  
  printf("\n\n\n%s\n", dot_description);

#if 1
  {
    FILE * f;
#if 0
    f = fopen("tree.dot", "w");
    //fwrite(dot_description, f);
    fputs(dot_description, f);
    fclose(f);
    system("dot -Tjpg tree.dot > tree.jpg && open tree.jpg");
#else
    char * filename = strcopy("tree");
    stradd3(&filename, "_rand", uint_string((unsigned)((uint8_t)random())));
    char * filename_dot = NULL;
    filename_dot = strconcat(filename, ".dot");
    char * cmd = NULL;
    asprintf(&cmd, "dot -Tjpg %s.dot > %s.jpg && open %s.jpg", filename, filename, filename);
    f = fopen(filename_dot, "w");
    fputs(dot_description, f);
    fclose(f);
    system(cmd);
    strfree(cmd);
    strfree(filename_dot);
    strfree(filename);
#endif
  }
#endif

  {
    const char * type = NULL;
    char c;
    int i;
    float f;
    double d;
    char * s;
    type = expression_tree_compute_constant_value_old(tree, &c, &i, &f, &d, &s);

    printf("TYPE: %s\n", type);
    if (type == CONSTANT_VALUE_TYPE_CHAR) printf("value = %c\n", c);
    if (type == CONSTANT_VALUE_TYPE_INT) printf("value = %d\n", i);
    if (type == CONSTANT_VALUE_TYPE_FLOAT) printf("value = %f\n", f);
    if (type == CONSTANT_VALUE_TYPE_DOUBLE) printf("value = %lf\n", d);
    if (type == CONSTANT_VALUE_TYPE_STRING) printf("value = %s\n", s);
  }


  fprintf(stderr, "TODO XXX: store the value in the symbol table!\n");
  //assert(false);
}



static int cast_priority(const char * type) {
  assert(type != NULL);
  assert(type != CONSTANT_VALUE_TYPE_STRING);
  assert(type != CONSTANT_VALUE_TYPE_IDENT);
  if (type == CONSTANT_VALUE_TYPE_CHAR) return 1;
  if (type == CONSTANT_VALUE_TYPE_INT) return 2;
  if (type == CONSTANT_VALUE_TYPE_FLOAT) return 3;
  if (type == CONSTANT_VALUE_TYPE_DOUBLE) return 4;
  assert(false);
  return 0;
}

static const char * return_the_largest_type(const char * type1, const char * type2) {
  const int p1 = cast_priority(type1);
  const int p2 = cast_priority(type2);
  if (p1 > p2) return type1;
  return type2;
}

static void convert_the_type(const char * type_src, const char * type_dest, constant_value_t * value) {
  assert(type_src != CONSTANT_VALUE_TYPE_NULL);
  assert(type_dest != CONSTANT_VALUE_TYPE_NULL);
  if (type_dest == CONSTANT_VALUE_TYPE_CHAR) {
    if (type_src == CONSTANT_VALUE_TYPE_CHAR) return;
    if (type_src == CONSTANT_VALUE_TYPE_INT) { value -> c = (char) value -> i; return; }
    if (type_src == CONSTANT_VALUE_TYPE_FLOAT) { value -> c = (char) value -> f; return; }
    if (type_src == CONSTANT_VALUE_TYPE_DOUBLE) { value -> c = (char) value -> d; return; }
    if (type_src == CONSTANT_VALUE_TYPE_STRING) { assert(false); return; }
    assert(false);
  }
  if (type_dest == CONSTANT_VALUE_TYPE_INT) {
    if (type_src == CONSTANT_VALUE_TYPE_CHAR) { value -> i = (int) value -> c; return; }
    if (type_src == CONSTANT_VALUE_TYPE_INT) { return; }
    if (type_src == CONSTANT_VALUE_TYPE_FLOAT) { value -> i = (int) value -> f; return; }
    if (type_src == CONSTANT_VALUE_TYPE_DOUBLE) { value -> i = (int) value -> d; return; }
    if (type_src == CONSTANT_VALUE_TYPE_STRING) { assert(false); return; }
    assert(false);
  }
  if (type_dest == CONSTANT_VALUE_TYPE_FLOAT) {
    if (type_src == CONSTANT_VALUE_TYPE_CHAR) { value -> f = (float) value -> c; return; }
    if (type_src == CONSTANT_VALUE_TYPE_INT) { value -> f = (float) value -> i; return; }
    if (type_src == CONSTANT_VALUE_TYPE_FLOAT) { return; }
    if (type_src == CONSTANT_VALUE_TYPE_DOUBLE) { value -> f = (float) value -> d; return; }
    if (type_src == CONSTANT_VALUE_TYPE_STRING) { assert(false); return; }
    assert(false);
  }
  if (type_dest == CONSTANT_VALUE_TYPE_DOUBLE) {
    if (type_src == CONSTANT_VALUE_TYPE_CHAR) { value -> d = (double) value -> c; return; }
    if (type_src == CONSTANT_VALUE_TYPE_INT) { value -> d = (double) value -> i; return; }
    if (type_src == CONSTANT_VALUE_TYPE_FLOAT) { value -> d = (double) value -> f; return; }
    if (type_src == CONSTANT_VALUE_TYPE_DOUBLE) { return; }
    if (type_src == CONSTANT_VALUE_TYPE_STRING) { assert(false); return; }
    assert(false);
  }
  if (type_dest == CONSTANT_VALUE_TYPE_STRING) {
    if (type_src == CONSTANT_VALUE_TYPE_CHAR) { assert(false); return; }
    if (type_src == CONSTANT_VALUE_TYPE_INT) { assert(false); return; }
    if (type_src == CONSTANT_VALUE_TYPE_FLOAT) { assert(false); return; }
    if (type_src == CONSTANT_VALUE_TYPE_DOUBLE) { assert(false); return; }
    if (type_src == CONSTANT_VALUE_TYPE_STRING) { return; }
    assert(false);
  }
  assert(false);
}




static void convert_the_type_old(const char * type_src, const char * type_dest, char * const char_ptr, int * const int_ptr, float * const float_ptr, double * const double_ptr, char * (* const string_ptr)) {
  assert(type_src != CONSTANT_VALUE_TYPE_NULL);
  assert(type_dest != CONSTANT_VALUE_TYPE_NULL);
  if (type_dest == CONSTANT_VALUE_TYPE_CHAR) {
    if (type_src == CONSTANT_VALUE_TYPE_CHAR) return;
    if (type_src == CONSTANT_VALUE_TYPE_INT) { *char_ptr = (char) *int_ptr; return; }
    if (type_src == CONSTANT_VALUE_TYPE_FLOAT) { *char_ptr = (char) *float_ptr; return; }
    if (type_src == CONSTANT_VALUE_TYPE_DOUBLE) { *char_ptr = (char) *double_ptr; return; }
    if (type_src == CONSTANT_VALUE_TYPE_STRING) { assert(false); return; }
    assert(false);
  }
  if (type_dest == CONSTANT_VALUE_TYPE_INT) {
    if (type_src == CONSTANT_VALUE_TYPE_CHAR) { *int_ptr = (int) *char_ptr; return; }
    if (type_src == CONSTANT_VALUE_TYPE_INT) { return; }
    if (type_src == CONSTANT_VALUE_TYPE_FLOAT) { *int_ptr = (int) *float_ptr; return; }
    if (type_src == CONSTANT_VALUE_TYPE_DOUBLE) { *int_ptr = (int) *double_ptr; return; }
    if (type_src == CONSTANT_VALUE_TYPE_STRING) { assert(false); return; }
    assert(false);
  }
  if (type_dest == CONSTANT_VALUE_TYPE_FLOAT) {
    if (type_src == CONSTANT_VALUE_TYPE_CHAR) { *float_ptr = (float) *char_ptr; return; }
    if (type_src == CONSTANT_VALUE_TYPE_INT) { *float_ptr = (float) *int_ptr; return; }
    if (type_src == CONSTANT_VALUE_TYPE_FLOAT) { return; }
    if (type_src == CONSTANT_VALUE_TYPE_DOUBLE) { *float_ptr = (float) *double_ptr; return; }
    if (type_src == CONSTANT_VALUE_TYPE_STRING) { assert(false); return; }
    assert(false);
  }
  if (type_dest == CONSTANT_VALUE_TYPE_DOUBLE) {
    if (type_src == CONSTANT_VALUE_TYPE_CHAR) { *double_ptr = (double) *char_ptr; return; }
    if (type_src == CONSTANT_VALUE_TYPE_INT) { *double_ptr = (double) *int_ptr; return; }
    if (type_src == CONSTANT_VALUE_TYPE_FLOAT) { *double_ptr = (double) *float_ptr; return; }
    if (type_src == CONSTANT_VALUE_TYPE_DOUBLE) { return; }
    if (type_src == CONSTANT_VALUE_TYPE_STRING) { assert(false); return; }
    assert(false);
  }
  if (type_dest == CONSTANT_VALUE_TYPE_STRING) {
    if (type_src == CONSTANT_VALUE_TYPE_CHAR) { assert(false); return; }
    if (type_src == CONSTANT_VALUE_TYPE_INT) { assert(false); return; }
    if (type_src == CONSTANT_VALUE_TYPE_FLOAT) { assert(false); return; }
    if (type_src == CONSTANT_VALUE_TYPE_DOUBLE) { assert(false); return; }
    if (type_src == CONSTANT_VALUE_TYPE_STRING) { return; }
    assert(false);
  }
  assert(false);
}






static const char * expression_tree_compute_constant_value(const expression_tree_t * const tree, constant_value_t * const value) {
  assert(tree != NULL);
  assert(value != NULL);
  
 if (tree -> type == EXPRESSION_TREE_TYPE_NULL) {
   assert(false);
   return NULL;
 }
 
 if (tree -> type == EXPRESSION_TREE_TYPE_LEAF) {
   const char * constant_type_of_the_token = NULL;
   constant_type_of_the_token = token_type_of_the_constant_value(tree -> content1 -> type);
   assert(constant_type_of_the_token != NULL);
   if (constant_type_of_the_token == CONSTANT_VALUE_TYPE_CHAR) {
     if (LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE == tree -> content1 -> type) value -> c = tree -> content1 -> value[1];
     else if (LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_ESCAPE == tree -> content1 -> type) value -> c = tree -> content1 -> value[2];
     else { assert(false); }
     return constant_type_of_the_token;
   }
   if (constant_type_of_the_token == CONSTANT_VALUE_TYPE_INT) {
     //value -> i = atoi(tree -> content1 -> value);
     value -> i = strtol(tree -> content1 -> value, NULL, 0);
     return constant_type_of_the_token;
   }
   if (constant_type_of_the_token == CONSTANT_VALUE_TYPE_FLOAT) {
     //value -> f = atof(tree -> content1 -> value);
     value -> f = strtof(tree -> content1 -> value, NULL);
     return constant_type_of_the_token;
   }
   if (constant_type_of_the_token == CONSTANT_VALUE_TYPE_DOUBLE) {
     value -> d = strtod(tree -> content1 -> value, NULL);
     return constant_type_of_the_token;
   }
   if (constant_type_of_the_token == CONSTANT_VALUE_TYPE_IDENT) {
     assert(false);
     return NULL;
   }
   if (constant_type_of_the_token == CONSTANT_VALUE_TYPE_STRING) {
     value -> s = strcopy(tree -> content1 -> value);
     return constant_type_of_the_token;
   }
   assert(false);
   return NULL;
 }

 
 if (tree -> type == EXPRESSION_TREE_TYPE_PREFIX_OPERATOR) {
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR) {
     // TODO: if the type of the child is a constant pointer toward a constant value, then we can compute it.
     assert(false);
     return NULL;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_OPERATOR) {
     const char * child_type = NULL;
     child_type = expression_tree_compute_constant_value(tree -> child1, value);
     assert(child_type != CONSTANT_VALUE_TYPE_STRING);
     return child_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_OPERATOR) {
     const char * child_type = NULL;
     child_type = expression_tree_compute_constant_value(tree -> child1, value);
     assert(child_type != CONSTANT_VALUE_TYPE_STRING);
     if (child_type == CONSTANT_VALUE_TYPE_CHAR) value -> c = - value -> c;
     if (child_type == CONSTANT_VALUE_TYPE_INT) value -> i = - value -> i;
     if (child_type == CONSTANT_VALUE_TYPE_FLOAT) value -> f = - value -> f;
     if (child_type == CONSTANT_VALUE_TYPE_DOUBLE) value -> d = - value -> d;
     return child_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_TILDE_OPERATOR) {
     const char * child_type = NULL;
     child_type = expression_tree_compute_constant_value(tree -> child1, value);
     assert(child_type != CONSTANT_VALUE_TYPE_STRING);
     if (child_type == CONSTANT_VALUE_TYPE_CHAR) value -> c = ~ value -> c;
     if (child_type == CONSTANT_VALUE_TYPE_INT) value -> i = ~ value -> i;
     if (child_type == CONSTANT_VALUE_TYPE_FLOAT) assert(false); //value -> f = ~ value -> f;
     if (child_type == CONSTANT_VALUE_TYPE_DOUBLE) assert(false); //value -> d = ~ value -> d;
     return child_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PERLUETE_OPERATOR) {
     // TODO: we should be able to get the address of a static variable or a function defined in the current module.
     assert(false);
     return NULL;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_PLUS_OPERATOR) {
     assert(false);
     return NULL;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_MINUS_OPERARTOR) {
     assert(false);
     return NULL;
   }

   assert(false);
   return NULL;
 }
 
 if (tree -> type == EXPRESSION_TREE_TYPE_INFIX_OPERATOR) {
   const char * child1_type = NULL;
   constant_value_t v1;
   child1_type = expression_tree_compute_constant_value(tree -> child1, &v1);
   const char * child2_type = NULL;
   constant_value_t v2;
   child2_type = expression_tree_compute_constant_value(tree -> child2, &v2);
   const char * node_type = NULL;
   if (child1_type == CONSTANT_VALUE_TYPE_STRING || child2_type == CONSTANT_VALUE_TYPE_STRING) {
     assert(false);
   }
   /*
     src/programme.c:1112: error: invalid operands to binary & (have ‘float’ and ‘float’)
     src/programme.c:1113: error: invalid operands to binary & (have ‘double’ and ‘double’)
     src/programme.c:1129: error: invalid operands to binary | (have ‘float’ and ‘float’)
     src/programme.c:1130: error: invalid operands to binary | (have ‘double’ and ‘double’)
     src/programme.c:1156: error: invalid operands to binary ^ (have ‘float’ and ‘float’)
     src/programme.c:1157: error: invalid operands to binary ^ (have ‘double’ and ‘double’)
     src/programme.c:1166: error: invalid operands to binary % (have ‘float’ and ‘float’)
     src/programme.c:1167: error: invalid operands to binary % (have ‘double’ and ‘double’)
     src/programme.c:1226: error: invalid operands to binary << (have ‘float’ and ‘float’)
     src/programme.c:1227: error: invalid operands to binary << (have ‘double’ and ‘double’)
     src/programme.c:1236: error: invalid operands to binary >> (have ‘float’ and ‘float’)
     src/programme.c:1237: error: invalid operands to binary >> (have ‘double’ and ‘double’)
   */

   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA) {
     *value = v2;
     return child2_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_POINT_OPERATOR) {
     // TODO left-hand must be a struct or a union
     assert(false);
     return NULL;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ARROW_OPERATOR) {
     // TODO left-hand must be a pointer to a struct or a union
     assert(false);
     return NULL;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type(child1_type, node_type, &v1);
     convert_the_type(child2_type, node_type, &v2);
     value -> c = v1.c * v2.c;
     value -> i = v1.i * v2.i;
     value -> f = v1.f * v2.f;
     value -> d = v1.d * v2.d;
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type(child1_type, node_type, &v1);
     convert_the_type(child2_type, node_type, &v2);
     value -> c = v1.c + v2.c;
     value -> i = v1.i + v2.i;
     value -> f = v1.f + v2.f;
     value -> d = v1.d + v2.d;
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type(child1_type, node_type, &v1);
     convert_the_type(child2_type, node_type, &v2);
     value -> c = v1.c - v2.c;
     value -> i = v1.i - v2.i;
     value -> f = v1.f - v2.f;
     value -> d = v1.d - v2.d;
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RDIV_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type(child1_type, node_type, &v1);
     convert_the_type(child2_type, node_type, &v2);
     value -> c = v1.c / v2.c;
     value -> i = v1.i / v2.i;
     value -> f = v1.f / v2.f;
     value -> d = v1.d / v2.d;
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PERLUETE_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type(child1_type, node_type, &v1);
     convert_the_type(child2_type, node_type, &v2);
     value -> c = v1.c & v2.c;
     value -> i = v1.i & v2.i;
     assert(node_type != CONSTANT_VALUE_TYPE_FLOAT); //value -> f = v1.f & v2.f;
     assert(node_type != CONSTANT_VALUE_TYPE_DOUBLE); //value -> d = v1.d & v2.d;
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PERLUETE_OPERATOR) {
     node_type = CONSTANT_VALUE_TYPE_INT;
     convert_the_type(child1_type, node_type, &v1);
     convert_the_type(child2_type, node_type, &v2);
     value -> i = v1.i && v2.i;
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PIPE_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type(child1_type, node_type, &v1);
     convert_the_type(child2_type, node_type, &v2);
     value -> c = v1.c | v2.c;
     value -> i = v1.i | v2.i;
     assert(node_type != CONSTANT_VALUE_TYPE_FLOAT); //value -> f = v1.f | v2.f;
     assert(node_type != CONSTANT_VALUE_TYPE_DOUBLE); //value -> d = v1.d | v2.d;
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PIPE_OPERATOR) {
     node_type = CONSTANT_VALUE_TYPE_INT;
     convert_the_type(child1_type, node_type, &v1);
     convert_the_type(child2_type, node_type, &v2);
     value -> i = v1.i || v2.i;
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_EQUAL_HUH_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type(child1_type, node_type, &v1);
     convert_the_type(child2_type, node_type, &v2);
     if (node_type == CONSTANT_VALUE_TYPE_CHAR) value -> i = (v1.c == v2.c);
     if (node_type == CONSTANT_VALUE_TYPE_INT) value -> i = (v1.i == v2.i);
     if (node_type == CONSTANT_VALUE_TYPE_FLOAT) value -> i = (v1.f == v2.f);
     if (node_type == CONSTANT_VALUE_TYPE_DOUBLE) value -> i = (v1.d == v2.d);
     return CONSTANT_VALUE_TYPE_INT;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HAT_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type(child1_type, node_type, &v1);
     convert_the_type(child2_type, node_type, &v2);
     value -> c = v1.c ^ v2.c;
     value -> i = v1.i ^ v2.i;
     assert(node_type != CONSTANT_VALUE_TYPE_FLOAT); //value -> f = v1.f ^ v2.f;
     assert(node_type != CONSTANT_VALUE_TYPE_DOUBLE); //value -> d = v1.d ^ v2.d;
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PERCENT_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type(child1_type, node_type, &v1);
     convert_the_type(child2_type, node_type, &v2);
     value -> c = v1.c % v2.c;
     value -> i = v1.i % v2.i;
     assert(node_type != CONSTANT_VALUE_TYPE_FLOAT); //value -> f = v1.f % v2.f;
     assert(node_type != CONSTANT_VALUE_TYPE_DOUBLE); //value -> d = v1.d % v2.d;
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIFFERENT_HUH_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type(child1_type, node_type, &v1);
     convert_the_type(child2_type, node_type, &v2);
     if (node_type == CONSTANT_VALUE_TYPE_CHAR) value -> i = (v1.c != v2.c);
     if (node_type == CONSTANT_VALUE_TYPE_INT) value -> i = (v1.i != v2.i);
     if (node_type == CONSTANT_VALUE_TYPE_FLOAT) value -> i = (v1.f != v2.f);
     if (node_type == CONSTANT_VALUE_TYPE_DOUBLE) value -> i = (v1.d != v2.d);
     return CONSTANT_VALUE_TYPE_INT;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type(child1_type, node_type, &v1);
     convert_the_type(child2_type, node_type, &v2);
     if (node_type == CONSTANT_VALUE_TYPE_CHAR) value -> i = (v1.c < v2.c);
     if (node_type == CONSTANT_VALUE_TYPE_INT) value -> i = (v1.i < v2.i);
     if (node_type == CONSTANT_VALUE_TYPE_FLOAT) value -> i = (v1.f < v2.f);
     if (node_type == CONSTANT_VALUE_TYPE_DOUBLE) value -> i = (v1.d < v2.d);
     return CONSTANT_VALUE_TYPE_INT;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type(child1_type, node_type, &v1);
     convert_the_type(child2_type, node_type, &v2);
     if (node_type == CONSTANT_VALUE_TYPE_CHAR) value -> i = (v1.c > v2.c);
     if (node_type == CONSTANT_VALUE_TYPE_INT) value -> i = (v1.i > v2.i);
     if (node_type == CONSTANT_VALUE_TYPE_FLOAT) value -> i = (v1.f > v2.f);
     if (node_type == CONSTANT_VALUE_TYPE_DOUBLE) value -> i = (v1.d > v2.d);
     return CONSTANT_VALUE_TYPE_INT;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OR_EQUAL_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type(child1_type, node_type, &v1);
     convert_the_type(child2_type, node_type, &v2);
     if (node_type == CONSTANT_VALUE_TYPE_CHAR) value -> i = (v1.c <= v2.c);
     if (node_type == CONSTANT_VALUE_TYPE_INT) value -> i = (v1.i <= v2.i);
     if (node_type == CONSTANT_VALUE_TYPE_FLOAT) value -> i = (v1.f <= v2.f);
     if (node_type == CONSTANT_VALUE_TYPE_DOUBLE) value -> i = (v1.d <= v2.d);
     return CONSTANT_VALUE_TYPE_INT;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OR_EQUAL_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type(child1_type, node_type, &v1);
     convert_the_type(child2_type, node_type, &v2);
     if (node_type == CONSTANT_VALUE_TYPE_CHAR) value -> i = (v1.c >= v2.c);
     if (node_type == CONSTANT_VALUE_TYPE_INT) value -> i = (v1.i >= v2.i);
     if (node_type == CONSTANT_VALUE_TYPE_FLOAT) value -> i = (v1.f >= v2.f);
     if (node_type == CONSTANT_VALUE_TYPE_DOUBLE) value -> i = (v1.d >= v2.d);
     return CONSTANT_VALUE_TYPE_INT;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_LSHIFT_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type(child1_type, node_type, &v1);
     convert_the_type(child2_type, node_type, &v2);
     value -> c = (v1.c << v2.c);
     value -> i = (v1.i << v2.i);
     assert(node_type != CONSTANT_VALUE_TYPE_FLOAT); //value -> f = (v1.f << v2.f);
     assert(node_type != CONSTANT_VALUE_TYPE_DOUBLE); //value -> d = (v1.d << v2.d);
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RSHIFT_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type(child1_type, node_type, &v1);
     convert_the_type(child2_type, node_type, &v2);
     value -> c = (v1.c >> v2.c);
     value -> i = (v1.i >> v2.i);
     assert(node_type != CONSTANT_VALUE_TYPE_FLOAT); //value -> f = (v1.f >> v2.f);
     assert(node_type != CONSTANT_VALUE_TYPE_DOUBLE); //value -> d = (v1.d >> v2.d);
     return node_type;
   }

   assert(false);
   return NULL;
 }
 
 
 if (tree -> type == EXPRESSION_TREE_TYPE_POSTFIX_OPERATOR) {
   assert(false); // None of the postfix operators (++ and --) are constants.
   return NULL;
 }
 
 if (tree -> type == EXPRESSION_TREE_TYPE_PAREN) {
   const char * child_type = NULL;
   child_type = expression_tree_compute_constant_value(tree -> child1, value);
   return child_type;
 }
 
 assert(false);
 return NULL;
}



static const char * expression_tree_compute_constant_value_old(const expression_tree_t * tree, char * const char_ptr, int * const int_ptr, float * const float_ptr, double * const double_ptr, char * (* const string_ptr)) {
  assert(tree != NULL);
  assert(char_ptr != NULL);
  assert(int_ptr != NULL);
  assert(float_ptr != NULL);
  assert(double_ptr != NULL);

 if (tree -> type == EXPRESSION_TREE_TYPE_NULL) {
   assert(false);
   return NULL;
 }
 
 if (tree -> type == EXPRESSION_TREE_TYPE_LEAF) {
   const char * constant_type_of_the_token = NULL;
   constant_type_of_the_token = token_type_of_the_constant_value(tree -> content1 -> type);
   assert(constant_type_of_the_token != NULL);
   if (constant_type_of_the_token == CONSTANT_VALUE_TYPE_CHAR) {
     if (LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE == tree -> content1 -> type) (*char_ptr) = tree -> content1 -> value[1];
     else if (LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_ESCAPE == tree -> content1 -> type) (*char_ptr) = tree -> content1 -> value[2];
     else { assert(false); }
     return constant_type_of_the_token;
   }
   if (constant_type_of_the_token == CONSTANT_VALUE_TYPE_INT) {
     //(*int_ptr) = atoi(tree -> content1 -> value);
     (*int_ptr) = strtol(tree -> content1 -> value, NULL, 0);
     return constant_type_of_the_token;
   }
   if (constant_type_of_the_token == CONSTANT_VALUE_TYPE_FLOAT) {
     //*float_ptr = atof(tree -> content1 -> value);
     *float_ptr = strtof(tree -> content1 -> value, NULL);
     return constant_type_of_the_token;
   }
   if (constant_type_of_the_token == CONSTANT_VALUE_TYPE_DOUBLE) {
     *double_ptr = strtod(tree -> content1 -> value, NULL);
     return constant_type_of_the_token;
   }
   if (constant_type_of_the_token == CONSTANT_VALUE_TYPE_IDENT) {
     assert(false);
     return NULL;
   }
   if (constant_type_of_the_token == CONSTANT_VALUE_TYPE_STRING) {
     (*string_ptr) = strcopy(tree -> content1 -> value);
     return constant_type_of_the_token;
   }
   assert(false);
   return NULL;
 }

 
 if (tree -> type == EXPRESSION_TREE_TYPE_PREFIX_OPERATOR) {
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR) {
     // TODO: if the type of the child is a constant pointer toward a constant value, then we can compute it.
     assert(false);
     return NULL;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_OPERATOR) {
     const char * child_type = NULL;
     child_type = expression_tree_compute_constant_value_old(tree -> child1, char_ptr, int_ptr, float_ptr, double_ptr, string_ptr);
     assert(child_type != CONSTANT_VALUE_TYPE_STRING);
     return child_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_OPERATOR) {
     const char * child_type = NULL;
     child_type = expression_tree_compute_constant_value_old(tree -> child1, char_ptr, int_ptr, float_ptr, double_ptr, string_ptr);
     assert(child_type != CONSTANT_VALUE_TYPE_STRING);
     if (child_type == CONSTANT_VALUE_TYPE_CHAR) (*char_ptr) = - (*char_ptr);
     if (child_type == CONSTANT_VALUE_TYPE_INT) (*int_ptr) = - (*int_ptr);
     if (child_type == CONSTANT_VALUE_TYPE_FLOAT) (*float_ptr) = - (*float_ptr);
     if (child_type == CONSTANT_VALUE_TYPE_DOUBLE) (*double_ptr) = - (*double_ptr);
     return child_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_TILDE_OPERATOR) {
     const char * child_type = NULL;
     child_type = expression_tree_compute_constant_value_old(tree -> child1, char_ptr, int_ptr, float_ptr, double_ptr, string_ptr);
     assert(child_type != CONSTANT_VALUE_TYPE_STRING);
     if (child_type == CONSTANT_VALUE_TYPE_CHAR) (*char_ptr) = ~ (*char_ptr);
     if (child_type == CONSTANT_VALUE_TYPE_INT) (*int_ptr) = ~ (*int_ptr);
     if (child_type == CONSTANT_VALUE_TYPE_FLOAT) assert(false); //(*float_ptr) = ~ (*float_ptr);
     if (child_type == CONSTANT_VALUE_TYPE_DOUBLE) assert(false); //(*double_ptr) = ~ (*double_ptr);
     return child_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PERLUETE_OPERATOR) {
     // TODO: we should be able to get the address of a static variable or a function defined in the current module.
     assert(false);
     return NULL;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_PLUS_OPERATOR) {
     assert(false);
     return NULL;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_MINUS_OPERARTOR) {
     assert(false);
     return NULL;
   }

   assert(false);
   return NULL;
 }
 
 if (tree -> type == EXPRESSION_TREE_TYPE_INFIX_OPERATOR) {
   const char * child1_type = NULL;
   char c1;
   int i1;
   float f1;
   double d1;
   char * s1;
   child1_type = expression_tree_compute_constant_value_old(tree -> child1, &c1, &i1, &f1, &d1, &s1);
   const char * child2_type = NULL;
   char c2;
   int i2;
   float f2;
   double d2;
   char * s2;
   child2_type = expression_tree_compute_constant_value_old(tree -> child2, &c2, &i2, &f2, &d2, &s2);
   const char * node_type = NULL;
   if (child1_type == CONSTANT_VALUE_TYPE_STRING || child2_type == CONSTANT_VALUE_TYPE_STRING) {
     assert(false);
   }
   /*
     src/programme.c:1112: error: invalid operands to binary & (have ‘float’ and ‘float’)
     src/programme.c:1113: error: invalid operands to binary & (have ‘double’ and ‘double’)
     src/programme.c:1129: error: invalid operands to binary | (have ‘float’ and ‘float’)
     src/programme.c:1130: error: invalid operands to binary | (have ‘double’ and ‘double’)
     src/programme.c:1156: error: invalid operands to binary ^ (have ‘float’ and ‘float’)
     src/programme.c:1157: error: invalid operands to binary ^ (have ‘double’ and ‘double’)
     src/programme.c:1166: error: invalid operands to binary % (have ‘float’ and ‘float’)
     src/programme.c:1167: error: invalid operands to binary % (have ‘double’ and ‘double’)
     src/programme.c:1226: error: invalid operands to binary << (have ‘float’ and ‘float’)
     src/programme.c:1227: error: invalid operands to binary << (have ‘double’ and ‘double’)
     src/programme.c:1236: error: invalid operands to binary >> (have ‘float’ and ‘float’)
     src/programme.c:1237: error: invalid operands to binary >> (have ‘double’ and ‘double’)
   */

   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA) {
     *char_ptr = c2;
     *int_ptr = i2;
     *float_ptr = f2;
     *double_ptr = d2;
     *string_ptr = s2;
     return child2_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_POINT_OPERATOR) {
     // TODO left-hand must be a struct or a union
     assert(false);
     return NULL;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ARROW_OPERATOR) {
     // TODO left-hand must be a pointer to a struct or a union
     assert(false);
     return NULL;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type_old(child1_type, node_type, &c1, &i1, &f1, &d1, &s1);
     convert_the_type_old(child2_type, node_type, &c2, &i2, &f2, &d2, &s2);
     *char_ptr = c1 * c2;
     *int_ptr = i1 * i2;
     *float_ptr = f1 * f2;
     *double_ptr = d1 * d2;
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type_old(child1_type, node_type, &c1, &i1, &f1, &d1, &s1);
     convert_the_type_old(child2_type, node_type, &c2, &i2, &f2, &d2, &s2);
     *char_ptr = c1 + c2;
     *int_ptr = i1 + i2;
     *float_ptr = f1 + f2;
     *double_ptr = d1 + d2;
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type_old(child1_type, node_type, &c1, &i1, &f1, &d1, &s1);
     convert_the_type_old(child2_type, node_type, &c2, &i2, &f2, &d2, &s2);
     *char_ptr = c1 - c2;
     *int_ptr = i1 - i2;
     *float_ptr = f1 - f2;
     *double_ptr = d1 - d2;
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RDIV_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type_old(child1_type, node_type, &c1, &i1, &f1, &d1, &s1);
     convert_the_type_old(child2_type, node_type, &c2, &i2, &f2, &d2, &s2);
     *char_ptr = c1 / c2;
     *int_ptr = i1 / i2;
     *float_ptr = f1 / f2;
     *double_ptr = d1 / d2;
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PERLUETE_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type_old(child1_type, node_type, &c1, &i1, &f1, &d1, &s1);
     convert_the_type_old(child2_type, node_type, &c2, &i2, &f2, &d2, &s2);
     *char_ptr = c1 & c2;
     *int_ptr = i1 & i2;
     assert(node_type != CONSTANT_VALUE_TYPE_FLOAT); //*float_ptr = f1 & f2;
     assert(node_type != CONSTANT_VALUE_TYPE_DOUBLE); //*double_ptr = d1 & d2;
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PERLUETE_OPERATOR) {
     node_type = CONSTANT_VALUE_TYPE_INT;
     convert_the_type_old(child1_type, node_type, &c1, &i1, &f1, &d1, &s1);
     convert_the_type_old(child2_type, node_type, &c2, &i2, &f2, &d2, &s2);
     *int_ptr = i1 && i2;
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PIPE_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type_old(child1_type, node_type, &c1, &i1, &f1, &d1, &s1);
     convert_the_type_old(child2_type, node_type, &c2, &i2, &f2, &d2, &s2);
     *char_ptr = c1 | c2;
     *int_ptr = i1 | i2;
     assert(node_type != CONSTANT_VALUE_TYPE_FLOAT); //*float_ptr = f1 | f2;
     assert(node_type != CONSTANT_VALUE_TYPE_DOUBLE); //*double_ptr = d1 | d2;
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PIPE_OPERATOR) {
     node_type = CONSTANT_VALUE_TYPE_INT;
     convert_the_type_old(child1_type, node_type, &c1, &i1, &f1, &d1, &s1);
     convert_the_type_old(child2_type, node_type, &c2, &i2, &f2, &d2, &s2);
     *int_ptr = i1 || i2;
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_EQUAL_HUH_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type_old(child1_type, node_type, &c1, &i1, &f1, &d1, &s1);
     convert_the_type_old(child2_type, node_type, &c2, &i2, &f2, &d2, &s2);
     if (node_type == CONSTANT_VALUE_TYPE_CHAR) *int_ptr = (c1 == c2);
     if (node_type == CONSTANT_VALUE_TYPE_INT) *int_ptr = (i1 == i2);
     if (node_type == CONSTANT_VALUE_TYPE_FLOAT) *int_ptr = (f1 == f2);
     if (node_type == CONSTANT_VALUE_TYPE_DOUBLE) *int_ptr = (d1 == d2);
     return CONSTANT_VALUE_TYPE_INT;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HAT_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type_old(child1_type, node_type, &c1, &i1, &f1, &d1, &s1);
     convert_the_type_old(child2_type, node_type, &c2, &i2, &f2, &d2, &s2);
     *char_ptr = c1 ^ c2;
     *int_ptr = i1 ^ i2;
     assert(node_type != CONSTANT_VALUE_TYPE_FLOAT); //*float_ptr = f1 ^ f2;
     assert(node_type != CONSTANT_VALUE_TYPE_DOUBLE); //*double_ptr = d1 ^ d2;
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PERCENT_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type_old(child1_type, node_type, &c1, &i1, &f1, &d1, &s1);
     convert_the_type_old(child2_type, node_type, &c2, &i2, &f2, &d2, &s2);
     *char_ptr = c1 % c2;
     *int_ptr = i1 % i2;
     assert(node_type != CONSTANT_VALUE_TYPE_FLOAT); //*float_ptr = f1 % f2;
     assert(node_type != CONSTANT_VALUE_TYPE_DOUBLE); //*double_ptr = d1 % d2;
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIFFERENT_HUH_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type_old(child1_type, node_type, &c1, &i1, &f1, &d1, &s1);
     convert_the_type_old(child2_type, node_type, &c2, &i2, &f2, &d2, &s2);
     if (node_type == CONSTANT_VALUE_TYPE_CHAR) *int_ptr = (c1 != c2);
     if (node_type == CONSTANT_VALUE_TYPE_INT) *int_ptr = (i1 != i2);
     if (node_type == CONSTANT_VALUE_TYPE_FLOAT) *int_ptr = (f1 != f2);
     if (node_type == CONSTANT_VALUE_TYPE_DOUBLE) *int_ptr = (d1 != d2);
     return CONSTANT_VALUE_TYPE_INT;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type_old(child1_type, node_type, &c1, &i1, &f1, &d1, &s1);
     convert_the_type_old(child2_type, node_type, &c2, &i2, &f2, &d2, &s2);
     if (node_type == CONSTANT_VALUE_TYPE_CHAR) *int_ptr = (c1 < c2);
     if (node_type == CONSTANT_VALUE_TYPE_INT) *int_ptr = (i1 < i2);
     if (node_type == CONSTANT_VALUE_TYPE_FLOAT) *int_ptr = (f1 < f2);
     if (node_type == CONSTANT_VALUE_TYPE_DOUBLE) *int_ptr = (d1 < d2);
     return CONSTANT_VALUE_TYPE_INT;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type_old(child1_type, node_type, &c1, &i1, &f1, &d1, &s1);
     convert_the_type_old(child2_type, node_type, &c2, &i2, &f2, &d2, &s2);
     if (node_type == CONSTANT_VALUE_TYPE_CHAR) *int_ptr = (c1 > c2);
     if (node_type == CONSTANT_VALUE_TYPE_INT) *int_ptr = (i1 > i2);
     if (node_type == CONSTANT_VALUE_TYPE_FLOAT) *int_ptr = (f1 > f2);
     if (node_type == CONSTANT_VALUE_TYPE_DOUBLE) *int_ptr = (d1 > d2);
     return CONSTANT_VALUE_TYPE_INT;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OR_EQUAL_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type_old(child1_type, node_type, &c1, &i1, &f1, &d1, &s1);
     convert_the_type_old(child2_type, node_type, &c2, &i2, &f2, &d2, &s2);
     if (node_type == CONSTANT_VALUE_TYPE_CHAR) *int_ptr = (c1 <= c2);
     if (node_type == CONSTANT_VALUE_TYPE_INT) *int_ptr = (i1 <= i2);
     if (node_type == CONSTANT_VALUE_TYPE_FLOAT) *int_ptr = (f1 <= f2);
     if (node_type == CONSTANT_VALUE_TYPE_DOUBLE) *int_ptr = (d1 <= d2);
     return CONSTANT_VALUE_TYPE_INT;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OR_EQUAL_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type_old(child1_type, node_type, &c1, &i1, &f1, &d1, &s1);
     convert_the_type_old(child2_type, node_type, &c2, &i2, &f2, &d2, &s2);
     if (node_type == CONSTANT_VALUE_TYPE_CHAR) *int_ptr = (c1 >= c2);
     if (node_type == CONSTANT_VALUE_TYPE_INT) *int_ptr = (i1 >= i2);
     if (node_type == CONSTANT_VALUE_TYPE_FLOAT) *int_ptr = (f1 >= f2);
     if (node_type == CONSTANT_VALUE_TYPE_DOUBLE) *int_ptr = (d1 >= d2);
     return CONSTANT_VALUE_TYPE_INT;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_LSHIFT_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type_old(child1_type, node_type, &c1, &i1, &f1, &d1, &s1);
     convert_the_type_old(child2_type, node_type, &c2, &i2, &f2, &d2, &s2);
     *char_ptr = (c1 << c2);
     *int_ptr = (i1 << i2);
     assert(node_type != CONSTANT_VALUE_TYPE_FLOAT); //*float_ptr = (f1 << f2);
     assert(node_type != CONSTANT_VALUE_TYPE_DOUBLE); //*double_ptr = (d1 << d2);
     return node_type;
   }
   if (tree -> content1 -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RSHIFT_OPERATOR) {
     node_type = return_the_largest_type(child1_type, child2_type);
     convert_the_type_old(child1_type, node_type, &c1, &i1, &f1, &d1, &s1);
     convert_the_type_old(child2_type, node_type, &c2, &i2, &f2, &d2, &s2);
     *char_ptr = (c1 >> c2);
     *int_ptr = (i1 >> i2);
     assert(node_type != CONSTANT_VALUE_TYPE_FLOAT); //*float_ptr = (f1 >> f2);
     assert(node_type != CONSTANT_VALUE_TYPE_DOUBLE); //*double_ptr = (d1 >> d2);
     return node_type;
   }

   assert(false);
   return NULL;
 }
 
 
 if (tree -> type == EXPRESSION_TREE_TYPE_POSTFIX_OPERATOR) {
   assert(false); // None of the postfix operators (++ and --) are constants.
   return NULL;
 }
 
 if (tree -> type == EXPRESSION_TREE_TYPE_PAREN) {
   const char * child_type = NULL;
   child_type = expression_tree_compute_constant_value_old(tree -> child1, char_ptr, int_ptr, float_ptr, double_ptr, string_ptr);
   return child_type;
 }
 
 assert(false);
 return NULL;
}



static const char * token_type_of_the_constant_value(const lexer_lexer_for_c_language_token_type_t type) {
  switch (type) {
  default: assert(false); return false; break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BLANK: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_MULTILINES: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_ONELINE_CPP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MONO_LINE: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MULTI_LINES: 
    assert(false);
    break;
	  
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT: 
    return CONSTANT_VALUE_TYPE_IDENT;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_ZERO:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC_V2:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_HEX:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_BIN:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VCC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VC:
    return CONSTANT_VALUE_TYPE_INT;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_WITH_EXP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_HEX_WITH_EXP:
    return CONSTANT_VALUE_TYPE_FLOAT;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_EMPTY:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_ESCAPE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_WIDE:
    return CONSTANT_VALUE_TYPE_CHAR;
    break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_ENDED_BY_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE_ENDED_BY_NEWLINE:
    return CONSTANT_VALUE_TYPE_STRING;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ELLIPSIS:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_POINT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ARROW_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RDIV_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_TILDE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PIPE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PIPE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_EQUAL_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HAT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PERCENT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BANG_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIFFERENT_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OR_EQUAL_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OR_EQUAL_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_MINUS_OPERARTOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_LSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COLON_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_STAR_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RDIV_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERCENT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_MINUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_LSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_HAT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PIPE_OPERATOR:
    assert(false);
    return NULL;
    break;
  }

  assert(false);
  return NULL;
}



static bool_t token_type_is_operator_huh(const lexer_lexer_for_c_language_token_type_t type) {
  switch (type) {
  default: assert(false); return false; break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BLANK: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_MULTILINES: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_ONELINE_CPP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MONO_LINE: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MULTI_LINES: 
    assert(false);
    // must have been already skipped and processed
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_ZERO:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC_V2:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_HEX:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_BIN:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VCC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_WITH_EXP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_HEX_WITH_EXP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_EMPTY:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_ESCAPE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_ENDED_BY_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE_ENDED_BY_NEWLINE:
    return false;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACE:
    return false;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ELLIPSIS:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON:
    return false;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_POINT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ARROW_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RDIV_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_TILDE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PIPE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PIPE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_EQUAL_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HAT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PERCENT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BANG_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIFFERENT_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OR_EQUAL_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OR_EQUAL_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_MINUS_OPERARTOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_LSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COLON_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_STAR_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RDIV_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERCENT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_MINUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_LSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_HAT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PIPE_OPERATOR:
    return true;
    break;
  }

  assert(false);
  return false;
}

static bool_t token_type_is_constant_or_ident_or_string_literal_huh(const lexer_lexer_for_c_language_token_type_t type) {
  switch (type) {
  default: assert(false); return false; break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BLANK: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_MULTILINES: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_ONELINE_CPP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MONO_LINE: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MULTI_LINES: 
    assert(false);
    // must have been already skipped and processed
    break;
	  
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_ZERO:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC_V2:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_HEX:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_BIN:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VCC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_WITH_EXP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_HEX_WITH_EXP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_EMPTY:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_ESCAPE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_ENDED_BY_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE_ENDED_BY_NEWLINE:
    return true;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACE:
    return false;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ELLIPSIS:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON:
    return false;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_POINT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ARROW_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RDIV_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_TILDE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PIPE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PIPE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_EQUAL_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HAT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PERCENT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BANG_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIFFERENT_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OR_EQUAL_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OR_EQUAL_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_MINUS_OPERARTOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_LSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COLON_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_STAR_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RDIV_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERCENT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_MINUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_LSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_HAT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PIPE_OPERATOR:
    return false;
    break;
  }

  assert(false);
  return false;
}

static bool_t token_type_is_prefix_operator_huh(const lexer_lexer_for_c_language_token_type_t type) {
  switch (type) {
  default: assert(false); return false; break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BLANK: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_MULTILINES: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_ONELINE_CPP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MONO_LINE: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MULTI_LINES: 
    assert(false);
    // must have been already skipped and processed
    break;
	  
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_ZERO:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC_V2:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_HEX:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_BIN:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VCC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_WITH_EXP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_HEX_WITH_EXP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_EMPTY:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_ESCAPE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_ENDED_BY_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE_ENDED_BY_NEWLINE:
    return false;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACE:
    return false;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ELLIPSIS:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON:
    return false;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_MINUS_OPERARTOR:
    return true;
    break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_TILDE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PIPE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HAT_OPERATOR:
    return false;
    break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_POINT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ARROW_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RDIV_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PIPE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_EQUAL_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PERCENT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BANG_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIFFERENT_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OR_EQUAL_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OR_EQUAL_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_LSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COLON_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_STAR_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RDIV_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERCENT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_MINUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_LSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_HAT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PIPE_OPERATOR:
    return false;
    break;
  }

  assert(false);
  return false;
}

static bool_t token_type_is_postfix_operator_huh(const lexer_lexer_for_c_language_token_type_t type) {
  switch (type) {
  default: assert(false); return false; break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BLANK: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_MULTILINES: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_ONELINE_CPP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MONO_LINE: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MULTI_LINES: 
    assert(false);
    // must have been already skipped and processed
    break;
	  
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_ZERO:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC_V2:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_HEX:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_BIN:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VCC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_WITH_EXP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_HEX_WITH_EXP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_EMPTY:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_ESCAPE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_ENDED_BY_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE_ENDED_BY_NEWLINE:
    return false;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACE:
    return false;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ELLIPSIS:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON:
    return false;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_TILDE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PIPE_OPERATOR:
    return false;
    break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_MINUS_OPERARTOR:
    return true;
    break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_POINT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ARROW_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RDIV_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PIPE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_EQUAL_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HAT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PERCENT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BANG_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIFFERENT_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OR_EQUAL_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OR_EQUAL_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_LSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COLON_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_STAR_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RDIV_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERCENT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_MINUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_LSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_HAT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PIPE_OPERATOR:
    return false;
    break;
  }

  assert(false);
  return false;
}

static bool_t token_type_is_infix_operator_huh(const lexer_lexer_for_c_language_token_type_t type) {
  switch (type) {
  default: assert(false); return false; break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BLANK: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_MULTILINES: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_ONELINE_CPP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MONO_LINE: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MULTI_LINES: 
    assert(false);
    // must have been already skipped and processed
    break;
	  
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_ZERO:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC_V2:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_HEX:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_BIN:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VCC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_WITH_EXP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_HEX_WITH_EXP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_EMPTY:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_ESCAPE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_ENDED_BY_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE_ENDED_BY_NEWLINE:
    return false;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACE:
    return false;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ELLIPSIS:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON:
    return false;
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BANG_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_TILDE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_MINUS_OPERARTOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COLON_OPERATOR:
    return false;
    break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_POINT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ARROW_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RDIV_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PIPE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PIPE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_EQUAL_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HAT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PERCENT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIFFERENT_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OR_EQUAL_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OR_EQUAL_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_LSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_STAR_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RDIV_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERCENT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_MINUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_LSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_HAT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PIPE_OPERATOR:
    return true;
    break;
  }

  assert(false);
  return false;
}

static int priority_as_infix_operator(const lexer_lexer_for_c_language_token_type_t type) {
#if 0
#define MM 0 #undef MM #define MM 1+MM
  {int a = MM;}
  {int a = MM;}
  {int a = MM;}
  {int a = MM;
    printf("a = %d\n", a);}
#endif

  switch (type) {
  default: assert(false); return false; break;
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BLANK: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_MULTILINES: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_ONELINE_CPP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MONO_LINE: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MULTI_LINES: 
    assert(false);
    // must have been already skipped and processed
    break;
	  
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT: 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_ZERO:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC_V2:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_HEX:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_BIN:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VCC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VC:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_WITH_EXP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_HEX_WITH_EXP:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_EMPTY:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_ESCAPE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_ENDED_BY_NEWLINE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE_ENDED_BY_NEWLINE:
    assert(false);
    // not operators
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACKET:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACE:
    assert(false);
    // not operators
    break;
    
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ELLIPSIS:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON:
    assert(false);
    // not operators
    break;
    

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA: 
    return 1; 
    break;
 
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_STAR_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RDIV_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERCENT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_MINUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_LSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERLUETE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_HAT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PIPE_OPERATOR:
    return 2;
    break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COLON_OPERATOR:
    assert(false); // ? infix ternary operator…?
    return 3;
    break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PIPE_OPERATOR:
    return 4;
    break;
   
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PERLUETE_OPERATOR:
    return 5;
    break;
   
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PIPE_OPERATOR:
    return 6;
    break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HAT_OPERATOR:
    return 7;
    break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PERLUETE_OPERATOR:
    return 8;
    break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_EQUAL_HUH_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIFFERENT_HUH_OPERATOR:
    return 9;
    break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OR_EQUAL_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OR_EQUAL_OPERATOR:
    return 10;
    break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_LSHIFT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RSHIFT_OPERATOR:
    return 11;
    break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_OPERATOR:
    return 12;
    break;

  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RDIV_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PERCENT_OPERATOR:
    return 13;
    break;
   
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_POINT_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ARROW_OPERATOR:
    return 14;
    break;
   
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_TILDE_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BANG_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_PLUS_OPERATOR:
  case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_MINUS_OPERARTOR:
    assert(false);
    break;
  }

  assert(false);
  return false;
}



expression_tree_t * build_the_expression_tree(const lexer_lexer_for_c_language_token_liste_t * tokens) {
  if (tokens == NULL) return NULL;

  tokens = skip_blanks_and_process_directives_tokens(tokens);
  if (tokens == NULL) return NULL;
  
  enum { SIZE_OF_STACK_OF_TREES = 128 };
  enum { SIZE_OF_STACK_OF_OPERATORS = 128 };
  enum { SIZE_OF_STACK_OF_STATES = 128 };
  expression_tree_t * stack_of_trees[SIZE_OF_STACK_OF_TREES];
  const lexer_lexer_for_c_language_token_t * stack_of_operators[SIZE_OF_STACK_OF_OPERATORS];
  int stack_of_states[SIZE_OF_STACK_OF_STATES];
  bzero(stack_of_trees, SIZE_OF_STACK_OF_TREES * sizeof(expression_tree_t * ));
  bzero(stack_of_operators, SIZE_OF_STACK_OF_OPERATORS * sizeof(const lexer_lexer_for_c_language_token_t *));
  bzero(stack_of_states, SIZE_OF_STACK_OF_STATES * sizeof(const int));
  int stack_of_trees_nb = 0;
  int stack_of_operators_nb = 0;
  int stack_of_states_nb = 0;
#define PUSH_TREE(ttt) { assert(stack_of_trees_nb < SIZE_OF_STACK_OF_TREES); stack_of_trees[stack_of_trees_nb] = (ttt); stack_of_trees_nb++; }
#define PUSH_OPERATOR(ttt) { assert(stack_of_operators_nb < SIZE_OF_STACK_OF_OPERATORS); stack_of_operators[stack_of_operators_nb] = (ttt); stack_of_operators_nb++; }
#define PUSH_STATE(ttt) { assert(stack_of_states_nb < SIZE_OF_STACK_OF_STATES); stack_of_states[stack_of_states_nb] = (ttt); stack_of_states_nb++; }
#define POP_TREE ((assert(stack_of_trees_nb > 0)), stack_of_trees_nb--, stack_of_trees[stack_of_trees_nb])
#define POP_OPERATOR ((assert(stack_of_operators_nb > 0)), stack_of_operators_nb--, stack_of_operators[stack_of_operators_nb])
#define REDUCE(n) ((assert(stack_of_states_nb > (n))), stack_of_states_nb -= (n+1), stack_of_states[stack_of_states_nb])
#define TOP_TREE ((assert(stack_of_trees_nb > 0)), stack_of_trees[stack_of_trees_nb-1])
#define TOP_OPERATOR ((assert(stack_of_operators_nb > 0)), stack_of_operators[stack_of_operators_nb-1])

  enum automaton_state_t { 
    AUTOMATON_STATE_NULL,
    AUTOMATON_STATE_FINAL,
    AUTOMATON_STATE_INITIAL,
    AUTOMATON_STATE_HAVE_READ_A_PREFIX_OPERATOR,
    AUTOMATON_STATE_HAVE_READ_A_VALUE_AVAILABLE_FOR_A_POSTFIX_OR_INFIX_OPERATOR,
    AUTOMATON_STATE_HAVE_READ_AN_INFIX_OPERATOR,
    AUTOMATON_STATE_HAVE_READ_AN_INFIX_OPERATOR_AND_TWO_VALUES,
    AUTOMATON_STATE_FUNCALL,
  };
  enum automaton_state_t state_current = AUTOMATON_STATE_INITIAL;
  enum automaton_state_t state_next = AUTOMATON_STATE_NULL;

  bool_t automaton_locked_huh = false;
  bool_t automaton_in_final_state_huh = false;
  bool_t first_loop_in_the_automaton = true;
  int funcall_nb = 0;

  // We do not implement a «push back» of trees in the reading stream.
  // Formelly, we should. (Can there be more than one push back? [I do not think so with non-contextual grammars.] More than one type of tree?)
  // So, we use the fact that there can be only one tree push and only one type (a value).
  bool_t Was_a_tree_pushed_back_in_the_instream_huh = false; // Only true when we just reduced? I think so.
  bool_t We_did_read_a_pushed_back_tree_in_the_instream_so_do_not_move_forward_in_the_instream = false;
  // There is no reading when we reduce.
  // There is a reading of the pushed back tree after the reduction.
  
  // First, we must begin with a value or a '(', or a prefix operators (++, --, sizeof, &, *, +, - , ~, !).
  do {
#if 0
    if (not(We_did_read_a_pushed_back_tree_in_the_instream_so_do_not_move_forward_in_the_instream)) {
      if (tokens != NULL) {
	if (not(Was_a_tree_pushed_back_in_the_instream_huh)) {
	  if (not(first_loop_in_the_automaton)) {
	    tokens = tokens -> cdr;
	  }
	  tokens = skip_blanks_and_process_directives_tokens(tokens);
	  //assert(tokens != NULL);
	}
      }
    }
    else {
      we_did_read_a_pushed_back_tree_in_the_instream_so_do_not_move_forward_in_the_instream = false;
    }

    if (first_loop_in_the_automaton) {
      first_loop_in_the_automaton = false;
    }
    
#endif
    
    
    PUSH_STATE(state_current);
#if 0
    if (Was_a_tree_pushed_back_in_the_instream_huh) {
      printf("state: %d  -- token: %s <%s>\n", state_current, "pushed back tree", TOP_TREE -> type);
    }
    else {
      printf("state: %d  -- token: %s\n", state_current, (tokens == NULL) ? "null" : tokens->car->value);
    }
#endif

    
    switch (state_current) {
    default: assert(false); break;
    case AUTOMATON_STATE_NULL: assert(false); break;
      
    case AUTOMATON_STATE_FINAL: {
      if (Was_a_tree_pushed_back_in_the_instream_huh) {
	assert(false);
      }
  
      automaton_in_final_state_huh = true;
    } break;
      
    case AUTOMATON_STATE_INITIAL: {
      if (Was_a_tree_pushed_back_in_the_instream_huh) {
	state_next = AUTOMATON_STATE_HAVE_READ_A_VALUE_AVAILABLE_FOR_A_POSTFIX_OR_INFIX_OPERATOR;
	Was_a_tree_pushed_back_in_the_instream_huh = false;
	We_did_read_a_pushed_back_tree_in_the_instream_so_do_not_move_forward_in_the_instream = true;
	break;
      }
      
      assert(tokens != NULL);
      
      if (token_type_is_constant_or_ident_or_string_literal_huh(tokens -> car -> type)) {
	expression_tree_t * tree;
	tree = expression_tree_make_on_the_heap(EXPRESSION_TREE_TYPE_LEAF, tokens -> car, NULL, NULL, 0, NULL, NULL, NULL); 
	PUSH_TREE(tree);
	tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr);
#if 0
	{ int b = (1, 2, 3); }
	{ int n = 1; ((assert(stack_of_states_nb > (n))), stack_of_states_nb -= (n), stack_of_states[stack_of_states_nb-1]); }
#endif
	state_next = REDUCE(0); // Because we did not shifted to the state "S -> c."
	Was_a_tree_pushed_back_in_the_instream_huh = true;
	break;
      }
      
      if (token_type_is_prefix_operator_huh(tokens -> car -> type)) {
	PUSH_OPERATOR(tokens -> car);
	tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr);
	state_next = AUTOMATON_STATE_HAVE_READ_A_PREFIX_OPERATOR;
	break;
      }
      
      if (tokens -> car -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR) {
	PUSH_OPERATOR(tokens -> car);
	tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr);
	state_next = AUTOMATON_STATE_INITIAL;
	break;
      }

      assert(false);
    } break;


    case AUTOMATON_STATE_HAVE_READ_A_VALUE_AVAILABLE_FOR_A_POSTFIX_OR_INFIX_OPERATOR: {
      if (Was_a_tree_pushed_back_in_the_instream_huh) {
	assert(false); // I do not know what to do with two successive values
      }

      if (tokens == NULL) {
	state_next = AUTOMATON_STATE_FINAL;
	break;
      }

      if (token_type_is_constant_or_ident_or_string_literal_huh(tokens -> car -> type)) {
	assert(false); // I do not know what to do with two successive values
      }
      
      if (tokens -> car -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR) {
	// It is a function call.
	PUSH_OPERATOR(tokens -> car);
	tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr);
	state_next = AUTOMATON_STATE_FUNCALL;
	break;
      }

      if (tokens -> car -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON) {
	tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr);
	assert(tokens == NULL);
	state_next = AUTOMATON_STATE_FINAL;
	break;
      }
      
      if (tokens -> car -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR) {
	assert(TOP_OPERATOR -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR);
	expression_tree_t * tree_child;
	tree_child = POP_TREE;
	const lexer_lexer_for_c_language_token_t * token_open_par;
	token_open_par = POP_OPERATOR;
	expression_tree_t * tree_node;
	tree_node = expression_tree_make_on_the_heap(EXPRESSION_TREE_TYPE_PAREN, token_open_par, tokens -> car, NULL, 1, tree_child, NULL, NULL); 
	PUSH_TREE(tree_node);
	tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr);
#if 0
	// Should be a REDUCE(3) and then a shit in reading "S".
	// As we do not have implemented the "reading S" operation, we reduce of 2 and then shift into the right state.
	(void) REDUCE(2);
	state_next = AUTOMATON_STATE_HAVE_READ_A_VALUE_AVAILABLE_FOR_A_POSTFIX_OR_INFIX_OPERATOR;
#else
	state_next = REDUCE(2); // We are reducing of 2 instead of 3 because we did not shifted after reading ')'.
	Was_a_tree_pushed_back_in_the_instream_huh = true;
#endif
	break;
      }

      if (token_type_is_postfix_operator_huh(tokens -> car -> type)) {
	expression_tree_t * tree_child;
	tree_child = POP_TREE;
	expression_tree_t * tree_node;
	tree_node = expression_tree_make_on_the_heap(EXPRESSION_TREE_TYPE_PAREN, tokens -> car, NULL, NULL, 1, tree_child, NULL, NULL); 
	PUSH_TREE(tree_node);
	tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr);
#if 0
	// Should be a REDUCE(2) and then a shit in reading "S".
	// As we do not have implemented the "reading S" operation, we reduce of 1 and then shift into the right state.
	(void) REDUCE(1);
	state_next = AUTOMATON_STATE_HAVE_READ_A_VALUE_AVAILABLE_FOR_A_POSTFIX_OR_INFIX_OPERATOR;
#else
	state_next = REDUCE(2);
	Was_a_tree_pushed_back_in_the_instream_huh = true;
#endif
	break;
      }
      
      if (token_type_is_infix_operator_huh(tokens -> car -> type)) {
	PUSH_OPERATOR(tokens -> car);
	tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr);
	state_next = AUTOMATON_STATE_HAVE_READ_AN_INFIX_OPERATOR;
	break;
      }
      
      assert(false);
    } break;


    case AUTOMATON_STATE_HAVE_READ_AN_INFIX_OPERATOR: {
      if (Was_a_tree_pushed_back_in_the_instream_huh) {
	// Ok, we would to reduce now and have a nice tree.
	// Unfortunately, the next operator (infix or postfix) might have priority, 
	// so we shift.
	state_next = AUTOMATON_STATE_HAVE_READ_AN_INFIX_OPERATOR_AND_TWO_VALUES;
	Was_a_tree_pushed_back_in_the_instream_huh = false;
	We_did_read_a_pushed_back_tree_in_the_instream_so_do_not_move_forward_in_the_instream = true;
	break;
      }
      
      assert(tokens != NULL);

      if (token_type_is_constant_or_ident_or_string_literal_huh(tokens -> car -> type)) {
	expression_tree_t * tree;
	tree = expression_tree_make_on_the_heap(EXPRESSION_TREE_TYPE_LEAF, tokens -> car, NULL, NULL, 0, NULL, NULL, NULL); 
	PUSH_TREE(tree);
	tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr);
	state_next = REDUCE(0); // Because we did not shifted to the state "S -> c."
	Was_a_tree_pushed_back_in_the_instream_huh = true;
	break;
      }
      
      if (tokens -> car -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR) {
	PUSH_OPERATOR(tokens -> car);
	tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr);
	state_next = AUTOMATON_STATE_INITIAL;
	break;
      }
      
      if (token_type_is_prefix_operator_huh(tokens -> car -> type)) {
	PUSH_OPERATOR(tokens -> car);
	tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr);
	state_next = AUTOMATON_STATE_HAVE_READ_A_PREFIX_OPERATOR;
	break;
      }
      
      assert(false);
    } break;


    case AUTOMATON_STATE_HAVE_READ_AN_INFIX_OPERATOR_AND_TWO_VALUES: {
      if (Was_a_tree_pushed_back_in_the_instream_huh) {
	assert(false); // I do not know what to do with two successive values
      }
      
      if (tokens != NULL && token_type_is_constant_or_ident_or_string_literal_huh(tokens -> car -> type)) {
	assert(false); // I do not know what to do with two successive values
      }
      
      if (tokens != NULL && tokens -> car -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR) {
	assert(false);
	// TODO: it is a function call
	break;
      }
      
      if (tokens == NULL || tokens -> car -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR) {
	// Alright! We reduce now!
	expression_tree_t * tree_child1;
	expression_tree_t * tree_child2;
	tree_child2 = POP_TREE;
	tree_child1 = POP_TREE;
	const lexer_lexer_for_c_language_token_t * token_operator;
	token_operator = POP_OPERATOR;
	expression_tree_t * tree_node;
	tree_node = expression_tree_make_on_the_heap(EXPRESSION_TREE_TYPE_INFIX_OPERATOR, token_operator, NULL, NULL, 2, tree_child1, tree_child2, NULL); 
	PUSH_TREE(tree_node);
	// tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr); // Nope! Because we did not read the input.
	state_next = REDUCE(3);
	Was_a_tree_pushed_back_in_the_instream_huh = true;
	break;
      }

      assert(tokens != NULL);

      if (token_type_is_postfix_operator_huh(tokens -> car -> type)) {
	expression_tree_t * tree_child;
	tree_child = POP_TREE;
	expression_tree_t * tree_node;
	tree_node = expression_tree_make_on_the_heap(EXPRESSION_TREE_TYPE_POSTFIX_OPERATOR, tokens -> car, NULL, NULL, 1, tree_child, NULL, NULL); 
	PUSH_TREE(tree_node);
	tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr);
	state_next = REDUCE(2);
	Was_a_tree_pushed_back_in_the_instream_huh = true;
	break;
      }
      
      if (token_type_is_infix_operator_huh(tokens -> car -> type)) {
	// Now is the trick.
	// If this operator has a higher priority, then we shift.
	// Otherwise, we reduce.
	const int p1 = priority_as_infix_operator(TOP_OPERATOR -> type);
	const int p2 = priority_as_infix_operator(tokens -> car -> type);
	if (p1 >= p2) { // We reduce!
	  expression_tree_t * tree_child1;
	  expression_tree_t * tree_child2;
	  tree_child2 = POP_TREE;
	  tree_child1 = POP_TREE;
	  const lexer_lexer_for_c_language_token_t * token_operator;
	  token_operator = POP_OPERATOR;
	  expression_tree_t * tree_node;
	  tree_node = expression_tree_make_on_the_heap(EXPRESSION_TREE_TYPE_INFIX_OPERATOR, token_operator, NULL, NULL, 2, tree_child1, tree_child2, NULL); 
	  PUSH_TREE(tree_node);
	  //tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr); // Nope, because we did not read the instream, but only the stack -- this the look-ahead mecanism.
	  state_next = REDUCE(3);
	  Was_a_tree_pushed_back_in_the_instream_huh = true;
	  break;
	}
	else { // We shift!
	  PUSH_OPERATOR(tokens -> car);
	  tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr);
	  state_next = AUTOMATON_STATE_HAVE_READ_AN_INFIX_OPERATOR;
	  break;
	}
	break;
      }
      
      assert(false);
    } break;


    case AUTOMATON_STATE_HAVE_READ_A_PREFIX_OPERATOR: {
      if (Was_a_tree_pushed_back_in_the_instream_huh) {
	expression_tree_t * tree;
	tree = POP_TREE;
	const lexer_lexer_for_c_language_token_t * token;
	token = POP_OPERATOR;
	expression_tree_t * tree_node;
	tree_node = expression_tree_make_on_the_heap(EXPRESSION_TREE_TYPE_PREFIX_OPERATOR, token, NULL, NULL, 1, tree, NULL, NULL); 
	PUSH_TREE(tree_node);
	tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr);
	state_next = REDUCE(2);
	Was_a_tree_pushed_back_in_the_instream_huh = true;
	break;
      }
      
      assert(tokens != NULL);

      if (token_type_is_constant_or_ident_or_string_literal_huh(tokens -> car -> type)) {
	expression_tree_t * tree;
	tree = expression_tree_make_on_the_heap(EXPRESSION_TREE_TYPE_LEAF, tokens -> car, NULL, NULL, 0, NULL, NULL, NULL); 
	const lexer_lexer_for_c_language_token_t * token;
	token = POP_OPERATOR;
	expression_tree_t * tree_node;
	tree_node = expression_tree_make_on_the_heap(EXPRESSION_TREE_TYPE_PREFIX_OPERATOR, token, NULL, NULL, 1, tree, NULL, NULL); 
	PUSH_TREE(tree_node);
	tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr);
	state_next = REDUCE(2);
	Was_a_tree_pushed_back_in_the_instream_huh = true;
	break;
      }
      
      if (token_type_is_prefix_operator_huh(tokens -> car -> type)) {
	PUSH_OPERATOR(tokens -> car);
	tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr);
	state_next = AUTOMATON_STATE_HAVE_READ_A_PREFIX_OPERATOR;
	break;
      }
      
      assert(false);
    } break;

    case AUTOMATON_STATE_FUNCALL: {
      if (Was_a_tree_pushed_back_in_the_instream_huh) {
	// Ok. We reduce if and only if the pushed back tree is a "(…)", 
	// otherwise we shift.
	if (TOP_TREE -> type == EXPRESSION_TREE_TYPE_PAREN) {
	  expression_tree_t * tree_child1;
	  expression_tree_t * tree_child2;
	  tree_child2 = POP_TREE;
	  tree_child1 = POP_TREE;
	  expression_tree_t * tree_node;
	  tree_node = expression_tree_make_on_the_heap(EXPRESSION_TREE_TYPE_FUNCALL, NULL, NULL, NULL, 2, tree_child1, tree_child2, NULL); 
	  PUSH_TREE(tree_node);
	  // tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr); // Nope! Because we did not read the input.
	  state_next = REDUCE(2);
	  Was_a_tree_pushed_back_in_the_instream_huh = true;
	  We_did_read_a_pushed_back_tree_in_the_instream_so_do_not_move_forward_in_the_instream = true;
	  break;
	}
	else {
	  state_next = AUTOMATON_STATE_HAVE_READ_A_VALUE_AVAILABLE_FOR_A_POSTFIX_OR_INFIX_OPERATOR;
	  Was_a_tree_pushed_back_in_the_instream_huh = false;
	  We_did_read_a_pushed_back_tree_in_the_instream_so_do_not_move_forward_in_the_instream = true;
	  break;
	}
      }

      state_next = AUTOMATON_STATE_INITIAL;
      break;
      
#if 1
      assert(tokens != NULL);
      
      if (token_type_is_constant_or_ident_or_string_literal_huh(tokens -> car -> type)) {
	expression_tree_t * tree;
	tree = expression_tree_make_on_the_heap(EXPRESSION_TREE_TYPE_LEAF, tokens -> car, NULL, NULL, 0, NULL, NULL, NULL); 
	PUSH_TREE(tree);
	tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr);
	state_next = REDUCE(0); // Because we did not shifted to the state "S -> c."
	Was_a_tree_pushed_back_in_the_instream_huh = true;
	break;
      }

      if (token_type_is_prefix_operator_huh(tokens -> car -> type)) {
	PUSH_OPERATOR(tokens -> car);
	tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr);
	state_next = AUTOMATON_STATE_HAVE_READ_A_PREFIX_OPERATOR;
	break;
      }
      
      if (tokens -> car -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR) {
	PUSH_OPERATOR(tokens -> car);
	tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr);
	state_next = AUTOMATON_STATE_INITIAL;
	break;
      }

      if (tokens -> car -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR) {
	// Alright, we are in the case "f()", so we reduce.
	const lexer_lexer_for_c_language_token_t * token_open_par = POP_OPERATOR;
	const lexer_lexer_for_c_language_token_t * token_close_par = tokens -> car;
	expression_tree_t * tree_child1;
	expression_tree_t * tree_child2;
	tree_child1 = POP_TREE;
	tree_child2 = expression_tree_make_on_the_heap(EXPRESSION_TREE_TYPE_NIL, token_open_par, token_close_par, NULL, 0, NULL, NULL, NULL); 
	expression_tree_t * funcall_tree;
	funcall_tree = expression_tree_make_on_the_heap(EXPRESSION_TREE_TYPE_FUNCALL, NULL, NULL, NULL, 2, tree_child1, tree_child2, NULL); 
	PUSH_TREE(funcall_tree);
	tokens = skip_blanks_and_process_directives_tokens(tokens -> cdr); // Yes, because we did read the instream (the ')').
	state_next = REDUCE(2);
	Was_a_tree_pushed_back_in_the_instream_huh = true;
	We_did_read_a_pushed_back_tree_in_the_instream_so_do_not_move_forward_in_the_instream = false;
	break;
      }
#endif
#if 0
      ();
#endif

      assert(false);
    } break;


    } // end of switch
    
    state_current = state_next;
  } while (not(automaton_locked_huh) && not(automaton_in_final_state_huh));

  
  
  assert(1 == stack_of_trees_nb);
  assert(0 == stack_of_operators_nb);
  assert(3 == stack_of_states_nb);
  
  return stack_of_trees[0];
}






#if 0
static int i = 3;
extern int i;
#endif

#if 0
extern int sb[*];
extern int sbb[];
extern int fff(int sb[*], int a);
extern int fffkk(int sb[], int a);
#endif

#if 0
static void fff(void) {
  goto lbl;
  int tab[3] = { 1, 2, 3};
 lbl:
  printf("%d\n", tab[1]);
}

  {
    goto lbl;
    int tab[3] = { 1, 2, 3};
  lbl:
    printf("%d\n", tab[1]);
    //    #line 1
    //#line (__LINE__+1)
    //#line __LINE__
    //  goto contin;
    do {
      printf("%d\n", tab[1]);
    } while (false);
  }
#endif

static void analyze_to_fill_the_global_symbol_table(const lexer_lexer_for_c_language_token_liste_t * tokens) {

  // Pour l'instant, nous oublions les directives.
  // On suppose que tout a été préprocessé correctement.

  // Two steps:
  //  1. Grouping of tokens in top-level braces, in top-level brackets, and in top-level parenthesis.
  //  2. Analyze to fill the table.

  // *** Traitement des «{…}» top-level.
  const int tokens_nb = lexer_lexer_for_c_language_token_liste_longueur(tokens);
  token_tree_t tree_null[tokens_nb];
  token_tree_t tree_initial[tokens_nb];
  token_tree_t tree_after_top_level_braces_and_brackets_and_parenthesis_processing[tokens_nb];
  for (int i = 0; i < tokens_nb; i++) {
    tree_null[i].type = TOKEN_TREE_TYPE_NULL;
    tree_null[i].token = NULL;
    tree_null[i].tokens = NULL;
  }
  for (int i = 0; i < tokens_nb; i++) {
    tree_initial[i] = tree_null[i];
    tree_after_top_level_braces_and_brackets_and_parenthesis_processing[i] = tree_null[i];
  }
  
  {
    const lexer_lexer_for_c_language_token_liste_t * p;
    int i;
    for (i = 0, p = tokens; i < tokens_nb; i++, p = p-> cdr) {
      assert(p != NULL);
      tree_initial[i].type = TOKEN_TREE_TYPE_LEAF;
      tree_initial[i].token = p -> car;
      tree_initial[i].tokens = NULL;
    }
    assert(p == NULL);
  }

  
  

  

  // top-level braces and top-level brackets and top-level parenthesis
  // «int fun(int tab[])»
  do {

    {
      // tree_after_top_level_braces_and_brackets_and_parenthesis_processing
      int index_in_tree_initial = 0;
      int index_in_tree_after_bracketing_and_parenthezing = 0;
      for (; index_in_tree_initial < tokens_nb; index_in_tree_initial++, index_in_tree_after_bracketing_and_parenthezing++) {
	if (tree_initial[index_in_tree_initial].type != TOKEN_TREE_TYPE_LEAF) {
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing] = tree_initial[index_in_tree_initial];
	  continue;
	}
	
	if (tree_initial[index_in_tree_initial].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE) {
	  if (tree_initial[index_in_tree_initial].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET) {
	    if (tree_initial[index_in_tree_initial].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR) {
	    tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing] = tree_initial[index_in_tree_initial];
	    continue;
	    }
	  }
	}
	
	if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE) {
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type = TOKEN_TREE_TYPE_NODE_TOP_BRACE;
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_vide();
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_cons(tree_initial[index_in_tree_initial].token, tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens);
	  int stack_count = 1;
	  while (stack_count != 0) {
	    index_in_tree_initial++;
	    assert(index_in_tree_initial < tokens_nb);
	    tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_cons(tree_initial[index_in_tree_initial].token, tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens);
	    if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE) stack_count++;
	    if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACE) stack_count--;
	  }
	  lexer_lexer_for_c_language_token_liste_reverse_surplace(&(tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens));
	  continue;
	}
      

	if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET) {
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type = TOKEN_TREE_TYPE_NODE_TOP_BRACKET;
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_vide();
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_cons(tree_initial[index_in_tree_initial].token, tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens);
	  int stack_count = 1;
	  while (stack_count != 0) {
	    index_in_tree_initial++;
	    assert(index_in_tree_initial < tokens_nb);
	    tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_cons(tree_initial[index_in_tree_initial].token, tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens);
	    if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET) stack_count++;
	    if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACKET) stack_count--;
	  }
	  lexer_lexer_for_c_language_token_liste_reverse_surplace(&(tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens));
	  continue;
	}
      


	if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR) {
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type = TOKEN_TREE_TYPE_NODE_TOP_PAREN;
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_vide();
	  tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_cons(tree_initial[index_in_tree_initial].token, tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens);
	  int stack_count = 1;
	  while (stack_count != 0) {
	    index_in_tree_initial++;
	    assert(index_in_tree_initial < tokens_nb);
	    tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens = lexer_lexer_for_c_language_token_liste_cons(tree_initial[index_in_tree_initial].token, tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens);
	    if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR) stack_count++;
	    if (tree_initial[index_in_tree_initial].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR) stack_count--;
	  }
	  lexer_lexer_for_c_language_token_liste_reverse_surplace(&(tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens));
	  continue;
	}

	assert(false);
      }

      
#if 0
    // printing
    for (int index_in_tree_after_bracketing_and_parenthezing = 0; tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type != TOKEN_TREE_TYPE_NULL; index_in_tree_after_bracketing_and_parenthezing++) {
      printf("[%3d] ", index_in_tree_after_bracketing_and_parenthezing);

      if (tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type == TOKEN_TREE_TYPE_LEAF) {
	printf("LEAF: '%s'\n", tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].token -> value);
	continue;
      }
      
      if (tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type == TOKEN_TREE_TYPE_NODE_TOP_BRACE) {
	printf("NODE TOP BRACE: ");
	for (const lexer_lexer_for_c_language_token_liste_t * p = tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens; p != NULL; p = p-> cdr)
	  printf("%s", p -> car -> value);
	printf("\n");
	continue;
      }

      if (tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type == TOKEN_TREE_TYPE_NODE_TOP_BRACKET) {
	printf("NODE TOP BRACKET: ");
	for (const lexer_lexer_for_c_language_token_liste_t * p = tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens; p != NULL; p = p-> cdr)
	  printf("%s", p -> car -> value);
	printf("\n");
	continue;
      }

      if (tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].type == TOKEN_TREE_TYPE_NODE_TOP_PAREN) {
	printf("NODE TOP PAREN: ");
	for (const lexer_lexer_for_c_language_token_liste_t * p = tree_after_top_level_braces_and_brackets_and_parenthesis_processing[index_in_tree_after_bracketing_and_parenthezing].tokens; p != NULL; p = p-> cdr)
	  printf("%s", p -> car -> value);
	printf("\n");
	continue;
      }

      puts("ERROR\n");
      assert(false);
    }
#endif
    }
  } while (false);
  // fin des brackets top-level
  







  token_tree_t tree[tokens_nb];
  for (int i = 0; i < tokens_nb; i++) {
    tree[i] = tree_after_top_level_braces_and_brackets_and_parenthesis_processing[i];
  }
  
  

  // *** maintenant on passe à l'analyse du top-level
  // Il s'agit véritablement d'un automate.
  // First: le class storage
  // Second: inline
  // Third: constness
  // Fourth: signedness («signed short int»)
  // Fifth: sizeness («signed short int»)
  // Sixth: core-type
  // Seventh: structured-type with the name <this one is the complicated one>
  // Eighth: a ; or a {…}
  //
  // NB: typedef is different in the meaning but is similar to a storage class in the syntax.
  // 
  // 
  {
  int i;
  i = 0;
  do {
    
    const char * storage_class = STORAGE_CLASS_SPECIFIER_NULL;
    const char * inline_class = INLINE_CLASS_SPECIFIER_NULL;
    const char * const_class = CONST_CLASS_SPECIFIER_NULL;
    const char * signed_class = SIGNED_CLASS_SPECIFIER_NULL;
    const char * size_class = SIZE_CLASS_SPECIFIER_NULL;
    const char * core_type = CORE_TYPE_SPECIFIER_NULL;
    int indirections_nb = 0;
    bool_t array_huh = false;
    const char * array_size_code = NULL;
    // TODO macros defined before the code of array_size_code
    bool_t fun_param_huh = false;
    const char * fun_param_code = NULL;
    // TODO macros defined before the code of fun_param_code
    bool_t fun_def_huh = false;
    const char * fun_def_code = NULL;
    
    
    // zeroth state: are we at the end of the file?
    i = skip_blanks_and_process_directives(i, tokens_nb, &tree);
    assert(i < tokens_nb);
    if (tree[i].type == TOKEN_TREE_TYPE_NULL) break;
    
    // first state of the automaton: the storage class
    do {
      i = skip_blanks_and_process_directives(i, tokens_nb, &tree);
      assert(i < tokens_nb);
      if (tree[i].type != TOKEN_TREE_TYPE_LEAF) break;
      if (tree[i].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT) break;
      if (0 == strcmp(tree[i].token -> value, "extern")) { storage_class = STORAGE_CLASS_SPECIFIER_EXTERN; i++; }
      if (0 == strcmp(tree[i].token -> value, "static")) { storage_class = STORAGE_CLASS_SPECIFIER_STATIC; i++; }
      if (0 == strcmp(tree[i].token -> value, "typedef")) { storage_class = STORAGE_CLASS_SPECIFIER_TYPEDEF; i++; }
    } while (false);
    
    // second state of the automaton: the inline keyword
    do {
      i = skip_blanks_and_process_directives(i, tokens_nb, &tree);
      assert(i < tokens_nb);
      if (tree[i].type != TOKEN_TREE_TYPE_LEAF) break;
      if (tree[i].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT) break;
      if (0 == strcmp(tree[i].token -> value, "inline")) { inline_class = INLINE_CLASS_SPECIFIER_INLINE; i++; }
    } while (false);
    
    // third state of the automaton: the const keyword
    do {
      i = skip_blanks_and_process_directives(i, tokens_nb, &tree);
      assert(i < tokens_nb);
      if (tree[i].type != TOKEN_TREE_TYPE_LEAF) break;
      if (tree[i].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT) break;
      if (0 == strcmp(tree[i].token -> value, "const")) { const_class = CONST_CLASS_SPECIFIER_CONST; i++; }
    } while (false);
    
    // fourth state: signedness
    do {
      i = skip_blanks_and_process_directives(i, tokens_nb, &tree);
      assert(i < tokens_nb);
      if (tree[i].type != TOKEN_TREE_TYPE_LEAF) break;
      if (tree[i].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT) break;
      if (0 == strcmp(tree[i].token -> value, "signed")) { signed_class = SIGNED_CLASS_SPECIFIER_SIGNED; i++; }
      if (0 == strcmp(tree[i].token -> value, "unsigned")) { signed_class = SIGNED_CLASS_SPECIFIER_UNSIGNED; i++; }
    } while (false);
    
    // fifth state: sizeness
    do {
      i = skip_blanks_and_process_directives(i, tokens_nb, &tree);
      assert(i < tokens_nb);
      if (tree[i].type != TOKEN_TREE_TYPE_LEAF) break;
      if (tree[i].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT) break;
      if (0 == strcmp(tree[i].token -> value, "short")) { size_class = SIZE_CLASS_SPECIFIER_SHORT; i++; }
      if (0 == strcmp(tree[i].token -> value, "long")) { size_class = SIZE_CLASS_SPECIFIER_LONG; i++; }
    } while (false);
    
    // fifth state bis: sizeness double
    do {
      i = skip_blanks_and_process_directives(i, tokens_nb, &tree);
      assert(i < tokens_nb);
      if (tree[i].type != TOKEN_TREE_TYPE_LEAF) break;
      if (tree[i].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT) break;
      if (0 == strcmp(tree[i].token -> value, "short")) { assert(size_class == SIZE_CLASS_SPECIFIER_SHORT); size_class = SIZE_CLASS_SPECIFIER_SHORT_SHORT; i++; }
      if (0 == strcmp(tree[i].token -> value, "long")) { assert(size_class == SIZE_CLASS_SPECIFIER_LONG); size_class = SIZE_CLASS_SPECIFIER_LONG_LONG; i++; }
    } while (false);
    
    // sixth state: core-type
    do {
      i = skip_blanks_and_process_directives(i, tokens_nb, &tree);
      assert(i < tokens_nb);
      if (tree[i].type != TOKEN_TREE_TYPE_LEAF) break;
      if (tree[i].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT) break;
      if (0 == strcmp(tree[i].token -> value, "void")) { core_type = CORE_TYPE_SPECIFIER_VOID; i++; }
      if (0 == strcmp(tree[i].token -> value, "char")) { core_type = CORE_TYPE_SPECIFIER_CHAR; i++; }
      if (0 == strcmp(tree[i].token -> value, "int")) { core_type = CORE_TYPE_SPECIFIER_INT; i++; }
      if (0 == strcmp(tree[i].token -> value, "float")) { core_type = CORE_TYPE_SPECIFIER_FLOAT; i++; }
      if (0 == strcmp(tree[i].token -> value, "double")) { core_type = CORE_TYPE_SPECIFIER_DOUBLE; i++; }
      if (0 == strcmp(tree[i].token -> value, "_Bool")) { core_type = CORE_TYPE_SPECIFIER__BOOL; i++; }
      if (0 == strcmp(tree[i].token -> value, "_Complex")) { core_type = CORE_TYPE_SPECIFIER__COMPLEX; i++; }
      // test if a keyword
      // test
      if (core_type == CORE_TYPE_SPECIFIER_NULL) {
	if (token_is_a_keyword_huh(tree[i].token -> value)) { assert(false); }
	if (signed_class == SIGNED_CLASS_SPECIFIER_NULL && size_class == SIZE_CLASS_SPECIFIER_NULL) {
	  //core_type = CORE_TYPE_SPECIFIER_IDENT;
	  core_type = strcopy(tree[i].token -> value);
	  i++;
	}
      }
    } while (false);
    
    // seventh state: structured type (the complicated part)
    // This is the "declarator" of the C99 grammar.
    // declarator: * * * … puis NAME puis […] or (…)
    // For the moment, we forget the "( declarator )" part.
    // 7.a. Counting the number of *
    i = skip_blanks_and_process_directives(i, tokens_nb, &tree);
    assert(i < tokens_nb);
    for (;;) {
      if (tree[i].type != TOKEN_TREE_TYPE_LEAF) break;
      if (tree[i].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR) break;
      indirections_nb++;
      i++;
      i = skip_blanks_and_process_directives(i, tokens_nb, &tree);
      assert(i < tokens_nb);
    } 
    
    // 7.b. The name of the type
    const char * name_being_declared = NULL;
    do {
      i = skip_blanks_and_process_directives(i, tokens_nb, &tree);
      assert(i < tokens_nb);
      if (tree[i].type != TOKEN_TREE_TYPE_LEAF) break;
      if (tree[i].token -> type != LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT) break;
      name_being_declared = tree[i].token -> value;
      i++;
    } while (false);
    
    // 7.c. Array
    const lexer_lexer_for_c_language_token_liste_t * array_size_code_tokens = NULL;
    do {
      i = skip_blanks_and_process_directives(i, tokens_nb, &tree);
      assert(i < tokens_nb);
      if (tree[i].type == TOKEN_TREE_TYPE_NODE_TOP_BRACKET) {
	array_huh = true;
	array_size_code_tokens = tree[i].tokens;
	array_size_code = lexer_lexer_for_c_language_token_liste_string_flat(tree[i].tokens);
	i++;
      }
    } while (false);
    
    // 7.d. function param
    const lexer_lexer_for_c_language_token_liste_t * fun_param_code_tokens = NULL;
    do {
      i = skip_blanks_and_process_directives(i, tokens_nb, &tree);
      assert(i < tokens_nb);
      if (tree[i].type == TOKEN_TREE_TYPE_NODE_TOP_PAREN) {
	fun_param_huh = true;
	fun_param_code_tokens = tree[i].tokens;
	fun_param_code = lexer_lexer_for_c_language_token_liste_string_flat(tree[i].tokens);
	i++;
      }
    } while (false);
    
    // eighth state: ; or {…}
    const lexer_lexer_for_c_language_token_liste_t * fun_def_code_tokens = NULL;
    do {
      i = skip_blanks_and_process_directives(i, tokens_nb, &tree);
      assert(i < tokens_nb);
      if (tree[i].type == TOKEN_TREE_TYPE_LEAF) {
	assert(tree[i].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON);
	i++;
      }
      else if (tree[i].type == TOKEN_TREE_TYPE_NODE_TOP_BRACE) {
	fun_def_huh = true;
	fun_def_code_tokens = tree[i].tokens;
	fun_def_code = lexer_lexer_for_c_language_token_liste_string_flat(tree[i].tokens);
	i++;
      }
      else {
	assert(false);
      }
    } while (false);
    


    // NOW, il faut pusher ce que nous venons de reconnaître sur la stack des symboles
#if 0
    {
      printf("Nous devons pusher le symbole '%s' dans la table des symboles", name_being_declared);
      printf(" ");
      printf("[");
      if (storage_class != STORAGE_CLASS_SPECIFIER_NULL) printf("storage_class: %s, ", storage_class);
      if (inline_class != INLINE_CLASS_SPECIFIER_NULL) printf("inlinedness: %s, ", inline_class);
      if (const_class != CONST_CLASS_SPECIFIER_NULL) printf("constness: %s, ", const_class);
      if (signed_class != SIGNED_CLASS_SPECIFIER_NULL) printf("signedness: %s, ", signed_class);
      if (size_class != SIZE_CLASS_SPECIFIER_NULL) printf("sizeness: %s, ", size_class);
      if (core_type != CORE_TYPE_SPECIFIER_NULL) printf("core_type: %s, ", core_type);
      if (indirections_nb != 0) printf("indirections_nb: %d, ", indirections_nb);
      if (array_huh) printf("array: %s, ", array_size_code);
      if (fun_param_huh) printf("fun_param: %s, ", fun_param_code);
      if (fun_def_huh) printf("fun_def: %s, ", fun_def_code);
      printf("]");
      printf("\n");
    }
#endif

#if 0
    static void global_symbol_table_push(const char * name, const char * storage_class, const char * inline_class, const char * const_class, const char * signed_class, const char * size_class,   const char * core_type, int indirections_nb, bool_t array_huh, const char * array_size_code, bool_t fun_param_huh, const char * fun_param_code, bool_t fun_def_huh, const char * fun_def_code);
#endif
#if 1
    if (name_being_declared != NULL) {
      global_symbol_table_push(name_being_declared, storage_class, inline_class, const_class, signed_class, size_class, core_type, indirections_nb, array_huh, array_size_code, array_size_code_tokens, fun_param_huh, fun_param_code, fun_param_code_tokens, fun_def_huh, fun_def_code, fun_def_code_tokens);
    }
    else {
      assert(name_being_declared == NULL);
      if (storage_class != STORAGE_CLASS_SPECIFIER_NULL) assert(false);
      if (inline_class != INLINE_CLASS_SPECIFIER_NULL) assert(false);
      if (const_class != CONST_CLASS_SPECIFIER_NULL) assert(false);
      if (signed_class != SIGNED_CLASS_SPECIFIER_NULL) assert(false);
      if (size_class != SIZE_CLASS_SPECIFIER_NULL) assert(false);
      if (core_type != CORE_TYPE_SPECIFIER_NULL) assert(false);
      if (indirections_nb != 0) assert(false);
      if (array_huh) assert(false);
      if (fun_param_huh) assert(false);
      if (fun_def_huh) assert(false);
    }
#endif



    // NEXT!
  } while (i < tokens_nb);
  }  


  return;
}




  

  
static bool programme_boucle_old2(const int argc, const char * argv[]) {
  token_tree_t tree[23];
  
  // *** maintenant on passe à l'analyse du top-level
  // Le top-level est une suite de déclarations et de définitions de fonctions.
  // start: top-list
  // top-list: top top-list | empty
  // top:
  //    function-definition [qui se termine par {}]
  //  | declaration-diverse [qui se termine par ;]
  //
  // function-definition: [storage | core-type | inline] [type tree -- ident -- (param)] {…}
  // 
  // declaration-diverse: [storage | core-type | inline] list-of-[type tree -- ident [= init] [,]] ;
  //
  // «declaration-diverse» contient aussi la déclaration de fonctions, puisque nous avons le droit de «int b(void);».
  // Bref, entre la «function-definition» est un cas particulier de «declaration-diverse» qui se termine par «{…‘}» et non par «;».
  // 
  // Et on va avoir nos premiers typedef, donc on a besoin d'une table des types.
  // Et une table des enums.
  //
  // Donc on commence soit par:
  //   extern static typedef struct union inline 
  //   void char short int long float double signed unsigned _Bool _Complex 
  //   const volatile 
  //   restrict auto register
  //
  // Pour l'instant, on oublie struct/union/enum/typedef.
  do {
    enum storage_class_t { STORAGE_CLASS_SPECIFIER_NULL, STORAGE_CLASS_SPECIFIER_STATIC, STORAGE_CLASS_SPECIFIER_EXTERN};
    enum core_type_t { CORE_TYPE_NULL, CORE_TYPE_IDENT, CORE_TYPE_VOID, CORE_TYPE_INT, CORE_TYPE_CHAR, CORE_TYPE_FLOAT, CORE_TYPE_DOUBLE, CORE_TYPE__BOOL, CORE_TYPE_COMPLEX};
    enum signedness_t { SIGNEDNESS_NULL, SIGNEDNESS_SIGNED, SIGNEDNESS_UNSIGNED};
    enum sizeness_t { SIZENESS_NULL, SIZENESS_SHORT_SHORT, SIZENESS_SHORT, SIZENESS_LONG, SIZENESS_LONG_LONG};
    enum inlinedness_t { INLINEDNESS_NULL, INLINEDNESS_INLINE};
    enum typedefness_t { TYPEDEFNESS_NULL, TYPEDEFNESS_YES};
    
    enum storage_class_t storage_class = STORAGE_CLASS_SPECIFIER_NULL;
    enum core_type_t core_type = CORE_TYPE_NULL;
    enum signedness_t signedness = SIGNEDNESS_NULL;
    enum sizeness_t sizeness = SIZENESS_NULL;
    enum inlinedness_t inlinedness = INLINEDNESS_NULL;
    enum typedefness_t typedefness = TYPEDEFNESS_NULL;
    
    const char * ident_match_key[] = { 
      "extern", "static", "typedef", 
      //"struct", "union", 
      "inline", 
      "void", "char", "int", "float", "double", "_Bool", "_Complex", 
      "short", "long", 
      "signed", "unsigned", 
      //   "const", "volatile", 
      //   "restrict", "auto", "register",
      NULL
    };

    enum ident_class { CLASS_NULL, STORAGE, TYPEDEF, INLINE, CORE_TYPE, SIZE, SIGNED};
    const enum ident_class ident_match_class[] = { 
      STORAGE, STORAGE, TYPEDEF, 
      //"struct", "union", 
      INLINE, 
      CORE_TYPE, CORE_TYPE, CORE_TYPE, CORE_TYPE, CORE_TYPE, CORE_TYPE, CORE_TYPE, 
      SIZE, SIZE, 
      SIGNED, SIGNED, 
      //   "const", "volatile", 
      //   "restrict", "auto", "register",
    };
    
    const int ident_match_value[] = { 
      STORAGE_CLASS_SPECIFIER_EXTERN, STORAGE_CLASS_SPECIFIER_STATIC, TYPEDEFNESS_YES, 
      //"struct", "union", 
      INLINEDNESS_INLINE, 
      CORE_TYPE_VOID, CORE_TYPE_CHAR, CORE_TYPE_INT, CORE_TYPE_FLOAT, CORE_TYPE_DOUBLE, CORE_TYPE__BOOL, CORE_TYPE_COMPLEX,
      SIZENESS_LONG_LONG, SIZENESS_LONG, 
      SIGNEDNESS_SIGNED, SIGNEDNESS_UNSIGNED, 
      //   "const", "volatile", 
      //   "restrict", "auto", "register",
      0
    };
    
    
    int i;
    i = 0;
    for (; tree[i].type != TOKEN_TREE_TYPE_NULL; i++) {
      bool_t break_for_huh = false;
      if (tree[i].type == TOKEN_TREE_TYPE_LEAF) {
	switch (tree[i].token -> type) {
	default: assert(0 != 0); return -1; break;
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BLANK: 
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_MULTILINES: 
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMENT_ONELINE_CPP:
	  continue;
	  break;
	  
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MONO_LINE: 
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIRECTIVE_MULTI_LINES: 
	  assert(false);
	  break;
	  
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT: 
	  fputs(tree[i].token -> value, stderr);
	  fputs(" -- ", stderr);
	  {
	    int j;
	    for (j = 0; ident_match_key[j] != NULL; j++) {
	      if (0 == strcmp(ident_match_key[j], tree[i].token -> value)) break;
	    }
	    //assert(ident_match_key[j] != NULL);
	    if (ident_match_key[j] == NULL) {
	      if (core_type == CORE_TYPE_NULL) { 
		core_type = CORE_TYPE_IDENT; 
		continue;
	      } 
	      else { 
		break_for_huh = true;
		break;
	      }
	    }
	    
	    switch (ident_match_class[j]) {
	    default: assert(false); break;
	    case CLASS_NULL: assert(false); break;
	    case STORAGE: if (storage_class == STORAGE_CLASS_SPECIFIER_NULL) { storage_class = ident_match_value[j]; } else { assert(false); } break;
	    case TYPEDEF: if (typedefness == TYPEDEFNESS_NULL) { typedefness = ident_match_value[j]; } else { assert(false); } break;
	    case INLINE: if (inlinedness == INLINEDNESS_NULL) { inlinedness = ident_match_value[j]; } else { assert(false); } break;
	    case SIZE: if (sizeness == SIZENESS_NULL) { sizeness = ident_match_value[j]; } else { assert(false); } break;
	    case SIGNED: if (signedness == SIGNEDNESS_NULL) { signedness = ident_match_value[j]; } else { assert(false); } break;
	    case CORE_TYPE: if (core_type == CORE_TYPE_NULL) { core_type = ident_match_value[j]; } else { assert(false); } break;
	    }
	  }
	  continue;
	  break;

	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_ZERO:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_DEC_V2:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_HEX:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_BIN:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VCC:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INTEGER_OCT_VC:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_SIMPLE:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_DEC_WITH_EXP:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_REAL_HEX_WITH_EXP:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_SIMPLE_NEWLINE:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_EMPTY:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_ESCAPE:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CHAR_WIDE:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_ENDED_BY_NEWLINE:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STRING_WIDE_ENDED_BY_NEWLINE:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_PAR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACKET:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACE:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_CLOSE_BRACE:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_POINT_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ARROW_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_STAR_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RDIV_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_TILDE_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PERLUETE_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PERLUETE_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SIMPLE_PIPE_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DOUBLE_PIPE_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_EQUAL_HUH_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HAT_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PERCENT_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_BANG_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_DIFFERENT_HUH_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_INF_OR_EQUAL_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SUP_OR_EQUAL_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_PLUS_PLUS_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_MINUS_MINUS_OPERARTOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_LSHIFT_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_RSHIFT_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_HUH_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COLON_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ELLIPSIS:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_STAR_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RDIV_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERCENT_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PLUS_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_MINUS_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_LSHIFT_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_RSHIFT_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PERLUETE_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_HAT_OPERATOR:
	case LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_PIPE_OPERATOR:
	  //assert(false);
	  break;
	}
      }
      else if (tree[i].type == TOKEN_TREE_TYPE_NODE_TOP_BRACE) {
	assert(false);
      }
      else {
	assert(false);
      }
      if (break_for_huh) break;
    }

    // 
    {
      if (storage_class != 0) printf("storage class: yes -- ");
      if (core_type != 0) printf("core type: yes -- ");
      if (signedness != 0) printf("signedness: yes -- ");
      if (sizeness != 0) printf("sizeness: yes -- ");
      if (inlinedness != 0) printf("inlinedness: yes -- ");
      if (typedefness != 0) printf("typedef: yes -- ");
    }
    
    assert(core_type != 0);
    // Now, soit c'est un type construit (pointeur), soit c'est un ident.
    {
      // TODO XXX
    }
    
    assert(tree[i].type == TOKEN_TREE_TYPE_LEAF);
    assert(tree[i].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_IDENT);
    
    const char * name_of_the_var_being_declared;
    name_of_the_var_being_declared = tree[i].token -> value;
    
    i++;
    assert(tree[i].type != TOKEN_TREE_TYPE_NULL);
    // Now, c'est soit […], soit (…), soit =, soit ,, soit;.
    bool_t fun_param_huh = false;
    bool_t fun_def_huh = false;
    bool_t array_huh = false;
    do {
      if (tree[i].type == TOKEN_TREE_TYPE_NODE_TOP_BRACE) {
	assert(false);
      }
      else if (tree[i].type == TOKEN_TREE_TYPE_LEAF) {
	if (tree[i].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON) {
	  // we arrived at the end of the declaration
	  break;
	}
	if (tree[i].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_PAR) {
	  fun_param_huh = true;
	  assert(false); // TODO XXX Il faut tout accumuler jusqu'à la prochaine parenthèse fermante.
	  break;
	}
	if (tree[i].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_OPEN_BRACKET) {
	  array_huh = true;
	  assert(false); // TODO XXX Il faut tout accumuler jusqu'au prochain crochet fermant.
	  break;
	}
	if (tree[i].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_ASSIGN_OPERATOR) {
	  assert(false); // TODO XXX À faire.
	  break;
	}
	if (tree[i].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_COMMA) {
	  assert(false); // TODO XXX À faire.
	  break;
	}
      }
      else {
	assert(false);
      }
    } while (false);

    // Now, on a soit un ;, soit {…}.
    do {
      if (tree[i].type == TOKEN_TREE_TYPE_NODE_TOP_BRACE) {
	fun_def_huh = true;
	assert(false);
      }
      else if (tree[i].type == TOKEN_TREE_TYPE_LEAF) {
	assert(tree[i].token -> type == LEXER_LEXER_FOR_C_LANGUAGE_TOKEN_TYPE_SEMICOLON);
	// we arrived at the end of the declaration
	break;
      }
      else {
	assert(false);
      }
      
    } while (false);

    // NOW, push this new global variable into the symbols' table.
    // TODO XXX

    // Then next
  } while (true);
  
  
  
  return false;
  }




int token_tree_ensure_the_c_code_is_well_braced_or_bracketed(const lexer_lexer_for_c_language_token_type_t opening_type, const lexer_lexer_for_c_language_token_type_t closing_type, const int nb_elt, token_tree_t (* tree_ptr)[]) {
  int stack_count;
  int previous_open_brace;
  
  stack_count = 0;
  previous_open_brace = -1;

  for (int i = 0; i < nb_elt; i++) {
    if ((*tree_ptr)[i].type != TOKEN_TREE_TYPE_LEAF) {
      continue;
    }

    if ((*tree_ptr)[i].token -> type == opening_type) {
      stack_count++;
      previous_open_brace = i;
      continue;
    }
    
    if ((*tree_ptr)[i].token -> type == closing_type) {
      if (stack_count == 0) return i;
      stack_count--;
      continue;
    }
  }

  if (0 == stack_count) return -1;
  return previous_open_brace;
}





const lexer_lexer_for_c_language_token_liste_t * ensure_the_c_code_is_well_braced_list(const lexer_lexer_for_c_language_token_type_t open_type, const lexer_lexer_for_c_language_token_type_t close_type, const lexer_lexer_for_c_language_token_liste_t * l) {
  return ensure_the_c_code_is_well_braced_list_aux(open_type, close_type, l, 0, NULL);
}

const lexer_lexer_for_c_language_token_liste_t * ensure_the_c_code_is_well_braced_list_aux(const lexer_lexer_for_c_language_token_type_t open_type, const lexer_lexer_for_c_language_token_type_t close_type, const lexer_lexer_for_c_language_token_liste_t * l, const int stack_count, const lexer_lexer_for_c_language_token_liste_t * previous_open_brace) {
  if (NULL == l) {
    if (0 == stack_count) {
      return NULL;
    }
    else {
      assert(previous_open_brace != NULL);
      return previous_open_brace;
    }
  }

  assert(l != NULL);

#if 0
  switch (l -> car -> type) {
  case open_type: return ensure_the_c_code_is_well_braced_aux(open_type, close_type, l -> cdr, stack_count+1); break;
  case close_type: 
    if (0 == stack_count) { return l; }
    else { return ensure_the_c_code_is_well_braced_aux(open_type, close_type, l -> cdr, stack_count-1); }
    break;
  default: return ensure_the_c_code_is_well_braced_aux(open_type, close_type, l -> cdr, stack_count); break;
  }
#else
  if (l -> car -> type == open_type) { 
    return ensure_the_c_code_is_well_braced_list_aux(open_type, close_type, l -> cdr, stack_count+1, l); 
  }
  if (l -> car -> type == close_type) { 
    if (0 == stack_count) { return l; }
    else { return ensure_the_c_code_is_well_braced_list_aux(open_type, close_type, l -> cdr, stack_count-1, previous_open_brace); }
  }
  return ensure_the_c_code_is_well_braced_list_aux(open_type, close_type, l -> cdr, stack_count, previous_open_brace); 
#endif

  assert(false);
  return NULL;
}



int token_tree_count_tokens_according_to_type(const lexer_lexer_for_c_language_token_type_t type, const int nb_elt, const token_tree_t * tree) {
  int count = 0;
  for (int i = 0; i < nb_elt; i++) {
    if (tree[i].type != TOKEN_TREE_TYPE_LEAF) continue;
    count += ((tree[i].token -> type == type) ? 1 : 0);
  }
  return count;
}


int lexer_lexer_for_c_language_token_liste_count_according_to_type(const lexer_lexer_for_c_language_token_type_t type, const lexer_lexer_for_c_language_token_liste_t * l) {
  if (NULL == l) return 0;
  
  const int head_count = ((l -> car -> type == type) ? 1 : 0);
  const int tail_count = lexer_lexer_for_c_language_token_liste_count_according_to_type(type, l -> cdr);
  
  return head_count + tail_count;
}





static bool programme_boucle_old(const int argc, const char * argv[]) {
  if (argc != 2) {
    printf("Please, provide exactly one name (the file named 'name'.lexer.type must exist in the current directory).\n");
    printf("For an example, I am writing a file named 'lexer_example.lexer.type'.\n");
    biglib_fichier_ecrire("lexer_example.lexer.type", lexer_example_lexer_type_ct);
    printf("Done. You can read it with the command 'more lexer_example.lexer.type'.\n");
    printf("Then, just type '%s lexer_example' to test me: I will produce a dotty file, a c file, and start a read-eval-print loop.\n", argv[0]);
    return false;
  }
  
  const char * const lexer_name = argv[1];
  const char * const lexer_name_upper = strupper(lexer_name);
  const char * const filename = strconcat(lexer_name, ".lexer.type");
  
  if (not(biglib_fichier_existe_huh(filename))) {
    printf("Sorry, I am unable to find the file named \"%s\".\n", filename);
    return false;
  }
  
  const char * const fichier_contenu = biglib_fichier_lire(filename);
  const str_tableau_t * const lignes = texte_en_ligne(fichier_contenu);
  
  
  // Lecture du fichier
  // Peuplement du nom des tokens et des expr des tokens
  str_t * enum_name[lignes -> nb];
  str_t * expr_reguliere[lignes -> nb];
  for (int i = 0; i < lignes -> nb; i++) {
    const bool b = texte_decouper(lignes -> tab[i], ':', &(enum_name[i]), &(expr_reguliere[i]));
    if (not(b)) {
      enum_name[i] = uint_string(i);
      expr_reguliere[i] = lignes -> tab[i];
    }
  }
  
  bool ligne_vide_huh[lignes -> nb];
  for (int i = 0; i < lignes -> nb; i++) {
    ligne_vide_huh[i] = la_string_ne_contient_que_des_caracteres_blancs_huh(lignes -> tab[i]);
  }
  
  automate_t * automates[lignes -> nb];
  for (int i = 0; i < lignes -> nb; i++) {
    automates[i] = NULL;
  }
  for (int i = 0; i < lignes -> nb; i++) {
    if (ligne_vide_huh[i]) continue;
    
    automates[i] = compiler_une_expression_reguliere_en_automate(expr_reguliere[i]);
  }

  str_t * lexical_analyser_dotty_code;
  lexical_analyser_dotty_code = gen_dotty_code(lignes -> nb, enum_name, expr_reguliere, ligne_vide_huh, automates);
  //printf("%s\n", lexical_analyser_dotty_code);


  char * fichier_dot_name;
  char * fichier_jpg_name;
  fichier_dot_name = strconcat2(lexer_name, ".dot");
  fichier_jpg_name = strconcat2(lexer_name, ".jpg");
  
#if 1
  {
    // generating dot file
    FILE * flux = stderr;
    fprintf(flux, "==> Generating .dot file...\n");
    biglib_fichier_ecrire(fichier_dot_name, lexical_analyser_dotty_code);
    fprintf(flux, "If you have graphviz installed on your system, you can generate a jpeg picture showing the automata of the lexical analyzer with the command 'dot -Tjpg -o ");
    fprintf(flux, "%s", fichier_jpg_name);
    fprintf(flux, " ");
    fprintf(flux, "%s", fichier_dot_name);
    fprintf(flux, "'.\n");
    //printf("\n");
  }
#endif

  char * fichier_c_name;
  char * fichier_h_name;
  fichier_c_name = strconcat2(lexer_name, ".c");
  fichier_h_name = strconcat2(lexer_name, ".h");
  
#if 1
  do {
    // generating c files
    FILE * flux = stderr;
    fprintf(flux, "==> Generating .c & .h files...\n");
    bool_t b;
    str_t * c_code_extern_declarations = NULL;
    str_t * c_code_static_declarations = NULL;
    str_t * c_code_definitions = NULL;
    str_t * c_code_main = NULL;
    b = gen_c_code(lexer_name, lignes -> nb, lignes, enum_name, expr_reguliere, ligne_vide_huh, automates, &c_code_extern_declarations, &c_code_static_declarations, &c_code_definitions, &c_code_main);
    if (not(b)) {
      fprintf(flux, "Something got wrong during the generation of the files...? Sorry, files are not generated.\n");
      break;
    }
    str_t * lexical_analyser_h_code = NULL;
    str_t * lexical_analyser_c_code = NULL;
    str_t * condition_h_name = NULL;
    condition_h_name = strupper(string_replace(fichier_h_name, '.', "_"));
    //lexical_analyser_h_code = strcopy(COPYING_at_start_of_c_files);
    lexical_analyser_h_code = strcopy("");
    stradd2(&lexical_analyser_h_code, "\n");
    stradd4(&lexical_analyser_h_code, "#ifndef ", strupper(condition_h_name), "\n");
    stradd4(&lexical_analyser_h_code, "#define ", strupper(condition_h_name), "\n");
    stradd2(&lexical_analyser_h_code, "\n");
    stradd2(&lexical_analyser_h_code, c_code_extern_declarations);
    stradd2(&lexical_analyser_h_code, "\n");
    stradd4(&lexical_analyser_h_code, "#endif /* ", strupper(condition_h_name), "*/\n");
    stradd2(&lexical_analyser_h_code, "\n");
    //lexical_analyser_c_code = strcopy(COPYING_at_start_of_c_files);
    lexical_analyser_c_code = strcopy("");
    stradd2(&lexical_analyser_c_code, "\n");
    stradd2(&lexical_analyser_c_code, "#define _GNU_SOURCE // pour avoir asprintf sous Debian qui est dans <stdio.h>\n");
    stradd2(&lexical_analyser_c_code, "\n");
    stradd4(&lexical_analyser_c_code, "#include \"", fichier_h_name, "\"\n");
    stradd2(&lexical_analyser_c_code, "\n");
    stradd2(&lexical_analyser_c_code, c_code_static_declarations);
    stradd2(&lexical_analyser_c_code, c_code_definitions);
    stradd2(&lexical_analyser_c_code, c_code_main);
    stradd2(&lexical_analyser_c_code, "\n");
    //printf("%s\n", lexical_analyser_c_code);
    biglib_fichier_ecrire(fichier_h_name, lexical_analyser_h_code);
    biglib_fichier_ecrire(fichier_c_name, lexical_analyser_c_code);
    fprintf(flux, "Files ");
    fprintf(flux, "'%s'", fichier_h_name);
    fprintf(flux, " and ");
    fprintf(flux, "'%s'", fichier_c_name);
    //fprintf(flux, " were generated. You can add these files to your projects, or you can compile and test them with a command like 'cc -std=c99 ");
    fputs(" were generated. You can add these files to your projects, or you can test them now with the command 'cc -std=c99 ", flux);
    fputs(" -D ", flux);
    fputs(strupper(strconcat3("lexer_", lexer_name, "_USE_MAIN_FUNCTION")), flux);
    fputs(" ", flux);
    fputs(fichier_c_name, flux);
    fputs(" && ./a.out'.\n", flux);
  } while(false);
#endif
  
  
  
  // starting read-eval-print loop
  printf("==> Starting read-eval-print loop (type 'quit', 'exit', 'bye', or 'stop' to quit).\n");
  read_eval_print_loop(lignes -> nb, enum_name, expr_reguliere, ligne_vide_huh, automates);
  
  /*
    TODO
     - par defaut, generation automatique d'un fichier 'lexer_example.lexer.type' si aucun arg est donne
     - re-tester avec nouveau et trucs plus compliques 'lexer_italien.lexer.type'
     
  */
  
  
  return true;
}

















bool_t gen_c_code(const str_t * lexer_name, const int nb, const str_tableau_t * lignes, str_t * * enum_name, str_t * * expr_reguliere, const bool * ligne_vide_huh, automate_t * * automates, str_t * * c_code_extern_declarations_ptr, str_t * * c_code_static_declarations_ptr, str_t * * c_code_definitions_ptr, str_t * * c_code_main_ptr) {

#if 1
  char * h_code_pour_enum = NULL;
  char * c_code_pour_enum = NULL;
  {
    char * typebase_name;
    typebase_name = strconcat3("lexer_", lexer_name, "_token_type");
    //void generation_code_c_pour_un_enum(const char * type_nom_sans_t, const unsigned int nb, str_t * * enum_name, char * * h_code, char * * c_code);
    generation_code_c_pour_un_enum(typebase_name, nb, enum_name, &h_code_pour_enum, &c_code_pour_enum);
    
#if 0
    printf("%s\n", h_code_pour_enum);
    printf("%s\n", c_code_pour_enum);
#endif
  }
#endif
  
  
  
#if 1
  char * h_code_pour_struct = NULL;
  char * c_code_pour_struct = NULL;
  {
    //char * type_name[] = {strcopy("int"), strcopy("char")};
    char * type_name[] = {strconcat3("lexer_", lexer_name, "_token_type_t"), strcopy("char")};
    bool_t scalar_huh[] = {true, false};
    char * champ_name[] = {strcopy("type"), strcopy("value")};
    char * typebase_name;
    typebase_name = strconcat3("lexer_", lexer_name, "_token");
    //void generation_code_c_pour_un_struct(const char * lexer_name, const int nb, str_t * * type_name, bool_t * scalar_huh, str_t * * champ_name, char * * h_code, char * * c_code);
    generation_code_c_pour_un_struct(typebase_name, 2, type_name, scalar_huh, champ_name, &h_code_pour_struct, &c_code_pour_struct);
    
#if 0
    printf("%s\n", h_code_pour_struct);
    printf("%s\n", c_code_pour_struct);
#endif
  }
#endif
  
  
#if 1
  char * h_code_pour_liste = NULL;
  char * c_code_pour_liste = NULL;
  {
    char * typebase_name;
    typebase_name = strconcat3("lexer_", lexer_name, "_token");
    //static void generation_code_c_pour_une_liste_pointeur(const char * typebase_name, char * * h_code, char * * c_code);
    generation_code_c_pour_une_liste_pointeur(typebase_name, &h_code_pour_liste, &c_code_pour_liste);
    
#if 0
    printf("%s\n", h_code_pour_liste);
    printf("%s\n", c_code_pour_liste);
#endif
  }
#endif
    
    
#if 1
  str_t * automates_declarations_c_code[nb];
  str_t * automates_declarations_c_entetes[nb];
  {
    str_t * automates_declarations_c_funname[nb];

    for (int i = 0; i < nb; i++) {
      automates_declarations_c_funname[i] = strconcat4("lexer_", lexer_name, "_automaton_token_", strlower(enum_name[i]));
      automates_declarations_c_code[i] = automate_to_c_function_bis(automates[i], automates_declarations_c_funname[i], "", true);
      automates_declarations_c_entetes[i] = automate_to_c_function_bis(automates[i], automates_declarations_c_funname[i], "static", false);
    }
    
#if 0
    for (int i = 0; i < nb; i++) {
      printf("%s\n", automates_declarations_c_entetes[i]);
    }
    printf("\n");
    
    for (int i = 0; i < nb; i++) {
      printf("%s\n", automates_declarations_c_code[i]);
    }
    printf("\n");
#endif
  }
#endif
  

#if 1
  char * h_code_pour_fun_aux = NULL;
  char * c_code_pour_fun_aux = NULL;
  {
    char * prepend_string;
    char * prepend_string_for_automaton;
    char * prepend_string_for_enum;
    prepend_string = strconcat3("lexer_", lexer_name, "_");
    prepend_string_for_automaton = strconcat3("lexer_", lexer_name, "_automaton_token_");
    prepend_string_for_enum = strconcat3("lexer_", lexer_name, "_token_type_");
    //static void generation_code_c_pour_la_fonction_auxliaire(const char * prepend_string, const int nb, str_t * * enum_basename, char * * h_code, char * * c_code);
    generation_code_c_pour_la_fonction_auxliaire(prepend_string, prepend_string_for_automaton, prepend_string_for_enum, nb, enum_name, &h_code_pour_fun_aux, &c_code_pour_fun_aux);
    
#if 0
    printf("%s\n", h_code_pour_fun_aux);
    printf("%s\n", c_code_pour_fun_aux);
#endif
  }
#endif
  
  
  
  
  // starting read-eval-print loop
  //read_eval_print_loop(lignes -> nb, enum_name, expr_reguliere, ligne_vide_huh, automates);
  
  /*
    Pour la generation du code C:
     - une fonction lex_aux qui retourne l'automate qui reconnait le plus long prefixe ainsi que la longueur du plus long prefixe (exactement comme 'type_du_plus_long_prefixe_reconnu'),
        Cette fonction est independante du contexte.
     - une fonction lex, qui elle n'est pas indpt du contexte, puisqu'elle doit generer une liste de lexemes.
       Nous devons donc:
        * definir un type lexeme [enum, struct]
        * definir un type liste_de_lexeme
        * et enfin la colle entre les deux.
     - Bref, pas mal de taf....
     - par defaut, generation automatique d'un fichier exemple si aucun arg est donne
     
  */

#if 1
  char * h_code_pour_fun_principale = NULL;
  char * c_code_pour_fun_principale = NULL;
  {
    char * prepend_string;
    prepend_string = strconcat3("lexer_", lexer_name, "");
    //static void generation_code_c_pour_la_fonction_principale(const char * prepend_string, const int nb, str_t * * enum_basename, char * * h_code, char * * c_code);
    generation_code_c_pour_la_fonction_principale(prepend_string, nb, enum_name, &h_code_pour_fun_principale, &c_code_pour_fun_principale);
    
#if 0
    printf("%s\n", h_code_pour_fun_principale);
    printf("%s\n", c_code_pour_fun_principale);
#endif
  }
#endif
  
  
 
#if 1
  char * h_code_pour_fun_readline = NULL;
  char * c_code_pour_fun_readline = NULL;
  {
    char * prepend_string;
    prepend_string = strconcat3("lexer_", lexer_name, "");
    //static void generation_code_c_pour_la_fonction_readline(const char * prepend_string, char * * h_code, char * * c_code);
    generation_code_c_pour_la_fonction_readline(prepend_string, &h_code_pour_fun_readline, &c_code_pour_fun_readline);
    
#if 0
    printf("%s\n", h_code_pour_fun_readline);
    printf("%s\n", c_code_pour_fun_readline);
#endif
  }
#endif
  
#if 1
  char * h_code_pour_fun_readevalprintloop = NULL;
  char * c_code_pour_fun_readevalprintloop = NULL;
  {
    char * prepend_string;
    prepend_string = strconcat3("lexer_", lexer_name, "");
    //static void generation_code_c_pour_la_fonction_readevalprintloop(const char * prepend_string, char * * h_code, char * * c_code);
    generation_code_c_pour_la_fonction_readevalprintloop(prepend_string, &h_code_pour_fun_readevalprintloop, &c_code_pour_fun_readevalprintloop);
    
#if 0
    printf("%s\n", h_code_pour_fun_readevalprintloop);
    printf("%s\n", c_code_pour_fun_readevalprintloop);
#endif
  }
#endif
  
  
#if 1
  char * h_code_pour_fun_main = NULL;
  char * c_code_pour_fun_main = NULL;
  {
    char * prepend_string = NULL;
    char * conditional_directive_name = NULL;
    prepend_string = strconcat3("lexer_", lexer_name, "");
    conditional_directive_name = strconcat(strupper(prepend_string), "_USE_MAIN_FUNCTION");
    //static void generation_code_c_pour_la_fonction_main(const char * prepend_string, const int nb, const str_tableau_t * lignes, const bool * ligne_vide_huh, char * * h_code, char * * c_code);
    generation_code_c_pour_la_fonction_main(prepend_string, conditional_directive_name, nb, lignes, ligne_vide_huh, &h_code_pour_fun_main, &c_code_pour_fun_main);
    
#if 0
    printf("%s\n", h_code_pour_fun_main);
    printf("%s\n", c_code_pour_fun_main);
#endif
  }
#endif
  
  

  *c_code_extern_declarations_ptr = strcopy("");
  *c_code_static_declarations_ptr = strcopy("");
  *c_code_definitions_ptr = strcopy("");
  *c_code_main_ptr = strcopy("");
  
  stradd2(c_code_extern_declarations_ptr, h_code_pour_enum);
  stradd2(c_code_definitions_ptr, c_code_pour_enum);
  stradd2(c_code_extern_declarations_ptr, h_code_pour_struct);
  stradd2(c_code_definitions_ptr, c_code_pour_struct);
  stradd2(c_code_extern_declarations_ptr, h_code_pour_liste);
  stradd2(c_code_definitions_ptr, c_code_pour_liste);
  for (int i = 0; i < nb; i++) {
    stradd2(c_code_static_declarations_ptr, automates_declarations_c_entetes[i]);
    stradd2(c_code_definitions_ptr, automates_declarations_c_code[i]);
  }
  stradd2(c_code_static_declarations_ptr, h_code_pour_fun_aux);
  stradd2(c_code_definitions_ptr, c_code_pour_fun_aux);
  stradd2(c_code_extern_declarations_ptr, h_code_pour_fun_principale);
  stradd2(c_code_definitions_ptr, c_code_pour_fun_principale);
  stradd2(c_code_static_declarations_ptr, h_code_pour_fun_readline);
  stradd2(c_code_definitions_ptr, c_code_pour_fun_readline);
  stradd2(c_code_static_declarations_ptr, h_code_pour_fun_readevalprintloop);
  stradd2(c_code_definitions_ptr, c_code_pour_fun_readevalprintloop);
  //stradd2(c_code_extern_declarations_ptr, h_code_pour_fun_main);
  stradd2(c_code_main_ptr, c_code_pour_fun_main);
  
  
  return true;
}











void read_eval_print_loop(const int nb, str_t * * enum_name, str_t * * expr_reguliere, const bool * ligne_vide_huh, automate_t * * automates) {
  str_t * mot;
  const char * prompt = "> ";

  for (;;) {
    printf("%s", prompt);
    mot = readline();
    
    {
      bool_t quit_huh;
      quit_huh = false; 
      quit_huh |= striequal(mot, "");
      quit_huh |= striequal(mot, "quit\n");
      quit_huh |= striequal(mot, "bye\n");
      quit_huh |= striequal(mot, "exit\n");
      quit_huh |= striequal(mot, "stop\n");
      quit_huh |= striequal(mot, "quit");
      quit_huh |= striequal(mot, "bye");
      quit_huh |= striequal(mot, "exit");
      quit_huh |= striequal(mot, "stop");
      if (quit_huh) break;
    }

    analyse_de_la_ligne(nb, enum_name, expr_reguliere, ligne_vide_huh, automates, mot);
    printf("\n");
  }
  
  printf("Bye!\n");
  return;
  
#if 0
  mot = readline();

  printf("READ: %s\n", mot);
  return;

  mot = strcopy("123 45 \n 2332a §");
  mot = strcopy("");
  mot = strcopy("123");
  mot = strcopy("123 45 2332 a"); 
  mot = strcopy("123 45 /* 2332 ****/ 4 a a23 3"); 
#endif

}


// size_t fread(void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream);
str_t * readline(void) {
  char buffer[1024];
  bzero(buffer, 1024 * (sizeof(char)));
  for (int i = 0; i < 1024; i++) {
    size_t nb_read;
    nb_read = fread(&(buffer[i]), 1, 1, stdin);
    if (buffer[i] == '\n') break;
  }
  return strcopy(buffer);
}



void analyse_de_la_ligne(const int nb, str_t * * enum_name, str_t * * expr_reguliere, const bool * ligne_vide_huh, automate_t * * automates, const char * mot) {
  int longueur_du_plus_long_prefixe_reconnu;
  int indice_de_l_automate_ayant_reconnu_le_plus_long_prefixe;
  int nb_lettres_deja_reconnus;
  
  indice_de_l_automate_ayant_reconnu_le_plus_long_prefixe = -1;
  
  for (nb_lettres_deja_reconnus = 0; mot[nb_lettres_deja_reconnus] != '\0'; nb_lettres_deja_reconnus += longueur_du_plus_long_prefixe_reconnu) {
    indice_de_l_automate_ayant_reconnu_le_plus_long_prefixe = type_du_plus_long_prefixe_reconnu(nb, enum_name, expr_reguliere, ligne_vide_huh, automates, &(mot[nb_lettres_deja_reconnus]), &longueur_du_plus_long_prefixe_reconnu);
    
    if (indice_de_l_automate_ayant_reconnu_le_plus_long_prefixe < 0) {
      break;
    }
    
    //printf("Le mot '%s' est de type %s.\n", mot, enum_name[indice_de_l_automate_ayant_reconnu_le_plus_long_prefixe]);
    printf("%s", enum_name[indice_de_l_automate_ayant_reconnu_le_plus_long_prefixe]);
    printf("[%s]", substring(mot, nb_lettres_deja_reconnus, nb_lettres_deja_reconnus + longueur_du_plus_long_prefixe_reconnu));
    printf(" ");
    fflush(NULL);
  }
  
  if (nb_lettres_deja_reconnus > 0) 
    printf("\n");

  if (indice_de_l_automate_ayant_reconnu_le_plus_long_prefixe < 0) {
    printf("The suffix '%s' of the text '%s' was not recognized.\n", &(mot[nb_lettres_deja_reconnus]), mot);
  }
  else {
    printf("The text '%s' was successfully analyzed.\n", mot);
  }
  
}



int type_du_plus_long_prefixe_reconnu(const unsigned int nb, str_t * * enum_name, str_t * * expr_reguliere, const bool * ligne_vide_huh, automate_t * * automates, const char * mot, int * longueur_du_plus_long_prefixe_reconnu) {
  assert(mot != NULL);

  *longueur_du_plus_long_prefixe_reconnu = -1;
  
  for (unsigned int i = 0; i < nb; i++) {
    bool_t b;
    b = automate_deterministe_huh(automates[i]);
    if (not(b)) {
      //printf("L'un des automates n'est pas deterministe, je ne suis pas en mesure de faire la simulation.\n");
      printf("One of the automata is not deterministic. I need to be improved to run the simulation. Sorry.\n");
      return false;
    }
  }
  
  unsigned int etat_courant[nb];
  char lettre;
  unsigned int lettre_indice;
  
  for (unsigned int i = 0; i < nb; i++) {
    etat_courant[i] = automates[i] -> etat_initial;
  }
  
  
  int indice_automate_ayant_reconnu_le_plus_long_prefixe;
  indice_automate_ayant_reconnu_le_plus_long_prefixe = -1;
  
  for (int j = 0; mot[j] != '\0'; j++) {
    lettre = mot[j];
    lettre_indice = ((unsigned int) ((unsigned char) lettre));
    for (unsigned int i = 0; i < nb; i++) {
      etat_courant[i] = automates[i] -> transition[etat_courant[i]][lettre_indice];
    }
    
    for (int i = 0; i < (int) nb; i++) {
      if (automates[i] -> etat_final_huh[etat_courant[i]]) {
	indice_automate_ayant_reconnu_le_plus_long_prefixe = i;
	*longueur_du_plus_long_prefixe_reconnu = j+1;
      }
    }
    
    bool tous_les_automates_sont_bloques_huh = true;
    for (int i = 0; i < (int) nb; i++) {
      if (0 != etat_courant[i]) tous_les_automates_sont_bloques_huh = false;
    }
    
    if (tous_les_automates_sont_bloques_huh) break;
  }
  
  return indice_automate_ayant_reconnu_le_plus_long_prefixe;
}





str_t * gen_dotty_code(const int nb, str_t * * enum_name, str_t * * expr_reguliere, const bool * ligne_vide_huh, automate_t * * automates) {
  str_t * automates_dotty_name[nb];
  str_t * automates_dotty_code[nb];
  for (int i = 0; i < nb; i++) {
    str_t * automate_dotty_name;
    automate_dotty_name = enum_name[i];
    automate_dotty_name = string_char_replace(automate_dotty_name, '(', 'p');
    string_char_replace_nocopy(automate_dotty_name, '(', 'q');
    stradd3(&automate_dotty_name, "_rand", uint_string((unsigned)((uint8_t)random())));

    automates_dotty_name[i] = automate_dotty_name;
    automates_dotty_code[i] = automate_to_dotty(automates[i], automate_dotty_name);
  }
  
  // generation du code dotty complet
  str_t * lexical_analyser_dotty_code;
  lexical_analyser_dotty_code = strcopy("");
  stradd2(&lexical_analyser_dotty_code, "digraph lexical_analyser {\n");
  stradd2(&lexical_analyser_dotty_code, "  rankdir = LR;\n");
  stradd2(&lexical_analyser_dotty_code, "  \n");
  for (int i = 0; i < nb; i++) {
    stradd2(&lexical_analyser_dotty_code, automates_dotty_code[i]);
    stradd2(&lexical_analyser_dotty_code, "\n");
  }
  stradd2(&lexical_analyser_dotty_code, "}\n");
  stradd2(&lexical_analyser_dotty_code, "\n");

  return lexical_analyser_dotty_code;
}







bool la_string_ne_contient_que_des_caracteres_blancs_huh(const str_t * str) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (not(char_blanc_huh(str[i])))
      return false;
  }
  return true;
}








automate_t * compiler_une_expression_reguliere_en_automate(const char * expression_a_compiler_en_automate) {
  int ret;
  char * err;
  bool pas_erreur;
  token_liste_t * tokens;
  arbre_t * arbre;
  automate_t * automate;

  tokens = lex(expression_a_compiler_en_automate, &pas_erreur, &err);
  if (not(pas_erreur)) {
    printf("Analyse lexicale ratée: %s\n", err);
    return NULL;
  }
  //printf("tokens = %s\n", token_liste_string(tokens));
  
  
  ret = parser_parse(tokens, &arbre, &err, NULL);
  if (ret != 0) {
    printf("Analyse syntaxique ratéee: %s\n", err);
    return NULL;
  }
  //ARBRE_SHOW(arbre);

  automate = compilation(arbre);
  //AUTOMATE_SHOW(automate);
  
  arbre_free(arbre);
  token_liste_free(tokens);
  return automate;
}




void automate_show_with_dotty(const automate_t * automate, const char * automate_name_const) {
  char * fichier_dot_name;
  char * fichier_jpg_name;
  char * automate_name;
  automate_name = string_char_replace(automate_name_const, '(', 'p');
  string_char_replace_nocopy(automate_name, '(', 'q');
  stradd3(&automate_name, "_rand", uint_string((unsigned)((uint8_t)random())));
  fichier_dot_name = strconcat2(automate_name, ".dot");
  fichier_jpg_name = strconcat2(automate_name, ".jpg");
  system(strconcat2("rm -f ", fichier_dot_name));
  system(strconcat2("rm -f ", fichier_jpg_name));
  char * dot_desc = automate_to_dotty(automate, automate_name);
  biglib_fichier_ecrire(fichier_dot_name, dot_desc);
  free(dot_desc);
  system(strconcat5("dot -Tjpg -o ", fichier_jpg_name, " ", fichier_dot_name, " > /dev/null 2>&1"));
  system(strconcat2("open ", fichier_jpg_name));
  free(fichier_jpg_name);
  free(fichier_dot_name);
}




void arbre_show_with_dotty(const arbre_t * arbre, const char * arbre_name_const) {
  char * fichier_dot_name;
  char * fichier_jpg_name;
  char * arbre_name;
  arbre_name = string_char_replace(arbre_name_const, '(', 'p');
  string_char_replace_nocopy(arbre_name, ')', 'q');
  stradd3(&arbre_name, "_rand", uint_string((unsigned)((uint8_t)random())));
  fichier_dot_name = strconcat2(arbre_name, ".dot");
  fichier_jpg_name = strconcat2(arbre_name, ".jpg");
  system(strconcat3("rm -f \"", fichier_dot_name, "\""));
  system(strconcat3("rm -f \"", fichier_jpg_name, "\""));
  char * dot_desc = arbre_to_dotty(arbre, arbre_name);
  biglib_fichier_ecrire(fichier_dot_name, dot_desc);
  free(dot_desc);
  system(strconcat5("dot -Tjpg -o \"", fichier_jpg_name, "\" \"", fichier_dot_name, "\" > /dev/null 2>&1"));
  system(strconcat3("open \"", fichier_jpg_name, "\""));
  free(fichier_jpg_name);
  free(fichier_dot_name);
}





bool texte_decouper(const str_t * const texte, const char c, str_t * * str_gauche, str_t * * str_droite) {
  const unsigned int len = strlen(texte);
  unsigned int position;
  for (position = 0; position < len; position++)
    if (texte[position] == c) break;
  if (position == len) return false;
  assert(position != len);
  (*str_gauche) = substring(texte, 0, position);
  (*str_droite) = substring(texte, position + 1, len);
  return true;
}














void generation_code_c_pour_un_enum(const char * typebasename, const int nb, str_t * * enum_name, char * * h_code, char * * c_code) {
  assert(typebasename != NULL);
  assert(nb >= 0);
  assert(enum_name != NULL);
  assert(h_code != NULL);
  assert(c_code != NULL);
  char * type_nom_sans_t;
  char * type_nom_avec_t;
  char * type_nom_sans_t_lower;
  char * type_nom_sans_t_upper;
  char * type_nom_avec_t_upper;
  /*
  char * fichier_h_nom;
  char * fichier_c_nom;
  char * fichier_type_nom;
  char * fichier_type_contenu;
  */
  char * fichier_h_contenu;
  char * fichier_c_contenu;
  
  //type_nom_sans_t = strconcat(strlower(lexer_name), "_type");
  type_nom_sans_t = strlower(typebasename);
  type_nom_avec_t = strconcat(type_nom_sans_t, "_t");
  type_nom_sans_t_upper = strupper(type_nom_sans_t);
  type_nom_avec_t_upper = strupper(type_nom_avec_t);
  type_nom_sans_t_lower = strlower(type_nom_sans_t);
  
  
  // ***************************************
  // Generation du code H
  {
    fichier_h_contenu = strcopy("");

#if 0
    stradd4(&fichier_h_contenu, "#ifndef ", type_nom_sans_t_upper, "_H\n");
    stradd4(&fichier_h_contenu, "#define ", type_nom_sans_t_upper, "_H\n");
#endif
    
    stradd2(&fichier_h_contenu, "\n");
    
    stradd4(&fichier_h_contenu, "#ifndef ", type_nom_avec_t_upper, "\n");
    stradd4(&fichier_h_contenu, "#define ", type_nom_avec_t_upper, "\n");
    stradd4(&fichier_h_contenu, "enum ", type_nom_avec_t, ";\n");
    stradd2(&fichier_h_contenu, "#ifndef __cplusplus\n");
    stradd6(&fichier_h_contenu, "typedef enum ", type_nom_avec_t, " ", type_nom_avec_t, ";\n");
    stradd2(&fichier_h_contenu, "#endif\n");
    stradd4(&fichier_h_contenu, "#endif /* ", type_nom_avec_t_upper, " */\n");
    
    stradd2(&fichier_h_contenu, "\n");
    
    stradd4(&fichier_h_contenu, "enum ", type_nom_avec_t, " {\n");
    assert(1 <= nb);
    for (int i = 0; i < nb - 1; i++) {
      stradd6(&fichier_h_contenu, "  ", type_nom_sans_t_upper, "_", enum_name[i],",\n");
    }
    stradd6(&fichier_h_contenu, "  ", type_nom_sans_t_upper, "_", enum_name[nb - 1],"\n");
    stradd2(&fichier_h_contenu, "};\n");
    
    stradd2(&fichier_h_contenu, "\n");
    
    stradd6(&fichier_h_contenu, "#define ", type_nom_sans_t_upper, "_NOMBRE ", uint_string(nb),"\n");
    stradd4(&fichier_h_contenu, "extern const int ", type_nom_sans_t, "_nombre;\n");
    stradd6(&fichier_h_contenu, "extern const char * ", type_nom_sans_t, "_string_tab[", type_nom_sans_t_upper,"_NOMBRE];\n");
    
    
    stradd2(&fichier_h_contenu, "\n");
    
    stradd6(&fichier_h_contenu, "extern ", type_nom_avec_t, " ", type_nom_sans_t, "_make(void);\n");
    stradd8(&fichier_h_contenu, "extern void ", type_nom_sans_t, "_free(", type_nom_avec_t, " ", type_nom_sans_t, ");\n");
    stradd10(&fichier_h_contenu, "extern ", type_nom_avec_t, " ", type_nom_sans_t, "_copy(const ", type_nom_avec_t, " ", type_nom_sans_t, ");\n");
    stradd8(&fichier_h_contenu, "extern char * ", type_nom_sans_t, "_string(const ", type_nom_avec_t, " ", type_nom_sans_t, ");\n");
    stradd8(&fichier_h_contenu, "extern const char * ", type_nom_sans_t, "_string_const(const ", type_nom_avec_t, " ", type_nom_sans_t, ");\n");
    //stradd12(&fichier_h_contenu, "extern bool ", type_nom_sans_t, "_equal(const ", type_nom_avec_t, " ", type_nom_sans_t, "1, const ", type_nom_avec_t, " ", type_nom_sans_t, "2);\n");
    stradd12(&fichier_h_contenu, "extern int ", type_nom_sans_t, "_equal(const ", type_nom_avec_t, " ", type_nom_sans_t, "1, const ", type_nom_avec_t, " ", type_nom_sans_t, "2);\n");
    
    stradd2(&fichier_h_contenu, "\n\n");

#if 0    
    stradd4(&fichier_h_contenu, "#endif /* ", type_nom_sans_t_upper, "_H */\n");
#endif
  }


  

  // ***************************************
  // Generation du code C
  {
    fichier_c_contenu = strcopy("");
    
    //stradd2(&fichier_c_contenu, "#include \"global.h\"\n");
    //stradd4(&fichier_c_contenu, "#include \"", fichier_h_nom, "\"\n");
    stradd2(&fichier_c_contenu, "#include <string.h>\n");
    stradd2(&fichier_c_contenu, "#include <stdlib.h>\n");
    stradd2(&fichier_c_contenu, "#include <assert.h>\n");
    
    stradd2(&fichier_c_contenu, "\n\n");
    
    char * lib_code_c = NULL;
    lib_code_c = generation_code_c_pour_la_lib(type_nom_sans_t_lower);
    stradd2(&fichier_c_contenu, lib_code_c);
    
    stradd2(&fichier_c_contenu, "\n\n");
    
    stradd6(&fichier_c_contenu, "static ", type_nom_avec_t, " ", type_nom_sans_t, "_int_to_enum(const int n);\n");
    stradd5(&fichier_c_contenu, type_nom_avec_t, " ", type_nom_sans_t, "_int_to_enum(const int n) {\n");
    stradd2(&fichier_c_contenu, "  switch (n) {\n");
    stradd2(&fichier_c_contenu, "    default: assert(0 != 0); return -1; break;\n");
    for (int i = 0; i < nb; i++) {
      stradd10(&fichier_c_contenu, "    case ", type_nom_sans_t_upper, "_", enum_name[i], ": return ", type_nom_sans_t_upper, "_", enum_name[i], "; break;\n");
    }
    stradd2(&fichier_c_contenu, "  };\n");
    stradd2(&fichier_c_contenu, "  assert(0 != 0);\n");
    stradd2(&fichier_c_contenu, "  return -1;\n");
    stradd2(&fichier_c_contenu, "};\n\n");
    
    stradd5(&fichier_c_contenu, type_nom_avec_t, " ", type_nom_sans_t, "_make(void) {\n");
    //stradd4(&fichier_c_contenu, "  return ", type_nom_sans_t, "_int_to_enum(n);\n");
    stradd2(&fichier_c_contenu, "  assert(0 != 0);\n");
    stradd2(&fichier_c_contenu, "  return 0;\n");
    stradd2(&fichier_c_contenu, "};\n\n");
    
    stradd8(&fichier_c_contenu, "void ", type_nom_sans_t, "_free(", type_nom_avec_t, " ", type_nom_sans_t, ") {\n");
    stradd2(&fichier_c_contenu, "  return;\n");
    stradd2(&fichier_c_contenu, "};\n\n");
    
    stradd9(&fichier_c_contenu, type_nom_avec_t, " ", type_nom_sans_t, "_copy(const ", type_nom_avec_t, " ", type_nom_sans_t, ") {\n");
    stradd4(&fichier_c_contenu, "  return ", type_nom_sans_t, ";\n");
    stradd2(&fichier_c_contenu, "};\n\n");
    
    stradd6(&fichier_c_contenu, "const char * ", type_nom_sans_t, "_string_tab[", uint_string(nb),"] = {\n");
    assert(1 <= nb);
    for (int i = 0; i < nb - 1; i++) {
      stradd6(&fichier_c_contenu, "  \"", type_nom_sans_t_upper, "_", enum_name[i], "\",\n");
    }
    stradd6(&fichier_c_contenu, "  \"", type_nom_sans_t_upper, "_", enum_name[nb - 1], "\"\n");
    stradd2(&fichier_c_contenu, "};\n\n");
    
    stradd8(&fichier_c_contenu, "const char * ", type_nom_sans_t, "_string_const(const ", type_nom_avec_t, " ", type_nom_sans_t, ") {\n");
    stradd6(&fichier_c_contenu, "  return ", type_nom_sans_t, "_string_tab[", type_nom_sans_t, "];\n");
    stradd2(&fichier_c_contenu, "};\n\n");

    stradd8(&fichier_c_contenu, "char * ", type_nom_sans_t, "_string(const ", type_nom_avec_t, " ", type_nom_sans_t, ") {\n");
    stradd8(&fichier_c_contenu, "  return ", type_nom_sans_t_lower, "_strcopy(", type_nom_sans_t, "_string_tab[", type_nom_sans_t, "]);\n");
    stradd2(&fichier_c_contenu, "};\n\n");
    
    stradd12(&fichier_c_contenu, "int ", type_nom_sans_t, "_equal(const ", type_nom_avec_t, " ", type_nom_sans_t, "1, const ", type_nom_avec_t, " ", type_nom_sans_t, "2) {\n");
    stradd6(&fichier_c_contenu, "  return (", type_nom_sans_t, "1 == ", type_nom_sans_t, "2);\n");
    stradd2(&fichier_c_contenu, "};\n\n");
    
    stradd2(&fichier_c_contenu, "\n\n");
    
  }
  
  
  *h_code = fichier_h_contenu;
  *c_code = fichier_c_contenu;
  
}
















void generation_code_c_pour_un_struct(const char * typebasename, const int nb, str_t * * type_name, bool_t * scalar_huh, str_t * * champ_name, char * * h_code, char * * c_code) {
  assert(typebasename != NULL);
  assert(nb >= 0);
  assert(type_name != NULL);
  assert(scalar_huh != NULL);
  assert(champ_name != NULL);
  assert(h_code != NULL);
  assert(c_code != NULL);
  char * type_nom_sans_t;
  char * type_nom_avec_t;
  char * type_nom_sans_t_upper;
  char * type_nom_avec_t_upper;
  char * type_nom_sans_t_lower;
  /*
  char * fichier_h_nom;
  char * fichier_c_nom;
  char * fichier_type_nom;
  char * fichier_type_contenu;
  */
  char * fichier_h_contenu;
  char * fichier_c_contenu;
  
  //type_nom_sans_t = strconcat(strlower(lexer_name), "_token");
  type_nom_sans_t = strlower(typebasename);
  type_nom_avec_t = strconcat(type_nom_sans_t, "_t");
  type_nom_sans_t_upper = strupper(type_nom_sans_t);
  type_nom_avec_t_upper = strupper(type_nom_avec_t);
  type_nom_sans_t_lower = strlower(type_nom_sans_t);
  
  
  
  // ***************************************
  // SUBTYPES
  const int subtypes_nb = nb;
  bool_t subtypes_ptr_huh[subtypes_nb];
  bool_t subtypes_tab_huh[subtypes_nb];
  char * subtypes_name[subtypes_nb];
  char * subtypes_typename_raw[subtypes_nb];
  char * subtypes_typename_avec_t[subtypes_nb];
  char * subtypes_typename_sans_t[subtypes_nb];
  char * subtypes_tab_nb_name[subtypes_nb];
  char * subtypes_used_typename[subtypes_nb];
  char * subtypes_full_name[subtypes_nb];
  
  for (int i = 0; i < subtypes_nb; i++) {
    subtypes_name[i] = champ_name[i];
    subtypes_typename_raw[i] = type_name[i];
    subtypes_typename_sans_t[i] = type_enlever_t(subtypes_typename_raw[i]);
    subtypes_typename_avec_t[i] = subtypes_typename_raw[i];
    
#if 0    
    subtypes_ptr_huh[i] = ((mots -> nb > 1) && ((0 == strcmp("*", mots -> tab[mots -> nb - 2])) || (0 == strcmp("tab_ptr", mots -> tab[mots -> nb - 2]))));
    subtypes_tab_huh[i] = ((mots -> nb > 1) && ((0 == strcmp("tab_ptr", mots -> tab[mots -> nb - 2])) || (0 == strcmp("tab_scalar", mots -> tab[mots -> nb - 2]))));
    subtypes_tab_nb_name[i] = (((mots -> nb > 2) && subtypes_tab_huh[i]) ? mots -> tab[mots -> nb - 3] : NULL);
#endif
    
    subtypes_ptr_huh[i] = not(scalar_huh[i]);
    subtypes_tab_huh[i] = false;
    subtypes_tab_nb_name[i] = NULL;
    
    //subtypes_used_typename[i] = strconcat4(subtypes_typename_sans_t[i], (subtypes_tab_huh[i] ? "_array" : ""), "_t", (subtypes_ptr_huh[i] ? " *" : ""));
    subtypes_used_typename[i] = strconcat2(subtypes_typename_avec_t[i], (subtypes_ptr_huh[i] ? " *" : ""));
    
    subtypes_full_name[i] = strconcat3(subtypes_used_typename[i], " ", subtypes_name[i]);
  }
  
  
  
  
  
  
  // ***************************************
  // Generation du fichier H
  
  {
    fichier_h_contenu = strcopy("");
    
    //stradd4(&fichier_h_contenu, "#ifndef ", type_nom_sans_t_upper, "_H\n");
    //stradd4(&fichier_h_contenu, "#define ", type_nom_sans_t_upper, "_H\n");
    
    stradd2(&fichier_h_contenu, "\n");
    
    stradd4(&fichier_h_contenu, "#ifndef STRUCT_", type_nom_avec_t_upper, "_DECLARED\n");
    stradd4(&fichier_h_contenu, "#define STRUCT_", type_nom_avec_t_upper, "_DECLARED\n");
    stradd4(&fichier_h_contenu, "struct ", type_nom_avec_t, ";\n");
    stradd4(&fichier_h_contenu, "#endif /* STRUCT_", type_nom_avec_t_upper, "_DECLARED */\n");
    
    stradd2(&fichier_h_contenu, "\n");
    
    stradd4(&fichier_h_contenu, "#ifndef ", type_nom_avec_t_upper, "\n");
    stradd4(&fichier_h_contenu, "#define ", type_nom_avec_t_upper, "\n");
    stradd2(&fichier_h_contenu, "#ifndef __cplusplus\n");
    stradd6(&fichier_h_contenu, "typedef struct ", type_nom_avec_t, " ", type_nom_avec_t, ";\n");
    stradd2(&fichier_h_contenu, "#endif /* __cplusplus */\n");
    stradd4(&fichier_h_contenu, "#endif /* ", type_nom_avec_t_upper, " */\n");
    
    stradd2(&fichier_h_contenu, "\n");
    
    stradd4(&fichier_h_contenu, "#ifndef STRUCT_", type_nom_avec_t_upper, "\n");
    stradd4(&fichier_h_contenu, "#define STRUCT_", type_nom_avec_t_upper, "\n");
    stradd4(&fichier_h_contenu, "struct ", type_nom_avec_t, " {\n");
    for (int i = 0; i < nb; i++) {
      stradd4(&fichier_h_contenu, "  ", subtypes_full_name[i], ";\n");
    }
    stradd2(&fichier_h_contenu, "};\n");
    stradd4(&fichier_h_contenu, "#endif /* STRUCT_", type_nom_avec_t_upper, " */\n");
    
    
    stradd2(&fichier_h_contenu, "\n");
    stradd2(&fichier_h_contenu, "\n");
    
    stradd6(&fichier_h_contenu, "extern ", type_nom_avec_t, " * ", type_nom_sans_t, "_make(");
    for (int i = 0; i < nb; i++) {
      stradd3(&fichier_h_contenu, "const ", subtypes_full_name[i]);
      if (i < nb - 1)
	stradd2(&fichier_h_contenu, ", ");
    }
    stradd2(&fichier_h_contenu, ");\n");
    stradd6(&fichier_h_contenu, "extern ", type_nom_avec_t, " * ", type_nom_sans_t, "_make_nocopy(");
    for (int i = 0; i < nb; i++) {
      stradd2(&fichier_h_contenu, subtypes_full_name[i]);
      if (i < nb - 1)
	stradd2(&fichier_h_contenu, ", ");
    }
    stradd2(&fichier_h_contenu, ");\n");
    stradd8(&fichier_h_contenu, "extern void ", type_nom_sans_t, "_free(", type_nom_avec_t, " * ", type_nom_sans_t, ");\n");
    stradd10(&fichier_h_contenu, "extern ", type_nom_avec_t, " * ", type_nom_sans_t, "_copy(const ", type_nom_avec_t, " * ", type_nom_sans_t, ");\n");
    stradd8(&fichier_h_contenu, "extern char * ", type_nom_sans_t, "_string(const ", type_nom_avec_t, " * ", type_nom_sans_t, ");\n");
    stradd12(&fichier_h_contenu, "extern int ", type_nom_sans_t, "_equal(const ", type_nom_avec_t, " * ", type_nom_sans_t, "1, const ", type_nom_avec_t, " * ", type_nom_sans_t, "2);\n");
    
    stradd2(&fichier_h_contenu, "\n");
    stradd2(&fichier_h_contenu, "\n");
    
    //stradd4(&fichier_h_contenu, "#endif /* ", type_nom_sans_t_upper, "_H */\n");
  }
  
  
  
  // ***************************************
  // Generation du fichier C

  {
    fichier_c_contenu = strcopy("");
    
    //stradd2(&fichier_c_contenu, "#include \"global.h\"\n");
    //stradd4(&fichier_c_contenu, "#include \"", fichier_h_nom, "\"\n");
    stradd2(&fichier_c_contenu, "#include <string.h>\n");
    stradd2(&fichier_c_contenu, "#include <stdlib.h>\n");
    stradd2(&fichier_c_contenu, "#include <assert.h>\n");
    stradd2(&fichier_c_contenu, "#include <stdio.h>\n");
    
    stradd2(&fichier_c_contenu, "\n\n");

    char * lib_code_c = NULL;
    lib_code_c = generation_code_c_pour_la_lib(type_nom_sans_t_lower);
    stradd2(&fichier_c_contenu, lib_code_c);
    
    
    stradd2(&fichier_c_contenu, "\n\n");
    stradd6(&fichier_c_contenu, "static ", type_nom_avec_t, " * ", type_nom_sans_t, "_allouer(void);\n");
    
    stradd2(&fichier_c_contenu, "\n\n");
    
    stradd5(&fichier_c_contenu, type_nom_avec_t, " * ", type_nom_sans_t, "_allouer(void) {\n");
    stradd6(&fichier_c_contenu, "  return (", type_nom_avec_t, " *) malloc((sizeof (", type_nom_avec_t, ")));\n");
    stradd2(&fichier_c_contenu, "};\n\n\n");
    
    stradd5(&fichier_c_contenu, type_nom_avec_t, " * ", type_nom_sans_t, "_make(");
    for (int i = 0; i < nb; i++) {
      stradd3(&fichier_c_contenu, "const ", subtypes_full_name[i]);
      if (i < nb - 1)
	stradd2(&fichier_c_contenu, ", ");
    }
    stradd2(&fichier_c_contenu, ") {\n");
    stradd4(&fichier_c_contenu, "  return ", type_nom_sans_t, "_make_nocopy(");
    for (int i = 0; i < nb; i++) {
      if (subtypes_ptr_huh[i] && not(subtypes_tab_huh[i])) {
	if (strequal(subtypes_typename_raw[i], "char")) 
	  stradd5(&fichier_c_contenu, type_nom_sans_t_lower, "_strcopy(", subtypes_name[i], ")");
	else
	  stradd5(&fichier_c_contenu, subtypes_typename_sans_t[i], "_copy(", subtypes_name[i], ")");
      }
      else if (subtypes_ptr_huh[i] && subtypes_tab_huh[i])
	stradd9(&fichier_c_contenu, subtypes_typename_sans_t[i], "_array_copy(", subtypes_name[i], ",", subtypes_tab_nb_name[i], ",", subtypes_tab_nb_name[i], ")");
      else
	stradd2(&fichier_c_contenu, subtypes_name[i]);
      
      if (i < nb - 1)
	stradd2(&fichier_c_contenu, ", ");
    }
    stradd2(&fichier_c_contenu, ");\n");
    stradd2(&fichier_c_contenu, "};\n\n\n");
    
    stradd5(&fichier_c_contenu, type_nom_avec_t, " * ", type_nom_sans_t, "_make_nocopy(");
    for (int i = 0; i < nb; i++) {
      stradd2(&fichier_c_contenu, subtypes_full_name[i]);
      if (i < nb - 1)
	stradd2(&fichier_c_contenu, ", ");
    }
    stradd2(&fichier_c_contenu, ") {\n");
    stradd4(&fichier_c_contenu, "  ", type_nom_avec_t, " * retour;\n\n");
    stradd4(&fichier_c_contenu, "  retour = ", type_nom_sans_t, "_allouer();\n\n");
#if 0
    for (int i = 0; i < nb; i++) {
      str_tableau_t * mots;
      mots = texte_en_mot(fichier_type_lignes -> tab[i]);
      assert(mots -> nb > 0);
      
      stradd6(&fichier_c_contenu, "  retour -> ", mots -> tab[mots -> nb - 1], " = ", mots -> tab[mots -> nb - 1], ";\n");
    }
#else
    for (int i = 0; i < nb; i++) {
      stradd6(&fichier_c_contenu, "  retour -> ", subtypes_name[i], " = ", subtypes_name[i], ";\n");
    }
#endif
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  return retour;\n");
    stradd2(&fichier_c_contenu, "};\n\n\n");
    
    
    
    
    stradd8(&fichier_c_contenu, "void ", type_nom_sans_t, "_free(", type_nom_avec_t, " * ", type_nom_sans_t, ") {\n");
    stradd4(&fichier_c_contenu, "  if (", type_nom_sans_t, " == NULL) return;\n");
    for (int i = 0; i < nb; i++) {
      if (subtypes_ptr_huh[i] && not(subtypes_tab_huh[i])) {
	if (strequal(subtypes_typename_raw[i], "char")) 
	  stradd6(&fichier_c_contenu, "  free(", type_nom_sans_t, " -> ", subtypes_name[i], ");\n");
	else
	  stradd8(&fichier_c_contenu, "  ", subtypes_typename_sans_t[i], "_free(", type_nom_sans_t, " -> ", subtypes_name[i], ");\n");
      }
      if (subtypes_ptr_huh[i] && subtypes_tab_huh[i]) {
	stradd8(&fichier_c_contenu, "  ", subtypes_typename_sans_t[i], "_array_free(", type_nom_sans_t, " -> ", subtypes_name[i], ", ");
	stradd9(&fichier_c_contenu, type_nom_sans_t, " -> ", subtypes_tab_nb_name[i], ", ",  type_nom_sans_t, " -> ", subtypes_tab_nb_name[i], ");\n");
      }
    }
    stradd4(&fichier_c_contenu, "  free(", type_nom_sans_t, ");\n");
    stradd2(&fichier_c_contenu, "  return;\n");
    stradd2(&fichier_c_contenu, "};\n\n\n");
    
    stradd9(&fichier_c_contenu, type_nom_avec_t, " * ", type_nom_sans_t, "_copy(const ", type_nom_avec_t, " * ", type_nom_sans_t, ") {\n");
    stradd4(&fichier_c_contenu, "  if (NULL == ", type_nom_sans_t, ") return NULL;\n");
    stradd4(&fichier_c_contenu, "  return ", type_nom_sans_t, "_make(");
#if 0
    for (int i = 0; i < nb; i++) {
      str_tableau_t * mots;
      mots = texte_en_mot(fichier_type_lignes -> tab[i]);
      assert(mots -> nb > 0);
      stradd4(&fichier_c_contenu, type_nom_sans_t, " -> ", mots -> tab[mots -> nb - 1]);
      if (i < nb - 1)
	stradd2(&fichier_c_contenu, ", ");
    }
#else
    for (int i = 0; i < nb; i++) {
      stradd4(&fichier_c_contenu, type_nom_sans_t, " -> ", subtypes_name[i]);
      if (i < nb - 1)
	stradd2(&fichier_c_contenu, ", ");
    }
#endif
    stradd2(&fichier_c_contenu, ");\n");
    stradd2(&fichier_c_contenu, "};\n\n\n");
    
    
    stradd8(&fichier_c_contenu, "char * ", type_nom_sans_t, "_string(const ", type_nom_avec_t, " * ", type_nom_sans_t, ") {\n");
    stradd6(&fichier_c_contenu, "  if (", type_nom_sans_t, " == NULL) return ", type_nom_sans_t, "_strcopy(\"NULL\");\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  char * retour;\n");
    stradd2(&fichier_c_contenu, "  char * temp;\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd4(&fichier_c_contenu, "  retour = ", type_nom_sans_t, "_strcopy(\"\");\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd6(&fichier_c_contenu, "  ", type_nom_sans_t, "_stradd2(&retour, \"struct ", type_nom_avec_t, " [\");\n");
    stradd2(&fichier_c_contenu, "  \n");
    for (int i = 0; i < nb; i++) {

      if (not(subtypes_tab_huh[i])) {
	if (strequal(subtypes_typename_raw[i], "char")) 
	  stradd8(&fichier_c_contenu, "  temp = ", type_nom_sans_t, "_strcopy(", type_nom_sans_t, " -> ", subtypes_name[i], ");\n");
	else if (strequal(subtypes_typename_raw[i], "int")) 
	  stradd8(&fichier_c_contenu, "  temp = ", type_nom_sans_t, "_int_string(", type_nom_sans_t, " -> ", subtypes_name[i], ");\n");
	else 
	  stradd8(&fichier_c_contenu, "  temp = ", subtypes_typename_sans_t[i], "_string(", type_nom_sans_t, " -> ", subtypes_name[i], ");\n");
      }
      else {
	stradd8(&fichier_c_contenu, "  temp = ", subtypes_typename_sans_t[i], "_array_string(", type_nom_sans_t, " -> ", subtypes_name[i], ", ");
	stradd9(&fichier_c_contenu, type_nom_sans_t, " -> ", subtypes_tab_nb_name[i],  ", ", type_nom_sans_t, " -> ", subtypes_tab_nb_name[i], ");\n");
      }
      stradd6(&fichier_c_contenu, "  ", type_nom_sans_t_lower, "_stradd3(&retour, \"", subtypes_name[i], " = \", temp);\n");
      //stradd2(&fichier_c_contenu, "  strfree(temp);\n");
      stradd2(&fichier_c_contenu, "  free(temp);\n");
      stradd2(&fichier_c_contenu, "  \n");
      
      if (i < nb - 1) {
	stradd4(&fichier_c_contenu, "  ", type_nom_sans_t_lower, "_stradd2(&retour, \", \");\n");
      }
      stradd2(&fichier_c_contenu, "  \n");
    }
    stradd4(&fichier_c_contenu, "  ", type_nom_sans_t_lower, "_stradd2(&retour, \"]\");\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  return retour;\n");
    stradd2(&fichier_c_contenu, "};\n");
    stradd2(&fichier_c_contenu, "\n");
    stradd2(&fichier_c_contenu, "\n");
    
    
    stradd12(&fichier_c_contenu, "int ", type_nom_sans_t, "_equal(const ", type_nom_avec_t, " * ", type_nom_sans_t, "1, const ", type_nom_avec_t, " * ", type_nom_sans_t, "2) {\n");
    stradd6(&fichier_c_contenu, "  if (", type_nom_sans_t, "1 == ", type_nom_sans_t, "2) return (0 == 0);\n");
    stradd4(&fichier_c_contenu, "  if (", type_nom_sans_t, "1 == NULL) return (0 != 0);\n");
    stradd4(&fichier_c_contenu, "  if (", type_nom_sans_t, "2 == NULL) return (0 != 0);\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  return (");
    
    for (int i = 0; i < nb; i++) {
      //if ((mots -> nb > 1) && (0 == strcmp("*", mots -> tab[mots -> nb - 2]))) 
      if (subtypes_ptr_huh[i] && not(subtypes_tab_huh[i])) {
	if (strequal(subtypes_typename_raw[i], "char")) 
	  stradd10(&fichier_c_contenu, "(0 == strcmp(", type_nom_sans_t, "1 -> ", subtypes_name[i], ", ", type_nom_sans_t, "2 -> ", subtypes_name[i], "))");
	else 
	  stradd12(&fichier_c_contenu, "(", subtypes_typename_sans_t[i], "_equal(", type_nom_sans_t, "1 -> ", subtypes_name[i], ", ", type_nom_sans_t, "2 -> ", subtypes_name[i], "))");
      }
      else if (subtypes_ptr_huh[i] && subtypes_tab_huh[i]) {
	//stradd12(&fichier_c_contenu, "(", subtypes_typename_sans_t[i], "_array_equal(", type_nom_sans_t, "1 -> ", subtypes_name[i], ", ", type_nom_sans_t, "2 -> ", subtypes_name[i], "))");
	stradd8(&fichier_c_contenu, "(", subtypes_typename_sans_t[i], "_array_equal(", type_nom_sans_t, "1 -> ", subtypes_name[i], ", ");
	stradd9(&fichier_c_contenu, type_nom_sans_t, "1 -> ", subtypes_tab_nb_name[i], ", ", type_nom_sans_t, "1 -> ", subtypes_tab_nb_name[i], ", ");
	stradd13(&fichier_c_contenu, type_nom_sans_t, "2 -> ", subtypes_name[i], ", ", type_nom_sans_t, "2 -> ", subtypes_tab_nb_name[i], ", ", type_nom_sans_t, "2 -> ", subtypes_tab_nb_name[i], "))");
	//stradd9(&fichier_c_contenu, type_nom_sans_t, " -> ", subtypes_tab_nb_name[i],  ", ", type_nom_sans_t, " -> ", subtypes_tab_nb_name[i], ");\n");
      }
      else
	stradd10(&fichier_c_contenu, "(", type_nom_sans_t, "1 -> ", subtypes_name[i], " == ", type_nom_sans_t, "2 -> ", subtypes_name[i], ")");
      
      if (i < nb - 1) {
	stradd2(&fichier_c_contenu, " && ");
      }
    }
    
    stradd2(&fichier_c_contenu, ");\n");
    stradd2(&fichier_c_contenu, "};\n\n\n");
  }
  
  
  
  *h_code = fichier_h_contenu;
  *c_code = fichier_c_contenu;
  
}






char * type_enlever_t(const char * str) {
  uint_t len;

  len = strlen(str);

  if (len < 2)
    return strcopy(str);

  if (0 != strcmp("_t", str + len - 2))
    return strcopy(str);

  char * retour;
  retour = strcopy(str);
  retour[len - 2] = '\0';

  return retour;
}










void generation_code_c_pour_une_liste_pointeur(const char * typebase_name, char * * h_code, char * * c_code) {
  assert(typebase_name != NULL);
  assert(h_code != NULL);
  assert(c_code != NULL);
  
  char * nv_liste_h;
  char * nv_liste_c;
  
  const char * type_name = typebase_name;
  char * type_name_lower = strlower(type_name);
  char * type_name_upper = strupper(type_name);
  
  nv_liste_h = strcopy(liste_pointeur_h_template);
  nv_liste_h = string_replace(nv_liste_h, '$', type_name_upper);
  nv_liste_h = string_replace(nv_liste_h, '@', type_name_lower);
  
  char * type_nom_sans_t;
  char * type_nom_avec_t;
  char * type_nom_sans_t_upper;
  char * type_nom_avec_t_upper;
  char * type_nom_sans_t_lower;
  
  type_nom_sans_t = strconcat(type_name, "_liste");
  type_nom_avec_t = strconcat(type_nom_sans_t, "_t");
  type_nom_sans_t_upper = strupper(type_nom_sans_t);
  type_nom_avec_t_upper = strupper(type_nom_avec_t);
  type_nom_sans_t_lower = strlower(type_nom_sans_t);
  
  nv_liste_c = strcopy("");
  char * lib_code_c = NULL;
  lib_code_c = generation_code_c_pour_la_lib(type_nom_sans_t_lower);
  stradd2(&nv_liste_c, lib_code_c);
  stradd2(&nv_liste_c, liste_pointeur_c_template);
  nv_liste_c = string_replace(nv_liste_c, '$', type_name_upper);
  nv_liste_c = string_replace(nv_liste_c, '@', type_name_lower);
  
  *h_code = nv_liste_h;
  *c_code = nv_liste_c;
  
}



char * string_replace(const char * text, const char c, const char * str) {
  const size_t text_len = strlen(text);
  const size_t str_len = strlen(str);

  const int nb_occ = nb_occurrences(text, c);

  const size_t new_len = text_len + nb_occ * str_len;

  char * nv_text = (char *) malloc((new_len + 1) * (sizeof (char)));

  unsigned pos = 0;
  while (*text != '\0') {
    if (*text == c) {
      memcpy(nv_text + pos, str, str_len);
      pos += str_len;
    }
    else {
      nv_text[pos] = *text;
      pos++;
    }

    text++;
  }
  
  nv_text[pos] = '\0';
  
  return nv_text;
}




int nb_occurrences(const char * str, const char c) {
  int nb = 0;
  while (*str != '\0') {
    if (*str == c) nb++;
    str++;
  }
  return nb;
}









char * generation_code_c_pour_la_lib(const char * basename) {
  assert(basename != NULL);
  char * type_nom_sans_t;
  char * type_nom_avec_t;
  char * type_nom_sans_t_upper;
  char * type_nom_avec_t_upper;
  char * type_nom_sans_t_lower;
  char * fichier_c_contenu;
  
  type_nom_sans_t = strcopy(basename);
  type_nom_avec_t = strconcat(type_nom_sans_t, "_t");
  type_nom_sans_t_upper = strupper(type_nom_sans_t);
  type_nom_avec_t_upper = strupper(type_nom_avec_t);
  type_nom_sans_t_lower = strlower(type_nom_sans_t);
  
  
  
  
  // ***************************************
  // Generation du fichier C

  {
    fichier_c_contenu = strcopy("");
    
    stradd2(&fichier_c_contenu, "#include <string.h>\n");
    stradd2(&fichier_c_contenu, "#include <stdlib.h>\n");
    stradd2(&fichier_c_contenu, "#include <assert.h>\n");
    stradd2(&fichier_c_contenu, "#include <stdio.h>\n");
    
    stradd2(&fichier_c_contenu, "\n\n");
    
    stradd4(&fichier_c_contenu, "static char * ", type_nom_sans_t_lower, "_strcopy(const char * str);\n");
    stradd4(&fichier_c_contenu, "char * ", type_nom_sans_t_lower, "_strcopy(const char * str) {\n");
    stradd2(&fichier_c_contenu, "  const size_t len = strlen(str);\n");
    stradd2(&fichier_c_contenu, "  const size_t len_octet = (len+1) * (sizeof(char));\n");
    stradd2(&fichier_c_contenu, "  char * retour;\n");
    stradd2(&fichier_c_contenu, "  retour = (char *) malloc(len_octet);\n");
    stradd2(&fichier_c_contenu, "  memcpy(retour, str, len_octet);\n");
    stradd2(&fichier_c_contenu, "  return retour;\n");
    stradd2(&fichier_c_contenu, "}\n");
    
    stradd2(&fichier_c_contenu, "\n\n");
    stradd4(&fichier_c_contenu, "static char * ", type_nom_sans_t_lower, "_int_string(int n);\n");
    stradd4(&fichier_c_contenu, "char * ", type_nom_sans_t_lower, "_int_string(int n) {\n");
    stradd2(&fichier_c_contenu, "  char * retour;\n");
    stradd2(&fichier_c_contenu, "  asprintf(&retour, \"%d\", n);\n");
    stradd2(&fichier_c_contenu, "  return retour;\n");
    stradd2(&fichier_c_contenu, "}\n");

    stradd2(&fichier_c_contenu, "\n\n");
    stradd4(&fichier_c_contenu, "static char * ", type_nom_sans_t_lower, "_strconcat2(const char * const str1, const char * const str2);\n");
    stradd4(&fichier_c_contenu, "char * ", type_nom_sans_t_lower, "_strconcat2(const char * const str1, const char * const str2) {\n");
    stradd2(&fichier_c_contenu, "  const size_t len = strlen(str1) + strlen(str2);\n");
    stradd2(&fichier_c_contenu, "  return strcat(strcpy(malloc((len + 1)*(sizeof(char))), str1), str2);\n");
    stradd2(&fichier_c_contenu, "}\n");
    
    stradd2(&fichier_c_contenu, "\n\n");
    stradd4(&fichier_c_contenu, "static char * ", type_nom_sans_t_lower, "_strconcat3(const char * const str1, const char * const str2, const char * const str3);\n");
    stradd4(&fichier_c_contenu, "char * ", type_nom_sans_t_lower, "_strconcat3(const char * const str1, const char * const str2, const char * const str3) {\n");
    stradd2(&fichier_c_contenu, "  const size_t len = strlen(str1) + strlen(str2) + strlen(str3);\n");
    stradd2(&fichier_c_contenu, "  return strcat(strcat(strcpy(malloc((len + 1)*(sizeof(char))), str1), str2), str3);\n");
    stradd2(&fichier_c_contenu, "}\n");

    stradd2(&fichier_c_contenu, "\n\n");
    stradd4(&fichier_c_contenu, "static void ", type_nom_sans_t_lower, "_stradd2(char * * str0, const char * str1);\n");
    stradd4(&fichier_c_contenu, "void ", type_nom_sans_t_lower, "_stradd2(char * * str0, const char * str1) {\n");
    stradd2(&fichier_c_contenu, "  char * temp;\n");
    stradd4(&fichier_c_contenu, "  temp = ", type_nom_sans_t_lower, "_strconcat2(*str0, str1);\n");
    stradd2(&fichier_c_contenu, "  free(*str0);\n");
    stradd2(&fichier_c_contenu, "  *str0 = temp;\n");
    stradd2(&fichier_c_contenu, "}\n");
    
    stradd2(&fichier_c_contenu, "\n\n");
    stradd4(&fichier_c_contenu, "static void ", type_nom_sans_t_lower, "_stradd3(char * * str0, const char * str1, const char * str2);\n");
    stradd4(&fichier_c_contenu, "void ", type_nom_sans_t_lower, "_stradd3(char * * str0, const char * str1, const char * str2) {\n");
    stradd2(&fichier_c_contenu, "  char * temp;\n");
    stradd4(&fichier_c_contenu, "  temp = ", type_nom_sans_t_lower, "_strconcat3(*str0, str1, str2);\n");
    stradd2(&fichier_c_contenu, "  free(*str0);\n");
    stradd2(&fichier_c_contenu, "  *str0 = temp;\n");
    stradd2(&fichier_c_contenu, "}\n");

    stradd2(&fichier_c_contenu, "\n\n");
    stradd4(&fichier_c_contenu, "static char * ", type_nom_sans_t_lower, "_substring(const char * str, unsigned int debut, unsigned int fin);\n");
    stradd4(&fichier_c_contenu, "char * ", type_nom_sans_t_lower, "_substring(const char * str, unsigned int debut, unsigned int fin) {\n");
    stradd2(&fichier_c_contenu, "  size_t len;\n");
    stradd2(&fichier_c_contenu, "  size_t taille_octet;\n");
    stradd2(&fichier_c_contenu, "  char * retour;\n");
    stradd2(&fichier_c_contenu, "  assert(debut <= fin);\n");
    stradd2(&fichier_c_contenu, "  len = fin - debut;\n");
    stradd2(&fichier_c_contenu, "  taille_octet = (len + 1) * (sizeof (char));\n");
    stradd2(&fichier_c_contenu, "  retour = (char *) malloc(taille_octet);\n");
    stradd2(&fichier_c_contenu, "  memcpy(retour, str + debut, taille_octet);\n");
    stradd2(&fichier_c_contenu, "  retour[len] = '\\0';\n");
    stradd2(&fichier_c_contenu, "  return retour;\n");
    stradd2(&fichier_c_contenu, "}\n");
    stradd2(&fichier_c_contenu, "\n\n");



    stradd2(&fichier_c_contenu, "\n\n\n");
  }
  
  
  
  return fichier_c_contenu;  
}











#if 0
  extern unsigned int lexeme_commentaire_multiligne_etat_initial_get(void);
  extern unsigned int lexeme_commentaire_multiligne_etat_puits_huh(const unsigned int etat);
  extern bool lexeme_commentaire_multiligne_etat_final_huh(const unsigned int etat);
  extern unsigned int lexeme_commentaire_multiligne_etat_suivant_get(const unsigned int etat_courant, const char lettre);
  extern bool lexeme_commentaire_multiligne_mot_reconnu_huh(const char * mot);
#endif

  /*
    Pour la generation du code C:
     - une fonction lex_aux qui retourne l'automate qui reconnait le plus long prefixe ainsi que la longueur du plus long prefixe (exactement comme 'type_du_plus_long_prefixe_reconnu'),
        Cette fonction est independante du contexte.
     - une fonction lex, qui elle n'est pas indpt du contexte, puisqu'elle doit generer une liste de lexemes.
       Nous devons donc:
        * definir un type lexeme [enum, struct]
        * definir un type liste_de_lexeme
        * et enfin la colle entre les deux.
     - par defaut, generation automatique d'un fichier exemple si aucun arg est donne
     
  */
void generation_code_c_pour_la_fonction_auxliaire(const char * prepend_string, const char * prepend_string_for_automaton, const char * prepend_string_for_enum, const int nb, str_t * * enum_basename, char * * h_code, char * * c_code) {
  assert(prepend_string != NULL);
  assert(prepend_string_for_automaton != NULL);
  assert(prepend_string_for_enum != NULL);
  assert(nb >= 0);
  assert(enum_basename != NULL);
  assert(h_code != NULL);
  assert(c_code != NULL);
  
  char * fichier_h_contenu = NULL;
  char * fichier_c_contenu = NULL;
  
  str_t * enum_name[nb];
  for (int i = 0; i < nb; i++) {
    enum_name[i] = strupper(strconcat2(prepend_string_for_enum, enum_basename[i]));
  }
  
  str_t * enum_type_name = NULL;
  enum_type_name = strlower(strconcat2(prepend_string_for_enum, "t"));
  
  str_t * automaton_name[nb];
  str_t * automaton_fun_etat_initial_get_name[nb];
  str_t * automaton_fun_etat_puits_huh_name[nb];
  str_t * automaton_fun_etat_final_huh_name[nb];
  str_t * automaton_fun_etat_etat_suivant_get_name[nb];
  for (int i = 0; i < nb; i++) {
    automaton_name[i] = strconcat2(prepend_string_for_automaton, strlower(enum_basename[i]));
    automaton_fun_etat_initial_get_name[i] = strconcat(automaton_name[i], "_etat_initial_get");
    automaton_fun_etat_puits_huh_name[i] = strconcat(automaton_name[i], "_etat_puits_huh");
    automaton_fun_etat_final_huh_name[i] = strconcat(automaton_name[i], "_etat_final_huh");
    automaton_fun_etat_etat_suivant_get_name[i] = strconcat(automaton_name[i], "_etat_suivant_get");
  }
  
  
  
  // ***************************************
  // Generation du fichier H
  {
    fichier_h_contenu = strcopy("");
    
    stradd2(&fichier_h_contenu, "\n\n");
    stradd2(&fichier_h_contenu, "\n\n");
  }
  
    
  // ***************************************
  // Generation du fichier C
  {
    fichier_c_contenu = strcopy("");

    stradd2(&fichier_c_contenu, "\n\n");
    
#if 0
  extern unsigned int lexeme_commentaire_multiligne_etat_initial_get(void);
  extern unsigned int lexeme_commentaire_multiligne_etat_puits_huh(const unsigned int etat);
  extern bool lexeme_commentaire_multiligne_etat_final_huh(const unsigned int etat);
  extern unsigned int lexeme_commentaire_multiligne_etat_suivant_get(const unsigned int etat_courant, const char lettre);
  extern bool lexeme_commentaire_multiligne_mot_reconnu_huh(const char * mot);
#endif
  
#if 1
  //int type_du_plus_long_prefixe_reconnu(const int nb, str_t * * enum_name, str_t * * expr_reguliere, const bool * ligne_vide_huh, automate_t * * automates, const char * mot, int * longueur_du_plus_long_prefixe_reconnu) {
    stradd2(&fichier_c_contenu, "\n\n");
    stradd4(&fichier_c_contenu, "static int type_du_plus_long_prefixe_reconnu(const char * mot, ", enum_type_name, " * type_ptr, int * longueur_du_plus_long_prefixe_reconnu_ptr);\n");
    stradd2(&fichier_c_contenu, "\n\n");
    stradd4(&fichier_c_contenu, "int type_du_plus_long_prefixe_reconnu(const char * mot, ", enum_type_name, " * type_ptr, int * longueur_du_plus_long_prefixe_reconnu_ptr) {\n");
    stradd2(&fichier_c_contenu, "  assert(mot != NULL);\n");
    stradd2(&fichier_c_contenu, "  assert(type_ptr != NULL);\n");
    stradd2(&fichier_c_contenu, "  assert(longueur_du_plus_long_prefixe_reconnu_ptr != NULL);\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  *longueur_du_plus_long_prefixe_reconnu_ptr = -1;\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd4(&fichier_c_contenu, "  int etat_courant[", int_string(nb),"];\n");
    stradd2(&fichier_c_contenu, "  char lettre;\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  {\n");
    for (int i = 0; i < nb; i++) {
      //stradd2(&fichier_c_contenu, "    etat_courant[0] = lexeme_commentaire_multiligne_etat_initial_get();\n");
      stradd6(&fichier_c_contenu, "    etat_courant[", int_string(i),"] = ", automaton_fun_etat_initial_get_name[i],"();\n");
    }
    stradd2(&fichier_c_contenu, "  }\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  int indice_automate_ayant_reconnu_le_plus_long_prefixe;\n");
    stradd2(&fichier_c_contenu, "  indice_automate_ayant_reconnu_le_plus_long_prefixe = -1;\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  for (int j = 0; mot[j] != '\\0'; j++) {\n");
    stradd2(&fichier_c_contenu, "    lettre = mot[j];\n");
    stradd2(&fichier_c_contenu, "    {\n");
    for (int i = 0; i < nb; i++) {
      //stradd2(&fichier_c_contenu, "      etat_courant[0] = lexeme_commentaire_multiligne_etat_suivant_get(etat_courant[0], lettre);\n");
      stradd8(&fichier_c_contenu, "      etat_courant[", int_string(i), "] = ", automaton_fun_etat_etat_suivant_get_name[i], "(etat_courant[", int_string(i),"], lettre);\n");
    }
    stradd2(&fichier_c_contenu, "    }\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "    {\n");
    for (int i = 0; i < nb; i++) {
      //stradd2(&fichier_c_contenu, "      if (lexeme_commentaire_multiligne_etat_final_huh(etat_courant[0])) {\n");
      //stradd2(&fichier_c_contenu, "        indice_automate_ayant_reconnu_le_plus_long_prefixe = 0;\n");
      //stradd2(&fichier_c_contenu, "        *longueur_du_plus_long_prefixe_reconnu_ptr = j+1;\n");
      //stradd2(&fichier_c_contenu, "      }\n");
      stradd6(&fichier_c_contenu, "      if (", automaton_fun_etat_final_huh_name[i], "(etat_courant[", int_string(i), "])) {\n");
      stradd4(&fichier_c_contenu, "        indice_automate_ayant_reconnu_le_plus_long_prefixe = ", int_string(i),";\n");
      stradd2(&fichier_c_contenu, "        *longueur_du_plus_long_prefixe_reconnu_ptr = j+1;\n");
      stradd2(&fichier_c_contenu, "      }\n");
    }
    stradd2(&fichier_c_contenu, "    }\n");
    stradd2(&fichier_c_contenu, "    \n");
    stradd2(&fichier_c_contenu, "    int tous_les_automates_sont_bloques_huh = (0 == 0);\n");
    stradd2(&fichier_c_contenu, "    {\n");
    for (int i = 0; i < nb; i++) {
      //stradd2(&fichier_c_contenu, "      tous_les_automates_sont_bloques_huh &= lexeme_commentaire_multiligne_etat_puits_huh(etat_courant[0]);\n");
      stradd6(&fichier_c_contenu, "      tous_les_automates_sont_bloques_huh &= ", automaton_fun_etat_puits_huh_name[i], "(etat_courant[", int_string(i), "]);\n");
    }
    stradd2(&fichier_c_contenu, "    }\n");
    stradd2(&fichier_c_contenu, "    \n");
    stradd2(&fichier_c_contenu, "    \n");
    stradd2(&fichier_c_contenu, "    if (tous_les_automates_sont_bloques_huh) break;\n");
    stradd2(&fichier_c_contenu, "  }\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  if (-1 == indice_automate_ayant_reconnu_le_plus_long_prefixe) {\n");
    stradd2(&fichier_c_contenu, "    return (0 != 0);\n");
    stradd2(&fichier_c_contenu, "  }\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd4(&fichier_c_contenu, "  ", enum_type_name, " type;\n");
    stradd2(&fichier_c_contenu, "  switch (indice_automate_ayant_reconnu_le_plus_long_prefixe) {\n");
    stradd2(&fichier_c_contenu, "    default: assert(0 != 0); break;\n");
    for (int i = 0; i < nb; i++) {
      //stradd10(&fichier_c_contenu, "    case ", type_nom_sans_t_upper, "_", enum_name[i], ": return ", type_nom_sans_t_upper, "_", enum_name[i], "; break;\n");
      stradd6(&fichier_c_contenu, "    case ", int_string(i), ": type = ", strupper(enum_name[i]), "; break;\n");
    }
    stradd2(&fichier_c_contenu, "  };\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  *type_ptr = type;\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  return (0 == 0);\n");
    stradd2(&fichier_c_contenu, "}\n");
    
#endif
    
    
    
    
  }
  
  *h_code = fichier_h_contenu;
  *c_code = fichier_c_contenu;
}







void generation_code_c_pour_la_fonction_principale(const char * prepend_string, const int nb, str_t * * enum_basename, char * * h_code, char * * c_code) {
  assert(prepend_string != NULL);
  assert(nb >= 0);
  assert(enum_basename != NULL);
  assert(h_code != NULL);
  assert(c_code != NULL);
  
  char * fichier_h_contenu = NULL;
  char * fichier_c_contenu = NULL;
  
  str_t * local_base_name;
  local_base_name = strcopy(prepend_string);

  str_t * token_liste_type_name = NULL;
  token_liste_type_name = strlower(strconcat(prepend_string, "_token_liste_t"));
  
  
  // ***************************************
  // Generation du fichier H
  {
    fichier_h_contenu = strcopy("");
    
    stradd2(&fichier_h_contenu, "\n");
    stradd2(&fichier_h_contenu, "\n");
    stradd4(&fichier_h_contenu, "extern ", token_liste_type_name, " * analyse_de_la_ligne(const char * mot, int * nb_lettres_qui_ont_ete_reconnues_ptr);\n");
    stradd2(&fichier_h_contenu, "\n");
    stradd2(&fichier_h_contenu, "\n");
  }
  
  
  // ***************************************
  // Generation du fichier C
  {
    fichier_c_contenu = strcopy("");
    
    stradd2(&fichier_c_contenu, "\n");
    stradd2(&fichier_c_contenu, "\n");
    
    {
      char * lib_code_c = NULL;
      lib_code_c = generation_code_c_pour_la_lib(local_base_name);
      stradd2(&fichier_c_contenu, lib_code_c);
    }

    stradd2(&fichier_c_contenu, "\n");
    //stradd4(&fichier_c_contenu, "static ", token_liste_type_name, " * analyse_de_la_ligne(const char * mot, int * nb_lettres_qui_ont_ete_reconnues_ptr);\n");
    stradd2(&fichier_c_contenu, "\n");
    stradd4(&fichier_c_contenu, "", token_liste_type_name, " * analyse_de_la_ligne(const char * mot, int * nb_lettres_qui_ont_ete_reconnues_ptr) {\n");
    stradd2(&fichier_c_contenu, "  int longueur_du_plus_long_prefixe_reconnu;\n");
    stradd2(&fichier_c_contenu, "  int plus_long_prefixe_reconnu_huh;\n");
    stradd2(&fichier_c_contenu, "  //int indice_de_l_automate_ayant_reconnu_le_plus_long_prefixe;\n");
    stradd4(&fichier_c_contenu, "  ", prepend_string, "_token_type_t type_du_le_plus_long_prefixe_reconnu;\n");
    stradd2(&fichier_c_contenu, "  int nb_lettres_deja_reconnues;\n");
    stradd4(&fichier_c_contenu, "  ", token_liste_type_name, " * tokens;\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd4(&fichier_c_contenu, "  tokens = ", prepend_string, "_token_liste_vide();\n");
    stradd2(&fichier_c_contenu, "  \n");
    //stradd2(&fichier_c_contenu, "  indice_de_l_automate_ayant_reconnu_le_plus_long_prefixe = -1;\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  for (nb_lettres_deja_reconnues = 0; mot[nb_lettres_deja_reconnues] != '\\0'; nb_lettres_deja_reconnues += longueur_du_plus_long_prefixe_reconnu) {\n");
    stradd2(&fichier_c_contenu, "    plus_long_prefixe_reconnu_huh = type_du_plus_long_prefixe_reconnu(&(mot[nb_lettres_deja_reconnues]), &type_du_le_plus_long_prefixe_reconnu, &longueur_du_plus_long_prefixe_reconnu);\n");
    stradd2(&fichier_c_contenu, "    \n");
    stradd2(&fichier_c_contenu, "    if (!(plus_long_prefixe_reconnu_huh)) {\n");
    stradd2(&fichier_c_contenu, "      break;\n");
    stradd2(&fichier_c_contenu, "    }\n");
    stradd2(&fichier_c_contenu, "    \n");
    stradd2(&fichier_c_contenu, "    {\n");
    stradd2(&fichier_c_contenu, "      char * lexeme = NULL;\n");
    //stradd2(&fichier_c_contenu, "      lexer_min_token_type_t t;\n");
    stradd4(&fichier_c_contenu, "      ", prepend_string, "_token_t * token;\n");
    //stradd2(&fichier_c_contenu, "      lexeme = substring(mot, nb_lettres_deja_reconnues, nb_lettres_deja_reconnues + longueur_du_plus_long_prefixe_reconnu);\n");
    stradd4(&fichier_c_contenu, "      lexeme = ", local_base_name, "_substring(mot, nb_lettres_deja_reconnues, nb_lettres_deja_reconnues + longueur_du_plus_long_prefixe_reconnu);\n");
    //stradd2(&fichier_c_contenu, "      t = lexer_min_token_type_make(indice_de_l_automate_ayant_reconnu_le_plus_long_prefixe);\n");
    stradd4(&fichier_c_contenu, "      token = ", prepend_string, "_token_make_nocopy(type_du_le_plus_long_prefixe_reconnu, lexeme);\n");
    stradd4(&fichier_c_contenu, "      tokens = ", prepend_string, "_token_liste_cons(token, tokens);\n");
    stradd2(&fichier_c_contenu, "    }\n");
    stradd2(&fichier_c_contenu, "  }\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd4(&fichier_c_contenu, "  ", prepend_string, "_token_liste_reverse_surplace(&tokens);\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  *nb_lettres_qui_ont_ete_reconnues_ptr = nb_lettres_deja_reconnues;\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  return tokens;\n");
    stradd2(&fichier_c_contenu, "}\n");
    stradd2(&fichier_c_contenu, "\n");
    stradd2(&fichier_c_contenu, "\n");
    

    
  }
  
  

  
  *h_code = fichier_h_contenu;
  *c_code = fichier_c_contenu;
}








void generation_code_c_pour_la_fonction_readline(const char * prepend_string, char * * h_code, char * * c_code) {
  assert(prepend_string != NULL);
  assert(h_code != NULL);
  assert(c_code != NULL);
  
  char * fichier_h_contenu = NULL;
  char * fichier_c_contenu = NULL;
  
  
  // ***************************************
  // Generation du fichier H
  {
    fichier_h_contenu = strcopy("");
    
    stradd2(&fichier_h_contenu, "\n\n");
    stradd2(&fichier_h_contenu, "\n\n");
  }
  
  
  // ***************************************
  // Generation du fichier C
  {
    fichier_c_contenu = strcopy("");
    
    stradd2(&fichier_c_contenu, "\n\n");

#if 0
    {
      char * lib_code_c = NULL;
      lib_code_c = generation_code_c_pour_la_lib(local_base_name);
      stradd2(&fichier_c_contenu, lib_code_c);
    }
#endif

    stradd2(&fichier_c_contenu, "\n\n");
    stradd2(&fichier_c_contenu, "#include <strings.h>\n");
    stradd2(&fichier_c_contenu, "\n\n");
    stradd4(&fichier_c_contenu, "static char * ", prepend_string, "_readline(void);\n");
    stradd2(&fichier_c_contenu, "\n\n");
    stradd4(&fichier_c_contenu, "char * ", prepend_string, "_readline(void) {\n");
    stradd2(&fichier_c_contenu, "  char buffer[1024];\n");
    stradd2(&fichier_c_contenu, "  {\n");
    stradd2(&fichier_c_contenu, "    bzero(buffer, 1024 * (sizeof(char)));\n");
    stradd2(&fichier_c_contenu, "    for (int i = 0; i < 1024; i++) {\n");
    stradd2(&fichier_c_contenu, "      size_t nb_read;\n");
    stradd2(&fichier_c_contenu, "      nb_read = fread(&(buffer[i]), 1, 1, stdin);\n");
    stradd2(&fichier_c_contenu, "      if (buffer[i] == '\\n') break;\n");
    stradd2(&fichier_c_contenu, "    }\n");
    stradd2(&fichier_c_contenu, "  }\n");
    stradd2(&fichier_c_contenu, "  char * retour;\n");
    stradd2(&fichier_c_contenu, "  {\n");
    stradd2(&fichier_c_contenu, "    const size_t len = strlen(buffer);\n");
    stradd2(&fichier_c_contenu, "    const size_t len_octet = (len+1) * (sizeof(char));\n");
    stradd2(&fichier_c_contenu, "    retour = (char *) malloc(len_octet);\n");
    stradd2(&fichier_c_contenu, "    memcpy(retour, buffer, len_octet);\n");
    stradd2(&fichier_c_contenu, "  }\n");
    stradd2(&fichier_c_contenu, "  return retour;\n");
    stradd2(&fichier_c_contenu, "}\n");
    stradd2(&fichier_c_contenu, "\n\n");
    
  }
  
  *h_code = fichier_h_contenu;
  *c_code = fichier_c_contenu;
}







void generation_code_c_pour_la_fonction_readevalprintloop(const char * prepend_string, char * * h_code, char * * c_code) {
  assert(prepend_string != NULL);
  assert(h_code != NULL);
  assert(c_code != NULL);
  
  char * fichier_h_contenu = NULL;
  char * fichier_c_contenu = NULL;
    
  
  // ***************************************
  // Generation du fichier H
  {
    fichier_h_contenu = strcopy("");
    
    stradd2(&fichier_h_contenu, "\n\n");
    stradd2(&fichier_h_contenu, "\n\n");
  }
  
  
  // ***************************************
  // Generation du fichier C
  {
    fichier_c_contenu = strcopy("");
    
    stradd2(&fichier_c_contenu, "\n\n");

#if 0
    {
      char * lib_code_c = NULL;
      lib_code_c = generation_code_c_pour_la_lib(local_base_name);
      stradd2(&fichier_c_contenu, lib_code_c);
    }
#endif
    
    stradd2(&fichier_c_contenu, "\n\n");
    stradd2(&fichier_c_contenu, "#include <string.h>\n");
    stradd2(&fichier_c_contenu, "\n\n");
    stradd4(&fichier_c_contenu, "static void ", prepend_string, "_read_eval_print_loop(void);\n");
    stradd2(&fichier_c_contenu, "\n");
    stradd4(&fichier_c_contenu, "void ", prepend_string, "_read_eval_print_loop(void) {\n");
    stradd2(&fichier_c_contenu, "  char * mot;\n");
    stradd2(&fichier_c_contenu, "  const char * prompt = \"> \";\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  printf(\"Starting read-eval-print loop (type 'quit', 'exit', 'bye', or 'stop' to quit).\\n\");\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  for (;;) {\n");
    stradd2(&fichier_c_contenu, "    printf(\"%s\", prompt);\n");
    stradd4(&fichier_c_contenu, "    mot = ", prepend_string, "_readline();\n");
    stradd2(&fichier_c_contenu, "    \n");
    stradd2(&fichier_c_contenu, "    {\n");
    stradd2(&fichier_c_contenu, "      int quit_huh;\n");
    stradd2(&fichier_c_contenu, "      quit_huh = (0 != 0); \n");
    stradd2(&fichier_c_contenu, "      quit_huh |= (0 == strcmp(mot, \"\"));\n");
    stradd2(&fichier_c_contenu, "      quit_huh |= (0 == strcmp(mot, \"quit\\n\"));\n");
    stradd2(&fichier_c_contenu, "      quit_huh |= (0 == strcmp(mot, \"bye\\n\"));\n");
    stradd2(&fichier_c_contenu, "      quit_huh |= (0 == strcmp(mot, \"exit\\n\"));\n");
    stradd2(&fichier_c_contenu, "      quit_huh |= (0 == strcmp(mot, \"stop\\n\"));\n");
    stradd2(&fichier_c_contenu, "      quit_huh |= (0 == strcmp(mot, \"quit\"));\n");
    stradd2(&fichier_c_contenu, "      quit_huh |= (0 == strcmp(mot, \"bye\"));\n");
    stradd2(&fichier_c_contenu, "      quit_huh |= (0 == strcmp(mot, \"exit\"));\n");
    stradd2(&fichier_c_contenu, "      quit_huh |= (0 == strcmp(mot, \"stop\"));\n");
    stradd2(&fichier_c_contenu, "      if (quit_huh) break;\n");
    stradd2(&fichier_c_contenu, "    }\n");
    stradd2(&fichier_c_contenu, "    \n");
    stradd4(&fichier_c_contenu, "    ", prepend_string, "_token_liste_t * tokens = NULL;\n");
    stradd2(&fichier_c_contenu, "    int nb_lettres_qui_ont_ete_reconnues = -1;\n");
    stradd2(&fichier_c_contenu, "    tokens = analyse_de_la_ligne(mot, &nb_lettres_qui_ont_ete_reconnues);\n");
    stradd4(&fichier_c_contenu, "    printf(\"%s\\n\", ", prepend_string, "_token_liste_string(tokens));\n");
    stradd2(&fichier_c_contenu, "    \n");
    stradd2(&fichier_c_contenu, "    if (mot[nb_lettres_qui_ont_ete_reconnues] != '\\0') {\n");
    //stradd2(&fichier_c_contenu, "      fputs(\"\\n\", stdout);\n");
    stradd2(&fichier_c_contenu, "      fputs(\"Unfortunately, there were letters on the line that were recognized: '\", stdout);\n");
    stradd2(&fichier_c_contenu, "      fputs(&mot[nb_lettres_qui_ont_ete_reconnues], stdout);\n");
    stradd2(&fichier_c_contenu, "      fputs(\"'.\", stdout);\n");
    stradd2(&fichier_c_contenu, "      fputs(\"\\n\", stdout);\n");
    stradd2(&fichier_c_contenu, "    }\n");
    stradd2(&fichier_c_contenu, "    \n");
    stradd2(&fichier_c_contenu, "  }\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  printf(\"Bye!\\n\");\n");
    stradd2(&fichier_c_contenu, "}\n");
    stradd2(&fichier_c_contenu, "\n");
    
  }
  
  *h_code = fichier_h_contenu;
  *c_code = fichier_c_contenu;
}






void generation_code_c_pour_la_fonction_main(const char * prepend_string, const char * conditional_directive_name, const int nb, const str_tableau_t * lignes, const bool * ligne_vide_huh, char * * h_code, char * * c_code) {
  assert(prepend_string != NULL);
  assert(h_code != NULL);
  assert(c_code != NULL);
  
  char * fichier_h_contenu = NULL;
  char * fichier_c_contenu = NULL;
  
  // ***************************************
  // Generation du fichier H
  {
    fichier_h_contenu = strcopy("");
    
    stradd2(&fichier_h_contenu, "\n\n");
    stradd2(&fichier_h_contenu, "\n\n");
  }
  
  
  // ***************************************
  // Generation du fichier C
  {
    fichier_c_contenu = strcopy("");
    
    stradd2(&fichier_c_contenu, "\n");
    stradd2(&fichier_c_contenu, "\n");
    stradd4(&fichier_c_contenu, "#ifdef ", conditional_directive_name,"\n");
    stradd2(&fichier_c_contenu, "\n");
    stradd2(&fichier_c_contenu, "\n");
    stradd2(&fichier_c_contenu, "int main(int argc, char * argv[]) {\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  printf(\"Hello! I will try to match the text you type with the following regular expressions:\\n\");\n");
    for (int i = 0; i < nb; i++) {
      if (not(ligne_vide_huh[i])) {
	//char * string_replace(const char * text, const char c, const char * str);
	stradd4(&fichier_c_contenu, "  printf(\"\\t%s\\n\", \"", string_replace(string_replace(lignes -> tab[i], '\\', "\\\\"), '"', "\\\""), "\");\n");
      }
    }
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd4(&fichier_c_contenu, "  ", prepend_string, "_read_eval_print_loop();\n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  \n");
#ifdef WINDOWS_DEV_CPP
    stradd2(&fichier_c_contenu, "  system(\"pause\");\n");
#endif
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  \n");
    stradd2(&fichier_c_contenu, "  return 0;\n");
    stradd2(&fichier_c_contenu, "}\n");
    stradd2(&fichier_c_contenu, "\n");
    stradd2(&fichier_c_contenu, "\n");
    stradd4(&fichier_c_contenu, "#endif /* ", conditional_directive_name, " */ \n");
    stradd2(&fichier_c_contenu, "\n");
    stradd2(&fichier_c_contenu, "\n");
    stradd2(&fichier_c_contenu, "\n");
    
  }
  
  *h_code = fichier_h_contenu;
  *c_code = fichier_c_contenu;
}







