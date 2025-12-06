/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_SURFACECONTROL_MOVABLEINSULATION_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SURFACECONTROL_MOVABLEINSULATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_SurfaceControl_MovableInsulationFields
 *  \brief Enumeration of OS:SurfaceControl:MovableInsulation's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_SurfaceControl_MovableInsulationFields, )
#else
class OS_SurfaceControl_MovableInsulationFields: public ::EnumBase<OS_SurfaceControl_MovableInsulationFields> {
 public: 
  enum domain 
  {
Handle, InsulationType, SurfaceName, MaterialName, ScheduleName,   };
  OS_SurfaceControl_MovableInsulationFields()
   : EnumBase<OS_SurfaceControl_MovableInsulationFields>(Handle) {} 
  OS_SurfaceControl_MovableInsulationFields(const std::string &t_name) 
   : EnumBase<OS_SurfaceControl_MovableInsulationFields>(t_name) {} 
  OS_SurfaceControl_MovableInsulationFields(int t_value) 
   : EnumBase<OS_SurfaceControl_MovableInsulationFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SurfaceControl_MovableInsulationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SurfaceControl_MovableInsulationFields>::integer_value()); }
   private:
    friend class EnumBase<OS_SurfaceControl_MovableInsulationFields>;
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
{ OS_SurfaceControl_MovableInsulationFields::Handle, "Handle", "Handle"},
{ OS_SurfaceControl_MovableInsulationFields::InsulationType, "InsulationType", "Insulation Type"},
{ OS_SurfaceControl_MovableInsulationFields::SurfaceName, "SurfaceName", "Surface Name"},
{ OS_SurfaceControl_MovableInsulationFields::MaterialName, "MaterialName", "Material Name"},
{ OS_SurfaceControl_MovableInsulationFields::ScheduleName, "ScheduleName", "Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SurfaceControl_MovableInsulationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SurfaceControl_MovableInsulationFields> OptionalOS_SurfaceControl_MovableInsulationFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SURFACECONTROL_MOVABLEINSULATION_FIELDENUMS_HXX
