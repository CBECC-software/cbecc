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

#include "../ReverseTranslator.hpp"

#include "../../model/CurveRectangularHyperbola2.hpp"
#include "../../model/CurveRectangularHyperbola2_Impl.hpp"

#include <utilities/idd/Curve_RectangularHyperbola2_FieldEnums.hxx>

using namespace openstudio::model;

namespace openstudio {
namespace energyplus {

boost::optional<ModelObject> ReverseTranslator::translateCurveRectangularHyperbola2( 
    const WorkspaceObject& workspaceObject )
{
  CurveRectangularHyperbola2 curve(m_model);

  OptionalString s;
  OptionalDouble d;
  
  if ((s = workspaceObject.name())) {
    curve.setName(*s);
  }

  if ((d = workspaceObject.getDouble(Curve_RectangularHyperbola2Fields::Coefficient1C1))) {
    curve.setCoefficient1C1(*d);
  }
  if ((d = workspaceObject.getDouble(Curve_RectangularHyperbola2Fields::Coefficient2C2))) {
    curve.setCoefficient2C2(*d);
  }
  if ((d = workspaceObject.getDouble(Curve_RectangularHyperbola2Fields::Coefficient3C3))) {
    curve.setCoefficient3C3(*d);
  }
  if ((d = workspaceObject.getDouble(Curve_RectangularHyperbola2Fields::MinimumValueofx))) {
    curve.setMinimumValueofx(*d);
  }
  if ((d = workspaceObject.getDouble(Curve_RectangularHyperbola2Fields::MaximumValueofx))) {
    curve.setMaximumValueofx(*d);
  }
  if ((d = workspaceObject.getDouble(Curve_RectangularHyperbola2Fields::MinimumCurveOutput))) {
    curve.setMinimumCurveOutput(*d);
  }
  if ((d = workspaceObject.getDouble(Curve_RectangularHyperbola2Fields::MaximumCurveOutput))) {
    curve.setMaximumCurveOutput(*d);
  }
  if ((s = workspaceObject.getString(Curve_RectangularHyperbola2Fields::InputUnitTypeforx,false,true))) {
    curve.setInputUnitTypeforx(*s);
  }
  if ((s = workspaceObject.getString(Curve_RectangularHyperbola2Fields::OutputUnitType,false,true))) {
    curve.setOutputUnitType(*s);
  }

  return curve;
}

} // energyplus
} // openstudio

