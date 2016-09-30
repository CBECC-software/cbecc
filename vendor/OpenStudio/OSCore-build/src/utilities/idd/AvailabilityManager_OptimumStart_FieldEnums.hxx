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

#ifndef UTILITIES_IDD_AVAILABILITYMANAGER_OPTIMUMSTART_FIELDENUMS_HXX
#define UTILITIES_IDD_AVAILABILITYMANAGER_OPTIMUMSTART_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AvailabilityManager_OptimumStartFields
 *  \brief Enumeration of AvailabilityManager:OptimumStart's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AvailabilityManager_OptimumStartFields, )
#else
class AvailabilityManager_OptimumStartFields: public ::EnumBase<AvailabilityManager_OptimumStartFields> {
 public: 
  enum domain 
  {
Name, ApplicabilityScheduleName, FanScheduleName, ControlType, ControlZoneName, ZoneListName, MaximumValueforOptimumStartTime, ControlAlgorithm, ConstantTemperatureGradientduringCooling, ConstantTemperatureGradientduringHeating, InitialTemperatureGradientduringCooling, InitialTemperatureGradientduringHeating, ConstantStartTime, NumberofPreviousDays,   };
  AvailabilityManager_OptimumStartFields()
   : EnumBase<AvailabilityManager_OptimumStartFields>(Name) {} 
  AvailabilityManager_OptimumStartFields(const std::string &t_name) 
   : EnumBase<AvailabilityManager_OptimumStartFields>(t_name) {} 
  AvailabilityManager_OptimumStartFields(int t_value) 
   : EnumBase<AvailabilityManager_OptimumStartFields>(t_value) {} 
  static std::string enumName() 
  { return "AvailabilityManager_OptimumStartFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AvailabilityManager_OptimumStartFields>::value()); }
   private:
    friend class EnumBase<AvailabilityManager_OptimumStartFields>;
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
{ AvailabilityManager_OptimumStartFields::Name, "Name", "Name"},
{ AvailabilityManager_OptimumStartFields::ApplicabilityScheduleName, "ApplicabilityScheduleName", "Applicability Schedule Name"},
{ AvailabilityManager_OptimumStartFields::FanScheduleName, "FanScheduleName", "Fan Schedule Name"},
{ AvailabilityManager_OptimumStartFields::ControlType, "ControlType", "Control Type"},
{ AvailabilityManager_OptimumStartFields::ControlZoneName, "ControlZoneName", "Control Zone Name"},
{ AvailabilityManager_OptimumStartFields::ZoneListName, "ZoneListName", "Zone List Name"},
{ AvailabilityManager_OptimumStartFields::MaximumValueforOptimumStartTime, "MaximumValueforOptimumStartTime", "Maximum Value for Optimum Start Time"},
{ AvailabilityManager_OptimumStartFields::ControlAlgorithm, "ControlAlgorithm", "Control Algorithm"},
{ AvailabilityManager_OptimumStartFields::ConstantTemperatureGradientduringCooling, "ConstantTemperatureGradientduringCooling", "Constant Temperature Gradient during Cooling"},
{ AvailabilityManager_OptimumStartFields::ConstantTemperatureGradientduringHeating, "ConstantTemperatureGradientduringHeating", "Constant Temperature Gradient during Heating"},
{ AvailabilityManager_OptimumStartFields::InitialTemperatureGradientduringCooling, "InitialTemperatureGradientduringCooling", "Initial Temperature Gradient during Cooling"},
{ AvailabilityManager_OptimumStartFields::InitialTemperatureGradientduringHeating, "InitialTemperatureGradientduringHeating", "Initial Temperature Gradient during Heating"},
{ AvailabilityManager_OptimumStartFields::ConstantStartTime, "ConstantStartTime", "Constant Start Time"},
{ AvailabilityManager_OptimumStartFields::NumberofPreviousDays, "NumberofPreviousDays", "Number of Previous Days"},
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
  inline std::ostream &operator<<(std::ostream &os, const AvailabilityManager_OptimumStartFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AvailabilityManager_OptimumStartFields> OptionalAvailabilityManager_OptimumStartFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AVAILABILITYMANAGER_OPTIMUMSTART_FIELDENUMS_HXX
