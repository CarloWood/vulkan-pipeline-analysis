#include "sys.h"
#include "DescriptorSetLayoutBinding.h"

#ifdef CWDEBUG
void DescriptorSetLayoutBinding::print_on(std::ostream& os) const
{
  os << "\n            " << PRINT_TYPE("DescriptorSetLayoutBinding") << '{';
  os << m_binding << ", " << m_descriptor_type << ", " << m_descriptor_count << ", " << m_stage_flags;
  os << '}';
}
#endif
