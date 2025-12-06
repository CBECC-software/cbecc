/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_WATERHEATER_SIZING_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_WATERHEATER_SIZING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_WaterHeater_SizingFields
 *  \brief Enumeration of OS:WaterHeater:Sizing's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_WaterHeater_SizingFields, )
#else
class OS_WaterHeater_SizingFields: public ::EnumBase<OS_WaterHeater_SizingFields> {
 public: 
  enum domain 
  {
Handle, WaterHeaterName, DesignMode, TimeStorageCanMeetPeakDraw, TimeforTankRecovery, NominalTankVolumeforAutosizingPlantConnections, NumberofBedrooms, NumberofBathrooms, StorageCapacityperPerson, RecoveryCapacityperPerson, StorageCapacityperFloorArea, RecoveryCapacityperFloorArea, NumberofUnits, StorageCapacityperUnit, RecoveryCapacityPerUnit, StorageCapacityperCollectorArea, HeightAspectRatio,   };
  OS_WaterHeater_SizingFields()
   : EnumBase<OS_WaterHeater_SizingFields>(Handle) {} 
  OS_WaterHeater_SizingFields(const std::string &t_name) 
   : EnumBase<OS_WaterHeater_SizingFields>(t_name) {} 
  OS_WaterHeater_SizingFields(int t_value) 
   : EnumBase<OS_WaterHeater_SizingFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_WaterHeater_SizingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_WaterHeater_SizingFields>::integer_value()); }
   private:
    friend class EnumBase<OS_WaterHeater_SizingFields>;
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
{ OS_WaterHeater_SizingFields::Handle, "Handle", "Handle"},
{ OS_WaterHeater_SizingFields::WaterHeaterName, "WaterHeaterName", "WaterHeater Name"},
{ OS_WaterHeater_SizingFields::DesignMode, "DesignMode", "Design Mode"},
{ OS_WaterHeater_SizingFields::TimeStorageCanMeetPeakDraw, "TimeStorageCanMeetPeakDraw", "Time Storage Can Meet Peak Draw"},
{ OS_WaterHeater_SizingFields::TimeforTankRecovery, "TimeforTankRecovery", "Time for Tank Recovery"},
{ OS_WaterHeater_SizingFields::NominalTankVolumeforAutosizingPlantConnections, "NominalTankVolumeforAutosizingPlantConnections", "Nominal Tank Volume for Autosizing Plant Connections"},
{ OS_WaterHeater_SizingFields::NumberofBedrooms, "NumberofBedrooms", "Number of Bedrooms"},
{ OS_WaterHeater_SizingFields::NumberofBathrooms, "NumberofBathrooms", "Number of Bathrooms"},
{ OS_WaterHeater_SizingFields::StorageCapacityperPerson, "StorageCapacityperPerson", "Storage Capacity per Person"},
{ OS_WaterHeater_SizingFields::RecoveryCapacityperPerson, "RecoveryCapacityperPerson", "Recovery Capacity per Person"},
{ OS_WaterHeater_SizingFields::StorageCapacityperFloorArea, "StorageCapacityperFloorArea", "Storage Capacity per Floor Area"},
{ OS_WaterHeater_SizingFields::RecoveryCapacityperFloorArea, "RecoveryCapacityperFloorArea", "Recovery Capacity per Floor Area"},
{ OS_WaterHeater_SizingFields::NumberofUnits, "NumberofUnits", "Number of Units"},
{ OS_WaterHeater_SizingFields::StorageCapacityperUnit, "StorageCapacityperUnit", "Storage Capacity per Unit"},
{ OS_WaterHeater_SizingFields::RecoveryCapacityPerUnit, "RecoveryCapacityPerUnit", "Recovery Capacity PerUnit"},
{ OS_WaterHeater_SizingFields::StorageCapacityperCollectorArea, "StorageCapacityperCollectorArea", "Storage Capacity per Collector Area"},
{ OS_WaterHeater_SizingFields::HeightAspectRatio, "HeightAspectRatio", "Height Aspect Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_WaterHeater_SizingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_WaterHeater_SizingFields> OptionalOS_WaterHeater_SizingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_WATERHEATER_SIZING_FIELDENUMS_HXX
