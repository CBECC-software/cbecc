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

#ifndef UTILITIES_IDD_COIL_HEATING_DX_VARIABLESPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_HEATING_DX_VARIABLESPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Heating_DX_VariableSpeedFields
 *  \brief Enumeration of Coil:Heating:DX:VariableSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Heating_DX_VariableSpeedFields, )
#else
class Coil_Heating_DX_VariableSpeedFields: public ::EnumBase<Coil_Heating_DX_VariableSpeedFields> {
 public: 
  enum domain 
  {
Name, IndoorAirInletNodeName, IndoorAirOutletNodeName, NumberofSpeeds, NominalSpeedLevel, RatedHeatingCapacityAtSelectedNominalSpeedLevel, RatedAirFlowRateAtSelectedNominalSpeedLevel, EnergyPartLoadFractionCurveName, DefrostEnergyInputRatioFunctionofTemperatureCurveName, MinimumOutdoorDryBulbTemperatureforCompressorOperation, OutdoorDryBulbTemperaturetoTurnOnCompressor, MaximumOutdoorDryBulbTemperatureforDefrostOperation, CrankcaseHeaterCapacity, MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, DefrostStrategy, DefrostControl, DefrostTimePeriodFraction, ResistiveDefrostHeaterCapacity,   };
  Coil_Heating_DX_VariableSpeedFields()
   : EnumBase<Coil_Heating_DX_VariableSpeedFields>(Name) {} 
  Coil_Heating_DX_VariableSpeedFields(const std::string &t_name) 
   : EnumBase<Coil_Heating_DX_VariableSpeedFields>(t_name) {} 
  Coil_Heating_DX_VariableSpeedFields(int t_value) 
   : EnumBase<Coil_Heating_DX_VariableSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Heating_DX_VariableSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Heating_DX_VariableSpeedFields>::value()); }
   private:
    friend class EnumBase<Coil_Heating_DX_VariableSpeedFields>;
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
{ Coil_Heating_DX_VariableSpeedFields::Name, "Name", "Name"},
{ Coil_Heating_DX_VariableSpeedFields::IndoorAirInletNodeName, "IndoorAirInletNodeName", "Indoor Air Inlet Node Name"},
{ Coil_Heating_DX_VariableSpeedFields::IndoorAirOutletNodeName, "IndoorAirOutletNodeName", "Indoor Air Outlet Node Name"},
{ Coil_Heating_DX_VariableSpeedFields::NumberofSpeeds, "NumberofSpeeds", "Number of Speeds"},
{ Coil_Heating_DX_VariableSpeedFields::NominalSpeedLevel, "NominalSpeedLevel", "Nominal Speed Level"},
{ Coil_Heating_DX_VariableSpeedFields::RatedHeatingCapacityAtSelectedNominalSpeedLevel, "RatedHeatingCapacityAtSelectedNominalSpeedLevel", "Rated Heating Capacity At Selected Nominal Speed Level"},
{ Coil_Heating_DX_VariableSpeedFields::RatedAirFlowRateAtSelectedNominalSpeedLevel, "RatedAirFlowRateAtSelectedNominalSpeedLevel", "Rated Air Flow Rate At Selected Nominal Speed Level"},
{ Coil_Heating_DX_VariableSpeedFields::EnergyPartLoadFractionCurveName, "EnergyPartLoadFractionCurveName", "Energy Part Load Fraction Curve Name"},
{ Coil_Heating_DX_VariableSpeedFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName, "DefrostEnergyInputRatioFunctionofTemperatureCurveName", "Defrost Energy Input Ratio Function of Temperature Curve Name"},
{ Coil_Heating_DX_VariableSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, "MinimumOutdoorDryBulbTemperatureforCompressorOperation", "Minimum Outdoor Dry-Bulb Temperature for Compressor Operation"},
{ Coil_Heating_DX_VariableSpeedFields::OutdoorDryBulbTemperaturetoTurnOnCompressor, "OutdoorDryBulbTemperaturetoTurnOnCompressor", "Outdoor Dry-Bulb Temperature to Turn On Compressor"},
{ Coil_Heating_DX_VariableSpeedFields::MaximumOutdoorDryBulbTemperatureforDefrostOperation, "MaximumOutdoorDryBulbTemperatureforDefrostOperation", "Maximum Outdoor Dry-Bulb Temperature for Defrost Operation"},
{ Coil_Heating_DX_VariableSpeedFields::CrankcaseHeaterCapacity, "CrankcaseHeaterCapacity", "Crankcase Heater Capacity"},
{ Coil_Heating_DX_VariableSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, "MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Crankcase Heater Operation"},
{ Coil_Heating_DX_VariableSpeedFields::DefrostStrategy, "DefrostStrategy", "Defrost Strategy"},
{ Coil_Heating_DX_VariableSpeedFields::DefrostControl, "DefrostControl", "Defrost Control"},
{ Coil_Heating_DX_VariableSpeedFields::DefrostTimePeriodFraction, "DefrostTimePeriodFraction", "Defrost Time Period Fraction"},
{ Coil_Heating_DX_VariableSpeedFields::ResistiveDefrostHeaterCapacity, "ResistiveDefrostHeaterCapacity", "Resistive Defrost Heater Capacity"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Heating_DX_VariableSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Heating_DX_VariableSpeedFields> OptionalCoil_Heating_DX_VariableSpeedFields ;
#endif

/** \class Coil_Heating_DX_VariableSpeedExtensibleFields
 *  \brief Enumeration of Coil:Heating:DX:VariableSpeed's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Coil_Heating_DX_VariableSpeedExtensibleFields, )
#else
class Coil_Heating_DX_VariableSpeedExtensibleFields: public ::EnumBase<Coil_Heating_DX_VariableSpeedExtensibleFields> {
 public: 
  enum domain 
  {
SpeedReferenceUnitGrossRatedHeatingCapacity, SpeedReferenceUnitGrossRatedHeatingCOP, SpeedReferenceUnitRatedAirFlowRate, SpeedHeatingCapacityFunctionofTemperatureCurveName, SpeedTotalHeatingCapacityFunctionofAirFlowFractionCurveName, SpeedEnergyInputRatioFunctionofTemperatureCurveName, SpeedEnergyInputRatioFunctionofAirFlowFractionCurveName,   };
  Coil_Heating_DX_VariableSpeedExtensibleFields()
   : EnumBase<Coil_Heating_DX_VariableSpeedExtensibleFields>(SpeedReferenceUnitGrossRatedHeatingCapacity) {} 
  Coil_Heating_DX_VariableSpeedExtensibleFields(const std::string &t_name) 
   : EnumBase<Coil_Heating_DX_VariableSpeedExtensibleFields>(t_name) {} 
  Coil_Heating_DX_VariableSpeedExtensibleFields(int t_value) 
   : EnumBase<Coil_Heating_DX_VariableSpeedExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Heating_DX_VariableSpeedExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Heating_DX_VariableSpeedExtensibleFields>::value()); }
   private:
    friend class EnumBase<Coil_Heating_DX_VariableSpeedExtensibleFields>;
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
{ Coil_Heating_DX_VariableSpeedExtensibleFields::SpeedReferenceUnitGrossRatedHeatingCapacity, "SpeedReferenceUnitGrossRatedHeatingCapacity", "Speed Reference Unit Gross Rated Heating Capacity"},
{ Coil_Heating_DX_VariableSpeedExtensibleFields::SpeedReferenceUnitGrossRatedHeatingCOP, "SpeedReferenceUnitGrossRatedHeatingCOP", "Speed Reference Unit Gross Rated Heating COP"},
{ Coil_Heating_DX_VariableSpeedExtensibleFields::SpeedReferenceUnitRatedAirFlowRate, "SpeedReferenceUnitRatedAirFlowRate", "Speed Reference Unit Rated Air Flow Rate"},
{ Coil_Heating_DX_VariableSpeedExtensibleFields::SpeedHeatingCapacityFunctionofTemperatureCurveName, "SpeedHeatingCapacityFunctionofTemperatureCurveName", "Speed Heating Capacity Function of Temperature Curve Name"},
{ Coil_Heating_DX_VariableSpeedExtensibleFields::SpeedTotalHeatingCapacityFunctionofAirFlowFractionCurveName, "SpeedTotalHeatingCapacityFunctionofAirFlowFractionCurveName", "Speed Total  Heating Capacity Function of Air Flow Fraction Curve Name"},
{ Coil_Heating_DX_VariableSpeedExtensibleFields::SpeedEnergyInputRatioFunctionofTemperatureCurveName, "SpeedEnergyInputRatioFunctionofTemperatureCurveName", "Speed Energy Input Ratio Function of Temperature Curve Name"},
{ Coil_Heating_DX_VariableSpeedExtensibleFields::SpeedEnergyInputRatioFunctionofAirFlowFractionCurveName, "SpeedEnergyInputRatioFunctionofAirFlowFractionCurveName", "Speed Energy Input Ratio Function of Air Flow Fraction Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Heating_DX_VariableSpeedExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Heating_DX_VariableSpeedExtensibleFields> OptionalCoil_Heating_DX_VariableSpeedExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_HEATING_DX_VARIABLESPEED_FIELDENUMS_HXX
