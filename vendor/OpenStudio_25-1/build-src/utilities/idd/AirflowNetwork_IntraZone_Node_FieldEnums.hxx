/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_AIRFLOWNETWORK_INTRAZONE_NODE_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRFLOWNETWORK_INTRAZONE_NODE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirflowNetwork_IntraZone_NodeFields
 *  \brief Enumeration of AirflowNetwork:IntraZone:Node's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirflowNetwork_IntraZone_NodeFields, )
#else
class AirflowNetwork_IntraZone_NodeFields: public ::EnumBase<AirflowNetwork_IntraZone_NodeFields> {
 public: 
  enum domain 
  {
Name, RoomAir_Node_AirflowNetworkName, ZoneName, NodeHeight,   };
  AirflowNetwork_IntraZone_NodeFields()
   : EnumBase<AirflowNetwork_IntraZone_NodeFields>(Name) {} 
  AirflowNetwork_IntraZone_NodeFields(const std::string &t_name) 
   : EnumBase<AirflowNetwork_IntraZone_NodeFields>(t_name) {} 
  AirflowNetwork_IntraZone_NodeFields(int t_value) 
   : EnumBase<AirflowNetwork_IntraZone_NodeFields>(t_value) {} 
  static std::string enumName() 
  { return "AirflowNetwork_IntraZone_NodeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirflowNetwork_IntraZone_NodeFields>::integer_value()); }
   private:
    friend class EnumBase<AirflowNetwork_IntraZone_NodeFields>;
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
{ AirflowNetwork_IntraZone_NodeFields::Name, "Name", "Name"},
{ AirflowNetwork_IntraZone_NodeFields::RoomAir_Node_AirflowNetworkName, "RoomAir_Node_AirflowNetworkName", "RoomAir:Node:AirflowNetwork Name"},
{ AirflowNetwork_IntraZone_NodeFields::ZoneName, "ZoneName", "Zone Name"},
{ AirflowNetwork_IntraZone_NodeFields::NodeHeight, "NodeHeight", "Node Height"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirflowNetwork_IntraZone_NodeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirflowNetwork_IntraZone_NodeFields> OptionalAirflowNetwork_IntraZone_NodeFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRFLOWNETWORK_INTRAZONE_NODE_FIELDENUMS_HXX
