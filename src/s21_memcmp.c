#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  unsigned char *str_1 = (unsigned char *)str1;
  unsigned char *str_2 = (unsigned char *)str2;
  int result = 0;

  for (s21_size_t x = 0; result == 0 && str_1[x] != '\0' && x < n; x += 1)
    result = str_1[x] - str_2[x];

  return result;
}