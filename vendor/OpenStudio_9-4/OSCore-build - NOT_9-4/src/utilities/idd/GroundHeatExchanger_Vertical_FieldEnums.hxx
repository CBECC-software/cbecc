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

#ifndef UTILITIES_IDD_GROUNDHEATEXCHANGER_VERTICAL_FIELDENUMS_HXX
#define UTILITIES_IDD_GROUNDHEATEXCHANGER_VERTICAL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class GroundHeatExchanger_VerticalFields
 *  \brief Enumeration of GroundHeatExchanger:Vertical's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(GroundHeatExchanger_VerticalFields, )
#else
class GroundHeatExchanger_VerticalFields: public ::EnumBase<GroundHeatExchanger_VerticalFields> {
 public: 
  enum domain 
  {
Name, InletNodeName, OutletNodeName, DesignFlowRate, NumberofBoreHoles, BoreHoleLength, BoreHoleRadius, GroundThermalConductivity, GroundThermalHeatCapacity, GroundTemperature, GroutThermalConductivity, PipeThermalConductivity, PipeOutDiameter, UTubeDistance, PipeThickness, MaximumLengthofSimulation, GFunctionReferenceRatio, NumberofDataPairsoftheGFunction,   };
  GroundHeatExchanger_VerticalFields()
   : EnumBase<GroundHeatExchanger_VerticalFields>(Name) {} 
  GroundHeatExchanger_VerticalFields(const std::string &t_name) 
   : EnumBase<GroundHeatExchanger_VerticalFields>(t_name) {} 
  GroundHeatExchanger_VerticalFields(int t_value) 
   : EnumBase<GroundHeatExchanger_VerticalFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatExchanger_VerticalFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatExchanger_VerticalFields>::value()); }
   private:
    friend class EnumBase<GroundHeatExchanger_VerticalFields>;
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
{ GroundHeatExchanger_VerticalFields::Name, "Name", "Name"},
{ GroundHeatExchanger_VerticalFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ GroundHeatExchanger_VerticalFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ GroundHeatExchanger_VerticalFields::DesignFlowRate, "DesignFlowRate", "Design Flow Rate"},
{ GroundHeatExchanger_VerticalFields::NumberofBoreHoles, "NumberofBoreHoles", "Number of Bore Holes"},
{ GroundHeatExchanger_VerticalFields::BoreHoleLength, "BoreHoleLength", "Bore Hole Length"},
{ GroundHeatExchanger_VerticalFields::BoreHoleRadius, "BoreHoleRadius", "Bore Hole Radius"},
{ GroundHeatExchanger_VerticalFields::GroundThermalConductivity, "GroundThermalConductivity", "Ground Thermal Conductivity"},
{ GroundHeatExchanger_VerticalFields::GroundThermalHeatCapacity, "GroundThermalHeatCapacity", "Ground Thermal Heat Capacity"},
{ GroundHeatExchanger_VerticalFields::GroundTemperature, "GroundTemperature", "Ground Temperature"},
{ GroundHeatExchanger_VerticalFields::GroutThermalConductivity, "GroutThermalConductivity", "Grout Thermal Conductivity"},
{ GroundHeatExchanger_VerticalFields::PipeThermalConductivity, "PipeThermalConductivity", "Pipe Thermal Conductivity"},
{ GroundHeatExchanger_VerticalFields::PipeOutDiameter, "PipeOutDiameter", "Pipe Out Diameter"},
{ GroundHeatExchanger_VerticalFields::UTubeDistance, "UTubeDistance", "U-Tube Distance"},
{ GroundHeatExchanger_VerticalFields::PipeThickness, "PipeThickness", "Pipe Thickness"},
{ GroundHeatExchanger_VerticalFields::MaximumLengthofSimulation, "MaximumLengthofSimulation", "Maximum Length of Simulation"},
{ GroundHeatExchanger_VerticalFields::GFunctionReferenceRatio, "GFunctionReferenceRatio", "G-Function Reference Ratio"},
{ GroundHeatExchanger_VerticalFields::NumberofDataPairsoftheGFunction, "NumberofDataPairsoftheGFunction", "Number of Data Pairs of the G Function"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatExchanger_VerticalFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatExchanger_VerticalFields> OptionalGroundHeatExchanger_VerticalFields ;
#endif

/** \class GroundHeatExchanger_VerticalExtensibleFields
 *  \brief Enumeration of GroundHeatExchanger:Vertical's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(GroundHeatExchanger_VerticalExtensibleFields, )
#else
class GroundHeatExchanger_VerticalExtensibleFields: public ::EnumBase<GroundHeatExchanger_VerticalExtensibleFields> {
 public: 
  enum domain 
  {
GFunctionLn_T_Ts_Value, GFunctionGValue,   };
  GroundHeatExchanger_VerticalExtensibleFields()
   : EnumBase<GroundHeatExchanger_VerticalExtensibleFields>(GFunctionLn_T_Ts_Value) {} 
  GroundHeatExchanger_VerticalExtensibleFields(const std::string &t_name) 
   : EnumBase<GroundHeatExchanger_VerticalExtensibleFields>(t_name) {} 
  GroundHeatExchanger_VerticalExtensibleFields(int t_value) 
   : EnumBase<GroundHeatExchanger_VerticalExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatExchanger_VerticalExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatExchanger_VerticalExtensibleFields>::value()); }
   private:
    friend class EnumBase<GroundHeatExchanger_VerticalExtensibleFields>;
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
{ GroundHeatExchanger_VerticalExtensibleFields::GFunctionLn_T_Ts_Value, "GFunctionLn_T_Ts_Value", "G-Function Ln(T/Ts) Value"},
{ GroundHeatExchanger_VerticalExtensibleFields::GFunctionGValue, "GFunctionGValue", "G-Function G Value"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatExchanger_VerticalExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatExchanger_VerticalExtensibleFields> OptionalGroundHeatExchanger_VerticalExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GROUNDHEATEXCHANGER_VERTICAL_FIELDENUMS_HXX
