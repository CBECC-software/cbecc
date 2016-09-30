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

#ifndef UTILITIES_IDD_ZONE_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneFields
 *  \brief Enumeration of Zone's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneFields, )
#else
class ZoneFields: public ::EnumBase<ZoneFields> {
 public: 
  enum domain 
  {
Name, DirectionofRelativeNorth, XOrigin, YOrigin, ZOrigin, Type, Multiplier, CeilingHeight, Volume, FloorArea, ZoneInsideConvectionAlgorithm, ZoneOutsideConvectionAlgorithm, PartofTotalFloorArea,   };
  ZoneFields()
   : EnumBase<ZoneFields>(Name) {} 
  ZoneFields(const std::string &t_name) 
   : EnumBase<ZoneFields>(t_name) {} 
  ZoneFields(int t_value) 
   : EnumBase<ZoneFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneFields>::value()); }
   private:
    friend class EnumBase<ZoneFields>;
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
{ ZoneFields::Name, "Name", "Name"},
{ ZoneFields::DirectionofRelativeNorth, "DirectionofRelativeNorth", "Direction of Relative North"},
{ ZoneFields::XOrigin, "XOrigin", "X Origin"},
{ ZoneFields::YOrigin, "YOrigin", "Y Origin"},
{ ZoneFields::ZOrigin, "ZOrigin", "Z Origin"},
{ ZoneFields::Type, "Type", "Type"},
{ ZoneFields::Multiplier, "Multiplier", "Multiplier"},
{ ZoneFields::CeilingHeight, "CeilingHeight", "Ceiling Height"},
{ ZoneFields::Volume, "Volume", "Volume"},
{ ZoneFields::FloorArea, "FloorArea", "Floor Area"},
{ ZoneFields::ZoneInsideConvectionAlgorithm, "ZoneInsideConvectionAlgorithm", "Zone Inside Convection Algorithm"},
{ ZoneFields::ZoneOutsideConvectionAlgorithm, "ZoneOutsideConvectionAlgorithm", "Zone Outside Convection Algorithm"},
{ ZoneFields::PartofTotalFloorArea, "PartofTotalFloorArea", "Part of Total Floor Area"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneFields> OptionalZoneFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONE_FIELDENUMS_HXX
