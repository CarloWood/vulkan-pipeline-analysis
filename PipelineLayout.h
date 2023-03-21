#pragma once

#include "DescriptorSetLayout.h"
#include "Generated.h"
#include "AShaderResource.h"
#include "utils/has_print_on.h"
#include <vector>

using utils::has_print_on::operator<<;

class PipelineLayout : public Generated<std::tuple<std::vector<DescriptorSetLayout>&>>
{
 public:
  PipelineLayout() : Generated("PipelineLayout", std::forward_as_tuple(m_descriptor_set_layouts)) { }

  void reset()
  {
    DoutEntering(dc::debug, "PipelineLayout::reset() [" << this << "]");
    m_descriptor_set_layouts.clear();
  }

  bool next()
  {
    DoutEntering(dc::debug|continued_cf, "PipelineLayout::next() [" << this << "] = ");
    bool result = true;
    if (!Generated::next())
    {
      size_t new_size = m_descriptor_set_layouts.size() + 1;
      if (new_size > number_of_shader_resources)
        result = false;
      else
        m_descriptor_set_layouts = std::vector<DescriptorSetLayout>(new_size);
    }
    Dout(dc::finish, std::boolalpha << result);
    return result;
  }

  void randomize(utils::RandomNumber& rn)
  {
    //DoutEntering(dc::debug, "Declarations::randomize()");
    std::uniform_int_distribution<size_t> distribution(0, number_of_shader_resources - 1);
    size_t new_size = rn.generate(distribution);
    m_descriptor_set_layouts.clear();
    m_descriptor_set_layouts.resize(new_size);
    Generated::randomize(rn);
  }

#ifdef CWDEBUG
  void print_on(std::ostream& os) const;
#endif

 private:
  // PipelineLayoutCreateInfo
  std::vector<DescriptorSetLayout> m_descriptor_set_layouts;    // Set of objects describing 
};
