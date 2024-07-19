#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  char *start = str;
  va_list pa;
  va_start(pa, format);
  while (*format) {
    if (*format != '%') {
      *str = *format;
      str++;
      format++;
    } else {
      format++;
      format_t format_sprintf = {0};
      if (parse_format(&format, &format_sprintf, pa)) {
        write_format(&str, &format_sprintf, pa);
      }
    }
  }
  va_end(pa);
  *str = '\0';
  return (str - start);
}

int parse_format(const char **format, format_t *format_sprintf, va_list pa) {
  int err_flag = 0;
  while (**format) {
    char curr = **format;
    if (curr == 'l')
      format_sprintf->length = 'l';
    else if (curr == 'L')
      format_sprintf->length = 'L';
    else if (curr == 'h')
      format_sprintf->length = 'h';
    else if (curr == '-') {
      format_sprintf->minus_flag = 1;
      if (format_sprintf->is_prec) {
        format_sprintf->is_prec = 0;
      }
    } else if (curr == '+')
      format_sprintf->plus_flag = 1;
    else if (curr == ' ')
      format_sprintf->space_flag = 1;
    else if (curr == '.')
      format_sprintf->is_prec = 1;
    else if (curr == '#')
      format_sprintf->hash = 1;
    else if (curr == '0' && !format_sprintf->is_prec &&
             !format_sprintf->width) {
      format_sprintf->zero = 1;
    } else if (isdigit(curr)) {
      if (format_sprintf->is_prec) {
        format_sprintf->prec = format_sprintf->prec * 10 + curr - 48;
      } else {
        format_sprintf->width = format_sprintf->width * 10 + curr - 48;
      }
    } else if (curr == '*') {
      if (format_sprintf->is_prec) {
        format_sprintf->prec = va_arg(pa, int);
        if (format_sprintf->prec < 0) format_sprintf->prec = 6;
      } else {
        format_sprintf->width = va_arg(pa, int);
        if (format_sprintf->width < 0) {
          format_sprintf->width = -format_sprintf->width;
          format_sprintf->minus_flag = 1;
        }
      }
    } else {
      if (is_spec(curr)) {
        format_sprintf->spec = curr;
        format_sprintf->base = get_base(curr);
        if (curr == 'X' || curr == 'E' || curr == 'G')
          format_sprintf->upper_case = 1;
        (*format)++;
      }
      break;
    }
    (*format)++;
  }
  format_sprintf->space_flag =
      (format_sprintf->space_flag && !format_sprintf->plus_flag);
  if (format_sprintf->spec == 'f' || format_sprintf->spec == 'e' ||
      format_sprintf->spec == 'E' || format_sprintf->spec == 'g' ||
      format_sprintf->spec == 'G') {
    format_sprintf->zero =
        (format_sprintf->zero && !format_sprintf->minus_flag);
  } else {
    format_sprintf->zero =
        (format_sprintf->zero && !format_sprintf->minus_flag &&
         !format_sprintf->is_prec);
  }
  if (format_sprintf->spec) err_flag = 1;
  return err_flag;
}

void write_format(char **str, format_t *format_sprintf, va_list pa) {
  if (format_sprintf->spec == 'd' || format_sprintf->spec == 'i') {
    process_d(str, format_sprintf, pa);
  } else if (format_sprintf->spec == 'u' || format_sprintf->spec == 'o' ||
             format_sprintf->spec == 'X' || format_sprintf->spec == 'x') {
    process_u(str, format_sprintf, pa);
  } else if (format_sprintf->spec == 'c') {
    process_c(str, format_sprintf, va_arg(pa, int));
  } else if (format_sprintf->spec == 's') {
    process_s(str, format_sprintf, pa);
  } else if (format_sprintf->spec == 'p') {
    process_p(str, format_sprintf, pa);
  } else if (format_sprintf->spec == '%') {
    process_c(str, format_sprintf, '%');
  } else if (format_sprintf->spec == 'f' || format_sprintf->spec == 'e' ||
             format_sprintf->spec == 'E' || format_sprintf->spec == 'g' ||
             format_sprintf->spec == 'G') {
    process_f(str, format_sprintf, pa);
  }
}

int get_base(char ch) {
  int base = 0;
  if (ch == 'o')
    base = 8;
  else if (ch == 'd' || ch == 'i' || ch == 'u' || ch == 'g' || ch == 'G' ||
           ch == 'f' || ch == 'e' || ch == 'E')
    base = 10;
  else if (ch == 'x' || ch == 'X' || ch == 'p')
    base = 16;
  return base;
}

