#include "c-string/c-string.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void string_init_globals(void) {
  gSTRING_ASCII_LOWERCASE = STRING_EXPR("abcdefghijklmnopqrstuvwxyz");
  gSTRING_ASCII_UPPERCASE = STRING_EXPR("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  gSTRING_ASCII_LETTERS =
      string_concat(&gSTRING_ASCII_LOWERCASE, &gSTRING_ASCII_UPPERCASE);
  gSTRING_DIGITS = STRING_EXPR("0123456789");
  gSTRING_HEXDIGITS = STRING_EXPR("0123456789abcdefABCDEF");
  gSTRING_OCTDIGITS = STRING_EXPR("01234567");
  gSTRING_PUNCTUATION = STRING_EXPR("!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");
  gSTRING_WHITESPACE = STRING_EXPR(" \t\n\r\f\v");
  gSTRING_PRINTABLE = string_concat_many(&gSTRING_ASCII_LETTERS,
      &gSTRING_DIGITS,
      &gSTRING_PUNCTUATION,
      &gSTRING_WHITESPACE,
      NULL);
}
void string_free_globals(void) {
  string_free(&gSTRING_ASCII_LETTERS);
  string_free(&gSTRING_PRINTABLE);
}
String string_new(void) {
  return (String){
      .str = STRING_CALLOC(1, 1),
      .len = 0,
      .cap = 1,
  };
}
String string_new_len(size_t len) {
  return (String){
      .str = STRING_MALLOC(len + 1),
      .len = len,
      .cap = len + 1,
  };
}
String string_from_cstr(const char* cstr) {
  size_t clen = strlen(cstr);
  String result = {
      .str = STRING_MALLOC(clen + 1),
      .len = clen,
      .cap = clen + 1,
  };
  strcpy(result.str, cstr);
  return result;
}
String string_from_bytes(const char* bytes, size_t len) {
  String result = {
      .str = STRING_MALLOC(len + 1),
      .len = len,
      .cap = len + 1,
  };
  memcpy(result.str, bytes, len);
  result.str[len] = '\0';
  return result;
}
String string_dup(const String* str) {
  return string_from_bytes(str->str, str->len);
}
void string_free(String* str) {
  if (str == NULL) {
    return;
  }
  free(str->str);
  str->str = NULL;
  str->len = 0;
  str->cap = 0;
}
String string_concat(const String* a, const String* b) {
  String result = string_new_len(a->len + b->len);
  memcpy(result.str, a->str, a->len);
  memcpy(result.str + a->len, b->str, b->len);
  result.str[result.len] = '\0';
  return result;
}
String string_concat_many(const String* first, ...) {
  size_t len = 0;
  va_list args;
  va_start(args, first);
  const String* s = first;
  while (s != NULL) {
    len += s->len;
    s = va_arg(args, const String*);
  }
  va_end(args);
  String result = string_new_len(len);
  size_t i = 0;
  va_start(args, first);
  s = first;
  while (s != NULL) {
    memcpy(result.str + i, s->str, s->len);
    i += s->len;
    s = va_arg(args, const String*);
  }
  va_end(args);
  return result;
}
String string_capitalize(const String* str) {
  String result = string_dup(str);
  result.str[0] = (char)toupper(result.str[0]);
  return result;
}
String string_casefold(const String* str) {
  String result = string_dup(str);
  for (size_t i = 0; i < result.len; i++) {
    result.str[i] = (char)tolower(result.str[i]);
  }
  return result;
}
String string_center(const String* str, size_t width) {
  return string_center_fill(str, width, ' ');
}
String string_center_fill(const String* str, size_t width, char fillchar) {
  size_t pad_len = width - str->len;
  size_t pad_left = pad_len / 2;
  size_t pad_right = pad_len - pad_left;
  String result = string_new_len(width);
  memset(result.str, fillchar, pad_left);
  memcpy(result.str + pad_left, str->str, str->len);
  memset(result.str + pad_left + str->len, fillchar, pad_right);
  return result;
}
size_t string_count(const String* str, const String* sub) {
  return string_count_within(str, sub, 0, str->len);
}
size_t string_count_after(const String* str, const String* sub, size_t start) {
  return string_count_within(str, sub, start, str->len);
}
size_t string_count_within(
    const String* str, const String* sub, size_t start, size_t end) {
  size_t count = 0;
  size_t i = start;
  while (i < end) {
    size_t j = 0;
    while (j < sub->len && i + j < end && str->str[i + j] == sub->str[j]) {
      j++;
    }
    if (j == sub->len) {
      count++;
      i += sub->len;
    } else {
      i++;
    }
  }
  return count;
}
bool string_endswith(const String* str, const String* suffix) {
  return string_endswith_within(str, suffix, 0, str->len);
}
bool string_endswith_after(
    const String* str, const String* suffix, size_t start) {
  return string_endswith_within(str, suffix, start, str->len);
}
bool string_endswith_within(
    const String* str, const String* suffix, size_t start, size_t end) {
  if (suffix->len > end - start) {
    return false;
  }
  size_t i = end - suffix->len;
  for (size_t j = 0; j < suffix->len; j++) {
    if (str->str[i + j] != suffix->str[j]) {
      return false;
    }
  }
  return true;
}
String string_expandtabs(const String* str) {
  return string_expandtabs_size(str, 8);
}
String string_expandtabs_size(const String* str, size_t tabsize) {
  String result = string_dup(str);
  size_t i = 0;
  while (i < result.len) {
    if (result.str[i] == '\t') {
      size_t j = i;
      while (j < result.len && result.str[j] == '\t') {
        j++;
      }
      size_t new_len = result.len + (tabsize - (i % tabsize)) - j;
      result.str = STRING_REALLOC(result.str, new_len + 1);
      memmove(result.str + i + tabsize, result.str + j, result.len - j);
      result.len = new_len;
      result.cap = new_len + 1;
    }
    i++;
  }
  return result;
}
size_t string_find(const String* str, const String* sub) {
  return string_find_within(str, sub, 0, str->len);
}
size_t string_find_after(const String* str, const String* sub, size_t start) {
  return string_find_within(str, sub, start, str->len);
}
size_t string_find_within(
    const String* str, const String* sub, size_t start, size_t end) {
  size_t i = start;
  while (i < end) {
    size_t j = 0;
    while (j < sub->len && i + j < end && str->str[i + j] == sub->str[j]) {
      j++;
    }
    if (j == sub->len) {
      return i;
    }
    i++;
  }
  return -1;
}
StringIndexResult string_index(const String* str, const String* sub) {
  return string_index_within(str, sub, 0, str->len);
}
StringIndexResult string_index_after(
    const String* str, const String* sub, size_t start) {
  return string_index_within(str, sub, start, str->len);
}
StringIndexResult string_index_within(
    const String* str, const String* sub, size_t start, size_t end) {
  size_t i = start;
  while (i < end) {
    size_t j = 0;
    while (j < sub->len && i + j < end && str->str[i + j] == sub->str[j]) {
      j++;
    }
    if (j == sub->len) {
      return (StringIndexResult){
          .is_ok = true,
          .u = {.ok = i},
      };
    }
    i++;
  }
  return (StringIndexResult){
      .is_ok = false,
      .u = {.err = STRING_CONSTANT("not found")},
  };
}
bool string_isalnum(const String* str) {
  for (size_t i = 0; i < str->len; i++) {
    if (!isalnum(str->str[i])) {
      return false;
    }
  }
  return true;
}
