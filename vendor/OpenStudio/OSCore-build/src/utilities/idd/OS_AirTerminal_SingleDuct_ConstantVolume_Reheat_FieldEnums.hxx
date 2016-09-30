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

#ifndef UTILITIES_IDD_OS_AIRTERMINAL_SINGLEDUCT_CONSTANTVOLUME_REHEAT_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRTERMINAL_SINGLEDUCT_CONSTANTVOLUME_REHEAT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields
 *  \brief Enumeration of OS:AirTerminal:SingleDuct:ConstantVolume:Reheat's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields, )
#else
class OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields: public ::EnumBase<OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, AirOutletNodeName, AirInletNodeName, MaximumAirFlowRate, ReheatCoilName, MaximumHotWaterorSteamFlowRate, MinimumHotWaterorSteamFlowRate, ConvergenceTolerance, MaximumReheatAirTemperature,   };
  OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields()
   : EnumBase<OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields>(Handle) {} 
  OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields(const std::string &t_name) 
   : EnumBase<OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields>(t_name) {} 
  OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields(int t_value) 
   : EnumBase<OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields>::value()); }
   private:
    friend class EnumBase<OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields>;
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
{ OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields::Handle, "Handle", "Handle"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields::Name, "Name", "Name"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, "MaximumAirFlowRate", "Maximum Air Flow Rate"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, "ReheatCoilName", "Reheat Coil Name"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate, "MaximumHotWaterorSteamFlowRate", "Maximum Hot Water or Steam Flow Rate"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MinimumHotWaterorSteamFlowRate, "MinimumHotWaterorSteamFlowRate", "Minimum Hot Water or Steam Flow Rate"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ConvergenceTolerance, "ConvergenceTolerance", "Convergence Tolerance"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumReheatAirTemperature, "MaximumReheatAirTemperature", "Maximum Reheat Air Temperature"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields> OptionalOS_AirTerminal_SingleDuct_ConstantVolume_ReheatFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRTERMINAL_SINGLEDUCT_CONSTANTVOLUME_REHEAT_FIELDENUMS_HXX
