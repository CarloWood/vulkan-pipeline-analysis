#pragma once

#include "Declarations.h"
#include "ShaderStageFlags.h"
#include "Generated.h"
#include "DeclarationMask.h"
#include "utils/has_print_on.h"
#include <vector>

static constexpr utils::bitset::IndexPOD index_end{number_of_stages};
using utils::bitset::index_begin;

using utils::has_print_on::operator<<;

class ShaderModule : public Generated<std::tuple<Declarations&>>
{
 public:
  ShaderModule(ShaderStageFlagBits stage) : Generated("ShaderModule", std::forward_as_tuple(m_declarations)), m_stage(stage), m_declarations(this)
  {
    ASSERT(index_begin <= stage && stage < index_end);
  }

  void print_on(std::ostream& os) const;

 private:
  ShaderStageFlagBits const m_stage;            // The stage that this shader module is intended for (fixed).
  Declarations m_declarations;                  // The declarations that this shader module is using.
};
