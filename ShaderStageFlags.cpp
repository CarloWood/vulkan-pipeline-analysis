#include "sys.h"
#include "ShaderStageFlags.h"

//static
std::uniform_int_distribution<decltype(ShaderStageFlags::m_bitmask)> ShaderStageFlags::s_distribution(1, (1 << number_of_stages) - 1);
