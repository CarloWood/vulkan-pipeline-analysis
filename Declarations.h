#pragma once

#include "Declaration.h"
#include "Generated.h"
#include <vector>

class Declarations : public Generated<std::tuple<std::vector<Declaration>&>>
{
 public:
  Declarations(ShaderModule const* owner) : Generated(std::forward_as_tuple(m_declarations)), m_owner(owner) { reset(); }

  void reset()
  {
    m_declarations.clear();
  }

  bool next()
  {
    if (Generated::next())
      return true;
    size_t new_size = m_declarations.size() + 1;
    if (new_size > number_of_shader_resources)
      return false;
    m_declarations.clear();
    m_declarations = std::vector<Declaration>{new_size, m_owner};
    return true;
  }

  void print_on(std::ostream& os) const
  {
    os << '{';
    os << "declarations:" << m_declarations;
    os << '}';
  }

 private:
  ShaderModule const* const m_owner;            // The ShaderModule that these Declarations are used in (fixed).
  std::vector<Declaration> m_declarations;
};
