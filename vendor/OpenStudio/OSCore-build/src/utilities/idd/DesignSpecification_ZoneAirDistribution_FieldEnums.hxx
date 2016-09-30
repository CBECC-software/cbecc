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

#ifndef UTILITIES_IDD_DESIGNSPECIFICATION_ZONEAIRDISTRIBUTION_FIELDENUMS_HXX
#define UTILITIES_IDD_DESIGNSPECIFICATION_ZONEAIRDISTRIBUTION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class DesignSpecification_ZoneAirDistributionFields
 *  \brief Enumeration of DesignSpecification:ZoneAirDistribution's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(DesignSpecification_ZoneAirDistributionFields, )
#else
class DesignSpecification_ZoneAirDistributionFields: public ::EnumBase<DesignSpecification_ZoneAirDistributionFields> {
 public: 
  enum domain 
  {
Name, ZoneAirDistributionEffectivenessinCoolingMode, ZoneAirDistributionEffectivenessinHeatingMode, ZoneAirDistributionEffectivenessScheduleName, ZoneSecondaryRecirculationFraction,   };
  DesignSpecification_ZoneAirDistributionFields()
   : EnumBase<DesignSpecification_ZoneAirDistributionFields>(Name) {} 
  DesignSpecification_ZoneAirDistributionFields(const std::string &t_name) 
   : EnumBase<DesignSpecification_ZoneAirDistributionFields>(t_name) {} 
  DesignSpecification_ZoneAirDistributionFields(int t_value) 
   : EnumBase<DesignSpecification_ZoneAirDistributionFields>(t_value) {} 
  static std::string enumName() 
  { return "DesignSpecification_ZoneAirDistributionFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DesignSpecification_ZoneAirDistributionFields>::value()); }
   private:
    friend class EnumBase<DesignSpecification_ZoneAirDistributionFields>;
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
{ DesignSpecification_ZoneAirDistributionFields::Name, "Name", "Name"},
{ DesignSpecification_ZoneAirDistributionFields::ZoneAirDistributionEffectivenessinCoolingMode, "ZoneAirDistributionEffectivenessinCoolingMode", "Zone Air Distribution Effectiveness in Cooling Mode"},
{ DesignSpecification_ZoneAirDistributionFields::ZoneAirDistributionEffectivenessinHeatingMode, "ZoneAirDistributionEffectivenessinHeatingMode", "Zone Air Distribution Effectiveness in Heating Mode"},
{ DesignSpecification_ZoneAirDistributionFields::ZoneAirDistributionEffectivenessScheduleName, "ZoneAirDistributionEffectivenessScheduleName", "Zone Air Distribution Effectiveness Schedule Name"},
{ DesignSpecification_ZoneAirDistributionFields::ZoneSecondaryRecirculationFraction, "ZoneSecondaryRecirculationFraction", "Zone Secondary Recirculation Fraction"},
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
  inline std::ostream &operator<<(std::ostream &os, const DesignSpecification_ZoneAirDistributionFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DesignSpecification_ZoneAirDistributionFields> OptionalDesignSpecification_ZoneAirDistributionFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_DESIGNSPECIFICATION_ZONEAIRDISTRIBUTION_FIELDENUMS_HXX
