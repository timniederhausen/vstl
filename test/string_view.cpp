/// @file
/// vstd::string_view tests
///
/// @copyright Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
/// Distributed under the Boost Software License, Version 1.0.
/// (See accompanying file LICENSE_1_0.txt or copy at
/// http://www.boost.org/LICENSE_1_0.txt)

#include <vstl/string_view.hpp>

#include <gtest/gtest.h>

VSTL_NS_BEGIN

TEST(StringView, Ctor)
{
  const vstd::string_view v1{};
  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v1.data(), nullptr);
  EXPECT_EQ(v1.empty(), true);

  const vstd::string_view v2{"Hallo Welt"};
  EXPECT_EQ(v2.size(), 10);
  EXPECT_EQ(v2.empty(), false);

  const vstd::string_view v3{v2};
  EXPECT_EQ(v3.size(), v2.size());
  EXPECT_EQ(v3.data(), v2.data());
  const vstd::string_view v4{v1};
  EXPECT_EQ(v4.size(), v1.size());
  EXPECT_EQ(v4.data(), v1.data());

  const vstd::string s1{"Hallo Welt"};
  const vstd::string_view v5{s1};
  EXPECT_EQ(v5.size(), s1.size());
  EXPECT_EQ(v5.data(), s1.data());
}

// Test hash equivalence between string and string_view
TEST(StringView, Hash)
{
  const vstd::string_view v1{"Hallo Welt"};
  const vstd::string s1{"Hallo Welt"};

  EXPECT_EQ(std::hash<vstd::string_view>()(v1), std::hash<vstd::string>()(s1));

  const vstd::wstring_view v2{L"Hallo Welt"};
  const vstd::wstring s2{L"Hallo Welt"};

  EXPECT_EQ(std::hash<vstd::wstring_view>()(v2),
            std::hash<vstd::wstring>()(s2));
}

VSTL_NS_END
