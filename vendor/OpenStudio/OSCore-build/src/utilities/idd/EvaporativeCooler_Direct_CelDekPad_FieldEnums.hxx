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

#ifndef UTILITIES_IDD_EVAPORATIVECOOLER_DIRECT_CELDEKPAD_FIELDENUMS_HXX
#define UTILITIES_IDD_EVAPORATIVECOOLER_DIRECT_CELDEKPAD_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class EvaporativeCooler_Direct_CelDekPadFields
 *  \brief Enumeration of EvaporativeCooler:Direct:CelDekPad's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(EvaporativeCooler_Direct_CelDekPadFields, )
#else
class EvaporativeCooler_Direct_CelDekPadFields: public ::EnumBase<EvaporativeCooler_Direct_CelDekPadFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, DirectPadArea, DirectPadDepth, RecirculatingWaterPumpPowerConsumption, AirInletNodeName, AirOutletNodeName, ControlType, WaterSupplyStorageTankName,   };
  EvaporativeCooler_Direct_CelDekPadFields()
   : EnumBase<EvaporativeCooler_Direct_CelDekPadFields>(Name) {} 
  EvaporativeCooler_Direct_CelDekPadFields(const std::string &t_name) 
   : EnumBase<EvaporativeCooler_Direct_CelDekPadFields>(t_name) {} 
  EvaporativeCooler_Direct_CelDekPadFields(int t_value) 
   : EnumBase<EvaporativeCooler_Direct_CelDekPadFields>(t_value) {} 
  static std::string enumName() 
  { return "EvaporativeCooler_Direct_CelDekPadFields"; }
  domain value() const { return static_cast<domain>(EnumBase<EvaporativeCooler_Direct_CelDekPadFields>::value()); }
   private:
    friend class EnumBase<EvaporativeCooler_Direct_CelDekPadFields>;
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
{ EvaporativeCooler_Direct_CelDekPadFields::Name, "Name", "Name"},
{ EvaporativeCooler_Direct_CelDekPadFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ EvaporativeCooler_Direct_CelDekPadFields::DirectPadArea, "DirectPadArea", "Direct Pad Area"},
{ EvaporativeCooler_Direct_CelDekPadFields::DirectPadDepth, "DirectPadDepth", "Direct Pad Depth"},
{ EvaporativeCooler_Direct_CelDekPadFields::RecirculatingWaterPumpPowerConsumption, "RecirculatingWaterPumpPowerConsumption", "Recirculating Water Pump Power Consumption"},
{ EvaporativeCooler_Direct_CelDekPadFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ EvaporativeCooler_Direct_CelDekPadFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ EvaporativeCooler_Direct_CelDekPadFields::ControlType, "ControlType", "Control Type"},
{ EvaporativeCooler_Direct_CelDekPadFields::WaterSupplyStorageTankName, "WaterSupplyStorageTankName", "Water Supply Storage Tank Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const EvaporativeCooler_Direct_CelDekPadFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<EvaporativeCooler_Direct_CelDekPadFields> OptionalEvaporativeCooler_Direct_CelDekPadFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_EVAPORATIVECOOLER_DIRECT_CELDEKPAD_FIELDENUMS_HXX
