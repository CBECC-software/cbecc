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

#ifndef UTILITIES_IDD_OS_COMPONENTCOST_LINEITEM_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COMPONENTCOST_LINEITEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ComponentCost_LineItemFields
 *  \brief Enumeration of OS:ComponentCost:LineItem's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
OPENSTUDIO_ENUM( OS_ComponentCost_LineItemFields,
  ((Handle)(Handle))
  ((Name)(Name))
  ((Type)(Type))
  ((LineItemType)(Line Item Type))
  ((ItemName)(Item Name))
  ((ObjectEndUseKey)(Object End Use Key))
  ((Quantity)(Quantity))
  ((MaterialCost)(Material Cost))
  ((MaterialCostUnits)(Material Cost Units))
  ((InstallationCost)(Installation Cost))
  ((InstallationCostUnits)(Installation Cost Units))
  ((ExpectedLife)(Expected Life))
  ((DemolitionCost)(Demolition Cost))
  ((DemolitionCostUnits)(Demolition Cost Units))
  ((SalvageValue)(Salvage Value))
  ((SalvageValueUnits)(Salvage Value Units))
);
 *  \endcode */
OPENSTUDIO_ENUM( OS_ComponentCost_LineItemFields,
  ((Handle)(Handle))
  ((Name)(Name))
  ((Type)(Type))
  ((LineItemType)(Line Item Type))
  ((ItemName)(Item Name))
  ((ObjectEndUseKey)(Object End Use Key))
  ((Quantity)(Quantity))
  ((MaterialCost)(Material Cost))
  ((MaterialCostUnits)(Material Cost Units))
  ((InstallationCost)(Installation Cost))
  ((InstallationCostUnits)(Installation Cost Units))
  ((ExpectedLife)(Expected Life))
  ((DemolitionCost)(Demolition Cost))
  ((DemolitionCostUnits)(Demolition Cost Units))
  ((SalvageValue)(Salvage Value))
  ((SalvageValueUnits)(Salvage Value Units))
);

/** \class OS_ComponentCost_LineItemExtensibleFields
 *  \brief Enumeration of OS:ComponentCost:LineItem's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
OPENSTUDIO_ENUM( OS_ComponentCost_LineItemExtensibleFields,
  ((RecurringCostName)(Recurring Cost Name))
  ((RecurringCostType)(Recurring Cost Type))
  ((RecurringCost)(Recurring Cost))
  ((RecurringCostUnits)(Recurring Cost Units))
  ((RecurringCostIntervalYears)(Recurring Cost Interval Years))
  ((RecurringCostIntervalMonths)(Recurring Cost Interval Months))
);
 *  \endcode */
OPENSTUDIO_ENUM( OS_ComponentCost_LineItemExtensibleFields,
  ((RecurringCostName)(Recurring Cost Name))
  ((RecurringCostType)(Recurring Cost Type))
  ((RecurringCost)(Recurring Cost))
  ((RecurringCostUnits)(Recurring Cost Units))
  ((RecurringCostIntervalYears)(Recurring Cost Interval Years))
  ((RecurringCostIntervalMonths)(Recurring Cost Interval Months))
);

} // openstudio

#endif // UTILITIES_IDD_OS_COMPONENTCOST_LINEITEM_FIELDENUMS_HXX
