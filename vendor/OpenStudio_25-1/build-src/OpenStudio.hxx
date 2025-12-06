/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef OPENSTUDIO_HXX
#define OPENSTUDIO_HXX

#include <string>
#include <string_view>

// Support for Ninja on Windows (Ninja isn't multi-configuration while MSVC is)
/* #undef NINJA */

// Return the version in MAJOR.MINOR.PATCH format (eg '3.0.0')
inline std::string openStudioVersion() {
  return "3.10.0";
}

// Includes prerelease tag if any, and build sha, eg: '3.0.0-rc1+baflkdhsia'
inline std::string openStudioLongVersion() {
  return "3.10.0+e80a80c812";
}

inline std::string openStudioVersionMajor() {
  return "3";
}

inline std::string openStudioVersionMinor() {
  return "10";
}

inline std::string openStudioVersionPatch() {
  return "0";
}

inline std::string openStudioVersionPrerelease() {
  return "";
}

inline std::string openStudioVersionBuildSHA() {
  return "e80a80c812";
}

inline int energyPlusVersionMajor() {
  return 25;
}

inline int energyPlusVersionMinor() {
  return 1;
}

inline int energyPlusVersionPatch() {
  return 0;
}

inline std::string energyPlusVersion() {
  return "25.1.0";
}

inline std::string energyPlusBuildSHA() {
  return "1c11a3d85f";
}

inline std::string rubyLibDir() {
  return "C:/dev/git-OpenStudio-25-1/ruby/";
}

inline std::string rubyOpenStudioDir() {
#ifdef WIN32
#  ifdef NINJA
  return "C:/dev/OpenStudio_25-1_build/release/ruby/";
#  else
  return "C:/dev/OpenStudio_25-1_build/release/ruby/" + std::string(CMAKE_INTDIR) + "/";
#  endif
#else
  return "C:/dev/OpenStudio_25-1_build/release/ruby/";
#endif
}

namespace openstudio {
namespace detail {

inline constexpr int cx_openStudioVersionMajor() {
  return 3;
}
inline constexpr int cx_openStudioVersionMinor() {
  return 10;
}
inline constexpr int cx_openStudioVersionPatch() {
  return 0;
}
inline constexpr std::string_view cx_openStudioVersion() {
  return "3.10.0";
}

}  // namespace detail
}  // namespace openstudio

#endif  // OPENSTUDIO_HXX
