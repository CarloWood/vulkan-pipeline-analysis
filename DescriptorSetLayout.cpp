#include "sys.h"
#include "DescriptorSetLayout.h"
#include "debug.h"

BindingIndex DescriptorSetLayout::get_sorted_begin(int vi, BindingIndex begin) const
{
  //DoutEntering(dc::notice|continued_cf, "DescriptorSetLayout::get_sorted_begin(" << vi << ", " << begin << ") --> ");
  ASSERT(vi >= binding_begin.m_index);
  BindingIndex result = vi == binding_begin.m_index ? begin : (*m_current_descriptor_set_layout_binding_vector)[vi - 1].binding().get_value() + 1;
  return result;
}

BindingIndex DescriptorSetLayout::get_sorted_end(int vi, BindingIndex end) const
{
  //DoutEntering(dc::notice|continued_cf, "DescriptorSetLayout::get_sorted_end(" << vi << ", " << end << ") --> ");
  BindingIndex result = end - (m_number_of_descriptor_set_layout_bindings - 1) + vi;
  return result;
}

#ifdef CWDEBUG
void DescriptorSetLayout::print_on(std::ostream& os) const
{
  os << "\n        " TYPE_COLOR_BEGIN "DescriptorSetLayout" TYPE_COLOR_END "{";
  os << "descriptor_set_layout_bindings:" << m_descriptor_set_layout_bindings;
  os << '}';
}
#endif
