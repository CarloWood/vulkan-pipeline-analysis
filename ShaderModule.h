#pragma once

#include "Declarations.h"
#include "ShaderStageFlags.h"
#include "Generated.h"
#include "SetIndexBindingSlots.h"
#include "utils/has_print_on.h"
#include <vector>

static constexpr utils::bitset::IndexPOD index_end{number_of_stages};
using utils::bitset::index_begin;

using utils::has_print_on::operator<<;

class ShaderModule : public Generated<std::tuple<Declarations&>>
{
 public:
  ShaderModule(ShaderStageFlagBits stage) : Generated("ShaderModule", std::forward_as_tuple(m_declarations)), m_stage(stage), m_declarations(this)
  {
    ASSERT(index_begin <= stage && stage < index_end);
  }

  void mark_used(SetIndexBindingSlots::bitset_type slots)
  {
    m_available_slots.mark_used(slots);
  }

  void mark_unused(SetIndexBindingSlots::bitset_type slots)
  {
    m_available_slots.mark_unused(slots);
  }

  void allow_all_slots()
  {
    m_available_slots.allow_all();
  }

  void print_on(std::ostream& os) const;

  SetIndexBindingSlots available_slots() const
  {
    return m_available_slots;
  }

 private:
  ShaderStageFlagBits const m_stage;            // The stage that this shader module is intended for (fixed).
  SetIndexBindingSlots m_available_slots;       // The set index / binding slots that are not used yet.
  Declarations m_declarations;                  // The declarations that this shader module is using.
};
