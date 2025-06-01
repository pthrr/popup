#pragma once

#include "oxidize.hpp"

constexpr u64 KiB = 1024;
constexpr u64 MiB = KiB * KiB;
constexpr u64 GiB = KiB * KiB * KiB;
constexpr u64 TiB = KiB * KiB * KiB * KiB;
constexpr u64 PiB = KiB * KiB * KiB * KiB * KiB;
constexpr u64 EiB = KiB * KiB * KiB * KiB * KiB * KiB;

constexpr auto operator"" _KiB( unsigned long long value ) -> u64
{
    return value * KiB;
}

constexpr auto operator"" _MiB( unsigned long long value ) -> u64
{
    return value * MiB;
}

constexpr auto operator"" _GiB( unsigned long long value ) -> u64
{
    return value * GiB;
}

constexpr auto operator"" _TiB( unsigned long long value ) -> u64
{
    return value * TiB;
}

constexpr auto operator"" _PiB( unsigned long long value ) -> u64
{
    return value * PiB;
}

constexpr auto operator"" _EiB( unsigned long long value ) -> u64
{
    return value * EiB;
}

constexpr u64 kHz = 1e3;
constexpr u64 MHz = 1e6;
constexpr u64 GHz = 1e9;
constexpr u64 THz = 1e12;
constexpr u64 PHz = 1e15;
constexpr u64 EHz = 1e18;

constexpr auto operator"" _kHz( unsigned long long value ) -> u64
{
    return value * kHz;
}

constexpr auto operator"" _MHz( unsigned long long value ) -> u64
{
    return value * MHz;
}

constexpr auto operator"" _GHz( unsigned long long value ) -> u64
{
    return value * GHz;
}

constexpr auto operator"" _THz( unsigned long long value ) -> u64
{
    return value * THz;
}

constexpr auto operator"" _PHz( unsigned long long value ) -> u64
{
    return value * PHz;
}

constexpr auto operator"" _EHz( unsigned long long value ) -> u64
{
    return value * EHz;
}

namespace types {

} // namespace types
