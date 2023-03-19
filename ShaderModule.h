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
  }

  void mark_used_slots(SetIndexBindingSlots::bitset_type slots)
  {
    m_available_slots.mark_used(slots);
  }

  void mark_unused_slots(SetIndexBindingSlots::bitset_type slots)
  {
    m_available_slots.mark_unused(slots);
  }

  void set_number_of_declarations(int number_of_declarations)
  {
    m_number_of_declarations = number_of_declarations;
  }

  void set_current_declaration_vector(std::vector<Declaration> const* declaration_vector)
  {
    m_declaration_vector = declaration_vector;
  }

  AShaderResourceIndex get_sorted_begin(int vi, AShaderResourceIndex begin) const
  {
    ASSERT(vi >= 0);
    return vi == 0 ? begin : (*m_declaration_vector)[vi - 1].a_shader_resource().get_value() + 1;
  }

  AShaderResourceIndex get_sorted_end(int vi, AShaderResourceIndex end) const
  {
    AShaderResourceIndex result = end - (m_number_of_declarations - 1) + vi;
    ASSERT(result.get_value() <= 4 || m_number_of_declarations == 0);
    return result;
  }

#ifdef CWDEBUG
  void print_on(std::ostream& os) const;
  void print_on_short(std::ostream& os) const;
#endif

  SetIndexBindingSlots available_slots() const
  {
    return m_available_slots;
  }

 private:
  ShaderStageFlagBits const m_stage;            // The stage that this shader module is intended for (fixed).
  SetIndexBindingSlots m_available_slots;       // The set index / binding slots that are not used yet.
  int m_number_of_declarations;                 // The current number of declarations this ShaderModule has, updated by Declarations:
  std::vector<Declaration> const* m_declaration_vector; // Points to the currently built vector, or the completed one in m_declarations.
  Declarations m_declarations;                  // The declarations that this shader module is using.
};
