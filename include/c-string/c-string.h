#pragma once

#include "c-string/result.h"

#include <stdbool.h>
#include <stddef.h>

#ifndef STRING_MALLOC
#define STRING_MALLOC(size) malloc(size)
#endif

#ifndef STRING_CALLOC
#define STRING_CALLOC(count, size) calloc(count, size)
#endif

#ifndef STRING_REALLOC
#define STRING_REALLOC(ptr, size) realloc(ptr, size)
#endif

typedef struct {
  char* str;
  size_t len;
  size_t cap;
} String;

// #define STRING_ENCODINGS_X \
//   X(ASCII, Y("ascii", "646", "us-ascii"), ascii) \
//   X(BIG5, Y("big5", "big5-tw", "csbig5"), big5) \
//   X(BIG5HKSCS, Y("big5hkscs", "big5-hkscs", "hkscs"), big5hkscs) \
//   X(CP037, Y("cp037", "IBM037", "IBM039"), cp037) \
//   X(CP273, Y("cp273", "IBM273", "csIBM273"), cp273) \
//   X(CP424, Y("cp424", "EBCDIC-CP-HE", "IBM424"), cp424) \
//   X(CP437, Y("cp437", "437", "IBM437"), cp437) \
//   X(CP500, Y("cp500", "EBCDIC-CP-BE", "EBCDIC-CP-CH", "IBM500"), cp500) \
//   X(CP720, Y("cp720"), cp720) \
//   X(CP737, Y("cp737"), cp737) \
//   X(CP775, Y("cp775", "IBM775"), cp775) \
//   X(CP850, Y("cp850", "850", "IBM850"), cp850) \
//   X(CP852, Y("cp852", "852", "IBM852"), cp852) \
//   X(CP855, Y("cp855", "855", "IBM855"), cp855) \
//   X(CP856, Y("cp856"), cp856) \
//   X(CP857, Y("cp857", "857", "IBM857"), cp857) \
//   X(CP858, Y("cp858", "858", "IBM858"), cp858) \
//   X(CP860, Y("cp860", "860", "IBM860"), cp860) \
//   X(CP861, Y("cp861", "861", "CP-IS", "IBM861"), cp861) \
//   X(CP862, Y("cp862", "862", "IBM862"), cp862) \
//   X(CP863, Y("cp863", "863", "IBM863"), cp863) \
//   X(CP864, Y("cp864", "IBM864"), cp864) \
//   X(CP865, Y("cp865", "865", "IBM865"), cp865) \
//   X(CP866, Y("cp866", "866", "IBM866"), cp866) \
//   X(CP869, Y("cp869", "869", "CP-GR", "IBM869"), cp869) \
//   X(CP874, Y("cp874"), cp874) \
//   X(CP875, Y("cp875"), cp875) \
//   X(CP932, Y("cp932", "932", "ms932", "mskanji", "ms-kanji"), cp932) \
//   X(CP949, Y("cp949", "949", "ms949", "uhc"), cp949) \
//   X(CP950, Y("cp950", "950", "ms950"), cp950) \
//   X(CP1006, Y("cp1006"), cp1006) \
//   X(CP1026, Y("cp1026", "ibm1026"), cp1026) \
//   X(CP1125, Y("cp1125", "1125", "ibm1125", "cp866u", "ruscii"), cp1125) \
//   X(CP1140, Y("cp1140", "ibm1140"), cp1140) \
//   X(CP1250, Y("cp1250", "windows-1250"), cp1250) \
//   X(CP1251, Y("cp1251", "windows-1251"), cp1251) \
//   X(CP1252, Y("cp1252", "windows-1252"), cp1252) \
//   X(CP1253, Y("cp1253", "windows-1253"), cp1253) \
//   X(CP1254, Y("cp1254", "windows-1254"), cp1254) \
//   X(CP1255, Y("cp1255", "windows-1255"), cp1255) \
//   X(CP1256, Y("cp1256", "windows-1256"), cp1256) \
//   X(CP1257, Y("cp1257", "windows-1257"), cp1257) \
//   X(CP1258, Y("cp1258", "windows-1258"), cp1258) \
//   X(EUC_JP, Y("euc_jp", "eucjp", "ujis", "u-jis"), euc_jp) \
//   X(EUC_JIS_2004, Y("euc_jis_2004", "jisx0213", "eucjis2004"), euc_jis_2004) \
//   X(EUC_JISX0213, Y("euc_jisx0213", "eucjisx0213"), euc_jisx0213) \
//   X(EUC_KR, \
//       Y("euc_kr", \
//           "euckr", \
//           "korean", \
//           "ksc5601", \
//           "ks_c-5601", \
//           "ks_c-5601-1987", \
//           "ksx1001", \
//           "ks_x-1001"), \
//       euc_kr) \
//   X(GB2312, \
//       Y("gb2312", \
//           "chinese", \
//           "csiso58gb231280", \
//           "euc-cn", \
//           "euccn", \
//           "eucgb2312-cn", \
//           "gb2312-1980", \
//           "gb2312-80", \
//           "iso-ir-58"), \
//       gp2312) \
//   X(GBK, Y("gbk", "936", "cp936", "ms936"), gbk) \
//   X(GB18030, Y("gb18030", "gb18030-2000"), gb18030) \
//   X(HZ, Y("hz", "hzgb", "hz-gb", "hz-gb-2312"), hz) \
//   X(ISO2022_JP, \
//       Y("iso2022_jp", "csiso2022jp", "iso2022jp", "iso-2022-jp"), \
//       iso2022_jp) \
//   X(ISO2022_JP_1, \
//       Y("iso2022_jp_1", "iso2022jp-1", "iso-2022-jp-1"), \
//       iso2022_jp_1) \
//   X(ISO2022_JP_2, \
//       Y("iso2022_jp_2", "iso2022jp-2", "iso2022-jp-2"), \
//       iso2022_jp_2) \
//   X(ISO2022_JP_2004, \
//       Y("iso2022_jp_2004", "iso2022jp-2004", "iso-2022-jp-2004"), \
//       iso2022_jp_2004) \
//   X(ISO2022_JP_3, \
//       Y("iso2022_jp_3", "iso2022jp-3", "iso-2022-jp-3"), \
//       iso2022_jp_3) \
//   X(ISO2022_JP_EXT, \
//       Y("iso2022_jp_ext", "iso2022jp-ext", "iso-2022-jp-ext"), \
//       iso2022_jp_ext) \
//   X(ISO2022_KR, \
//       Y("iso2022_kr", "csiso2022kr", "iso2022kr", "iso-2022-kr"), \
//       iso2022_kr) \
//   X(LATIN_1, \
//       Y("latin_1", \
//           "iso-8859-1", \
//           "iso8859-1", \
//           "8859", \
//           "cp819", \
//           "latin", \
//           "latin1", \
//           "L1"), \
//       latin_1) \
//   X(ISO8859_2, Y("iso8859_2", "iso-8859-2", "latin2", "L2"), iso8859_2) \
//   X(ISO8859_3, Y("iso8859_3", "iso-8859-3", "latin3", "L3"), iso8859_3) \
//   X(ISO8859_4, Y("iso8859_4", "iso-8859-4", "latin4", "L4"), iso8859_4) \
//   X(ISO8859_5, Y("iso8859_5", "iso-8859-5", "cyrillic"), iso8859_5) \
//   X(ISO8859_6, Y("iso8859_6", "iso-8859-6", "arabic"), iso8859_6) \
//   X(ISO8859_7, Y("iso8859_7", "iso-8859-7", "greek", "greek8"), iso8859_7) \
//   X(ISO8859_8, Y("iso8859_8", "iso-8859-8", "hebrew"), iso8859_8) \
//   X(ISO8859_9, Y("iso8859_9", "iso-8859-9", "latin5", "L5"), iso8859_9) \
//   X(ISO8859_10, Y("iso8859_10", "iso-8859-10", "latin6", "L6"), iso8859_10) \
//   X(ISO8859_11, Y("iso8859_11", "iso-8859-11", "thai"), iso8859_11) \
//   X(ISO8859_13, Y("iso8859_13", "iso-8859-13", "latin7", "L7"), iso8859_13) \
//   X(ISO8859_14, Y("iso8859_14", "iso-8859-14", "latin8", "L8"), iso8859_14) \
//   X(ISO8859_15, Y("iso8859_15", "iso-8859-15", "latin9", "L9"), iso8859_15) \
//   X(ISO8859_16, Y("iso8859_16", "iso-8859-16", "latin10", "L10"), iso8859_16) \
//   X(JOHAB, Y("johab", "cp1361", "ms1361"), johab) \
//   X(KOI8_R, Y("koi8_r"), koi8_r) \
//   X(KOI8_T, Y("koi8_t"), koi8_t) \
//   X(KOI8_U, Y("koi8_u"), koi8_u) \
//   X(KZ1048, Y("kz1048", "kz_1048", "strk1048_2002", "rk1048"), kz1048) \
//   X(MAC_CYRILLIC, Y("mac_cyrillic", "maccyrillic"), mac_cyrillic) \
//   X(MAC_GREEK, Y("mac_greek", "macgreek"), mac_greek) \
//   X(MAC_ICELAND, Y("mac_iceland", "maciceland"), mac_iceland) \
//   X(MAC_LATIN2, \
//       Y("mac_latin2", "maclatin2", "maccentraleurope", "mac_centeuro"), \
//       mac_latin2) \
//   X(MAC_ROMAN, Y("mac_roman", "macroman", "macintosh"), mac_roman) \
//   X(MAC_TURKISH, Y("mac_turkish", "macturkish"), mac_turkish) \
//   X(PTCP154, \
//       Y("ptcp154", "csptcp154", "pt154", "cp154", "cyrillic-asian"), \
//       ptcp154) \
//   X(SHIFT_JIS, \
//       Y("shift_jis", "csshiftjis", "shiftjis", "sjis", "s_jis"), \
//       shift_jis) \
//   X(SHIFT_JIS_2004, \
//       Y("shift_jis_2004", "shiftjis2004", "sjis_2004", "sjis2004"), \
//       shift_jis_2004) \
//   X(SHIFT_JISX0213, \
//       Y("shift_jisx0213", "shiftjisx0213", "sjisx0213", "s_jisx0213"), \
//       shift_jisx0213) \
//   X(UTF_32, Y("utf_32", "U32", "utf32"), utf_32) \
//   X(UTF_32_BE, Y("utf_32_be", "UTF-32BE"), utf_32_be) \
//   X(UTF_32_LE, Y("utf_32_le", "UTF-32LE"), utf_32_le) \
//   X(UTF_16, Y("utf_16", "U16", "utf16"), utf_16) \
//   X(UTF_16_BE, Y("utf_16_be", "UTF-16BE"), utf_16_be) \
//   X(UTF_16_LE, Y("utf_16_le", "UTF-16LE"), utf_16_le) \
//   X(UTF_7, Y("utf_7", "U7", "unicode-1-1-utf-7"), utf_7) \
//   X(UTF_8, Y("utf_8", "U8", "UTF", "utf8", "cp65001"), utf_8) \
//   X(UTF_8_SIG, Y("utf_8_sig"), utf_8_sig)

