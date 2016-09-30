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

#ifndef UTILITIES_IDD_OS_AIRLOOPHVAC_UNITARYCOOLONLY_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRLOOPHVAC_UNITARYCOOLONLY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirLoopHVAC_UnitaryCoolOnlyFields
 *  \brief Enumeration of OS:AirLoopHVAC:UnitaryCoolOnly's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirLoopHVAC_UnitaryCoolOnlyFields, )
#else
class OS_AirLoopHVAC_UnitaryCoolOnlyFields: public ::EnumBase<OS_AirLoopHVAC_UnitaryCoolOnlyFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, DXCoolingCoilSystemInletNodeName, DXCoolingCoilSystemOutletNodeName, DXCoolingCoilSystemSensorNodeName, CoolingCoilObjectType, CoolingCoilName, DehumidificationControlType, RunonSensibleLoad, RunonLatentLoad,   };
  OS_AirLoopHVAC_UnitaryCoolOnlyFields()
   : EnumBase<OS_AirLoopHVAC_UnitaryCoolOnlyFields>(Handle) {} 
  OS_AirLoopHVAC_UnitaryCoolOnlyFields(const std::string &t_name) 
   : EnumBase<OS_AirLoopHVAC_UnitaryCoolOnlyFields>(t_name) {} 
  OS_AirLoopHVAC_UnitaryCoolOnlyFields(int t_value) 
   : EnumBase<OS_AirLoopHVAC_UnitaryCoolOnlyFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirLoopHVAC_UnitaryCoolOnlyFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirLoopHVAC_UnitaryCoolOnlyFields>::value()); }
   private:
    friend class EnumBase<OS_AirLoopHVAC_UnitaryCoolOnlyFields>;
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
{ OS_AirLoopHVAC_UnitaryCoolOnlyFields::Handle, "Handle", "Handle"},
{ OS_AirLoopHVAC_UnitaryCoolOnlyFields::Name, "Name", "Name"},
{ OS_AirLoopHVAC_UnitaryCoolOnlyFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_AirLoopHVAC_UnitaryCoolOnlyFields::DXCoolingCoilSystemInletNodeName, "DXCoolingCoilSystemInletNodeName", "DX Cooling Coil System Inlet Node Name"},
{ OS_AirLoopHVAC_UnitaryCoolOnlyFields::DXCoolingCoilSystemOutletNodeName, "DXCoolingCoilSystemOutletNodeName", "DX Cooling Coil System Outlet Node Name"},
{ OS_AirLoopHVAC_UnitaryCoolOnlyFields::DXCoolingCoilSystemSensorNodeName, "DXCoolingCoilSystemSensorNodeName", "DX Cooling Coil System Sensor Node Name"},
{ OS_AirLoopHVAC_UnitaryCoolOnlyFields::CoolingCoilObjectType, "CoolingCoilObjectType", "Cooling Coil Object Type"},
{ OS_AirLoopHVAC_UnitaryCoolOnlyFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ OS_AirLoopHVAC_UnitaryCoolOnlyFields::DehumidificationControlType, "DehumidificationControlType", "Dehumidification Control Type"},
{ OS_AirLoopHVAC_UnitaryCoolOnlyFields::RunonSensibleLoad, "RunonSensibleLoad", "Run on Sensible Load"},
{ OS_AirLoopHVAC_UnitaryCoolOnlyFields::RunonLatentLoad, "RunonLatentLoad", "Run on Latent Load"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirLoopHVAC_UnitaryCoolOnlyFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirLoopHVAC_UnitaryCoolOnlyFields> OptionalOS_AirLoopHVAC_UnitaryCoolOnlyFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRLOOPHVAC_UNITARYCOOLONLY_FIELDENUMS_HXX
