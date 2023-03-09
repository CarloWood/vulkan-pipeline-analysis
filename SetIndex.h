#pragma once

#include "Interval.h"
#include "utils/BitSet.h"

// Index into the vk::DescriptorSet const* pDescriptorSets array of CommandBuffer::bindDescriptorSets.
// Hardcoded as `set` numbers in a compiled shader module.
using SetIndexIndex = utils::bitset::Index;

static constexpr utils::bitset::IndexPOD set_index_begin{0};
static constexpr utils::bitset::IndexPOD set_index_end{3};

class SetIndex : public Interval<SetIndexIndex>
{
 public:
  SetIndex() : Interval<SetIndexIndex>(set_index_begin, set_index_end) { }

 private:
  char const* demangled_name() const override
  {
    return "SetIndex";
  }
};
