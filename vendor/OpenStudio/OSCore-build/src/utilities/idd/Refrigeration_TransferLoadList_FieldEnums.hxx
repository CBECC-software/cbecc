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

#ifndef UTILITIES_IDD_REFRIGERATION_TRANSFERLOADLIST_FIELDENUMS_HXX
#define UTILITIES_IDD_REFRIGERATION_TRANSFERLOADLIST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Refrigeration_TransferLoadListFields
 *  \brief Enumeration of Refrigeration:TransferLoadList's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Refrigeration_TransferLoadListFields, )
#else
class Refrigeration_TransferLoadListFields: public ::EnumBase<Refrigeration_TransferLoadListFields> {
 public: 
  enum domain 
  {
Name,   };
  Refrigeration_TransferLoadListFields()
   : EnumBase<Refrigeration_TransferLoadListFields>(Name) {} 
  Refrigeration_TransferLoadListFields(const std::string &t_name) 
   : EnumBase<Refrigeration_TransferLoadListFields>(t_name) {} 
  Refrigeration_TransferLoadListFields(int t_value) 
   : EnumBase<Refrigeration_TransferLoadListFields>(t_value) {} 
  static std::string enumName() 
  { return "Refrigeration_TransferLoadListFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Refrigeration_TransferLoadListFields>::value()); }
   private:
    friend class EnumBase<Refrigeration_TransferLoadListFields>;
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
{ Refrigeration_TransferLoadListFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Refrigeration_TransferLoadListFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Refrigeration_TransferLoadListFields> OptionalRefrigeration_TransferLoadListFields ;
#endif

/** \class Refrigeration_TransferLoadListExtensibleFields
 *  \brief Enumeration of Refrigeration:TransferLoadList's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Refrigeration_TransferLoadListExtensibleFields, )
#else
class Refrigeration_TransferLoadListExtensibleFields: public ::EnumBase<Refrigeration_TransferLoadListExtensibleFields> {
 public: 
  enum domain 
  {
CascadeCondenserNameorSecondarySystemName,   };
  Refrigeration_TransferLoadListExtensibleFields()
   : EnumBase<Refrigeration_TransferLoadListExtensibleFields>(CascadeCondenserNameorSecondarySystemName) {} 
  Refrigeration_TransferLoadListExtensibleFields(const std::string &t_name) 
   : EnumBase<Refrigeration_TransferLoadListExtensibleFields>(t_name) {} 
  Refrigeration_TransferLoadListExtensibleFields(int t_value) 
   : EnumBase<Refrigeration_TransferLoadListExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Refrigeration_TransferLoadListExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Refrigeration_TransferLoadListExtensibleFields>::value()); }
   private:
    friend class EnumBase<Refrigeration_TransferLoadListExtensibleFields>;
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
{ Refrigeration_TransferLoadListExtensibleFields::CascadeCondenserNameorSecondarySystemName, "CascadeCondenserNameorSecondarySystemName", "Cascade Condenser Name or Secondary System Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Refrigeration_TransferLoadListExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Refrigeration_TransferLoadListExtensibleFields> OptionalRefrigeration_TransferLoadListExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_REFRIGERATION_TRANSFERLOADLIST_FIELDENUMS_HXX
