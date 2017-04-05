#ifndef VSTL_STRING_VIEW_HPP
#define VSTL_STRING_VIEW_HPP

#include <vstl/detail/config.hpp>

#if VSTD_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <vstl/string.hpp>

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/throw_exception.hpp>

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <iosfwd>

VSTL_NS_BEGIN

/// Mostly-conforming implementation of std::basic_string_view
/// @todo constexpr versions of functions using char_traits
template <class T, class Traits = std::char_traits<T>>
class basic_string_view
{
public:
  // types
  typedef Traits traits_type;
  typedef T value_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
  typedef const_pointer const_iterator;
  typedef const_iterator iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef const_reverse_iterator reverse_iterator;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  static BOOST_CONSTEXPR_OR_CONST size_type npos = size_type(~0);

  // 7.3, basic_string_view constructors and assignment operators
  BOOST_CONSTEXPR basic_string_view() BOOST_NOEXCEPT
    : data_(nullptr)
    , size_(0)
  {
    // ctor
  }

  BOOST_CONSTEXPR basic_string_view(const basic_string_view&)
      BOOST_NOEXCEPT = default;
  basic_string_view& operator=(const basic_string_view&)
      BOOST_NOEXCEPT = default;

  basic_string_view(const basic_string<T, Traits>& str)
    : data_(str.data())
    , size_(str.size())
  {
    // ctor
  }

  BOOST_CONSTEXPR basic_string_view(const T* str)
    : data_(str)
    , size_(traits_type::length(str))
  {
    // ctor
  }

  BOOST_CONSTEXPR basic_string_view(const T* str, size_type len)
    : data_(str)
    , size_(len)
  {
    // ctor
  }

  // 7.4, basic_string_view iterator support
  BOOST_CONSTEXPR const_iterator begin() const BOOST_NOEXCEPT
  {
    return data_;
  }
  BOOST_CONSTEXPR const_iterator end() const BOOST_NOEXCEPT
  {
    return data_ + size_;
  }

  BOOST_CONSTEXPR const_iterator cbegin() const BOOST_NOEXCEPT
  {
    return data_;
  }
  BOOST_CONSTEXPR const_iterator cend() const BOOST_NOEXCEPT
  {
    return data_ + size_;
  }

  const_reverse_iterator rbegin() const BOOST_NOEXCEPT
  {
    return const_reverse_iterator(end());
  }
  const_reverse_iterator rend() const BOOST_NOEXCEPT
  {
    return const_reverse_iterator(end());
  }

  const_reverse_iterator crbegin() const BOOST_NOEXCEPT
  {
    return const_reverse_iterator(begin());
  }
  const_reverse_iterator crend() const BOOST_NOEXCEPT
  {
    return const_reverse_iterator(begin());
  }

  // 7.5, basic_string_view capacity
  BOOST_CONSTEXPR size_type size() const BOOST_NOEXCEPT
  {
    return size_;
  }
  BOOST_CONSTEXPR size_type length() const BOOST_NOEXCEPT
  {
    return size_;
  }
  BOOST_CONSTEXPR size_type max_size() const BOOST_NOEXCEPT
  {
    return size_;
  }
  BOOST_CONSTEXPR bool empty() const BOOST_NOEXCEPT
  {
    return size_ == 0;
  }

  // 7.6, basic_string_view element access
  BOOST_CONSTEXPR const_reference operator[](size_type pos) const
  {
    // TODO(tim): assert
    return data_[pos];
  }

  BOOST_CONSTEXPR const_reference at(size_type pos) const
  {
    return pos < size_ ? data_[pos] :
      (BOOST_THROW_EXCEPTION(std::out_of_range("vstd::basic_string_view::at")), data_[0]);
  }

  BOOST_CONSTEXPR const_reference front() const
  {
    // TODO(tim): assert
    return data_[0];
  }

  BOOST_CONSTEXPR const_reference back() const
  {
    // TODO(tim): assert
    return data_[size_ - 1];
  }

  BOOST_CONSTEXPR const_pointer data() const BOOST_NOEXCEPT
  {
    return data_;
  }

  // 7.7, basic_string_view modifiers
  BOOST_CXX14_CONSTEXPR void clear() BOOST_NOEXCEPT
  {
    data_ = nullptr;
    size_ = 0;
  }

