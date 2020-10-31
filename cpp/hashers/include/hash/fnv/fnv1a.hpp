#pragma once

#include <hash/fnv/details.hpp>
#include <string_view>

namespace hash::fnv {

template <typename HashType> //
constexpr HashType fnv1a(std::string_view data) {
  using details::FNV_offset_basis;
  using details::FNV_prime;
  constexpr const HashType offset_basis = FNV_offset_basis<HashType>::value;
  constexpr const HashType prime = FNV_prime<HashType>::value;

  HashType result = offset_basis;
  for (auto &v : data) {
    result ^= static_cast<uint8_t>(v);
    result *= prime;
  }
  return result;
}

} // namespace hash::fnv
