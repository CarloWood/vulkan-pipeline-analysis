#include "sys.h"
#include "Declarations.h"
#include "ShaderModule.h"

bool Declarations::next()
{
  DoutEntering(dc::debug|continued_cf, "Declarations::next() [" << this << "] = ");
  bool result = true;
  if (!Generated::next())
  {
    size_t new_size = m_declarations.size() + 1;
    if (new_size > number_of_shader_resources)
      result = false;
    else
    {
      std::deque<Declaration> new_declarations;
      m_owner->set_number_of_declarations(new_size);
      m_owner->set_current_declaration_vector(&new_declarations);
      for (int i = 0; i < new_size; ++i)
        new_declarations.emplace_back(m_owner, i);
      m_declarations = std::move(new_declarations);
      m_owner->set_current_declaration_vector(&m_declarations);
    }
  }
  Dout(dc::finish, std::boolalpha << result);
  return result;
}

void Declarations::randomize(utils::RandomNumber& rn)
{
  DoutEntering(dc::debug, "Declarations::randomize() [" << this << "]");
  m_owner->allow_all();
  size_t new_size = rn.generate(s_distribution);
  std::deque<Declaration> new_declarations;
  m_owner->set_number_of_declarations(new_size);
  m_owner->set_current_declaration_vector(&new_declarations);
  for (int i = 0; i < new_size; ++i)
    new_declarations.emplace_back(m_owner, rn, i);
  m_declarations = std::move(new_declarations);
  m_owner->set_current_declaration_vector(&m_declarations);
}

//static
std::uniform_int_distribution<size_t> Declarations::s_distribution(0, number_of_shader_resources);
