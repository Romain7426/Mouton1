#ifndef BIGLIB_RM_RECURSIVE_H
#define BIGLIB_RM_RECURSIVE_H

extern bool_t biglib_rm_recursive(const char * path, const int verbose_level);
extern bool_t path_is_file_huh(const char * path);
extern bool_t path_is_dir_huh(const char * path);

extern const char * path_type(const char * path);


#endif /* BIGLIB_RM_RECURSIVE_H */

