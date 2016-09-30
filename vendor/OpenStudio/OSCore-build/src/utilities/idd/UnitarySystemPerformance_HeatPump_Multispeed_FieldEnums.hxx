/**********************************************************************
*  Copyright (c) 2008-2015, Alliance for Sustainable Energy.
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

#ifndef UTILITIES_IDD_UNITARYSYSTEMPERFORMANCE_HEATPUMP_MULTISPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_UNITARYSYSTEMPERFORMANCE_HEATPUMP_MULTISPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class UnitarySystemPerformance_HeatPump_MultispeedFields
 *  \brief Enumeration of UnitarySystemPerformance:HeatPump:Multispeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(UnitarySystemPerformance_HeatPump_MultispeedFields, )
#else
class UnitarySystemPerformance_HeatPump_MultispeedFields: public ::EnumBase<UnitarySystemPerformance_HeatPump_MultispeedFields> {
 public: 
  enum domain 
  {
Name, NumberofSpeedsforHeating, NumberofSpeedsforCooling,   };
  UnitarySystemPerformance_HeatPump_MultispeedFields()
   : EnumBase<UnitarySystemPerformance_HeatPump_MultispeedFields>(Name) {} 
  UnitarySystemPerformance_HeatPump_MultispeedFields(const std::string &t_name) 
   : EnumBase<UnitarySystemPerformance_HeatPump_MultispeedFields>(t_name) {} 
  UnitarySystemPerformance_HeatPump_MultispeedFields(int t_value) 
   : EnumBase<UnitarySystemPerformance_HeatPump_MultispeedFields>(t_value) {} 
  static std::string enumName() 
  { return "UnitarySystemPerformance_HeatPump_MultispeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<UnitarySystemPerformance_HeatPump_MultispeedFields>::value()); }
   private:
    friend class EnumBase<UnitarySystemPerformance_HeatPump_MultispeedFields>;
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
{ UnitarySystemPerformance_HeatPump_MultispeedFields::Name, "Name", "Name"},
{ UnitarySystemPerformance_HeatPump_MultispeedFields::NumberofSpeedsforHeating, "NumberofSpeedsforHeating", "Number of Speeds for Heating"},
{ UnitarySystemPerformance_HeatPump_MultispeedFields::NumberofSpeedsforCooling, "NumberofSpeedsforCooling", "Number of Speeds for Cooling"},
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
  inline std::ostream &operator<<(std::ostream &os, const UnitarySystemPerformance_HeatPump_MultispeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<UnitarySystemPerformance_HeatPump_MultispeedFields> OptionalUnitarySystemPerformance_HeatPump_MultispeedFields ;
#endif

/** \class UnitarySystemPerformance_HeatPump_MultispeedExtensibleFields
 *  \brief Enumeration of UnitarySystemPerformance:HeatPump:Multispeed's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(UnitarySystemPerformance_HeatPump_MultispeedExtensibleFields, )
#else
class UnitarySystemPerformance_HeatPump_MultispeedExtensibleFields: public ::EnumBase<UnitarySystemPerformance_HeatPump_MultispeedExtensibleFields> {
 public: 
  enum domain 
  {
HeatingSpeedSupplyAirFlowRatio, CoolingSpeedSupplyAirFlowRatio,   };
  UnitarySystemPerformance_HeatPump_MultispeedExtensibleFields()
   : EnumBase<UnitarySystemPerformance_HeatPump_MultispeedExtensibleFields>(HeatingSpeedSupplyAirFlowRatio) {} 
  UnitarySystemPerformance_HeatPump_MultispeedExtensibleFields(const std::string &t_name) 
   : EnumBase<UnitarySystemPerformance_HeatPump_MultispeedExtensibleFields>(t_name) {} 
  UnitarySystemPerformance_HeatPump_MultispeedExtensibleFields(int t_value) 
   : EnumBase<UnitarySystemPerformance_HeatPump_MultispeedExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "UnitarySystemPerformance_HeatPump_MultispeedExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<UnitarySystemPerformance_HeatPump_MultispeedExtensibleFields>::value()); }
   private:
    friend class EnumBase<UnitarySystemPerformance_HeatPump_MultispeedExtensibleFields>;
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
{ UnitarySystemPerformance_HeatPump_MultispeedExtensibleFields::HeatingSpeedSupplyAirFlowRatio, "HeatingSpeedSupplyAirFlowRatio", "Heating Speed Supply Air Flow Ratio"},
{ UnitarySystemPerformance_HeatPump_MultispeedExtensibleFields::CoolingSpeedSupplyAirFlowRatio, "CoolingSpeedSupplyAirFlowRatio", "Cooling Speed Supply Air Flow Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const UnitarySystemPerformance_HeatPump_MultispeedExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<UnitarySystemPerformance_HeatPump_MultispeedExtensibleFields> OptionalUnitarySystemPerformance_HeatPump_MultispeedExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_UNITARYSYSTEMPERFORMANCE_HEATPUMP_MULTISPEED_FIELDENUMS_HXX
