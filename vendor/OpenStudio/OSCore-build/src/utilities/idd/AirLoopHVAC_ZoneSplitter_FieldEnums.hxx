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

#ifndef UTILITIES_IDD_AIRLOOPHVAC_ZONESPLITTER_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRLOOPHVAC_ZONESPLITTER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirLoopHVAC_ZoneSplitterFields
 *  \brief Enumeration of AirLoopHVAC:ZoneSplitter's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirLoopHVAC_ZoneSplitterFields, )
#else
class AirLoopHVAC_ZoneSplitterFields: public ::EnumBase<AirLoopHVAC_ZoneSplitterFields> {
 public: 
  enum domain 
  {
Name, InletNodeName,   };
  AirLoopHVAC_ZoneSplitterFields()
   : EnumBase<AirLoopHVAC_ZoneSplitterFields>(Name) {} 
  AirLoopHVAC_ZoneSplitterFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_ZoneSplitterFields>(t_name) {} 
  AirLoopHVAC_ZoneSplitterFields(int t_value) 
   : EnumBase<AirLoopHVAC_ZoneSplitterFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_ZoneSplitterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_ZoneSplitterFields>::value()); }
   private:
    friend class EnumBase<AirLoopHVAC_ZoneSplitterFields>;
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
{ AirLoopHVAC_ZoneSplitterFields::Name, "Name", "Name"},
{ AirLoopHVAC_ZoneSplitterFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_ZoneSplitterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_ZoneSplitterFields> OptionalAirLoopHVAC_ZoneSplitterFields ;
#endif

/** \class AirLoopHVAC_ZoneSplitterExtensibleFields
 *  \brief Enumeration of AirLoopHVAC:ZoneSplitter's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(AirLoopHVAC_ZoneSplitterExtensibleFields, )
#else
class AirLoopHVAC_ZoneSplitterExtensibleFields: public ::EnumBase<AirLoopHVAC_ZoneSplitterExtensibleFields> {
 public: 
  enum domain 
  {
OutletNodeName,   };
  AirLoopHVAC_ZoneSplitterExtensibleFields()
   : EnumBase<AirLoopHVAC_ZoneSplitterExtensibleFields>(OutletNodeName) {} 
  AirLoopHVAC_ZoneSplitterExtensibleFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_ZoneSplitterExtensibleFields>(t_name) {} 
  AirLoopHVAC_ZoneSplitterExtensibleFields(int t_value) 
   : EnumBase<AirLoopHVAC_ZoneSplitterExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_ZoneSplitterExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_ZoneSplitterExtensibleFields>::value()); }
   private:
    friend class EnumBase<AirLoopHVAC_ZoneSplitterExtensibleFields>;
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
{ AirLoopHVAC_ZoneSplitterExtensibleFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_ZoneSplitterExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_ZoneSplitterExtensibleFields> OptionalAirLoopHVAC_ZoneSplitterExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRLOOPHVAC_ZONESPLITTER_FIELDENUMS_HXX
