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

#ifndef UTILITIES_IDD_SHADING_OVERHANG_FIELDENUMS_HXX
#define UTILITIES_IDD_SHADING_OVERHANG_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Shading_OverhangFields
 *  \brief Enumeration of Shading:Overhang's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Shading_OverhangFields, )
#else
class Shading_OverhangFields: public ::EnumBase<Shading_OverhangFields> {
 public: 
  enum domain 
  {
Name, WindoworDoorName, HeightaboveWindoworDoor, TiltAnglefromWindow_Door, LeftextensionfromWindow_DoorWidth, RightextensionfromWindow_DoorWidth, Depth,   };
  Shading_OverhangFields()
   : EnumBase<Shading_OverhangFields>(Name) {} 
  Shading_OverhangFields(const std::string &t_name) 
   : EnumBase<Shading_OverhangFields>(t_name) {} 
  Shading_OverhangFields(int t_value) 
   : EnumBase<Shading_OverhangFields>(t_value) {} 
  static std::string enumName() 
  { return "Shading_OverhangFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Shading_OverhangFields>::value()); }
   private:
    friend class EnumBase<Shading_OverhangFields>;
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
{ Shading_OverhangFields::Name, "Name", "Name"},
{ Shading_OverhangFields::WindoworDoorName, "WindoworDoorName", "Window or Door Name"},
{ Shading_OverhangFields::HeightaboveWindoworDoor, "HeightaboveWindoworDoor", "Height above Window or Door"},
{ Shading_OverhangFields::TiltAnglefromWindow_Door, "TiltAnglefromWindow_Door", "Tilt Angle from Window/Door"},
{ Shading_OverhangFields::LeftextensionfromWindow_DoorWidth, "LeftextensionfromWindow_DoorWidth", "Left extension from Window/Door Width"},
{ Shading_OverhangFields::RightextensionfromWindow_DoorWidth, "RightextensionfromWindow_DoorWidth", "Right extension from Window/Door Width"},
{ Shading_OverhangFields::Depth, "Depth", "Depth"},
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
  inline std::ostream &operator<<(std::ostream &os, const Shading_OverhangFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Shading_OverhangFields> OptionalShading_OverhangFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SHADING_OVERHANG_FIELDENUMS_HXX
