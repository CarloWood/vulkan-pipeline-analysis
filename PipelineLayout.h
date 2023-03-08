#pragma once

#include "DescriptorSetLayout.h"
#include "Generated.h"
#include "AShaderResource.h"
#include "utils/has_print_on.h"
#include <vector>

using utils::has_print_on::operator<<;

class PipelineLayout : public Generated<std::tuple<std::vector<DescriptorSetLayout>&>>
{
 public:
  PipelineLayout() : Generated("PipelineLayout", std::forward_as_tuple(m_descriptor_set_layouts)) { }

  void reset()
  {
    m_descriptor_set_layouts.clear();
  }

  bool next()
  {
    if (Generated::next())
      return true;
    size_t new_size = m_descriptor_set_layouts.size() + 1;
    if (new_size > number_of_shader_resources)
      return false;
    m_descriptor_set_layouts = std::vector<DescriptorSetLayout>(new_size);
    return true;
  }

  void print_on(std::ostream& os) const;

 private:
  // PipelineLayoutCreateInfo
  std::vector<DescriptorSetLayout> m_descriptor_set_layouts;    // Set of objects describing 
};
