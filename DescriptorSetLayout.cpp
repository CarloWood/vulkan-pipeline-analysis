#include "sys.h"
#include "DescriptorSetLayout.h"
#include "debug.h"

void DescriptorSetLayout::print_on(std::ostream& os) const
{
  os << '{';
  os << "descriptor_set_layout_bindings:" << m_descriptor_set_layout_bindings;
  os << '}';
}
