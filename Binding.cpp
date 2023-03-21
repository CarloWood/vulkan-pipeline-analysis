#include "sys.h"
#include "Binding.h"
#include "DescriptorSetLayout.h"

BindingIndex Binding::get_sorted_begin() const
{
  //DoutEntering(dc::debug, "Binding::get_sorted_begin() [" << this << "]");
  return m_owner->get_sorted_begin(m_vi, binding_begin);
}

BindingIndex Binding::get_sorted_end() const
{
  //DoutEntering(dc::debug, "Binding::get_sorted_end() [" << this << "]");
  return m_owner->get_sorted_end(m_vi, binding_end);
}
