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

#ifndef UTILITIES_IDD_OS_BOILER_HOTWATER_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_BOILER_HOTWATER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Boiler_HotWaterFields
 *  \brief Enumeration of OS:Boiler:HotWater's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Boiler_HotWaterFields, )
#else
class OS_Boiler_HotWaterFields: public ::EnumBase<OS_Boiler_HotWaterFields> {
 public: 
  enum domain 
  {
Handle, Name, FuelType, NominalCapacity, NominalThermalEfficiency, EfficiencyCurveTemperatureEvaluationVariable, NormalizedBoilerEfficiencyCurveName, DesignWaterOutletTemperature, DesignWaterFlowRate, MinimumPartLoadRatio, MaximumPartLoadRatio, OptimumPartLoadRatio, BoilerWaterInletNodeName, BoilerWaterOutletNodeName, WaterOutletUpperTemperatureLimit, BoilerFlowMode, ParasiticElectricLoad, SizingFactor,   };
  OS_Boiler_HotWaterFields()
   : EnumBase<OS_Boiler_HotWaterFields>(Handle) {} 
  OS_Boiler_HotWaterFields(const std::string &t_name) 
   : EnumBase<OS_Boiler_HotWaterFields>(t_name) {} 
  OS_Boiler_HotWaterFields(int t_value) 
   : EnumBase<OS_Boiler_HotWaterFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Boiler_HotWaterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Boiler_HotWaterFields>::value()); }
   private:
    friend class EnumBase<OS_Boiler_HotWaterFields>;
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
{ OS_Boiler_HotWaterFields::Handle, "Handle", "Handle"},
{ OS_Boiler_HotWaterFields::Name, "Name", "Name"},
{ OS_Boiler_HotWaterFields::FuelType, "FuelType", "Fuel Type"},
{ OS_Boiler_HotWaterFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ OS_Boiler_HotWaterFields::NominalThermalEfficiency, "NominalThermalEfficiency", "Nominal Thermal Efficiency"},
{ OS_Boiler_HotWaterFields::EfficiencyCurveTemperatureEvaluationVariable, "EfficiencyCurveTemperatureEvaluationVariable", "Efficiency Curve Temperature Evaluation Variable"},
{ OS_Boiler_HotWaterFields::NormalizedBoilerEfficiencyCurveName, "NormalizedBoilerEfficiencyCurveName", "Normalized Boiler Efficiency Curve Name"},
{ OS_Boiler_HotWaterFields::DesignWaterOutletTemperature, "DesignWaterOutletTemperature", "Design Water Outlet Temperature"},
{ OS_Boiler_HotWaterFields::DesignWaterFlowRate, "DesignWaterFlowRate", "Design Water Flow Rate"},
{ OS_Boiler_HotWaterFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ OS_Boiler_HotWaterFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ OS_Boiler_HotWaterFields::OptimumPartLoadRatio, "OptimumPartLoadRatio", "Optimum Part Load Ratio"},
{ OS_Boiler_HotWaterFields::BoilerWaterInletNodeName, "BoilerWaterInletNodeName", "Boiler Water Inlet Node Name"},
{ OS_Boiler_HotWaterFields::BoilerWaterOutletNodeName, "BoilerWaterOutletNodeName", "Boiler Water Outlet Node Name"},
{ OS_Boiler_HotWaterFields::WaterOutletUpperTemperatureLimit, "WaterOutletUpperTemperatureLimit", "Water Outlet Upper Temperature Limit"},
{ OS_Boiler_HotWaterFields::BoilerFlowMode, "BoilerFlowMode", "Boiler Flow Mode"},
{ OS_Boiler_HotWaterFields::ParasiticElectricLoad, "ParasiticElectricLoad", "Parasitic Electric Load"},
{ OS_Boiler_HotWaterFields::SizingFactor, "SizingFactor", "Sizing Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Boiler_HotWaterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Boiler_HotWaterFields> OptionalOS_Boiler_HotWaterFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_BOILER_HOTWATER_FIELDENUMS_HXX
