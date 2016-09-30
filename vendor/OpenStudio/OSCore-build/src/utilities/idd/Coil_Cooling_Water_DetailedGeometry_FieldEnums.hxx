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

#ifndef UTILITIES_IDD_COIL_COOLING_WATER_DETAILEDGEOMETRY_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_COOLING_WATER_DETAILEDGEOMETRY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Cooling_Water_DetailedGeometryFields
 *  \brief Enumeration of Coil:Cooling:Water:DetailedGeometry's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Cooling_Water_DetailedGeometryFields, )
#else
class Coil_Cooling_Water_DetailedGeometryFields: public ::EnumBase<Coil_Cooling_Water_DetailedGeometryFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, MaximumWaterFlowRate, TubeOutsideSurfaceArea, TotalTubeInsideArea, FinSurfaceArea, MinimumAirflowArea, CoilDepth, FinDiameter, FinThickness, TubeInsideDiameter, TubeOutsideDiameter, TubeThermalConductivity, FinThermalConductivity, FinSpacing, TubeDepthSpacing, NumberofTubeRows, NumberofTubesperRow, WaterInletNodeName, WaterOutletNodeName, AirInletNodeName, AirOutletNodeName, CondensateCollectionWaterStorageTankName,   };
  Coil_Cooling_Water_DetailedGeometryFields()
   : EnumBase<Coil_Cooling_Water_DetailedGeometryFields>(Name) {} 
  Coil_Cooling_Water_DetailedGeometryFields(const std::string &t_name) 
   : EnumBase<Coil_Cooling_Water_DetailedGeometryFields>(t_name) {} 
  Coil_Cooling_Water_DetailedGeometryFields(int t_value) 
   : EnumBase<Coil_Cooling_Water_DetailedGeometryFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Cooling_Water_DetailedGeometryFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Cooling_Water_DetailedGeometryFields>::value()); }
   private:
    friend class EnumBase<Coil_Cooling_Water_DetailedGeometryFields>;
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
{ Coil_Cooling_Water_DetailedGeometryFields::Name, "Name", "Name"},
{ Coil_Cooling_Water_DetailedGeometryFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Coil_Cooling_Water_DetailedGeometryFields::MaximumWaterFlowRate, "MaximumWaterFlowRate", "Maximum Water Flow Rate"},
{ Coil_Cooling_Water_DetailedGeometryFields::TubeOutsideSurfaceArea, "TubeOutsideSurfaceArea", "Tube Outside Surface Area"},
{ Coil_Cooling_Water_DetailedGeometryFields::TotalTubeInsideArea, "TotalTubeInsideArea", "Total Tube Inside Area"},
{ Coil_Cooling_Water_DetailedGeometryFields::FinSurfaceArea, "FinSurfaceArea", "Fin Surface Area"},
{ Coil_Cooling_Water_DetailedGeometryFields::MinimumAirflowArea, "MinimumAirflowArea", "Minimum Airflow Area"},
{ Coil_Cooling_Water_DetailedGeometryFields::CoilDepth, "CoilDepth", "Coil Depth"},
{ Coil_Cooling_Water_DetailedGeometryFields::FinDiameter, "FinDiameter", "Fin Diameter"},
{ Coil_Cooling_Water_DetailedGeometryFields::FinThickness, "FinThickness", "Fin Thickness"},
{ Coil_Cooling_Water_DetailedGeometryFields::TubeInsideDiameter, "TubeInsideDiameter", "Tube Inside Diameter"},
{ Coil_Cooling_Water_DetailedGeometryFields::TubeOutsideDiameter, "TubeOutsideDiameter", "Tube Outside Diameter"},
{ Coil_Cooling_Water_DetailedGeometryFields::TubeThermalConductivity, "TubeThermalConductivity", "Tube Thermal Conductivity"},
{ Coil_Cooling_Water_DetailedGeometryFields::FinThermalConductivity, "FinThermalConductivity", "Fin Thermal Conductivity"},
{ Coil_Cooling_Water_DetailedGeometryFields::FinSpacing, "FinSpacing", "Fin Spacing"},
{ Coil_Cooling_Water_DetailedGeometryFields::TubeDepthSpacing, "TubeDepthSpacing", "Tube Depth Spacing"},
{ Coil_Cooling_Water_DetailedGeometryFields::NumberofTubeRows, "NumberofTubeRows", "Number of Tube Rows"},
{ Coil_Cooling_Water_DetailedGeometryFields::NumberofTubesperRow, "NumberofTubesperRow", "Number of Tubes per Row"},
{ Coil_Cooling_Water_DetailedGeometryFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ Coil_Cooling_Water_DetailedGeometryFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ Coil_Cooling_Water_DetailedGeometryFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Coil_Cooling_Water_DetailedGeometryFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Coil_Cooling_Water_DetailedGeometryFields::CondensateCollectionWaterStorageTankName, "CondensateCollectionWaterStorageTankName", "Condensate Collection Water Storage Tank Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Cooling_Water_DetailedGeometryFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Cooling_Water_DetailedGeometryFields> OptionalCoil_Cooling_Water_DetailedGeometryFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_COOLING_WATER_DETAILEDGEOMETRY_FIELDENUMS_HXX
