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

#ifndef UTILITIES_IDD_OS_GENERATOR_FUELSUPPLY_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_GENERATOR_FUELSUPPLY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Generator_FuelSupplyFields
 *  \brief Enumeration of OS:Generator:FuelSupply's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Generator_FuelSupplyFields, )
#else
class OS_Generator_FuelSupplyFields: public ::EnumBase<OS_Generator_FuelSupplyFields> {
 public: 
  enum domain 
  {
Handle, Name, FuelTemperatureModelingMode, FuelTemperatureReferenceNodeName, FuelTemperatureScheduleName, CompressorPowerMultiplierFunctionofFuelRateCurveName, CompressorHeatLossFactor, FuelType, LiquidGenericFuelLowerHeatingValue, LiquidGenericFuelHigherHeatingValue, LiquidGenericFuelMolecularWeight, LiquidGenericFuelCO2EmissionFactor, NumberofConstituentsinGaseousConstituentFuelSupply,   };
  OS_Generator_FuelSupplyFields()
   : EnumBase<OS_Generator_FuelSupplyFields>(Handle) {} 
  OS_Generator_FuelSupplyFields(const std::string &t_name) 
   : EnumBase<OS_Generator_FuelSupplyFields>(t_name) {} 
  OS_Generator_FuelSupplyFields(int t_value) 
   : EnumBase<OS_Generator_FuelSupplyFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Generator_FuelSupplyFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Generator_FuelSupplyFields>::value()); }
   private:
    friend class EnumBase<OS_Generator_FuelSupplyFields>;
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
{ OS_Generator_FuelSupplyFields::Handle, "Handle", "Handle"},
{ OS_Generator_FuelSupplyFields::Name, "Name", "Name"},
{ OS_Generator_FuelSupplyFields::FuelTemperatureModelingMode, "FuelTemperatureModelingMode", "Fuel Temperature Modeling Mode"},
{ OS_Generator_FuelSupplyFields::FuelTemperatureReferenceNodeName, "FuelTemperatureReferenceNodeName", "Fuel Temperature Reference Node Name"},
{ OS_Generator_FuelSupplyFields::FuelTemperatureScheduleName, "FuelTemperatureScheduleName", "Fuel Temperature Schedule Name"},
{ OS_Generator_FuelSupplyFields::CompressorPowerMultiplierFunctionofFuelRateCurveName, "CompressorPowerMultiplierFunctionofFuelRateCurveName", "Compressor Power Multiplier Function of Fuel Rate Curve Name"},
{ OS_Generator_FuelSupplyFields::CompressorHeatLossFactor, "CompressorHeatLossFactor", "Compressor Heat Loss Factor"},
{ OS_Generator_FuelSupplyFields::FuelType, "FuelType", "Fuel Type"},
{ OS_Generator_FuelSupplyFields::LiquidGenericFuelLowerHeatingValue, "LiquidGenericFuelLowerHeatingValue", "Liquid Generic Fuel Lower Heating Value"},
{ OS_Generator_FuelSupplyFields::LiquidGenericFuelHigherHeatingValue, "LiquidGenericFuelHigherHeatingValue", "Liquid Generic Fuel Higher Heating Value"},
{ OS_Generator_FuelSupplyFields::LiquidGenericFuelMolecularWeight, "LiquidGenericFuelMolecularWeight", "Liquid Generic Fuel Molecular Weight"},
{ OS_Generator_FuelSupplyFields::LiquidGenericFuelCO2EmissionFactor, "LiquidGenericFuelCO2EmissionFactor", "Liquid Generic Fuel CO2 Emission Factor"},
{ OS_Generator_FuelSupplyFields::NumberofConstituentsinGaseousConstituentFuelSupply, "NumberofConstituentsinGaseousConstituentFuelSupply", "Number of Constituents in Gaseous Constituent Fuel Supply"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Generator_FuelSupplyFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Generator_FuelSupplyFields> OptionalOS_Generator_FuelSupplyFields ;
#endif

/** \class OS_Generator_FuelSupplyExtensibleFields
 *  \brief Enumeration of OS:Generator:FuelSupply's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_Generator_FuelSupplyExtensibleFields, )
#else
class OS_Generator_FuelSupplyExtensibleFields: public ::EnumBase<OS_Generator_FuelSupplyExtensibleFields> {
 public: 
  enum domain 
  {
ConstituentName, ConstituentMolarFraction,   };
  OS_Generator_FuelSupplyExtensibleFields()
   : EnumBase<OS_Generator_FuelSupplyExtensibleFields>(ConstituentName) {} 
  OS_Generator_FuelSupplyExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Generator_FuelSupplyExtensibleFields>(t_name) {} 
  OS_Generator_FuelSupplyExtensibleFields(int t_value) 
   : EnumBase<OS_Generator_FuelSupplyExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Generator_FuelSupplyExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Generator_FuelSupplyExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_Generator_FuelSupplyExtensibleFields>;
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
{ OS_Generator_FuelSupplyExtensibleFields::ConstituentName, "ConstituentName", "Constituent Name"},
{ OS_Generator_FuelSupplyExtensibleFields::ConstituentMolarFraction, "ConstituentMolarFraction", "Constituent Molar Fraction"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Generator_FuelSupplyExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Generator_FuelSupplyExtensibleFields> OptionalOS_Generator_FuelSupplyExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_GENERATOR_FUELSUPPLY_FIELDENUMS_HXX
