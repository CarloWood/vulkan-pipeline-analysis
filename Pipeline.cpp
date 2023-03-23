#include "sys.h"
#include "Pipeline.h"
#include "debug.h"

Declaration const* Pipeline::acquire_slot(Declaration const* current_declaration, SetIndexBindingSlots::bitset_type slot)
{
  utils::bitset::Index i = slot.lssbi();
  Declaration const* previous_stage = m_slot_owner[i()];
  if (!previous_stage)
    m_slot_owner[i()] = current_declaration;
  // Return the previous stage if we're not the owner.
  return previous_stage;
}

void Pipeline::release_slot(Declaration const* current_declaration, SetIndexBindingSlots::bitset_type slot)
{
  utils::bitset::Index i = slot.lssbi();
  // Only the current owner, that called acquire_slot, may release the slot again.
  ASSERT(m_slot_owner[i()] == current_declaration);
  m_slot_owner[i()] = nullptr;
}

bool Pipeline::is_sane() const
{
  std::array<SetIndexBindingSlot::slot_as_bit_type, number_of_stages> slots;
  int stage_index = 0;
  std::deque<DescriptorSetLayout> const& descriptor_set_layouts = m_layout.descriptor_set_layouts();
  for (Stage const& stage : m_stages)
  {
    ShaderModule const& shader_module = stage.module();
    Declarations const& declarations = shader_module.declarations();
    ASSERT(declarations.owning_shader_module() == &shader_module);
    std::deque<Declaration> const& declaration_list = declarations.declaration_list();
    int vi = 0;
    AShaderResourceIndex prev_shader_resource_index;
    slots[stage_index].reset();
    for (Declaration const& declaration : declaration_list)
    {
      ASSERT(declaration.owning_shader_module() == &shader_module);
      SetIndexBindingSlot const& set_index_binding_slot = declaration.set_index_binding_slot();
      ASSERT(set_index_binding_slot.owning_declaration() == &declaration);
      ASSERT(set_index_binding_slot.get_vi() == vi);
      AShaderResource const& a_shader_resource = declaration.a_shader_resource();
      ASSERT(a_shader_resource.owning_declaration() == &declaration);
      ASSERT(a_shader_resource.get_vi() == vi);

      AShaderResourceIndex shader_resource_index = a_shader_resource.get_value();
      ASSERT(prev_shader_resource_index.undefined() || shader_resource_index > prev_shader_resource_index);
      prev_shader_resource_index = shader_resource_index;

      SetIndexBindingSlot::slot_as_bit_type slot_as_bit = set_index_binding_slot.slot_as_bit();
      ASSERT((slots[stage_index] & slot_as_bit).none());
      slots[stage_index] |= slot_as_bit;

      Declaration const* was_used_in = nullptr;
      for (int si = 0; si < stage_index; ++si)
        if ((slots[si] & slot_as_bit).any())
        {
          Stage const& prev_stage = m_stages[si];
          ShaderModule const& prev_shader_module = prev_stage.module();
          Declarations const& prev_declarations = prev_shader_module.declarations();
          std::deque<Declaration> const& prev_declaration_list = prev_declarations.declaration_list();
          for (Declaration const& prev_declaration : prev_declaration_list)
          {
            SetIndexBindingSlot const& prev_set_index_binding_slot = prev_declaration.set_index_binding_slot();
            SetIndexBindingSlot::slot_as_bit_type prev_slot_as_bit = prev_set_index_binding_slot.slot_as_bit();
            if (prev_slot_as_bit == slot_as_bit)
            {
              was_used_in = &prev_declaration;
              break;
            }
          }
          ASSERT(was_used_in);
          break;
        }

      Declaration const* previous_stage = set_index_binding_slot.previous_stage();
      ASSERT(was_used_in == previous_stage);

      DescriptorCount const& descriptor_count = a_shader_resource.descriptor_count();
      if (previous_stage)
      {
        AShaderResource const& prev_a_shader_resource = previous_stage->a_shader_resource();
        ASSERT(a_shader_resource.owning_declaration() != prev_a_shader_resource.owning_declaration());
        ASSERT(descriptor_count == prev_a_shader_resource.descriptor_count());
        AShaderResourceIndex prev_shader_resource_index = prev_a_shader_resource.get_value();
        ASSERT(shader_resource_index == prev_shader_resource_index);
      }

      // Check the layout.
      std::pair<SetIndexIndex, BindingIndex> set_index_binding = set_index_binding_slot.get_set_index_binding();
      SetIndexIndex set_index(utils::bitset::index_begin);
      utils::bitset::Index stage_index2({static_cast<int8_t>(stage_index)});
      bool found_set_index = false;
      bool found_descriptor_set_layout_binding = false;
      for (DescriptorSetLayout const& descriptor_set_layout : descriptor_set_layouts)
      {
        if (set_index == set_index_binding.first)
        {
          found_set_index = true;
          std::vector<DescriptorSetLayoutBinding> const& descriptor_set_layout_bindings = descriptor_set_layout.descriptor_set_layout_bindings();
          for (DescriptorSetLayoutBinding const& descriptor_set_layout_binding : descriptor_set_layout_bindings)
          {
            if (descriptor_set_layout_binding.binding().get_value() == set_index_binding.second)
            {
              ASSERT(!found_descriptor_set_layout_binding);
              found_descriptor_set_layout_binding = true;
              DescriptorType const& descriptor_type = descriptor_set_layout_binding.descriptor_type();
              DescriptorCount const& descriptor_count = descriptor_set_layout_binding.descriptor_count();
              ShaderStageFlags const& stage_flags = descriptor_set_layout_binding.stage_flags();

              ASSERT(stage_flags.test(stage_index2));
              ASSERT(descriptor_type == AShaderResource::shader_resource(a_shader_resource.get_value()).type());
              ASSERT(descriptor_count == a_shader_resource.descriptor_count());
            }
          }
        }
        ++set_index;
      }
      if (!found_descriptor_set_layout_binding)
        DoutFatal(dc::fatal, "Could not find " << set_index_binding_slot << " (used in stage " << stage_index << ") in the layout.");

      ++vi;
    }
    ++stage_index;
  }

  return true;
}

#ifdef CWDEBUG
void Pipeline::print_on(std::ostream& os) const
{
  os << PRINT_TYPE("Pipeline") << '{';
  os << "stages:" << m_stages;
#if !DISABLE_LAYOUT
  os << ",\n    layout:" << m_layout;
#endif
  os << "\n    }";
}
#endif
