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

#ifndef UTILITIES_IDD_OS_GROUNDHEATEXCHANGER_HORIZONTALTRENCH_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_GROUNDHEATEXCHANGER_HORIZONTALTRENCH_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_GroundHeatExchanger_HorizontalTrenchFields
 *  \brief Enumeration of OS:GroundHeatExchanger:HorizontalTrench's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_GroundHeatExchanger_HorizontalTrenchFields, )
#else
class OS_GroundHeatExchanger_HorizontalTrenchFields: public ::EnumBase<OS_GroundHeatExchanger_HorizontalTrenchFields> {
 public: 
  enum domain 
  {
Handle, Name, InletNodeName, OutletNodeName, DesignFlowRate, TrenchLengthinPipeAxialDirection, NumberofTrenches, HorizontalSpacingBetweenPipes, PipeInnerDiameter, PipeOuterDiameter, BurialDepth, SoilThermalConductivity, SoilDensity, SoilSpecificHeat, PipeThermalConductivity, PipeDensity, PipeSpecificHeat, SoilMoistureContentPercent, SoilMoistureContentPercentatSaturation, GroundTemperatureModel, KusudaAchenbachAverageSurfaceTemperature, KusudaAchenbachAverageAmplitudeofSurfaceTemperature, KusudaAchenbachPhaseShiftofMinimumSurfaceTemperature, EvapotranspirationGroundCoverParameter,   };
  OS_GroundHeatExchanger_HorizontalTrenchFields()
   : EnumBase<OS_GroundHeatExchanger_HorizontalTrenchFields>(Handle) {} 
  OS_GroundHeatExchanger_HorizontalTrenchFields(const std::string &t_name) 
   : EnumBase<OS_GroundHeatExchanger_HorizontalTrenchFields>(t_name) {} 
  OS_GroundHeatExchanger_HorizontalTrenchFields(int t_value) 
   : EnumBase<OS_GroundHeatExchanger_HorizontalTrenchFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_GroundHeatExchanger_HorizontalTrenchFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_GroundHeatExchanger_HorizontalTrenchFields>::value()); }
   private:
    friend class EnumBase<OS_GroundHeatExchanger_HorizontalTrenchFields>;
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
{ OS_GroundHeatExchanger_HorizontalTrenchFields::Handle, "Handle", "Handle"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::Name, "Name", "Name"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::DesignFlowRate, "DesignFlowRate", "Design Flow Rate"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::TrenchLengthinPipeAxialDirection, "TrenchLengthinPipeAxialDirection", "Trench Length in Pipe Axial Direction"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::NumberofTrenches, "NumberofTrenches", "Number of Trenches"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::HorizontalSpacingBetweenPipes, "HorizontalSpacingBetweenPipes", "Horizontal Spacing Between Pipes"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::PipeInnerDiameter, "PipeInnerDiameter", "Pipe Inner Diameter"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::PipeOuterDiameter, "PipeOuterDiameter", "Pipe Outer Diameter"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::BurialDepth, "BurialDepth", "Burial Depth"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::SoilThermalConductivity, "SoilThermalConductivity", "Soil Thermal Conductivity"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::SoilDensity, "SoilDensity", "Soil Density"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::SoilSpecificHeat, "SoilSpecificHeat", "Soil Specific Heat"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::PipeThermalConductivity, "PipeThermalConductivity", "Pipe Thermal Conductivity"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::PipeDensity, "PipeDensity", "Pipe Density"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::PipeSpecificHeat, "PipeSpecificHeat", "Pipe Specific Heat"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::SoilMoistureContentPercent, "SoilMoistureContentPercent", "Soil Moisture Content Percent"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::SoilMoistureContentPercentatSaturation, "SoilMoistureContentPercentatSaturation", "Soil Moisture Content Percent at Saturation"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::GroundTemperatureModel, "GroundTemperatureModel", "Ground Temperature Model"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::KusudaAchenbachAverageSurfaceTemperature, "KusudaAchenbachAverageSurfaceTemperature", "Kusuda-Achenbach Average Surface Temperature"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::KusudaAchenbachAverageAmplitudeofSurfaceTemperature, "KusudaAchenbachAverageAmplitudeofSurfaceTemperature", "Kusuda-Achenbach Average Amplitude of Surface Temperature"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::KusudaAchenbachPhaseShiftofMinimumSurfaceTemperature, "KusudaAchenbachPhaseShiftofMinimumSurfaceTemperature", "Kusuda-Achenbach Phase Shift of Minimum Surface Temperature"},
{ OS_GroundHeatExchanger_HorizontalTrenchFields::EvapotranspirationGroundCoverParameter, "EvapotranspirationGroundCoverParameter", "Evapotranspiration Ground Cover Parameter"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_GroundHeatExchanger_HorizontalTrenchFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_GroundHeatExchanger_HorizontalTrenchFields> OptionalOS_GroundHeatExchanger_HorizontalTrenchFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_GROUNDHEATEXCHANGER_HORIZONTALTRENCH_FIELDENUMS_HXX
