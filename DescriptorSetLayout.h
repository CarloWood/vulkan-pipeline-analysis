#pragma once

#include "DescriptorSetLayoutBinding.h"
#include "utils/has_print_on.h"
#include <vector>

using utils::has_print_on::operator<<;

class DescriptorSetLayout : public Generated<std::tuple<std::vector<DescriptorSetLayoutBinding>&>>
{
 public:
  DescriptorSetLayout() : Generated(std::forward_as_tuple(m_descriptor_set_layout_bindings)) { }

  void print_on(std::ostream& os) const;

 private:
  // DescriptorSetLayoutCreateInfo.
  std::vector<DescriptorSetLayoutBinding> m_descriptor_set_layout_bindings;     // Set of objects that describe the binding info.
};
