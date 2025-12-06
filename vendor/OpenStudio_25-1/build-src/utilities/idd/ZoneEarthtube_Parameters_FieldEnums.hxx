/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_ZONEEARTHTUBE_PARAMETERS_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEEARTHTUBE_PARAMETERS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneEarthtube_ParametersFields
 *  \brief Enumeration of ZoneEarthtube:Parameters's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneEarthtube_ParametersFields, )
#else
class ZoneEarthtube_ParametersFields: public ::EnumBase<ZoneEarthtube_ParametersFields> {
 public: 
  enum domain 
  {
EarthTubeModelParametersName, NodesAboveEarthTube, NodesBelowEarthTube, EarthTubeDimensionlessBoundaryAbove, EarthTubeDimensionlessBoundaryBelow, EarthTubeSolutionSpaceWidth,   };
  ZoneEarthtube_ParametersFields()
   : EnumBase<ZoneEarthtube_ParametersFields>(EarthTubeModelParametersName) {} 
  ZoneEarthtube_ParametersFields(const std::string &t_name) 
   : EnumBase<ZoneEarthtube_ParametersFields>(t_name) {} 
  ZoneEarthtube_ParametersFields(int t_value) 
   : EnumBase<ZoneEarthtube_ParametersFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneEarthtube_ParametersFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneEarthtube_ParametersFields>::integer_value()); }
   private:
    friend class EnumBase<ZoneEarthtube_ParametersFields>;
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
{ ZoneEarthtube_ParametersFields::EarthTubeModelParametersName, "EarthTubeModelParametersName", "Earth Tube Model Parameters Name"},
{ ZoneEarthtube_ParametersFields::NodesAboveEarthTube, "NodesAboveEarthTube", "Nodes Above Earth Tube"},
{ ZoneEarthtube_ParametersFields::NodesBelowEarthTube, "NodesBelowEarthTube", "Nodes Below Earth Tube"},
{ ZoneEarthtube_ParametersFields::EarthTubeDimensionlessBoundaryAbove, "EarthTubeDimensionlessBoundaryAbove", "Earth Tube Dimensionless Boundary Above"},
{ ZoneEarthtube_ParametersFields::EarthTubeDimensionlessBoundaryBelow, "EarthTubeDimensionlessBoundaryBelow", "Earth Tube Dimensionless Boundary Below"},
{ ZoneEarthtube_ParametersFields::EarthTubeSolutionSpaceWidth, "EarthTubeSolutionSpaceWidth", "Earth Tube Solution Space Width"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneEarthtube_ParametersFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneEarthtube_ParametersFields> OptionalZoneEarthtube_ParametersFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEEARTHTUBE_PARAMETERS_FIELDENUMS_HXX
