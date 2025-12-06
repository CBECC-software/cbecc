/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_COIL_COOLING_WATER_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_COOLING_WATER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Cooling_WaterFields
 *  \brief Enumeration of Coil:Cooling:Water's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Cooling_WaterFields, )
#else
class Coil_Cooling_WaterFields: public ::EnumBase<Coil_Cooling_WaterFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, DesignWaterFlowRate, DesignAirFlowRate, DesignInletWaterTemperature, DesignInletAirTemperature, DesignOutletAirTemperature, DesignInletAirHumidityRatio, DesignOutletAirHumidityRatio, WaterInletNodeName, WaterOutletNodeName, AirInletNodeName, AirOutletNodeName, TypeofAnalysis, HeatExchangerConfiguration, CondensateCollectionWaterStorageTankName, DesignWaterTemperatureDifference,   };
  Coil_Cooling_WaterFields()
   : EnumBase<Coil_Cooling_WaterFields>(Name) {} 
  Coil_Cooling_WaterFields(const std::string &t_name) 
   : EnumBase<Coil_Cooling_WaterFields>(t_name) {} 
  Coil_Cooling_WaterFields(int t_value) 
   : EnumBase<Coil_Cooling_WaterFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Cooling_WaterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Cooling_WaterFields>::integer_value()); }
   private:
    friend class EnumBase<Coil_Cooling_WaterFields>;
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
{ Coil_Cooling_WaterFields::Name, "Name", "Name"},
{ Coil_Cooling_WaterFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Coil_Cooling_WaterFields::DesignWaterFlowRate, "DesignWaterFlowRate", "Design Water Flow Rate"},
{ Coil_Cooling_WaterFields::DesignAirFlowRate, "DesignAirFlowRate", "Design Air Flow Rate"},
{ Coil_Cooling_WaterFields::DesignInletWaterTemperature, "DesignInletWaterTemperature", "Design Inlet Water Temperature"},
{ Coil_Cooling_WaterFields::DesignInletAirTemperature, "DesignInletAirTemperature", "Design Inlet Air Temperature"},
{ Coil_Cooling_WaterFields::DesignOutletAirTemperature, "DesignOutletAirTemperature", "Design Outlet Air Temperature"},
{ Coil_Cooling_WaterFields::DesignInletAirHumidityRatio, "DesignInletAirHumidityRatio", "Design Inlet Air Humidity Ratio"},
{ Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio, "DesignOutletAirHumidityRatio", "Design Outlet Air Humidity Ratio"},
{ Coil_Cooling_WaterFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ Coil_Cooling_WaterFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ Coil_Cooling_WaterFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Coil_Cooling_WaterFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Coil_Cooling_WaterFields::TypeofAnalysis, "TypeofAnalysis", "Type of Analysis"},
{ Coil_Cooling_WaterFields::HeatExchangerConfiguration, "HeatExchangerConfiguration", "Heat Exchanger Configuration"},
{ Coil_Cooling_WaterFields::CondensateCollectionWaterStorageTankName, "CondensateCollectionWaterStorageTankName", "Condensate Collection Water Storage Tank Name"},
{ Coil_Cooling_WaterFields::DesignWaterTemperatureDifference, "DesignWaterTemperatureDifference", "Design Water Temperature Difference"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Cooling_WaterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Cooling_WaterFields> OptionalCoil_Cooling_WaterFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_COOLING_WATER_FIELDENUMS_HXX
