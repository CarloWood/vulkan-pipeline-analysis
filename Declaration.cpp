#include "sys.h"
#include "Declaration.h"
#include "ShaderModule.h"

Declaration::Declaration(ShaderModule* owner, utils::RandomNumber& rn, int vi) :
  Generated("Declaration", std::forward_as_tuple(m_set_index_binding_slot, m_a_shader_resource)),
  m_magic(constructed_magic),
  m_owner(owner), m_set_index_binding_slot(this, rn, vi), m_a_shader_resource(this, rn, vi)
{
  DoutEntering(dc::debug, "Declaration::Declaration(" << owner << ", rn, " << vi << ") [" << this << "]");
  bool too_large;
  SetIndexBindingSlot::slot_as_bit_type rejected_slots;
  rejected_slots.reset();
  while (m_a_shader_resource.out_of_range(too_large))
  {
    if (too_large)
      rejected_slots |= m_set_index_binding_slot.slot_as_bit();
    // This should only happen when the slot that was generated is a slot that is used by a previous stage.
    ASSERT(m_set_index_binding_slot.previous_stage());
    m_set_index_binding_slot.init(rn);
    m_a_shader_resource.randomize(rn);
  }
  m_owner->mark_unused_slot(nullptr, rejected_slots, false);
  m_owner->update_layout(*this);
}

#ifdef CWDEBUG
void Declaration::print_on(std::ostream& os) const
{
  ASSERT(m_magic == constructed_magic);
  os << "\n        " << PRINT_TYPE("Declaration") << '{';
  os << "owner:";
  m_owner->print_on_short(os);
  os << ", set_index_binding_slot";
  if (DEBUGCHANNELS::dc::debug.is_on())
    os << "[" << &m_set_index_binding_slot << "]";
  os << ":" << m_set_index_binding_slot <<
      ",\n            a_shader_resource:" << m_a_shader_resource;
  os << '}';
}
#endif
