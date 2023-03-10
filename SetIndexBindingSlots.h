#pragma once

#include "Binding.h"
#include "SetIndex.h"
#include "utils/BitSet.h"
#include <cstdint>

class SetIndexBindingSlots
{
 public:
  using bitset_type = utils::BitSet<uint32_t>;

  static constexpr int binding_width = binding_end.m_index - binding_begin.m_index;
  static constexpr utils::bitset::Index index_end = utils::bitset::Index{set_index_end} * binding_width;
  static constexpr bitset_type end{index_end};
  static constexpr bitset_type all_slots = end - 1;

  void mark_used(bitset_type slots)
  {
    m_used_set_index_binding_slots.set(slots);
  }

  void mark_unused(bitset_type slots)
  {
    m_used_set_index_binding_slots.reset(slots);
  }

  void allow_all()
  {
    m_used_set_index_binding_slots.reset(all_slots);
  }

  // Accessor.
  bitset_type used_set_index_binding_slots() const
  {
    return m_used_set_index_binding_slots;
  }

  bitset_type unused_set_index_binding_slots() const
  {
    bitset_type result{all_slots};
    result.reset(m_used_set_index_binding_slots);
    return result;
  }

 private:
  bitset_type m_used_set_index_binding_slots{};
};
