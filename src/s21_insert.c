#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res_str = s21_NULL;
  if (src && str && s21_strlen(src) >= start_index) {
    res_str =
        (char *)calloc(s21_strlen(src) + s21_strlen(str) + 1, sizeof(char));
    if (res_str) {
      s21_strncpy(res_str, src, start_index);
      *(res_str + start_index) = '\0';
      s21_strcat(res_str, str);
      s21_strcat(res_str, src + start_index);
    }
  }
  return (void *)res_str;
}