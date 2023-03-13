#include "sys.h"
#include "Stage.h"

#ifdef CWDEBUG
void Stage::print_on(std::ostream& os) const
{
  os << "\n    " TYPE_COLOR_BEGIN "Stage" TYPE_COLOR_END "{";
  os << "module:" << m_module;
  os << '}';
}
#endif
