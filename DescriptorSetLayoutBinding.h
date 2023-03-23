#pragma once

#include "Binding.h"
#include "ShaderStageFlags.h"
#include "DescriptorType.h"
#include "DescriptorCount.h"
#include "Generated.h"
#include "SetIndex.h"
#include "utils/has_print_on.h"
#include <tuple>

using utils::has_print_on::operator<<;

class DescriptorSetLayoutBinding : public Generated<std::tuple<Binding&, DescriptorType&, DescriptorCount&, ShaderStageFlags&>>
{
 public:
  DescriptorSetLayoutBinding() :
    Generated("DescriptorSetLayoutBinding", std::forward_as_tuple(m_binding, m_descriptor_type, m_descriptor_count, m_stage_flags))
    { }

  DescriptorSetLayoutBinding(utils::RandomNumber& rn) :
    DescriptorSetLayoutBinding()
  {
    randomize(rn);
  }

  DescriptorSetLayoutBinding(BindingIndex binding_index, DescriptorType const& descriptor_type,
      DescriptorCount const& descriptor_count, ShaderStageFlagBits shader_stage_flag_bit);

  void also_used_in(ShaderStageFlagBits shader_stage_flag_bit)
  {
    DoutEntering(dc::debug, "DescriptorSetLayoutBinding::also_used_in(" << shader_stage_flag_bit << ") [" << this << "]");
    Dout(dc::debug|continued_cf, "Changing m_stage_flags @" << &m_stage_flags << " from " << m_stage_flags << " to ");
    m_stage_flags.set(shader_stage_flag_bit);
    Dout(dc::finish, m_stage_flags);
  }

  // Accessors.
  Binding const& binding() const { return m_binding; }
  DescriptorType const& descriptor_type() const { return m_descriptor_type; }
  DescriptorCount const& descriptor_count() const { return m_descriptor_count; }
  ShaderStageFlags const& stage_flags() const { return m_stage_flags; }

#ifdef CWDEBUG
  void print_on(std::ostream& os) const;
#endif

 private:
  Binding m_binding;                    // The binding number of this entry and corresponds to a resource
                                        // of the same binding number in the shader stages.
  DescriptorType m_descriptor_type;     // The type of resource descriptors used for this binding.
  DescriptorCount m_descriptor_count;   // The number of descriptors contained in the binding, accessed in
                                        // a shader as an array (except if descriptorType is
                                        // VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK).
  ShaderStageFlags m_stage_flags;       // A bitmask specifying which stages can access the resource on this binding.
};
