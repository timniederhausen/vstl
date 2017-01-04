/// @file
/// vstd::string_view tests
///
/// @copyright Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
/// Distributed under the Boost Software License, Version 1.0.
/// (See accompanying file LICENSE_1_0.txt or copy at
/// http://www.boost.org/LICENSE_1_0.txt)

#include <vstl/string_view.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(vstl_string_view)

BOOST_AUTO_TEST_CASE(constructor)
{
  const vstd::string_view v1{};
  BOOST_CHECK(v1.size() == 0);
  BOOST_CHECK(v1.data() == nullptr);
  BOOST_CHECK(v1.empty());

  const vstd::string_view v2{"Hallo Welt"};
  BOOST_CHECK(v2.size() == 10);
  BOOST_CHECK(!v2.empty());

  const vstd::string_view v3{v2};
  BOOST_CHECK(v3.size() == v2.size());
  BOOST_CHECK(v3.data() == v2.data());
  const vstd::string_view v4{v1};
  BOOST_CHECK(v4.size() == v1.size());
  BOOST_CHECK(v4.data() == v1.data());

  const vstd::string s1{"Hallo Welt"};
  const vstd::string_view v5{s1};
  BOOST_CHECK(v5.size() == s1.size());
  BOOST_CHECK(v5.data() == s1.data());
}

// Test hash equivalence between string and string_view
BOOST_AUTO_TEST_CASE(hash_equivalence)
{
  const vstd::string_view v1{"Hallo Welt"};
  const vstd::string s1{"Hallo Welt"};

  BOOST_CHECK(std::hash<vstd::string_view>()(v1) ==
              std::hash<vstd::string>()(s1));

  const vstd::wstring_view v2{L"Hallo Welt"};
  const vstd::wstring s2{L"Hallo Welt"};

  BOOST_CHECK(std::hash<vstd::wstring_view>()(v2) ==
              std::hash<vstd::wstring>()(s2));
}

BOOST_AUTO_TEST_SUITE_END()
