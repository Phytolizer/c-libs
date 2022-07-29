#include "c-string/c-string.h"

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
