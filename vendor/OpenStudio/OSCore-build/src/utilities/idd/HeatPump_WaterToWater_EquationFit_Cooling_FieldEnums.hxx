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

#ifndef UTILITIES_IDD_HEATPUMP_WATERTOWATER_EQUATIONFIT_COOLING_FIELDENUMS_HXX
#define UTILITIES_IDD_HEATPUMP_WATERTOWATER_EQUATIONFIT_COOLING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HeatPump_WaterToWater_EquationFit_CoolingFields
 *  \brief Enumeration of HeatPump:WaterToWater:EquationFit:Cooling's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HeatPump_WaterToWater_EquationFit_CoolingFields, )
#else
class HeatPump_WaterToWater_EquationFit_CoolingFields: public ::EnumBase<HeatPump_WaterToWater_EquationFit_CoolingFields> {
 public: 
  enum domain 
  {
Name, SourceSideInletNodeName, SourceSideOutletNodeName, LoadSideInletNodeName, LoadSideOutletNodeName, RatedLoadSideFlowRate, RatedSourceSideFlowRate, RatedCoolingCapacity, RatedCoolingPowerConsumption, CoolingCapacityCoefficient1, CoolingCapacityCoefficient2, CoolingCapacityCoefficient3, CoolingCapacityCoefficient4, CoolingCapacityCoefficient5, CoolingCompressorPowerCoefficient1, CoolingCompressorPowerCoefficient2, CoolingCompressorPowerCoefficient3, CoolingCompressorPowerCoefficient4, CoolingCompressorPowerCoefficient5,   };
  HeatPump_WaterToWater_EquationFit_CoolingFields()
   : EnumBase<HeatPump_WaterToWater_EquationFit_CoolingFields>(Name) {} 
  HeatPump_WaterToWater_EquationFit_CoolingFields(const std::string &t_name) 
   : EnumBase<HeatPump_WaterToWater_EquationFit_CoolingFields>(t_name) {} 
  HeatPump_WaterToWater_EquationFit_CoolingFields(int t_value) 
   : EnumBase<HeatPump_WaterToWater_EquationFit_CoolingFields>(t_value) {} 
  static std::string enumName() 
  { return "HeatPump_WaterToWater_EquationFit_CoolingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HeatPump_WaterToWater_EquationFit_CoolingFields>::value()); }
   private:
    friend class EnumBase<HeatPump_WaterToWater_EquationFit_CoolingFields>;
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
{ HeatPump_WaterToWater_EquationFit_CoolingFields::Name, "Name", "Name"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideInletNodeName, "SourceSideInletNodeName", "Source Side Inlet Node Name"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideOutletNodeName, "SourceSideOutletNodeName", "Source Side Outlet Node Name"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::LoadSideInletNodeName, "LoadSideInletNodeName", "Load Side Inlet Node Name"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::LoadSideOutletNodeName, "LoadSideOutletNodeName", "Load Side Outlet Node Name"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::RatedLoadSideFlowRate, "RatedLoadSideFlowRate", "Rated Load Side Flow Rate"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::RatedSourceSideFlowRate, "RatedSourceSideFlowRate", "Rated Source Side Flow Rate"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::RatedCoolingCapacity, "RatedCoolingCapacity", "Rated Cooling Capacity"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::RatedCoolingPowerConsumption, "RatedCoolingPowerConsumption", "Rated Cooling Power Consumption"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::CoolingCapacityCoefficient1, "CoolingCapacityCoefficient1", "Cooling Capacity Coefficient 1"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::CoolingCapacityCoefficient2, "CoolingCapacityCoefficient2", "Cooling Capacity Coefficient 2"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::CoolingCapacityCoefficient3, "CoolingCapacityCoefficient3", "Cooling Capacity Coefficient 3"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::CoolingCapacityCoefficient4, "CoolingCapacityCoefficient4", "Cooling Capacity Coefficient 4"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::CoolingCapacityCoefficient5, "CoolingCapacityCoefficient5", "Cooling Capacity Coefficient 5"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::CoolingCompressorPowerCoefficient1, "CoolingCompressorPowerCoefficient1", "Cooling Compressor Power Coefficient 1"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::CoolingCompressorPowerCoefficient2, "CoolingCompressorPowerCoefficient2", "Cooling Compressor Power Coefficient 2"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::CoolingCompressorPowerCoefficient3, "CoolingCompressorPowerCoefficient3", "Cooling Compressor Power Coefficient 3"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::CoolingCompressorPowerCoefficient4, "CoolingCompressorPowerCoefficient4", "Cooling Compressor Power Coefficient 4"},
{ HeatPump_WaterToWater_EquationFit_CoolingFields::CoolingCompressorPowerCoefficient5, "CoolingCompressorPowerCoefficient5", "Cooling Compressor Power Coefficient 5"},
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
  inline std::ostream &operator<<(std::ostream &os, const HeatPump_WaterToWater_EquationFit_CoolingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HeatPump_WaterToWater_EquationFit_CoolingFields> OptionalHeatPump_WaterToWater_EquationFit_CoolingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HEATPUMP_WATERTOWATER_EQUATIONFIT_COOLING_FIELDENUMS_HXX
