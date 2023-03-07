#include "sys.h"
#include "DescriptorSetLayout.h"
#include "debug.h"

void DescriptorSetLayout::print_on(std::ostream& os) const
{
  os << TYPE_COLOR_BEGIN "DescriptorSetLayout" TYPE_COLOR_END "{";
  os << "descriptor_set_layout_bindings:" << m_descriptor_set_layout_bindings;
  os << '}';
}
