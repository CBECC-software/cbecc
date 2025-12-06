/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_ZONEHVAC_BASEBOARD_RADIANTCONVECTIVE_WATER_DESIGN_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_BASEBOARD_RADIANTCONVECTIVE_WATER_DESIGN_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields
 *  \brief Enumeration of ZoneHVAC:Baseboard:RadiantConvective:Water:Design's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields, )
#else
class ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields: public ::EnumBase<ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields> {
 public: 
  enum domain 
  {
Name, HeatingDesignCapacityMethod, HeatingDesignCapacityPerFloorArea, FractionofAutosizedHeatingDesignCapacity, ConvergenceTolerance, FractionRadiant, FractionofRadiantEnergyIncidentonPeople,   };
  ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields()
   : EnumBase<ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields>(Name) {} 
  ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields>(t_name) {} 
  ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields(int t_value) 
   : EnumBase<ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields>::integer_value()); }
   private:
    friend class EnumBase<ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields>;
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
{ ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::Name, "Name", "Name"},
{ ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::HeatingDesignCapacityMethod, "HeatingDesignCapacityMethod", "Heating Design Capacity Method"},
{ ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::HeatingDesignCapacityPerFloorArea, "HeatingDesignCapacityPerFloorArea", "Heating Design Capacity Per Floor Area"},
{ ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::FractionofAutosizedHeatingDesignCapacity, "FractionofAutosizedHeatingDesignCapacity", "Fraction of Autosized Heating Design Capacity"},
{ ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::ConvergenceTolerance, "ConvergenceTolerance", "Convergence Tolerance"},
{ ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::FractionRadiant, "FractionRadiant", "Fraction Radiant"},
{ ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::FractionofRadiantEnergyIncidentonPeople, "FractionofRadiantEnergyIncidentonPeople", "Fraction of Radiant Energy Incident on People"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields> OptionalZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_BASEBOARD_RADIANTCONVECTIVE_WATER_DESIGN_FIELDENUMS_HXX
