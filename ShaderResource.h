#pragma once

#include "DescriptorType.h"
#include "utils/has_print_on.h"
#include <string>

using utils::has_print_on::operator<<;

class ShaderResource
{
 public:
  ShaderResource(char const* name, DescriptorType type) : m_name(name), m_type(type) { }

#ifdef CWDEBUG
  void print_on(std::ostream& os) const;
#endif

  // Accessor.
  std::string const& name() const { return m_name; }

 private:
  std::string const m_name;             // The (debug) name of this shader resource (fixed).
  DescriptorType const m_type;          // The type of this shader resource (fixed).
};
