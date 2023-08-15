#ifndef ANIME_DATABASE_H
#define ANIME_DATABASE_H


extern const anime_t * anime_database__get(const char * filename); 
extern const anime_t * anime_database__load__compile_time(const char * filename); 


#endif 
