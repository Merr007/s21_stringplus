
#include <check.h>
#include <string.h>

#include "s21_string.h"

#define size 512
#define BUFF_SIZE 512

char str_1[size] = {'\0'}, str_2[size] = {'\0'};
int int_test1 = 0, int_test2 = 0;
int n = 2100, n1 = 0, n2 = -21;
long int lg = 12345678912345, lg1 = -12345678912345;
short sh = 123, sh1 = -123;
void free_two(char *arr_1, char *arr_2) {
  int len_1 = sizeof(arr_1);
  int len_2 = sizeof(arr_2);

  if (len_1 < len_2) len_1 = len_2;

  for (int i = 0; i < len_1; i++) {
    arr_1[i] = '\0';
    arr_2[i] = '\0';
  }
}
char char_test1 = 'T', char_test2 = 'Z';

START_TEST(test_s21_memchr) {
  char src1_def[15] = "1234567890";
  char src1_s21[15] = "1234567890";
  ck_assert_str_eq(memchr(src1_def, '4', 10), s21_memchr(src1_s21, '4', 10));

  char str1[10] = "Hello";
  ck_assert_mem_eq(s21_memchr(str1, 'H', 5), memchr(str1, 'H', 5), 5);

  char str2[10] = "Hellosdsfq";
  ck_assert_mem_eq(s21_memchr(str2, 'l', 0), memchr(str2, 'l', 0), 0);
}
END_TEST

START_TEST(test_s21_memcmp) {
  char src3[15] = "12345678901";
  char dst3[15] = "werwe";
  ck_assert_msg(memcmp(src3, dst3, 15) <= 0 && s21_memcmp(src3, dst3, 15) <= 0,
                "No");

  char src4[15] = "erteterteqwe";
  char dst4[15] = "erteterte";
  ck_assert_msg(memcmp(src4, dst4, 15) >= 0 && s21_memcmp(src4, dst4, 15) >= 0,
                "No");
}
END_TEST

START_TEST(test_s21_memcpy) {
  char str1_def[80], str1_s21[80], str1_text[] = "123456";
  memcpy(str1_def, str1_text, 7);
  s21_memcpy(str1_s21, str1_text, 7);
  ck_assert_str_eq(str1_def, str1_s21);

  char str2_def[] = "aaaaaaaaaaaaaaaaaaaaaaaaa";
  char str2_s21[] = "aaaaaaaaaaaaaaaaaaaaaaaaa";
  char str2_text[] = "Hello, I am from America.";
  memcpy(str2_def, str2_text, 10);
  s21_memcpy(str2_s21, str2_text, 10);
  ck_assert_str_eq(str2_def, str2_s21);
}
END_TEST

START_TEST(test_s21_memset) {
  unsigned char src1[15] = "1234567890";
  unsigned char src2[15] = "1234567890";
  ck_assert_str_eq(memset(src1, '1', 10), s21_memset(src2, '1', 10));

  unsigned char src3[25] = "gergeebdjnyjtykxhdurnr";
  unsigned char src4[25] = "gergeebdjnyjtykxhdurnr";
  ck_assert_str_eq(memset(src3, '1', 20), s21_memset(src4, '1', 20));
}
END_TEST

START_TEST(test_s21_strlen) {
  char str1[11] = "0123456789";
  ck_assert_int_eq(strlen(str1), s21_strlen(str1));

  char str2[12] = "";
  ck_assert_int_eq(strlen(str2), s21_strlen(str2));

  char str3[12] = "\n";
  ck_assert_int_eq(strlen(str3), s21_strlen(str3));
}
END_TEST

START_TEST(test_s21_strcat) {
  char app1[1024] = "вторая строка123";
  char dst1[1024] = "первая строка5555";
  char dst2[1024] = "первая строка5555";
  ck_assert_str_eq(strcat(dst1, app1), s21_strcat(dst2, app1));

  char app2[1024] = "вторая строка123";
  char dst3[1024] = "";
  char dst4[1024] = "";
  ck_assert_str_eq(strcat(dst3, app2), s21_strcat(dst4, app2));

  char app3[1024] = "";
  char dst5[1024] = "первая строка5555";
  char dst6[1024] = "первая строка5555";
  ck_assert_str_eq(strcat(dst5, app3), s21_strcat(dst6, app3));
}
END_TEST
START_TEST(STRCATTest1) {
  char app[1024] = "вторая строка ";
  char dst[1024] = "первая строка ";
  ck_assert_str_eq(s21_strcat(dst, app), strcat(dst, app));
}
END_TEST
START_TEST(STRCATTest2) {
  char app[1024] = " ";
  char dst[1024] = "   ";
  ck_assert_str_eq(s21_strcat(dst, app), strcat(dst, app));
}
END_TEST
START_TEST(STRCATTest3) {
  char app[1024] = "s s d";
  char dst[1024] = " s  s  s  sd aff   ";
  ck_assert_str_eq(s21_strcat(dst, app), strcat(dst, app));
}
END_TEST
START_TEST(STRCATTest4) {
  char app[1024] = "sdddadasdsa";
  char dst[1024] = "s                              ";
  ck_assert_str_eq(s21_strcat(dst, app), strcat(dst, app));
}
END_TEST
START_TEST(STRCATTest5) {
  char app[1024] = "\0";
  char dst[1024] = "\n\0";
  ck_assert_str_eq(s21_strcat(dst, app), strcat(dst, app));
}
END_TEST

START_TEST(test_s21_strncat) {
  char src1_def[10] = "000";
  char app1_def[10] = "12345";
  char src1_s21[10] = "000";
  char app1_s21[10] = "12345";
  ck_assert_str_eq(strncat(src1_def, app1_def, 3),
                   s21_strncat(src1_s21, app1_s21, 3));

  char src2_def[10] = "000";
  char app2_def[10] = "12345";
  char src2_s21[10] = "000";
  char app2_s21[10] = "12345";
  ck_assert_str_eq(strncat(src2_def, app2_def, 7),
                   s21_strncat(src2_s21, app2_s21, 7));
}
END_TEST

START_TEST(test_s21_strcspn) {
  char str[13] = "0123456789";
  char sym[10] = "9876";
  ck_assert_int_eq(strcspn(str, sym), s21_strcspn(str, sym));

  char str1[13] = "xyzbxz";
  char sym1[10] = "abc";
  ck_assert_int_eq(strcspn(str1, sym1), s21_strcspn(str1, sym1));

  char str2[13] = "xyzbxz";
  char sym2[10] = "xyzbxz";
  ck_assert_int_eq(strcspn(str2, sym2), s21_strcspn(str2, sym2));

  char str3[13] = "xyzbxz";
  char sym3[10] = "no match";
  ck_assert_int_eq(strcspn(str3, sym3), s21_strcspn(str3, sym3));

  char str4[13] = "xyzbxz";
  char sym4[10] = "";
  ck_assert_int_eq(strcspn(str4, sym4), s21_strcspn(str4, sym4));

  char str5[13] = "";
  char sym5[10] = "abc";
  ck_assert_int_eq(strcspn(str5, sym5), s21_strcspn(str5, sym5));

  char str6[13] = "";
  char sym6[10] = "";
  ck_assert_int_eq(strcspn(str6, sym6), s21_strcspn(str6, sym6));
}
END_TEST

