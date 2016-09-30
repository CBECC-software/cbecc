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

#ifndef UTILITIES_IDD_COILSYSTEM_COOLING_DX_FIELDENUMS_HXX
#define UTILITIES_IDD_COILSYSTEM_COOLING_DX_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class CoilSystem_Cooling_DXFields
 *  \brief Enumeration of CoilSystem:Cooling:DX's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(CoilSystem_Cooling_DXFields, )
#else
class CoilSystem_Cooling_DXFields: public ::EnumBase<CoilSystem_Cooling_DXFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, DXCoolingCoilSystemInletNodeName, DXCoolingCoilSystemOutletNodeName, DXCoolingCoilSystemSensorNodeName, CoolingCoilObjectType, CoolingCoilName, DehumidificationControlType, RunonSensibleLoad, RunonLatentLoad, UseOutdoorAirDXCoolingCoil, OutdoorAirDXCoolingCoilLeavingMinimumAirTemperature,   };
  CoilSystem_Cooling_DXFields()
   : EnumBase<CoilSystem_Cooling_DXFields>(Name) {} 
  CoilSystem_Cooling_DXFields(const std::string &t_name) 
   : EnumBase<CoilSystem_Cooling_DXFields>(t_name) {} 
  CoilSystem_Cooling_DXFields(int t_value) 
   : EnumBase<CoilSystem_Cooling_DXFields>(t_value) {} 
  static std::string enumName() 
  { return "CoilSystem_Cooling_DXFields"; }
  domain value() const { return static_cast<domain>(EnumBase<CoilSystem_Cooling_DXFields>::value()); }
   private:
    friend class EnumBase<CoilSystem_Cooling_DXFields>;
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
{ CoilSystem_Cooling_DXFields::Name, "Name", "Name"},
{ CoilSystem_Cooling_DXFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ CoilSystem_Cooling_DXFields::DXCoolingCoilSystemInletNodeName, "DXCoolingCoilSystemInletNodeName", "DX Cooling Coil System Inlet Node Name"},
{ CoilSystem_Cooling_DXFields::DXCoolingCoilSystemOutletNodeName, "DXCoolingCoilSystemOutletNodeName", "DX Cooling Coil System Outlet Node Name"},
{ CoilSystem_Cooling_DXFields::DXCoolingCoilSystemSensorNodeName, "DXCoolingCoilSystemSensorNodeName", "DX Cooling Coil System Sensor Node Name"},
{ CoilSystem_Cooling_DXFields::CoolingCoilObjectType, "CoolingCoilObjectType", "Cooling Coil Object Type"},
{ CoilSystem_Cooling_DXFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ CoilSystem_Cooling_DXFields::DehumidificationControlType, "DehumidificationControlType", "Dehumidification Control Type"},
{ CoilSystem_Cooling_DXFields::RunonSensibleLoad, "RunonSensibleLoad", "Run on Sensible Load"},
{ CoilSystem_Cooling_DXFields::RunonLatentLoad, "RunonLatentLoad", "Run on Latent Load"},
{ CoilSystem_Cooling_DXFields::UseOutdoorAirDXCoolingCoil, "UseOutdoorAirDXCoolingCoil", "Use Outdoor Air DX Cooling Coil"},
{ CoilSystem_Cooling_DXFields::OutdoorAirDXCoolingCoilLeavingMinimumAirTemperature, "OutdoorAirDXCoolingCoilLeavingMinimumAirTemperature", "Outdoor Air DX Cooling Coil Leaving Minimum Air Temperature"},
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
  inline std::ostream &operator<<(std::ostream &os, const CoilSystem_Cooling_DXFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<CoilSystem_Cooling_DXFields> OptionalCoilSystem_Cooling_DXFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COILSYSTEM_COOLING_DX_FIELDENUMS_HXX
