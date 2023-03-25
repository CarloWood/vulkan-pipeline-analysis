#pragma once

#include "DescriptorSetLayoutBinding.h"
#include "AShaderResource.h"
#include "utils/has_print_on.h"
#include <list>

using utils::has_print_on::operator<<;

class DescriptorSetLayout : public Generated<std::tuple<std::list<DescriptorSetLayoutBinding>&>>
{
 public:
  DescriptorSetLayout() : Generated("DescriptorSetLayout", std::forward_as_tuple(m_descriptor_set_layout_bindings)),
    m_current_descriptor_set_layout_binding_list(&m_descriptor_set_layout_bindings)
  {
    DoutEntering(dc::debug, "DescriptorSetLayout::DescriptorSetLayout() [" << this << "]");
  }

  DescriptorSetLayout(DescriptorSetLayout const&) = delete;
  DescriptorSetLayout(DescriptorSetLayout&& orig) :
    Generated("DescriptorSetLayout", std::forward_as_tuple(m_descriptor_set_layout_bindings)),
    m_current_descriptor_set_layout_binding_list(orig.m_current_descriptor_set_layout_binding_list),
    m_descriptor_set_layout_bindings(std::move(orig.m_descriptor_set_layout_bindings))
  {
    DoutEntering(dc::debug, "DescriptorSetLayout::DescriptorSetLayout(DescriptorSetLayout&&) [" << this << "]");
  }
  DescriptorSetLayout& operator=(DescriptorSetLayout const&) = delete;
  DescriptorSetLayout& operator=(DescriptorSetLayout&&) = delete;

  void reset()
  {
    DoutEntering(dc::debug, "DescriptorSetLayout::reset() [" << this << "]");
    m_descriptor_set_layout_bindings.clear();
    m_current_descriptor_set_layout_binding_list = &m_descriptor_set_layout_bindings;
  }

  bool next()
  {
    DoutEntering(dc::debug|continued_cf, "DescriptorSetLayout::next() [" << this << "] = ");
    bool result = true;
    if (!Generated::next())
    {
      size_t new_size = m_descriptor_set_layout_bindings.size() + 1;
      if (new_size > number_of_shader_resources)
        result = false;
      else
      {
        std::list<DescriptorSetLayoutBinding> new_descriptor_set_layout_bindings;
        m_current_descriptor_set_layout_binding_list = &new_descriptor_set_layout_bindings;
        for (int i = 0; i < new_size; ++i)
          new_descriptor_set_layout_bindings.emplace_back();
        m_descriptor_set_layout_bindings = std::move(new_descriptor_set_layout_bindings);
        m_current_descriptor_set_layout_binding_list = &m_descriptor_set_layout_bindings;
      }
    }
    Dout(dc::finish, result);
    return result;
  }

  void randomize(utils::RandomNumber& rn)
  {
    DoutEntering(dc::debug, "DescriptorSetLayout::randomize() [" << this << "]");
    std::uniform_int_distribution<size_t> distribution(0, number_of_shader_resources - 1);
    size_t new_size = rn.generate(distribution);
    std::list<DescriptorSetLayoutBinding> new_descriptor_set_layout_bindings;
    m_current_descriptor_set_layout_binding_list = &new_descriptor_set_layout_bindings;
    for (int i = 0; i < new_size; ++i)
      new_descriptor_set_layout_bindings.emplace_back(rn);
    m_descriptor_set_layout_bindings = std::move(new_descriptor_set_layout_bindings);
    m_current_descriptor_set_layout_binding_list = &m_descriptor_set_layout_bindings;
  }

  std::list<DescriptorSetLayoutBinding>& descriptor_set_layout_bindings()
  {
    return m_descriptor_set_layout_bindings;
  }

  void remove_layout(BindingIndex prev_binding_index);
  void update_layout(BindingIndex prev_binding_index, Declaration const& declaration);

  // Accessors.
  std::list<DescriptorSetLayoutBinding> const& descriptor_set_layout_bindings() const
  {
    // Don't access this when it isn't current.
    ASSERT(m_current_descriptor_set_layout_binding_list == &m_descriptor_set_layout_bindings);
    return m_descriptor_set_layout_bindings;
  }

#ifdef CWDEBUG
  void print_on(std::ostream& os) const;
#endif

 private:
  // DescriptorSetLayoutCreateInfo.
  std::list<DescriptorSetLayoutBinding> const* m_current_descriptor_set_layout_binding_list;        // The list that is currently
                                                                        // being built, or m_descriptor_set_layout_bindings once built.
  std::list<DescriptorSetLayoutBinding> m_descriptor_set_layout_bindings;     // Set of objects that describe the binding info.
};
