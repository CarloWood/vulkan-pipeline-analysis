#pragma once

#include "utils/has_print_on.h"
#include "utils/RandomNumber.h"
#include <array>
#include "debug.h"

#define DISABLE_DESCRIPTOR_COUNT 0

using utils::has_print_on::operator<<;

class DescriptorCount
{
 public:
  DescriptorCount() { reset(); }

  void reset()
  {
#if !DISABLE_DESCRIPTOR_COUNT
    DoutEntering(dc::debug, "DescriptorCount::reset() [" << this << "]");
#endif
    m_count = -1;
  }

  bool next()
  {
#if DISABLE_DESCRIPTOR_COUNT
    return false;
#else
    DoutEntering(dc::debug|continued_cf, "DescriptorCount::next() [" << this << "] = ");
    bool result = true;
    if (m_count > 1)
      result = false;     // We reached the end of this "range".
    else if (m_count == -1)
      m_count = 1;
    else
      m_count = 7;      // Just any value larger than 1. This is the array size.
    Dout(dc::finish, std::boolalpha << result);
    return result;
#endif
  }

  void randomize(utils::RandomNumber& rn)
  {
#if DISABLE_DESCRIPTOR_COUNT
    m_count = -1;
#else
    DoutEntering(dc::debug, "DescriptorCount::randomize() [" << this << "]");
    static std::array<int, 3> values = { -1, 1, 7 };
    m_count = values[rn.generate(s_distribution)];
#endif
  }

  friend bool operator==(DescriptorCount lhs, DescriptorCount rhs)
  {
    return lhs.m_count == rhs.m_count;
  }

#ifdef CWDEBUG
  void print_on(std::ostream& os) const
  {
    os << PRINT_TYPE("DescriptorCount") << '{' << m_count << '}';
  }
#endif

 private:
  static std::uniform_int_distribution<int> s_distribution;
  int m_count;          // -1: unbound array; 1: not an array; otherwise the size of the array.
};
