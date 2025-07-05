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
