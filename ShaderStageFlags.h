#pragma once

#include "utils/BitSet.h"
#include "utils/has_print_on.h"
#include "utils/RandomNumber.h"
#include <cstdint>
#include "debug.h"

static constexpr int number_of_stages = 3;
static constexpr utils::bitset::IndexPOD shader_stage_flags_end{number_of_stages};

using utils::has_print_on::operator<<;

// Bit mask of pipeline stages.
class ShaderStageFlags : public utils::BitSet<uint32_t>
{
 public:
  using utils::BitSet<uint32_t>::BitSet;
  ShaderStageFlags() { reset(); }

  void reset()
  {
    m_bitmask = 1;
  }

  bool next()
  {
    ++m_bitmask;
    return !test(Index{shader_stage_flags_end});
  }

  void randomize(utils::RandomNumber& rn)
  {
    //DoutEntering(dc::notice, "ShaderStageFlags::randomize()");
    m_bitmask = rn.generate(s_distribution);
  }

#ifdef CWDEBUG
  void print_on(std::ostream& os) const
  {
    using namespace utils::bitset;
    std::string result;
    for (Index index = Index{shader_stage_flags_end} - 1; index >= index_begin; --index)
      result += test(index) ? '1' : '0';

    os << TYPE_COLOR_BEGIN "ShaderStageFlags" TYPE_COLOR_END << " [" << this << "] {" << result << "}";
  }
#endif

 private:
  static std::uniform_int_distribution<decltype(m_bitmask)> s_distribution;
};

class ShaderStageFlagBits : public ShaderStageFlags::Index
{
 public:
  ShaderStageFlagBits() { reset(); }
  ShaderStageFlagBits(ShaderStageFlags::Index const& index) : ShaderStageFlags::Index(index) { }
  constexpr ShaderStageFlagBits(utils::bitset::IndexPOD index) : ShaderStageFlags::Index(index) { }

  void reset()
  {
    m_index = 0;
  }

  bool next()
  {
    ++m_index;
    return m_index < number_of_stages;
  }
};

static constexpr ShaderStageFlagBits stage0 = utils::bitset::IndexPOD{0};
static constexpr ShaderStageFlagBits stage1 = utils::bitset::IndexPOD{1};
static constexpr ShaderStageFlagBits stage2 = utils::bitset::IndexPOD{2};
