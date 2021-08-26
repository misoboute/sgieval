#pragma once

#include <cstdint>
#include <unordered_set>

namespace sgieval
{

class UnsortedUIntPairSet
{
  public:
    using UInt = std::uint32_t;
    using UIntWide = std::uint64_t;

    void AddPair(UInt first, UInt second)
    {
        m_set.insert(ConvertPairToUIntWide(first, second));
    }

    bool HasPair(UInt first, UInt second) const
    {
        return m_set.find(ConvertPairToUIntWide(first, second)) != m_set.cend();
    }

    size_t Count() const
    {
        return m_set.size();
    }

  private:
    union UIntPair {
        UIntPair(std::uint32_t a, std::uint32_t b) : m_first(a), m_second(b)
        {
        }

        struct
        {
            std::uint32_t m_first, m_second;
        };
        std::uint64_t m_both;
    };

    static UIntWide ConvertPairToUIntWide(UInt a, UInt b)
    {
        return (a > b ? UIntPair(b, a) : UIntPair(a, b)).m_both;
    };

    std::unordered_set<UIntWide> m_set;
};

} // namespace sgieval
