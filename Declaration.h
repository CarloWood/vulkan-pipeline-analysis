#pragma once

#ifndef DECLARATION_H
#define DECLARATION_H

#include "SetIndexBindingSlot.h"
#include "AShaderResource.h"
#include "Generated.h"
#include "utils/has_print_on.h"
#include <tuple>

class ShaderModule;
class PipelineLayout;

using utils::has_print_on::operator<<;

// Represents shader resource declarations in a shader.
//
// For example,
//
//   layout(set = 1, binding = 0) uniform sampler2D u_CombinedImageSampler_bottom0[];
//   layout(set = 0, binding = 2) uniform u_s0b2 { vec2 unused; float x; } BottomPosition;
//
class Declaration : public Generated<std::tuple<SetIndexBindingSlot&, AShaderResource&>>
{
 public:
  static constexpr long constructed_magic = 0x572827251;
  static constexpr long destructed_magic = 0xabc78ecff;
  static constexpr long moved_magic = 0x6511245fe;

  Declaration(ShaderModule* owner, int vi);

  Declaration(ShaderModule* owner, utils::RandomNumber& rn, int vi);

  Declaration(Declaration const&) = delete;
  Declaration(Declaration&& orig) :
    Generated("Declaration", std::forward_as_tuple(m_set_index_binding_slot, m_a_shader_resource)),
    m_magic(constructed_magic),
    // None of the members contain references and can therefore be copied.
    m_owner(orig.m_owner), m_set_index_binding_slot(orig.m_set_index_binding_slot), m_a_shader_resource(orig.m_a_shader_resource)
  {
    DoutEntering(dc::debug, "Declaration(Declaration&& " << &orig << ") [" << this << "]");
    orig.m_magic = moved_magic;
  }
  Declaration& operator=(Declaration const&) = delete;
  Declaration& operator=(Declaration&&) = delete;

  ~Declaration();

  void reset();
  bool next();

  AShaderResource const& a_shader_resource() const
  {
    ASSERT(m_magic == constructed_magic);
    return m_a_shader_resource;
  }

  ShaderModule* owning_shader_module() const
  {
    ASSERT(m_magic == constructed_magic);
    return m_owner;
  }

  Declaration const* previous_stage_using_slot() const
  {
    DoutEntering(dc::debug|continued_cf, "Declaration::previous_stage_using_slot() [" << this << "] = ");
    ASSERT(m_magic == constructed_magic);
    Declaration const* result = m_set_index_binding_slot.previous_stage();
    Dout(dc::finish, result);
    return result;
  }

  // Accessors.
  SetIndexBindingSlot const& set_index_binding_slot() const { return m_set_index_binding_slot; }
  ShaderModule* shader_module() const { return m_owner; }

#ifdef CWDEBUG
  void print_on(std::ostream& os) const;
#endif

 private:
  long m_magic;
  ShaderModule* const m_owner;                  // The ShaderModule that this Declaration instance is used in (fixed).
  SetIndexBindingSlot m_set_index_binding_slot; // The set index and binding number that this declaration uses.
  AShaderResource m_a_shader_resource;          // The shader resource that is expected to be bound.
  PipelineLayout* m_pipeline_layout;            // Pointer the PipelineLayout.
};

#endif // DECLARATION_H
