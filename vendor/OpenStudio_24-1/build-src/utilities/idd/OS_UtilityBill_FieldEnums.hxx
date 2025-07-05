/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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