char get_char_by_num(long int n, int is_upper) {
  char ch = '0';
  if (n >= 0 && n <= 9)
    ch = n + '0';
  else {
    if (n == 10)
      ch = 'a' - is_upper * 32;
    else if (n == 11)
      ch = 'b' - is_upper * 32;
    else if (n == 12)
      ch = 'c' - is_upper * 32;
    else if (n == 13)
      ch = 'd' - is_upper * 32;
    else if (n == 14)
      ch = 'e' - is_upper * 32;
    else if (n == 15)
      ch = 'f' - is_upper * 32;
  }
  return ch;
}

int is_spec(char ch) {
  int flag = 0;
  if (s21_strchr("cdifsugGeExXonp", ch) || ch == '%') flag = 1;
  return flag;
}

s21_size_t num_of_digits_f(long double f, format_t *format_sprintf) {
  s21_size_t res = 1;
  f = (f < 0.) ? -f : f;
  res = num_of_digits_d((long int)round_f(format_sprintf, f), format_sprintf);
  res += format_sprintf->prec;
  if ((format_sprintf->flag_g && format_sprintf->is_prec == 0)) {
  } else if (!(format_sprintf->is_prec && format_sprintf->prec == 0)) {
    res++;
  }
  if (format_sprintf->is_prec && format_sprintf->prec == 0 &&
      format_sprintf->hash)
    res++;
  if (format_sprintf->spec == 'e' || format_sprintf->spec == 'E') res += 4;
  return res;
}

long double round_f(format_t *format_sprintf, long double f) {
  int round = 5;
  if (f != 0) {
    double vr = pow(0.1, format_sprintf->prec + 1);
    f += round * vr;
  }
  return f;
}

long double get_mantis(int *mantis, long double f) {
  f = (f < 0.) ? -f : f;
  if (f == 0.0) {
    *mantis = 0;
  } else if ((long int)f == 0) {
    while ((long int)f == 0) {
      f *= 10;
      (*mantis)++;
    }
  } else {
    while ((long int)f >= 10) {
      f /= 10;
      (*mantis)--;
    }
  }
  return f;
}

s21_size_t num_of_digits_d(long int n, format_t *format_sprintf) {
  s21_size_t res = 1;
  int counter = 0;
  n = (n < 0) ? -n : n;
  while (n > 0) {
    n /= format_sprintf->base;
    if (counter > 0) {
      res++;
    }
    counter++;
  }
  return res;
}

s21_size_t num_of_digits_u(unsigned long long n, format_t *format_sprintf) {
  s21_size_t res = 1;
  int counter = 0;
  while (n > 0) {
    n /= format_sprintf->base;
    if (counter > 0) {
      res++;
    }
    counter++;
  }
  return res;
}

void process_f(char **str, format_t *format_sprintf, va_list pa) {
  long double f = 0;
  if (format_sprintf->length == 'L') {
    f = va_arg(pa, long double);
  } else {
    f = va_arg(pa, double);
  }

  if (!format_sprintf->is_prec) format_sprintf->prec = 6;
  if (format_sprintf->spec == 'g' || format_sprintf->spec == 'G') {
    format_sprintf->flag_g = 1;
    get_spec(format_sprintf, f);
  }

  s21_size_t size = get_arr_size_f(format_sprintf, f);
  char *f_string = (char *)calloc(size, sizeof(char));
  if (f_string) {
    f_to_str(format_sprintf, f, f_string, size);
    for (s21_size_t i = 0; i < size; i++) {
      **str = f_string[i];
      (*str)++;
    }
    free(f_string);
  }
}

void get_spec(format_t *format_sprintf, long double f) {
  int t_mantis = 0;
  get_mantis(&t_mantis, f);
  if ((-5 <= t_mantis && t_mantis < 6)) {
    format_sprintf->spec = 'f';
    format_sprintf->prec = t_mantis < 0 ? -t_mantis : t_mantis;
  } else {
    format_sprintf->spec = format_sprintf->spec == 'g' ? 'e' : 'E';
    format_sprintf->prec = format_sprintf->prec == 0 ? format_sprintf->prec
                                                     : format_sprintf->prec - 1;
  }
}

void process_u(char **str, format_t *format_sprintf, va_list pa) {
  unsigned long long n = 0;
  if (format_sprintf->length == 'l') {
    n = (unsigned long long)va_arg(pa, unsigned long long int);
  } else if (format_sprintf->length == 'h') {
    n = (unsigned short)va_arg(pa, unsigned int);
  } else {
    n = (long unsigned)va_arg(pa, unsigned long int);
  }

  s21_size_t size = get_arr_size_u(format_sprintf, n);
  char *u_string = (char *)calloc(size, sizeof(char));
  if (u_string) {
    u_to_str(format_sprintf, n, u_string, size);
    for (s21_size_t i = 0; i < size; i++) {
      **str = u_string[i];
      (*str)++;
    }
    free(u_string);
  }
}

