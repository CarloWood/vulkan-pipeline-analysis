#include "sys.h"
#include "Pipeline.h"
#include "debug.h"

Declaration const* Pipeline::acquire_slot(Declaration const* current_declaration, SetIndexBindingSlots::bitset_type slot)
{
  utils::bitset::Index i = slot.lssbi();
  Declaration const* previous_stage = m_slot_owner[i()];
  if (!previous_stage)
    m_slot_owner[i()] = current_declaration;
  // Return the previous stage if we're not the owner.
  return previous_stage;
}

void Pipeline::release_slot(Declaration const* current_declaration, SetIndexBindingSlots::bitset_type slot)
{
  utils::bitset::Index i = slot.lssbi();
  // Only the current owner, that called acquire_slot, may release the slot again.
  ASSERT(m_slot_owner[i()] == current_declaration);
  m_slot_owner[i()] = nullptr;
}

#ifdef CWDEBUG
void Pipeline::print_on(std::ostream& os) const
{
  os << PRINT_TYPE("Pipeline") << '{';
  os << "stages:" << m_stages << ",\n    layout:" << m_layout;
  os << "\n    }";
}
#endif
