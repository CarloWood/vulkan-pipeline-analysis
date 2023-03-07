#pragma once

#ifndef DECLARATION_H
#define DECLARATION_H

#include "SetIndex.h"
#include "Binding.h"
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
class Declaration : public Generated<std::tuple<SetIndex&, Binding&, AShaderResource&>>
{
 public:
  Declaration(ShaderModule const* owner) :
    Generated("Declaration", std::forward_as_tuple(m_set_index, m_binding, m_a_shader_resource)), m_owner(owner) { }

  Declaration(Declaration const*) = delete;
  Declaration(Declaration&& orig) :
    Generated("Declaration", std::forward_as_tuple(m_set_index, m_binding, m_a_shader_resource)),
    // All three members are Intervals and can therefore be copied.
    m_owner(orig.m_owner), m_set_index(orig.m_set_index), m_binding(orig.m_binding), m_a_shader_resource(orig.m_a_shader_resource) { }
  Declaration& operator=(Declaration const*) = delete;
  Declaration& operator=(Declaration&&) = delete;

  void print_on(std::ostream& os) const;

 private:
  ShaderModule const* const m_owner;    // The ShaderModule that this Declaration instance is used in (fixed).
  SetIndex m_set_index;                 // The set index that this declaration uses.
  Binding m_binding;                    // The binding number that this declaration uses.
  AShaderResource m_a_shader_resource;  // The shader resource that is expected to be bound.
};

#endif // DECLARATION_H
