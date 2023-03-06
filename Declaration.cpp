#include "sys.h"
#include "Declaration.h"

void Declaration::print_on(std::ostream& os) const
{
  os << '{';
  os << "owner:" << m_owner <<
      ", set_index:" << m_set_index <<
      ", binding:" << m_binding <<
      ", a_shader_resource:" << m_a_shader_resource;
  os << '}';
}