// typedef enum {
//   STRING_ENCODING_INVALID,
// #define X(x, _y, _z) STRING_ENCODING_##x,
//   STRING_ENCODINGS_X
// #undef X
// } StringEncoding;

void string_init_globals(void);
void string_free_globals(void);
String string_new(void);
String string_new_len(size_t len);
String string_from_cstr(const char* cstr);
String string_from_bytes(const char* bytes, size_t len);
String string_dup(const String* str);
void string_free(String* str);
String string_concat(const String* a, const String* b);
String string_concat_many(const String* first, ...);

String string_capitalize(const String* str);
String string_casefold(const String* str);
String string_center(const String* str, size_t width);
String string_center_fill(const String* str, size_t width, char fillchar);
size_t string_count(const String* str, const String* sub);
size_t string_count_after(const String* str, const String* sub, size_t start);
size_t string_count_within(
    const String* str, const String* sub, size_t start, size_t end);
// TODO: #1 better abstraction for separating bytestrings and Unicode strings
// String string_decode(const char* encoding, const String* str);
bool string_endswith(const String* str, const String* suffix);
bool string_endswith_after(
    const String* str, const String* suffix, size_t start);
bool string_endswith_within(
    const String* str, const String* suffix, size_t start, size_t end);
String string_expandtabs(const String* str);
String string_expandtabs_size(const String* str, size_t tabsize);
size_t string_find(const String* str, const String* sub);
size_t string_find_after(const String* str, const String* sub, size_t start);
size_t string_find_within(
    const String* str, const String* sub, size_t start, size_t end);
