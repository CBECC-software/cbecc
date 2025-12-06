/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AIRFLOWNETWORKSPECIFIEDFLOWRATE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRFLOWNETWORKSPECIFIEDFLOWRATE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirflowNetworkSpecifiedFlowRateFields
 *  \brief Enumeration of OS:AirflowNetworkSpecifiedFlowRate's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirflowNetworkSpecifiedFlowRateFields, )
#else
class OS_AirflowNetworkSpecifiedFlowRateFields: public ::EnumBase<OS_AirflowNetworkSpecifiedFlowRateFields> {
 public: 
  enum domain 
  {
Handle, Name, AirFlowValue, AirFlowUnits,   };
  OS_AirflowNetworkSpecifiedFlowRateFields()
   : EnumBase<OS_AirflowNetworkSpecifiedFlowRateFields>(Handle) {} 
  OS_AirflowNetworkSpecifiedFlowRateFields(const std::string &t_name) 
   : EnumBase<OS_AirflowNetworkSpecifiedFlowRateFields>(t_name) {} 
  OS_AirflowNetworkSpecifiedFlowRateFields(int t_value) 
   : EnumBase<OS_AirflowNetworkSpecifiedFlowRateFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirflowNetworkSpecifiedFlowRateFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirflowNetworkSpecifiedFlowRateFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirflowNetworkSpecifiedFlowRateFields>;
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
{ OS_AirflowNetworkSpecifiedFlowRateFields::Handle, "Handle", "Handle"},
{ OS_AirflowNetworkSpecifiedFlowRateFields::Name, "Name", "Name"},
{ OS_AirflowNetworkSpecifiedFlowRateFields::AirFlowValue, "AirFlowValue", "Air Flow Value"},
{ OS_AirflowNetworkSpecifiedFlowRateFields::AirFlowUnits, "AirFlowUnits", "Air Flow Units"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirflowNetworkSpecifiedFlowRateFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirflowNetworkSpecifiedFlowRateFields> OptionalOS_AirflowNetworkSpecifiedFlowRateFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRFLOWNETWORKSPECIFIEDFLOWRATE_FIELDENUMS_HXX
