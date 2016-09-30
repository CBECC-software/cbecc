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

#ifndef UTILITIES_IDD_UNITARYSYSTEMPERFORMANCE_MULTISPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_UNITARYSYSTEMPERFORMANCE_MULTISPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class UnitarySystemPerformance_MultispeedFields
 *  \brief Enumeration of UnitarySystemPerformance:Multispeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(UnitarySystemPerformance_MultispeedFields, )
#else
class UnitarySystemPerformance_MultispeedFields: public ::EnumBase<UnitarySystemPerformance_MultispeedFields> {
 public: 
  enum domain 
  {
Name, NumberofSpeedsforHeating, NumberofSpeedsforCooling, SingleModeOperation,   };
  UnitarySystemPerformance_MultispeedFields()
   : EnumBase<UnitarySystemPerformance_MultispeedFields>(Name) {} 
  UnitarySystemPerformance_MultispeedFields(const std::string &t_name) 
   : EnumBase<UnitarySystemPerformance_MultispeedFields>(t_name) {} 
  UnitarySystemPerformance_MultispeedFields(int t_value) 
   : EnumBase<UnitarySystemPerformance_MultispeedFields>(t_value) {} 
  static std::string enumName() 
  { return "UnitarySystemPerformance_MultispeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<UnitarySystemPerformance_MultispeedFields>::value()); }
   private:
    friend class EnumBase<UnitarySystemPerformance_MultispeedFields>;
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
{ UnitarySystemPerformance_MultispeedFields::Name, "Name", "Name"},
{ UnitarySystemPerformance_MultispeedFields::NumberofSpeedsforHeating, "NumberofSpeedsforHeating", "Number of Speeds for Heating"},
{ UnitarySystemPerformance_MultispeedFields::NumberofSpeedsforCooling, "NumberofSpeedsforCooling", "Number of Speeds for Cooling"},
{ UnitarySystemPerformance_MultispeedFields::SingleModeOperation, "SingleModeOperation", "Single Mode Operation"},
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
  inline std::ostream &operator<<(std::ostream &os, const UnitarySystemPerformance_MultispeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<UnitarySystemPerformance_MultispeedFields> OptionalUnitarySystemPerformance_MultispeedFields ;
#endif

/** \class UnitarySystemPerformance_MultispeedExtensibleFields
 *  \brief Enumeration of UnitarySystemPerformance:Multispeed's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(UnitarySystemPerformance_MultispeedExtensibleFields, )
#else
class UnitarySystemPerformance_MultispeedExtensibleFields: public ::EnumBase<UnitarySystemPerformance_MultispeedExtensibleFields> {
 public: 
  enum domain 
  {
HeatingSpeedSupplyAirFlowRatio, CoolingSpeedSupplyAirFlowRatio,   };
  UnitarySystemPerformance_MultispeedExtensibleFields()
   : EnumBase<UnitarySystemPerformance_MultispeedExtensibleFields>(HeatingSpeedSupplyAirFlowRatio) {} 
  UnitarySystemPerformance_MultispeedExtensibleFields(const std::string &t_name) 
   : EnumBase<UnitarySystemPerformance_MultispeedExtensibleFields>(t_name) {} 
  UnitarySystemPerformance_MultispeedExtensibleFields(int t_value) 
   : EnumBase<UnitarySystemPerformance_MultispeedExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "UnitarySystemPerformance_MultispeedExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<UnitarySystemPerformance_MultispeedExtensibleFields>::value()); }
   private:
    friend class EnumBase<UnitarySystemPerformance_MultispeedExtensibleFields>;
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
{ UnitarySystemPerformance_MultispeedExtensibleFields::HeatingSpeedSupplyAirFlowRatio, "HeatingSpeedSupplyAirFlowRatio", "Heating Speed Supply Air Flow Ratio"},
{ UnitarySystemPerformance_MultispeedExtensibleFields::CoolingSpeedSupplyAirFlowRatio, "CoolingSpeedSupplyAirFlowRatio", "Cooling Speed Supply Air Flow Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const UnitarySystemPerformance_MultispeedExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<UnitarySystemPerformance_MultispeedExtensibleFields> OptionalUnitarySystemPerformance_MultispeedExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_UNITARYSYSTEMPERFORMANCE_MULTISPEED_FIELDENUMS_HXX
