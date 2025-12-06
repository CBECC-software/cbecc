/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_CHILLER_ELECTRIC_ASHRAE205_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_CHILLER_ELECTRIC_ASHRAE205_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Chiller_Electric_ASHRAE205Fields
 *  \brief Enumeration of OS:Chiller:Electric:ASHRAE205's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Chiller_Electric_ASHRAE205Fields, )
#else
class OS_Chiller_Electric_ASHRAE205Fields: public ::EnumBase<OS_Chiller_Electric_ASHRAE205Fields> {
 public: 
  enum domain 
  {
Handle, Name, RepresentationFileName, PerformanceInterpolationMethod, RatedCapacity, SizingFactor, AmbientTemperatureIndicator, AmbientTemperatureScheduleName, AmbientTemperatureZoneName, AmbientTemperatureOutdoorAirNodeName, ChilledWaterInletNodeName, ChilledWaterOutletNodeName, ChilledWaterMaximumRequestedFlowRate, CondenserInletNodeName, CondenserOutletNodeName, CondenserMaximumRequestedFlowRate, ChillerFlowMode, OilCoolerInletNodeName, OilCoolerOutletNodeName, OilCoolerDesignFlowRate, AuxiliaryInletNodeName, AuxiliaryOutletNodeName, AuxiliaryCoolingDesignFlowRate, HeatRecoveryInletNodeName, HeatRecoveryOutletNodeName, EndUseSubcategory,   };
  OS_Chiller_Electric_ASHRAE205Fields()
   : EnumBase<OS_Chiller_Electric_ASHRAE205Fields>(Handle) {} 
  OS_Chiller_Electric_ASHRAE205Fields(const std::string &t_name) 
   : EnumBase<OS_Chiller_Electric_ASHRAE205Fields>(t_name) {} 
  OS_Chiller_Electric_ASHRAE205Fields(int t_value) 
   : EnumBase<OS_Chiller_Electric_ASHRAE205Fields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Chiller_Electric_ASHRAE205Fields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Chiller_Electric_ASHRAE205Fields>::integer_value()); }
   private:
    friend class EnumBase<OS_Chiller_Electric_ASHRAE205Fields>;
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
{ OS_Chiller_Electric_ASHRAE205Fields::Handle, "Handle", "Handle"},
{ OS_Chiller_Electric_ASHRAE205Fields::Name, "Name", "Name"},
{ OS_Chiller_Electric_ASHRAE205Fields::RepresentationFileName, "RepresentationFileName", "Representation File Name"},
{ OS_Chiller_Electric_ASHRAE205Fields::PerformanceInterpolationMethod, "PerformanceInterpolationMethod", "Performance Interpolation Method"},
{ OS_Chiller_Electric_ASHRAE205Fields::RatedCapacity, "RatedCapacity", "Rated Capacity"},
{ OS_Chiller_Electric_ASHRAE205Fields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ OS_Chiller_Electric_ASHRAE205Fields::AmbientTemperatureIndicator, "AmbientTemperatureIndicator", "Ambient Temperature Indicator"},
{ OS_Chiller_Electric_ASHRAE205Fields::AmbientTemperatureScheduleName, "AmbientTemperatureScheduleName", "Ambient Temperature Schedule Name"},
{ OS_Chiller_Electric_ASHRAE205Fields::AmbientTemperatureZoneName, "AmbientTemperatureZoneName", "Ambient Temperature Zone Name"},
{ OS_Chiller_Electric_ASHRAE205Fields::AmbientTemperatureOutdoorAirNodeName, "AmbientTemperatureOutdoorAirNodeName", "Ambient Temperature Outdoor Air Node Name"},
{ OS_Chiller_Electric_ASHRAE205Fields::ChilledWaterInletNodeName, "ChilledWaterInletNodeName", "Chilled Water Inlet Node Name"},
{ OS_Chiller_Electric_ASHRAE205Fields::ChilledWaterOutletNodeName, "ChilledWaterOutletNodeName", "Chilled Water Outlet Node Name"},
{ OS_Chiller_Electric_ASHRAE205Fields::ChilledWaterMaximumRequestedFlowRate, "ChilledWaterMaximumRequestedFlowRate", "Chilled Water Maximum Requested Flow Rate"},
{ OS_Chiller_Electric_ASHRAE205Fields::CondenserInletNodeName, "CondenserInletNodeName", "Condenser Inlet Node Name"},
{ OS_Chiller_Electric_ASHRAE205Fields::CondenserOutletNodeName, "CondenserOutletNodeName", "Condenser Outlet Node Name"},
{ OS_Chiller_Electric_ASHRAE205Fields::CondenserMaximumRequestedFlowRate, "CondenserMaximumRequestedFlowRate", "Condenser Maximum Requested Flow Rate"},
{ OS_Chiller_Electric_ASHRAE205Fields::ChillerFlowMode, "ChillerFlowMode", "Chiller Flow Mode"},
{ OS_Chiller_Electric_ASHRAE205Fields::OilCoolerInletNodeName, "OilCoolerInletNodeName", "Oil Cooler Inlet Node Name"},
{ OS_Chiller_Electric_ASHRAE205Fields::OilCoolerOutletNodeName, "OilCoolerOutletNodeName", "Oil Cooler Outlet Node Name"},
{ OS_Chiller_Electric_ASHRAE205Fields::OilCoolerDesignFlowRate, "OilCoolerDesignFlowRate", "Oil Cooler Design Flow Rate"},
{ OS_Chiller_Electric_ASHRAE205Fields::AuxiliaryInletNodeName, "AuxiliaryInletNodeName", "Auxiliary Inlet Node Name"},
{ OS_Chiller_Electric_ASHRAE205Fields::AuxiliaryOutletNodeName, "AuxiliaryOutletNodeName", "Auxiliary Outlet Node Name"},
{ OS_Chiller_Electric_ASHRAE205Fields::AuxiliaryCoolingDesignFlowRate, "AuxiliaryCoolingDesignFlowRate", "Auxiliary Cooling Design Flow Rate"},
{ OS_Chiller_Electric_ASHRAE205Fields::HeatRecoveryInletNodeName, "HeatRecoveryInletNodeName", "Heat Recovery Inlet Node Name"},
{ OS_Chiller_Electric_ASHRAE205Fields::HeatRecoveryOutletNodeName, "HeatRecoveryOutletNodeName", "Heat Recovery Outlet Node Name"},
{ OS_Chiller_Electric_ASHRAE205Fields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Chiller_Electric_ASHRAE205Fields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Chiller_Electric_ASHRAE205Fields> OptionalOS_Chiller_Electric_ASHRAE205Fields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_CHILLER_ELECTRIC_ASHRAE205_FIELDENUMS_HXX
