#include "sys.h"
#include "AShaderResource.h"

void AShaderResource::print_on(std::ostream& os) const
{
  os << '{';
  os << "current_shader_resource:\"" << s_shader_resources[m_value].name() << '"';
  os << '}';
}

//static
std::array<ShaderResource, number_of_shader_resources> const AShaderResource::s_shader_resources = {{
  { "uniform_buffer0", descriptor_type_begin },
  { "uniform_buffer1", descriptor_type_begin },
  { "texture0", texture_type },
  { "texture1", texture_type }
}};
