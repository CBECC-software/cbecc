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

#ifndef UTILITIES_IDD_OS_ELECTRICLOADCENTER_DISTRIBUTION_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ELECTRICLOADCENTER_DISTRIBUTION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ElectricLoadCenter_DistributionFields
 *  \brief Enumeration of OS:ElectricLoadCenter:Distribution's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ElectricLoadCenter_DistributionFields, )
#else
class OS_ElectricLoadCenter_DistributionFields: public ::EnumBase<OS_ElectricLoadCenter_DistributionFields> {
 public: 
  enum domain 
  {
Handle, Name, GeneratorListName, GeneratorOperationSchemeType, DemandLimitSchemePurchasedElectricDemandLimit, TrackScheduleNameSchemeScheduleName, TrackMeterSchemeMeterName, ElectricalBussType, InverterObjectName, ElectricalStorageObjectName, TransformerObjectName,   };
  OS_ElectricLoadCenter_DistributionFields()
   : EnumBase<OS_ElectricLoadCenter_DistributionFields>(Handle) {} 
  OS_ElectricLoadCenter_DistributionFields(const std::string &t_name) 
   : EnumBase<OS_ElectricLoadCenter_DistributionFields>(t_name) {} 
  OS_ElectricLoadCenter_DistributionFields(int t_value) 
   : EnumBase<OS_ElectricLoadCenter_DistributionFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ElectricLoadCenter_DistributionFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ElectricLoadCenter_DistributionFields>::value()); }
   private:
    friend class EnumBase<OS_ElectricLoadCenter_DistributionFields>;
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
{ OS_ElectricLoadCenter_DistributionFields::Handle, "Handle", "Handle"},
{ OS_ElectricLoadCenter_DistributionFields::Name, "Name", "Name"},
{ OS_ElectricLoadCenter_DistributionFields::GeneratorListName, "GeneratorListName", "Generator List Name"},
{ OS_ElectricLoadCenter_DistributionFields::GeneratorOperationSchemeType, "GeneratorOperationSchemeType", "Generator Operation Scheme Type"},
{ OS_ElectricLoadCenter_DistributionFields::DemandLimitSchemePurchasedElectricDemandLimit, "DemandLimitSchemePurchasedElectricDemandLimit", "Demand Limit Scheme Purchased Electric Demand Limit"},
{ OS_ElectricLoadCenter_DistributionFields::TrackScheduleNameSchemeScheduleName, "TrackScheduleNameSchemeScheduleName", "Track Schedule Name Scheme Schedule Name"},
{ OS_ElectricLoadCenter_DistributionFields::TrackMeterSchemeMeterName, "TrackMeterSchemeMeterName", "Track Meter Scheme Meter Name"},
{ OS_ElectricLoadCenter_DistributionFields::ElectricalBussType, "ElectricalBussType", "Electrical Buss Type"},
{ OS_ElectricLoadCenter_DistributionFields::InverterObjectName, "InverterObjectName", "Inverter Object Name"},
{ OS_ElectricLoadCenter_DistributionFields::ElectricalStorageObjectName, "ElectricalStorageObjectName", "Electrical Storage Object Name"},
{ OS_ElectricLoadCenter_DistributionFields::TransformerObjectName, "TransformerObjectName", "Transformer Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ElectricLoadCenter_DistributionFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ElectricLoadCenter_DistributionFields> OptionalOS_ElectricLoadCenter_DistributionFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ELECTRICLOADCENTER_DISTRIBUTION_FIELDENUMS_HXX
