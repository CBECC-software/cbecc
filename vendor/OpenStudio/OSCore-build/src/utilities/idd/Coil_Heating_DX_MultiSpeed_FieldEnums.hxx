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

#ifndef UTILITIES_IDD_COIL_HEATING_DX_MULTISPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_HEATING_DX_MULTISPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Heating_DX_MultiSpeedFields
 *  \brief Enumeration of Coil:Heating:DX:MultiSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Heating_DX_MultiSpeedFields, )
#else
class Coil_Heating_DX_MultiSpeedFields: public ::EnumBase<Coil_Heating_DX_MultiSpeedFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, MinimumOutdoorDryBulbTemperatureforCompressorOperation, OutdoorDryBulbTemperaturetoTurnOnCompressor, CrankcaseHeaterCapacity, MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, DefrostEnergyInputRatioFunctionofTemperatureCurveName, MaximumOutdoorDryBulbTemperatureforDefrostOperation, DefrostStrategy, DefrostControl, DefrostTimePeriodFraction, ResistiveDefrostHeaterCapacity, ApplyPartLoadFractiontoSpeedsGreaterthan1, FuelType, RegionnumberforCalculatingHSPF, NumberofSpeeds,   };
  Coil_Heating_DX_MultiSpeedFields()
   : EnumBase<Coil_Heating_DX_MultiSpeedFields>(Name) {} 
  Coil_Heating_DX_MultiSpeedFields(const std::string &t_name) 
   : EnumBase<Coil_Heating_DX_MultiSpeedFields>(t_name) {} 
  Coil_Heating_DX_MultiSpeedFields(int t_value) 
   : EnumBase<Coil_Heating_DX_MultiSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Heating_DX_MultiSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Heating_DX_MultiSpeedFields>::value()); }
   private:
    friend class EnumBase<Coil_Heating_DX_MultiSpeedFields>;
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
{ Coil_Heating_DX_MultiSpeedFields::Name, "Name", "Name"},
{ Coil_Heating_DX_MultiSpeedFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Coil_Heating_DX_MultiSpeedFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Coil_Heating_DX_MultiSpeedFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Coil_Heating_DX_MultiSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, "MinimumOutdoorDryBulbTemperatureforCompressorOperation", "Minimum Outdoor Dry-Bulb Temperature for Compressor Operation"},
{ Coil_Heating_DX_MultiSpeedFields::OutdoorDryBulbTemperaturetoTurnOnCompressor, "OutdoorDryBulbTemperaturetoTurnOnCompressor", "Outdoor Dry-Bulb Temperature to Turn On Compressor"},
{ Coil_Heating_DX_MultiSpeedFields::CrankcaseHeaterCapacity, "CrankcaseHeaterCapacity", "Crankcase Heater Capacity"},
{ Coil_Heating_DX_MultiSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, "MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Crankcase Heater Operation"},
{ Coil_Heating_DX_MultiSpeedFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName, "DefrostEnergyInputRatioFunctionofTemperatureCurveName", "Defrost Energy Input Ratio Function of Temperature Curve Name"},
{ Coil_Heating_DX_MultiSpeedFields::MaximumOutdoorDryBulbTemperatureforDefrostOperation, "MaximumOutdoorDryBulbTemperatureforDefrostOperation", "Maximum Outdoor Dry-Bulb Temperature for Defrost Operation"},
{ Coil_Heating_DX_MultiSpeedFields::DefrostStrategy, "DefrostStrategy", "Defrost Strategy"},
{ Coil_Heating_DX_MultiSpeedFields::DefrostControl, "DefrostControl", "Defrost Control"},
{ Coil_Heating_DX_MultiSpeedFields::DefrostTimePeriodFraction, "DefrostTimePeriodFraction", "Defrost Time Period Fraction"},
{ Coil_Heating_DX_MultiSpeedFields::ResistiveDefrostHeaterCapacity, "ResistiveDefrostHeaterCapacity", "Resistive Defrost Heater Capacity"},
{ Coil_Heating_DX_MultiSpeedFields::ApplyPartLoadFractiontoSpeedsGreaterthan1, "ApplyPartLoadFractiontoSpeedsGreaterthan1", "Apply Part Load Fraction to Speeds Greater than 1"},
{ Coil_Heating_DX_MultiSpeedFields::FuelType, "FuelType", "Fuel Type"},
{ Coil_Heating_DX_MultiSpeedFields::RegionnumberforCalculatingHSPF, "RegionnumberforCalculatingHSPF", "Region number for Calculating HSPF"},
{ Coil_Heating_DX_MultiSpeedFields::NumberofSpeeds, "NumberofSpeeds", "Number of Speeds"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Heating_DX_MultiSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Heating_DX_MultiSpeedFields> OptionalCoil_Heating_DX_MultiSpeedFields ;
#endif

/** \class Coil_Heating_DX_MultiSpeedExtensibleFields
 *  \brief Enumeration of Coil:Heating:DX:MultiSpeed's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Coil_Heating_DX_MultiSpeedExtensibleFields, )
#else
class Coil_Heating_DX_MultiSpeedExtensibleFields: public ::EnumBase<Coil_Heating_DX_MultiSpeedExtensibleFields> {
 public: 
  enum domain 
  {
SpeedGrossRatedHeatingCapacity, SpeedGrossRatedHeatingCOP, SpeedRatedAirFlowRate, SpeedRatedSupplyAirFanPowerPerVolumeFlowRate, SpeedHeatingCapacityFunctionofTemperatureCurveName, SpeedHeatingCapacityFunctionofFlowFractionCurveName, SpeedEnergyInputRatioFunctionofTemperatureCurveName, SpeedEnergyInputRatioFunctionofFlowFractionCurveName, SpeedPartLoadFractionCorrelationCurveName, SpeedRatedWasteHeatFractionofPowerInput, SpeedWasteHeatFunctionofTemperatureCurveName,   };
  Coil_Heating_DX_MultiSpeedExtensibleFields()
   : EnumBase<Coil_Heating_DX_MultiSpeedExtensibleFields>(SpeedGrossRatedHeatingCapacity) {} 
  Coil_Heating_DX_MultiSpeedExtensibleFields(const std::string &t_name) 
   : EnumBase<Coil_Heating_DX_MultiSpeedExtensibleFields>(t_name) {} 
  Coil_Heating_DX_MultiSpeedExtensibleFields(int t_value) 
   : EnumBase<Coil_Heating_DX_MultiSpeedExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Heating_DX_MultiSpeedExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Heating_DX_MultiSpeedExtensibleFields>::value()); }
   private:
    friend class EnumBase<Coil_Heating_DX_MultiSpeedExtensibleFields>;
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
{ Coil_Heating_DX_MultiSpeedExtensibleFields::SpeedGrossRatedHeatingCapacity, "SpeedGrossRatedHeatingCapacity", "Speed Gross Rated Heating Capacity"},
{ Coil_Heating_DX_MultiSpeedExtensibleFields::SpeedGrossRatedHeatingCOP, "SpeedGrossRatedHeatingCOP", "Speed Gross Rated Heating COP"},
{ Coil_Heating_DX_MultiSpeedExtensibleFields::SpeedRatedAirFlowRate, "SpeedRatedAirFlowRate", "Speed Rated Air Flow Rate"},
{ Coil_Heating_DX_MultiSpeedExtensibleFields::SpeedRatedSupplyAirFanPowerPerVolumeFlowRate, "SpeedRatedSupplyAirFanPowerPerVolumeFlowRate", "Speed Rated Supply Air Fan Power Per Volume Flow Rate"},
{ Coil_Heating_DX_MultiSpeedExtensibleFields::SpeedHeatingCapacityFunctionofTemperatureCurveName, "SpeedHeatingCapacityFunctionofTemperatureCurveName", "Speed Heating Capacity Function of Temperature Curve Name"},
{ Coil_Heating_DX_MultiSpeedExtensibleFields::SpeedHeatingCapacityFunctionofFlowFractionCurveName, "SpeedHeatingCapacityFunctionofFlowFractionCurveName", "Speed Heating Capacity Function of Flow Fraction Curve Name"},
{ Coil_Heating_DX_MultiSpeedExtensibleFields::SpeedEnergyInputRatioFunctionofTemperatureCurveName, "SpeedEnergyInputRatioFunctionofTemperatureCurveName", "Speed Energy Input Ratio Function of Temperature Curve Name"},
{ Coil_Heating_DX_MultiSpeedExtensibleFields::SpeedEnergyInputRatioFunctionofFlowFractionCurveName, "SpeedEnergyInputRatioFunctionofFlowFractionCurveName", "Speed Energy Input Ratio Function of Flow Fraction Curve Name"},
{ Coil_Heating_DX_MultiSpeedExtensibleFields::SpeedPartLoadFractionCorrelationCurveName, "SpeedPartLoadFractionCorrelationCurveName", "Speed Part Load Fraction Correlation Curve Name"},
{ Coil_Heating_DX_MultiSpeedExtensibleFields::SpeedRatedWasteHeatFractionofPowerInput, "SpeedRatedWasteHeatFractionofPowerInput", "Speed Rated Waste Heat Fraction of Power Input"},
{ Coil_Heating_DX_MultiSpeedExtensibleFields::SpeedWasteHeatFunctionofTemperatureCurveName, "SpeedWasteHeatFunctionofTemperatureCurveName", "Speed Waste Heat Function of Temperature Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Heating_DX_MultiSpeedExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Heating_DX_MultiSpeedExtensibleFields> OptionalCoil_Heating_DX_MultiSpeedExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_HEATING_DX_MULTISPEED_FIELDENUMS_HXX
