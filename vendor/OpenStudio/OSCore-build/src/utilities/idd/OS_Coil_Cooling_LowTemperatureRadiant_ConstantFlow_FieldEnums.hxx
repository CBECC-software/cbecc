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

#ifndef UTILITIES_IDD_OS_COIL_COOLING_LOWTEMPERATURERADIANT_CONSTANTFLOW_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_COOLING_LOWTEMPERATURERADIANT_CONSTANTFLOW_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields
 *  \brief Enumeration of OS:Coil:Cooling:LowTemperatureRadiant:ConstantFlow's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields, )
#else
class OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields: public ::EnumBase<OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields> {
 public: 
  enum domain 
  {
Handle, Name, CoolingWaterInletNodeName, CoolingWaterOutletNodeName, CoolingHighWaterTemperatureScheduleName, CoolingLowWaterTemperatureScheduleName, CoolingHighControlTemperatureScheduleName, CoolingLowControlTemperatureScheduleName, CondensationControlType, CondensationControlDewpointOffset,   };
  OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields()
   : EnumBase<OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields>(Handle) {} 
  OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields>(t_name) {} 
  OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields(int t_value) 
   : EnumBase<OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields>::value()); }
   private:
    friend class EnumBase<OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields>;
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
{ OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::Handle, "Handle", "Handle"},
{ OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::Name, "Name", "Name"},
{ OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingWaterInletNodeName, "CoolingWaterInletNodeName", "Cooling Water Inlet Node Name"},
{ OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingWaterOutletNodeName, "CoolingWaterOutletNodeName", "Cooling Water Outlet Node Name"},
{ OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingHighWaterTemperatureScheduleName, "CoolingHighWaterTemperatureScheduleName", "Cooling High Water Temperature Schedule Name"},
{ OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingLowWaterTemperatureScheduleName, "CoolingLowWaterTemperatureScheduleName", "Cooling Low Water Temperature Schedule Name"},
{ OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingHighControlTemperatureScheduleName, "CoolingHighControlTemperatureScheduleName", "Cooling High Control Temperature Schedule Name"},
{ OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingLowControlTemperatureScheduleName, "CoolingLowControlTemperatureScheduleName", "Cooling Low Control Temperature Schedule Name"},
{ OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CondensationControlType, "CondensationControlType", "Condensation Control Type"},
{ OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CondensationControlDewpointOffset, "CondensationControlDewpointOffset", "Condensation Control Dewpoint Offset"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields> OptionalOS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_COOLING_LOWTEMPERATURERADIANT_CONSTANTFLOW_FIELDENUMS_HXX
