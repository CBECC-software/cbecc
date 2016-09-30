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

#ifndef UTILITIES_IDD_OS_HEATPUMP_WATERTOWATER_EQUATIONFIT_HEATING_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_HEATPUMP_WATERTOWATER_EQUATIONFIT_HEATING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_HeatPump_WaterToWater_EquationFit_HeatingFields
 *  \brief Enumeration of OS:HeatPump:WaterToWater:EquationFit:Heating's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_HeatPump_WaterToWater_EquationFit_HeatingFields, )
#else
class OS_HeatPump_WaterToWater_EquationFit_HeatingFields: public ::EnumBase<OS_HeatPump_WaterToWater_EquationFit_HeatingFields> {
 public: 
  enum domain 
  {
Handle, Name, SourceSideInletNodeName, SourceSideOutletNodeName, LoadSideInletNodeName, LoadSideOutletNodeName, RatedLoadSideFlowRate, RatedSourceSideFlowRate, RatedHeatingCapacity, RatedHeatingPowerConsumption, HeatingCapacityCoefficient1, HeatingCapacityCoefficient2, HeatingCapacityCoefficient3, HeatingCapacityCoefficient4, HeatingCapacityCoefficient5, HeatingCompressorPowerCoefficient1, HeatingCompressorPowerCoefficient2, HeatingCompressorPowerCoefficient3, HeatingCompressorPowerCoefficient4, HeatingCompressorPowerCoefficient5,   };
  OS_HeatPump_WaterToWater_EquationFit_HeatingFields()
   : EnumBase<OS_HeatPump_WaterToWater_EquationFit_HeatingFields>(Handle) {} 
  OS_HeatPump_WaterToWater_EquationFit_HeatingFields(const std::string &t_name) 
   : EnumBase<OS_HeatPump_WaterToWater_EquationFit_HeatingFields>(t_name) {} 
  OS_HeatPump_WaterToWater_EquationFit_HeatingFields(int t_value) 
   : EnumBase<OS_HeatPump_WaterToWater_EquationFit_HeatingFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_HeatPump_WaterToWater_EquationFit_HeatingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_HeatPump_WaterToWater_EquationFit_HeatingFields>::value()); }
   private:
    friend class EnumBase<OS_HeatPump_WaterToWater_EquationFit_HeatingFields>;
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
{ OS_HeatPump_WaterToWater_EquationFit_HeatingFields::Handle, "Handle", "Handle"},
{ OS_HeatPump_WaterToWater_EquationFit_HeatingFields::Name, "Name", "Name"},
{ OS_HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideInletNodeName, "SourceSideInletNodeName", "Source Side Inlet Node Name"},
{ OS_HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideOutletNodeName, "SourceSideOutletNodeName", "Source Side Outlet Node Name"},
{ OS_HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideInletNodeName, "LoadSideInletNodeName", "Load Side Inlet Node Name"},
{ OS_HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideOutletNodeName, "LoadSideOutletNodeName", "Load Side Outlet Node Name"},
{ OS_HeatPump_WaterToWater_EquationFit_HeatingFields::RatedLoadSideFlowRate, "RatedLoadSideFlowRate", "Rated Load Side Flow Rate"},
{ OS_HeatPump_WaterToWater_EquationFit_HeatingFields::RatedSourceSideFlowRate, "RatedSourceSideFlowRate", "Rated Source Side Flow Rate"},
{ OS_HeatPump_WaterToWater_EquationFit_HeatingFields::RatedHeatingCapacity, "RatedHeatingCapacity", "Rated Heating Capacity"},
{ OS_HeatPump_WaterToWater_EquationFit_HeatingFields::RatedHeatingPowerConsumption, "RatedHeatingPowerConsumption", "Rated Heating Power Consumption"},
{ OS_HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCapacityCoefficient1, "HeatingCapacityCoefficient1", "Heating Capacity Coefficient 1"},
{ OS_HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCapacityCoefficient2, "HeatingCapacityCoefficient2", "Heating Capacity Coefficient 2"},
{ OS_HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCapacityCoefficient3, "HeatingCapacityCoefficient3", "Heating Capacity Coefficient 3"},
{ OS_HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCapacityCoefficient4, "HeatingCapacityCoefficient4", "Heating Capacity Coefficient 4"},
{ OS_HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCapacityCoefficient5, "HeatingCapacityCoefficient5", "Heating Capacity Coefficient 5"},
{ OS_HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCompressorPowerCoefficient1, "HeatingCompressorPowerCoefficient1", "Heating Compressor Power Coefficient 1"},
{ OS_HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCompressorPowerCoefficient2, "HeatingCompressorPowerCoefficient2", "Heating Compressor Power Coefficient 2"},
{ OS_HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCompressorPowerCoefficient3, "HeatingCompressorPowerCoefficient3", "Heating Compressor Power Coefficient 3"},
{ OS_HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCompressorPowerCoefficient4, "HeatingCompressorPowerCoefficient4", "Heating Compressor Power Coefficient 4"},
{ OS_HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCompressorPowerCoefficient5, "HeatingCompressorPowerCoefficient5", "Heating Compressor Power Coefficient 5"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_HeatPump_WaterToWater_EquationFit_HeatingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_HeatPump_WaterToWater_EquationFit_HeatingFields> OptionalOS_HeatPump_WaterToWater_EquationFit_HeatingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_HEATPUMP_WATERTOWATER_EQUATIONFIT_HEATING_FIELDENUMS_HXX
