/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AIRFLOWNETWORKOUTDOORAIRFLOW_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRFLOWNETWORKOUTDOORAIRFLOW_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirflowNetworkOutdoorAirflowFields
 *  \brief Enumeration of OS:AirflowNetworkOutdoorAirflow's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirflowNetworkOutdoorAirflowFields, )
#else
class OS_AirflowNetworkOutdoorAirflowFields: public ::EnumBase<OS_AirflowNetworkOutdoorAirflowFields> {
 public: 
  enum domain 
  {
Handle, Name, CrackName,   };
  OS_AirflowNetworkOutdoorAirflowFields()
   : EnumBase<OS_AirflowNetworkOutdoorAirflowFields>(Handle) {} 
  OS_AirflowNetworkOutdoorAirflowFields(const std::string &t_name) 
   : EnumBase<OS_AirflowNetworkOutdoorAirflowFields>(t_name) {} 
  OS_AirflowNetworkOutdoorAirflowFields(int t_value) 
   : EnumBase<OS_AirflowNetworkOutdoorAirflowFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirflowNetworkOutdoorAirflowFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirflowNetworkOutdoorAirflowFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirflowNetworkOutdoorAirflowFields>;
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
{ OS_AirflowNetworkOutdoorAirflowFields::Handle, "Handle", "Handle"},
{ OS_AirflowNetworkOutdoorAirflowFields::Name, "Name", "Name"},
{ OS_AirflowNetworkOutdoorAirflowFields::CrackName, "CrackName", "Crack Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirflowNetworkOutdoorAirflowFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirflowNetworkOutdoorAirflowFields> OptionalOS_AirflowNetworkOutdoorAirflowFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRFLOWNETWORKOUTDOORAIRFLOW_FIELDENUMS_HXX
