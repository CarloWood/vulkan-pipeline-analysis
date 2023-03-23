#pragma once

#include "Declaration.h"
#include "Generated.h"
#include <deque>

class Declarations : public Generated<std::tuple<std::deque<Declaration>&>>
{
 public:
  Declarations(ShaderModule* owner) : Generated("Declarations", std::forward_as_tuple(m_declarations)), m_owner(owner) { reset(); }

  void reset()
  {
    DoutEntering(dc::debug, "Declarations::reset() [" << this << "]");
    m_declarations.clear();
  }

  bool next();
  void randomize(utils::RandomNumber& rn);

#ifdef CWDEBUG
  void print_on(std::ostream& os) const
  {
    os << PRINT_TYPE("Declarations") << '{';
    os << "declarations:" << m_declarations;
    os << '}';
  }
#endif

  std::deque<Declaration> const& declarations() const
  {
    return m_declarations;
  }

  ShaderModule const* owning_shader_module() const { return m_owner; }
  std::deque<Declaration> const& declaration_list() const { return m_declarations; }

 private:
  static std::uniform_int_distribution<size_t> s_distribution;
  ShaderModule* const m_owner;                  // The ShaderModule that these Declarations are used in (fixed).
  std::deque<Declaration> m_declarations;
};
