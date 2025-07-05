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

#ifndef UTILITIES_IDD_GROUNDHEATEXCHANGER_HORIZONTALTRENCH_FIELDENUMS_HXX
#define UTILITIES_IDD_GROUNDHEATEXCHANGER_HORIZONTALTRENCH_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class GroundHeatExchanger_HorizontalTrenchFields
 *  \brief Enumeration of GroundHeatExchanger:HorizontalTrench's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(GroundHeatExchanger_HorizontalTrenchFields, )
#else
class GroundHeatExchanger_HorizontalTrenchFields: public ::EnumBase<GroundHeatExchanger_HorizontalTrenchFields> {
 public: 
  enum domain 
  {
Name, InletNodeName, OutletNodeName, DesignFlowRate, TrenchLengthinPipeAxialDirection, NumberofTrenches, HorizontalSpacingBetweenPipes, PipeInnerDiameter, PipeOuterDiameter, BurialDepth, SoilThermalConductivity, SoilDensity, SoilSpecificHeat, PipeThermalConductivity, PipeDensity, PipeSpecificHeat, SoilMoistureContentPercent, SoilMoistureContentPercentatSaturation, UndisturbedGroundTemperatureModelType, UndisturbedGroundTemperatureModelName, EvapotranspirationGroundCoverParameter,   };
  GroundHeatExchanger_HorizontalTrenchFields()
   : EnumBase<GroundHeatExchanger_HorizontalTrenchFields>(Name) {} 
  GroundHeatExchanger_HorizontalTrenchFields(const std::string &t_name) 
   : EnumBase<GroundHeatExchanger_HorizontalTrenchFields>(t_name) {} 
  GroundHeatExchanger_HorizontalTrenchFields(int t_value) 
   : EnumBase<GroundHeatExchanger_HorizontalTrenchFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatExchanger_HorizontalTrenchFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatExchanger_HorizontalTrenchFields>::value()); }
   private:
    friend class EnumBase<GroundHeatExchanger_HorizontalTrenchFields>;
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
{ GroundHeatExchanger_HorizontalTrenchFields::Name, "Name", "Name"},
{ GroundHeatExchanger_HorizontalTrenchFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ GroundHeatExchanger_HorizontalTrenchFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ GroundHeatExchanger_HorizontalTrenchFields::DesignFlowRate, "DesignFlowRate", "Design Flow Rate"},
{ GroundHeatExchanger_HorizontalTrenchFields::TrenchLengthinPipeAxialDirection, "TrenchLengthinPipeAxialDirection", "Trench Length in Pipe Axial Direction"},
{ GroundHeatExchanger_HorizontalTrenchFields::NumberofTrenches, "NumberofTrenches", "Number of Trenches"},
{ GroundHeatExchanger_HorizontalTrenchFields::HorizontalSpacingBetweenPipes, "HorizontalSpacingBetweenPipes", "Horizontal Spacing Between Pipes"},
{ GroundHeatExchanger_HorizontalTrenchFields::PipeInnerDiameter, "PipeInnerDiameter", "Pipe Inner Diameter"},
{ GroundHeatExchanger_HorizontalTrenchFields::PipeOuterDiameter, "PipeOuterDiameter", "Pipe Outer Diameter"},
{ GroundHeatExchanger_HorizontalTrenchFields::BurialDepth, "BurialDepth", "Burial Depth"},
{ GroundHeatExchanger_HorizontalTrenchFields::SoilThermalConductivity, "SoilThermalConductivity", "Soil Thermal Conductivity"},
{ GroundHeatExchanger_HorizontalTrenchFields::SoilDensity, "SoilDensity", "Soil Density"},
{ GroundHeatExchanger_HorizontalTrenchFields::SoilSpecificHeat, "SoilSpecificHeat", "Soil Specific Heat"},
{ GroundHeatExchanger_HorizontalTrenchFields::PipeThermalConductivity, "PipeThermalConductivity", "Pipe Thermal Conductivity"},
{ GroundHeatExchanger_HorizontalTrenchFields::PipeDensity, "PipeDensity", "Pipe Density"},
{ GroundHeatExchanger_HorizontalTrenchFields::PipeSpecificHeat, "PipeSpecificHeat", "Pipe Specific Heat"},
{ GroundHeatExchanger_HorizontalTrenchFields::SoilMoistureContentPercent, "SoilMoistureContentPercent", "Soil Moisture Content Percent"},
{ GroundHeatExchanger_HorizontalTrenchFields::SoilMoistureContentPercentatSaturation, "SoilMoistureContentPercentatSaturation", "Soil Moisture Content Percent at Saturation"},
{ GroundHeatExchanger_HorizontalTrenchFields::UndisturbedGroundTemperatureModelType, "UndisturbedGroundTemperatureModelType", "Undisturbed Ground Temperature Model Type"},
{ GroundHeatExchanger_HorizontalTrenchFields::UndisturbedGroundTemperatureModelName, "UndisturbedGroundTemperatureModelName", "Undisturbed Ground Temperature Model Name"},
{ GroundHeatExchanger_HorizontalTrenchFields::EvapotranspirationGroundCoverParameter, "EvapotranspirationGroundCoverParameter", "Evapotranspiration Ground Cover Parameter"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatExchanger_HorizontalTrenchFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatExchanger_HorizontalTrenchFields> OptionalGroundHeatExchanger_HorizontalTrenchFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GROUNDHEATEXCHANGER_HORIZONTALTRENCH_FIELDENUMS_HXX
