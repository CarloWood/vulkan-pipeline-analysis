#pragma once

#include "PipelineLayout.h"
#include "Stage.h"
#include "Generated.h"
#include "SetIndexBindingSlots.h"
#include "utils/has_print_on.h"
#include <array>

#define DISABLE_LAYOUT 0

class Declaration;

using utils::has_print_on::operator<<;

namespace category {
struct Slot;
} // namespace category
using SlotIndex = utils::VectorIndex<category::Slot>;

class Pipeline : public Generated<std::tuple<std::array<Stage, number_of_stages>&
#if !DISABLE_LAYOUT
                 , PipelineLayout&
#endif
                 >>
{                                                       // vk::GraphicsPipelineCreateInfo element(s).
 public:
  static constexpr SlotIndex number_of_slots{static_cast<size_t>(SetIndexBindingSlots::index_end())};

  Pipeline() : Generated("Pipeline", std::forward_as_tuple(m_stages
#if !DISABLE_LAYOUT
        , m_layout
#endif
        )),
      m_stages{{ { this, stage0 }, { this, stage1 }, { this, stage2 } }}
  {
  }

  Declaration const* acquire_slot(Declaration const* current_declaration, SetIndexBindingSlots::bitset_type slot);
  void release_slot(Declaration const* current_declaration, SetIndexBindingSlots::bitset_type slot);

  void randomize(utils::RandomNumber& rn)
  {
    bool success = false;
    while (!success)
    {
      try
      {
        for (int i = 0; i < number_of_slots.get_value(); ++i)
          m_slot_owner[i] = nullptr;
        for (int i = 0; i < number_of_stages; ++i)
          m_stages[i].reset();
        m_layout.reset();
        Generated<std::tuple<std::array<Stage, number_of_stages>&
#if !DISABLE_LAYOUT
                     , PipelineLayout&
#endif
                     >>::randomize(rn);
        success = true;
      }
      catch (RanOutOfSlots const&)
      {
      }
    }
  }

#ifdef CWDEBUG
  void print_on(std::ostream& os) const;
#endif

  bool is_sane() const;

 private:
  std::array<Declaration const*, number_of_slots.get_value()> m_slot_owner{};  // The Declaration that first used a given slot.
  std::array<Stage, number_of_stages> m_stages;                                // stageCount, pStages.
#if !DISABLE_LAYOUT
  PipelineLayout m_layout;                                                     // layout.
#endif
};
