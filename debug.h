#pragma once

#include <cwds/debug.h>

#ifdef CWDEBUG

template<typename T>
char const* demangled_name()
{
  return libcwd::type_info_of<T>().demangled_name();
}

#define TYPE_COLOR_BEGIN "\e[32m"
#define TYPE_COLOR_END "\e[0m"

#define PRINT_TYPE(typename_str) \
    PrintType(typename_str, this)

struct PrintType
{
  char const* name;
  void const* obj_ptr;

  PrintType(char const* name_, void const* obj_ptr_) : name(name_), obj_ptr(obj_ptr_) { }
};

inline std::ostream& operator<<(std::ostream& os, PrintType const& pt)
{
  os << TYPE_COLOR_BEGIN << pt.name << TYPE_COLOR_END;
  if (DEBUGCHANNELS::dc::debug.is_on())
    os << '[' << pt.obj_ptr << ']';
  return os;
}

#endif // CWDEBUG
