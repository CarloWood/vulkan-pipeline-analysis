#pragma once

#include "Declaration.h"
#include "Generated.h"
#include <vector>

class Declarations : public Generated<std::tuple<std::vector<Declaration>&>>
{
 public:
  Declarations(ShaderModule* owner) : Generated("Declarations", std::forward_as_tuple(m_declarations)), m_owner(owner) { reset(); }

  void reset()
  {
    //DoutEntering(dc::notice, "Declarations::reset()");
    m_declarations.clear();
  }

  bool next();
  void randomize(utils::RandomNumber& rn);

  void print_on(std::ostream& os) const
  {
    os << TYPE_COLOR_BEGIN "Declarations" TYPE_COLOR_END << "{";
    os << "declarations:" << m_declarations;
    os << '}';
  }

  std::vector<Declaration> const& declarations() const
  {
    return m_declarations;
  }

 private:
  static std::uniform_int_distribution<size_t> s_distribution;
  ShaderModule* const m_owner;                  // The ShaderModule that these Declarations are used in (fixed).
  std::vector<Declaration> m_declarations;
};
