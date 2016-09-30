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

#ifndef UTILITIES_IDD_ROOMAIR_TEMPERATUREPATTERN_NONDIMENSIONALHEIGHT_FIELDENUMS_HXX
#define UTILITIES_IDD_ROOMAIR_TEMPERATUREPATTERN_NONDIMENSIONALHEIGHT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class RoomAir_TemperaturePattern_NondimensionalHeightFields
 *  \brief Enumeration of RoomAir:TemperaturePattern:NondimensionalHeight's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(RoomAir_TemperaturePattern_NondimensionalHeightFields, )
#else
class RoomAir_TemperaturePattern_NondimensionalHeightFields: public ::EnumBase<RoomAir_TemperaturePattern_NondimensionalHeightFields> {
 public: 
  enum domain 
  {
Name, ControlIntegerforPatternControlScheduleName, ThermostatOffset, ReturnAirOffset, ExhaustAirOffset,   };
  RoomAir_TemperaturePattern_NondimensionalHeightFields()
   : EnumBase<RoomAir_TemperaturePattern_NondimensionalHeightFields>(Name) {} 
  RoomAir_TemperaturePattern_NondimensionalHeightFields(const std::string &t_name) 
   : EnumBase<RoomAir_TemperaturePattern_NondimensionalHeightFields>(t_name) {} 
  RoomAir_TemperaturePattern_NondimensionalHeightFields(int t_value) 
   : EnumBase<RoomAir_TemperaturePattern_NondimensionalHeightFields>(t_value) {} 
  static std::string enumName() 
  { return "RoomAir_TemperaturePattern_NondimensionalHeightFields"; }
  domain value() const { return static_cast<domain>(EnumBase<RoomAir_TemperaturePattern_NondimensionalHeightFields>::value()); }
   private:
    friend class EnumBase<RoomAir_TemperaturePattern_NondimensionalHeightFields>;
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
{ RoomAir_TemperaturePattern_NondimensionalHeightFields::Name, "Name", "Name"},
{ RoomAir_TemperaturePattern_NondimensionalHeightFields::ControlIntegerforPatternControlScheduleName, "ControlIntegerforPatternControlScheduleName", "Control Integer for Pattern Control Schedule Name"},
{ RoomAir_TemperaturePattern_NondimensionalHeightFields::ThermostatOffset, "ThermostatOffset", "Thermostat Offset"},
{ RoomAir_TemperaturePattern_NondimensionalHeightFields::ReturnAirOffset, "ReturnAirOffset", "Return Air Offset"},
{ RoomAir_TemperaturePattern_NondimensionalHeightFields::ExhaustAirOffset, "ExhaustAirOffset", "Exhaust Air Offset"},
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
  inline std::ostream &operator<<(std::ostream &os, const RoomAir_TemperaturePattern_NondimensionalHeightFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<RoomAir_TemperaturePattern_NondimensionalHeightFields> OptionalRoomAir_TemperaturePattern_NondimensionalHeightFields ;
#endif

/** \class RoomAir_TemperaturePattern_NondimensionalHeightExtensibleFields
 *  \brief Enumeration of RoomAir:TemperaturePattern:NondimensionalHeight's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(RoomAir_TemperaturePattern_NondimensionalHeightExtensibleFields, )
#else
class RoomAir_TemperaturePattern_NondimensionalHeightExtensibleFields: public ::EnumBase<RoomAir_TemperaturePattern_NondimensionalHeightExtensibleFields> {
 public: 
  enum domain 
  {
PairZetaNondimensionalHeight, PairDeltaAdjacentAirTemperature,   };
  RoomAir_TemperaturePattern_NondimensionalHeightExtensibleFields()
   : EnumBase<RoomAir_TemperaturePattern_NondimensionalHeightExtensibleFields>(PairZetaNondimensionalHeight) {} 
  RoomAir_TemperaturePattern_NondimensionalHeightExtensibleFields(const std::string &t_name) 
   : EnumBase<RoomAir_TemperaturePattern_NondimensionalHeightExtensibleFields>(t_name) {} 
  RoomAir_TemperaturePattern_NondimensionalHeightExtensibleFields(int t_value) 
   : EnumBase<RoomAir_TemperaturePattern_NondimensionalHeightExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "RoomAir_TemperaturePattern_NondimensionalHeightExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<RoomAir_TemperaturePattern_NondimensionalHeightExtensibleFields>::value()); }
   private:
    friend class EnumBase<RoomAir_TemperaturePattern_NondimensionalHeightExtensibleFields>;
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
{ RoomAir_TemperaturePattern_NondimensionalHeightExtensibleFields::PairZetaNondimensionalHeight, "PairZetaNondimensionalHeight", "Pair Zeta Nondimensional Height"},
{ RoomAir_TemperaturePattern_NondimensionalHeightExtensibleFields::PairDeltaAdjacentAirTemperature, "PairDeltaAdjacentAirTemperature", "Pair Delta Adjacent Air Temperature"},
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
  inline std::ostream &operator<<(std::ostream &os, const RoomAir_TemperaturePattern_NondimensionalHeightExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<RoomAir_TemperaturePattern_NondimensionalHeightExtensibleFields> OptionalRoomAir_TemperaturePattern_NondimensionalHeightExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ROOMAIR_TEMPERATUREPATTERN_NONDIMENSIONALHEIGHT_FIELDENUMS_HXX
