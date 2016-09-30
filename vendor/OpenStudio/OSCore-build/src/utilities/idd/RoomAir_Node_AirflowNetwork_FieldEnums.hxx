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

#ifndef UTILITIES_IDD_ROOMAIR_NODE_AIRFLOWNETWORK_FIELDENUMS_HXX
#define UTILITIES_IDD_ROOMAIR_NODE_AIRFLOWNETWORK_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class RoomAir_Node_AirflowNetworkFields
 *  \brief Enumeration of RoomAir:Node:AirflowNetwork's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(RoomAir_Node_AirflowNetworkFields, )
#else
class RoomAir_Node_AirflowNetworkFields: public ::EnumBase<RoomAir_Node_AirflowNetworkFields> {
 public: 
  enum domain 
  {
Name, ZoneName, FractionofZoneAirVolume, RoomAir_Node_AirflowNetwork_AdjacentSurfaceListName, RoomAir_Node_AirflowNetwork_InternalGainsName, RoomAir_Node_AirflowNetwork_HVACEquipmentName,   };
  RoomAir_Node_AirflowNetworkFields()
   : EnumBase<RoomAir_Node_AirflowNetworkFields>(Name) {} 
  RoomAir_Node_AirflowNetworkFields(const std::string &t_name) 
   : EnumBase<RoomAir_Node_AirflowNetworkFields>(t_name) {} 
  RoomAir_Node_AirflowNetworkFields(int t_value) 
   : EnumBase<RoomAir_Node_AirflowNetworkFields>(t_value) {} 
  static std::string enumName() 
  { return "RoomAir_Node_AirflowNetworkFields"; }
  domain value() const { return static_cast<domain>(EnumBase<RoomAir_Node_AirflowNetworkFields>::value()); }
   private:
    friend class EnumBase<RoomAir_Node_AirflowNetworkFields>;
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
{ RoomAir_Node_AirflowNetworkFields::Name, "Name", "Name"},
{ RoomAir_Node_AirflowNetworkFields::ZoneName, "ZoneName", "Zone Name"},
{ RoomAir_Node_AirflowNetworkFields::FractionofZoneAirVolume, "FractionofZoneAirVolume", "Fraction of Zone Air Volume"},
{ RoomAir_Node_AirflowNetworkFields::RoomAir_Node_AirflowNetwork_AdjacentSurfaceListName, "RoomAir_Node_AirflowNetwork_AdjacentSurfaceListName", "RoomAir:Node:AirflowNetwork:AdjacentSurfaceList Name"},
{ RoomAir_Node_AirflowNetworkFields::RoomAir_Node_AirflowNetwork_InternalGainsName, "RoomAir_Node_AirflowNetwork_InternalGainsName", "RoomAir:Node:AirflowNetwork:InternalGains Name"},
{ RoomAir_Node_AirflowNetworkFields::RoomAir_Node_AirflowNetwork_HVACEquipmentName, "RoomAir_Node_AirflowNetwork_HVACEquipmentName", "RoomAir:Node:AirflowNetwork:HVACEquipment Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const RoomAir_Node_AirflowNetworkFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<RoomAir_Node_AirflowNetworkFields> OptionalRoomAir_Node_AirflowNetworkFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ROOMAIR_NODE_AIRFLOWNETWORK_FIELDENUMS_HXX
