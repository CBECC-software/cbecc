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

#ifndef UTILITIES_IDD_OS_GROUNDHEATEXCHANGER_VERTICAL_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_GROUNDHEATEXCHANGER_VERTICAL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_GroundHeatExchanger_VerticalFields
 *  \brief Enumeration of OS:GroundHeatExchanger:Vertical's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_GroundHeatExchanger_VerticalFields, )
#else
class OS_GroundHeatExchanger_VerticalFields: public ::EnumBase<OS_GroundHeatExchanger_VerticalFields> {
 public: 
  enum domain 
  {
Handle, Name, InletNodeName, OutletNodeName, MaximumFlowRate, NumberofBoreHoles, BoreHoleLength, BoreHoleRadius, GroundThermalConductivity, GroundThermalHeatCapacity, GroundTemperature, DesignFlowRate, GroutThermalConductivity, PipeThermalConductivity, PipeOutDiameter, UTubeDistance, PipeThickness, MaximumLengthofSimulation, GFunctionReferenceRatio,   };
  OS_GroundHeatExchanger_VerticalFields()
   : EnumBase<OS_GroundHeatExchanger_VerticalFields>(Handle) {} 
  OS_GroundHeatExchanger_VerticalFields(const std::string &t_name) 
   : EnumBase<OS_GroundHeatExchanger_VerticalFields>(t_name) {} 
  OS_GroundHeatExchanger_VerticalFields(int t_value) 
   : EnumBase<OS_GroundHeatExchanger_VerticalFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_GroundHeatExchanger_VerticalFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_GroundHeatExchanger_VerticalFields>::value()); }
   private:
    friend class EnumBase<OS_GroundHeatExchanger_VerticalFields>;
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
{ OS_GroundHeatExchanger_VerticalFields::Handle, "Handle", "Handle"},
{ OS_GroundHeatExchanger_VerticalFields::Name, "Name", "Name"},
{ OS_GroundHeatExchanger_VerticalFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ OS_GroundHeatExchanger_VerticalFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ OS_GroundHeatExchanger_VerticalFields::MaximumFlowRate, "MaximumFlowRate", "Maximum Flow Rate"},
{ OS_GroundHeatExchanger_VerticalFields::NumberofBoreHoles, "NumberofBoreHoles", "Number of Bore Holes"},
{ OS_GroundHeatExchanger_VerticalFields::BoreHoleLength, "BoreHoleLength", "Bore Hole Length"},
{ OS_GroundHeatExchanger_VerticalFields::BoreHoleRadius, "BoreHoleRadius", "Bore Hole Radius"},
{ OS_GroundHeatExchanger_VerticalFields::GroundThermalConductivity, "GroundThermalConductivity", "Ground Thermal Conductivity"},
{ OS_GroundHeatExchanger_VerticalFields::GroundThermalHeatCapacity, "GroundThermalHeatCapacity", "Ground Thermal Heat Capacity"},
{ OS_GroundHeatExchanger_VerticalFields::GroundTemperature, "GroundTemperature", "Ground Temperature"},
{ OS_GroundHeatExchanger_VerticalFields::DesignFlowRate, "DesignFlowRate", "Design Flow Rate"},
{ OS_GroundHeatExchanger_VerticalFields::GroutThermalConductivity, "GroutThermalConductivity", "Grout Thermal Conductivity"},
{ OS_GroundHeatExchanger_VerticalFields::PipeThermalConductivity, "PipeThermalConductivity", "Pipe Thermal Conductivity"},
{ OS_GroundHeatExchanger_VerticalFields::PipeOutDiameter, "PipeOutDiameter", "Pipe Out Diameter"},
{ OS_GroundHeatExchanger_VerticalFields::UTubeDistance, "UTubeDistance", "U-Tube Distance"},
{ OS_GroundHeatExchanger_VerticalFields::PipeThickness, "PipeThickness", "Pipe Thickness"},
{ OS_GroundHeatExchanger_VerticalFields::MaximumLengthofSimulation, "MaximumLengthofSimulation", "Maximum Length of Simulation"},
{ OS_GroundHeatExchanger_VerticalFields::GFunctionReferenceRatio, "GFunctionReferenceRatio", "G-Function Reference Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_GroundHeatExchanger_VerticalFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_GroundHeatExchanger_VerticalFields> OptionalOS_GroundHeatExchanger_VerticalFields ;
#endif

/** \class OS_GroundHeatExchanger_VerticalExtensibleFields
 *  \brief Enumeration of OS:GroundHeatExchanger:Vertical's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_GroundHeatExchanger_VerticalExtensibleFields, )
#else
class OS_GroundHeatExchanger_VerticalExtensibleFields: public ::EnumBase<OS_GroundHeatExchanger_VerticalExtensibleFields> {
 public: 
  enum domain 
  {
GFunctionLn_T_Ts_Value, GFunctionGValue,   };
  OS_GroundHeatExchanger_VerticalExtensibleFields()
   : EnumBase<OS_GroundHeatExchanger_VerticalExtensibleFields>(GFunctionLn_T_Ts_Value) {} 
  OS_GroundHeatExchanger_VerticalExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_GroundHeatExchanger_VerticalExtensibleFields>(t_name) {} 
  OS_GroundHeatExchanger_VerticalExtensibleFields(int t_value) 
   : EnumBase<OS_GroundHeatExchanger_VerticalExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_GroundHeatExchanger_VerticalExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_GroundHeatExchanger_VerticalExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_GroundHeatExchanger_VerticalExtensibleFields>;
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
{ OS_GroundHeatExchanger_VerticalExtensibleFields::GFunctionLn_T_Ts_Value, "GFunctionLn_T_Ts_Value", "G-Function Ln(T/Ts) Value"},
{ OS_GroundHeatExchanger_VerticalExtensibleFields::GFunctionGValue, "GFunctionGValue", "G-Function G Value"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_GroundHeatExchanger_VerticalExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_GroundHeatExchanger_VerticalExtensibleFields> OptionalOS_GroundHeatExchanger_VerticalExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_GROUNDHEATEXCHANGER_VERTICAL_FIELDENUMS_HXX
