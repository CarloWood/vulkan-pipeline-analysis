#pragma once

#include "utils/has_print_on.h"

using utils::has_print_on::operator<<;

class ShaderResource
{
 public:
  void print_on(std::ostream& os) const;

 private:
  DescriptorType m_type;                // The type of this shader resource.
};
