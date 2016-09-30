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

#ifndef UTILITIES_IDD_SHADING_OVERHANG_PROJECTION_FIELDENUMS_HXX
#define UTILITIES_IDD_SHADING_OVERHANG_PROJECTION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Shading_Overhang_ProjectionFields
 *  \brief Enumeration of Shading:Overhang:Projection's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Shading_Overhang_ProjectionFields, )
#else
class Shading_Overhang_ProjectionFields: public ::EnumBase<Shading_Overhang_ProjectionFields> {
 public: 
  enum domain 
  {
Name, WindoworDoorName, HeightaboveWindoworDoor, TiltAnglefromWindow_Door, LeftextensionfromWindow_DoorWidth, RightextensionfromWindow_DoorWidth, DepthasFractionofWindow_DoorHeight,   };
  Shading_Overhang_ProjectionFields()
   : EnumBase<Shading_Overhang_ProjectionFields>(Name) {} 
  Shading_Overhang_ProjectionFields(const std::string &t_name) 
   : EnumBase<Shading_Overhang_ProjectionFields>(t_name) {} 
  Shading_Overhang_ProjectionFields(int t_value) 
   : EnumBase<Shading_Overhang_ProjectionFields>(t_value) {} 
  static std::string enumName() 
  { return "Shading_Overhang_ProjectionFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Shading_Overhang_ProjectionFields>::value()); }
   private:
    friend class EnumBase<Shading_Overhang_ProjectionFields>;
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
{ Shading_Overhang_ProjectionFields::Name, "Name", "Name"},
{ Shading_Overhang_ProjectionFields::WindoworDoorName, "WindoworDoorName", "Window or Door Name"},
{ Shading_Overhang_ProjectionFields::HeightaboveWindoworDoor, "HeightaboveWindoworDoor", "Height above Window or Door"},
{ Shading_Overhang_ProjectionFields::TiltAnglefromWindow_Door, "TiltAnglefromWindow_Door", "Tilt Angle from Window/Door"},
{ Shading_Overhang_ProjectionFields::LeftextensionfromWindow_DoorWidth, "LeftextensionfromWindow_DoorWidth", "Left extension from Window/Door Width"},
{ Shading_Overhang_ProjectionFields::RightextensionfromWindow_DoorWidth, "RightextensionfromWindow_DoorWidth", "Right extension from Window/Door Width"},
{ Shading_Overhang_ProjectionFields::DepthasFractionofWindow_DoorHeight, "DepthasFractionofWindow_DoorHeight", "Depth as Fraction of Window/Door Height"},
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
  inline std::ostream &operator<<(std::ostream &os, const Shading_Overhang_ProjectionFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Shading_Overhang_ProjectionFields> OptionalShading_Overhang_ProjectionFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SHADING_OVERHANG_PROJECTION_FIELDENUMS_HXX