// TODO: #2 String string_format(const String* str, ...);
typedef RESULT_T(size_t, String) StringIndexResult;
StringIndexResult string_index(const String* str, const String* sub);
StringIndexResult string_index_after(
    const String* str, const String* sub, size_t start);
StringIndexResult string_index_within(
    const String* str, const String* sub, size_t start, size_t end);
bool string_isalnum(const String* str);
bool string_isalpha(const String* str);
bool string_isascii(const String* str);
bool string_isdecimal(const String* str);
bool string_isdigit(const String* str);
bool string_isidentifier(const String* str);
bool string_islower(const String* str);
bool string_isnumeric(const String* str);
bool string_isprintable(const String* str);
bool string_isspace(const String* str);
bool string_istitle(const String* str);
bool string_isupper(const String* str);
String string_join(const String* sep, const String* first, ...);
String string_ljust(const String* str, size_t width);
String string_ljust_char(const String* str, size_t width, char fillchar);
String string_lower(const String* str);
String string_lstrip(const String* str);
String string_lstrip_chars(const String* str, const String* chars);
typedef struct {
  String left;
  String center;
  String right;
} StringPartitionResult;
StringPartitionResult string_partition(const String* str, const String* sep);
String string_removeprefix(const String* str, const String* prefix);
String string_removesuffix(const String* str, const String* suffix);
String string_replace(const String* str, const String* old, const String* new);
String string_replace_count(
    const String* str, const String* old, const String* new, size_t count);