void process_d(char **str, format_t *format_sprintf, va_list pa) {
  long int n = 0;
  if (format_sprintf->length == 'l') {
    n = va_arg(pa, long int);
  } else if (format_sprintf->length == 'h') {
    n = (short)va_arg(pa, int);
  } else {
    n = va_arg(pa, int);
  }
  s21_size_t size = get_arr_size_d(format_sprintf, n);
  char *d_string = (char *)calloc(size, sizeof(char));
  if (d_string) {
    d_to_str(format_sprintf, n, d_string, size);
    for (s21_size_t i = 0; i < size; i++) {
      **str = d_string[i];
      (*str)++;
    }
    free(d_string);
  }
}

void process_c(char **str, format_t *format_sprintf, char sym) {
  if (format_sprintf->width && !format_sprintf->minus_flag) {
    for (int i = 0; i < format_sprintf->width - 1; i++) {
      **str = ' ';
      (*str)++;
    }
    **str = sym;
    (*str)++;
  } else if (format_sprintf->width && format_sprintf->minus_flag) {
    **str = sym;
    (*str)++;
    for (int i = 0; i < format_sprintf->width - 1; i++) {
      **str = ' ';
      (*str)++;
    }
  } else {
    **str = sym;
    (*str)++;
  }
}

void process_p(char **str, format_t *format_sprintf, va_list pa) {
  unsigned long int ptr = va_arg(pa, unsigned long int);
  format_sprintf->hash = 1;
  s21_size_t size = get_arr_size_u(format_sprintf, ptr);
  char *u_string = (char *)calloc(size, sizeof(char));
  if (u_string) {
    u_to_str(format_sprintf, ptr, u_string, size);
    for (s21_size_t i = 0; i < size; i++) {
      **str = u_string[i];
      (*str)++;
    }
    free(u_string);
  }
}

void process_s(char **str, format_t *format_sprintf, va_list pa) {
  char *s = va_arg(pa, char *);
  int len = s21_strlen(s), size = 0;

  if (format_sprintf->is_prec && len > format_sprintf->prec)
    len = format_sprintf->prec;

  if (len < format_sprintf->width)
    size = format_sprintf->width;
  else
    size = len;

  if (format_sprintf->minus_flag) {
    for (int i = 0; i < len; i++) {
      **str = s[i];
      (*str)++;
      size--;
    }

    while (size > 0) {
      **str = ' ';
      (*str)++;
      size--;
    }
  } else {
    while (size - len > 0) {
      **str = ' ';
      (*str)++;
      size--;
    }

    for (int i = 0; i < len; i++) {
      **str = s[i];
      (*str)++;
    }
  }
}

// Flags u/o/x/X
s21_size_t get_arr_size_u(format_t *format_sprintf, unsigned long long n) {
  s21_size_t res = num_of_digits_u(n, format_sprintf);
  if (format_sprintf->hash && format_sprintf->base == 8 && n != 0) res++;
  if ((s21_size_t)format_sprintf->prec > res) res = format_sprintf->prec;
  if (format_sprintf->hash && format_sprintf->base == 16 && n != 0)
    res = res + 2;
  if ((s21_size_t)format_sprintf->width > res) res = format_sprintf->width;
  return res;
}
// Flags d/i
s21_size_t get_arr_size_d(format_t *format_sprintf, long int n) {
  s21_size_t res = num_of_digits_d(n, format_sprintf);
  if (format_sprintf->space_flag || format_sprintf->plus_flag || n < 0) res++;
  if ((s21_size_t)format_sprintf->width > res) res = format_sprintf->width;
  if ((s21_size_t)format_sprintf->prec > res) {
    res = format_sprintf->prec;
    if (format_sprintf->space_flag || format_sprintf->plus_flag || n < 0) res++;
  }
  return res;
}
// Flags f/e/E/g/G
s21_size_t get_arr_size_f(format_t *format_sprintf, long double f) {
  s21_size_t res = num_of_digits_f(f, format_sprintf);
  if (format_sprintf->space_flag || format_sprintf->plus_flag || f < 0.) res++;
  if ((s21_size_t)format_sprintf->width > res) res = format_sprintf->width;
  return res;
}

