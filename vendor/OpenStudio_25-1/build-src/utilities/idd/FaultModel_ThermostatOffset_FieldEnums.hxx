/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_FAULTMODEL_THERMOSTATOFFSET_FIELDENUMS_HXX
#define UTILITIES_IDD_FAULTMODEL_THERMOSTATOFFSET_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class FaultModel_ThermostatOffsetFields
 *  \brief Enumeration of FaultModel:ThermostatOffset's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(FaultModel_ThermostatOffsetFields, )
#else
class FaultModel_ThermostatOffsetFields: public ::EnumBase<FaultModel_ThermostatOffsetFields> {
 public: 
  enum domain 
  {
Name, ThermostatName, AvailabilityScheduleName, SeverityScheduleName, ReferenceThermostatOffset,   };
  FaultModel_ThermostatOffsetFields()
   : EnumBase<FaultModel_ThermostatOffsetFields>(Name) {} 
  FaultModel_ThermostatOffsetFields(const std::string &t_name) 
   : EnumBase<FaultModel_ThermostatOffsetFields>(t_name) {} 
  FaultModel_ThermostatOffsetFields(int t_value) 
   : EnumBase<FaultModel_ThermostatOffsetFields>(t_value) {} 
  static std::string enumName() 
  { return "FaultModel_ThermostatOffsetFields"; }
  domain value() const { return static_cast<domain>(EnumBase<FaultModel_ThermostatOffsetFields>::integer_value()); }
   private:
    friend class EnumBase<FaultModel_ThermostatOffsetFields>;
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
{ FaultModel_ThermostatOffsetFields::Name, "Name", "Name"},
{ FaultModel_ThermostatOffsetFields::ThermostatName, "ThermostatName", "Thermostat Name"},
{ FaultModel_ThermostatOffsetFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ FaultModel_ThermostatOffsetFields::SeverityScheduleName, "SeverityScheduleName", "Severity Schedule Name"},
{ FaultModel_ThermostatOffsetFields::ReferenceThermostatOffset, "ReferenceThermostatOffset", "Reference Thermostat Offset"},
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
  inline std::ostream &operator<<(std::ostream &os, const FaultModel_ThermostatOffsetFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<FaultModel_ThermostatOffsetFields> OptionalFaultModel_ThermostatOffsetFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FAULTMODEL_THERMOSTATOFFSET_FIELDENUMS_HXX
