#pragma once

#include "utils/has_print_on.h"
#include "utils/RandomNumber.h"
#include <array>
#include "debug.h"

using utils::has_print_on::operator<<;

class DescriptorCount
{
 public:
  DescriptorCount() { reset(); }

  void reset()
  {
    //DoutEntering(dc::notice, "DescriptorCount::reset()");
    m_count = -1;
  }

  bool next()
  {
    //DoutEntering(dc::notice, "DescriptorCount::next()");
    if (m_count > 1)
      return false;     // We reached the end of this "range".
    if (m_count == -1)
      m_count = 1;
    else
      m_count = 7;      // Just any value larger than 1. This is the array size.
    return true;
  }

  void randomize(utils::RandomNumber& rn)
  {
    //DoutEntering(dc::notice, "DescriptorCount::randomize()");
    static std::array<int, 3> values = { -1, 1, 7 };
    m_count = values[rn.generate(s_distribution)];
  }

#ifdef CWDEBUG
  void print_on(std::ostream& os) const
  {
    os << TYPE_COLOR_BEGIN "DescriptorCount" TYPE_COLOR_END << "{" << m_count << "}";
  }
#endif

 private:
  static std::uniform_int_distribution<int> s_distribution;
  int m_count;          // -1: unbound array; 1: not an array; otherwise the size of the array.
};