START_TEST(test_s21_strpbrk) {
  char string[100] = "The 3 men and 2 boys ate 5 pigs\n";
  char *result = NULL;
  char *result_1 = NULL;
  ;
  result = strpbrk(string, "0123456789");
  result_1 = s21_strpbrk(string, "0123456789");
  ck_assert_str_eq(result, result_1);

  result = strpbrk(result, "0123456789");
  result_1 = s21_strpbrk(result_1, "0123456789");
  ck_assert_str_eq(result, result_1);

  result_1 = s21_strpbrk(result_1, "0123456789");
  result = strpbrk(result, "0123456789");
  ck_assert_str_eq(result, result_1);

  result_1 = s21_strpbrk(result_1, "9");
  result = strpbrk(result, "9");
  ck_assert_msg(result == NULL && result_1 == NULL, "Return not NULL");
}
END_TEST

START_TEST(test_s21_strchr) {
  char str1[11] = "23456789";
  int ch1 = '4';
  char *ach1_def;
  char *ach1_s21;
  ach1_def = strchr(str1, ch1);
  ach1_s21 = s21_strchr(str1, ch1);
  ck_assert_str_eq(ach1_def, ach1_s21);

  char str2[11] = "23456789";
  int ch2 = '1';
  char *ach2_def;
  char *ach2_s21;
  ach2_def = strchr(str2, ch2);
  ach2_s21 = s21_strchr(str2, ch2);
  ck_assert(ach2_def == ach2_s21);

  char str3[] = "Hello world";
  int ch = '\0';
  ck_assert_str_eq(s21_strchr(str3, ch), strchr(str3, ch));

  char str4[] = "";
  int ch12 = '\0';
  ck_assert_str_eq(s21_strchr(str4, ch12), strchr(str4, ch12));
}
END_TEST

START_TEST(test_s21_strncpy) {
  char src[] = "12345\0006789";
  char dst1[] = "aaaaaaaaaa";
  char dst2[] = "aaaaaaaaaa";
  char dst3[] = "aaaaaaaaaa";
  char dst4[] = "aaaaaaaaaa";
  ck_assert_str_eq(strncpy(dst1, src, 3), s21_strncpy(dst3, src, 3));
  ck_assert_str_eq(strncpy(dst2, src, 7), s21_strncpy(dst4, src, 7));
}
END_TEST

