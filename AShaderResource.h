#pragma once

#include "ShaderResource.h"
#include "DescriptorType.h"
#include "BitSetInterval.h"
#include "utils/has_print_on.h"
#include "utils/Array.h"
#include <cstdint>

static constexpr std::size_t number_of_shader_resources = 4;
static constexpr DescriptorTypeIndex uniform_buffer_type = descriptor_type_begin;
static constexpr DescriptorTypeIndex texture_type = descriptor_type_begin + 1;

class ShaderModule;

namespace category {
struct AShaderResource;
} // namespace category

// Id that uniquely identifies a resource (descriptor) within a descriptor set.
using AShaderResourceIndex = utils::VectorIndex<category::AShaderResource>;

using utils::has_print_on::operator<<;

class AShaderResource : public BitSetInterval<AShaderResourceIndex>
{
 public:
  AShaderResource(ShaderModule* owner, int vi) :
    m_owner(owner), m_vi(vi) { reset(); }

  AShaderResource(ShaderModule* owner, utils::RandomNumber& rn, int vi) :
    m_owner(owner), m_vi(vi) { randomize(rn); }

  void print_on(std::ostream& os) const;

 private:
  char const* demangled_name() const override
  {
    return "AShaderResource";
  }

  int get_vi() const override
  {
    return m_vi;
  }

  bitset_type available_values() const override;
  void mark_unused_values(bitset_type shader_resources) const override;
  void mark_used_values(bitset_type shader_resources) const override;

 private:
  static utils::Array<ShaderResource, number_of_shader_resources, AShaderResourceIndex> const s_shader_resources;

  ShaderModule* m_owner;
  int const m_vi;
};
