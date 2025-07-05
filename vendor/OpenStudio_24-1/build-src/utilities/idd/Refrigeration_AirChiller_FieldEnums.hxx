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

#ifndef UTILITIES_IDD_REFRIGERATION_AIRCHILLER_FIELDENUMS_HXX
#define UTILITIES_IDD_REFRIGERATION_AIRCHILLER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Refrigeration_AirChillerFields
 *  \brief Enumeration of Refrigeration:AirChiller's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Refrigeration_AirChillerFields, )
#else
class Refrigeration_AirChillerFields: public ::EnumBase<Refrigeration_AirChillerFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, CapacityRatingType, RatedUnitLoadFactor, RatedCapacity, RatedRelativeHumidity, RatedCoolingSourceTemperature, RatedTemperatureDifferenceDT1, MaximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature, CoilMaterialCorrectionFactor, RefrigerantCorrectionFactor, CapacityCorrectionCurveType, CapacityCorrectionCurveName, SHR60CorrectionFactor, RatedTotalHeatingPower, HeatingPowerScheduleName, FanSpeedControlType, RatedFanPower, RatedAirFlow, MinimumFanAirFlowRatio, DefrostType, DefrostControlType, DefrostScheduleName, DefrostDripDownScheduleName, DefrostPower, TemperatureTerminationDefrostFractiontoIce, VerticalLocation, AverageRefrigerantChargeInventory,   };
  Refrigeration_AirChillerFields()
   : EnumBase<Refrigeration_AirChillerFields>(Name) {} 
  Refrigeration_AirChillerFields(const std::string &t_name) 
   : EnumBase<Refrigeration_AirChillerFields>(t_name) {} 
  Refrigeration_AirChillerFields(int t_value) 
   : EnumBase<Refrigeration_AirChillerFields>(t_value) {} 
  static std::string enumName() 
  { return "Refrigeration_AirChillerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Refrigeration_AirChillerFields>::value()); }
   private:
    friend class EnumBase<Refrigeration_AirChillerFields>;
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
{ Refrigeration_AirChillerFields::Name, "Name", "Name"},
{ Refrigeration_AirChillerFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Refrigeration_AirChillerFields::CapacityRatingType, "CapacityRatingType", "Capacity Rating Type"},
{ Refrigeration_AirChillerFields::RatedUnitLoadFactor, "RatedUnitLoadFactor", "Rated Unit Load Factor"},
{ Refrigeration_AirChillerFields::RatedCapacity, "RatedCapacity", "Rated Capacity"},
{ Refrigeration_AirChillerFields::RatedRelativeHumidity, "RatedRelativeHumidity", "Rated Relative Humidity"},
{ Refrigeration_AirChillerFields::RatedCoolingSourceTemperature, "RatedCoolingSourceTemperature", "Rated Cooling Source Temperature"},
{ Refrigeration_AirChillerFields::RatedTemperatureDifferenceDT1, "RatedTemperatureDifferenceDT1", "Rated Temperature Difference DT1"},
{ Refrigeration_AirChillerFields::MaximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature, "MaximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature", "Maximum Temperature Difference Between Inlet Air and Evaporating Temperature"},
{ Refrigeration_AirChillerFields::CoilMaterialCorrectionFactor, "CoilMaterialCorrectionFactor", "Coil Material Correction Factor"},
{ Refrigeration_AirChillerFields::RefrigerantCorrectionFactor, "RefrigerantCorrectionFactor", "Refrigerant Correction Factor"},
{ Refrigeration_AirChillerFields::CapacityCorrectionCurveType, "CapacityCorrectionCurveType", "Capacity Correction Curve Type"},
{ Refrigeration_AirChillerFields::CapacityCorrectionCurveName, "CapacityCorrectionCurveName", "Capacity Correction Curve Name"},
{ Refrigeration_AirChillerFields::SHR60CorrectionFactor, "SHR60CorrectionFactor", "SHR60 Correction Factor"},
{ Refrigeration_AirChillerFields::RatedTotalHeatingPower, "RatedTotalHeatingPower", "Rated Total Heating Power"},
{ Refrigeration_AirChillerFields::HeatingPowerScheduleName, "HeatingPowerScheduleName", "Heating Power Schedule Name"},
{ Refrigeration_AirChillerFields::FanSpeedControlType, "FanSpeedControlType", "Fan Speed Control Type"},
{ Refrigeration_AirChillerFields::RatedFanPower, "RatedFanPower", "Rated Fan Power"},
{ Refrigeration_AirChillerFields::RatedAirFlow, "RatedAirFlow", "Rated Air Flow"},
{ Refrigeration_AirChillerFields::MinimumFanAirFlowRatio, "MinimumFanAirFlowRatio", "Minimum Fan Air Flow Ratio"},
{ Refrigeration_AirChillerFields::DefrostType, "DefrostType", "Defrost Type"},
{ Refrigeration_AirChillerFields::DefrostControlType, "DefrostControlType", "Defrost Control Type"},
{ Refrigeration_AirChillerFields::DefrostScheduleName, "DefrostScheduleName", "Defrost Schedule Name"},
{ Refrigeration_AirChillerFields::DefrostDripDownScheduleName, "DefrostDripDownScheduleName", "Defrost Drip-Down Schedule Name"},
{ Refrigeration_AirChillerFields::DefrostPower, "DefrostPower", "Defrost Power"},
{ Refrigeration_AirChillerFields::TemperatureTerminationDefrostFractiontoIce, "TemperatureTerminationDefrostFractiontoIce", "Temperature Termination Defrost Fraction to Ice"},
{ Refrigeration_AirChillerFields::VerticalLocation, "VerticalLocation", "Vertical Location"},
{ Refrigeration_AirChillerFields::AverageRefrigerantChargeInventory, "AverageRefrigerantChargeInventory", "Average Refrigerant Charge Inventory"},
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
  inline std::ostream &operator<<(std::ostream &os, const Refrigeration_AirChillerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Refrigeration_AirChillerFields> OptionalRefrigeration_AirChillerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_REFRIGERATION_AIRCHILLER_FIELDENUMS_HXX
