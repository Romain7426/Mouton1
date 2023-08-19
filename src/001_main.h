#ifndef MAIN_H
#define MAIN_H

#if 0 
extern const char *  main_argv0; 
extern       int16_t main_argv0__bytesize; 
extern       char *  main_argv0__progname; // RL: INVARIANT: It should not hold any slash character '/'. 
extern       int16_t main_argv0__progname__bytesize; 
extern       char *  main_argv0__progdir; // RL: INVARIANT: The last char should be the slash character '/', unless it is root. 
extern       int16_t main_argv0__progdir__bytesize; 
#endif 

extern void main__stdout_log_buffer__flush(void); 
extern void main__stderr_buffer__flush(void); 


#endif /* MAIN_H */

