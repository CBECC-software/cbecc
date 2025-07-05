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

#ifndef UTILITIES_IDD_HEATEXCHANGER_WATERSIDEECONOMIZER_FIELDENUMS_HXX
#define UTILITIES_IDD_HEATEXCHANGER_WATERSIDEECONOMIZER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HeatExchanger_WatersideEconomizerFields
 *  \brief Enumeration of HeatExchanger:WatersideEconomizer's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
OPENSTUDIO_ENUM( HeatExchanger_WatersideEconomizerFields,
  ((Name)(Name))
  ((HeatExchangerType)(Heat Exchanger Type))
  ((AvailabilityScheduleName)(Availability Schedule Name))
  ((ChilledWaterInletNodeName)(Chilled Water Inlet Node Name))
  ((ChilledWaterOutletNodeName)(Chilled Water Outlet Node Name))
  ((CondenserInletNodeName)(Condenser Inlet Node Name))
  ((CondenserOutletNodeName)(Condenser Outlet Node Name))
  ((ChilledWaterSideMaximumFlowRate)(Chilled Water Side Maximum Flow Rate))
  ((CondenserSideMaximumFlowRate)(Condenser Side Maximum Flow Rate))
  ((HeatExchangerUFactorTimesAreaValue)(Heat Exchanger U-Factor Times Area Value))
  ((MinimumTemperatureDifferencetoActivateHeatExchanger)(Minimum Temperature Difference to Activate Heat Exchanger))
);
 *  \endcode */
OPENSTUDIO_ENUM( HeatExchanger_WatersideEconomizerFields,
  ((Name)(Name))
  ((HeatExchangerType)(Heat Exchanger Type))
  ((AvailabilityScheduleName)(Availability Schedule Name))
  ((ChilledWaterInletNodeName)(Chilled Water Inlet Node Name))
  ((ChilledWaterOutletNodeName)(Chilled Water Outlet Node Name))
  ((CondenserInletNodeName)(Condenser Inlet Node Name))
  ((CondenserOutletNodeName)(Condenser Outlet Node Name))
  ((ChilledWaterSideMaximumFlowRate)(Chilled Water Side Maximum Flow Rate))
  ((CondenserSideMaximumFlowRate)(Condenser Side Maximum Flow Rate))
  ((HeatExchangerUFactorTimesAreaValue)(Heat Exchanger U-Factor Times Area Value))
  ((MinimumTemperatureDifferencetoActivateHeatExchanger)(Minimum Temperature Difference to Activate Heat Exchanger))
);

} // openstudio

#endif // UTILITIES_IDD_HEATEXCHANGER_WATERSIDEECONOMIZER_FIELDENUMS_HXX
