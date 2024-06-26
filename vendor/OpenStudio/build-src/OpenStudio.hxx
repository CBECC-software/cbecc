#ifndef OPENSTUDIO_HXX
#define OPENSTUDIO_HXX

// Support for Ninja on Windows (Ninja isn't multi-configuration while MSVC is)
/* #undef NINJA */

// Return the version in MAJOR.MINOR.PATCH format (eg '3.0.0')
inline std::string openStudioVersion()
{
  return "3.1.1";
}

// Includes prerelease tag if any, and build sha, eg: '3.0.0-rc1+baflkdhsia'
inline std::string openStudioLongVersion()
{
  return "3.1.1-alpha+67ce318787";
}

inline std::string openStudioVersionMajor()
{
  return "3";
}

inline std::string openStudioVersionMinor()
{
  return "1";
}

inline std::string openStudioVersionPatch()
{
  return "1";
}

inline std::string openStudioVersionPrerelease()
{
  return "alpha";
}

inline std::string openStudioVersionBuildSHA()
{
  return "67ce318787";
}

inline int energyPlusVersionMajor()
{
  return 9;
}

inline int energyPlusVersionMinor()
{
  return 4;
}

inline int energyPlusVersionPatch()
{
  return 0;
}

inline std::string energyPlusVersion()
{
  return "9.4.0";
}

inline std::string energyPlusBuildSHA()
{
  return "998c4b761e";
}

inline std::string rubyLibDir()
{
  return "D:/Dev/git-OpenStudio/ruby/";
}

inline std::string rubyOpenStudioDir()
{
  #ifdef WIN32
    #ifdef NINJA
      return "D:/Dev/git-OpenStudio/build/ruby/";
    #else
      return "D:/Dev/git-OpenStudio/build/ruby/" + std::string(CMAKE_INTDIR) + "/";
    #endif
  #else
    return "D:/Dev/git-OpenStudio/build/ruby/";
  #endif
}


#endif // OPENSTUDIO_HXX

