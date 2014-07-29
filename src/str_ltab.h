#ifndef STR_LTAB_H
#define STR_LTAB_H

#ifndef STR_LTAB_T
#define STR_LTAB_T
typedef str_t * str_ltab_t;
#endif


extern str_ltab_t * str_ltab_make(const unsigned int taille);

extern void str_ltab_free(str_ltab_t * a);
extern void str_ltab_free_nocopy(str_ltab_t * a);

extern unsigned int str_ltab_longueur(const str_ltab_t * a);

extern str_ltab_t * str_ltab_copy(const str_ltab_t * a);

extern char * str_ltab_string(const str_ltab_t * a);


extern bool str_ltab_equal(const str_ltab_t * array1, const str_ltab_t * array2); 

extern str_ltab_t * str_ltab_reverse(const str_ltab_t * a);

extern void str_ltab_reverse_surplace(str_ltab_t * array); 

extern str_ltab_t * str_ltab_append(const str_ltab_t * array1, const str_ltab_t * array2);
extern str_ltab_t * str_ltab_append_nocopy(str_ltab_t * array1, str_ltab_t * array2);


extern bool str_ltab_member_huh(const str_t * a, const str_ltab_t * array);


extern str_ltab_t * str_ltab_map(str_t * (* f)(const str_t *), const str_ltab_t * a);

extern str_t * str_ltab_fold(str_t * (* f)(const str_t *, const str_t *), const str_t * a, const str_ltab_t * array);


extern uint_t str_ltab_count(const str_t * a, const str_ltab_t * array);



#endif /* STR_LTAB_H */
