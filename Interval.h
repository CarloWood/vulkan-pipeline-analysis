#pragma once

#include "utils/BitSet.h"
#include "utils/Vector.h"
#include "utils/has_print_on.h"
#include "utils/RandomNumber.h"
#include "utils/is_specialization_of.h"
#include <type_traits>
#include "debug.h"

using utils::has_print_on::operator<<;

template<typename T>
concept ConceptIsBitSetIndex = std::is_same_v<T, utils::bitset::Index>;

template<typename T>
inline constexpr bool is_vector_index = utils::is_specialization_of_v<T, utils::VectorIndex>;

template<typename I>
concept ConceptIsVectorIndex = is_vector_index<I>;

template<typename I>
class Interval
{
 public:
  template<ConceptIsBitSetIndex T = I>
  constexpr Interval(I begin, I end) : m_distribution(begin(), end() - 1), m_begin(begin), m_end(end), m_value(begin)
  {
    // The interval may not be empty.
    ASSERT(begin < end);
  }

  template<ConceptIsVectorIndex VECTORINDEX = I>
  constexpr Interval(I begin, I end) : m_distribution(begin.get_value(), end.get_value() - 1), m_begin(begin), m_end(end), m_value(begin)
  {
    // The interval may not be empty.
    ASSERT(begin < end);
  }

  void reset()
  {
    DoutEntering(dc::debug, demangled_name() << "::reset() [" << this << "]");
    m_value = m_begin;
  }

  bool next()
  {
    DoutEntering(dc::debug|continued_cf, demangled_name() << "::next() [" << this << "] = ");
    Dout(dc::debug, "m_value " << m_value << " --> " << (m_value + 1));
    ++m_value;
    bool result = m_value < m_end;
    Dout(dc::finish, std::boolalpha << result);
    return result;
  }

  void randomize(utils::RandomNumber& rn)
  {
    DoutEntering(dc::debug, demangled_name() << "::randomize() [" << this << "]");
    if constexpr (std::is_same_v<I, utils::bitset::Index>)
    {
      utils::bitset::IndexPOD index{rn.generate(m_distribution)};
      m_value = I{index};
    }
    else
      m_value = I{static_cast<size_t>(rn.generate(m_distribution))};
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

  virtual char const* demangled_name() const = 0;

 private:
  I const m_begin;
  I const m_end;

 protected:
  std::uniform_int_distribution<int8_t> m_distribution;
  I m_value;
};
