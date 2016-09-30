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

#ifndef UTILITIES_IDD_LIFECYCLECOST_USEADJUSTMENT_FIELDENUMS_HXX
#define UTILITIES_IDD_LIFECYCLECOST_USEADJUSTMENT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class LifeCycleCost_UseAdjustmentFields
 *  \brief Enumeration of LifeCycleCost:UseAdjustment's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(LifeCycleCost_UseAdjustmentFields, )
#else
class LifeCycleCost_UseAdjustmentFields: public ::EnumBase<LifeCycleCost_UseAdjustmentFields> {
 public: 
  enum domain 
  {
Name, Resource,   };
  LifeCycleCost_UseAdjustmentFields()
   : EnumBase<LifeCycleCost_UseAdjustmentFields>(Name) {} 
  LifeCycleCost_UseAdjustmentFields(const std::string &t_name) 
   : EnumBase<LifeCycleCost_UseAdjustmentFields>(t_name) {} 
  LifeCycleCost_UseAdjustmentFields(int t_value) 
   : EnumBase<LifeCycleCost_UseAdjustmentFields>(t_value) {} 
  static std::string enumName() 
  { return "LifeCycleCost_UseAdjustmentFields"; }
  domain value() const { return static_cast<domain>(EnumBase<LifeCycleCost_UseAdjustmentFields>::value()); }
   private:
    friend class EnumBase<LifeCycleCost_UseAdjustmentFields>;
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
{ LifeCycleCost_UseAdjustmentFields::Name, "Name", "Name"},
{ LifeCycleCost_UseAdjustmentFields::Resource, "Resource", "Resource"},
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
  inline std::ostream &operator<<(std::ostream &os, const LifeCycleCost_UseAdjustmentFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<LifeCycleCost_UseAdjustmentFields> OptionalLifeCycleCost_UseAdjustmentFields ;
#endif

/** \class LifeCycleCost_UseAdjustmentExtensibleFields
 *  \brief Enumeration of LifeCycleCost:UseAdjustment's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(LifeCycleCost_UseAdjustmentExtensibleFields, )
#else
class LifeCycleCost_UseAdjustmentExtensibleFields: public ::EnumBase<LifeCycleCost_UseAdjustmentExtensibleFields> {
 public: 
  enum domain 
  {
YearMultiplier,   };
  LifeCycleCost_UseAdjustmentExtensibleFields()
   : EnumBase<LifeCycleCost_UseAdjustmentExtensibleFields>(YearMultiplier) {} 
  LifeCycleCost_UseAdjustmentExtensibleFields(const std::string &t_name) 
   : EnumBase<LifeCycleCost_UseAdjustmentExtensibleFields>(t_name) {} 
  LifeCycleCost_UseAdjustmentExtensibleFields(int t_value) 
   : EnumBase<LifeCycleCost_UseAdjustmentExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "LifeCycleCost_UseAdjustmentExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<LifeCycleCost_UseAdjustmentExtensibleFields>::value()); }
   private:
    friend class EnumBase<LifeCycleCost_UseAdjustmentExtensibleFields>;
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
{ LifeCycleCost_UseAdjustmentExtensibleFields::YearMultiplier, "YearMultiplier", "Year Multiplier"},
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
  inline std::ostream &operator<<(std::ostream &os, const LifeCycleCost_UseAdjustmentExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<LifeCycleCost_UseAdjustmentExtensibleFields> OptionalLifeCycleCost_UseAdjustmentExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_LIFECYCLECOST_USEADJUSTMENT_FIELDENUMS_HXX
