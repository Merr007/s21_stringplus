#include "s21_string.h"

int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
  int nam = 0;
  char* man = (char*)str1 + n;
  while (nam == 0 && (*str1 || *str2) && str1 != man) {
    nam = (*str1++) - (*str2++);
  }
  return nam;
}