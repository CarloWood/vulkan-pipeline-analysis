#pragma once

static constexpr number_of_stages = 3;

using stage_id = int;
using stage_id_mask = unsigned int;

class Stage
{
  stage_id m_id;

 public:
  static stage_id_mask id_to_mask(stage_id id)
  {
    return stage_id_mask{1} << id;
  }

  static stage_id mask_to_id(stage_id_mask bit)
  {
    utils::
  }

  Stage(stage_id id) : m_id(id)
  {
    assert(0 <= id && id < number_of_stages);
  }
};
