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

#ifndef UTILITIES_IDD_GENERATOR_FUELSUPPLY_FIELDENUMS_HXX
#define UTILITIES_IDD_GENERATOR_FUELSUPPLY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Generator_FuelSupplyFields
 *  \brief Enumeration of Generator:FuelSupply's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Generator_FuelSupplyFields, )
#else
class Generator_FuelSupplyFields: public ::EnumBase<Generator_FuelSupplyFields> {
 public: 
  enum domain 
  {
Name, FuelTemperatureModelingMode, FuelTemperatureReferenceNodeName, FuelTemperatureScheduleName, CompressorPowerMultiplierFunctionofFuelRateCurveName, CompressorHeatLossFactor, FuelType, LiquidGenericFuelLowerHeatingValue, LiquidGenericFuelHigherHeatingValue, LiquidGenericFuelMolecularWeight, LiquidGenericFuelCO2EmissionFactor, NumberofConstituentsinGaseousConstituentFuelSupply,   };
  Generator_FuelSupplyFields()
   : EnumBase<Generator_FuelSupplyFields>(Name) {} 
  Generator_FuelSupplyFields(const std::string &t_name) 
   : EnumBase<Generator_FuelSupplyFields>(t_name) {} 
  Generator_FuelSupplyFields(int t_value) 
   : EnumBase<Generator_FuelSupplyFields>(t_value) {} 
  static std::string enumName() 
  { return "Generator_FuelSupplyFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Generator_FuelSupplyFields>::value()); }
   private:
    friend class EnumBase<Generator_FuelSupplyFields>;
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
{ Generator_FuelSupplyFields::Name, "Name", "Name"},
{ Generator_FuelSupplyFields::FuelTemperatureModelingMode, "FuelTemperatureModelingMode", "Fuel Temperature Modeling Mode"},
{ Generator_FuelSupplyFields::FuelTemperatureReferenceNodeName, "FuelTemperatureReferenceNodeName", "Fuel Temperature Reference Node Name"},
{ Generator_FuelSupplyFields::FuelTemperatureScheduleName, "FuelTemperatureScheduleName", "Fuel Temperature Schedule Name"},
{ Generator_FuelSupplyFields::CompressorPowerMultiplierFunctionofFuelRateCurveName, "CompressorPowerMultiplierFunctionofFuelRateCurveName", "Compressor Power Multiplier Function of Fuel Rate Curve Name"},
{ Generator_FuelSupplyFields::CompressorHeatLossFactor, "CompressorHeatLossFactor", "Compressor Heat Loss Factor"},
{ Generator_FuelSupplyFields::FuelType, "FuelType", "Fuel Type"},
{ Generator_FuelSupplyFields::LiquidGenericFuelLowerHeatingValue, "LiquidGenericFuelLowerHeatingValue", "Liquid Generic Fuel Lower Heating Value"},
{ Generator_FuelSupplyFields::LiquidGenericFuelHigherHeatingValue, "LiquidGenericFuelHigherHeatingValue", "Liquid Generic Fuel Higher Heating Value"},
{ Generator_FuelSupplyFields::LiquidGenericFuelMolecularWeight, "LiquidGenericFuelMolecularWeight", "Liquid Generic Fuel Molecular Weight"},
{ Generator_FuelSupplyFields::LiquidGenericFuelCO2EmissionFactor, "LiquidGenericFuelCO2EmissionFactor", "Liquid Generic Fuel CO2 Emission Factor"},
{ Generator_FuelSupplyFields::NumberofConstituentsinGaseousConstituentFuelSupply, "NumberofConstituentsinGaseousConstituentFuelSupply", "Number of Constituents in Gaseous Constituent Fuel Supply"},
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
  inline std::ostream &operator<<(std::ostream &os, const Generator_FuelSupplyFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Generator_FuelSupplyFields> OptionalGenerator_FuelSupplyFields ;
#endif

/** \class Generator_FuelSupplyExtensibleFields
 *  \brief Enumeration of Generator:FuelSupply's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Generator_FuelSupplyExtensibleFields, )
#else
class Generator_FuelSupplyExtensibleFields: public ::EnumBase<Generator_FuelSupplyExtensibleFields> {
 public: 
  enum domain 
  {
ConstituentName, ConstituentMolarFraction,   };
  Generator_FuelSupplyExtensibleFields()
   : EnumBase<Generator_FuelSupplyExtensibleFields>(ConstituentName) {} 
  Generator_FuelSupplyExtensibleFields(const std::string &t_name) 
   : EnumBase<Generator_FuelSupplyExtensibleFields>(t_name) {} 
  Generator_FuelSupplyExtensibleFields(int t_value) 
   : EnumBase<Generator_FuelSupplyExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Generator_FuelSupplyExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Generator_FuelSupplyExtensibleFields>::value()); }
   private:
    friend class EnumBase<Generator_FuelSupplyExtensibleFields>;
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
{ Generator_FuelSupplyExtensibleFields::ConstituentName, "ConstituentName", "Constituent Name"},
{ Generator_FuelSupplyExtensibleFields::ConstituentMolarFraction, "ConstituentMolarFraction", "Constituent Molar Fraction"},
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
  inline std::ostream &operator<<(std::ostream &os, const Generator_FuelSupplyExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Generator_FuelSupplyExtensibleFields> OptionalGenerator_FuelSupplyExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GENERATOR_FUELSUPPLY_FIELDENUMS_HXX
