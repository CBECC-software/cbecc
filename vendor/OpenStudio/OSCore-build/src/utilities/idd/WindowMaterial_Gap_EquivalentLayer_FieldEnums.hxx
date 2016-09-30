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

#ifndef UTILITIES_IDD_WINDOWMATERIAL_GAP_EQUIVALENTLAYER_FIELDENUMS_HXX
#define UTILITIES_IDD_WINDOWMATERIAL_GAP_EQUIVALENTLAYER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WindowMaterial_Gap_EquivalentLayerFields
 *  \brief Enumeration of WindowMaterial:Gap:EquivalentLayer's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WindowMaterial_Gap_EquivalentLayerFields, )
#else
class WindowMaterial_Gap_EquivalentLayerFields: public ::EnumBase<WindowMaterial_Gap_EquivalentLayerFields> {
 public: 
  enum domain 
  {
Name, GasType, Thickness, GapVentType, ConductivityCoefficientA, ConductivityCoefficientB, ConductivityCoefficientC, ViscosityCoefficientA, ViscosityCoefficientB, ViscosityCoefficientC, SpecificHeatCoefficientA, SpecificHeatCoefficientB, SpecificHeatCoefficientC, MolecularWeight, SpecificHeatRatio,   };
  WindowMaterial_Gap_EquivalentLayerFields()
   : EnumBase<WindowMaterial_Gap_EquivalentLayerFields>(Name) {} 
  WindowMaterial_Gap_EquivalentLayerFields(const std::string &t_name) 
   : EnumBase<WindowMaterial_Gap_EquivalentLayerFields>(t_name) {} 
  WindowMaterial_Gap_EquivalentLayerFields(int t_value) 
   : EnumBase<WindowMaterial_Gap_EquivalentLayerFields>(t_value) {} 
  static std::string enumName() 
  { return "WindowMaterial_Gap_EquivalentLayerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WindowMaterial_Gap_EquivalentLayerFields>::value()); }
   private:
    friend class EnumBase<WindowMaterial_Gap_EquivalentLayerFields>;
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
{ WindowMaterial_Gap_EquivalentLayerFields::Name, "Name", "Name"},
{ WindowMaterial_Gap_EquivalentLayerFields::GasType, "GasType", "Gas Type"},
{ WindowMaterial_Gap_EquivalentLayerFields::Thickness, "Thickness", "Thickness"},
{ WindowMaterial_Gap_EquivalentLayerFields::GapVentType, "GapVentType", "Gap Vent Type"},
{ WindowMaterial_Gap_EquivalentLayerFields::ConductivityCoefficientA, "ConductivityCoefficientA", "Conductivity Coefficient A"},
{ WindowMaterial_Gap_EquivalentLayerFields::ConductivityCoefficientB, "ConductivityCoefficientB", "Conductivity Coefficient B"},
{ WindowMaterial_Gap_EquivalentLayerFields::ConductivityCoefficientC, "ConductivityCoefficientC", "Conductivity Coefficient C"},
{ WindowMaterial_Gap_EquivalentLayerFields::ViscosityCoefficientA, "ViscosityCoefficientA", "Viscosity Coefficient A"},
{ WindowMaterial_Gap_EquivalentLayerFields::ViscosityCoefficientB, "ViscosityCoefficientB", "Viscosity Coefficient B"},
{ WindowMaterial_Gap_EquivalentLayerFields::ViscosityCoefficientC, "ViscosityCoefficientC", "Viscosity Coefficient C"},
{ WindowMaterial_Gap_EquivalentLayerFields::SpecificHeatCoefficientA, "SpecificHeatCoefficientA", "Specific Heat Coefficient A"},
{ WindowMaterial_Gap_EquivalentLayerFields::SpecificHeatCoefficientB, "SpecificHeatCoefficientB", "Specific Heat Coefficient B"},
{ WindowMaterial_Gap_EquivalentLayerFields::SpecificHeatCoefficientC, "SpecificHeatCoefficientC", "Specific Heat Coefficient C"},
{ WindowMaterial_Gap_EquivalentLayerFields::MolecularWeight, "MolecularWeight", "Molecular Weight"},
{ WindowMaterial_Gap_EquivalentLayerFields::SpecificHeatRatio, "SpecificHeatRatio", "Specific Heat Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const WindowMaterial_Gap_EquivalentLayerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WindowMaterial_Gap_EquivalentLayerFields> OptionalWindowMaterial_Gap_EquivalentLayerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WINDOWMATERIAL_GAP_EQUIVALENTLAYER_FIELDENUMS_HXX
