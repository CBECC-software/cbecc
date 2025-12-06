/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_CONSTRUCTION_AIRBOUNDARY_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_CONSTRUCTION_AIRBOUNDARY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Construction_AirBoundaryFields
 *  \brief Enumeration of OS:Construction:AirBoundary's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Construction_AirBoundaryFields, )
#else
class OS_Construction_AirBoundaryFields: public ::EnumBase<OS_Construction_AirBoundaryFields> {
 public: 
  enum domain 
  {
Handle, Name, AirExchangeMethod, SimpleMixingAirChangesperHour, SimpleMixingScheduleName, SurfaceRenderingName,   };
  OS_Construction_AirBoundaryFields()
   : EnumBase<OS_Construction_AirBoundaryFields>(Handle) {} 
  OS_Construction_AirBoundaryFields(const std::string &t_name) 
   : EnumBase<OS_Construction_AirBoundaryFields>(t_name) {} 
  OS_Construction_AirBoundaryFields(int t_value) 
   : EnumBase<OS_Construction_AirBoundaryFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Construction_AirBoundaryFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Construction_AirBoundaryFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Construction_AirBoundaryFields>;
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
{ OS_Construction_AirBoundaryFields::Handle, "Handle", "Handle"},
{ OS_Construction_AirBoundaryFields::Name, "Name", "Name"},
{ OS_Construction_AirBoundaryFields::AirExchangeMethod, "AirExchangeMethod", "Air Exchange Method"},
{ OS_Construction_AirBoundaryFields::SimpleMixingAirChangesperHour, "SimpleMixingAirChangesperHour", "Simple Mixing Air Changes per Hour"},
{ OS_Construction_AirBoundaryFields::SimpleMixingScheduleName, "SimpleMixingScheduleName", "Simple Mixing Schedule Name"},
{ OS_Construction_AirBoundaryFields::SurfaceRenderingName, "SurfaceRenderingName", "Surface Rendering Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Construction_AirBoundaryFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Construction_AirBoundaryFields> OptionalOS_Construction_AirBoundaryFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_CONSTRUCTION_AIRBOUNDARY_FIELDENUMS_HXX
