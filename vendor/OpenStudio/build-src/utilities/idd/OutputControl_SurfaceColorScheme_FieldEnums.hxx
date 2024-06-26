/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

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