  BOOST_CXX14_CONSTEXPR void remove_prefix(size_type n)
  {
    // TODO(tim): assert
    data_ += n;
    size_ -= n;
  }

  BOOST_CXX14_CONSTEXPR void remove_suffix(size_type n)
  {
    // TODO(tim): assert
    size_ -= n;
  }

  BOOST_CXX14_CONSTEXPR void swap(basic_string_view& s) BOOST_NOEXCEPT
  {
    const const_pointer data = s.data_;
    s.data_ = data_;
    data_ = data;

    const size_type size = s.size_;
    s.size_ = size_;
    size_ = size;
  }

  size_type copy(T* s, size_type n, size_type pos = 0) const
  {
    n = std::min(n, size_ - pos);
    traits_type::copy(s, data_ + pos, n);
    return n;
  }

  BOOST_CONSTEXPR basic_string_view substr(size_type pos = 0,
                                           size_type n = npos) const
  {
    return pos <= size_ ?
      basic_string_view(data_ + pos, std::min(n, size_ - pos)) :
      (BOOST_THROW_EXCEPTION(
          std::out_of_range("vstd::basic_string_view::substr")),
       basic_string_view());
  }

  int compare(const basic_string_view& s) const BOOST_NOEXCEPT
  {
    const size_type l1 = size_, l2 = s.size_, lm = std::min(l1, l2);
    int r = traits_type::compare(data_, s.data_, lm);
    if (r == 0 && l1 != l2)
      r = l1 < l2 ? -1 : 1;
    return r;
  }

  int compare(size_type pos1, size_type n1, const basic_string_view& s) const
  {
    return substr(pos1, n1).compare(s);
  }

  int compare(size_type pos1,
              size_type n1,
              const basic_string_view& s,
              size_type pos2,
              size_type n2) const
  {
    return substr(pos1, n1).compare(s.substr(pos2, n2));
  }

  int compare(const_pointer s) const
  {
    return compare(basic_string_view(s));
  }

  int compare(size_type pos1, size_type n1, const_pointer s) const
  {
    return substr(pos1, n1).compare(basic_string_view(s));
  }

  int compare(size_type pos1, size_type n1, const_pointer s, size_type n2) const
  {
    return substr(pos1, n1).compare(basic_string_view(s, n2));
  }

  size_type find(basic_string_view s, size_type pos = 0) const BOOST_NOEXCEPT
  {
    return find(s.data(), pos, s.size_);
  }

  size_type find(T c, size_type pos = 0) const BOOST_NOEXCEPT
  {
    size_type r = npos;
    if (pos < size_) {
      const size_type n = size_ - pos;
      const T* p = traits_type::find(data_ + pos, n, c);
      if (p)
        r = p - data_;
    }
    return r;
  }

  size_type find(const_pointer s, size_type pos, size_type n) const
  {
    if (n == 0)
      return pos <= size_ ? pos : npos;

    if (n <= size_) {
      for (; pos <= size_ - n; ++pos) {
        if (traits_type::eq(data_[pos], s[0]) &&
            traits_type::compare(data_ + pos + 1, s + 1, n - 1) == 0)
          return pos;
      }
    }
    return npos;
  }

  size_type find(const_pointer s, size_type pos = 0) const
  {
    return find(s, pos, traits_type::length(s));
  }

  size_type rfind(basic_string_view s,
                  size_type pos = npos) const BOOST_NOEXCEPT
  {
    return rfind(s.data(), pos, s.size_);
  }

  size_type rfind(T c, size_type pos = npos) const BOOST_NOEXCEPT
  {
    size_type size = size_;
    if (size != 0) {
      if (--size > pos)
        size = pos;
      for (++size; size-- > 0;)
        if (traits_type::eq(data_[size], c))
          return size;
    }
    return npos;
  }

  size_type rfind(const_pointer s, size_type pos, size_type n) const
  {
    if (n <= size_) {
      pos = std::min(size_type(size_ - n), pos);
      do {
        if (traits_type::compare(data_ + pos, s, n) == 0)
          return pos;
      } while (pos-- > 0);
    }
    return npos;
  }

  size_type rfind(const_pointer s, size_type pos = npos) const
  {
    return rfind(s, pos, traits_type::length(s));
  }

