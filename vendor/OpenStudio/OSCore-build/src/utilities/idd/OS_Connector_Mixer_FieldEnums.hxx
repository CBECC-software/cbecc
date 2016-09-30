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

#ifndef UTILITIES_IDD_OS_CONNECTOR_MIXER_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_CONNECTOR_MIXER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Connector_MixerFields
 *  \brief Enumeration of OS:Connector:Mixer's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Connector_MixerFields, )
#else
class OS_Connector_MixerFields: public ::EnumBase<OS_Connector_MixerFields> {
 public: 
  enum domain 
  {
Handle, Name, OutletBranchName,   };
  OS_Connector_MixerFields()
   : EnumBase<OS_Connector_MixerFields>(Handle) {} 
  OS_Connector_MixerFields(const std::string &t_name) 
   : EnumBase<OS_Connector_MixerFields>(t_name) {} 
  OS_Connector_MixerFields(int t_value) 
   : EnumBase<OS_Connector_MixerFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Connector_MixerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Connector_MixerFields>::value()); }
   private:
    friend class EnumBase<OS_Connector_MixerFields>;
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
{ OS_Connector_MixerFields::Handle, "Handle", "Handle"},
{ OS_Connector_MixerFields::Name, "Name", "Name"},
{ OS_Connector_MixerFields::OutletBranchName, "OutletBranchName", "Outlet Branch Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Connector_MixerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Connector_MixerFields> OptionalOS_Connector_MixerFields ;
#endif

/** \class OS_Connector_MixerExtensibleFields
 *  \brief Enumeration of OS:Connector:Mixer's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_Connector_MixerExtensibleFields, )
#else
class OS_Connector_MixerExtensibleFields: public ::EnumBase<OS_Connector_MixerExtensibleFields> {
 public: 
  enum domain 
  {
InletBranchName,   };
  OS_Connector_MixerExtensibleFields()
   : EnumBase<OS_Connector_MixerExtensibleFields>(InletBranchName) {} 
  OS_Connector_MixerExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Connector_MixerExtensibleFields>(t_name) {} 
  OS_Connector_MixerExtensibleFields(int t_value) 
   : EnumBase<OS_Connector_MixerExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Connector_MixerExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Connector_MixerExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_Connector_MixerExtensibleFields>;
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
{ OS_Connector_MixerExtensibleFields::InletBranchName, "InletBranchName", "Inlet Branch Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Connector_MixerExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Connector_MixerExtensibleFields> OptionalOS_Connector_MixerExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_CONNECTOR_MIXER_FIELDENUMS_HXX
