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

#ifndef UTILITIES_IDD_AIRLOOPHVAC_RETURNPLENUM_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRLOOPHVAC_RETURNPLENUM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirLoopHVAC_ReturnPlenumFields
 *  \brief Enumeration of AirLoopHVAC:ReturnPlenum's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirLoopHVAC_ReturnPlenumFields, )
#else
class AirLoopHVAC_ReturnPlenumFields: public ::EnumBase<AirLoopHVAC_ReturnPlenumFields> {
 public: 
  enum domain 
  {
Name, ZoneName, ZoneNodeName, OutletNodeName, InducedAirOutletNodeorNodeListName,   };
  AirLoopHVAC_ReturnPlenumFields()
   : EnumBase<AirLoopHVAC_ReturnPlenumFields>(Name) {} 
  AirLoopHVAC_ReturnPlenumFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_ReturnPlenumFields>(t_name) {} 
  AirLoopHVAC_ReturnPlenumFields(int t_value) 
   : EnumBase<AirLoopHVAC_ReturnPlenumFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_ReturnPlenumFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_ReturnPlenumFields>::value()); }
   private:
    friend class EnumBase<AirLoopHVAC_ReturnPlenumFields>;
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
{ AirLoopHVAC_ReturnPlenumFields::Name, "Name", "Name"},
{ AirLoopHVAC_ReturnPlenumFields::ZoneName, "ZoneName", "Zone Name"},
{ AirLoopHVAC_ReturnPlenumFields::ZoneNodeName, "ZoneNodeName", "Zone Node Name"},
{ AirLoopHVAC_ReturnPlenumFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ AirLoopHVAC_ReturnPlenumFields::InducedAirOutletNodeorNodeListName, "InducedAirOutletNodeorNodeListName", "Induced Air Outlet Node or NodeList Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_ReturnPlenumFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_ReturnPlenumFields> OptionalAirLoopHVAC_ReturnPlenumFields ;
#endif

/** \class AirLoopHVAC_ReturnPlenumExtensibleFields
 *  \brief Enumeration of AirLoopHVAC:ReturnPlenum's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(AirLoopHVAC_ReturnPlenumExtensibleFields, )
#else
class AirLoopHVAC_ReturnPlenumExtensibleFields: public ::EnumBase<AirLoopHVAC_ReturnPlenumExtensibleFields> {
 public: 
  enum domain 
  {
InletNodeName,   };
  AirLoopHVAC_ReturnPlenumExtensibleFields()
   : EnumBase<AirLoopHVAC_ReturnPlenumExtensibleFields>(InletNodeName) {} 
  AirLoopHVAC_ReturnPlenumExtensibleFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_ReturnPlenumExtensibleFields>(t_name) {} 
  AirLoopHVAC_ReturnPlenumExtensibleFields(int t_value) 
   : EnumBase<AirLoopHVAC_ReturnPlenumExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_ReturnPlenumExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_ReturnPlenumExtensibleFields>::value()); }
   private:
    friend class EnumBase<AirLoopHVAC_ReturnPlenumExtensibleFields>;
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
{ AirLoopHVAC_ReturnPlenumExtensibleFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_ReturnPlenumExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_ReturnPlenumExtensibleFields> OptionalAirLoopHVAC_ReturnPlenumExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRLOOPHVAC_RETURNPLENUM_FIELDENUMS_HXX
