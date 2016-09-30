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

#ifndef UTILITIES_IDD_ELECTRICLOADCENTER_DISTRIBUTION_FIELDENUMS_HXX
#define UTILITIES_IDD_ELECTRICLOADCENTER_DISTRIBUTION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ElectricLoadCenter_DistributionFields
 *  \brief Enumeration of ElectricLoadCenter:Distribution's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ElectricLoadCenter_DistributionFields, )
#else
class ElectricLoadCenter_DistributionFields: public ::EnumBase<ElectricLoadCenter_DistributionFields> {
 public: 
  enum domain 
  {
Name, GeneratorListName, GeneratorOperationSchemeType, GeneratorDemandLimitSchemePurchasedElectricDemandLimit, GeneratorTrackScheduleNameSchemeScheduleName, GeneratorTrackMeterSchemeMeterName, ElectricalBussType, InverterName, ElectricalStorageObjectName, TransformerObjectName, StorageOperationScheme, StorageControlTrackMeterName, StorageConverterObjectName, MaximumStorageStateofChargeFraction, MinimumStorageStateofChargeFraction, DesignStorageControlChargePower, StorageChargePowerFractionScheduleName, DesignStorageControlDischargePower, StorageDischargePowerFractionScheduleName, StorageControlUtilityDemandTarget, StorageControlUtilityDemandTargetFractionScheduleName,   };
  ElectricLoadCenter_DistributionFields()
   : EnumBase<ElectricLoadCenter_DistributionFields>(Name) {} 
  ElectricLoadCenter_DistributionFields(const std::string &t_name) 
   : EnumBase<ElectricLoadCenter_DistributionFields>(t_name) {} 
  ElectricLoadCenter_DistributionFields(int t_value) 
   : EnumBase<ElectricLoadCenter_DistributionFields>(t_value) {} 
  static std::string enumName() 
  { return "ElectricLoadCenter_DistributionFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ElectricLoadCenter_DistributionFields>::value()); }
   private:
    friend class EnumBase<ElectricLoadCenter_DistributionFields>;
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
{ ElectricLoadCenter_DistributionFields::Name, "Name", "Name"},
{ ElectricLoadCenter_DistributionFields::GeneratorListName, "GeneratorListName", "Generator List Name"},
{ ElectricLoadCenter_DistributionFields::GeneratorOperationSchemeType, "GeneratorOperationSchemeType", "Generator Operation Scheme Type"},
{ ElectricLoadCenter_DistributionFields::GeneratorDemandLimitSchemePurchasedElectricDemandLimit, "GeneratorDemandLimitSchemePurchasedElectricDemandLimit", "Generator Demand Limit Scheme Purchased Electric Demand Limit"},
{ ElectricLoadCenter_DistributionFields::GeneratorTrackScheduleNameSchemeScheduleName, "GeneratorTrackScheduleNameSchemeScheduleName", "Generator Track Schedule Name Scheme Schedule Name"},
{ ElectricLoadCenter_DistributionFields::GeneratorTrackMeterSchemeMeterName, "GeneratorTrackMeterSchemeMeterName", "Generator Track Meter Scheme Meter Name"},
{ ElectricLoadCenter_DistributionFields::ElectricalBussType, "ElectricalBussType", "Electrical Buss Type"},
{ ElectricLoadCenter_DistributionFields::InverterName, "InverterName", "Inverter Name"},
{ ElectricLoadCenter_DistributionFields::ElectricalStorageObjectName, "ElectricalStorageObjectName", "Electrical Storage Object Name"},
{ ElectricLoadCenter_DistributionFields::TransformerObjectName, "TransformerObjectName", "Transformer Object Name"},
{ ElectricLoadCenter_DistributionFields::StorageOperationScheme, "StorageOperationScheme", "Storage Operation Scheme"},
{ ElectricLoadCenter_DistributionFields::StorageControlTrackMeterName, "StorageControlTrackMeterName", "Storage Control Track Meter Name"},
{ ElectricLoadCenter_DistributionFields::StorageConverterObjectName, "StorageConverterObjectName", "Storage Converter Object Name"},
{ ElectricLoadCenter_DistributionFields::MaximumStorageStateofChargeFraction, "MaximumStorageStateofChargeFraction", "Maximum Storage State of Charge Fraction"},
{ ElectricLoadCenter_DistributionFields::MinimumStorageStateofChargeFraction, "MinimumStorageStateofChargeFraction", "Minimum Storage State of Charge Fraction"},
{ ElectricLoadCenter_DistributionFields::DesignStorageControlChargePower, "DesignStorageControlChargePower", "Design Storage Control Charge Power"},
{ ElectricLoadCenter_DistributionFields::StorageChargePowerFractionScheduleName, "StorageChargePowerFractionScheduleName", "Storage Charge Power Fraction Schedule Name"},
{ ElectricLoadCenter_DistributionFields::DesignStorageControlDischargePower, "DesignStorageControlDischargePower", "Design Storage Control Discharge Power"},
{ ElectricLoadCenter_DistributionFields::StorageDischargePowerFractionScheduleName, "StorageDischargePowerFractionScheduleName", "Storage Discharge Power Fraction Schedule Name"},
{ ElectricLoadCenter_DistributionFields::StorageControlUtilityDemandTarget, "StorageControlUtilityDemandTarget", "Storage Control Utility Demand Target"},
{ ElectricLoadCenter_DistributionFields::StorageControlUtilityDemandTargetFractionScheduleName, "StorageControlUtilityDemandTargetFractionScheduleName", "Storage Control Utility Demand Target Fraction Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ElectricLoadCenter_DistributionFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ElectricLoadCenter_DistributionFields> OptionalElectricLoadCenter_DistributionFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ELECTRICLOADCENTER_DISTRIBUTION_FIELDENUMS_HXX
