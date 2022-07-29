#pragma once

#define RESULT_T(T, E) \
  struct { \
    bool is_ok; \
    union { \
      T ok; \
      E err; \
    } u; \
  }
