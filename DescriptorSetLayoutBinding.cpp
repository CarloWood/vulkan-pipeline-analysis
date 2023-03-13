#include "sys.h"
#include "DescriptorSetLayoutBinding.h"

#ifdef CWDEBUG
void DescriptorSetLayoutBinding::print_on(std::ostream& os) const
{
  os << "\n            " TYPE_COLOR_BEGIN "DescriptorSetLayoutBinding" TYPE_COLOR_END "{";
  os << m_binding << ", " << m_descriptor_type << ", " << m_descriptor_count << ", " << m_stage_flags;
  os << '}';
}
#endif
