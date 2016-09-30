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

#ifndef UTILITIES_IDD_ZONEINFILTRATION_EFFECTIVELEAKAGEAREA_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEINFILTRATION_EFFECTIVELEAKAGEAREA_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneInfiltration_EffectiveLeakageAreaFields
 *  \brief Enumeration of ZoneInfiltration:EffectiveLeakageArea's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneInfiltration_EffectiveLeakageAreaFields, )
#else
class ZoneInfiltration_EffectiveLeakageAreaFields: public ::EnumBase<ZoneInfiltration_EffectiveLeakageAreaFields> {
 public: 
  enum domain 
  {
Name, ZoneName, ScheduleName, EffectiveAirLeakageArea, StackCoefficient, WindCoefficient,   };
  ZoneInfiltration_EffectiveLeakageAreaFields()
   : EnumBase<ZoneInfiltration_EffectiveLeakageAreaFields>(Name) {} 
  ZoneInfiltration_EffectiveLeakageAreaFields(const std::string &t_name) 
   : EnumBase<ZoneInfiltration_EffectiveLeakageAreaFields>(t_name) {} 
  ZoneInfiltration_EffectiveLeakageAreaFields(int t_value) 
   : EnumBase<ZoneInfiltration_EffectiveLeakageAreaFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneInfiltration_EffectiveLeakageAreaFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneInfiltration_EffectiveLeakageAreaFields>::value()); }
   private:
    friend class EnumBase<ZoneInfiltration_EffectiveLeakageAreaFields>;
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
{ ZoneInfiltration_EffectiveLeakageAreaFields::Name, "Name", "Name"},
{ ZoneInfiltration_EffectiveLeakageAreaFields::ZoneName, "ZoneName", "Zone Name"},
{ ZoneInfiltration_EffectiveLeakageAreaFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ ZoneInfiltration_EffectiveLeakageAreaFields::EffectiveAirLeakageArea, "EffectiveAirLeakageArea", "Effective Air Leakage Area"},
{ ZoneInfiltration_EffectiveLeakageAreaFields::StackCoefficient, "StackCoefficient", "Stack Coefficient"},
{ ZoneInfiltration_EffectiveLeakageAreaFields::WindCoefficient, "WindCoefficient", "Wind Coefficient"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneInfiltration_EffectiveLeakageAreaFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneInfiltration_EffectiveLeakageAreaFields> OptionalZoneInfiltration_EffectiveLeakageAreaFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEINFILTRATION_EFFECTIVELEAKAGEAREA_FIELDENUMS_HXX
