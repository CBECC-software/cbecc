#ifndef OPENSTUDIO_HXX
#define OPENSTUDIO_HXX

#include <string>
#include <string_view>

// Support for Ninja on Windows (Ninja isn't multi-configuration while MSVC is)
/* #undef NINJA */

// Return the version in MAJOR.MINOR.PATCH format (eg '3.0.0')
inline std::string openStudioVersion() {
  return "3.8.0";
}

// Includes prerelease tag if any, and build sha, eg: '3.0.0-rc1+baflkdhsia'
inline std::string openStudioLongVersion() {
  return "3.8.0+3b14b9c731";
}

inline std::string openStudioVersionMajor() {
  return "3";
}

inline std::string openStudioVersionMinor() {
  return "8";
}

inline std::string openStudioVersionPatch() {
  return "0";
}

inline std::string openStudioVersionPrerelease() {
  return "";
}

inline std::string openStudioVersionBuildSHA() {
  return "3b14b9c731";
}

inline int energyPlusVersionMajor() {
  return 24;
}

inline int energyPlusVersionMinor() {
  return 1;
}

inline int energyPlusVersionPatch() {
  return 0;
}

inline std::string energyPlusVersion() {
  return "24.1.0";
}

inline std::string energyPlusBuildSHA() {
  return "9d7789a3ac";
}

inline std::string rubyLibDir() {
  return "C:/dev/git-OpenStudio-24-1/ruby/";
}

inline std::string rubyOpenStudioDir() {
#ifdef WIN32
#  ifdef NINJA
  return "C:/dev/OpenStudio_24-1_build/release/ruby/";
#  else
  return "C:/dev/OpenStudio_24-1_build/release/ruby/" + std::string(CMAKE_INTDIR) + "/";
#  endif
#else
  return "C:/dev/OpenStudio_24-1_build/release/ruby/";
#endif
}

namespace openstudio {
namespace detail {

inline constexpr int cx_openStudioVersionMajor() {
  return 3;
}
inline constexpr int cx_openStudioVersionMinor() {
  return 8;
}
inline constexpr int cx_openStudioVersionPatch() {
  return 0;
}
inline constexpr std::string_view cx_openStudioVersion() {
  return "3.8.0";
}

}  // namespace detail
}  // namespace openstudio

#endif  // OPENSTUDIO_HXX
