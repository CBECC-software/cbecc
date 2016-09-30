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
Name, ZoneorZoneListName, ScheduleName, DesignLevelCalculationMethod, LightingLevel, WattsperZoneFloorArea, WattsperPerson, ReturnAirFraction, FractionRadiant, FractionVisible, FractionReplaceable, EndUseSubcategory, ReturnAirFractionCalculatedfromPlenumTemperature, ReturnAirFractionFunctionofPlenumTemperatureCoefficient1, ReturnAirFractionFunctionofPlenumTemperatureCoefficient2,   };
  LightsFields()
   : EnumBase<LightsFields>(Name) {} 
  LightsFields(const std::string &t_name) 
   : EnumBase<LightsFields>(t_name) {} 
  LightsFields(int t_value) 
   : EnumBase<LightsFields>(t_value) {} 
  static std::string enumName() 
  { return "LightsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<LightsFields>::value()); }
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
{ LightsFields::ZoneorZoneListName, "ZoneorZoneListName", "Zone or ZoneList Name"},
{ LightsFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ LightsFields::DesignLevelCalculationMethod, "DesignLevelCalculationMethod", "Design Level Calculation Method"},
{ LightsFields::LightingLevel, "LightingLevel", "Lighting Level"},
{ LightsFields::WattsperZoneFloorArea, "WattsperZoneFloorArea", "Watts per Zone Floor Area"},
{ LightsFields::WattsperPerson, "WattsperPerson", "Watts per Person"},
{ LightsFields::ReturnAirFraction, "ReturnAirFraction", "Return Air Fraction"},
{ LightsFields::FractionRadiant, "FractionRadiant", "Fraction Radiant"},
{ LightsFields::FractionVisible, "FractionVisible", "Fraction Visible"},
{ LightsFields::FractionReplaceable, "FractionReplaceable", "Fraction Replaceable"},
{ LightsFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ LightsFields::ReturnAirFractionCalculatedfromPlenumTemperature, "ReturnAirFractionCalculatedfromPlenumTemperature", "Return Air Fraction Calculated from Plenum Temperature"},
{ LightsFields::ReturnAirFractionFunctionofPlenumTemperatureCoefficient1, "ReturnAirFractionFunctionofPlenumTemperatureCoefficient1", "Return Air Fraction Function of Plenum Temperature Coefficient 1"},
{ LightsFields::ReturnAirFractionFunctionofPlenumTemperatureCoefficient2, "ReturnAirFractionFunctionofPlenumTemperatureCoefficient2", "Return Air Fraction Function of Plenum Temperature Coefficient 2"},
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
