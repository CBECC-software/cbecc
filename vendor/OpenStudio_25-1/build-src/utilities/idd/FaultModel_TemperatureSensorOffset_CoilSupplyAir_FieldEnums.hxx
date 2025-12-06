/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_FAULTMODEL_TEMPERATURESENSOROFFSET_COILSUPPLYAIR_FIELDENUMS_HXX
#define UTILITIES_IDD_FAULTMODEL_TEMPERATURESENSOROFFSET_COILSUPPLYAIR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class FaultModel_TemperatureSensorOffset_CoilSupplyAirFields
 *  \brief Enumeration of FaultModel:TemperatureSensorOffset:CoilSupplyAir's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(FaultModel_TemperatureSensorOffset_CoilSupplyAirFields, )
#else
class FaultModel_TemperatureSensorOffset_CoilSupplyAirFields: public ::EnumBase<FaultModel_TemperatureSensorOffset_CoilSupplyAirFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, SeverityScheduleName, CoilObjectType, CoilObjectName, WaterCoilControllerName, ReferenceSensorOffset,   };
  FaultModel_TemperatureSensorOffset_CoilSupplyAirFields()
   : EnumBase<FaultModel_TemperatureSensorOffset_CoilSupplyAirFields>(Name) {} 
  FaultModel_TemperatureSensorOffset_CoilSupplyAirFields(const std::string &t_name) 
   : EnumBase<FaultModel_TemperatureSensorOffset_CoilSupplyAirFields>(t_name) {} 
  FaultModel_TemperatureSensorOffset_CoilSupplyAirFields(int t_value) 
   : EnumBase<FaultModel_TemperatureSensorOffset_CoilSupplyAirFields>(t_value) {} 
  static std::string enumName() 
  { return "FaultModel_TemperatureSensorOffset_CoilSupplyAirFields"; }
  domain value() const { return static_cast<domain>(EnumBase<FaultModel_TemperatureSensorOffset_CoilSupplyAirFields>::integer_value()); }
   private:
    friend class EnumBase<FaultModel_TemperatureSensorOffset_CoilSupplyAirFields>;
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
{ FaultModel_TemperatureSensorOffset_CoilSupplyAirFields::Name, "Name", "Name"},
{ FaultModel_TemperatureSensorOffset_CoilSupplyAirFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ FaultModel_TemperatureSensorOffset_CoilSupplyAirFields::SeverityScheduleName, "SeverityScheduleName", "Severity Schedule Name"},
{ FaultModel_TemperatureSensorOffset_CoilSupplyAirFields::CoilObjectType, "CoilObjectType", "Coil Object Type"},
{ FaultModel_TemperatureSensorOffset_CoilSupplyAirFields::CoilObjectName, "CoilObjectName", "Coil Object Name"},
{ FaultModel_TemperatureSensorOffset_CoilSupplyAirFields::WaterCoilControllerName, "WaterCoilControllerName", "Water Coil Controller Name"},
{ FaultModel_TemperatureSensorOffset_CoilSupplyAirFields::ReferenceSensorOffset, "ReferenceSensorOffset", "Reference Sensor Offset"},
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
  inline std::ostream &operator<<(std::ostream &os, const FaultModel_TemperatureSensorOffset_CoilSupplyAirFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<FaultModel_TemperatureSensorOffset_CoilSupplyAirFields> OptionalFaultModel_TemperatureSensorOffset_CoilSupplyAirFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FAULTMODEL_TEMPERATURESENSOROFFSET_COILSUPPLYAIR_FIELDENUMS_HXX
