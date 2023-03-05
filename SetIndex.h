#pragma once

#include "Interval.h"
#include "utils/Vector.h"

namespace category {
struct SetIndex;
} // namespace category

// Index into the vk::DescriptorSet const* pDescriptorSets array of CommandBuffer::bindDescriptorSets.
// Hardcoded as `set` numbers in a compiled shader module.
using SetIndexIndex = utils::VectorIndex<category::SetIndex>;

static constexpr SetIndexIndex set_index_begin{0};
static constexpr SetIndexIndex set_index_end{3};

class SetIndex : public Interval<SetIndexIndex>
{
 public:
  SetIndex() : Interval<SetIndexIndex>(set_index_begin, set_index_end) { }
};
