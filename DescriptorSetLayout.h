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
    std::vector<DescriptorSetLayoutBinding> new_descriptor_set_layout_bindings;
    new_descriptor_set_layout_bindings.reserve(new_size);
    m_number_of_descriptor_set_layout_bindings = new_size;
    m_current_descriptor_set_layout_binding_vector = &new_descriptor_set_layout_bindings;
    for (int i = 0; i < new_size; ++i)
      new_descriptor_set_layout_bindings.emplace_back(this, i);
    m_descriptor_set_layout_bindings = std::move(new_descriptor_set_layout_bindings);
    m_current_descriptor_set_layout_binding_vector = &m_descriptor_set_layout_bindings;
    return true;
  }

  void randomize(utils::RandomNumber& rn)
  {
    //DoutEntering(dc::notice, "DescriptorSetLayout::randomize()");
    std::uniform_int_distribution<size_t> distribution(0, number_of_shader_resources - 1);
    size_t new_size = rn.generate(distribution);
    std::vector<DescriptorSetLayoutBinding> new_descriptor_set_layout_bindings;
    new_descriptor_set_layout_bindings.reserve(new_size);
    m_number_of_descriptor_set_layout_bindings = new_size;
    m_current_descriptor_set_layout_binding_vector = &new_descriptor_set_layout_bindings;
    for (int i = 0; i < new_size; ++i)
      new_descriptor_set_layout_bindings.emplace_back(this, rn, i);
    m_descriptor_set_layout_bindings = std::move(new_descriptor_set_layout_bindings);
    m_current_descriptor_set_layout_binding_vector = &m_descriptor_set_layout_bindings;
  }

  BindingIndex get_sorted_begin(int vi, BindingIndex begin) const;
  BindingIndex get_sorted_end(int vi, BindingIndex end) const;

#ifdef CWDEBUG
  void print_on(std::ostream& os) const;
#endif

 private:
  // DescriptorSetLayoutCreateInfo.
  std::size_t m_number_of_descriptor_set_layout_bindings;               // The number of DescriptorSetLayoutBinding objects that will
                                                                        // be added, or are already added, to m_descriptor_set_layout_bindings.
  std::vector<DescriptorSetLayoutBinding> const* m_current_descriptor_set_layout_binding_vector;        // The vector that is currently
                                                                        // being built, or m_descriptor_set_layout_bindings once built.
  std::vector<DescriptorSetLayoutBinding> m_descriptor_set_layout_bindings;     // Set of objects that describe the binding info.
};
