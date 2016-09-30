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

#ifndef UTILITIES_IDD_ZONEINFILTRATION_FLOWCOEFFICIENT_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEINFILTRATION_FLOWCOEFFICIENT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneInfiltration_FlowCoefficientFields
 *  \brief Enumeration of ZoneInfiltration:FlowCoefficient's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneInfiltration_FlowCoefficientFields, )
#else
class ZoneInfiltration_FlowCoefficientFields: public ::EnumBase<ZoneInfiltration_FlowCoefficientFields> {
 public: 
  enum domain 
  {
Name, ZoneName, ScheduleName, FlowCoefficient, StackCoefficient, PressureExponent, WindCoefficient, ShelterFactor,   };
  ZoneInfiltration_FlowCoefficientFields()
   : EnumBase<ZoneInfiltration_FlowCoefficientFields>(Name) {} 
  ZoneInfiltration_FlowCoefficientFields(const std::string &t_name) 
   : EnumBase<ZoneInfiltration_FlowCoefficientFields>(t_name) {} 
  ZoneInfiltration_FlowCoefficientFields(int t_value) 
   : EnumBase<ZoneInfiltration_FlowCoefficientFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneInfiltration_FlowCoefficientFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneInfiltration_FlowCoefficientFields>::value()); }
   private:
    friend class EnumBase<ZoneInfiltration_FlowCoefficientFields>;
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
{ ZoneInfiltration_FlowCoefficientFields::Name, "Name", "Name"},
{ ZoneInfiltration_FlowCoefficientFields::ZoneName, "ZoneName", "Zone Name"},
{ ZoneInfiltration_FlowCoefficientFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ ZoneInfiltration_FlowCoefficientFields::FlowCoefficient, "FlowCoefficient", "Flow Coefficient"},
{ ZoneInfiltration_FlowCoefficientFields::StackCoefficient, "StackCoefficient", "Stack Coefficient"},
{ ZoneInfiltration_FlowCoefficientFields::PressureExponent, "PressureExponent", "Pressure Exponent"},
{ ZoneInfiltration_FlowCoefficientFields::WindCoefficient, "WindCoefficient", "Wind Coefficient"},
{ ZoneInfiltration_FlowCoefficientFields::ShelterFactor, "ShelterFactor", "Shelter Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneInfiltration_FlowCoefficientFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneInfiltration_FlowCoefficientFields> OptionalZoneInfiltration_FlowCoefficientFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEINFILTRATION_FLOWCOEFFICIENT_FIELDENUMS_HXX
