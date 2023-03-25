#include "sys.h"
#include "DescriptorSetLayout.h"
#include "Declaration.h"
#include "ShaderModule.h"
#include "debug.h"
#include <algorithm>

void DescriptorSetLayout::remove_layout(BindingIndex prev_binding_index)
{
  DoutEntering(dc::debug, "DescriptorSetLayout::remove_layout(" << prev_binding_index << ") [" << this << "]");

  auto descriptor_set_layout_binding = std::find_if(m_descriptor_set_layout_bindings.begin(), m_descriptor_set_layout_bindings.end(),
        [&](DescriptorSetLayoutBinding const& descriptor_set_layout_binding)
        {
          return descriptor_set_layout_binding.binding().get_value() == prev_binding_index;
        });

  ASSERT(descriptor_set_layout_binding != m_descriptor_set_layout_bindings.end());

  m_descriptor_set_layout_bindings.erase(descriptor_set_layout_binding);
}

void DescriptorSetLayout::update_layout(BindingIndex prev_binding_index, Declaration const& declaration)
{
  DoutEntering(dc::debug, "DescriptorSetLayout::update_layout(" << prev_binding_index << ", " << declaration << ") [" << this << "]");

  auto descriptor_set_layout_binding = std::find_if(m_descriptor_set_layout_bindings.begin(), m_descriptor_set_layout_bindings.end(),
        [&](DescriptorSetLayoutBinding const& descriptor_set_layout_binding)
        {
          return descriptor_set_layout_binding.binding().get_value() == prev_binding_index;
        });

  ASSERT(descriptor_set_layout_binding != m_descriptor_set_layout_bindings.end());

  std::pair<SetIndexIndex, BindingIndex> set_index_binding = declaration.set_index_binding_slot().get_set_index_binding();
  SetIndexIndex set_index_index = set_index_binding.first;
  BindingIndex new_binding_index = set_index_binding.second;

  AShaderResource const& a_shader_resource = declaration.a_shader_resource();
  DescriptorType const& descriptor_type = AShaderResource::shader_resource(a_shader_resource.get_value()).type();
  DescriptorCount const& descriptor_count = a_shader_resource.descriptor_count();

  if (prev_binding_index == new_binding_index)
    descriptor_set_layout_binding->update(descriptor_type, descriptor_count);
  else
  {
    auto new_descriptor_set_layout_binding = std::find_if(m_descriptor_set_layout_bindings.begin(), m_descriptor_set_layout_bindings.end(),
          [&](DescriptorSetLayoutBinding const& descriptor_set_layout_binding)
          {
            return descriptor_set_layout_binding.binding().get_value() == new_binding_index;
          });

    ASSERT(new_descriptor_set_layout_binding == m_descriptor_set_layout_bindings.end());

    m_descriptor_set_layout_bindings.erase(descriptor_set_layout_binding);
    m_descriptor_set_layout_bindings.emplace_back(new_binding_index, descriptor_type, descriptor_count, declaration.shader_module()->stage());
  }
}

#ifdef CWDEBUG
void DescriptorSetLayout::print_on(std::ostream& os) const
{
  os << "\n        " << PRINT_TYPE("DescriptorSetLayout") << '{';
  os << "descriptor_set_layout_bindings:" << m_descriptor_set_layout_bindings;
  os << '}';
}
#endif
