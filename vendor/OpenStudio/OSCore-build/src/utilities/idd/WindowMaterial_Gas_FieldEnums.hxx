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

#ifndef UTILITIES_IDD_WINDOWMATERIAL_GAS_FIELDENUMS_HXX
#define UTILITIES_IDD_WINDOWMATERIAL_GAS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WindowMaterial_GasFields
 *  \brief Enumeration of WindowMaterial:Gas's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WindowMaterial_GasFields, )
#else
class WindowMaterial_GasFields: public ::EnumBase<WindowMaterial_GasFields> {
 public: 
  enum domain 
  {
Name, GasType, Thickness, ConductivityCoefficientA, ConductivityCoefficientB, ConductivityCoefficientC, ViscosityCoefficientA, ViscosityCoefficientB, ViscosityCoefficientC, SpecificHeatCoefficientA, SpecificHeatCoefficientB, SpecificHeatCoefficientC, MolecularWeight, SpecificHeatRatio,   };
  WindowMaterial_GasFields()
   : EnumBase<WindowMaterial_GasFields>(Name) {} 
  WindowMaterial_GasFields(const std::string &t_name) 
   : EnumBase<WindowMaterial_GasFields>(t_name) {} 
  WindowMaterial_GasFields(int t_value) 
   : EnumBase<WindowMaterial_GasFields>(t_value) {} 
  static std::string enumName() 
  { return "WindowMaterial_GasFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WindowMaterial_GasFields>::value()); }
   private:
    friend class EnumBase<WindowMaterial_GasFields>;
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
{ WindowMaterial_GasFields::Name, "Name", "Name"},
{ WindowMaterial_GasFields::GasType, "GasType", "Gas Type"},
{ WindowMaterial_GasFields::Thickness, "Thickness", "Thickness"},
{ WindowMaterial_GasFields::ConductivityCoefficientA, "ConductivityCoefficientA", "Conductivity Coefficient A"},
{ WindowMaterial_GasFields::ConductivityCoefficientB, "ConductivityCoefficientB", "Conductivity Coefficient B"},
{ WindowMaterial_GasFields::ConductivityCoefficientC, "ConductivityCoefficientC", "Conductivity Coefficient C"},
{ WindowMaterial_GasFields::ViscosityCoefficientA, "ViscosityCoefficientA", "Viscosity Coefficient A"},
{ WindowMaterial_GasFields::ViscosityCoefficientB, "ViscosityCoefficientB", "Viscosity Coefficient B"},
{ WindowMaterial_GasFields::ViscosityCoefficientC, "ViscosityCoefficientC", "Viscosity Coefficient C"},
{ WindowMaterial_GasFields::SpecificHeatCoefficientA, "SpecificHeatCoefficientA", "Specific Heat Coefficient A"},
{ WindowMaterial_GasFields::SpecificHeatCoefficientB, "SpecificHeatCoefficientB", "Specific Heat Coefficient B"},
{ WindowMaterial_GasFields::SpecificHeatCoefficientC, "SpecificHeatCoefficientC", "Specific Heat Coefficient C"},
{ WindowMaterial_GasFields::MolecularWeight, "MolecularWeight", "Molecular Weight"},
{ WindowMaterial_GasFields::SpecificHeatRatio, "SpecificHeatRatio", "Specific Heat Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const WindowMaterial_GasFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WindowMaterial_GasFields> OptionalWindowMaterial_GasFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WINDOWMATERIAL_GAS_FIELDENUMS_HXX
