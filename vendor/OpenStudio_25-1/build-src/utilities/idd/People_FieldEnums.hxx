/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_PEOPLE_FIELDENUMS_HXX
#define UTILITIES_IDD_PEOPLE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PeopleFields
 *  \brief Enumeration of People's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PeopleFields, )
#else
class PeopleFields: public ::EnumBase<PeopleFields> {
 public: 
  enum domain 
  {
Name, ZoneorZoneListorSpaceorSpaceListName, NumberofPeopleScheduleName, NumberofPeopleCalculationMethod, NumberofPeople, PeopleperFloorArea, FloorAreaperPerson, FractionRadiant, SensibleHeatFraction, ActivityLevelScheduleName, CarbonDioxideGenerationRate, EnableASHRAE55ComfortWarnings, MeanRadiantTemperatureCalculationType, SurfaceName_AngleFactorListName, WorkEfficiencyScheduleName, ClothingInsulationCalculationMethod, ClothingInsulationCalculationMethodScheduleName, ClothingInsulationScheduleName, AirVelocityScheduleName, ThermalComfortModel1Type, ThermalComfortModel2Type, ThermalComfortModel3Type, ThermalComfortModel4Type, ThermalComfortModel5Type, ThermalComfortModel6Type, ThermalComfortModel7Type, AnkleLevelAirVelocityScheduleName, ColdStressTemperatureThreshold, HeatStressTemperatureThreshold,   };
  PeopleFields()
   : EnumBase<PeopleFields>(Name) {} 
  PeopleFields(const std::string &t_name) 
   : EnumBase<PeopleFields>(t_name) {} 
  PeopleFields(int t_value) 
   : EnumBase<PeopleFields>(t_value) {} 
  static std::string enumName() 
  { return "PeopleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PeopleFields>::integer_value()); }
   private:
    friend class EnumBase<PeopleFields>;
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
{ PeopleFields::Name, "Name", "Name"},
{ PeopleFields::ZoneorZoneListorSpaceorSpaceListName, "ZoneorZoneListorSpaceorSpaceListName", "Zone or ZoneList or Space or SpaceList Name"},
{ PeopleFields::NumberofPeopleScheduleName, "NumberofPeopleScheduleName", "Number of People Schedule Name"},
{ PeopleFields::NumberofPeopleCalculationMethod, "NumberofPeopleCalculationMethod", "Number of People Calculation Method"},
{ PeopleFields::NumberofPeople, "NumberofPeople", "Number of People"},
{ PeopleFields::PeopleperFloorArea, "PeopleperFloorArea", "People per Floor Area"},
{ PeopleFields::FloorAreaperPerson, "FloorAreaperPerson", "Floor Area per Person"},
{ PeopleFields::FractionRadiant, "FractionRadiant", "Fraction Radiant"},
{ PeopleFields::SensibleHeatFraction, "SensibleHeatFraction", "Sensible Heat Fraction"},
{ PeopleFields::ActivityLevelScheduleName, "ActivityLevelScheduleName", "Activity Level Schedule Name"},
{ PeopleFields::CarbonDioxideGenerationRate, "CarbonDioxideGenerationRate", "Carbon Dioxide Generation Rate"},
{ PeopleFields::EnableASHRAE55ComfortWarnings, "EnableASHRAE55ComfortWarnings", "Enable ASHRAE 55 Comfort Warnings"},
{ PeopleFields::MeanRadiantTemperatureCalculationType, "MeanRadiantTemperatureCalculationType", "Mean Radiant Temperature Calculation Type"},
{ PeopleFields::SurfaceName_AngleFactorListName, "SurfaceName_AngleFactorListName", "Surface Name/Angle Factor List Name"},
{ PeopleFields::WorkEfficiencyScheduleName, "WorkEfficiencyScheduleName", "Work Efficiency Schedule Name"},
{ PeopleFields::ClothingInsulationCalculationMethod, "ClothingInsulationCalculationMethod", "Clothing Insulation Calculation Method"},
{ PeopleFields::ClothingInsulationCalculationMethodScheduleName, "ClothingInsulationCalculationMethodScheduleName", "Clothing Insulation Calculation Method Schedule Name"},
{ PeopleFields::ClothingInsulationScheduleName, "ClothingInsulationScheduleName", "Clothing Insulation Schedule Name"},
{ PeopleFields::AirVelocityScheduleName, "AirVelocityScheduleName", "Air Velocity Schedule Name"},
{ PeopleFields::ThermalComfortModel1Type, "ThermalComfortModel1Type", "Thermal Comfort Model 1 Type"},
{ PeopleFields::ThermalComfortModel2Type, "ThermalComfortModel2Type", "Thermal Comfort Model 2 Type"},
{ PeopleFields::ThermalComfortModel3Type, "ThermalComfortModel3Type", "Thermal Comfort Model 3 Type"},
{ PeopleFields::ThermalComfortModel4Type, "ThermalComfortModel4Type", "Thermal Comfort Model 4 Type"},
{ PeopleFields::ThermalComfortModel5Type, "ThermalComfortModel5Type", "Thermal Comfort Model 5 Type"},
{ PeopleFields::ThermalComfortModel6Type, "ThermalComfortModel6Type", "Thermal Comfort Model 6 Type"},
{ PeopleFields::ThermalComfortModel7Type, "ThermalComfortModel7Type", "Thermal Comfort Model 7 Type"},
{ PeopleFields::AnkleLevelAirVelocityScheduleName, "AnkleLevelAirVelocityScheduleName", "Ankle Level Air Velocity Schedule Name"},
{ PeopleFields::ColdStressTemperatureThreshold, "ColdStressTemperatureThreshold", "Cold Stress Temperature Threshold"},
{ PeopleFields::HeatStressTemperatureThreshold, "HeatStressTemperatureThreshold", "Heat Stress Temperature Threshold"},
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
  inline std::ostream &operator<<(std::ostream &os, const PeopleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PeopleFields> OptionalPeopleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PEOPLE_FIELDENUMS_HXX
