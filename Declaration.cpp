#include "sys.h"
#include "Declaration.h"
#include "ShaderModule.h"

#ifdef CWDEBUG
void Declaration::print_on(std::ostream& os) const
{
  ASSERT(m_magic == constructed_magic);
  os << "\n        " << PRINT_TYPE("Declaration") << '{';
  os << "owner:";
  m_owner->print_on_short(os);
  os << ", set_index_binding_slot";
  if (DEBUGCHANNELS::dc::debug.is_on())
    os << "[" << &m_set_index_binding_slot << "]";
  os << ":" << m_set_index_binding_slot <<
      ",\n            a_shader_resource:" << m_a_shader_resource;
  os << '}';
}
#endif
