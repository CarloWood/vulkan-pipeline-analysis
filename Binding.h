#pragma once

#include "Interval.h"
#include "utils/BitSet.h"

// Id that uniquely identifies a resource (descriptor) within a descriptor set.
using BindingIndex = utils::bitset::Index;

static constexpr utils::bitset::IndexPOD binding_begin{0};
static constexpr utils::bitset::IndexPOD binding_end{3};

class Binding : public Interval<BindingIndex>
{
 public:
  Binding() : Interval<BindingIndex>(binding_begin, binding_end) { }

 private:
  char const* demangled_name() const override
  {
    return "Binding";
  }
};
