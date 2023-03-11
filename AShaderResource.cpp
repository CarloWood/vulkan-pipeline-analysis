#include "sys.h"
#include "AShaderResource.h"
#include "ShaderModule.h"

AShaderResource::bitset_type AShaderResource::available_values() const
{
  return m_owner->available_shader_resources().unused_shader_resources();
}

void AShaderResource::mark_unused_values(bitset_type shader_resources) const
{
  m_owner->mark_unused_shader_resources(shader_resources);
}

void AShaderResource::mark_used_values(bitset_type shader_resources) const
{
  m_owner->mark_used_shader_resources(shader_resources);
}

void AShaderResource::print_on(std::ostream& os) const
{
  os << TYPE_COLOR_BEGIN "AShaderResource" TYPE_COLOR_END "{";
  os << "current_shader_resource:\"" << s_shader_resources[get_value()].name() << '"';
  os << "} (" << m_vi << ")";
}

//static
utils::Array<ShaderResource, number_of_shader_resources, AShaderResourceIndex> const AShaderResource::s_shader_resources = {{
  { "uniform_buffer0", descriptor_type_begin },
  { "uniform_buffer1", descriptor_type_begin },
  { "texture0", texture_type },
  { "texture1", texture_type }
}};
