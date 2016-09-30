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

#ifndef UTILITIES_IDD_WINDOWPROPERTY_STORMWINDOW_FIELDENUMS_HXX
#define UTILITIES_IDD_WINDOWPROPERTY_STORMWINDOW_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WindowProperty_StormWindowFields
 *  \brief Enumeration of WindowProperty:StormWindow's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WindowProperty_StormWindowFields, )
#else
class WindowProperty_StormWindowFields: public ::EnumBase<WindowProperty_StormWindowFields> {
 public: 
  enum domain 
  {
WindowName, StormGlassLayerName, DistanceBetweenStormGlassLayerandAdjacentGlass, MonththatStormGlassLayerisPutOn, DayofMonththatStormGlassLayerisPutOn, MonththatStormGlassLayerisTakenOff, DayofMonththatStormGlassLayerisTakenOff,   };
  WindowProperty_StormWindowFields()
   : EnumBase<WindowProperty_StormWindowFields>(WindowName) {} 
  WindowProperty_StormWindowFields(const std::string &t_name) 
   : EnumBase<WindowProperty_StormWindowFields>(t_name) {} 
  WindowProperty_StormWindowFields(int t_value) 
   : EnumBase<WindowProperty_StormWindowFields>(t_value) {} 
  static std::string enumName() 
  { return "WindowProperty_StormWindowFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WindowProperty_StormWindowFields>::value()); }
   private:
    friend class EnumBase<WindowProperty_StormWindowFields>;
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
{ WindowProperty_StormWindowFields::WindowName, "WindowName", "Window Name"},
{ WindowProperty_StormWindowFields::StormGlassLayerName, "StormGlassLayerName", "Storm Glass Layer Name"},
{ WindowProperty_StormWindowFields::DistanceBetweenStormGlassLayerandAdjacentGlass, "DistanceBetweenStormGlassLayerandAdjacentGlass", "Distance Between Storm Glass Layer and Adjacent Glass"},
{ WindowProperty_StormWindowFields::MonththatStormGlassLayerisPutOn, "MonththatStormGlassLayerisPutOn", "Month that Storm Glass Layer is Put On"},
{ WindowProperty_StormWindowFields::DayofMonththatStormGlassLayerisPutOn, "DayofMonththatStormGlassLayerisPutOn", "Day of Month that Storm Glass Layer is Put On"},
{ WindowProperty_StormWindowFields::MonththatStormGlassLayerisTakenOff, "MonththatStormGlassLayerisTakenOff", "Month that Storm Glass Layer is Taken Off"},
{ WindowProperty_StormWindowFields::DayofMonththatStormGlassLayerisTakenOff, "DayofMonththatStormGlassLayerisTakenOff", "Day of Month that Storm Glass Layer is Taken Off"},
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
  inline std::ostream &operator<<(std::ostream &os, const WindowProperty_StormWindowFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WindowProperty_StormWindowFields> OptionalWindowProperty_StormWindowFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WINDOWPROPERTY_STORMWINDOW_FIELDENUMS_HXX
