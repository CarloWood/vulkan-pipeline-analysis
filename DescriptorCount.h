#pragma once

#include "utils/has_print_on.h"

using utils::has_print_on::operator<<;

class DescriptorCount
{
 public:
  DescriptorCount() { reset(); }

  void reset()
  {
    m_count = -1;
  }

  bool next()
  {
    if (m_count > 1)
      return false;     // We reached the end of this "range".
    if (m_count == -1)
      m_count = 1;
    else
      m_count = 7;      // Just any value larger than 1. This is the array size.
    return true;
  }

  void print_on(std::ostream& os) const
  {
    os << m_count;
  }

 private:
  int m_count;          // -1: unbound array; 1: not an array; otherwise the size of the array.
};
