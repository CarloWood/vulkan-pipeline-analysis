#pragma once

#include <cwds/debug.h>

template<typename T>
char const* demangled_name()
{
  return libcwd::type_info_of<T>().demangled_name();
}

#define TYPE_COLOR_BEGIN "\e[32m"
#define TYPE_COLOR_END "\e[0m"
