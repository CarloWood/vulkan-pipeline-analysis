#include "sys.h"
#include "AShaderResource.h"
#include "ShaderModule.h"
#include "Declaration.h"

void AShaderResource::reset()
{
  DoutEntering(dc::debug, "AShaderResource::reset() [" << this << "]");
  Declaration const* previous_stage_using_slot = m_owner->previous_stage_using_slot();
  if (previous_stage_using_slot)
    copy_from(previous_stage_using_slot->a_shader_resource());
  else
  {
    m_descriptor_count.reset();
    IntervalExclusiveSorted<AShaderResourceIndex>::reset();
  }
}

bool AShaderResource::next()
{
  DoutEntering(dc::debug|continued_cf, "AShaderResource::next() [" << this << "] = ");
  bool result = false;
  if (m_owner->previous_stage_using_slot())
    result = false;
  else if (m_descriptor_count.next())
    result = true;
  else if (IntervalExclusiveSorted<AShaderResourceIndex>::next())
  {
    m_descriptor_count.reset();
    result = true;
  }
  Dout(dc::finish, std::boolalpha << result);
  return result;
}

void AShaderResource::randomize(utils::RandomNumber& rn)
{
  m_descriptor_count.randomize(rn);
  IntervalExclusiveSorted<AShaderResourceIndex>::randomize(rn);
}

AShaderResourceIndex AShaderResource::get_sorted_begin() const
{
  return m_owner->shader_module()->get_sorted_begin(m_vi, s_shader_resources.ibegin());
}

AShaderResourceIndex AShaderResource::get_sorted_end() const
{
  return m_owner->shader_module()->get_sorted_end(m_vi, s_shader_resources.iend());
}

#ifdef CWDEBUG
void AShaderResource::print_on(std::ostream& os) const
{
  os << PRINT_TYPE("AShaderResource") << '{';
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
