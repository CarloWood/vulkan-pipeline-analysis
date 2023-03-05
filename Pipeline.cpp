#include "sys.h"
#include "Pipeline.h"
#include "debug.h"

void Pipeline::print_on(std::ostream& os) const
{
  os << '{';
  os << "stages:" << m_stages <<
      ", layout:" << m_layout;
  os << '}';
}
