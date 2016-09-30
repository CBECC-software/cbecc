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
