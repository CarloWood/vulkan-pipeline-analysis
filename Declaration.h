#pragma once

#ifndef DECLARATION_H
#define DECLARATION_H

#include "SetIndexBindingSlot.h"
#include "AShaderResource.h"
#include "Generated.h"
#include "utils/has_print_on.h"
#include <tuple>

class ShaderModule;

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

  Declaration(ShaderModule* owner, int vi) :
    Generated("Declaration", std::forward_as_tuple(m_set_index_binding_slot, m_a_shader_resource)),
    m_magic(constructed_magic),
    m_owner(owner), m_set_index_binding_slot(this, vi), m_a_shader_resource(this, vi)
  {
    DoutEntering(dc::debug, "Declaration(" << owner << ", " << vi << ") [" << this << "]");
  }

  Declaration(ShaderModule* owner, utils::RandomNumber& rn, int vi) :
    Generated("Declaration", std::forward_as_tuple(m_set_index_binding_slot, m_a_shader_resource)),
    m_magic(constructed_magic),
    m_owner(owner), m_set_index_binding_slot(this, rn, vi), m_a_shader_resource(this, rn, vi) { }

  Declaration(Declaration const*) = delete;
  Declaration(Declaration&& orig) :
    Generated("Declaration", std::forward_as_tuple(m_set_index_binding_slot, m_a_shader_resource)),
    m_magic(constructed_magic),
    // None of the members contain references and can therefore be copied.
    m_owner(orig.m_owner), m_set_index_binding_slot(orig.m_set_index_binding_slot), m_a_shader_resource(orig.m_a_shader_resource)
  {
    DoutEntering(dc::debug, "Declaration(Declaration&& " << &orig << ") [" << this << "]");
    orig.m_magic = moved_magic;
  }
  Declaration& operator=(Declaration const*) = delete;
  Declaration& operator=(Declaration&&) = delete;

  ~Declaration()
  {
    DoutEntering(dc::debug, "~Declaration() [" << this << "]");
    ASSERT(m_magic == constructed_magic || m_magic == moved_magic);
    m_magic = destructed_magic;
  }

  AShaderResource const& a_shader_resource() const
  {
    ASSERT(m_magic == constructed_magic);
    return m_a_shader_resource;
  }

  ShaderModule* shader_module() const
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

#ifdef CWDEBUG
  void print_on(std::ostream& os) const;
#endif

 private:
  long m_magic;
  ShaderModule* const m_owner;                  // The ShaderModule that this Declaration instance is used in (fixed).
  SetIndexBindingSlot m_set_index_binding_slot; // The set index and binding number that this declaration uses.
  AShaderResource m_a_shader_resource;          // The shader resource that is expected to be bound.
};

#endif // DECLARATION_H
