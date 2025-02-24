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
#include "../../model/Model.hpp"
#include "../../model/RefrigerationCondenserCascade.hpp"

#include <utilities/idd/Refrigeration_Condenser_Cascade_FieldEnums.hxx>
#include "../../utilities/idd/IddEnums.hpp"
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  boost::optional<IdfObject> ForwardTranslator::translateRefrigerationCondenserCascade(RefrigerationCondenserCascade& modelObject) {
    OptionalModelObject temp;
    OptionalString optS;
    boost::optional<std::string> s;
    boost::optional<double> d;

    // Name
    IdfObject cascade = createRegisterAndNameIdfObject(openstudio::IddObjectType::Refrigeration_Condenser_Cascade, modelObject);

    // Rated Condensing Temperature
    d = modelObject.ratedCondensingTemperature();
    if (d) {
      cascade.setDouble(Refrigeration_Condenser_CascadeFields::RatedCondensingTemperature, d.get());
    }

    // Rated Approach Temperature Difference
    d = modelObject.ratedApproachTemperatureDifference();
    if (d) {
      cascade.setDouble(Refrigeration_Condenser_CascadeFields::RatedApproachTemperatureDifference, d.get());
    }

    // Rated Effective Total Heat Rejection Rate
    d = modelObject.ratedEffectiveTotalHeatRejectionRate();
    if (d) {
      cascade.setDouble(Refrigeration_Condenser_CascadeFields::RatedEffectiveTotalHeatRejectionRate, d.get());
    }

    // Condensing Temperature Control Type
    s = modelObject.condensingTemperatureControlType();
    if (s) {
      cascade.setString(Refrigeration_Condenser_CascadeFields::CondensingTemperatureControlType, s.get());
    }

    // Condenser Refrigerant Operating Charge Inventory
    d = modelObject.condenserRefrigerantOperatingChargeInventory();
    if (d) {
      cascade.setDouble(Refrigeration_Condenser_CascadeFields::CondenserRefrigerantOperatingChargeInventory, d.get());
    }

    // Condensate Receiver Refrigerant Inventory
    d = modelObject.condensateReceiverRefrigerantInventory();
    if (d) {
      cascade.setDouble(Refrigeration_Condenser_CascadeFields::CondensateReceiverRefrigerantInventory, d.get());
    }

    // Condensate Piping Refrigerant Inventory
    d = modelObject.condensatePipingRefrigerantInventory();
    if (d) {
      cascade.setDouble(Refrigeration_Condenser_CascadeFields::CondensatePipingRefrigerantInventory, d.get());
    }

    return cascade;
  }
}  // namespace energyplus
}  // namespace openstudio
