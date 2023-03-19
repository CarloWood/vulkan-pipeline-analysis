#include "sys.h"
#include "AShaderResource.h"
#include "ShaderModule.h"

AShaderResourceIndex AShaderResource::get_sorted_begin() const
{
  return m_owner->get_sorted_begin(m_vi, s_shader_resources.ibegin());
}

AShaderResourceIndex AShaderResource::get_sorted_end() const
{
  return m_owner->get_sorted_end(m_vi, s_shader_resources.iend());
}

#ifdef CWDEBUG
void AShaderResource::print_on(std::ostream& os) const
{
  os << TYPE_COLOR_BEGIN "AShaderResource" TYPE_COLOR_END "{";
  os << "current_shader_resource:\"" << s_shader_resources[get_value()].name() << '"';
  os << ", descriptor_count:" << m_descriptor_count;
  os << "} (" << m_vi << ")";
}
#endif

//static
utils::Array<ShaderResource, number_of_shader_resources, AShaderResourceIndex> const AShaderResource::s_shader_resources = {{
  { "uniform_buffer0", uniform_buffer_type },
  { "uniform_buffer1", uniform_buffer_type },
  { "texture0", texture_type },
  { "texture1", texture_type }
}};
