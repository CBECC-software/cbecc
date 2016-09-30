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

#ifndef UTILITIES_IDD_ROOF_FIELDENUMS_HXX
#define UTILITIES_IDD_ROOF_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class RoofFields
 *  \brief Enumeration of Roof's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(RoofFields, )
#else
class RoofFields: public ::EnumBase<RoofFields> {
 public: 
  enum domain 
  {
Name, ConstructionName, ZoneName, AzimuthAngle, TiltAngle, StartingXCoordinate, StartingYCoordinate, StartingZCoordinate, Length, Width,   };
  RoofFields()
   : EnumBase<RoofFields>(Name) {} 
  RoofFields(const std::string &t_name) 
   : EnumBase<RoofFields>(t_name) {} 
  RoofFields(int t_value) 
   : EnumBase<RoofFields>(t_value) {} 
  static std::string enumName() 
  { return "RoofFields"; }
  domain value() const { return static_cast<domain>(EnumBase<RoofFields>::value()); }
   private:
    friend class EnumBase<RoofFields>;
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
{ RoofFields::Name, "Name", "Name"},
{ RoofFields::ConstructionName, "ConstructionName", "Construction Name"},
{ RoofFields::ZoneName, "ZoneName", "Zone Name"},
{ RoofFields::AzimuthAngle, "AzimuthAngle", "Azimuth Angle"},
{ RoofFields::TiltAngle, "TiltAngle", "Tilt Angle"},
{ RoofFields::StartingXCoordinate, "StartingXCoordinate", "Starting X Coordinate"},
{ RoofFields::StartingYCoordinate, "StartingYCoordinate", "Starting Y Coordinate"},
{ RoofFields::StartingZCoordinate, "StartingZCoordinate", "Starting Z Coordinate"},
{ RoofFields::Length, "Length", "Length"},
{ RoofFields::Width, "Width", "Width"},
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
  inline std::ostream &operator<<(std::ostream &os, const RoofFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<RoofFields> OptionalRoofFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ROOF_FIELDENUMS_HXX
