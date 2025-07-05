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

#ifndef UTILITIES_IDD_ROOMAIRSETTINGS_AIRFLOWNETWORK_FIELDENUMS_HXX
#define UTILITIES_IDD_ROOMAIRSETTINGS_AIRFLOWNETWORK_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class RoomAirSettings_AirflowNetworkFields
 *  \brief Enumeration of RoomAirSettings:AirflowNetwork's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(RoomAirSettings_AirflowNetworkFields, )
#else
class RoomAirSettings_AirflowNetworkFields: public ::EnumBase<RoomAirSettings_AirflowNetworkFields> {
 public: 
  enum domain 
  {
Name, ZoneName, ControlPointRoomAirflowNetwork_NodeName,   };
  RoomAirSettings_AirflowNetworkFields()
   : EnumBase<RoomAirSettings_AirflowNetworkFields>(Name) {} 
  RoomAirSettings_AirflowNetworkFields(const std::string &t_name) 
   : EnumBase<RoomAirSettings_AirflowNetworkFields>(t_name) {} 
  RoomAirSettings_AirflowNetworkFields(int t_value) 
   : EnumBase<RoomAirSettings_AirflowNetworkFields>(t_value) {} 
  static std::string enumName() 
  { return "RoomAirSettings_AirflowNetworkFields"; }
  domain value() const { return static_cast<domain>(EnumBase<RoomAirSettings_AirflowNetworkFields>::value()); }
   private:
    friend class EnumBase<RoomAirSettings_AirflowNetworkFields>;
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
{ RoomAirSettings_AirflowNetworkFields::Name, "Name", "Name"},
{ RoomAirSettings_AirflowNetworkFields::ZoneName, "ZoneName", "Zone Name"},
{ RoomAirSettings_AirflowNetworkFields::ControlPointRoomAirflowNetwork_NodeName, "ControlPointRoomAirflowNetwork_NodeName", "Control Point RoomAirflowNetwork:Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const RoomAirSettings_AirflowNetworkFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<RoomAirSettings_AirflowNetworkFields> OptionalRoomAirSettings_AirflowNetworkFields ;
#endif

/** \class RoomAirSettings_AirflowNetworkExtensibleFields
 *  \brief Enumeration of RoomAirSettings:AirflowNetwork's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(RoomAirSettings_AirflowNetworkExtensibleFields, )
#else
class RoomAirSettings_AirflowNetworkExtensibleFields: public ::EnumBase<RoomAirSettings_AirflowNetworkExtensibleFields> {
 public: 
  enum domain 
  {
RoomAirflowNetwork_NodeName,   };
  RoomAirSettings_AirflowNetworkExtensibleFields()
   : EnumBase<RoomAirSettings_AirflowNetworkExtensibleFields>(RoomAirflowNetwork_NodeName) {} 
  RoomAirSettings_AirflowNetworkExtensibleFields(const std::string &t_name) 
   : EnumBase<RoomAirSettings_AirflowNetworkExtensibleFields>(t_name) {} 
  RoomAirSettings_AirflowNetworkExtensibleFields(int t_value) 
   : EnumBase<RoomAirSettings_AirflowNetworkExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "RoomAirSettings_AirflowNetworkExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<RoomAirSettings_AirflowNetworkExtensibleFields>::value()); }
   private:
    friend class EnumBase<RoomAirSettings_AirflowNetworkExtensibleFields>;
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
{ RoomAirSettings_AirflowNetworkExtensibleFields::RoomAirflowNetwork_NodeName, "RoomAirflowNetwork_NodeName", "RoomAirflowNetwork:Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const RoomAirSettings_AirflowNetworkExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<RoomAirSettings_AirflowNetworkExtensibleFields> OptionalRoomAirSettings_AirflowNetworkExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ROOMAIRSETTINGS_AIRFLOWNETWORK_FIELDENUMS_HXX
