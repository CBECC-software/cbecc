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

#ifndef UTILITIES_IDD_OS_COMPONENTCOST_ADJUSTMENTS_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COMPONENTCOST_ADJUSTMENTS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ComponentCost_AdjustmentsFields
 *  \brief Enumeration of OS:ComponentCost:Adjustments's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ComponentCost_AdjustmentsFields, )
#else
class OS_ComponentCost_AdjustmentsFields: public ::EnumBase<OS_ComponentCost_AdjustmentsFields> {
 public: 
  enum domain 
  {
Handle, MiscellaneousCostperConditionedArea, DesignandEngineeringFees, ContractorFee, Contingency, PermitsBondingandInsurance, CommissioningFee, RegionalAdjustmentFactor,   };
  OS_ComponentCost_AdjustmentsFields()
   : EnumBase<OS_ComponentCost_AdjustmentsFields>(Handle) {} 
  OS_ComponentCost_AdjustmentsFields(const std::string &t_name) 
   : EnumBase<OS_ComponentCost_AdjustmentsFields>(t_name) {} 
  OS_ComponentCost_AdjustmentsFields(int t_value) 
   : EnumBase<OS_ComponentCost_AdjustmentsFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ComponentCost_AdjustmentsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ComponentCost_AdjustmentsFields>::value()); }
   private:
    friend class EnumBase<OS_ComponentCost_AdjustmentsFields>;
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
{ OS_ComponentCost_AdjustmentsFields::Handle, "Handle", "Handle"},
{ OS_ComponentCost_AdjustmentsFields::MiscellaneousCostperConditionedArea, "MiscellaneousCostperConditionedArea", "Miscellaneous Cost per Conditioned Area"},
{ OS_ComponentCost_AdjustmentsFields::DesignandEngineeringFees, "DesignandEngineeringFees", "Design and Engineering Fees"},
{ OS_ComponentCost_AdjustmentsFields::ContractorFee, "ContractorFee", "Contractor Fee"},
{ OS_ComponentCost_AdjustmentsFields::Contingency, "Contingency", "Contingency"},
{ OS_ComponentCost_AdjustmentsFields::PermitsBondingandInsurance, "PermitsBondingandInsurance", "Permits Bonding and Insurance"},
{ OS_ComponentCost_AdjustmentsFields::CommissioningFee, "CommissioningFee", "Commissioning Fee"},
{ OS_ComponentCost_AdjustmentsFields::RegionalAdjustmentFactor, "RegionalAdjustmentFactor", "Regional Adjustment Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ComponentCost_AdjustmentsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ComponentCost_AdjustmentsFields> OptionalOS_ComponentCost_AdjustmentsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COMPONENTCOST_ADJUSTMENTS_FIELDENUMS_HXX
