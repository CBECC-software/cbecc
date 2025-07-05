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

#ifndef UTILITIES_IDD_PIPINGSYSTEM_UNDERGROUND_DOMAIN_FIELDENUMS_HXX
#define UTILITIES_IDD_PIPINGSYSTEM_UNDERGROUND_DOMAIN_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PipingSystem_Underground_DomainFields
 *  \brief Enumeration of PipingSystem:Underground:Domain's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PipingSystem_Underground_DomainFields, )
#else
class PipingSystem_Underground_DomainFields: public ::EnumBase<PipingSystem_Underground_DomainFields> {
 public: 
  enum domain 
  {
Name, Xmax, Ymax, Zmax, XDirectionMeshDensityParameter, XDirectionMeshType, XDirectionGeometricCoefficient, YDirectionMeshDensityParameter, YDirectionMeshType, YDirectionGeometricCoefficient, ZDirectionMeshDensityParameter, ZDirectionMeshType, ZDirectionGeometricCoefficient, SoilThermalConductivity, SoilDensity, SoilSpecificHeat, SoilMoistureContentVolumeFraction, SoilMoistureContentVolumeFractionatSaturation, UndisturbedGroundTemperatureModelType, UndisturbedGroundTemperatureModelName, ThisDomainIncludesBasementSurfaceInteraction, WidthofBasementFloorinGroundDomain, DepthofBasementWallInGroundDomain, ShiftPipeXCoordinatesByBasementWidth, NameofBasementWallBoundaryConditionModel, NameofBasementFloorBoundaryConditionModel, ConvergenceCriterionfortheOuterCartesianDomainIterationLoop, MaximumIterationsintheOuterCartesianDomainIterationLoop, EvapotranspirationGroundCoverParameter, NumberofPipeCircuitsEnteredforthisDomain,   };
  PipingSystem_Underground_DomainFields()
   : EnumBase<PipingSystem_Underground_DomainFields>(Name) {} 
  PipingSystem_Underground_DomainFields(const std::string &t_name) 
   : EnumBase<PipingSystem_Underground_DomainFields>(t_name) {} 
  PipingSystem_Underground_DomainFields(int t_value) 
   : EnumBase<PipingSystem_Underground_DomainFields>(t_value) {} 
  static std::string enumName() 
  { return "PipingSystem_Underground_DomainFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PipingSystem_Underground_DomainFields>::value()); }
   private:
    friend class EnumBase<PipingSystem_Underground_DomainFields>;
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
{ PipingSystem_Underground_DomainFields::Name, "Name", "Name"},
{ PipingSystem_Underground_DomainFields::Xmax, "Xmax", "Xmax"},
{ PipingSystem_Underground_DomainFields::Ymax, "Ymax", "Ymax"},
{ PipingSystem_Underground_DomainFields::Zmax, "Zmax", "Zmax"},
{ PipingSystem_Underground_DomainFields::XDirectionMeshDensityParameter, "XDirectionMeshDensityParameter", "X-Direction Mesh Density Parameter"},
{ PipingSystem_Underground_DomainFields::XDirectionMeshType, "XDirectionMeshType", "X-Direction Mesh Type"},
{ PipingSystem_Underground_DomainFields::XDirectionGeometricCoefficient, "XDirectionGeometricCoefficient", "X-Direction Geometric Coefficient"},
{ PipingSystem_Underground_DomainFields::YDirectionMeshDensityParameter, "YDirectionMeshDensityParameter", "Y-Direction Mesh Density Parameter"},
{ PipingSystem_Underground_DomainFields::YDirectionMeshType, "YDirectionMeshType", "Y-Direction Mesh Type"},
{ PipingSystem_Underground_DomainFields::YDirectionGeometricCoefficient, "YDirectionGeometricCoefficient", "Y-Direction Geometric Coefficient"},
{ PipingSystem_Underground_DomainFields::ZDirectionMeshDensityParameter, "ZDirectionMeshDensityParameter", "Z-Direction Mesh Density Parameter"},
{ PipingSystem_Underground_DomainFields::ZDirectionMeshType, "ZDirectionMeshType", "Z-Direction Mesh Type"},
{ PipingSystem_Underground_DomainFields::ZDirectionGeometricCoefficient, "ZDirectionGeometricCoefficient", "Z-Direction Geometric Coefficient"},
{ PipingSystem_Underground_DomainFields::SoilThermalConductivity, "SoilThermalConductivity", "Soil Thermal Conductivity"},
{ PipingSystem_Underground_DomainFields::SoilDensity, "SoilDensity", "Soil Density"},
{ PipingSystem_Underground_DomainFields::SoilSpecificHeat, "SoilSpecificHeat", "Soil Specific Heat"},
{ PipingSystem_Underground_DomainFields::SoilMoistureContentVolumeFraction, "SoilMoistureContentVolumeFraction", "Soil Moisture Content Volume Fraction"},
{ PipingSystem_Underground_DomainFields::SoilMoistureContentVolumeFractionatSaturation, "SoilMoistureContentVolumeFractionatSaturation", "Soil Moisture Content Volume Fraction at Saturation"},
{ PipingSystem_Underground_DomainFields::UndisturbedGroundTemperatureModelType, "UndisturbedGroundTemperatureModelType", "Undisturbed Ground Temperature Model Type"},
{ PipingSystem_Underground_DomainFields::UndisturbedGroundTemperatureModelName, "UndisturbedGroundTemperatureModelName", "Undisturbed Ground Temperature Model Name"},
{ PipingSystem_Underground_DomainFields::ThisDomainIncludesBasementSurfaceInteraction, "ThisDomainIncludesBasementSurfaceInteraction", "This Domain Includes Basement Surface Interaction"},
{ PipingSystem_Underground_DomainFields::WidthofBasementFloorinGroundDomain, "WidthofBasementFloorinGroundDomain", "Width of Basement Floor in Ground Domain"},
{ PipingSystem_Underground_DomainFields::DepthofBasementWallInGroundDomain, "DepthofBasementWallInGroundDomain", "Depth of Basement Wall In Ground Domain"},
{ PipingSystem_Underground_DomainFields::ShiftPipeXCoordinatesByBasementWidth, "ShiftPipeXCoordinatesByBasementWidth", "Shift Pipe X Coordinates By Basement Width"},
{ PipingSystem_Underground_DomainFields::NameofBasementWallBoundaryConditionModel, "NameofBasementWallBoundaryConditionModel", "Name of Basement Wall Boundary Condition Model"},
{ PipingSystem_Underground_DomainFields::NameofBasementFloorBoundaryConditionModel, "NameofBasementFloorBoundaryConditionModel", "Name of Basement Floor Boundary Condition Model"},
{ PipingSystem_Underground_DomainFields::ConvergenceCriterionfortheOuterCartesianDomainIterationLoop, "ConvergenceCriterionfortheOuterCartesianDomainIterationLoop", "Convergence Criterion for the Outer Cartesian Domain Iteration Loop"},
{ PipingSystem_Underground_DomainFields::MaximumIterationsintheOuterCartesianDomainIterationLoop, "MaximumIterationsintheOuterCartesianDomainIterationLoop", "Maximum Iterations in the Outer Cartesian Domain Iteration Loop"},
{ PipingSystem_Underground_DomainFields::EvapotranspirationGroundCoverParameter, "EvapotranspirationGroundCoverParameter", "Evapotranspiration Ground Cover Parameter"},
{ PipingSystem_Underground_DomainFields::NumberofPipeCircuitsEnteredforthisDomain, "NumberofPipeCircuitsEnteredforthisDomain", "Number of Pipe Circuits Entered for this Domain"},
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
  inline std::ostream &operator<<(std::ostream &os, const PipingSystem_Underground_DomainFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PipingSystem_Underground_DomainFields> OptionalPipingSystem_Underground_DomainFields ;
#endif

/** \class PipingSystem_Underground_DomainExtensibleFields
 *  \brief Enumeration of PipingSystem:Underground:Domain's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(PipingSystem_Underground_DomainExtensibleFields, )
#else
class PipingSystem_Underground_DomainExtensibleFields: public ::EnumBase<PipingSystem_Underground_DomainExtensibleFields> {
 public: 
  enum domain 
  {
PipeCircuit,   };
  PipingSystem_Underground_DomainExtensibleFields()
   : EnumBase<PipingSystem_Underground_DomainExtensibleFields>(PipeCircuit) {} 
  PipingSystem_Underground_DomainExtensibleFields(const std::string &t_name) 
   : EnumBase<PipingSystem_Underground_DomainExtensibleFields>(t_name) {} 
  PipingSystem_Underground_DomainExtensibleFields(int t_value) 
   : EnumBase<PipingSystem_Underground_DomainExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "PipingSystem_Underground_DomainExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PipingSystem_Underground_DomainExtensibleFields>::value()); }
   private:
    friend class EnumBase<PipingSystem_Underground_DomainExtensibleFields>;
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
{ PipingSystem_Underground_DomainExtensibleFields::PipeCircuit, "PipeCircuit", "Pipe Circuit"},
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
  inline std::ostream &operator<<(std::ostream &os, const PipingSystem_Underground_DomainExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PipingSystem_Underground_DomainExtensibleFields> OptionalPipingSystem_Underground_DomainExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PIPINGSYSTEM_UNDERGROUND_DOMAIN_FIELDENUMS_HXX
