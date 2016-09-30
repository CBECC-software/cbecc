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

#ifndef UTILITIES_IDD_OS_COIL_COOLING_DX_VARIABLESPEED_SPEEDDATA_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_COOLING_DX_VARIABLESPEED_SPEEDDATA_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields
 *  \brief Enumeration of OS:Coil:Cooling:DX:VariableSpeed:SpeedData's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields, )
#else
class OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields: public ::EnumBase<OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields> {
 public: 
  enum domain 
  {
Handle, Name, ReferenceUnitGrossRatedTotalCoolingCapacity, ReferenceUnitGrossRatedSensibleHeatRatio, ReferenceUnitGrossRatedCoolingCOP, ReferenceUnitRatedAirFlowRate, ReferenceUnitRatedCondenserAirFlowRate, ReferenceUnitRatedPadEffectivenessofEvapPrecooling, TotalCoolingCapacityFunctionofTemperatureCurveName, TotalCoolingCapacityFunctionofAirFlowFractionCurveName, EnergyInputRatioFunctionofTemperatureCurveName, EnergyInputRatioFunctionofAirFlowFractionCurveName,   };
  OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields()
   : EnumBase<OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields>(Handle) {} 
  OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields>(t_name) {} 
  OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields(int t_value) 
   : EnumBase<OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields>::value()); }
   private:
    friend class EnumBase<OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields>;
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
{ OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields::Handle, "Handle", "Handle"},
{ OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields::Name, "Name", "Name"},
{ OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields::ReferenceUnitGrossRatedTotalCoolingCapacity, "ReferenceUnitGrossRatedTotalCoolingCapacity", "Reference Unit Gross Rated Total Cooling Capacity"},
{ OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields::ReferenceUnitGrossRatedSensibleHeatRatio, "ReferenceUnitGrossRatedSensibleHeatRatio", "Reference Unit Gross Rated Sensible Heat Ratio"},
{ OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields::ReferenceUnitGrossRatedCoolingCOP, "ReferenceUnitGrossRatedCoolingCOP", "Reference Unit Gross Rated Cooling COP"},
{ OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields::ReferenceUnitRatedAirFlowRate, "ReferenceUnitRatedAirFlowRate", "Reference Unit Rated Air Flow Rate"},
{ OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields::ReferenceUnitRatedCondenserAirFlowRate, "ReferenceUnitRatedCondenserAirFlowRate", "Reference Unit Rated Condenser Air Flow Rate"},
{ OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields::ReferenceUnitRatedPadEffectivenessofEvapPrecooling, "ReferenceUnitRatedPadEffectivenessofEvapPrecooling", "Reference Unit Rated Pad Effectiveness of Evap Precooling"},
{ OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields::TotalCoolingCapacityFunctionofTemperatureCurveName, "TotalCoolingCapacityFunctionofTemperatureCurveName", "Total Cooling Capacity Function of Temperature Curve Name"},
{ OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields::TotalCoolingCapacityFunctionofAirFlowFractionCurveName, "TotalCoolingCapacityFunctionofAirFlowFractionCurveName", "Total Cooling Capacity Function of Air Flow Fraction Curve Name"},
{ OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields::EnergyInputRatioFunctionofTemperatureCurveName, "EnergyInputRatioFunctionofTemperatureCurveName", "Energy Input Ratio Function of Temperature Curve Name"},
{ OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields::EnergyInputRatioFunctionofAirFlowFractionCurveName, "EnergyInputRatioFunctionofAirFlowFractionCurveName", "Energy Input Ratio Function of Air Flow Fraction Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields> OptionalOS_Coil_Cooling_DX_VariableSpeed_SpeedDataFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_COOLING_DX_VARIABLESPEED_SPEEDDATA_FIELDENUMS_HXX
