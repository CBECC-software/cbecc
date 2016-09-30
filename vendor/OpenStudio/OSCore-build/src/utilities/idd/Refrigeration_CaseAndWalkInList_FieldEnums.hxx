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

#ifndef UTILITIES_IDD_REFRIGERATION_CASEANDWALKINLIST_FIELDENUMS_HXX
#define UTILITIES_IDD_REFRIGERATION_CASEANDWALKINLIST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Refrigeration_CaseAndWalkInListFields
 *  \brief Enumeration of Refrigeration:CaseAndWalkInList's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Refrigeration_CaseAndWalkInListFields, )
#else
class Refrigeration_CaseAndWalkInListFields: public ::EnumBase<Refrigeration_CaseAndWalkInListFields> {
 public: 
  enum domain 
  {
Name,   };
  Refrigeration_CaseAndWalkInListFields()
   : EnumBase<Refrigeration_CaseAndWalkInListFields>(Name) {} 
  Refrigeration_CaseAndWalkInListFields(const std::string &t_name) 
   : EnumBase<Refrigeration_CaseAndWalkInListFields>(t_name) {} 
  Refrigeration_CaseAndWalkInListFields(int t_value) 
   : EnumBase<Refrigeration_CaseAndWalkInListFields>(t_value) {} 
  static std::string enumName() 
  { return "Refrigeration_CaseAndWalkInListFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Refrigeration_CaseAndWalkInListFields>::value()); }
   private:
    friend class EnumBase<Refrigeration_CaseAndWalkInListFields>;
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
{ Refrigeration_CaseAndWalkInListFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Refrigeration_CaseAndWalkInListFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Refrigeration_CaseAndWalkInListFields> OptionalRefrigeration_CaseAndWalkInListFields ;
#endif

/** \class Refrigeration_CaseAndWalkInListExtensibleFields
 *  \brief Enumeration of Refrigeration:CaseAndWalkInList's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Refrigeration_CaseAndWalkInListExtensibleFields, )
#else
class Refrigeration_CaseAndWalkInListExtensibleFields: public ::EnumBase<Refrigeration_CaseAndWalkInListExtensibleFields> {
 public: 
  enum domain 
  {
CaseorWalkInName,   };
  Refrigeration_CaseAndWalkInListExtensibleFields()
   : EnumBase<Refrigeration_CaseAndWalkInListExtensibleFields>(CaseorWalkInName) {} 
  Refrigeration_CaseAndWalkInListExtensibleFields(const std::string &t_name) 
   : EnumBase<Refrigeration_CaseAndWalkInListExtensibleFields>(t_name) {} 
  Refrigeration_CaseAndWalkInListExtensibleFields(int t_value) 
   : EnumBase<Refrigeration_CaseAndWalkInListExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Refrigeration_CaseAndWalkInListExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Refrigeration_CaseAndWalkInListExtensibleFields>::value()); }
   private:
    friend class EnumBase<Refrigeration_CaseAndWalkInListExtensibleFields>;
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
{ Refrigeration_CaseAndWalkInListExtensibleFields::CaseorWalkInName, "CaseorWalkInName", "Case or WalkIn Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Refrigeration_CaseAndWalkInListExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Refrigeration_CaseAndWalkInListExtensibleFields> OptionalRefrigeration_CaseAndWalkInListExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_REFRIGERATION_CASEANDWALKINLIST_FIELDENUMS_HXX
