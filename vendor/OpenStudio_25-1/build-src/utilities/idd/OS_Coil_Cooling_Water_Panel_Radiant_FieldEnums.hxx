/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_COIL_COOLING_WATER_PANEL_RADIANT_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_COOLING_WATER_PANEL_RADIANT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_Cooling_Water_Panel_RadiantFields
 *  \brief Enumeration of OS:Coil:Cooling:Water:Panel:Radiant's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_Cooling_Water_Panel_RadiantFields, )
#else
class OS_Coil_Cooling_Water_Panel_RadiantFields: public ::EnumBase<OS_Coil_Cooling_Water_Panel_RadiantFields> {
 public: 
  enum domain 
  {
Handle, Name, WaterInletNodeName, WaterOutletNodeName, RatedInletWaterTemperature, RatedInletSpaceTemperature, RatedWaterMassFlowRate, CoolingDesignCapacityMethod, CoolingDesignCapacity, CoolingDesignCapacityPerFloorArea, FractionofAutosizedCoolingDesignCapacity, MaximumChilledWaterFlowRate, ControlType, CoolingControlThrottlingRange, CoolingControlTemperatureScheduleName, CondensationControlType, CondensationControlDewpointOffset,   };
  OS_Coil_Cooling_Water_Panel_RadiantFields()
   : EnumBase<OS_Coil_Cooling_Water_Panel_RadiantFields>(Handle) {} 
  OS_Coil_Cooling_Water_Panel_RadiantFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Cooling_Water_Panel_RadiantFields>(t_name) {} 
  OS_Coil_Cooling_Water_Panel_RadiantFields(int t_value) 
   : EnumBase<OS_Coil_Cooling_Water_Panel_RadiantFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Cooling_Water_Panel_RadiantFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Cooling_Water_Panel_RadiantFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Coil_Cooling_Water_Panel_RadiantFields>;
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
{ OS_Coil_Cooling_Water_Panel_RadiantFields::Handle, "Handle", "Handle"},
{ OS_Coil_Cooling_Water_Panel_RadiantFields::Name, "Name", "Name"},
{ OS_Coil_Cooling_Water_Panel_RadiantFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ OS_Coil_Cooling_Water_Panel_RadiantFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ OS_Coil_Cooling_Water_Panel_RadiantFields::RatedInletWaterTemperature, "RatedInletWaterTemperature", "Rated Inlet Water Temperature"},
{ OS_Coil_Cooling_Water_Panel_RadiantFields::RatedInletSpaceTemperature, "RatedInletSpaceTemperature", "Rated Inlet Space Temperature"},
{ OS_Coil_Cooling_Water_Panel_RadiantFields::RatedWaterMassFlowRate, "RatedWaterMassFlowRate", "Rated Water Mass Flow Rate"},
{ OS_Coil_Cooling_Water_Panel_RadiantFields::CoolingDesignCapacityMethod, "CoolingDesignCapacityMethod", "Cooling Design Capacity Method"},
{ OS_Coil_Cooling_Water_Panel_RadiantFields::CoolingDesignCapacity, "CoolingDesignCapacity", "Cooling Design Capacity"},
{ OS_Coil_Cooling_Water_Panel_RadiantFields::CoolingDesignCapacityPerFloorArea, "CoolingDesignCapacityPerFloorArea", "Cooling Design Capacity Per Floor Area"},
{ OS_Coil_Cooling_Water_Panel_RadiantFields::FractionofAutosizedCoolingDesignCapacity, "FractionofAutosizedCoolingDesignCapacity", "Fraction of Autosized Cooling Design Capacity"},
{ OS_Coil_Cooling_Water_Panel_RadiantFields::MaximumChilledWaterFlowRate, "MaximumChilledWaterFlowRate", "Maximum Chilled Water Flow Rate"},
{ OS_Coil_Cooling_Water_Panel_RadiantFields::ControlType, "ControlType", "Control Type"},
{ OS_Coil_Cooling_Water_Panel_RadiantFields::CoolingControlThrottlingRange, "CoolingControlThrottlingRange", "Cooling Control Throttling Range"},
{ OS_Coil_Cooling_Water_Panel_RadiantFields::CoolingControlTemperatureScheduleName, "CoolingControlTemperatureScheduleName", "Cooling Control Temperature Schedule Name"},
{ OS_Coil_Cooling_Water_Panel_RadiantFields::CondensationControlType, "CondensationControlType", "Condensation Control Type"},
{ OS_Coil_Cooling_Water_Panel_RadiantFields::CondensationControlDewpointOffset, "CondensationControlDewpointOffset", "Condensation Control Dewpoint Offset"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Cooling_Water_Panel_RadiantFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Cooling_Water_Panel_RadiantFields> OptionalOS_Coil_Cooling_Water_Panel_RadiantFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_COOLING_WATER_PANEL_RADIANT_FIELDENUMS_HXX
