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

#ifndef UTILITIES_IDD_LIFECYCLECOST_USEPRICEESCALATION_FIELDENUMS_HXX
#define UTILITIES_IDD_LIFECYCLECOST_USEPRICEESCALATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class LifeCycleCost_UsePriceEscalationFields
 *  \brief Enumeration of LifeCycleCost:UsePriceEscalation's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(LifeCycleCost_UsePriceEscalationFields, )
#else
class LifeCycleCost_UsePriceEscalationFields: public ::EnumBase<LifeCycleCost_UsePriceEscalationFields> {
 public: 
  enum domain 
  {
Name, Resource, EscalationStartYear, EscalationStartMonth,   };
  LifeCycleCost_UsePriceEscalationFields()
   : EnumBase<LifeCycleCost_UsePriceEscalationFields>(Name) {} 
  LifeCycleCost_UsePriceEscalationFields(const std::string &t_name) 
   : EnumBase<LifeCycleCost_UsePriceEscalationFields>(t_name) {} 
  LifeCycleCost_UsePriceEscalationFields(int t_value) 
   : EnumBase<LifeCycleCost_UsePriceEscalationFields>(t_value) {} 
  static std::string enumName() 
  { return "LifeCycleCost_UsePriceEscalationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<LifeCycleCost_UsePriceEscalationFields>::value()); }
   private:
    friend class EnumBase<LifeCycleCost_UsePriceEscalationFields>;
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
{ LifeCycleCost_UsePriceEscalationFields::Name, "Name", "Name"},
{ LifeCycleCost_UsePriceEscalationFields::Resource, "Resource", "Resource"},
{ LifeCycleCost_UsePriceEscalationFields::EscalationStartYear, "EscalationStartYear", "Escalation Start Year"},
{ LifeCycleCost_UsePriceEscalationFields::EscalationStartMonth, "EscalationStartMonth", "Escalation Start Month"},
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
  inline std::ostream &operator<<(std::ostream &os, const LifeCycleCost_UsePriceEscalationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<LifeCycleCost_UsePriceEscalationFields> OptionalLifeCycleCost_UsePriceEscalationFields ;
#endif

/** \class LifeCycleCost_UsePriceEscalationExtensibleFields
 *  \brief Enumeration of LifeCycleCost:UsePriceEscalation's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(LifeCycleCost_UsePriceEscalationExtensibleFields, )
#else
class LifeCycleCost_UsePriceEscalationExtensibleFields: public ::EnumBase<LifeCycleCost_UsePriceEscalationExtensibleFields> {
 public: 
  enum domain 
  {
YearEscalation,   };
  LifeCycleCost_UsePriceEscalationExtensibleFields()
   : EnumBase<LifeCycleCost_UsePriceEscalationExtensibleFields>(YearEscalation) {} 
  LifeCycleCost_UsePriceEscalationExtensibleFields(const std::string &t_name) 
   : EnumBase<LifeCycleCost_UsePriceEscalationExtensibleFields>(t_name) {} 
  LifeCycleCost_UsePriceEscalationExtensibleFields(int t_value) 
   : EnumBase<LifeCycleCost_UsePriceEscalationExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "LifeCycleCost_UsePriceEscalationExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<LifeCycleCost_UsePriceEscalationExtensibleFields>::value()); }
   private:
    friend class EnumBase<LifeCycleCost_UsePriceEscalationExtensibleFields>;
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
{ LifeCycleCost_UsePriceEscalationExtensibleFields::YearEscalation, "YearEscalation", "Year Escalation"},
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
  inline std::ostream &operator<<(std::ostream &os, const LifeCycleCost_UsePriceEscalationExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<LifeCycleCost_UsePriceEscalationExtensibleFields> OptionalLifeCycleCost_UsePriceEscalationExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_LIFECYCLECOST_USEPRICEESCALATION_FIELDENUMS_HXX
