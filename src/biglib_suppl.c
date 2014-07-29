#include "global.h"
#include "biglib_suppl.h"




#include <fcntl.h>


void put_string_fdes(const char * string, const int fdes) {
  //write(stdout -> fd, buf, len);
  // ll /dev/std*
  // 2: stderr
  // 1: stdout
  // 0: stdin
  if (string == NULL) {
    const char buf[] = "(null)";
    const int len = strlen(buf);
    write(fdes, buf, len);
    return;
  }
  
  const int len = strlen(string);
  write(fdes, string, len);
}


void put_string(const char * string) {
  //write(stdout -> fd, buf, len);
  // ll /dev/std*
  // 2: stderr
  // 1: stdout
  // 0: stdin
  put_string_fdes(string, 1);
}


int int_max_brute(void) {
  static int int_max_save = -1;
  
  if (int_max_save != -1) 
    return int_max_save;
  
  int i;
  for (i = 0; i >= 0; i++);
  assert(i < 0);
  i--;
  assert(i >= 0);
  int_max_save = i;
  return i;
}


int int_max(void) {
  // TODO XXX use the ~ operator?
  static int int_max_save = -1;
  
  if (int_max_save != -1) 
    return int_max_save;

#if 0
  {
    const int int_size_in_bytes = sizeof(int);
    const int int_size_in_bits = 8*int_size_in_bytes;
    int acc;
    acc = 1;
    for (int i = 0; i < int_size_in_bits-1; i++) acc *= 2;
    assert(acc < 0);
    acc--;
    assert(acc >= 0);
    int_max_save = acc;
    return acc;
  }
#else
  {
    int i;
    for (i = 1; i >= 0; i *= 2);
    assert(i < 0);
    i--;
    assert(i >= 0);
    int_max_save = i;
    assert(int_max_save == (~0)); // I am just testing.
    assert(int_max_save == (~(1 << (sizeof (int))))); // I am just testing.
    return i;
  }
#endif
}



void put_int_fdes_old(const int n_given, const int fdes) {
  //write(stdout -> fd, buf, len);
  // ll /dev/std*
  // 2: stderr
  // 1: stdout
  // 0: stdin
  int n;
  n = n_given;

  if (n < 0) {
    write(fdes, "-", 1);
    n = -n;
  }
  
  const char int2ascii[] = "0123456789";

  // Naturally, the number is printed reversed.
  // So, first, we compute the size of the string representing the number.
  int len;
  len = 0;
  do {
    n /= 10;
    len++;
    
    // assert(len > 0);
    if (len <= 0) {
      // "Very bad error in put_int_string.\n";
      abort();
    }
  } while (n > 0);
  
  // Then, allocate the space to reverse.
  char buf[len+1];
  buf[len] = '\0';
  // Then we reset n.
  n = n_given;
  if (n < 0) n = -n;
  // Now pushing the bytes onto the stack.
  for (int i = 0; i < len; i++) {
    buf[len - i -1] = int2ascii[(n % 10)];
    n /= 10;
  }
  // assert(n == 0);
  if (n != 0) {
    // "Very bad error in put_int_string.\n";
    abort();
  }
  
  // Now printing.
  write(fdes, buf, len);
}

void put_int_fdes(const int n_given, const int fdes) {
  //write(stdout -> fd, buf, len);
  // ll /dev/std*
  // 2: stderr
  // 1: stdout
  // 0: stdin
  int n;
  n = n_given;

  if (n < 0) {
    write(fdes, "-", 1);
  }
  
  const char int2ascii[] = "0123456789";

  // Naturally, the number is printed reversed.
  // So, first, we compute the size of the string representing the number.
  int len;
  len = 0;
  do {
    n /= 10;
    len++;
    
    // assert(len > 0);
    if (len <= 0) {
      // "Very bad error in put_int_string.\n";
      abort();
    }
  } while (n != 0);
  
  // Then, allocate the space to reverse.
  char buf[len+1];
  buf[len] = '\0';
  // Then we reset n.
  n = n_given;
  // Now pushing the bytes onto the stack.
  for (int i = 0; i < len; i++) {
    const int q = (n / 10);
    //const int m = (n % 10);
    int m = (n - 10*q);
    if (m < 0) m = -m;
    buf[len - i -1] = int2ascii[m];
    n = q;
  }
  // assert(n == 0);
  if (n != 0) {
    // "Very bad error in put_int_string.\n";
    abort();
  }
  //abort();
  
  // Now printing.
  write(fdes, buf, len);
}

void put_uint64_fdes(const uint64_t n_given, const int fdes) {
  //write(stdout -> fd, buf, len);
  // ll /dev/std*
  // 2: stderr
  // 1: stdout
  // 0: stdin
  uint64_t n;
  n = n_given;

  const char int2ascii[] = "0123456789";

  // Naturally, the number is printed reversed.
  // So, first, we compute the size of the string representing the number.
  int len;
  len = 0;
  do {
    n /= 10;
    len++;
    
    // assert(len > 0);
    if (len <= 0) {
      // "Very bad error in put_int_string.\n";
      abort();
    }
  } while (n > 0);

  // Then, allocate the space to reverse.
  char buf[len+1];
  buf[len] = '\0';
  // Then we reset n.
  n = n_given;
  // Now pushing the bytes onto the stack.
  for (int i = 0; i < len; i++) {
    buf[len - i -1] = int2ascii[(n % 10)];
    n /= 10;
  }
  // assert(n == 0);
  if (n != 0) {
    // "Very bad error in put_int_string.\n";
    abort();
  }
  
  // Now printing.
  write(fdes, buf, len);
}

void put_int_stderr(const int n_given) {
  //write(stdout -> fd, buf, len);
  // ll /dev/std*
  // 2: stderr
  // 1: stdout
  // 0: stdin
  put_int_fdes(n_given, 2);
}

void put_int(const int n_given) {
  //write(stdout -> fd, buf, len);
  // ll /dev/std*
  // 2: stderr
  // 1: stdout
  // 0: stdin
  put_int_fdes(n_given, 1);
}

void put_uint64_stderr(const uint64_t n_given) {
  //write(stdout -> fd, buf, len);
  // ll /dev/std*
  // 2: stderr
  // 1: stdout
  // 0: stdin
  put_int_fdes(n_given, 2);
}

void put_uint64(const uint64_t n_given) {
  //write(stdout -> fd, buf, len);
  // ll /dev/std*
  // 2: stderr
  // 1: stdout
  // 0: stdin
  put_int_fdes(n_given, 1);
}





