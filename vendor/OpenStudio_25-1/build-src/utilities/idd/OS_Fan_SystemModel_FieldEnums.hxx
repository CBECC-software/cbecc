/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_FAN_SYSTEMMODEL_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_FAN_SYSTEMMODEL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Fan_SystemModelFields
 *  \brief Enumeration of OS:Fan:SystemModel's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Fan_SystemModelFields, )
#else
class OS_Fan_SystemModelFields: public ::EnumBase<OS_Fan_SystemModelFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, DesignMaximumAirFlowRate, SpeedControlMethod, ElectricPowerMinimumFlowRateFraction, DesignPressureRise, MotorEfficiency, MotorInAirStreamFraction, DesignElectricPowerConsumption, DesignPowerSizingMethod, ElectricPowerPerUnitFlowRate, ElectricPowerPerUnitFlowRatePerUnitPressure, FanTotalEfficiency, ElectricPowerFunctionofFlowFractionCurveName, NightVentilationModePressureRise, NightVentilationModeFlowFraction, MotorLossZoneName, MotorLossRadiativeFraction, EndUseSubcategory,   };
  OS_Fan_SystemModelFields()
   : EnumBase<OS_Fan_SystemModelFields>(Handle) {} 
  OS_Fan_SystemModelFields(const std::string &t_name) 
   : EnumBase<OS_Fan_SystemModelFields>(t_name) {} 
  OS_Fan_SystemModelFields(int t_value) 
   : EnumBase<OS_Fan_SystemModelFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Fan_SystemModelFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Fan_SystemModelFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Fan_SystemModelFields>;
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
{ OS_Fan_SystemModelFields::Handle, "Handle", "Handle"},
{ OS_Fan_SystemModelFields::Name, "Name", "Name"},
{ OS_Fan_SystemModelFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_Fan_SystemModelFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_Fan_SystemModelFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_Fan_SystemModelFields::DesignMaximumAirFlowRate, "DesignMaximumAirFlowRate", "Design Maximum Air Flow Rate"},
{ OS_Fan_SystemModelFields::SpeedControlMethod, "SpeedControlMethod", "Speed Control Method"},
{ OS_Fan_SystemModelFields::ElectricPowerMinimumFlowRateFraction, "ElectricPowerMinimumFlowRateFraction", "Electric Power Minimum Flow Rate Fraction"},
{ OS_Fan_SystemModelFields::DesignPressureRise, "DesignPressureRise", "Design Pressure Rise"},
{ OS_Fan_SystemModelFields::MotorEfficiency, "MotorEfficiency", "Motor Efficiency"},
{ OS_Fan_SystemModelFields::MotorInAirStreamFraction, "MotorInAirStreamFraction", "Motor In Air Stream Fraction"},
{ OS_Fan_SystemModelFields::DesignElectricPowerConsumption, "DesignElectricPowerConsumption", "Design Electric Power Consumption"},
{ OS_Fan_SystemModelFields::DesignPowerSizingMethod, "DesignPowerSizingMethod", "Design Power Sizing Method"},
{ OS_Fan_SystemModelFields::ElectricPowerPerUnitFlowRate, "ElectricPowerPerUnitFlowRate", "Electric Power Per Unit Flow Rate"},
{ OS_Fan_SystemModelFields::ElectricPowerPerUnitFlowRatePerUnitPressure, "ElectricPowerPerUnitFlowRatePerUnitPressure", "Electric Power Per Unit Flow Rate Per Unit Pressure"},
{ OS_Fan_SystemModelFields::FanTotalEfficiency, "FanTotalEfficiency", "Fan Total Efficiency"},
{ OS_Fan_SystemModelFields::ElectricPowerFunctionofFlowFractionCurveName, "ElectricPowerFunctionofFlowFractionCurveName", "Electric Power Function of Flow Fraction Curve Name"},
{ OS_Fan_SystemModelFields::NightVentilationModePressureRise, "NightVentilationModePressureRise", "Night Ventilation Mode Pressure Rise"},
{ OS_Fan_SystemModelFields::NightVentilationModeFlowFraction, "NightVentilationModeFlowFraction", "Night Ventilation Mode Flow Fraction"},
{ OS_Fan_SystemModelFields::MotorLossZoneName, "MotorLossZoneName", "Motor Loss Zone Name"},
{ OS_Fan_SystemModelFields::MotorLossRadiativeFraction, "MotorLossRadiativeFraction", "Motor Loss Radiative Fraction"},
{ OS_Fan_SystemModelFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Fan_SystemModelFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Fan_SystemModelFields> OptionalOS_Fan_SystemModelFields ;
#endif

/** \class OS_Fan_SystemModelExtensibleFields
 *  \brief Enumeration of OS:Fan:SystemModel's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Fan_SystemModelExtensibleFields, )
#else
class OS_Fan_SystemModelExtensibleFields: public ::EnumBase<OS_Fan_SystemModelExtensibleFields> {
 public: 
  enum domain 
  {
SpeedFlowFraction, SpeedElectricPowerFraction,   };
  OS_Fan_SystemModelExtensibleFields()
   : EnumBase<OS_Fan_SystemModelExtensibleFields>(SpeedFlowFraction) {} 
  OS_Fan_SystemModelExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Fan_SystemModelExtensibleFields>(t_name) {} 
  OS_Fan_SystemModelExtensibleFields(int t_value) 
   : EnumBase<OS_Fan_SystemModelExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Fan_SystemModelExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Fan_SystemModelExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Fan_SystemModelExtensibleFields>;
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
{ OS_Fan_SystemModelExtensibleFields::SpeedFlowFraction, "SpeedFlowFraction", "Speed Flow Fraction"},
{ OS_Fan_SystemModelExtensibleFields::SpeedElectricPowerFraction, "SpeedElectricPowerFraction", "Speed Electric Power Fraction"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Fan_SystemModelExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Fan_SystemModelExtensibleFields> OptionalOS_Fan_SystemModelExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_FAN_SYSTEMMODEL_FIELDENUMS_HXX
