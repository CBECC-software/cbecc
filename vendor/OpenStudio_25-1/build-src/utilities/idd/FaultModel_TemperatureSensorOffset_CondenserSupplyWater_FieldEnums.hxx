/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_FAULTMODEL_TEMPERATURESENSOROFFSET_CONDENSERSUPPLYWATER_FIELDENUMS_HXX
#define UTILITIES_IDD_FAULTMODEL_TEMPERATURESENSOROFFSET_CONDENSERSUPPLYWATER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields
 *  \brief Enumeration of FaultModel:TemperatureSensorOffset:CondenserSupplyWater's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields, )
#else
class FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields: public ::EnumBase<FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, SeverityScheduleName, CoolingTowerObjectType, CoolingTowerObjectName, ReferenceSensorOffset,   };
  FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields()
   : EnumBase<FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields>(Name) {} 
  FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields(const std::string &t_name) 
   : EnumBase<FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields>(t_name) {} 
  FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields(int t_value) 
   : EnumBase<FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields>(t_value) {} 
  static std::string enumName() 
  { return "FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields>::integer_value()); }
   private:
    friend class EnumBase<FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields>;
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
{ FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields::Name, "Name", "Name"},
{ FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields::SeverityScheduleName, "SeverityScheduleName", "Severity Schedule Name"},
{ FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields::CoolingTowerObjectType, "CoolingTowerObjectType", "Cooling Tower Object Type"},
{ FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields::CoolingTowerObjectName, "CoolingTowerObjectName", "Cooling Tower Object Name"},
{ FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields::ReferenceSensorOffset, "ReferenceSensorOffset", "Reference Sensor Offset"},
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
  inline std::ostream &operator<<(std::ostream &os, const FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields> OptionalFaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FAULTMODEL_TEMPERATURESENSOROFFSET_CONDENSERSUPPLYWATER_FIELDENUMS_HXX
