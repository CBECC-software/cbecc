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

#ifndef UTILITIES_IDD_SOLARCOLLECTORPERFORMANCE_PHOTOVOLTAICTHERMAL_SIMPLE_FIELDENUMS_HXX
#define UTILITIES_IDD_SOLARCOLLECTORPERFORMANCE_PHOTOVOLTAICTHERMAL_SIMPLE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields
 *  \brief Enumeration of SolarCollectorPerformance:PhotovoltaicThermal:Simple's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields, )
#else
class SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields: public ::EnumBase<SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields> {
 public: 
  enum domain 
  {
Name, FractionofSurfaceAreawithActiveThermalCollector, ThermalConversionEfficiencyInputModeType, ValueforThermalConversionEfficiencyifFixed, ThermalConversionEfficiencyScheduleName, FrontSurfaceEmittance,   };
  SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields()
   : EnumBase<SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields>(Name) {} 
  SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields(const std::string &t_name) 
   : EnumBase<SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields>(t_name) {} 
  SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields(int t_value) 
   : EnumBase<SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields>(t_value) {} 
  static std::string enumName() 
  { return "SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields>::value()); }
   private:
    friend class EnumBase<SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields>;
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
{ SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields::Name, "Name", "Name"},
{ SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields::FractionofSurfaceAreawithActiveThermalCollector, "FractionofSurfaceAreawithActiveThermalCollector", "Fraction of Surface Area with Active Thermal Collector"},
{ SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields::ThermalConversionEfficiencyInputModeType, "ThermalConversionEfficiencyInputModeType", "Thermal Conversion Efficiency Input Mode Type"},
{ SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields::ValueforThermalConversionEfficiencyifFixed, "ValueforThermalConversionEfficiencyifFixed", "Value for Thermal Conversion Efficiency if Fixed"},
{ SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields::ThermalConversionEfficiencyScheduleName, "ThermalConversionEfficiencyScheduleName", "Thermal Conversion Efficiency Schedule Name"},
{ SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields::FrontSurfaceEmittance, "FrontSurfaceEmittance", "Front Surface Emittance"},
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
  inline std::ostream &operator<<(std::ostream &os, const SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields> OptionalSolarCollectorPerformance_PhotovoltaicThermal_SimpleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SOLARCOLLECTORPERFORMANCE_PHOTOVOLTAICTHERMAL_SIMPLE_FIELDENUMS_HXX
