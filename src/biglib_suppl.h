#ifndef BIGLIB_SUPPL_H
#define BIGLIB_SUPPL_H


#define string_size_for_n(n) ((sizeof((n)) << 3)+1)
#define intX_string_on_the_stack(n) glue3(int,sizeof((n)),_string_in_the_buffer)((n), string_size_for_n(n), char buffer[string_size_for_n(n)])
//#define int4_string_on_the_stack(n) int4_string_in_the_buffer((n), string_size_for_n(n), char buffer[string_size_for_n(n)])
//#define int4_string_on_the_stack(n) int4_string_in_the_buffer((n), string_size_for_n(n), (char []){char * buffer[string_size_for_n(n)];})
#define int4_string_on_the_stack(n) int4_string_in_the_buffer((n), string_size_for_n(n), alloca(sizeof(char) * (1+string_size_for_n(n))))

static char * int4_string_in_the_buffer(const int n_given, const int buffer_size, char * buffer) {
  if (n_given == 0) return strcpy(buffer, "0");
  
  int i = 0;
  int n = n_given;
  if (n < 0) {
    buffer[i] = '-';
    n = -n;
    i++;
  }
  assert(n > 0);
  while (n > 0) {
    const int quotient = n / 10;
    const int remainder = n % 10;
    buffer[i] = remainder + '0';
    i++;
    n = quotient;
  }
  buffer[i] = '\0';
  i++;
  const int size_computed = i;
  assert(size_computed <= buffer_size);
  
  char temp[size_computed];
  strcpy(temp, buffer);
  if (n_given < 0) buffer[0] = '-';
  for (int j = ((n_given < 0) ? 1 : 0); j < size_computed-1; j++)
    buffer[j] = temp[size_computed-(j-((n_given < 0) ? 1 : 0))-1-1];
  
  return buffer;
}



static char char_escape_str_2_char(const char * str) {
  const int len = strlen(str);
  assert(len == 4);
  assert(str[0] == '\'');
  assert(str[1] == '\\');
  assert(str[3] == '\'');
  char retour = -1;
  switch (str[2]) {
  case '0': retour = '\0'; break;
  case 'a': retour = '\a'; break;
  case 'b': retour = '\b'; break;
  case 't': retour = '\t'; break;
  case 'n': retour = '\n'; break;
  case 'v': retour = '\v'; break;
  case 'f': retour = '\f'; break;
  case 'r': retour = '\r'; break;
  case 'e': retour = '\e'; break;
  case '\\': retour = '\\'; break;
  case '"': retour = '"'; break;
  default: retour = str[2]; break;
  }
  return retour;
}




#define char_2_string__stack(c) (char_2_string__buffer((c), 2, (char *) alloca(2 * sizeof(char))))
static char * char_2_string__buffer(const char c, const int buffer_size, char * buffer) {
  assert(buffer_size > 2);
  buffer[0] = c;
  buffer[1] = '\0';
  return buffer;
}



