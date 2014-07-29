#ifndef STRUCTURES_H
#define STRUCTURES_H


extern void structures_init(void);
extern void structures_end(void);



// *****************************************************************

struct nombre_t;
#ifndef __cplusplus
typedef struct nombre_t nombre_t;
#endif

struct nombre_tableau_t;
#ifndef __cplusplus
typedef struct nombre_tableau_t nombre_tableau_t;
#endif

struct nombre_liste_t;
#ifndef __cplusplus
typedef struct nombre_liste_t nombre_liste_t;
#endif

enum nombre_type_t;
#ifndef __cplusplus
typedef enum nombre_type_t nombre_type_t;
#endif

union nombre_valeur_t;
#ifndef __cplusplus
typedef union nombre_valeur_t nombre_valeur_t;
#endif  

struct chaine_t;
#ifndef __cplusplus
typedef struct chaine_t chaine_t;
#endif

enum input_state_t;
#ifndef __cplusplus
typedef enum input_state_t input_state_t;
#endif


#ifndef ENV_T
#define ENV_T
struct env_t;
#ifndef __cplusplus
typedef struct env_t env_t;
#endif /* __cplusplus */
#endif /* ENV_T */




enum syntax_tree_type_t;
typedef enum syntax_tree_type_t syntax_tree_type_t;

union syntax_tree_valeur_t;
typedef union syntax_tree_valeur_t syntax_tree_valeur_t;

struct syntax_tree_t;
typedef struct syntax_tree_t syntax_tree_t;

struct syntax_tree_tableau_t;
typedef struct syntax_tree_tableau_t syntax_tree_tableau_t;

struct syntax_tree_liste_t;
typedef struct syntax_tree_liste_t syntax_tree_liste_t;


enum semantic_tree_type_t;
typedef enum semantic_tree_type_t semantic_tree_type_t;

union semantic_tree_valeur_t;
typedef union semantic_tree_valeur_t semantic_tree_valeur_t;

struct semantic_tree_t;
typedef struct semantic_tree_t semantic_tree_t;

struct semantic_tree_tableau_t;
typedef struct semantic_tree_tableau_t semantic_tree_tableau_t;

struct semantic_tree_liste_t;
typedef struct semantic_tree_liste_t semantic_tree_liste_t;


typedef nombre_t * fonction0_t(void);
typedef nombre_t * fonction1_t(const nombre_t * nombre);
typedef nombre_t * fonction2_t(const nombre_t * nombre1, const nombre_t * nombre2);

struct answer_t;
#ifndef __cplusplus
typedef struct answer_t answer_t;
#endif

struct location_t;
#ifndef __cplusplus
typedef struct location_t location_t;
#endif


struct position_t;

struct position_t {
  unsigned int position;
  unsigned int ligne;
  unsigned int colonne;
};

#ifndef __cplusplus
typedef struct position_t position_t;
#endif

typedef enum token_type_t token_type_t;
typedef union token_valeur_t token_valeur_t;

struct token_t;  
#ifndef __cplusplus
typedef struct token_t token_t;
#endif


#ifndef TOKEN_LISTE_T
#define TOKEN_LISTE_T
struct token_liste_t {
  struct token_liste_t * cdr;
  token_t * car;
};
#ifndef __cplusplus
typedef struct token_liste_t token_liste_t;
#endif
#endif

struct lexer_state_t;
#ifndef __cplusplus
typedef struct lexer_state_t lexer_state_t;
#endif



#ifndef AUTOMATE_T
#define AUTOMATE_T
struct automate_t;
#ifndef __cplusplus
typedef struct automate_t automate_t;
#endif /* __cplusplus */
#endif /* AUTOMATE_T */


#ifndef ARBRE_T
#define ARBRE_T
struct arbre_t;
#ifndef __cplusplus
typedef struct arbre_t arbre_t;
#endif /* __cplusplus */
#endif /* ARBRE_T */


#ifndef ARBRE_LISTE_T
#define ARBRE_LISTE_T
struct arbre_liste_t {
  struct arbre_liste_t * cdr;
  arbre_t * car;
};
#ifndef __cplusplus
typedef struct arbre_liste_t arbre_liste_t;
#endif
#endif


#endif /* STRUCTURES_H */


