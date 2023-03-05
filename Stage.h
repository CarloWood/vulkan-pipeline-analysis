#pragma once

#include "ShaderModule.h"
#include "ShaderStageFlags.h"
#include "Generated.h"
#include "utils/is_power_of_two.h"
#include "utils/log2.h"
#include "utils/has_print_on.h"
#include "debug.h"

static constexpr utils::bitset::IndexPOD index_end{number_of_stages};
using utils::bitset::index_begin;

using utils::has_print_on::operator<<;

class Stage : public Generated<std::tuple<ShaderStageFlagBits&, ShaderModule&>>
{
 public:
  static ShaderStageFlags id_to_mask(ShaderStageFlagBits id)
  {
    return {id};
  }

  static ShaderStageFlagBits mask_to_id(ShaderStageFlags bit)
  {
    ASSERT(bit.is_single_bit());
    utils::bitset::Index index{bit.lssbi()};
    return ShaderStageFlagBits{index};
  }

  Stage() : Generated(std::forward_as_tuple(m_id, m_module)) { }

  Stage(ShaderStageFlagBits id) : Generated(std::forward_as_tuple(m_id, m_module)), m_id(id)
  {
    ASSERT(index_begin <= id && id < index_end);
  }

  void print_on(std::ostream& os) const;

 private:
  ShaderStageFlagBits m_id;             // One bit value specifying a single pipeline stage.
  ShaderModule m_module;                // Handle to the compiled shader code for this stage.
};
