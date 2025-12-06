/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_ELECTRICLOADCENTER_STORAGE_LIIONNMCBATTERY_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ELECTRICLOADCENTER_STORAGE_LIIONNMCBATTERY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields
 *  \brief Enumeration of OS:ElectricLoadCenter:Storage:LiIonNMCBattery's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields, )
#else
class OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields: public ::EnumBase<OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, ZoneName, RadiativeFraction, LifetimeModel, NumberofCellsinSeries, NumberofStringsinParallel, InitialFractionalStateofCharge, DCtoDCChargingEfficiency, BatteryMass, BatterySurfaceArea, BatterySpecificHeatCapacity, HeatTransferCoefficientBetweenBatteryandAmbient, FullyChargedCellVoltage, CellVoltageatEndofExponentialZone, CellVoltageatEndofNominalZone, DefaultNominalCellVoltage, FullyChargedCellCapacity, FractionofCellCapacityRemovedattheEndofExponentialZone, FractionofCellCapacityRemovedattheEndofNominalZone, ChargeRateatWhichVoltagevsCapacityCurveWasGenerated, BatteryCellInternalElectricalResistance,   };
  OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields()
   : EnumBase<OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields>(Handle) {} 
  OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields(const std::string &t_name) 
   : EnumBase<OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields>(t_name) {} 
  OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields(int t_value) 
   : EnumBase<OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields>;
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
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::Handle, "Handle", "Handle"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::Name, "Name", "Name"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::ZoneName, "ZoneName", "Zone Name"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::RadiativeFraction, "RadiativeFraction", "Radiative Fraction"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::LifetimeModel, "LifetimeModel", "Lifetime Model"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::NumberofCellsinSeries, "NumberofCellsinSeries", "Number of Cells in Series"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::NumberofStringsinParallel, "NumberofStringsinParallel", "Number of Strings in Parallel"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::InitialFractionalStateofCharge, "InitialFractionalStateofCharge", "Initial Fractional State of Charge"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::DCtoDCChargingEfficiency, "DCtoDCChargingEfficiency", "DC to DC Charging Efficiency"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::BatteryMass, "BatteryMass", "Battery Mass"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::BatterySurfaceArea, "BatterySurfaceArea", "Battery Surface Area"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::BatterySpecificHeatCapacity, "BatterySpecificHeatCapacity", "Battery Specific Heat Capacity"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::HeatTransferCoefficientBetweenBatteryandAmbient, "HeatTransferCoefficientBetweenBatteryandAmbient", "Heat Transfer Coefficient Between Battery and Ambient"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::FullyChargedCellVoltage, "FullyChargedCellVoltage", "Fully Charged Cell Voltage"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::CellVoltageatEndofExponentialZone, "CellVoltageatEndofExponentialZone", "Cell Voltage at End of Exponential Zone"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::CellVoltageatEndofNominalZone, "CellVoltageatEndofNominalZone", "Cell Voltage at End of Nominal Zone"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::DefaultNominalCellVoltage, "DefaultNominalCellVoltage", "Default Nominal Cell Voltage"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::FullyChargedCellCapacity, "FullyChargedCellCapacity", "Fully Charged Cell Capacity"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::FractionofCellCapacityRemovedattheEndofExponentialZone, "FractionofCellCapacityRemovedattheEndofExponentialZone", "Fraction of Cell Capacity Removed at the End of Exponential Zone"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::FractionofCellCapacityRemovedattheEndofNominalZone, "FractionofCellCapacityRemovedattheEndofNominalZone", "Fraction of Cell Capacity Removed at the End of Nominal Zone"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::ChargeRateatWhichVoltagevsCapacityCurveWasGenerated, "ChargeRateatWhichVoltagevsCapacityCurveWasGenerated", "Charge Rate at Which Voltage vs Capacity Curve Was Generated"},
{ OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields::BatteryCellInternalElectricalResistance, "BatteryCellInternalElectricalResistance", "Battery Cell Internal Electrical Resistance"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields> OptionalOS_ElectricLoadCenter_Storage_LiIonNMCBatteryFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ELECTRICLOADCENTER_STORAGE_LIIONNMCBATTERY_FIELDENUMS_HXX
