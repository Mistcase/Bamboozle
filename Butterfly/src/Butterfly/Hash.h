#pragma once

#include <cstdint>
#include <string>

namespace butterfly
{
    namespace hash_impl
    {
        // https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
        constexpr uint32_t fnv1a_32(const char* s, size_t size)
        {
            constexpr uint32_t _FNV_offset_basis = 2166136261;
            constexpr uint32_t _FNV_prime = 16777619;

            uint32_t _hash = _FNV_offset_basis;
            for (size_t i = 0; i < size; i++)
            {
                _hash ^= *(s + i);
                _hash *= _FNV_prime;
            }

            return _hash;
        }

    } // namespace hash_impl

    constexpr uint32_t operator"" _hash(const char* s, size_t size)
    {
        return hash_impl::fnv1a_32(s, size);
    }

    inline uint32_t hash(const std::string& s)
    {
        return hash_impl::fnv1a_32(s.c_str(), s.length());
    }

} // namespace butterfly
