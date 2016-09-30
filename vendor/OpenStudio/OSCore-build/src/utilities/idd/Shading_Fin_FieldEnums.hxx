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

#ifndef UTILITIES_IDD_SHADING_FIN_FIELDENUMS_HXX
#define UTILITIES_IDD_SHADING_FIN_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Shading_FinFields
 *  \brief Enumeration of Shading:Fin's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Shading_FinFields, )
#else
class Shading_FinFields: public ::EnumBase<Shading_FinFields> {
 public: 
  enum domain 
  {
Name, WindoworDoorName, LeftExtensionfromWindow_Door, LeftDistanceAboveTopofWindow, LeftDistanceBelowBottomofWindow, LeftTiltAnglefromWindow_Door, LeftDepth, RightExtensionfromWindow_Door, RightDistanceAboveTopofWindow, RightDistanceBelowBottomofWindow, RightTiltAnglefromWindow_Door, RightDepth,   };
  Shading_FinFields()
   : EnumBase<Shading_FinFields>(Name) {} 
  Shading_FinFields(const std::string &t_name) 
   : EnumBase<Shading_FinFields>(t_name) {} 
  Shading_FinFields(int t_value) 
   : EnumBase<Shading_FinFields>(t_value) {} 
  static std::string enumName() 
  { return "Shading_FinFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Shading_FinFields>::value()); }
   private:
    friend class EnumBase<Shading_FinFields>;
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
{ Shading_FinFields::Name, "Name", "Name"},
{ Shading_FinFields::WindoworDoorName, "WindoworDoorName", "Window or Door Name"},
{ Shading_FinFields::LeftExtensionfromWindow_Door, "LeftExtensionfromWindow_Door", "Left Extension from Window/Door"},
{ Shading_FinFields::LeftDistanceAboveTopofWindow, "LeftDistanceAboveTopofWindow", "Left Distance Above Top of Window"},
{ Shading_FinFields::LeftDistanceBelowBottomofWindow, "LeftDistanceBelowBottomofWindow", "Left Distance Below Bottom of Window"},
{ Shading_FinFields::LeftTiltAnglefromWindow_Door, "LeftTiltAnglefromWindow_Door", "Left Tilt Angle from Window/Door"},
{ Shading_FinFields::LeftDepth, "LeftDepth", "Left Depth"},
{ Shading_FinFields::RightExtensionfromWindow_Door, "RightExtensionfromWindow_Door", "Right Extension from Window/Door"},
{ Shading_FinFields::RightDistanceAboveTopofWindow, "RightDistanceAboveTopofWindow", "Right Distance Above Top of Window"},
{ Shading_FinFields::RightDistanceBelowBottomofWindow, "RightDistanceBelowBottomofWindow", "Right Distance Below Bottom of Window"},
{ Shading_FinFields::RightTiltAnglefromWindow_Door, "RightTiltAnglefromWindow_Door", "Right Tilt Angle from Window/Door"},
{ Shading_FinFields::RightDepth, "RightDepth", "Right Depth"},
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
  inline std::ostream &operator<<(std::ostream &os, const Shading_FinFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Shading_FinFields> OptionalShading_FinFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SHADING_FIN_FIELDENUMS_HXX
