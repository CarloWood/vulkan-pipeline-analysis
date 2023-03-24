#pragma once

#include "IntervalExclusiveSorted.h"
#include "utils/BitSet.h"

class DescriptorSetLayout;

// Id that uniquely identifies a resource (descriptor) within a descriptor set.
using BindingIndex = utils::bitset::Index;

static constexpr utils::bitset::IndexPOD binding_begin{0};
static constexpr utils::bitset::IndexPOD binding_end{3};

class Binding : public IntervalExclusiveSorted<BindingIndex>
{
 public:
  void set_index(BindingIndex binding_index)
  {
    m_value = binding_index;
  }

 private:
  BindingIndex get_sorted_begin() const override { ASSERT(false); return binding_begin; }
  BindingIndex get_sorted_end() const override { ASSERT(false); return binding_end; }
  int get_vi() const override { ASSERT(false); return -1; }

  char const* demangled_name() const override
  {
    return "Binding";
  }
};
