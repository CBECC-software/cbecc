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

#ifndef UTILITIES_IDD_SOLARCOLLECTOR_UNGLAZEDTRANSPIRED_FIELDENUMS_HXX
#define UTILITIES_IDD_SOLARCOLLECTOR_UNGLAZEDTRANSPIRED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SolarCollector_UnglazedTranspiredFields
 *  \brief Enumeration of SolarCollector:UnglazedTranspired's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SolarCollector_UnglazedTranspiredFields, )
#else
class SolarCollector_UnglazedTranspiredFields: public ::EnumBase<SolarCollector_UnglazedTranspiredFields> {
 public: 
  enum domain 
  {
Name, BoundaryConditionsModelName, AvailabilityScheduleName, InletNodeName, OutletNodeName, SetpointNodeName, ZoneNodeName, FreeHeatingSetpointScheduleName, DiameterofPerforationsinCollector, DistanceBetweenPerforationsinCollector, ThermalEmissivityofCollectorSurface, SolarAbsorbtivityofCollectorSurface, EffectiveOverallHeightofCollector, EffectiveGapThicknessofPlenumBehindCollector, EffectiveCrossSectionAreaofPlenumBehindCollector, HoleLayoutPatternforPitch, HeatExchangeEffectivenessCorrelation, RatioofActualCollectorSurfaceAreatoProjectedSurfaceArea, RoughnessofCollector, CollectorThickness, EffectivenessforPerforationswithRespecttoWind, DischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow,   };
  SolarCollector_UnglazedTranspiredFields()
   : EnumBase<SolarCollector_UnglazedTranspiredFields>(Name) {} 
  SolarCollector_UnglazedTranspiredFields(const std::string &t_name) 
   : EnumBase<SolarCollector_UnglazedTranspiredFields>(t_name) {} 
  SolarCollector_UnglazedTranspiredFields(int t_value) 
   : EnumBase<SolarCollector_UnglazedTranspiredFields>(t_value) {} 
  static std::string enumName() 
  { return "SolarCollector_UnglazedTranspiredFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SolarCollector_UnglazedTranspiredFields>::value()); }
   private:
    friend class EnumBase<SolarCollector_UnglazedTranspiredFields>;
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
{ SolarCollector_UnglazedTranspiredFields::Name, "Name", "Name"},
{ SolarCollector_UnglazedTranspiredFields::BoundaryConditionsModelName, "BoundaryConditionsModelName", "Boundary Conditions Model Name"},
{ SolarCollector_UnglazedTranspiredFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ SolarCollector_UnglazedTranspiredFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ SolarCollector_UnglazedTranspiredFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ SolarCollector_UnglazedTranspiredFields::SetpointNodeName, "SetpointNodeName", "Setpoint Node Name"},
{ SolarCollector_UnglazedTranspiredFields::ZoneNodeName, "ZoneNodeName", "Zone Node Name"},
{ SolarCollector_UnglazedTranspiredFields::FreeHeatingSetpointScheduleName, "FreeHeatingSetpointScheduleName", "Free Heating Setpoint Schedule Name"},
{ SolarCollector_UnglazedTranspiredFields::DiameterofPerforationsinCollector, "DiameterofPerforationsinCollector", "Diameter of Perforations in Collector"},
{ SolarCollector_UnglazedTranspiredFields::DistanceBetweenPerforationsinCollector, "DistanceBetweenPerforationsinCollector", "Distance Between Perforations in Collector"},
{ SolarCollector_UnglazedTranspiredFields::ThermalEmissivityofCollectorSurface, "ThermalEmissivityofCollectorSurface", "Thermal Emissivity of Collector Surface"},
{ SolarCollector_UnglazedTranspiredFields::SolarAbsorbtivityofCollectorSurface, "SolarAbsorbtivityofCollectorSurface", "Solar Absorbtivity of Collector Surface"},
{ SolarCollector_UnglazedTranspiredFields::EffectiveOverallHeightofCollector, "EffectiveOverallHeightofCollector", "Effective Overall Height of Collector"},
{ SolarCollector_UnglazedTranspiredFields::EffectiveGapThicknessofPlenumBehindCollector, "EffectiveGapThicknessofPlenumBehindCollector", "Effective Gap Thickness of Plenum Behind Collector"},
{ SolarCollector_UnglazedTranspiredFields::EffectiveCrossSectionAreaofPlenumBehindCollector, "EffectiveCrossSectionAreaofPlenumBehindCollector", "Effective Cross Section Area of Plenum Behind Collector"},
{ SolarCollector_UnglazedTranspiredFields::HoleLayoutPatternforPitch, "HoleLayoutPatternforPitch", "Hole Layout Pattern for Pitch"},
{ SolarCollector_UnglazedTranspiredFields::HeatExchangeEffectivenessCorrelation, "HeatExchangeEffectivenessCorrelation", "Heat Exchange Effectiveness Correlation"},
{ SolarCollector_UnglazedTranspiredFields::RatioofActualCollectorSurfaceAreatoProjectedSurfaceArea, "RatioofActualCollectorSurfaceAreatoProjectedSurfaceArea", "Ratio of Actual Collector Surface Area to Projected Surface Area"},
{ SolarCollector_UnglazedTranspiredFields::RoughnessofCollector, "RoughnessofCollector", "Roughness of Collector"},
{ SolarCollector_UnglazedTranspiredFields::CollectorThickness, "CollectorThickness", "Collector Thickness"},
{ SolarCollector_UnglazedTranspiredFields::EffectivenessforPerforationswithRespecttoWind, "EffectivenessforPerforationswithRespecttoWind", "Effectiveness for Perforations with Respect to Wind"},
{ SolarCollector_UnglazedTranspiredFields::DischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow, "DischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow", "Discharge Coefficient for Openings with Respect to Buoyancy Driven Flow"},
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
  inline std::ostream &operator<<(std::ostream &os, const SolarCollector_UnglazedTranspiredFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SolarCollector_UnglazedTranspiredFields> OptionalSolarCollector_UnglazedTranspiredFields ;
#endif

/** \class SolarCollector_UnglazedTranspiredExtensibleFields
 *  \brief Enumeration of SolarCollector:UnglazedTranspired's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(SolarCollector_UnglazedTranspiredExtensibleFields, )
#else
class SolarCollector_UnglazedTranspiredExtensibleFields: public ::EnumBase<SolarCollector_UnglazedTranspiredExtensibleFields> {
 public: 
  enum domain 
  {
SurfaceName,   };
  SolarCollector_UnglazedTranspiredExtensibleFields()
   : EnumBase<SolarCollector_UnglazedTranspiredExtensibleFields>(SurfaceName) {} 
  SolarCollector_UnglazedTranspiredExtensibleFields(const std::string &t_name) 
   : EnumBase<SolarCollector_UnglazedTranspiredExtensibleFields>(t_name) {} 
  SolarCollector_UnglazedTranspiredExtensibleFields(int t_value) 
   : EnumBase<SolarCollector_UnglazedTranspiredExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "SolarCollector_UnglazedTranspiredExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SolarCollector_UnglazedTranspiredExtensibleFields>::value()); }
   private:
    friend class EnumBase<SolarCollector_UnglazedTranspiredExtensibleFields>;
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
{ SolarCollector_UnglazedTranspiredExtensibleFields::SurfaceName, "SurfaceName", "Surface Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SolarCollector_UnglazedTranspiredExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SolarCollector_UnglazedTranspiredExtensibleFields> OptionalSolarCollector_UnglazedTranspiredExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SOLARCOLLECTOR_UNGLAZEDTRANSPIRED_FIELDENUMS_HXX
