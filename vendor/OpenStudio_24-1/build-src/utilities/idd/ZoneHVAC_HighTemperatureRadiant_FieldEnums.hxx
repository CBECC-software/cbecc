/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_ZONEHVAC_HIGHTEMPERATURERADIANT_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_HIGHTEMPERATURERADIANT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_HighTemperatureRadiantFields
 *  \brief Enumeration of ZoneHVAC:HighTemperatureRadiant's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_HighTemperatureRadiantFields, )
#else
class ZoneHVAC_HighTemperatureRadiantFields: public ::EnumBase<ZoneHVAC_HighTemperatureRadiantFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, ZoneName, HeatingDesignCapacityMethod, HeatingDesignCapacity, HeatingDesignCapacityPerFloorArea, FractionofAutosizedHeatingDesignCapacity, FuelType, CombustionEfficiency, FractionofInputConvertedtoRadiantEnergy, FractionofInputConvertedtoLatentEnergy, FractionofInputthatIsLost, TemperatureControlType, HeatingThrottlingRange, HeatingSetpointTemperatureScheduleName, FractionofRadiantEnergyIncidentonPeople,   };
  ZoneHVAC_HighTemperatureRadiantFields()
   : EnumBase<ZoneHVAC_HighTemperatureRadiantFields>(Name) {} 
  ZoneHVAC_HighTemperatureRadiantFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_HighTemperatureRadiantFields>(t_name) {} 
  ZoneHVAC_HighTemperatureRadiantFields(int t_value) 
   : EnumBase<ZoneHVAC_HighTemperatureRadiantFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_HighTemperatureRadiantFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_HighTemperatureRadiantFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_HighTemperatureRadiantFields>;
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
{ ZoneHVAC_HighTemperatureRadiantFields::Name, "Name", "Name"},
{ ZoneHVAC_HighTemperatureRadiantFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_HighTemperatureRadiantFields::ZoneName, "ZoneName", "Zone Name"},
{ ZoneHVAC_HighTemperatureRadiantFields::HeatingDesignCapacityMethod, "HeatingDesignCapacityMethod", "Heating Design Capacity Method"},
{ ZoneHVAC_HighTemperatureRadiantFields::HeatingDesignCapacity, "HeatingDesignCapacity", "Heating Design Capacity"},
{ ZoneHVAC_HighTemperatureRadiantFields::HeatingDesignCapacityPerFloorArea, "HeatingDesignCapacityPerFloorArea", "Heating Design Capacity Per Floor Area"},
{ ZoneHVAC_HighTemperatureRadiantFields::FractionofAutosizedHeatingDesignCapacity, "FractionofAutosizedHeatingDesignCapacity", "Fraction of Autosized Heating Design Capacity"},
{ ZoneHVAC_HighTemperatureRadiantFields::FuelType, "FuelType", "Fuel Type"},
{ ZoneHVAC_HighTemperatureRadiantFields::CombustionEfficiency, "CombustionEfficiency", "Combustion Efficiency"},
{ ZoneHVAC_HighTemperatureRadiantFields::FractionofInputConvertedtoRadiantEnergy, "FractionofInputConvertedtoRadiantEnergy", "Fraction of Input Converted to Radiant Energy"},
{ ZoneHVAC_HighTemperatureRadiantFields::FractionofInputConvertedtoLatentEnergy, "FractionofInputConvertedtoLatentEnergy", "Fraction of Input Converted to Latent Energy"},
{ ZoneHVAC_HighTemperatureRadiantFields::FractionofInputthatIsLost, "FractionofInputthatIsLost", "Fraction of Input that Is Lost"},
{ ZoneHVAC_HighTemperatureRadiantFields::TemperatureControlType, "TemperatureControlType", "Temperature Control Type"},
{ ZoneHVAC_HighTemperatureRadiantFields::HeatingThrottlingRange, "HeatingThrottlingRange", "Heating Throttling Range"},
{ ZoneHVAC_HighTemperatureRadiantFields::HeatingSetpointTemperatureScheduleName, "HeatingSetpointTemperatureScheduleName", "Heating Setpoint Temperature Schedule Name"},
{ ZoneHVAC_HighTemperatureRadiantFields::FractionofRadiantEnergyIncidentonPeople, "FractionofRadiantEnergyIncidentonPeople", "Fraction of Radiant Energy Incident on People"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_HighTemperatureRadiantFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_HighTemperatureRadiantFields> OptionalZoneHVAC_HighTemperatureRadiantFields ;
#endif

/** \class ZoneHVAC_HighTemperatureRadiantExtensibleFields
 *  \brief Enumeration of ZoneHVAC:HighTemperatureRadiant's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(ZoneHVAC_HighTemperatureRadiantExtensibleFields, )
#else
class ZoneHVAC_HighTemperatureRadiantExtensibleFields: public ::EnumBase<ZoneHVAC_HighTemperatureRadiantExtensibleFields> {
 public: 
  enum domain 
  {
SurfaceName, FractionofRadiantEnergytoSurface,   };
  ZoneHVAC_HighTemperatureRadiantExtensibleFields()
   : EnumBase<ZoneHVAC_HighTemperatureRadiantExtensibleFields>(SurfaceName) {} 
  ZoneHVAC_HighTemperatureRadiantExtensibleFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_HighTemperatureRadiantExtensibleFields>(t_name) {} 
  ZoneHVAC_HighTemperatureRadiantExtensibleFields(int t_value) 
   : EnumBase<ZoneHVAC_HighTemperatureRadiantExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_HighTemperatureRadiantExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_HighTemperatureRadiantExtensibleFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_HighTemperatureRadiantExtensibleFields>;
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
{ ZoneHVAC_HighTemperatureRadiantExtensibleFields::SurfaceName, "SurfaceName", "Surface Name"},
{ ZoneHVAC_HighTemperatureRadiantExtensibleFields::FractionofRadiantEnergytoSurface, "FractionofRadiantEnergytoSurface", "Fraction of Radiant Energy to Surface"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_HighTemperatureRadiantExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_HighTemperatureRadiantExtensibleFields> OptionalZoneHVAC_HighTemperatureRadiantExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_HIGHTEMPERATURERADIANT_FIELDENUMS_HXX
