#pragma once

#include "ShaderResource.h"
#include "DescriptorType.h"
#include "IntervalExclusiveSorted.h"
#include "DescriptorCount.h"
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

class AShaderResource : public IntervalExclusiveSorted<AShaderResourceIndex>
{
 public:
  AShaderResource(ShaderModule* owner, int vi) :
    m_owner(owner), m_vi(vi) { reset(); }

  AShaderResource(ShaderModule* owner, utils::RandomNumber& rn, int vi) :
    m_owner(owner), m_vi(vi) { randomize(rn); }

  void reset()
  {
    m_descriptor_count.reset();
    IntervalExclusiveSorted<AShaderResourceIndex>::reset();
  }

  bool next()
  {
    if (m_descriptor_count.next())
      return true;
    if (IntervalExclusiveSorted<AShaderResourceIndex>::next())
    {
      m_descriptor_count.reset();
      return true;
    }
    return false;
  }

  void randomize(utils::RandomNumber& rn)
  {
    m_descriptor_count.randomize(rn);
    IntervalExclusiveSorted<AShaderResourceIndex>::randomize(rn);
  }

#ifdef CWDEBUG
  void print_on(std::ostream& os) const;
#endif

 private:
  char const* demangled_name() const override
  {
    return "AShaderResource";
  }

  AShaderResourceIndex get_sorted_begin() const override;
  AShaderResourceIndex get_sorted_end() const override;

  int get_vi() const override
  {
    return m_vi;
  }

 private:
  static utils::Array<ShaderResource, number_of_shader_resources, AShaderResourceIndex> const s_shader_resources;

  ShaderModule* m_owner;
  int const m_vi;
  DescriptorCount m_descriptor_count;
};
