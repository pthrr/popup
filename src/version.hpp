#pragma once

#include <string_view>

namespace version {

constexpr int PROJECT_VERSION_MAJOR{ 0 };
constexpr int PROJECT_VERSION_MINOR{ 1 };
constexpr int PROJECT_VERSION_PATCH{ 0 };

struct Version
{
    int major = -1;
    int minor = -1;
    int patch = -1;
};

constexpr Version PROJECT_VERSION{ PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH };

#ifdef NDEBUG
constexpr bool IS_DEBUG = false;
#else
constexpr bool IS_DEBUG = true;
#endif

constexpr std::string_view BUILD_VERSION{ "<COMMIT_SHA>" };
constexpr std::string_view BUILD_TYPE{ IS_DEBUG ? "DEBUG" : "RELEASE" };

} // namespace version
