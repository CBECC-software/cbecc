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

#ifndef UTILITIES_IDD_OUTPUTCONTROL_SURFACECOLORSCHEME_FIELDENUMS_HXX
#define UTILITIES_IDD_OUTPUTCONTROL_SURFACECOLORSCHEME_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OutputControl_SurfaceColorSchemeFields
 *  \brief Enumeration of OutputControl:SurfaceColorScheme's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OutputControl_SurfaceColorSchemeFields, )
#else
class OutputControl_SurfaceColorSchemeFields: public ::EnumBase<OutputControl_SurfaceColorSchemeFields> {
 public: 
  enum domain 
  {
Name,   };
  OutputControl_SurfaceColorSchemeFields()
   : EnumBase<OutputControl_SurfaceColorSchemeFields>(Name) {} 
  OutputControl_SurfaceColorSchemeFields(const std::string &t_name) 
   : EnumBase<OutputControl_SurfaceColorSchemeFields>(t_name) {} 
  OutputControl_SurfaceColorSchemeFields(int t_value) 
   : EnumBase<OutputControl_SurfaceColorSchemeFields>(t_value) {} 
  static std::string enumName() 
  { return "OutputControl_SurfaceColorSchemeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OutputControl_SurfaceColorSchemeFields>::value()); }
   private:
    friend class EnumBase<OutputControl_SurfaceColorSchemeFields>;
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
{ OutputControl_SurfaceColorSchemeFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OutputControl_SurfaceColorSchemeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OutputControl_SurfaceColorSchemeFields> OptionalOutputControl_SurfaceColorSchemeFields ;
#endif

/** \class OutputControl_SurfaceColorSchemeExtensibleFields
 *  \brief Enumeration of OutputControl:SurfaceColorScheme's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OutputControl_SurfaceColorSchemeExtensibleFields, )
#else
class OutputControl_SurfaceColorSchemeExtensibleFields: public ::EnumBase<OutputControl_SurfaceColorSchemeExtensibleFields> {
 public: 
  enum domain 
  {
DrawingElementType, ColorforDrawingElement,   };
  OutputControl_SurfaceColorSchemeExtensibleFields()
   : EnumBase<OutputControl_SurfaceColorSchemeExtensibleFields>(DrawingElementType) {} 
  OutputControl_SurfaceColorSchemeExtensibleFields(const std::string &t_name) 
   : EnumBase<OutputControl_SurfaceColorSchemeExtensibleFields>(t_name) {} 
  OutputControl_SurfaceColorSchemeExtensibleFields(int t_value) 
   : EnumBase<OutputControl_SurfaceColorSchemeExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OutputControl_SurfaceColorSchemeExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OutputControl_SurfaceColorSchemeExtensibleFields>::value()); }
   private:
    friend class EnumBase<OutputControl_SurfaceColorSchemeExtensibleFields>;
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
{ OutputControl_SurfaceColorSchemeExtensibleFields::DrawingElementType, "DrawingElementType", "Drawing Element Type"},
{ OutputControl_SurfaceColorSchemeExtensibleFields::ColorforDrawingElement, "ColorforDrawingElement", "Color for Drawing Element"},
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
  inline std::ostream &operator<<(std::ostream &os, const OutputControl_SurfaceColorSchemeExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OutputControl_SurfaceColorSchemeExtensibleFields> OptionalOutputControl_SurfaceColorSchemeExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OUTPUTCONTROL_SURFACECOLORSCHEME_FIELDENUMS_HXX
