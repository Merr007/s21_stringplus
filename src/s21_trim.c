#include "s21_string.h"

s21_size_t s21_strespn(const char *str1, const char *str2);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *whiteSpase(char *src, char *trim_chars, int flag);

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = s21_NULL;
  if (src == s21_NULL && trim_chars == s21_NULL) {
    result = s21_NULL;
  } else if (trim_chars == s21_NULL) {
    result = whiteSpase((char *)src, (char *)trim_chars, 1);
  } else if (src != s21_NULL) {
    if (!s21_strlen(trim_chars)) {
      result = whiteSpase((char *)src, (char *)trim_chars, 1);
    } else {
      result = whiteSpase((char *)src, (char *)trim_chars, 0);
    }
  }
  return result;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t result = 0;
  int i = 0, j = 0;
  while (str1[i]) {
    while (str2[j]) {
      if (str1[i] == str2[j]) {
        break;
      }
      j++;
    }
    if (str1[i] != str2[j]) {
      break;
    }
    i++;
    j = 0;
  }
  result = i;
  return result;
}

char *whiteSpase(char *src, char *trim_chars, int flag) {
  s21_size_t size = s21_strlen(src), start_step = 0, end_step = 0;
  char *result = (char *)malloc((size + 1) * sizeof(char));
  if (flag) {
    char whitespase[] = {9, 10, 11, 12, 13, 32, '\0'};
    start_step = s21_strspn(src, whitespase);
    end_step = s21_strespn(src + start_step, whitespase);
    s21_strncpy(result, src + start_step, size - start_step - end_step);
  } else {
    start_step = s21_strspn(src, trim_chars);
    end_step = s21_strespn(src + start_step, trim_chars);
    s21_strncpy(result, src + start_step, size - start_step - end_step);
  }
  result[size - start_step - end_step] = 0;
  return result;
}

s21_size_t s21_strespn(const char *str1, const char *str2) {
  s21_size_t size = s21_strlen(str1);
  char *buf = (char *)malloc((size + 1) * sizeof(char));
  for (s21_size_t i = 0; i < size; i++) {
    buf[i] = str1[size - 1 - i];
  }
  buf[size] = 0;
  size = 0;
  size = s21_strspn(buf, str2);
  free(buf);
  return size;
}