#ifndef FMT_H
#define FMT_H
#ifdef _MSC_VER
#define FMT_UNICODE 0
#endif
#include <fmt/core.h>
static_assert(FMT_VERSION >= 50000, "Fmt 5.0.0 or greater is required");
#include <fmt/printf.h>
#if FMT_VERSION >= 80000 || FMT_VERSION < 50300
#include <utility> //std::forward
#include "compiler_features.h"

#define FMT_ADL_FUNCTION_NAME adapt_string_view
#define OVERRIDE_FMT(func) template<typename... Args>\
ForceInline decltype(auto) func(Args&&... args) {\
	return fmt::func(FMT_ADL_FUNCTION_NAME(std::forward<Args>(args))...);\
}
template <typename T>
constexpr ForceInline const T& FMT_ADL_FUNCTION_NAME(const T& obj) {
    return obj;
}
#else
#define FMT_ADL_FUNCTION_NAME to_string_view
#define OVERRIDE_FMT(func) using fmt::func;
#endif
#if FMT_VERSION >= 80000
#include <fmt/xchar.h>
#endif
#if FMT_VERSION >= 60000
#include <fmt/chrono.h>
#else
#include <fmt/time.h>
#endif

namespace nonstd { namespace sv_lite {
template<class CharT, class Traits>
class basic_string_view;
template<typename T, typename Traits>
inline fmt::basic_string_view<T> FMT_ADL_FUNCTION_NAME(const nonstd::sv_lite::basic_string_view<T, Traits>& s) {
	return { s.data(), s.size() };
}
}}

namespace irr {namespace core {
template<typename T, typename TAlloc>
class string;
template<typename T, typename TAlloc>
inline fmt::basic_string_view<T> FMT_ADL_FUNCTION_NAME(const irr::core::string<T, TAlloc>& s) {
	return { s.data(), s.size() };
}
}}

namespace epro {
OVERRIDE_FMT(format)
OVERRIDE_FMT(sprintf)
OVERRIDE_FMT(print)
}
#undef OVERRIDE_FMT
#undef FMT_ADL_FUNCTION_NAME

#endif
