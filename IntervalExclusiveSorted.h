#pragma once

#include "utils/BitSet.h"
#include "utils/Vector.h"
#include "utils/has_print_on.h"
#include "utils/RandomNumber.h"
#include "utils/is_specialization_of.h"
#include <type_traits>
#include "debug.h"

#if -0

// The following shows how reset() and next() are called in the case of
// three (nested) IntervalExclusiveSorted objects, L0, L1 and L2.
bool success0 = true;
for (L0.reset(); success0; success0 = L0.next())
{
  bool success1 = true;
  for (L1.reset(); success1; success1 = L1.next())
  {
    bool success2 = true;
    for (L2.reset(); L2 < E; success2 = L2.next())
    {
    }
  }
}

// What that should mimic the following:
for (L0 = 0; L0 < E - 2; ++L0)
{
  for (L1 = L0 + 1; L1 < E - 1; ++L1)
  {
    for (L2 = L1 + 1; L2 < E; ++L2)
    {
    }
  }
}

#endif

using utils::has_print_on::operator<<;

template<typename I>
class IntervalExclusiveSorted
{
 public:
  void reset()
  {
    DoutEntering(dc::debug, demangled_name() << "::reset() [" <<  this << "]");
    m_begin = get_sorted_begin();       // Should return m_value of the previous loop plus 1,
                                        // or the real begin value when there is no previous loop.
    m_end = get_sorted_end();           // Should return the read end minus the number of more inner loops that follow.
    m_value = m_begin;
    Dout(dc::debug, "m_value --> " << m_value);
  }

  bool next()
  {
    DoutEntering(dc::debug|continued_cf, demangled_name() << "::next() [" <<  this << "] = ");
    Dout(dc::debug, "m_value " << m_value << " --> " << (m_value + 1));
    ++m_value;
    bool result = m_value < m_end;
    Dout(dc::finish, std::boolalpha << result);
    return result;
  }

  void randomize(utils::RandomNumber& rn)
  {
    //DoutEntering(dc::debug, demangled_name() << "::randomize()");
    m_begin = get_sorted_begin();
    m_end = get_sorted_end();
    ASSERT(m_begin < m_end);
    if (m_begin == m_end - 1)
      m_value = m_begin;
    else
    {
      if constexpr (std::is_same_v<I, utils::bitset::Index>)
      {
        std::uniform_int_distribution<int8_t> distribution(m_begin(), m_end() - 1);
        utils::bitset::IndexPOD index{rn.generate(distribution)};
        m_value = I{index};
      }
      else
      {
        std::uniform_int_distribution<int8_t> distribution(m_begin.get_value(), m_end.get_value() - 1);
        m_value = I{static_cast<size_t>(rn.generate(distribution))};
      }
    }
  }

#ifdef CWDEBUG
  void print_on(std::ostream& os) const
  {
    os << PRINT_TYPE(demangled_name()) << '{' << m_value << '}';
  }
#endif

  I get_value() const
  {
    return m_value;
  }

  virtual I get_sorted_begin() const = 0;
  virtual I get_sorted_end() const = 0;
  virtual char const* demangled_name() const = 0;
  virtual int get_vi() const = 0;

 private:
  I m_begin;
  I m_end;

 protected:
  I m_value;
};
