#ifndef MAIN_H
#define MAIN_H

extern const char *  main_argv0; 
extern       int16_t main_argv0__bytesize; 
extern       char *  main_argv0__progname; // RL: INVARIANT: It should not hold any slash character '/'. 
extern       int16_t main_argv0__progname__bytesize; 
extern       char *  main_argv0__progdir; // RL: INVARIANT: The last char should be the slash character '/', unless it is root. 
extern       int16_t main_argv0__progdir__bytesize; 


#endif /* MAIN_H */

