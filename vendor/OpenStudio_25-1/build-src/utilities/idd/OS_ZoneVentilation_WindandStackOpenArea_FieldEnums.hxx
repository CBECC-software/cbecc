/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_ZONEVENTILATION_WINDANDSTACKOPENAREA_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ZONEVENTILATION_WINDANDSTACKOPENAREA_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ZoneVentilation_WindandStackOpenAreaFields
 *  \brief Enumeration of OS:ZoneVentilation:WindandStackOpenArea's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ZoneVentilation_WindandStackOpenAreaFields, )
#else
class OS_ZoneVentilation_WindandStackOpenAreaFields: public ::EnumBase<OS_ZoneVentilation_WindandStackOpenAreaFields> {
 public: 
  enum domain 
  {
Handle, Name, OpeningArea, OpeningAreaFractionScheduleName, OpeningEffectiveness, EffectiveAngle, HeightDifference, DischargeCoefficientforOpening, MinimumIndoorTemperature, MinimumIndoorTemperatureScheduleName, MaximumIndoorTemperature, MaximumIndoorTemperatureScheduleName, DeltaTemperature, DeltaTemperatureScheduleName, MinimumOutdoorTemperature, MinimumOutdoorTemperatureScheduleName, MaximumOutdoorTemperature, MaximumOutdoorTemperatureScheduleName, MaximumWindSpeed,   };
  OS_ZoneVentilation_WindandStackOpenAreaFields()
   : EnumBase<OS_ZoneVentilation_WindandStackOpenAreaFields>(Handle) {} 
  OS_ZoneVentilation_WindandStackOpenAreaFields(const std::string &t_name) 
   : EnumBase<OS_ZoneVentilation_WindandStackOpenAreaFields>(t_name) {} 
  OS_ZoneVentilation_WindandStackOpenAreaFields(int t_value) 
   : EnumBase<OS_ZoneVentilation_WindandStackOpenAreaFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ZoneVentilation_WindandStackOpenAreaFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ZoneVentilation_WindandStackOpenAreaFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ZoneVentilation_WindandStackOpenAreaFields>;
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
{ OS_ZoneVentilation_WindandStackOpenAreaFields::Handle, "Handle", "Handle"},
{ OS_ZoneVentilation_WindandStackOpenAreaFields::Name, "Name", "Name"},
{ OS_ZoneVentilation_WindandStackOpenAreaFields::OpeningArea, "OpeningArea", "Opening Area"},
{ OS_ZoneVentilation_WindandStackOpenAreaFields::OpeningAreaFractionScheduleName, "OpeningAreaFractionScheduleName", "Opening Area Fraction Schedule Name"},
{ OS_ZoneVentilation_WindandStackOpenAreaFields::OpeningEffectiveness, "OpeningEffectiveness", "Opening Effectiveness"},
{ OS_ZoneVentilation_WindandStackOpenAreaFields::EffectiveAngle, "EffectiveAngle", "Effective Angle"},
{ OS_ZoneVentilation_WindandStackOpenAreaFields::HeightDifference, "HeightDifference", "Height Difference"},
{ OS_ZoneVentilation_WindandStackOpenAreaFields::DischargeCoefficientforOpening, "DischargeCoefficientforOpening", "Discharge Coefficient for Opening"},
{ OS_ZoneVentilation_WindandStackOpenAreaFields::MinimumIndoorTemperature, "MinimumIndoorTemperature", "Minimum Indoor Temperature"},
{ OS_ZoneVentilation_WindandStackOpenAreaFields::MinimumIndoorTemperatureScheduleName, "MinimumIndoorTemperatureScheduleName", "Minimum Indoor Temperature Schedule Name"},
{ OS_ZoneVentilation_WindandStackOpenAreaFields::MaximumIndoorTemperature, "MaximumIndoorTemperature", "Maximum Indoor Temperature"},
{ OS_ZoneVentilation_WindandStackOpenAreaFields::MaximumIndoorTemperatureScheduleName, "MaximumIndoorTemperatureScheduleName", "Maximum Indoor Temperature Schedule Name"},
{ OS_ZoneVentilation_WindandStackOpenAreaFields::DeltaTemperature, "DeltaTemperature", "Delta Temperature"},
{ OS_ZoneVentilation_WindandStackOpenAreaFields::DeltaTemperatureScheduleName, "DeltaTemperatureScheduleName", "Delta Temperature Schedule Name"},
{ OS_ZoneVentilation_WindandStackOpenAreaFields::MinimumOutdoorTemperature, "MinimumOutdoorTemperature", "Minimum Outdoor Temperature"},
{ OS_ZoneVentilation_WindandStackOpenAreaFields::MinimumOutdoorTemperatureScheduleName, "MinimumOutdoorTemperatureScheduleName", "Minimum Outdoor Temperature Schedule Name"},
{ OS_ZoneVentilation_WindandStackOpenAreaFields::MaximumOutdoorTemperature, "MaximumOutdoorTemperature", "Maximum Outdoor Temperature"},
{ OS_ZoneVentilation_WindandStackOpenAreaFields::MaximumOutdoorTemperatureScheduleName, "MaximumOutdoorTemperatureScheduleName", "Maximum Outdoor Temperature Schedule Name"},
{ OS_ZoneVentilation_WindandStackOpenAreaFields::MaximumWindSpeed, "MaximumWindSpeed", "Maximum Wind Speed"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ZoneVentilation_WindandStackOpenAreaFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ZoneVentilation_WindandStackOpenAreaFields> OptionalOS_ZoneVentilation_WindandStackOpenAreaFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ZONEVENTILATION_WINDANDSTACKOPENAREA_FIELDENUMS_HXX
