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

#ifndef UTILITIES_IDD_AIRTERMINAL_SINGLEDUCT_SERIESPIU_REHEAT_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRTERMINAL_SINGLEDUCT_SERIESPIU_REHEAT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirTerminal_SingleDuct_SeriesPIU_ReheatFields
 *  \brief Enumeration of AirTerminal:SingleDuct:SeriesPIU:Reheat's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirTerminal_SingleDuct_SeriesPIU_ReheatFields, )
#else
class AirTerminal_SingleDuct_SeriesPIU_ReheatFields: public ::EnumBase<AirTerminal_SingleDuct_SeriesPIU_ReheatFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, MaximumAirFlowRate, MaximumPrimaryAirFlowRate, MinimumPrimaryAirFlowFraction, SupplyAirInletNodeName, SecondaryAirInletNodeName, OutletNodeName, ReheatCoilAirInletNodeName, ZoneMixerName, FanName, ReheatCoilObjectType, ReheatCoilName, MaximumHotWaterorSteamFlowRate, MinimumHotWaterorSteamFlowRate, ConvergenceTolerance,   };
  AirTerminal_SingleDuct_SeriesPIU_ReheatFields()
   : EnumBase<AirTerminal_SingleDuct_SeriesPIU_ReheatFields>(Name) {} 
  AirTerminal_SingleDuct_SeriesPIU_ReheatFields(const std::string &t_name) 
   : EnumBase<AirTerminal_SingleDuct_SeriesPIU_ReheatFields>(t_name) {} 
  AirTerminal_SingleDuct_SeriesPIU_ReheatFields(int t_value) 
   : EnumBase<AirTerminal_SingleDuct_SeriesPIU_ReheatFields>(t_value) {} 
  static std::string enumName() 
  { return "AirTerminal_SingleDuct_SeriesPIU_ReheatFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirTerminal_SingleDuct_SeriesPIU_ReheatFields>::value()); }
   private:
    friend class EnumBase<AirTerminal_SingleDuct_SeriesPIU_ReheatFields>;
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
{ AirTerminal_SingleDuct_SeriesPIU_ReheatFields::Name, "Name", "Name"},
{ AirTerminal_SingleDuct_SeriesPIU_ReheatFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumAirFlowRate, "MaximumAirFlowRate", "Maximum Air Flow Rate"},
{ AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumPrimaryAirFlowRate, "MaximumPrimaryAirFlowRate", "Maximum Primary Air Flow Rate"},
{ AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MinimumPrimaryAirFlowFraction, "MinimumPrimaryAirFlowFraction", "Minimum Primary Air Flow Fraction"},
{ AirTerminal_SingleDuct_SeriesPIU_ReheatFields::SupplyAirInletNodeName, "SupplyAirInletNodeName", "Supply Air Inlet Node Name"},
{ AirTerminal_SingleDuct_SeriesPIU_ReheatFields::SecondaryAirInletNodeName, "SecondaryAirInletNodeName", "Secondary Air Inlet Node Name"},
{ AirTerminal_SingleDuct_SeriesPIU_ReheatFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilAirInletNodeName, "ReheatCoilAirInletNodeName", "Reheat Coil Air Inlet Node Name"},
{ AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ZoneMixerName, "ZoneMixerName", "Zone Mixer Name"},
{ AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanName, "FanName", "Fan Name"},
{ AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilObjectType, "ReheatCoilObjectType", "Reheat Coil Object Type"},
{ AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName, "ReheatCoilName", "Reheat Coil Name"},
{ AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, "MaximumHotWaterorSteamFlowRate", "Maximum Hot Water or Steam Flow Rate"},
{ AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MinimumHotWaterorSteamFlowRate, "MinimumHotWaterorSteamFlowRate", "Minimum Hot Water or Steam Flow Rate"},
{ AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ConvergenceTolerance, "ConvergenceTolerance", "Convergence Tolerance"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirTerminal_SingleDuct_SeriesPIU_ReheatFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirTerminal_SingleDuct_SeriesPIU_ReheatFields> OptionalAirTerminal_SingleDuct_SeriesPIU_ReheatFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRTERMINAL_SINGLEDUCT_SERIESPIU_REHEAT_FIELDENUMS_HXX
