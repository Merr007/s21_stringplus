#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  const char *pstr1 = str1;
  const char *pstr2 = str2;
  int lengthStr1 = s21_strlen(pstr1);
  int lengthStr2 = s21_strlen(pstr2);
  if (lengthStr2 > 0) {
    for (int i = 0; i < lengthStr1; i++) {
      unsigned char *pstr2 = (unsigned char *)str2;
      for (int j = 0; j < lengthStr2; j++) {
        if (*pstr1 == *pstr2) {
          return (char *)pstr1;
        }
        pstr2++;
      }
      pstr1++;
    }
  }

  return s21_NULL;
}