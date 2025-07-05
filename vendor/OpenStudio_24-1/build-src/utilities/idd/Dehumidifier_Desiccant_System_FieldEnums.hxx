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

#ifndef UTILITIES_IDD_DEHUMIDIFIER_DESICCANT_SYSTEM_FIELDENUMS_HXX
#define UTILITIES_IDD_DEHUMIDIFIER_DESICCANT_SYSTEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Dehumidifier_Desiccant_SystemFields
 *  \brief Enumeration of Dehumidifier:Desiccant:System's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Dehumidifier_Desiccant_SystemFields, )
#else
class Dehumidifier_Desiccant_SystemFields: public ::EnumBase<Dehumidifier_Desiccant_SystemFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, DesiccantHeatExchangerObjectType, DesiccantHeatExchangerName, SensorNodeName, RegenerationAirFanObjectType, RegenerationAirFanName, RegenerationAirFanPlacement, RegenerationAirHeaterObjectType, RegenerationAirHeaterName, RegenerationInletAirSetpointTemperature, CompanionCoolingCoilObjectType, CompanionCoolingCoilName, CompanionCoolingCoilUpstreamofDehumidifierProcessInlet, CompanionCoilRegenerationAirHeating, ExhaustFanMaximumFlowRate, ExhaustFanMaximumPower, ExhaustFanPowerCurveName,   };
  Dehumidifier_Desiccant_SystemFields()
   : EnumBase<Dehumidifier_Desiccant_SystemFields>(Name) {} 
  Dehumidifier_Desiccant_SystemFields(const std::string &t_name) 
   : EnumBase<Dehumidifier_Desiccant_SystemFields>(t_name) {} 
  Dehumidifier_Desiccant_SystemFields(int t_value) 
   : EnumBase<Dehumidifier_Desiccant_SystemFields>(t_value) {} 
  static std::string enumName() 
  { return "Dehumidifier_Desiccant_SystemFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Dehumidifier_Desiccant_SystemFields>::value()); }
   private:
    friend class EnumBase<Dehumidifier_Desiccant_SystemFields>;
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
{ Dehumidifier_Desiccant_SystemFields::Name, "Name", "Name"},
{ Dehumidifier_Desiccant_SystemFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Dehumidifier_Desiccant_SystemFields::DesiccantHeatExchangerObjectType, "DesiccantHeatExchangerObjectType", "Desiccant Heat Exchanger Object Type"},
{ Dehumidifier_Desiccant_SystemFields::DesiccantHeatExchangerName, "DesiccantHeatExchangerName", "Desiccant Heat Exchanger Name"},
{ Dehumidifier_Desiccant_SystemFields::SensorNodeName, "SensorNodeName", "Sensor Node Name"},
{ Dehumidifier_Desiccant_SystemFields::RegenerationAirFanObjectType, "RegenerationAirFanObjectType", "Regeneration Air Fan Object Type"},
{ Dehumidifier_Desiccant_SystemFields::RegenerationAirFanName, "RegenerationAirFanName", "Regeneration Air Fan Name"},
{ Dehumidifier_Desiccant_SystemFields::RegenerationAirFanPlacement, "RegenerationAirFanPlacement", "Regeneration Air Fan Placement"},
{ Dehumidifier_Desiccant_SystemFields::RegenerationAirHeaterObjectType, "RegenerationAirHeaterObjectType", "Regeneration Air Heater Object Type"},
{ Dehumidifier_Desiccant_SystemFields::RegenerationAirHeaterName, "RegenerationAirHeaterName", "Regeneration Air Heater Name"},
{ Dehumidifier_Desiccant_SystemFields::RegenerationInletAirSetpointTemperature, "RegenerationInletAirSetpointTemperature", "Regeneration Inlet Air Setpoint Temperature"},
{ Dehumidifier_Desiccant_SystemFields::CompanionCoolingCoilObjectType, "CompanionCoolingCoilObjectType", "Companion Cooling Coil Object Type"},
{ Dehumidifier_Desiccant_SystemFields::CompanionCoolingCoilName, "CompanionCoolingCoilName", "Companion Cooling Coil Name"},
{ Dehumidifier_Desiccant_SystemFields::CompanionCoolingCoilUpstreamofDehumidifierProcessInlet, "CompanionCoolingCoilUpstreamofDehumidifierProcessInlet", "Companion Cooling Coil Upstream of Dehumidifier Process Inlet"},
{ Dehumidifier_Desiccant_SystemFields::CompanionCoilRegenerationAirHeating, "CompanionCoilRegenerationAirHeating", "Companion Coil Regeneration Air Heating"},
{ Dehumidifier_Desiccant_SystemFields::ExhaustFanMaximumFlowRate, "ExhaustFanMaximumFlowRate", "Exhaust Fan Maximum Flow Rate"},
{ Dehumidifier_Desiccant_SystemFields::ExhaustFanMaximumPower, "ExhaustFanMaximumPower", "Exhaust Fan Maximum Power"},
{ Dehumidifier_Desiccant_SystemFields::ExhaustFanPowerCurveName, "ExhaustFanPowerCurveName", "Exhaust Fan Power Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Dehumidifier_Desiccant_SystemFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Dehumidifier_Desiccant_SystemFields> OptionalDehumidifier_Desiccant_SystemFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_DEHUMIDIFIER_DESICCANT_SYSTEM_FIELDENUMS_HXX
