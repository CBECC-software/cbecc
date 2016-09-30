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

#ifndef UTILITIES_IDD_OS_REFRIGERATION_AIRCHILLER_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_REFRIGERATION_AIRCHILLER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Refrigeration_AirChillerFields
 *  \brief Enumeration of OS:Refrigeration:AirChiller's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Refrigeration_AirChillerFields, )
#else
class OS_Refrigeration_AirChillerFields: public ::EnumBase<OS_Refrigeration_AirChillerFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, CapacityRatingType, RatedUnitLoadFactor, RatedCapacity, RatedRelativeHumidity, RatedCoolingSourceTemperature, RatedTemperatureDifferenceDT1, MaximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature, CoilMaterialCorrectionFactor, RefrigerantCorrectionFactor, CapacityCorrectionCurveType, CapacityCorrectionCurveName, SHR60CorrectionFactor, RatedTotalHeatingPower, HeatingPowerScheduleName, FanSpeedControlType, RatedFanPower, RatedAirFlow, MinimumFanAirFlowRatio, DefrostType, DefrostControlType, DefrostScheduleName, DefrostDripDownScheduleName, DefrostPower, TemperatureTerminationDefrostFractiontoIce, VerticalLocation, AverageRefrigerantChargeInventory,   };
  OS_Refrigeration_AirChillerFields()
   : EnumBase<OS_Refrigeration_AirChillerFields>(Handle) {} 
  OS_Refrigeration_AirChillerFields(const std::string &t_name) 
   : EnumBase<OS_Refrigeration_AirChillerFields>(t_name) {} 
  OS_Refrigeration_AirChillerFields(int t_value) 
   : EnumBase<OS_Refrigeration_AirChillerFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Refrigeration_AirChillerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Refrigeration_AirChillerFields>::value()); }
   private:
    friend class EnumBase<OS_Refrigeration_AirChillerFields>;
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
{ OS_Refrigeration_AirChillerFields::Handle, "Handle", "Handle"},
{ OS_Refrigeration_AirChillerFields::Name, "Name", "Name"},
{ OS_Refrigeration_AirChillerFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_Refrigeration_AirChillerFields::CapacityRatingType, "CapacityRatingType", "Capacity Rating Type"},
{ OS_Refrigeration_AirChillerFields::RatedUnitLoadFactor, "RatedUnitLoadFactor", "Rated Unit Load Factor"},
{ OS_Refrigeration_AirChillerFields::RatedCapacity, "RatedCapacity", "Rated Capacity"},
{ OS_Refrigeration_AirChillerFields::RatedRelativeHumidity, "RatedRelativeHumidity", "Rated Relative Humidity"},
{ OS_Refrigeration_AirChillerFields::RatedCoolingSourceTemperature, "RatedCoolingSourceTemperature", "Rated Cooling Source Temperature"},
{ OS_Refrigeration_AirChillerFields::RatedTemperatureDifferenceDT1, "RatedTemperatureDifferenceDT1", "Rated Temperature Difference DT1"},
{ OS_Refrigeration_AirChillerFields::MaximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature, "MaximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature", "Maximum Temperature Difference Between Inlet Air and Evaporating Temperature"},
{ OS_Refrigeration_AirChillerFields::CoilMaterialCorrectionFactor, "CoilMaterialCorrectionFactor", "Coil Material Correction Factor"},
{ OS_Refrigeration_AirChillerFields::RefrigerantCorrectionFactor, "RefrigerantCorrectionFactor", "Refrigerant Correction Factor"},
{ OS_Refrigeration_AirChillerFields::CapacityCorrectionCurveType, "CapacityCorrectionCurveType", "Capacity Correction Curve Type"},
{ OS_Refrigeration_AirChillerFields::CapacityCorrectionCurveName, "CapacityCorrectionCurveName", "Capacity Correction Curve Name"},
{ OS_Refrigeration_AirChillerFields::SHR60CorrectionFactor, "SHR60CorrectionFactor", "SHR60 Correction Factor"},
{ OS_Refrigeration_AirChillerFields::RatedTotalHeatingPower, "RatedTotalHeatingPower", "Rated Total Heating Power"},
{ OS_Refrigeration_AirChillerFields::HeatingPowerScheduleName, "HeatingPowerScheduleName", "Heating Power Schedule Name"},
{ OS_Refrigeration_AirChillerFields::FanSpeedControlType, "FanSpeedControlType", "Fan Speed Control Type"},
{ OS_Refrigeration_AirChillerFields::RatedFanPower, "RatedFanPower", "Rated Fan Power"},
{ OS_Refrigeration_AirChillerFields::RatedAirFlow, "RatedAirFlow", "Rated Air Flow"},
{ OS_Refrigeration_AirChillerFields::MinimumFanAirFlowRatio, "MinimumFanAirFlowRatio", "Minimum Fan Air Flow Ratio"},
{ OS_Refrigeration_AirChillerFields::DefrostType, "DefrostType", "Defrost Type"},
{ OS_Refrigeration_AirChillerFields::DefrostControlType, "DefrostControlType", "Defrost Control Type"},
{ OS_Refrigeration_AirChillerFields::DefrostScheduleName, "DefrostScheduleName", "Defrost Schedule Name"},
{ OS_Refrigeration_AirChillerFields::DefrostDripDownScheduleName, "DefrostDripDownScheduleName", "Defrost Drip-Down Schedule Name"},
{ OS_Refrigeration_AirChillerFields::DefrostPower, "DefrostPower", "Defrost Power"},
{ OS_Refrigeration_AirChillerFields::TemperatureTerminationDefrostFractiontoIce, "TemperatureTerminationDefrostFractiontoIce", "Temperature Termination Defrost Fraction to Ice"},
{ OS_Refrigeration_AirChillerFields::VerticalLocation, "VerticalLocation", "Vertical Location"},
{ OS_Refrigeration_AirChillerFields::AverageRefrigerantChargeInventory, "AverageRefrigerantChargeInventory", "Average Refrigerant Charge Inventory"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Refrigeration_AirChillerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Refrigeration_AirChillerFields> OptionalOS_Refrigeration_AirChillerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_REFRIGERATION_AIRCHILLER_FIELDENUMS_HXX
