#pragma once

#include "ShaderResource.h"
#include "DescriptorType.h"
#include "utils/has_print_on.h"
#include "utils/Array.h"
#include <cstdint>

static constexpr std::size_t number_of_shader_resources = 4;
static constexpr DescriptorTypeIndex uniform_buffer_type = descriptor_type_begin;
static constexpr DescriptorTypeIndex texture_type = descriptor_type_begin + 1;

namespace category {
struct AShaderResource;
} // namespace category

// Id that uniquely identifies a resource (descriptor) within a descriptor set.
using AShaderResourceIndex = utils::VectorIndex<category::AShaderResource>;

static constexpr AShaderResourceIndex a_shader_resource_begin{0};
static constexpr AShaderResourceIndex a_shader_resource_end{number_of_shader_resources};

using utils::has_print_on::operator<<;

class AShaderResource : public Interval<AShaderResourceIndex>
{
 public:
  AShaderResource() : Interval(a_shader_resource_begin, a_shader_resource_end) { }

  void print_on(std::ostream& os) const;

 private:
  char const* demangled_name() const override
  {
    return "AShaderResource";
  }

 private:
  static utils::Array<ShaderResource, number_of_shader_resources, AShaderResourceIndex> const s_shader_resources;
};
