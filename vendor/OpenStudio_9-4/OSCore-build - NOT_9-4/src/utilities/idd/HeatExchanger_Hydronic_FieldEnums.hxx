/**********************************************************************
*  Copyright (c) 2008-2013, Alliance for Sustainable Energy.
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

#ifndef UTILITIES_IDD_HEATEXCHANGER_HYDRONIC_FIELDENUMS_HXX
#define UTILITIES_IDD_HEATEXCHANGER_HYDRONIC_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HeatExchanger_HydronicFields
 *  \brief Enumeration of HeatExchanger:Hydronic's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
OPENSTUDIO_ENUM( HeatExchanger_HydronicFields,
  ((Name)(Name))
  ((ControlledComponentName)(Controlled Component Name))
  ((ControlledComponentObjectType)(Controlled Component Object Type))
  ((SetpointScheduleName)(Setpoint Schedule Name))
  ((CondenserInletNodeName)(Condenser Inlet Node Name))
  ((CondenserOutletNodeName)(Condenser Outlet Node Name))
  ((PlantInletNodeName)(Plant Inlet Node Name))
  ((PlantOutletNodeName)(Plant Outlet Node Name))
  ((FreeCoolingControlMode)(Free Cooling Control Mode))
  ((HeatExchangerSetpointScheduleName)(Heat Exchanger Setpoint Schedule Name))
  ((HeatExchangeMode)(Heat Exchange Mode))
  ((UFactorTimesAreaValue)(U-Factor Times Area Value))
  ((CondenserSideFlowRate)(Condenser Side Flow Rate))
  ((PlantSideFlowRate)(Plant Side Flow Rate))
  ((ControlledComponentCondenserInletNodeName)(Controlled Component Condenser Inlet Node Name))
  ((ControlledComponentCondenserOutletNodeName)(Controlled Component Condenser Outlet Node Name))
  ((ControlledComponentPlantInletNodeName)(Controlled Component Plant Inlet Node Name))
  ((ControlledComponentPlantOutletNodeName)(Controlled Component Plant Outlet Node Name))
);
 *  \endcode */
OPENSTUDIO_ENUM( HeatExchanger_HydronicFields,
  ((Name)(Name))
  ((ControlledComponentName)(Controlled Component Name))
  ((ControlledComponentObjectType)(Controlled Component Object Type))
  ((SetpointScheduleName)(Setpoint Schedule Name))
  ((CondenserInletNodeName)(Condenser Inlet Node Name))
  ((CondenserOutletNodeName)(Condenser Outlet Node Name))
  ((PlantInletNodeName)(Plant Inlet Node Name))
  ((PlantOutletNodeName)(Plant Outlet Node Name))
  ((FreeCoolingControlMode)(Free Cooling Control Mode))
  ((HeatExchangerSetpointScheduleName)(Heat Exchanger Setpoint Schedule Name))
  ((HeatExchangeMode)(Heat Exchange Mode))
  ((UFactorTimesAreaValue)(U-Factor Times Area Value))
  ((CondenserSideFlowRate)(Condenser Side Flow Rate))
  ((PlantSideFlowRate)(Plant Side Flow Rate))
  ((ControlledComponentCondenserInletNodeName)(Controlled Component Condenser Inlet Node Name))
  ((ControlledComponentCondenserOutletNodeName)(Controlled Component Condenser Outlet Node Name))
  ((ControlledComponentPlantInletNodeName)(Controlled Component Plant Inlet Node Name))
  ((ControlledComponentPlantOutletNodeName)(Controlled Component Plant Outlet Node Name))
);

} // openstudio

#endif // UTILITIES_IDD_HEATEXCHANGER_HYDRONIC_FIELDENUMS_HXX
