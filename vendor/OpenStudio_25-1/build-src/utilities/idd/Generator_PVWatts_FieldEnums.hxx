/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_GENERATOR_PVWATTS_FIELDENUMS_HXX
#define UTILITIES_IDD_GENERATOR_PVWATTS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Generator_PVWattsFields
 *  \brief Enumeration of Generator:PVWatts's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Generator_PVWattsFields, )
#else
class Generator_PVWattsFields: public ::EnumBase<Generator_PVWattsFields> {
 public: 
  enum domain 
  {
Name, PVWattsVersion, DCSystemCapacity, ModuleType, ArrayType, SystemLosses, ArrayGeometryType, TiltAngle, AzimuthAngle, SurfaceName, GroundCoverageRatio,   };
  Generator_PVWattsFields()
   : EnumBase<Generator_PVWattsFields>(Name) {} 
  Generator_PVWattsFields(const std::string &t_name) 
   : EnumBase<Generator_PVWattsFields>(t_name) {} 
  Generator_PVWattsFields(int t_value) 
   : EnumBase<Generator_PVWattsFields>(t_value) {} 
  static std::string enumName() 
  { return "Generator_PVWattsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Generator_PVWattsFields>::integer_value()); }
   private:
    friend class EnumBase<Generator_PVWattsFields>;
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
{ Generator_PVWattsFields::Name, "Name", "Name"},
{ Generator_PVWattsFields::PVWattsVersion, "PVWattsVersion", "PVWatts Version"},
{ Generator_PVWattsFields::DCSystemCapacity, "DCSystemCapacity", "DC System Capacity"},
{ Generator_PVWattsFields::ModuleType, "ModuleType", "Module Type"},
{ Generator_PVWattsFields::ArrayType, "ArrayType", "Array Type"},
{ Generator_PVWattsFields::SystemLosses, "SystemLosses", "System Losses"},
{ Generator_PVWattsFields::ArrayGeometryType, "ArrayGeometryType", "Array Geometry Type"},
{ Generator_PVWattsFields::TiltAngle, "TiltAngle", "Tilt Angle"},
{ Generator_PVWattsFields::AzimuthAngle, "AzimuthAngle", "Azimuth Angle"},
{ Generator_PVWattsFields::SurfaceName, "SurfaceName", "Surface Name"},
{ Generator_PVWattsFields::GroundCoverageRatio, "GroundCoverageRatio", "Ground Coverage Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const Generator_PVWattsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Generator_PVWattsFields> OptionalGenerator_PVWattsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GENERATOR_PVWATTS_FIELDENUMS_HXX
