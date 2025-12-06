/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_AIRFLOWNETWORK_DISTRIBUTION_COMPONENT_RELIEFAIRFLOW_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRFLOWNETWORK_DISTRIBUTION_COMPONENT_RELIEFAIRFLOW_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirflowNetwork_Distribution_Component_ReliefAirFlowFields
 *  \brief Enumeration of AirflowNetwork:Distribution:Component:ReliefAirFlow's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirflowNetwork_Distribution_Component_ReliefAirFlowFields, )
#else
class AirflowNetwork_Distribution_Component_ReliefAirFlowFields: public ::EnumBase<AirflowNetwork_Distribution_Component_ReliefAirFlowFields> {
 public: 
  enum domain 
  {
Name, OutdoorAirMixerName, AirMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions, AirMassFlowExponentWhenNoOutdoorAirFlow, ReferenceCrackConditions,   };
  AirflowNetwork_Distribution_Component_ReliefAirFlowFields()
   : EnumBase<AirflowNetwork_Distribution_Component_ReliefAirFlowFields>(Name) {} 
  AirflowNetwork_Distribution_Component_ReliefAirFlowFields(const std::string &t_name) 
   : EnumBase<AirflowNetwork_Distribution_Component_ReliefAirFlowFields>(t_name) {} 
  AirflowNetwork_Distribution_Component_ReliefAirFlowFields(int t_value) 
   : EnumBase<AirflowNetwork_Distribution_Component_ReliefAirFlowFields>(t_value) {} 
  static std::string enumName() 
  { return "AirflowNetwork_Distribution_Component_ReliefAirFlowFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirflowNetwork_Distribution_Component_ReliefAirFlowFields>::integer_value()); }
   private:
    friend class EnumBase<AirflowNetwork_Distribution_Component_ReliefAirFlowFields>;
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
{ AirflowNetwork_Distribution_Component_ReliefAirFlowFields::Name, "Name", "Name"},
{ AirflowNetwork_Distribution_Component_ReliefAirFlowFields::OutdoorAirMixerName, "OutdoorAirMixerName", "Outdoor Air Mixer Name"},
{ AirflowNetwork_Distribution_Component_ReliefAirFlowFields::AirMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions, "AirMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions", "Air Mass Flow Coefficient When No Outdoor Air Flow at Reference Conditions"},
{ AirflowNetwork_Distribution_Component_ReliefAirFlowFields::AirMassFlowExponentWhenNoOutdoorAirFlow, "AirMassFlowExponentWhenNoOutdoorAirFlow", "Air Mass Flow Exponent When No Outdoor Air Flow"},
{ AirflowNetwork_Distribution_Component_ReliefAirFlowFields::ReferenceCrackConditions, "ReferenceCrackConditions", "Reference Crack Conditions"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirflowNetwork_Distribution_Component_ReliefAirFlowFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirflowNetwork_Distribution_Component_ReliefAirFlowFields> OptionalAirflowNetwork_Distribution_Component_ReliefAirFlowFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRFLOWNETWORK_DISTRIBUTION_COMPONENT_RELIEFAIRFLOW_FIELDENUMS_HXX
