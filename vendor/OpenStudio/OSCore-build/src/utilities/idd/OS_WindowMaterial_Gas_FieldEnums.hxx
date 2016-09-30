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

#ifndef UTILITIES_IDD_OS_WINDOWMATERIAL_GAS_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_WINDOWMATERIAL_GAS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_WindowMaterial_GasFields
 *  \brief Enumeration of OS:WindowMaterial:Gas's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_WindowMaterial_GasFields, )
#else
class OS_WindowMaterial_GasFields: public ::EnumBase<OS_WindowMaterial_GasFields> {
 public: 
  enum domain 
  {
Handle, Name, GasType, Thickness, ConductivityCoefficientA, ConductivityCoefficientB, ConductivityCoefficientC, ViscosityCoefficientA, ViscosityCoefficientB, ViscosityCoefficientC, SpecificHeatCoefficientA, SpecificHeatCoefficientB, SpecificHeatCoefficientC, MolecularWeight, SpecificHeatRatio,   };
  OS_WindowMaterial_GasFields()
   : EnumBase<OS_WindowMaterial_GasFields>(Handle) {} 
  OS_WindowMaterial_GasFields(const std::string &t_name) 
   : EnumBase<OS_WindowMaterial_GasFields>(t_name) {} 
  OS_WindowMaterial_GasFields(int t_value) 
   : EnumBase<OS_WindowMaterial_GasFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_WindowMaterial_GasFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_WindowMaterial_GasFields>::value()); }
   private:
    friend class EnumBase<OS_WindowMaterial_GasFields>;
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
{ OS_WindowMaterial_GasFields::Handle, "Handle", "Handle"},
{ OS_WindowMaterial_GasFields::Name, "Name", "Name"},
{ OS_WindowMaterial_GasFields::GasType, "GasType", "Gas Type"},
{ OS_WindowMaterial_GasFields::Thickness, "Thickness", "Thickness"},
{ OS_WindowMaterial_GasFields::ConductivityCoefficientA, "ConductivityCoefficientA", "Conductivity Coefficient A"},
{ OS_WindowMaterial_GasFields::ConductivityCoefficientB, "ConductivityCoefficientB", "Conductivity Coefficient B"},
{ OS_WindowMaterial_GasFields::ConductivityCoefficientC, "ConductivityCoefficientC", "Conductivity Coefficient C"},
{ OS_WindowMaterial_GasFields::ViscosityCoefficientA, "ViscosityCoefficientA", "Viscosity Coefficient A"},
{ OS_WindowMaterial_GasFields::ViscosityCoefficientB, "ViscosityCoefficientB", "Viscosity Coefficient B"},
{ OS_WindowMaterial_GasFields::ViscosityCoefficientC, "ViscosityCoefficientC", "Viscosity Coefficient C"},
{ OS_WindowMaterial_GasFields::SpecificHeatCoefficientA, "SpecificHeatCoefficientA", "Specific Heat Coefficient A"},
{ OS_WindowMaterial_GasFields::SpecificHeatCoefficientB, "SpecificHeatCoefficientB", "Specific Heat Coefficient B"},
{ OS_WindowMaterial_GasFields::SpecificHeatCoefficientC, "SpecificHeatCoefficientC", "Specific Heat Coefficient C"},
{ OS_WindowMaterial_GasFields::MolecularWeight, "MolecularWeight", "Molecular Weight"},
{ OS_WindowMaterial_GasFields::SpecificHeatRatio, "SpecificHeatRatio", "Specific Heat Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_WindowMaterial_GasFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_WindowMaterial_GasFields> OptionalOS_WindowMaterial_GasFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_WINDOWMATERIAL_GAS_FIELDENUMS_HXX
