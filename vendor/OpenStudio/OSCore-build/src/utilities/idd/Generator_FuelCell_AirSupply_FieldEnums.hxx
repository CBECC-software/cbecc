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

#ifndef UTILITIES_IDD_GENERATOR_FUELCELL_AIRSUPPLY_FIELDENUMS_HXX
#define UTILITIES_IDD_GENERATOR_FUELCELL_AIRSUPPLY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Generator_FuelCell_AirSupplyFields
 *  \brief Enumeration of Generator:FuelCell:AirSupply's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Generator_FuelCell_AirSupplyFields, )
#else
class Generator_FuelCell_AirSupplyFields: public ::EnumBase<Generator_FuelCell_AirSupplyFields> {
 public: 
  enum domain 
  {
Name, AirInletNodeName, BlowerPowerCurveName, BlowerHeatLossFactor, AirSupplyRateCalculationMode, StoichiometricRatio, AirRateFunctionofElectricPowerCurveName, AirRateAirTemperatureCoefficient, AirRateFunctionofFuelRateCurveName, AirIntakeHeatRecoveryMode, AirSupplyConstituentMode, NumberofUserDefinedConstituents,   };
  Generator_FuelCell_AirSupplyFields()
   : EnumBase<Generator_FuelCell_AirSupplyFields>(Name) {} 
  Generator_FuelCell_AirSupplyFields(const std::string &t_name) 
   : EnumBase<Generator_FuelCell_AirSupplyFields>(t_name) {} 
  Generator_FuelCell_AirSupplyFields(int t_value) 
   : EnumBase<Generator_FuelCell_AirSupplyFields>(t_value) {} 
  static std::string enumName() 
  { return "Generator_FuelCell_AirSupplyFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Generator_FuelCell_AirSupplyFields>::value()); }
   private:
    friend class EnumBase<Generator_FuelCell_AirSupplyFields>;
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
{ Generator_FuelCell_AirSupplyFields::Name, "Name", "Name"},
{ Generator_FuelCell_AirSupplyFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Generator_FuelCell_AirSupplyFields::BlowerPowerCurveName, "BlowerPowerCurveName", "Blower Power Curve Name"},
{ Generator_FuelCell_AirSupplyFields::BlowerHeatLossFactor, "BlowerHeatLossFactor", "Blower Heat Loss Factor"},
{ Generator_FuelCell_AirSupplyFields::AirSupplyRateCalculationMode, "AirSupplyRateCalculationMode", "Air Supply Rate Calculation Mode"},
{ Generator_FuelCell_AirSupplyFields::StoichiometricRatio, "StoichiometricRatio", "Stoichiometric Ratio"},
{ Generator_FuelCell_AirSupplyFields::AirRateFunctionofElectricPowerCurveName, "AirRateFunctionofElectricPowerCurveName", "Air Rate Function of Electric Power Curve Name"},
{ Generator_FuelCell_AirSupplyFields::AirRateAirTemperatureCoefficient, "AirRateAirTemperatureCoefficient", "Air Rate Air Temperature Coefficient"},
{ Generator_FuelCell_AirSupplyFields::AirRateFunctionofFuelRateCurveName, "AirRateFunctionofFuelRateCurveName", "Air Rate Function of Fuel Rate Curve Name"},
{ Generator_FuelCell_AirSupplyFields::AirIntakeHeatRecoveryMode, "AirIntakeHeatRecoveryMode", "Air Intake Heat Recovery Mode"},
{ Generator_FuelCell_AirSupplyFields::AirSupplyConstituentMode, "AirSupplyConstituentMode", "Air Supply Constituent Mode"},
{ Generator_FuelCell_AirSupplyFields::NumberofUserDefinedConstituents, "NumberofUserDefinedConstituents", "Number of UserDefined Constituents"},
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
  inline std::ostream &operator<<(std::ostream &os, const Generator_FuelCell_AirSupplyFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Generator_FuelCell_AirSupplyFields> OptionalGenerator_FuelCell_AirSupplyFields ;
#endif

/** \class Generator_FuelCell_AirSupplyExtensibleFields
 *  \brief Enumeration of Generator:FuelCell:AirSupply's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Generator_FuelCell_AirSupplyExtensibleFields, )
#else
class Generator_FuelCell_AirSupplyExtensibleFields: public ::EnumBase<Generator_FuelCell_AirSupplyExtensibleFields> {
 public: 
  enum domain 
  {
ConstituentName, MolarFraction,   };
  Generator_FuelCell_AirSupplyExtensibleFields()
   : EnumBase<Generator_FuelCell_AirSupplyExtensibleFields>(ConstituentName) {} 
  Generator_FuelCell_AirSupplyExtensibleFields(const std::string &t_name) 
   : EnumBase<Generator_FuelCell_AirSupplyExtensibleFields>(t_name) {} 
  Generator_FuelCell_AirSupplyExtensibleFields(int t_value) 
   : EnumBase<Generator_FuelCell_AirSupplyExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Generator_FuelCell_AirSupplyExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Generator_FuelCell_AirSupplyExtensibleFields>::value()); }
   private:
    friend class EnumBase<Generator_FuelCell_AirSupplyExtensibleFields>;
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
{ Generator_FuelCell_AirSupplyExtensibleFields::ConstituentName, "ConstituentName", "Constituent Name"},
{ Generator_FuelCell_AirSupplyExtensibleFields::MolarFraction, "MolarFraction", "Molar Fraction"},
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
  inline std::ostream &operator<<(std::ostream &os, const Generator_FuelCell_AirSupplyExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Generator_FuelCell_AirSupplyExtensibleFields> OptionalGenerator_FuelCell_AirSupplyExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GENERATOR_FUELCELL_AIRSUPPLY_FIELDENUMS_HXX
