#pragma once

#include "Declaration.h"
#include "Generated.h"
#include <vector>

class Declarations : public Generated<std::tuple<std::vector<Declaration>&>>
{
 public:
  Declarations(ShaderModule const* owner) : Generated("Declarations", std::forward_as_tuple(m_declarations)), m_owner(owner) { reset(); }

  void reset()
  {
    //DoutEntering(dc::notice, "Declarations::reset()");
    m_declarations.clear();
  }

  bool next()
  {
    if (Generated::next())
      return true;
    size_t new_size = m_declarations.size() + 1;
    if (new_size > number_of_shader_resources)
      return false;
    std::vector<Declaration> new_declarations;
    for (int i = 0; i < new_size; ++i)
      new_declarations.emplace_back(m_owner);
    m_declarations = std::move(new_declarations);
    return true;
  }

  void print_on(std::ostream& os) const
  {
    os << TYPE_COLOR_BEGIN "Declarations" TYPE_COLOR_END << "{";
    os << "declarations:" << m_declarations;
    os << '}';
  }

 private:
  ShaderModule const* const m_owner;            // The ShaderModule that these Declarations are used in (fixed).
  std::vector<Declaration> m_declarations;
};
