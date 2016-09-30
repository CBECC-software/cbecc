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

#ifndef UTILITIES_IDD_ELECTRICLOADCENTER_INVERTER_LOOKUPTABLE_FIELDENUMS_HXX
#define UTILITIES_IDD_ELECTRICLOADCENTER_INVERTER_LOOKUPTABLE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ElectricLoadCenter_Inverter_LookUpTableFields
 *  \brief Enumeration of ElectricLoadCenter:Inverter:LookUpTable's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ElectricLoadCenter_Inverter_LookUpTableFields, )
#else
class ElectricLoadCenter_Inverter_LookUpTableFields: public ::EnumBase<ElectricLoadCenter_Inverter_LookUpTableFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, ZoneName, RadiativeFraction, RatedMaximumContinuousOutputPower, NightTareLossPower, NominalVoltageInput, Efficiencyat10_PowerandNominalVoltage, Efficiencyat20_PowerandNominalVoltage, Efficiencyat30_PowerandNominalVoltage, Efficiencyat50_PowerandNominalVoltage, Efficiencyat75_PowerandNominalVoltage, Efficiencyat100_PowerandNominalVoltage,   };
  ElectricLoadCenter_Inverter_LookUpTableFields()
   : EnumBase<ElectricLoadCenter_Inverter_LookUpTableFields>(Name) {} 
  ElectricLoadCenter_Inverter_LookUpTableFields(const std::string &t_name) 
   : EnumBase<ElectricLoadCenter_Inverter_LookUpTableFields>(t_name) {} 
  ElectricLoadCenter_Inverter_LookUpTableFields(int t_value) 
   : EnumBase<ElectricLoadCenter_Inverter_LookUpTableFields>(t_value) {} 
  static std::string enumName() 
  { return "ElectricLoadCenter_Inverter_LookUpTableFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ElectricLoadCenter_Inverter_LookUpTableFields>::value()); }
   private:
    friend class EnumBase<ElectricLoadCenter_Inverter_LookUpTableFields>;
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
{ ElectricLoadCenter_Inverter_LookUpTableFields::Name, "Name", "Name"},
{ ElectricLoadCenter_Inverter_LookUpTableFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ElectricLoadCenter_Inverter_LookUpTableFields::ZoneName, "ZoneName", "Zone Name"},
{ ElectricLoadCenter_Inverter_LookUpTableFields::RadiativeFraction, "RadiativeFraction", "Radiative Fraction"},
{ ElectricLoadCenter_Inverter_LookUpTableFields::RatedMaximumContinuousOutputPower, "RatedMaximumContinuousOutputPower", "Rated Maximum Continuous Output Power"},
{ ElectricLoadCenter_Inverter_LookUpTableFields::NightTareLossPower, "NightTareLossPower", "Night Tare Loss Power"},
{ ElectricLoadCenter_Inverter_LookUpTableFields::NominalVoltageInput, "NominalVoltageInput", "Nominal Voltage Input"},
{ ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat10_PowerandNominalVoltage, "Efficiencyat10_PowerandNominalVoltage", "Efficiency at 10% Power and Nominal Voltage"},
{ ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat20_PowerandNominalVoltage, "Efficiencyat20_PowerandNominalVoltage", "Efficiency at 20% Power and Nominal Voltage"},
{ ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat30_PowerandNominalVoltage, "Efficiencyat30_PowerandNominalVoltage", "Efficiency at 30% Power and Nominal Voltage"},
{ ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat50_PowerandNominalVoltage, "Efficiencyat50_PowerandNominalVoltage", "Efficiency at 50% Power and Nominal Voltage"},
{ ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat75_PowerandNominalVoltage, "Efficiencyat75_PowerandNominalVoltage", "Efficiency at 75% Power and Nominal Voltage"},
{ ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat100_PowerandNominalVoltage, "Efficiencyat100_PowerandNominalVoltage", "Efficiency at 100% Power and Nominal Voltage"},
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
  inline std::ostream &operator<<(std::ostream &os, const ElectricLoadCenter_Inverter_LookUpTableFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ElectricLoadCenter_Inverter_LookUpTableFields> OptionalElectricLoadCenter_Inverter_LookUpTableFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ELECTRICLOADCENTER_INVERTER_LOOKUPTABLE_FIELDENUMS_HXX