size_t string_rfind(const String* str, const String* sub);
size_t string_rfind_after(const String* str, const String* sub, size_t start);
size_t string_rfind_within(
    const String* str, const String* sub, size_t start, size_t end);
StringIndexResult string_rindex(const String* str, const String* sub);
StringIndexResult string_rindex_after(
    const String* str, const String* sub, size_t start);
StringIndexResult string_rindex_within(
    const String* str, const String* sub, size_t start, size_t end);
String string_rjust(const String* str, size_t width);
String string_rjust_char(const String* str, size_t width, char fillchar);
StringPartitionResult string_rpartition(const String* str, const String* sep);
size_t string_rsplit(
    const String* str, String* out_buffer, size_t out_buffer_size);
size_t string_rsplit_sep(const String* str,
    const String* sep,
    String* out_buffer,
    size_t out_buffer_len);
size_t string_rsplit_max(const String* str,
    size_t maxsplit,
    String* out_buffer,
    size_t out_buffer_len);
size_t string_rsplit_sep_max(const String* str,
    const String* sep,
    size_t maxsplit,
    String* out_buffer,
    size_t out_buffer_len);
String string_rstrip(const String* str);
String string_rstrip_chars(const String* str, const String* chars);
size_t string_split(
    const String* str, String* out_buffer, size_t out_buffer_size);
size_t string_split_sep(const String* str,
    const String* sep,
    String* out_buffer,
    size_t out_buffer_len);
size_t string_split_max(const String* str,
    size_t maxsplit,
    String* out_buffer,
    size_t out_buffer_len);
size_t string_split_sep_max(const String* str,
    const String* sep,
    size_t maxsplit,
    String* out_buffer,
    size_t out_buffer_len);
size_t string_splitlines(
    const String* str, String* out_buffer, size_t out_buffer_size);
size_t string_splitlines_keepends(
    const String* str, String* out_buffer, size_t out_buffer_size);
bool string_startswith(const String* str, const String* prefix);
bool string_startswith_after(
    const String* str, const String* prefix, size_t start);
bool string_startswith_within(
    const String* str, const String* prefix, size_t start, size_t end);
String string_strip(const String* str);
String string_strip_chars(const String* str, const String* chars);
String string_swapcase(const String* str);
String string_title(const String* str);
// TODO: #3 String string_translate(const String* str, const
// StringTranslationTable* table);

#define STRING_CONSTANT(cstr) \
  { .str = cstr, .len = sizeof(cstr) - 1, .cap = sizeof(cstr) }
#define STRING_EXPR(cstr) (String) STRING_CONSTANT(cstr)
#define STRING_CONCAT_MANY(...) string_concat_many(__VA_ARGS__, NULL)

extern String gSTRING_ASCII_LETTERS;
extern String gSTRING_ASCII_LOWERCASE;
extern String gSTRING_ASCII_UPPERCASE;
extern String gSTRING_DIGITS;
extern String gSTRING_HEXDIGITS;
extern String gSTRING_OCTDIGITS;
extern String gSTRING_PUNCTUATION;
extern String gSTRING_PRINTABLE;
extern String gSTRING_WHITESPACE;
