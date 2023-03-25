#include "sys.h"
#include "PipelineLayout.h"
#include "Declaration.h"
#include "ShaderModule.h"
#include "debug.h"
#include <algorithm>

void PipelineLayout::update_layout_remove(std::pair<SetIndexIndex, BindingIndex> prev_set_index_binding_slot)
{
  DoutEntering(dc::debug, "PipelineLayout::update_layout_remove(" << prev_set_index_binding_slot << ") [" << this << "]");

  size_t prev_set_index = prev_set_index_binding_slot.first();
  ASSERT(m_descriptor_set_layouts.size() > prev_set_index);

  std::list<DescriptorSetLayoutBinding>& descriptor_set_layout_bindings =
      m_descriptor_set_layouts[prev_set_index].descriptor_set_layout_bindings();

  auto descriptor_set_layout_binding = std::find_if(descriptor_set_layout_bindings.begin(), descriptor_set_layout_bindings.end(),
        [&](DescriptorSetLayoutBinding const& descriptor_set_layout_binding)
        {
          return descriptor_set_layout_binding.binding().get_value() == prev_set_index_binding_slot.second;
        });

  ASSERT(descriptor_set_layout_binding != descriptor_set_layout_bindings.end());
  descriptor_set_layout_bindings.erase(descriptor_set_layout_binding);
}

void PipelineLayout::update_layout_add(Declaration const& declaration)
{
  DoutEntering(dc::debug, "PipelineLayout::update_layout_add(" << declaration << ") [" << this << "]");

  SetIndexBindingSlot const& set_index_binding_slot = declaration.set_index_binding_slot();
  std::pair<SetIndexIndex, BindingIndex> set_index_binding = set_index_binding_slot.get_set_index_binding();

  size_t set_index = set_index_binding.first();
  if (m_descriptor_set_layouts.size() <= set_index)
    m_descriptor_set_layouts.resize(set_index + 1);

  std::list<DescriptorSetLayoutBinding>& descriptor_set_layout_bindings =
      m_descriptor_set_layouts[set_index].descriptor_set_layout_bindings();

  auto descriptor_set_layout_binding = std::find_if(descriptor_set_layout_bindings.begin(), descriptor_set_layout_bindings.end(),
        [&](DescriptorSetLayoutBinding const& descriptor_set_layout_binding)
        {
          return descriptor_set_layout_binding.binding().get_value() == set_index_binding.second;
        });

  ShaderModule* shader_module = declaration.owning_shader_module();
  if (descriptor_set_layout_binding != descriptor_set_layout_bindings.end())
  {
    Dout(dc::debug, "set_index " << set_index << " has already binding " << set_index_binding.second << ": " << descriptor_set_layout_bindings);
    descriptor_set_layout_binding->also_used_in(shader_module->stage());
  }
  else
  {
    AShaderResource const& a_shader_resource = declaration.a_shader_resource();
    descriptor_set_layout_bindings.emplace_back(
        set_index_binding.second, AShaderResource::shader_resource(a_shader_resource.get_value()).type(),
        a_shader_resource.descriptor_count(), shader_module->stage());
  }
}

void PipelineLayout::update_layout(std::pair<SetIndexIndex, BindingIndex> prev_set_index_binding_slot, Declaration const& declaration)
{
  std::pair<SetIndexIndex, BindingIndex> set_index_binding = declaration.set_index_binding_slot().get_set_index_binding();
  SetIndexIndex set_index_index = set_index_binding.first;

  if (set_index_index == prev_set_index_binding_slot.first)
    m_descriptor_set_layouts[set_index_index()].update_layout(prev_set_index_binding_slot.second, declaration);
  else
  {
    m_descriptor_set_layouts[prev_set_index_binding_slot.first()].remove_layout(prev_set_index_binding_slot.second);
    update_layout_add(declaration);
  }
}

#ifdef CWDEBUG
void PipelineLayout::print_on(std::ostream& os) const
{
  os << PRINT_TYPE("PipelineLayout") << '{';
  os << "descriptor_set_layouts:" << m_descriptor_set_layouts;
  os << '}';
}
#endif
