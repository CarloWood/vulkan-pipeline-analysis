#include "sys.h"
#include "Stage.h"

void Stage::print_on(std::ostream& os) const
{
  os << '{';
  os << "id:" << m_id <<
      ", module:" << m_module;
  os << '}';
}
