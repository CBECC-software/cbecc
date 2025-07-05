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

#ifndef UTILITIES_IDD_COIL_COOLING_DX_TWOSTAGEWITHHUMIDITYCONTROLMODE_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_COOLING_DX_TWOSTAGEWITHHUMIDITYCONTROLMODE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Cooling_DX_TwoStageWithHumidityControlModeFields
 *  \brief Enumeration of Coil:Cooling:DX:TwoStageWithHumidityControlMode's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Cooling_DX_TwoStageWithHumidityControlModeFields, )
#else
class Coil_Cooling_DX_TwoStageWithHumidityControlModeFields: public ::EnumBase<Coil_Cooling_DX_TwoStageWithHumidityControlModeFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, CrankcaseHeaterCapacity, MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, NumberofCapacityStages, NumberofEnhancedDehumidificationModes, NormalModeStage1CoilPerformanceObjectType, NormalModeStage1CoilPerformanceName, NormalModeStage1_PLUS_2CoilPerformanceObjectType, NormalModeStage1_PLUS_2CoilPerformanceName, DehumidificationMode1Stage1CoilPerformanceObjectType, DehumidificationMode1Stage1CoilPerformanceName, DehumidificationMode1Stage1_PLUS_2CoilPerformanceObjectType, DehumidificationMode1Stage1_PLUS_2CoilPerformanceName, SupplyWaterStorageTankName, CondensateCollectionWaterStorageTankName, MinimumOutdoorDryBulbTemperatureforCompressorOperation, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName,   };
  Coil_Cooling_DX_TwoStageWithHumidityControlModeFields()
   : EnumBase<Coil_Cooling_DX_TwoStageWithHumidityControlModeFields>(Name) {} 
  Coil_Cooling_DX_TwoStageWithHumidityControlModeFields(const std::string &t_name) 
   : EnumBase<Coil_Cooling_DX_TwoStageWithHumidityControlModeFields>(t_name) {} 
  Coil_Cooling_DX_TwoStageWithHumidityControlModeFields(int t_value) 
   : EnumBase<Coil_Cooling_DX_TwoStageWithHumidityControlModeFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Cooling_DX_TwoStageWithHumidityControlModeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Cooling_DX_TwoStageWithHumidityControlModeFields>::value()); }
   private:
    friend class EnumBase<Coil_Cooling_DX_TwoStageWithHumidityControlModeFields>;
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
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::Name, "Name", "Name"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::CrankcaseHeaterCapacity, "CrankcaseHeaterCapacity", "Crankcase Heater Capacity"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, "MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Crankcase Heater Operation"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NumberofCapacityStages, "NumberofCapacityStages", "Number of Capacity Stages"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NumberofEnhancedDehumidificationModes, "NumberofEnhancedDehumidificationModes", "Number of Enhanced Dehumidification Modes"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NormalModeStage1CoilPerformanceObjectType, "NormalModeStage1CoilPerformanceObjectType", "Normal Mode Stage 1 Coil Performance Object Type"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NormalModeStage1CoilPerformanceName, "NormalModeStage1CoilPerformanceName", "Normal Mode Stage 1 Coil Performance Name"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NormalModeStage1_PLUS_2CoilPerformanceObjectType, "NormalModeStage1_PLUS_2CoilPerformanceObjectType", "Normal Mode Stage 1+2 Coil Performance Object Type"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::NormalModeStage1_PLUS_2CoilPerformanceName, "NormalModeStage1_PLUS_2CoilPerformanceName", "Normal Mode Stage 1+2 Coil Performance Name"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::DehumidificationMode1Stage1CoilPerformanceObjectType, "DehumidificationMode1Stage1CoilPerformanceObjectType", "Dehumidification Mode 1 Stage 1 Coil Performance Object Type"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::DehumidificationMode1Stage1CoilPerformanceName, "DehumidificationMode1Stage1CoilPerformanceName", "Dehumidification Mode 1 Stage 1 Coil Performance Name"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::DehumidificationMode1Stage1_PLUS_2CoilPerformanceObjectType, "DehumidificationMode1Stage1_PLUS_2CoilPerformanceObjectType", "Dehumidification Mode 1 Stage 1+2 Coil Performance Object Type"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::DehumidificationMode1Stage1_PLUS_2CoilPerformanceName, "DehumidificationMode1Stage1_PLUS_2CoilPerformanceName", "Dehumidification Mode 1 Stage 1+2 Coil Performance Name"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::SupplyWaterStorageTankName, "SupplyWaterStorageTankName", "Supply Water Storage Tank Name"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::CondensateCollectionWaterStorageTankName, "CondensateCollectionWaterStorageTankName", "Condensate Collection Water Storage Tank Name"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, "MinimumOutdoorDryBulbTemperatureforCompressorOperation", "Minimum Outdoor Dry-Bulb Temperature for Compressor Operation"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ Coil_Cooling_DX_TwoStageWithHumidityControlModeFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Cooling_DX_TwoStageWithHumidityControlModeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Cooling_DX_TwoStageWithHumidityControlModeFields> OptionalCoil_Cooling_DX_TwoStageWithHumidityControlModeFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_COOLING_DX_TWOSTAGEWITHHUMIDITYCONTROLMODE_FIELDENUMS_HXX
