#include "s21_string.h"

char *s21_strcat(char *dest, const char *append) {
  s21_size_t last_ind = s21_strlen(dest);
  for (int i = 0; append[i] != '\0'; i++) {
    dest[last_ind] = append[i];
    last_ind++;
  }
  dest[last_ind] = '\0';
  return dest;
}