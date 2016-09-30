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

#ifndef UTILITIES_IDD_SOLARCOLLECTOR_FLATPLATE_WATER_FIELDENUMS_HXX
#define UTILITIES_IDD_SOLARCOLLECTOR_FLATPLATE_WATER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SolarCollector_FlatPlate_WaterFields
 *  \brief Enumeration of SolarCollector:FlatPlate:Water's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SolarCollector_FlatPlate_WaterFields, )
#else
class SolarCollector_FlatPlate_WaterFields: public ::EnumBase<SolarCollector_FlatPlate_WaterFields> {
 public: 
  enum domain 
  {
Name, SolarCollectorPerformanceName, SurfaceName, InletNodeName, OutletNodeName, MaximumFlowRate,   };
  SolarCollector_FlatPlate_WaterFields()
   : EnumBase<SolarCollector_FlatPlate_WaterFields>(Name) {} 
  SolarCollector_FlatPlate_WaterFields(const std::string &t_name) 
   : EnumBase<SolarCollector_FlatPlate_WaterFields>(t_name) {} 
  SolarCollector_FlatPlate_WaterFields(int t_value) 
   : EnumBase<SolarCollector_FlatPlate_WaterFields>(t_value) {} 
  static std::string enumName() 
  { return "SolarCollector_FlatPlate_WaterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SolarCollector_FlatPlate_WaterFields>::value()); }
   private:
    friend class EnumBase<SolarCollector_FlatPlate_WaterFields>;
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
{ SolarCollector_FlatPlate_WaterFields::Name, "Name", "Name"},
{ SolarCollector_FlatPlate_WaterFields::SolarCollectorPerformanceName, "SolarCollectorPerformanceName", "SolarCollectorPerformance Name"},
{ SolarCollector_FlatPlate_WaterFields::SurfaceName, "SurfaceName", "Surface Name"},
{ SolarCollector_FlatPlate_WaterFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ SolarCollector_FlatPlate_WaterFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ SolarCollector_FlatPlate_WaterFields::MaximumFlowRate, "MaximumFlowRate", "Maximum Flow Rate"},
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
  inline std::ostream &operator<<(std::ostream &os, const SolarCollector_FlatPlate_WaterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SolarCollector_FlatPlate_WaterFields> OptionalSolarCollector_FlatPlate_WaterFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SOLARCOLLECTOR_FLATPLATE_WATER_FIELDENUMS_HXX
