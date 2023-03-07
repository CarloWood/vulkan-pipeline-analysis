#include "sys.h"
#include "ShaderModule.h"

void ShaderModule::print_on(std::ostream& os) const
{
  os << TYPE_COLOR_BEGIN "ShaderModule" TYPE_COLOR_END "{";
  os << "stage:" << m_stage <<
      ", declarations:" << m_declarations;
  os << '}';
}
