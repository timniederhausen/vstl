/// @file
/// Defines the C++17 size() function.
///
/// @copyright Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
/// Distributed under the Boost Software License, Version 1.0.
/// (See accompanying file LICENSE_1_0.txt or copy at
/// http://www.boost.org/LICENSE_1_0.txt)

#ifndef VSTL_ITERATOR_SIZE_HPP
#define VSTL_ITERATOR_SIZE_HPP

#include <vstl/detail/config.hpp>

#if VSTD_HAS_PRAGMA_ONCE
# pragma once
#endif

VSTL_NS_BEGIN

template <class C>
BOOST_CONSTEXPR auto size(const C& c) -> decltype(c.size())
{
  return c.size();
}

template <class T, std::size_t N>
BOOST_CONSTEXPR std::size_t size(const T (&array)[N]) noexcept
{
  return N;
}

VSTL_NS_END

#endif
