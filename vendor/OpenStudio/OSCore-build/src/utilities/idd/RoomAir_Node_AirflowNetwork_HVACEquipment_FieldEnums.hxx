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

#ifndef UTILITIES_IDD_ROOMAIR_NODE_AIRFLOWNETWORK_HVACEQUIPMENT_FIELDENUMS_HXX
#define UTILITIES_IDD_ROOMAIR_NODE_AIRFLOWNETWORK_HVACEQUIPMENT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class RoomAir_Node_AirflowNetwork_HVACEquipmentFields
 *  \brief Enumeration of RoomAir:Node:AirflowNetwork:HVACEquipment's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(RoomAir_Node_AirflowNetwork_HVACEquipmentFields, )
#else
class RoomAir_Node_AirflowNetwork_HVACEquipmentFields: public ::EnumBase<RoomAir_Node_AirflowNetwork_HVACEquipmentFields> {
 public: 
  enum domain 
  {
Name,   };
  RoomAir_Node_AirflowNetwork_HVACEquipmentFields()
   : EnumBase<RoomAir_Node_AirflowNetwork_HVACEquipmentFields>(Name) {} 
  RoomAir_Node_AirflowNetwork_HVACEquipmentFields(const std::string &t_name) 
   : EnumBase<RoomAir_Node_AirflowNetwork_HVACEquipmentFields>(t_name) {} 
  RoomAir_Node_AirflowNetwork_HVACEquipmentFields(int t_value) 
   : EnumBase<RoomAir_Node_AirflowNetwork_HVACEquipmentFields>(t_value) {} 
  static std::string enumName() 
  { return "RoomAir_Node_AirflowNetwork_HVACEquipmentFields"; }
  domain value() const { return static_cast<domain>(EnumBase<RoomAir_Node_AirflowNetwork_HVACEquipmentFields>::value()); }
   private:
    friend class EnumBase<RoomAir_Node_AirflowNetwork_HVACEquipmentFields>;
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
{ RoomAir_Node_AirflowNetwork_HVACEquipmentFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const RoomAir_Node_AirflowNetwork_HVACEquipmentFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<RoomAir_Node_AirflowNetwork_HVACEquipmentFields> OptionalRoomAir_Node_AirflowNetwork_HVACEquipmentFields ;
#endif

/** \class RoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields
 *  \brief Enumeration of RoomAir:Node:AirflowNetwork:HVACEquipment's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(RoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields, )
#else
class RoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields: public ::EnumBase<RoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields> {
 public: 
  enum domain 
  {
ZoneHVACorAirTerminalEquipmentObjectType, ZoneHVACorAirTerminalEquipmentObjectName, FractionofOutputorSupplyAirfromHVACEquipment, FractionofInputorReturnAirtoHVACEquipment,   };
  RoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields()
   : EnumBase<RoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields>(ZoneHVACorAirTerminalEquipmentObjectType) {} 
  RoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields(const std::string &t_name) 
   : EnumBase<RoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields>(t_name) {} 
  RoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields(int t_value) 
   : EnumBase<RoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "RoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<RoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields>::value()); }
   private:
    friend class EnumBase<RoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields>;
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
{ RoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields::ZoneHVACorAirTerminalEquipmentObjectType, "ZoneHVACorAirTerminalEquipmentObjectType", "ZoneHVAC or Air Terminal Equipment Object Type"},
{ RoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields::ZoneHVACorAirTerminalEquipmentObjectName, "ZoneHVACorAirTerminalEquipmentObjectName", "ZoneHVAC or Air Terminal Equipment Object Name"},
{ RoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields::FractionofOutputorSupplyAirfromHVACEquipment, "FractionofOutputorSupplyAirfromHVACEquipment", "Fraction of Output or Supply Air from HVAC Equipment"},
{ RoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields::FractionofInputorReturnAirtoHVACEquipment, "FractionofInputorReturnAirtoHVACEquipment", "Fraction of Input or Return Air to HVAC Equipment"},
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
  inline std::ostream &operator<<(std::ostream &os, const RoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<RoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields> OptionalRoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ROOMAIR_NODE_AIRFLOWNETWORK_HVACEQUIPMENT_FIELDENUMS_HXX
