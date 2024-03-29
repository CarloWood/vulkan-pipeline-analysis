#pragma once

#include "Interval.h"
#include "utils/Vector.h"

namespace category {
struct DescriptorType;
} // namespace category

// Id that uniquely defines the type of a shader resource and/or what
// shader resource type a descriptor can bind.
using DescriptorTypeIndex = utils::VectorIndex<category::DescriptorType>;

static constexpr DescriptorTypeIndex descriptor_type_begin{0};
static constexpr DescriptorTypeIndex descriptor_type_end{2};

class DescriptorType : public Interval<DescriptorTypeIndex>
{
 public:
  DescriptorType() : Interval<DescriptorTypeIndex>(descriptor_type_begin, descriptor_type_end) { }
  DescriptorType(DescriptorTypeIndex index) : Interval<DescriptorTypeIndex>(index, index + 1) { }

  friend bool operator==(DescriptorType const& lhs, DescriptorType const& rhs)
  {
    return lhs.m_value == rhs.m_value;
  }

 private:
  char const* demangled_name() const override
  {
    return "DescriptorType";
  }
};
