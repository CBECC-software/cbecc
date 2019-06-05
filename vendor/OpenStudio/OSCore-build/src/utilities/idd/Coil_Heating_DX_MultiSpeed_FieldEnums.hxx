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
