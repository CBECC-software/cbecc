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

#ifndef UTILITIES_IDD_OS_UTILITYCOST_TARIFF_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_UTILITYCOST_TARIFF_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_UtilityCost_TariffFields
 *  \brief Enumeration of OS:UtilityCost:Tariff's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_UtilityCost_TariffFields, )
#else
class OS_UtilityCost_TariffFields: public ::EnumBase<OS_UtilityCost_TariffFields> {
 public: 
  enum domain 
  {
Handle, Name, OutputMeterName, ConversionFactorChoice, EnergyConversionFactor, DemandConversionFactor, TimeofUsePeriodScheduleName, SeasonScheduleName, MonthScheduleName, DemandWindowLength, MonthlyChargeorVariableName, MinimumMonthlyChargeorVariableName, RealTimePricingChargeScheduleName, CustomerBaselineLoadScheduleName, GroupName, BuyOrSell,   };
  OS_UtilityCost_TariffFields()
   : EnumBase<OS_UtilityCost_TariffFields>(Handle) {} 
  OS_UtilityCost_TariffFields(const std::string &t_name) 
   : EnumBase<OS_UtilityCost_TariffFields>(t_name) {} 
  OS_UtilityCost_TariffFields(int t_value) 
   : EnumBase<OS_UtilityCost_TariffFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_UtilityCost_TariffFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_UtilityCost_TariffFields>::value()); }
   private:
    friend class EnumBase<OS_UtilityCost_TariffFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ OS_UtilityCost_TariffFields::Handle, "Handle", "Handle"},
{ OS_UtilityCost_TariffFields::Name, "Name", "Name"},
{ OS_UtilityCost_TariffFields::OutputMeterName, "OutputMeterName", "Output Meter Name"},
{ OS_UtilityCost_TariffFields::ConversionFactorChoice, "ConversionFactorChoice", "Conversion Factor Choice"},
{ OS_UtilityCost_TariffFields::EnergyConversionFactor, "EnergyConversionFactor", "Energy Conversion Factor"},
{ OS_UtilityCost_TariffFields::DemandConversionFactor, "DemandConversionFactor", "Demand Conversion Factor"},
{ OS_UtilityCost_TariffFields::TimeofUsePeriodScheduleName, "TimeofUsePeriodScheduleName", "Time of Use Period Schedule Name"},
{ OS_UtilityCost_TariffFields::SeasonScheduleName, "SeasonScheduleName", "Season Schedule Name"},
{ OS_UtilityCost_TariffFields::MonthScheduleName, "MonthScheduleName", "Month Schedule Name"},
{ OS_UtilityCost_TariffFields::DemandWindowLength, "DemandWindowLength", "Demand Window Length"},
{ OS_UtilityCost_TariffFields::MonthlyChargeorVariableName, "MonthlyChargeorVariableName", "Monthly Charge or Variable Name"},
{ OS_UtilityCost_TariffFields::MinimumMonthlyChargeorVariableName, "MinimumMonthlyChargeorVariableName", "Minimum Monthly Charge or Variable Name"},
{ OS_UtilityCost_TariffFields::RealTimePricingChargeScheduleName, "RealTimePricingChargeScheduleName", "Real Time Pricing Charge Schedule Name"},
{ OS_UtilityCost_TariffFields::CustomerBaselineLoadScheduleName, "CustomerBaselineLoadScheduleName", "Customer Baseline Load Schedule Name"},
{ OS_UtilityCost_TariffFields::GroupName, "GroupName", "Group Name"},
{ OS_UtilityCost_TariffFields::BuyOrSell, "BuyOrSell", "Buy Or Sell"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const OS_UtilityCost_TariffFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_UtilityCost_TariffFields> OptionalOS_UtilityCost_TariffFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_UTILITYCOST_TARIFF_FIELDENUMS_HXX
