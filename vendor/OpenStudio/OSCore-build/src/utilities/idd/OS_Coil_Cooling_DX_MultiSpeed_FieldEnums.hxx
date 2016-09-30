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

#ifndef UTILITIES_IDD_OS_COIL_COOLING_DX_MULTISPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_COOLING_DX_MULTISPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_Cooling_DX_MultiSpeedFields
 *  \brief Enumeration of OS:Coil:Cooling:DX:MultiSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_Cooling_DX_MultiSpeedFields, )
#else
class OS_Coil_Cooling_DX_MultiSpeedFields: public ::EnumBase<OS_Coil_Cooling_DX_MultiSpeedFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilitySchedule, AirInletNode, AirOutletNode, CondenserAirInletNode, CondenserType, SupplyWaterStorageTank, CondensateCollectionWaterStorageTank, ApplyPartLoadFractiontoSpeedsGreaterthan1, ApplyLatentDegradationtoSpeedsGreaterthan1, CrankcaseHeaterCapacity, MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingSchedule, FuelType,   };
  OS_Coil_Cooling_DX_MultiSpeedFields()
   : EnumBase<OS_Coil_Cooling_DX_MultiSpeedFields>(Handle) {} 
  OS_Coil_Cooling_DX_MultiSpeedFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Cooling_DX_MultiSpeedFields>(t_name) {} 
  OS_Coil_Cooling_DX_MultiSpeedFields(int t_value) 
   : EnumBase<OS_Coil_Cooling_DX_MultiSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Cooling_DX_MultiSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Cooling_DX_MultiSpeedFields>::value()); }
   private:
    friend class EnumBase<OS_Coil_Cooling_DX_MultiSpeedFields>;
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
{ OS_Coil_Cooling_DX_MultiSpeedFields::Handle, "Handle", "Handle"},
{ OS_Coil_Cooling_DX_MultiSpeedFields::Name, "Name", "Name"},
{ OS_Coil_Cooling_DX_MultiSpeedFields::AvailabilitySchedule, "AvailabilitySchedule", "Availability Schedule"},
{ OS_Coil_Cooling_DX_MultiSpeedFields::AirInletNode, "AirInletNode", "Air Inlet Node"},
{ OS_Coil_Cooling_DX_MultiSpeedFields::AirOutletNode, "AirOutletNode", "Air Outlet Node"},
{ OS_Coil_Cooling_DX_MultiSpeedFields::CondenserAirInletNode, "CondenserAirInletNode", "Condenser Air Inlet Node"},
{ OS_Coil_Cooling_DX_MultiSpeedFields::CondenserType, "CondenserType", "Condenser Type"},
{ OS_Coil_Cooling_DX_MultiSpeedFields::SupplyWaterStorageTank, "SupplyWaterStorageTank", "Supply Water Storage Tank"},
{ OS_Coil_Cooling_DX_MultiSpeedFields::CondensateCollectionWaterStorageTank, "CondensateCollectionWaterStorageTank", "Condensate Collection Water Storage Tank"},
{ OS_Coil_Cooling_DX_MultiSpeedFields::ApplyPartLoadFractiontoSpeedsGreaterthan1, "ApplyPartLoadFractiontoSpeedsGreaterthan1", "Apply Part Load Fraction to Speeds Greater than 1"},
{ OS_Coil_Cooling_DX_MultiSpeedFields::ApplyLatentDegradationtoSpeedsGreaterthan1, "ApplyLatentDegradationtoSpeedsGreaterthan1", "Apply Latent Degradation to Speeds Greater than 1"},
{ OS_Coil_Cooling_DX_MultiSpeedFields::CrankcaseHeaterCapacity, "CrankcaseHeaterCapacity", "Crankcase Heater Capacity"},
{ OS_Coil_Cooling_DX_MultiSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, "MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Crankcase Heater Operation"},
{ OS_Coil_Cooling_DX_MultiSpeedFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ OS_Coil_Cooling_DX_MultiSpeedFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ OS_Coil_Cooling_DX_MultiSpeedFields::BasinHeaterOperatingSchedule, "BasinHeaterOperatingSchedule", "Basin Heater Operating Schedule"},
{ OS_Coil_Cooling_DX_MultiSpeedFields::FuelType, "FuelType", "Fuel Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Cooling_DX_MultiSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Cooling_DX_MultiSpeedFields> OptionalOS_Coil_Cooling_DX_MultiSpeedFields ;
#endif

/** \class OS_Coil_Cooling_DX_MultiSpeedExtensibleFields
 *  \brief Enumeration of OS:Coil:Cooling:DX:MultiSpeed's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_Coil_Cooling_DX_MultiSpeedExtensibleFields, )
#else
class OS_Coil_Cooling_DX_MultiSpeedExtensibleFields: public ::EnumBase<OS_Coil_Cooling_DX_MultiSpeedExtensibleFields> {
 public: 
  enum domain 
  {
Stage,   };
  OS_Coil_Cooling_DX_MultiSpeedExtensibleFields()
   : EnumBase<OS_Coil_Cooling_DX_MultiSpeedExtensibleFields>(Stage) {} 
  OS_Coil_Cooling_DX_MultiSpeedExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Cooling_DX_MultiSpeedExtensibleFields>(t_name) {} 
  OS_Coil_Cooling_DX_MultiSpeedExtensibleFields(int t_value) 
   : EnumBase<OS_Coil_Cooling_DX_MultiSpeedExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Cooling_DX_MultiSpeedExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Cooling_DX_MultiSpeedExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_Coil_Cooling_DX_MultiSpeedExtensibleFields>;
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
{ OS_Coil_Cooling_DX_MultiSpeedExtensibleFields::Stage, "Stage", "Stage"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Cooling_DX_MultiSpeedExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Cooling_DX_MultiSpeedExtensibleFields> OptionalOS_Coil_Cooling_DX_MultiSpeedExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_COOLING_DX_MULTISPEED_FIELDENUMS_HXX
