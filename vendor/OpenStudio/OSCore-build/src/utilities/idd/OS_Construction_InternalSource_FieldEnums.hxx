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

#ifndef UTILITIES_IDD_OS_CONSTRUCTION_INTERNALSOURCE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_CONSTRUCTION_INTERNALSOURCE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Construction_InternalSourceFields
 *  \brief Enumeration of OS:Construction:InternalSource's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Construction_InternalSourceFields, )
#else
class OS_Construction_InternalSourceFields: public ::EnumBase<OS_Construction_InternalSourceFields> {
 public: 
  enum domain 
  {
Handle, Name, SourcePresentAfterLayerNumber, TemperatureCalculationRequestedAfterLayerNumber, DimensionsfortheCTFCalculation, TubeSpacing, SurfaceRenderingName,   };
  OS_Construction_InternalSourceFields()
   : EnumBase<OS_Construction_InternalSourceFields>(Handle) {} 
  OS_Construction_InternalSourceFields(const std::string &t_name) 
   : EnumBase<OS_Construction_InternalSourceFields>(t_name) {} 
  OS_Construction_InternalSourceFields(int t_value) 
   : EnumBase<OS_Construction_InternalSourceFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Construction_InternalSourceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Construction_InternalSourceFields>::value()); }
   private:
    friend class EnumBase<OS_Construction_InternalSourceFields>;
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
{ OS_Construction_InternalSourceFields::Handle, "Handle", "Handle"},
{ OS_Construction_InternalSourceFields::Name, "Name", "Name"},
{ OS_Construction_InternalSourceFields::SourcePresentAfterLayerNumber, "SourcePresentAfterLayerNumber", "Source Present After Layer Number"},
{ OS_Construction_InternalSourceFields::TemperatureCalculationRequestedAfterLayerNumber, "TemperatureCalculationRequestedAfterLayerNumber", "Temperature Calculation Requested After Layer Number"},
{ OS_Construction_InternalSourceFields::DimensionsfortheCTFCalculation, "DimensionsfortheCTFCalculation", "Dimensions for the CTF Calculation"},
{ OS_Construction_InternalSourceFields::TubeSpacing, "TubeSpacing", "Tube Spacing"},
{ OS_Construction_InternalSourceFields::SurfaceRenderingName, "SurfaceRenderingName", "Surface Rendering Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Construction_InternalSourceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Construction_InternalSourceFields> OptionalOS_Construction_InternalSourceFields ;
#endif

/** \class OS_Construction_InternalSourceExtensibleFields
 *  \brief Enumeration of OS:Construction:InternalSource's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_Construction_InternalSourceExtensibleFields, )
#else
class OS_Construction_InternalSourceExtensibleFields: public ::EnumBase<OS_Construction_InternalSourceExtensibleFields> {
 public: 
  enum domain 
  {
Layer,   };
  OS_Construction_InternalSourceExtensibleFields()
   : EnumBase<OS_Construction_InternalSourceExtensibleFields>(Layer) {} 
  OS_Construction_InternalSourceExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Construction_InternalSourceExtensibleFields>(t_name) {} 
  OS_Construction_InternalSourceExtensibleFields(int t_value) 
   : EnumBase<OS_Construction_InternalSourceExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Construction_InternalSourceExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Construction_InternalSourceExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_Construction_InternalSourceExtensibleFields>;
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
{ OS_Construction_InternalSourceExtensibleFields::Layer, "Layer", "Layer"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Construction_InternalSourceExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Construction_InternalSourceExtensibleFields> OptionalOS_Construction_InternalSourceExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_CONSTRUCTION_INTERNALSOURCE_FIELDENUMS_HXX
