/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_COIL_HEATING_DX_SINGLESPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_HEATING_DX_SINGLESPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Heating_DX_SingleSpeedFields
 *  \brief Enumeration of Coil:Heating:DX:SingleSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Heating_DX_SingleSpeedFields, )
#else
class Coil_Heating_DX_SingleSpeedFields: public ::EnumBase<Coil_Heating_DX_SingleSpeedFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, GrossRatedHeatingCapacity, GrossRatedHeatingCOP, RatedAirFlowRate, RatedSupplyFanPowerPerVolumeFlowRate, AirInletNodeName, AirOutletNodeName, HeatingCapacityFunctionofTemperatureCurveName, HeatingCapacityFunctionofFlowFractionCurveName, EnergyInputRatioFunctionofTemperatureCurveName, EnergyInputRatioFunctionofFlowFractionCurveName, PartLoadFractionCorrelationCurveName, DefrostEnergyInputRatioFunctionofTemperatureCurveName, MinimumOutdoorDryBulbTemperatureforCompressorOperation, OutdoorDryBulbTemperaturetoTurnOnCompressor, MaximumOutdoorDryBulbTemperatureforDefrostOperation, CrankcaseHeaterCapacity, MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, DefrostStrategy, DefrostControl, DefrostTimePeriodFraction, ResistiveDefrostHeaterCapacity, RegionnumberforcalculatingHSPF, EvaporatorAirInletNodeName, ZoneNameforEvaporatorPlacement, SecondaryCoilAirFlowRate, SecondaryCoilFanFlowScalingFactor, NominalSensibleHeatRatioofSecondaryCoil, SensibleHeatRatioModifierFunctionofTemperatureCurveName, SensibleHeatRatioModifierFunctionofFlowFractionCurveName,   };
  Coil_Heating_DX_SingleSpeedFields()
   : EnumBase<Coil_Heating_DX_SingleSpeedFields>(Name) {} 
  Coil_Heating_DX_SingleSpeedFields(const std::string &t_name) 
   : EnumBase<Coil_Heating_DX_SingleSpeedFields>(t_name) {} 
  Coil_Heating_DX_SingleSpeedFields(int t_value) 
   : EnumBase<Coil_Heating_DX_SingleSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Heating_DX_SingleSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Heating_DX_SingleSpeedFields>::value()); }
   private:
    friend class EnumBase<Coil_Heating_DX_SingleSpeedFields>;
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
{ Coil_Heating_DX_SingleSpeedFields::Name, "Name", "Name"},
{ Coil_Heating_DX_SingleSpeedFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Coil_Heating_DX_SingleSpeedFields::GrossRatedHeatingCapacity, "GrossRatedHeatingCapacity", "Gross Rated Heating Capacity"},
{ Coil_Heating_DX_SingleSpeedFields::GrossRatedHeatingCOP, "GrossRatedHeatingCOP", "Gross Rated Heating COP"},
{ Coil_Heating_DX_SingleSpeedFields::RatedAirFlowRate, "RatedAirFlowRate", "Rated Air Flow Rate"},
{ Coil_Heating_DX_SingleSpeedFields::RatedSupplyFanPowerPerVolumeFlowRate, "RatedSupplyFanPowerPerVolumeFlowRate", "Rated Supply Fan Power Per Volume Flow Rate"},
{ Coil_Heating_DX_SingleSpeedFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Coil_Heating_DX_SingleSpeedFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Coil_Heating_DX_SingleSpeedFields::HeatingCapacityFunctionofTemperatureCurveName, "HeatingCapacityFunctionofTemperatureCurveName", "Heating Capacity Function of Temperature Curve Name"},
{ Coil_Heating_DX_SingleSpeedFields::HeatingCapacityFunctionofFlowFractionCurveName, "HeatingCapacityFunctionofFlowFractionCurveName", "Heating Capacity Function of Flow Fraction Curve Name"},
{ Coil_Heating_DX_SingleSpeedFields::EnergyInputRatioFunctionofTemperatureCurveName, "EnergyInputRatioFunctionofTemperatureCurveName", "Energy Input Ratio Function of Temperature Curve Name"},
{ Coil_Heating_DX_SingleSpeedFields::EnergyInputRatioFunctionofFlowFractionCurveName, "EnergyInputRatioFunctionofFlowFractionCurveName", "Energy Input Ratio Function of Flow Fraction Curve Name"},
{ Coil_Heating_DX_SingleSpeedFields::PartLoadFractionCorrelationCurveName, "PartLoadFractionCorrelationCurveName", "Part Load Fraction Correlation Curve Name"},
{ Coil_Heating_DX_SingleSpeedFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName, "DefrostEnergyInputRatioFunctionofTemperatureCurveName", "Defrost Energy Input Ratio Function of Temperature Curve Name"},
{ Coil_Heating_DX_SingleSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, "MinimumOutdoorDryBulbTemperatureforCompressorOperation", "Minimum Outdoor Dry-Bulb Temperature for Compressor Operation"},
{ Coil_Heating_DX_SingleSpeedFields::OutdoorDryBulbTemperaturetoTurnOnCompressor, "OutdoorDryBulbTemperaturetoTurnOnCompressor", "Outdoor Dry-Bulb Temperature to Turn On Compressor"},
{ Coil_Heating_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforDefrostOperation, "MaximumOutdoorDryBulbTemperatureforDefrostOperation", "Maximum Outdoor Dry-Bulb Temperature for Defrost Operation"},
{ Coil_Heating_DX_SingleSpeedFields::CrankcaseHeaterCapacity, "CrankcaseHeaterCapacity", "Crankcase Heater Capacity"},
{ Coil_Heating_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, "MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Crankcase Heater Operation"},
{ Coil_Heating_DX_SingleSpeedFields::DefrostStrategy, "DefrostStrategy", "Defrost Strategy"},
{ Coil_Heating_DX_SingleSpeedFields::DefrostControl, "DefrostControl", "Defrost Control"},
{ Coil_Heating_DX_SingleSpeedFields::DefrostTimePeriodFraction, "DefrostTimePeriodFraction", "Defrost Time Period Fraction"},
{ Coil_Heating_DX_SingleSpeedFields::ResistiveDefrostHeaterCapacity, "ResistiveDefrostHeaterCapacity", "Resistive Defrost Heater Capacity"},
{ Coil_Heating_DX_SingleSpeedFields::RegionnumberforcalculatingHSPF, "RegionnumberforcalculatingHSPF", "Region number for calculating HSPF"},
{ Coil_Heating_DX_SingleSpeedFields::EvaporatorAirInletNodeName, "EvaporatorAirInletNodeName", "Evaporator Air Inlet Node Name"},
{ Coil_Heating_DX_SingleSpeedFields::ZoneNameforEvaporatorPlacement, "ZoneNameforEvaporatorPlacement", "Zone Name for Evaporator Placement"},
{ Coil_Heating_DX_SingleSpeedFields::SecondaryCoilAirFlowRate, "SecondaryCoilAirFlowRate", "Secondary Coil Air Flow Rate"},
{ Coil_Heating_DX_SingleSpeedFields::SecondaryCoilFanFlowScalingFactor, "SecondaryCoilFanFlowScalingFactor", "Secondary Coil Fan Flow Scaling Factor"},
{ Coil_Heating_DX_SingleSpeedFields::NominalSensibleHeatRatioofSecondaryCoil, "NominalSensibleHeatRatioofSecondaryCoil", "Nominal Sensible Heat Ratio of Secondary Coil"},
{ Coil_Heating_DX_SingleSpeedFields::SensibleHeatRatioModifierFunctionofTemperatureCurveName, "SensibleHeatRatioModifierFunctionofTemperatureCurveName", "Sensible Heat Ratio Modifier Function of Temperature Curve Name"},
{ Coil_Heating_DX_SingleSpeedFields::SensibleHeatRatioModifierFunctionofFlowFractionCurveName, "SensibleHeatRatioModifierFunctionofFlowFractionCurveName", "Sensible Heat Ratio Modifier Function of Flow Fraction Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Heating_DX_SingleSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Heating_DX_SingleSpeedFields> OptionalCoil_Heating_DX_SingleSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_HEATING_DX_SINGLESPEED_FIELDENUMS_HXX
