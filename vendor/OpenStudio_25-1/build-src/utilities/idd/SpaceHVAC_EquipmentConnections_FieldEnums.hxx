/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_SPACEHVAC_EQUIPMENTCONNECTIONS_FIELDENUMS_HXX
#define UTILITIES_IDD_SPACEHVAC_EQUIPMENTCONNECTIONS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SpaceHVAC_EquipmentConnectionsFields
 *  \brief Enumeration of SpaceHVAC:EquipmentConnections's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SpaceHVAC_EquipmentConnectionsFields, )
#else
class SpaceHVAC_EquipmentConnectionsFields: public ::EnumBase<SpaceHVAC_EquipmentConnectionsFields> {
 public: 
  enum domain 
  {
SpaceName, SpaceAirInletNodeorNodeListName, SpaceAirExhaustNodeorNodeListName, SpaceAirNodeName, SpaceReturnAirNodeorNodeListName, SpaceReturnAirNode1FlowRateFractionScheduleName, SpaceReturnAirNode1FlowRateBasisNodeorNodeListName,   };
  SpaceHVAC_EquipmentConnectionsFields()
   : EnumBase<SpaceHVAC_EquipmentConnectionsFields>(SpaceName) {} 
  SpaceHVAC_EquipmentConnectionsFields(const std::string &t_name) 
   : EnumBase<SpaceHVAC_EquipmentConnectionsFields>(t_name) {} 
  SpaceHVAC_EquipmentConnectionsFields(int t_value) 
   : EnumBase<SpaceHVAC_EquipmentConnectionsFields>(t_value) {} 
  static std::string enumName() 
  { return "SpaceHVAC_EquipmentConnectionsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SpaceHVAC_EquipmentConnectionsFields>::integer_value()); }
   private:
    friend class EnumBase<SpaceHVAC_EquipmentConnectionsFields>;
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
{ SpaceHVAC_EquipmentConnectionsFields::SpaceName, "SpaceName", "Space Name"},
{ SpaceHVAC_EquipmentConnectionsFields::SpaceAirInletNodeorNodeListName, "SpaceAirInletNodeorNodeListName", "Space Air Inlet Node or NodeList Name"},
{ SpaceHVAC_EquipmentConnectionsFields::SpaceAirExhaustNodeorNodeListName, "SpaceAirExhaustNodeorNodeListName", "Space Air Exhaust Node or NodeList Name"},
{ SpaceHVAC_EquipmentConnectionsFields::SpaceAirNodeName, "SpaceAirNodeName", "Space Air Node Name"},
{ SpaceHVAC_EquipmentConnectionsFields::SpaceReturnAirNodeorNodeListName, "SpaceReturnAirNodeorNodeListName", "Space Return Air Node or NodeList Name"},
{ SpaceHVAC_EquipmentConnectionsFields::SpaceReturnAirNode1FlowRateFractionScheduleName, "SpaceReturnAirNode1FlowRateFractionScheduleName", "Space Return Air Node 1 Flow Rate Fraction Schedule Name"},
{ SpaceHVAC_EquipmentConnectionsFields::SpaceReturnAirNode1FlowRateBasisNodeorNodeListName, "SpaceReturnAirNode1FlowRateBasisNodeorNodeListName", "Space Return Air Node 1 Flow Rate Basis Node or NodeList Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SpaceHVAC_EquipmentConnectionsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SpaceHVAC_EquipmentConnectionsFields> OptionalSpaceHVAC_EquipmentConnectionsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SPACEHVAC_EQUIPMENTCONNECTIONS_FIELDENUMS_HXX
