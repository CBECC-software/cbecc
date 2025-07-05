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

#ifndef UTILITIES_IDD_PUMP_CONSTANTSPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_PUMP_CONSTANTSPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Pump_ConstantSpeedFields
 *  \brief Enumeration of Pump:ConstantSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Pump_ConstantSpeedFields, )
#else
class Pump_ConstantSpeedFields: public ::EnumBase<Pump_ConstantSpeedFields> {
 public: 
  enum domain 
  {
Name, InletNodeName, OutletNodeName, DesignFlowRate, DesignPumpHead, DesignPowerConsumption, MotorEfficiency, FractionofMotorInefficienciestoFluidStream, PumpControlType, PumpFlowRateScheduleName, PumpCurveName, ImpellerDiameter, RotationalSpeed, ZoneName, SkinLossRadiativeFraction, DesignPowerSizingMethod, DesignElectricPowerperUnitFlowRate, DesignShaftPowerperUnitFlowRateperUnitHead, EndUseSubcategory,   };
  Pump_ConstantSpeedFields()
   : EnumBase<Pump_ConstantSpeedFields>(Name) {} 
  Pump_ConstantSpeedFields(const std::string &t_name) 
   : EnumBase<Pump_ConstantSpeedFields>(t_name) {} 
  Pump_ConstantSpeedFields(int t_value) 
   : EnumBase<Pump_ConstantSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "Pump_ConstantSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Pump_ConstantSpeedFields>::value()); }
   private:
    friend class EnumBase<Pump_ConstantSpeedFields>;
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
{ Pump_ConstantSpeedFields::Name, "Name", "Name"},
{ Pump_ConstantSpeedFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ Pump_ConstantSpeedFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ Pump_ConstantSpeedFields::DesignFlowRate, "DesignFlowRate", "Design Flow Rate"},
{ Pump_ConstantSpeedFields::DesignPumpHead, "DesignPumpHead", "Design Pump Head"},
{ Pump_ConstantSpeedFields::DesignPowerConsumption, "DesignPowerConsumption", "Design Power Consumption"},
{ Pump_ConstantSpeedFields::MotorEfficiency, "MotorEfficiency", "Motor Efficiency"},
{ Pump_ConstantSpeedFields::FractionofMotorInefficienciestoFluidStream, "FractionofMotorInefficienciestoFluidStream", "Fraction of Motor Inefficiencies to Fluid Stream"},
{ Pump_ConstantSpeedFields::PumpControlType, "PumpControlType", "Pump Control Type"},
{ Pump_ConstantSpeedFields::PumpFlowRateScheduleName, "PumpFlowRateScheduleName", "Pump Flow Rate Schedule Name"},
{ Pump_ConstantSpeedFields::PumpCurveName, "PumpCurveName", "Pump Curve Name"},
{ Pump_ConstantSpeedFields::ImpellerDiameter, "ImpellerDiameter", "Impeller Diameter"},
{ Pump_ConstantSpeedFields::RotationalSpeed, "RotationalSpeed", "Rotational Speed"},
{ Pump_ConstantSpeedFields::ZoneName, "ZoneName", "Zone Name"},
{ Pump_ConstantSpeedFields::SkinLossRadiativeFraction, "SkinLossRadiativeFraction", "Skin Loss Radiative Fraction"},
{ Pump_ConstantSpeedFields::DesignPowerSizingMethod, "DesignPowerSizingMethod", "Design Power Sizing Method"},
{ Pump_ConstantSpeedFields::DesignElectricPowerperUnitFlowRate, "DesignElectricPowerperUnitFlowRate", "Design Electric Power per Unit Flow Rate"},
{ Pump_ConstantSpeedFields::DesignShaftPowerperUnitFlowRateperUnitHead, "DesignShaftPowerperUnitFlowRateperUnitHead", "Design Shaft Power per Unit Flow Rate per Unit Head"},
{ Pump_ConstantSpeedFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const Pump_ConstantSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Pump_ConstantSpeedFields> OptionalPump_ConstantSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PUMP_CONSTANTSPEED_FIELDENUMS_HXX
