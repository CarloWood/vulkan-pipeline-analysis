#pragma once

#include "ShaderResource.h"
#include "DescriptorType.h"
#include "utils/has_print_on.h"
#include <array>
#include <cstdint>

static constexpr std::size_t number_of_shader_resources = 4;
static constexpr DescriptorTypeIndex uniform_buffer_type = descriptor_type_begin;
static constexpr DescriptorTypeIndex texture_type = descriptor_type_begin + 1;

using utils::has_print_on::operator<<;

class AShaderResource : Interval<std::size_t>
{
 public:
  AShaderResource() : Interval<std::size_t>(0, number_of_shader_resources) { }

  void print_on(std::ostream& os) const;

 private:
  static std::array<ShaderResource, number_of_shader_resources> const s_shader_resources;
};
