/// @file
/// Defines the vstd::vector template
///
/// @copyright Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
/// Distributed under the Boost Software License, Version 1.0.
/// (See accompanying file LICENSE_1_0.txt or copy at
/// http://www.boost.org/LICENSE_1_0.txt)

#ifndef VSTL_VECTOR_HPP
#define VSTL_VECTOR_HPP

#include <vstl/detail/config.hpp>

#if VSTD_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <vector>

VSTL_NS_BEGIN

using std::vector;

template <typename T, class Allocator, typename Predicate>
inline void erase_if(vector<T, Allocator>& c, Predicate p)
{
  c.erase(std::remove_if(c.begin(), c.end(), p), c.end());
}

template <typename T, class Allocator, typename U>
inline void erase(vector<T, Allocator>& c, const U& v)
{
  c.erase(std::remove(c.begin(), c.end(), v), c.end());
}

VSTL_NS_END

#endif
