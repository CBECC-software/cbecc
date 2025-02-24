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

#include "../../model/ScheduleTypeLimits.hpp"
#include <utilities/idd/OS_ScheduleTypeLimits_FieldEnums.hxx>

#include <utilities/idd/ScheduleTypeLimits_FieldEnums.hxx>
#include "../../utilities/idd/IddEnums.hpp"
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  boost::optional<IdfObject> ForwardTranslator::translateScheduleTypeLimits(ScheduleTypeLimits& modelObject) {
    IdfObject idfObject(openstudio::IddObjectType::ScheduleTypeLimits);
    m_idfObjects.push_back(idfObject);

    idfObject.setString(ScheduleTypeLimitsFields::Name, modelObject.name().get());

    OptionalDouble d = modelObject.getDouble(OS_ScheduleTypeLimitsFields::LowerLimitValue, false);
    if (d) {
      idfObject.setDouble(ScheduleTypeLimitsFields::LowerLimitValue, *d);
    }

    d = modelObject.getDouble(OS_ScheduleTypeLimitsFields::UpperLimitValue, false);
    if (d) {
      idfObject.setDouble(ScheduleTypeLimitsFields::UpperLimitValue, *d);
    }

    OptionalString s = modelObject.getString(OS_ScheduleTypeLimitsFields::NumericType, false, true);
    if (s) {
      idfObject.setString(ScheduleTypeLimitsFields::NumericType, *s);
    }

    s = modelObject.getString(OS_ScheduleTypeLimitsFields::UnitType, false, true);
    if (s) {
      std::string unitType = *s;
      boost::to_lower(unitType);
      if ((unitType == "clothinginsulation") || (unitType == "controlmode") || (unitType == "linearpowerdensity") || (unitType == "massflowrate")
          || (unitType == "pressure") || (unitType == "rotationsperminute") || (unitType == "solarenergy") || (unitType == "volumetricflowrate")) {
        // unit type key is unsupported in EnergyPlus--fall back on 'Any Number'
        m_idfObjects.pop_back();
        if (!m_anyNumberScheduleTypeLimits) {
          IdfObject anyNumberLimits(IddObjectType::ScheduleTypeLimits);
          m_idfObjects.push_back(anyNumberLimits);
          anyNumberLimits.setName("Any Number");
          m_anyNumberScheduleTypeLimits = anyNumberLimits;
        }
        return m_anyNumberScheduleTypeLimits;
      }
      idfObject.setString(ScheduleTypeLimitsFields::UnitType, unitType);
    }

    return boost::optional<IdfObject>(idfObject);
  }

}  // namespace energyplus

}  // namespace openstudio
