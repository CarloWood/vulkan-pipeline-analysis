#include "sys.h"
#include "Declarations.h"
#include "ShaderModule.h"

void Declarations::randomize(utils::RandomNumber& rn)
{
  //DoutEntering(dc::notice, "Declarations::randomize()");
  m_owner->allow_all_slots();
  size_t new_size = rn.generate(s_distribution);
  std::vector<Declaration> new_declarations;
  for (int i = 0; i < new_size; ++i)
  {
    new_declarations.emplace_back(m_owner, rn, i);
  }
  m_declarations = std::move(new_declarations);
}

//static
std::uniform_int_distribution<size_t> Declarations::s_distribution(0, number_of_shader_resources);
