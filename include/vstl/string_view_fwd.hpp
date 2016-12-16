/// @file
/// Defines the string types
///
/// @copyright Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
/// Distributed under the Boost Software License, Version 1.0.
/// (See accompanying file LICENSE_1_0.txt or copy at
/// http://www.boost.org/LICENSE_1_0.txt)

#ifndef VSTL_STRING_VIEWFWD_HPP
#define VSTL_STRING_VIEWFWD_HPP

#include <vstl/detail/config.hpp>

#if VSTD_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <string>

VSTL_NS_BEGIN

template <typename charT, typename traits>
class basic_string_view;

typedef basic_string_view<char, std::char_traits<char>> string_view;
typedef basic_string_view<wchar_t, std::char_traits<wchar_t>> wstring_view;

VSTL_NS_END

#endif
