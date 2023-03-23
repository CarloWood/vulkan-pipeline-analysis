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

class Pipeline;

class ShaderModule : public Generated<std::tuple<Declarations&>>
{
 public:
  ShaderModule(Pipeline* owner, ShaderStageFlagBits stage) :
    Generated("ShaderModule", std::forward_as_tuple(m_declarations)), m_owner(owner), m_stage(stage), m_declarations(this)
  {
    ASSERT(index_begin <= stage && stage < index_end);
  }

  void allow_all()
  {
    m_available_slots.allow_all();
  }

  Declaration const* mark_used_slot(Declaration const* current_declaration, SetIndexBindingSlots::bitset_type slot);
  void mark_unused_slot(Declaration const* current_declaration, SetIndexBindingSlots::bitset_type slot, bool we_are_owner);

  void set_number_of_declarations(int number_of_declarations)
  {
    DoutEntering(dc::debug, "ShaderModule::set_number_of_declarations(" << number_of_declarations << ") [" << this << "]");
    m_number_of_declarations = number_of_declarations;
  }

  void set_current_declaration_vector(std::deque<Declaration> const* declaration_vector)
  {
    DoutEntering(dc::debug, "ShaderModule::set_current_declaration_vector(" << declaration_vector << ") [" << this << "]");
    m_declaration_vector = declaration_vector;
  }

  AShaderResourceIndex get_sorted_begin(int vi, AShaderResourceIndex begin) const
  {
    DoutEntering(dc::debug, "ShaderModule::get_sorted_begin(vi:" << vi << ", begin:" << begin << ") [" << this << "]");
    ASSERT(vi >= 0);
    if (vi == 0)
    {
      Dout(dc::debug, "Returning " << begin << " because vi == 0.");
      return begin;
    }
    AShaderResourceIndex result = (*m_declaration_vector)[vi - 1].a_shader_resource().get_value() + 1;
    Dout(dc::debug, "The previous declaration is " << &(*m_declaration_vector)[vi - 1] << " with shader resource: " <<
        (*m_declaration_vector)[vi - 1].a_shader_resource() << ": returning " << result);
    return result;
  }

  AShaderResourceIndex get_sorted_end(int vi, AShaderResourceIndex end) const
  {
    DoutEntering(dc::debug, "ShaderModule::get_sorted_end(vi:" << vi << ", end:" << end << ") [" << this << "]");
    AShaderResourceIndex result = end - (m_number_of_declarations - 1) + vi;
    ASSERT(result.get_value() <= 4 || m_number_of_declarations == 0);
    Dout(dc::debug, "Returning end - (m_number_of_declarations - 1) + vi = " << result);
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

  void update_layout(Declaration const& declaration);

  // Accessor.
  Declarations const& declarations() const { return m_declarations; }
  ShaderStageFlagBits stage() const { return m_stage; }

 private:
  Pipeline* m_owner;                            // Pointer back to the pipeline.
  ShaderStageFlagBits const m_stage;            // The stage that this shader module is intended for (fixed).
  SetIndexBindingSlots m_available_slots;       // The set index / binding slots that are not used yet.
  int m_number_of_declarations;                 // The current number of declarations this ShaderModule has, updated by Declarations:
  std::deque<Declaration> const* m_declaration_vector; // Points to the currently built vector, or the completed one in m_declarations.
  Declarations m_declarations;                  // The declarations that this shader module is using.
};
