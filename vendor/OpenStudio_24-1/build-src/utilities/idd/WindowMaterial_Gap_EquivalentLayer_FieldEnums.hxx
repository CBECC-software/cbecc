/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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
