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

#ifndef UTILITIES_IDD_OS_COIL_HEATING_DX_MULTISPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_HEATING_DX_MULTISPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_Heating_DX_MultiSpeedFields
 *  \brief Enumeration of OS:Coil:Heating:DX:MultiSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_Heating_DX_MultiSpeedFields, )
#else
class OS_Coil_Heating_DX_MultiSpeedFields: public ::EnumBase<OS_Coil_Heating_DX_MultiSpeedFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, MinimumOutdoorDryBulbTemperatureforCompressorOperation, OutdoorDryBulbTemperaturetoTurnOnCompressor, CrankcaseHeaterCapacity, MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, DefrostEnergyInputRatioFunctionofTemperatureCurveName, MaximumOutdoorDryBulbTemperatureforDefrostOperation, DefrostStrategy, DefrostControl, DefrostTimePeriodFraction, ResistiveDefrostHeaterCapacity, ApplyPartLoadFractiontoSpeedsGreaterthan1, FuelType, RegionnumberforCalculatingHSPF, StageDataList,   };
  OS_Coil_Heating_DX_MultiSpeedFields()
   : EnumBase<OS_Coil_Heating_DX_MultiSpeedFields>(Handle) {} 
  OS_Coil_Heating_DX_MultiSpeedFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Heating_DX_MultiSpeedFields>(t_name) {} 
  OS_Coil_Heating_DX_MultiSpeedFields(int t_value) 
   : EnumBase<OS_Coil_Heating_DX_MultiSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Heating_DX_MultiSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Heating_DX_MultiSpeedFields>::value()); }
   private:
    friend class EnumBase<OS_Coil_Heating_DX_MultiSpeedFields>;
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
{ OS_Coil_Heating_DX_MultiSpeedFields::Handle, "Handle", "Handle"},
{ OS_Coil_Heating_DX_MultiSpeedFields::Name, "Name", "Name"},
{ OS_Coil_Heating_DX_MultiSpeedFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_Coil_Heating_DX_MultiSpeedFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_Coil_Heating_DX_MultiSpeedFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_Coil_Heating_DX_MultiSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, "MinimumOutdoorDryBulbTemperatureforCompressorOperation", "Minimum Outdoor Dry-Bulb Temperature for Compressor Operation"},
{ OS_Coil_Heating_DX_MultiSpeedFields::OutdoorDryBulbTemperaturetoTurnOnCompressor, "OutdoorDryBulbTemperaturetoTurnOnCompressor", "Outdoor Dry-Bulb Temperature to Turn On Compressor"},
{ OS_Coil_Heating_DX_MultiSpeedFields::CrankcaseHeaterCapacity, "CrankcaseHeaterCapacity", "Crankcase Heater Capacity"},
{ OS_Coil_Heating_DX_MultiSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, "MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Crankcase Heater Operation"},
{ OS_Coil_Heating_DX_MultiSpeedFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName, "DefrostEnergyInputRatioFunctionofTemperatureCurveName", "Defrost Energy Input Ratio Function of Temperature Curve Name"},
{ OS_Coil_Heating_DX_MultiSpeedFields::MaximumOutdoorDryBulbTemperatureforDefrostOperation, "MaximumOutdoorDryBulbTemperatureforDefrostOperation", "Maximum Outdoor Dry-Bulb Temperature for Defrost Operation"},
{ OS_Coil_Heating_DX_MultiSpeedFields::DefrostStrategy, "DefrostStrategy", "Defrost Strategy"},
{ OS_Coil_Heating_DX_MultiSpeedFields::DefrostControl, "DefrostControl", "Defrost Control"},
{ OS_Coil_Heating_DX_MultiSpeedFields::DefrostTimePeriodFraction, "DefrostTimePeriodFraction", "Defrost Time Period Fraction"},
{ OS_Coil_Heating_DX_MultiSpeedFields::ResistiveDefrostHeaterCapacity, "ResistiveDefrostHeaterCapacity", "Resistive Defrost Heater Capacity"},
{ OS_Coil_Heating_DX_MultiSpeedFields::ApplyPartLoadFractiontoSpeedsGreaterthan1, "ApplyPartLoadFractiontoSpeedsGreaterthan1", "Apply Part Load Fraction to Speeds Greater than 1"},
{ OS_Coil_Heating_DX_MultiSpeedFields::FuelType, "FuelType", "Fuel Type"},
{ OS_Coil_Heating_DX_MultiSpeedFields::RegionnumberforCalculatingHSPF, "RegionnumberforCalculatingHSPF", "Region number for Calculating HSPF"},
{ OS_Coil_Heating_DX_MultiSpeedFields::StageDataList, "StageDataList", "Stage Data List"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Heating_DX_MultiSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Heating_DX_MultiSpeedFields> OptionalOS_Coil_Heating_DX_MultiSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_HEATING_DX_MULTISPEED_FIELDENUMS_HXX
