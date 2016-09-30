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

#ifndef UTILITIES_IDD_FLOOR_ADIABATIC_FIELDENUMS_HXX
#define UTILITIES_IDD_FLOOR_ADIABATIC_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Floor_AdiabaticFields
 *  \brief Enumeration of Floor:Adiabatic's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Floor_AdiabaticFields, )
#else
class Floor_AdiabaticFields: public ::EnumBase<Floor_AdiabaticFields> {
 public: 
  enum domain 
  {
Name, ConstructionName, ZoneName, AzimuthAngle, TiltAngle, StartingXCoordinate, StartingYCoordinate, StartingZCoordinate, Length, Width,   };
  Floor_AdiabaticFields()
   : EnumBase<Floor_AdiabaticFields>(Name) {} 
  Floor_AdiabaticFields(const std::string &t_name) 
   : EnumBase<Floor_AdiabaticFields>(t_name) {} 
  Floor_AdiabaticFields(int t_value) 
   : EnumBase<Floor_AdiabaticFields>(t_value) {} 
  static std::string enumName() 
  { return "Floor_AdiabaticFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Floor_AdiabaticFields>::value()); }
   private:
    friend class EnumBase<Floor_AdiabaticFields>;
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
{ Floor_AdiabaticFields::Name, "Name", "Name"},
{ Floor_AdiabaticFields::ConstructionName, "ConstructionName", "Construction Name"},
{ Floor_AdiabaticFields::ZoneName, "ZoneName", "Zone Name"},
{ Floor_AdiabaticFields::AzimuthAngle, "AzimuthAngle", "Azimuth Angle"},
{ Floor_AdiabaticFields::TiltAngle, "TiltAngle", "Tilt Angle"},
{ Floor_AdiabaticFields::StartingXCoordinate, "StartingXCoordinate", "Starting X Coordinate"},
{ Floor_AdiabaticFields::StartingYCoordinate, "StartingYCoordinate", "Starting Y Coordinate"},
{ Floor_AdiabaticFields::StartingZCoordinate, "StartingZCoordinate", "Starting Z Coordinate"},
{ Floor_AdiabaticFields::Length, "Length", "Length"},
{ Floor_AdiabaticFields::Width, "Width", "Width"},
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
  inline std::ostream &operator<<(std::ostream &os, const Floor_AdiabaticFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Floor_AdiabaticFields> OptionalFloor_AdiabaticFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FLOOR_ADIABATIC_FIELDENUMS_HXX
