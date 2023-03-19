#include "sys.h"
#include "Declaration.h"
#include "ShaderModule.h"

#ifdef CWDEBUG
void Declaration::print_on(std::ostream& os) const
{
  os << "\n        " TYPE_COLOR_BEGIN "Declaration" TYPE_COLOR_END "{";
  os << "owner:";
  m_owner->print_on_short(os);
  os << ", set_index_binding_slot:" << m_set_index_binding_slot <<
      ",\n            a_shader_resource:" << m_a_shader_resource;
  os << '}';
}
#endif
