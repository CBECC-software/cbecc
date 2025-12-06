/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_GENERATOR_PVWATTS_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_GENERATOR_PVWATTS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Generator_PVWattsFields
 *  \brief Enumeration of OS:Generator:PVWatts's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Generator_PVWattsFields, )
#else
class OS_Generator_PVWattsFields: public ::EnumBase<OS_Generator_PVWattsFields> {
 public: 
  enum domain 
  {
Handle, Name, PVWattsVersion, DCSystemCapacity, ModuleType, ArrayType, SystemLosses, TiltAngle, AzimuthAngle, SurfaceName, GroundCoverageRatio,   };
  OS_Generator_PVWattsFields()
   : EnumBase<OS_Generator_PVWattsFields>(Handle) {} 
  OS_Generator_PVWattsFields(const std::string &t_name) 
   : EnumBase<OS_Generator_PVWattsFields>(t_name) {} 
  OS_Generator_PVWattsFields(int t_value) 
   : EnumBase<OS_Generator_PVWattsFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Generator_PVWattsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Generator_PVWattsFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Generator_PVWattsFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ OS_Generator_PVWattsFields::Handle, "Handle", "Handle"},
{ OS_Generator_PVWattsFields::Name, "Name", "Name"},
{ OS_Generator_PVWattsFields::PVWattsVersion, "PVWattsVersion", "PVWatts Version"},
{ OS_Generator_PVWattsFields::DCSystemCapacity, "DCSystemCapacity", "DC System Capacity"},
{ OS_Generator_PVWattsFields::ModuleType, "ModuleType", "Module Type"},
{ OS_Generator_PVWattsFields::ArrayType, "ArrayType", "Array Type"},
{ OS_Generator_PVWattsFields::SystemLosses, "SystemLosses", "System Losses"},
{ OS_Generator_PVWattsFields::TiltAngle, "TiltAngle", "Tilt Angle"},
{ OS_Generator_PVWattsFields::AzimuthAngle, "AzimuthAngle", "Azimuth Angle"},
{ OS_Generator_PVWattsFields::SurfaceName, "SurfaceName", "Surface Name"},
{ OS_Generator_PVWattsFields::GroundCoverageRatio, "GroundCoverageRatio", "Ground Coverage Ratio"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const OS_Generator_PVWattsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Generator_PVWattsFields> OptionalOS_Generator_PVWattsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_GENERATOR_PVWATTS_FIELDENUMS_HXX
