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

#ifndef UTILITIES_IDD_WATERHEATER_SIZING_FIELDENUMS_HXX
#define UTILITIES_IDD_WATERHEATER_SIZING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WaterHeater_SizingFields
 *  \brief Enumeration of WaterHeater:Sizing's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WaterHeater_SizingFields, )
#else
class WaterHeater_SizingFields: public ::EnumBase<WaterHeater_SizingFields> {
 public: 
  enum domain 
  {
WaterHeaterName, DesignMode, TimeStorageCanMeetPeakDraw, TimeforTankRecovery, NominalTankVolumeforAutosizingPlantConnections, NumberofBedrooms, NumberofBathrooms, StorageCapacityperPerson, RecoveryCapacityperPerson, StorageCapacityperFloorArea, RecoveryCapacityperFloorArea, NumberofUnits, StorageCapacityperUnit, RecoveryCapacityPerUnit, StorageCapacityperCollectorArea, HeightAspectRatio,   };
  WaterHeater_SizingFields()
   : EnumBase<WaterHeater_SizingFields>(WaterHeaterName) {} 
  WaterHeater_SizingFields(const std::string &t_name) 
   : EnumBase<WaterHeater_SizingFields>(t_name) {} 
  WaterHeater_SizingFields(int t_value) 
   : EnumBase<WaterHeater_SizingFields>(t_value) {} 
  static std::string enumName() 
  { return "WaterHeater_SizingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WaterHeater_SizingFields>::value()); }
   private:
    friend class EnumBase<WaterHeater_SizingFields>;
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
{ WaterHeater_SizingFields::WaterHeaterName, "WaterHeaterName", "WaterHeater Name"},
{ WaterHeater_SizingFields::DesignMode, "DesignMode", "Design Mode"},
{ WaterHeater_SizingFields::TimeStorageCanMeetPeakDraw, "TimeStorageCanMeetPeakDraw", "Time Storage Can Meet Peak Draw"},
{ WaterHeater_SizingFields::TimeforTankRecovery, "TimeforTankRecovery", "Time for Tank Recovery"},
{ WaterHeater_SizingFields::NominalTankVolumeforAutosizingPlantConnections, "NominalTankVolumeforAutosizingPlantConnections", "Nominal Tank Volume for Autosizing Plant Connections"},
{ WaterHeater_SizingFields::NumberofBedrooms, "NumberofBedrooms", "Number of Bedrooms"},
{ WaterHeater_SizingFields::NumberofBathrooms, "NumberofBathrooms", "Number of Bathrooms"},
{ WaterHeater_SizingFields::StorageCapacityperPerson, "StorageCapacityperPerson", "Storage Capacity per Person"},
{ WaterHeater_SizingFields::RecoveryCapacityperPerson, "RecoveryCapacityperPerson", "Recovery Capacity per Person"},
{ WaterHeater_SizingFields::StorageCapacityperFloorArea, "StorageCapacityperFloorArea", "Storage Capacity per Floor Area"},
{ WaterHeater_SizingFields::RecoveryCapacityperFloorArea, "RecoveryCapacityperFloorArea", "Recovery Capacity per Floor Area"},
{ WaterHeater_SizingFields::NumberofUnits, "NumberofUnits", "Number of Units"},
{ WaterHeater_SizingFields::StorageCapacityperUnit, "StorageCapacityperUnit", "Storage Capacity per Unit"},
{ WaterHeater_SizingFields::RecoveryCapacityPerUnit, "RecoveryCapacityPerUnit", "Recovery Capacity PerUnit"},
{ WaterHeater_SizingFields::StorageCapacityperCollectorArea, "StorageCapacityperCollectorArea", "Storage Capacity per Collector Area"},
{ WaterHeater_SizingFields::HeightAspectRatio, "HeightAspectRatio", "Height Aspect Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const WaterHeater_SizingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WaterHeater_SizingFields> OptionalWaterHeater_SizingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WATERHEATER_SIZING_FIELDENUMS_HXX
