#pragma once

#include "utils/has_print_on.h"
#include "debug.h"

using utils::has_print_on::operator<<;

template<typename I>
class Interval
{
 public:
  constexpr Interval(I begin, I end) : m_begin(begin), m_end(end)
  {
    // The interval may not be empty.
    ASSERT(begin < end);
    reset();
  }

  void reset()
  {
    //DoutEntering(dc::notice, demangled_name<I>() << "::reset()");
    m_value = m_begin;
  }

  bool next()
  {
    //DoutEntering(dc::notice, demangled_name<I>() << "::next()");
    //Dout(dc::notice, "m_value = " << m_value);
    ++m_value;
    //Dout(dc::notice, "m_value = " << m_value);
    return m_value < m_end;
  }

  void print_on(std::ostream& os) const
  {
    os << TYPE_COLOR_BEGIN << demangled_name<I>() << TYPE_COLOR_END << '{' << m_value << '}';
  }

 private:
  I const m_begin;
  I const m_end;

 protected:
  I m_value;
};
