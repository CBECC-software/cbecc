/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_LIGHTS_FIELDENUMS_HXX
#define UTILITIES_IDD_LIGHTS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class LightsFields
 *  \brief Enumeration of Lights's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(LightsFields, )
#else
class LightsFields: public ::EnumBase<LightsFields> {
 public: 
  enum domain 
  {
Name, ZoneorZoneListorSpaceorSpaceListName, ScheduleName, DesignLevelCalculationMethod, LightingLevel, WattsperFloorArea, WattsperPerson, ReturnAirFraction, FractionRadiant, FractionVisible, FractionReplaceable, EndUseSubcategory, ReturnAirFractionCalculatedfromPlenumTemperature, ReturnAirFractionFunctionofPlenumTemperatureCoefficient1, ReturnAirFractionFunctionofPlenumTemperatureCoefficient2, ReturnAirHeatGainNodeName, ExhaustAirHeatGainNodeName,   };
  LightsFields()
   : EnumBase<LightsFields>(Name) {} 
  LightsFields(const std::string &t_name) 
   : EnumBase<LightsFields>(t_name) {} 
  LightsFields(int t_value) 
   : EnumBase<LightsFields>(t_value) {} 
  static std::string enumName() 
  { return "LightsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<LightsFields>::integer_value()); }
   private:
    friend class EnumBase<LightsFields>;
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
{ LightsFields::Name, "Name", "Name"},
{ LightsFields::ZoneorZoneListorSpaceorSpaceListName, "ZoneorZoneListorSpaceorSpaceListName", "Zone or ZoneList or Space or SpaceList Name"},
{ LightsFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ LightsFields::DesignLevelCalculationMethod, "DesignLevelCalculationMethod", "Design Level Calculation Method"},
{ LightsFields::LightingLevel, "LightingLevel", "Lighting Level"},
{ LightsFields::WattsperFloorArea, "WattsperFloorArea", "Watts per Floor Area"},
{ LightsFields::WattsperPerson, "WattsperPerson", "Watts per Person"},
{ LightsFields::ReturnAirFraction, "ReturnAirFraction", "Return Air Fraction"},
{ LightsFields::FractionRadiant, "FractionRadiant", "Fraction Radiant"},
{ LightsFields::FractionVisible, "FractionVisible", "Fraction Visible"},
{ LightsFields::FractionReplaceable, "FractionReplaceable", "Fraction Replaceable"},
{ LightsFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ LightsFields::ReturnAirFractionCalculatedfromPlenumTemperature, "ReturnAirFractionCalculatedfromPlenumTemperature", "Return Air Fraction Calculated from Plenum Temperature"},
{ LightsFields::ReturnAirFractionFunctionofPlenumTemperatureCoefficient1, "ReturnAirFractionFunctionofPlenumTemperatureCoefficient1", "Return Air Fraction Function of Plenum Temperature Coefficient 1"},
{ LightsFields::ReturnAirFractionFunctionofPlenumTemperatureCoefficient2, "ReturnAirFractionFunctionofPlenumTemperatureCoefficient2", "Return Air Fraction Function of Plenum Temperature Coefficient 2"},
{ LightsFields::ReturnAirHeatGainNodeName, "ReturnAirHeatGainNodeName", "Return Air Heat Gain Node Name"},
{ LightsFields::ExhaustAirHeatGainNodeName, "ExhaustAirHeatGainNodeName", "Exhaust Air Heat Gain Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const LightsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<LightsFields> OptionalLightsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_LIGHTS_FIELDENUMS_HXX
