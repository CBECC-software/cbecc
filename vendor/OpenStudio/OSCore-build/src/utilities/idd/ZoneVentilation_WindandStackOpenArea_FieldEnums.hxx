/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef UTILITIES_IDD_ZONEVENTILATION_WINDANDSTACKOPENAREA_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEVENTILATION_WINDANDSTACKOPENAREA_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneVentilation_WindandStackOpenAreaFields
 *  \brief Enumeration of ZoneVentilation:WindandStackOpenArea's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneVentilation_WindandStackOpenAreaFields, )
#else
class ZoneVentilation_WindandStackOpenAreaFields: public ::EnumBase<ZoneVentilation_WindandStackOpenAreaFields> {
 public: 
  enum domain 
  {
Name, ZoneName, OpeningArea, OpeningAreaFractionScheduleName, OpeningEffectiveness, EffectiveAngle, HeightDifference, DischargeCoefficientforOpening, MinimumIndoorTemperature, MinimumIndoorTemperatureScheduleName, MaximumIndoorTemperature, MaximumIndoorTemperatureScheduleName, DeltaTemperature, DeltaTemperatureScheduleName, MinimumOutdoorTemperature, MinimumOutdoorTemperatureScheduleName, MaximumOutdoorTemperature, MaximumOutdoorTemperatureScheduleName, MaximumWindSpeed,   };
  ZoneVentilation_WindandStackOpenAreaFields()
   : EnumBase<ZoneVentilation_WindandStackOpenAreaFields>(Name) {} 
  ZoneVentilation_WindandStackOpenAreaFields(const std::string &t_name) 
   : EnumBase<ZoneVentilation_WindandStackOpenAreaFields>(t_name) {} 
  ZoneVentilation_WindandStackOpenAreaFields(int t_value) 
   : EnumBase<ZoneVentilation_WindandStackOpenAreaFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneVentilation_WindandStackOpenAreaFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneVentilation_WindandStackOpenAreaFields>::value()); }
   private:
    friend class EnumBase<ZoneVentilation_WindandStackOpenAreaFields>;
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
{ ZoneVentilation_WindandStackOpenAreaFields::Name, "Name", "Name"},
{ ZoneVentilation_WindandStackOpenAreaFields::ZoneName, "ZoneName", "Zone Name"},
{ ZoneVentilation_WindandStackOpenAreaFields::OpeningArea, "OpeningArea", "Opening Area"},
{ ZoneVentilation_WindandStackOpenAreaFields::OpeningAreaFractionScheduleName, "OpeningAreaFractionScheduleName", "Opening Area Fraction Schedule Name"},
{ ZoneVentilation_WindandStackOpenAreaFields::OpeningEffectiveness, "OpeningEffectiveness", "Opening Effectiveness"},
{ ZoneVentilation_WindandStackOpenAreaFields::EffectiveAngle, "EffectiveAngle", "Effective Angle"},
{ ZoneVentilation_WindandStackOpenAreaFields::HeightDifference, "HeightDifference", "Height Difference"},
{ ZoneVentilation_WindandStackOpenAreaFields::DischargeCoefficientforOpening, "DischargeCoefficientforOpening", "Discharge Coefficient for Opening"},
{ ZoneVentilation_WindandStackOpenAreaFields::MinimumIndoorTemperature, "MinimumIndoorTemperature", "Minimum Indoor Temperature"},
{ ZoneVentilation_WindandStackOpenAreaFields::MinimumIndoorTemperatureScheduleName, "MinimumIndoorTemperatureScheduleName", "Minimum Indoor Temperature Schedule Name"},
{ ZoneVentilation_WindandStackOpenAreaFields::MaximumIndoorTemperature, "MaximumIndoorTemperature", "Maximum Indoor Temperature"},
{ ZoneVentilation_WindandStackOpenAreaFields::MaximumIndoorTemperatureScheduleName, "MaximumIndoorTemperatureScheduleName", "Maximum Indoor Temperature Schedule Name"},
{ ZoneVentilation_WindandStackOpenAreaFields::DeltaTemperature, "DeltaTemperature", "Delta Temperature"},
{ ZoneVentilation_WindandStackOpenAreaFields::DeltaTemperatureScheduleName, "DeltaTemperatureScheduleName", "Delta Temperature Schedule Name"},
{ ZoneVentilation_WindandStackOpenAreaFields::MinimumOutdoorTemperature, "MinimumOutdoorTemperature", "Minimum Outdoor Temperature"},
{ ZoneVentilation_WindandStackOpenAreaFields::MinimumOutdoorTemperatureScheduleName, "MinimumOutdoorTemperatureScheduleName", "Minimum Outdoor Temperature Schedule Name"},
{ ZoneVentilation_WindandStackOpenAreaFields::MaximumOutdoorTemperature, "MaximumOutdoorTemperature", "Maximum Outdoor Temperature"},
{ ZoneVentilation_WindandStackOpenAreaFields::MaximumOutdoorTemperatureScheduleName, "MaximumOutdoorTemperatureScheduleName", "Maximum Outdoor Temperature Schedule Name"},
{ ZoneVentilation_WindandStackOpenAreaFields::MaximumWindSpeed, "MaximumWindSpeed", "Maximum Wind Speed"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneVentilation_WindandStackOpenAreaFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneVentilation_WindandStackOpenAreaFields> OptionalZoneVentilation_WindandStackOpenAreaFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEVENTILATION_WINDANDSTACKOPENAREA_FIELDENUMS_HXX