void d_to_str(format_t *format_sprintf, long int n, char *str,
              s21_size_t size) {
  s21_size_t digits = num_of_digits_d(n, format_sprintf);
  long int n_copy = (n < 0) ? -n : n;
  int count = 0, flag = 0;
  char *num_str = (char *)calloc(digits, sizeof(char));
  if (num_str) {
    for (s21_size_t i = 0; i < digits; i++) {
      num_str[i] = get_char_by_num(n_copy % format_sprintf->base, 0);
      n_copy /= format_sprintf->base;
    }
    if (format_sprintf->minus_flag ||
        (!format_sprintf->minus_flag &&
         (format_sprintf->zero ||
          (fmax(format_sprintf->prec, digits) + 1 >= format_sprintf->width)))) {
      if (n < 0) {
        *str = '-';
        str++;
        count++;
        flag = 1;
      } else if (format_sprintf->plus_flag) {
        *str = '+';
        str++;
        count++;
        flag = 1;
      } else if (format_sprintf->space_flag) {
        *str = ' ';
        str++;
        count++;
        flag = 1;
      }
    }
    if (format_sprintf->minus_flag) {
      while ((s21_size_t)format_sprintf->prec > digits) {
        *str = '0';
        format_sprintf->prec--;
        str++;
        count++;
      }
      for (int i = digits - 1; i >= 0; i--) {
        *str = num_str[i];
        str++;
        count++;
      }
      while ((s21_size_t)count < size) {
        *str = ' ';
        str++;
        count++;
      }
    } else {
      if (format_sprintf->zero) {
        while (format_sprintf->width - count - digits > 0) {
          *str = '0';
          str++;
          count++;
        }
      } else {
        while (format_sprintf->width - count -
                   fmax(format_sprintf->prec, digits) >
               1) {
          *str = ' ';
          count++;
          str++;
        }
        if (n < 0 && !flag) {
          *str = '-';
          str++;
        } else if (format_sprintf->plus_flag && !flag) {
          *str = '+';
          str++;
        } else if (format_sprintf->width - count -
                       fmax(format_sprintf->prec, digits) ==
                   1) {
          *str = ' ';
          str++;
        }
        while ((s21_size_t)format_sprintf->prec > digits) {
          *str = '0';
          format_sprintf->prec--;
          str++;
        }
      }
      for (int i = digits - 1; i >= 0; i--) {
        *str = num_str[i];
        str++;
      }
    }
    free(num_str);
  }
}

void u_to_str(format_t *format_sprintf, unsigned long long n, char *str,
              s21_size_t size) {
  s21_size_t digits = num_of_digits_u(n, format_sprintf);
  unsigned long long n_copy = n;
  int count = 0, base = 0;
  char *num_str = (char *)calloc(digits, sizeof(char));
  if (num_str) {
    for (s21_size_t i = 0; i < digits; i++) {
      num_str[i] = get_char_by_num(n_copy % format_sprintf->base,
                                   format_sprintf->upper_case);
      n_copy /= format_sprintf->base;
    }
    if (n == 0 && format_sprintf->hash) {
      if (!format_sprintf->zero)
        base = 1;
      else
        base = format_sprintf->width;
    } else if (format_sprintf->hash && format_sprintf->base == 8) {
      if (digits >= (s21_size_t)format_sprintf->prec)
        base = digits + 1;
      else
        base = format_sprintf->prec;
    } else if (format_sprintf->hash && format_sprintf->base == 16)
      base = fmax(format_sprintf->prec, digits) + 2;
    else
      base = fmax(format_sprintf->prec, digits);
    while (!format_sprintf->minus_flag &&
           format_sprintf->width - count - base > 0) {
      *str = ' ';
      str++;
      count++;
    }

    if (format_sprintf->hash && n != 0) {
      *str = '0';
      str++;
      count++;
      base--;
      if (format_sprintf->base == 16) {
        *str = format_sprintf->upper_case ? 'X' : 'x';
        str++;
        count++;
        base--;
      }
    }
    while (base - digits > 0) {
      *str = '0';
      str++;
      count++;
      base--;
    }

    for (int i = digits - 1; i >= 0; i--) {
      *str = num_str[i];
      str++;
      count++;
    }
    while (size - count > 0) {
      *str = ' ';
      str++;
      count++;
    }
    free(num_str);
  }
}

