#pragma once

#ifndef DECLARATION_H
#define DECLARATION_H

#include "SetIndex.h"
#include "Binding.h"
#include "AShaderResource.h"
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
class Declaration
{
 public:
  Declaration(ShaderModule const* owner) : m_owner(owner) { reset(); }

  void print_on(std::ostream& os) const;

  void reset() { }
  bool next() { return false; }

 private:
  ShaderModule const* const m_owner;    // The ShaderModule that this Declaration instance is used in (fixed).
  SetIndex m_set_index;                 // The set index that this declaration uses.
  Binding m_binding;                    // The binding number that this declaration uses.
  AShaderResource m_a_shader_resource;  // The shader resource that is expected to be bound.
};

#endif // DECLARATION_H