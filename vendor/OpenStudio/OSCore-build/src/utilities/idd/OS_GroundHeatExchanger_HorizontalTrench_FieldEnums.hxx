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
