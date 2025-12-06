/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_SPECIFIEDFLOWRATE_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_SPECIFIEDFLOWRATE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirflowNetwork_MultiZone_SpecifiedFlowRateFields
 *  \brief Enumeration of AirflowNetwork:MultiZone:SpecifiedFlowRate's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirflowNetwork_MultiZone_SpecifiedFlowRateFields, )
#else
class AirflowNetwork_MultiZone_SpecifiedFlowRateFields: public ::EnumBase<AirflowNetwork_MultiZone_SpecifiedFlowRateFields> {
 public: 
  enum domain 
  {
Name, AirFlowValue, AirFlowUnits,   };
  AirflowNetwork_MultiZone_SpecifiedFlowRateFields()
   : EnumBase<AirflowNetwork_MultiZone_SpecifiedFlowRateFields>(Name) {} 
  AirflowNetwork_MultiZone_SpecifiedFlowRateFields(const std::string &t_name) 
   : EnumBase<AirflowNetwork_MultiZone_SpecifiedFlowRateFields>(t_name) {} 
  AirflowNetwork_MultiZone_SpecifiedFlowRateFields(int t_value) 
   : EnumBase<AirflowNetwork_MultiZone_SpecifiedFlowRateFields>(t_value) {} 
  static std::string enumName() 
  { return "AirflowNetwork_MultiZone_SpecifiedFlowRateFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirflowNetwork_MultiZone_SpecifiedFlowRateFields>::integer_value()); }
   private:
    friend class EnumBase<AirflowNetwork_MultiZone_SpecifiedFlowRateFields>;
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
{ AirflowNetwork_MultiZone_SpecifiedFlowRateFields::Name, "Name", "Name"},
{ AirflowNetwork_MultiZone_SpecifiedFlowRateFields::AirFlowValue, "AirFlowValue", "Air Flow Value"},
{ AirflowNetwork_MultiZone_SpecifiedFlowRateFields::AirFlowUnits, "AirFlowUnits", "Air Flow Units"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirflowNetwork_MultiZone_SpecifiedFlowRateFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirflowNetwork_MultiZone_SpecifiedFlowRateFields> OptionalAirflowNetwork_MultiZone_SpecifiedFlowRateFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_SPECIFIEDFLOWRATE_FIELDENUMS_HXX
