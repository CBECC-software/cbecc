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

#ifndef UTILITIES_IDD_OS_COOLINGTOWERPERFORMANCE_YORKCALC_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COOLINGTOWERPERFORMANCE_YORKCALC_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_CoolingTowerPerformance_YorkCalcFields
 *  \brief Enumeration of OS:CoolingTowerPerformance:YorkCalc's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_CoolingTowerPerformance_YorkCalcFields, )
#else
class OS_CoolingTowerPerformance_YorkCalcFields: public ::EnumBase<OS_CoolingTowerPerformance_YorkCalcFields> {
 public: 
  enum domain 
  {
Handle, Name, MinimumInletAirWetBulbTemperature, MaximumInletAirWetBulbTemperature, MinimumRangeTemperature, MaximumRangeTemperature, MinimumApproachTemperature, MaximumApproachTemperature, MinimumWaterFlowRateRatio, MaximumWaterFlowRateRatio, MaximumLiquidtoGasRatio, Coefficient1, Coefficient2, Coefficient3, Coefficient4, Coefficient5, Coefficient6, Coefficient7, Coefficient8, Coefficient9, Coefficient10, Coefficient11, Coefficient12, Coefficient13, Coefficient14, Coefficient15, Coefficient16, Coefficient17, Coefficient18, Coefficient19, Coefficient20, Coefficient21, Coefficient22, Coefficient23, Coefficient24, Coefficient25, Coefficient26, Coefficient27,   };
  OS_CoolingTowerPerformance_YorkCalcFields()
   : EnumBase<OS_CoolingTowerPerformance_YorkCalcFields>(Handle) {} 
  OS_CoolingTowerPerformance_YorkCalcFields(const std::string &t_name) 
   : EnumBase<OS_CoolingTowerPerformance_YorkCalcFields>(t_name) {} 
  OS_CoolingTowerPerformance_YorkCalcFields(int t_value) 
   : EnumBase<OS_CoolingTowerPerformance_YorkCalcFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_CoolingTowerPerformance_YorkCalcFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_CoolingTowerPerformance_YorkCalcFields>::value()); }
   private:
    friend class EnumBase<OS_CoolingTowerPerformance_YorkCalcFields>;
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
{ OS_CoolingTowerPerformance_YorkCalcFields::Handle, "Handle", "Handle"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Name, "Name", "Name"},
{ OS_CoolingTowerPerformance_YorkCalcFields::MinimumInletAirWetBulbTemperature, "MinimumInletAirWetBulbTemperature", "Minimum Inlet Air Wet-Bulb Temperature"},
{ OS_CoolingTowerPerformance_YorkCalcFields::MaximumInletAirWetBulbTemperature, "MaximumInletAirWetBulbTemperature", "Maximum Inlet Air Wet-Bulb Temperature"},
{ OS_CoolingTowerPerformance_YorkCalcFields::MinimumRangeTemperature, "MinimumRangeTemperature", "Minimum Range Temperature"},
{ OS_CoolingTowerPerformance_YorkCalcFields::MaximumRangeTemperature, "MaximumRangeTemperature", "Maximum Range Temperature"},
{ OS_CoolingTowerPerformance_YorkCalcFields::MinimumApproachTemperature, "MinimumApproachTemperature", "Minimum Approach Temperature"},
{ OS_CoolingTowerPerformance_YorkCalcFields::MaximumApproachTemperature, "MaximumApproachTemperature", "Maximum Approach Temperature"},
{ OS_CoolingTowerPerformance_YorkCalcFields::MinimumWaterFlowRateRatio, "MinimumWaterFlowRateRatio", "Minimum Water Flow Rate Ratio"},
{ OS_CoolingTowerPerformance_YorkCalcFields::MaximumWaterFlowRateRatio, "MaximumWaterFlowRateRatio", "Maximum Water Flow Rate Ratio"},
{ OS_CoolingTowerPerformance_YorkCalcFields::MaximumLiquidtoGasRatio, "MaximumLiquidtoGasRatio", "Maximum Liquid to Gas Ratio"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient1, "Coefficient1", "Coefficient 1"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient2, "Coefficient2", "Coefficient 2"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient3, "Coefficient3", "Coefficient 3"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient4, "Coefficient4", "Coefficient 4"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient5, "Coefficient5", "Coefficient 5"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient6, "Coefficient6", "Coefficient 6"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient7, "Coefficient7", "Coefficient 7"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient8, "Coefficient8", "Coefficient 8"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient9, "Coefficient9", "Coefficient 9"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient10, "Coefficient10", "Coefficient 10"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient11, "Coefficient11", "Coefficient 11"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient12, "Coefficient12", "Coefficient 12"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient13, "Coefficient13", "Coefficient 13"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient14, "Coefficient14", "Coefficient 14"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient15, "Coefficient15", "Coefficient 15"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient16, "Coefficient16", "Coefficient 16"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient17, "Coefficient17", "Coefficient 17"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient18, "Coefficient18", "Coefficient 18"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient19, "Coefficient19", "Coefficient 19"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient20, "Coefficient20", "Coefficient 20"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient21, "Coefficient21", "Coefficient 21"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient22, "Coefficient22", "Coefficient 22"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient23, "Coefficient23", "Coefficient 23"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient24, "Coefficient24", "Coefficient 24"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient25, "Coefficient25", "Coefficient 25"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient26, "Coefficient26", "Coefficient 26"},
{ OS_CoolingTowerPerformance_YorkCalcFields::Coefficient27, "Coefficient27", "Coefficient 27"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_CoolingTowerPerformance_YorkCalcFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_CoolingTowerPerformance_YorkCalcFields> OptionalOS_CoolingTowerPerformance_YorkCalcFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COOLINGTOWERPERFORMANCE_YORKCALC_FIELDENUMS_HXX
