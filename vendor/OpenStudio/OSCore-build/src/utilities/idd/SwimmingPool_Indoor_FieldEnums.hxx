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

#ifndef UTILITIES_IDD_SWIMMINGPOOL_INDOOR_FIELDENUMS_HXX
#define UTILITIES_IDD_SWIMMINGPOOL_INDOOR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SwimmingPool_IndoorFields
 *  \brief Enumeration of SwimmingPool:Indoor's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SwimmingPool_IndoorFields, )
#else
class SwimmingPool_IndoorFields: public ::EnumBase<SwimmingPool_IndoorFields> {
 public: 
  enum domain 
  {
Name, SurfaceName, AverageDepth, ActivityFactorScheduleName, MakeupWaterSupplyScheduleName, CoverScheduleName, CoverEvaporationFactor, CoverConvectionFactor, CoverShortWavelengthRadiationFactor, CoverLongWavelengthRadiationFactor, PoolWaterInletNode, PoolWaterOutletNode, PoolHeatingSystemMaximumWaterFlowRate, PoolMiscellaneousEquipmentPower, SetpointTemperatureSchedule, MaximumNumberofPeople, PeopleSchedule, PeopleHeatGainSchedule,   };
  SwimmingPool_IndoorFields()
   : EnumBase<SwimmingPool_IndoorFields>(Name) {} 
  SwimmingPool_IndoorFields(const std::string &t_name) 
   : EnumBase<SwimmingPool_IndoorFields>(t_name) {} 
  SwimmingPool_IndoorFields(int t_value) 
   : EnumBase<SwimmingPool_IndoorFields>(t_value) {} 
  static std::string enumName() 
  { return "SwimmingPool_IndoorFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SwimmingPool_IndoorFields>::value()); }
   private:
    friend class EnumBase<SwimmingPool_IndoorFields>;
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
{ SwimmingPool_IndoorFields::Name, "Name", "Name"},
{ SwimmingPool_IndoorFields::SurfaceName, "SurfaceName", "Surface Name"},
{ SwimmingPool_IndoorFields::AverageDepth, "AverageDepth", "Average Depth"},
{ SwimmingPool_IndoorFields::ActivityFactorScheduleName, "ActivityFactorScheduleName", "Activity Factor Schedule Name"},
{ SwimmingPool_IndoorFields::MakeupWaterSupplyScheduleName, "MakeupWaterSupplyScheduleName", "Make-up Water Supply Schedule Name"},
{ SwimmingPool_IndoorFields::CoverScheduleName, "CoverScheduleName", "Cover Schedule Name"},
{ SwimmingPool_IndoorFields::CoverEvaporationFactor, "CoverEvaporationFactor", "Cover Evaporation Factor"},
{ SwimmingPool_IndoorFields::CoverConvectionFactor, "CoverConvectionFactor", "Cover Convection Factor"},
{ SwimmingPool_IndoorFields::CoverShortWavelengthRadiationFactor, "CoverShortWavelengthRadiationFactor", "Cover Short-Wavelength Radiation Factor"},
{ SwimmingPool_IndoorFields::CoverLongWavelengthRadiationFactor, "CoverLongWavelengthRadiationFactor", "Cover Long-Wavelength Radiation Factor"},
{ SwimmingPool_IndoorFields::PoolWaterInletNode, "PoolWaterInletNode", "Pool Water Inlet Node"},
{ SwimmingPool_IndoorFields::PoolWaterOutletNode, "PoolWaterOutletNode", "Pool Water Outlet Node"},
{ SwimmingPool_IndoorFields::PoolHeatingSystemMaximumWaterFlowRate, "PoolHeatingSystemMaximumWaterFlowRate", "Pool Heating System Maximum Water Flow Rate"},
{ SwimmingPool_IndoorFields::PoolMiscellaneousEquipmentPower, "PoolMiscellaneousEquipmentPower", "Pool Miscellaneous Equipment Power"},
{ SwimmingPool_IndoorFields::SetpointTemperatureSchedule, "SetpointTemperatureSchedule", "Setpoint Temperature Schedule"},
{ SwimmingPool_IndoorFields::MaximumNumberofPeople, "MaximumNumberofPeople", "Maximum Number of People"},
{ SwimmingPool_IndoorFields::PeopleSchedule, "PeopleSchedule", "People Schedule"},
{ SwimmingPool_IndoorFields::PeopleHeatGainSchedule, "PeopleHeatGainSchedule", "People Heat Gain Schedule"},
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
  inline std::ostream &operator<<(std::ostream &os, const SwimmingPool_IndoorFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SwimmingPool_IndoorFields> OptionalSwimmingPool_IndoorFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SWIMMINGPOOL_INDOOR_FIELDENUMS_HXX
