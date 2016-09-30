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

#ifndef UTILITIES_IDD_PLANTEQUIPMENTOPERATION_COMPONENTSETPOINT_FIELDENUMS_HXX
#define UTILITIES_IDD_PLANTEQUIPMENTOPERATION_COMPONENTSETPOINT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PlantEquipmentOperation_ComponentSetpointFields
 *  \brief Enumeration of PlantEquipmentOperation:ComponentSetpoint's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PlantEquipmentOperation_ComponentSetpointFields, )
#else
class PlantEquipmentOperation_ComponentSetpointFields: public ::EnumBase<PlantEquipmentOperation_ComponentSetpointFields> {
 public: 
  enum domain 
  {
Name,   };
  PlantEquipmentOperation_ComponentSetpointFields()
   : EnumBase<PlantEquipmentOperation_ComponentSetpointFields>(Name) {} 
  PlantEquipmentOperation_ComponentSetpointFields(const std::string &t_name) 
   : EnumBase<PlantEquipmentOperation_ComponentSetpointFields>(t_name) {} 
  PlantEquipmentOperation_ComponentSetpointFields(int t_value) 
   : EnumBase<PlantEquipmentOperation_ComponentSetpointFields>(t_value) {} 
  static std::string enumName() 
  { return "PlantEquipmentOperation_ComponentSetpointFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PlantEquipmentOperation_ComponentSetpointFields>::value()); }
   private:
    friend class EnumBase<PlantEquipmentOperation_ComponentSetpointFields>;
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
{ PlantEquipmentOperation_ComponentSetpointFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const PlantEquipmentOperation_ComponentSetpointFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PlantEquipmentOperation_ComponentSetpointFields> OptionalPlantEquipmentOperation_ComponentSetpointFields ;
#endif

/** \class PlantEquipmentOperation_ComponentSetpointExtensibleFields
 *  \brief Enumeration of PlantEquipmentOperation:ComponentSetpoint's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(PlantEquipmentOperation_ComponentSetpointExtensibleFields, )
#else
class PlantEquipmentOperation_ComponentSetpointExtensibleFields: public ::EnumBase<PlantEquipmentOperation_ComponentSetpointExtensibleFields> {
 public: 
  enum domain 
  {
EquipmentObjectType, EquipmentName, DemandCalculationNodeName, SetpointNodeName, ComponentFlowRate, OperationType,   };
  PlantEquipmentOperation_ComponentSetpointExtensibleFields()
   : EnumBase<PlantEquipmentOperation_ComponentSetpointExtensibleFields>(EquipmentObjectType) {} 
  PlantEquipmentOperation_ComponentSetpointExtensibleFields(const std::string &t_name) 
   : EnumBase<PlantEquipmentOperation_ComponentSetpointExtensibleFields>(t_name) {} 
  PlantEquipmentOperation_ComponentSetpointExtensibleFields(int t_value) 
   : EnumBase<PlantEquipmentOperation_ComponentSetpointExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "PlantEquipmentOperation_ComponentSetpointExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PlantEquipmentOperation_ComponentSetpointExtensibleFields>::value()); }
   private:
    friend class EnumBase<PlantEquipmentOperation_ComponentSetpointExtensibleFields>;
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
{ PlantEquipmentOperation_ComponentSetpointExtensibleFields::EquipmentObjectType, "EquipmentObjectType", "Equipment Object Type"},
{ PlantEquipmentOperation_ComponentSetpointExtensibleFields::EquipmentName, "EquipmentName", "Equipment Name"},
{ PlantEquipmentOperation_ComponentSetpointExtensibleFields::DemandCalculationNodeName, "DemandCalculationNodeName", "Demand Calculation Node Name"},
{ PlantEquipmentOperation_ComponentSetpointExtensibleFields::SetpointNodeName, "SetpointNodeName", "Setpoint Node Name"},
{ PlantEquipmentOperation_ComponentSetpointExtensibleFields::ComponentFlowRate, "ComponentFlowRate", "Component Flow Rate"},
{ PlantEquipmentOperation_ComponentSetpointExtensibleFields::OperationType, "OperationType", "Operation Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const PlantEquipmentOperation_ComponentSetpointExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PlantEquipmentOperation_ComponentSetpointExtensibleFields> OptionalPlantEquipmentOperation_ComponentSetpointExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PLANTEQUIPMENTOPERATION_COMPONENTSETPOINT_FIELDENUMS_HXX
