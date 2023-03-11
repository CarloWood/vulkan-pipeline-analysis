#pragma once

#ifndef DECLARATION_H
#define DECLARATION_H

#include "SetIndexBindingSlot.h"
#include "AShaderResource.h"
#include "Generated.h"
#include "utils/has_print_on.h"

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
  Declaration(ShaderModule* owner, int vi) :
    Generated("Declaration", std::forward_as_tuple(m_set_index_binding_slot, m_a_shader_resource)),
    m_owner(owner), m_set_index_binding_slot(owner, vi), m_a_shader_resource(owner, vi) { }

  Declaration(ShaderModule* owner, utils::RandomNumber& rn, int vi) :
    Generated("Declaration", std::forward_as_tuple(m_set_index_binding_slot, m_a_shader_resource)),
    m_owner(owner), m_set_index_binding_slot(owner, rn, vi), m_a_shader_resource(owner, rn, vi) { }

  Declaration(Declaration const*) = delete;
  Declaration(Declaration&& orig) :
    Generated("Declaration", std::forward_as_tuple(m_set_index_binding_slot, m_a_shader_resource)),
    // None of the members contain references and can therefore be copied.
    m_owner(orig.m_owner), m_set_index_binding_slot(orig.m_set_index_binding_slot), m_a_shader_resource(orig.m_a_shader_resource) { }
  Declaration& operator=(Declaration const*) = delete;
  Declaration& operator=(Declaration&&) = delete;

  void print_on(std::ostream& os) const;

 private:
  ShaderModule const* const m_owner;            // The ShaderModule that this Declaration instance is used in (fixed).
  SetIndexBindingSlot m_set_index_binding_slot; // The set index and binding number that this declaration uses.
  AShaderResource m_a_shader_resource;          // The shader resource that is expected to be bound.
};

#endif // DECLARATION_H
