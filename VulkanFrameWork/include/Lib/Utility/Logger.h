#pragma once
#include <crtdbg.h>
namespace Lib{
namespace Utility{
#define DBG_PRTF(msg, ...) _RPTN(_CRT_WARN, msg, __VA_ARGS__)
}
}
