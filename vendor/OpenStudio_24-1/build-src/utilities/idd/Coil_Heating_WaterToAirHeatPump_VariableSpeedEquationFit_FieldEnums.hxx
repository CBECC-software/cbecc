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

#ifndef UTILITIES_IDD_COIL_HEATING_WATERTOAIRHEATPUMP_VARIABLESPEEDEQUATIONFIT_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_HEATING_WATERTOAIRHEATPUMP_VARIABLESPEEDEQUATIONFIT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields
 *  \brief Enumeration of Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields, )
#else
class Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields: public ::EnumBase<Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields> {
 public: 
  enum domain 
  {
Name, WatertoRefrigerantHXWaterInletNodeName, WatertoRefrigerantHXWaterOutletNodeName, IndoorAirInletNodeName, IndoorAirOutletNodeName, NumberofSpeeds, NominalSpeedLevel, RatedHeatingCapacityAtSelectedNominalSpeedLevel, RatedAirFlowRateAtSelectedNominalSpeedLevel, RatedWaterFlowRateAtSelectedNominalSpeedLevel, EnergyPartLoadFractionCurveName,   };
  Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields()
   : EnumBase<Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields>(Name) {} 
  Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields(const std::string &t_name) 
   : EnumBase<Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields>(t_name) {} 
  Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields(int t_value) 
   : EnumBase<Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields>::value()); }
   private:
    friend class EnumBase<Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields>;
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
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::Name, "Name", "Name"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::WatertoRefrigerantHXWaterInletNodeName, "WatertoRefrigerantHXWaterInletNodeName", "Water-to-Refrigerant HX Water Inlet Node Name"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::WatertoRefrigerantHXWaterOutletNodeName, "WatertoRefrigerantHXWaterOutletNodeName", "Water-to-Refrigerant HX Water Outlet Node Name"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::IndoorAirInletNodeName, "IndoorAirInletNodeName", "Indoor Air Inlet Node Name"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::IndoorAirOutletNodeName, "IndoorAirOutletNodeName", "Indoor Air Outlet Node Name"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::NumberofSpeeds, "NumberofSpeeds", "Number of Speeds"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::NominalSpeedLevel, "NominalSpeedLevel", "Nominal Speed Level"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedHeatingCapacityAtSelectedNominalSpeedLevel, "RatedHeatingCapacityAtSelectedNominalSpeedLevel", "Rated Heating Capacity At Selected Nominal Speed Level"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedAirFlowRateAtSelectedNominalSpeedLevel, "RatedAirFlowRateAtSelectedNominalSpeedLevel", "Rated Air Flow Rate At Selected Nominal Speed Level"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedWaterFlowRateAtSelectedNominalSpeedLevel, "RatedWaterFlowRateAtSelectedNominalSpeedLevel", "Rated Water Flow Rate At Selected Nominal Speed Level"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::EnergyPartLoadFractionCurveName, "EnergyPartLoadFractionCurveName", "Energy Part Load Fraction Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields> OptionalCoil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields ;
#endif

/** \class Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields
 *  \brief Enumeration of Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields, )
#else
class Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields: public ::EnumBase<Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields> {
 public: 
  enum domain 
  {
SpeedReferenceUnitGrossRatedHeatingCapacity, SpeedReferenceUnitGrossRatedHeatingCOP, SpeedReferenceUnitRatedAirFlow, SpeedReferenceUnitRatedWaterFlowRate, SpeedHeatingCapacityFunctionofTemperatureCurveName, SpeedTotalHeatingCapacityFunctionofAirFlowFractionCurveName, SpeedHeatingCapacityFunctionofWaterFlowFractionCurveName, SpeedEnergyInputRatioFunctionofTemperatureCurveName, SpeedEnergyInputRatioFunctionofAirFlowFractionCurveName, SpeedEnergyInputRatioFunctionofWaterFlowFractionCurveName, SpeedReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions, SpeedWasteHeatFunctionofTemperatureCurveName,   };
  Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields()
   : EnumBase<Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields>(SpeedReferenceUnitGrossRatedHeatingCapacity) {} 
  Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields(const std::string &t_name) 
   : EnumBase<Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields>(t_name) {} 
  Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields(int t_value) 
   : EnumBase<Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields>::value()); }
   private:
    friend class EnumBase<Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields>;
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
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields::SpeedReferenceUnitGrossRatedHeatingCapacity, "SpeedReferenceUnitGrossRatedHeatingCapacity", "Speed Reference Unit Gross Rated Heating Capacity"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields::SpeedReferenceUnitGrossRatedHeatingCOP, "SpeedReferenceUnitGrossRatedHeatingCOP", "Speed Reference Unit Gross Rated Heating COP"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields::SpeedReferenceUnitRatedAirFlow, "SpeedReferenceUnitRatedAirFlow", "Speed Reference Unit Rated Air Flow"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields::SpeedReferenceUnitRatedWaterFlowRate, "SpeedReferenceUnitRatedWaterFlowRate", "Speed Reference Unit Rated Water Flow Rate"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields::SpeedHeatingCapacityFunctionofTemperatureCurveName, "SpeedHeatingCapacityFunctionofTemperatureCurveName", "Speed Heating Capacity Function of Temperature Curve Name"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields::SpeedTotalHeatingCapacityFunctionofAirFlowFractionCurveName, "SpeedTotalHeatingCapacityFunctionofAirFlowFractionCurveName", "Speed Total  Heating Capacity Function of Air Flow Fraction Curve Name"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields::SpeedHeatingCapacityFunctionofWaterFlowFractionCurveName, "SpeedHeatingCapacityFunctionofWaterFlowFractionCurveName", "Speed Heating Capacity Function of Water Flow Fraction Curve Name"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields::SpeedEnergyInputRatioFunctionofTemperatureCurveName, "SpeedEnergyInputRatioFunctionofTemperatureCurveName", "Speed Energy Input Ratio Function of Temperature Curve Name"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields::SpeedEnergyInputRatioFunctionofAirFlowFractionCurveName, "SpeedEnergyInputRatioFunctionofAirFlowFractionCurveName", "Speed Energy Input Ratio Function of Air Flow Fraction Curve Name"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields::SpeedEnergyInputRatioFunctionofWaterFlowFractionCurveName, "SpeedEnergyInputRatioFunctionofWaterFlowFractionCurveName", "Speed Energy Input Ratio Function of Water Flow Fraction Curve Name"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields::SpeedReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions, "SpeedReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions", "Speed Reference Unit Waste Heat Fraction of Input Power At Rated Conditions"},
{ Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields::SpeedWasteHeatFunctionofTemperatureCurveName, "SpeedWasteHeatFunctionofTemperatureCurveName", "Speed Waste Heat Function of Temperature Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields> OptionalCoil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_HEATING_WATERTOAIRHEATPUMP_VARIABLESPEEDEQUATIONFIT_FIELDENUMS_HXX
