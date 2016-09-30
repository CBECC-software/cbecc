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

#ifndef UTILITIES_IDD_BRANCHLIST_FIELDENUMS_HXX
#define UTILITIES_IDD_BRANCHLIST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class BranchListFields
 *  \brief Enumeration of BranchList's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(BranchListFields, )
#else
class BranchListFields: public ::EnumBase<BranchListFields> {
 public: 
  enum domain 
  {
Name,   };
  BranchListFields()
   : EnumBase<BranchListFields>(Name) {} 
  BranchListFields(const std::string &t_name) 
   : EnumBase<BranchListFields>(t_name) {} 
  BranchListFields(int t_value) 
   : EnumBase<BranchListFields>(t_value) {} 
  static std::string enumName() 
  { return "BranchListFields"; }
  domain value() const { return static_cast<domain>(EnumBase<BranchListFields>::value()); }
   private:
    friend class EnumBase<BranchListFields>;
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
{ BranchListFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const BranchListFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<BranchListFields> OptionalBranchListFields ;
#endif

/** \class BranchListExtensibleFields
 *  \brief Enumeration of BranchList's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(BranchListExtensibleFields, )
#else
class BranchListExtensibleFields: public ::EnumBase<BranchListExtensibleFields> {
 public: 
  enum domain 
  {
BranchName,   };
  BranchListExtensibleFields()
   : EnumBase<BranchListExtensibleFields>(BranchName) {} 
  BranchListExtensibleFields(const std::string &t_name) 
   : EnumBase<BranchListExtensibleFields>(t_name) {} 
  BranchListExtensibleFields(int t_value) 
   : EnumBase<BranchListExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "BranchListExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<BranchListExtensibleFields>::value()); }
   private:
    friend class EnumBase<BranchListExtensibleFields>;
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
{ BranchListExtensibleFields::BranchName, "BranchName", "Branch Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const BranchListExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<BranchListExtensibleFields> OptionalBranchListExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_BRANCHLIST_FIELDENUMS_HXX
