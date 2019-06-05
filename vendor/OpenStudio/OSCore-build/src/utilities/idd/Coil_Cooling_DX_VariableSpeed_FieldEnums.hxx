/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2019, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_COIL_COOLING_DX_VARIABLESPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_COOLING_DX_VARIABLESPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Cooling_DX_VariableSpeedFields
 *  \brief Enumeration of Coil:Cooling:DX:VariableSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Cooling_DX_VariableSpeedFields, )
#else
class Coil_Cooling_DX_VariableSpeedFields: public ::EnumBase<Coil_Cooling_DX_VariableSpeedFields> {
 public: 
  enum domain 
  {
Name, IndoorAirInletNodeName, IndoorAirOutletNodeName, NumberofSpeeds, NominalSpeedLevel, GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel, RatedAirFlowRateAtSelectedNominalSpeedLevel, NominalTimeforCondensatetoBeginLeavingtheCoil, InitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity, EnergyPartLoadFractionCurveName, CondenserAirInletNodeName, CondenserType, EvaporativeCondenserPumpRatedPowerConsumption, CrankcaseHeaterCapacity, MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, MinimumOutdoorDryBulbTemperatureforCompressorOperation, SupplyWaterStorageTankName, CondensateCollectionWaterStorageTankName, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName,   };
  Coil_Cooling_DX_VariableSpeedFields()
   : EnumBase<Coil_Cooling_DX_VariableSpeedFields>(Name) {} 
  Coil_Cooling_DX_VariableSpeedFields(const std::string &t_name) 
   : EnumBase<Coil_Cooling_DX_VariableSpeedFields>(t_name) {} 
  Coil_Cooling_DX_VariableSpeedFields(int t_value) 
   : EnumBase<Coil_Cooling_DX_VariableSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Cooling_DX_VariableSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Cooling_DX_VariableSpeedFields>::value()); }
   private:
    friend class EnumBase<Coil_Cooling_DX_VariableSpeedFields>;
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
{ Coil_Cooling_DX_VariableSpeedFields::Name, "Name", "Name"},
{ Coil_Cooling_DX_VariableSpeedFields::IndoorAirInletNodeName, "IndoorAirInletNodeName", "Indoor Air Inlet Node Name"},
{ Coil_Cooling_DX_VariableSpeedFields::IndoorAirOutletNodeName, "IndoorAirOutletNodeName", "Indoor Air Outlet Node Name"},
{ Coil_Cooling_DX_VariableSpeedFields::NumberofSpeeds, "NumberofSpeeds", "Number of Speeds"},
{ Coil_Cooling_DX_VariableSpeedFields::NominalSpeedLevel, "NominalSpeedLevel", "Nominal Speed Level"},
{ Coil_Cooling_DX_VariableSpeedFields::GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel, "GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel", "Gross Rated Total Cooling Capacity At Selected Nominal Speed Level"},
{ Coil_Cooling_DX_VariableSpeedFields::RatedAirFlowRateAtSelectedNominalSpeedLevel, "RatedAirFlowRateAtSelectedNominalSpeedLevel", "Rated Air Flow Rate At Selected Nominal Speed Level"},
{ Coil_Cooling_DX_VariableSpeedFields::NominalTimeforCondensatetoBeginLeavingtheCoil, "NominalTimeforCondensatetoBeginLeavingtheCoil", "Nominal Time for Condensate to Begin Leaving the Coil"},
{ Coil_Cooling_DX_VariableSpeedFields::InitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity, "InitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity", "Initial Moisture Evaporation Rate Divided by Steady-State AC Latent Capacity"},
{ Coil_Cooling_DX_VariableSpeedFields::EnergyPartLoadFractionCurveName, "EnergyPartLoadFractionCurveName", "Energy Part Load Fraction Curve Name"},
{ Coil_Cooling_DX_VariableSpeedFields::CondenserAirInletNodeName, "CondenserAirInletNodeName", "Condenser Air Inlet Node Name"},
{ Coil_Cooling_DX_VariableSpeedFields::CondenserType, "CondenserType", "Condenser Type"},
{ Coil_Cooling_DX_VariableSpeedFields::EvaporativeCondenserPumpRatedPowerConsumption, "EvaporativeCondenserPumpRatedPowerConsumption", "Evaporative Condenser Pump Rated Power Consumption"},
{ Coil_Cooling_DX_VariableSpeedFields::CrankcaseHeaterCapacity, "CrankcaseHeaterCapacity", "Crankcase Heater Capacity"},
{ Coil_Cooling_DX_VariableSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, "MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Crankcase Heater Operation"},
{ Coil_Cooling_DX_VariableSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, "MinimumOutdoorDryBulbTemperatureforCompressorOperation", "Minimum Outdoor Dry-Bulb Temperature for Compressor Operation"},
{ Coil_Cooling_DX_VariableSpeedFields::SupplyWaterStorageTankName, "SupplyWaterStorageTankName", "Supply Water Storage Tank Name"},
{ Coil_Cooling_DX_VariableSpeedFields::CondensateCollectionWaterStorageTankName, "CondensateCollectionWaterStorageTankName", "Condensate Collection Water Storage Tank Name"},
{ Coil_Cooling_DX_VariableSpeedFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ Coil_Cooling_DX_VariableSpeedFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ Coil_Cooling_DX_VariableSpeedFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Cooling_DX_VariableSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Cooling_DX_VariableSpeedFields> OptionalCoil_Cooling_DX_VariableSpeedFields ;
#endif

/** \class Coil_Cooling_DX_VariableSpeedExtensibleFields
 *  \brief Enumeration of Coil:Cooling:DX:VariableSpeed's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Coil_Cooling_DX_VariableSpeedExtensibleFields, )
#else
class Coil_Cooling_DX_VariableSpeedExtensibleFields: public ::EnumBase<Coil_Cooling_DX_VariableSpeedExtensibleFields> {
 public: 
  enum domain 
  {
SpeedReferenceUnitGrossRatedTotalCoolingCapacity, SpeedReferenceUnitGrossRatedSensibleHeatRatio, SpeedReferenceUnitGrossRatedCoolingCOP, SpeedReferenceUnitRatedAirFlowRate, SpeedReferenceUnitRatedCondenserAirFlowRate, SpeedReferenceUnitRatedPadEffectivenessofEvapPrecooling, SpeedTotalCoolingCapacityFunctionofTemperatureCurveName, SpeedTotalCoolingCapacityFunctionofAirFlowFractionCurveName, SpeedEnergyInputRatioFunctionofTemperatureCurveName, SpeedEnergyInputRatioFunctionofAirFlowFractionCurveName,   };
  Coil_Cooling_DX_VariableSpeedExtensibleFields()
   : EnumBase<Coil_Cooling_DX_VariableSpeedExtensibleFields>(SpeedReferenceUnitGrossRatedTotalCoolingCapacity) {} 
  Coil_Cooling_DX_VariableSpeedExtensibleFields(const std::string &t_name) 
   : EnumBase<Coil_Cooling_DX_VariableSpeedExtensibleFields>(t_name) {} 
  Coil_Cooling_DX_VariableSpeedExtensibleFields(int t_value) 
   : EnumBase<Coil_Cooling_DX_VariableSpeedExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Cooling_DX_VariableSpeedExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Cooling_DX_VariableSpeedExtensibleFields>::value()); }
   private:
    friend class EnumBase<Coil_Cooling_DX_VariableSpeedExtensibleFields>;
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
{ Coil_Cooling_DX_VariableSpeedExtensibleFields::SpeedReferenceUnitGrossRatedTotalCoolingCapacity, "SpeedReferenceUnitGrossRatedTotalCoolingCapacity", "Speed Reference Unit Gross Rated Total Cooling Capacity"},
{ Coil_Cooling_DX_VariableSpeedExtensibleFields::SpeedReferenceUnitGrossRatedSensibleHeatRatio, "SpeedReferenceUnitGrossRatedSensibleHeatRatio", "Speed Reference Unit Gross Rated Sensible Heat Ratio"},
{ Coil_Cooling_DX_VariableSpeedExtensibleFields::SpeedReferenceUnitGrossRatedCoolingCOP, "SpeedReferenceUnitGrossRatedCoolingCOP", "Speed Reference Unit Gross Rated Cooling COP"},
{ Coil_Cooling_DX_VariableSpeedExtensibleFields::SpeedReferenceUnitRatedAirFlowRate, "SpeedReferenceUnitRatedAirFlowRate", "Speed Reference Unit Rated Air Flow Rate"},
{ Coil_Cooling_DX_VariableSpeedExtensibleFields::SpeedReferenceUnitRatedCondenserAirFlowRate, "SpeedReferenceUnitRatedCondenserAirFlowRate", "Speed Reference Unit Rated Condenser Air Flow Rate"},
{ Coil_Cooling_DX_VariableSpeedExtensibleFields::SpeedReferenceUnitRatedPadEffectivenessofEvapPrecooling, "SpeedReferenceUnitRatedPadEffectivenessofEvapPrecooling", "Speed Reference Unit Rated Pad Effectiveness of Evap Precooling"},
{ Coil_Cooling_DX_VariableSpeedExtensibleFields::SpeedTotalCoolingCapacityFunctionofTemperatureCurveName, "SpeedTotalCoolingCapacityFunctionofTemperatureCurveName", "Speed Total Cooling Capacity Function of Temperature Curve Name"},
{ Coil_Cooling_DX_VariableSpeedExtensibleFields::SpeedTotalCoolingCapacityFunctionofAirFlowFractionCurveName, "SpeedTotalCoolingCapacityFunctionofAirFlowFractionCurveName", "Speed Total Cooling Capacity Function of Air Flow Fraction Curve Name"},
{ Coil_Cooling_DX_VariableSpeedExtensibleFields::SpeedEnergyInputRatioFunctionofTemperatureCurveName, "SpeedEnergyInputRatioFunctionofTemperatureCurveName", "Speed Energy Input Ratio Function of Temperature Curve Name"},
{ Coil_Cooling_DX_VariableSpeedExtensibleFields::SpeedEnergyInputRatioFunctionofAirFlowFractionCurveName, "SpeedEnergyInputRatioFunctionofAirFlowFractionCurveName", "Speed Energy Input Ratio Function of Air Flow Fraction Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Cooling_DX_VariableSpeedExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Cooling_DX_VariableSpeedExtensibleFields> OptionalCoil_Cooling_DX_VariableSpeedExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_COOLING_DX_VARIABLESPEED_FIELDENUMS_HXX
