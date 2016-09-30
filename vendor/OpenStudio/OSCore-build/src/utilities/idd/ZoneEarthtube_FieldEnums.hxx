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

#ifndef UTILITIES_IDD_ZONEEARTHTUBE_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEEARTHTUBE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneEarthtubeFields
 *  \brief Enumeration of ZoneEarthtube's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneEarthtubeFields, )
#else
class ZoneEarthtubeFields: public ::EnumBase<ZoneEarthtubeFields> {
 public: 
  enum domain 
  {
ZoneName, ScheduleName, DesignFlowRate, MinimumZoneTemperaturewhenCooling, MaximumZoneTemperaturewhenHeating, DeltaTemperature, EarthtubeType, FanPressureRise, FanTotalEfficiency, PipeRadius, PipeThickness, PipeLength, PipeThermalConductivity, PipeDepthUnderGroundSurface, SoilCondition, AverageSoilSurfaceTemperature, AmplitudeofSoilSurfaceTemperature, PhaseConstantofSoilSurfaceTemperature, ConstantTermFlowCoefficient, TemperatureTermFlowCoefficient, VelocityTermFlowCoefficient, VelocitySquaredTermFlowCoefficient,   };
  ZoneEarthtubeFields()
   : EnumBase<ZoneEarthtubeFields>(ZoneName) {} 
  ZoneEarthtubeFields(const std::string &t_name) 
   : EnumBase<ZoneEarthtubeFields>(t_name) {} 
  ZoneEarthtubeFields(int t_value) 
   : EnumBase<ZoneEarthtubeFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneEarthtubeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneEarthtubeFields>::value()); }
   private:
    friend class EnumBase<ZoneEarthtubeFields>;
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
{ ZoneEarthtubeFields::ZoneName, "ZoneName", "Zone Name"},
{ ZoneEarthtubeFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ ZoneEarthtubeFields::DesignFlowRate, "DesignFlowRate", "Design Flow Rate"},
{ ZoneEarthtubeFields::MinimumZoneTemperaturewhenCooling, "MinimumZoneTemperaturewhenCooling", "Minimum Zone Temperature when Cooling"},
{ ZoneEarthtubeFields::MaximumZoneTemperaturewhenHeating, "MaximumZoneTemperaturewhenHeating", "Maximum Zone Temperature when Heating"},
{ ZoneEarthtubeFields::DeltaTemperature, "DeltaTemperature", "Delta Temperature"},
{ ZoneEarthtubeFields::EarthtubeType, "EarthtubeType", "Earthtube Type"},
{ ZoneEarthtubeFields::FanPressureRise, "FanPressureRise", "Fan Pressure Rise"},
{ ZoneEarthtubeFields::FanTotalEfficiency, "FanTotalEfficiency", "Fan Total Efficiency"},
{ ZoneEarthtubeFields::PipeRadius, "PipeRadius", "Pipe Radius"},
{ ZoneEarthtubeFields::PipeThickness, "PipeThickness", "Pipe Thickness"},
{ ZoneEarthtubeFields::PipeLength, "PipeLength", "Pipe Length"},
{ ZoneEarthtubeFields::PipeThermalConductivity, "PipeThermalConductivity", "Pipe Thermal Conductivity"},
{ ZoneEarthtubeFields::PipeDepthUnderGroundSurface, "PipeDepthUnderGroundSurface", "Pipe Depth Under Ground Surface"},
{ ZoneEarthtubeFields::SoilCondition, "SoilCondition", "Soil Condition"},
{ ZoneEarthtubeFields::AverageSoilSurfaceTemperature, "AverageSoilSurfaceTemperature", "Average Soil Surface Temperature"},
{ ZoneEarthtubeFields::AmplitudeofSoilSurfaceTemperature, "AmplitudeofSoilSurfaceTemperature", "Amplitude of Soil Surface Temperature"},
{ ZoneEarthtubeFields::PhaseConstantofSoilSurfaceTemperature, "PhaseConstantofSoilSurfaceTemperature", "Phase Constant of Soil Surface Temperature"},
{ ZoneEarthtubeFields::ConstantTermFlowCoefficient, "ConstantTermFlowCoefficient", "Constant Term Flow Coefficient"},
{ ZoneEarthtubeFields::TemperatureTermFlowCoefficient, "TemperatureTermFlowCoefficient", "Temperature Term Flow Coefficient"},
{ ZoneEarthtubeFields::VelocityTermFlowCoefficient, "VelocityTermFlowCoefficient", "Velocity Term Flow Coefficient"},
{ ZoneEarthtubeFields::VelocitySquaredTermFlowCoefficient, "VelocitySquaredTermFlowCoefficient", "Velocity Squared Term Flow Coefficient"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneEarthtubeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneEarthtubeFields> OptionalZoneEarthtubeFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEEARTHTUBE_FIELDENUMS_HXX
