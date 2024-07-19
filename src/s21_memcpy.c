#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *dest_buff = dest;
  const char *src_buff = src;
  for (s21_size_t i = 0; i < n; i++) {
    dest_buff[i] = src_buff[i];
  }

  return dest;
}
