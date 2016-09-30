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

#ifndef UTILITIES_IDD_CENTRALHEATPUMPSYSTEM_FIELDENUMS_HXX
#define UTILITIES_IDD_CENTRALHEATPUMPSYSTEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class CentralHeatPumpSystemFields
 *  \brief Enumeration of CentralHeatPumpSystem's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(CentralHeatPumpSystemFields, )
#else
class CentralHeatPumpSystemFields: public ::EnumBase<CentralHeatPumpSystemFields> {
 public: 
  enum domain 
  {
Name, ControlMethod, CoolingLoopInletNodeName, CoolingLoopOutletNodeName, SourceLoopInletNodeName, SourceLoopOutletNodeName, HeatingLoopInletNodeName, HeatingLoopOutletNodeName, AncillaryPower, AncillaryOperationScheduleName,   };
  CentralHeatPumpSystemFields()
   : EnumBase<CentralHeatPumpSystemFields>(Name) {} 
  CentralHeatPumpSystemFields(const std::string &t_name) 
   : EnumBase<CentralHeatPumpSystemFields>(t_name) {} 
  CentralHeatPumpSystemFields(int t_value) 
   : EnumBase<CentralHeatPumpSystemFields>(t_value) {} 
  static std::string enumName() 
  { return "CentralHeatPumpSystemFields"; }
  domain value() const { return static_cast<domain>(EnumBase<CentralHeatPumpSystemFields>::value()); }
   private:
    friend class EnumBase<CentralHeatPumpSystemFields>;
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
{ CentralHeatPumpSystemFields::Name, "Name", "Name"},
{ CentralHeatPumpSystemFields::ControlMethod, "ControlMethod", "Control Method"},
{ CentralHeatPumpSystemFields::CoolingLoopInletNodeName, "CoolingLoopInletNodeName", "Cooling Loop Inlet Node Name"},
{ CentralHeatPumpSystemFields::CoolingLoopOutletNodeName, "CoolingLoopOutletNodeName", "Cooling Loop Outlet Node Name"},
{ CentralHeatPumpSystemFields::SourceLoopInletNodeName, "SourceLoopInletNodeName", "Source Loop Inlet Node Name"},
{ CentralHeatPumpSystemFields::SourceLoopOutletNodeName, "SourceLoopOutletNodeName", "Source Loop Outlet Node Name"},
{ CentralHeatPumpSystemFields::HeatingLoopInletNodeName, "HeatingLoopInletNodeName", "Heating Loop Inlet Node Name"},
{ CentralHeatPumpSystemFields::HeatingLoopOutletNodeName, "HeatingLoopOutletNodeName", "Heating Loop Outlet Node Name"},
{ CentralHeatPumpSystemFields::AncillaryPower, "AncillaryPower", "Ancillary Power"},
{ CentralHeatPumpSystemFields::AncillaryOperationScheduleName, "AncillaryOperationScheduleName", "Ancillary Operation Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const CentralHeatPumpSystemFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<CentralHeatPumpSystemFields> OptionalCentralHeatPumpSystemFields ;
#endif

/** \class CentralHeatPumpSystemExtensibleFields
 *  \brief Enumeration of CentralHeatPumpSystem's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(CentralHeatPumpSystemExtensibleFields, )
#else
class CentralHeatPumpSystemExtensibleFields: public ::EnumBase<CentralHeatPumpSystemExtensibleFields> {
 public: 
  enum domain 
  {
ChillerHeaterModulesPerformanceComponentObjectType, ChillerHeaterModulesPerformanceComponentName, ChillerHeaterModulesControlScheduleName, NumberofChillerHeaterModules,   };
  CentralHeatPumpSystemExtensibleFields()
   : EnumBase<CentralHeatPumpSystemExtensibleFields>(ChillerHeaterModulesPerformanceComponentObjectType) {} 
  CentralHeatPumpSystemExtensibleFields(const std::string &t_name) 
   : EnumBase<CentralHeatPumpSystemExtensibleFields>(t_name) {} 
  CentralHeatPumpSystemExtensibleFields(int t_value) 
   : EnumBase<CentralHeatPumpSystemExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "CentralHeatPumpSystemExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<CentralHeatPumpSystemExtensibleFields>::value()); }
   private:
    friend class EnumBase<CentralHeatPumpSystemExtensibleFields>;
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
{ CentralHeatPumpSystemExtensibleFields::ChillerHeaterModulesPerformanceComponentObjectType, "ChillerHeaterModulesPerformanceComponentObjectType", "Chiller Heater Modules Performance Component Object Type"},
{ CentralHeatPumpSystemExtensibleFields::ChillerHeaterModulesPerformanceComponentName, "ChillerHeaterModulesPerformanceComponentName", "Chiller Heater Modules Performance Component Name"},
{ CentralHeatPumpSystemExtensibleFields::ChillerHeaterModulesControlScheduleName, "ChillerHeaterModulesControlScheduleName", "Chiller Heater Modules Control Schedule Name"},
{ CentralHeatPumpSystemExtensibleFields::NumberofChillerHeaterModules, "NumberofChillerHeaterModules", "Number of Chiller Heater Modules"},
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
  inline std::ostream &operator<<(std::ostream &os, const CentralHeatPumpSystemExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<CentralHeatPumpSystemExtensibleFields> OptionalCentralHeatPumpSystemExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CENTRALHEATPUMPSYSTEM_FIELDENUMS_HXX
