#include "sys.h"
#include "SetIndexBindingSlot.h"
#include "ShaderModule.h"

void SetIndexBindingSlot::reset()
{
  DoutEntering(dc::debug, "SetIndexBindingSlot::reset(vi=" << m_vi << ") [" << this << "]");
  m_available_slots_iter = m_owner->owning_shader_module()->available_slots().unused_set_index_binding_slots()();
  m_slot_as_bit = *m_available_slots_iter;
  m_previous_stage = m_owner->owning_shader_module()->mark_used_slot(m_owner, m_slot_as_bit);
  Dout(dc::debug, "Set m_previous_stage [" << &m_previous_stage << "] to " << m_previous_stage);
}

bool SetIndexBindingSlot::next()
{
  Dout(dc::debug|continued_cf, "SetIndexBindingSlot::next(vi=" << m_vi << ") [" << this << "] = ");
  Dout(dc::debug, "Passing !m_previous_stage [" << &m_previous_stage << "] as second argment to mark_unused_slot:");
  m_owner->owning_shader_module()->mark_unused_slot(m_owner, m_slot_as_bit, !m_previous_stage);
  Dout(dc::debug, "Setting m_previous_stage [" << &m_previous_stage << "] to nullptr.");
  m_previous_stage = nullptr;
  m_slot_as_bit = *++m_available_slots_iter;
  bool success = m_slot_as_bit.any();
  if (success)
  {
    m_previous_stage = m_owner->owning_shader_module()->mark_used_slot(m_owner, m_slot_as_bit);
    Dout(dc::debug, "Set m_previous_stage [" << &m_previous_stage << "] to " << m_previous_stage);
  }
  Dout(dc::finish, std::boolalpha << success);
  return success;
}

void SetIndexBindingSlot::randomize(utils::RandomNumber& rn)
{
  DoutEntering(dc::debug, "SetIndexBindingSlot::randomize(rn) [" << this << "]");
  if (m_slot_as_bit.any())
    m_owner->owning_shader_module()->mark_unused_slot(m_owner, m_slot_as_bit, !m_previous_stage);
  auto available_bits = m_owner->owning_shader_module()->available_slots().unused_set_index_binding_slots();
  Dout(dc::debug, "available_bits = " << available_bits);
  m_available_slots_iter = available_bits();
  std::size_t number_of_available_bits = available_bits.count();
  if (number_of_available_bits == 0)
    throw RanOutOfSlots{};
  ASSERT(number_of_available_bits > 0);
  std::uniform_int_distribution<int> dist(0, number_of_available_bits - 1);
  int bit = rn.generate(dist);
  Dout(dc::debug, "Randomly picking bit " << bit);
  while (bit > 0)
  {
    ++m_available_slots_iter;
    --bit;
  }
  m_slot_as_bit = *m_available_slots_iter;
  Dout(dc::debug, "m_slot_as_bit is now " << m_slot_as_bit);
  m_previous_stage = m_owner->owning_shader_module()->mark_used_slot(m_owner, m_slot_as_bit);
}

#ifdef CWDEBUG
void SetIndexBindingSlot::print_on(std::ostream& os) const
{
  std::pair<SetIndexIndex, BindingIndex> set_index_binding_pair = get_set_index_binding();
  os << set_index_binding_pair.first << '.' << set_index_binding_pair.second << " (" << m_vi << ")";
}
#endif
