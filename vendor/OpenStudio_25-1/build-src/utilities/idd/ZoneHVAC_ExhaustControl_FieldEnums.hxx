/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_ZONEHVAC_EXHAUSTCONTROL_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_EXHAUSTCONTROL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_ExhaustControlFields
 *  \brief Enumeration of ZoneHVAC:ExhaustControl's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_ExhaustControlFields, )
#else
class ZoneHVAC_ExhaustControlFields: public ::EnumBase<ZoneHVAC_ExhaustControlFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, ZoneName, InletNodeName, OutletNodeName, DesignExhaustFlowRate, FlowControlType, ExhaustFlowFractionScheduleName, SupplyNodeorNodeListName, MinimumZoneTemperatureLimitScheduleName, MinimumExhaustFlowFractionScheduleName, BalancedExhaustFractionScheduleName,   };
  ZoneHVAC_ExhaustControlFields()
   : EnumBase<ZoneHVAC_ExhaustControlFields>(Name) {} 
  ZoneHVAC_ExhaustControlFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_ExhaustControlFields>(t_name) {} 
  ZoneHVAC_ExhaustControlFields(int t_value) 
   : EnumBase<ZoneHVAC_ExhaustControlFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_ExhaustControlFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_ExhaustControlFields>::integer_value()); }
   private:
    friend class EnumBase<ZoneHVAC_ExhaustControlFields>;
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
{ ZoneHVAC_ExhaustControlFields::Name, "Name", "Name"},
{ ZoneHVAC_ExhaustControlFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_ExhaustControlFields::ZoneName, "ZoneName", "Zone Name"},
{ ZoneHVAC_ExhaustControlFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ ZoneHVAC_ExhaustControlFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ ZoneHVAC_ExhaustControlFields::DesignExhaustFlowRate, "DesignExhaustFlowRate", "Design Exhaust Flow Rate"},
{ ZoneHVAC_ExhaustControlFields::FlowControlType, "FlowControlType", "Flow Control Type"},
{ ZoneHVAC_ExhaustControlFields::ExhaustFlowFractionScheduleName, "ExhaustFlowFractionScheduleName", "Exhaust Flow Fraction Schedule Name"},
{ ZoneHVAC_ExhaustControlFields::SupplyNodeorNodeListName, "SupplyNodeorNodeListName", "Supply Node or NodeList Name"},
{ ZoneHVAC_ExhaustControlFields::MinimumZoneTemperatureLimitScheduleName, "MinimumZoneTemperatureLimitScheduleName", "Minimum Zone Temperature Limit Schedule Name"},
{ ZoneHVAC_ExhaustControlFields::MinimumExhaustFlowFractionScheduleName, "MinimumExhaustFlowFractionScheduleName", "Minimum Exhaust Flow Fraction Schedule Name"},
{ ZoneHVAC_ExhaustControlFields::BalancedExhaustFractionScheduleName, "BalancedExhaustFractionScheduleName", "Balanced Exhaust Fraction Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_ExhaustControlFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_ExhaustControlFields> OptionalZoneHVAC_ExhaustControlFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_EXHAUSTCONTROL_FIELDENUMS_HXX
