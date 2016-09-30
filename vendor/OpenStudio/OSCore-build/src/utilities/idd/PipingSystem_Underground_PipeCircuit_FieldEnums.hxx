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

#ifndef UTILITIES_IDD_PIPINGSYSTEM_UNDERGROUND_PIPECIRCUIT_FIELDENUMS_HXX
#define UTILITIES_IDD_PIPINGSYSTEM_UNDERGROUND_PIPECIRCUIT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PipingSystem_Underground_PipeCircuitFields
 *  \brief Enumeration of PipingSystem:Underground:PipeCircuit's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PipingSystem_Underground_PipeCircuitFields, )
#else
class PipingSystem_Underground_PipeCircuitFields: public ::EnumBase<PipingSystem_Underground_PipeCircuitFields> {
 public: 
  enum domain 
  {
Name, PipeThermalConductivity, PipeDensity, PipeSpecificHeat, PipeInnerDiameter, PipeOuterDiameter, DesignFlowRate, CircuitInletNode, CircuitOutletNode, ConvergenceCriterionfortheInnerRadialIterationLoop, MaximumIterationsintheInnerRadialIterationLoop, NumberofSoilNodesintheInnerRadialNearPipeMeshRegion, RadialThicknessofInnerRadialNearPipeMeshRegion, NumberofPipeSegmentsEnteredforthisPipeCircuit,   };
  PipingSystem_Underground_PipeCircuitFields()
   : EnumBase<PipingSystem_Underground_PipeCircuitFields>(Name) {} 
  PipingSystem_Underground_PipeCircuitFields(const std::string &t_name) 
   : EnumBase<PipingSystem_Underground_PipeCircuitFields>(t_name) {} 
  PipingSystem_Underground_PipeCircuitFields(int t_value) 
   : EnumBase<PipingSystem_Underground_PipeCircuitFields>(t_value) {} 
  static std::string enumName() 
  { return "PipingSystem_Underground_PipeCircuitFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PipingSystem_Underground_PipeCircuitFields>::value()); }
   private:
    friend class EnumBase<PipingSystem_Underground_PipeCircuitFields>;
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
{ PipingSystem_Underground_PipeCircuitFields::Name, "Name", "Name"},
{ PipingSystem_Underground_PipeCircuitFields::PipeThermalConductivity, "PipeThermalConductivity", "Pipe Thermal Conductivity"},
{ PipingSystem_Underground_PipeCircuitFields::PipeDensity, "PipeDensity", "Pipe Density"},
{ PipingSystem_Underground_PipeCircuitFields::PipeSpecificHeat, "PipeSpecificHeat", "Pipe Specific Heat"},
{ PipingSystem_Underground_PipeCircuitFields::PipeInnerDiameter, "PipeInnerDiameter", "Pipe Inner Diameter"},
{ PipingSystem_Underground_PipeCircuitFields::PipeOuterDiameter, "PipeOuterDiameter", "Pipe Outer Diameter"},
{ PipingSystem_Underground_PipeCircuitFields::DesignFlowRate, "DesignFlowRate", "Design Flow Rate"},
{ PipingSystem_Underground_PipeCircuitFields::CircuitInletNode, "CircuitInletNode", "Circuit Inlet Node"},
{ PipingSystem_Underground_PipeCircuitFields::CircuitOutletNode, "CircuitOutletNode", "Circuit Outlet Node"},
{ PipingSystem_Underground_PipeCircuitFields::ConvergenceCriterionfortheInnerRadialIterationLoop, "ConvergenceCriterionfortheInnerRadialIterationLoop", "Convergence Criterion for the Inner Radial Iteration Loop"},
{ PipingSystem_Underground_PipeCircuitFields::MaximumIterationsintheInnerRadialIterationLoop, "MaximumIterationsintheInnerRadialIterationLoop", "Maximum Iterations in the Inner Radial Iteration Loop"},
{ PipingSystem_Underground_PipeCircuitFields::NumberofSoilNodesintheInnerRadialNearPipeMeshRegion, "NumberofSoilNodesintheInnerRadialNearPipeMeshRegion", "Number of Soil Nodes in the Inner Radial Near Pipe Mesh Region"},
{ PipingSystem_Underground_PipeCircuitFields::RadialThicknessofInnerRadialNearPipeMeshRegion, "RadialThicknessofInnerRadialNearPipeMeshRegion", "Radial Thickness of Inner Radial Near Pipe Mesh Region"},
{ PipingSystem_Underground_PipeCircuitFields::NumberofPipeSegmentsEnteredforthisPipeCircuit, "NumberofPipeSegmentsEnteredforthisPipeCircuit", "Number of Pipe Segments Entered for this Pipe Circuit"},
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
  inline std::ostream &operator<<(std::ostream &os, const PipingSystem_Underground_PipeCircuitFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PipingSystem_Underground_PipeCircuitFields> OptionalPipingSystem_Underground_PipeCircuitFields ;
#endif

/** \class PipingSystem_Underground_PipeCircuitExtensibleFields
 *  \brief Enumeration of PipingSystem:Underground:PipeCircuit's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(PipingSystem_Underground_PipeCircuitExtensibleFields, )
#else
class PipingSystem_Underground_PipeCircuitExtensibleFields: public ::EnumBase<PipingSystem_Underground_PipeCircuitExtensibleFields> {
 public: 
  enum domain 
  {
PipeSegment,   };
  PipingSystem_Underground_PipeCircuitExtensibleFields()
   : EnumBase<PipingSystem_Underground_PipeCircuitExtensibleFields>(PipeSegment) {} 
  PipingSystem_Underground_PipeCircuitExtensibleFields(const std::string &t_name) 
   : EnumBase<PipingSystem_Underground_PipeCircuitExtensibleFields>(t_name) {} 
  PipingSystem_Underground_PipeCircuitExtensibleFields(int t_value) 
   : EnumBase<PipingSystem_Underground_PipeCircuitExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "PipingSystem_Underground_PipeCircuitExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PipingSystem_Underground_PipeCircuitExtensibleFields>::value()); }
   private:
    friend class EnumBase<PipingSystem_Underground_PipeCircuitExtensibleFields>;
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
{ PipingSystem_Underground_PipeCircuitExtensibleFields::PipeSegment, "PipeSegment", "Pipe Segment"},
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
  inline std::ostream &operator<<(std::ostream &os, const PipingSystem_Underground_PipeCircuitExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PipingSystem_Underground_PipeCircuitExtensibleFields> OptionalPipingSystem_Underground_PipeCircuitExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PIPINGSYSTEM_UNDERGROUND_PIPECIRCUIT_FIELDENUMS_HXX
