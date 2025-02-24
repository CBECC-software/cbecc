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

#include "../ForwardTranslator.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/ThermostatSetpointDualSetpoint.hpp"
#include <utilities/idd/ThermostatSetpoint_DualSetpoint_FieldEnums.hxx>
#include <utilities/idd/ThermostatSetpoint_SingleHeating_FieldEnums.hxx>
#include <utilities/idd/ThermostatSetpoint_SingleCooling_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

using namespace std;

namespace openstudio {

namespace energyplus {

  boost::optional<IdfObject> ForwardTranslator::translateThermostatSetpointDualSetpoint(ThermostatSetpointDualSetpoint& modelObject) {
    OptionalSchedule heat_sch = modelObject.getHeatingSchedule();
    OptionalSchedule cool_sch = modelObject.getCoolingSchedule();
    boost::optional<IdfObject> result;

    // Two schedules = DualSetpoint
    if (heat_sch.is_initialized() && cool_sch.is_initialized()) {
      IdfObject thermostat(openstudio::IddObjectType::ThermostatSetpoint_DualSetpoint);
      m_idfObjects.push_back(thermostat);

      // Name
      OptionalString s = modelObject.name();
      if (s) {
        thermostat.setName(*s);
      }

      // Heating Setpoint Temperature Schedule Name
      translateAndMapModelObject(*heat_sch);
      thermostat.setString(ThermostatSetpoint_DualSetpointFields::HeatingSetpointTemperatureScheduleName, heat_sch->name().get());

      // Cooling Setpoint Temperature Schedule Name
      translateAndMapModelObject(*cool_sch);
      thermostat.setString(ThermostatSetpoint_DualSetpointFields::CoolingSetpointTemperatureScheduleName, cool_sch->name().get());

      result = thermostat;

      // Heating only
    } else if (heat_sch.is_initialized() && !cool_sch.is_initialized()) {
      IdfObject thermostat(openstudio::IddObjectType::ThermostatSetpoint_SingleHeating);
      m_idfObjects.push_back(thermostat);

      // Name
      OptionalString s = modelObject.name();
      if (s) {
        thermostat.setName(*s);
      }

      // (Heating) Setpoint Temperature Schedule Name
      translateAndMapModelObject(*heat_sch);
      thermostat.setString(ThermostatSetpoint_SingleHeatingFields::SetpointTemperatureScheduleName, heat_sch->name().get());

      result = thermostat;

      // Cooling only
    } else if (!heat_sch.is_initialized() && cool_sch.is_initialized()) {
      IdfObject thermostat(openstudio::IddObjectType::ThermostatSetpoint_SingleCooling);
      m_idfObjects.push_back(thermostat);

      // Name
      OptionalString s = modelObject.name();
      if (s) {
        thermostat.setName(*s);
      }

      // (Cooling) Setpoint Temperature Schedule Name
      translateAndMapModelObject(*cool_sch);
      thermostat.setString(ThermostatSetpoint_SingleCoolingFields::SetpointTemperatureScheduleName, cool_sch->name().get());

      result = thermostat;
    }
    // No other cases, in ForwardTranslateThermalZone, we have checked that there is at least one schedule

    // Temperature Difference Between Cutout And Setpoint => Handle in ForwardTranslateThermalZone to place on ZoneControlThermostat object

    return result;
  }

}  // namespace energyplus

}  // namespace openstudio
