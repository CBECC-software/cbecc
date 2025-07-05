#ifndef OPENSTUDIO_HXX
#define OPENSTUDIO_HXX

inline std::string openStudioVersion()
{
  return "1.11.3";
}

inline std::string openStudioLongVersion()
{
  return "1.11.3.f52686d8e1";
}

inline int energyPlusVersionMajor()
{
  return 8;
}

inline int energyPlusVersionMinor()
{
  return 5;
}

inline int energyPlusVersionPatch()
{
  return 0;
}

inline std::string energyPlusVersion()
{
  return "8.5.0";
}

inline std::string energyPlusBuildSHA()
{
  return "c87e61b44b";
}

inline std::string rubyLibDir()
{
  return "C:/Users/Scott/Documents/GitHub/OpenStudio/openstudiocore/ruby/";
}

inline std::string rubyOpenStudioDir()
{
  #ifdef WIN32
    return "C:/dev/OpenStudio-CBECC/OSCore-prefix/src/OSCore-build/ruby/" + std::string(CMAKE_INTDIR) + "/";
  #else
    return "C:/dev/OpenStudio-CBECC/OSCore-prefix/src/OSCore-build/ruby/";
  #endif
}


#endif // OPENSTUDIO_HXX

