#ifndef READLINE_H
#define READLINE_H 

// RL: This is necessary as libedit & libtermcap break SDL. 
// RL: To circumvent that, these two functions should likely be loaded at runtime with 'dlopen'. 
 
extern char * readline(const char * prompt); 

extern void add_history(const char * line); 


#endif /* READLINE_H */ 
