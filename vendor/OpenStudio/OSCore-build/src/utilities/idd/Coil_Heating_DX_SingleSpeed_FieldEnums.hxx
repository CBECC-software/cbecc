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
