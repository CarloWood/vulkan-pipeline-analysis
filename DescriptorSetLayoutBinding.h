#pragma once

#include "Binding.h"
#include "ShaderStageFlags.h"
#include "DescriptorType.h"
#include "DescriptorCount.h"
#include "Generated.h"
#include "utils/has_print_on.h"

using utils::has_print_on::operator<<;

class DescriptorSetLayoutBinding : public Generated<std::tuple<Binding&, DescriptorType&, DescriptorCount&, ShaderStageFlags&>>
{
 public:
  DescriptorSetLayoutBinding() : Generated(std::forward_as_tuple(m_binding, m_descriptor_type, m_descriptor_count, m_stage_flags)) { }
  void print_on(std::ostream& os) const;

 private:
  Binding m_binding;                    // The binding number of this entry and corresponds to a resource
                                        // of the same binding number in the shader stages.
  DescriptorType m_descriptor_type;     // The type of resource descriptors used for this binding.
  DescriptorCount m_descriptor_count;   // The number of descriptors contained in the binding, accessed in
                                        // a shader as an array (except if descriptorType is
                                        // VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK).
  ShaderStageFlags m_stage_flags;       // A bitmask specifying which stages can access the resource on this binding.
};
