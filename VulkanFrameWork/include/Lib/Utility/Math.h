#pragma once
namespace Lib{
namespace Utility{
template<typename T>
T Max(T const& a, T const& b) {
	return (a >= b) ? a : b;
}

template<typename T>
T const& Max(T const& a, T const& b) {
	return (a >= b) ? a : b;
}
template<typename T>
T const& Min(T const& a, T const& b) {
	return (a <= b) ? a : b;
}
}
}

