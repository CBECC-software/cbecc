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

#ifndef UTILITIES_IDD_LIFECYCLECOST_PARAMETERS_FIELDENUMS_HXX
#define UTILITIES_IDD_LIFECYCLECOST_PARAMETERS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class LifeCycleCost_ParametersFields
 *  \brief Enumeration of LifeCycleCost:Parameters's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(LifeCycleCost_ParametersFields, )
#else
class LifeCycleCost_ParametersFields: public ::EnumBase<LifeCycleCost_ParametersFields> {
 public: 
  enum domain 
  {
Name, DiscountingConvention, InflationApproach, RealDiscountRate, NominalDiscountRate, Inflation, BaseDateMonth, BaseDateYear, ServiceDateMonth, ServiceDateYear, LengthofStudyPeriodinYears, Taxrate, DepreciationMethod,   };
  LifeCycleCost_ParametersFields()
   : EnumBase<LifeCycleCost_ParametersFields>(Name) {} 
  LifeCycleCost_ParametersFields(const std::string &t_name) 
   : EnumBase<LifeCycleCost_ParametersFields>(t_name) {} 
  LifeCycleCost_ParametersFields(int t_value) 
   : EnumBase<LifeCycleCost_ParametersFields>(t_value) {} 
  static std::string enumName() 
  { return "LifeCycleCost_ParametersFields"; }
  domain value() const { return static_cast<domain>(EnumBase<LifeCycleCost_ParametersFields>::value()); }
   private:
    friend class EnumBase<LifeCycleCost_ParametersFields>;
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
{ LifeCycleCost_ParametersFields::Name, "Name", "Name"},
{ LifeCycleCost_ParametersFields::DiscountingConvention, "DiscountingConvention", "Discounting Convention"},
{ LifeCycleCost_ParametersFields::InflationApproach, "InflationApproach", "Inflation Approach"},
{ LifeCycleCost_ParametersFields::RealDiscountRate, "RealDiscountRate", "Real Discount Rate"},
{ LifeCycleCost_ParametersFields::NominalDiscountRate, "NominalDiscountRate", "Nominal Discount Rate"},
{ LifeCycleCost_ParametersFields::Inflation, "Inflation", "Inflation"},
{ LifeCycleCost_ParametersFields::BaseDateMonth, "BaseDateMonth", "Base Date Month"},
{ LifeCycleCost_ParametersFields::BaseDateYear, "BaseDateYear", "Base Date Year"},
{ LifeCycleCost_ParametersFields::ServiceDateMonth, "ServiceDateMonth", "Service Date Month"},
{ LifeCycleCost_ParametersFields::ServiceDateYear, "ServiceDateYear", "Service Date Year"},
{ LifeCycleCost_ParametersFields::LengthofStudyPeriodinYears, "LengthofStudyPeriodinYears", "Length of Study Period in Years"},
{ LifeCycleCost_ParametersFields::Taxrate, "Taxrate", "Tax rate"},
{ LifeCycleCost_ParametersFields::DepreciationMethod, "DepreciationMethod", "Depreciation Method"},
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
  inline std::ostream &operator<<(std::ostream &os, const LifeCycleCost_ParametersFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<LifeCycleCost_ParametersFields> OptionalLifeCycleCost_ParametersFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_LIFECYCLECOST_PARAMETERS_FIELDENUMS_HXX
