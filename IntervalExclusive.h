#pragma once

#include "utils/BitSet.h"
#include "utils/Vector.h"
#include "utils/has_print_on.h"
#include "utils/RandomNumber.h"
#include "utils/is_specialization_of.h"
#include <type_traits>
#include "debug.h"

using utils::has_print_on::operator<<;

template<typename I>
class IntervalExclusive
{
 public:
  using bitset_type = utils::BitSet<uint32_t>;
  using value_as_bit_type = bitset_type;
  using const_iterator = utils::bitset::const_iterator<value_as_bit_type::mask_type>;

  // Initialization happens by the call to reset(), which must be done from the constructor of the derived class.
  IntervalExclusive() = default;

  void reset();
  bool next();
  void randomize(utils::RandomNumber& rn);

#ifdef CWDEBUG
  void print_on(std::ostream& os) const
  {
    os << TYPE_COLOR_BEGIN << demangled_name() << TYPE_COLOR_END << '{' << get_value() << '}';
  }
#endif

  I get_value() const
  {
    utils::bitset::Index bit_index = m_value_as_bit.lssbi();
    if constexpr (std::is_same_v<I, utils::bitset::Index>)
      return bit_index;
    else
      return I{static_cast<size_t>(bit_index())};
  }

  virtual int get_vi() const = 0;
  virtual char const* demangled_name() const = 0;
  virtual bitset_type available_values() const = 0;
  virtual void mark_unused_values(bitset_type values) const = 0;
  virtual void mark_used_values(bitset_type values) const = 0;

 private:
  const_iterator m_available_values_iter;
  value_as_bit_type m_value_as_bit;
};

template<typename I>
void IntervalExclusive<I>::reset()
{
#if 0 //def CWDEBUG
  DoutEntering(dc::notice|continued_cf, demangled_name() << "::reset(");
  int vi = get_vi();
  if (vi != -1)
    Dout(dc::continued, vi);
#endif
  m_available_values_iter = available_values()();
  m_value_as_bit = *m_available_values_iter;
  //Dout(dc::finish, ") --> " << *this);
  mark_used_values(m_value_as_bit);
}

template<typename I>
bool IntervalExclusive<I>::next()
{
#if 0 //def CWDEBUG
  Dout(dc::notice|continued_cf, demangled_name() << "::next(");
  int vi = get_vi();
  if (vi != -1)
    Dout(dc::continued, vi);
#endif
  mark_unused_values(m_value_as_bit);
  m_value_as_bit = *++m_available_values_iter;
  //Dout(dc::finish, ") --> " << *this);
  mark_used_values(m_value_as_bit);
  return m_value_as_bit.any();
}

template<typename I>
void IntervalExclusive<I>::randomize(utils::RandomNumber& rn)
{
  bitset_type available_bits = available_values();
  m_available_values_iter = available_bits();
  std::size_t number_of_available_bits = available_bits.count();
  ASSERT(number_of_available_bits > 0);
  std::uniform_int_distribution<int> dist(0, number_of_available_bits - 1);
  int bit = rn.generate(dist);
  while (bit > 0)
  {
    ++m_available_values_iter;
    --bit;
  }
  m_value_as_bit = *m_available_values_iter;
  mark_used_values(m_value_as_bit);
}
