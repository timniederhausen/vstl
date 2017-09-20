/// @file
/// vstd::string template instantiation
///
/// @copyright Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
/// Distributed under the Boost Software License, Version 1.0.
/// (See accompanying file LICENSE_1_0.txt or copy at
/// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/container/string.hpp>

namespace boost
{
namespace container
{
template class boost::container::basic_string<
    char,
    std::char_traits<char>,
    boost::container::new_allocator<char>>;

template class boost::container::basic_string<
    wchar_t,
    std::char_traits<wchar_t>,
    boost::container::new_allocator<wchar_t>>;
}
}
