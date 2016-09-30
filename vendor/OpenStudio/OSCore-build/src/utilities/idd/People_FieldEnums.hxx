/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

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
Name, ZoneorZoneListName, NumberofPeopleScheduleName, NumberofPeopleCalculationMethod, NumberofPeople, PeopleperZoneFloorArea, ZoneFloorAreaperPerson, FractionRadiant, SensibleHeatFraction, ActivityLevelScheduleName, CarbonDioxideGenerationRate, EnableASHRAE55ComfortWarnings, MeanRadiantTemperatureCalculationType, SurfaceName_AngleFactorListName, WorkEfficiencyScheduleName, ClothingInsulationCalculationMethod, ClothingInsulationCalculationMethodScheduleName, ClothingInsulationScheduleName, AirVelocityScheduleName,   };
  PeopleFields()
   : EnumBase<PeopleFields>(Name) {} 
  PeopleFields(const std::string &t_name) 
   : EnumBase<PeopleFields>(t_name) {} 
  PeopleFields(int t_value) 
   : EnumBase<PeopleFields>(t_value) {} 
  static std::string enumName() 
  { return "PeopleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PeopleFields>::value()); }
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
{ PeopleFields::ZoneorZoneListName, "ZoneorZoneListName", "Zone or ZoneList Name"},
{ PeopleFields::NumberofPeopleScheduleName, "NumberofPeopleScheduleName", "Number of People Schedule Name"},
{ PeopleFields::NumberofPeopleCalculationMethod, "NumberofPeopleCalculationMethod", "Number of People Calculation Method"},
{ PeopleFields::NumberofPeople, "NumberofPeople", "Number of People"},
{ PeopleFields::PeopleperZoneFloorArea, "PeopleperZoneFloorArea", "People per Zone Floor Area"},
{ PeopleFields::ZoneFloorAreaperPerson, "ZoneFloorAreaperPerson", "Zone Floor Area per Person"},
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

/** \class PeopleExtensibleFields
 *  \brief Enumeration of People's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(PeopleExtensibleFields, )
#else
class PeopleExtensibleFields: public ::EnumBase<PeopleExtensibleFields> {
 public: 
  enum domain 
  {
ThermalComfortModelType,   };
  PeopleExtensibleFields()
   : EnumBase<PeopleExtensibleFields>(ThermalComfortModelType) {} 
  PeopleExtensibleFields(const std::string &t_name) 
   : EnumBase<PeopleExtensibleFields>(t_name) {} 
  PeopleExtensibleFields(int t_value) 
   : EnumBase<PeopleExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "PeopleExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PeopleExtensibleFields>::value()); }
   private:
    friend class EnumBase<PeopleExtensibleFields>;
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
{ PeopleExtensibleFields::ThermalComfortModelType, "ThermalComfortModelType", "Thermal Comfort Model Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const PeopleExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PeopleExtensibleFields> OptionalPeopleExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PEOPLE_FIELDENUMS_HXX
