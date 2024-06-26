/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
