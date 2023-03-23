#include "sys.h"
#include "DescriptorSetLayoutBinding.h"

DescriptorSetLayoutBinding::DescriptorSetLayoutBinding(BindingIndex binding_index, DescriptorType const& descriptor_type,
    DescriptorCount const& descriptor_count, ShaderStageFlagBits shader_stage_flag_bit) :
  Generated("DescriptorSetLayoutBinding", std::forward_as_tuple(m_binding, m_descriptor_type, m_descriptor_count, m_stage_flags))
{
  DoutEntering(dc::debug, "DescriptorSetLayoutBinding::DescriptorSetLayoutBinding(" <<
      binding_index << ", " << descriptor_type << ", " << descriptor_count << ", " << shader_stage_flag_bit << ") [" << this << "]");
  m_binding.set_index(binding_index);
  m_descriptor_type.set_value(descriptor_type.get_value());
  m_descriptor_count = descriptor_count;
  m_stage_flags = shader_stage_flag_bit;
  Dout(dc::debug, "Set m_stage_flags @" << &m_stage_flags << " to " << m_stage_flags);
}

#ifdef CWDEBUG
void DescriptorSetLayoutBinding::print_on(std::ostream& os) const
{
  os << "\n            " << PRINT_TYPE("DescriptorSetLayoutBinding") << '{';
  os << m_binding << ", " << m_descriptor_type << ", " << m_descriptor_count << ", " << m_stage_flags;
  os << '}';
}
#endif
