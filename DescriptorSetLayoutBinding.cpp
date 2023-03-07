#include "sys.h"
#include "DescriptorSetLayoutBinding.h"

void DescriptorSetLayoutBinding::print_on(std::ostream& os) const
{
  os << TYPE_COLOR_BEGIN "DescriptorSetLayoutBinding" TYPE_COLOR_END "{";
  os << "binding:" << m_binding <<
      ", descriptor_type:" << m_descriptor_type <<
      ", descriptor_count:" << m_descriptor_count <<
      ", stage_flags:" << m_stage_flags;
  os << '}';
}
