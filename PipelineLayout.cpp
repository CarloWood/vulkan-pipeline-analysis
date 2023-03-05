#include "sys.h"
#include "PipelineLayout.h"
#include "debug.h"

void PipelineLayout::print_on(std::ostream& os) const
{
  os << '{';
  os << "descriptor_set_layouts" << m_descriptor_set_layouts;
  os << '}';
}
