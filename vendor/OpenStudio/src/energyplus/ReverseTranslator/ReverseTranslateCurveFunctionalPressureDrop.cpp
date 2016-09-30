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

#include "../../model/CurveFunctionalPressureDrop.hpp"
#include "../../model/CurveFunctionalPressureDrop_Impl.hpp"

#include <utilities/idd/Curve_Functional_PressureDrop_FieldEnums.hxx>

using namespace openstudio::model;

namespace openstudio {
namespace energyplus {

boost::optional<ModelObject> ReverseTranslator::translateCurveFunctionalPressureDrop( 
    const WorkspaceObject& workspaceObject )
{
  CurveFunctionalPressureDrop curve(m_model);

  OptionalString s;
  OptionalDouble d;
  
  if ((s = workspaceObject.name())) {
    curve.setName(*s);
  }

  if ((d = workspaceObject.getDouble(Curve_Functional_PressureDropFields::Diameter))) {
    curve.setDiameter(*d);
  }
  if ((d = workspaceObject.getDouble(Curve_Functional_PressureDropFields::MinorLossCoefficient))) {
    curve.setMinorLossCoefficient(*d);
  }
  if ((d = workspaceObject.getDouble(Curve_Functional_PressureDropFields::Length))) {
    curve.setLength(*d);
  }
  if ((d = workspaceObject.getDouble(Curve_Functional_PressureDropFields::Roughness))) {
    curve.setRoughness(*d);
  }
  if ((d = workspaceObject.getDouble(Curve_Functional_PressureDropFields::FixedFrictionFactor))) {
    curve.setFixedFrictionFactor(*d);
  }

  return curve;
}

} // energyplus
} // openstudio
