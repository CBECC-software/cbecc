/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_ZONEAIRMASSFLOWCONSERVATION_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEAIRMASSFLOWCONSERVATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneAirMassFlowConservationFields
 *  \brief Enumeration of ZoneAirMassFlowConservation's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneAirMassFlowConservationFields, )
#else
class ZoneAirMassFlowConservationFields: public ::EnumBase<ZoneAirMassFlowConservationFields> {
 public: 
  enum domain 
  {
AdjustZoneMixingandReturnForAirMassFlowBalance, InfiltrationBalancingMethod, InfiltrationBalancingZones,   };
  ZoneAirMassFlowConservationFields()
   : EnumBase<ZoneAirMassFlowConservationFields>(AdjustZoneMixingandReturnForAirMassFlowBalance) {} 
  ZoneAirMassFlowConservationFields(const std::string &t_name) 
   : EnumBase<ZoneAirMassFlowConservationFields>(t_name) {} 
  ZoneAirMassFlowConservationFields(int t_value) 
   : EnumBase<ZoneAirMassFlowConservationFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneAirMassFlowConservationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneAirMassFlowConservationFields>::integer_value()); }
   private:
    friend class EnumBase<ZoneAirMassFlowConservationFields>;
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
{ ZoneAirMassFlowConservationFields::AdjustZoneMixingandReturnForAirMassFlowBalance, "AdjustZoneMixingandReturnForAirMassFlowBalance", "Adjust Zone Mixing and Return For Air Mass Flow Balance"},
{ ZoneAirMassFlowConservationFields::InfiltrationBalancingMethod, "InfiltrationBalancingMethod", "Infiltration Balancing Method"},
{ ZoneAirMassFlowConservationFields::InfiltrationBalancingZones, "InfiltrationBalancingZones", "Infiltration Balancing Zones"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneAirMassFlowConservationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneAirMassFlowConservationFields> OptionalZoneAirMassFlowConservationFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEAIRMASSFLOWCONSERVATION_FIELDENUMS_HXX
