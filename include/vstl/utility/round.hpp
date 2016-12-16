/// @file
/// Defines some rounding utility functions.
///
/// @copyright Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
/// Distributed under the Boost Software License, Version 1.0.
/// (See accompanying file LICENSE_1_0.txt or copy at
/// http://www.boost.org/LICENSE_1_0.txt)

#ifndef VSTL_UTILITY_ROUND_HPP
#define VSTL_UTILITY_ROUND_HPP

#include <vstl/detail/config.hpp>

#if VSTD_HAS_PRAGMA_ONCE
#pragma once
#endif

VSTL_NS_BEGIN

template <typename Integer>
BOOST_CONSTEXPR Integer round_down(Integer number, Integer factor)
{
  return number - number % factor;
}

template <typename Integer>
BOOST_CONSTEXPR Integer round_down_pow2(Integer number, Integer factor)
{
  return number - number & (factor - 1);
}

template <typename Integer>
BOOST_CONSTEXPR Integer round_up(Integer number, Integer factor)
{
  return number + factor - (number % factor);
}

template <typename Integer>
BOOST_CONSTEXPR Integer round_up_pow2(Integer number, Integer factor)
{
  return (number + factor - 1) & ~(factor - 1);
}

VSTL_NS_END

#endif
