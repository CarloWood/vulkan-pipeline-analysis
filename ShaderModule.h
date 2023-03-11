#pragma once

#include "Declarations.h"
#include "ShaderStageFlags.h"
#include "Generated.h"
#include "SetIndexBindingSlots.h"
#include "ShaderResources.h"
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

  void allow_all()
  {
    m_available_slots.allow_all();
    m_available_shader_resources.allow_all();
  }

  void mark_used_slots(SetIndexBindingSlots::bitset_type slots)
  {
    m_available_slots.mark_used(slots);
  }

  void mark_unused_slots(SetIndexBindingSlots::bitset_type slots)
  {
    m_available_slots.mark_unused(slots);
  }

  void mark_used_shader_resources(ShaderResources::bitset_type shader_resources)
  {
    m_available_shader_resources.mark_used(shader_resources);
  }

  void mark_unused_shader_resources(ShaderResources::bitset_type shader_resources)
  {
    m_available_shader_resources.mark_unused(shader_resources);
  }

  void print_on(std::ostream& os) const;

  SetIndexBindingSlots available_slots() const
  {
    return m_available_slots;
  }

  ShaderResources available_shader_resources() const
  {
    return m_available_shader_resources;
  }

 private:
  ShaderStageFlagBits const m_stage;            // The stage that this shader module is intended for (fixed).
  SetIndexBindingSlots m_available_slots;       // The set index / binding slots that are not used yet.
  ShaderResources m_available_shader_resources; // The shader resources that are not used yet.
  Declarations m_declarations;                  // The declarations that this shader module is using.
};
