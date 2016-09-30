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

#ifndef UTILITIES_IDD_OS_LIFECYCLECOST_USEPRICEESCALATION_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_LIFECYCLECOST_USEPRICEESCALATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_LifeCycleCost_UsePriceEscalationFields
 *  \brief Enumeration of OS:LifeCycleCost:UsePriceEscalation's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_LifeCycleCost_UsePriceEscalationFields, )
#else
class OS_LifeCycleCost_UsePriceEscalationFields: public ::EnumBase<OS_LifeCycleCost_UsePriceEscalationFields> {
 public: 
  enum domain 
  {
Handle, Name, Resource, EscalationStartYear, EscalationStartMonth,   };
  OS_LifeCycleCost_UsePriceEscalationFields()
   : EnumBase<OS_LifeCycleCost_UsePriceEscalationFields>(Handle) {} 
  OS_LifeCycleCost_UsePriceEscalationFields(const std::string &t_name) 
   : EnumBase<OS_LifeCycleCost_UsePriceEscalationFields>(t_name) {} 
  OS_LifeCycleCost_UsePriceEscalationFields(int t_value) 
   : EnumBase<OS_LifeCycleCost_UsePriceEscalationFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_LifeCycleCost_UsePriceEscalationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_LifeCycleCost_UsePriceEscalationFields>::value()); }
   private:
    friend class EnumBase<OS_LifeCycleCost_UsePriceEscalationFields>;
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
{ OS_LifeCycleCost_UsePriceEscalationFields::Handle, "Handle", "Handle"},
{ OS_LifeCycleCost_UsePriceEscalationFields::Name, "Name", "Name"},
{ OS_LifeCycleCost_UsePriceEscalationFields::Resource, "Resource", "Resource"},
{ OS_LifeCycleCost_UsePriceEscalationFields::EscalationStartYear, "EscalationStartYear", "Escalation Start Year"},
{ OS_LifeCycleCost_UsePriceEscalationFields::EscalationStartMonth, "EscalationStartMonth", "Escalation Start Month"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_LifeCycleCost_UsePriceEscalationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_LifeCycleCost_UsePriceEscalationFields> OptionalOS_LifeCycleCost_UsePriceEscalationFields ;
#endif

/** \class OS_LifeCycleCost_UsePriceEscalationExtensibleFields
 *  \brief Enumeration of OS:LifeCycleCost:UsePriceEscalation's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_LifeCycleCost_UsePriceEscalationExtensibleFields, )
#else
class OS_LifeCycleCost_UsePriceEscalationExtensibleFields: public ::EnumBase<OS_LifeCycleCost_UsePriceEscalationExtensibleFields> {
 public: 
  enum domain 
  {
YearEscalation,   };
  OS_LifeCycleCost_UsePriceEscalationExtensibleFields()
   : EnumBase<OS_LifeCycleCost_UsePriceEscalationExtensibleFields>(YearEscalation) {} 
  OS_LifeCycleCost_UsePriceEscalationExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_LifeCycleCost_UsePriceEscalationExtensibleFields>(t_name) {} 
  OS_LifeCycleCost_UsePriceEscalationExtensibleFields(int t_value) 
   : EnumBase<OS_LifeCycleCost_UsePriceEscalationExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_LifeCycleCost_UsePriceEscalationExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_LifeCycleCost_UsePriceEscalationExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_LifeCycleCost_UsePriceEscalationExtensibleFields>;
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
{ OS_LifeCycleCost_UsePriceEscalationExtensibleFields::YearEscalation, "YearEscalation", "Year Escalation"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_LifeCycleCost_UsePriceEscalationExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_LifeCycleCost_UsePriceEscalationExtensibleFields> OptionalOS_LifeCycleCost_UsePriceEscalationExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_LIFECYCLECOST_USEPRICEESCALATION_FIELDENUMS_HXX
