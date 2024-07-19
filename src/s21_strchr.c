#include "s21_string.h"

char *s21_strchr(const char *str, int ch) {
  char *sym = s21_NULL;
  int i = 0;
  for (; str[i] != '\0' && !(sym); i++) {
    if (str[i] == ch) sym = (char *)(str + i);
  }
  if (str[i] == '\0' && ch == '\0') sym = (char *)(str + i);
  return sym;
}