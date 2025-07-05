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

#ifndef UTILITIES_IDD_OS_LIFECYCLECOST_NONRECURRINGCOST_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_LIFECYCLECOST_NONRECURRINGCOST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_LifeCycleCost_NonrecurringCostFields
 *  \brief Enumeration of OS:LifeCycleCost:NonrecurringCost's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
OPENSTUDIO_ENUM( OS_LifeCycleCost_NonrecurringCostFields,
  ((Handle)(Handle))
  ((Name)(Name))
  ((Category)(Category))
  ((Cost)(Cost))
  ((StartofCosts)(Start of Costs))
  ((YearsfromStart)(Years from Start))
  ((MonthsfromStart)(Months from Start))
);
 *  \endcode */
OPENSTUDIO_ENUM( OS_LifeCycleCost_NonrecurringCostFields,
  ((Handle)(Handle))
  ((Name)(Name))
  ((Category)(Category))
  ((Cost)(Cost))
  ((StartofCosts)(Start of Costs))
  ((YearsfromStart)(Years from Start))
  ((MonthsfromStart)(Months from Start))
);

} // openstudio

#endif // UTILITIES_IDD_OS_LIFECYCLECOST_NONRECURRINGCOST_FIELDENUMS_HXX
