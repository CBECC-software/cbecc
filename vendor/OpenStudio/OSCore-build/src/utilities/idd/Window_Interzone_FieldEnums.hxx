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

#ifndef UTILITIES_IDD_WINDOW_INTERZONE_FIELDENUMS_HXX
#define UTILITIES_IDD_WINDOW_INTERZONE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Window_InterzoneFields
 *  \brief Enumeration of Window:Interzone's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Window_InterzoneFields, )
#else
class Window_InterzoneFields: public ::EnumBase<Window_InterzoneFields> {
 public: 
  enum domain 
  {
Name, ConstructionName, BuildingSurfaceName, OutsideBoundaryConditionObject, Multiplier, StartingXCoordinate, StartingZCoordinate, Length, Height,   };
  Window_InterzoneFields()
   : EnumBase<Window_InterzoneFields>(Name) {} 
  Window_InterzoneFields(const std::string &t_name) 
   : EnumBase<Window_InterzoneFields>(t_name) {} 
  Window_InterzoneFields(int t_value) 
   : EnumBase<Window_InterzoneFields>(t_value) {} 
  static std::string enumName() 
  { return "Window_InterzoneFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Window_InterzoneFields>::value()); }
   private:
    friend class EnumBase<Window_InterzoneFields>;
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
{ Window_InterzoneFields::Name, "Name", "Name"},
{ Window_InterzoneFields::ConstructionName, "ConstructionName", "Construction Name"},
{ Window_InterzoneFields::BuildingSurfaceName, "BuildingSurfaceName", "Building Surface Name"},
{ Window_InterzoneFields::OutsideBoundaryConditionObject, "OutsideBoundaryConditionObject", "Outside Boundary Condition Object"},
{ Window_InterzoneFields::Multiplier, "Multiplier", "Multiplier"},
{ Window_InterzoneFields::StartingXCoordinate, "StartingXCoordinate", "Starting X Coordinate"},
{ Window_InterzoneFields::StartingZCoordinate, "StartingZCoordinate", "Starting Z Coordinate"},
{ Window_InterzoneFields::Length, "Length", "Length"},
{ Window_InterzoneFields::Height, "Height", "Height"},
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
  inline std::ostream &operator<<(std::ostream &os, const Window_InterzoneFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Window_InterzoneFields> OptionalWindow_InterzoneFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WINDOW_INTERZONE_FIELDENUMS_HXX
