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

#ifndef UTILITIES_IDD_OS_PEOPLE_DEFINITION_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_PEOPLE_DEFINITION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_People_DefinitionFields
 *  \brief Enumeration of OS:People:Definition's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_People_DefinitionFields, )
#else
class OS_People_DefinitionFields: public ::EnumBase<OS_People_DefinitionFields> {
 public: 
  enum domain 
  {
Handle, Name, NumberofPeopleCalculationMethod, NumberofPeople, PeopleperSpaceFloorArea, SpaceFloorAreaperPerson, FractionRadiant, SensibleHeatFraction, CarbonDioxideGenerationRate, EnableASHRAE55ComfortWarnings, MeanRadiantTemperatureCalculationType,   };
  OS_People_DefinitionFields()
   : EnumBase<OS_People_DefinitionFields>(Handle) {} 
  OS_People_DefinitionFields(const std::string &t_name) 
   : EnumBase<OS_People_DefinitionFields>(t_name) {} 
  OS_People_DefinitionFields(int t_value) 
   : EnumBase<OS_People_DefinitionFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_People_DefinitionFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_People_DefinitionFields>::value()); }
   private:
    friend class EnumBase<OS_People_DefinitionFields>;
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
{ OS_People_DefinitionFields::Handle, "Handle", "Handle"},
{ OS_People_DefinitionFields::Name, "Name", "Name"},
{ OS_People_DefinitionFields::NumberofPeopleCalculationMethod, "NumberofPeopleCalculationMethod", "Number of People Calculation Method"},
{ OS_People_DefinitionFields::NumberofPeople, "NumberofPeople", "Number of People"},
{ OS_People_DefinitionFields::PeopleperSpaceFloorArea, "PeopleperSpaceFloorArea", "People per Space Floor Area"},
{ OS_People_DefinitionFields::SpaceFloorAreaperPerson, "SpaceFloorAreaperPerson", "Space Floor Area per Person"},
{ OS_People_DefinitionFields::FractionRadiant, "FractionRadiant", "Fraction Radiant"},
{ OS_People_DefinitionFields::SensibleHeatFraction, "SensibleHeatFraction", "Sensible Heat Fraction"},
{ OS_People_DefinitionFields::CarbonDioxideGenerationRate, "CarbonDioxideGenerationRate", "Carbon Dioxide Generation Rate"},
{ OS_People_DefinitionFields::EnableASHRAE55ComfortWarnings, "EnableASHRAE55ComfortWarnings", "Enable ASHRAE 55 Comfort Warnings"},
{ OS_People_DefinitionFields::MeanRadiantTemperatureCalculationType, "MeanRadiantTemperatureCalculationType", "Mean Radiant Temperature Calculation Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_People_DefinitionFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_People_DefinitionFields> OptionalOS_People_DefinitionFields ;
#endif

/** \class OS_People_DefinitionExtensibleFields
 *  \brief Enumeration of OS:People:Definition's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_People_DefinitionExtensibleFields, )
#else
class OS_People_DefinitionExtensibleFields: public ::EnumBase<OS_People_DefinitionExtensibleFields> {
 public: 
  enum domain 
  {
ThermalComfortModelType,   };
  OS_People_DefinitionExtensibleFields()
   : EnumBase<OS_People_DefinitionExtensibleFields>(ThermalComfortModelType) {} 
  OS_People_DefinitionExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_People_DefinitionExtensibleFields>(t_name) {} 
  OS_People_DefinitionExtensibleFields(int t_value) 
   : EnumBase<OS_People_DefinitionExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_People_DefinitionExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_People_DefinitionExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_People_DefinitionExtensibleFields>;
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
{ OS_People_DefinitionExtensibleFields::ThermalComfortModelType, "ThermalComfortModelType", "Thermal Comfort Model Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_People_DefinitionExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_People_DefinitionExtensibleFields> OptionalOS_People_DefinitionExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_PEOPLE_DEFINITION_FIELDENUMS_HXX
