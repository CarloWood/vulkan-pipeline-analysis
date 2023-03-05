#pragma once

#include "Declaration.h"
#include "ShaderStageFlags.h"
#include "Generated.h"
#include "utils/has_print_on.h"
#include <vector>

using utils::has_print_on::operator<<;

class ShaderModule : public Generated<std::tuple<ShaderStageFlagBits&, std::vector<Declaration>&>>
{
 public:
  ShaderModule() : Generated(std::forward_as_tuple(m_stage, m_declarations)) { }

  void print_on(std::ostream& os) const;

 private:
  ShaderStageFlagBits m_stage;                  // The stage that this shader module is intended for.
  std::vector<Declaration> m_declarations;      // The declarations that this shader module is using.
};
