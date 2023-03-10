#include "sys.h"
#include "SetIndexBindingSlot.h"
#include "ShaderModule.h"

void SetIndexBindingSlot::reset()
{
  Dout(dc::notice|continued_cf, "SetIndexBindingSlot::reset(" << m_vi << ") --> ");
  m_available_slots_iter = m_owner->available_slots().unused_set_index_binding_slots()();
  m_slot_as_bit = *m_available_slots_iter;
  Dout(dc::finish, *this);
  m_owner->mark_used(m_slot_as_bit);
}

bool SetIndexBindingSlot::next()
{
  Dout(dc::notice|continued_cf, "SetIndexBindingSlot::next(" << m_vi << ") --> ");
  m_owner->mark_unused(m_slot_as_bit);
  m_slot_as_bit = *++m_available_slots_iter;
  Dout(dc::finish, *this);
  m_owner->mark_used(m_slot_as_bit);
  return m_slot_as_bit.any();
}

void SetIndexBindingSlot::randomize(utils::RandomNumber& rn)
{
  auto available_bits = m_owner->available_slots().unused_set_index_binding_slots();
  m_available_slots_iter = available_bits();
  std::size_t number_of_available_bits = available_bits.count();
  ASSERT(number_of_available_bits > 0);
  std::uniform_int_distribution<int> dist(0, number_of_available_bits - 1);
  int bit = rn.generate(dist);
  while (bit > 0)
  {
    ++m_available_slots_iter;
    --bit;
  }
  m_slot_as_bit = *m_available_slots_iter;
  m_owner->mark_used(m_slot_as_bit);
}

void SetIndexBindingSlot::print_on(std::ostream& os) const
{
  std::pair<SetIndexIndex, BindingIndex> set_index_binding_pair = get_set_index_binding(get_bitset());
  os << set_index_binding_pair.first << '.' << set_index_binding_pair.second << " (" << m_vi << ")";
}
