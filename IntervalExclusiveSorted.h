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
    //DoutEntering(dc::notice, demangled_name() << "::reset()");
    m_begin = get_sorted_begin();       // Should return m_value of the previous loop plus 1,
                                        // or the real begin value when there is no previous loop.
    m_end = get_sorted_end();           // Should return the read end minus the number of more inner loops that follow.
    m_value = m_begin;
  }

  bool next()
  {
    //DoutEntering(dc::notice, demangled_name() << "::next()");
    //Dout(dc::notice, "m_value = " << m_value);
    ++m_value;
    //Dout(dc::notice, "m_value = " << m_value);
    return m_value < m_end;
  }

  void randomize(utils::RandomNumber& rn)
  {
    //DoutEntering(dc::notice, demangled_name() << "::randomize()");
    if constexpr (std::is_same_v<I, utils::bitset::Index>)
    {
      utils::bitset::IndexPOD index{rn.generate(m_distribution)};
      m_value = I{index};
    }
    else
      m_value = I{static_cast<size_t>(rn.generate(m_distribution))};
  }

  void print_on(std::ostream& os) const
  {
    os << TYPE_COLOR_BEGIN << demangled_name() << TYPE_COLOR_END << '{' << m_value << '}';
  }

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
  std::uniform_int_distribution<int8_t> m_distribution;
  I m_value;
};
