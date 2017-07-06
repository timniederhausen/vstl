/// @file
/// Defines the string types
///
/// @copyright Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
/// Distributed under the Boost Software License, Version 1.0.
/// (See accompanying file LICENSE_1_0.txt or copy at
/// http://www.boost.org/LICENSE_1_0.txt)

#ifndef VSTL_STRING_HPP
#define VSTL_STRING_HPP

#include <vstl/detail/config.hpp>

#if VSTD_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/container/string.hpp>

namespace boost {
namespace container {

extern template class boost::container::basic_string<
    char,
    std::char_traits<char>,
    boost::container::new_allocator<char>>;

extern template class boost::container::basic_string<
    wchar_t,
    std::char_traits<wchar_t>,
    boost::container::new_allocator<wchar_t>>;

}
}

VSTL_NS_BEGIN

using boost::container::basic_string;
using boost::container::string;
using boost::container::wstring;

inline void assign(vstd::string& dst, const std::string& src)
{
  dst.assign(src.data(), src.size());
}

VSTL_NS_END

namespace std {

template <class T, class Traits>
struct hash<vstd::basic_string<T, Traits>>
{
  size_t operator()(const vstd::basic_string<T, Traits>& s) const
  {
    return boost::hash_range(s.begin(), s.end());
  }
};

}

#endif
