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

#ifndef UTILITIES_IDD_OS_REFRIGERATION_WALKIN_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_REFRIGERATION_WALKIN_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Refrigeration_WalkInFields
 *  \brief Enumeration of OS:Refrigeration:WalkIn's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Refrigeration_WalkInFields, )
#else
class OS_Refrigeration_WalkInFields: public ::EnumBase<OS_Refrigeration_WalkInFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, RatedCoilCoolingCapacity, OperatingTemperature, RatedCoolingSourceTemperature, RatedTotalHeatingPower, HeatingPowerScheduleName, RatedCoolingCoilFanPower, RatedCirculationFanPower, RatedTotalLightingPower, LightingScheduleName, DefrostType, DefrostControlType, DefrostScheduleName, DefrostDripDownScheduleName, DefrostPower, TemperatureTerminationDefrostFractiontoIce, RestockingScheduleName, AverageRefrigerantChargeInventory, InsulatedFloorSurfaceArea, InsulatedFloorUValue, WalkInDefrostCycleParametersName,   };
  OS_Refrigeration_WalkInFields()
   : EnumBase<OS_Refrigeration_WalkInFields>(Handle) {} 
  OS_Refrigeration_WalkInFields(const std::string &t_name) 
   : EnumBase<OS_Refrigeration_WalkInFields>(t_name) {} 
  OS_Refrigeration_WalkInFields(int t_value) 
   : EnumBase<OS_Refrigeration_WalkInFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Refrigeration_WalkInFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Refrigeration_WalkInFields>::value()); }
   private:
    friend class EnumBase<OS_Refrigeration_WalkInFields>;
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
{ OS_Refrigeration_WalkInFields::Handle, "Handle", "Handle"},
{ OS_Refrigeration_WalkInFields::Name, "Name", "Name"},
{ OS_Refrigeration_WalkInFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_Refrigeration_WalkInFields::RatedCoilCoolingCapacity, "RatedCoilCoolingCapacity", "Rated Coil Cooling Capacity"},
{ OS_Refrigeration_WalkInFields::OperatingTemperature, "OperatingTemperature", "Operating Temperature"},
{ OS_Refrigeration_WalkInFields::RatedCoolingSourceTemperature, "RatedCoolingSourceTemperature", "Rated Cooling Source Temperature"},
{ OS_Refrigeration_WalkInFields::RatedTotalHeatingPower, "RatedTotalHeatingPower", "Rated Total Heating Power"},
{ OS_Refrigeration_WalkInFields::HeatingPowerScheduleName, "HeatingPowerScheduleName", "Heating Power Schedule Name"},
{ OS_Refrigeration_WalkInFields::RatedCoolingCoilFanPower, "RatedCoolingCoilFanPower", "Rated Cooling Coil Fan Power"},
{ OS_Refrigeration_WalkInFields::RatedCirculationFanPower, "RatedCirculationFanPower", "Rated Circulation Fan Power"},
{ OS_Refrigeration_WalkInFields::RatedTotalLightingPower, "RatedTotalLightingPower", "Rated Total Lighting Power"},
{ OS_Refrigeration_WalkInFields::LightingScheduleName, "LightingScheduleName", "Lighting Schedule Name"},
{ OS_Refrigeration_WalkInFields::DefrostType, "DefrostType", "Defrost Type"},
{ OS_Refrigeration_WalkInFields::DefrostControlType, "DefrostControlType", "Defrost Control Type"},
{ OS_Refrigeration_WalkInFields::DefrostScheduleName, "DefrostScheduleName", "Defrost Schedule Name"},
{ OS_Refrigeration_WalkInFields::DefrostDripDownScheduleName, "DefrostDripDownScheduleName", "Defrost Drip-Down Schedule Name"},
{ OS_Refrigeration_WalkInFields::DefrostPower, "DefrostPower", "Defrost Power"},
{ OS_Refrigeration_WalkInFields::TemperatureTerminationDefrostFractiontoIce, "TemperatureTerminationDefrostFractiontoIce", "Temperature Termination Defrost Fraction to Ice"},
{ OS_Refrigeration_WalkInFields::RestockingScheduleName, "RestockingScheduleName", "Restocking Schedule Name"},
{ OS_Refrigeration_WalkInFields::AverageRefrigerantChargeInventory, "AverageRefrigerantChargeInventory", "Average Refrigerant Charge Inventory"},
{ OS_Refrigeration_WalkInFields::InsulatedFloorSurfaceArea, "InsulatedFloorSurfaceArea", "Insulated Floor Surface Area"},
{ OS_Refrigeration_WalkInFields::InsulatedFloorUValue, "InsulatedFloorUValue", "Insulated Floor U-Value"},
{ OS_Refrigeration_WalkInFields::WalkInDefrostCycleParametersName, "WalkInDefrostCycleParametersName", "WalkIn Defrost Cycle Parameters Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Refrigeration_WalkInFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Refrigeration_WalkInFields> OptionalOS_Refrigeration_WalkInFields ;
#endif

/** \class OS_Refrigeration_WalkInExtensibleFields
 *  \brief Enumeration of OS:Refrigeration:WalkIn's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Refrigeration_WalkInExtensibleFields, )
#else
class OS_Refrigeration_WalkInExtensibleFields: public ::EnumBase<OS_Refrigeration_WalkInExtensibleFields> {
 public: 
  enum domain 
  {
WalkInZoneBoundary,   };
  OS_Refrigeration_WalkInExtensibleFields()
   : EnumBase<OS_Refrigeration_WalkInExtensibleFields>(WalkInZoneBoundary) {} 
  OS_Refrigeration_WalkInExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Refrigeration_WalkInExtensibleFields>(t_name) {} 
  OS_Refrigeration_WalkInExtensibleFields(int t_value) 
   : EnumBase<OS_Refrigeration_WalkInExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Refrigeration_WalkInExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Refrigeration_WalkInExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_Refrigeration_WalkInExtensibleFields>;
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
{ OS_Refrigeration_WalkInExtensibleFields::WalkInZoneBoundary, "WalkInZoneBoundary", "WalkIn Zone Boundary"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Refrigeration_WalkInExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Refrigeration_WalkInExtensibleFields> OptionalOS_Refrigeration_WalkInExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_REFRIGERATION_WALKIN_FIELDENUMS_HXX
