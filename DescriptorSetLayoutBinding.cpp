#include "sys.h"
#include "DescriptorSetLayoutBinding.h"

void DescriptorSetLayoutBinding::print_on(std::ostream& os) const
{
  os << '{';
  os << "binding:" << m_binding <<
      ", descriptor_type:" << m_descriptor_type <<
      ", descriptor_count:" << m_descriptor_count <<
      ", stage_flags:" << m_stage_flags;
  os << '}';
}
