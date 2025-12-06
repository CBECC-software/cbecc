/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_DESIGNSPECIFICATION_AIRTERMINAL_SIZING_FIELDENUMS_HXX
#define UTILITIES_IDD_DESIGNSPECIFICATION_AIRTERMINAL_SIZING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class DesignSpecification_AirTerminal_SizingFields
 *  \brief Enumeration of DesignSpecification:AirTerminal:Sizing's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(DesignSpecification_AirTerminal_SizingFields, )
#else
class DesignSpecification_AirTerminal_SizingFields: public ::EnumBase<DesignSpecification_AirTerminal_SizingFields> {
 public: 
  enum domain 
  {
Name, FractionofDesignCoolingLoad, CoolingDesignSupplyAirTemperatureDifferenceRatio, FractionofDesignHeatingLoad, HeatingDesignSupplyAirTemperatureDifferenceRatio, FractionofMinimumOutdoorAirFlow,   };
  DesignSpecification_AirTerminal_SizingFields()
   : EnumBase<DesignSpecification_AirTerminal_SizingFields>(Name) {} 
  DesignSpecification_AirTerminal_SizingFields(const std::string &t_name) 
   : EnumBase<DesignSpecification_AirTerminal_SizingFields>(t_name) {} 
  DesignSpecification_AirTerminal_SizingFields(int t_value) 
   : EnumBase<DesignSpecification_AirTerminal_SizingFields>(t_value) {} 
  static std::string enumName() 
  { return "DesignSpecification_AirTerminal_SizingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DesignSpecification_AirTerminal_SizingFields>::integer_value()); }
   private:
    friend class EnumBase<DesignSpecification_AirTerminal_SizingFields>;
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
{ DesignSpecification_AirTerminal_SizingFields::Name, "Name", "Name"},
{ DesignSpecification_AirTerminal_SizingFields::FractionofDesignCoolingLoad, "FractionofDesignCoolingLoad", "Fraction of Design Cooling Load"},
{ DesignSpecification_AirTerminal_SizingFields::CoolingDesignSupplyAirTemperatureDifferenceRatio, "CoolingDesignSupplyAirTemperatureDifferenceRatio", "Cooling Design Supply Air Temperature Difference Ratio"},
{ DesignSpecification_AirTerminal_SizingFields::FractionofDesignHeatingLoad, "FractionofDesignHeatingLoad", "Fraction of Design Heating Load"},
{ DesignSpecification_AirTerminal_SizingFields::HeatingDesignSupplyAirTemperatureDifferenceRatio, "HeatingDesignSupplyAirTemperatureDifferenceRatio", "Heating Design Supply Air Temperature Difference Ratio"},
{ DesignSpecification_AirTerminal_SizingFields::FractionofMinimumOutdoorAirFlow, "FractionofMinimumOutdoorAirFlow", "Fraction of Minimum Outdoor Air Flow"},
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
  inline std::ostream &operator<<(std::ostream &os, const DesignSpecification_AirTerminal_SizingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DesignSpecification_AirTerminal_SizingFields> OptionalDesignSpecification_AirTerminal_SizingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_DESIGNSPECIFICATION_AIRTERMINAL_SIZING_FIELDENUMS_HXX
