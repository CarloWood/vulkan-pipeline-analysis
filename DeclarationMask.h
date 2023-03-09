#pragma once

#include "SetIndex.h"
#include "Binding.h"
#include "utils/BitSet.h"
#include <cstdint>

class DeclarationMask
{
  using used_set_index_binding_pairs_type = utils::BitSet<uint32_t>;

  static constexpr int binding_width = binding_end.m_index - binding_begin.m_index;

  // Encode the value of set_index and binding into a single bit.
  static used_set_index_binding_pairs_type encode(SetIndex set_index, Binding binding)
  {
    int8_t offset = set_index.get_value() - set_index_begin;
    utils::bitset::Index set_index_index = utils::bitset::IndexPOD{offset};
    int binding_index = binding.get_value() - binding_begin;
    utils::bitset::Index bit_index = set_index_index * binding_width + binding_index;
    return {bit_index};
  }

  void mark_used(SetIndex set_index, Binding binding)
  {
    m_used_set_index_binding_pairs |= encode(set_index, binding);
  }

 private:
  used_set_index_binding_pairs_type m_used_set_index_binding_pairs{};
};
