#include "sys.h"
#include "Pipeline.h"
#include "debug.h"

ShaderModule const* Pipeline::acquire_slot(ShaderModule const* shader_module, SetIndexBindingSlots::bitset_type slot)
{
  utils::bitset::Index i = slot.lssbi();
  ShaderModule const* previous_stage = m_slot_owner[i()];
  if (!previous_stage)
    m_slot_owner[i()] = shader_module;
  // Return true if now we are the owner.
  return previous_stage;
}

void Pipeline::release_slot(ShaderModule const* shader_module, SetIndexBindingSlots::bitset_type slot)
{
  utils::bitset::Index i = slot.lssbi();
  // Only the current owner, that called acquire_slot, may release the slot again.
  ASSERT(m_slot_owner[i()] == shader_module);
  m_slot_owner[i()] = nullptr;
}

#ifdef CWDEBUG
void Pipeline::print_on(std::ostream& os) const
{
  os << TYPE_COLOR_BEGIN "Pipeline" TYPE_COLOR_END "{";
  os << "stages:" << m_stages ;//<<
//      ",\n    layout:" << m_layout;
  os << "\n    }";
}
#endif
