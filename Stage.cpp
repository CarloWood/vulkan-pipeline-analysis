#include "sys.h"
#include "Stage.h"

#ifdef CWDEBUG
void Stage::print_on(std::ostream& os) const
{
  os << "\n    " << PRINT_TYPE("Stage") << '{';
  os << "module:" << m_module;
  os << '}';
}
#endif
