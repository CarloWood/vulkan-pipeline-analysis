#pragma once

#include "PipelineLayout.h"
#include "Stage.h"
#include <array>

class Pipeline
{
  PipelineLayout m_layout;
  std::array<Stage, number_of_stages> m_stages;
};
