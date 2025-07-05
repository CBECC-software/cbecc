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

#ifndef UTILITIES_IDD_ZONECONTROL_THERMOSTAT_STAGEDDUALSETPOINT_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONECONTROL_THERMOSTAT_STAGEDDUALSETPOINT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneControl_Thermostat_StagedDualSetpointFields
 *  \brief Enumeration of ZoneControl:Thermostat:StagedDualSetpoint's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneControl_Thermostat_StagedDualSetpointFields, )
#else
class ZoneControl_Thermostat_StagedDualSetpointFields: public ::EnumBase<ZoneControl_Thermostat_StagedDualSetpointFields> {
 public: 
  enum domain 
  {
Name, ZoneorZoneListName, NumberofHeatingStages, HeatingTemperatureSetpointScheduleName, HeatingThrottlingTemperatureRange, Stage1HeatingTemperatureOffset, Stage2HeatingTemperatureOffset, Stage3HeatingTemperatureOffset, Stage4HeatingTemperatureOffset, NumberofCoolingStages, CoolingTemperatureSetpointBaseScheduleName, CoolingThrottlingTemperatureRange, Stage1CoolingTemperatureOffset, Stage2CoolingTemperatureOffset, Stage3CoolingTemperatureOffset, Stage4CoolingTemperatureOffset,   };
  ZoneControl_Thermostat_StagedDualSetpointFields()
   : EnumBase<ZoneControl_Thermostat_StagedDualSetpointFields>(Name) {} 
  ZoneControl_Thermostat_StagedDualSetpointFields(const std::string &t_name) 
   : EnumBase<ZoneControl_Thermostat_StagedDualSetpointFields>(t_name) {} 
  ZoneControl_Thermostat_StagedDualSetpointFields(int t_value) 
   : EnumBase<ZoneControl_Thermostat_StagedDualSetpointFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneControl_Thermostat_StagedDualSetpointFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneControl_Thermostat_StagedDualSetpointFields>::value()); }
   private:
    friend class EnumBase<ZoneControl_Thermostat_StagedDualSetpointFields>;
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
{ ZoneControl_Thermostat_StagedDualSetpointFields::Name, "Name", "Name"},
{ ZoneControl_Thermostat_StagedDualSetpointFields::ZoneorZoneListName, "ZoneorZoneListName", "Zone or ZoneList Name"},
{ ZoneControl_Thermostat_StagedDualSetpointFields::NumberofHeatingStages, "NumberofHeatingStages", "Number of Heating Stages"},
{ ZoneControl_Thermostat_StagedDualSetpointFields::HeatingTemperatureSetpointScheduleName, "HeatingTemperatureSetpointScheduleName", "Heating Temperature Setpoint Schedule Name"},
{ ZoneControl_Thermostat_StagedDualSetpointFields::HeatingThrottlingTemperatureRange, "HeatingThrottlingTemperatureRange", "Heating Throttling Temperature Range"},
{ ZoneControl_Thermostat_StagedDualSetpointFields::Stage1HeatingTemperatureOffset, "Stage1HeatingTemperatureOffset", "Stage 1 Heating Temperature Offset"},
{ ZoneControl_Thermostat_StagedDualSetpointFields::Stage2HeatingTemperatureOffset, "Stage2HeatingTemperatureOffset", "Stage 2 Heating Temperature Offset"},
{ ZoneControl_Thermostat_StagedDualSetpointFields::Stage3HeatingTemperatureOffset, "Stage3HeatingTemperatureOffset", "Stage 3 Heating Temperature Offset"},
{ ZoneControl_Thermostat_StagedDualSetpointFields::Stage4HeatingTemperatureOffset, "Stage4HeatingTemperatureOffset", "Stage 4 Heating Temperature Offset"},
{ ZoneControl_Thermostat_StagedDualSetpointFields::NumberofCoolingStages, "NumberofCoolingStages", "Number of Cooling Stages"},
{ ZoneControl_Thermostat_StagedDualSetpointFields::CoolingTemperatureSetpointBaseScheduleName, "CoolingTemperatureSetpointBaseScheduleName", "Cooling Temperature Setpoint Base Schedule Name"},
{ ZoneControl_Thermostat_StagedDualSetpointFields::CoolingThrottlingTemperatureRange, "CoolingThrottlingTemperatureRange", "Cooling Throttling Temperature Range"},
{ ZoneControl_Thermostat_StagedDualSetpointFields::Stage1CoolingTemperatureOffset, "Stage1CoolingTemperatureOffset", "Stage 1 Cooling Temperature Offset"},
{ ZoneControl_Thermostat_StagedDualSetpointFields::Stage2CoolingTemperatureOffset, "Stage2CoolingTemperatureOffset", "Stage 2 Cooling Temperature Offset"},
{ ZoneControl_Thermostat_StagedDualSetpointFields::Stage3CoolingTemperatureOffset, "Stage3CoolingTemperatureOffset", "Stage 3 Cooling Temperature Offset"},
{ ZoneControl_Thermostat_StagedDualSetpointFields::Stage4CoolingTemperatureOffset, "Stage4CoolingTemperatureOffset", "Stage 4 Cooling Temperature Offset"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneControl_Thermostat_StagedDualSetpointFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneControl_Thermostat_StagedDualSetpointFields> OptionalZoneControl_Thermostat_StagedDualSetpointFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONECONTROL_THERMOSTAT_STAGEDDUALSETPOINT_FIELDENUMS_HXX
