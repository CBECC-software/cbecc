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

#ifndef UTILITIES_IDD_SETPOINTMANAGER_RETURNTEMPERATURE_CHILLEDWATER_FIELDENUMS_HXX
#define UTILITIES_IDD_SETPOINTMANAGER_RETURNTEMPERATURE_CHILLEDWATER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SetpointManager_ReturnTemperature_ChilledWaterFields
 *  \brief Enumeration of SetpointManager:ReturnTemperature:ChilledWater's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SetpointManager_ReturnTemperature_ChilledWaterFields, )
#else
class SetpointManager_ReturnTemperature_ChilledWaterFields: public ::EnumBase<SetpointManager_ReturnTemperature_ChilledWaterFields> {
 public: 
  enum domain 
  {
Name, PlantLoopSupplyOutletNode, PlantLoopSupplyInletNode, MinimumSupplyTemperatureSetpoint, MaximumSupplyTemperatureSetpoint, ReturnTemperatureSetpointInputType, ReturnTemperatureSetpointConstantValue, ReturnTemperatureSetpointScheduleName,   };
  SetpointManager_ReturnTemperature_ChilledWaterFields()
   : EnumBase<SetpointManager_ReturnTemperature_ChilledWaterFields>(Name) {} 
  SetpointManager_ReturnTemperature_ChilledWaterFields(const std::string &t_name) 
   : EnumBase<SetpointManager_ReturnTemperature_ChilledWaterFields>(t_name) {} 
  SetpointManager_ReturnTemperature_ChilledWaterFields(int t_value) 
   : EnumBase<SetpointManager_ReturnTemperature_ChilledWaterFields>(t_value) {} 
  static std::string enumName() 
  { return "SetpointManager_ReturnTemperature_ChilledWaterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SetpointManager_ReturnTemperature_ChilledWaterFields>::value()); }
   private:
    friend class EnumBase<SetpointManager_ReturnTemperature_ChilledWaterFields>;
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
{ SetpointManager_ReturnTemperature_ChilledWaterFields::Name, "Name", "Name"},
{ SetpointManager_ReturnTemperature_ChilledWaterFields::PlantLoopSupplyOutletNode, "PlantLoopSupplyOutletNode", "Plant Loop Supply Outlet Node"},
{ SetpointManager_ReturnTemperature_ChilledWaterFields::PlantLoopSupplyInletNode, "PlantLoopSupplyInletNode", "Plant Loop Supply Inlet Node"},
{ SetpointManager_ReturnTemperature_ChilledWaterFields::MinimumSupplyTemperatureSetpoint, "MinimumSupplyTemperatureSetpoint", "Minimum Supply Temperature Setpoint"},
{ SetpointManager_ReturnTemperature_ChilledWaterFields::MaximumSupplyTemperatureSetpoint, "MaximumSupplyTemperatureSetpoint", "Maximum Supply Temperature Setpoint"},
{ SetpointManager_ReturnTemperature_ChilledWaterFields::ReturnTemperatureSetpointInputType, "ReturnTemperatureSetpointInputType", "Return Temperature Setpoint Input Type"},
{ SetpointManager_ReturnTemperature_ChilledWaterFields::ReturnTemperatureSetpointConstantValue, "ReturnTemperatureSetpointConstantValue", "Return Temperature Setpoint Constant Value"},
{ SetpointManager_ReturnTemperature_ChilledWaterFields::ReturnTemperatureSetpointScheduleName, "ReturnTemperatureSetpointScheduleName", "Return Temperature Setpoint Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SetpointManager_ReturnTemperature_ChilledWaterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SetpointManager_ReturnTemperature_ChilledWaterFields> OptionalSetpointManager_ReturnTemperature_ChilledWaterFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SETPOINTMANAGER_RETURNTEMPERATURE_CHILLEDWATER_FIELDENUMS_HXX
