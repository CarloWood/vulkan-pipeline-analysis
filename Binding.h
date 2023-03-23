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
  Binding() : m_owner(nullptr), m_vi(-1) { }

  Binding(DescriptorSetLayout const* owner, int vi) : m_owner(owner), m_vi(vi)
  {
    reset();
  }

  void set_index(BindingIndex binding_index)
  {
    m_value = binding_index;
  }

 private:
  BindingIndex get_sorted_begin() const override;
  BindingIndex get_sorted_end() const override;

  char const* demangled_name() const override
  {
    return "Binding";
  }

  int get_vi() const override
  {
    return m_vi;
  }

  DescriptorSetLayout const* m_owner;
  int const m_vi;
};
