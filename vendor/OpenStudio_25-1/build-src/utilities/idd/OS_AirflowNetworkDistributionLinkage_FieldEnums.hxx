/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AIRFLOWNETWORKDISTRIBUTIONLINKAGE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRFLOWNETWORKDISTRIBUTIONLINKAGE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirflowNetworkDistributionLinkageFields
 *  \brief Enumeration of OS:AirflowNetworkDistributionLinkage's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirflowNetworkDistributionLinkageFields, )
#else
class OS_AirflowNetworkDistributionLinkageFields: public ::EnumBase<OS_AirflowNetworkDistributionLinkageFields> {
 public: 
  enum domain 
  {
Handle, Name, Node1Name, Node2Name, ComponentName, ThermalZoneName,   };
  OS_AirflowNetworkDistributionLinkageFields()
   : EnumBase<OS_AirflowNetworkDistributionLinkageFields>(Handle) {} 
  OS_AirflowNetworkDistributionLinkageFields(const std::string &t_name) 
   : EnumBase<OS_AirflowNetworkDistributionLinkageFields>(t_name) {} 
  OS_AirflowNetworkDistributionLinkageFields(int t_value) 
   : EnumBase<OS_AirflowNetworkDistributionLinkageFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirflowNetworkDistributionLinkageFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirflowNetworkDistributionLinkageFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirflowNetworkDistributionLinkageFields>;
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
{ OS_AirflowNetworkDistributionLinkageFields::Handle, "Handle", "Handle"},
{ OS_AirflowNetworkDistributionLinkageFields::Name, "Name", "Name"},
{ OS_AirflowNetworkDistributionLinkageFields::Node1Name, "Node1Name", "Node 1 Name"},
{ OS_AirflowNetworkDistributionLinkageFields::Node2Name, "Node2Name", "Node 2 Name"},
{ OS_AirflowNetworkDistributionLinkageFields::ComponentName, "ComponentName", "Component Name"},
{ OS_AirflowNetworkDistributionLinkageFields::ThermalZoneName, "ThermalZoneName", "Thermal Zone Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirflowNetworkDistributionLinkageFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirflowNetworkDistributionLinkageFields> OptionalOS_AirflowNetworkDistributionLinkageFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRFLOWNETWORKDISTRIBUTIONLINKAGE_FIELDENUMS_HXX