START_TEST(test_s21_strstr1) {
  char str1[] = "0123456789";
  char str2[] = "345";
  ck_assert_str_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST
START_TEST(test_s21_strstr2) {
  char str3[] = "0123456789";
  char str4[] = "256";
  char *istr3 = strstr(str3, str4);
  char *istr4 = s21_strstr(str3, str4);
  ck_assert_int_eq(istr3 - str3 + 1, istr4 - str3 + 1);

  char str1[10] = "hello";
  char str2[10] = "";
  ck_assert_msg(s21_strstr(str1, str2) == strstr(str1, str2), "failed");
}
END_TEST
START_TEST(test_s21_strstr3) {
  char str5[] = "hello";
  char str6[] = "";
  ck_assert_str_eq(s21_strstr(str5, str6), strstr(str5, str6));
}
END_TEST
START_TEST(STRSTRTest1) {
  char str1[10] = "hello";
  char str2[10] = "he";
  ck_assert_msg(s21_strstr(str1, str2) == strstr(str1, str2), "failed");
}
END_TEST
START_TEST(STRSTRTest3) {
  char str1[10] = "hello";
  char str2[10] = "qw";
  ck_assert_msg(s21_strstr(str1, str2) == strstr(str1, str2), "failed");
}
END_TEST
START_TEST(STRSTRTest4) {
  char str1[10] = "hello";
  char str2[10] = "hellp";
  ck_assert_msg(s21_strstr(str1, str2) == strstr(str1, str2), "failed");
}
END_TEST
START_TEST(STRSTRTest5) {
  char str1[1024] = "hello sweet hello";
  char str2[10] = "hello";
  ck_assert_msg(s21_strstr(str1, str2) == strstr(str1, str2), "failed");
}
END_TEST

START_TEST(test_s21_to_upper) {
  char str1[] = "adgreg";
  char *d1 = s21_to_upper(str1);
  ck_assert_str_eq(d1, "ADGREG");
  free(d1);

  char str2[] = "adg23/";
  char *d2 = s21_to_upper(str2);
  ck_assert_str_eq(d2, "ADG23/");
  free(d2);

  char str3[] = "";
  char *d3 = s21_to_upper(str3);
  ck_assert_str_eq(d3, "");
  free(d3);
}
END_TEST

START_TEST(test_s21_to_lower) {
  char str1[] = "ADGREG";
  char *d1 = s21_to_lower(str1);
  ck_assert_str_eq(d1, "adgreg");
  free(d1);

  char str2[] = "ADG23/";
  char *d2 = s21_to_lower(str2);
  ck_assert_str_eq(d2, "adg23/");
  free(d2);

  char str3[] = "";
  char *d3 = s21_to_lower(str3);
  ck_assert_str_eq(d3, "");
  free(d3);
}
END_TEST

START_TEST(test_s21_strrchr) {
  char str[] = "0163456769";
  int ch = '6';
  char *ach;
  char *ach2;
  ach = strrchr(str, ch);
  ach2 = s21_strrchr(str, ch);
  ck_assert_str_eq(ach, ach2);

  char str2[] = "erterterty";
  int ch2 = '6';
  char *ach3;
  char *ach4;
  ach3 = strrchr(str2, ch2);
  ach4 = s21_strrchr(str2, ch2);
  ck_assert(ach3 == ach4);

  char str1[] = "Hello";
  int c = 0;
  ck_assert_ptr_eq(s21_strrchr(str1, c), strrchr(str1, c));
}
END_TEST
START_TEST(STRRCHRTest1) {
  char str1[] = "Hello, Mel";
  int c = 'e';
  ck_assert_ptr_eq(s21_strrchr(str1, c), strrchr(str1, c));
}
END_TEST
START_TEST(STRRCHRTest2) {
  char str1[] = "Hello, Mel";
  int c = 'p';
  ck_assert_ptr_eq(s21_strrchr(str1, c), strrchr(str1, c));
}
END_TEST
START_TEST(STRRCHRTest3) {
  char str1[] = "";
  int c = 'l';
  ck_assert_ptr_eq(s21_strrchr(str1, c), strrchr(str1, c));
}
END_TEST
START_TEST(STRRCHRTest5) {
  char str1[] = "Hello";
  int c = 'o';
  ck_assert_ptr_eq(s21_strrchr(str1, c), strrchr(str1, c));
}
END_TEST

START_TEST(test_s21_strncmp) {
  char str1[16] = "1234567890";
  char str2[16] = "1234567890";
  ck_assert_int_eq(strncmp(str1, str2, 5), s21_strncmp(str1, str2, 5));

  char str3[16] = "1234567890";
  char str4[16] = "1334567890";
  ck_assert_int_eq(strncmp(str3, str4, 5), s21_strncmp(str3, str4, 5));

  char str9[10] = "1234567890";
  char str10[16] = "02";
  ck_assert_int_eq(strncmp(str9, str10, 0), s21_strncmp(str9, str10, 0));
}
END_TEST

START_TEST(test_s21_strtok) {
  char str1_def[] = "test1/test2/test3/test4";
  char str1_s21[] = "test1/test2/test3/test4";
  char sep1[] = "/";
  char *istr1_def;
  char *istr1_s21;
  istr1_def = strtok(str1_def, sep1);
  istr1_s21 = s21_strtok(str1_s21, sep1);
  ck_assert((istr1_def != NULL) && (istr1_s21 != NULL));
  while ((istr1_def != NULL) && (istr1_s21 != NULL)) {
    ck_assert_str_eq(istr1_def, istr1_s21);
    istr1_def = strtok(NULL, sep1);
    istr1_s21 = s21_strtok(NULL, sep1);
  }

  char *str2_def = NULL;
  char *str2_s21 = NULL;
  char sep2[] = "/";
  char *istr2_def;
  char *istr2_s21;
  istr2_def = strtok(str2_def, sep2);
  istr2_s21 = s21_strtok(str2_s21, sep2);
  ck_assert(istr2_def == NULL && istr2_s21 == NULL);

  char str3_def[] = "test1/test2/test3/test4";
  char str3_s21[] = "test1/test2/test3/test4";
  char sep3[] = "est";
  char *istr3_def;
  char *istr3_s21;
  istr3_def = strtok(str3_def, sep3);
  istr3_s21 = s21_strtok(str3_s21, sep3);
  ck_assert((istr3_def != NULL) && (istr3_s21 != NULL));
  while ((istr3_def != NULL) && (istr3_s21 != NULL)) {
    ck_assert_str_eq(istr3_def, istr3_s21);
    istr3_def = strtok(NULL, sep3);
    istr3_s21 = s21_strtok(NULL, sep3);
  }

  char str4_def[] = "test1/test2/test3/test4";
  char str4_s21[] = "test1/test2/test3/test4";
  char sep4[] = "ret";
  char *istr4_def;
  char *istr4_s21;
  istr4_def = strtok(str4_def, sep4);
  istr4_s21 = s21_strtok(str4_s21, sep4);
  ck_assert((istr4_def != NULL) && (istr4_s21 != NULL));
  while ((istr4_def != NULL) && (istr4_s21 != NULL)) {
    ck_assert_str_eq(istr4_def, istr4_s21);
    istr4_def = strtok(NULL, sep4);
    istr4_s21 = s21_strtok(NULL, sep4);
  }

  char str5_def[] = "test1/test2/test3/test4";
  char str5_s21[] = "test1/test2/test3/test4";
  char sep5[] = "";
  char *istr5_def;
  char *istr5_s21;
  istr5_def = strtok(str5_def, sep5);
  istr5_s21 = s21_strtok(str5_s21, sep5);
  ck_assert((istr5_def != NULL) && (istr5_s21 != NULL));
  while ((istr5_def != NULL) && (istr5_s21 != NULL)) {
    ck_assert_str_eq(istr5_def, istr5_s21);
    istr5_def = strtok(NULL, sep5);
    istr5_s21 = s21_strtok(NULL, sep5);
  }
}
END_TEST

START_TEST(test_s21_strtok_2) {
  char str2_def[] = "";
  char str2_s21[] = "";
  char sep2[] = "/";
  char *istr2_def;
  char *istr2_s21;
  istr2_def = strtok(str2_def, sep2);
  istr2_s21 = s21_strtok(str2_s21, sep2);
  ck_assert_msg(istr2_def == NULL && istr2_s21 == NULL, "Return not NULL");
}
END_TEST

START_TEST(INSERTTest1) {
  char str1[4] = "abc";
  char str2[5] = "1234";
  char *str3 = (char *)s21_insert(str1, str2, 2);
  ck_assert_str_eq(str3, "ab1234c");
  free(str3);
}
END_TEST
START_TEST(INSERTTest2) {
  char str1[1] = "";
  char str2[5] = "1234";
  char *str3 = (char *)s21_insert(str1, str2, 1);
  ck_assert_ptr_eq(str3, NULL);
  free(str3);
}
END_TEST
START_TEST(INSERTTest3) {
  char str1[2] = " ";
  char str2[5] = "1234";
  char *str3 = (char *)s21_insert(str1, str2, 1);
  ck_assert_str_eq(str3, " 1234");
  free(str3);
}
END_TEST
START_TEST(INSERTTest4) {
  char str1[4] = "abc";
  char str2[2] = " ";
  char *str3 = (char *)s21_insert(str1, str2, 2);
  ck_assert_str_eq(str3, "ab c");
  free(str3);
}
END_TEST
START_TEST(INSERTTest5) {
  char str1[4] = "abc";
  char str2[5] = "1234";
  char *str3 = (char *)s21_insert(str1, str2, -1);
  ck_assert_ptr_eq(str3, NULL);
  free(str3);
}
END_TEST
START_TEST(INSERTTest6) {
  char str1[4] = "abc";
  char str2[5] = "1234";
  char *str3 = (char *)s21_insert(str1, str2, 0);
  ck_assert_str_eq(str3, "1234abc");
  free(str3);
}
END_TEST
START_TEST(INSERTTest7) {
  char *str1 = NULL;
  char str2[5] = "1234";
  char *str3 = (char *)s21_insert(str1, str2, 0);
  ck_assert_ptr_eq(str3, NULL);
  free(str3);
}
END_TEST

START_TEST(test_s21_strerror) {
  for (int i = -1; i <= 130; i++) {
    char *str1;
    str1 = strerror(i);
    char *str2;
    str2 = s21_strerror(i);
    ck_assert_uint_eq((unsigned long)*str1, (unsigned long)*str2);
  }
}
END_TEST
START_TEST(strerror_test) {
  const char *ptr1 = s21_strerror(107);
  const char *ptr2 = strerror(107);
  char str1[256] = "";
  char str2[256] = "";
  for (int i = 0; ptr1[i] != '\0'; i++) {
    str1[i] = ptr1[i];
  }
  for (int i = 0; ptr2[i] != '\0'; i++) {
    str2[i] = ptr2[i];
  }
  ck_assert_str_eq(str1, str2);
  ck_assert_pstr_eq(s21_strerror(105), strerror(105));
  ck_assert_pstr_eq(s21_strerror(0), strerror(0));

  char delim[] = "l";
  char s_1[] = "leelaobblpppploooool";
  char s_2[] = "leelaobblpppploooool";
  ck_assert_pstr_eq(strtok(s_1, delim), s21_strtok(s_2, delim));
  for (int i = 0; i < 100; i++) {
    ck_assert_pstr_eq(strtok(NULL, delim), s21_strtok(NULL, delim));
  }

  const char delim1[] = ",";
  char input1[] = "Hello,World";
  char input_copy1[] = "Hello,World";
  char *result_s21_1 = s21_strtok(input_copy1, delim1);
  char *result_std_1 = strtok(input1, delim1);
  ck_assert_str_eq(result_s21_1, result_std_1);

  const char delim2[] = ",;";
  char input2[] = "apple,orange;banana";
  char input_copy2[] = "apple,orange;banana";
  char *result_s21_2 = s21_strtok(input_copy2, delim2);
  char *result_std_2 = strtok(input2, delim2);
  ck_assert_str_eq(result_s21_2, result_std_2);

  const char delim3[] = "-";
  char input3[] = "one--two--three";
  char input_copy3[] = "one--two--three";
  char *result_s21_3 = s21_strtok(input_copy3, delim3);
  char *result_std_3 = strtok(input3, delim3);
  ck_assert_str_eq(result_s21_3, result_std_3);

  const char delim4[] = ",";
  char input4[] = ",,apple,orange";
  char input_copy4[] = ",,apple,orange";
  char *result_s21_4 = s21_strtok(input_copy4, delim4);
  char *result_std_4 = strtok(input4, delim4);
  ck_assert_str_eq(result_s21_4, result_std_4);

  const char delim5[] = ",";
  char input5[] = "";
  char input_copy5[] = "";
  char *result_s21_5 = s21_strtok(input_copy5, delim5);
  char *result_std_5 = strtok(input5, delim5);
  ck_assert_ptr_eq(result_s21_5, result_std_5);

  const char delim6[] = ",";
  char *result_s21_6 = s21_strtok(NULL, delim6);
  char *result_std_6 = strtok(NULL, delim6);
  ck_assert_ptr_eq(result_s21_6, result_std_6);

  char input7[] = "A";
  char input_copy7[] = "A";
  char *result_s21_7 = s21_strtok(input_copy7, "\0");
  char *result_std_7 = strtok(input7, "\0");
  ck_assert_pstr_eq(result_s21_7, result_std_7);
}
END_TEST
START_TEST(s21_strerror_test) {
  char *test1 = s21_strerror(0);
  char *test2 = strerror(0);
  char *test3 = s21_strerror(106);
  char *test4 = strerror(106);
  char *test5 = s21_strerror(2147483647);
  char *test6 = strerror(2147483647);
  char *test7 = s21_strerror(-214748364);
  char *test8 = strerror(-214748364);
  ck_assert_uint_eq((unsigned long)*test1, (unsigned long)*test2);
  ck_assert_uint_eq((unsigned long)*test3, (unsigned long)*test4);
  ck_assert_uint_eq((unsigned long)*test5, (unsigned long)*test6);
  ck_assert_uint_eq((unsigned long)*test7, (unsigned long)*test8);
}
END_TEST

START_TEST(test_s21_trim) {
  char charsToTrim1[] = {'*', ' ', '\''};
  char banner1[] = "*** Much Ado About Nothing ***";
  char check1[] = "Much Ado About Nothing";
  char *result1;
  result1 = s21_trim(banner1, charsToTrim1);
  ck_assert_str_eq(result1, check1);
  free(result1);

  char charsToTrim2[] = {'*', ' ', '\''};
  char *banner2 = NULL;
  char *result2;
  char *check2 = NULL;
  result2 = s21_trim(banner2, charsToTrim2);
  ck_assert_msg(result2 == check2, "Return not NULL");
  free(result2);

  char *charsToTrim3 = NULL;
  char banner3[] = "*** Much Ado About Nothing ***";
  char *result3;
  char check3[] = "*** Much Ado About Nothing ***";
  result3 = s21_trim(banner3, charsToTrim3);
  ck_assert_str_eq(result3, check3);
  free(result3);

  char *charsToTrim4 = NULL;
  char banner4[] = "   *** Much Ado About Nothing ***   ";
  char *result4;
  char check4[] = "*** Much Ado About Nothing ***";
  result4 = s21_trim(banner4, charsToTrim4);
  ck_assert_str_eq(result4, check4);
  free(result4);
}
END_TEST

START_TEST(test_s21_sprintf_di_test1) {
  int iii = 12723;
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %-d", iii);
  sprintf(str2, "Hello %-d", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_di_test2) {
  int iii = -12723;
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %d", iii);
  sprintf(str2, "Hello %d", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_di_test3) {
  int iii = 12723;
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %.3d", iii);
  sprintf(str2, "Hello %.3d", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_di_test4) {
  int iii = -12346;
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %010d", iii);
  sprintf(str2, "Hello %010d", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_di_test5) {
  int iii = 123;
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %.d", iii);
  sprintf(str2, "Hello %.d", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_di_test6) {
  int iii = 0;
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %i", iii);
  sprintf(str2, "Hello %i", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_di_test7) {
  int iii = -1444;
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %+i", iii);
  sprintf(str2, "Hello %+i", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_di_test8) {
  int iii = 5421;
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %+3.i", iii);
  sprintf(str2, "Hello %+3.i", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_di_test9) {
  long int iii = 23568251976105;
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %ld", iii);
  sprintf(str2, "Hello %ld", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_di_test10) {
  long int iii = 21231231976105;
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %.12ld", iii);
  sprintf(str2, "Hello %.12ld", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_di_test11) {
  short iii = 21231;
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %.12hi", iii);
  sprintf(str2, "Hello %.12hi", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_di_test12) {
  short iii = 21231;
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %hd", iii);
  sprintf(str2, "Hello %hd", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s21_sprintf_c_test1) {
  char iii = '$';
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %c", iii);
  sprintf(str2, "Hello %c", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_c_test2) {
  char iii = '$';
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %-15c", iii);
  sprintf(str2, "Hello %-15c", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_c_test3) {
  char iii = '$';
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %6c", iii);
  sprintf(str2, "Hello %6c", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_s_test1) {
  char iii[] = "VASOS";
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %s", iii);
  sprintf(str2, "Hello %s", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_s_test2) {
  char iii[] = "VASOS";
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %7s", iii);
  sprintf(str2, "Hello %7s", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_s_test3) {
  char iii[] = "VASOS";
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %.4s", iii);
  sprintf(str2, "Hello %.4s", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_s_test4) {
  char fff[] = "uuuu";
  char outStr[100];
  s21_sprintf(outStr, "Hello %% %s world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %% %s world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_s_test5) {
  char fff[] = "uuuu";
  char outStr[100];
  s21_sprintf(outStr, "Hello %% %10s world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %% %10s world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_s_test6) {
  char fff[] = "uuuu";
  char outStr[100];
  s21_sprintf(outStr, "Hello %% %-10s world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %% %-10s world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_u_test1) {
  int iii = -14234;
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %-7.35u", iii);
  sprintf(str2, "Hello %-7.35u", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_u_test2) {
  int iii = 2314;
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %.u", iii);
  sprintf(str2, "Hello %.u", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_u_test3) {
  int iii = -31124;
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %-3u", iii);
  sprintf(str2, "Hello %-3u", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_u_test4) {
  int iii = 123;
  char outStr1[100];
  char *str1 = outStr1;
  char outStr2[100];
  char *str2 = outStr2;
  s21_sprintf(str1, "Hello %4.1u", iii);
  sprintf(str2, "Hello %4.1u", iii);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(test_s21_sprintf_float_1) {
  double fff = 127.56;
  char outStr[100];
  s21_sprintf(outStr, "Hello %f", fff);
  char str_check[100];
  sprintf(str_check, "Hello %f", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_2) {
  double fff = 127.56;
  char outStr[100];
  s21_sprintf(outStr, "Hello %f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_3) {
  double fff = -127.56;
  char outStr[100];
  s21_sprintf(outStr, "Hello %f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_4) {
  double fff = -9.099;
  char outStr[100];
  s21_sprintf(outStr, "Hello %+f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %+f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_5) {
  double fff = 127.56;
  char outStr[100];
  s21_sprintf(outStr, "Hello %+f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %+f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_6) {
  double fff = 127.56;
  char outStr[100];
  s21_sprintf(outStr, "Hello % f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello % f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_7) {
  double fff = -127.56;
  char outStr[100];
  s21_sprintf(outStr, "Hello % f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello % f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_8) {
  double fff = 127.56;
  char outStr[100];
  s21_sprintf(outStr, "Hello %.f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %.f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_9) {
  double fff = -127.56;
  char outStr[100];
  s21_sprintf(outStr, "Hello %.f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %.f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_10) {
  double fff = 127.468;
  char outStr[100];
  s21_sprintf(outStr, "Hello %.0f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %.0f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_11) {
  double fff = -127.468;
  char outStr[100];
  s21_sprintf(outStr, "Hello %.0f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %.0f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_12) {
  double fff = 127.468;
  char outStr[100];
  s21_sprintf(outStr, "Hello %.5f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %.5f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_13) {
  double fff = -127.468;
  char outStr[100];
  s21_sprintf(outStr, "Hello %.5f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %.5f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_14) {
  double fff = 0.468;
  char outStr[100];
  s21_sprintf(outStr, "Hello %.5f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %.5f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_15) {
  double fff = -0.468;
  char outStr[100];
  s21_sprintf(outStr, "Hello %.5f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %.5f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_16) {
  double fff = 0.468;
  char outStr[100];
  s21_sprintf(outStr, "Hello %.5f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %.5f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_17) {
  double fff = -0.468;
  char outStr[100];
  s21_sprintf(outStr, "Hello % .5f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello % .5f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_18) {
  double fff = 0.468;
  char outStr[100];
  s21_sprintf(outStr, "Hello %+.1f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %+.1f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_19) {
  double fff = -0.468;
  char outStr[100];
  s21_sprintf(outStr, "Hello %+.1f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %+.1f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_20) {
  double fff = 0.568;
  char outStr[100];
  s21_sprintf(outStr, "Hello %+.1f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %+.1f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_21) {
  double fff = -0.568;
  char outStr[100];
  s21_sprintf(outStr, "Hello %+.1f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %+.1f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_22) {
  double fff = 0.568;
  char outStr[100];
  s21_sprintf(outStr, "Hello %10.1f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %10.1f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_23) {
  double fff = -0.568;
  char outStr[100];
  char str_check[100];
  int res = s21_sprintf(outStr, "Hello %10.1f world!", fff);
  int res1 = sprintf(str_check, "Hello %10.1f world!", fff);
  ck_assert_str_eq(outStr, str_check);
  ck_assert_int_eq(res, res1);
}
END_TEST
START_TEST(test_s21_sprintf_float_24) {
  double fff = 0.568;
  char outStr[100];
  int res = s21_sprintf(outStr, "Hello %+10.1f world!", fff);
  char str_check[100];
  int res1 = sprintf(str_check, "Hello %+10.1f world!", fff);
  ck_assert_str_eq(outStr, str_check);
  ck_assert_int_eq(res, res1);
}
END_TEST
START_TEST(test_s21_sprintf_float_25) {
  double fff = -0.568;
  char outStr[100];
  s21_sprintf(outStr, "Hello %+10.1f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %+10.1f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_26) {
  double fff = 0.568;
  char outStr[100];
  s21_sprintf(outStr, "Hello %-10.1f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %-10.1f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_27) {
  double fff = -0.568;
  char outStr[100];
  s21_sprintf(outStr, "Hello %-10.1f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %-10.1f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_28) {
  double fff = 1.568;
  char outStr[100];
  s21_sprintf(outStr, "Hello %-10.1f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %-10.1f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_29) {
  double fff = -1.568;
  char outStr[100];
  s21_sprintf(outStr, "Hello %-10.1f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %-10.1f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_30) {
  double fff = 0.56823;
  char outStr[100];
  s21_sprintf(outStr, "Hello %-10.1f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %-10.1f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_31) {
  double fff = 0.56823;
  char outStr[100];
  s21_sprintf(outStr, "Hello %-3.1f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %-3.1f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_32) {
  double fff = 1.56823;
  char outStr[100];
  s21_sprintf(outStr, "Hello %-10.1f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %-10.1f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_33) {
  double fff = 1.568;
  char outStr[100];
  s21_sprintf(outStr, "Hello %-3.10f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %-3.10f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_34) {
  double fff = 1.56823;
  char outStr[100];
  s21_sprintf(outStr, "Hello % .1f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello % .1f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_35) {
  double fff = -1.5807;
  char outStr[100];
  s21_sprintf(outStr, "Hello % .10f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello % .10f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_36) {
  double fff = -9.0989;
  char outStr[100];
  s21_sprintf(outStr, "Hello %.*f world!", 10, fff);
  char str_check[100];
  sprintf(str_check, "Hello %.*f world!", 10, fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_37) {
  double fff = -1.56844;
  char outStr[100];
  s21_sprintf(outStr, "Hello %10f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %10f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_38) {
  double fff = -1.56823;
  char outStr[100];
  s21_sprintf(outStr, "Hello %10.f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %10.f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_39) {
  double fff = -1.56823;
  char outStr[100];
  s21_sprintf(outStr, "Hello %10.1f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %10.1f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_40) {
  double fff = 9.9999999;
  char outStr[100];
  s21_sprintf(outStr, "Hello %5f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %5f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_41) {
  double fff = 1.5;
  char outStr[100];
  s21_sprintf(outStr, "Hello %0.f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %0.f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_42) {
  double fff = 1.5;
  char outStr[100];
  s21_sprintf(outStr, "Hello %0.f world!", fff);
  char str_check[100];
  sprintf(str_check, "Hello %0.f world!", fff);
  ck_assert_str_eq(outStr, str_check);
}
END_TEST
START_TEST(test_s21_sprintf_float_43) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%f|\n", 324.34);
  sprintf(data1, "|%f|\n", 324.34);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_44) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%10f|\n", 324.343);
  sprintf(data1, "|%10f|\n", 324.343);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_45) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%10.3f|\n", 324.343);
  sprintf(data1, "|%10.3f|\n", 324.343);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_46) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "%1.9f", 324.343);
  sprintf(data1, "%1.9f", 324.343);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_47) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%-1.10f|\n", 324.343);
  sprintf(data1, "|%-1.10f|\n", 324.343);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_48) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%-1.10f|\n", -324.343);
  sprintf(data1, "|%-1.10f|\n", -324.343);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_49) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%.10f|\n", -324.343);
  sprintf(data1, "|%.10f|\n", -324.343);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_50) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%.10f|\n", 324.343);
  sprintf(data1, "|%.10f|\n", 324.343);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_51) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%10f|\n", 324.1);
  sprintf(data1, "|%10f|\n", 324.1);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_52) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%+10f|\n", 324.1);
  sprintf(data1, "|%+10f|\n", 324.1);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_53) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%#10f|\n", 324.1);
  sprintf(data1, "|%#10f|\n", 324.1);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_54) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%#10f|\n", 324.1123132);
  sprintf(data1, "|%#10f|\n", 324.1123132);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_56) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%.0f|\n", 324.1123132);
  sprintf(data1, "|%.0f|\n", 324.1123132);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_58) {
  //
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%10.10f|\n", 320.3);
  sprintf(data1, "|%10.10f|\n", 320.3);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_59) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%-10.10f|\n", 320.3);
  sprintf(data1, "|%-10.10f|\n", 320.3);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_60) {
  //
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%-10.10f|\n", 320.3);
  sprintf(data1, "|%-10.10f|\n", 320.3);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_61) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%-10.10f|\n", -320.3);
  sprintf(data1, "|%-10.10f|\n", -320.3);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_62) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%.0f|\n", -320.3);
  sprintf(data1, "|%.0f|\n", -320.3);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_63) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%.0f|\n", -320.3);
  sprintf(data1, "|%.0f|\n", -320.3);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_67) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|% -5.1f|\n", 0.001);
  sprintf(data1, "|% -5.1f|\n", 0.001);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_68) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%5.1f|\n", 324.324);
  sprintf(data1, "|%5.1f|\n", 324.324);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_69) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%5.3f|\n", 0.0001);
  sprintf(data1, "|%5.3f|\n", 0.0001);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_70) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%5.*f|\n", 10, 0.0001);
  sprintf(data1, "|%5.*f|\n", 10, 0.0001);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_71) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%5.*f|\n", -10, 0.0001);
  sprintf(data1, "|%5.*f|\n", -10, 0.0001);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_72) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%*.*f|\n", 23, -10, 0.0001);
  sprintf(data1, "|%*.*f|\n", 23, -10, 0.0001);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_73) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%*.*f|\n", -23, -10, 0.0001);
  sprintf(data1, "|%*.*f|\n", -23, -10, 0.0001);
  ck_assert_str_eq(data, data1);
}
END_TEST
START_TEST(test_s21_sprintf_float_74) {
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%*.*f|\n", 0, -10, 0.0001);
  sprintf(data1, "|%*.*f|\n", 0, -10, 0.0001);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(test_s21_sprintf_p) {
  s21_sprintf(str_1, "qwerty");
  sprintf(str_2, "qwerty");
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  void *p1 = (void *)0x123456789;
  void *p2 = (void *)4325234;
  void *p3 = (void *)0x123f324b;
  void *p4 = (void *)432520;

  int_test1 = sprintf(str_1, "%p", p1);
  int_test2 = s21_sprintf(str_2, "%p", p1);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  free_two(str_1, str_2);

  int_test1 = sprintf(str_1, "%20p", p2);
  int_test2 = s21_sprintf(str_2, "%20p", p2);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  free_two(str_1, str_2);

  int_test1 = sprintf(str_1, "%-15p", p3);
  int_test2 = s21_sprintf(str_2, "%-15p", p3);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  free_two(str_1, str_2);

  int_test1 = sprintf(str_1, "%10p", p4);
  int_test2 = s21_sprintf(str_2, "%10p", p4);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  free_two(str_1, str_2);

  int_test1 = sprintf(str_1, "%-15p", p2);
  int_test2 = s21_sprintf(str_2, "%-15p", p2);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  free_two(str_1, str_2);

  int_test1 = sprintf(str_1, "%*p", 10, p3);
  int_test2 = s21_sprintf(str_2, "%*p", 10, p3);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  free_two(str_1, str_2);

  int_test1 = sprintf(str_1, "%10p", p1);
  int_test2 = s21_sprintf(str_2, "%10p", p1);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  free_two(str_1, str_2);

  int_test1 = sprintf(str_1, "%*p", 10, p4);
  int_test2 = s21_sprintf(str_2, "%*p", 10, p4);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  free_two(str_1, str_2);
}
END_TEST

START_TEST(test_s21_sprintf_g) {
  int_test1 = s21_sprintf(str_1, "%g", 2345.4324);
  int_test2 = sprintf(str_2, "%g", 2345.4324);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%+#25.8g", 0.0000034);
  int_test2 = sprintf(str_2, "%+#25.8g", 0.0000034);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%015g", 3456.3424);
  int_test2 = sprintf(str_2, "%015g", 3456.3424);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);
}
END_TEST

START_TEST(test_s21_sprintf_G) {
  int_test1 = s21_sprintf(str_1, "%G", 2345.4324);
  int_test2 = sprintf(str_2, "%G", 2345.4324);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%+#25.8G", 0.0000034);
  int_test2 = sprintf(str_2, "%+#25.8G", 0.0000034);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%015G", 3456.3424);
  int_test2 = sprintf(str_2, "%015G", 3456.3424);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);
}
END_TEST

START_TEST(test_s21_sprintf_o) {
  s21_sprintf(str_1, "abc %o", 4784);
  sprintf(str_2, "abc %o", 4784);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %#o", 4784);
  sprintf(str_2, "abc %#o", 4784);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %o", 0);
  sprintf(str_2, "abc %o", 0);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-25.10o", 12345);
  int_test2 = sprintf(str_2, "%-25.10o", 12345);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-10o", 6532);
  int_test2 = sprintf(str_2, "%-10o", 6532);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%#-30.2o", 43522);
  int_test2 = sprintf(str_2, "%#-30.2o", 43522);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);
}
END_TEST

START_TEST(test_s21_sprintf_E) {
  s21_sprintf(str_1, "abc %E", 0.4784);
  sprintf(str_2, "abc %E", 0.4784);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %-20E", 0.4784);
  sprintf(str_2, "abc %-20E", 0.4784);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %+20E", 0.0);
  sprintf(str_2, "abc %+20E", 0.0);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %20E", 123456789.123456789);
  sprintf(str_2, "abc %20E", 123456789.123456789);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%+-25.4E", 3456.4325);
  int_test2 = sprintf(str_2, "%+-25.4E", 3456.4325);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-*.10E", 5, -0.05234);
  int_test2 = sprintf(str_2, "%-*.10E", 5, -0.05234);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);
}
END_TEST

START_TEST(test_s21_sprintf_e) {
  int_test1 = s21_sprintf(str_1, "%+-20e", 2543.43254);
  int_test2 = sprintf(str_2, "%+-20e", 2543.43254);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %e", 0.4784);
  sprintf(str_2, "abc %e", 0.4784);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %e", 7.8);
  sprintf(str_2, "abc %e", 7.8);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %e", 17.8);
  sprintf(str_2, "abc %e", 17.8);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %Le", (long double)17.8);
  sprintf(str_2, "abc %Le", (long double)17.8);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%+-20e", 2543.43254);
  int_test2 = sprintf(str_2, "%+-20e", 2543.43254);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%010.*e", 15, -0.00123);
  int_test2 = sprintf(str_2, "%010.*e", 15, -0.00123);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%#025.10e", 45678.342532);
  int_test2 = sprintf(str_2, "%#025.10e", 45678.342532);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);
}
END_TEST

START_TEST(test_s21_sprintf_X) {
  s21_sprintf(str_1, "%X", n);
  sprintf(str_2, "%X", n);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%X %X", n, n2);
  sprintf(str_2, "%X %X", n, n2);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%X %X%X", n, n2, n1);
  sprintf(str_2, "%X %X%X", n, n2, n1);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-10X %lX", 21, lg1);
  sprintf(str_2, "%-10X %lX", 21, lg1);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%lX", lg1);
  sprintf(str_2, "%lX", lg1);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-10X", 21);
  sprintf(str_2, "%-10X", 21);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%10X %-10X", 0, 21);
  sprintf(str_2, "%10X %-10X", 0, 21);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%#X %#X", n, n2);
  sprintf(str_2, "%#X %#X", n, n2);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-#10X %#10X", 21, 42);
  sprintf(str_2, "%-#10X %#10X", 21, 42);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-#10X%#10X", 21, 42);
  sprintf(str_2, "%-#10X%#10X", 21, 42);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-#10X", 21);
  sprintf(str_2, "%-#10X", 21);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%#10X", 42);
  sprintf(str_2, "%#10X", 42);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%0#10X", n1);
  sprintf(str_2, "%0#10X", n1);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);
}
END_TEST

Suite *example_suite_create(void) {
  Suite *suite = suite_create("Test of s21_string");
  TCase *tcase_core = tcase_create("Core of s21_string");
  tcase_add_test(tcase_core, test_s21_memchr);
  tcase_add_test(tcase_core, test_s21_memcmp);
  tcase_add_test(tcase_core, test_s21_memcpy);
  tcase_add_test(tcase_core, test_s21_memset);
  tcase_add_test(tcase_core, test_s21_strlen);
  tcase_add_test(tcase_core, test_s21_strcat);
  tcase_add_test(tcase_core, test_s21_strncat);
  tcase_add_test(tcase_core, STRCATTest1);
  tcase_add_test(tcase_core, STRCATTest2);
  tcase_add_test(tcase_core, STRCATTest3);
  tcase_add_test(tcase_core, STRCATTest4);
  tcase_add_test(tcase_core, STRCATTest5);
  tcase_add_test(tcase_core, test_s21_strcspn);
  tcase_add_test(tcase_core, test_s21_strpbrk);
  tcase_add_test(tcase_core, test_s21_strchr);
  tcase_add_test(tcase_core, test_s21_strncpy);
  tcase_add_test(tcase_core, test_s21_strstr1);
  tcase_add_test(tcase_core, test_s21_strstr2);
  tcase_add_test(tcase_core, test_s21_strstr3);
  tcase_add_test(tcase_core, STRSTRTest1);
  tcase_add_test(tcase_core, STRSTRTest3);
  tcase_add_test(tcase_core, STRSTRTest4);
  tcase_add_test(tcase_core, STRSTRTest5);
  tcase_add_test(tcase_core, test_s21_to_upper);
  tcase_add_test(tcase_core, test_s21_to_lower);
  tcase_add_test(tcase_core, test_s21_strrchr);
  tcase_add_test(tcase_core, STRRCHRTest1);
  tcase_add_test(tcase_core, STRRCHRTest2);
  tcase_add_test(tcase_core, STRRCHRTest3);
  tcase_add_test(tcase_core, STRRCHRTest5);
  tcase_add_test(tcase_core, test_s21_strncmp);
  tcase_add_test(tcase_core, test_s21_strtok);
  tcase_add_test(tcase_core, test_s21_strtok_2);
  tcase_add_test(tcase_core, INSERTTest1);
  tcase_add_test(tcase_core, INSERTTest2);
  tcase_add_test(tcase_core, INSERTTest3);
  tcase_add_test(tcase_core, INSERTTest4);
  tcase_add_test(tcase_core, INSERTTest5);
  tcase_add_test(tcase_core, INSERTTest6);
  tcase_add_test(tcase_core, INSERTTest7);
  tcase_add_test(tcase_core, test_s21_strerror);
  tcase_add_test(tcase_core, strerror_test);
  tcase_add_test(tcase_core, s21_strerror_test);
  tcase_add_test(tcase_core, test_s21_trim);
  tcase_add_test(tcase_core, test_s21_sprintf_p);
  tcase_add_test(tcase_core, test_s21_sprintf_g);
  tcase_add_test(tcase_core, test_s21_sprintf_G);
  tcase_add_test(tcase_core, test_s21_sprintf_E);
  tcase_add_test(tcase_core, test_s21_sprintf_e);
  tcase_add_test(tcase_core, test_s21_sprintf_X);
  tcase_add_test(tcase_core, test_s21_sprintf_o);
  tcase_add_test(tcase_core, test_s21_sprintf_di_test1);
  tcase_add_test(tcase_core, test_s21_sprintf_di_test2);
  tcase_add_test(tcase_core, test_s21_sprintf_di_test3);
  tcase_add_test(tcase_core, test_s21_sprintf_di_test4);
  tcase_add_test(tcase_core, test_s21_sprintf_di_test5);
  tcase_add_test(tcase_core, test_s21_sprintf_di_test6);
  tcase_add_test(tcase_core, test_s21_sprintf_di_test7);
  tcase_add_test(tcase_core, test_s21_sprintf_di_test8);
  tcase_add_test(tcase_core, test_s21_sprintf_di_test9);
  tcase_add_test(tcase_core, test_s21_sprintf_di_test10);
  tcase_add_test(tcase_core, test_s21_sprintf_di_test11);
  tcase_add_test(tcase_core, test_s21_sprintf_di_test12);

  tcase_add_test(tcase_core, test_s21_sprintf_c_test1);
  tcase_add_test(tcase_core, test_s21_sprintf_c_test2);
  tcase_add_test(tcase_core, test_s21_sprintf_c_test3);

  tcase_add_test(tcase_core, test_s21_sprintf_s_test1);
  tcase_add_test(tcase_core, test_s21_sprintf_s_test2);
  tcase_add_test(tcase_core, test_s21_sprintf_s_test3);
  tcase_add_test(tcase_core, test_s21_sprintf_s_test4);
  tcase_add_test(tcase_core, test_s21_sprintf_s_test5);
  tcase_add_test(tcase_core, test_s21_sprintf_s_test6);

  tcase_add_test(tcase_core, test_s21_sprintf_u_test1);
  tcase_add_test(tcase_core, test_s21_sprintf_u_test2);
  tcase_add_test(tcase_core, test_s21_sprintf_u_test3);
  tcase_add_test(tcase_core, test_s21_sprintf_u_test4);

  tcase_add_test(tcase_core, test_s21_sprintf_float_1);
  tcase_add_test(tcase_core, test_s21_sprintf_float_2);
  tcase_add_test(tcase_core, test_s21_sprintf_float_3);
  tcase_add_test(tcase_core, test_s21_sprintf_float_4);
  tcase_add_test(tcase_core, test_s21_sprintf_float_5);
  tcase_add_test(tcase_core, test_s21_sprintf_float_6);
  tcase_add_test(tcase_core, test_s21_sprintf_float_7);
  tcase_add_test(tcase_core, test_s21_sprintf_float_8);
  tcase_add_test(tcase_core, test_s21_sprintf_float_9);
  tcase_add_test(tcase_core, test_s21_sprintf_float_10);
  tcase_add_test(tcase_core, test_s21_sprintf_float_11);
  tcase_add_test(tcase_core, test_s21_sprintf_float_12);
  tcase_add_test(tcase_core, test_s21_sprintf_float_13);
  tcase_add_test(tcase_core, test_s21_sprintf_float_14);
  tcase_add_test(tcase_core, test_s21_sprintf_float_15);
  tcase_add_test(tcase_core, test_s21_sprintf_float_16);
  tcase_add_test(tcase_core, test_s21_sprintf_float_17);
  tcase_add_test(tcase_core, test_s21_sprintf_float_18);
  tcase_add_test(tcase_core, test_s21_sprintf_float_19);
  tcase_add_test(tcase_core, test_s21_sprintf_float_20);
  tcase_add_test(tcase_core, test_s21_sprintf_float_21);
  tcase_add_test(tcase_core, test_s21_sprintf_float_22);
  tcase_add_test(tcase_core, test_s21_sprintf_float_23);
  tcase_add_test(tcase_core, test_s21_sprintf_float_24);
  tcase_add_test(tcase_core, test_s21_sprintf_float_25);
  tcase_add_test(tcase_core, test_s21_sprintf_float_26);
  tcase_add_test(tcase_core, test_s21_sprintf_float_27);
  tcase_add_test(tcase_core, test_s21_sprintf_float_28);
  tcase_add_test(tcase_core, test_s21_sprintf_float_29);
  tcase_add_test(tcase_core, test_s21_sprintf_float_30);
  tcase_add_test(tcase_core, test_s21_sprintf_float_31);
  tcase_add_test(tcase_core, test_s21_sprintf_float_32);
  tcase_add_test(tcase_core, test_s21_sprintf_float_33);
  tcase_add_test(tcase_core, test_s21_sprintf_float_34);
  tcase_add_test(tcase_core, test_s21_sprintf_float_35);
  tcase_add_test(tcase_core, test_s21_sprintf_float_36);
  tcase_add_test(tcase_core, test_s21_sprintf_float_37);
  tcase_add_test(tcase_core, test_s21_sprintf_float_38);
  tcase_add_test(tcase_core, test_s21_sprintf_float_39);
  tcase_add_test(tcase_core, test_s21_sprintf_float_40);
  tcase_add_test(tcase_core, test_s21_sprintf_float_41);
  tcase_add_test(tcase_core, test_s21_sprintf_float_42);
  tcase_add_test(tcase_core, test_s21_sprintf_float_43);
  tcase_add_test(tcase_core, test_s21_sprintf_float_44);
  tcase_add_test(tcase_core, test_s21_sprintf_float_45);
  tcase_add_test(tcase_core, test_s21_sprintf_float_46);
  tcase_add_test(tcase_core, test_s21_sprintf_float_47);
  tcase_add_test(tcase_core, test_s21_sprintf_float_48);
  tcase_add_test(tcase_core, test_s21_sprintf_float_49);
  tcase_add_test(tcase_core, test_s21_sprintf_float_50);
  tcase_add_test(tcase_core, test_s21_sprintf_float_51);
  tcase_add_test(tcase_core, test_s21_sprintf_float_52);
  tcase_add_test(tcase_core, test_s21_sprintf_float_53);
  tcase_add_test(tcase_core, test_s21_sprintf_float_54);
  tcase_add_test(tcase_core, test_s21_sprintf_float_56);
  tcase_add_test(tcase_core, test_s21_sprintf_float_58);
  tcase_add_test(tcase_core, test_s21_sprintf_float_59);
  tcase_add_test(tcase_core, test_s21_sprintf_float_60);
  tcase_add_test(tcase_core, test_s21_sprintf_float_61);
  tcase_add_test(tcase_core, test_s21_sprintf_float_62);
  tcase_add_test(tcase_core, test_s21_sprintf_float_63);
  tcase_add_test(tcase_core, test_s21_sprintf_float_67);
  tcase_add_test(tcase_core, test_s21_sprintf_float_68);
  tcase_add_test(tcase_core, test_s21_sprintf_float_69);
  tcase_add_test(tcase_core, test_s21_sprintf_float_70);
  tcase_add_test(tcase_core, test_s21_sprintf_float_71);
  tcase_add_test(tcase_core, test_s21_sprintf_float_72);
  tcase_add_test(tcase_core, test_s21_sprintf_float_73);
  tcase_add_test(tcase_core, test_s21_sprintf_float_74);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

int main(void) {
  Suite *suite = example_suite_create();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return failed_count != 0 ? 1 : 0;
}
