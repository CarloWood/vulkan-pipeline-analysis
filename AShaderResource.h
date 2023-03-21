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
class Declaration;

namespace category {
struct AShaderResource;
} // namespace category

// Id that uniquely identifies a resource (descriptor) within a descriptor set.
using AShaderResourceIndex = utils::VectorIndex<category::AShaderResource>;

using utils::has_print_on::operator<<;

class AShaderResource : public IntervalExclusiveSorted<AShaderResourceIndex>
{
 public:
  AShaderResource(Declaration const* owner, int vi) :
    m_owner(owner), m_vi(vi) { reset(); }

  AShaderResource(Declaration const* owner, utils::RandomNumber& rn, int vi) :
    m_owner(owner), m_vi(vi) { randomize(rn); }

  void reset();
  bool next();
  void randomize(utils::RandomNumber& rn);

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

  void copy_from(AShaderResource const& other)
  {
    DoutEntering(dc::debug, "AShaderResource::copy_from(" << &other << ") [" << this << "]");

    m_value = other.m_value;
    m_vi = other.m_vi;
    m_descriptor_count = other.m_descriptor_count;
    Dout(dc::debug, "m_vi = " << m_vi << "; m_descriptor_count = " << m_descriptor_count);
  }

  int get_vi() const override
  {
    return m_vi;
  }

 private:
  static utils::Array<ShaderResource, number_of_shader_resources, AShaderResourceIndex> const s_shader_resources;

  Declaration const* const m_owner;
  int m_vi;
  DescriptorCount m_descriptor_count;
};
