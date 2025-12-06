/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_GENERATOR_WINDTURBINE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_GENERATOR_WINDTURBINE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Generator_WindTurbineFields
 *  \brief Enumeration of OS:Generator:WindTurbine's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Generator_WindTurbineFields, )
#else
class OS_Generator_WindTurbineFields: public ::EnumBase<OS_Generator_WindTurbineFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, RotorType, PowerControl, RatedRotorSpeed, RotorDiameter, OverallHeight, NumberofBlades, RatedPower, RatedWindSpeed, CutInWindSpeed, CutOutWindSpeed, FractionsystemEfficiency, MaximumTipSpeedRatio, MaximumPowerCoefficient, AnnualLocalAverageWindSpeed, HeightforLocalAverageWindSpeed, BladeChordArea, BladeDragCoefficient, BladeLiftCoefficient, PowerCoefficientC1, PowerCoefficientC2, PowerCoefficientC3, PowerCoefficientC4, PowerCoefficientC5, PowerCoefficientC6,   };
  OS_Generator_WindTurbineFields()
   : EnumBase<OS_Generator_WindTurbineFields>(Handle) {} 
  OS_Generator_WindTurbineFields(const std::string &t_name) 
   : EnumBase<OS_Generator_WindTurbineFields>(t_name) {} 
  OS_Generator_WindTurbineFields(int t_value) 
   : EnumBase<OS_Generator_WindTurbineFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Generator_WindTurbineFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Generator_WindTurbineFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Generator_WindTurbineFields>;
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
{ OS_Generator_WindTurbineFields::Handle, "Handle", "Handle"},
{ OS_Generator_WindTurbineFields::Name, "Name", "Name"},
{ OS_Generator_WindTurbineFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_Generator_WindTurbineFields::RotorType, "RotorType", "Rotor Type"},
{ OS_Generator_WindTurbineFields::PowerControl, "PowerControl", "Power Control"},
{ OS_Generator_WindTurbineFields::RatedRotorSpeed, "RatedRotorSpeed", "Rated Rotor Speed"},
{ OS_Generator_WindTurbineFields::RotorDiameter, "RotorDiameter", "Rotor Diameter"},
{ OS_Generator_WindTurbineFields::OverallHeight, "OverallHeight", "Overall Height"},
{ OS_Generator_WindTurbineFields::NumberofBlades, "NumberofBlades", "Number of Blades"},
{ OS_Generator_WindTurbineFields::RatedPower, "RatedPower", "Rated Power"},
{ OS_Generator_WindTurbineFields::RatedWindSpeed, "RatedWindSpeed", "Rated Wind Speed"},
{ OS_Generator_WindTurbineFields::CutInWindSpeed, "CutInWindSpeed", "Cut In Wind Speed"},
{ OS_Generator_WindTurbineFields::CutOutWindSpeed, "CutOutWindSpeed", "Cut Out Wind Speed"},
{ OS_Generator_WindTurbineFields::FractionsystemEfficiency, "FractionsystemEfficiency", "Fraction system Efficiency"},
{ OS_Generator_WindTurbineFields::MaximumTipSpeedRatio, "MaximumTipSpeedRatio", "Maximum Tip Speed Ratio"},
{ OS_Generator_WindTurbineFields::MaximumPowerCoefficient, "MaximumPowerCoefficient", "Maximum Power Coefficient"},
{ OS_Generator_WindTurbineFields::AnnualLocalAverageWindSpeed, "AnnualLocalAverageWindSpeed", "Annual Local Average Wind Speed"},
{ OS_Generator_WindTurbineFields::HeightforLocalAverageWindSpeed, "HeightforLocalAverageWindSpeed", "Height for Local Average Wind Speed"},
{ OS_Generator_WindTurbineFields::BladeChordArea, "BladeChordArea", "Blade Chord Area"},
{ OS_Generator_WindTurbineFields::BladeDragCoefficient, "BladeDragCoefficient", "Blade Drag Coefficient"},
{ OS_Generator_WindTurbineFields::BladeLiftCoefficient, "BladeLiftCoefficient", "Blade Lift Coefficient"},
{ OS_Generator_WindTurbineFields::PowerCoefficientC1, "PowerCoefficientC1", "Power Coefficient C1"},
{ OS_Generator_WindTurbineFields::PowerCoefficientC2, "PowerCoefficientC2", "Power Coefficient C2"},
{ OS_Generator_WindTurbineFields::PowerCoefficientC3, "PowerCoefficientC3", "Power Coefficient C3"},
{ OS_Generator_WindTurbineFields::PowerCoefficientC4, "PowerCoefficientC4", "Power Coefficient C4"},
{ OS_Generator_WindTurbineFields::PowerCoefficientC5, "PowerCoefficientC5", "Power Coefficient C5"},
{ OS_Generator_WindTurbineFields::PowerCoefficientC6, "PowerCoefficientC6", "Power Coefficient C6"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Generator_WindTurbineFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Generator_WindTurbineFields> OptionalOS_Generator_WindTurbineFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_GENERATOR_WINDTURBINE_FIELDENUMS_HXX
