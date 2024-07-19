#ifndef S_21_STRING_H
#define S_21_STRING_H

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define s21_NULL ((void *)0)

typedef long unsigned s21_size_t;

void *s21_memcpy(void *dest, const void *src, s21_size_t n);
s21_size_t s21_strlen(const char *str);
char *s21_strcat(char *dest, const char *append);
char *s21_strncat(char *dest, const char *append, s21_size_t n);
char *s21_strchr(const char *str, int ch);
char *s21_strrchr(const char *str, int ch);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strtok(char *s, const char *delim);
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

typedef struct formatted_struct {
  int minus_flag;
  int plus_flag;
  int space_flag;
  int width;
  int prec;
  int is_prec;
  int length;
  int zero;
  int hash;
  int base;
  int upper_case;
  int flag_g;
  char spec;
} format_t;

int s21_sprintf(char *str, const char *format, ...);
int parse_format(const char **format, format_t *format_sprintf, va_list pa);
int is_spec(char ch);
void write_format(char **str, format_t *format_sprintf, va_list pa);
void process_c(char **str, format_t *format_sprintf, char sym);
void process_d(char **str, format_t *format_sprintf, va_list pa);
void process_u(char **str, format_t *format_sprintf, va_list pa);
void process_s(char **str, format_t *format_sprintf, va_list pa);
void process_p(char **str, format_t *format_sprintf, va_list pa);
void process_f(char **str, format_t *format_sprintf, va_list pa);
s21_size_t get_arr_size_d(format_t *format_sprintf, long int n);
s21_size_t get_arr_size_u(format_t *format_sprintf, unsigned long long n);
s21_size_t get_arr_size_f(format_t *format_sprintf, long double f);
void d_to_str(format_t *format_sprintf, long int n, char *str, s21_size_t size);
void u_to_str(format_t *format_sprintf, unsigned long long n, char *str,
              s21_size_t size);
void f_to_str(format_t *format_sprintf, long double n, char *str,
              s21_size_t size);
long double round_f(format_t *format_sprintf, long double f);
long double get_mantis(int *mantis, long double f);
void get_spec(format_t *format_sprintf, long double f);
int get_base(char ch);
s21_size_t num_of_digits_d(long int n, format_t *format_sprintf);
s21_size_t num_of_digits_u(unsigned long long n, format_t *format_sprintf);
s21_size_t num_of_digits_f(long double f, format_t *format_sprintf);
char get_char_by_num(long int n, int is_upper);

#endif