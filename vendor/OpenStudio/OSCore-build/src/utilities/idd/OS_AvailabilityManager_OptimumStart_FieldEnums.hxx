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

#ifndef UTILITIES_IDD_OS_AVAILABILITYMANAGER_OPTIMUMSTART_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AVAILABILITYMANAGER_OPTIMUMSTART_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AvailabilityManager_OptimumStartFields
 *  \brief Enumeration of OS:AvailabilityManager:OptimumStart's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AvailabilityManager_OptimumStartFields, )
#else
class OS_AvailabilityManager_OptimumStartFields: public ::EnumBase<OS_AvailabilityManager_OptimumStartFields> {
 public: 
  enum domain 
  {
Handle, Name, ApplicabilitySchedule, FanSchedule, ControlType, ControlZone, ZoneList, MaximumValueforOptimumStartTime, ControlAlgorithm, ConstantTemperatureGradientduringCooling, ConstantTemperatureGradientduringHeating, InitialTemperatureGradientduringCooling, InitialTemperatureGradientduringHeating, ConstantStartTime, NumberofPreviousDays,   };
  OS_AvailabilityManager_OptimumStartFields()
   : EnumBase<OS_AvailabilityManager_OptimumStartFields>(Handle) {} 
  OS_AvailabilityManager_OptimumStartFields(const std::string &t_name) 
   : EnumBase<OS_AvailabilityManager_OptimumStartFields>(t_name) {} 
  OS_AvailabilityManager_OptimumStartFields(int t_value) 
   : EnumBase<OS_AvailabilityManager_OptimumStartFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AvailabilityManager_OptimumStartFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AvailabilityManager_OptimumStartFields>::value()); }
   private:
    friend class EnumBase<OS_AvailabilityManager_OptimumStartFields>;
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
{ OS_AvailabilityManager_OptimumStartFields::Handle, "Handle", "Handle"},
{ OS_AvailabilityManager_OptimumStartFields::Name, "Name", "Name"},
{ OS_AvailabilityManager_OptimumStartFields::ApplicabilitySchedule, "ApplicabilitySchedule", "Applicability Schedule"},
{ OS_AvailabilityManager_OptimumStartFields::FanSchedule, "FanSchedule", "Fan Schedule"},
{ OS_AvailabilityManager_OptimumStartFields::ControlType, "ControlType", "Control Type"},
{ OS_AvailabilityManager_OptimumStartFields::ControlZone, "ControlZone", "Control Zone"},
{ OS_AvailabilityManager_OptimumStartFields::ZoneList, "ZoneList", "Zone List"},
{ OS_AvailabilityManager_OptimumStartFields::MaximumValueforOptimumStartTime, "MaximumValueforOptimumStartTime", "Maximum Value for Optimum Start Time"},
{ OS_AvailabilityManager_OptimumStartFields::ControlAlgorithm, "ControlAlgorithm", "Control Algorithm"},
{ OS_AvailabilityManager_OptimumStartFields::ConstantTemperatureGradientduringCooling, "ConstantTemperatureGradientduringCooling", "Constant Temperature Gradient during Cooling"},
{ OS_AvailabilityManager_OptimumStartFields::ConstantTemperatureGradientduringHeating, "ConstantTemperatureGradientduringHeating", "Constant Temperature Gradient during Heating"},
{ OS_AvailabilityManager_OptimumStartFields::InitialTemperatureGradientduringCooling, "InitialTemperatureGradientduringCooling", "Initial Temperature Gradient during Cooling"},
{ OS_AvailabilityManager_OptimumStartFields::InitialTemperatureGradientduringHeating, "InitialTemperatureGradientduringHeating", "Initial Temperature Gradient during Heating"},
{ OS_AvailabilityManager_OptimumStartFields::ConstantStartTime, "ConstantStartTime", "Constant Start Time"},
{ OS_AvailabilityManager_OptimumStartFields::NumberofPreviousDays, "NumberofPreviousDays", "Number of Previous Days"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AvailabilityManager_OptimumStartFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AvailabilityManager_OptimumStartFields> OptionalOS_AvailabilityManager_OptimumStartFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AVAILABILITYMANAGER_OPTIMUMSTART_FIELDENUMS_HXX
