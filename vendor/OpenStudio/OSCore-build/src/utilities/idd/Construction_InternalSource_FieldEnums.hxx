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

#ifndef UTILITIES_IDD_CONSTRUCTION_INTERNALSOURCE_FIELDENUMS_HXX
#define UTILITIES_IDD_CONSTRUCTION_INTERNALSOURCE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Construction_InternalSourceFields
 *  \brief Enumeration of Construction:InternalSource's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Construction_InternalSourceFields, )
#else
class Construction_InternalSourceFields: public ::EnumBase<Construction_InternalSourceFields> {
 public: 
  enum domain 
  {
Name, SourcePresentAfterLayerNumber, TemperatureCalculationRequestedAfterLayerNumber, DimensionsfortheCTFCalculation, TubeSpacing,   };
  Construction_InternalSourceFields()
   : EnumBase<Construction_InternalSourceFields>(Name) {} 
  Construction_InternalSourceFields(const std::string &t_name) 
   : EnumBase<Construction_InternalSourceFields>(t_name) {} 
  Construction_InternalSourceFields(int t_value) 
   : EnumBase<Construction_InternalSourceFields>(t_value) {} 
  static std::string enumName() 
  { return "Construction_InternalSourceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Construction_InternalSourceFields>::value()); }
   private:
    friend class EnumBase<Construction_InternalSourceFields>;
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
{ Construction_InternalSourceFields::Name, "Name", "Name"},
{ Construction_InternalSourceFields::SourcePresentAfterLayerNumber, "SourcePresentAfterLayerNumber", "Source Present After Layer Number"},
{ Construction_InternalSourceFields::TemperatureCalculationRequestedAfterLayerNumber, "TemperatureCalculationRequestedAfterLayerNumber", "Temperature Calculation Requested After Layer Number"},
{ Construction_InternalSourceFields::DimensionsfortheCTFCalculation, "DimensionsfortheCTFCalculation", "Dimensions for the CTF Calculation"},
{ Construction_InternalSourceFields::TubeSpacing, "TubeSpacing", "Tube Spacing"},
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
  inline std::ostream &operator<<(std::ostream &os, const Construction_InternalSourceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Construction_InternalSourceFields> OptionalConstruction_InternalSourceFields ;
#endif

/** \class Construction_InternalSourceExtensibleFields
 *  \brief Enumeration of Construction:InternalSource's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Construction_InternalSourceExtensibleFields, )
#else
class Construction_InternalSourceExtensibleFields: public ::EnumBase<Construction_InternalSourceExtensibleFields> {
 public: 
  enum domain 
  {
Layer,   };
  Construction_InternalSourceExtensibleFields()
   : EnumBase<Construction_InternalSourceExtensibleFields>(Layer) {} 
  Construction_InternalSourceExtensibleFields(const std::string &t_name) 
   : EnumBase<Construction_InternalSourceExtensibleFields>(t_name) {} 
  Construction_InternalSourceExtensibleFields(int t_value) 
   : EnumBase<Construction_InternalSourceExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Construction_InternalSourceExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Construction_InternalSourceExtensibleFields>::value()); }
   private:
    friend class EnumBase<Construction_InternalSourceExtensibleFields>;
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
{ Construction_InternalSourceExtensibleFields::Layer, "Layer", "Layer"},
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
  inline std::ostream &operator<<(std::ostream &os, const Construction_InternalSourceExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Construction_InternalSourceExtensibleFields> OptionalConstruction_InternalSourceExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CONSTRUCTION_INTERNALSOURCE_FIELDENUMS_HXX
