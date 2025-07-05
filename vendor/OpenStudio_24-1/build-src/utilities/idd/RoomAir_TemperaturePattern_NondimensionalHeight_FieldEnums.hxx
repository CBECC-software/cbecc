/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

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
