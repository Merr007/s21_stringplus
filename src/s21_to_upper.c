#include "s21_string.h"

void *s21_to_upper(const char *str) {
  char *res_str = s21_NULL;
  if (str) {
    res_str = (char *)calloc(s21_strlen(str) + 1, sizeof(char));
    for (s21_size_t i = 0; i < s21_strlen(str); i++) {
      if (str[i] >= 'a' && str[i] <= 'z') {
        res_str[i] = str[i] - 32;
      } else {
        res_str[i] = str[i];
      }
    }
  }
  return (void *)res_str;
}