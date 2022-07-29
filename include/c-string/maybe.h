#pragma once

#define MAYBE_T(T) \
  struct { \
    T value; \
    bool has_value; \
  }
