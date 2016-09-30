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

#ifndef UTILITIES_IDD_OS_COIL_HEATING_DX_SINGLESPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_HEATING_DX_SINGLESPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_Heating_DX_SingleSpeedFields
 *  \brief Enumeration of OS:Coil:Heating:DX:SingleSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_Heating_DX_SingleSpeedFields, )
#else
class OS_Coil_Heating_DX_SingleSpeedFields: public ::EnumBase<OS_Coil_Heating_DX_SingleSpeedFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, RatedTotalHeatingCapacity, RatedCOP, RatedAirFlowRate, AirInletNodeName, AirOutletNodeName, TotalHeatingCapacityFunctionofTemperatureCurveName, TotalHeatingCapacityFunctionofFlowFractionCurveName, EnergyInputRatioFunctionofTemperatureCurveName, EnergyInputRatioFunctionofFlowFractionCurveName, PartLoadFractionCorrelationCurveName, DefrostEnergyInputRatioFunctionofTemperatureCurveName, MinimumOutdoorDryBulbTemperatureforCompressorOperation, MaximumOutdoorDryBulbTemperatureforDefrostOperation, CrankcaseHeaterCapacity, MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, DefrostStrategy, DefrostControl, DefrostTimePeriodFraction, ResistiveDefrostHeaterCapacity,   };
  OS_Coil_Heating_DX_SingleSpeedFields()
   : EnumBase<OS_Coil_Heating_DX_SingleSpeedFields>(Handle) {} 
  OS_Coil_Heating_DX_SingleSpeedFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Heating_DX_SingleSpeedFields>(t_name) {} 
  OS_Coil_Heating_DX_SingleSpeedFields(int t_value) 
   : EnumBase<OS_Coil_Heating_DX_SingleSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Heating_DX_SingleSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Heating_DX_SingleSpeedFields>::value()); }
   private:
    friend class EnumBase<OS_Coil_Heating_DX_SingleSpeedFields>;
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
{ OS_Coil_Heating_DX_SingleSpeedFields::Handle, "Handle", "Handle"},
{ OS_Coil_Heating_DX_SingleSpeedFields::Name, "Name", "Name"},
{ OS_Coil_Heating_DX_SingleSpeedFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_Coil_Heating_DX_SingleSpeedFields::RatedTotalHeatingCapacity, "RatedTotalHeatingCapacity", "Rated Total Heating Capacity"},
{ OS_Coil_Heating_DX_SingleSpeedFields::RatedCOP, "RatedCOP", "Rated COP"},
{ OS_Coil_Heating_DX_SingleSpeedFields::RatedAirFlowRate, "RatedAirFlowRate", "Rated Air Flow Rate"},
{ OS_Coil_Heating_DX_SingleSpeedFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_Coil_Heating_DX_SingleSpeedFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_Coil_Heating_DX_SingleSpeedFields::TotalHeatingCapacityFunctionofTemperatureCurveName, "TotalHeatingCapacityFunctionofTemperatureCurveName", "Total Heating Capacity Function of Temperature Curve Name"},
{ OS_Coil_Heating_DX_SingleSpeedFields::TotalHeatingCapacityFunctionofFlowFractionCurveName, "TotalHeatingCapacityFunctionofFlowFractionCurveName", "Total Heating Capacity Function of Flow Fraction Curve Name"},
{ OS_Coil_Heating_DX_SingleSpeedFields::EnergyInputRatioFunctionofTemperatureCurveName, "EnergyInputRatioFunctionofTemperatureCurveName", "Energy Input Ratio Function of Temperature Curve Name"},
{ OS_Coil_Heating_DX_SingleSpeedFields::EnergyInputRatioFunctionofFlowFractionCurveName, "EnergyInputRatioFunctionofFlowFractionCurveName", "Energy Input Ratio Function of Flow Fraction Curve Name"},
{ OS_Coil_Heating_DX_SingleSpeedFields::PartLoadFractionCorrelationCurveName, "PartLoadFractionCorrelationCurveName", "Part Load Fraction Correlation Curve Name"},
{ OS_Coil_Heating_DX_SingleSpeedFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName, "DefrostEnergyInputRatioFunctionofTemperatureCurveName", "Defrost Energy Input Ratio Function of Temperature Curve Name"},
{ OS_Coil_Heating_DX_SingleSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, "MinimumOutdoorDryBulbTemperatureforCompressorOperation", "Minimum Outdoor Dry-Bulb Temperature for Compressor Operation"},
{ OS_Coil_Heating_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforDefrostOperation, "MaximumOutdoorDryBulbTemperatureforDefrostOperation", "Maximum Outdoor Dry-Bulb Temperature for Defrost Operation"},
{ OS_Coil_Heating_DX_SingleSpeedFields::CrankcaseHeaterCapacity, "CrankcaseHeaterCapacity", "Crankcase Heater Capacity"},
{ OS_Coil_Heating_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, "MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Crankcase Heater Operation"},
{ OS_Coil_Heating_DX_SingleSpeedFields::DefrostStrategy, "DefrostStrategy", "Defrost Strategy"},
{ OS_Coil_Heating_DX_SingleSpeedFields::DefrostControl, "DefrostControl", "Defrost Control"},
{ OS_Coil_Heating_DX_SingleSpeedFields::DefrostTimePeriodFraction, "DefrostTimePeriodFraction", "Defrost Time Period Fraction"},
{ OS_Coil_Heating_DX_SingleSpeedFields::ResistiveDefrostHeaterCapacity, "ResistiveDefrostHeaterCapacity", "Resistive Defrost Heater Capacity"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Heating_DX_SingleSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Heating_DX_SingleSpeedFields> OptionalOS_Coil_Heating_DX_SingleSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_HEATING_DX_SINGLESPEED_FIELDENUMS_HXX