void f_to_str(format_t *format_sprintf, long double f, char *str,
              s21_size_t size) {
  long double f_copy = (f < 0) ? -f : f, fract;
  int count = 0, flag = 0, whole = 0, mantis = 0;
  s21_size_t digits =
      num_of_digits_d((long int)round_f(format_sprintf, f), format_sprintf);
  if (format_sprintf->spec == 'e' || format_sprintf->spec == 'E') {
    f_copy = get_mantis(&mantis, f);
    digits = 1;
  }
  int full_num = (int)num_of_digits_f(f_copy, format_sprintf);
  f_copy = round_f(format_sprintf, f_copy);
  whole = (int)f_copy;
  char *num_str = (char *)calloc(digits, sizeof(char));
  char *fract_str = (char *)calloc(format_sprintf->prec, sizeof(char));
  if (num_str) {
    long int f_int = (long int)f_copy;
    for (s21_size_t i = 0; i < digits; i++) {
      num_str[i] = get_char_by_num(f_int % format_sprintf->base,
                                   format_sprintf->upper_case);
      f_int /= format_sprintf->base;
    }
    if (format_sprintf->minus_flag ||
        (!format_sprintf->minus_flag &&
         (format_sprintf->zero || full_num > format_sprintf->width))) {
      if (f < 0.) {
        *str = '-';
        str++;
        count++;
        flag = 1;
      } else if (format_sprintf->plus_flag) {
        *str = '+';
        str++;
        count++;
        flag = 1;
      } else if (format_sprintf->space_flag) {
        *str = ' ';
        str++;
        count++;
        flag = 1;
      }
    }
    if (fract_str) {
      fract = f_copy - whole;
      for (s21_size_t i = 0; i < (s21_size_t)format_sprintf->prec; i++) {
        fract = (fract - (int)fract) * 10;
        fract_str[i] = (int)fract % 10 + '0';
      }
    }

    if (format_sprintf->minus_flag) {
      for (int i = digits - 1; i >= 0; i--) {
        *str = num_str[i];
        str++;
        count++;
      }
      if (!(format_sprintf->is_prec && format_sprintf->prec == 0 &&
            !format_sprintf->hash)) {
        *str = '.';
        str++;
        count++;
      }
      if (fract_str) {
        for (s21_size_t i = 0; i < (s21_size_t)format_sprintf->prec; i++) {
          *str = fract_str[i];
          str++;
          count++;
        }
      }
      if (format_sprintf->spec == 'e' || format_sprintf->spec == 'E') {
        *str = format_sprintf->upper_case ? 'E' : 'e';
        str++;
        count++;
        *str = mantis > 0 ? '-' : '+';
        str++;
        count++;
        mantis = mantis < 0 ? -mantis : mantis;
        if (mantis < 10) {
          *str = '0';
          str++;
          count++;
          *str = mantis + '0';
          str++;
          count++;
        } else {
          *str = mantis / 10;
          str++;
          count++;
          *str = mantis % 10;
          str++;
          count++;
        }
      }
      while ((s21_size_t)count < size) {
        *str = ' ';
        str++;
        count++;
      }
    } else {
      if (format_sprintf->plus_flag || format_sprintf->space_flag || f < 0.)
        count++;
      if (format_sprintf->zero) {
        while (format_sprintf->width - count - full_num > 0) {
          *str = '0';
          str++;
          count++;
        }
      } else {
        while (format_sprintf->width - count - full_num > 0) {
          *str = ' ';
          count++;
          str++;
        }
      }

      if (f < 0. && !flag) {
        *str = '-';
        str++;
      } else if (format_sprintf->plus_flag && !flag) {
        *str = '+';
        str++;
      } else if (format_sprintf->width - count - full_num == 1) {
        *str = ' ';
        str++;
      }
      for (int i = digits - 1; i >= 0; i--) {
        *str = num_str[i];
        str++;
      }
      if (!(format_sprintf->is_prec && format_sprintf->prec == 0 &&
            !format_sprintf->hash)) {
        *str = '.';
        str++;
      }
      if (fract_str) {
        for (s21_size_t i = 0; i < (s21_size_t)format_sprintf->prec; i++) {
          *str = fract_str[i];
          str++;
        }
      }
      if (format_sprintf->spec == 'e' || format_sprintf->spec == 'E') {
        *str = format_sprintf->upper_case ? 'E' : 'e';
        str++;
        *str = mantis > 0 ? '-' : '+';
        str++;
        mantis = mantis < 0 ? -mantis : mantis;
        if (mantis < 10) {
          *str = '0';
          str++;
          *str = mantis + '0';
          str++;
        } else {
          *str = mantis / 10;
          str++;
          *str = mantis % 10;
          str++;
        }
      }
    }
  }
  if (num_str) free(num_str);
  if (fract_str) free(fract_str);
}