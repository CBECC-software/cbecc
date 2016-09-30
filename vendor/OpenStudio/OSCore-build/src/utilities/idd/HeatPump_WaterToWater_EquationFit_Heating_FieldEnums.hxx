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

#ifndef UTILITIES_IDD_HEATPUMP_WATERTOWATER_EQUATIONFIT_HEATING_FIELDENUMS_HXX
#define UTILITIES_IDD_HEATPUMP_WATERTOWATER_EQUATIONFIT_HEATING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HeatPump_WaterToWater_EquationFit_HeatingFields
 *  \brief Enumeration of HeatPump:WaterToWater:EquationFit:Heating's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HeatPump_WaterToWater_EquationFit_HeatingFields, )
#else
class HeatPump_WaterToWater_EquationFit_HeatingFields: public ::EnumBase<HeatPump_WaterToWater_EquationFit_HeatingFields> {
 public: 
  enum domain 
  {
Name, SourceSideInletNodeName, SourceSideOutletNodeName, LoadSideInletNodeName, LoadSideOutletNodeName, RatedLoadSideFlowRate, RatedSourceSideFlowRate, RatedHeatingCapacity, RatedHeatingPowerConsumption, HeatingCapacityCoefficient1, HeatingCapacityCoefficient2, HeatingCapacityCoefficient3, HeatingCapacityCoefficient4, HeatingCapacityCoefficient5, HeatingCompressorPowerCoefficient1, HeatingCompressorPowerCoefficient2, HeatingCompressorPowerCoefficient3, HeatingCompressorPowerCoefficient4, HeatingCompressorPowerCoefficient5,   };
  HeatPump_WaterToWater_EquationFit_HeatingFields()
   : EnumBase<HeatPump_WaterToWater_EquationFit_HeatingFields>(Name) {} 
  HeatPump_WaterToWater_EquationFit_HeatingFields(const std::string &t_name) 
   : EnumBase<HeatPump_WaterToWater_EquationFit_HeatingFields>(t_name) {} 
  HeatPump_WaterToWater_EquationFit_HeatingFields(int t_value) 
   : EnumBase<HeatPump_WaterToWater_EquationFit_HeatingFields>(t_value) {} 
  static std::string enumName() 
  { return "HeatPump_WaterToWater_EquationFit_HeatingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HeatPump_WaterToWater_EquationFit_HeatingFields>::value()); }
   private:
    friend class EnumBase<HeatPump_WaterToWater_EquationFit_HeatingFields>;
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
{ HeatPump_WaterToWater_EquationFit_HeatingFields::Name, "Name", "Name"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideInletNodeName, "SourceSideInletNodeName", "Source Side Inlet Node Name"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideOutletNodeName, "SourceSideOutletNodeName", "Source Side Outlet Node Name"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideInletNodeName, "LoadSideInletNodeName", "Load Side Inlet Node Name"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideOutletNodeName, "LoadSideOutletNodeName", "Load Side Outlet Node Name"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::RatedLoadSideFlowRate, "RatedLoadSideFlowRate", "Rated Load Side Flow Rate"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::RatedSourceSideFlowRate, "RatedSourceSideFlowRate", "Rated Source Side Flow Rate"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::RatedHeatingCapacity, "RatedHeatingCapacity", "Rated Heating Capacity"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::RatedHeatingPowerConsumption, "RatedHeatingPowerConsumption", "Rated Heating Power Consumption"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCapacityCoefficient1, "HeatingCapacityCoefficient1", "Heating Capacity Coefficient 1"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCapacityCoefficient2, "HeatingCapacityCoefficient2", "Heating Capacity Coefficient 2"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCapacityCoefficient3, "HeatingCapacityCoefficient3", "Heating Capacity Coefficient 3"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCapacityCoefficient4, "HeatingCapacityCoefficient4", "Heating Capacity Coefficient 4"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCapacityCoefficient5, "HeatingCapacityCoefficient5", "Heating Capacity Coefficient 5"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCompressorPowerCoefficient1, "HeatingCompressorPowerCoefficient1", "Heating Compressor Power Coefficient 1"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCompressorPowerCoefficient2, "HeatingCompressorPowerCoefficient2", "Heating Compressor Power Coefficient 2"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCompressorPowerCoefficient3, "HeatingCompressorPowerCoefficient3", "Heating Compressor Power Coefficient 3"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCompressorPowerCoefficient4, "HeatingCompressorPowerCoefficient4", "Heating Compressor Power Coefficient 4"},
{ HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCompressorPowerCoefficient5, "HeatingCompressorPowerCoefficient5", "Heating Compressor Power Coefficient 5"},
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
  inline std::ostream &operator<<(std::ostream &os, const HeatPump_WaterToWater_EquationFit_HeatingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HeatPump_WaterToWater_EquationFit_HeatingFields> OptionalHeatPump_WaterToWater_EquationFit_HeatingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HEATPUMP_WATERTOWATER_EQUATIONFIT_HEATING_FIELDENUMS_HXX
