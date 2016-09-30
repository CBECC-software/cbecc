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

#ifndef UTILITIES_IDD_WATERUSE_CONNECTIONS_FIELDENUMS_HXX
#define UTILITIES_IDD_WATERUSE_CONNECTIONS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WaterUse_ConnectionsFields
 *  \brief Enumeration of WaterUse:Connections's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WaterUse_ConnectionsFields, )
#else
class WaterUse_ConnectionsFields: public ::EnumBase<WaterUse_ConnectionsFields> {
 public: 
  enum domain 
  {
Name, InletNodeName, OutletNodeName, SupplyWaterStorageTankName, ReclamationWaterStorageTankName, HotWaterSupplyTemperatureScheduleName, ColdWaterSupplyTemperatureScheduleName, DrainWaterHeatExchangerType, DrainWaterHeatExchangerDestination, DrainWaterHeatExchangerUFactorTimesArea,   };
  WaterUse_ConnectionsFields()
   : EnumBase<WaterUse_ConnectionsFields>(Name) {} 
  WaterUse_ConnectionsFields(const std::string &t_name) 
   : EnumBase<WaterUse_ConnectionsFields>(t_name) {} 
  WaterUse_ConnectionsFields(int t_value) 
   : EnumBase<WaterUse_ConnectionsFields>(t_value) {} 
  static std::string enumName() 
  { return "WaterUse_ConnectionsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WaterUse_ConnectionsFields>::value()); }
   private:
    friend class EnumBase<WaterUse_ConnectionsFields>;
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
{ WaterUse_ConnectionsFields::Name, "Name", "Name"},
{ WaterUse_ConnectionsFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ WaterUse_ConnectionsFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ WaterUse_ConnectionsFields::SupplyWaterStorageTankName, "SupplyWaterStorageTankName", "Supply Water Storage Tank Name"},
{ WaterUse_ConnectionsFields::ReclamationWaterStorageTankName, "ReclamationWaterStorageTankName", "Reclamation Water Storage Tank Name"},
{ WaterUse_ConnectionsFields::HotWaterSupplyTemperatureScheduleName, "HotWaterSupplyTemperatureScheduleName", "Hot Water Supply Temperature Schedule Name"},
{ WaterUse_ConnectionsFields::ColdWaterSupplyTemperatureScheduleName, "ColdWaterSupplyTemperatureScheduleName", "Cold Water Supply Temperature Schedule Name"},
{ WaterUse_ConnectionsFields::DrainWaterHeatExchangerType, "DrainWaterHeatExchangerType", "Drain Water Heat Exchanger Type"},
{ WaterUse_ConnectionsFields::DrainWaterHeatExchangerDestination, "DrainWaterHeatExchangerDestination", "Drain Water Heat Exchanger Destination"},
{ WaterUse_ConnectionsFields::DrainWaterHeatExchangerUFactorTimesArea, "DrainWaterHeatExchangerUFactorTimesArea", "Drain Water Heat Exchanger U-Factor Times Area"},
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
  inline std::ostream &operator<<(std::ostream &os, const WaterUse_ConnectionsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WaterUse_ConnectionsFields> OptionalWaterUse_ConnectionsFields ;
#endif

/** \class WaterUse_ConnectionsExtensibleFields
 *  \brief Enumeration of WaterUse:Connections's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(WaterUse_ConnectionsExtensibleFields, )
#else
class WaterUse_ConnectionsExtensibleFields: public ::EnumBase<WaterUse_ConnectionsExtensibleFields> {
 public: 
  enum domain 
  {
WaterUseEquipmentName,   };
  WaterUse_ConnectionsExtensibleFields()
   : EnumBase<WaterUse_ConnectionsExtensibleFields>(WaterUseEquipmentName) {} 
  WaterUse_ConnectionsExtensibleFields(const std::string &t_name) 
   : EnumBase<WaterUse_ConnectionsExtensibleFields>(t_name) {} 
  WaterUse_ConnectionsExtensibleFields(int t_value) 
   : EnumBase<WaterUse_ConnectionsExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "WaterUse_ConnectionsExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WaterUse_ConnectionsExtensibleFields>::value()); }
   private:
    friend class EnumBase<WaterUse_ConnectionsExtensibleFields>;
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
{ WaterUse_ConnectionsExtensibleFields::WaterUseEquipmentName, "WaterUseEquipmentName", "Water Use Equipment Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const WaterUse_ConnectionsExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WaterUse_ConnectionsExtensibleFields> OptionalWaterUse_ConnectionsExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WATERUSE_CONNECTIONS_FIELDENUMS_HXX
