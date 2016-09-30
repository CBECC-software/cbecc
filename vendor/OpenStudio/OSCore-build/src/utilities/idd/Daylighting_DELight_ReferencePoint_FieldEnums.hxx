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

#ifndef UTILITIES_IDD_DAYLIGHTING_DELIGHT_REFERENCEPOINT_FIELDENUMS_HXX
#define UTILITIES_IDD_DAYLIGHTING_DELIGHT_REFERENCEPOINT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Daylighting_DELight_ReferencePointFields
 *  \brief Enumeration of Daylighting:DELight:ReferencePoint's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Daylighting_DELight_ReferencePointFields, )
#else
class Daylighting_DELight_ReferencePointFields: public ::EnumBase<Daylighting_DELight_ReferencePointFields> {
 public: 
  enum domain 
  {
Name, DElightName, XcoordinateofReferencePoint, YcoordinateofReferencePoint, ZcoordinateofReferencePoint, FractionofZoneControlledbyReferencePoint, IlluminanceSetpointatReferencePoint,   };
  Daylighting_DELight_ReferencePointFields()
   : EnumBase<Daylighting_DELight_ReferencePointFields>(Name) {} 
  Daylighting_DELight_ReferencePointFields(const std::string &t_name) 
   : EnumBase<Daylighting_DELight_ReferencePointFields>(t_name) {} 
  Daylighting_DELight_ReferencePointFields(int t_value) 
   : EnumBase<Daylighting_DELight_ReferencePointFields>(t_value) {} 
  static std::string enumName() 
  { return "Daylighting_DELight_ReferencePointFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Daylighting_DELight_ReferencePointFields>::value()); }
   private:
    friend class EnumBase<Daylighting_DELight_ReferencePointFields>;
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
{ Daylighting_DELight_ReferencePointFields::Name, "Name", "Name"},
{ Daylighting_DELight_ReferencePointFields::DElightName, "DElightName", "DElight Name"},
{ Daylighting_DELight_ReferencePointFields::XcoordinateofReferencePoint, "XcoordinateofReferencePoint", "X-coordinate of Reference Point"},
{ Daylighting_DELight_ReferencePointFields::YcoordinateofReferencePoint, "YcoordinateofReferencePoint", "Y-coordinate of Reference Point"},
{ Daylighting_DELight_ReferencePointFields::ZcoordinateofReferencePoint, "ZcoordinateofReferencePoint", "Z-coordinate of Reference Point"},
{ Daylighting_DELight_ReferencePointFields::FractionofZoneControlledbyReferencePoint, "FractionofZoneControlledbyReferencePoint", "Fraction of Zone Controlled by Reference Point"},
{ Daylighting_DELight_ReferencePointFields::IlluminanceSetpointatReferencePoint, "IlluminanceSetpointatReferencePoint", "Illuminance Setpoint at Reference Point"},
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
  inline std::ostream &operator<<(std::ostream &os, const Daylighting_DELight_ReferencePointFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Daylighting_DELight_ReferencePointFields> OptionalDaylighting_DELight_ReferencePointFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_DAYLIGHTING_DELIGHT_REFERENCEPOINT_FIELDENUMS_HXX
