# FetchContent was added to 3.14.
cmake_minimum_required(VERSION 3.14...3.17)

# Compile all subdirectories with the same standard.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(vulkan-pipeline-analysis
  LANGUAGES C CXX
  DESCRIPTION "A small test application to investigate dependencies between shader (module)s, descriptor (sets) and shader resources."
)

#==============================================================================
# Begin of gitache configuration.

include(FetchContent)  

set(GITACHE_PACKAGES libcwd_r)  # List of requested packages (example).
FetchContent_Declare(  
  gitache  
  GIT_REPOSITORY "https://github.com/CarloWood/gitache.git"  
  GIT_TAG        "stable"  
)
FetchContent_MakeAvailable(gitache)

# End of gitache configuration.

#==============================================================================
# This project uses aicxx modules.
include(cwm4/cmake/AICxxProject)

#==============================================================================
# OPTIONS

# End of OPTIONS section.

#==============================================================================

# Exit if someone tries to contaminate the source directory with an in-source build.
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "Please do out-of-source builds."
                      "Cleanup: \"rm -rf CMake CMakeCache.txt CMakeFiles/\"")
endif ()

#==============================================================================
# CONFIG FILES

# Tell cwds/sys.h that we have a config.h.
#add_definitions(-DHAVE_CONFIG_H)
#include_directories(${top_objdir})
# End of CONFIG FILES section.

#==============================================================================

# Declare aicxx submodules.
include(AICxxSubmodules)

add_executable(analysis
  main.cpp
  DescriptorSetLayoutBinding.cpp
  Declaration.cpp
  DescriptorSetLayout.cpp
  Pipeline.cpp
  PipelineLayout.cpp
  Stage.cpp
  ShaderModule.cpp
)

target_link_libraries(analysis
  PRIVATE
    ${AICXX_OBJECTS_LIST}
)
