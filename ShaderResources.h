#pragma once

#include "AShaderResource.h"
#include "utils/BitSet.h"
#include <cstdint>

class ShaderResources
{
 public:
  using bitset_type = utils::BitSet<uint32_t>;

  static constexpr utils::bitset::Index index_end = utils::bitset::Index{utils::bitset::IndexPOD{number_of_shader_resources}};
  static constexpr bitset_type end{index_end};
  static constexpr bitset_type all_shader_resources = end - 1;

  void mark_used(bitset_type shader_resources)
  {
    m_used_shader_resources.set(shader_resources);
  }

  void mark_unused(bitset_type shader_resources)
  {
    m_used_shader_resources.reset(shader_resources);
  }

  void allow_all()
  {
    m_used_shader_resources.reset(all_shader_resources);
  }

  // Accessor.
  bitset_type used_shader_resources() const
  {
    return m_used_shader_resources;
  }

  bitset_type unused_shader_resources() const
  {
    bitset_type result{all_shader_resources};
    result.reset(m_used_shader_resources);
    return result;
  }

 private:
  bitset_type m_used_shader_resources{};
};