// If a number 'm' is written with n1 figures in base b1,
// then it will need n2 = n1 * ln(b1) / ln(b2) figures to be written in base b2.
// When b1 is greater than b2, instead of computing ln(b1) / ln(b2), we use the 
// approximation b1/b2 (which is greater than ln(b1)/ln(b2) [except for 2 and 3]).
// (This is just a greater approximation. For instance, if a number is written with 21 figures in base 100, then it will be written with 42 figures in base 10, but the approximation 100/10 implies that 210 figures are needed to write the number in base 10. This is just an approximation and it is good enough [base 2, 8, 10, 16].)
// When b1 is lesser than b2, we just use the same number of figures.
// NB: if b1 is 2, then b2 should be greater than 4.
#define string_size_from_hex_to_dec(hex_len) (2*(hex_len)+1) // ln(16) / ln(10) = 1.20
#define int_string_hex_2_int_string_dec__stack(str_hex_given) (int_string_hex_2_int_string_dec__buffer((str_hex_given), string_size_from_hex_to_dec(strlen(str_hex_given)), (char *) alloca(strlen(str_hex_given) * (sizeof(char)))))
static char * int_string_hex_2_int_string_dec__buffer(const char * n_given, const int buffer_size, char * buffer) {
  assert(n_given != NULL);
  const int n_given_len = strlen(n_given);
  const int start = (n_given_len >= 2 && (n_given[1] == 'x' || n_given[1] == 'X')) ? 2 : 0;
  int hex_figures[n_given_len];
  bzero(hex_figures, n_given_len * sizeof(int));
  for (int i = start; i < n_given_len; i++) {
    if (n_given[i] >= '0' && n_given[i] <= '9') { hex_figures[i] = n_given[i] - '0'; continue; }
    if (n_given[i] >= 'A' && n_given[i] <= 'F') { hex_figures[i] = n_given[i] - 'A' + 10; continue; }
    if (n_given[i] >= 'a' && n_given[i] <= 'f') { hex_figures[i] = n_given[i] - 'a' + 10; continue; }
    assert(false);
  }
  const int len = n_given_len - start;
	  
  int base_exp_n[2*len];
  base_exp_n[0] = 1;
  int base_exp_n_len = 1;
  int base_exp_n_by_figure[2*len];
  int base_exp_n_by_figure_len = -1;
	  

  bzero(buffer, buffer_size);
  int computed_fig_nb_in_the_buffer = -1;
  for (int i = len-1; i >= 0; i--) {
    { // c * 16^n in base 10
      int carry = 0;
      for (int k = 0; k < base_exp_n_len; k++) {
	const int tmp = base_exp_n[k] * hex_figures[i] + carry;
	const int quotient = tmp / 10;
	const int remainder = tmp % 10;
	base_exp_n_by_figure[k] = remainder;
	carry = quotient;
      }
      base_exp_n_by_figure_len = base_exp_n_len;
      if (carry > 0) {
	assert(carry < 2);
	base_exp_n_by_figure[base_exp_n_len] = carry;
	base_exp_n_by_figure_len++;
      }
    }
    { // adding c*16^n to the current number computed
      assert(buffer_size > base_exp_n_by_figure_len);
      int carry = 0;
      int j = buffer_size-2;
      for (int k = 0; k < base_exp_n_by_figure_len; k++) {
	buffer[j] += base_exp_n_by_figure[k] + carry;
	if (buffer[j] >= 10) { carry = 1; buffer[j]--; }
	j--;
      }
      computed_fig_nb_in_the_buffer = base_exp_n_by_figure_len;
      if (carry > 0) {
	assert(carry < 2);
	buffer[j] = carry;
	computed_fig_nb_in_the_buffer++;
      }
    }
    { // computing 16^(n+1)
      int carry = 0;
      for (int k = 0; k < base_exp_n_len; k++) {
	const int tmp = base_exp_n[k] * 16 + carry;
	const int quotient = tmp / 10;
	const int remainder = tmp % 10;
	base_exp_n_by_figure[k] = remainder;
	carry = quotient;
      }
      base_exp_n_by_figure_len = base_exp_n_len;
      if (carry > 0) {
	assert(carry < 2);
	base_exp_n_by_figure[base_exp_n_len] = carry;
	base_exp_n_by_figure_len++;
      }
      for (int k = 0; k < base_exp_n_by_figure_len; k++) 
	base_exp_n[k] = base_exp_n_by_figure[k];
      base_exp_n_len = base_exp_n_by_figure_len;
    }
  }

  // Now we have to rebase at the start of the buffer.
  const int computed_size_of_the_buffer = computed_fig_nb_in_the_buffer+1;
  {
    const int shift = buffer_size - computed_size_of_the_buffer;
    assert(shift >= 0);
    for (int j = 0; j < computed_size_of_the_buffer-1; j++)
      buffer[j] = buffer[j + shift];
  }

  // Now we have just to add '0'
  for (int j = 0; j < computed_size_of_the_buffer-1; j++)
    buffer[j] += '0';

  // And the final '\0'
  buffer[computed_size_of_the_buffer-1] = '\0';

  return buffer;
}
      




extern void put_string_fdes(const char * string, const int fdes);
extern void put_string(const char * string);
extern int int_max_brute(void);
extern int int_max(void);
extern void put_int_fdes_old(const int n_given, const int fdes);
extern void put_int_fdes(const int n_given, const int fdes);
extern void put_uint64_fdes(const uint64_t n_given, const int fdes);
extern void put_int_stderr(const int n_given);
extern void put_int(const int n_given);
extern void put_uint64_stderr(const uint64_t n_given);
extern void put_uint64(const uint64_t n_given);





#endif /* BIGLIB_SUPPL_H */

