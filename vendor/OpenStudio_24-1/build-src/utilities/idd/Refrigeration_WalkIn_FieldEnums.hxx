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

#ifndef UTILITIES_IDD_REFRIGERATION_WALKIN_FIELDENUMS_HXX
#define UTILITIES_IDD_REFRIGERATION_WALKIN_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Refrigeration_WalkInFields
 *  \brief Enumeration of Refrigeration:WalkIn's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Refrigeration_WalkInFields, )
#else
class Refrigeration_WalkInFields: public ::EnumBase<Refrigeration_WalkInFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, RatedCoilCoolingCapacity, OperatingTemperature, RatedCoolingSourceTemperature, RatedTotalHeatingPower, HeatingPowerScheduleName, RatedCoolingCoilFanPower, RatedCirculationFanPower, RatedTotalLightingPower, LightingScheduleName, DefrostType, DefrostControlType, DefrostScheduleName, DefrostDripDownScheduleName, DefrostPower, TemperatureTerminationDefrostFractiontoIce, RestockingScheduleName, AverageRefrigerantChargeInventory, InsulatedFloorSurfaceArea, InsulatedFloorUValue,   };
  Refrigeration_WalkInFields()
   : EnumBase<Refrigeration_WalkInFields>(Name) {} 
  Refrigeration_WalkInFields(const std::string &t_name) 
   : EnumBase<Refrigeration_WalkInFields>(t_name) {} 
  Refrigeration_WalkInFields(int t_value) 
   : EnumBase<Refrigeration_WalkInFields>(t_value) {} 
  static std::string enumName() 
  { return "Refrigeration_WalkInFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Refrigeration_WalkInFields>::value()); }
   private:
    friend class EnumBase<Refrigeration_WalkInFields>;
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
{ Refrigeration_WalkInFields::Name, "Name", "Name"},
{ Refrigeration_WalkInFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Refrigeration_WalkInFields::RatedCoilCoolingCapacity, "RatedCoilCoolingCapacity", "Rated Coil Cooling Capacity"},
{ Refrigeration_WalkInFields::OperatingTemperature, "OperatingTemperature", "Operating Temperature"},
{ Refrigeration_WalkInFields::RatedCoolingSourceTemperature, "RatedCoolingSourceTemperature", "Rated Cooling Source Temperature"},
{ Refrigeration_WalkInFields::RatedTotalHeatingPower, "RatedTotalHeatingPower", "Rated Total Heating Power"},
{ Refrigeration_WalkInFields::HeatingPowerScheduleName, "HeatingPowerScheduleName", "Heating Power Schedule Name"},
{ Refrigeration_WalkInFields::RatedCoolingCoilFanPower, "RatedCoolingCoilFanPower", "Rated Cooling Coil Fan Power"},
{ Refrigeration_WalkInFields::RatedCirculationFanPower, "RatedCirculationFanPower", "Rated Circulation Fan Power"},
{ Refrigeration_WalkInFields::RatedTotalLightingPower, "RatedTotalLightingPower", "Rated Total Lighting Power"},
{ Refrigeration_WalkInFields::LightingScheduleName, "LightingScheduleName", "Lighting Schedule Name"},
{ Refrigeration_WalkInFields::DefrostType, "DefrostType", "Defrost Type"},
{ Refrigeration_WalkInFields::DefrostControlType, "DefrostControlType", "Defrost Control Type"},
{ Refrigeration_WalkInFields::DefrostScheduleName, "DefrostScheduleName", "Defrost Schedule Name"},
{ Refrigeration_WalkInFields::DefrostDripDownScheduleName, "DefrostDripDownScheduleName", "Defrost Drip-Down Schedule Name"},
{ Refrigeration_WalkInFields::DefrostPower, "DefrostPower", "Defrost Power"},
{ Refrigeration_WalkInFields::TemperatureTerminationDefrostFractiontoIce, "TemperatureTerminationDefrostFractiontoIce", "Temperature Termination Defrost Fraction to Ice"},
{ Refrigeration_WalkInFields::RestockingScheduleName, "RestockingScheduleName", "Restocking Schedule Name"},
{ Refrigeration_WalkInFields::AverageRefrigerantChargeInventory, "AverageRefrigerantChargeInventory", "Average Refrigerant Charge Inventory"},
{ Refrigeration_WalkInFields::InsulatedFloorSurfaceArea, "InsulatedFloorSurfaceArea", "Insulated Floor Surface Area"},
{ Refrigeration_WalkInFields::InsulatedFloorUValue, "InsulatedFloorUValue", "Insulated Floor U-Value"},
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
  inline std::ostream &operator<<(std::ostream &os, const Refrigeration_WalkInFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Refrigeration_WalkInFields> OptionalRefrigeration_WalkInFields ;
#endif

/** \class Refrigeration_WalkInExtensibleFields
 *  \brief Enumeration of Refrigeration:WalkIn's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Refrigeration_WalkInExtensibleFields, )
#else
class Refrigeration_WalkInExtensibleFields: public ::EnumBase<Refrigeration_WalkInExtensibleFields> {
 public: 
  enum domain 
  {
ZoneName, TotalInsulatedSurfaceAreaFacingZone, InsulatedSurfaceUValueFacingZone, AreaofGlassReachInDoorsFacingZone, HeightofGlassReachInDoorsFacingZone, GlassReachInDoorUValueFacingZone, GlassReachInDoorOpeningScheduleNameFacingZone, AreaofStockingDoorsFacingZone, HeightofStockingDoorsFacingZone, StockingDoorUValueFacingZone, StockingDoorOpeningScheduleNameFacingZone, StockingDoorOpeningProtectionTypeFacingZone,   };
  Refrigeration_WalkInExtensibleFields()
   : EnumBase<Refrigeration_WalkInExtensibleFields>(ZoneName) {} 
  Refrigeration_WalkInExtensibleFields(const std::string &t_name) 
   : EnumBase<Refrigeration_WalkInExtensibleFields>(t_name) {} 
  Refrigeration_WalkInExtensibleFields(int t_value) 
   : EnumBase<Refrigeration_WalkInExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Refrigeration_WalkInExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Refrigeration_WalkInExtensibleFields>::value()); }
   private:
    friend class EnumBase<Refrigeration_WalkInExtensibleFields>;
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
{ Refrigeration_WalkInExtensibleFields::ZoneName, "ZoneName", "Zone Name"},
{ Refrigeration_WalkInExtensibleFields::TotalInsulatedSurfaceAreaFacingZone, "TotalInsulatedSurfaceAreaFacingZone", "Total Insulated Surface Area Facing Zone"},
{ Refrigeration_WalkInExtensibleFields::InsulatedSurfaceUValueFacingZone, "InsulatedSurfaceUValueFacingZone", "Insulated Surface U-Value Facing Zone"},
{ Refrigeration_WalkInExtensibleFields::AreaofGlassReachInDoorsFacingZone, "AreaofGlassReachInDoorsFacingZone", "Area of Glass Reach In Doors Facing Zone"},
{ Refrigeration_WalkInExtensibleFields::HeightofGlassReachInDoorsFacingZone, "HeightofGlassReachInDoorsFacingZone", "Height of Glass Reach In Doors Facing Zone"},
{ Refrigeration_WalkInExtensibleFields::GlassReachInDoorUValueFacingZone, "GlassReachInDoorUValueFacingZone", "Glass Reach In Door U Value Facing Zone"},
{ Refrigeration_WalkInExtensibleFields::GlassReachInDoorOpeningScheduleNameFacingZone, "GlassReachInDoorOpeningScheduleNameFacingZone", "Glass Reach In Door Opening Schedule Name Facing Zone"},
{ Refrigeration_WalkInExtensibleFields::AreaofStockingDoorsFacingZone, "AreaofStockingDoorsFacingZone", "Area of Stocking Doors Facing Zone"},
{ Refrigeration_WalkInExtensibleFields::HeightofStockingDoorsFacingZone, "HeightofStockingDoorsFacingZone", "Height of Stocking Doors Facing Zone"},
{ Refrigeration_WalkInExtensibleFields::StockingDoorUValueFacingZone, "StockingDoorUValueFacingZone", "Stocking Door U Value Facing Zone"},
{ Refrigeration_WalkInExtensibleFields::StockingDoorOpeningScheduleNameFacingZone, "StockingDoorOpeningScheduleNameFacingZone", "Stocking Door Opening Schedule Name Facing Zone"},
{ Refrigeration_WalkInExtensibleFields::StockingDoorOpeningProtectionTypeFacingZone, "StockingDoorOpeningProtectionTypeFacingZone", "Stocking Door Opening Protection Type Facing Zone"},
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
  inline std::ostream &operator<<(std::ostream &os, const Refrigeration_WalkInExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Refrigeration_WalkInExtensibleFields> OptionalRefrigeration_WalkInExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_REFRIGERATION_WALKIN_FIELDENUMS_HXX
