#pragma once

#include "DescriptorSetLayoutBinding.h"
#include "AShaderResource.h"
#include "utils/has_print_on.h"
#include <vector>

using utils::has_print_on::operator<<;

class DescriptorSetLayout : public Generated<std::tuple<std::vector<DescriptorSetLayoutBinding>&>>
{
 public:
  DescriptorSetLayout() : Generated("DescriptorSetLayout", std::forward_as_tuple(m_descriptor_set_layout_bindings)) { }

  DescriptorSetLayout(DescriptorSetLayout const&) = delete;
  DescriptorSetLayout(DescriptorSetLayout&& orig) :
    Generated("DescriptorSetLayout", std::forward_as_tuple(m_descriptor_set_layout_bindings)),
    m_descriptor_set_layout_bindings(std::move(orig.m_descriptor_set_layout_bindings)) { }
  DescriptorSetLayout& operator=(DescriptorSetLayout const&) = delete;
  DescriptorSetLayout& operator=(DescriptorSetLayout&&) = delete;

  void reset()
  {
    m_descriptor_set_layout_bindings.clear();
  }

  bool next()
  {
    if (Generated::next())
      return true;
    size_t new_size = m_descriptor_set_layout_bindings.size() + 1;
    if (new_size > number_of_shader_resources)
      return false;
    m_descriptor_set_layout_bindings.clear();
    m_descriptor_set_layout_bindings.resize(new_size);
    return true;
  }

  void print_on(std::ostream& os) const;

 private:
  // DescriptorSetLayoutCreateInfo.
  std::vector<DescriptorSetLayoutBinding> m_descriptor_set_layout_bindings;     // Set of objects that describe the binding info.
};
