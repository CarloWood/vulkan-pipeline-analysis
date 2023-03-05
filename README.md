# vulkan-pipeline-analysis

## vk::Pipeline

A VkPipeline (vk::Pipeline) is created by a call to vkCreateGraphicsPipelines.
Each pipeline that this function creates uses a VkGraphicsPipelineCreateInfo
(vk::GraphicsPipelineCreateInfo) as create info. This struct contains, among
others:

    // Pipeline
    uint32_t                                         stageCount;        // Is the number of entries in the pStages array.
    VkPipelineShaderStageCreateInfo const*           pStages;           // Array describing the set of the shader stages to be included.
    VkPipelineLayout                                 layout;            // The description of binding locations used by both the pipeline
                                                                        // and descriptor sets used with the pipeline.

### vk::GraphicsPipelineCreateInfo::pStages

Each of the `stageCount` stages can be one of the types enumerated by vk::ShaderStageFlagBits,
for example eVertex, eGeometry, eFragment, eCompute, etc. There can only be at most one of each type.

The struct VkPipelineShaderStageCreateInfo contains, among others:

    // Stage
    VkShaderStageFlagBits                            stage;             // One bit value specifying a single pipeline stage.
    VkShaderModule                                   module;            // Handle to the compiled shader code for this stage.

#### vk::PipelineShaderStageCreateInfo::module

A VkShaderModule (vk::ShaderModule) is created by a call to vkCreateShaderModule,
which uses a VkShaderModuleCreateInfo as create info. This struct contains,
among others:

    // ShaderModule
    size_t                                           codeSize;          // The size, in bytes, of the code pointed to by pCode.
    uint32_t const*                                  pCode;             // A pointer to code that is used to create the shader module.

### vk::GraphicsPipelineCreateInfo::layout

The layout of the VkPipeline is created by a call to vkCreatePipelineLayout,
which uses a VkPipelineLayoutCreateInfo as create info. This struct contains,
among others:

    // PipelineLayout
    uint32_t                                         setLayoutCount;    // The number of descriptor sets included in the pipeline layout.
    VkDescriptorSetLayout const*                     pSetLayouts;       // Array of descriptor set layout handles.

#### vk::PipelineLayoutCreateInfo::pSetLayouts

Each VkDescriptorSetLayout (vk::DescriptorSetLayout) is created by a call to vkCreateDescriptorSetLayout,
which uses a VkDescriptorSetLayoutCreateInfo as create info. This struct contains,
among others:

    // DescriptorSetLayout
    uint32_t                                         bindingCount;      // The number of elements in pBindings.
    VkDescriptorSetLayoutBinding const*              pBindings;         // Array of VkDescriptorSetLayoutBinding structures.

##### vk::DescriptorSetLayoutCreateInfo::pBindings

The struct VkDescriptorSetLayoutBinding contains, among others:

    // DescriptorSetLayoutBinding
    uint32_t                                         binding;           // The binding number of this entry and corresponds to a resource
                                                                        // of the same binding number in the shader stages.
    VkDescriptorType                                 descriptorType;    // The type of resource descriptors used for this binding.
    uint32_t                                         descriptorCount;   // The number of descriptors contained in the binding, accessed in
                                                                        // a shader as an array (except if descriptorType is
                                                                        // VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK).
    VkShaderStageFlags                               stageFlags;        // A bitmask specifying which stages can access the resource on
                                                                        // this binding.
# vk::ShaderModule declarations

The pipeline layout must match the declarations used in the shader modules
that it is using. Those declaration reveal the same data as that we see
back in VkDescriptorSetLayoutBinding. For example a given VkShaderModule
could contain code (pointed to by pCode) that contains:

    // Declaration               // ShaderResource
    layout(set = 1, binding = 0) uniform sampler2D u_CombinedImageSampler_bottom0[];
    layout(set = 0, binding = 2) uniform u_s0b2 { vec2 unused; float x; } BottomPosition;

where each `layout` line a "declaration" that defines a certain set index, binding
number and shader resource that should be bound.

The shader resource is characterized by its type (the same as vk::DescriptorType) and
by the stages that it must be visible to.

