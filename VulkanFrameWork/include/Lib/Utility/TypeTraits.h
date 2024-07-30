#pragma once
#include <type_traits>
#include <functional>

namespace Lib{
namespace Utility{

	template<bool Cond, typename T=void>
	struct EnableIf{};

	template<typename T>
	struct EnableIf<true, T> {
		typedef T type;
	};

template<typename Func, typename... Args>
struct IsInvocable;

template<typename R, typename... Args>
struct IsInvocable<R(*)(Args...)> {
	static const bool value = true;
};

template<typename Func, typename... Args>
struct IsInvocable {
private:
	template<typename F, typename... A>
	static decltype(std::declval(F)(std::declval(A)...), std::true_type) test(int);

	template<typename F, typename... A>
	static std::false_type test(...);
public:
	static const bool value = decltype(test<Func, Args...>(0))::value;
};

template<typename Func>
struct ArgCounter;

//ÉâÉÄÉ_ä÷êî
template<typename ClassName, typename Func, typename... Arg>
struct ArgCounter<Func(ClassName::*)(Arg...)const> {
	static constexpr uint32_t value = sizeof...(Arg);
};


template<typename Func>
struct FunctionTraits;

template<typename Ret, typename... Args>
struct FunctionTraits<Ret(*)(Args...)>
{
	using type = Ret(*)(Args...);
};


template<typename ClassType, typename Ret, typename... Args>
struct FunctionTraits<Ret(ClassType::*)(Args...)const>
{
	using type = Ret(ClassType::*)(Args...)const;
};

template<typename Functor>
struct FunctionTraits
{
	using type = decltype(std::function(std::declval<Functor>()));
};

}
}
#include "Lib/Utility/TypeTraits.inl"