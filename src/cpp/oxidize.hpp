#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <expected>
#include <print>
#include <source_location>
#include <stdfloat>
#include <string>

using namespace std::literals::string_literals;

// ---------------------------------------------------------------------------

using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;

using i64 = int64_t;
using i32 = int32_t;
using i16 = int16_t;
using i8 = int8_t;

using f128 = std::float128_t;
using f64 = std::float64_t;
using f32 = std::float32_t;
using f16 = std::float16_t;

using usize = size_t;
using isize = ptrdiff_t;

using str = const char*;

constexpr auto operator"" _i8( unsigned long long int value ) -> i8
{
    return static_cast< i8 >( value );
}

constexpr auto operator"" _i16( unsigned long long int value ) -> i16
{
    return static_cast< i16 >( value );
}

constexpr auto operator"" _i32( unsigned long long int value ) -> i32
{
    return static_cast< i32 >( value );
}

constexpr auto operator"" _i64( unsigned long long int value ) -> i64
{
    return static_cast< i64 >( value );
}

constexpr auto operator"" _u8( unsigned long long int value ) -> u8
{
    return static_cast< u8 >( value );
}

constexpr auto operator"" _u16( unsigned long long int value ) -> u16
{
    return static_cast< u16 >( value );
}

constexpr auto operator"" _u32( unsigned long long int value ) -> u32
{
    return static_cast< u32 >( value );
}

constexpr auto operator"" _u64( unsigned long long int value ) -> u64
{
    return static_cast< u64 >( value );
}

constexpr auto operator"" _f16( long double value ) -> f16
{
    return static_cast< f16 >( value );
}

constexpr auto operator"" _f32( long double value ) -> f32
{
    return static_cast< f32 >( value );
}

constexpr auto operator"" _f64( long double value ) -> f64
{
    return static_cast< f64 >( value );
}

constexpr auto operator"" _f128( long double value ) -> f128
{
    return static_cast< f128 >( value );
}

// ---------------------------------------------------------------------------

inline auto panic( std::string const& message ) -> void
{
    throw std::runtime_error( message );
}

inline auto todo() -> void
{
    throw std::logic_error( "Not yet implemented" );
}

using std::unreachable;

// ---------------------------------------------------------------------------

#ifdef NDEBUG
#define DEBUG_ASSERT( condition ) ( (void)0 )
#else
#define DEBUG_ASSERT( condition ) assert( condition )
#endif

#ifdef NDEBUG
#define DBG( x ) ( x )
#else
#define DBG( x ) oxidize::dbg_impl( ( x ), #x, std::source_location::current() )
#endif

// ---------------------------------------------------------------------------

struct [[nodiscard]] Error
{
    enum class ErrorType
    {
        ArithmeticError,
        FloatingPointError,
        OverflowError,
        ZeroDivisionError,
        AssertionError,
        AttributeError,
        IndexError,
        KeyError,
        OSError,
        TimeoutError,
        RuntimeError,
        NotImplementedError,
        SyntaxError,
        SystemError,
        TypeError,
        ValueError,
        GenericError,
    };

    str message;
    ErrorType type;

    explicit Error( str msg, ErrorType typ )
        : message( msg )
        , type( typ )
    {
    }

    // clang-format off
    static auto to_string( ErrorType typ ) -> str {
        switch ( typ ) {
            case Error::ErrorType::ArithmeticError: return "ArithmeticError";
            case Error::ErrorType::FloatingPointError: return "FloatingPointError";
            case Error::ErrorType::OverflowError: return "OverflowError";
            case Error::ErrorType::ZeroDivisionError: return "ZeroDivisionError";
            case Error::ErrorType::AssertionError: return "AssertionError";
            case Error::ErrorType::AttributeError: return "AttributeError";
            case Error::ErrorType::IndexError: return "IndexError";
            case Error::ErrorType::KeyError: return "KeyError";
            case Error::ErrorType::OSError: return "OSError";
            case Error::ErrorType::TimeoutError: return "TimeoutError";
            case Error::ErrorType::RuntimeError: return "RuntimeError";
            case Error::ErrorType::NotImplementedError: return "NotImplementedError";
            case Error::ErrorType::SyntaxError: return "SyntaxError";
            case Error::ErrorType::SystemError: return "SystemError";
            case Error::ErrorType::TypeError: return "TypeError";
            case Error::ErrorType::ValueError: return "ValueError";
            case Error::ErrorType::GenericError: return "GenericError";
            default: return "UnknownError";
        }
    } // clang-format on

    [[nodiscard]] auto to_string() const -> std::string
    {
        return std::format( "{}: {}", to_string( type ), message );
    }
};

template< typename T >
using Result = std::expected< T, Error >;
using Status = Result< void >;

template< typename T >
inline auto Ok( T value ) -> Result< T >
{
    return value;
}

inline auto Err( str msg, Error::ErrorType typ = Error::ErrorType::GenericError ) -> std::unexpected< Error >
{
    return std::unexpected< Error >( Error( msg, typ ) );
}

namespace oxidize {

template< typename T >
auto dbg_impl( T&& value, str expr, std::source_location const location ) -> T
{
    std::print( "{} = {} ({}:{}:{}:{}\n",
        expr,
        value,
        location.file_name(),
        location.function_name(),
        location.line(),
        location.column() );
    return std::forward< T >( value );
}

} // namespace oxidize
