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

#ifndef UTILITIES_IDD_ELECTRICLOADCENTER_STORAGE_CONVERTER_FIELDENUMS_HXX
#define UTILITIES_IDD_ELECTRICLOADCENTER_STORAGE_CONVERTER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ElectricLoadCenter_Storage_ConverterFields
 *  \brief Enumeration of ElectricLoadCenter:Storage:Converter's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ElectricLoadCenter_Storage_ConverterFields, )
#else
class ElectricLoadCenter_Storage_ConverterFields: public ::EnumBase<ElectricLoadCenter_Storage_ConverterFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, PowerConversionEfficiencyMethod, SimpleFixedEfficiency, DesignMaximumContinuousInputPower, EfficiencyFunctionofPowerCurveName, AncillaryPowerConsumedInStandby, ZoneName, RadiativeFraction,   };
  ElectricLoadCenter_Storage_ConverterFields()
   : EnumBase<ElectricLoadCenter_Storage_ConverterFields>(Name) {} 
  ElectricLoadCenter_Storage_ConverterFields(const std::string &t_name) 
   : EnumBase<ElectricLoadCenter_Storage_ConverterFields>(t_name) {} 
  ElectricLoadCenter_Storage_ConverterFields(int t_value) 
   : EnumBase<ElectricLoadCenter_Storage_ConverterFields>(t_value) {} 
  static std::string enumName() 
  { return "ElectricLoadCenter_Storage_ConverterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ElectricLoadCenter_Storage_ConverterFields>::value()); }
   private:
    friend class EnumBase<ElectricLoadCenter_Storage_ConverterFields>;
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
{ ElectricLoadCenter_Storage_ConverterFields::Name, "Name", "Name"},
{ ElectricLoadCenter_Storage_ConverterFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ElectricLoadCenter_Storage_ConverterFields::PowerConversionEfficiencyMethod, "PowerConversionEfficiencyMethod", "Power Conversion Efficiency Method"},
{ ElectricLoadCenter_Storage_ConverterFields::SimpleFixedEfficiency, "SimpleFixedEfficiency", "Simple Fixed Efficiency"},
{ ElectricLoadCenter_Storage_ConverterFields::DesignMaximumContinuousInputPower, "DesignMaximumContinuousInputPower", "Design Maximum Continuous Input Power"},
{ ElectricLoadCenter_Storage_ConverterFields::EfficiencyFunctionofPowerCurveName, "EfficiencyFunctionofPowerCurveName", "Efficiency Function of Power Curve Name"},
{ ElectricLoadCenter_Storage_ConverterFields::AncillaryPowerConsumedInStandby, "AncillaryPowerConsumedInStandby", "Ancillary Power Consumed In Standby"},
{ ElectricLoadCenter_Storage_ConverterFields::ZoneName, "ZoneName", "Zone Name"},
{ ElectricLoadCenter_Storage_ConverterFields::RadiativeFraction, "RadiativeFraction", "Radiative Fraction"},
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
  inline std::ostream &operator<<(std::ostream &os, const ElectricLoadCenter_Storage_ConverterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ElectricLoadCenter_Storage_ConverterFields> OptionalElectricLoadCenter_Storage_ConverterFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ELECTRICLOADCENTER_STORAGE_CONVERTER_FIELDENUMS_HXX