  size_type find_first_of(basic_string_view s,
                          size_type pos = 0) const BOOST_NOEXCEPT
  {
    return find_first_of(s.data(), pos, s.size_);
  }

  size_type find_first_of(T c, size_type pos = 0) const BOOST_NOEXCEPT
  {
    return find(c, pos);
  }

  size_type find_first_of(const_pointer s, size_type pos, size_type n) const
  {
    for (; n != 0 && pos < size_; ++pos) {
      const T* p = traits_type::find(s, n, data_[pos]);
      if (p)
        return pos;
    }
    return npos;
  }

  size_type find_first_of(const_pointer s, size_type pos = 0) const
  {
    return find_first_of(s, pos, traits_type::length(s));
  }

  size_type find_last_of(basic_string_view s,
                         size_type pos = npos) const BOOST_NOEXCEPT
  {
    return find_last_of(s.data(), pos, s.size_);
  }

  size_type find_last_of(T c, size_type pos = npos) const BOOST_NOEXCEPT
  {
    return rfind(c, pos);
  }

  size_type find_last_of(const_pointer s, size_type pos, size_type n) const
  {
    size_type size = size_;
    if (size != 0 && n != 0) {
      if (--size > pos)
        size = pos;
      do {
        if (traits_type::find(s, n, data_[size]))
          return size;
      } while (size-- != 0);
    }
    return npos;
  }

  size_type find_last_of(const_pointer s, size_type pos = npos) const
  {
    return find_last_of(s, pos, traits_type::length(s));
  }

  size_type find_first_not_of(basic_string_view s,
                              size_type pos = 0) const BOOST_NOEXCEPT
  {
    return find_first_not_of(s.data(), pos, s.size_);
  }

  size_type find_first_not_of(T c, size_type pos = 0) const BOOST_NOEXCEPT
  {
    for (; pos < size_; ++pos)
      if (!traits_type::eq(data_[pos], c))
        return pos;
    return npos;
  }

  size_type find_first_not_of(const_pointer s, size_type pos, size_type n) const
  {
    for (; pos < size_; ++pos)
      if (!traits_type::find(s, n, data_[pos]))
        return pos;
    return npos;
  }

  size_type find_first_not_of(const_pointer s, size_type pos = 0) const
  {
    return find_first_not_of(s, pos, traits_type::length(s));
  }

  size_type find_last_not_of(basic_string_view s,
                             size_type pos = npos) const BOOST_NOEXCEPT
  {
    return find_last_not_of(s.data(), pos, s.size_);
  }

  size_type find_last_not_of(T c, size_type pos = npos) const BOOST_NOEXCEPT
  {
    size_type size = size_;
    if (size != 0) {
      if (--size > pos)
        size = pos;
      do {
        if (!traits_type::eq(data_[size], c))
          return size;
      } while (size-- != 0);
    }
    return npos;
  }

  size_type find_last_not_of(const_pointer s, size_type pos, size_type n) const
  {
    size_type size = size_;
    if (size != 0) {
      if (--size > pos)
        size = pos;
      do {
        if (!traits_type::find(s, n, data_[size]))
          return size;
      } while (size-- != 0);
    }
    return npos;
  }

  size_type find_last_not_of(const_pointer s, size_type pos = npos) const
  {
    return find_last_not_of(s, pos, traits_type::length(s));
  }

// extensions
#ifndef BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
  explicit operator basic_string<T, Traits>() const
  {
    return basic_string<T, Traits>(data_, size_);
  }
#endif

  basic_string<T, Traits> to_string() const
  {
    return basic_string<T, Traits>(data_, size_);
  }

  bool starts_with(T c) const
  {
    return !empty() && traits_type::eq(c, *data_);
  }

  bool starts_with(const basic_string_view& s) const
  {
    return size_ >= s.size_ &&
           traits_type::compare(data_, s.data_, s.size_) == 0;
  }

  bool ends_with(T c) const
  {
    return !empty() && traits_type::eq(c, data_[size_ - 1]);
  }

  bool ends_with(const basic_string_view& s) const
  {
    return size_ >= s.size_ &&
           traits_type::compare(data_ + size_ - s.size_, s.data_, s.size_) == 0;
  }

private:
  const_pointer data_;
  size_type size_;
};

template <typename T, typename Traits>
inline bool operator==(const basic_string_view<T, Traits>& x,
                       const basic_string_view<T, Traits>& y)
{
  if (x.size() != y.size())
    return false;
  return x.compare(y) == 0;
}

