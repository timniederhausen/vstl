/// @file
/// vstd::string_view template instantiation
///
/// @copyright Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
/// Distributed under the Boost Software License, Version 1.0.
/// (See accompanying file LICENSE_1_0.txt or copy at
/// http://www.boost.org/LICENSE_1_0.txt)

#define VSTD_BUILDING_STRINGVIEW 1

#include <vstl/string_view.hpp>

VSTL_NS_BEGIN

template class basic_string_view<char, std::char_traits<char>>;
template class basic_string_view<wchar_t, std::char_traits<wchar_t>>;

VSTL_NS_END
