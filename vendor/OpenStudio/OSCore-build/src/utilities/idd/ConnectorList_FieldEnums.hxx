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

#ifndef UTILITIES_IDD_CONNECTORLIST_FIELDENUMS_HXX
#define UTILITIES_IDD_CONNECTORLIST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ConnectorListFields
 *  \brief Enumeration of ConnectorList's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ConnectorListFields, )
#else
class ConnectorListFields: public ::EnumBase<ConnectorListFields> {
 public: 
  enum domain 
  {
Name,   };
  ConnectorListFields()
   : EnumBase<ConnectorListFields>(Name) {} 
  ConnectorListFields(const std::string &t_name) 
   : EnumBase<ConnectorListFields>(t_name) {} 
  ConnectorListFields(int t_value) 
   : EnumBase<ConnectorListFields>(t_value) {} 
  static std::string enumName() 
  { return "ConnectorListFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ConnectorListFields>::value()); }
   private:
    friend class EnumBase<ConnectorListFields>;
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
{ ConnectorListFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ConnectorListFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ConnectorListFields> OptionalConnectorListFields ;
#endif

/** \class ConnectorListExtensibleFields
 *  \brief Enumeration of ConnectorList's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(ConnectorListExtensibleFields, )
#else
class ConnectorListExtensibleFields: public ::EnumBase<ConnectorListExtensibleFields> {
 public: 
  enum domain 
  {
ConnectorObjectType, ConnectorName,   };
  ConnectorListExtensibleFields()
   : EnumBase<ConnectorListExtensibleFields>(ConnectorObjectType) {} 
  ConnectorListExtensibleFields(const std::string &t_name) 
   : EnumBase<ConnectorListExtensibleFields>(t_name) {} 
  ConnectorListExtensibleFields(int t_value) 
   : EnumBase<ConnectorListExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "ConnectorListExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ConnectorListExtensibleFields>::value()); }
   private:
    friend class EnumBase<ConnectorListExtensibleFields>;
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
{ ConnectorListExtensibleFields::ConnectorObjectType, "ConnectorObjectType", "Connector Object Type"},
{ ConnectorListExtensibleFields::ConnectorName, "ConnectorName", "Connector Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ConnectorListExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ConnectorListExtensibleFields> OptionalConnectorListExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CONNECTORLIST_FIELDENUMS_HXX
