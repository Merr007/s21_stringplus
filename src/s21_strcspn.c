#include "s21_string.h"

s21_size_t s21_strcspn(const char* str1, const char* str2) {
  const char* ptr1 = str1;
  const char* ptr2 = s21_NULL;

  for (; *ptr1 != '\0'; ++ptr1) {
    for (ptr2 = str2; *ptr2 != '\0'; ++ptr2) {
      if (*ptr1 == *ptr2) {
        return ptr1 - str1;
      }
    }
  }

  return ptr1 - str1;
}