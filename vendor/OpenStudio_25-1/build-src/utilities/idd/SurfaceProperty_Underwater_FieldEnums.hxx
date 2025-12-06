/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_SURFACEPROPERTY_UNDERWATER_FIELDENUMS_HXX
#define UTILITIES_IDD_SURFACEPROPERTY_UNDERWATER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SurfaceProperty_UnderwaterFields
 *  \brief Enumeration of SurfaceProperty:Underwater's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SurfaceProperty_UnderwaterFields, )
#else
class SurfaceProperty_UnderwaterFields: public ::EnumBase<SurfaceProperty_UnderwaterFields> {
 public: 
  enum domain 
  {
Name, DistancefromSurfaceCentroidtoLeadingEdgeofBoundaryLayer, FreeStreamWaterTemperatureSchedule, FreeStreamWaterVelocitySchedule,   };
  SurfaceProperty_UnderwaterFields()
   : EnumBase<SurfaceProperty_UnderwaterFields>(Name) {} 
  SurfaceProperty_UnderwaterFields(const std::string &t_name) 
   : EnumBase<SurfaceProperty_UnderwaterFields>(t_name) {} 
  SurfaceProperty_UnderwaterFields(int t_value) 
   : EnumBase<SurfaceProperty_UnderwaterFields>(t_value) {} 
  static std::string enumName() 
  { return "SurfaceProperty_UnderwaterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SurfaceProperty_UnderwaterFields>::integer_value()); }
   private:
    friend class EnumBase<SurfaceProperty_UnderwaterFields>;
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
{ SurfaceProperty_UnderwaterFields::Name, "Name", "Name"},
{ SurfaceProperty_UnderwaterFields::DistancefromSurfaceCentroidtoLeadingEdgeofBoundaryLayer, "DistancefromSurfaceCentroidtoLeadingEdgeofBoundaryLayer", "Distance from Surface Centroid to Leading Edge of Boundary Layer"},
{ SurfaceProperty_UnderwaterFields::FreeStreamWaterTemperatureSchedule, "FreeStreamWaterTemperatureSchedule", "Free Stream Water Temperature Schedule"},
{ SurfaceProperty_UnderwaterFields::FreeStreamWaterVelocitySchedule, "FreeStreamWaterVelocitySchedule", "Free Stream Water Velocity Schedule"},
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
  inline std::ostream &operator<<(std::ostream &os, const SurfaceProperty_UnderwaterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SurfaceProperty_UnderwaterFields> OptionalSurfaceProperty_UnderwaterFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SURFACEPROPERTY_UNDERWATER_FIELDENUMS_HXX
