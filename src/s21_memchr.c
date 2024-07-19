#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *pstr = (unsigned char *)str;
  void *res = s21_NULL;
  for (s21_size_t i = 0; i < n; i++) {
    if (*pstr == (unsigned char)c) {
      res = pstr;
      break;
    }
    pstr++;
  }
  return res;
}