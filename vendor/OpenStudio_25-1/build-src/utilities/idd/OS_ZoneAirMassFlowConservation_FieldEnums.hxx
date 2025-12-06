/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_ZONEAIRMASSFLOWCONSERVATION_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ZONEAIRMASSFLOWCONSERVATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ZoneAirMassFlowConservationFields
 *  \brief Enumeration of OS:ZoneAirMassFlowConservation's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ZoneAirMassFlowConservationFields, )
#else
class OS_ZoneAirMassFlowConservationFields: public ::EnumBase<OS_ZoneAirMassFlowConservationFields> {
 public: 
  enum domain 
  {
Handle, AdjustZoneMixingandReturnForAirMassFlowBalance, InfiltrationBalancingMethod, InfiltrationBalancingZones,   };
  OS_ZoneAirMassFlowConservationFields()
   : EnumBase<OS_ZoneAirMassFlowConservationFields>(Handle) {} 
  OS_ZoneAirMassFlowConservationFields(const std::string &t_name) 
   : EnumBase<OS_ZoneAirMassFlowConservationFields>(t_name) {} 
  OS_ZoneAirMassFlowConservationFields(int t_value) 
   : EnumBase<OS_ZoneAirMassFlowConservationFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ZoneAirMassFlowConservationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ZoneAirMassFlowConservationFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ZoneAirMassFlowConservationFields>;
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
{ OS_ZoneAirMassFlowConservationFields::Handle, "Handle", "Handle"},
{ OS_ZoneAirMassFlowConservationFields::AdjustZoneMixingandReturnForAirMassFlowBalance, "AdjustZoneMixingandReturnForAirMassFlowBalance", "Adjust Zone Mixing and Return For Air Mass Flow Balance"},
{ OS_ZoneAirMassFlowConservationFields::InfiltrationBalancingMethod, "InfiltrationBalancingMethod", "Infiltration Balancing Method"},
{ OS_ZoneAirMassFlowConservationFields::InfiltrationBalancingZones, "InfiltrationBalancingZones", "Infiltration Balancing Zones"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ZoneAirMassFlowConservationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ZoneAirMassFlowConservationFields> OptionalOS_ZoneAirMassFlowConservationFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ZONEAIRMASSFLOWCONSERVATION_FIELDENUMS_HXX
