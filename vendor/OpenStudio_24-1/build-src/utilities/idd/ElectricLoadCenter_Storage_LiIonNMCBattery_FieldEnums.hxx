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

#ifndef UTILITIES_IDD_ELECTRICLOADCENTER_STORAGE_LIIONNMCBATTERY_FIELDENUMS_HXX
#define UTILITIES_IDD_ELECTRICLOADCENTER_STORAGE_LIIONNMCBATTERY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ElectricLoadCenter_Storage_LiIonNMCBatteryFields
 *  \brief Enumeration of ElectricLoadCenter:Storage:LiIonNMCBattery's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ElectricLoadCenter_Storage_LiIonNMCBatteryFields, )
#else
class ElectricLoadCenter_Storage_LiIonNMCBatteryFields: public ::EnumBase<ElectricLoadCenter_Storage_LiIonNMCBatteryFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, ZoneName, RadiativeFraction, LifetimeModel, NumberofCellsinSeries, NumberofStringsinParallel, InitialFractionalStateofCharge, DCtoDCChargingEfficiency, BatteryMass, BatterySurfaceArea, BatterySpecificHeatCapacity, HeatTransferCoefficientBetweenBatteryandAmbient, FullyChargedCellVoltage, CellVoltageatEndofExponentialZone, CellVoltageatEndofNominalZone, DefaultNominalCellVoltage, FullyChargedCellCapacity, FractionofCellCapacityRemovedattheEndofExponentialZone, FractionofCellCapacityRemovedattheEndofNominalZone, ChargeRateatWhichVoltagevsCapacityCurveWasGenerated, BatteryCellInternalElectricalResistance,   };
  ElectricLoadCenter_Storage_LiIonNMCBatteryFields()
   : EnumBase<ElectricLoadCenter_Storage_LiIonNMCBatteryFields>(Name) {} 
  ElectricLoadCenter_Storage_LiIonNMCBatteryFields(const std::string &t_name) 
   : EnumBase<ElectricLoadCenter_Storage_LiIonNMCBatteryFields>(t_name) {} 
  ElectricLoadCenter_Storage_LiIonNMCBatteryFields(int t_value) 
   : EnumBase<ElectricLoadCenter_Storage_LiIonNMCBatteryFields>(t_value) {} 
  static std::string enumName() 
  { return "ElectricLoadCenter_Storage_LiIonNMCBatteryFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ElectricLoadCenter_Storage_LiIonNMCBatteryFields>::value()); }
   private:
    friend class EnumBase<ElectricLoadCenter_Storage_LiIonNMCBatteryFields>;
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
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::Name, "Name", "Name"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::ZoneName, "ZoneName", "Zone Name"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::RadiativeFraction, "RadiativeFraction", "Radiative Fraction"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::LifetimeModel, "LifetimeModel", "Lifetime Model"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::NumberofCellsinSeries, "NumberofCellsinSeries", "Number of Cells in Series"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::NumberofStringsinParallel, "NumberofStringsinParallel", "Number of Strings in Parallel"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::InitialFractionalStateofCharge, "InitialFractionalStateofCharge", "Initial Fractional State of Charge"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::DCtoDCChargingEfficiency, "DCtoDCChargingEfficiency", "DC to DC Charging Efficiency"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::BatteryMass, "BatteryMass", "Battery Mass"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::BatterySurfaceArea, "BatterySurfaceArea", "Battery Surface Area"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::BatterySpecificHeatCapacity, "BatterySpecificHeatCapacity", "Battery Specific Heat Capacity"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::HeatTransferCoefficientBetweenBatteryandAmbient, "HeatTransferCoefficientBetweenBatteryandAmbient", "Heat Transfer Coefficient Between Battery and Ambient"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::FullyChargedCellVoltage, "FullyChargedCellVoltage", "Fully Charged Cell Voltage"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::CellVoltageatEndofExponentialZone, "CellVoltageatEndofExponentialZone", "Cell Voltage at End of Exponential Zone"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::CellVoltageatEndofNominalZone, "CellVoltageatEndofNominalZone", "Cell Voltage at End of Nominal Zone"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::DefaultNominalCellVoltage, "DefaultNominalCellVoltage", "Default Nominal Cell Voltage"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::FullyChargedCellCapacity, "FullyChargedCellCapacity", "Fully Charged Cell Capacity"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::FractionofCellCapacityRemovedattheEndofExponentialZone, "FractionofCellCapacityRemovedattheEndofExponentialZone", "Fraction of Cell Capacity Removed at the End of Exponential Zone"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::FractionofCellCapacityRemovedattheEndofNominalZone, "FractionofCellCapacityRemovedattheEndofNominalZone", "Fraction of Cell Capacity Removed at the End of Nominal Zone"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::ChargeRateatWhichVoltagevsCapacityCurveWasGenerated, "ChargeRateatWhichVoltagevsCapacityCurveWasGenerated", "Charge Rate at Which Voltage vs Capacity Curve Was Generated"},
{ ElectricLoadCenter_Storage_LiIonNMCBatteryFields::BatteryCellInternalElectricalResistance, "BatteryCellInternalElectricalResistance", "Battery Cell Internal Electrical Resistance"},
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
  inline std::ostream &operator<<(std::ostream &os, const ElectricLoadCenter_Storage_LiIonNMCBatteryFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ElectricLoadCenter_Storage_LiIonNMCBatteryFields> OptionalElectricLoadCenter_Storage_LiIonNMCBatteryFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ELECTRICLOADCENTER_STORAGE_LIIONNMCBATTERY_FIELDENUMS_HXX
