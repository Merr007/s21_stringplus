#include "s21_string.h"

char *s21_strncat(char *dest, const char *append, s21_size_t n) {
  s21_size_t last_ind = s21_strlen(dest);
  for (s21_size_t i = 0; append[i] != '\0' && i < n; i++) {
    dest[last_ind] = append[i];
    last_ind++;
  }
  dest[last_ind] = '\0';
  return dest;
}