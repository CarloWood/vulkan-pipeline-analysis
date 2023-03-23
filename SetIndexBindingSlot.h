#pragma once

#include "SetIndexBindingSlots.h"
#include <stdexcept>

class ShaderModule;
class Declaration;

struct RanOutOfSlots : std::underflow_error
{
  RanOutOfSlots() : std::underflow_error("No more set_index.binding slots") { }
};

class SetIndexBindingSlot
{
 public:
  using bitset_type = SetIndexBindingSlots::bitset_type;
  using slot_as_bit_type = bitset_type;
  using const_iterator = utils::bitset::const_iterator<slot_as_bit_type::mask_type>;

  static constexpr int binding_width = binding_end.m_index - binding_begin.m_index;
  static constexpr utils::bitset::Index index_end = utils::bitset::Index{set_index_end} * binding_width;
  static constexpr slot_as_bit_type end{index_end};

  SetIndexBindingSlot(Declaration* owner, int vi) : m_owner(owner), m_vi(vi)
  {
    DoutEntering(dc::debug, "SetIndexBindingSlot(...) [" << this << "]");
    reset();
  }

  SetIndexBindingSlot(Declaration* owner, utils::RandomNumber& rn, int vi) : m_owner(owner), m_vi(vi), m_previous_stage(nullptr)
  {
    DoutEntering(dc::debug, "SetIndexBindingSlot::SetIndexBindingSlot(" << owner << ", rn, " << vi << ") [" << this << "]");
    init(rn);
  }

  void init(utils::RandomNumber& rn)
  {
    DoutEntering(dc::debug, "SetIndexBindingSlot::init(rn) [" << this << "]");
    m_slot_as_bit.reset();
    randomize(rn);
  }

  // Encode the value of set_index and binding into a single bit.
  SetIndexBindingSlot(SetIndex set_index, Binding binding) : m_owner(nullptr), m_vi(-1), m_previous_stage(nullptr)
  {
    int8_t offset = set_index.get_value() - set_index_begin;
    utils::bitset::Index set_index_index = utils::bitset::IndexPOD{offset};
    int binding_index = binding.get_value() - binding_begin;
    utils::bitset::Index bit_index = set_index_index * binding_width + binding_index;
    m_slot_as_bit.reset();
    m_slot_as_bit.set(bit_index);
  }

  std::pair<SetIndexIndex, BindingIndex> get_set_index_binding() const
  {
    utils::bitset::Index bit_index = m_slot_as_bit.lssbi();
    return { bit_index / binding_width, bit_index % binding_width };
  }

  Declaration const* previous_stage() const
  {
    DoutEntering(dc::debug, "SetIndexBindingSlot::previous_stage() [" << this << "] = " << m_previous_stage << " [" << &m_previous_stage << "]");
    return m_previous_stage;
  }

  void reset();
  bool next();
  void randomize(utils::RandomNumber& rn);

  // Accessors.
  Declaration const* owning_declaration() const { return m_owner; }
  int get_vi() const { return m_vi; }
  slot_as_bit_type slot_as_bit() const { ASSERT(m_slot_as_bit.is_single_bit()); return m_slot_as_bit; }

#ifdef CWDEBUG
  void print_on(std::ostream& os) const;
#endif

 private:
  Declaration* m_owner;
  int const m_vi;
  const_iterator m_available_slots_iter;
  slot_as_bit_type m_slot_as_bit;
  Declaration const* m_previous_stage;          // If m_slot_as_bit was first used in a previous stage, then this is set to that previous stage.
};
