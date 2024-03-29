#include "sys.h"
#include "ShaderModule.h"
#include "Pipeline.h"

Declaration const* ShaderModule::mark_used_slot(Declaration const* current_declaration, SetIndexBindingSlots::bitset_type slot)
{
  DoutEntering(dc::debug|continued_cf, "ShaderModule::mark_used_slot(" << current_declaration << ", " << slot << ") [" << this << "] = ");
  Declaration const* previous_stage = m_owner->acquire_slot(current_declaration, slot);
  m_available_slots.mark_used(slot);
  Dout(dc::finish, previous_stage);
  return previous_stage;
}

void ShaderModule::mark_unused_slot(Declaration const* current_declaration, SetIndexBindingSlots::bitset_type slot, bool we_are_owner)
{
  DoutEntering(dc::debug, "ShaderModule::mark_unused_slot(" << current_declaration << ", " << slot << ", " << std::boolalpha << we_are_owner << ") [" << this << "]");
  if (we_are_owner)
    m_owner->release_slot(current_declaration, slot);
  m_available_slots.mark_unused(slot);
}

void ShaderModule::update_layout_add(Declaration const& declaration)
{
  m_owner->update_layout_add(declaration);
}

void ShaderModule::update_layout_remove(std::pair<SetIndexIndex, BindingIndex> prev_set_index_binding_slot)
{
  m_owner->update_layout_remove(prev_set_index_binding_slot);
}

#ifdef CWDEBUG
void ShaderModule::print_on(std::ostream& os) const
{
  os << PRINT_TYPE("ShaderModule") << '{';
  os << "stage:" << m_stage <<
      ", declarations:" << m_declarations;
  os << '}';
}

void ShaderModule::print_on_short(std::ostream& os) const
{
  os << "ShaderModule stage " << m_stage;
}
#endif