template <typename T, typename Traits, typename Allocator>
inline bool operator==(const basic_string_view<T, Traits>& x,
                       const basic_string<T, Traits>& y)
{
  return x == basic_string_view<T, Traits>(y);
}

template <typename T, typename Traits, typename Allocator>
inline bool operator==(const basic_string<T, Traits>& x,
                       const basic_string_view<T, Traits>& y)
{
  return basic_string_view<T, Traits>(x) == y;
}

template <typename T, typename Traits>
inline bool operator==(const basic_string_view<T, Traits>& x, const T* y)
{
  return x == basic_string_view<T, Traits>(y);
}

template <typename T, typename Traits>
inline bool operator==(const T* x, const basic_string_view<T, Traits>& y)
{
  return basic_string_view<T, Traits>(x) == y;
}

template <typename T, typename Traits>
inline bool operator!=(const basic_string_view<T, Traits>& x,
                       const basic_string_view<T, Traits>& y)
{
  if (x.size() != y.size())
    return true;
  return x.compare(y) != 0;
}

template <typename T, typename Traits>
inline bool operator!=(const basic_string_view<T, Traits>& x,
                       const basic_string<T, Traits>& y)
{
  return x != basic_string_view<T, Traits>(y);
}

template <typename T, typename Traits>
inline bool operator!=(const basic_string<T, Traits>& x,
                       const basic_string_view<T, Traits>& y)
{
  return basic_string_view<T, Traits>(x) != y;
}

template <typename T, typename Traits>
inline bool operator!=(const basic_string_view<T, Traits>& x, const T* y)
{
  return x != basic_string_view<T, Traits>(y);
}

template <typename T, typename Traits>
inline bool operator!=(const T* x, const basic_string_view<T, Traits>& y)
{
  return basic_string_view<T, Traits>(x) != y;
}

template <typename T, typename Traits>
inline bool operator<(const basic_string_view<T, Traits>& x,
                      const basic_string_view<T, Traits>& y)
{
  return x.compare(y) < 0;
}

template <typename T, typename Traits>
inline bool operator<(const basic_string_view<T, Traits>& x,
                      const basic_string<T, Traits>& y)
{
  return x < basic_string_view<T, Traits>(y);
}

template <typename T, typename Traits>
inline bool operator<(const basic_string<T, Traits>& x,
                      const basic_string_view<T, Traits>& y)
{
  return basic_string_view<T, Traits>(x) < y;
}

template <typename T, typename Traits>
inline bool operator<(const basic_string_view<T, Traits>& x, const T* y)
{
  return x < basic_string_view<T, Traits>(y);
}

template <typename T, typename Traits>
inline bool operator<(const T* x, const basic_string_view<T, Traits>& y)
{
  return basic_string_view<T, Traits>(x) < y;
}

template <typename T, typename Traits>
inline bool operator>(const basic_string_view<T, Traits>& x,
                      const basic_string_view<T, Traits>& y)
{
  return x.compare(y) > 0;
}

template <typename T, typename Traits>
inline bool operator>(const basic_string_view<T, Traits>& x,
                      const basic_string<T, Traits>& y)
{
  return x > basic_string_view<T, Traits>(y);
}

template <typename T, typename Traits>
inline bool operator>(const basic_string<T, Traits>& x,
                      const basic_string_view<T, Traits>& y)
{
  return basic_string_view<T, Traits>(x) > y;
}

template <typename T, typename Traits>
inline bool operator>(const basic_string_view<T, Traits>& x, const T* y)
{
  return x > basic_string_view<T, Traits>(y);
}

template <typename T, typename Traits>
inline bool operator>(const T* x, const basic_string_view<T, Traits>& y)
{
  return basic_string_view<T, Traits>(x) > y;
}

template <typename T, typename Traits>
inline bool operator<=(const basic_string_view<T, Traits>& x,
                       const basic_string_view<T, Traits>& y)
{
  return x.compare(y) <= 0;
}

template <typename T, typename Traits>
inline bool operator<=(const basic_string_view<T, Traits>& x,
                       const basic_string<T, Traits>& y)
{
  return x <= basic_string_view<T, Traits>(y);
}

