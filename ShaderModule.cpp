#include "sys.h"
#include "ShaderModule.h"
#include "Pipeline.h"

ShaderModule const* ShaderModule::mark_used_slot(SetIndexBindingSlots::bitset_type slot)
{
  ShaderModule const* previous_stage = m_owner->acquire_slot(this, slot);
  m_available_slots.mark_used(slot);
  return previous_stage;
}

void ShaderModule::mark_unused_slot(SetIndexBindingSlots::bitset_type slot, bool we_are_owner)
{
  if (we_are_owner)
    m_owner->release_slot(this, slot);
  m_available_slots.mark_unused(slot);
}

#ifdef CWDEBUG
void ShaderModule::print_on(std::ostream& os) const
{
  os << TYPE_COLOR_BEGIN "ShaderModule" TYPE_COLOR_END "{";
  os << "stage:" << m_stage <<
      ", declarations:" << m_declarations;
  os << '}';
}

void ShaderModule::print_on_short(std::ostream& os) const
{
  os << "ShaderModule stage " << m_stage;
}
#endif
