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

#ifndef UTILITIES_IDD_OS_COILSYSTEM_COOLING_WATER_HEATEXCHANGERASSISTED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COILSYSTEM_COOLING_WATER_HEATEXCHANGERASSISTED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields
 *  \brief Enumeration of OS:CoilSystem:Cooling:Water:HeatExchangerAssisted's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields, )
#else
class OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields: public ::EnumBase<OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields> {
 public: 
  enum domain 
  {
Handle, Name, AirInletNodeName, AirOutletNodeName, HeatExchanger, CoolingCoil,   };
  OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields()
   : EnumBase<OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields>(Handle) {} 
  OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields(const std::string &t_name) 
   : EnumBase<OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields>(t_name) {} 
  OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields(int t_value) 
   : EnumBase<OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields>::value()); }
   private:
    friend class EnumBase<OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields>;
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
{ OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields::Handle, "Handle", "Handle"},
{ OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields::Name, "Name", "Name"},
{ OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields::HeatExchanger, "HeatExchanger", "Heat Exchanger"},
{ OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoil, "CoolingCoil", "Cooling Coil"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields> OptionalOS_CoilSystem_Cooling_Water_HeatExchangerAssistedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COILSYSTEM_COOLING_WATER_HEATEXCHANGERASSISTED_FIELDENUMS_HXX