template <typename T, typename Traits>
inline bool operator<=(const basic_string<T, Traits>& x,
                       const basic_string_view<T, Traits>& y)
{
  return basic_string_view<T, Traits>(x) <= y;
}

template <typename T, typename Traits>
inline bool operator<=(const basic_string_view<T, Traits>& x, const T* y)
{
  return x <= basic_string_view<T, Traits>(y);
}

template <typename T, typename Traits>
inline bool operator<=(const T* x, const basic_string_view<T, Traits>& y)
{
  return basic_string_view<T, Traits>(x) <= y;
}

template <typename T, typename Traits>
inline bool operator>=(const basic_string_view<T, Traits>& x,
                       const basic_string_view<T, Traits>& y)
{
  return x.compare(y) >= 0;
}

template <typename T, typename Traits>
inline bool operator>=(const basic_string_view<T, Traits>& x,
                       const vstd::basic_string<T, Traits>& y)
{
  return x >= basic_string_view<T, Traits>(y);
}

template <typename T, typename Traits>
inline bool operator>=(const vstd::basic_string<T, Traits>& x,
                       const basic_string_view<T, Traits>& y)
{
  return basic_string_view<T, Traits>(x) >= y;
}

template <typename T, typename Traits>
inline bool operator>=(const basic_string_view<T, Traits>& x, const T* y)
{
  return x >= basic_string_view<T, Traits>(y);
}

template <typename T, typename Traits>
inline bool operator>=(const T* x, const basic_string_view<T, Traits>& y)
{
  return basic_string_view<T, Traits>(x) >= y;
}

namespace detail
{
template <class T, class Traits>
inline void insert_fill_chars(std::basic_ostream<T, Traits>& os, std::size_t n)
{
  enum
  {
    chunk_size = 8
  };
  T fill_chars[chunk_size];
  std::fill_n(fill_chars, static_cast<std::size_t>(chunk_size), os.fill());
  for (; n >= chunk_size && os.good(); n -= chunk_size)
    os.write(fill_chars, static_cast<std::size_t>(chunk_size));
  if (n > 0 && os.good())
    os.write(fill_chars, n);
}

template <class T, class Traits>
void insert_aligned(std::basic_ostream<T, Traits>& os,
                    const basic_string_view<T, Traits>& str)
{
  const std::size_t size = str.size();
  const std::size_t alignment_size =
      static_cast<std::size_t>(os.width()) - size;
  const bool align_left =
      (os.flags() & std::basic_ostream<T, Traits>::adjustfield) ==
      std::basic_ostream<T, Traits>::left;
  if (!align_left) {
    detail::insert_fill_chars(os, alignment_size);
    if (os.good())
      os.write(str.data(), size);
  } else {
    os.write(str.data(), size);
    if (os.good())
      detail::insert_fill_chars(os, alignment_size);
  }
}

} // namespace detail

// Inserter
template <class T, class Traits>
inline std::basic_ostream<T, Traits>& operator<<(
    std::basic_ostream<T, Traits>& os,
    const basic_string_view<T, Traits>& str)
{
  if (os.good()) {
    const std::size_t size = str.size();
    const std::size_t w = static_cast<std::size_t>(os.width());
    if (w <= size)
      os.write(str.data(), size);
    else
      detail::insert_aligned(os, str);
    os.width(0);
  }
  return os;
}

#if !VSTD_BUILDING_STRINGVIEW
extern template class basic_string_view<char, std::char_traits<char>>;
extern template class basic_string_view<wchar_t, std::char_traits<wchar_t>>;
#endif

typedef basic_string_view<char> string_view;
typedef basic_string_view<wchar_t> wstring_view;

template <class T, class Traits>
inline std::size_t hash_value(const vstd::basic_string_view<T, Traits>& s)
{
  return boost::hash_range(s.begin(), s.end());
}

inline void assign(string& dst, const string_view& src)
{
  dst.assign(src.data(), src.size());
}

inline void assign(wstring& dst, const wstring_view& src)
{
  dst.assign(src.data(), src.size());
}

VSTL_NS_END

namespace std {

template <class T, class Traits>
struct hash<vstd::basic_string_view<T, Traits>>
{
  size_t operator()(const vstd::basic_string_view<T, Traits>& s) const
  {
    return boost::hash_range(s.begin(), s.end());
  }
};

}

#endif
