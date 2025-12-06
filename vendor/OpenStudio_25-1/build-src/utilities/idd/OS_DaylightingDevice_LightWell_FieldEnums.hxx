/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_DAYLIGHTINGDEVICE_LIGHTWELL_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_DAYLIGHTINGDEVICE_LIGHTWELL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_DaylightingDevice_LightWellFields
 *  \brief Enumeration of OS:DaylightingDevice:LightWell's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_DaylightingDevice_LightWellFields, )
#else
class OS_DaylightingDevice_LightWellFields: public ::EnumBase<OS_DaylightingDevice_LightWellFields> {
 public: 
  enum domain 
  {
Handle, Name, ExteriorWindowName, HeightofWell, PerimeterofBottomofWell, AreaofBottomofWell, VisibleReflectanceofWellWalls,   };
  OS_DaylightingDevice_LightWellFields()
   : EnumBase<OS_DaylightingDevice_LightWellFields>(Handle) {} 
  OS_DaylightingDevice_LightWellFields(const std::string &t_name) 
   : EnumBase<OS_DaylightingDevice_LightWellFields>(t_name) {} 
  OS_DaylightingDevice_LightWellFields(int t_value) 
   : EnumBase<OS_DaylightingDevice_LightWellFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_DaylightingDevice_LightWellFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_DaylightingDevice_LightWellFields>::integer_value()); }
   private:
    friend class EnumBase<OS_DaylightingDevice_LightWellFields>;
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
{ OS_DaylightingDevice_LightWellFields::Handle, "Handle", "Handle"},
{ OS_DaylightingDevice_LightWellFields::Name, "Name", "Name"},
{ OS_DaylightingDevice_LightWellFields::ExteriorWindowName, "ExteriorWindowName", "Exterior Window Name"},
{ OS_DaylightingDevice_LightWellFields::HeightofWell, "HeightofWell", "Height of Well"},
{ OS_DaylightingDevice_LightWellFields::PerimeterofBottomofWell, "PerimeterofBottomofWell", "Perimeter of Bottom of Well"},
{ OS_DaylightingDevice_LightWellFields::AreaofBottomofWell, "AreaofBottomofWell", "Area of Bottom of Well"},
{ OS_DaylightingDevice_LightWellFields::VisibleReflectanceofWellWalls, "VisibleReflectanceofWellWalls", "Visible Reflectance of Well Walls"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_DaylightingDevice_LightWellFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_DaylightingDevice_LightWellFields> OptionalOS_DaylightingDevice_LightWellFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_DAYLIGHTINGDEVICE_LIGHTWELL_FIELDENUMS_HXX
