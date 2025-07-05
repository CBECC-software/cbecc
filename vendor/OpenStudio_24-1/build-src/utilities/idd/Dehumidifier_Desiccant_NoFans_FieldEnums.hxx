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

#ifndef UTILITIES_IDD_DEHUMIDIFIER_DESICCANT_NOFANS_FIELDENUMS_HXX
#define UTILITIES_IDD_DEHUMIDIFIER_DESICCANT_NOFANS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Dehumidifier_Desiccant_NoFansFields
 *  \brief Enumeration of Dehumidifier:Desiccant:NoFans's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Dehumidifier_Desiccant_NoFansFields, )
#else
class Dehumidifier_Desiccant_NoFansFields: public ::EnumBase<Dehumidifier_Desiccant_NoFansFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, ProcessAirInletNodeName, ProcessAirOutletNodeName, RegenerationAirInletNodeName, RegenerationFanInletNodeName, ControlType, LeavingMaximumHumidityRatioSetpoint, NominalProcessAirFlowRate, NominalProcessAirVelocity, RotorPower, RegenerationCoilObjectType, RegenerationCoilName, RegenerationFanObjectType, RegenerationFanName, PerformanceModelType, LeavingDryBulbFunctionofEnteringDryBulbandHumidityRatioCurveName, LeavingDryBulbFunctionofAirVelocityCurveName, LeavingHumidityRatioFunctionofEnteringDryBulbandHumidityRatioCurveName, LeavingHumidityRatioFunctionofAirVelocityCurveName, RegenerationEnergyFunctionofEnteringDryBulbandHumidityRatioCurveName, RegenerationEnergyFunctionofAirVelocityCurveName, RegenerationVelocityFunctionofEnteringDryBulbandHumidityRatioCurveName, RegenerationVelocityFunctionofAirVelocityCurveName, NominalRegenerationTemperature,   };
  Dehumidifier_Desiccant_NoFansFields()
   : EnumBase<Dehumidifier_Desiccant_NoFansFields>(Name) {} 
  Dehumidifier_Desiccant_NoFansFields(const std::string &t_name) 
   : EnumBase<Dehumidifier_Desiccant_NoFansFields>(t_name) {} 
  Dehumidifier_Desiccant_NoFansFields(int t_value) 
   : EnumBase<Dehumidifier_Desiccant_NoFansFields>(t_value) {} 
  static std::string enumName() 
  { return "Dehumidifier_Desiccant_NoFansFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Dehumidifier_Desiccant_NoFansFields>::value()); }
   private:
    friend class EnumBase<Dehumidifier_Desiccant_NoFansFields>;
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
{ Dehumidifier_Desiccant_NoFansFields::Name, "Name", "Name"},
{ Dehumidifier_Desiccant_NoFansFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Dehumidifier_Desiccant_NoFansFields::ProcessAirInletNodeName, "ProcessAirInletNodeName", "Process Air Inlet Node Name"},
{ Dehumidifier_Desiccant_NoFansFields::ProcessAirOutletNodeName, "ProcessAirOutletNodeName", "Process Air Outlet Node Name"},
{ Dehumidifier_Desiccant_NoFansFields::RegenerationAirInletNodeName, "RegenerationAirInletNodeName", "Regeneration Air Inlet Node Name"},
{ Dehumidifier_Desiccant_NoFansFields::RegenerationFanInletNodeName, "RegenerationFanInletNodeName", "Regeneration Fan Inlet Node Name"},
{ Dehumidifier_Desiccant_NoFansFields::ControlType, "ControlType", "Control Type"},
{ Dehumidifier_Desiccant_NoFansFields::LeavingMaximumHumidityRatioSetpoint, "LeavingMaximumHumidityRatioSetpoint", "Leaving Maximum Humidity Ratio Setpoint"},
{ Dehumidifier_Desiccant_NoFansFields::NominalProcessAirFlowRate, "NominalProcessAirFlowRate", "Nominal Process Air Flow Rate"},
{ Dehumidifier_Desiccant_NoFansFields::NominalProcessAirVelocity, "NominalProcessAirVelocity", "Nominal Process Air Velocity"},
{ Dehumidifier_Desiccant_NoFansFields::RotorPower, "RotorPower", "Rotor Power"},
{ Dehumidifier_Desiccant_NoFansFields::RegenerationCoilObjectType, "RegenerationCoilObjectType", "Regeneration Coil Object Type"},
{ Dehumidifier_Desiccant_NoFansFields::RegenerationCoilName, "RegenerationCoilName", "Regeneration Coil Name"},
{ Dehumidifier_Desiccant_NoFansFields::RegenerationFanObjectType, "RegenerationFanObjectType", "Regeneration Fan Object Type"},
{ Dehumidifier_Desiccant_NoFansFields::RegenerationFanName, "RegenerationFanName", "Regeneration Fan Name"},
{ Dehumidifier_Desiccant_NoFansFields::PerformanceModelType, "PerformanceModelType", "Performance Model Type"},
{ Dehumidifier_Desiccant_NoFansFields::LeavingDryBulbFunctionofEnteringDryBulbandHumidityRatioCurveName, "LeavingDryBulbFunctionofEnteringDryBulbandHumidityRatioCurveName", "Leaving Dry-Bulb Function of Entering Dry-Bulb and Humidity Ratio Curve Name"},
{ Dehumidifier_Desiccant_NoFansFields::LeavingDryBulbFunctionofAirVelocityCurveName, "LeavingDryBulbFunctionofAirVelocityCurveName", "Leaving Dry-Bulb Function of Air Velocity Curve Name"},
{ Dehumidifier_Desiccant_NoFansFields::LeavingHumidityRatioFunctionofEnteringDryBulbandHumidityRatioCurveName, "LeavingHumidityRatioFunctionofEnteringDryBulbandHumidityRatioCurveName", "Leaving Humidity Ratio Function of Entering Dry-Bulb and Humidity Ratio Curve Name"},
{ Dehumidifier_Desiccant_NoFansFields::LeavingHumidityRatioFunctionofAirVelocityCurveName, "LeavingHumidityRatioFunctionofAirVelocityCurveName", "Leaving Humidity Ratio Function of Air Velocity Curve Name"},
{ Dehumidifier_Desiccant_NoFansFields::RegenerationEnergyFunctionofEnteringDryBulbandHumidityRatioCurveName, "RegenerationEnergyFunctionofEnteringDryBulbandHumidityRatioCurveName", "Regeneration Energy Function of Entering Dry-Bulb and Humidity Ratio Curve Name"},
{ Dehumidifier_Desiccant_NoFansFields::RegenerationEnergyFunctionofAirVelocityCurveName, "RegenerationEnergyFunctionofAirVelocityCurveName", "Regeneration Energy Function of Air Velocity Curve Name"},
{ Dehumidifier_Desiccant_NoFansFields::RegenerationVelocityFunctionofEnteringDryBulbandHumidityRatioCurveName, "RegenerationVelocityFunctionofEnteringDryBulbandHumidityRatioCurveName", "Regeneration Velocity Function of Entering Dry-Bulb and Humidity Ratio Curve Name"},
{ Dehumidifier_Desiccant_NoFansFields::RegenerationVelocityFunctionofAirVelocityCurveName, "RegenerationVelocityFunctionofAirVelocityCurveName", "Regeneration Velocity Function of Air Velocity Curve Name"},
{ Dehumidifier_Desiccant_NoFansFields::NominalRegenerationTemperature, "NominalRegenerationTemperature", "Nominal Regeneration Temperature"},
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
  inline std::ostream &operator<<(std::ostream &os, const Dehumidifier_Desiccant_NoFansFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Dehumidifier_Desiccant_NoFansFields> OptionalDehumidifier_Desiccant_NoFansFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_DEHUMIDIFIER_DESICCANT_NOFANS_FIELDENUMS_HXX
