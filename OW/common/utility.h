#pragma once

#include <string>

#define _TSTR(s) _T(s)
#define _NSTR(s) s     // Narrow string
#define _WSTR(s) _L(s) // Wide string

// Standard text types:
typedef char char_t;
typedef const char_t LiteralString[];
typedef std::basic_string<char_t> tstring;

#define IS_CSTR_EMPTY(s) (s == nullptr || s[0] == '\0')

#define ENUM_INDEX(enumVal) (static_cast<size_t>(enumVal))
#define COUNTOF(array) _countof(array)

#ifndef NDEBUG
#	define TODO(s) /* Don't release without it. */
#endif
