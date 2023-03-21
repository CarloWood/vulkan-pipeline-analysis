#include "sys.h"
#include "PipelineLayout.h"
#include "debug.h"

#ifdef CWDEBUG
void PipelineLayout::print_on(std::ostream& os) const
{
  os << PRINT_TYPE("PipelineLayout") << '{';
  os << "descriptor_set_layouts:" << m_descriptor_set_layouts;
  os << '}';
}
#endif
