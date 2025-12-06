/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_ELECTRICLOADCENTER_INVERTER_FUNCTIONOFPOWER_FIELDENUMS_HXX
#define UTILITIES_IDD_ELECTRICLOADCENTER_INVERTER_FUNCTIONOFPOWER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ElectricLoadCenter_Inverter_FunctionOfPowerFields
 *  \brief Enumeration of ElectricLoadCenter:Inverter:FunctionOfPower's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ElectricLoadCenter_Inverter_FunctionOfPowerFields, )
#else
class ElectricLoadCenter_Inverter_FunctionOfPowerFields: public ::EnumBase<ElectricLoadCenter_Inverter_FunctionOfPowerFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, ZoneName, RadiativeFraction, EfficiencyFunctionofPowerCurveName, RatedMaximumContinuousInputPower, MinimumEfficiency, MaximumEfficiency, MinimumPowerOutput, MaximumPowerOutput, AncillaryPowerConsumedInStandby,   };
  ElectricLoadCenter_Inverter_FunctionOfPowerFields()
   : EnumBase<ElectricLoadCenter_Inverter_FunctionOfPowerFields>(Name) {} 
  ElectricLoadCenter_Inverter_FunctionOfPowerFields(const std::string &t_name) 
   : EnumBase<ElectricLoadCenter_Inverter_FunctionOfPowerFields>(t_name) {} 
  ElectricLoadCenter_Inverter_FunctionOfPowerFields(int t_value) 
   : EnumBase<ElectricLoadCenter_Inverter_FunctionOfPowerFields>(t_value) {} 
  static std::string enumName() 
  { return "ElectricLoadCenter_Inverter_FunctionOfPowerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ElectricLoadCenter_Inverter_FunctionOfPowerFields>::integer_value()); }
   private:
    friend class EnumBase<ElectricLoadCenter_Inverter_FunctionOfPowerFields>;
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
{ ElectricLoadCenter_Inverter_FunctionOfPowerFields::Name, "Name", "Name"},
{ ElectricLoadCenter_Inverter_FunctionOfPowerFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ElectricLoadCenter_Inverter_FunctionOfPowerFields::ZoneName, "ZoneName", "Zone Name"},
{ ElectricLoadCenter_Inverter_FunctionOfPowerFields::RadiativeFraction, "RadiativeFraction", "Radiative Fraction"},
{ ElectricLoadCenter_Inverter_FunctionOfPowerFields::EfficiencyFunctionofPowerCurveName, "EfficiencyFunctionofPowerCurveName", "Efficiency Function of Power Curve Name"},
{ ElectricLoadCenter_Inverter_FunctionOfPowerFields::RatedMaximumContinuousInputPower, "RatedMaximumContinuousInputPower", "Rated Maximum Continuous Input Power"},
{ ElectricLoadCenter_Inverter_FunctionOfPowerFields::MinimumEfficiency, "MinimumEfficiency", "Minimum Efficiency"},
{ ElectricLoadCenter_Inverter_FunctionOfPowerFields::MaximumEfficiency, "MaximumEfficiency", "Maximum Efficiency"},
{ ElectricLoadCenter_Inverter_FunctionOfPowerFields::MinimumPowerOutput, "MinimumPowerOutput", "Minimum Power Output"},
{ ElectricLoadCenter_Inverter_FunctionOfPowerFields::MaximumPowerOutput, "MaximumPowerOutput", "Maximum Power Output"},
{ ElectricLoadCenter_Inverter_FunctionOfPowerFields::AncillaryPowerConsumedInStandby, "AncillaryPowerConsumedInStandby", "Ancillary Power Consumed In Standby"},
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
  inline std::ostream &operator<<(std::ostream &os, const ElectricLoadCenter_Inverter_FunctionOfPowerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ElectricLoadCenter_Inverter_FunctionOfPowerFields> OptionalElectricLoadCenter_Inverter_FunctionOfPowerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ELECTRICLOADCENTER_INVERTER_FUNCTIONOFPOWER_FIELDENUMS_HXX
