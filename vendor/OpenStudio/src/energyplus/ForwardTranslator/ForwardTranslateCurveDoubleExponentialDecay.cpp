/**********************************************************************
 *  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#include "../ForwardTranslator.hpp"

#include "../../model/CurveDoubleExponentialDecay.hpp"
#include "../../model/CurveDoubleExponentialDecay_Impl.hpp"

#include "../../utilities/core/Assert.hpp"

#include <utilities/idd/Curve_DoubleExponentialDecay_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;
using namespace std;

namespace openstudio {
namespace energyplus {

boost::optional<IdfObject> ForwardTranslator::translateCurveDoubleExponentialDecay( 
    CurveDoubleExponentialDecay& modelObject)
{
  IdfObject idfObject(IddObjectType::Curve_DoubleExponentialDecay);

  m_idfObjects.push_back(idfObject);

  OptionalString s;
  OptionalDouble d;

  if ((s = modelObject.name())) {
    idfObject.setName(*s);
  }

  idfObject.setDouble(Curve_DoubleExponentialDecayFields::Coefficient1C1,modelObject.coefficient1C1());
  idfObject.setDouble(Curve_DoubleExponentialDecayFields::Coefficient2C2,modelObject.coefficient2C2());
  idfObject.setDouble(Curve_DoubleExponentialDecayFields::Coefficient3C3,modelObject.coefficient3C3());
  idfObject.setDouble(Curve_DoubleExponentialDecayFields::Coefficient3C4,modelObject.coefficient3C4());
  idfObject.setDouble(Curve_DoubleExponentialDecayFields::Coefficient3C5,modelObject.coefficient3C5());
  idfObject.setDouble(Curve_DoubleExponentialDecayFields::MinimumValueofx,modelObject.minimumValueofx());
  idfObject.setDouble(Curve_DoubleExponentialDecayFields::MaximumValueofx,modelObject.maximumValueofx());
  if ((d = modelObject.minimumCurveOutput())) {
    idfObject.setDouble(Curve_DoubleExponentialDecayFields::MinimumCurveOutput,*d);
  }
  if ((d = modelObject.maximumCurveOutput())) {
    idfObject.setDouble(Curve_DoubleExponentialDecayFields::MaximumCurveOutput,*d);
  }
  if (!modelObject.isInputUnitTypeforxDefaulted()) {
    idfObject.setString(Curve_DoubleExponentialDecayFields::InputUnitTypeforx,modelObject.inputUnitTypeforx());
  }
  if (!modelObject.isOutputUnitTypeDefaulted()) {
    idfObject.setString(Curve_DoubleExponentialDecayFields::OutputUnitType,modelObject.outputUnitType());
  }

  return idfObject;
}

} // energyplus
} // openstudio
