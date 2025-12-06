/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AIRFLOWNETWORKDISTRIBUTIONNODE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRFLOWNETWORKDISTRIBUTIONNODE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirflowNetworkDistributionNodeFields
 *  \brief Enumeration of OS:AirflowNetworkDistributionNode's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirflowNetworkDistributionNodeFields, )
#else
class OS_AirflowNetworkDistributionNodeFields: public ::EnumBase<OS_AirflowNetworkDistributionNodeFields> {
 public: 
  enum domain 
  {
Handle, Name, ComponentNameorNodeName, NodeHeight,   };
  OS_AirflowNetworkDistributionNodeFields()
   : EnumBase<OS_AirflowNetworkDistributionNodeFields>(Handle) {} 
  OS_AirflowNetworkDistributionNodeFields(const std::string &t_name) 
   : EnumBase<OS_AirflowNetworkDistributionNodeFields>(t_name) {} 
  OS_AirflowNetworkDistributionNodeFields(int t_value) 
   : EnumBase<OS_AirflowNetworkDistributionNodeFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirflowNetworkDistributionNodeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirflowNetworkDistributionNodeFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirflowNetworkDistributionNodeFields>;
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
{ OS_AirflowNetworkDistributionNodeFields::Handle, "Handle", "Handle"},
{ OS_AirflowNetworkDistributionNodeFields::Name, "Name", "Name"},
{ OS_AirflowNetworkDistributionNodeFields::ComponentNameorNodeName, "ComponentNameorNodeName", "Component Name or Node Name"},
{ OS_AirflowNetworkDistributionNodeFields::NodeHeight, "NodeHeight", "Node Height"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirflowNetworkDistributionNodeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirflowNetworkDistributionNodeFields> OptionalOS_AirflowNetworkDistributionNodeFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRFLOWNETWORKDISTRIBUTIONNODE_FIELDENUMS_HXX
