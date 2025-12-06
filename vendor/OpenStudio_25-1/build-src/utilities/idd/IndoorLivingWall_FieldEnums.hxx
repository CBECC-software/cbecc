/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_INDOORLIVINGWALL_FIELDENUMS_HXX
#define UTILITIES_IDD_INDOORLIVINGWALL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class IndoorLivingWallFields
 *  \brief Enumeration of IndoorLivingWall's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(IndoorLivingWallFields, )
#else
class IndoorLivingWallFields: public ::EnumBase<IndoorLivingWallFields> {
 public: 
  enum domain 
  {
Name, SurfaceName, ScheduleName, EvapotranspirationCalculationMethod, LightingMethod, LEDIntensityScheduleName, DaylightingControlName, LEDDaylightTargetedLightingIntensityScheduleName, TotalLeafArea, LEDNominalIntensity, LEDNominalPower, RadiantFractionofLEDLights,   };
  IndoorLivingWallFields()
   : EnumBase<IndoorLivingWallFields>(Name) {} 
  IndoorLivingWallFields(const std::string &t_name) 
   : EnumBase<IndoorLivingWallFields>(t_name) {} 
  IndoorLivingWallFields(int t_value) 
   : EnumBase<IndoorLivingWallFields>(t_value) {} 
  static std::string enumName() 
  { return "IndoorLivingWallFields"; }
  domain value() const { return static_cast<domain>(EnumBase<IndoorLivingWallFields>::integer_value()); }
   private:
    friend class EnumBase<IndoorLivingWallFields>;
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
{ IndoorLivingWallFields::Name, "Name", "Name"},
{ IndoorLivingWallFields::SurfaceName, "SurfaceName", "Surface Name"},
{ IndoorLivingWallFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ IndoorLivingWallFields::EvapotranspirationCalculationMethod, "EvapotranspirationCalculationMethod", "Evapotranspiration Calculation Method"},
{ IndoorLivingWallFields::LightingMethod, "LightingMethod", "Lighting Method"},
{ IndoorLivingWallFields::LEDIntensityScheduleName, "LEDIntensityScheduleName", "LED Intensity Schedule Name"},
{ IndoorLivingWallFields::DaylightingControlName, "DaylightingControlName", "Daylighting Control Name"},
{ IndoorLivingWallFields::LEDDaylightTargetedLightingIntensityScheduleName, "LEDDaylightTargetedLightingIntensityScheduleName", "LED-Daylight Targeted Lighting Intensity Schedule Name"},
{ IndoorLivingWallFields::TotalLeafArea, "TotalLeafArea", "Total Leaf Area"},
{ IndoorLivingWallFields::LEDNominalIntensity, "LEDNominalIntensity", "LED Nominal Intensity"},
{ IndoorLivingWallFields::LEDNominalPower, "LEDNominalPower", "LED Nominal Power"},
{ IndoorLivingWallFields::RadiantFractionofLEDLights, "RadiantFractionofLEDLights", "Radiant Fraction of LED Lights"},
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
  inline std::ostream &operator<<(std::ostream &os, const IndoorLivingWallFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<IndoorLivingWallFields> OptionalIndoorLivingWallFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_INDOORLIVINGWALL_FIELDENUMS_HXX
