#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  unsigned char *pstr = (unsigned char *)str;
  int length = 0;
  while (*pstr != 0) {
    length++;
    pstr++;
  }
  return length;
}