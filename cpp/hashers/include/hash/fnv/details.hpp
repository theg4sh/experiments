#pragma once

#include <cstdint>

namespace hash::fnv::details {

// Magic values got from
// https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV_hash_parameters

template <typename HashType> struct FNV_offset_basis {};
//
template <> struct FNV_offset_basis<uint32_t> {
  static constexpr const uint32_t value = 0x811c9dc5;
};
template <> struct FNV_offset_basis<uint64_t> {
  static constexpr const uint64_t value = 0xcbf29ce484222325UL;
};
// 128: 0x6c62272e07bb014262b821756295c58d
// 256: 0xdd268dbcaac550362d98c384c4e576ccc8b1536847b6bbb31023b4c8caee0535

} // namespace hash::fnv::details

namespace hash::fnv::details {

template <typename HashType> struct FNV_prime {};
//
template <> struct FNV_prime<uint32_t> {
  static constexpr const uint32_t value = 0x0100193;
};
template <> struct FNV_prime<uint64_t> {
  static constexpr const uint64_t value = 0x00000100000001B3UL;
};
// 128: 0x0000000001000000000000000000013B
// 256: 0x0000000000000000000001000000000000000000000000000000000000000163
// clang-format on

} // namespace hash::fnv::details
