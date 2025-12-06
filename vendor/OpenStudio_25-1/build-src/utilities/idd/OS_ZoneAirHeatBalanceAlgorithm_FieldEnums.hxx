/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_ZONEAIRHEATBALANCEALGORITHM_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ZONEAIRHEATBALANCEALGORITHM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ZoneAirHeatBalanceAlgorithmFields
 *  \brief Enumeration of OS:ZoneAirHeatBalanceAlgorithm's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ZoneAirHeatBalanceAlgorithmFields, )
#else
class OS_ZoneAirHeatBalanceAlgorithmFields: public ::EnumBase<OS_ZoneAirHeatBalanceAlgorithmFields> {
 public: 
  enum domain 
  {
Handle, Algorithm, DoSpaceHeatBalanceforSizing, DoSpaceHeatBalanceforSimulation,   };
  OS_ZoneAirHeatBalanceAlgorithmFields()
   : EnumBase<OS_ZoneAirHeatBalanceAlgorithmFields>(Handle) {} 
  OS_ZoneAirHeatBalanceAlgorithmFields(const std::string &t_name) 
   : EnumBase<OS_ZoneAirHeatBalanceAlgorithmFields>(t_name) {} 
  OS_ZoneAirHeatBalanceAlgorithmFields(int t_value) 
   : EnumBase<OS_ZoneAirHeatBalanceAlgorithmFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ZoneAirHeatBalanceAlgorithmFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ZoneAirHeatBalanceAlgorithmFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ZoneAirHeatBalanceAlgorithmFields>;
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
{ OS_ZoneAirHeatBalanceAlgorithmFields::Handle, "Handle", "Handle"},
{ OS_ZoneAirHeatBalanceAlgorithmFields::Algorithm, "Algorithm", "Algorithm"},
{ OS_ZoneAirHeatBalanceAlgorithmFields::DoSpaceHeatBalanceforSizing, "DoSpaceHeatBalanceforSizing", "Do Space Heat Balance for Sizing"},
{ OS_ZoneAirHeatBalanceAlgorithmFields::DoSpaceHeatBalanceforSimulation, "DoSpaceHeatBalanceforSimulation", "Do Space Heat Balance for Simulation"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ZoneAirHeatBalanceAlgorithmFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ZoneAirHeatBalanceAlgorithmFields> OptionalOS_ZoneAirHeatBalanceAlgorithmFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ZONEAIRHEATBALANCEALGORITHM_FIELDENUMS_HXX
