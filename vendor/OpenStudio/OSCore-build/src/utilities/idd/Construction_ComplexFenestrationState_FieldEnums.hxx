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

#ifndef UTILITIES_IDD_CONSTRUCTION_COMPLEXFENESTRATIONSTATE_FIELDENUMS_HXX
#define UTILITIES_IDD_CONSTRUCTION_COMPLEXFENESTRATIONSTATE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Construction_ComplexFenestrationStateFields
 *  \brief Enumeration of Construction:ComplexFenestrationState's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Construction_ComplexFenestrationStateFields, )
#else
class Construction_ComplexFenestrationStateFields: public ::EnumBase<Construction_ComplexFenestrationStateFields> {
 public: 
  enum domain 
  {
Name, BasisType, BasisSymmetryType, WindowThermalModel, BasisMatrixName, SolarOpticalComplexFrontTransmittanceMatrixName, SolarOpticalComplexBackReflectanceMatrixName, VisibleOpticalComplexFrontTransmittanceMatrixName, VisibleOpticalComplexBackTransmittanceMatrixName,   };
  Construction_ComplexFenestrationStateFields()
   : EnumBase<Construction_ComplexFenestrationStateFields>(Name) {} 
  Construction_ComplexFenestrationStateFields(const std::string &t_name) 
   : EnumBase<Construction_ComplexFenestrationStateFields>(t_name) {} 
  Construction_ComplexFenestrationStateFields(int t_value) 
   : EnumBase<Construction_ComplexFenestrationStateFields>(t_value) {} 
  static std::string enumName() 
  { return "Construction_ComplexFenestrationStateFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Construction_ComplexFenestrationStateFields>::value()); }
   private:
    friend class EnumBase<Construction_ComplexFenestrationStateFields>;
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
{ Construction_ComplexFenestrationStateFields::Name, "Name", "Name"},
{ Construction_ComplexFenestrationStateFields::BasisType, "BasisType", "Basis Type"},
{ Construction_ComplexFenestrationStateFields::BasisSymmetryType, "BasisSymmetryType", "Basis Symmetry Type"},
{ Construction_ComplexFenestrationStateFields::WindowThermalModel, "WindowThermalModel", "Window Thermal Model"},
{ Construction_ComplexFenestrationStateFields::BasisMatrixName, "BasisMatrixName", "Basis Matrix Name"},
{ Construction_ComplexFenestrationStateFields::SolarOpticalComplexFrontTransmittanceMatrixName, "SolarOpticalComplexFrontTransmittanceMatrixName", "Solar Optical Complex Front Transmittance Matrix Name"},
{ Construction_ComplexFenestrationStateFields::SolarOpticalComplexBackReflectanceMatrixName, "SolarOpticalComplexBackReflectanceMatrixName", "Solar Optical Complex Back Reflectance Matrix Name"},
{ Construction_ComplexFenestrationStateFields::VisibleOpticalComplexFrontTransmittanceMatrixName, "VisibleOpticalComplexFrontTransmittanceMatrixName", "Visible Optical Complex Front Transmittance Matrix Name"},
{ Construction_ComplexFenestrationStateFields::VisibleOpticalComplexBackTransmittanceMatrixName, "VisibleOpticalComplexBackTransmittanceMatrixName", "Visible Optical Complex Back Transmittance Matrix Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Construction_ComplexFenestrationStateFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Construction_ComplexFenestrationStateFields> OptionalConstruction_ComplexFenestrationStateFields ;
#endif

/** \class Construction_ComplexFenestrationStateExtensibleFields
 *  \brief Enumeration of Construction:ComplexFenestrationState's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Construction_ComplexFenestrationStateExtensibleFields, )
#else
class Construction_ComplexFenestrationStateExtensibleFields: public ::EnumBase<Construction_ComplexFenestrationStateExtensibleFields> {
 public: 
  enum domain 
  {
LayerName, LayerDirectionalFrontAbsoptanceMatrixName, LayerDirectionalBackAbsoptanceMatrixName, GapName, CFSGapDirectionalFrontAbsoptanceMatrixName, CFSGapDirectionalBackAbsoptanceMatrixName,   };
  Construction_ComplexFenestrationStateExtensibleFields()
   : EnumBase<Construction_ComplexFenestrationStateExtensibleFields>(LayerName) {} 
  Construction_ComplexFenestrationStateExtensibleFields(const std::string &t_name) 
   : EnumBase<Construction_ComplexFenestrationStateExtensibleFields>(t_name) {} 
  Construction_ComplexFenestrationStateExtensibleFields(int t_value) 
   : EnumBase<Construction_ComplexFenestrationStateExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Construction_ComplexFenestrationStateExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Construction_ComplexFenestrationStateExtensibleFields>::value()); }
   private:
    friend class EnumBase<Construction_ComplexFenestrationStateExtensibleFields>;
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
{ Construction_ComplexFenestrationStateExtensibleFields::LayerName, "LayerName", "Layer Name"},
{ Construction_ComplexFenestrationStateExtensibleFields::LayerDirectionalFrontAbsoptanceMatrixName, "LayerDirectionalFrontAbsoptanceMatrixName", "Layer Directional Front Absoptance Matrix Name"},
{ Construction_ComplexFenestrationStateExtensibleFields::LayerDirectionalBackAbsoptanceMatrixName, "LayerDirectionalBackAbsoptanceMatrixName", "Layer Directional Back Absoptance Matrix Name"},
{ Construction_ComplexFenestrationStateExtensibleFields::GapName, "GapName", "Gap Name"},
{ Construction_ComplexFenestrationStateExtensibleFields::CFSGapDirectionalFrontAbsoptanceMatrixName, "CFSGapDirectionalFrontAbsoptanceMatrixName", "CFS Gap Directional Front Absoptance Matrix Name"},
{ Construction_ComplexFenestrationStateExtensibleFields::CFSGapDirectionalBackAbsoptanceMatrixName, "CFSGapDirectionalBackAbsoptanceMatrixName", "CFS Gap Directional Back Absoptance Matrix Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Construction_ComplexFenestrationStateExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Construction_ComplexFenestrationStateExtensibleFields> OptionalConstruction_ComplexFenestrationStateExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CONSTRUCTION_COMPLEXFENESTRATIONSTATE_FIELDENUMS_HXX
