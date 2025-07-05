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

#ifndef UTILITIES_IDD_ZONEHVAC_LOWTEMPERATURERADIANT_VARIABLEFLOW_DESIGN_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_LOWTEMPERATURERADIANT_VARIABLEFLOW_DESIGN_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields
 *  \brief Enumeration of ZoneHVAC:LowTemperatureRadiant:VariableFlow:Design's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields, )
#else
class ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields: public ::EnumBase<ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields> {
 public: 
  enum domain 
  {
Name, FluidtoRadiantSurfaceHeatTransferModel, HydronicTubingInsideDiameter, HydronicTubingOutsideDiameter, HydronicTubingConductivity, TemperatureControlType, SetpointControlType, HeatingDesignCapacityMethod, HeatingDesignCapacityPerFloorArea, FractionofAutosizedHeatingDesignCapacity, HeatingControlThrottlingRange, HeatingControlTemperatureScheduleName, CoolingDesignCapacityMethod, CoolingDesignCapacityPerFloorArea, FractionofAutosizedCoolingDesignCapacity, CoolingControlThrottlingRange, CoolingControlTemperatureScheduleName, CondensationControlType, CondensationControlDewpointOffset, ChangeoverDelayTimePeriodSchedule,   };
  ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields()
   : EnumBase<ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields>(Name) {} 
  ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields>(t_name) {} 
  ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields(int t_value) 
   : EnumBase<ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields>;
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
{ ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::Name, "Name", "Name"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel, "FluidtoRadiantSurfaceHeatTransferModel", "Fluid to Radiant Surface Heat Transfer Model"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HydronicTubingInsideDiameter, "HydronicTubingInsideDiameter", "Hydronic Tubing Inside Diameter"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HydronicTubingOutsideDiameter, "HydronicTubingOutsideDiameter", "Hydronic Tubing Outside Diameter"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HydronicTubingConductivity, "HydronicTubingConductivity", "Hydronic Tubing Conductivity"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::TemperatureControlType, "TemperatureControlType", "Temperature Control Type"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::SetpointControlType, "SetpointControlType", "Setpoint Control Type"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingDesignCapacityMethod, "HeatingDesignCapacityMethod", "Heating Design Capacity Method"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingDesignCapacityPerFloorArea, "HeatingDesignCapacityPerFloorArea", "Heating Design Capacity Per Floor Area"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::FractionofAutosizedHeatingDesignCapacity, "FractionofAutosizedHeatingDesignCapacity", "Fraction of Autosized Heating Design Capacity"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingControlThrottlingRange, "HeatingControlThrottlingRange", "Heating Control Throttling Range"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingControlTemperatureScheduleName, "HeatingControlTemperatureScheduleName", "Heating Control Temperature Schedule Name"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingDesignCapacityMethod, "CoolingDesignCapacityMethod", "Cooling Design Capacity Method"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingDesignCapacityPerFloorArea, "CoolingDesignCapacityPerFloorArea", "Cooling Design Capacity Per Floor Area"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::FractionofAutosizedCoolingDesignCapacity, "FractionofAutosizedCoolingDesignCapacity", "Fraction of Autosized Cooling Design Capacity"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingControlThrottlingRange, "CoolingControlThrottlingRange", "Cooling Control Throttling Range"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingControlTemperatureScheduleName, "CoolingControlTemperatureScheduleName", "Cooling Control Temperature Schedule Name"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CondensationControlType, "CondensationControlType", "Condensation Control Type"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CondensationControlDewpointOffset, "CondensationControlDewpointOffset", "Condensation Control Dewpoint Offset"},
{ ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::ChangeoverDelayTimePeriodSchedule, "ChangeoverDelayTimePeriodSchedule", "Changeover Delay Time Period Schedule"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields> OptionalZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_LOWTEMPERATURERADIANT_VARIABLEFLOW_DESIGN_FIELDENUMS_HXX
