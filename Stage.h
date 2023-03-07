#pragma once

#include "ShaderModule.h"
#include "ShaderStageFlags.h"
#include "Generated.h"
#include "utils/is_power_of_two.h"
#include "utils/log2.h"
#include "utils/has_print_on.h"
#include "debug.h"

using utils::has_print_on::operator<<;

class Stage : public Generated<std::tuple<ShaderModule&>>
{
 public:
#if 0
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
#endif

  Stage(ShaderStageFlagBits id) : Generated("Stage", std::forward_as_tuple(m_module)), m_module(id)
  {
  }

  void print_on(std::ostream& os) const;

 private:
  ShaderModule m_module;                // Handle to the compiled shader code for this stage.
};
