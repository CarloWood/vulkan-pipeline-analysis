#include "sys.h"
#include "ShaderModule.h"

void ShaderModule::print_on(std::ostream& os) const
{
  os << '{';
  os << "stage:" << m_stage <<
      ", declarations:" << m_declarations;
  os << '}';
}
