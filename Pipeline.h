#pragma once

#include "PipelineLayout.h"
#include "Stage.h"
#include "Generated.h"
#include "utils/has_print_on.h"
#include <array>

using utils::has_print_on::operator<<;

class Pipeline : public Generated<std::tuple<std::array<Stage, number_of_stages>&, PipelineLayout&>>
{                                                       // vk::GraphicsPipelineCreateInfo element(s).
 public:
  Pipeline() : Generated("Pipeline", std::forward_as_tuple(m_stages, m_layout)), m_stages{ stage0, stage1, stage2 }
  {
  }

#ifdef CWDEBUG
  void print_on(std::ostream& os) const;
#endif

 private:
  std::array<Stage, number_of_stages> m_stages;         // stageCount, pStages.
  PipelineLayout m_layout;                              // layout.
};
