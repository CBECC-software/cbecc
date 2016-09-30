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

#ifndef UTILITIES_IDD_OS_UTILITYBILL_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_UTILITYBILL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_UtilityBillFields
 *  \brief Enumeration of OS:UtilityBill's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_UtilityBillFields, )
#else
class OS_UtilityBillFields: public ::EnumBase<OS_UtilityBillFields> {
 public: 
  enum domain 
  {
Handle, Name, FuelType, MeterInstallLocation, MeterSpecificInstallLocation, MeterEndUseCategory, MeterSpecificEndUse, ConsumptionUnit, ConsumptionUnitConversionFactor, PeakDemandUnit, TimestepsinPeakDemandWindow,   };
  OS_UtilityBillFields()
   : EnumBase<OS_UtilityBillFields>(Handle) {} 
  OS_UtilityBillFields(const std::string &t_name) 
   : EnumBase<OS_UtilityBillFields>(t_name) {} 
  OS_UtilityBillFields(int t_value) 
   : EnumBase<OS_UtilityBillFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_UtilityBillFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_UtilityBillFields>::value()); }
   private:
    friend class EnumBase<OS_UtilityBillFields>;
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
{ OS_UtilityBillFields::Handle, "Handle", "Handle"},
{ OS_UtilityBillFields::Name, "Name", "Name"},
{ OS_UtilityBillFields::FuelType, "FuelType", "Fuel Type"},
{ OS_UtilityBillFields::MeterInstallLocation, "MeterInstallLocation", "Meter Install Location"},
{ OS_UtilityBillFields::MeterSpecificInstallLocation, "MeterSpecificInstallLocation", "Meter Specific Install Location"},
{ OS_UtilityBillFields::MeterEndUseCategory, "MeterEndUseCategory", "Meter End Use Category"},
{ OS_UtilityBillFields::MeterSpecificEndUse, "MeterSpecificEndUse", "Meter Specific End Use"},
{ OS_UtilityBillFields::ConsumptionUnit, "ConsumptionUnit", "Consumption Unit"},
{ OS_UtilityBillFields::ConsumptionUnitConversionFactor, "ConsumptionUnitConversionFactor", "Consumption Unit Conversion Factor"},
{ OS_UtilityBillFields::PeakDemandUnit, "PeakDemandUnit", "Peak Demand Unit"},
{ OS_UtilityBillFields::TimestepsinPeakDemandWindow, "TimestepsinPeakDemandWindow", "Timesteps in Peak Demand Window"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_UtilityBillFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_UtilityBillFields> OptionalOS_UtilityBillFields ;
#endif

/** \class OS_UtilityBillExtensibleFields
 *  \brief Enumeration of OS:UtilityBill's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_UtilityBillExtensibleFields, )
#else
class OS_UtilityBillExtensibleFields: public ::EnumBase<OS_UtilityBillExtensibleFields> {
 public: 
  enum domain 
  {
BillingPeriodBeginMonth, BillingPeriodBeginDayofMonth, BillingPeriodBeginYear, NumberofDaysinBillingPeriod, BillingPeriodConsumption, BillingPeriodPeakDemand, BillingPeriodTotalCost,   };
  OS_UtilityBillExtensibleFields()
   : EnumBase<OS_UtilityBillExtensibleFields>(BillingPeriodBeginMonth) {} 
  OS_UtilityBillExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_UtilityBillExtensibleFields>(t_name) {} 
  OS_UtilityBillExtensibleFields(int t_value) 
   : EnumBase<OS_UtilityBillExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_UtilityBillExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_UtilityBillExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_UtilityBillExtensibleFields>;
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
{ OS_UtilityBillExtensibleFields::BillingPeriodBeginMonth, "BillingPeriodBeginMonth", "Billing Period Begin Month"},
{ OS_UtilityBillExtensibleFields::BillingPeriodBeginDayofMonth, "BillingPeriodBeginDayofMonth", "Billing Period Begin Day of Month"},
{ OS_UtilityBillExtensibleFields::BillingPeriodBeginYear, "BillingPeriodBeginYear", "Billing Period Begin Year"},
{ OS_UtilityBillExtensibleFields::NumberofDaysinBillingPeriod, "NumberofDaysinBillingPeriod", "Number of Days in Billing Period"},
{ OS_UtilityBillExtensibleFields::BillingPeriodConsumption, "BillingPeriodConsumption", "Billing Period Consumption"},
{ OS_UtilityBillExtensibleFields::BillingPeriodPeakDemand, "BillingPeriodPeakDemand", "Billing Period Peak Demand"},
{ OS_UtilityBillExtensibleFields::BillingPeriodTotalCost, "BillingPeriodTotalCost", "Billing Period Total Cost"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_UtilityBillExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_UtilityBillExtensibleFields> OptionalOS_UtilityBillExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_UTILITYBILL_FIELDENUMS_HXX
