#pragma once
#include <vulkan/vulkan.h>
#include <stdexcept>

#define VEXCEPT(r)\
if(r != VK_SUCCESS){\
throw std::runtime_error("failed "#r);\
}

