/// @file
/// Forward declares the string types.
///
/// @copyright Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
/// Distributed under the Boost Software License, Version 1.0.
/// (See accompanying file LICENSE_1_0.txt or copy at
/// http://www.boost.org/LICENSE_1_0.txt)

#ifndef VSTL_STRINGFWD_HPP
#define VSTL_STRINGFWD_HPP

#include <vstl/detail/config.hpp>

#if VSTD_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/container/container_fwd.hpp>

namespace boost {
namespace container {
namespace pmr {

typedef boost::container::
    basic_string<char, std::char_traits<char>, polymorphic_allocator<char>>
        string;

}
}
}

VSTL_NS_BEGIN

using boost::container::pmr::string;

VSTL_NS_END

#endif
