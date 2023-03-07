#pragma once

#include "DescriptorSetLayout.h"
#include "Generated.h"
#include "utils/has_print_on.h"
#include <vector>

using utils::has_print_on::operator<<;

class PipelineLayout : public Generated<std::tuple<std::vector<DescriptorSetLayout>&>>
{
 public:
  PipelineLayout() : Generated("PipelineLayout", std::forward_as_tuple(m_descriptor_set_layouts)) { }

  void print_on(std::ostream& os) const;

  // PipelineLayoutCreateInfo
  std::vector<DescriptorSetLayout> m_descriptor_set_layouts;    // Set of objects describing 
};
