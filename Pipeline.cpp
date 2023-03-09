#include "sys.h"
#include "Pipeline.h"
#include "debug.h"

void Pipeline::print_on(std::ostream& os) const
{
  os << TYPE_COLOR_BEGIN "Pipeline" TYPE_COLOR_END "{";
  os << "stages:" << m_stages <<
      ", layout:" << m_layout;
  os << "\n    }";
}
