#pragma once

#include "Interval.h"
#include "utils/Vector.h"

namespace category {
struct Binding;
} // namespace category

// Id that uniquely identifies a resource (descriptor) within a descriptor set.
using BindingIndex = utils::VectorIndex<category::Binding>;

template<>
constexpr char const* demangled_name<BindingIndex>()
{
  return "Binding";
}

static constexpr BindingIndex binding_begin{0};
static constexpr BindingIndex binding_end{3};

class Binding : public Interval<BindingIndex>
{
 public:
  Binding() : Interval<BindingIndex>(binding_begin, binding_end) { }
};
